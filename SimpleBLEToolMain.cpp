/***************************************************************
 * Name:      SimpleBLEToolMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    HYH (2229388563@qq.com)
 * Created:   2022-09-13
 * Copyright: HYH (hyhsystem.cn)
 * License:
 **************************************************************/

#include "simpleble/Adapter.h"
#include "simpleble/PeripheralSafe.h"
#include "simpleble/Utils.h"
#include "simpleble/Logging.h"
#include <wx/treectrl.h>
#include "BLERSSIDialog.h"
#include "BLEPeripheralDialog.h"
#include "ble_company_id.h"
/*
wxTreeCtrl的item
*/

class wxTreeCtrlAdapterItemData:public wxTreeItemData
{
public:
    SimpleBLE::Adapter adapter;
    wxTreeCtrlAdapterItemData(SimpleBLE::Adapter &_adapter):adapter(_adapter)
    {

    }
    virtual ~wxTreeCtrlAdapterItemData()
    {
        if(adapter.scan_is_active())
        {
            adapter.scan_stop();
        }
        adapter.set_callback_on_scan_start([]() {});
        adapter.set_callback_on_scan_stop([]() {});
        adapter.set_callback_on_scan_updated([](SimpleBLE::Peripheral) {});
        adapter.set_callback_on_scan_found([](SimpleBLE::Peripheral) {});
    }
};
class wxTreeCtrlAdapterPerhItemData:public wxTreeItemData
{
public:
    SimpleBLE::Peripheral Perh;
    BLERSSIDialog *rssi_dlg;
    BLEPeripheralDialog *perh_dlg;
    wxTreeCtrlAdapterPerhItemData(SimpleBLE::Peripheral _Perh):Perh(_Perh)
    {
        rssi_dlg=NULL;
        perh_dlg=NULL;
    }
    virtual ~wxTreeCtrlAdapterPerhItemData()
    {
        if(rssi_dlg!=NULL)
        {
            rssi_dlg->Close();
        }
        if(perh_dlg!=NULL)
        {
            perh_dlg->Close();
        }
    }
};

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "SimpleBLEToolMain.h"
#include "wx/log.h"
#include "wx/menu.h"

SimpleBLEToolFrame::SimpleBLEToolFrame(wxFrame *frame)
    : GUIFrame(frame)
{
    Centre();

    {
        wxLog::EnableLogging(true);
        {
            //设置日志窗口
            wxLogTextCtrl *logger=new wxLogTextCtrl(m_textCtrlLog);
            wxLog::SetActiveTarget(logger);
        }
    }

    {
        //设定simpleBLE的日志系统
        auto cb=[](SimpleBLE::Logging::Level lv, const std::string& module, const std::string& file, uint32_t line, const std::string& function, const std::string& message) ->void
        {
            wxString log=wxString(_T("SimpleBLE日志:"))+"\r\n";
            log+=wxString(_T("\tLevel:"))+wxString::FromCDouble(lv)+"\r\n";
            log+=wxString(_T("\tModule:"))+module+"\t";
            log+=wxString(file+_T(":"))+wxString::FromDouble(line)+"\r\n";
            log+=wxString(_T("\tfunction:"))+function+"\r\n";
            log+=message;
            wxLogMessage(log);
        };

        SimpleBLE::Logging::Logger::get()->set_callback(cb);
        SimpleBLE::Logging::Logger::get()->set_level(SimpleBLE::Logging::VERBOSE);

    }

    wxLogMessage(_T("程序已启动!"));

    //更新BLE适配器列表
    UpdateBLEAdapterList();
}

SimpleBLEToolFrame::~SimpleBLEToolFrame()
{
    m_treeCtrl_adapter->DeleteAllItems();
    wxLog::EnableLogging(false);
}

void SimpleBLEToolFrame::OnClose(wxCloseEvent &event)
{
    Destroy();
}

void SimpleBLEToolFrame::OnQuit(wxCommandEvent &event)
{
    Destroy();
}

void SimpleBLEToolFrame::OnAbout(wxCommandEvent &event)
{
    GUIAboutDialog dlg(this);
    dlg.ShowModal();
}

void SimpleBLEToolFrame::OnMenuClose( wxCommandEvent& event )
{
    OnQuit(event);
}
void SimpleBLEToolFrame::OnMenuAbout( wxCommandEvent& event )
{
    OnAbout(event);
}

void SimpleBLEToolFrame::OnMenuReFreshAdapterList( wxCommandEvent& event )
{
    UpdateBLEAdapterList();
}

void SimpleBLEToolFrame::OnTreeAdapterRightClick( wxTreeEvent& event )
{
    wxTreeItemData *data=dynamic_cast<wxTreeItemData *>(event.GetClientObject());
    if(data!=NULL)
    {
        m_treeCtrl_adapter->SelectItem(event.GetItem());
        {
            wxTreeCtrlAdapterItemData * _Data=dynamic_cast<wxTreeCtrlAdapterItemData *>(data);
            if(_Data!=NULL)
            {
                SimpleBLE::Adapter  adapter=_Data->adapter;
                wxMenu menu;
                {
                    if(adapter.scan_is_active())
                    {
                        auto menufunc=[&]( wxCommandEvent& event )
                        {
                            adapter.scan_stop();
                        };
                        wxMenuItem *item=menu.Append(1000,_T("停止扫描"));
                        menu.Bind(wxEVT_COMMAND_MENU_SELECTED,menufunc,item->GetId(),item->GetId());

                    }
                    else
                    {
                        auto menufunc=[&]( wxCommandEvent& event )
                        {
                            {
                                std::lock_guard<std::mutex> lock(PerhList_Lock);
                                if(PerhList.find(adapter.address())!=PerhList.end())
                                {
                                    for(auto it:PerhList[adapter.address()])
                                    {
                                        m_treeCtrl_adapter->Delete(it.second.perh);
                                    }
                                    PerhList[adapter.address()].clear();
                                }

                            }
                            adapter.scan_start();
                        };
                        wxMenuItem *item=menu.Append(1000,_T("重新开始扫描"));
                        menu.Bind(wxEVT_COMMAND_MENU_SELECTED,menufunc,item->GetId(),item->GetId());
                    }
                    menu.AppendSeparator();
                }
                PopupMenu(&menu);
            }
        }
        {
            wxTreeCtrlAdapterPerhItemData * _Data=dynamic_cast<wxTreeCtrlAdapterPerhItemData *>(data);
            if(_Data!=NULL)
            {
                wxMenu menu;
                {
                    auto menufunc=[&]( wxCommandEvent& event )
                    {
                        if(_Data->rssi_dlg==NULL)
                        {
                            _Data->rssi_dlg=new BLERSSIDialog(this);
                            _Data->rssi_dlg->SetBLEPerh(_Data->Perh);
                            _Data->rssi_dlg->SetOnClose([=]()
                            {
                                _Data->rssi_dlg=NULL;
                            });
                        }
                        _Data->rssi_dlg->Show();
                        _Data->rssi_dlg->SetFocus();
                    };
                    wxMenuItem *item=menu.Append(1000,_T("实时RSSI数据"));
                    menu.Bind(wxEVT_COMMAND_MENU_SELECTED,menufunc,item->GetId(),item->GetId());
                }
                menu.AppendSeparator();

                {
                    auto menufunc=[&]( wxCommandEvent& event )
                    {
                        if(_Data->perh_dlg==NULL)
                        {
                            _Data->perh_dlg=new BLEPeripheralDialog(this);
                            _Data->perh_dlg->SetBLEPerh(_Data->Perh);
                            _Data->perh_dlg->SetOnClose([=]()
                            {
                                _Data->perh_dlg=NULL;
                            });
                        }
                        _Data->perh_dlg->Show();
                        _Data->perh_dlg->SetFocus();

                    };
                    wxMenuItem *item=menu.Append(1001,_T("外设详情"));
                    menu.Bind(wxEVT_COMMAND_MENU_SELECTED,menufunc,item->GetId(),item->GetId());
                }
                menu.AppendSeparator();
                {
                    auto menufunc=[&]( wxCommandEvent& event )
                    {
                        for(auto data:_Data->Perh.manufacturer_data())
                        {
                            uint16_t id=data.first;//厂商ID
                            std::string Dat=data.second;//数据
                            std::string hexstr;
                            {
                                for(size_t i=0; i<Dat.length(); i++)
                                {
                                    char buff[10]= {0};
                                    snprintf(buff,sizeof(buff)-1,"%02X ",(uint8_t)(Dat.c_str()[i]));
                                    hexstr+=buff;
                                }
                            }

                            wxLogMessage(_T("%s 厂商自定义广播数据:\r\n\t厂商ID:%04X [ %s ]\r\n\t数据(%d Bytes):%s\r\n\t数据(HEX):%s\r\n"),wxString(_Data->Perh.address()),id,wxString::FromUTF8(ble_find_company_by_id(id).desc),(int)Dat.length(),wxString::FromUTF8(Dat.c_str(),Dat.length()),wxString(hexstr));
                        }
                    };
                    wxMenuItem *item=menu.Append(1002,_T("制造商自定义数据(广播包/扫描响应包)"));
                    menu.Bind(wxEVT_COMMAND_MENU_SELECTED,menufunc,item->GetId(),item->GetId());
                }
                menu.AppendSeparator();

                PopupMenu(&menu);
            }
        }
    }
}

void SimpleBLEToolFrame::OnUpdateTimer( wxTimerEvent& event )
{
    ProcessUpdateUIFunction();
}

void SimpleBLEToolFrame::UpdateBLEAdapterList()
{
    auto cb=[&]()
    {
        {

            m_treeCtrl_adapter->DeleteAllItems();
            {
                std::lock_guard<std::mutex> lock(PerhList_Lock);
                PerhList.clear();
            }
            m_treeCtrl_adapter->AddRoot(_T("Adapter"));

            auto adapter_list = SimpleBLE::Adapter::get_adapters();

            if (adapter_list.empty())
            {
                wxLogMessage(_T("未找到任何适配器!"));
            }

            for (auto& adapter : adapter_list)
            {
                wxString adapterstr= wxString(_T("适配器: ")) + adapter.identifier()+" [" + adapter.address() + "]" ;
                wxLogMessage(adapterstr);
                wxTreeItemId adaptertreeid=m_treeCtrl_adapter->AppendItem(m_treeCtrl_adapter->GetRootItem(),wxString(adapterstr),-1,-1,new wxTreeCtrlAdapterItemData(adapter));
                {
                    auto cb=[=]()
                    {
                        wxLogMessage(adapterstr+_T(" 已开始扫描!!!"));
                    };
                    adapter.set_callback_on_scan_start(cb);
                }

                {
                    auto cb=[=]()
                    {
                        wxLogMessage(adapterstr+_T(" 已停止扫描!!!"));
                    };
                    adapter.set_callback_on_scan_stop(cb);
                }

                {
                    wxString adapter_addr=adapter.address();
                    auto cb=[=](SimpleBLE::Peripheral perh)
                    {

                        SimpleBLE::Safe::Peripheral Perh(perh);
                        wxString perhstr=wxString(perh.identifier()) + " [" <<  perh.address() + "] ";
                        wxLogMessage(adapterstr+_T(" 找到设备 ")+perhstr);
                        {
                            wxString detail=wxString(_T("\r\n\t外设:"))+perhstr+"\r\n";
                            detail+=wxString(_T("\tRSSI:"))+std::to_string(perh.rssi())+"\r\n";
                            if(Perh.is_paired().has_value())
                            {
                                detail+=wxString(perh.is_paired()?_T("\t已配对"):_T("\t未配对"))+"\r\n";
                            }
                            if(Perh.is_connectable().has_value())
                            {
                                detail+=wxString(perh.is_connectable()?_T("\t可连接"):_T("\t不可连接"))+"\r\n";
                            }

                            wxLogMessage(detail);
                        }
                        wxString perh_addr=perh.address();
                        auto updateui=[=]()
                        {
                            wxTreeItemId wxtreeperhid=m_treeCtrl_adapter->AppendItem(adaptertreeid,perhstr,-1,-1,new wxTreeCtrlAdapterPerhItemData(perh));
                            m_treeCtrl_adapter->Expand(adaptertreeid);
                            {
                                //设置ID
                                std::lock_guard<std::mutex> lock(PerhList_Lock);
                                wxTreeCtrlAdapterPerhID ID=
                                {
                                    adaptertreeid,
                                    wxtreeperhid
                                };
                                this->PerhList[adapter_addr][perh_addr]=ID;
                            }
                        };
                        AddUpdateUIFunciton(updateui);
                    };
                    adapter.set_callback_on_scan_found(cb);
                }

                {
                    wxString adapter_addr=adapter.address();
                    auto cb=[=](SimpleBLE::Peripheral perh)
                    {
                        {
                            //调用回调函数
                            std::lock_guard<std::mutex> lock(ScanUpdateMapLock);
                            for(auto pair:ScanUpdateMap)
                            {
                                if(pair.second!=NULL)
                                {
                                    pair.second(perh);
                                }
                            }
                        }
                        std::lock_guard<std::mutex> lock(PerhList_Lock);
                        std::map<wxString,std::map<wxString,wxTreeCtrlAdapterPerhID>> &PerhList=this->PerhList;
                        wxTreeCtrlAdapterPerhID ID;
                        if(PerhList.find(adapter_addr)!=PerhList.end())
                        {
                            if(PerhList[adapter_addr].find(perh.address())!=PerhList[adapter_addr].end())
                            {
                                ID=PerhList[adapter_addr][perh.address()];
                            }
                            else
                            {
                                return;
                            }
                        }
                        else
                        {
                            return;
                        }
                        wxString perhstr=wxString(perh.identifier()) + " [" <<  perh.address() + "] ";
                        auto updateui=[=]()
                        {
                            if(m_treeCtrl_adapter->GetItemText(ID.perh)!=perhstr)
                            {
                                m_treeCtrl_adapter->SetItemText(ID.perh,perhstr);
                                m_treeCtrl_adapter->Expand(ID.adapter);
                            }
                        };
                        AddUpdateUIFunciton(updateui);

                        //wxLogMessage(_T("外设: %s 状态已更新(RSSI:%d)!"),perhstr,(int)perh.rssi());
                    };
                    adapter.set_callback_on_scan_updated(cb);
                }

                adapter.scan_start();
            }

        }

        wxLogMessage(SimpleBLE::Adapter::bluetooth_enabled()?_T("蓝牙已启用!"):_T("蓝牙未启用!"));
    };

    AddUpdateUIFunciton(cb);
}


void SimpleBLEToolFrame::RegisterScanUpdateCallback(void * owner,std::function<void (SimpleBLE::Peripheral)>cb)
{
    std::lock_guard<std::mutex> lock(ScanUpdateMapLock);
    if(owner!=NULL)
    {
        ScanUpdateMap[owner]=cb;
    }
}

void SimpleBLEToolFrame::UnRegistterScanUpdateCallback(void *owner)
{
    std::lock_guard<std::mutex> lock(ScanUpdateMapLock);
    if(ScanUpdateMap.find(owner)!=ScanUpdateMap.end())
    {
        ScanUpdateMap.erase(owner);
    }
}

void SimpleBLEToolFrame::AddUpdateUIFuncitonByOther(std::function<void(void)> func)
{
    AddUpdateUIFunciton(func);
}

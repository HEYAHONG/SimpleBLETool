#include "BLEPeripheralDialog.h"
#include "wx/msgdlg.h"
#include "misc.h"
#include <thread>

#include <wx/treectrl.h>
#include <wx/clipbrd.h>
#include "InputDialog.h"


class wxTreeCtrlPerhItemData:public wxTreeItemData
{
public:
    SimpleBLE::Peripheral perh;
    wxTreeCtrlPerhItemData(SimpleBLE::Peripheral _perh):perh(_perh)
    {

    }
    virtual ~wxTreeCtrlPerhItemData()
    {

    }
};


class wxTreeCtrlServiceItemData:public wxTreeItemData
{
public:
    SimpleBLE::Peripheral perh;
    SimpleBLE::BluetoothUUID ServiceUUID;
    wxTreeCtrlServiceItemData(SimpleBLE::Peripheral _perh,SimpleBLE::BluetoothUUID _ServiceUUID):perh(_perh),ServiceUUID(_ServiceUUID)
    {

    }
    virtual ~wxTreeCtrlServiceItemData()
    {

    }
};


class wxTreeCtrlServiceCharItemData:public wxTreeItemData
{
public:
    SimpleBLE::Peripheral perh;
    SimpleBLE::BluetoothUUID ServiceUUID;
    SimpleBLE::BluetoothUUID CharUUID;
    wxTreeCtrlServiceCharItemData(SimpleBLE::Peripheral _perh,SimpleBLE::BluetoothUUID _ServiceUUID,SimpleBLE::BluetoothUUID _CharUUID):perh(_perh),ServiceUUID(_ServiceUUID),CharUUID(_CharUUID)
    {

    }
    virtual ~wxTreeCtrlServiceCharItemData()
    {
        if(perh.initialized())
        {
            SimpleBLE::Safe::Peripheral _perh(perh);
            _perh.notify(ServiceUUID,CharUUID,[](SimpleBLE::ByteArray payload) {});
            _perh.indicate(ServiceUUID,CharUUID,[](SimpleBLE::ByteArray payload) {});
            _perh.unsubscribe(ServiceUUID,CharUUID);
        }
    }
};

class wxTreeCtrlServiceCharDescItemData:public wxTreeItemData
{
public:
    SimpleBLE::Peripheral perh;
    SimpleBLE::BluetoothUUID ServiceUUID;
    SimpleBLE::BluetoothUUID CharUUID;
    SimpleBLE::BluetoothUUID DescUUID;
    wxTreeCtrlServiceCharDescItemData(SimpleBLE::Peripheral _perh,SimpleBLE::BluetoothUUID _ServiceUUID,SimpleBLE::BluetoothUUID _CharUUID,SimpleBLE::BluetoothUUID _DescUUID):perh(_perh),ServiceUUID(_ServiceUUID),CharUUID(_CharUUID),DescUUID(_DescUUID)
    {

    }
    virtual ~wxTreeCtrlServiceCharDescItemData()
    {

    }
};


extern const char * bluetooth_ico_xpm[];
BLEPeripheralDialog::BLEPeripheralDialog(wxWindow* parent):GUIPeripheral(parent)
{
    SetIcon(bluetooth_ico_xpm);
    mainwindow=dynamic_cast<SimpleBLEToolFrame *>(parent);
    if(mainwindow==NULL)
    {
        wxLogMessage(_T("此窗口必须由主窗口调用"));
        Close();
        return;
    }

}

BLEPeripheralDialog::~BLEPeripheralDialog()
{
    {
        SimpleBLE::Safe::Peripheral perh(Perh);
        if(perh.initialized())
        {
            perh.set_callback_on_connected([]() {});
            perh.set_callback_on_disconnected([]() {});
        }
    }
    if(OnCloseCb!=NULL)
    {
        OnCloseCb();
    }

    if(m_treeCtrl->GetCount()!=0)
    {
        m_treeCtrl->DeleteAllItems();
    }
}


void BLEPeripheralDialog::SetBLEPerh(SimpleBLE::Peripheral _Perh)
{
    Perh=_Perh;
    if(Perh.initialized())
    {
        UpdateStatus();
    }
}

void BLEPeripheralDialog::SetOnClose(std::function<void(void)> OnClose)
{
    OnCloseCb=OnClose;
}

void BLEPeripheralDialog::OnClose( wxCloseEvent& event )
{
    Destroy();
}

void BLEPeripheralDialog::OnUnpair( wxCommandEvent& event )
{
    {
        wxLogMessage(wxString(_T("正在取消配对 "))+Perh.address());
        SimpleBLE::Safe::Peripheral perh(Perh);
        perh.unpair();
        UpdateStatus();
    };
    m_button_unpair->Enable(false);
}
void BLEPeripheralDialog::OnConnect( wxCommandEvent& event )
{
    {
        SimpleBLE::Safe::Peripheral perh(Perh);
        perh.set_callback_on_connected([=]()
        {
            UpdateStatus();
        });
        bool is_connected=perh.connect();
        std::string addr=perh.address().value_or("");
        mainwindow->AddUpdateUIFuncitonByOther([=]()
        {
            wxLogMessage(wxString(_T("正在连接 "))+addr);
            if(!is_connected)
            {
                wxMessageBox(_T("连接失败"),_T("错误"));
            }
        });
    };
    m_button_connect->Enable(false);
}
void BLEPeripheralDialog::OnDisConnect( wxCommandEvent& event )
{
    {
        SimpleBLE::Safe::Peripheral perh(Perh);
        perh.set_callback_on_disconnected([=]()
        {
            UpdateStatus();
        });
        std::string addr=perh.address().value_or("");
        mainwindow->AddUpdateUIFuncitonByOther([=]()
        {
            wxLogMessage(wxString(_T("正在断开连接 "))+Perh.address());
        });
        perh.disconnect();
    };
    m_button_disconnect->Enable(false);
}

void BLEPeripheralDialog::OnTreeItemRightClick( wxTreeEvent& event )
{
    wxTreeItemData *data=dynamic_cast<wxTreeItemData *>(event.GetClientObject());
    if(data!=NULL)
    {
        m_treeCtrl->SelectItem(event.GetItem());
        wxMenu menu;
        SimpleBLE::Safe::Peripheral perh(Perh);

        {
            auto menufunc=[&]( wxCommandEvent& event_menu )
            {
                if (wxTheClipboard->Open())
                {
                    wxTheClipboard->SetData( new wxTextDataObject(m_treeCtrl->GetItemText(event.GetItem())));
                    wxTheClipboard->Close();
                }
            };
            wxMenuItem *item=menu.Append(1000,_T("复制节点名称"));
            menu.Bind(wxEVT_COMMAND_MENU_SELECTED,menufunc,item->GetId(),item->GetId());
        }

        menu.AppendSeparator();

        {
            wxTreeCtrlPerhItemData *_Data=dynamic_cast<wxTreeCtrlPerhItemData *>(data);
            if(_Data!=NULL)
            {
                //设备
            }
        }

        {
            wxTreeCtrlServiceItemData *_Data=dynamic_cast<wxTreeCtrlServiceItemData *>(data);
            if(_Data!=NULL)
            {
                //服务
            }
        }

        {
            wxTreeCtrlServiceCharItemData *_Data=dynamic_cast<wxTreeCtrlServiceCharItemData *>(data);
            if(_Data!=NULL)
            {
                //特征
                {
                    auto menufunc=[&]( wxCommandEvent& event_menu )
                    {

                        std::optional<SimpleBLE::ByteArray> read_data;
                        try
                        {
                            read_data=perh.read(_Data->ServiceUUID,_Data->CharUUID);
                        }
                        catch(...)
                        {
                            wxMessageBox(_T("读取出错!"),_T("错误"));
                        }
                        if(read_data.has_value() && !read_data.value_or("").empty())
                        {
                            std::string str=read_data.value_or("");
                            std::string hexstr;
                            {
                                for(size_t i=0; i<str.length(); i++)
                                {
                                    char buff[10]= {0};
                                    snprintf(buff,sizeof(buff)-1,"%02X ",(int)(str.c_str()[i]));
                                    hexstr+=buff;
                                }
                            }
                            wxLogMessage(wxString(_T("成功读取到设备数据\r\n\t设备:%s\r\n\t服务:%s\r\n\t特征:%s\r\n\t数据:%s\r\n\t数据(HEX):%s")),wxString(_Data->perh.address()),_Data->ServiceUUID,_Data->CharUUID,wxString::FromUTF8(str.c_str(),str.length()),hexstr);
                            wxMessageBox(_T("读取成功,请在主窗口的日志中查看读取结果!"),_T("提示"));
                        }
                        else
                        {
                            wxMessageBox(_T("读取失败或未读到有效数据!"),_T("提示"));
                        }
                    };
                    wxMenuItem *item=menu.Append(1301,_T("读取"));
                    menu.Bind(wxEVT_COMMAND_MENU_SELECTED,menufunc,item->GetId(),item->GetId());
                }

                {
                    auto menufunc=[&]( wxCommandEvent& event_menu )
                    {
                        InputDialog dlg(this);
                        if(wxID_OK==dlg.ShowModal())
                        {
                            std::string str=dlg.GetData();
                            std::string hexstr;
                            {
                                for(size_t i=0; i<str.length(); i++)
                                {
                                    char buff[10]= {0};
                                    snprintf(buff,sizeof(buff)-1,"%02X ",(int)(str.c_str()[i]));
                                    hexstr+=buff;
                                }
                            }
                            wxLogMessage(wxString(_T("准备写入数据到设备\r\n\t设备:%s\r\n\t服务:%s\r\n\t特征:%s\r\n\t数据:%s\r\n\t数据(HEX):%s")),wxString(_Data->perh.address()),_Data->ServiceUUID,_Data->CharUUID,wxString::FromUTF8(str.c_str(),str.length()),hexstr);
                            if(perh.write_request(_Data->ServiceUUID,_Data->CharUUID,str))
                            {
                                wxLogMessage(_T("%s 写入数据成功!"),perh.address().value_or(""));
                                wxMessageBox(_T("写入成功!"),_T("提示"));
                            }
                            else
                            {
                                wxLogMessage(_T("%s 写入数据失败!"),perh.address().value_or(""));
                                wxMessageBox(_T("写入失败!"),_T("错误"));
                            }

                        }
                        else
                        {
                            wxLogMessage(_T("%s 取消输入数据!!"),perh.address().value_or(""));
                        }
                    };
                    wxMenuItem *item=menu.Append(1302,_T("写入请求"));
                    menu.Bind(wxEVT_COMMAND_MENU_SELECTED,menufunc,item->GetId(),item->GetId());
                }

                {
                    auto menufunc=[&]( wxCommandEvent& event_menu )
                    {
                        InputDialog dlg(this);
                        if(wxID_OK==dlg.ShowModal())
                        {
                            std::string str=dlg.GetData();
                            std::string hexstr;
                            {
                                for(size_t i=0; i<str.length(); i++)
                                {
                                    char buff[10]= {0};
                                    snprintf(buff,sizeof(buff)-1,"%02X ",(int)(str.c_str()[i]));
                                    hexstr+=buff;
                                }
                            }
                            wxLogMessage(wxString(_T("准备写入数据到设备\r\n\t设备:%s\r\n\t服务:%s\r\n\t特征:%s\r\n\t数据:%s\r\n\t数据(HEX):%s")),wxString(_Data->perh.address()),_Data->ServiceUUID,_Data->CharUUID,wxString::FromUTF8(str.c_str(),str.length()),hexstr);
                            if(perh.write_command(_Data->ServiceUUID,_Data->CharUUID,str))
                            {
                                wxLogMessage(_T("%s 写入数据成功!"),perh.address().value_or(""));
                                wxMessageBox(_T("写入成功!"),_T("提示"));
                            }
                            else
                            {
                                wxLogMessage(_T("%s 写入数据失败!"),perh.address().value_or(""));
                                wxMessageBox(_T("写入失败!"),_T("错误"));
                            }

                        }
                        else
                        {
                            wxLogMessage(_T("%s 取消输入数据!!"),perh.address().value_or(""));
                        }
                    };
                    wxMenuItem *item=menu.Append(1303,_T("写入命令"));
                    menu.Bind(wxEVT_COMMAND_MENU_SELECTED,menufunc,item->GetId(),item->GetId());
                }

                {
                    auto menufunc=[&]( wxCommandEvent& event_menu )
                    {
                        auto cb=[=](SimpleBLE::ByteArray payload)
                        {
                            std::string str=payload;
                            std::string hexstr;
                            {
                                for(size_t i=0; i<str.length(); i++)
                                {
                                    char buff[10]= {0};
                                    snprintf(buff,sizeof(buff)-1,"%02X ",(int)(str.c_str()[i]));
                                    hexstr+=buff;
                                }
                            }
                            wxLogMessage(wxString(_T("接收到通知数据\r\n\t设备:%s\r\n\t服务:%s\r\n\t特征:%s\r\n\t数据:%s\r\n\t数据(HEX):%s")),wxString(_Data->perh.address()),_Data->ServiceUUID,_Data->CharUUID,wxString::FromUTF8(str.c_str(),str.length()),hexstr);

                        };
                        if(perh.notify(_Data->ServiceUUID,_Data->CharUUID,cb))
                        {
                            wxMessageBox(_T("设置通知数据成功!"),_T("提示"));
                        }
                        else
                        {
                            wxMessageBox(_T("设置通知数据失败!"),_T("错误"));
                        }
                    };
                    wxMenuItem *item=menu.Append(1304,_T("接收通知数据"));
                    menu.Bind(wxEVT_COMMAND_MENU_SELECTED,menufunc,item->GetId(),item->GetId());
                }

                {
                    auto menufunc=[&]( wxCommandEvent& event_menu )
                    {
                        auto cb=[=](SimpleBLE::ByteArray payload)
                        {
                            std::string str=payload;
                            std::string hexstr;
                            {
                                for(size_t i=0; i<str.length(); i++)
                                {
                                    char buff[10]= {0};
                                    snprintf(buff,sizeof(buff)-1,"%02X ",(int)(str.c_str()[i]));
                                    hexstr+=buff;
                                }
                            }
                            wxLogMessage(wxString(_T("接收到指示数据\r\n\t设备:%s\r\n\t服务:%s\r\n\t特征:%s\r\n\t数据:%s\r\n\t数据(HEX):%s")),wxString(_Data->perh.address()),_Data->ServiceUUID,_Data->CharUUID,wxString::FromUTF8(str.c_str(),str.length()),hexstr);

                        };
                        if(perh.notify(_Data->ServiceUUID,_Data->CharUUID,cb))
                        {
                            wxMessageBox(_T("设置指示数据成功!"),_T("提示"));
                        }
                        else
                        {
                            wxMessageBox(_T("设置指示数据失败!"),_T("错误"));
                        }
                    };
                    wxMenuItem *item=menu.Append(1305,_T("接收指示数据"));
                    menu.Bind(wxEVT_COMMAND_MENU_SELECTED,menufunc,item->GetId(),item->GetId());
                }

                {
                    auto menufunc=[&]( wxCommandEvent& event_menu )
                    {
                        if(perh.unsubscribe(_Data->ServiceUUID,_Data->CharUUID))
                        {
                            wxMessageBox(_T("取消数据订阅成功!"),_T("提示"));
                        }
                        else
                        {
                            wxMessageBox(_T("取消数据订阅失败!"),_T("错误"));
                        }
                    };
                    wxMenuItem *item=menu.Append(1306,_T("取消数据订阅"));
                    menu.Bind(wxEVT_COMMAND_MENU_SELECTED,menufunc,item->GetId(),item->GetId());
                }
            }
        }

        {
            wxTreeCtrlServiceCharDescItemData *_Data=dynamic_cast<wxTreeCtrlServiceCharDescItemData *>(data);
            if(_Data!=NULL)
            {
                //描述符

                {
                    auto menufunc=[&]( wxCommandEvent& event_menu )
                    {

                        std::optional<SimpleBLE::ByteArray> read_data;
                        try
                        {
                            read_data=perh.read(_Data->ServiceUUID,_Data->CharUUID,_Data->DescUUID);
                        }
                        catch(...)
                        {
                            wxMessageBox(_T("读取出错!"),_T("错误"));
                            return;
                        }
                        if(read_data.has_value() && !read_data.value_or("").empty())
                        {
                            std::string str=read_data.value();
                            std::string hexstr;
                            {
                                for(size_t i=0; i<str.length(); i++)
                                {
                                    char buff[10]= {0};
                                    snprintf(buff,sizeof(buff)-1,"%02X ",(int)(str.c_str()[i]));
                                    hexstr+=buff;
                                }
                            }
                            wxLogMessage(wxString(_T("成功读取到设备数据\r\n\t设备:%s\r\n\t服务:%s\r\n\t特征:%s\r\n\t描述符:%s\r\n\t数据:%s\r\n\t数据(HEX):%s")),wxString(_Data->perh.address()),_Data->ServiceUUID,_Data->CharUUID,_Data->DescUUID,wxString::FromUTF8(str.c_str(),str.length()),hexstr);
                            wxMessageBox(_T("读取成功,请在主窗口的日志中查看读取结果!"),_T("提示"));
                        }
                        else
                        {
                            wxMessageBox(_T("读取失败或未读到有效数据!"),_T("提示"));
                        }
                    };
                    wxMenuItem *item=menu.Append(1401,_T("读取"));
                    menu.Bind(wxEVT_COMMAND_MENU_SELECTED,menufunc,item->GetId(),item->GetId());
                }

                {
                    auto menufunc=[&]( wxCommandEvent& event_menu )
                    {
                        InputDialog dlg(this);
                        if(wxID_OK==dlg.ShowModal())
                        {
                            std::string str=dlg.GetData();
                            std::string hexstr;
                            {
                                for(size_t i=0; i<str.length(); i++)
                                {
                                    char buff[10]= {0};
                                    snprintf(buff,sizeof(buff)-1,"%02X ",(int)(str.c_str()[i]));
                                    hexstr+=buff;
                                }
                            }
                            wxLogMessage(wxString(_T("准备写入数据到设备\r\n\t设备:%s\r\n\t服务:%s\r\n\t特征:%s\r\n\t描述符:%s\r\n\t数据:%s\r\n\t数据(HEX):%s")),wxString(_Data->perh.address()),_Data->ServiceUUID,_Data->CharUUID,_Data->DescUUID,wxString::FromUTF8(str.c_str(),str.length()),hexstr);
                            if(perh.write(_Data->ServiceUUID,_Data->CharUUID,_Data->DescUUID,str))
                            {
                                wxLogMessage(_T("%s 写入数据成功!"),perh.address().value_or(""));
                                wxMessageBox(_T("写入成功!"),_T("提示"));
                            }
                            else
                            {
                                wxLogMessage(_T("%s 写入数据失败!"),perh.address().value_or(""));
                                wxMessageBox(_T("写入失败!"),_T("错误"));
                            }

                        }
                        else
                        {
                            wxLogMessage(_T("%s 取消输入数据!!"),perh.address().value_or(""));
                        }
                    };
                    wxMenuItem *item=menu.Append(1402,_T("写入"));
                    menu.Bind(wxEVT_COMMAND_MENU_SELECTED,menufunc,item->GetId(),item->GetId());
                }
            }
        }

        PopupMenu(&menu);
    }
}

void BLEPeripheralDialog::UpdateStatus()
{
    if(mainwindow!=NULL)
    {
        mainwindow->AddUpdateUIFuncitonByOther([=]()
        {
            SimpleBLE::Safe::Peripheral perh(Perh);
            SetTitle(wxString(perh.identifier().value_or("")) + " [" <<  perh.address().value_or("") + "] ");
            {
                auto is_paired=perh.is_paired();
                m_button_unpair->Enable(false);
                if(is_paired.has_value())
                {
                    bool val=(*is_paired);
                    m_button_unpair->Enable(false);
                    if(val)
                    {
                        m_button_unpair->Enable(true);
                        m_statusBar->PushStatusText(_T("已配对"),0);
                    }
                    else
                    {
                        m_statusBar->PushStatusText(_T("未配对"),0);
                    }
                }
                else
                {

                    m_statusBar->PushStatusText(_T("配对情况未知"),0);
                }
            }
            {
                auto is_connected=perh.is_connected();
                m_button_connect->Enable(false);
                m_button_disconnect->Enable(false);
                if(is_connected.has_value())
                {
                    bool val=(*is_connected);
                    if(val)
                    {
                        m_button_disconnect->Enable(true);
                        m_statusBar->PushStatusText(_T("已连接"),1);
                    }
                    else
                    {
                        m_button_connect->Enable(true);
                        m_statusBar->PushStatusText(_T("未连接"),1);
                    }
                }
                else
                {

                    m_statusBar->PushStatusText(_T("连接情况未知"),1);
                }

                if(perh.is_connectable().has_value() && !(*perh.is_connectable()))
                {
                    m_button_connect->Enable(false);
                }
            }
            {
                if(m_treeCtrl->GetCount()!=0)
                    m_treeCtrl->DeleteAllItems();
                wxTreeItemId root=m_treeCtrl->AddRoot(wxString(Perh.identifier()) + " [" <<  Perh.address() + "]",-1,-1,new wxTreeCtrlPerhItemData(Perh));

                auto services = perh.services();
                if(services.has_value())
                {
                    auto ToDesc=[](std::string uuid)->std::string
                    {
                        if(IsBLEShortUUID(uuid))
                        {
                            std::string shortuuid=uuid.substr(4,4);
                            std::string desc=GetBLEUuidDescByShortUuid(std::stoll(shortuuid,NULL,16));
                            return shortuuid+(desc.empty()?"":(std::string(" [")+desc+"]"));
                        }
                        else
                        {
                            return uuid;
                        }
                    };
                    for (auto service : *services)
                    {
                        wxTreeItemId serviceid=m_treeCtrl->AppendItem(root,wxString(_T("服务: "))+ToDesc(service.uuid()),-1,-1,new wxTreeCtrlServiceItemData(Perh,service.uuid()));
                        for (auto characteristic : service.characteristics())
                        {
                            wxTreeItemId charid=m_treeCtrl->AppendItem(serviceid,wxString(_T("特征: "))+ToDesc(characteristic.uuid()),-1,-1,new wxTreeCtrlServiceCharItemData(Perh,service.uuid(),characteristic.uuid()));
                            for (auto& descriptor : characteristic.descriptors())
                            {
                                wxTreeItemId descid=m_treeCtrl->AppendItem(charid,wxString(_T("描述符: "))+ToDesc(descriptor.uuid()),-1,-1,new wxTreeCtrlServiceCharDescItemData(Perh,service.uuid(),characteristic.uuid(),descriptor.uuid()));
                            }
                        }
                    }
                    m_treeCtrl->ExpandAll();
                }
            }
        });
    }
}

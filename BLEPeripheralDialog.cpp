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
        wxLogMessage(_T("?????????????????????????????????"));
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
        wxLogMessage(wxString(_T("?????????????????? "))+Perh.address());
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
            wxLogMessage(wxString(_T("???????????? "))+addr);
            if(!is_connected)
            {
                wxMessageBox(_T("????????????"),_T("??????"));
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
            wxLogMessage(wxString(_T("?????????????????? "))+Perh.address());
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
        {
            auto menufunc=[&]( wxCommandEvent& event_menu )
            {
                if (wxTheClipboard->Open())
                {
                    wxTheClipboard->SetData( new wxTextDataObject(m_treeCtrl->GetItemText(event.GetItem())));
                    wxTheClipboard->Close();
                }
            };
            wxMenuItem *item=menu.Append(1000,_T("??????????????????"));
            menu.Bind(wxEVT_COMMAND_MENU_SELECTED,menufunc,item->GetId(),item->GetId());
        }

        menu.AppendSeparator();

        {
            wxTreeCtrlPerhItemData *_Data=dynamic_cast<wxTreeCtrlPerhItemData *>(data);
            if(_Data!=NULL)
            {
                //??????
            }
        }

        {
            wxTreeCtrlServiceItemData *_Data=dynamic_cast<wxTreeCtrlServiceItemData *>(data);
            if(_Data!=NULL)
            {
                //??????
            }
        }

        {
            wxTreeCtrlServiceCharItemData *_Data=dynamic_cast<wxTreeCtrlServiceCharItemData *>(data);
            if(_Data!=NULL)
            {
                //??????
                {
                    auto menufunc=[=]( wxCommandEvent& event_menu )
                    {
                        SimpleBLE::Safe::Peripheral perh(_Data->perh);
                        std::optional<SimpleBLE::ByteArray> read_data;
                        try
                        {
                            read_data=perh.read(_Data->ServiceUUID,_Data->CharUUID);
                        }
                        catch(...)
                        {
                            wxMessageBox(_T("????????????!"),_T("??????"));
                        }
                        if(read_data.has_value() && !read_data.value_or("").empty())
                        {
                            std::string str=read_data.value_or("");
                            std::string hexstr;
                            {
                                for(size_t i=0; i<str.length(); i++)
                                {
                                    char buff[10]= {0};
                                    snprintf(buff,sizeof(buff)-1,"%02X ",(uint8_t)(str.c_str()[i]));
                                    hexstr+=buff;
                                }
                            }
                            wxLogMessage(wxString(_T("???????????????????????????\r\n\t??????:%s\r\n\t??????:%s\r\n\t??????:%s\r\n\t??????:%s\r\n\t??????(HEX):%s")),wxString(_Data->perh.address()),_Data->ServiceUUID,_Data->CharUUID,wxString::FromUTF8(str.c_str(),str.length()),hexstr);
                            wxMessageBox(_T("????????????,?????????????????????????????????????????????!"),_T("??????"));
                        }
                        else
                        {
                            wxMessageBox(_T("????????????????????????????????????!"),_T("??????"));
                        }
                    };
                    wxMenuItem *item=menu.Append(1301,_T("??????"));
                    menu.Bind(wxEVT_COMMAND_MENU_SELECTED,menufunc,item->GetId(),item->GetId());
                }

                {
                    auto menufunc=[=]( wxCommandEvent& event_menu )
                    {
                        SimpleBLE::Safe::Peripheral perh(_Data->perh);
                        InputDialog dlg(this);
                        if(wxID_OK==dlg.ShowModal())
                        {
                            std::string str=dlg.GetData().ToStdString();
                            std::string hexstr;
                            {
                                for(size_t i=0; i<str.length(); i++)
                                {
                                    char buff[10]= {0};
                                    snprintf(buff,sizeof(buff)-1,"%02X ",(uint8_t)(str.c_str()[i]));
                                    hexstr+=buff;
                                }
                            }
                            wxLogMessage(wxString(_T("???????????????????????????\r\n\t??????:%s\r\n\t??????:%s\r\n\t??????:%s\r\n\t??????:%s\r\n\t??????(HEX):%s")),wxString(_Data->perh.address()),_Data->ServiceUUID,_Data->CharUUID,wxString::FromUTF8(str.c_str(),str.length()),hexstr);
                            if(perh.write_request(_Data->ServiceUUID,_Data->CharUUID,str))
                            {
                                wxLogMessage(_T("%s ??????????????????!"),perh.address().value_or(""));
                                wxMessageBox(_T("????????????!"),_T("??????"));
                            }
                            else
                            {
                                wxLogMessage(_T("%s ??????????????????!"),perh.address().value_or(""));
                                wxMessageBox(_T("????????????!"),_T("??????"));
                            }

                        }
                        else
                        {
                            wxLogMessage(_T("%s ??????????????????!!"),perh.address().value_or(""));
                        }
                    };
                    wxMenuItem *item=menu.Append(1302,_T("????????????"));
                    menu.Bind(wxEVT_COMMAND_MENU_SELECTED,menufunc,item->GetId(),item->GetId());
                }

                {
                    auto menufunc=[=]( wxCommandEvent& event_menu )
                    {
                        SimpleBLE::Safe::Peripheral perh(_Data->perh);
                        InputDialog dlg(this);
                        if(wxID_OK==dlg.ShowModal())
                        {
                            std::string str=dlg.GetData().ToStdString();
                            std::string hexstr;
                            {
                                for(size_t i=0; i<str.length(); i++)
                                {
                                    char buff[10]= {0};
                                    snprintf(buff,sizeof(buff)-1,"%02X ",(uint8_t)(str.c_str()[i]));
                                    hexstr+=buff;
                                }
                            }
                            wxLogMessage(wxString(_T("???????????????????????????\r\n\t??????:%s\r\n\t??????:%s\r\n\t??????:%s\r\n\t??????:%s\r\n\t??????(HEX):%s")),wxString(_Data->perh.address()),_Data->ServiceUUID,_Data->CharUUID,wxString::FromUTF8(str.c_str(),str.length()),hexstr);
                            if(perh.write_command(_Data->ServiceUUID,_Data->CharUUID,str))
                            {
                                wxLogMessage(_T("%s ??????????????????!"),perh.address().value_or(""));
                                wxMessageBox(_T("????????????!"),_T("??????"));
                            }
                            else
                            {
                                wxLogMessage(_T("%s ??????????????????!"),perh.address().value_or(""));
                                wxMessageBox(_T("????????????!"),_T("??????"));
                            }

                        }
                        else
                        {
                            wxLogMessage(_T("%s ??????????????????!!"),perh.address().value_or(""));
                        }
                    };
                    wxMenuItem *item=menu.Append(1303,_T("????????????"));
                    menu.Bind(wxEVT_COMMAND_MENU_SELECTED,menufunc,item->GetId(),item->GetId());
                }

                {
                    auto menufunc=[=]( wxCommandEvent& event_menu )
                    {
                        SimpleBLE::Safe::Peripheral perh(_Data->perh);
                        auto cb=[=](SimpleBLE::ByteArray payload)
                        {
                            std::string str=payload;
                            std::string hexstr;
                            {
                                for(size_t i=0; i<str.length(); i++)
                                {
                                    char buff[10]= {0};
                                    snprintf(buff,sizeof(buff)-1,"%02X ",(uint8_t)(str.c_str()[i]));
                                    hexstr+=buff;
                                }
                            }
                            wxLogMessage(wxString(_T("?????????????????????\r\n\t??????:%s\r\n\t??????:%s\r\n\t??????:%s\r\n\t??????:%s\r\n\t??????(HEX):%s")),wxString(_Data->perh.address()),_Data->ServiceUUID,_Data->CharUUID,wxString::FromUTF8(str.c_str(),str.length()),hexstr);

                        };
                        if(perh.notify(_Data->ServiceUUID,_Data->CharUUID,cb))
                        {
                            wxMessageBox(_T("????????????????????????!"),_T("??????"));
                        }
                        else
                        {
                            wxMessageBox(_T("????????????????????????!"),_T("??????"));
                        }
                    };
                    wxMenuItem *item=menu.Append(1304,_T("??????????????????"));
                    menu.Bind(wxEVT_COMMAND_MENU_SELECTED,menufunc,item->GetId(),item->GetId());
                }

                {
                    auto menufunc=[=]( wxCommandEvent& event_menu )
                    {
                        SimpleBLE::Safe::Peripheral perh(_Data->perh);
                        auto cb=[=](SimpleBLE::ByteArray payload)
                        {
                            std::string str=payload;
                            std::string hexstr;
                            {
                                for(size_t i=0; i<str.length(); i++)
                                {
                                    char buff[10]= {0};
                                    snprintf(buff,sizeof(buff)-1,"%02X ",(uint8_t)(str.c_str()[i]));
                                    hexstr+=buff;
                                }
                            }
                            wxLogMessage(wxString(_T("?????????????????????\r\n\t??????:%s\r\n\t??????:%s\r\n\t??????:%s\r\n\t??????:%s\r\n\t??????(HEX):%s")),wxString(_Data->perh.address()),_Data->ServiceUUID,_Data->CharUUID,wxString::FromUTF8(str.c_str(),str.length()),hexstr);

                        };
                        if(perh.notify(_Data->ServiceUUID,_Data->CharUUID,cb))
                        {
                            wxMessageBox(_T("????????????????????????!"),_T("??????"));
                        }
                        else
                        {
                            wxMessageBox(_T("????????????????????????!"),_T("??????"));
                        }
                    };
                    wxMenuItem *item=menu.Append(1305,_T("??????????????????"));
                    menu.Bind(wxEVT_COMMAND_MENU_SELECTED,menufunc,item->GetId(),item->GetId());
                }

                {
                    auto menufunc=[=]( wxCommandEvent& event_menu )
                    {
                        SimpleBLE::Safe::Peripheral perh(_Data->perh);
                        if(perh.unsubscribe(_Data->ServiceUUID,_Data->CharUUID))
                        {
                            wxMessageBox(_T("????????????????????????!"),_T("??????"));
                        }
                        else
                        {
                            wxMessageBox(_T("????????????????????????!"),_T("??????"));
                        }
                    };
                    wxMenuItem *item=menu.Append(1306,_T("??????????????????"));
                    menu.Bind(wxEVT_COMMAND_MENU_SELECTED,menufunc,item->GetId(),item->GetId());
                }
            }
        }

        {
            wxTreeCtrlServiceCharDescItemData *_Data=dynamic_cast<wxTreeCtrlServiceCharDescItemData *>(data);
            if(_Data!=NULL)
            {
                //?????????

                {
                    auto menufunc=[=]( wxCommandEvent& event_menu )
                    {
                        SimpleBLE::Safe::Peripheral perh(_Data->perh);
                        std::optional<SimpleBLE::ByteArray> read_data;
                        try
                        {
                            read_data=perh.read(_Data->ServiceUUID,_Data->CharUUID,_Data->DescUUID);
                        }
                        catch(...)
                        {
                            wxMessageBox(_T("????????????!"),_T("??????"));
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
                                    snprintf(buff,sizeof(buff)-1,"%02X ",(uint8_t)(str.c_str()[i]));
                                    hexstr+=buff;
                                }
                            }
                            wxLogMessage(wxString(_T("???????????????????????????\r\n\t??????:%s\r\n\t??????:%s\r\n\t??????:%s\r\n\t?????????:%s\r\n\t??????:%s\r\n\t??????(HEX):%s")),wxString(_Data->perh.address()),_Data->ServiceUUID,_Data->CharUUID,_Data->DescUUID,wxString::FromUTF8(str.c_str(),str.length()),hexstr);
                            wxMessageBox(_T("????????????,?????????????????????????????????????????????!"),_T("??????"));
                        }
                        else
                        {
                            wxMessageBox(_T("????????????????????????????????????!"),_T("??????"));
                        }
                    };
                    wxMenuItem *item=menu.Append(1401,_T("??????"));
                    menu.Bind(wxEVT_COMMAND_MENU_SELECTED,menufunc,item->GetId(),item->GetId());
                }

                {
                    auto menufunc=[=]( wxCommandEvent& event_menu )
                    {
                        SimpleBLE::Safe::Peripheral perh(_Data->perh);
                        InputDialog dlg(this);
                        if(wxID_OK==dlg.ShowModal())
                        {
                            std::string str=dlg.GetData().ToStdString();
                            std::string hexstr;
                            {
                                for(size_t i=0; i<str.length(); i++)
                                {
                                    char buff[10]= {0};
                                    snprintf(buff,sizeof(buff)-1,"%02X ",(uint8_t)(str.c_str()[i]));
                                    hexstr+=buff;
                                }
                            }
                            wxLogMessage(wxString(_T("???????????????????????????\r\n\t??????:%s\r\n\t??????:%s\r\n\t??????:%s\r\n\t?????????:%s\r\n\t??????:%s\r\n\t??????(HEX):%s")),wxString(_Data->perh.address()),_Data->ServiceUUID,_Data->CharUUID,_Data->DescUUID,wxString::FromUTF8(str.c_str(),str.length()),hexstr);
                            if(perh.write(_Data->ServiceUUID,_Data->CharUUID,_Data->DescUUID,str))
                            {
                                wxLogMessage(_T("%s ??????????????????!"),perh.address().value_or(""));
                                wxMessageBox(_T("????????????!"),_T("??????"));
                            }
                            else
                            {
                                wxLogMessage(_T("%s ??????????????????!"),perh.address().value_or(""));
                                wxMessageBox(_T("????????????!"),_T("??????"));
                            }

                        }
                        else
                        {
                            wxLogMessage(_T("%s ??????????????????!!"),perh.address().value_or(""));
                        }
                    };
                    wxMenuItem *item=menu.Append(1402,_T("??????"));
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
                        m_statusBar->PushStatusText(_T("?????????"),0);
                    }
                    else
                    {
                        m_statusBar->PushStatusText(_T("?????????"),0);
                    }
                }
                else
                {

                    m_statusBar->PushStatusText(_T("??????????????????"),0);
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
                        m_statusBar->PushStatusText(_T("?????????"),1);
                    }
                    else
                    {
                        m_button_connect->Enable(true);
                        m_statusBar->PushStatusText(_T("?????????"),1);
                    }
                }
                else
                {

                    m_statusBar->PushStatusText(_T("??????????????????"),1);
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
                        wxTreeItemId serviceid=m_treeCtrl->AppendItem(root,wxString(_T("??????: "))+ToDesc(service.uuid()),-1,-1,new wxTreeCtrlServiceItemData(Perh,service.uuid()));
                        for (auto characteristic : service.characteristics())
                        {
                            wxTreeItemId charid=m_treeCtrl->AppendItem(serviceid,wxString(_T("??????: "))+ToDesc(characteristic.uuid()),-1,-1,new wxTreeCtrlServiceCharItemData(Perh,service.uuid(),characteristic.uuid()));
                            for (auto& descriptor : characteristic.descriptors())
                            {
                                wxTreeItemId descid=m_treeCtrl->AppendItem(charid,wxString(_T("?????????: "))+ToDesc(descriptor.uuid()),-1,-1,new wxTreeCtrlServiceCharDescItemData(Perh,service.uuid(),characteristic.uuid(),descriptor.uuid()));
                            }
                        }
                    }
                    m_treeCtrl->ExpandAll();
                }
            }
        });
    }
}

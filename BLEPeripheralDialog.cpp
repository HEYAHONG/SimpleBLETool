#include "BLEPeripheralDialog.h"
#include "wx/msgdlg.h"
#include "misc.h"
#include <thread>
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
                wxTreeItemId root=m_treeCtrl->AddRoot(wxString(Perh.identifier()) + " [" <<  Perh.address() + "]");

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
                        wxTreeItemId serviceid=m_treeCtrl->AppendItem(root,wxString(_T("服务: "))+ToDesc(service.uuid()));
                        for (auto characteristic : service.characteristics())
                        {
                            wxTreeItemId charid=m_treeCtrl->AppendItem(serviceid,wxString(_T("特征: "))+ToDesc(characteristic.uuid()));
                            for (auto& descriptor : characteristic.descriptors())
                            {
                                wxTreeItemId descid=m_treeCtrl->AppendItem(charid,wxString(_T("描述符: "))+ToDesc(descriptor.uuid()));
                            }
                        }
                    }
                    m_treeCtrl->ExpandAll();
                }
            }
        });
    }
}

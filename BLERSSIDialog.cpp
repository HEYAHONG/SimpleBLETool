#include "BLERSSIDialog.h"
#include <chrono>
#include <iomanip>
#include <ctime>
#include <sstream>
#include "time.h"


BLERSSIDialog::BLERSSIDialog( wxWindow* parent):GUIBLERSSIDialog(parent)
{
    //ctor
    mainwindow=dynamic_cast<SimpleBLEToolFrame *>(parent);
    if(mainwindow==NULL)
    {
        wxLogMessage(_T("此窗口必须由主窗口调用"));
        Close();
        return;
    }

    auto cb=[&](SimpleBLE::Peripheral perh)
    {
        if(!Perh.initialized())
        {
            return;
        }
        if(Perh.address()==perh.address())
        {
            int rssi=perh.rssi();
            auto uicb=[=]()
            {
                wxDataViewListStore *store=m_dataViewListCtrl->GetStore();
                wxVector< wxVariant > data;
                data.push_back(wxString(std::to_string(rssi)));
                wxString time_stamp;
                {
                    std::stringstream out;
                    using namespace std::chrono;
                    std::chrono::system_clock::time_point t = std::chrono::system_clock::now();
                    time_t c = std::chrono::system_clock::to_time_t(t);
                    struct tm m_tm;
#ifdef WIN32
                    localtime_s(&m_tm,&c);
#else
                    localtime_r(&c,&m_tm);
#endif // WIN32

                    out<<std::put_time(&m_tm, "%F %T ") <<std::setfill('0')<<std::setw(3)<<(std::chrono::duration_cast<std::chrono::milliseconds>(t.time_since_epoch()) % 1000).count();
                    time_stamp=out.str();
                }
                data.push_back(time_stamp);
                store->InsertItem(0,data);
            };
            mainwindow->AddUpdateUIFuncitonByOther(uicb);
        }
    };
    mainwindow->RegisterScanUpdateCallback(this,cb);
}

BLERSSIDialog::~BLERSSIDialog()
{
    //dtor
    mainwindow->UnRegistterScanUpdateCallback(this);
    if(OnCloseCb!=NULL)
    {
        OnCloseCb();
    }
}

void BLERSSIDialog::SetBLEPerh(SimpleBLE::Peripheral _Perh)
{
    SetTitle(wxString(_Perh.identifier()) + " [" <<  _Perh.address() + "] ");
    Perh=_Perh;
}

void  BLERSSIDialog::SetOnClose(std::function<void(void)> OnClose)
{
    OnCloseCb=OnClose;
}

void BLERSSIDialog::OnClose( wxCloseEvent& event )
{
    Destroy();
}

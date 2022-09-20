#ifndef BLEPERIPHERALDIALOG_H
#define BLEPERIPHERALDIALOG_H

#include "SimpleBLEToolMain.h"
#include "wx/log.h"

class BLEPeripheralDialog:public GUIPeripheral
{
public:
    BLEPeripheralDialog( wxWindow* parent);
    virtual ~BLEPeripheralDialog();

    void SetBLEPerh(SimpleBLE::Peripheral _Perh);
    void SetOnClose(std::function<void(void)> OnClose);

protected:
    virtual void OnClose( wxCloseEvent& event );
    virtual void OnUnpair( wxCommandEvent& event );
    virtual void OnConnect( wxCommandEvent& event );
    virtual void OnDisConnect( wxCommandEvent& event );
    virtual void OnTreeItemRightClick( wxTreeEvent& event );

private:

    SimpleBLEToolFrame *mainwindow;
    SimpleBLE::Peripheral Perh;
    std::function<void(void)> OnCloseCb;

    void UpdateStatus();
};

#endif // BLEPERIPHERALDIALOG_H

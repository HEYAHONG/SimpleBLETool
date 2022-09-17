#ifndef BLERSSIDIALOG_H
#define BLERSSIDIALOG_H

#include "SimpleBLEToolMain.h"
#include "wx/log.h"

class BLERSSIDialog:public GUIBLERSSIDialog
{

public:
    BLERSSIDialog( wxWindow* parent);
    virtual ~BLERSSIDialog();

    void  SetBLEPerh(SimpleBLE::Peripheral _Perh);

    void SetOnClose(std::function<void(void)> OnClose);

protected:
    virtual void OnClose( wxCloseEvent& event );

private:
    SimpleBLEToolFrame *mainwindow;
    SimpleBLE::Peripheral Perh;

    std::function<void(void)> OnCloseCb;
};

#endif // BLERSSIDIALOG_H

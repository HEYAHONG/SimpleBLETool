#ifndef INPUTDIALOG_H
#define INPUTDIALOG_H

#include "GUIFrame.h"

class InputDialog:public GUIInputDialog
{
    public:
        InputDialog(wxWindow* parent);
        virtual ~InputDialog();


        wxString GetData();

    protected:
        virtual void OnOk( wxCommandEvent& event );

    private:

        wxString data;
};

#endif // INPUTDIALOG_H

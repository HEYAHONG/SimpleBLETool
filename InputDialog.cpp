#include "InputDialog.h"
#include "wx/msgdlg.h"

InputDialog::InputDialog(wxWindow* parent):GUIInputDialog(parent)
{
    //ctor
}

InputDialog::~InputDialog()
{
    //dtor
}

wxString InputDialog::GetData()
{
    return data;
}

void InputDialog::OnOk( wxCommandEvent& event )
{
    data=m_textCtrl->GetValue();

    if(data.length()==0)
    {
        wxMessageBox(_T("输入不能为空!直接退出请点关闭!"),_T("提示"));
        return;
    }

    if(m_checkBox_Hex->IsChecked())
    {
        wxString raw_str=data;
        raw_str.Replace(" ","");
        raw_str.Replace("\r","");
        raw_str.Replace("\n","");
        if((raw_str.length()%2)!=0)
        {
            raw_str+=_T("0");
        }

        {
            data=_T("");
            for(size_t i=0;i<raw_str.length();i+=2)
            {
                char buff[2]={0};
                std::string tempstr=raw_str.substr(i,2).ToStdString();
                try
                {
                    buff[0]=std::stoi(tempstr,NULL,16);
                }
                catch(...)
                {
                     wxMessageBox(_T("输入的不是Hex字符串!"),_T("错误"));
                    return;
                }

                data+=std::string(buff,1);
            }
        }

    }

    EndModal(wxID_OK);
}

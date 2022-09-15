/***************************************************************
 * Name:      SimpleBLEToolApp.cpp
 * Purpose:   Code for Application Class
 * Author:    HYH (2229388563@qq.com)
 * Created:   2022-09-13
 * Copyright: HYH (hyhsystem.cn)
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "SimpleBLEToolApp.h"
#include "SimpleBLEToolMain.h"

IMPLEMENT_APP(SimpleBLEToolApp);

extern const char * bluetooth_ico_xpm[];

bool SimpleBLEToolApp::OnInit()
{
    SimpleBLEToolFrame* frame = new SimpleBLEToolFrame(0L);
    frame->SetIcon(bluetooth_ico_xpm); // To Set App Icon
    frame->Show();
    
    return true;
}

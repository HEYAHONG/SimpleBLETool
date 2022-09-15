/***************************************************************
 * Name:      SimpleBLEToolApp.h
 * Purpose:   Defines Application Class
 * Author:    HYH (2229388563@qq.com)
 * Created:   2022-09-13
 * Copyright: HYH (hyhsystem.cn)
 * License:
 **************************************************************/

#ifndef SIMPLEBLETOOLAPP_H
#define SIMPLEBLETOOLAPP_H

#include <wx/app.h>

class SimpleBLEToolApp : public wxApp
{
    public:
        virtual bool OnInit();
        SimpleBLEToolApp()=default;
        virtual ~SimpleBLEToolApp()=default;
};

#endif // SIMPLEBLETOOLAPP_H

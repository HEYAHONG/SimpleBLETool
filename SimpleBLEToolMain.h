/***************************************************************
 * Name:      SimpleBLEToolMain.h
 * Purpose:   Defines Application Frame
 * Author:    HYH (2229388563@qq.com)
 * Created:   2022-09-13
 * Copyright: HYH (hyhsystem.cn)
 * License:
 **************************************************************/

#ifndef SIMPLEBLETOOLMAIN_H
#define SIMPLEBLETOOLMAIN_H



#include "SimpleBLEToolApp.h"


#include "GUIFrame.h"
#include "mutex"
#include "queue"
#include "functional"
#include "map"
#include "wx/treectrl.h"

class SimpleBLEToolFrame: public GUIFrame
{
public:
    SimpleBLEToolFrame(wxFrame *frame);
    ~SimpleBLEToolFrame();

    /*
    外设列表(wxTreeCtrl)
    */
    typedef struct
    {
        wxTreeItemId adapter;
        wxTreeItemId perh;
    } wxTreeCtrlAdapterPerhID;
    std::map<wxString,std::map<wxString,wxTreeCtrlAdapterPerhID>> PerhList;
    std::mutex PerhList_Lock;

private:
    virtual void OnClose(wxCloseEvent& event);
    virtual void OnQuit(wxCommandEvent& event);
    virtual void OnAbout(wxCommandEvent& event);

    virtual void OnMenuClose( wxCommandEvent& event );
    virtual void OnMenuAbout( wxCommandEvent& event );
    virtual void OnMenuReFreshAdapterList( wxCommandEvent& event );
    virtual void OnTreeAdapterRightClick( wxTreeEvent& event );

    virtual void OnUpdateTimer( wxTimerEvent& event );

    /*
        许多更新UI的操作最好在定时器/主线程内调用,故需要更新UI的队列
    */
    struct
    {
        std::mutex lock;
        std::queue<std::function<void(void)>> Queue;
    } UpdateUI;

    /*
        向更新UI队列中添加带有UI操作的函数
    */
    void AddUpdateUIFunciton(std::function<void(void)> func)
    {
        std::lock_guard<std::mutex> lock(UpdateUI.lock);
        UpdateUI.Queue.push(func);
    };
    /*
        处理更新UI队列中的函数
    */
    void ProcessUpdateUIFunction()
    {
        std::lock_guard<std::mutex> lock(UpdateUI.lock);
        while(UpdateUI.Queue.size()>0)
        {
            std::function<void(void)> cb=UpdateUI.Queue.front();
            if(cb!=NULL)
            {
                cb();
            }
            UpdateUI.Queue.pop();
        };
    }

    void UpdateBLEAdapterList();


};

#endif // SIMPLEBLETOOLMAIN_H

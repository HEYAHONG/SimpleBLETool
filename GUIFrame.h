///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/cshelp.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/statusbr.h>
#include <wx/timer.h>
#include <wx/textctrl.h>
#include <wx/treectrl.h>
#include <wx/frame.h>
#include <wx/aui/aui.h>
#include <wx/stattext.h>
#include <wx/sizer.h>
#include <wx/hyperlink.h>
#include <wx/dialog.h>
#include <wx/dataview.h>

///////////////////////////////////////////////////////////////////////////

#define ID_MenuFileQuit 1000
#define ID_MenuReFreshAdapterList 1001
#define ID_MenuHelpAbout 1002
#define wxID_Updatetimer 1003
#define wxID_UpdateTimer 1004

///////////////////////////////////////////////////////////////////////////////
/// Class GUIFrame
///////////////////////////////////////////////////////////////////////////////
class GUIFrame : public wxFrame
{
	private:

	protected:
		wxMenuBar* m_menubar;
		wxMenu* MenuFile;
		wxMenu* MenuOperate;
		wxMenu* MenuHelp;
		wxStatusBar* m_statusBar;
		wxTimer m_Updatetimer;
		wxTextCtrl* m_textCtrlLog;
		wxTreeCtrl* m_treeCtrl_adapter;
		wxTimer m_UpdateTimer;

		// Virtual event handlers, override them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnMenuClose( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMenuReFreshAdapterList( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMenuAbout( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnUpdateTimer( wxTimerEvent& event ) { event.Skip(); }
		virtual void OnTreeAdapterRightClick( wxTreeEvent& event ) { event.Skip(); }


	public:

		GUIFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("SimpleBLETool"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		wxAuiManager m_mgr;

		~GUIFrame();

};

///////////////////////////////////////////////////////////////////////////////
/// Class GUIAboutDialog
///////////////////////////////////////////////////////////////////////////////
class GUIAboutDialog : public wxDialog
{
	private:

	protected:
		wxStaticText* m_staticText1;
		wxStaticText* m_staticText2;
		wxHyperlinkCtrl* m_hyperlink1;
		wxHyperlinkCtrl* m_hyperlink2;

	public:

		GUIAboutDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("关于"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE );

		~GUIAboutDialog();

};

///////////////////////////////////////////////////////////////////////////////
/// Class GUIBLERSSIDialog
///////////////////////////////////////////////////////////////////////////////
class GUIBLERSSIDialog : public wxDialog
{
	private:

	protected:
		wxDataViewListCtrl* m_dataViewListCtrl;
		wxDataViewColumn* m_dataViewListColumn_RSSI;
		wxDataViewColumn* m_dataViewListColumn_Time;

		// Virtual event handlers, override them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }


	public:

		GUIBLERSSIDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 400,600 ), long style = wxDEFAULT_DIALOG_STYLE );

		~GUIBLERSSIDialog();

};


///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif //WX_PRECOMP

#include "GUIFrame.h"

// Using the construction of a static object to ensure that the help provider is set
// wx Manages the most recent HelpProvider passed to ::Set, but not the previous ones
// If ::Set gets called more than once, the previous one is returned and should be deleted
class wxFBContextSensitiveHelpSetter
{
public:
wxFBContextSensitiveHelpSetter()
{
wxSimpleHelpProvider* help = new wxSimpleHelpProvider();
wxHelpProvider* old = wxHelpProvider::Set( help );
if (old != 0){
delete old;
}
}
};

static wxFBContextSensitiveHelpSetter s_wxFBSetTheHelpProvider;
///////////////////////////////////////////////////////////////////////////

GUIFrame::GUIFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 800,600 ), wxDefaultSize );
	m_mgr.SetManagedWindow(this);
	m_mgr.SetFlags(wxAUI_MGR_DEFAULT);

	m_menubar = new wxMenuBar( 0 );
	MenuFile = new wxMenu();
	wxMenuItem* MenuFileQuit;
	MenuFileQuit = new wxMenuItem( MenuFile, ID_MenuFileQuit, wxString( wxT("退出") ) + wxT('\t') + wxT("Alt-F4"), wxT("退出"), wxITEM_NORMAL );
	MenuFile->Append( MenuFileQuit );

	m_menubar->Append( MenuFile, wxT("文件") );

	MenuOperate = new wxMenu();
	wxMenuItem* MenuReFreshAdapterList;
	MenuReFreshAdapterList = new wxMenuItem( MenuOperate, ID_MenuReFreshAdapterList, wxString( wxT("刷新适配器列表") ) , wxT("刷新适配器列表"), wxITEM_NORMAL );
	MenuOperate->Append( MenuReFreshAdapterList );

	m_menubar->Append( MenuOperate, wxT("操作") );

	MenuHelp = new wxMenu();
	wxMenuItem* MenuHelpAbout;
	MenuHelpAbout = new wxMenuItem( MenuHelp, ID_MenuHelpAbout, wxString( wxT("关于") ) + wxT('\t') + wxT("F1"), wxT("关于"), wxITEM_NORMAL );
	MenuHelp->Append( MenuHelpAbout );

	m_menubar->Append( MenuHelp, wxT("帮助") );

	this->SetMenuBar( m_menubar );

	m_statusBar = this->CreateStatusBar( 2, wxSTB_DEFAULT_STYLE, wxID_ANY );
	m_Updatetimer.SetOwner( this, wxID_Updatetimer );
	m_textCtrlLog = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY );
	m_mgr.AddPane( m_textCtrlLog, wxAuiPaneInfo() .Center() .CaptionVisible( false ).CloseButton( false ).PinButton( true ).Dock().Resizable().FloatingSize( wxDefaultSize ).DockFixed( true ).BottomDockable( false ).TopDockable( false ).LeftDockable( false ).RightDockable( false ).Floatable( false ).CentrePane() );

	m_treeCtrl_adapter = new wxTreeCtrl( this, wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), wxTR_DEFAULT_STYLE|wxTR_HIDE_ROOT|wxTR_SINGLE );
	m_mgr.AddPane( m_treeCtrl_adapter, wxAuiPaneInfo() .Left() .Caption( wxT("适配器") ).CloseButton( false ).PinButton( true ).Dock().Resizable().FloatingSize( wxDefaultSize ).BottomDockable( false ).TopDockable( false ).MinSize( wxSize( 300,600 ) ) );

	m_UpdateTimer.SetOwner( this, wxID_UpdateTimer );
	m_UpdateTimer.Start( 5 );


	m_mgr.Update();

	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIFrame::OnClose ) );
	MenuFile->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnMenuClose ), this, MenuFileQuit->GetId());
	MenuOperate->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnMenuReFreshAdapterList ), this, MenuReFreshAdapterList->GetId());
	MenuHelp->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnMenuAbout ), this, MenuHelpAbout->GetId());
	this->Connect( wxID_Updatetimer, wxEVT_TIMER, wxTimerEventHandler( GUIFrame::OnUpdateTimer ) );
	m_treeCtrl_adapter->Connect( wxEVT_COMMAND_TREE_ITEM_RIGHT_CLICK, wxTreeEventHandler( GUIFrame::OnTreeAdapterRightClick ), NULL, this );
	this->Connect( wxID_UpdateTimer, wxEVT_TIMER, wxTimerEventHandler( GUIFrame::OnUpdateTimer ) );
}

GUIFrame::~GUIFrame()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIFrame::OnClose ) );
	this->Disconnect( wxID_Updatetimer, wxEVT_TIMER, wxTimerEventHandler( GUIFrame::OnUpdateTimer ) );
	m_treeCtrl_adapter->Disconnect( wxEVT_COMMAND_TREE_ITEM_RIGHT_CLICK, wxTreeEventHandler( GUIFrame::OnTreeAdapterRightClick ), NULL, this );
	this->Disconnect( wxID_UpdateTimer, wxEVT_TIMER, wxTimerEventHandler( GUIFrame::OnUpdateTimer ) );

	m_mgr.UnInit();

}

GUIAboutDialog::GUIAboutDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxHORIZONTAL );


	bSizer1->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );


	bSizer4->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText1 = new wxStaticText( this, wxID_ANY, wxT("SimpleBLETool BY 何亚红"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL );
	m_staticText1->Wrap( -1 );
	bSizer2->Add( m_staticText1, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );


	bSizer4->Add( bSizer2, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText2 = new wxStaticText( this, wxID_ANY, wxT("依赖库："), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	bSizer3->Add( m_staticText2, 0, wxALL, 5 );


	bSizer4->Add( bSizer3, 1, wxEXPAND, 5 );

	m_hyperlink1 = new wxHyperlinkCtrl( this, wxID_ANY, wxT("wxWidgets"), wxT("https://www.wxwidgets.org/"), wxDefaultPosition, wxDefaultSize, wxHL_DEFAULT_STYLE );
	bSizer4->Add( m_hyperlink1, 0, wxALL, 5 );

	m_hyperlink2 = new wxHyperlinkCtrl( this, wxID_ANY, wxT("SimpleBLE"), wxT("https://github.com/OpenBluetoothToolbox/SimpleBLE.git"), wxDefaultPosition, wxDefaultSize, wxHL_DEFAULT_STYLE );
	bSizer4->Add( m_hyperlink2, 0, wxALL, 5 );


	bSizer4->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer1->Add( bSizer4, 1, wxEXPAND, 5 );


	bSizer1->Add( 0, 0, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer1 );
	this->Layout();
	bSizer1->Fit( this );

	this->Centre( wxBOTH );
}

GUIAboutDialog::~GUIAboutDialog()
{
}

GUIBLERSSIDialog::GUIBLERSSIDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( -1,-1 ), wxDefaultSize );

	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );

	m_dataViewListCtrl = new wxDataViewListCtrl( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_dataViewListColumn_RSSI = m_dataViewListCtrl->AppendTextColumn( wxT("RSSI(dbm)"), wxDATAVIEW_CELL_INERT, -1, static_cast<wxAlignment>(wxALIGN_CENTER|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL), wxDATAVIEW_COL_RESIZABLE );
	m_dataViewListColumn_Time = m_dataViewListCtrl->AppendTextColumn( wxT("时间"), wxDATAVIEW_CELL_INERT, -1, static_cast<wxAlignment>(wxALIGN_CENTER|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL), wxDATAVIEW_COL_RESIZABLE );
	bSizer5->Add( m_dataViewListCtrl, 1, wxALL|wxEXPAND, 5 );


	this->SetSizer( bSizer5 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIBLERSSIDialog::OnClose ) );
}

GUIBLERSSIDialog::~GUIBLERSSIDialog()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIBLERSSIDialog::OnClose ) );

}

GUIPeripheral::GUIPeripheral( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 600,400 ), wxDefaultSize );
	m_mgr.SetManagedWindow(this);
	m_mgr.SetFlags(wxAUI_MGR_DEFAULT);

	m_toolBar = new wxToolBar( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL );
	m_button_unpair = new wxButton( m_toolBar, wxID_ANY, wxT("取消配对"), wxDefaultPosition, wxDefaultSize, 0 );
	m_toolBar->AddControl( m_button_unpair );
	m_button_connect = new wxButton( m_toolBar, wxID_ANY, wxT("连接"), wxDefaultPosition, wxDefaultSize, 0 );
	m_toolBar->AddControl( m_button_connect );
	m_button_disconnect = new wxButton( m_toolBar, wxID_ANY, wxT("断开连接"), wxDefaultPosition, wxDefaultSize, 0 );
	m_toolBar->AddControl( m_button_disconnect );
	m_toolBar->Realize();
	m_mgr.AddPane( m_toolBar, wxAuiPaneInfo() .Top() .CaptionVisible( false ).CloseButton( false ).PinButton( true ).Dock().Resizable().FloatingSize( wxDefaultSize ).LeftDockable( false ).RightDockable( false ).Floatable( false ) );


	m_treeCtrl = new wxTreeCtrl( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTR_DEFAULT_STYLE|wxTR_SINGLE );
	m_mgr.AddPane( m_treeCtrl, wxAuiPaneInfo() .Left() .CaptionVisible( false ).CloseButton( false ).Movable( false ).Dock().Resizable().FloatingSize( wxDefaultSize ).BottomDockable( false ).TopDockable( false ).LeftDockable( false ).RightDockable( false ).Floatable( false ).CentrePane() );

	m_statusBar = this->CreateStatusBar( 2, wxSTB_DEFAULT_STYLE, wxID_ANY );

	m_mgr.Update();
	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIPeripheral::OnClose ) );
	m_button_unpair->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIPeripheral::OnUnpair ), NULL, this );
	m_button_connect->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIPeripheral::OnConnect ), NULL, this );
	m_button_disconnect->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIPeripheral::OnDisConnect ), NULL, this );
	m_treeCtrl->Connect( wxEVT_COMMAND_TREE_ITEM_RIGHT_CLICK, wxTreeEventHandler( GUIPeripheral::OnTreeItemRightClick ), NULL, this );
}

GUIPeripheral::~GUIPeripheral()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIPeripheral::OnClose ) );
	m_button_unpair->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIPeripheral::OnUnpair ), NULL, this );
	m_button_connect->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIPeripheral::OnConnect ), NULL, this );
	m_button_disconnect->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIPeripheral::OnDisConnect ), NULL, this );
	m_treeCtrl->Disconnect( wxEVT_COMMAND_TREE_ITEM_RIGHT_CLICK, wxTreeEventHandler( GUIPeripheral::OnTreeItemRightClick ), NULL, this );

	m_mgr.UnInit();

}

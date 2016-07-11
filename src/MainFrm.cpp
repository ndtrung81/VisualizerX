// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Visualizer_X.h"

#include "MainFrm.h"
#include "Visualizer_XDoc.h"
#include "Visualizer_XView.h"
#include "Splash.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_DROPFILES()
	ON_COMMAND(ID_WINDOW_CLOSEALL, OnWindowCloseall)
	ON_COMMAND(ID_WINDOW_TILEVERTICALLY, OnWindowTilevertically)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_FRAME, OnUpdateFrame)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
	ID_INDICATOR_FRAME
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	DragAcceptFiles();

	// CG: The following line was added by the Splash Screen component.
	CSplashWnd::ShowSplashScreen(this);
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


void CMainFrame::OnDropFiles(HDROP hDropInfo) 
{
	// TODO: Add your message handler code here and/or call default
	char sFileName[512];
	DragQueryFile(hDropInfo, 0, sFileName, 512);	

	CMDIFrameWnd::OnDropFiles(hDropInfo);

	CMDIChildWnd* pChildWnd = (CMDIChildWnd*)GetActiveFrame();
	if (pChildWnd != NULL)
	{
		CVisualizer_XView* pView = (CVisualizer_XView*)pChildWnd->GetActiveView();
		if (pView != NULL)
		{
			pView->ReadXYZFile(sFileName);
			pView->Invalidate();
		}
	}

/*  This code generates a new document and a view attached to it
	CVisualizer_XApp* pApp = (CVisualizer_XApp*)AfxGetApp();
	POSITION pos;
	pos = pApp->GetFirstDocTemplatePosition();
	CDocTemplate* pDocTemplate = pApp->GetNextDocTemplate(pos);
	CVisualizer_XDoc* pDoc = (CVisualizer_XDoc*)pDocTemplate->CreateNewDocument();
	CMDIChildWnd* pChildWnd = (CMDIChildWnd*)pDocTemplate->CreateNewFrame(pDoc, NULL);
	if (pChildWnd != NULL)
	{
		pChildWnd->InitialUpdateFrame(pDoc, TRUE);
		CVisualizer_XView* pView = (CVisualizer_XView*)pChildWnd->GetActiveView();
		if (pView != NULL)
		{
			pView->ReadXYZFile(sFileName);
			pView->Invalidate();
		}
	}
*/
	
}

void CMainFrame::OnWindowCloseall() 
{
	// TODO: Add your command handler code here
	CVisualizer_XApp* pApp = (CVisualizer_XApp*)AfxGetApp();
	CDocTemplate* pDocTemplate;

	POSITION pos;
	pos = pApp->GetFirstDocTemplatePosition();

	while (pos != NULL)
	{
		pDocTemplate = pApp->GetNextDocTemplate(pos);
		pDocTemplate->CloseAllDocuments(FALSE);
	}
}


void CMainFrame::OnWindowTilevertically() 
{
	// TODO: Add your command handler code here
	CVisualizer_XApp* pApp = (CVisualizer_XApp*)AfxGetApp();
	CDocTemplate* pDocTemplate;
	CVisualizer_XDoc* pDoc;

	POSITION template_pos;
	template_pos = pApp->GetFirstDocTemplatePosition();

	while (template_pos != NULL)
	{
		pDocTemplate = pApp->GetNextDocTemplate(template_pos);
		POSITION doc_pos = pDocTemplate->GetFirstDocPosition();
		while (doc_pos != NULL)
		{
			pDoc = (CVisualizer_XDoc*)pDocTemplate->GetNextDoc(doc_pos);
			
		}
	}
}

void CMainFrame::OnUpdateFrame(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(); 

	CMDIChildWnd* pChildWnd = (CMDIChildWnd*)GetActiveFrame();
	if (pChildWnd != NULL)
	{
		CVisualizer_XView* pView = (CVisualizer_XView*)pChildWnd->GetActiveView();
		if (pView != NULL)
		{
			CString strFrame;

			strFrame.Format("Frm: %d", pView->m_frameID); 
			pCmdUI->SetText(strFrame); 
		}
	}
    


    

}
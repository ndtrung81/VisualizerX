// DlgToolBar.cpp: implementation of the CDlgToolBar class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Visualizer_X.h"
#include "DlgToolBar.h"
#include <afxpriv.h>

#include "RDFDialog.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CDlgToolBar, CToolBar)
	//{{AFX_MSG_MAP(CDlgToolBar)
	ON_WM_KEYDOWN()
	ON_MESSAGE(WM_IDLEUPDATECMDUI, OnIdleUpdateCmdUI)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDlgToolBar::CDlgToolBar()
{

}

CDlgToolBar::~CDlgToolBar()
{

}

LRESULT CDlgToolBar::OnIdleUpdateCmdUI(WPARAM wParam, LPARAM)
{
	if (IsWindowVisible())
	{
		CFrameWnd *pParent = (CFrameWnd *)GetParent();
		if (pParent)
			OnUpdateCmdUI(pParent, (BOOL)wParam);
	}

	return 0L;
}

void CDlgToolBar::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CRDFDialog* pParent = (CRDFDialog*)GetParent();
//	pParent->HandleKeyDown(nChar, nRepCnt, nFlags);
}
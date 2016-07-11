// DrawnEdit.cpp : implementation file
//

#include "stdafx.h"
#include "Visualizer_X.h"
#include "DrawnEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDrawnEdit

CDrawnEdit::CDrawnEdit()
{
}

CDrawnEdit::~CDrawnEdit()
{
}


BEGIN_MESSAGE_MAP(CDrawnEdit, CEdit)
	//{{AFX_MSG_MAP(CDrawnEdit)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDrawnEdit message handlers

void CDrawnEdit::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CRect rect;
	GetClientRect(&rect);
	m_graphCtrl.SetBoundRect(rect);
	m_graphCtrl.Draw(&dc);
	
	// Do not call CEdit::OnPaint() for painting messages
}




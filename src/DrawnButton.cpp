// DrawnButton.cpp : implementation file
//

#include "stdafx.h"
#include "Visualizer_X.h"
#include "DrawnButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDrawnButton

CDrawnButton::CDrawnButton()
{
}

CDrawnButton::~CDrawnButton()
{
}


BEGIN_MESSAGE_MAP(CDrawnButton, CButton)
	//{{AFX_MSG_MAP(CDrawnButton)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDrawnButton message handlers

void CDrawnButton::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CBrush brush(m_nColor);
	
	CRect rect;
	GetClientRect(&rect);
	dc.FillRect(&rect, &brush);
	
	brush.DeleteObject();
	// Do not call CButton::OnPaint() for painting messages
}

void CDrawnButton::SetColor(COLORREF nColor)
{
	m_nColor = nColor;
}

// FormatDialog.cpp : implementation file
//

#include "stdafx.h"
#include "visualizer_x.h"
#include "FormatDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFormatDialog dialog


CFormatDialog::CFormatDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CFormatDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFormatDialog)
	m_nLineWidth = 0;
	m_largeTickYInterval = 0.0;
	m_largeTickXInterval = 0.0;
	m_smallTickXInterval = 0.0;
	m_smallTickYInterval = 0.0;
	m_nFontSize = 0;
	m_maxx = 0.0;
	m_maxy = 0.0;
	m_minx = 0.0;
	m_miny = 0.0;
	//}}AFX_DATA_INIT
}


void CFormatDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFormatDialog)
	DDX_Control(pDX, IDC_BUTTON_COLOR, m_drawnButton);
	DDX_Text(pDX, IDC_LINEWIDTH, m_nLineWidth);
	DDX_Text(pDX, IDC_MAJORTICKY, m_largeTickYInterval);
	DDX_Text(pDX, IDC_MAJORTICKX, m_largeTickXInterval);
	DDX_Text(pDX, IDC_MINORTICKX, m_smallTickXInterval);
	DDX_Text(pDX, IDC_MINORTICKY, m_smallTickYInterval);
	DDX_Text(pDX, IDC_FONTSIZE, m_nFontSize);
	DDX_Text(pDX, IDC_MAXX, m_maxx);
	DDX_Text(pDX, IDC_MAXY, m_maxy);
	DDX_Text(pDX, IDC_MINX, m_minx);
	DDX_Text(pDX, IDC_MINY, m_miny);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFormatDialog, CDialog)
	//{{AFX_MSG_MAP(CFormatDialog)
	ON_BN_CLICKED(IDC_BUTTON_COLOR, OnButtonColor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFormatDialog message handlers

void CFormatDialog::OnButtonColor() 
{
	// TODO: Add your control notification handler code here
	CColorDialog dlg;
	if (dlg.DoModal() == IDOK)
	{
		m_drawnButton.m_nColor = dlg.GetColor();
		m_color = dlg.GetColor();
		Invalidate();
	}
}

BOOL CFormatDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_drawnButton.m_nColor = m_color;
	Invalidate();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

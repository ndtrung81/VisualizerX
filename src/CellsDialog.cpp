// CellsDialog.cpp : implementation file
//

#include "stdafx.h"
#include "visualizer_x.h"
#include "CellsDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCellsDialog dialog


CCellsDialog::CCellsDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CCellsDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCellsDialog)
	m_ncellx = 0;
	m_ncelly = 0;
	m_ncellz = 0;
	//}}AFX_DATA_INIT
}


void CCellsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCellsDialog)
	DDX_Text(pDX, IDC_DIV_X, m_ncellx);
	DDX_Text(pDX, IDC_DIV_Y, m_ncelly);
	DDX_Text(pDX, IDC_DIV_Z, m_ncellz);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCellsDialog, CDialog)
	//{{AFX_MSG_MAP(CCellsDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCellsDialog message handlers

// ClusteringDialog.cpp : implementation file
//

#include "stdafx.h"
#include "visualizer_x.h"
#include "ClusteringDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClusteringDialog dialog


CClusteringDialog::CClusteringDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CClusteringDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CClusteringDialog)
	m_periodicWrapped = FALSE;
	m_nType = -1;
	m_cutoff = 0.0;
	//}}AFX_DATA_INIT
}


void CClusteringDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CClusteringDialog)
	DDX_Check(pDX, IDC_CHECK_PBC, m_periodicWrapped);
	DDX_CBIndex(pDX, IDC_COMBO_TYPE, m_nType);
	DDX_Text(pDX, IDC_EDIT_CUTOFF, m_cutoff);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CClusteringDialog, CDialog)
	//{{AFX_MSG_MAP(CClusteringDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClusteringDialog message handlers

// ReplicateDialog.cpp : implementation file
//

#include "stdafx.h"
#include "visualizer_x.h"
#include "ReplicateDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReplicateDialog dialog


CReplicateDialog::CReplicateDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CReplicateDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CReplicateDialog)
	m_numCopies = 1;
	m_shiftx = 0.0;
	m_shifty = 0.0;
	m_shiftz = 0.0;
	m_nRepX = 1;
	m_nRepY = 1;
	m_nRepZ = 1;
	//}}AFX_DATA_INIT
}


void CReplicateDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReplicateDialog)
	DDX_Text(pDX, IDC_NUMCOPIES, m_numCopies);
	DDX_Text(pDX, IDC_SHIFTX, m_shiftx);
	DDX_Text(pDX, IDC_SHIFTY, m_shifty);
	DDX_Text(pDX, IDC_SHIFTZ, m_shiftz);
	DDX_Text(pDX, IDC_REP_X, m_nRepX);
	DDX_Text(pDX, IDC_REP_Y, m_nRepY);
	DDX_Text(pDX, IDC_REP_Z, m_nRepZ);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CReplicateDialog, CDialog)
	//{{AFX_MSG_MAP(CReplicateDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReplicateDialog message handlers

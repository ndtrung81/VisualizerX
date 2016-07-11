// BODDialog.cpp : implementation file
//

#include "stdafx.h"
#include "visualizer_x.h"
#include "BODDialog.h"
#include "Visualizer_XView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBODDialog dialog


CBODDialog::CBODDialog(CWnd* pParent /*=NULL*/)
	: CModelessDialog(CBODDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBODDialog)
	m_nType = 0;
	m_cut_in = 1.0;
	m_cut_out = 2.0;
	m_nMaxPoints = 256;
	m_nWindowSize = 0;
	m_sStatus = _T("Ready");
	m_bShowBonds = FALSE;
	m_sCoordinationNumber = _T("Coordination number:");
	//}}AFX_DATA_INIT
}


void CBODDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBODDialog)
	DDX_CBIndex(pDX, IDC_COMBO_TYPE, m_nType);
	DDX_Text(pDX, IDC_CUTIN, m_cut_in);
	DDX_Text(pDX, IDC_CUTOUT, m_cut_out);
	DDX_Text(pDX, IDC_MAXPOINTS, m_nMaxPoints);
	DDX_Text(pDX, IDC_WINDOWSIZE, m_nWindowSize);
	DDX_Text(pDX, IDC_STATIC_STATUS, m_sStatus);
	DDX_Check(pDX, IDC_CHECK_SHOWBONDS, m_bShowBonds);
	DDX_Text(pDX, IDC_STATIC_COORD, m_sCoordinationNumber);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBODDialog, CModelessDialog)
	//{{AFX_MSG_MAP(CBODDialog)
	ON_BN_CLICKED(IDC_UPDATE, OnUpdateParams)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_CHECK_SHOWBONDS, OnCheckShowbonds)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBODDialog message handlers

void CBODDialog::OnUpdateParams() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	m_sStatus.Format("Computing..");
	UpdateData(FALSE);
	((CVisualizer_XView*)m_pParent)->m_nChosenType = m_nType-1;
	((CVisualizer_XView*)m_pParent)->m_cut_in = m_cut_in;
	((CVisualizer_XView*)m_pParent)->m_cut_out = m_cut_out;
	((CVisualizer_XView*)m_pParent)->m_nMaxPoints = m_nMaxPoints;
	((CVisualizer_XView*)m_pParent)->m_nBODWindowSize = m_nWindowSize;
	((CVisualizer_XView*)m_pParent)->m_bDrawingBonds = m_bShowBonds;

	((CVisualizer_XView*)m_pParent)->ComputeBOD();
	
	double coordinationNumber = ((CVisualizer_XView*)m_pParent)->m_coordinationNumber;

	m_sCoordinationNumber.Format("Coordination number: %0.3f", coordinationNumber);

	m_sStatus.Format("Ready");
	UpdateData(FALSE);
	
}

void CBODDialog::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	((CVisualizer_XView*)m_pParent)->m_pBODDialog = NULL;
	DestroyWindow();
}

//DEL void CBODDialog::OnSelchangeComboType() 
//DEL {
//DEL 	// TODO: Add your control notification handler code here
//DEL 	UpdateData(TRUE);
//DEL 
//DEL 	((CVisualizer_XView*)m_pParent)->m_nChosenType = m_nType-1;
//DEL 
//DEL 	m_sStatus.Format("Computing..");
//DEL 	UpdateData(FALSE);
//DEL 	
//DEL 	((CVisualizer_XView*)m_pParent)->ComputeBOD();
//DEL 
//DEL 	m_sStatus.Format("Ready");
//DEL 	UpdateData(FALSE);
//DEL }

void CBODDialog::OnCheckShowbonds() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	((CVisualizer_XView*)m_pParent)->m_bDrawingBonds = m_bShowBonds;
	((CVisualizer_XView*)m_pParent)->Invalidate();
}

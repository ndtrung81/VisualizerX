// ProjectionDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Visualizer_X.h"
#include "ProjectionDialog.h"
#include "Visualizer_XView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProjectionDialog dialog

CProjectionDialog::CProjectionDialog(CWnd* pParent /*=NULL*/)
	: CModelessDialog(CProjectionDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProjectionDialog)
	m_bottom = 0.0;
	m_left = 0.0;
	m_bPerspective = 1;
	m_right = 0.0;
	m_top = 0.0;
	m_near = 0.0;
	m_far = 0.0;
	m_translate = 0.0;
	m_scale = 0.0;
	//}}AFX_DATA_INIT
}


void CProjectionDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProjectionDialog)
	DDX_Text(pDX, IDC_BOTTOM, m_bottom);
	DDX_Text(pDX, IDC_LEFT, m_left);
	DDX_Radio(pDX, IDC_ORTHO, m_bPerspective);
	DDX_Text(pDX, IDC_RIGHT, m_right);
	DDX_Text(pDX, IDC_TOP, m_top);
	DDX_Text(pDX, IDC_NEAR, m_near);
	DDX_Text(pDX, IDC_FAR, m_far);
	DDX_Text(pDX, IDC_TRANSLATE, m_translate);
	DDX_Text(pDX, IDC_SCALE, m_scale);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CProjectionDialog, CDialog)
	//{{AFX_MSG_MAP(CProjectionDialog)
	ON_EN_KILLFOCUS(IDC_BOTTOM, OnKillfocusControls)
	ON_BN_CLICKED(IDC_RESET, OnReset)
	ON_EN_KILLFOCUS(IDC_FAR, OnKillfocusControls)
	ON_BN_CLICKED(IDC_FRUSTUM, OnKillfocusControls)
	ON_EN_KILLFOCUS(IDC_LEFT, OnKillfocusControls)
	ON_EN_KILLFOCUS(IDC_NEAR, OnKillfocusControls)
	ON_BN_CLICKED(IDC_ORTHO, OnKillfocusControls)
	ON_EN_KILLFOCUS(IDC_RIGHT, OnKillfocusControls)
	ON_EN_KILLFOCUS(IDC_TOP, OnKillfocusControls)
	ON_EN_KILLFOCUS(IDC_TRANSLATE, OnKillfocusControls)
	ON_EN_KILLFOCUS(IDC_SCALE, OnKillfocusControls)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProjectionDialog message handlers

void CProjectionDialog::OnOK() 
{
	// TODO: Add extra validation here
	((CVisualizer_XView*)m_pParent)->m_pProjectionDialog = NULL;
	DestroyWindow();
}

void CProjectionDialog::OnKillfocusControls() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	((CVisualizer_XView*)m_pParent)->UpdateProjection();
}

void CProjectionDialog::OnReset() 
{
	// TODO: Add your control notification handler code here
	((CVisualizer_XView*)m_pParent)->ResetView();
}

void CProjectionDialog::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	((CVisualizer_XView*)m_pParent)->m_pProjectionDialog = NULL;
	DestroyWindow();
}

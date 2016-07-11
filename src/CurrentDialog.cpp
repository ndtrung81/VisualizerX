// CurrentDialog.cpp : implementation file
//

#include "stdafx.h"
#include "visualizer_x.h"
#include "CurrentDialog.h"

#include "Visualizer_XView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCurrentDialog dialog


CCurrentDialog::CCurrentDialog(CWnd* pParent /*=NULL*/)
	: CModelessDialog(CCurrentDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCurrentDialog)
	m_xLightAngle = 0.0;
	m_xLightPosition = 0.0;
	m_yLightAngle = 0.0;
	m_yLightPosition = 0.0;
	m_zLightAngle = 0.0;
	m_zLightPosition = 0.0;
	m_particleScale = 0.0;
	m_bottom = 0.0;
	m_far = 0.0;
	m_left = 0.0;
	m_near = 0.0;
	m_right = 0.0;
	m_scale = 0.0;
	m_top = 0.0;
	m_translate = 0.0;
	m_xAngle = 0.0;
	m_yAngle = 0.0;
	m_zAngle = 0.0;
	m_lightConstantAttenuation = 0.0;
	m_lightLinearAttenuation = 0.0;
	m_lightQuadraticAttenuation = 0.0;
	//}}AFX_DATA_INIT
}


void CCurrentDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCurrentDialog)
	DDX_Text(pDX, IDC_LIGHT_XANGLE, m_xLightAngle);
	DDX_Text(pDX, IDC_LIGHT_XPOS, m_xLightPosition);
	DDX_Text(pDX, IDC_LIGHT_YANGLE, m_yLightAngle);
	DDX_Text(pDX, IDC_LIGHT_YPOS, m_yLightPosition);
	DDX_Text(pDX, IDC_LIGHT_ZANGLE, m_zLightAngle);
	DDX_Text(pDX, IDC_LIGHT_ZPOS, m_zLightPosition);
	DDX_Text(pDX, IDC_PARTICLE_SCALE, m_particleScale);
	DDX_Text(pDX, IDC_VIEW_BOTTOM, m_bottom);
	DDX_Text(pDX, IDC_VIEW_FAR, m_far);
	DDX_Text(pDX, IDC_VIEW_LEFT, m_left);
	DDX_Text(pDX, IDC_VIEW_NEAR, m_near);
	DDX_Text(pDX, IDC_VIEW_RIGHT, m_right);
	DDX_Text(pDX, IDC_VIEW_SCALE, m_scale);
	DDX_Text(pDX, IDC_VIEW_TOP, m_top);
	DDX_Text(pDX, IDC_VIEW_TRANSLATE, m_translate);
	DDX_Text(pDX, IDC_VIEW_XANGLE, m_xAngle);
	DDX_Text(pDX, IDC_VIEW_YANGLE, m_yAngle);
	DDX_Text(pDX, IDC_VIEW_ZANGLE, m_zAngle);
	DDX_Text(pDX, IDC_LIGHT_CONSTANT, m_lightConstantAttenuation);
	DDX_Text(pDX, IDC_LIGHT_LINEAR, m_lightLinearAttenuation);
	DDX_Text(pDX, IDC_LIGHT_QUAD, m_lightQuadraticAttenuation);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCurrentDialog, CDialog)
	//{{AFX_MSG_MAP(CCurrentDialog)
	ON_BN_CLICKED(IDC_UPDATE, OnUpdateParams)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_RESET, OnReset)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCurrentDialog message handlers

void CCurrentDialog::OnUpdateParams() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	((CVisualizer_XView*)m_pParent)->UpdateParams();
}

void CCurrentDialog::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	((CVisualizer_XView*)m_pParent)->m_pCurrentDialog = NULL;
	DestroyWindow();
}

void CCurrentDialog::OnReset() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	((CVisualizer_XView*)m_pParent)->ResetParams();	
}

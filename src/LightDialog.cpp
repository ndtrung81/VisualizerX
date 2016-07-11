// LightDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Visualizer_X.h"
#include "LightDialog.h"

#include "Visualizer_XView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLightDialog dialog


CLightDialog::CLightDialog(CWnd* pParent /*=NULL*/)
	: CModelessDialog(CLightDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLightDialog)
	m_pos_x = 1.0;
	m_pos_y = 1.0;
	m_pos_z = 1.0;
	m_bPointSrc = FALSE;
	
	//}}AFX_DATA_INIT

	m_ambientLight[0] = 1.0f;
	m_ambientLight[1] = 1.0f;
	m_ambientLight[2] = 1.0f;
	m_ambientLight[3] = 1.0f;

	m_diffuseLight[0] = 0.4f;
	m_diffuseLight[1] = 0.4f;
	m_diffuseLight[2] = 0.4f;
	m_diffuseLight[3] = 1.0f;

	m_specularLight[0] = 0.8f;
	m_specularLight[1] = 0.8f;
	m_specularLight[2] = 0.8f;
	m_specularLight[3] = 1.0f;
	
	m_positionLight[0] = 1.0f;
	m_positionLight[1] = 1.0f;
	m_positionLight[2] = 1.0f;
	m_positionLight[3] = 0.0f;
}


void CLightDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLightDialog)
	DDX_Control(pDX, IDC_SLIDER_SPECULAR_RED, m_specularRed);
	DDX_Control(pDX, IDC_SLIDER_SPECULAR_GREEN, m_specularGreen);
	DDX_Control(pDX, IDC_SLIDER_SPECULAR_BLUE, m_specularBlue);
	DDX_Control(pDX, IDC_SLIDER_DIFFUSE_RED, m_diffuseRed);
	DDX_Control(pDX, IDC_SLIDER_DIFFUSE_GREEN, m_diffuseGreen);
	DDX_Control(pDX, IDC_SLIDER_DIFFUSE_BLUE, m_diffuseBlue);
	DDX_Control(pDX, IDC_SLIDER_AMBIENT_RED, m_ambientRed);
	DDX_Control(pDX, IDC_SLIDER_AMBIENT_GREEN, m_ambientGreen);
	DDX_Control(pDX, IDC_SLIDER_AMBIENT_BLUE, m_ambientBlue);
	DDX_Text(pDX, IDC_LIGHT_POS_Y, m_pos_y);
	DDX_Text(pDX, IDC_LIGHT_POS_Z, m_pos_z);
	DDX_Check(pDX, IDC_CHECK_POINT_SRC, m_bPointSrc);
	DDX_Text(pDX, IDC_LIGHT_POS_X, m_pos_x);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLightDialog, CDialog)
	//{{AFX_MSG_MAP(CLightDialog)
	ON_WM_CLOSE()
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_AMBIENT_BLUE, OnReleasedcaptureSlider)
	ON_EN_CHANGE(IDC_LIGHT_POS_X, OnChangeLightPos)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_AMBIENT_GREEN, OnReleasedcaptureSlider)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_AMBIENT_RED, OnReleasedcaptureSlider)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_DIFFUSE_BLUE, OnReleasedcaptureSlider)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_DIFFUSE_GREEN, OnReleasedcaptureSlider)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_DIFFUSE_RED, OnReleasedcaptureSlider)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_SPECULAR_BLUE, OnReleasedcaptureSlider)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_SPECULAR_GREEN, OnReleasedcaptureSlider)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_SPECULAR_RED, OnReleasedcaptureSlider)
	ON_EN_CHANGE(IDC_LIGHT_POS_Y, OnChangeLightPos)
	ON_EN_CHANGE(IDC_LIGHT_POS_Z, OnChangeLightPos)
	ON_BN_CLICKED(IDC_CHECK_POINT_SRC, OnCheckPointSrc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLightDialog message handlers

BOOL CLightDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_ambientBlue.SetRange(0, 255);
	m_ambientGreen.SetRange(0, 255);
	m_ambientRed.SetRange(0, 255);

	m_diffuseBlue.SetRange(0, 255);
	m_diffuseGreen.SetRange(0, 255);
	m_diffuseRed.SetRange(0, 255);

	m_specularBlue.SetRange(0, 255);
	m_specularGreen.SetRange(0, 255);
	m_specularRed.SetRange(0, 255);

	SetAmbientLight(m_ambientLight);
	SetDiffuseLight(m_diffuseLight);
	SetSpecularLight(m_specularLight);
	SetPositionLight(m_positionLight);

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//////////////////////////////////////////////////////////////////
//

void CLightDialog::GetAmbientLight(double *ambient)
{
	ambient[0] = (double) m_ambientRed.GetPos() / 255.0;
	ambient[1] = (double) m_ambientGreen.GetPos() / 255.0;
	ambient[2] = (double) m_ambientBlue.GetPos() / 255.0;
	ambient[3] = 1.0;
}

void CLightDialog::GetDiffuseLight(double *diffuse)
{
	diffuse[0] = (double) m_diffuseRed.GetPos() / 255.0;
	diffuse[1] = (double) m_diffuseGreen.GetPos() / 255.0;
	diffuse[2] = (double) m_diffuseBlue.GetPos() / 255.0;
	diffuse[3] = 1.0;
}

void CLightDialog::GetSpecularLight(double *specular)
{
	specular[0] = (double) m_specularRed.GetPos() / 255.0;
	specular[1] = (double) m_specularGreen.GetPos() / 255.0;
	specular[2] = (double) m_specularBlue.GetPos() / 255.0;
	specular[3] = 1.0;
}

void CLightDialog::GetPositionLight(double *position)
{
	position[0] = m_pos_x;
	position[1] = m_pos_y;
	position[2] = m_pos_z;
	if (m_bPointSrc == TRUE)
		position[3] = 1.0;
	else
		position[3] = 0.0;
}


void CLightDialog::SetAmbientLight(double *ambient)
{
	m_ambientRed.SetPos((int)(ambient[0] * 255.0));
	m_ambientGreen.SetPos((int)(ambient[1] * 255.0));
	m_ambientBlue.SetPos((int)(ambient[2] * 255.0));
}

void CLightDialog::SetDiffuseLight(double *diffuse)
{
	m_diffuseRed.SetPos((int)(diffuse[0] * 255.0));
	m_diffuseGreen.SetPos((int)(diffuse[1] * 255.0));
	m_diffuseBlue.SetPos((int)(diffuse[2] * 255.0));
}

void CLightDialog::SetSpecularLight(double *specular)
{
	m_specularRed.SetPos((int)(specular[0] * 255.0));
	m_specularGreen.SetPos((int)(specular[1] * 255.0));
	m_specularBlue.SetPos((int)(specular[2] * 255.0));
}

void CLightDialog::SetPositionLight(double *position)
{
	m_pos_x = position[0];
	m_pos_y = position[1];
	m_pos_z = position[2];

	if (position[3] == 1.0)
		m_bPointSrc = TRUE;
	else
		m_bPointSrc = FALSE;
}

void CLightDialog::OnOK() 
{
	// TODO: Add extra validation here
	((CVisualizer_XView*)m_pParent)->m_pLightDialog = NULL;
	DestroyWindow();
}


void CLightDialog::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	((CVisualizer_XView*)m_pParent)->m_pLightDialog = NULL;
	DestroyWindow();
}

void CLightDialog::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	delete this;
}

void CLightDialog::OnReleasedcaptureSlider(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	GetAmbientLight(m_ambientLight);
	GetDiffuseLight(m_diffuseLight);
	GetSpecularLight(m_specularLight);

	((CVisualizer_XView*)m_pParent)->UpdateLight();

	*pResult = 0;
}

void CLightDialog::OnChangeLightPos() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	GetPositionLight(m_positionLight);

	((CVisualizer_XView*)m_pParent)->UpdateLight();
}

void CLightDialog::OnCheckPointSrc() 
{
	// TODO: Add your control notification handler code here
	m_bPointSrc = !m_bPointSrc;	

	GetPositionLight(m_positionLight);

	((CVisualizer_XView*)m_pParent)->UpdateLight();
}

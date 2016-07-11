// MaterialsDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Visualizer_X.h"
#include "MaterialsDialog.h"

#include "Visualizer_XView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMaterialsDialog dialog


CMaterialsDialog::CMaterialsDialog(CWnd* pParent /*=NULL*/)
	: CModelessDialog(CMaterialsDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMaterialsDialog)
	m_shininess = 0.0;
	m_nMaterialsType = 0;
	m_nPresetColor = 0;
	//}}AFX_DATA_INIT
}


void CMaterialsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMaterialsDialog)
	DDX_Control(pDX, IDC_SLIDER_EMISSION_ALPHA, m_emissionAlpha);
	DDX_Control(pDX, IDC_SLIDER_SPECULAR_ALPHA, m_specularAlpha);
	DDX_Control(pDX, IDC_SLIDER_DIFFUSE_ALPHA, m_diffuseAlpha);
	DDX_Control(pDX, IDC_SLIDER_AMBIENT_ALPHA, m_ambientAlpha);
	DDX_Control(pDX, IDC_SLIDER_EMISSION_RED, m_emissionRed);
	DDX_Control(pDX, IDC_SLIDER_EMISSION_GREEN, m_emissionGreen);
	DDX_Control(pDX, IDC_SLIDER_EMISSION_BLUE, m_emissionBlue);
	DDX_Control(pDX, IDC_SLIDER_SPECULAR_RED, m_specularRed);
	DDX_Control(pDX, IDC_SLIDER_SPECULAR_GREEN, m_specularGreen);
	DDX_Control(pDX, IDC_SLIDER_SPECULAR_BLUE, m_specularBlue);
	DDX_Control(pDX, IDC_SLIDER_DIFFUSE_RED, m_diffuseRed);
	DDX_Control(pDX, IDC_SLIDER_DIFFUSE_GREEN, m_diffuseGreen);
	DDX_Control(pDX, IDC_SLIDER_DIFFUSE_BLUE, m_diffuseBlue);
	DDX_Control(pDX, IDC_SLIDER_AMBIENT_RED, m_ambientRed);
	DDX_Control(pDX, IDC_SLIDER_AMBIENT_GREEN, m_ambientGreen);
	DDX_Control(pDX, IDC_SLIDER_AMBIENT_BLUE, m_ambientBlue);
	DDX_Text(pDX, IDC_SHININESS, m_shininess);
	DDX_CBIndex(pDX, IDC_COMBO_MATTYPE, m_nMaterialsType);
	DDX_CBIndex(pDX, IDC_COMBO_COLOR, m_nPresetColor);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMaterialsDialog, CDialog)
	//{{AFX_MSG_MAP(CMaterialsDialog)
	ON_WM_CLOSE()
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_AMBIENT_RED, OnReleasedcaptureSlider)
	ON_CBN_SELCHANGE(IDC_COMBO_MATTYPE, OnSelchangeComboMattype)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_AMBIENT_BLUE, OnReleasedcaptureSlider)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_AMBIENT_GREEN, OnReleasedcaptureSlider)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_DIFFUSE_BLUE, OnReleasedcaptureSlider)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_DIFFUSE_GREEN, OnReleasedcaptureSlider)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_DIFFUSE_RED, OnReleasedcaptureSlider)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_EMISSION_BLUE, OnReleasedcaptureSlider)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_EMISSION_GREEN, OnReleasedcaptureSlider)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_EMISSION_RED, OnReleasedcaptureSlider)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_SPECULAR_BLUE, OnReleasedcaptureSlider)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_SPECULAR_GREEN, OnReleasedcaptureSlider)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_SPECULAR_RED, OnReleasedcaptureSlider)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_AMBIENT_ALPHA, OnReleasedcaptureSlider)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_DIFFUSE_ALPHA, OnReleasedcaptureSlider)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_EMISSION_ALPHA, OnReleasedcaptureSlider)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_SPECULAR_ALPHA, OnReleasedcaptureSlider)
	ON_CBN_SELCHANGE(IDC_COMBO_COLOR, OnSelchangeComboColor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMaterialsDialog message handlers

void CMaterialsDialog::GetMaterialAmbient(double *ambient)
{
	ambient[0] = (double) m_ambientRed.GetPos() / 255.0;
	ambient[1] = (double) m_ambientGreen.GetPos() / 255.0;
	ambient[2] = (double) m_ambientBlue.GetPos() / 255.0;
	ambient[3] = (double) m_ambientAlpha.GetPos() / 255.0;;
}

void CMaterialsDialog::GetMaterialDiffuse(double *diffuse)
{
	diffuse[0] = (double) m_diffuseRed.GetPos() / 255.0;
	diffuse[1] = (double) m_diffuseGreen.GetPos() / 255.0;
	diffuse[2] = (double) m_diffuseBlue.GetPos() / 255.0;
	diffuse[3] = (double) m_diffuseAlpha.GetPos() / 255.0;;
}

void CMaterialsDialog::GetMaterialSpecular(double *specular)
{
	specular[0] = (double) m_specularRed.GetPos() / 255.0;
	specular[1] = (double) m_specularGreen.GetPos() / 255.0;
	specular[2] = (double) m_specularBlue.GetPos() / 255.0;
	specular[3] = (double) m_specularAlpha.GetPos() / 255.0;
}

void CMaterialsDialog::GetMaterialEmission(double *emission)
{
	emission[0] = (double) m_emissionRed.GetPos() / 255.0;
	emission[1] = (double) m_emissionGreen.GetPos() / 255.0;
	emission[2] = (double) m_emissionBlue.GetPos() / 255.0;
	emission[3] = (double) m_emissionAlpha.GetPos() / 255.0;
}


void CMaterialsDialog::SetMaterialAmbient(double *ambient)
{
	m_ambientRed.SetPos((int)(ambient[0] * 255.0));
	m_ambientGreen.SetPos((int)(ambient[1] * 255.0));
	m_ambientBlue.SetPos((int)(ambient[2] * 255.0));
	m_ambientAlpha.SetPos((int)(ambient[3] * 255.0));
}

void CMaterialsDialog::SetMaterialDiffuse(double *diffuse)
{
	m_diffuseRed.SetPos((int)(diffuse[0] * 255.0));
	m_diffuseGreen.SetPos((int)(diffuse[1] * 255.0));
	m_diffuseBlue.SetPos((int)(diffuse[2] * 255.0));
	m_diffuseAlpha.SetPos((int)(diffuse[3] * 255.0));
}

void CMaterialsDialog::SetMaterialSpecular(double *specular)
{
	m_specularRed.SetPos((int)(specular[0] * 255.0));
	m_specularGreen.SetPos((int)(specular[1] * 255.0));
	m_specularBlue.SetPos((int)(specular[2] * 255.0));
	m_specularAlpha.SetPos((int)(specular[3] * 255.0));
}


void CMaterialsDialog::SetMaterialEmission(double *emission)
{
	m_emissionRed.SetPos((int)(emission[0] * 255.0));
	m_emissionGreen.SetPos((int)(emission[1] * 255.0));
	m_emissionBlue.SetPos((int)(emission[2] * 255.0));
	m_emissionAlpha.SetPos((int)(emission[3] * 255.0));
}	


BOOL CMaterialsDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_ambientBlue.SetRange(0, 255);
	m_ambientGreen.SetRange(0, 255);
	m_ambientRed.SetRange(0, 255);
	m_ambientAlpha.SetRange(0, 255);

	m_diffuseBlue.SetRange(0, 255);
	m_diffuseGreen.SetRange(0, 255);
	m_diffuseRed.SetRange(0, 255);
	m_diffuseAlpha.SetRange(0, 255);

	m_specularBlue.SetRange(0, 255);
	m_specularGreen.SetRange(0, 255);
	m_specularRed.SetRange(0, 255);
	m_specularAlpha.SetRange(0, 255);

	m_emissionBlue.SetRange(0, 255);
	m_emissionGreen.SetRange(0, 255);
	m_emissionRed.SetRange(0, 255);
	m_emissionAlpha.SetRange(0, 255);

	SetMaterialAmbient(m_materialAmbient);
	SetMaterialDiffuse(m_materialDiffuse);
	SetMaterialSpecular(m_materialSpecular);
	SetMaterialEmission(m_materialEmission);

//	HICON hIcon = AfxGetApp()->LoadIcon(IDR_MATERIALS);
//	SetIcon(hIcon, TRUE);
//	SetIcon(hIcon, FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMaterialsDialog::OnApply() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	GetMaterialAmbient(m_materialAmbient);
	GetMaterialDiffuse(m_materialDiffuse);
	GetMaterialSpecular(m_materialSpecular);
	GetMaterialEmission(m_materialEmission);

	((CVisualizer_XView*)m_pParent)->UpdateMaterials();
}

void CMaterialsDialog::OnOK() 
{
	// TODO: Add extra validation here
	((CVisualizer_XView*)m_pParent)->m_pMaterialsDialog = NULL;
	DestroyWindow();
}

void CMaterialsDialog::OnClose() 
{
	// TODO: Add extra validation here
	((CVisualizer_XView*)m_pParent)->m_pMaterialsDialog = NULL;
	DestroyWindow();
}

void CMaterialsDialog::OnReleasedcaptureSlider(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	GetMaterialAmbient(m_materialAmbient);
	GetMaterialDiffuse(m_materialDiffuse);
	GetMaterialSpecular(m_materialSpecular);
	GetMaterialEmission(m_materialEmission);

	((CVisualizer_XView*)m_pParent)->UpdateMaterials();

	*pResult = 0;
}

void CMaterialsDialog::OnUpdateMaterialsType() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_UPDATE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	m_materialAmbient[0] = ((CVisualizer_XView*)m_pParent)->m_materialAmbient[m_nMaterialsType][0];
	m_materialAmbient[1] = ((CVisualizer_XView*)m_pParent)->m_materialAmbient[m_nMaterialsType][1];
	m_materialAmbient[2] = ((CVisualizer_XView*)m_pParent)->m_materialAmbient[m_nMaterialsType][2];
	m_materialAmbient[3] = ((CVisualizer_XView*)m_pParent)->m_materialAmbient[m_nMaterialsType][3];
	
	m_materialDiffuse[0] = ((CVisualizer_XView*)m_pParent)->m_materialDiffuse[m_nMaterialsType][0];
	m_materialDiffuse[1] = ((CVisualizer_XView*)m_pParent)->m_materialDiffuse[m_nMaterialsType][1];
	m_materialDiffuse[2] = ((CVisualizer_XView*)m_pParent)->m_materialDiffuse[m_nMaterialsType][2];
	m_materialDiffuse[3] = ((CVisualizer_XView*)m_pParent)->m_materialDiffuse[m_nMaterialsType][3];

	m_materialSpecular[0] = ((CVisualizer_XView*)m_pParent)->m_materialSpecular[0];
	m_materialSpecular[1] = ((CVisualizer_XView*)m_pParent)->m_materialSpecular[1];
	m_materialSpecular[2] = ((CVisualizer_XView*)m_pParent)->m_materialSpecular[2];
	m_materialSpecular[3] = ((CVisualizer_XView*)m_pParent)->m_materialSpecular[3];

	m_materialEmission[0] = ((CVisualizer_XView*)m_pParent)->m_materialEmission[0];
	m_materialEmission[1] = ((CVisualizer_XView*)m_pParent)->m_materialEmission[1];
	m_materialEmission[2] = ((CVisualizer_XView*)m_pParent)->m_materialEmission[2];
	m_materialEmission[3] = ((CVisualizer_XView*)m_pParent)->m_materialEmission[3];
	
	SetMaterialAmbient(m_materialAmbient);
	SetMaterialDiffuse(m_materialDiffuse);
	SetMaterialSpecular(m_materialSpecular);
	SetMaterialEmission(m_materialEmission);
}


void CMaterialsDialog::OnSelchangeComboMattype() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	m_materialAmbient[0] = ((CVisualizer_XView*)m_pParent)->m_materialAmbient[m_nMaterialsType][0];
	m_materialAmbient[1] = ((CVisualizer_XView*)m_pParent)->m_materialAmbient[m_nMaterialsType][1];
	m_materialAmbient[2] = ((CVisualizer_XView*)m_pParent)->m_materialAmbient[m_nMaterialsType][2];
	m_materialAmbient[3] = ((CVisualizer_XView*)m_pParent)->m_materialAmbient[m_nMaterialsType][3];
	
	m_materialDiffuse[0] = ((CVisualizer_XView*)m_pParent)->m_materialDiffuse[m_nMaterialsType][0];
	m_materialDiffuse[1] = ((CVisualizer_XView*)m_pParent)->m_materialDiffuse[m_nMaterialsType][1];
	m_materialDiffuse[2] = ((CVisualizer_XView*)m_pParent)->m_materialDiffuse[m_nMaterialsType][2];
	m_materialDiffuse[3] = ((CVisualizer_XView*)m_pParent)->m_materialDiffuse[m_nMaterialsType][3];
	
	m_materialSpecular[0] = ((CVisualizer_XView*)m_pParent)->m_materialSpecular[0];
	m_materialSpecular[1] = ((CVisualizer_XView*)m_pParent)->m_materialSpecular[1];
	m_materialSpecular[2] = ((CVisualizer_XView*)m_pParent)->m_materialSpecular[2];
	m_materialSpecular[3] = ((CVisualizer_XView*)m_pParent)->m_materialSpecular[3];

	m_materialEmission[0] = ((CVisualizer_XView*)m_pParent)->m_materialEmission[0];
	m_materialEmission[1] = ((CVisualizer_XView*)m_pParent)->m_materialEmission[1];
	m_materialEmission[2] = ((CVisualizer_XView*)m_pParent)->m_materialEmission[2];
	m_materialEmission[3] = ((CVisualizer_XView*)m_pParent)->m_materialEmission[3];

	SetMaterialAmbient(m_materialAmbient);
	SetMaterialDiffuse(m_materialDiffuse);
	SetMaterialSpecular(m_materialSpecular);
	SetMaterialEmission(m_materialEmission);

	((CVisualizer_XView*)m_pParent)->UpdateMaterials();
}


void CMaterialsDialog::OnSelchangeComboColor() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	m_materialAmbient[0] = ((CVisualizer_XView*)m_pParent)->m_materialAmbient[m_nPresetColor][0];
	m_materialAmbient[1] = ((CVisualizer_XView*)m_pParent)->m_materialAmbient[m_nPresetColor][1];
	m_materialAmbient[2] = ((CVisualizer_XView*)m_pParent)->m_materialAmbient[m_nPresetColor][2];
	m_materialAmbient[3] = ((CVisualizer_XView*)m_pParent)->m_materialAmbient[m_nPresetColor][3];
	
	m_materialDiffuse[0] = ((CVisualizer_XView*)m_pParent)->m_materialDiffuse[m_nPresetColor][0];
	m_materialDiffuse[1] = ((CVisualizer_XView*)m_pParent)->m_materialDiffuse[m_nPresetColor][1];
	m_materialDiffuse[2] = ((CVisualizer_XView*)m_pParent)->m_materialDiffuse[m_nPresetColor][2];
	m_materialDiffuse[3] = ((CVisualizer_XView*)m_pParent)->m_materialDiffuse[m_nPresetColor][3];
	
	m_materialSpecular[0] = ((CVisualizer_XView*)m_pParent)->m_materialSpecular[0];
	m_materialSpecular[1] = ((CVisualizer_XView*)m_pParent)->m_materialSpecular[1];
	m_materialSpecular[2] = ((CVisualizer_XView*)m_pParent)->m_materialSpecular[2];
	m_materialSpecular[3] = ((CVisualizer_XView*)m_pParent)->m_materialSpecular[3];

	m_materialEmission[0] = ((CVisualizer_XView*)m_pParent)->m_materialEmission[0];
	m_materialEmission[1] = ((CVisualizer_XView*)m_pParent)->m_materialEmission[1];
	m_materialEmission[2] = ((CVisualizer_XView*)m_pParent)->m_materialEmission[2];
	m_materialEmission[3] = ((CVisualizer_XView*)m_pParent)->m_materialEmission[3];

	SetMaterialAmbient(m_materialAmbient);
	SetMaterialDiffuse(m_materialDiffuse);
	SetMaterialSpecular(m_materialSpecular);
	SetMaterialEmission(m_materialEmission);

	((CVisualizer_XView*)m_pParent)->UpdateMaterials();
}

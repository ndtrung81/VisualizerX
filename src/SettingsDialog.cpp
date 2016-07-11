// SettingsDialog.cpp : implementation file
//

#include "stdafx.h"
#include "visualizer_x.h"
#include "SettingsDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSettingsDialog dialog


CSettingsDialog::CSettingsDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CSettingsDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSettingsDialog)
	m_rotatingStep = 0.0;
	m_particleTranslatingStep = 0.0;
	m_particleScalingStep = 0.0;
	m_bXRotate = FALSE;
	m_bYRotate = FALSE;
	m_bZRotate = FALSE;
	m_xModelAngle = 0.0;
	m_yModelAngle = 0.0;
	m_zModelAngle = 0.0;
	m_bUseTwoLightSources = FALSE;
	m_nTranslatingDirection = 0;
	m_bBlend = FALSE;
	m_nApplyDrawingCommand = TRUE;
	m_nResolution = 0;
	m_bFogging = FALSE;
	m_fogDensity = 0.0;
	m_nFogMode = 0;
	m_fog_far = 0.0;
	m_fog_near = 0.0;
	m_outlineWidth = 1.0;
	m_bDrawingOutlines = FALSE;
	m_objectScale = 1.0;
	//}}AFX_DATA_INIT
}


void CSettingsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSettingsDialog)
	DDX_Text(pDX, IDC_ROTATESTEP, m_rotatingStep);
	DDX_Text(pDX, IDC_PARTICLETRANSLATESTEP, m_particleTranslatingStep);
	DDX_Text(pDX, IDC_PARTICLESCALESTEP, m_particleScalingStep);
	DDX_Check(pDX, IDC_CHECK_XROTATE, m_bXRotate);
	DDX_Check(pDX, IDC_CHECK_YROTATE, m_bYRotate);
	DDX_Check(pDX, IDC_CHECK_ZROTATE, m_bZRotate);
	DDX_Text(pDX, IDC_XMODELANGLE, m_xModelAngle);
	DDX_Text(pDX, IDC_YMODELANGLE, m_yModelAngle);
	DDX_Text(pDX, IDC_ZMODELANGLE, m_zModelAngle);
	DDX_Check(pDX, IDC_CHECK_TWOLIGHTSRC, m_bUseTwoLightSources);
	DDX_CBIndex(pDX, IDC_COMBO_DIR, m_nTranslatingDirection);
	DDX_Check(pDX, IDC_CHECK_BLEND, m_bBlend);
	DDX_Check(pDX, IDC_CHECK_APPLYCOMMAND, m_nApplyDrawingCommand);
	DDX_Text(pDX, IDC_RESOLUTION, m_nResolution);
	DDV_MinMaxInt(pDX, m_nResolution, 4, 80);
	DDX_Check(pDX, IDC_CHECK_FOGGING, m_bFogging);
	DDX_Text(pDX, IDC_FOGDENSITY, m_fogDensity);
	DDX_CBIndex(pDX, IDC_COMBO_FOGMODE, m_nFogMode);
	DDX_Text(pDX, IDC_FOG_FAR, m_fog_far);
	DDX_Text(pDX, IDC_FOG_NEAR, m_fog_near);
	DDX_Text(pDX, IDC_OUTLINEWIDTH, m_outlineWidth);
	DDX_Check(pDX, IDC_CHECK_OUTLINE, m_bDrawingOutlines);
	DDX_Text(pDX, IDC_OBJECTSCALE, m_objectScale);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSettingsDialog, CDialog)
	//{{AFX_MSG_MAP(CSettingsDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSettingsDialog message handlers

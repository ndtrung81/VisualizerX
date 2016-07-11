// SpecialEffectsPage.cpp : implementation file
//

#include "stdafx.h"
#include "visualizer_x.h"
#include "SpecialEffectsPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSpecialEffectsPage property page

IMPLEMENT_DYNCREATE(CSpecialEffectsPage, CPropertyPage)

CSpecialEffectsPage::CSpecialEffectsPage() : CPropertyPage(CSpecialEffectsPage::IDD)
{
	//{{AFX_DATA_INIT(CSpecialEffectsPage)
	m_bUseTwoLightSources = FALSE;
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
	//}}AFX_DATA_INIT
}

CSpecialEffectsPage::~CSpecialEffectsPage()
{
}

void CSpecialEffectsPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSpecialEffectsPage)
	DDX_Check(pDX, IDC_CHECK_TWOLIGHTSRC, m_bUseTwoLightSources);
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
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSpecialEffectsPage, CPropertyPage)
	//{{AFX_MSG_MAP(CSpecialEffectsPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSpecialEffectsPage message handlers

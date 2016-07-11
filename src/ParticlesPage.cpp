// ParticlesPage.cpp : implementation file
//

#include "stdafx.h"
#include "visualizer_x.h"
#include "ParticlesPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CParticlesPage property page

IMPLEMENT_DYNCREATE(CParticlesPage, CPropertyPage)

CParticlesPage::CParticlesPage() : CPropertyPage(CParticlesPage::IDD)
{
	//{{AFX_DATA_INIT(CParticlesPage)
	m_rotatingStep = 0.0;
	m_particleTranslatingStep = 0.0;
	m_particleScalingStep = 0.0;
	m_nTranslatingDirection = 0;
	m_maxScale = 0.0;
	m_minScale = 0.0;
	m_objectScale = 1.0;
	m_scaleCoeff = 0.0;
	//}}AFX_DATA_INIT
}

CParticlesPage::~CParticlesPage()
{
}

void CParticlesPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CParticlesPage)
	DDX_Text(pDX, IDC_ROTATESTEP, m_rotatingStep);
	DDX_Text(pDX, IDC_PARTICLETRANSLATESTEP, m_particleTranslatingStep);
	DDX_Text(pDX, IDC_PARTICLESCALESTEP, m_particleScalingStep);
	DDX_CBIndex(pDX, IDC_COMBO_DIR, m_nTranslatingDirection);
	DDX_Text(pDX, IDC_PARTICLE_MAXSCALE, m_maxScale);
	DDX_Text(pDX, IDC_PARTICLE_MINSCALE, m_minScale);
	DDX_Text(pDX, IDC_OBJECTSCALE, m_objectScale);
	DDX_Text(pDX, IDC_PARTICLE_SCALINGCOEFF, m_scaleCoeff);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CParticlesPage, CPropertyPage)
	//{{AFX_MSG_MAP(CParticlesPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CParticlesPage message handlers

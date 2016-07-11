// PreprocPage.cpp : implementation file
//

#include "stdafx.h"
#include "visualizer_x.h"
#include "PreprocPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPreprocPage property page

IMPLEMENT_DYNCREATE(CPreprocPage, CPropertyPage)

CPreprocPage::CPreprocPage() : CPropertyPage(CPreprocPage::IDD)
{
	//{{AFX_DATA_INIT(CPreprocPage)
		// NOTE: the ClassWizard will add member initialization here
	m_bXRotate = FALSE;
	m_bYRotate = FALSE;
	m_bZRotate = FALSE;
	m_xModelAngle = 0.0;
	m_yModelAngle = 0.0;
	m_zModelAngle = 0.0;
	//}}AFX_DATA_INIT
}

CPreprocPage::~CPreprocPage()
{
}

void CPreprocPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPreprocPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Check(pDX, IDC_CHECK_XROTATE, m_bXRotate);
	DDX_Check(pDX, IDC_CHECK_YROTATE, m_bYRotate);
	DDX_Check(pDX, IDC_CHECK_ZROTATE, m_bZRotate);
	DDX_Text(pDX, IDC_XMODELANGLE, m_xModelAngle);
	DDX_Text(pDX, IDC_YMODELANGLE, m_yModelAngle);
	DDX_Text(pDX, IDC_ZMODELANGLE, m_zModelAngle);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPreprocPage, CPropertyPage)
	//{{AFX_MSG_MAP(CPreprocPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPreprocPage message handlers

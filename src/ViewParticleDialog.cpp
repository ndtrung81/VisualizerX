// ViewParticleDialog.cpp : implementation file
//

#include "stdafx.h"
#include "visualizer_x.h"
#include "ViewParticleDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewParticleDialog dialog


CViewParticleDialog::CViewParticleDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CViewParticleDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CViewParticleDialog)
	m_nParticleEndIndex = 0;
	m_nParticleStartIndex = 0;
	m_center_box = _T("");
	m_center_sphere = _T("");
	m_Lx = 0.0;
	m_Ly = 0.0;
	m_Lz = 0.0;
	m_nVolType = 0;
	m_bOutside = FALSE;
	m_radius_outer = 0.0;
	m_radius_inner = 0.0;
	//}}AFX_DATA_INIT
}


void CViewParticleDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CViewParticleDialog)
	DDX_Text(pDX, IDC_EDIT_INDEX_END, m_nParticleEndIndex);
	DDX_Text(pDX, IDC_EDIT_INDEX_START, m_nParticleStartIndex);
	DDX_Text(pDX, IDC_CENTER_BOX, m_center_box);
	DDX_Text(pDX, IDC_CENTER_SPHERE, m_center_sphere);
	DDX_Text(pDX, IDC_LX, m_Lx);
	DDX_Text(pDX, IDC_LY, m_Ly);
	DDX_Text(pDX, IDC_LZ, m_Lz);
	DDX_Radio(pDX, IDC_RADIO_VOLTYPE, m_nVolType);
	DDX_Check(pDX, IDC_CHECK_OUTSIDE, m_bOutside);
	DDX_Text(pDX, IDC_RADIUS_OUTER, m_radius_outer);
	DDX_Text(pDX, IDC_RADIUS_INNER, m_radius_inner);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CViewParticleDialog, CDialog)
	//{{AFX_MSG_MAP(CViewParticleDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewParticleDialog message handlers



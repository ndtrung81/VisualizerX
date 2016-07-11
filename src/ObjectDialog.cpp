// ObjectDialog.cpp : implementation file
//

#include "stdafx.h"
#include "visualizer_x.h"
#include "ObjectDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace std;
/////////////////////////////////////////////////////////////////////////////
// CObjectDialog dialog


CObjectDialog::CObjectDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CObjectDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CObjectDialog)
	m_nHeaderLines = 0;
	m_nStartingParticleIdx = 0;
	m_sFileName = _T("");
	m_objectScale = 1.0;
	m_nBeadsInParticle = 1;
	m_strAttachedIndices = _T("0");
	m_nNumObjectsInParticle = 1;
	m_bUseParticleType = TRUE;
	m_nObjectType = 0;
	//}}AFX_DATA_INIT
}


void CObjectDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CObjectDialog)
	DDX_Text(pDX, IDC_HEADERLINES, m_nHeaderLines);
	DDX_Text(pDX, IDC_STARTIDX, m_nStartingParticleIdx);
	DDX_Text(pDX, IDC_STATIC_FILENAME, m_sFileName);
	DDX_Text(pDX, IDC_OBJSCALE, m_objectScale);
	DDX_Text(pDX, IDC_NUMBEADSPERPARTICLE, m_nBeadsInParticle);
	DDX_Text(pDX, IDC_LOCALINDICES, m_strAttachedIndices);
	DDX_Text(pDX, IDC_NUMOBJSPERPARTICLE, m_nNumObjectsInParticle);
	DDX_Check(pDX, IDC_CHECK_USEPARTICLETYPE, m_bUseParticleType);
	DDX_CBIndex(pDX, IDC_COMBO_TYPE, m_nObjectType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CObjectDialog, CDialog)
	//{{AFX_MSG_MAP(CObjectDialog)
	ON_BN_CLICKED(IDC_DEF_FILE, OnDefFile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CObjectDialog message handlers

void CObjectDialog::OnDefFile() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	CFileDialog dlg(TRUE, 
					"txt", 
					NULL, 
					OFN_FILEMUSTEXIST,
					"All Files (*.*)|*.*||",
					this);



	if (dlg.DoModal() == IDOK)
	{
		m_sFileName = dlg.GetPathName();
		
		UpdateData(FALSE);
	}
}

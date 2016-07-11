// ParticleTemplateDialog.cpp : implementation file
//

#include "stdafx.h"
#include "visualizer_x.h"
#include "ParticleTemplateDialog.h"
#include <fstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace std;
/////////////////////////////////////////////////////////////////////////////
// CParticleTemplateDialog dialog


CParticleTemplateDialog::CParticleTemplateDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CParticleTemplateDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CParticleTemplateDialog)
	m_nBeadsSkipped = 2;
	m_sFileName = _T("");
	m_bOverrideNumBeads = FALSE;
	m_nNumBeads = 0;
	m_bReleasePBC = TRUE;
	//}}AFX_DATA_INIT
}


void CParticleTemplateDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CParticleTemplateDialog)
	DDX_Control(pDX, IDC_LIST_FILE_DESCR, m_filePreview);
	DDX_Text(pDX, IDC_NUMBEADS_SKIPPED, m_nBeadsSkipped);
	DDX_Text(pDX, IDC_STATIC_FILENAME, m_sFileName);
	DDX_Check(pDX, IDC_CHECK_OVERRIDENUMBEADS, m_bOverrideNumBeads);
	DDX_Text(pDX, IDC_NUMBEADS, m_nNumBeads);
	DDX_Check(pDX, IDC_CHECK_RELEASEPBC, m_bReleasePBC);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CParticleTemplateDialog, CDialog)
	//{{AFX_MSG_MAP(CParticleTemplateDialog)
	ON_BN_CLICKED(IDC_DEF_FILE, OnDefFile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CParticleTemplateDialog message handlers

void CParticleTemplateDialog::OnDefFile() 
{
	UpdateData(TRUE);

	// TODO: Add your control notification handler code here
	CFileDialog dlg(TRUE, 
					"txt", 
					NULL, 
					OFN_FILEMUSTEXIST,
					"Definition Files (*.txt, *.dat)|*.txt; *.dat|All Files (*.*)|*.*||",
					this);
	
		
	if (dlg.DoModal() == IDOK)
	{
		m_sFileName = dlg.GetPathName();

		UpdateList();

		UpdateData(FALSE);
	}
}

void CParticleTemplateDialog::UpdateList() 
{
	std::ifstream ifs;
	char str[100];
	
	if (strlen(m_sFileName) == 0)
		return;

	ifs.open(m_sFileName);
	if (ifs.fail())
		return;

	m_filePreview.ResetContent();
	while (!ifs.eof())
	{
		ifs.getline(str, 100);

		m_filePreview.AddString(str);
	}

}


BOOL CParticleTemplateDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	UpdateList();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

// ReadDialog.cpp : implementation file
//

#include "stdafx.h"
#include "visualizer_x.h"
#include "ReadDialog.h"
#include "ParticleTemplateDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReadDialog dialog


CReadDialog::CReadDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CReadDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CReadDialog)
	m_bExport2Bmp = FALSE;
	m_sFileRead = _T("");
	m_sScriptFileName = _T("");
	m_bUseTemplate = TRUE;
	m_sTemplateFile = _T("");
	m_nStartingFrame = 0;
	m_sExportingDirectory = _T("");
	//}}AFX_DATA_INIT
	
	m_nBeadsSkipped = 0;
	m_nBeadsInParticle = 1;
	m_bOverrideNumBeads = FALSE;
}


void CReadDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReadDialog)
	DDX_Check(pDX, IDC_CHECK_EXPORTBMP, m_bExport2Bmp);
	DDX_Text(pDX, IDC_STATIC_FILENAME, m_sFileRead);
	DDX_Text(pDX, IDC_STATIC_SCRIPT, m_sScriptFileName);
	DDX_Check(pDX, IDC_CHECK_USETEMPLATE, m_bUseTemplate);
	DDX_Text(pDX, IDC_STATIC_TEMPLATE, m_sTemplateFile);
	DDX_Text(pDX, IDC_STARTING_FRAME, m_nStartingFrame);
	DDX_Text(pDX, IDC_EDIT_WORKINGDIR, m_sExportingDirectory);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CReadDialog, CDialog)
	//{{AFX_MSG_MAP(CReadDialog)
	ON_BN_CLICKED(ID_BROWSE_READ, OnBrowseRead)
	ON_BN_CLICKED(ID_BROWSE_SCRIPT, OnBrowseScript)
	ON_BN_CLICKED(ID_BROWSE_TEMPLATE, OnBrowseTemplate)
	ON_BN_CLICKED(ID_BROWSE_EXPORTDIR, OnBrowseExportdir)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReadDialog message handlers

void CReadDialog::OnBrowseRead() 
{
	// TODO: Add your control notification handler code here
	CFileDialog dlg(TRUE, 
					"txt", 
					NULL, 
					OFN_FILEMUSTEXIST,
					"Visualization Files (*.txt, *.dat)|*.txt; *.dat|All Files (*.*)|*.*||",
					this);

	UpdateData(TRUE);

	if (dlg.DoModal() == IDOK)
	{
		m_sFileRead = dlg.GetPathName();
		
		UpdateData(FALSE);
	}
}

void CReadDialog::OnBrowseScript() 
{
	// TODO: Add your control notification handler code here
	CFileDialog dlg(TRUE, 
					"txt", 
					NULL, 
					OFN_FILEMUSTEXIST,
					"Visualization Files (*.txt, *.dat)|*.txt; *.dat|All Files (*.*)|*.*||",
					this);

	UpdateData(TRUE);

	if (dlg.DoModal() == IDOK)
	{
		m_sScriptFileName = dlg.GetPathName();
		UpdateData(FALSE);
	}
	
}

void CReadDialog::OnBrowseTemplate() 
{
	// TODO: Add your control notification handler code here
		// TODO: Add your command handler code here
	CParticleTemplateDialog dlg;
	CVisualizer_XApp* pApp = (CVisualizer_XApp*)AfxGetApp();
	
	dlg.m_nBeadsSkipped = m_nBeadsSkipped;
	dlg.m_sFileName = pApp->m_sTemplateFileName;		

	UpdateData(TRUE);

	if (dlg.DoModal() == IDOK)
	{
		if (dlg.m_sFileName.GetLength() == 0)
			return;

		m_nBeadsSkipped = dlg.m_nBeadsSkipped;
		pApp->m_sTemplateFileName = dlg.m_sFileName;		
		m_bOverrideNumBeads = dlg.m_bOverrideNumBeads;
		if (m_bOverrideNumBeads == TRUE)
			m_nBeadsInParticle = dlg.m_nNumBeads;

		m_sTemplateFile = dlg.m_sFileName;
		UpdateData(FALSE);
	}
}



void CReadDialog::OnBrowseExportdir() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	CoInitialize(NULL);
	
	BROWSEINFO bfi;
	memset(&bfi, 0, sizeof(BROWSEINFO));
	// replace this with a non-null value if you wish browsing from a specific root folder instead of "my computer"
	bfi.hwndOwner = NULL;

	LPITEMIDLIST pidl = SHBrowseForFolder((LPBROWSEINFO)&bfi);
	LPTSTR pszPath = new TCHAR[MAX_PATH];
	SHGetPathFromIDList(pidl, pszPath);
	
	m_sExportingDirectory.Format("%s", pszPath);

	UpdateData(FALSE);

	delete [] pszPath;
	
	IMalloc* memAllocator = NULL;
	HRESULT hr = CoGetMalloc(1, &memAllocator);
	memAllocator->Free((void*)pidl);
	
	CoUninitialize();

}

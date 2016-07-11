#if !defined(AFX_READDIALOG_H__12522D3D_1AEA_49E2_8B9C_8BBB2062474B__INCLUDED_)
#define AFX_READDIALOG_H__12522D3D_1AEA_49E2_8B9C_8BBB2062474B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ReadDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CReadDialog dialog

class CReadDialog : public CDialog
{
// Construction
public:
	CReadDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CReadDialog)
	enum { IDD = IDD_READ_DIALOG };
	BOOL	m_bExport2Bmp;
	CString	m_sFileRead;
	CString	m_sScriptFileName;
	BOOL	m_bUseTemplate;
	CString	m_sTemplateFile;
	int		m_nStartingFrame;
	CString	m_sExportingDirectory;
	//}}AFX_DATA

	int m_nBeadsInParticle;
	int	m_nBeadsSkipped;
	BOOL	m_bOverrideNumBeads;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReadDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	
	// Generated message map functions
	//{{AFX_MSG(CReadDialog)
	afx_msg void OnBrowseRead();
	afx_msg void OnBrowseScript();
	afx_msg void OnBrowseTemplate();
	afx_msg void OnBrowseExportdir();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_READDIALOG_H__12522D3D_1AEA_49E2_8B9C_8BBB2062474B__INCLUDED_)

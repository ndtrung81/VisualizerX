#if !defined(AFX_PARTICLETEMPLATEDIALOG_H__85C09A8D_9040_43DF_B850_9D946A2C2F09__INCLUDED_)
#define AFX_PARTICLETEMPLATEDIALOG_H__85C09A8D_9040_43DF_B850_9D946A2C2F09__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ParticleTemplateDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CParticleTemplateDialog dialog

class CParticleTemplateDialog : public CDialog
{
// Construction
public:
	CParticleTemplateDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CParticleTemplateDialog)
	enum { IDD = IDD_PARTICLE_DIALOG };
	CListBox	m_filePreview;
	int	m_nBeadsSkipped;
	CString	m_sFileName;
	BOOL	m_bOverrideNumBeads;
	int		m_nNumBeads;
	BOOL	m_bReleasePBC;
	//}}AFX_DATA
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CParticleTemplateDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void	UpdateList();

	// Generated message map functions
	//{{AFX_MSG(CParticleTemplateDialog)
	afx_msg void OnDefFile();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PARTICLETEMPLATEDIALOG_H__85C09A8D_9040_43DF_B850_9D946A2C2F09__INCLUDED_)

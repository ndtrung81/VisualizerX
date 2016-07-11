#if !defined(AFX_OBJECTDIALOG_H__7CC4FE1A_3BFD_4982_81DC_A7C43B95E44A__INCLUDED_)
#define AFX_OBJECTDIALOG_H__7CC4FE1A_3BFD_4982_81DC_A7C43B95E44A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ObjectDialog.h : header file
//

#include <vector>

/////////////////////////////////////////////////////////////////////////////
// CObjectDialog dialog

class CObjectDialog : public CDialog
{
// Construction
public:
	CObjectDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CObjectDialog)
	enum { IDD = IDD_ADDOBJ_DIALOG };
	int		m_nHeaderLines;
	int		m_nStartingParticleIdx;
	CString	m_sFileName;
	double	m_objectScale;
	int		m_nBeadsInParticle;
	CString	m_strAttachedIndices;
	int		m_nNumObjectsInParticle;
	BOOL	m_bUseParticleType;
	int		m_nObjectType;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CObjectDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CObjectDialog)
	afx_msg void OnDefFile();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OBJECTDIALOG_H__7CC4FE1A_3BFD_4982_81DC_A7C43B95E44A__INCLUDED_)

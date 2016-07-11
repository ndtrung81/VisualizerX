#if !defined(AFX_PREPROCPAGE_H__E6E14656_80C9_4EE0_8507_C2B7C534D26A__INCLUDED_)
#define AFX_PREPROCPAGE_H__E6E14656_80C9_4EE0_8507_C2B7C534D26A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PreprocPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPreprocPage dialog

class CPreprocPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CPreprocPage)

// Construction
public:
	CPreprocPage();
	~CPreprocPage();

// Dialog Data
	//{{AFX_DATA(CPreprocPage)
	enum { IDD = IDD_PROPPAGE_SETTINGS_PREPROC };
		// NOTE - ClassWizard will add data members here.
	BOOL	m_bXRotate;
	BOOL	m_bYRotate;
	BOOL	m_bZRotate;
	double	m_xModelAngle;
	double	m_yModelAngle;
	double	m_zModelAngle;
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPreprocPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPreprocPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PREPROCPAGE_H__E6E14656_80C9_4EE0_8507_C2B7C534D26A__INCLUDED_)

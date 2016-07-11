#if !defined(AFX_VIEWPARTICLEDIALOG_H__1FE2FAB5_9C40_428E_8918_FF668EFC8B59__INCLUDED_)
#define AFX_VIEWPARTICLEDIALOG_H__1FE2FAB5_9C40_428E_8918_FF668EFC8B59__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ViewParticleDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CViewParticleDialog dialog

class CViewParticleDialog : public CDialog
{
// Construction
public:
	CViewParticleDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CViewParticleDialog)
	enum { IDD = IDD_VIEWPARTICLE_DIALOG };
	int		m_nParticleEndIndex;
	int		m_nParticleStartIndex;
	CString	m_center_box;
	CString	m_center_sphere;
	double	m_Lx;
	double	m_Ly;
	double	m_Lz;
	int		m_nVolType;
	BOOL	m_bOutside;
	double	m_radius_outer;
	double	m_radius_inner;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewParticleDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CViewParticleDialog)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEWPARTICLEDIALOG_H__1FE2FAB5_9C40_428E_8918_FF668EFC8B59__INCLUDED_)

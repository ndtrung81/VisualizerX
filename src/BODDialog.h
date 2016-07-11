#if !defined(AFX_BODDIALOG_H__DE3638E0_031E_49D8_B1D0_0E6C6D4B8723__INCLUDED_)
#define AFX_BODDIALOG_H__DE3638E0_031E_49D8_B1D0_0E6C6D4B8723__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BODDialog.h : header file
//

#include "ModelessDialog.h"
/////////////////////////////////////////////////////////////////////////////
// CBODDialog dialog

class CBODDialog : public CModelessDialog
{
// Construction
public:
	CBODDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBODDialog)
	enum { IDD = IDD_BOD_DIALOG };
	int		m_nType;
	double	m_cut_in;
	double	m_cut_out;
	int		m_nMaxPoints;
	int		m_nWindowSize;
	CString	m_sStatus;
	BOOL	m_bShowBonds;
	CString	m_sCoordinationNumber;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBODDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBODDialog)
	afx_msg void OnUpdateParams();
	afx_msg void OnClose();
	afx_msg void OnCheckShowbonds();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BODDIALOG_H__DE3638E0_031E_49D8_B1D0_0E6C6D4B8723__INCLUDED_)

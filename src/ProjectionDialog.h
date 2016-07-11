#if !defined(AFX_PROJECTIONDIALOG_H__EAA9C591_4F2D_46A0_BED0_C0545E53AC2F__INCLUDED_)
#define AFX_PROJECTIONDIALOG_H__EAA9C591_4F2D_46A0_BED0_C0545E53AC2F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProjectionDialog.h : header file
//

#include "ModelessDialog.h"
/////////////////////////////////////////////////////////////////////////////
// CProjectionDialog dialog

class CProjectionDialog : public CModelessDialog
{
// Construction
public:
	CProjectionDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CProjectionDialog)
	enum { IDD = IDD_PROJECTION_DIALOG };
	double	m_bottom;
	double	m_left;
	int		m_bPerspective;
	double	m_right;
	double	m_top;
	double	m_near;
	double	m_far;
	double	m_translate;
	double	m_scale;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProjectionDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CProjectionDialog)
	virtual void OnOK();
	afx_msg void OnKillfocusControls();
	afx_msg void OnReset();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROJECTIONDIALOG_H__EAA9C591_4F2D_46A0_BED0_C0545E53AC2F__INCLUDED_)

#if !defined(AFX_CELLSDIALOG_H__AEC53FEF_1198_4F23_8AB6_E2D446E3479F__INCLUDED_)
#define AFX_CELLSDIALOG_H__AEC53FEF_1198_4F23_8AB6_E2D446E3479F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CellsDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCellsDialog dialog

class CCellsDialog : public CDialog
{
// Construction
public:
	CCellsDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCellsDialog)
	enum { IDD = IDD_CELLS_DIALOG };
	int		m_ncellx;
	int		m_ncelly;
	int		m_ncellz;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCellsDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCellsDialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CELLSDIALOG_H__AEC53FEF_1198_4F23_8AB6_E2D446E3479F__INCLUDED_)

#if !defined(AFX_CHANGETYPEDIALOG_H__7E680D0B_7AB9_424E_BC7D_6B7C1AC8B061__INCLUDED_)
#define AFX_CHANGETYPEDIALOG_H__7E680D0B_7AB9_424E_BC7D_6B7C1AC8B061__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChangeTypeDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChangeTypeDialog dialog

class CChangeTypeDialog : public CDialog
{
// Construction
public:
	CChangeTypeDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CChangeTypeDialog)
	enum { IDD = IDD_DIALOG_CHANGETYPE };
	int		m_nDestType;
	int		m_nSrcType;
	BOOL	m_bSwap;
	int		m_nLocalIndex;
	//}}AFX_DATA

	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChangeTypeDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CChangeTypeDialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHANGETYPEDIALOG_H__7E680D0B_7AB9_424E_BC7D_6B7C1AC8B061__INCLUDED_)

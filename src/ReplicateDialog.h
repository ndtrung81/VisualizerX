#if !defined(AFX_REPLICATEDIALOG_H__EA55C912_A84E_4D48_843C_B81A65B5B149__INCLUDED_)
#define AFX_REPLICATEDIALOG_H__EA55C912_A84E_4D48_843C_B81A65B5B149__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ReplicateDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CReplicateDialog dialog

class CReplicateDialog : public CDialog
{
// Construction
public:
	CReplicateDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CReplicateDialog)
	enum { IDD = IDD_REPLICATE_DIALOG };
	int		m_numCopies;
	double	m_shiftx;
	double	m_shifty;
	double	m_shiftz;
	int		m_nRepX;
	int		m_nRepY;
	int		m_nRepZ;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReplicateDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CReplicateDialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REPLICATEDIALOG_H__EA55C912_A84E_4D48_843C_B81A65B5B149__INCLUDED_)

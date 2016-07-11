#if !defined(AFX_CLUSTERINGDIALOG_H__653DA0EB_C788_4876_A86F_DCDEB3BB3471__INCLUDED_)
#define AFX_CLUSTERINGDIALOG_H__653DA0EB_C788_4876_A86F_DCDEB3BB3471__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ClusteringDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CClusteringDialog dialog

class CClusteringDialog : public CDialog
{
// Construction
public:
	CClusteringDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CClusteringDialog)
	enum { IDD = IDD_CLUSTER_DIALOG };
	BOOL	m_periodicWrapped;
	int		m_nType;
	double	m_cutoff;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClusteringDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CClusteringDialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLUSTERINGDIALOG_H__653DA0EB_C788_4876_A86F_DCDEB3BB3471__INCLUDED_)

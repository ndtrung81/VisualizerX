// DlgToolBar.h: interface for the CDlgToolBar class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DLGTOOLBAR_H__988E721E_E878_11D6_A03E_D61AE823C170__INCLUDED_)
#define AFX_DLGTOOLBAR_H__988E721E_E878_11D6_A03E_D61AE823C170__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDlgToolBar : public CToolBar  
{
public:
	CDlgToolBar();
	virtual ~CDlgToolBar();

protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgToolBar)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg LRESULT OnIdleUpdateCmdUI(WPARAM wParam, LPARAM);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_DLGTOOLBAR_H__988E721E_E878_11D6_A03E_D61AE823C170__INCLUDED_)

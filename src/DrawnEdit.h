#if !defined(AFX_DRAWNEDIT_H__CC1A14A1_EAAE_11D8_AD91_0002444AAF71__INCLUDED_)
#define AFX_DRAWNEDIT_H__CC1A14A1_EAAE_11D8_AD91_0002444AAF71__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DrawnEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDrawnEdit window
#include "GraphCtrl.h"

class CDrawnEdit : public CEdit
{
// Construction
public:
	CDrawnEdit();

// Attributes
public:
	CGraphCtrl m_graphCtrl;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDrawnEdit)
	//}}AFX_VIRTUAL
	
// Implementation
public:
	virtual ~CDrawnEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDrawnEdit)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRAWNEDIT_H__CC1A14A1_EAAE_11D8_AD91_0002444AAF71__INCLUDED_)

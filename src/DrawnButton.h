#if !defined(AFX_DRAWNBUTTON_H__00ACEA03_ED23_11D8_B483_91AC7447CF71__INCLUDED_)
#define AFX_DRAWNBUTTON_H__00ACEA03_ED23_11D8_B483_91AC7447CF71__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DrawnButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDrawnButton window

class CDrawnButton : public CButton
{
// Construction
public:
	CDrawnButton();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDrawnButton)
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetColor(COLORREF nColor);
	COLORREF m_nColor;
	virtual ~CDrawnButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDrawnButton)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRAWNBUTTON_H__00ACEA03_ED23_11D8_B483_91AC7447CF71__INCLUDED_)

#if !defined(AFX_FORMATDIALOG_H__189AF515_5F2C_4AB0_9415_1B6104697537__INCLUDED_)
#define AFX_FORMATDIALOG_H__189AF515_5F2C_4AB0_9415_1B6104697537__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FormatDialog.h : header file
//

#include "DrawnButton.h"
/////////////////////////////////////////////////////////////////////////////
// CFormatDialog dialog

class CFormatDialog : public CDialog
{
// Construction
public:
	CFormatDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFormatDialog)
	enum { IDD = IDD_FORMAT_DIALOG };
	CDrawnButton	m_drawnButton;
	int		m_nLineWidth;
	double	m_largeTickYInterval;
	double	m_largeTickXInterval;
	double	m_smallTickXInterval;
	double	m_smallTickYInterval;
	int		m_nFontSize;
	double	m_maxx;
	double	m_maxy;
	double	m_minx;
	double	m_miny;
	//}}AFX_DATA
	
	COLORREF m_color;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFormatDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFormatDialog)
	afx_msg void OnButtonColor();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FORMATDIALOG_H__189AF515_5F2C_4AB0_9415_1B6104697537__INCLUDED_)

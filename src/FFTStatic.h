#if !defined(AFX_FFTSTATIC_H__3D017155_E074_4554_89A7_A7FC60185653__INCLUDED_)
#define AFX_FFTSTATIC_H__3D017155_E074_4554_89A7_A7FC60185653__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FFTStatic.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFFTStatic window

class CFFTStatic : public CStatic
{
// Construction
public:
	CFFTStatic();

// Attributes
public:

	double** m_diffData;
	int m_nFFTSize;
	int m_nDiffWindowSize;
	double m_zoom;
	
// Operations
public:
	COLORREF ConvertDouble2RGB(double value);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFFTStatic)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFFTStatic();
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CFFTStatic)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FFTSTATIC_H__3D017155_E074_4554_89A7_A7FC60185653__INCLUDED_)

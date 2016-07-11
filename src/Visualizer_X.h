// Visualizer_X.h : main header file for the VISUALIZER_X application
//

#if !defined(AFX_VISUALIZER_X_H__CFFFCBC9_F536_485C_ADCC_E89A6E361A80__INCLUDED_)
#define AFX_VISUALIZER_X_H__CFFFCBC9_F536_485C_ADCC_E89A6E361A80__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include <fstream>
/////////////////////////////////////////////////////////////////////////////
// CVisualizer_XApp:
// See Visualizer_X.cpp for the implementation of this class
//

class CVisualizer_XApp : public CWinApp
{
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CVisualizer_XApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVisualizer_XApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL
	static int m_bFirstTime;
	CString	m_sDataFileName;
	CString	m_sTemplateFileName;

// Implementation
	//{{AFX_MSG(CVisualizer_XApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VISUALIZER_X_H__CFFFCBC9_F536_485C_ADCC_E89A6E361A80__INCLUDED_)

#if !defined(AFX_CURRENTDIALOG_H__D13C3BF8_A827_4D41_BD12_AECCB17FAF8E__INCLUDED_)
#define AFX_CURRENTDIALOG_H__D13C3BF8_A827_4D41_BD12_AECCB17FAF8E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CurrentDialog.h : header file
//

#include "ModelessDialog.h"
/////////////////////////////////////////////////////////////////////////////
// CCurrentDialog dialog

class CCurrentDialog : public CModelessDialog
{
// Construction
public:
	CCurrentDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCurrentDialog)
	enum { IDD = IDD_CURRENT_DIALOG };
	double	m_xLightAngle;
	double	m_xLightPosition;
	double	m_yLightAngle;
	double	m_yLightPosition;
	double	m_zLightAngle;
	double	m_zLightPosition;
	double	m_particleScale;
	double	m_bottom;
	double	m_far;
	double	m_left;
	double	m_near;
	double	m_right;
	double	m_scale;
	double	m_top;
	double	m_translate;
	double	m_xAngle;
	double	m_yAngle;
	double	m_zAngle;
	double	m_lightConstantAttenuation;
	double	m_lightLinearAttenuation;
	double	m_lightQuadraticAttenuation;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCurrentDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCurrentDialog)
	afx_msg void OnUpdateParams();
	afx_msg void OnClose();
	afx_msg void OnReset();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CURRENTDIALOG_H__D13C3BF8_A827_4D41_BD12_AECCB17FAF8E__INCLUDED_)

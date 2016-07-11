#if !defined(AFX_LIGHTDIALOG_H__9A06CF43_89EE_49B4_B4BB_2C03DE08E3A0__INCLUDED_)
#define AFX_LIGHTDIALOG_H__9A06CF43_89EE_49B4_B4BB_2C03DE08E3A0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LightDialog.h : header file
//

#include "ModelessDialog.h"
/////////////////////////////////////////////////////////////////////////////
// CLightDialog dialog

class CLightDialog : public CModelessDialog
{
// Construction
public:
	CLightDialog(CWnd* pParent = NULL);   // standard constructor

	void GetAmbientLight(double* ambient);
	void GetDiffuseLight(double* diffuse);
	void GetSpecularLight(double* specular);
	void GetPositionLight(double* position);

	void SetAmbientLight(double* ambient);
	void SetDiffuseLight(double* diffuse);
	void SetSpecularLight(double* specular);
	void SetPositionLight(double* position);
// Dialog Data
	//{{AFX_DATA(CLightDialog)
	enum { IDD = IDD_LIGHT_DIALOG };
	CSliderCtrl	m_specularRed;
	CSliderCtrl	m_specularGreen;
	CSliderCtrl	m_specularBlue;
	CSliderCtrl	m_diffuseRed;
	CSliderCtrl	m_diffuseGreen;
	CSliderCtrl	m_diffuseBlue;
	CSliderCtrl	m_ambientRed;
	CSliderCtrl	m_ambientGreen;
	CSliderCtrl	m_ambientBlue;
	double	m_pos_y;
	double	m_pos_z;
	BOOL	m_bPointSrc;
	double	m_pos_x;
	//}}AFX_DATA

	double		m_ambientLight[4];
	double		m_diffuseLight[4];
	double		m_specularLight[4];
	double		m_positionLight[4];


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLightDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLightDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void OnReleasedcaptureSlider(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnOK();
	afx_msg void OnChangeLightPos();
	afx_msg void OnCheckPointSrc();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LIGHTDIALOG_H__9A06CF43_89EE_49B4_B4BB_2C03DE08E3A0__INCLUDED_)

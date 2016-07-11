#if !defined(AFX_MATERIALSDIALOG_H__822F27EA_8EA4_485F_868C_077D532444C5__INCLUDED_)
#define AFX_MATERIALSDIALOG_H__822F27EA_8EA4_485F_868C_077D532444C5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MaterialsDialog.h : header file
//

#include "ModelessDialog.h"
/////////////////////////////////////////////////////////////////////////////
// CMaterialsDialog dialog

class CMaterialsDialog : public CModelessDialog
{
// Construction
public:
	CMaterialsDialog(CWnd* pParent = NULL);   // standard constructor

	void GetMaterialAmbient(double* ambient);
	void GetMaterialDiffuse(double* diffuse);
	void GetMaterialSpecular(double* specular);
	void GetMaterialEmission(double* emission);

	void SetMaterialAmbient(double* ambient);
	void SetMaterialDiffuse(double* diffuse);
	void SetMaterialSpecular(double* specular);
	void SetMaterialEmission(double* emission);

// Dialog Data
	//{{AFX_DATA(CMaterialsDialog)
	enum { IDD = IDD_MATERIALS_DIALOG };
	CSliderCtrl	m_emissionAlpha;
	CSliderCtrl	m_specularAlpha;
	CSliderCtrl	m_diffuseAlpha;
	CSliderCtrl	m_ambientAlpha;
	CSliderCtrl	m_emissionRed;
	CSliderCtrl	m_emissionGreen;
	CSliderCtrl	m_emissionBlue;
	CSliderCtrl	m_specularRed;
	CSliderCtrl	m_specularGreen;
	CSliderCtrl	m_specularBlue;
	CSliderCtrl	m_diffuseRed;
	CSliderCtrl	m_diffuseGreen;
	CSliderCtrl	m_diffuseBlue;
	CSliderCtrl	m_ambientRed;
	CSliderCtrl	m_ambientGreen;
	CSliderCtrl	m_ambientBlue;
	double	m_shininess;
	int		m_nMaterialsType;
	int		m_nPresetColor;
	//}}AFX_DATA

	double		m_materialAmbient[4];
	double		m_materialDiffuse[4];
	double		m_materialSpecular[4];
	double		m_materialEmission[4];

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMaterialsDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMaterialsDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnApply();
	virtual void OnOK();
	virtual void OnClose();
	afx_msg void OnReleasedcaptureSlider(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnUpdateMaterialsType();
	afx_msg void OnSelchangeComboMattype();
	afx_msg void OnSelchangeComboColor();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MATERIALSDIALOG_H__822F27EA_8EA4_485F_868C_077D532444C5__INCLUDED_)

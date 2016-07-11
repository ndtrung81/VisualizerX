#if !defined(AFX_SETTINGSDIALOG_H__53DD5706_991C_437F_ACC0_2E96B704726C__INCLUDED_)
#define AFX_SETTINGSDIALOG_H__53DD5706_991C_437F_ACC0_2E96B704726C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SettingsDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSettingsDialog dialog

class CSettingsDialog : public CDialog
{
// Construction
public:
	CSettingsDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSettingsDialog)
	enum { IDD = IDD_SETTINGS_DIALOG };
	double	m_rotatingStep;
	double	m_particleTranslatingStep;
	double	m_particleScalingStep;
	BOOL	m_bXRotate;
	BOOL	m_bYRotate;
	BOOL	m_bZRotate;
	double	m_xModelAngle;
	double	m_yModelAngle;
	double	m_zModelAngle;
	BOOL	m_bUseTwoLightSources;
	int		m_nTranslatingDirection;
	BOOL	m_bBlend;
	BOOL	m_nApplyDrawingCommand;
	int		m_nResolution;
	BOOL	m_bFogging;
	double	m_fogDensity;
	int		m_nFogMode;
	double	m_fog_far;
	double	m_fog_near;
	double	m_outlineWidth;
	BOOL	m_bDrawingOutlines;
	double	m_objectScale;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSettingsDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSettingsDialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETTINGSDIALOG_H__53DD5706_991C_437F_ACC0_2E96B704726C__INCLUDED_)

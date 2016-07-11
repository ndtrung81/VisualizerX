#if !defined(AFX_SPECIALEFFECTSPAGE_H__1AEAED8F_AC43_4EFB_9AA3_F0EF04E19215__INCLUDED_)
#define AFX_SPECIALEFFECTSPAGE_H__1AEAED8F_AC43_4EFB_9AA3_F0EF04E19215__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SpecialEffectsPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSpecialEffectsPage dialog

class CSpecialEffectsPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CSpecialEffectsPage)

// Construction
public:
	CSpecialEffectsPage();
	~CSpecialEffectsPage();

// Dialog Data
	//{{AFX_DATA(CSpecialEffectsPage)
	enum { IDD = IDD_PROPPAGE_SETTINGS_EFFECTS };
	BOOL	m_bUseTwoLightSources;
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
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CSpecialEffectsPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CSpecialEffectsPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPECIALEFFECTSPAGE_H__1AEAED8F_AC43_4EFB_9AA3_F0EF04E19215__INCLUDED_)

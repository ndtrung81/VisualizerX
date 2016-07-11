#if !defined(AFX_PARTICLESPAGE_H__C06C3231_BD7D_4D60_A153_88B219F861CB__INCLUDED_)
#define AFX_PARTICLESPAGE_H__C06C3231_BD7D_4D60_A153_88B219F861CB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ParticlesPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CParticlesPage dialog

class CParticlesPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CParticlesPage)

// Construction
public:
	CParticlesPage();
	~CParticlesPage();

// Dialog Data
	//{{AFX_DATA(CParticlesPage)
	enum { IDD = IDD_PROPPAGE_SETTINGS_PARTICLES };
	double	m_rotatingStep;
	double	m_particleTranslatingStep;
	double	m_particleScalingStep;
	int		m_nTranslatingDirection;
	double	m_maxScale;
	double	m_minScale;
	double	m_objectScale;
	double	m_scaleCoeff;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CParticlesPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CParticlesPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PARTICLESPAGE_H__C06C3231_BD7D_4D60_A153_88B219F861CB__INCLUDED_)

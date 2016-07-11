#if !defined(AFX_DIFFRACTIONDIALOG_H__0D7A9FE5_C2E4_4FA0_831B_5888B7830EDC__INCLUDED_)
#define AFX_DIFFRACTIONDIALOG_H__0D7A9FE5_C2E4_4FA0_831B_5888B7830EDC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DiffractionDialog.h : header file
//

#include "FFTStatic.h"
#include "ResizingDialog.h"

/////////////////////////////////////////////////////////////////////////////
// CDiffractionDialog dialog

class CDiffractionDialog : public CResizingDialog
{
// Construction
public:
	CDiffractionDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDiffractionDialog)
	enum { IDD = IDD_DIFFRACTION_DIALOG };
	CFFTStatic	m_diffPlot;
	double	m_intensity;
	double	m_peakwidth;
	double	m_zoom;
	int		m_nFFTSizeIndex;
	//}}AFX_DATA

	UINT			m_nID;
	CWnd*			m_pParent;

	BOOL Create();
	void ScaleData();
	void UpdateDiffractionExt();
	void MoveControls();

	double** m_diffData;
	int m_nDiffWindowSize;
	int m_nFFTSize;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDiffractionDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL
	
	

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDiffractionDialog)
	afx_msg void OnUpdateDiffraction();
	afx_msg void OnClose();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIFFRACTIONDIALOG_H__0D7A9FE5_C2E4_4FA0_831B_5888B7830EDC__INCLUDED_)

#if !defined(AFX_RDFDIALOG_H__18251482_11D8_4568_AE74_DB10634A509F__INCLUDED_)
#define AFX_RDFDIALOG_H__18251482_11D8_4568_AE74_DB10634A509F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RDFDialog.h : header file
//

#include "Position.h"
#include "ResizingDialog.h"
#include "DrawnEdit.h"
#include "DlgToolBar.h"
#include <vector>
/////////////////////////////////////////////////////////////////////////////
// CRDFDialog dialog

class CRDFDialog : public CResizingDialog
{
// Construction
public:
	CRDFDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRDFDialog)
	enum { IDD = IDD_RDF_DIALOG };
	CScrollBar	m_binsizeCtrl;
	CDrawnEdit	m_edit;
	int		m_nType;
	double	m_binSize;
	double	m_Lmax;
	CString	m_xypos;
	BOOL	m_bDrawCursor;
	int		m_nDimension;
	BOOL	m_bInverse;
	//}}AFX_DATA
	
	const UINT FAR* m_lpaIDToolBar;
	int             m_cIDToolBar;
	UINT            m_nIDBitmap;
	CDlgToolBar		m_toolbar;

	UINT			m_nID;
	CWnd*			m_pParent;

	BOOL m_bRDFCalculated;
	BOOL Create();
	void Compute();
	
	void MoveControls();
	unsigned char* SnapClient(CSize *pSize);
	
	void structure_factor(double* r, double* g, int nBins, 
			double bulkDensity, double* q, double* S);
	
	std::vector<CPosition> m_positionArray;
	double m_Lx, m_Ly, m_Lz;
	double m_init_binSize;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRDFDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:
	
	// Generated message map functions
	//{{AFX_MSG(CRDFDialog)
	afx_msg void OnClose();
	afx_msg void OnCompute();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	afx_msg void OnFormatGridlines();
	afx_msg void OnGraphCopytoclipboard();
	afx_msg void OnFormatSeries();
	afx_msg void OnSelchangeComboType();
	afx_msg void OnCheckCursor();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSelchangeComboDim();
	afx_msg void OnFormatSave();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnCheckSq();
	//}}AFX_MSG
	afx_msg void OnInitMenuPopup(CMenu *pPopupMenu, UINT nIndex,BOOL bSysMenu);
	DECLARE_MESSAGE_MAP()

	
	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RDFDIALOG_H__18251482_11D8_4568_AE74_DB10634A509F__INCLUDED_)

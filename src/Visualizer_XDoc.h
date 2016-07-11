// Visualizer_XDoc.h : interface of the CVisualizer_XDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_VISUALIZER_XDOC_H__9D85109F_DB88_42B9_8743_D519A721E452__INCLUDED_)
#define AFX_VISUALIZER_XDOC_H__9D85109F_DB88_42B9_8743_D519A721E452__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CVisualizer_XDoc : public CDocument
{
protected: // create from serialization only
	CVisualizer_XDoc();
	DECLARE_DYNCREATE(CVisualizer_XDoc)

// Attributes
public:
	double	m_particleScale;
	double	m_particleScalingStep;
	double	m_particleTranslatingStep;
	double	m_objectScale;
	double	m_minScale;
	double	m_maxScale;
	double	m_scaleCoeff;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVisualizer_XDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CVisualizer_XDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CVisualizer_XDoc)
	afx_msg void OnFileWritetopos();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VISUALIZER_XDOC_H__9D85109F_DB88_42B9_8743_D519A721E452__INCLUDED_)

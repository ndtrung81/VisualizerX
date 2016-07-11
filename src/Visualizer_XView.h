// Visualizer_XView.h : interface of the CVisualizer_XView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_VISUALIZER_XVIEW_H__3AABD796_9ACD_40A0_A6AB_4A446BFBEC20__INCLUDED_)
#define AFX_VISUALIZER_XVIEW_H__3AABD796_9ACD_40A0_A6AB_4A446BFBEC20__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GLEnabledView.h"
#include "Particle.h"
#include "MaterialsDialog.h"
#include "LightDialog.h"
#include "ProjectionDialog.h"
#include "CurrentDialog.h"
#include "RDFDialog.h"
#include "BODDialog.h"
#include "DiffractionDialog.h"

#include "DrawingObject.h"

#include <iostream>
#include <vector>

class CVisualizer_XDoc;

struct Region
{
	int type;
	double centerx, centery, centerz;
	double xlo, xhi, ylo, yhi, zlo, zhi;
	double box_scale; // mapping between real box to scaled box
	double radius_inner, radius_outer;
	BOOL m_bOutside;
};

class CVisualizer_XView : public CGLEnabledView
{
protected: // create from serialization only
	CVisualizer_XView();
	DECLARE_DYNCREATE(CVisualizer_XView)

// Attributes
public:
	CVisualizer_XDoc* GetDocument();

	void		CopyToClipboard();

	GLfloat		m_materialAmbientRed[4];
	GLfloat		m_materialAmbientGreen[4];
	GLfloat		m_materialAmbientBlue[4];
	GLfloat		m_materialAmbientGrey[4];
	GLfloat		m_materialAmbientYellow[4];
	GLfloat		m_materialAmbientPurple[4];
	GLfloat		m_materialAmbientPink[4];
	GLfloat		m_materialAmbientViolet[4];
	GLfloat		m_materialAmbientWhite[4];
	GLfloat*	m_materialAmbient[8];

	GLfloat		m_materialDiffuseRed[4];
	GLfloat		m_materialDiffuseGreen[4];
	GLfloat		m_materialDiffuseBlue[4];
	GLfloat		m_materialDiffuseGrey[4];
	GLfloat		m_materialDiffuseYellow[4];
	GLfloat		m_materialDiffusePurple[4];
	GLfloat		m_materialDiffusePink[4];
	GLfloat		m_materialDiffuseViolet[4];
	GLfloat		m_materialDiffuseWhite[4];
	GLfloat*	m_materialDiffuse[8];


	GLfloat		m_materialEmission[4];
	GLfloat		m_materialSpecular[4];
	
	GLfloat		m_ambientLight0[4];
	GLfloat		m_diffuseLight0[4];
	GLfloat		m_specularLight0[4];
	GLfloat		m_positionLight0[4];

	GLfloat		m_ambientLight1[4];
	GLfloat		m_diffuseLight1[4];
	GLfloat		m_specularLight1[4];
	GLfloat		m_positionLight1[4];

	GLfloat	m_lightConstantAttenuation;
	GLfloat	m_lightLinearAttenuation;
	GLfloat	m_lightQuadraticAttenuation;

	GLfloat		m_fogColor[4];
	BOOL		m_bFogging;
	double		m_fogDensity;
	int			m_fogMode;
	double		m_fog_near;
	double		m_fog_far;

	BOOL		m_bUseTwoLightSources;
	BOOL		m_bBlend;
	BOOL		m_bDrawingOutlines;

	double		m_outlineWidth;

	GLfloat		m_background[3];
// Operations
public:
	CMaterialsDialog* m_pMaterialsDialog;
	void	UpdateMaterials();

	CLightDialog* m_pLightDialog;
	void	UpdateLight();

	CProjectionDialog* m_pProjectionDialog;
	void	UpdateProjection();
	void	ResetView();

	CCurrentDialog* m_pCurrentDialog;
	void	UpdateParams(BOOL nFlags=FALSE);
	void	ResetParams();

	CRDFDialog* m_pRDFDialog;
	CBODDialog* m_pBODDialog;
	
	CDiffractionDialog* m_pDiffractionDialog;
	void	UpdateDiffraction();

	BOOL	m_bLightSrc;
	BOOL	m_bPerspective;
	BOOL	m_bStartSelected;
	BOOL	m_bBoundingBox;
	double	m_left, m_right, m_top, m_bottom, m_near, m_far;

	BOOL	m_bIsReadingFromFile;
	BOOL	m_bIsReadingFromStdIn;

	BOOL	m_bPlay;
	int		m_bXRotate, m_bYRotate, m_bZRotate;
	double	m_xModelAngle, m_yModelAngle, m_zModelAngle;

	int		m_nParticleStartIndex, m_nParticleEndIndex;

	int		m_ncellx, m_ncelly, m_ncellz;
	int		m_nDrawCells;

	Region	m_region;

	BOOL	m_bPickingMode;

	// bitmap
	BITMAPFILEHEADER bmfh;
	HBITMAP hDrawingSurface;
	BYTE* pDrawingSurfaceBits;
	BITMAPINFOHEADER BMIH;

	unsigned char* SnapClient(CSize *pSize);

	CString	m_sExportingDirectory;
	BOOL m_bExport2Bmp;
	int m_frameID;
	void CreateBitmapFile(CString sFileName);

	double m_viewportScale;
	void outputEPS(int size, int doSort);

	void PickParticle(CPoint point);
	void GetOGLPos(int x, int y, double& posx, double& posy, double& posz);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVisualizer_XView)
	public:
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	void	BuildQuadrDispList();
	
	int		ReadXYZFile(CString sFileName);
	int		SaveXYZFile(std::ostream& os);
	void	FindBoxLength();
	void	CleanRead(std::istream& is);
	void	Read(std::istream& is);
	void	ApplyTemplate();
	
	
	BOOL	IsVisualized(int index);

	void	ReadScriptFile(CString sFileName);

	std::ifstream m_ifs;

	void	DrawScene(GLenum mode);
	void	DrawParticles(GLenum mode);
	void	DrawBox();
	void	DrawCoordinates();
	void	DrawBOD();
	void	DrawCells();
	void	DrawObjects();
	void	DrawBonds();
	void	DrawOutlines();

	void	OnCreateGL();
	void	OnDrawGL();

	void	SetOutputData(BOOL bOutputData);
	void	SetDataType(int nDataType);

	void	AddObjectsFromFile(std::istream& ifs, int startingIdx, std::vector<int>& localIndices, int nNumObjectsInParticle);
	void	ComputeBOD();

	virtual ~CVisualizer_XView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	GLenum		m_quadricNormals;
	GLenum		m_quadricDwStyle;
	GLenum		m_quadricOrientation;
	CGLQuadric*	m_quadric;
	CGLDispList m_quadricList;
public:
	void PrepareBitmapFile();
	int			m_nParticles;
	int			m_nBeadsInParticle;
	int			m_nBeadsSkipped;
	std::vector<CParticle*> m_particleArray;
	double		m_particleScale;
	double		m_Lx, m_Ly, m_Lz;
	double		m_Lx0, m_Ly0, m_Lz0;
	BOOL		m_nHiddenType[6];
	int			m_nChosenType;

	double		m_shininess;
	double		m_displacement;
	double		m_xangle, m_yangle, m_zangle, m_xLightAngle, m_yLightAngle, m_zLightAngle;
	double		m_targetXangle, m_targetYangle, m_targetZangle;
	double		m_scale, m_targetScale;
	double		m_boxSizex, m_boxSizey, m_boxSizez;
	double		m_boxSizex0, m_boxSizey0, m_boxSizez0;
	double		m_translate;
	CPoint		m_currentPoint;

	std::vector<CDrawingObject*> m_objectArray;
	std::vector<CDrawingObject*> m_bondArray;

	BOOL		m_bFirstTimeApplyingTemplate;
	BOOL		m_bUsingTemplate;
	BOOL		m_bOverrideNumBeads;
	BOOL		m_bReleasePBC;
	CString		m_sFileName;
	BOOL		m_bOutputData;
	int			m_nDataType;
	CString		m_sScriptFileName;

	double		m_rotatingStep;
	int			m_nTranslatingDirection;
	int			m_nResolution;

	BOOL	m_bDrawBOD;
	BOOL	m_bDrawOrigin;
	BOOL	m_bDrawingObjects;
	BOOL	m_bDrawingBonds;

	double	m_cut_in;
	double	m_cut_out;
	int	m_nMaxPoints;
	int m_nBODWindowSize;
	std::vector<CPosition> m_bodData;
	double m_coordinationNumber;

	double** m_diffData;
	int m_nFFTSize;
	void ComputeDiffraction(int nFFTSize, double peakwidth, double intensity, double zoom);

// Generated message map functions
protected:
	//{{AFX_MSG(CVisualizer_XView)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnViewLight();
	afx_msg void OnViewMaterials();
	afx_msg void OnDestroy();
	afx_msg void OnToggleLightsrc();
	afx_msg void OnUpdateToggleLightsrc(CCmdUI* pCmdUI);
	afx_msg void OnEditCopy();
	afx_msg void OnViewProjection();
	afx_msg void OnOrtho();
	afx_msg void OnUpdateOrtho(CCmdUI* pCmdUI);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnViewBackground();
	afx_msg void OnFileUsingTemplate();
	afx_msg void OnFileRead();
	afx_msg void OnViewTypeType1();
	afx_msg void OnViewTypeType2();
	afx_msg void OnViewTypeType3();
	afx_msg void OnViewTypeType4();
	afx_msg void OnViewTypeType5();
	afx_msg void OnViewTypeType6();
	afx_msg void OnUpdateViewTypeType1(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewTypeType2(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewTypeType3(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewTypeType4(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewTypeType5(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewTypeType6(CCmdUI* pCmdUI);
	afx_msg void OnViewTypeAll();
	afx_msg void OnUpdateViewTypeAll(CCmdUI* pCmdUI);
	afx_msg void OnFileWrite();
	afx_msg void OnEditSettings();
	afx_msg void OnXy();
	afx_msg void OnYz();
	afx_msg void OnZx();
	afx_msg void OnViewParticle();
	afx_msg void OnToolsClustering();
	afx_msg void OnTranslatingDirection();
	afx_msg void OnUpdateNegative(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePositive(CCmdUI* pCmdUI);
	afx_msg void OnViewCells();
	afx_msg void OnEditExport();
	afx_msg void OnToolsMovetoorigin();
	afx_msg void OnViewCurrentparameters();
	afx_msg void OnXz();
	afx_msg void OnYx();
	afx_msg void OnZy();
	afx_msg void OnToolsAddobjectsFromfile();
	afx_msg void OnUpdateDrawingobjs(CCmdUI* pCmdUI);
	afx_msg void OnDrawingobjs();
	afx_msg void OnEditExporttopostscript();
	afx_msg void OnFileLoad();
	afx_msg void OnToolsRdf();
	afx_msg void OnUpdateToolsRdf(CCmdUI* pCmdUI);
	afx_msg void OnBod();
	afx_msg void OnToolsBod();
	afx_msg void OnDraworigin();
	afx_msg void OnUpdateDraworigin(CCmdUI* pCmdUI);
	afx_msg void OnUpdateBod(CCmdUI* pCmdUI);
	afx_msg void OnHelpUsersguide();
	afx_msg void OnToolsChangetype();
	afx_msg void OnUpdateToolsChangetype(CCmdUI* pCmdUI);
	afx_msg void OnFileSave();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnPickingMode();
	afx_msg void OnUpdatePickingMode(CCmdUI* pCmdUI);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnFileWritetopos();
	afx_msg void OnToolsDiffraction();
	afx_msg void OnUpdateToolsDiffraction(CCmdUI* pCmdUI);
	afx_msg void OnUpdateToolsBod(CCmdUI* pCmdUI);
	afx_msg void OnToolsReplicate();
	afx_msg void OnFileWritetopov();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Visualizer_XView.cpp
inline CVisualizer_XDoc* CVisualizer_XView::GetDocument()
   { return (CVisualizer_XDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VISUALIZER_XVIEW_H__3AABD796_9ACD_40A0_A6AB_4A446BFBEC20__INCLUDED_)

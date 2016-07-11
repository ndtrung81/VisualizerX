#if !defined(AFX_GLENABLEDVIEW_H__59CED13F_E584_11D1_ACB3_E52ED8AC9002__INCLUDED_)
#define AFX_GLENABLEDVIEW_H__59CED13F_E584_11D1_ACB3_E52ED8AC9002__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
/////////////////////////////////////////////////////////////////////////////
// CGLEnabledView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Global type definitions
	enum InfoField {VENDOR,RENDERER,VERSION,ACCELERATION,EXTENSIONS};
	enum ColorsNumber{INDEXED,THOUSANDS,MILLIONS,MILLIONS_WITH_TRANSPARENCY};
	enum ZAccuracy{NORMAL,ACCURATE};

/////////////////////////////////////////////////////////////////////////////
// CGLEnabledView view

class CGLEnabledView : public CView
{
protected:
	CGLEnabledView();// protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CGLEnabledView)

/* CGLDispList
DESC:
- This is an helper class which let you create "display list objects",
  use these objects to define the key elements in your scene (a disp.
  list is faster than the corresponding GL commands).
- Through the class members functions you have total control on a
  single display list.
- An isolated display list save OGL parameters before execution
  (so it's not affected by preceding transformations or settings).
*/
	class CGLDispList
	{
	friend class CGLEnabledView;
	private:
		BOOL m_bIsolated;
		int m_glListId;
	
	public:
		CGLDispList();  
		~CGLDispList(); 

		int		GetListID();
		void	StartDef(BOOL bImmediateExec=FALSE);	// Enclose a disp.list def.
		void	EndDef();
		void	Draw();								// Execute disp list GL commands 
		void	SetIsolation(BOOL bValue) {m_bIsolated=bValue;}; // Set isolation property
	};

/* CGLTesselator
DESC:
- This is a wrapper class which let you create "tesselator objects",
  use these objects to create concave or self intersecting polygons.
- OGL tessellation objects converts a vertices list describing a convex
  or self-intersecting polygon in one or more GL primitives.Read the
  docs to understand the callbacks mechanism.
- The callbacks have been defined as a simple and direct mapping to
  corresponding GL primitive (no per vertex color or texture information).
- The callbacks have to be global functions.
- A very simple garbage collection list has been implemented to manage new
  vertices create by combine callback.
- Elaboration and drawing occur after EndDef().
*/
	class CGLTesselator
	{
	public:
		CGLTesselator();  
		~CGLTesselator(); 

		// Properties functions
		void	SetFilling(BOOL bFill = TRUE);
		BOOL	GetFilling();
		void	SetWindingRule(GLdouble which);
		GLdouble GetWindingRule();
		
		// Definition functions
		void	StartDef();
		void	AddVertexArray(GLdouble arr[][3],int size);
		void	AddVertex(GLdouble vertData[3]);
		void	ContourSeparator();
		void	EndDef(); // Here occur drawing

	private:
		GLUtesselator* m_tessObj;
	};

/* CGLQuadric
DESC:
- This is a wrapper class which let you create "quadric objects",
  use these objects to create spheres, disks and cylinders.
- All GL commands related to quadrics have been wrapped hiding the
  quadric object parameter.
*/
	class CGLQuadric
	{
	public:
		CGLQuadric(GLenum drwStyle = GLU_FILL, 
				   GLenum normals = GLU_FLAT, 
				   GLenum side = GLU_OUTSIDE,
				   BOOL bGenerateTxtrCoords = FALSE);
		~CGLQuadric();
		
		// Properties functions
		void SetDrawStyle(GLenum style);
		void SetOrientation(GLenum type);
		void SetTextureCoordsGen(BOOL flag);
		void SetNormals(GLenum type);
		// Drawing functions
		void DrawPartialDisk(GLdouble innerRadius,GLdouble outerRadius,int slices,int loops,GLdouble startAngle,GLdouble sweepAngle);
		void DrawDisk(GLdouble innerRadius,GLdouble outerRadius,int slices,int loops);
		void DrawCylinder(GLdouble baseRadius,GLdouble topRadius,GLdouble height,int slices,int stacks);
		void DrawSphere(GLdouble radius,int longitudeSubdiv,int latitudeSubdiv);

	private:
		GLUquadricObj* m_quadrObj;
	};

// Attributes
public:

// Operations
public:
/* Stock Display lists functions
DESC.: these display lists are internally organized in a vector (20 max),
       you have control on definition and redrawing only. 
       use them for background elements which are to be drawn everytime
       all together.
NOTE: between BeginStockDispList and EndStockDispList should be present OpenGL calls only (see documentation for which are allowed and how are them treated)
*/
	void StartStockDListDef();	// Allocates a new stock display list entry and opens a display list definition
	void EndStockListDef();		// Closes a stock display list definition
	void DrawStockDispLists();	// Executes all the stock display lists
	void ClearStockDispLists(); // Deletes all the stock display lists

	// Information retrieval function
	const CString GetInformation(InfoField type);

	// Mouse cursor function
	void SetMouseCursor(HCURSOR mcursor = NULL);

	// Attribute retrieval function
	double GetAspectRatio() { return m_dAspectRatio; }

	// Rendering Context switching
	void BeginGLCommands();		// Used to issue GL commands outside Overridables
	void EndGLCommands();		// i.e: in menu event handlers, button events handler etc.

	// Overridables
	virtual void OnCreateGL();	// Override to set bg color, activate z-buffer, and other global settings
	virtual void OnSizeGL(int cx, int cy); // override to adapt the viewport to the window
	virtual void OnDrawGL();	// Override to issue drawing functions
	virtual void VideoMode(ColorsNumber &c,ZAccuracy &z,BOOL &dbuf); // Override to specify some video mode parameters

	void CopyToClipboard(); 


	// EPS
	virtual void outputEPS(int size, int doSort);
	void print3DcolorVertex(GLint size, GLint* count, GLfloat* buffer);
	void printBuffer(GLint size, GLfloat * buffer);
	GLfloat* spewPrimitiveEPS(FILE* file, GLfloat* loc);
	void spewUnsortedFeedback(FILE * file, GLint size, GLfloat* buffer);
	void spewSortedFeedback(FILE* file, GLint size, GLfloat* buffer);
	void spewWireFrameEPS(FILE * file, int doSort, GLint size, GLfloat * buffer, char *creator);

// Overrides
// NOTE: these have been declared private because they shouldn't be
//		 overridden, use the provided virtual functions instead.
private:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGLEnabledView)
	public:
	virtual void OnDraw(CDC* pDC);      // Overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CGLEnabledView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
// NOTE: these have been declared private because they shouldn't be
//		 overridden, use the provided virtual functions instead.
private:
	//{{AFX_MSG(CGLEnabledView)
		afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
		afx_msg void OnDestroy();
		afx_msg BOOL OnEraseBkgnd(CDC* pDC);
		afx_msg void OnSize(UINT nType, int cx, int cy);
		afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// member variables
protected:
	CDC*			m_pCDC;					// WinGDI Device Context
	HGLRC			m_hRC;					// OpenGL Rendering Context
	HCURSOR			m_hMouseCursor;			// Mouse cursor handle for the view
	CPalette		m_CurrentPalette;		// Palettes
	CPalette*		m_pOldPalette;
	CRect			m_ClientRect;			// Client area size
	double			m_dAspectRatio;			// Aspect ratio
	int				m_DispListVector[20];	// Internal stock display list vector
	BOOL			m_bInsideDispList;		// Disp List definition semaphore
	BOOL			m_bExternGLCall;
	BOOL			m_bExternDispListCall;

	// Initialization helper functions
	unsigned char	ComponentFromIndex(int i, UINT nbits, UINT shift);
	void			CreateRGBPalette();
	BOOL			bSetupPixelFormat();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GLENABLEDVIEW_H__59CED13F_E584_11D1_ACB3_E52ED8AC9002__INCLUDED_)

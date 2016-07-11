// Visualizer_XView.cpp : implementation of the CVisualizer_XView class
//

#include "stdafx.h"
#include "Visualizer_X.h"

#include "Visualizer_XDoc.h"
#include "Visualizer_XView.h"
#include "LightDialog.h"
#include "ProjectionDialog.h"
#include "ParticleTemplateDialog.h"
#include "ViewParticleDialog.h"
#include "SettingsDialog.h"
#include "CellsDialog.h"
#include "ReadDialog.h"
#include "HelpDialog.h"
#include "ChangeTypeDialog.h"
#include "ObjectDialog.h"
#include "ReplicateDialog.h"

#include "ParticlesPage.h"
#include "SpecialEffectsPage.h"
#include "PreprocPage.h"

#include "Sphere.h"
#include "Line.h"
#include "strman.h"

#include "ArrowObject.h"
#include "BondObject.h"

#include "Texture.h"

#include "myfft.h"
#include "matrix.h"

#include <cassert>
#include <fstream>
#include <iostream>
#include <strstream>
#include <string>
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace std;
/////////////////////////////////////////////////////////////////////////////
// CVisualizer_XView

IMPLEMENT_DYNCREATE(CVisualizer_XView, CGLEnabledView)

BEGIN_MESSAGE_MAP(CVisualizer_XView, CGLEnabledView)
	//{{AFX_MSG_MAP(CVisualizer_XView)
	ON_WM_MOUSEMOVE()
	ON_WM_KEYUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_VIEW_LIGHT, OnViewLight)
	ON_COMMAND(ID_VIEW_MATERIALS, OnViewMaterials)
	ON_WM_DESTROY()
	ON_COMMAND(ID_TOGGLE_LIGHTSRC, OnToggleLightsrc)
	ON_UPDATE_COMMAND_UI(ID_TOGGLE_LIGHTSRC, OnUpdateToggleLightsrc)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_VIEW_PROJECTION, OnViewProjection)
	ON_COMMAND(ID_ORTHO, OnOrtho)
	ON_UPDATE_COMMAND_UI(ID_ORTHO, OnUpdateOrtho)
	ON_WM_TIMER()
	ON_COMMAND(ID_VIEW_BACKGROUND, OnViewBackground)
	ON_COMMAND(ID_FILE_USINGTEMPLATE, OnFileUsingTemplate)
	ON_COMMAND(ID_FILE_READ, OnFileRead)
	ON_COMMAND(ID_VIEW_TYPE_TYPE1, OnViewTypeType1)
	ON_COMMAND(ID_VIEW_TYPE_TYPE2, OnViewTypeType2)
	ON_COMMAND(ID_VIEW_TYPE_TYPE3, OnViewTypeType3)
	ON_COMMAND(ID_VIEW_TYPE_TYPE4, OnViewTypeType4)
	ON_COMMAND(ID_VIEW_TYPE_TYPE5, OnViewTypeType5)
	ON_COMMAND(ID_VIEW_TYPE_TYPE6, OnViewTypeType6)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TYPE_TYPE1, OnUpdateViewTypeType1)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TYPE_TYPE2, OnUpdateViewTypeType2)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TYPE_TYPE3, OnUpdateViewTypeType3)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TYPE_TYPE4, OnUpdateViewTypeType4)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TYPE_TYPE5, OnUpdateViewTypeType5)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TYPE_TYPE6, OnUpdateViewTypeType6)
	ON_COMMAND(ID_VIEW_TYPE_ALL, OnViewTypeAll)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TYPE_ALL, OnUpdateViewTypeAll)
	ON_COMMAND(ID_FILE_WRITE, OnFileWrite)
	ON_COMMAND(ID_EDIT_SETTINGS, OnEditSettings)
	ON_COMMAND(IDC_XY, OnXy)
	ON_COMMAND(IDC_YZ, OnYz)
	ON_COMMAND(IDC_ZX, OnZx)
	ON_COMMAND(ID_VIEW_PARTICLE, OnViewParticle)
	ON_COMMAND(ID_TOOLS_CLUSTERING, OnToolsClustering)
	ON_COMMAND(ID_POSITIVE, OnTranslatingDirection)
	ON_UPDATE_COMMAND_UI(ID_NEGATIVE, OnUpdateNegative)
	ON_UPDATE_COMMAND_UI(ID_POSITIVE, OnUpdatePositive)
	ON_COMMAND(ID_VIEW_CELLS, OnViewCells)
	ON_COMMAND(ID_EDIT_EXPORT, OnEditExport)
	ON_COMMAND(ID_TOOLS_MOVETOORIGIN, OnToolsMovetoorigin)
	ON_COMMAND(ID_VIEW_CURRENTPARAMETERS, OnViewCurrentparameters)
	ON_COMMAND(ID_XZ, OnXz)
	ON_COMMAND(ID_YX, OnYx)
	ON_COMMAND(ID_ZY, OnZy)
	ON_COMMAND(ID_TOOLS_ADDOBJECTS_FROMFILE, OnToolsAddobjectsFromfile)
	ON_UPDATE_COMMAND_UI(ID_DRAWINGOBJS, OnUpdateDrawingobjs)
	ON_COMMAND(ID_DRAWINGOBJS, OnDrawingobjs)
	ON_COMMAND(ID_EDIT_EXPORTTOPOSTSCRIPT, OnEditExporttopostscript)
	ON_COMMAND(ID_FILE_LOADSTATE, OnFileLoad)
	ON_COMMAND(ID_TOOLS_RDF, OnToolsRdf)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_RDF, OnUpdateToolsRdf)
	ON_COMMAND(ID_BOD, OnBod)
	ON_COMMAND(ID_TOOLS_BOD, OnToolsBod)
	ON_COMMAND(ID_DRAWORIGIN, OnDraworigin)
	ON_UPDATE_COMMAND_UI(ID_DRAWORIGIN, OnUpdateDraworigin)
	ON_UPDATE_COMMAND_UI(ID_BOD, OnUpdateBod)
	ON_COMMAND(ID_HELP_USERSGUIDE, OnHelpUsersguide)
	ON_COMMAND(ID_TOOLS_CHANGETYPE, OnToolsChangetype)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_CHANGETYPE, OnUpdateToolsChangetype)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_PICKING_MODE, OnPickingMode)
	ON_UPDATE_COMMAND_UI(ID_PICKING_MODE, OnUpdatePickingMode)
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_FILE_WRITETOPOS, OnFileWritetopos)
	ON_COMMAND(ID_TOOLS_DIFFRACTION, OnToolsDiffraction)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_DIFFRACTION, OnUpdateToolsDiffraction)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_BOD, OnUpdateToolsBod)
	ON_COMMAND(ID_TOOLS_REPLICATE, OnToolsReplicate)
	ON_COMMAND(ID_FILE_WRITETOPOV, OnFileWritetopov)
	ON_COMMAND(ID_NEGATIVE, OnTranslatingDirection)
	ON_WM_MOUSEWHEEL()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CGLEnabledView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CGLEnabledView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CGLEnabledView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVisualizer_XView construction/destruction

CVisualizer_XView::CVisualizer_XView()
{
	// TODO: add construction code here
	m_quadricNormals = GLU_SMOOTH;
	m_quadricDwStyle = GLU_FILL;
	m_quadricOrientation = GLU_OUTSIDE;
	m_quadric = new CGLQuadric(m_quadricDwStyle, m_quadricNormals, m_quadricOrientation);
	
	// Material
	m_materialAmbientRed[0] = 0.4f;
	m_materialAmbientRed[1] = 0.05f;
	m_materialAmbientRed[2] = 0.05f;
	m_materialAmbientRed[3] = 1.0f;

	m_materialAmbientGreen[0] = 0.1f;
	m_materialAmbientGreen[1] = 0.35f;
	m_materialAmbientGreen[2] = 0.1f;
	m_materialAmbientGreen[3] = 1.0f;

	m_materialAmbientBlue[0] = 0.1f;
	m_materialAmbientBlue[1] = 0.1f;
	m_materialAmbientBlue[2] = 0.3f;
	m_materialAmbientBlue[3] = 1.0f;

	m_materialAmbientGrey[0] = 0.25f;
	m_materialAmbientGrey[1] = 0.25f;
	m_materialAmbientGrey[2] = 0.25f;
	m_materialAmbientGrey[3] = 1.0f;

	m_materialAmbientYellow[0] = 0.3f;
	m_materialAmbientYellow[1] = 0.1f;
	m_materialAmbientYellow[2] = 0.1f;
	m_materialAmbientYellow[3] = 1.0f;

	m_materialAmbientPurple[0] = 0.3f;
	m_materialAmbientPurple[1] = 0.0f;
	m_materialAmbientPurple[2] = 0.3f;
	m_materialAmbientPurple[3] = 1.0f;
	
	m_materialAmbientPink[0] = 0.4f;
	m_materialAmbientPink[1] = 0.1f;
	m_materialAmbientPink[2] = 0.2f;
	m_materialAmbientPink[3] = 1.0f;

	m_materialAmbientViolet[0] = 0.3f;
	m_materialAmbientViolet[1] = 0.0f;
	m_materialAmbientViolet[2] = 0.3f;
	m_materialAmbientViolet[3] = 1.0f;

	m_materialAmbientWhite[0] = 1.0f;
	m_materialAmbientWhite[1] = 1.0f;
	m_materialAmbientWhite[2] = 1.0f;
	m_materialAmbientWhite[3] = 1.0f;

	m_materialAmbient[0] = m_materialAmbientGrey;
	m_materialAmbient[1] = m_materialAmbientYellow;
	m_materialAmbient[2] = m_materialAmbientBlue;
	m_materialAmbient[3] = m_materialAmbientGreen;
	m_materialAmbient[4] = m_materialAmbientRed;
	m_materialAmbient[5] = m_materialAmbientPurple;
	m_materialAmbient[6] = m_materialAmbientPink;
	m_materialAmbient[7] = m_materialAmbientViolet;

	m_materialDiffuseRed[0] = 0.5f;
	m_materialDiffuseRed[1] = 0.0f;
	m_materialDiffuseRed[2] = 0.0f;
	m_materialDiffuseRed[3] = 0.9f;

	m_materialDiffuseGreen[0] = 0.5f;
	m_materialDiffuseGreen[1] = 0.5f;
	m_materialDiffuseGreen[2] = 0.5f;
	m_materialDiffuseGreen[3] = 1.0f;

	m_materialDiffuseBlue[0] = 0.2f;
	m_materialDiffuseBlue[1] = 0.6f;
	m_materialDiffuseBlue[2] = 0.5f;
	m_materialDiffuseBlue[3] = 1.0f;

	m_materialDiffuseGrey[0] = 0.85f;
	m_materialDiffuseGrey[1] = 0.85f;
	m_materialDiffuseGrey[2] = 0.85f;
	m_materialDiffuseGrey[3] = 1.0f;	//0.3f;

	m_materialDiffuseYellow[0] = 0.6f;
	m_materialDiffuseYellow[1] = 0.5f;
	m_materialDiffuseYellow[2] = 0.0f;
	m_materialDiffuseYellow[3] = 1.0f;

	m_materialDiffusePurple[0] = 0.5f;
	m_materialDiffusePurple[1] = 0.5f;
	m_materialDiffusePurple[2] = 0.5f;
	m_materialDiffusePurple[3] = 1.0f;

	m_materialDiffusePink[0] = 1.0f;
	m_materialDiffusePink[1] = 0.5f;
	m_materialDiffusePink[2] = 0.7f;
	m_materialDiffusePink[3] = 1.0f;

	m_materialDiffuseViolet[0] = 0.7f;
	m_materialDiffuseViolet[1] = 0.7f;
	m_materialDiffuseViolet[2] = 0.7f;
	m_materialDiffuseViolet[3] = 1.0f;

	m_materialDiffuseWhite[0] = 1.0f;
	m_materialDiffuseWhite[1] = 1.0f;
	m_materialDiffuseWhite[2] = 1.0f;
	m_materialDiffuseWhite[3] = 1.0f;

	m_materialDiffuse[0] = m_materialDiffuseGrey;
	m_materialDiffuse[1] = m_materialDiffuseYellow;
	m_materialDiffuse[2] = m_materialDiffuseBlue;
	m_materialDiffuse[3] = m_materialDiffuseGreen;
	m_materialDiffuse[4] = m_materialDiffuseRed;
	m_materialDiffuse[5] = m_materialDiffusePurple;
	m_materialDiffuse[6] = m_materialDiffusePink;
	m_materialDiffuse[7] = m_materialDiffuseViolet;

	m_materialSpecular[0] = 0.9f;
	m_materialSpecular[1] = 0.9f;
	m_materialSpecular[2] = 0.9f;
	m_materialSpecular[3] = 1.0f;

	m_materialEmission[0] = 0.0f;
	m_materialEmission[1] = 0.0f;
	m_materialEmission[2] = 0.0f;
	m_materialEmission[3] = 1.0f;
	
	m_background[0] = 0.0f;
	m_background[1] = 0.0f;
	m_background[2] = 0.0f;

	// Light 0
	m_ambientLight0[0] = 1.0f;
	m_ambientLight0[1] = 1.0f;
	m_ambientLight0[2] = 1.0f;
	m_ambientLight0[3] = 1.0f;

	m_diffuseLight0[0] = 1.0f;
	m_diffuseLight0[1] = 1.0f;
	m_diffuseLight0[2] = 1.0f;
	m_diffuseLight0[3] = 1.0f;

	m_specularLight0[0] = 0.3f;
	m_specularLight0[1] = 0.3f;
	m_specularLight0[2] = 0.3f;
	m_specularLight0[3] = 1.0f;
	
	m_positionLight0[0] = 1.0f;
	m_positionLight0[1] = 1.0f;
	m_positionLight0[2] = 1.0f;
	m_positionLight0[3] = 0.0f;

	// Light 1
	m_ambientLight1[0] = 0.2f;
	m_ambientLight1[1] = 0.2f;
	m_ambientLight1[2] = 0.2f;
	m_ambientLight1[3] = 1.0f;

	m_diffuseLight1[0] = 0.4f;
	m_diffuseLight1[1] = 0.4f;
	m_diffuseLight1[2] = 0.4f;
	m_diffuseLight1[3] = 1.0f;

	m_specularLight1[0] = 1.0f;
	m_specularLight1[1] = 1.0f;
	m_specularLight1[2] = 1.0f;
	m_specularLight1[3] = 1.0f;
	
	m_positionLight1[0] = -5.0f;
	m_positionLight1[1] = 3.0f;
	m_positionLight1[2] = 2.0f;
	m_positionLight1[3] = 0.0f;

	m_lightConstantAttenuation = 1.0;
	m_lightLinearAttenuation = 0.0;
	m_lightQuadraticAttenuation = 0.0;


	m_bUseTwoLightSources = TRUE;
	m_bBlend = TRUE;

	m_shininess		= 90.0f;

	m_xLightAngle	= 25.0f;
	m_yLightAngle	= 37.0f;
	m_zLightAngle	= 10.0f;
	m_particleScale = 1.0f;
	
	m_displacement	= 0.0f;
	m_boxSizex		= 0.75f;
	m_boxSizey		= 0.75f;
	m_boxSizez		= 0.75f;

	m_nParticles	= 0;
	m_nBeadsInParticle	= 1;
	m_pMaterialsDialog = 0x0;
	m_pLightDialog = 0x0;
	m_pProjectionDialog = 0x0;
	m_pCurrentDialog = 0x0;
	m_pRDFDialog = 0x0;
	m_pBODDialog = 0x0;
	m_pDiffractionDialog = 0x0;

	m_bLightSrc	= FALSE;
	m_bStartSelected = FALSE;
	m_bBoundingBox = TRUE;

	m_Lx			= -1.0;
	m_Ly			= -1.0;
	m_Lz			= -1.0;
	m_scale			= 0.182f;
	m_targetScale	= m_scale;
	m_xangle		= 0.0f; //;40; //-97.0f;
	m_yangle		= 0.0f;	//-74; // -3.0f;
	m_zangle		= 0.0f;

	m_targetXangle	= m_xangle;
	m_targetYangle	= m_yangle;
	m_targetZangle	= m_zangle;

	m_xModelAngle	= 0.0;
	m_yModelAngle	= 0.0;
	m_zModelAngle	= 0.0;

	m_translate		= -1.8;
	m_bPerspective = FALSE;
	m_left			= -1.2;	//-0.182;	//-1.2
	m_right			= 1.2;	//0.182;
	m_top			= 1.2;	//0.182;
	m_bottom		= -1.2;	//-0.182;
	m_near			= 1.0;
	m_far			= 3.5;

	for (int i=0; i<6; i++)
		m_nHiddenType[i]	= FALSE;

	m_nParticleStartIndex = -1;
	m_nParticleEndIndex = -1;

	m_bFirstTimeApplyingTemplate = FALSE;
	m_bUsingTemplate = FALSE;
	m_bOverrideNumBeads = FALSE;
	m_bReleasePBC = TRUE;
	m_nBeadsSkipped = 0;
	m_bIsReadingFromFile = FALSE;
	m_bIsReadingFromStdIn = FALSE;
	m_bOutputData = FALSE;
	m_nDataType = __VIS;

	m_bPlay = FALSE;
	m_bXRotate = FALSE;
	m_bYRotate = TRUE;
	m_bZRotate = FALSE;

	m_rotatingStep = 1.0;
	m_nTranslatingDirection = 0;
	m_nResolution = 32;

	m_ncellx = m_ncelly = m_ncellz = 1;
	m_nDrawCells = 0;

	m_bExport2Bmp = TRUE;
	m_frameID = 0;

	m_bFogging = FALSE; //TRUE;
	m_fogColor[0] = m_background[0];
	m_fogColor[1] = m_background[1];
	m_fogColor[2] = m_background[2];
	m_fogColor[3] = 0.5f;
	m_fogDensity = 0.2f;
	m_fogMode = 0;
	m_fog_far = 2.5;
	m_fog_near = 1.5;

	m_bDrawBOD = FALSE;
	m_bDrawOrigin = TRUE;
	m_bDrawingObjects = TRUE;
	m_bDrawingBonds = TRUE;
	m_bPickingMode = FALSE;
	m_bDrawingOutlines = FALSE;
	
	m_outlineWidth = 1.0;

	m_nChosenType = 0;
	m_cut_in = 1.1;
	m_cut_out = 1.3;
	m_nMaxPoints = 1024;
	m_nBODWindowSize = 100;
	m_viewportScale = 1.0;

	m_diffData = 0x0;
	m_nFFTSize = 256;
}

CVisualizer_XView::~CVisualizer_XView()
{
	delete m_quadric;

	if (m_diffData) 
	{
		for (int i=0; i<m_nFFTSize; i++)
			delete [] m_diffData[i];
		delete [] m_diffData;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CVisualizer_XView drawing

/////////////////////////////////////////////////////////////////////////////
// CVisualizer_XView printing

BOOL CVisualizer_XView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CVisualizer_XView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CVisualizer_XView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CVisualizer_XView diagnostics

#ifdef _DEBUG
void CVisualizer_XView::AssertValid() const
{
	CView::AssertValid();
}

void CVisualizer_XView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CVisualizer_XDoc* CVisualizer_XView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CVisualizer_XDoc)));
	return (CVisualizer_XDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CVisualizer_XView message handlers

void CVisualizer_XView::OnCreateGL()
{
	glEnable(GL_DEPTH_TEST);

	// Set background color to black
	glClearColor(0.f, 0.f, 0.f, 1.0f);

	// Set clear Z-Buffer value
	glClearDepth(1.0f);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_LINE_SMOOTH);
	glShadeModel(GL_SMOOTH); 
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	
	// Create and enable a white directional light
	glLightfv(GL_LIGHT0, GL_DIFFUSE, m_diffuseLight0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, m_ambientLight0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, m_specularLight0);
	glLightfv(GL_LIGHT0, GL_POSITION, m_positionLight0);

	glLightfv(GL_LIGHT1, GL_DIFFUSE, m_diffuseLight1);
	glLightfv(GL_LIGHT1, GL_AMBIENT, m_ambientLight1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, m_specularLight1);
	glLightfv(GL_LIGHT1, GL_POSITION, m_positionLight1);

	glMaterialfv(GL_FRONT, GL_SPECULAR, m_materialSpecular);
	glMaterialfv(GL_FRONT, GL_EMISSION, m_materialEmission);
	glMaterialf(GL_FRONT, GL_SHININESS, m_shininess);

	glFogfv(GL_FOG_COLOR, m_fogColor);          /* Define the fog colour */
	glFogf(GL_FOG_DENSITY, m_fogDensity);                /* How dense */
	glFogi(GL_FOG_MODE, GL_EXP2);             /* exponential decay */
	glFogf(GL_FOG_START, m_near);                 /* Where we start fogging */
	glFogf(GL_FOG_END, m_far);                   /* end */
	glHint(GL_FOG_HINT, GL_NICEST);             /* compute per vertex */
	if (m_bFogging == TRUE)
		glEnable(GL_FOG);                           

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	if (m_bUseTwoLightSources)
		glEnable(GL_LIGHT1);
	
	glPolygonMode(GL_FRONT,GL_FILL);
	glPolygonMode(GL_BACK,GL_FILL);

	// Prepare a bunch of line segments (carthesian axes arrows)
	StartStockDListDef();

	EndStockListDef();

	BuildQuadrDispList();
}

void CVisualizer_XView::OnDrawGL()
{
	DrawScene(GL_RENDER);
}

void CVisualizer_XView::BuildQuadrDispList()
{
	int SECTIONS = 8;
	double RADIUS = 1.0f; 
	
	// Construct a quadric object
	CGLQuadric q(m_quadricDwStyle, m_quadricNormals, m_quadricOrientation);
	
	// Open disp list definition
	m_quadricList.StartDef();
	
	q.DrawSphere(RADIUS, SECTIONS, SECTIONS);
		
	// Close disp list definition
	m_quadricList.EndDef();
}

///////////////////////////////////////////////////////////////////////////////////
//
void CVisualizer_XView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (GetCapture() == this)
	{
		CVisualizer_XDoc* pDoc = GetDocument();
		if ((nFlags & MK_SHIFT) == MK_SHIFT)
		{
			m_scale += (GLfloat)(point.y - m_currentPoint.y) * pDoc->m_scaleCoeff;
			if (m_scale > pDoc->m_maxScale)
				m_scale = pDoc->m_maxScale;
			if (m_scale <= pDoc->m_minScale)
				m_scale = pDoc->m_minScale;

			m_left = -1.0 * m_scale;
			m_top = 1.0 * m_scale;
			m_right = 1.0 * m_scale;
			m_bottom = -1.0 * m_scale;

			if (m_pProjectionDialog != NULL)
			{
				m_pProjectionDialog->m_scale = m_scale;
				m_pProjectionDialog->UpdateData(FALSE);
			}

			if (m_pCurrentDialog != NULL) 
				UpdateParams(TRUE);
		}
		else if ((nFlags & MK_CONTROL) == MK_CONTROL)
		{
			m_translate += (GLfloat)(point.y - m_currentPoint.y) * 0.001f;
			
			if (m_pProjectionDialog != NULL)
			{
				m_pProjectionDialog->m_translate = m_translate;
				m_pProjectionDialog->UpdateData(FALSE);
			}

			if (m_pCurrentDialog != NULL) 
				UpdateParams(TRUE);
		}
		else
		{
			if (m_bLightSrc == TRUE)
			{
				if (m_bPickingMode == FALSE)
				{
					m_xLightAngle += (GLfloat)(point.y - m_currentPoint.y) / 3.6f;
					m_yLightAngle += (GLfloat)(point.x - m_currentPoint.x) / 3.6f;
				}
			}
			else
			{
				if (m_bPickingMode == FALSE)
				{
					m_xangle += (GLfloat)(point.y - m_currentPoint.y) / 3.6f;
					m_yangle += (GLfloat)(point.x - m_currentPoint.x) / 3.6f;
				}
			}
			
			if (m_pCurrentDialog != NULL) 
				UpdateParams(TRUE);

		}
		
		Invalidate();

		m_currentPoint = point;
	}


	CGLEnabledView::OnMouseMove(nFlags, point);
}

BOOL CVisualizer_XView::OnMouseWheel(UINT nFlags, short zDelta, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CVisualizer_XDoc* pDoc = GetDocument();
	m_scale += zDelta / WHEEL_DELTA * 0.1; //pDoc->m_scaleCoeff;
	if (m_scale > pDoc->m_maxScale)
		m_scale = pDoc->m_maxScale;
	if (m_scale <= pDoc->m_minScale)
		m_scale = pDoc->m_minScale;

	m_left = -1.0 * m_scale;
	m_top = 1.0 * m_scale;
	m_right = 1.0 * m_scale;
	m_bottom = -1.0 * m_scale;

	if (m_pProjectionDialog != NULL)
	{
		m_pProjectionDialog->m_scale = m_scale;
		m_pProjectionDialog->UpdateData(FALSE);
	}

	if (m_pCurrentDialog != NULL) 
		UpdateParams(TRUE);

	Invalidate();
	return CGLEnabledView::OnMouseWheel(nFlags, zDelta, point);
}

void CVisualizer_XView::GetOGLPos(int x, int y, double& posx, double& posy, double& posz)
{
	GLint viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];
	GLfloat winX, winY, winZ;

	// Specify the target DeviceContext of the subsequent OGL calls
	wglMakeCurrent(m_pCDC->GetSafeHdc(), m_hRC);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearDepth(1.0f);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);

	// This sets the region in the client window to be drawn
	// The origin of the viewport coordinates is located at the left-bottom corner
	CRect rect;
	GetClientRect(&rect);
	int size, centerx, centery, cx, cy;
	cx = rect.Width();
	cy = rect.Height();
	size = (cx > cy) ? cx : cy;
	centerx = cx / 2;
	centery = cy / 2;
			
	glViewport(centerx * m_viewportScale - size  * m_viewportScale / 2, centery * m_viewportScale - size  * m_viewportScale /2, 
		size * m_viewportScale, size * m_viewportScale);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	if (m_bPerspective == TRUE)
		glFrustum(m_left, m_right, m_bottom, m_right, m_near, m_far);
	else
		glOrtho(m_left, m_right, m_bottom, m_right, m_near, m_far);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	
	glPushMatrix();
		glRotatef(m_xLightAngle, 1.0, 0.0, 0.0);
		glRotatef(m_yLightAngle, 0.0, 1.0, 0.0);
		glRotatef(m_zLightAngle, 0.0, 0.0, 1.0);
	glPopMatrix();
			
	// Move the model -1.0 units along the z-axis
	glTranslatef(0.0, 0.0, m_translate);
	glRotatef(m_xangle, 1.0, 0.0, 0.0);
	glRotatef(m_yangle, 0.0, 1.0, 0.0);
	glRotatef(m_zangle, 0.0, 0.0, 1.0);

	glRotatef(m_xModelAngle, 1.0, 0.0, 0.0);
	glRotatef(m_yModelAngle, 0.0, 1.0, 0.0);
	glRotatef(m_zModelAngle, 0.0, 0.0, 1.0);
	
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	glGetIntegerv(GL_VIEWPORT, viewport);

	winX = (float)x;
//	winY = (float)viewport[3] - (float)y;
	winY = (float)viewport[1] + ((float)viewport[3] + (float)cy)/2.0 - (float)y;
	glReadPixels(x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);

	double nearplane, farplane;
	gluUnProject(winX, winY, 0.0, modelview, projection, viewport, &posx, &posy, &nearplane);
	gluUnProject(winX, winY, 1.0, modelview, projection, viewport, &posx, &posy, &farplane);
	gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posx, &posy, &posz);

	double t = nearplane + (posz - nearplane) / (farplane - nearplane);

	double Lx=m_Lx, Ly=m_Ly, Lz=m_Lz;
	if (m_Lx < 0.0) Lx = -m_Lx;
	if (m_Ly < 0.0) Ly = -m_Ly;
	if (m_Lz < 0.0) Lz = -m_Lz;

	posx = posx / m_boxSizex * Lx;
	posy = posy / m_boxSizey * Ly;
	posz = posz / m_boxSizez * Lz;

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	wglMakeCurrent(NULL, NULL);
}

void CVisualizer_XView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_currentPoint = CPoint(0, 0);
	ReleaseCapture();
	
	if (m_bPickingMode == TRUE)
	{
		PickParticle(point);
	
	/*	double posx, posy, posz;
		GetOGLPos(point.x, point.y, posx, posy, posz);
		CString str;
		str.Format("%f %f %f\n", posx, posy, posz);
		MessageBox(str);
	*/
	}

	if (m_pDiffractionDialog)
	{
		m_pDiffractionDialog->UpdateDiffractionExt();
	}
	

	CGLEnabledView::OnLButtonUp(nFlags, point);
}

void CVisualizer_XView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_currentPoint = point;
	SetCapture();

	CGLEnabledView::OnLButtonDown(nFlags, point);
}

void CVisualizer_XView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	CVisualizer_XDoc* pDoc = GetDocument();
	double L[3];

	L[0] = m_boxSizex;
	L[1] = m_boxSizey;
	L[2] = m_boxSizez;

	int i;
	switch (nChar)
	{
	case VK_RIGHT:
		pDoc->m_particleScale += pDoc->m_particleScalingStep;
		if (pDoc->m_particleScale > pDoc->m_maxScale)
			pDoc->m_particleScale = pDoc->m_maxScale;
	
		m_particleScale = pDoc->m_particleScale;
		for (i=0; i<m_particleArray.size(); i++)
			m_particleArray[i]->Zoom(pDoc->m_particleScale);
	

		if (m_pCurrentDialog != NULL) 
			UpdateParams(TRUE);

		pDoc->SetModifiedFlag();
		pDoc->UpdateAllViews(NULL);
		break;
	
	case VK_LEFT:
		pDoc->m_particleScale -= pDoc->m_particleScalingStep;
		if (pDoc->m_particleScale < pDoc->m_minScale)
			pDoc->m_particleScale = pDoc->m_minScale;

		m_particleScale = pDoc->m_particleScale;
		for (i=0; i<m_particleArray.size(); i++)
			m_particleArray[i]->Zoom(pDoc->m_particleScale);
	
		if (m_pCurrentDialog != NULL) 
			UpdateParams(TRUE);

		pDoc->SetModifiedFlag();
		pDoc->UpdateAllViews(NULL);
		break;
	
	case '0':
	case VK_NUMPAD0:
		m_nHiddenType[0] = !m_nHiddenType[0];
		Invalidate();
		break;
	
	case '1':
	case VK_NUMPAD1:
		m_nHiddenType[1] = !m_nHiddenType[1];
		Invalidate();
		break;

	case '2':
	case VK_NUMPAD2:
		m_nHiddenType[2] = !m_nHiddenType[2];
		Invalidate();
		break;

	case '3':
	case VK_NUMPAD3:
		m_nHiddenType[3] = !m_nHiddenType[3];
		Invalidate();
		break;

	case '4':
	case VK_NUMPAD4:
		m_nHiddenType[4] = !m_nHiddenType[4];
		Invalidate();
		break;

	case '5':
	case VK_NUMPAD5:
		m_nHiddenType[5] = !m_nHiddenType[5];
		Invalidate();
		break;

	case 'O':
		m_bPerspective = !m_bPerspective;
		Invalidate();
		break;

	case 'D':
		m_bDrawingObjects = !m_bDrawingObjects;
		Invalidate();
		break;

	case VK_ADD:
		m_scale += 0.02f;
		if (m_scale >= 10.0)
			m_scale = 10.0f;

		if (m_pCurrentDialog != NULL) 
			UpdateParams(TRUE);

		Invalidate();
		break;

	case VK_SUBTRACT:
		m_scale -= 0.02f;
		if (m_scale <= 0.1)
			m_scale = 0.1f;

		if (m_pCurrentDialog != NULL) 
			UpdateParams(TRUE);

		Invalidate();
		break;
	
	case VK_UP:
		m_translate += 0.02f;
		if (m_translate >= 10.0)
			m_translate = 10.0f;

		if (m_pCurrentDialog != NULL) 
			UpdateParams(TRUE);

		Invalidate();
		break;

	case VK_DOWN:
		m_translate -= 0.02f;
		if (m_translate <= -10.0)
			m_translate = -10.0f;

		if (m_pCurrentDialog != NULL) 
			UpdateParams(TRUE);

		Invalidate();
		break;

	case 0x50: // 'P'
		m_bIsReadingFromFile = !m_bIsReadingFromFile;
		m_bIsReadingFromStdIn = !m_bIsReadingFromStdIn;

		Invalidate();
		break;

	case 0x58: // 'X'
		for (i=0; i<m_particleArray.size(); i++)
		{
			if (m_nTranslatingDirection == 0)	// positive direction
				m_particleArray[i]->Translate(m_boxSizex * pDoc->m_particleTranslatingStep, 0.0, 0.0, m_boxSizex, m_boxSizey, m_boxSizez);
			else
				m_particleArray[i]->Translate(-m_boxSizex * pDoc->m_particleTranslatingStep, 0.0, 0.0, m_boxSizex, m_boxSizey, m_boxSizez);

			if (m_bReleasePBC)
				m_particleArray[i]->ReleasePeriodicBoundaryConditions(L);
		}

		Invalidate();
		break;

	case 0x59: // 'Y'
		for (i=0; i<m_particleArray.size(); i++)
		{
			if (m_nTranslatingDirection == 0)	// positive direction
				m_particleArray[i]->Translate(0.0, m_boxSizey * pDoc->m_particleTranslatingStep, 0.0, m_boxSizex, m_boxSizey, m_boxSizez);
			else
				m_particleArray[i]->Translate(0.0, -m_boxSizey * pDoc->m_particleTranslatingStep, 0.0, m_boxSizex, m_boxSizey, m_boxSizez);
			
			if (m_bReleasePBC)
				m_particleArray[i]->ReleasePeriodicBoundaryConditions(L);
		}

		Invalidate();
		break;

	case 0x5A: // 'Z'
		for (i=0; i<m_particleArray.size(); i++)
		{
			if (m_nTranslatingDirection == 0)	// positive direction
				m_particleArray[i]->Translate(0.0, 0.0, m_boxSizez * pDoc->m_particleTranslatingStep, m_boxSizex, m_boxSizey, m_boxSizez);
			else
				m_particleArray[i]->Translate(0.0, 0.0, -m_boxSizez * pDoc->m_particleTranslatingStep, m_boxSizex, m_boxSizey, m_boxSizez);
			
			if (m_bReleasePBC)
				m_particleArray[i]->ReleasePeriodicBoundaryConditions(L);
		}

		Invalidate();
		break;

	case 'B':
		m_bBoundingBox = !m_bBoundingBox;

		Invalidate();
		break;

	case 'R':
		m_bPlay = !m_bPlay;

		if (m_bPlay == TRUE)
			SetTimer(1, 500, NULL);
		else
			KillTimer(1);
	
		break;

	case 'A':
		if (m_nParticleStartIndex > 0)
		{
			m_nParticleStartIndex = -1;
			m_nParticleEndIndex = -1;
			Invalidate();
		}
	
	
		break;
	default: 
		break;
	}

	CGLEnabledView::OnKeyUp(nChar, nRepCnt, nFlags);
}

//////////////////////////////////////////////////////////////////////////////////
//

void CVisualizer_XView::DrawCoordinates()
{
	glLineWidth(2.0f);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, m_materialAmbientRed);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
		glVertex3f(0., 0., 0.);
		glVertex3f(0.7f, 0., 0.);
	glEnd();

	glBegin(GL_LINES);
		glVertex3f(0.7f, 0., 0.);
		glVertex3f(0.55f, 0.05f, 0.f);
	glEnd();

	glBegin(GL_LINES);
		glVertex3f(0.7f, 0.f, 0.f);
		glVertex3f(0.55f, -0.05f, 0.f);
	glEnd();

	glBegin(GL_LINES);
		glVertex3f(0.8f, -0.1f, 0.f);
		glVertex3f(0.9f, -0.25f, 0.f);
	glEnd();

	glBegin(GL_LINES);
		glVertex3f(0.9f, -0.1f, 0.f);
		glVertex3f(0.8f, -0.25f, 0.f);
	glEnd();

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, m_materialAmbientGreen);
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINES);
		glVertex3f(0.f, 0.f, 0.f);
		glVertex3f(0.f, 0.7f, 0.f);
	glEnd();

	glBegin(GL_LINES);
		glVertex3f(0.f, 0.7f, 0.f);
		glVertex3f(0.05f, 0.55f, 0.f);
	glEnd();

	glBegin(GL_LINES);
		glVertex3f(0.f, 0.7f, 0.f);
		glVertex3f(-0.05f, 0.55f, 0.f);
	glEnd();

	glBegin(GL_LINES);
		glVertex3f(0.15f, 0.85f, 0.f);
		glVertex3f(0.2f, 0.9f, 0.f);
	glEnd();

	glBegin(GL_LINES);
		glVertex3f(0.15f, 0.85f, 0.f);
		glVertex3f(0.1f, 0.9f, 0.f);
	glEnd();

	glBegin(GL_LINES);
		glVertex3f(0.15f, 0.85f, 0.f);
		glVertex3f(0.15f, 0.75f, 0.f);
	glEnd();
		

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, m_materialAmbientBlue);
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINES);
		glVertex3f(0.f, 0.f, 0.f);
		glVertex3f(0.f, 0.f, 0.7f);
	glEnd();

	glBegin(GL_LINES);
		glVertex3f(0.f, 0.f, 0.7f);
		glVertex3f(0.f, 0.05f, 0.55f);
	glEnd();

	glBegin(GL_LINES);
		glVertex3f(0.f, 0.f, 0.7f);
		glVertex3f(0.f, -0.05f, 0.55f);
	glEnd();

	glBegin(GL_LINES);
		glVertex3f(0.f, -0.1f, 0.8f);
		glVertex3f(0.f, -0.1f, 0.9f);
	glEnd();

	glBegin(GL_LINES);
		glVertex3f(0.f, -0.1f, 0.8f);
		glVertex3f(0.f, -0.25f, 0.9f);
	glEnd();

	glBegin(GL_LINES);
		glVertex3f(0.f, -0.25f, 0.9f);
		glVertex3f(0.f, -0.25f, 0.8f);
	glEnd();

	glBegin(GL_LINES);
		glVertex3f(0.f, -0.175f, 0.8f);
		glVertex3f(0.f, -0.175f, 0.9f);
	glEnd();
}

void CVisualizer_XView::DrawBOD()
{
	GLUquadricObj* cyl;
	cyl = gluNewQuadric();
	
	int i;
	double x, y, z, radius = 0.8;
	
	GLfloat color[4];
	color[0] = 0.05f;
	color[1] = 0.05f;
	color[2] = 0.05f;
	color[3] = 1.0f;

	glMaterialfv(GL_FRONT, GL_AMBIENT, m_materialAmbientBlue);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, m_materialDiffuseBlue);
	gluSphere(cyl, radius, 64, 64);

	if (m_nParticles <= 1)
		return;

	int nPoints = m_bodData.size();
	if (nPoints == 0)
		return;

	if (m_nChosenType >= 0)
	{
		glMaterialfv(GL_FRONT, GL_AMBIENT, m_materialAmbient[m_nChosenType]);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, m_materialDiffuse[m_nChosenType]);
	}
	else // all chosen
	{
		glMaterialfv(GL_FRONT, GL_AMBIENT, m_materialAmbient[0]);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, m_materialDiffuse[0]);
	}

	for (i=0; i<nPoints; i++)
	{
		x = m_bodData[i][0] * radius;
		y = m_bodData[i][1] * radius;
		z = m_bodData[i][2] * radius;

		glPushMatrix();
		glTranslatef(x, y, z);
		gluSphere(cyl, 0.02, 16, 16);
		glTranslatef(-x, -y, -z);
		glPopMatrix();
	}

	gluDeleteQuadric(cyl);
}

void CVisualizer_XView::DrawOutlines()
{
	float	outlineColor[3]	= {0.0f, 0.0f, 0.0f};		// Color Of The Lines

	glEnable (GL_BLEND);				// Enable Blending
	// Set The Blend Mode		
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glPolygonMode (GL_BACK, GL_LINE);		// Draw Backfacing Polygons As Wireframes
	glLineWidth (m_outlineWidth);			// Set The Line Width
	
	glCullFace(GL_FRONT);				// Don't Draw Any Front-Facing Polygons
	
	glDepthFunc(GL_LEQUAL);			// Change The Depth Mode
	
	glColor3fv(&outlineColor[0]);			// Set The Outline Color

	DrawParticles(GL_RENDER);

	glDepthFunc (GL_LEQUAL);				// Reset The Depth-Testing Mode

	glCullFace (GL_BACK);				// Reset The Face To Be Culled

	glPolygonMode (GL_BACK, GL_FILL);		// Reset Back-Facing Polygon Drawing Mode
	glPolygonMode (GL_FRONT, GL_FILL);		// Reset Back-Facing Polygon Drawing Mode

}

void CVisualizer_XView::DrawBox()
{
//	glLineWidth(2.0f);
	double PI = 4.0 * atan(1.0);
	glColor3f(0.1f, 0.1f, 0.1f);

	double radius = 0.004f;
	double lengthx = m_boxSizex;
	double lengthy = m_boxSizey;
	double lengthz = m_boxSizez;

	GLUquadricObj* cyl;
	cyl = gluNewQuadric();

	// Corners
	glPushMatrix();
	glTranslatef(-m_boxSizex/2.0, -m_boxSizey/2.0, -m_boxSizez/2.0);
	gluSphere(cyl, radius, 16, 16);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(m_boxSizex/2.0, -m_boxSizey/2.0, -m_boxSizez/2.0);
	gluSphere(cyl, radius, 16, 16);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(m_boxSizex/2.0, m_boxSizey/2.0, -m_boxSizez/2.0);
	gluSphere(cyl, radius, 16, 16);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-m_boxSizex/2.0, m_boxSizey/2.0, -m_boxSizez/2.0);
	gluSphere(cyl, radius, 16, 16);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-m_boxSizex/2.0, -m_boxSizey/2.0, m_boxSizez/2.0);
	gluSphere(cyl, radius, 16, 16);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(m_boxSizex/2.0, -m_boxSizey/2.0, m_boxSizez/2.0);
	gluSphere(cyl, radius, 16, 16);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(m_boxSizex/2.0, m_boxSizey/2.0, m_boxSizez/2.0);
	gluSphere(cyl, radius, 16, 16);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-m_boxSizex/2.0, m_boxSizey/2.0, m_boxSizez/2.0);
	gluSphere(cyl, radius, 16, 16);
	glPopMatrix();

	////////
	glPushMatrix();
	glTranslatef(-m_boxSizex/2.0, -m_boxSizey/2.0, -m_boxSizez/2.0);
	gluCylinder(cyl, radius, radius, lengthz, 16, 16);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(m_boxSizex/2.0, -m_boxSizey/2.0, -m_boxSizez/2.0);
	gluCylinder(cyl, radius, radius, lengthz, 16, 16);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(m_boxSizex/2.0, m_boxSizey/2.0, -m_boxSizez/2.0);
	gluCylinder(cyl, radius, radius, lengthz, 16, 16);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-m_boxSizex/2.0, m_boxSizey/2.0, -m_boxSizez/2.0);
	gluCylinder(cyl, radius, radius, lengthz, 16, 16);
	glPopMatrix();

	/////////
	glPushMatrix();
	glTranslatef(-m_boxSizex/2.0, -m_boxSizey/2.0, -m_boxSizez/2.0);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(cyl, radius, radius, lengthy, 16, 16);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(m_boxSizex/2.0, -m_boxSizey/2.0, -m_boxSizez/2.0);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(cyl, radius, radius, lengthy, 16, 16);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(m_boxSizex/2.0, -m_boxSizey/2.0, m_boxSizez/2.0);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(cyl, radius, radius, lengthy, 16, 16);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-m_boxSizex/2.0, -m_boxSizey/2.0, m_boxSizez/2.0);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(cyl, radius, radius, lengthy, 16, 16);
	glPopMatrix();

	
	//////////
	glPushMatrix();
	glTranslatef(-m_boxSizex/2.0, -m_boxSizey/2.0, -m_boxSizez/2.0);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	gluCylinder(cyl, radius, radius, lengthx, 16, 16);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-m_boxSizex/2.0, m_boxSizey/2.0, -m_boxSizez/2.0);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	gluCylinder(cyl, radius, radius, lengthx, 16, 16);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-m_boxSizex/2.0, m_boxSizey/2.0, m_boxSizez/2.0);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	gluCylinder(cyl, radius, radius, lengthx, 16, 16);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-m_boxSizex/2.0, -m_boxSizey/2.0, m_boxSizez/2.0);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	gluCylinder(cyl, radius, radius, lengthx, 16, 16);
	glPopMatrix();

		

	
/*	glBegin(GL_LINE_STRIP);
		glVertex3f(-m_boxSizex/2.0, -m_boxSizey/2.0, -m_boxSizez/2.0);
		glVertex3f(-m_boxSizex/2.0, -m_boxSizey/2.0,  m_boxSizez/2.0);
		glVertex3f( m_boxSizex/2.0, -m_boxSizey/2.0,  m_boxSizez/2.0);
		glVertex3f( m_boxSizex/2.0, -m_boxSizey/2.0, -m_boxSizez/2.0);
		glVertex3f(-m_boxSizex/2.0, -m_boxSizey/2.0, -m_boxSizez/2.0);
	glEnd();

	glBegin(GL_LINE_STRIP);
		glVertex3f( m_boxSizex/2.0, m_boxSizey/2.0,  m_boxSizez/2.0);
		glVertex3f( m_boxSizex/2.0, m_boxSizey/2.0, -m_boxSizez/2.0);
		glVertex3f(-m_boxSizex/2.0, m_boxSizey/2.0, -m_boxSizez/2.0);
		glVertex3f(-m_boxSizex/2.0, m_boxSizey/2.0,  m_boxSizez/2.0);
		glVertex3f( m_boxSizex/2.0, m_boxSizey/2.0,  m_boxSizez/2.0);
	glEnd();

	glBegin(GL_LINES);
		glVertex3f(m_boxSizex/2.0, -m_boxSizey/2.0, m_boxSizez/2.0);
		glVertex3f(m_boxSizex/2.0,  m_boxSizey/2.0, m_boxSizez/2.0);
	glEnd();

	glBegin(GL_LINES);
		glVertex3f(m_boxSizex/2.0, -m_boxSizey/2.0, -m_boxSizez/2.0);
		glVertex3f(m_boxSizex/2.0,  m_boxSizey/2.0, -m_boxSizez/2.0);
	glEnd();

	glBegin(GL_LINES);
		glVertex3f(-m_boxSizex/2.0, -m_boxSizey/2.0, -m_boxSizez/2.0);
		glVertex3f(-m_boxSizex/2.0,  m_boxSizey/2.0, -m_boxSizez/2.0);
	glEnd();

	glBegin(GL_LINES);
		glVertex3f(-m_boxSizex/2.0, -m_boxSizey/2.0, m_boxSizez/2.0);
		glVertex3f(-m_boxSizex/2.0,  m_boxSizey/2.0, m_boxSizez/2.0);
	glEnd();
*/
	
	

	gluDeleteQuadric(cyl);
}

void CVisualizer_XView::DrawCells()
{
	glColor3f(0.1f, 0.1f, 0.1f);

	int i;
	for (i=1; i<m_ncellx; i++)
	{
		glBegin(GL_LINES);
			glVertex3f(m_boxSizex/2.0, -m_boxSizey/2.0, m_boxSizez/2.0);
			glVertex3f(m_boxSizex/2.0,  m_boxSizey/2.0, m_boxSizez/2.0);
		glEnd();
	}

	
}

void CVisualizer_XView::DrawParticles(GLenum mode)
{
	int		i;
	CParticle*	pParticle;

	m_nParticles = m_particleArray.size();
	for (i=0; i<m_nParticles; i++)
	{
		pParticle = m_particleArray[i];
		int bVisualized = IsVisualized(i);
		if (bVisualized == TRUE)
		{
			if (mode == GL_SELECT) 
				glLoadName(i);

			pParticle->Draw(m_materialAmbient, m_materialDiffuse, m_nHiddenType, m_nResolution);
		}
	}

}

void CVisualizer_XView::DrawObjects()
{
	CDrawingObject*	pObject;
	int nObjects = m_objectArray.size();

	for (int i=0; i<nObjects; i++)
	{
		pObject = m_objectArray[i];
		if (IsVisualized(pObject->m_nParticleIndex) == FALSE)
			continue;

		pObject->Draw(m_materialAmbient, m_materialDiffuse, m_nHiddenType, m_nResolution);
	}

}

void CVisualizer_XView::DrawBonds()
{
	CDrawingObject*	pObject;
	int nObjects = m_bondArray.size();

	double radius_outer2 = m_region.radius_outer * m_region.radius_outer;
	double radius_inner2 = m_region.radius_inner * m_region.radius_inner;
	for (int i=0; i<nObjects; i++)
	{
		pObject = m_bondArray[i];
		
		BOOL bInside = FALSE;
		CPosition *pos1 = ((CBondObject*)pObject)->m_position1;
		if (m_region.type == 0)	// box
		{
			if ((*pos1)[0] >= m_region.xlo && (*pos1)[0] <= m_region.xhi
				&& (*pos1)[1] >= m_region.ylo && (*pos1)[1] <= m_region.yhi
				&& (*pos1)[2] >= m_region.zlo && (*pos1)[2] <= m_region.zhi)
			{
				bInside = TRUE;
			}
		}
		else
		{
			double r2 = ((*pos1)[0] - m_region.centerx) * ((*pos1)[0] - m_region.centerx) +
				((*pos1)[1] - m_region.centery) * ((*pos1)[1] - m_region.centery) + 
				((*pos1)[2] - m_region.centerz) * ((*pos1)[2] - m_region.centerz);
			
			if (r2 >= radius_inner2 && r2 <= radius_outer2)
			{
				bInside = TRUE;
			}
		}
		
		if (bInside == TRUE)
			pObject->Draw(m_materialAmbient, m_materialDiffuse, m_nHiddenType, m_nResolution);
	}

}

void CVisualizer_XView::DrawScene(GLenum mode)
{
	int i;
	
	// There are 2 ways to understand the following transformations:
	// 1st: imagine that the global coordinates are transformed by each transformation
	//      and the object is drawn in the transformed global coordinates. Every rotation is
	//		performed with respected to these transformed global x-, y- or z- axes. 
	//		The order of transformation conforms to the commands, 
	//		e.g. rotate everything (including the x, y axes) about the z axis by 20 deg, and then rotates 
	//		everything about the new y axis by 20 deg, next draw the cube. The cube will be located at 
	//		the origin of the new global coordinates.
	// 2nd: imagine that the global coordinates are fixed, but the local coordinates of the object are
	//		transformed with respect to the global ones. Transformation are then in reverse order.
	//		The cube above is first drawn at the origin of the global coordinates. Then it is rotated by 20 deg 
	//		about the global y axis, then rotated by 20 deg about the global z axis. 
	//		The results coming out are the same but the fact that the modelview matrix is affected 
	//		by those transformations. That's why glPushMatrix() and glPopMatrix() are used to recover the original
	//		modelview matrix so that the next drawing can be continued with the original global coordinates.
	CRect rect;
	GetClientRect(&rect);

	CVisualizer_XDoc* pDoc = GetDocument();
	m_particleScale = pDoc->m_particleScale;

	if (m_bUseTwoLightSources == TRUE)
		glEnable(GL_LIGHT1);
	else
		glDisable(GL_LIGHT1);

	if (m_bBlend)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	else
		glDisable(GL_BLEND);

	for (i=0; i<3; i++)
	{
		if (i==2) // draw the bond order diagram
		{	
			if (m_bDrawBOD == FALSE)
				continue;
	
			int cx = rect.Width();
			int cy = rect.Height();

			glViewport(0, (cy - m_nBODWindowSize) * m_viewportScale, m_nBODWindowSize * m_viewportScale, m_nBODWindowSize * m_viewportScale);

			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			// Create a viewing volume: left = -1, right = 1.0, bottom = -1.0, top = 1.0, near = 2.0, far = 7.0;
			// where near and far are positive distances from the "eyes" 
			glOrtho(-1.0, 1.0, -1.0, 1.0, 1.0, 10.0);
		
			glDisable(GL_FOG);
			
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			glPushMatrix();
				glRotatef(m_xLightAngle, 1.0, 0.0, 0.0);
				glRotatef(m_yLightAngle, 0.0, 1.0, 0.0);
				glRotatef(m_zLightAngle, 0.0, 0.0, 1.0);
				glLightfv(GL_LIGHT0, GL_POSITION, m_positionLight0);
			glPopMatrix();

			glPushMatrix();
				// Move the model -2.0 units along the z-axis
				glTranslatef(0.0, 0.0, -2.0);
				glRotatef(m_xangle, 1.0, 0.0, 0.0);
				glRotatef(m_yangle, 0.0, 1.0, 0.0);
				glRotatef(m_zangle, 0.0, 0.0, 1.0);
						
				DrawBOD(); 
			glPopMatrix();
		}
		else if (i==1) // draw the coordinates thereafter
		{
			if (m_bDrawOrigin == FALSE)
				continue;
			int size = 100;		
			
			glViewport(0, 0, size * m_viewportScale, size * m_viewportScale);

			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			// Create a viewing volume: left = -1, right = 1.0, bottom = -1.0, top = 1.0, near = 2.0, far = 7.0;
			// where near and far are positive distances from the "eyes" 
			glOrtho(-1.0, 1.0, -1.0, 1.0, 1.0, 10.0);
		
			glDisable(GL_FOG);

			glPushMatrix();
				// Move the model -2.0 units along the z-axis
				glTranslatef(0.0, 0.0, -2.0);
				glRotatef(m_xangle, 1.0, 0.0, 0.0);
				glRotatef(m_yangle, 0.0, 1.0, 0.0);
				glRotatef(m_zangle, 0.0, 0.0, 1.0);

			//	glRotatef(m_xModelAngle, 1.0, 0.0, 0.0);
			//	glRotatef(m_yModelAngle, 0.0, 1.0, 0.0);
			//	glRotatef(m_zModelAngle, 0.0, 0.0, 1.0);
								
				DrawCoordinates(); 
			glPopMatrix();
		}
		else
		{
			// This sets the region in the client window to be drawn
			// The origin of the viewport coordinates is located at the left-bottom corner
			int size, centerx, centery, cx, cy;
			cx = rect.Width();
			cy = rect.Height();
			size = (cx > cy) ? cx : cy;
			centerx = cx / 2;
			centery = cy / 2;
			
			// enable fog
			if (m_bFogging == TRUE)
			{
				m_fogColor[0] = m_background[0];
				m_fogColor[1] = m_background[1];
				m_fogColor[2] = m_background[2];	
				glFogfv(GL_FOG_COLOR, m_fogColor);          /* Define the fog colour */
				glFogf(GL_FOG_DENSITY, m_fogDensity);
				glFogf(GL_FOG_START, m_fog_near);                 /* Where we start fogging */
				glFogf(GL_FOG_END, m_fog_far);                   /* end */
				if (m_fogMode == 0) 
					glFogf(GL_FOG_MODE, GL_EXP2);
				else if (m_fogMode == 1) 
					glFogf(GL_FOG_MODE, GL_EXP);
				else
					glFogf(GL_FOG_MODE, GL_LINEAR);
				glEnable(GL_FOG);
				

			}
			else
				glDisable(GL_FOG); 
			
			glViewport(centerx * m_viewportScale - size  * m_viewportScale / 2, centery * m_viewportScale - size  * m_viewportScale /2, 
				size * m_viewportScale, size * m_viewportScale);
		//	glViewport(0, 0, size * m_viewportScale, size * m_viewportScale);


			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			// Create a viewing volume: left = -1, right = 1.0, bottom = -1.0, top = 1.0, near = 2.0, far = 7.0;
			// where near and far are positive distances from the "eyes" 
			if (m_bPerspective == TRUE)
				glFrustum(m_left, m_right, m_bottom, m_right, m_near, m_far);
			//	gluPerspective(60.0, 1.0, m_near, m_far);
			else
				glOrtho(m_left, m_right, m_bottom, m_right, m_near, m_far);

			// Now fix the light source position with respect to the eyes
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			glLightfv(GL_LIGHT0, GL_DIFFUSE, m_diffuseLight0);
			glLightfv(GL_LIGHT0, GL_AMBIENT, m_ambientLight0);
			glLightfv(GL_LIGHT0, GL_SPECULAR, m_specularLight0);

			glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, m_lightConstantAttenuation);
			glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, m_lightLinearAttenuation);
			glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, m_lightQuadraticAttenuation);

			glPushMatrix();
				glRotatef(m_xLightAngle, 1.0, 0.0, 0.0);
				glRotatef(m_yLightAngle, 0.0, 1.0, 0.0);
				glRotatef(m_zLightAngle, 0.0, 0.0, 1.0);
				glLightfv(GL_LIGHT0, GL_POSITION, m_positionLight0);
				glLightfv(GL_LIGHT1, GL_POSITION, m_positionLight1);
			glPopMatrix();

			glClearColor(m_background[0], m_background[1], m_background[2], 0.0);
			glClearStencil(0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
			
			glPushMatrix();
				// Move the model -1.0 units along the z-axis
				glTranslatef(0.0, 0.0, m_translate);
				glRotatef(m_xangle, 1.0, 0.0, 0.0);
				glRotatef(m_yangle, 0.0, 1.0, 0.0);
				glRotatef(m_zangle, 0.0, 0.0, 1.0);

				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				glMaterialfv(GL_FRONT, GL_SPECULAR, m_materialSpecular);
				glMaterialfv(GL_FRONT, GL_EMISSION, m_materialEmission);
				glMaterialf(GL_FRONT, GL_SHININESS, m_shininess);
			
			
				glRotatef(m_xModelAngle, 1.0, 0.0, 0.0);
				glRotatef(m_yModelAngle, 0.0, 1.0, 0.0);
				glRotatef(m_zModelAngle, 0.0, 0.0, 1.0);
				
				DrawParticles(mode);
				
				if (m_bDrawingOutlines)
					DrawOutlines();

				if (m_bDrawingObjects == TRUE)
					DrawObjects();
				
				if (m_bDrawingBonds == TRUE)
					DrawBonds();

				if (m_bBoundingBox == TRUE)
				{
					glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, m_materialAmbientGrey);
					DrawBox(); 
				}
	
			glPopMatrix();
		}
	}
}

void CVisualizer_XView::OnFileWrite() 
{
	// TODO: Add your command handler code here
	CFileDialog dlg(FALSE, 
					"txt", 
					NULL, 
					OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
					"XYZ Files (*.xyz)|*.xyz|All Files (*.*)|*.*||",
					this);



	if (dlg.DoModal() == IDOK)
	{
		CString fileName = dlg.GetPathName();
			
		std::ofstream ofs;
		ofs.open(fileName);

		int nNumVisualizedBeads = SaveXYZFile(ofs);
	
		ofs.close();

		ofs.open("visualized-particles.txt");
		ofs << nNumVisualizedBeads << "\n";
		for (int i=0; i<m_nParticles; i++)
		{
			if (IsVisualized(i) == TRUE)
				ofs << i << "\n";
		}

		ofs.close();
	}
	
}

int CVisualizer_XView::SaveXYZFile(std::ostream& os)
{
	int i, j, count=0;
	
	int nNumVisualizedBeads = 0;
	for (i=0; i<m_nParticles; i++)
	{
		if (IsVisualized(i) == TRUE)
		{
			count++;

			CParticle* pParticle = m_particleArray[i];
			for (j=0; j<pParticle->m_positionArray.size(); j++)
			{
				int nType = pParticle->m_positionArray[j].GetType();
				if (m_nHiddenType[nType] == FALSE)
					nNumVisualizedBeads++;
			}
		}
		
	}
	
	os << nNumVisualizedBeads << std::endl;
	os << m_Lx << "\t" << m_Ly << "\t" << m_Lz << std::endl;
	
	for (i=0; i<m_nParticles; i++)
	{
		if (IsVisualized(i) == TRUE)
		{
			m_particleArray[i]->BoxScaling(m_boxSizex, m_boxSizey, m_boxSizez, m_Lx, m_Ly, m_Lz);

			m_particleArray[i]->Write(os, m_nHiddenType);

			m_particleArray[i]->BoxScaling(m_Lx, m_Ly, m_Lz, m_boxSizex, m_boxSizey, m_boxSizez);
		}
	}
	
	return nNumVisualizedBeads;
}

int CVisualizer_XView::ReadXYZFile(CString sFileName)
{
	std::ifstream ifs;
	
	ifs.open(sFileName);
	
	m_sFileName = sFileName;

	int i;
	char s[50];
	double pos[3], L=1.0;

	ifs.getline(s, 50);
	sscanf(s, "%d", &m_nParticles);
	
	ifs.getline(s, 50);
	if (iswdigit(s[0]))
	{
		sscanf(s, "%lf\t%lf\t%lf", &m_Lx, &m_Ly, &m_Lz);

		L = m_Lx;
		if (L < m_Ly)
			L = m_Ly;
		if (L < m_Lz)
			L = m_Lz;
		
		m_boxSizex = 0.75 * m_Lx / L;
		m_boxSizey = 0.75 * m_Ly / L;
		m_boxSizez = 0.75 * m_Lz / L;
	}

	m_particleArray.clear();
	for (i=0; i<m_nParticles; i++)
	{
		ifs >> s >> pos[0] >> pos[1] >> pos[2];
		
		m_particleArray.push_back(new CSphere(s, pos));
	}

	if (m_Lx < 0.0 || m_Ly < 0.0 || m_Lz < 0.0)
	{
		FindBoxLength();

		L = m_Lx;
		if (L < m_Ly)
			L = m_Ly;
		if (L < m_Lz)
			L = m_Lz;
	}

	for (i=0; i<m_nParticles; i++)
		((CSphere*)m_particleArray[i])->BoxScaling(m_Lx, m_Ly, m_Lz, m_boxSizex, m_boxSizey, m_boxSizez);
	
	CVisualizer_XDoc* pDoc = GetDocument();
	pDoc->m_particleScale = 0.5 / m_Lx * m_boxSizex;
	pDoc->m_objectScale = pDoc->m_particleScale;

	m_nParticleStartIndex = 0;
	m_nParticleEndIndex = m_nParticles - 1;

	m_region.centerx = 0.0;
	m_region.centery = 0.0;
	m_region.centerz = 0.0;
	m_region.type = 0; // box
	m_region.xlo = -m_boxSizex/2.0;
	m_region.xhi = m_boxSizex/2.0;
	m_region.ylo = -m_boxSizey/2.0;
	m_region.yhi = m_boxSizey/2.0;
	m_region.zlo = -m_boxSizez/2.0;
	m_region.zhi = m_boxSizez/2.0;
	m_region.box_scale = 0.75 / L;
	m_region.radius_inner = 0.0;
	m_region.radius_outer = L * m_region.box_scale;
	m_region.m_bOutside = FALSE;

	if (m_nParticles < 1000)
		m_nResolution = 32;
	else if (m_nParticles < 5000)
		m_nResolution = 16;
	else if (m_nParticles < 30000)
		m_nResolution = 8;
	else
		m_nResolution = 4;

	ifs.close();

	return 1;
}

void CVisualizer_XView::FindBoxLength()
{
	int i, j;
	double Lx2=0.0, Ly2=0.0, Lz2=0.0;
	CParticle* pParticle;

	for (i=0; i<m_nParticles; i++)
	{
		pParticle = m_particleArray[i];
		for (j=0; j<pParticle->m_positionArray.size(); j++)
		{
			if (Lx2 < fabs(pParticle->m_positionArray[j][0]))
				Lx2 = fabs(pParticle->m_positionArray[j][0]);

			if (Ly2 < fabs(pParticle->m_positionArray[j][1]))
				Ly2 = fabs(pParticle->m_positionArray[j][1]);

			if (Lz2 < fabs(pParticle->m_positionArray[j][2]))
				Lz2 = fabs(pParticle->m_positionArray[j][2]);
		}
	}

	m_Lx = Lx2 * 2.0;
	m_Ly = Ly2 * 2.0;
	m_Lz = Lz2 * 2.0;

	if (m_Lx < 1e-6) m_Lx = 1.0;
	if (m_Ly < 1e-6) m_Ly = 1.0;
	if (m_Lz < 1e-6) m_Lz = 1.0;

	double L = m_Lx;
	if (L < m_Ly)
		L = m_Ly;
	if (L < m_Lz)
		L = m_Lz;

	m_boxSizex = 0.75 * m_Lx / L;
	m_boxSizey = 0.75 * m_Ly / L;
	m_boxSizez = 0.75 * m_Lz / L;
}

void CVisualizer_XView::CleanRead(std::istream& is)
{
	std::string identifier; 
	
	if (m_nDataType == __VIS)
	{
		char s[10];

		is >> s;
		if (strcmp(s, "#") == 0)
		{
			SetTimer(1, 500, NULL);
			return;
		}
		
		m_Lx = atof(s);
		is >> m_Ly >> m_Lz;
		
		double L = m_Lx;
		if (L < m_Ly)
			L = m_Ly;
		if (L < m_Lz)
			L = m_Lz;
		
		m_boxSizex = 0.75 * m_Lx / L;
		m_boxSizey = 0.75 * m_Ly / L;
		m_boxSizez = 0.75 * m_Lz / L;
		
		m_particleArray.clear();
		m_nParticles = 0;
		while (1)
		{
			CParticle* pParticle = new CParticle;
			if (pParticle->ReadDrawingTemplate(is) < 0)
				break;
			
			pParticle->BoxScaling(m_Lx, m_Ly, m_Lz, m_boxSizex, m_boxSizey, m_boxSizez);
			m_particleArray.push_back(pParticle);
			m_nParticles++;
		}	
	
	
	}
	else if (m_nDataType == __XYZ)
	{
		int i;
		double pos[3];
		char s[10];

		is >> m_nParticles;
		is >> m_Lx >> m_Ly >> m_Lz;
		
		double L = m_Lx;
		if (L < m_Ly)
			L = m_Ly;
		if (L < m_Lz)
			L = m_Lz;

		m_boxSizex = m_boxSizex0 = 0.75 * m_Lx / L;
		m_boxSizey = m_boxSizey0 = 0.75 * m_Ly / L;
		m_boxSizez = m_boxSizez0 = 0.75 * m_Lz / L;
		
		m_Lx0 = m_Lx;
		m_Ly0 = m_Ly;
		m_Lz0 = m_Lz;

		m_particleArray.clear();
		for (i=0; i<m_nParticles; i++)
		{
			is >> s >> pos[0] >> pos[1] >> pos[2];
			
			pos[0] = pos[0] / m_Lx * m_boxSizex;
			pos[1] = pos[1] / m_Ly * m_boxSizey;
			pos[2] = pos[2] / m_Lz * m_boxSizez;
			
			m_particleArray.push_back(new CSphere(s, pos));
		}

		m_region.centerx = 0.0;
		m_region.centery = 0.0;
		m_region.centerz = 0.0;
		m_region.type = 0; // box
		m_region.xlo = -m_boxSizex/2.0;
		m_region.xhi = m_boxSizex/2.0;
		m_region.ylo = -m_boxSizey/2.0;
		m_region.yhi = m_boxSizey/2.0;
		m_region.zlo = -m_boxSizez/2.0;
		m_region.zhi = m_boxSizez/2.0;
		m_region.box_scale = 0.75 / L;
		m_region.radius_inner = 0.0;
		m_region.radius_outer = L * m_region.box_scale;
	}


	SetTimer(1, 50, NULL);
	
	Invalidate();
}

void CVisualizer_XView::Read(std::istream& is)
{
	if (m_nDataType == __VIS)
	{
		int i;
		std::string identifier; 
		
		char s[10];

		while (is >> s)
		{
			if (strcmp(s, "#") == 0)
			{
				Invalidate();
				return;		
			}
			
			m_Lx = atof(s);
			is >> m_Ly >> m_Lz;
			
			
			double L = m_Lx;
			if (L < m_Ly)
				L = m_Ly;
			if (L < m_Lz)
				L = m_Lz;
			
			m_boxSizex = 0.75 * m_Lx / L;
			m_boxSizey = 0.75 * m_Ly / L;
			m_boxSizez = 0.75 * m_Lz / L;
			
			for (i=0; i<m_nParticles; i++)
			{
				m_particleArray[i]->Read(is);
				m_particleArray[i]->BoxScaling(m_Lx, m_Ly, m_Lz, m_boxSizex, m_boxSizey, m_boxSizez);
			}
		
		}

		// Only reach here at the end of file or std::cin
		if (m_bIsReadingFromFile)
		{
			m_bIsReadingFromFile = FALSE;
			
			if (m_ifs.is_open())
				m_ifs.close();
		}
				
				
		if (m_bIsReadingFromStdIn)
			m_bIsReadingFromStdIn = FALSE;

		KillTimer(1);
		return;
		
	}
	else if (m_nDataType == __XYZ)
	{
		int i;
		double pos[3];
		char s[10];
		std::string identifier;

		while (is >> s)
		{
			if (m_bUsingTemplate == FALSE)
			{
				m_nParticles = atoi(s);
				is >> m_Lx >> m_Ly >> m_Lz;
				
				double L = m_Lx;
				if (L < m_Ly)
					L = m_Ly;
				if (L < m_Lz)
					L = m_Lz;
				
				m_boxSizex = m_boxSizex0 * m_Lx / m_Lx0; //0.75 * m_Lx / L;
				m_boxSizey = m_boxSizey0 * m_Ly / m_Ly0; //0.75 * m_Ly / L;
				m_boxSizez = m_boxSizez0 * m_Lz / m_Lz0; //0.75 * m_Lz / L;
				
				for (i=0; i<m_nParticles; i++)
				{
					is >> s >> pos[0] >> pos[1] >> pos[2];
					
					pos[0] = pos[0] / m_Lx * m_boxSizex;
					pos[1] = pos[1] / m_Ly * m_boxSizey;
					pos[2] = pos[2] / m_Lz * m_boxSizez;
					
					((CSphere*)m_particleArray[i])->SetCenter(pos[0], pos[1], pos[2]);
				}
			}
			else
			{
				int local_index, particle_index, nBeads;
				nBeads = atoi(s);
				is >> m_Lx >> m_Ly >> m_Lz;
				
				double L = m_Lx;
				if (L < m_Ly)
					L = m_Ly;
				if (L < m_Lz)
					L = m_Lz;
				
				m_boxSizex = m_boxSizex0 * m_Lx / m_Lx0; //0.75 * m_Lx / L;
				m_boxSizey = m_boxSizey0 * m_Ly / m_Ly0; //0.75 * m_Ly / L;
				m_boxSizez = m_boxSizez0 * m_Lz / m_Lz0; //0.75 * m_Lz / L;
				

				for (i=0; i<nBeads; i++)
				{
					is >> s >> pos[0] >> pos[1] >> pos[2];
					
					pos[0] = pos[0] / m_Lx * m_boxSizex;
					pos[1] = pos[1] / m_Ly * m_boxSizey;
					pos[2] = pos[2] / m_Lz * m_boxSizez;
					
					particle_index = i / m_nBeadsInParticle;
					local_index = i % m_nBeadsInParticle;
					m_particleArray[particle_index]->SetSite(local_index, pos);
				}

				ApplyTemplate();
			}

			Invalidate();
			return;
		}
		
		// Only reach here at the end of file or std::cin
		if (m_bIsReadingFromFile)
		{
			m_bIsReadingFromFile = FALSE;
			
			if (m_ifs.is_open())
				m_ifs.close();
		}
				
		if (m_bIsReadingFromStdIn)
			m_bIsReadingFromStdIn = FALSE;

		KillTimer(1);
		return;
	}

	
}

void CVisualizer_XView::SetOutputData(BOOL bOutputData)
{
	m_bOutputData = bOutputData;
}

void CVisualizer_XView::SetDataType(int nDataType)
{
	m_nDataType = nDataType;
}


/////////////////////////////////////////////////////////////////////////////
//

void CVisualizer_XView::OnViewLight() 
{
	// TODO: Add your command handler code here
	if (m_pLightDialog == NULL)
	{
		m_pLightDialog = new CLightDialog(this);

		m_pLightDialog->m_ambientLight[0] = m_ambientLight0[0];
		m_pLightDialog->m_ambientLight[1] = m_ambientLight0[1];
		m_pLightDialog->m_ambientLight[2] = m_ambientLight0[2];
		
		m_pLightDialog->m_diffuseLight[0] = m_diffuseLight0[0];
		m_pLightDialog->m_diffuseLight[1] = m_diffuseLight0[1];
		m_pLightDialog->m_diffuseLight[2] = m_diffuseLight0[2];
		
		m_pLightDialog->m_specularLight[0] = m_specularLight0[0];
		m_pLightDialog->m_specularLight[1] = m_specularLight0[1];
		m_pLightDialog->m_specularLight[2] = m_specularLight0[2];
		
		m_pLightDialog->m_positionLight[0] = m_positionLight0[0];
		m_pLightDialog->m_positionLight[1] = m_positionLight0[1];
		m_pLightDialog->m_positionLight[2] = m_positionLight0[2];
		m_pLightDialog->m_positionLight[3] = m_positionLight0[3];

		if (m_positionLight0[3] == 1.0)
			m_pLightDialog->m_bPointSrc = TRUE;
		else
			m_pLightDialog->m_bPointSrc = FALSE;

		m_pLightDialog->Create();
	}
}

void CVisualizer_XView::OnViewMaterials() 
{
	// TODO: Add your command handler code here
	if (m_pMaterialsDialog == NULL)
	{
		m_pMaterialsDialog = new CMaterialsDialog(this);

		m_pMaterialsDialog->m_nMaterialsType = 0;
		
		m_pMaterialsDialog->m_materialAmbient[0] = m_materialAmbient[0][0];
		m_pMaterialsDialog->m_materialAmbient[1] = m_materialAmbient[0][1];
		m_pMaterialsDialog->m_materialAmbient[2] = m_materialAmbient[0][2];
		m_pMaterialsDialog->m_materialAmbient[3] = m_materialAmbient[0][3];
		
		m_pMaterialsDialog->m_materialDiffuse[0] = m_materialDiffuse[0][0];
		m_pMaterialsDialog->m_materialDiffuse[1] = m_materialDiffuse[0][1];
		m_pMaterialsDialog->m_materialDiffuse[2] = m_materialDiffuse[0][2];
		m_pMaterialsDialog->m_materialDiffuse[3] = m_materialDiffuse[0][3];
		
		m_pMaterialsDialog->m_materialSpecular[0] = m_materialSpecular[0];
		m_pMaterialsDialog->m_materialSpecular[1] = m_materialSpecular[1];
		m_pMaterialsDialog->m_materialSpecular[2] = m_materialSpecular[2];
		m_pMaterialsDialog->m_materialSpecular[3] = m_materialSpecular[3];
		
		m_pMaterialsDialog->m_materialEmission[0] = m_materialEmission[0];
		m_pMaterialsDialog->m_materialEmission[1] = m_materialEmission[1];
		m_pMaterialsDialog->m_materialEmission[2] = m_materialEmission[2];
		m_pMaterialsDialog->m_materialEmission[3] = m_materialEmission[3];

		m_pMaterialsDialog->m_shininess = m_shininess;

		m_pMaterialsDialog->Create();
	}
}

void CVisualizer_XView::UpdateMaterials()
{
	int nMaterialsType = m_pMaterialsDialog->m_nMaterialsType;
	
	m_materialAmbient[nMaterialsType][0] = m_pMaterialsDialog->m_materialAmbient[0];
	m_materialAmbient[nMaterialsType][1] = m_pMaterialsDialog->m_materialAmbient[1];
	m_materialAmbient[nMaterialsType][2] = m_pMaterialsDialog->m_materialAmbient[2];
	m_materialAmbient[nMaterialsType][3] = m_pMaterialsDialog->m_materialAmbient[3];
	
	m_materialDiffuse[nMaterialsType][0] = m_pMaterialsDialog->m_materialDiffuse[0];
	m_materialDiffuse[nMaterialsType][1] = m_pMaterialsDialog->m_materialDiffuse[1];
	m_materialDiffuse[nMaterialsType][2] = m_pMaterialsDialog->m_materialDiffuse[2];
	m_materialDiffuse[nMaterialsType][3] = m_pMaterialsDialog->m_materialDiffuse[3];
	
	m_materialSpecular[0] = m_pMaterialsDialog->m_materialSpecular[0];
	m_materialSpecular[1] = m_pMaterialsDialog->m_materialSpecular[1];
	m_materialSpecular[2] = m_pMaterialsDialog->m_materialSpecular[2];
	m_materialSpecular[3] = m_pMaterialsDialog->m_materialSpecular[3];
	
	m_materialEmission[0] = m_pMaterialsDialog->m_materialEmission[0];
	m_materialEmission[1] = m_pMaterialsDialog->m_materialEmission[1];
	m_materialEmission[2] = m_pMaterialsDialog->m_materialEmission[2];		
	m_materialEmission[3] = m_pMaterialsDialog->m_materialEmission[3];		
	
	m_shininess = m_pMaterialsDialog->m_shininess;
	
	Invalidate();
}

void CVisualizer_XView::UpdateLight()
{
	m_ambientLight0[0] = m_pLightDialog->m_ambientLight[0];
	m_ambientLight0[1] = m_pLightDialog->m_ambientLight[1];
	m_ambientLight0[2] = m_pLightDialog->m_ambientLight[2];
	
	m_diffuseLight0[0] = m_pLightDialog->m_diffuseLight[0];
	m_diffuseLight0[1] = m_pLightDialog->m_diffuseLight[1];
	m_diffuseLight0[2] = m_pLightDialog->m_diffuseLight[2];
	
	m_specularLight0[0] = m_pLightDialog->m_specularLight[0];
	m_specularLight0[1] = m_pLightDialog->m_specularLight[1];
	m_specularLight0[2] = m_pLightDialog->m_specularLight[2];
	
	m_positionLight0[0] = m_pLightDialog->m_positionLight[0];
	m_positionLight0[1] = m_pLightDialog->m_positionLight[1];
	m_positionLight0[2] = m_pLightDialog->m_positionLight[2];
	m_positionLight0[3] = m_pLightDialog->m_positionLight[3];

	Invalidate();
}

void CVisualizer_XView::OnViewCurrentparameters() 
{
	// TODO: Add your command handler code here
	if (m_pCurrentDialog == NULL)
	{
		m_pCurrentDialog = new CCurrentDialog(this);

		m_pCurrentDialog->m_particleScale = m_particleScale;

		m_pCurrentDialog->m_left	= m_left;
		m_pCurrentDialog->m_right	= m_right;
		m_pCurrentDialog->m_top		= m_top;
		m_pCurrentDialog->m_bottom	= m_bottom;
		m_pCurrentDialog->m_near	= m_near;
		m_pCurrentDialog->m_far		= m_far;

		m_pCurrentDialog->m_translate	= m_translate;
		m_pCurrentDialog->m_scale		= m_scale;

		m_pCurrentDialog->m_xAngle = m_xangle;
		m_pCurrentDialog->m_yAngle = m_yangle;
		m_pCurrentDialog->m_zAngle = m_zangle;

		m_pCurrentDialog->m_xLightAngle = m_xLightAngle;
		m_pCurrentDialog->m_yLightAngle = m_yLightAngle;
		m_pCurrentDialog->m_zLightAngle = m_zLightAngle;

		m_pCurrentDialog->m_xLightPosition = m_positionLight0[0];
		m_pCurrentDialog->m_yLightPosition = m_positionLight0[1];
		m_pCurrentDialog->m_zLightPosition = m_positionLight0[2];

		m_pCurrentDialog->m_lightConstantAttenuation = m_lightConstantAttenuation;
		m_pCurrentDialog->m_lightLinearAttenuation = m_lightLinearAttenuation;
		m_pCurrentDialog->m_lightQuadraticAttenuation = m_lightQuadraticAttenuation;

		m_pCurrentDialog->Create();
	}
}

void CVisualizer_XView::UpdateParams(BOOL nFlags)
{
	CVisualizer_XDoc* pDoc = GetDocument();

	if (nFlags == FALSE)
	{
		pDoc->m_particleScale = m_pCurrentDialog->m_particleScale;
		for (int i=0; i<m_particleArray.size(); i++)
			m_particleArray[i]->Zoom(pDoc->m_particleScale);

		m_left	= m_pCurrentDialog->m_left;
		m_right	= m_pCurrentDialog->m_right;
		m_top	= m_pCurrentDialog->m_top;
		m_bottom	= m_pCurrentDialog->m_bottom;
		m_near	= m_pCurrentDialog->m_near;
		m_far	= m_pCurrentDialog->m_far;
	
		m_translate	= m_pCurrentDialog->m_translate;
		m_scale		= m_pCurrentDialog->m_scale;
	
		m_xangle = m_pCurrentDialog->m_xAngle;
		m_yangle = m_pCurrentDialog->m_yAngle;
		m_zangle = m_pCurrentDialog->m_zAngle;
	
		m_xLightAngle = m_pCurrentDialog->m_xLightAngle;
		m_yLightAngle = m_pCurrentDialog->m_yLightAngle;
		m_zLightAngle = m_pCurrentDialog->m_zLightAngle;
	
		m_positionLight0[0] = m_pCurrentDialog->m_xLightPosition;
		m_positionLight0[1] = m_pCurrentDialog->m_yLightPosition;
		m_positionLight0[2] = m_pCurrentDialog->m_zLightPosition;
	
		m_lightConstantAttenuation = m_pCurrentDialog->m_lightConstantAttenuation;
		m_lightLinearAttenuation = m_pCurrentDialog->m_lightLinearAttenuation;
		m_lightQuadraticAttenuation = m_pCurrentDialog->m_lightQuadraticAttenuation;

		Invalidate();
	}
	else // update from changes
	{
		m_pCurrentDialog->m_particleScale = pDoc->m_particleScale;

		m_pCurrentDialog->m_left	= m_left;
		m_pCurrentDialog->m_right	= m_right;
		m_pCurrentDialog->m_top		= m_top;
		m_pCurrentDialog->m_bottom	= m_bottom;
		m_pCurrentDialog->m_near	= m_near;
		m_pCurrentDialog->m_far		= m_far;

		m_pCurrentDialog->m_translate	= m_translate;
		m_pCurrentDialog->m_scale		= m_scale;

		m_pCurrentDialog->m_xAngle = m_xangle;
		m_pCurrentDialog->m_yAngle = m_yangle;
		m_pCurrentDialog->m_zAngle = m_zangle;

		m_pCurrentDialog->m_xLightAngle = m_xLightAngle;
		m_pCurrentDialog->m_yLightAngle = m_yLightAngle;
		m_pCurrentDialog->m_zLightAngle = m_zLightAngle;

		m_pCurrentDialog->m_xLightPosition = m_positionLight0[0];
		m_pCurrentDialog->m_yLightPosition = m_positionLight0[1];
		m_pCurrentDialog->m_zLightPosition = m_positionLight0[2];

		m_pCurrentDialog->UpdateData(FALSE);

	}
}

void CVisualizer_XView::ResetParams()
{
	CVisualizer_XDoc* pDoc = GetDocument();

	m_left	= -1.0;
	m_right	= 1.0;
	m_top	= 1.0; 
	m_bottom	=  -1.0;
	m_near	= 1.0;
	m_far	= 10.0;
	
	m_translate	= -1.8;
	m_scale		= 1.0;
	
	m_xangle = 15.0;
	m_yangle = -77.0;
	m_zangle = 0.0;
	
	m_xLightAngle = 0.0;
	m_yLightAngle = 0.0;
	m_zLightAngle = 0.0;
	
	m_positionLight0[0] = 1.0;
	m_positionLight0[1] = 1.0;
	m_positionLight0[2] = 1.0;

	pDoc->m_particleScale = 0.72;

	m_pCurrentDialog->m_particleScale = pDoc->m_particleScale;
	
	m_pCurrentDialog->m_left	= m_left;
	m_pCurrentDialog->m_right	= m_right;
	m_pCurrentDialog->m_top		= m_top;
	m_pCurrentDialog->m_bottom	= m_bottom;
	m_pCurrentDialog->m_near	= m_near;
	m_pCurrentDialog->m_far		= m_far;
	
	m_pCurrentDialog->m_translate	= m_translate;
	m_pCurrentDialog->m_scale		= m_scale;
	
	m_pCurrentDialog->m_xAngle = m_xangle;
	m_pCurrentDialog->m_yAngle = m_yangle;
	m_pCurrentDialog->m_zAngle = m_zangle;
	
	m_pCurrentDialog->m_xLightAngle = m_xLightAngle;
	m_pCurrentDialog->m_yLightAngle = m_yLightAngle;
	m_pCurrentDialog->m_zLightAngle = m_zLightAngle;
	
	m_pCurrentDialog->m_xLightPosition = m_positionLight0[0];
	m_pCurrentDialog->m_yLightPosition = m_positionLight0[1];
	m_pCurrentDialog->m_zLightPosition = m_positionLight0[2];
	
	m_pCurrentDialog->UpdateData(FALSE);

	Invalidate();
}


void CVisualizer_XView::OnViewProjection() 
{
	// TODO: Add your command handler code here
	if (m_pProjectionDialog == NULL)
	{
		m_pProjectionDialog = new CProjectionDialog(this);

		m_pProjectionDialog->m_bPerspective = m_bPerspective;
		m_pProjectionDialog->m_left	= m_left;
		m_pProjectionDialog->m_right = m_right;
		m_pProjectionDialog->m_top	= m_top;
		m_pProjectionDialog->m_bottom	= m_bottom;
		m_pProjectionDialog->m_near	= m_near;
		m_pProjectionDialog->m_far	= m_far;
		m_pProjectionDialog->m_translate = m_translate;
		m_pProjectionDialog->m_scale = m_scale;
		
		m_pProjectionDialog->Create();
	}
}

void CVisualizer_XView::UpdateProjection()
{
	m_bPerspective = m_pProjectionDialog->m_bPerspective;
	m_left	= 	m_pProjectionDialog->m_left;
	m_right	= 	m_pProjectionDialog->m_right;
	m_top	= 	m_pProjectionDialog->m_top;
	m_bottom =	m_pProjectionDialog->m_bottom;
	m_near	= 	m_pProjectionDialog->m_near;
	m_far	= 	m_pProjectionDialog->m_far;
	m_translate = m_pProjectionDialog->m_translate;
	m_scale = m_pProjectionDialog->m_scale;

	Invalidate();
}

void CVisualizer_XView::OnDestroy() 
{
	// TODO: Add your message handler code here
	if (m_pLightDialog != NULL)
		m_pLightDialog->DestroyWindow();

	if (m_pMaterialsDialog != NULL)
		m_pMaterialsDialog->DestroyWindow();

	if (m_pProjectionDialog != NULL)
		m_pProjectionDialog->DestroyWindow();

	if (m_pCurrentDialog != NULL)
		m_pCurrentDialog->DestroyWindow();

	if (m_pRDFDialog != NULL)
		m_pRDFDialog->DestroyWindow();

	if (m_pBODDialog != NULL)
		m_pBODDialog->DestroyWindow();

	if (m_pDiffractionDialog != NULL)
		m_pDiffractionDialog->DestroyWindow();

	if (m_bPlay == TRUE)
		KillTimer(1);

	CView::OnDestroy();
}

void CVisualizer_XView::OnToggleLightsrc() 
{
	// TODO: Add your command handler code here
	m_bLightSrc = !m_bLightSrc;
}

void CVisualizer_XView::OnUpdateToggleLightsrc(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_bLightSrc == TRUE);
}

void CVisualizer_XView::CopyToClipboard() 
{
/*	CMetaFileDC* pMetaDC = new CMetaFileDC();
	pMetaDC->CreateEnhanced(GetDC(), NULL, NULL, "whatever");
	pMetaDC->m_hAttribDC = GetDC()->GetSafeHdc();
	//draw meta file

	CDC* pDC = GetDC();
	CRect rect;
	GetClientRect(&rect);
	pMetaDC->BitBlt(rect.left, rect.top, rect.Width() - 200, rect.Height(), pDC, 100, 0, SRCCOPY); 
	
	
	//close meta file dc and prepare for clipboard;
	HENHMETAFILE hMF = pMetaDC->CloseEnhanced();
	
	
	//copy to clipboard
	OpenClipboard();
	EmptyClipboard();
	::SetClipboardData(CF_ENHMETAFILE, hMF);
	CloseClipboard();
	

//	DeleteMetaFile(hMF);
	delete pMetaDC;	
*/

	// Export to DIB image
	BeginWaitCursor();
	
	// Get client geometry
	CRect rect;
	GetClientRect(&rect);
	CSize size(rect.Width(),rect.Height());
	TRACE("  client zone : (%d;%d)\n",size.cx,size.cy);
	// Lines have to be 32 bytes aligned, suppose 24 bits per pixel
	// I just cropped it
//	size.cx -= size.cx % 4;

	CDC *pDC = GetDC();
	int bitsPerPixel = pDC->GetDeviceCaps(BITSPIXEL);
	switch(bitsPerPixel){
		case 8:
		case 24: size.cx -= size.cx % 4; break;
		case 16: size.cx -= size.cx % 2; break;
		case 32:
		default: break;
	}

	TRACE("  final client zone : (%d;%d)\n",size.cx,size.cy);

	const int bytesPerPixel = 4;

	// Need to create a render context here, otherwise nothing is drawn..
	HGLRC hRC = wglCreateContext(pDC->m_hDC);

	// and make hRC current
	wglMakeCurrent(pDC->m_hDC, hRC);

	// Alloc pixel bytes
	int NbBytes = bytesPerPixel * size.cx * size.cy;
	unsigned char *pPixelData = new unsigned char[NbBytes];
	
	// Copy from OpenGL
	::glReadPixels(0,0,size.cx,size.cy,GL_RGBA,GL_UNSIGNED_BYTE,pPixelData);
	
	// Fill header
	BITMAPINFOHEADER header;
	header.biWidth = size.cx;
	header.biHeight = size.cy;
	header.biSizeImage = NbBytes;
	header.biSize = sizeof(BITMAPINFOHEADER);
	header.biPlanes = 1;
	header.biBitCount =  bytesPerPixel * 8; // RGB
	header.biCompression = 0;
	header.biXPelsPerMeter = 0;
	header.biYPelsPerMeter = 0;
	header.biClrUsed = 0;
	header.biClrImportant = 0;
	
	// Generate handle
	HANDLE handle = (HANDLE)::GlobalAlloc (GHND,sizeof(BITMAPINFOHEADER) + NbBytes);
	if(handle != NULL)
	{
		// Lock handle
		char *pData = (char *) ::GlobalLock((HGLOBAL)handle);
		// Copy header and data
		memcpy(pData,&header,sizeof(BITMAPINFOHEADER));
		memcpy(pData+sizeof(BITMAPINFOHEADER),pPixelData,NbBytes);
		// Unlock
		::GlobalUnlock((HGLOBAL)handle);
		
		// Push DIB in clipboard
		OpenClipboard();
		EmptyClipboard();
		SetClipboardData(CF_DIB,handle);
		CloseClipboard();
	}
	
	// turn it back
	wglMakeCurrent(NULL, NULL);

	// Cleanup
	delete [] pPixelData;
	
	EndWaitCursor(); 
	
/*

	if(OpenClipboard()) 
	{ 
		BeginWaitCursor(); 
		
		// Snap (see below) 
		
		CSize size; 
		unsigned char *pixel = SnapClient(&size); 
		
		// Image 
		
		CTexture image; 
		
		// Link image - buffer 
		
		VERIFY(image.ReadBuffer(pixel,size.cx,size.cy,24)); 
		
		// Cleanup memory 
		
		delete [] pixel; 
		EmptyClipboard(); 
		SetClipboardData(CF_DIB,image.ExportHandle()); // short is better 
		
		CloseClipboard(); 
		EndWaitCursor(); 
	} 
*/
}

void CVisualizer_XView::OnEditCopy() 
{
	// TODO: Add your command handler code here
	CopyToClipboard();
}

unsigned char* CVisualizer_XView::SnapClient(CSize *pSize) 
{ 
	BeginWaitCursor(); 
	
	// Client zone 
	
	CRect rect; 
	GetClientRect(&rect); 
	CSize size(rect.Width(),rect.Height()); 
	*pSize = size; 
	ASSERT(size.cx > 0); 
	ASSERT(size.cy > 0); 
	
	// Alloc 
	
	unsigned char *pixel = new unsigned char[3*size.cx*size.cy]; 
	ASSERT(pixel != NULL); 
	
	// Capture frame buffer 
	
	TRACE("Start reading client...\n"); 
	TRACE("Client : (%d,%d)\n",size.cx,size.cy); 
	CRect ClientRect,MainRect; 
	this->GetWindowRect(&ClientRect); 
	CWnd *pMain = AfxGetApp()->m_pMainWnd; 
	CWindowDC dc(pMain); 
	pMain->GetWindowRect(&MainRect); 
	int xOffset = ClientRect.left - MainRect.left; 
	int yOffset = ClientRect.top - MainRect.top; 
	for(int j=0;j < size.cy; j++)
		for(int i=0;i < size.cx; i++) 
		{ 
			COLORREF color = dc.GetPixel(i+xOffset,j+yOffset); // slow but reliable 
			
			pixel[3*(size.cx*(size.cy-1-j)+i)] = (BYTE)GetBValue(color); 
			pixel[3*(size.cx*(size.cy-1-j)+i)+1] = (BYTE)GetGValue(color); 
			pixel[3*(size.cx*(size.cy-1-j)+i)+2] = (BYTE)GetRValue(color); 
		}  
	EndWaitCursor(); 
	return pixel; 
} 


void CVisualizer_XView::OnEditExport() 
{
	// TODO: Add your command handler code here
	CreateBitmapFile("snapshot.bmp");
}

void CVisualizer_XView::CreateBitmapFile(CString sFileName)
{
	CRect rDrawingSurface;
	GetClientRect(&rDrawingSurface);
	CDC* pDC = GetDC();
	
	BMIH.biSize = sizeof(BITMAPINFOHEADER);
	BMIH.biBitCount = 24;
	BMIH.biPlanes = 1;
	BMIH.biCompression = BI_RGB;
	BMIH.biWidth = rDrawingSurface.Width();
	BMIH.biHeight = rDrawingSurface.Height();
	BMIH.biSizeImage = ((((BMIH.biWidth * BMIH.biBitCount) + 31) & ~31) >> 3) * BMIH.biHeight;
	hDrawingSurface = CreateDIBSection(pDC->GetSafeHdc(), (CONST BITMAPINFO*)&BMIH, DIB_RGB_COLORS, 
		(void**)&pDrawingSurfaceBits, NULL, 0);
	
	// associate a mem dc to the bitmap
	CDC dcMem;
	dcMem.CreateCompatibleDC(pDC);
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(dcMem.GetSafeHdc(), hDrawingSurface);	
	
	// copy the pdc to the mem dc associated with the bitmap
	BOOL bResult = BitBlt(dcMem.GetSafeHdc(), rDrawingSurface.left, rDrawingSurface.top,
		rDrawingSurface.Width(), rDrawingSurface.Height(),
		pDC->GetSafeHdc(), 0, 0, SRCCOPY);
	
	SelectObject(dcMem.GetSafeHdc(), hOldBitmap);
	
	ReleaseDC(pDC);
	
	int nBitsOffset = sizeof(BITMAPFILEHEADER) + BMIH.biSize; 
	LONG lImageSize = BMIH.biSizeImage;
	LONG lFileSize = nBitsOffset + lImageSize;
	bmfh.bfType = 'B'+('M'<<8);			
	bmfh.bfOffBits = nBitsOffset;		
	bmfh.bfSize = lFileSize;				
	bmfh.bfReserved1 = bmfh.bfReserved2 = 0;
	
	// write the bitmap info to a bitmap file
	FILE *pFile = fopen(sFileName, "wb");
	
	//Write the bitmap file header
	UINT nWrittenFileHeaderSize = fwrite(&bmfh, 1, sizeof(BITMAPFILEHEADER), pFile);
	//And then the bitmap info header
	UINT nWrittenInfoHeaderSize = fwrite(&BMIH, 1, sizeof(BITMAPINFOHEADER), pFile);
	//Finally, write the image data itself -- the data represents our drawing
	UINT nWrittenDIBDataSize = fwrite(pDrawingSurfaceBits, 1, lImageSize, pFile);
	
	fclose(pFile);


}

void CVisualizer_XView::OnOrtho() 
{
	// TODO: Add your command handler code here
	m_bPerspective = !m_bPerspective;
	Invalidate();
}

void CVisualizer_XView::OnUpdateOrtho(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_bPerspective);
}

void CVisualizer_XView::ResetView()
{
	m_scale		= 1.0f;
	m_xangle	= 0.0f;
	m_yangle	= 0.0f;
	m_translate	= -1.65f;
	m_bPerspective = TRUE;
	m_left = -1.0;
	m_right = 1.0;
	m_top = 1.0;
	m_bottom = -1.0;
	m_near = 1.0;
	m_far = 10.0;

	if (m_pProjectionDialog != NULL)
	{
		m_pProjectionDialog->m_bPerspective = m_bPerspective;
		m_pProjectionDialog->m_left	= m_left;
		m_pProjectionDialog->m_right = m_right;
		m_pProjectionDialog->m_top	= m_top;
		m_pProjectionDialog->m_bottom	= m_bottom;
		m_pProjectionDialog->m_near	= m_near;
		m_pProjectionDialog->m_far	= m_far;
		m_pProjectionDialog->m_translate = m_translate;
		m_pProjectionDialog->m_scale = m_scale;

		m_pProjectionDialog->UpdateData(FALSE);
	}

	Invalidate();
}

void CVisualizer_XView::OnTimer(UINT_PTR nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if (m_bIsReadingFromFile == TRUE)
	{
		Read(m_ifs);

		CString sFileName;
		if (m_bExport2Bmp == TRUE)
		{
			sFileName.Format("%s\\snapshot_%d.bmp", m_sExportingDirectory, m_frameID);
			CreateBitmapFile(sFileName);
			m_frameID++;
		}
	}
	
	if (m_bIsReadingFromStdIn == TRUE)
		Read(std::cin);

	if (m_bPlay == TRUE)
	{
	/*	if (m_bXRotate == TRUE)
			m_xangle += m_rotatingStep;

		if (m_bYRotate == TRUE)
			m_yangle += m_rotatingStep;

		if (m_bZRotate == TRUE)
			m_zangle += m_rotatingStep;
	*/
	//	if (m_translate < -1.)
	//		m_translate += 0.02f;
		
	//	if (m_zangle <= 20.0)
	//		m_zangle += m_rotatingStep;

	/*	m_rotatingStep = 1.0;
		if (m_xangle <= m_targetXangle)
			m_xangle += m_rotatingStep;
		else if (m_xangle >= m_targetXangle)
			m_xangle -= m_rotatingStep;

		if (m_yangle <= m_targetYangle)
			m_yangle += m_rotatingStep;
		else if (m_yangle >= m_targetYangle)
			m_yangle -= m_rotatingStep;

		if (m_zangle <= m_targetZangle)
			m_zangle += 0.5;
		else if (m_zangle >= m_targetZangle)
			m_zangle -= 0.5;

		if (m_scale <= m_targetScale)
		{
			m_scale += 0.008;
		
			m_left = -1.0 * m_scale;
			m_top = 1.0 * m_scale;
			m_right = 1.0 * m_scale;
			m_bottom = -1.0 * m_scale;
		}
		else if (m_scale >= m_targetScale)
		{
			m_scale -= 0.008;
		
			m_left = -1.0 * m_scale;
			m_top = 1.0 * m_scale;
			m_right = 1.0 * m_scale;
			m_bottom = -1.0 * m_scale;
		}
	*/

		Invalidate();
	}

	CGLEnabledView::OnTimer(nIDEvent);
}

void CVisualizer_XView::OnViewBackground() 
{
	// TODO: Add your command handler code here
	CColorDialog dlg;

	if (dlg.DoModal() == IDOK)
	{
		COLORREF nColor = dlg.GetColor();
		m_background[0] = GetRValue(nColor) / 255.0;
		m_background[1] = GetGValue(nColor) / 255.0;
		m_background[2] = GetBValue(nColor) / 255.0;

		Invalidate();
	}
}

void CVisualizer_XView::OnFileUsingTemplate() 
{
	// TODO: Add your command handler code here
	CParticleTemplateDialog dlg;
	CVisualizer_XApp* pApp = (CVisualizer_XApp*)AfxGetApp();
	
	dlg.m_nBeadsSkipped = m_nBeadsSkipped;
	dlg.m_bOverrideNumBeads = m_bOverrideNumBeads;
	dlg.m_sFileName = pApp->m_sTemplateFileName;		
	dlg.m_bReleasePBC = m_bReleasePBC;
	dlg.m_nNumBeads = m_nBeadsInParticle;

	if (dlg.DoModal() == IDOK)
	{
		m_nBeadsSkipped = dlg.m_nBeadsSkipped;
		m_bOverrideNumBeads = dlg.m_bOverrideNumBeads;
		m_bReleasePBC = dlg.m_bReleasePBC;
		pApp->m_sTemplateFileName = dlg.m_sFileName;
		
		if (m_bOverrideNumBeads == TRUE)
			m_nBeadsInParticle = dlg.m_nNumBeads;
		
		ApplyTemplate();
		
		Invalidate();
	}

}

void CVisualizer_XView::OnFileRead() 
{
	// TODO: Add your command handler code here
	CReadDialog dlg;

	dlg.m_bExport2Bmp = m_bExport2Bmp;
	dlg.m_sExportingDirectory = m_sExportingDirectory;
	dlg.m_nStartingFrame = m_frameID;
	dlg.m_sScriptFileName = m_sScriptFileName;

	if (dlg.DoModal() == IDOK)
	{
		CString sFileName = dlg.m_sFileRead;

		m_bExport2Bmp = dlg.m_bExport2Bmp;
		if (m_bExport2Bmp == TRUE)
			m_frameID = dlg.m_nStartingFrame;

		
		m_sScriptFileName = dlg.m_sScriptFileName;

		ReadScriptFile(m_sScriptFileName);

		m_sExportingDirectory = dlg.m_sExportingDirectory;

		// This clear() is mandatory when re-open the file, otherwise ifs will not start from the beginning!
		m_ifs.clear();
		
		m_ifs.open(sFileName);

		m_nDataType = __XYZ;
		m_bIsReadingFromFile = TRUE;
		CleanRead(m_ifs);

		m_nBeadsSkipped = dlg.m_nBeadsSkipped;
		if (dlg.m_bOverrideNumBeads == TRUE)
			m_nBeadsInParticle = dlg.m_nBeadsInParticle;

		CVisualizer_XDoc* pDoc = GetDocument();
		for (int i=0; i<m_particleArray.size(); i++)
			m_particleArray[i]->Zoom(pDoc->m_particleScale);

		ApplyTemplate();

		// Turn on playback
		m_bPlay = TRUE;
		
	}
	
}

void CVisualizer_XView::ReadScriptFile(CString sFileName)
{
	CVisualizer_XDoc* pDoc = GetDocument();
	std::ifstream ifs(sFileName);

	char line[100];
	std::string entry, value;
	while (!ifs.eof())
	{
		ifs.getline(line, 100);

		Parse(line, entry, value);
	
		if (strcmp(entry.data(), "[Particle Scale]") == 0)
		{
			pDoc->m_particleScale = atof(value.data());
		//	for (int i=0; i<m_particleArray.size(); i++)
		//		m_particleArray[i]->Zoom(pDoc->m_particleScale);
		}
		else if (strcmp(entry.data(), "[Left]") == 0)
			m_left = atof(value.data());
		else if (strcmp(entry.data(), "[Right]") == 0)
			m_right = atof(value.data());
		else if (strcmp(entry.data(), "[Top]") == 0)
			m_top = atof(value.data());
		else if (strcmp(entry.data(), "[Bottom]") == 0)
			m_bottom = atof(value.data());
		else if (strcmp(entry.data(), "[Translate]") == 0)
			m_translate = atof(value.data());
		else if (strcmp(entry.data(), "[Scale]") == 0)
			m_scale = atof(value.data());
		else if (strcmp(entry.data(), "[X Angle]") == 0)
			m_xangle = atof(value.data());
		else if (strcmp(entry.data(), "[Y Angle]") == 0)
			m_yangle = atof(value.data());
		else if (strcmp(entry.data(), "[Z Angle]") == 0)
			m_zangle = atof(value.data());
		else if (strcmp(entry.data(), "[X Light Angle]") == 0)
			m_xLightAngle = atof(value.data());
		else if (strcmp(entry.data(), "[Y Light Angle]") == 0)
			m_yLightAngle = atof(value.data());
		else if (strcmp(entry.data(), "[Z Light Angle]") == 0)
			m_zLightAngle = atof(value.data());
		else if (strcmp(entry.data(), "[X Light Position]") == 0)
			m_positionLight0[0] = atof(value.data());
		else if (strcmp(entry.data(), "[Y Light Position]") == 0)
			m_positionLight0[1] = atof(value.data());
		else if (strcmp(entry.data(), "[Z Light Position]") == 0)
			m_positionLight0[2] = atof(value.data());
		else if (strcmp(entry.data(), "[Draw Box]") == 0)
			m_bBoundingBox = atoi(value.data());
		else if (strcmp(entry.data(), "[Draw Coordinates]") == 0)
			m_bDrawOrigin = atoi(value.data());
		else if (strcmp(entry.data(), "[Hidden Type]") == 0)
		{
			int nType = atoi(value.data());
			m_nHiddenType[nType] = 1;
		}
		else if (strcmp(entry.data(), "[Background]") == 0)
		{
			sscanf(value.data(), "%lf\t%lf\t%lf", &m_background[0], &m_background[1], &m_background[2]);

		}
		else if (strcmp(entry.data(), "[Target Scale]") == 0)
			m_targetScale = atof(value.data());
		else if (strcmp(entry.data(), "[Target X Angle]") == 0)
			m_targetXangle = atof(value.data());
		else if (strcmp(entry.data(), "[Target Y Angle]") == 0)
			m_targetYangle = atof(value.data());
		else if (strcmp(entry.data(), "[Target Z Angle]") == 0)
			m_targetZangle = atof(value.data());
		else if (strcmp(entry.data(), "[Region]") == 0)
		{	
			m_region.type = 1;
			double radius;
			sscanf(value.data(), "%lf", &radius);
			m_region.radius_outer = m_region.box_scale * radius;
		}
		else if (strcmp(entry.data(), "[Particles]") == 0)
		{
			sscanf(value.data(), "%d\t%d", &m_nParticleStartIndex, &m_nParticleEndIndex);

		}
		else if (strcmp(entry.data(), "[Resolution]") == 0)
		{
			m_nResolution = atoi(value.data());
		}
		else if (strcmp(entry.data(), "[Fogging]") == 0)
		{
			int flag = atoi(value.data());
			if (flag == 0)
				m_bFogging = FALSE;
			else 
				m_bFogging = TRUE;
		}

	}

	ifs.close();
}

void CVisualizer_XView::OnViewTypeType1() 
{
	// TODO: Add your command handler code here
	m_nChosenType = 0;
}

void CVisualizer_XView::OnViewTypeType2() 
{
	// TODO: Add your command handler code here
	m_nChosenType = 1;
}

void CVisualizer_XView::OnViewTypeType3() 
{
	// TODO: Add your command handler code here
	m_nChosenType = 2;
}

void CVisualizer_XView::OnViewTypeType4() 
{
	// TODO: Add your command handler code here
	m_nChosenType = 3;
}

void CVisualizer_XView::OnViewTypeType5() 
{
	// TODO: Add your command handler code here
	m_nChosenType = 4;
}

void CVisualizer_XView::OnViewTypeType6() 
{
	// TODO: Add your command handler code here
	m_nChosenType = 5;
}


void CVisualizer_XView::OnUpdateViewTypeType1(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_nChosenType == 0);
}

void CVisualizer_XView::OnUpdateViewTypeType2(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_nChosenType == 1);
}

void CVisualizer_XView::OnUpdateViewTypeType3(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_nChosenType == 2);
}

void CVisualizer_XView::OnUpdateViewTypeType4(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_nChosenType == 3);
}

void CVisualizer_XView::OnUpdateViewTypeType5(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_nChosenType == 4);
}

void CVisualizer_XView::OnUpdateViewTypeType6(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_nChosenType == 5);
}

void CVisualizer_XView::OnViewTypeAll() 
{
	// TODO: Add your command handler code here
	m_nChosenType = -1;
}

void CVisualizer_XView::OnUpdateViewTypeAll(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_nChosenType == -1);
}


///////////////////////////////////////////////////////////////
//

void CVisualizer_XView::OnEditSettings() 
{
	// TODO: Add your command handler code here
	CVisualizer_XDoc* pDoc = GetDocument();
	CPropertySheet sheet(_T("Settings"));
	CParticlesPage particlesPage;
	CSpecialEffectsPage effectsPage;
	CPreprocPage preprocPage;
	
	int i;
//	CSettingsDialog	dlg;
	particlesPage.m_particleScalingStep		= pDoc->m_particleScalingStep;
	particlesPage.m_particleTranslatingStep	= pDoc->m_particleTranslatingStep;
	particlesPage.m_rotatingStep			= m_rotatingStep;
	particlesPage.m_nTranslatingDirection	= m_nTranslatingDirection;
	particlesPage.m_minScale = pDoc->m_minScale;
	particlesPage.m_maxScale = pDoc->m_maxScale;
	particlesPage.m_scaleCoeff = pDoc->m_scaleCoeff;
	particlesPage.m_objectScale = pDoc->m_objectScale;

	preprocPage.m_bXRotate		= m_bXRotate;
	preprocPage.m_bYRotate		= m_bYRotate;
	preprocPage.m_bZRotate		= m_bZRotate;
	preprocPage.m_xModelAngle	= m_xModelAngle;
	preprocPage.m_yModelAngle	= m_yModelAngle;
	preprocPage.m_zModelAngle	= m_zModelAngle;
	
	effectsPage.m_bUseTwoLightSources = m_bUseTwoLightSources;
	effectsPage.m_bBlend		= m_bBlend;
	effectsPage.m_nResolution	= m_nResolution;
	effectsPage.m_bFogging		= m_bFogging;
	effectsPage.m_fogDensity	= m_fogDensity;
	effectsPage.m_nFogMode		= m_fogMode;
	effectsPage.m_fog_far		= m_fog_far;
	effectsPage.m_fog_near		= m_fog_near;
	effectsPage.m_bDrawingOutlines = m_bDrawingOutlines;
	effectsPage.m_outlineWidth = m_outlineWidth;
	effectsPage.m_nApplyDrawingCommand = TRUE;
	
	for (i=0; i<m_nParticles; i++)
		if (m_particleArray[i]->m_nApplyingCommand == 0)
		{
			effectsPage.m_nApplyDrawingCommand = FALSE;
			break;
		}

	sheet.AddPage(&particlesPage);
	sheet.AddPage(&effectsPage);
	sheet.AddPage(&preprocPage);
	
	if (sheet.DoModal() == IDOK)
	{
		pDoc->m_particleScalingStep	= particlesPage.m_particleScalingStep;
		pDoc->m_particleTranslatingStep = particlesPage.m_particleTranslatingStep;
		m_rotatingStep = particlesPage.m_rotatingStep;
		m_nTranslatingDirection	= particlesPage.m_nTranslatingDirection;
		pDoc->m_minScale	= particlesPage.m_minScale;
		pDoc->m_maxScale	= particlesPage.m_maxScale;
		pDoc->m_scaleCoeff	= particlesPage.m_scaleCoeff;
		pDoc->m_objectScale = particlesPage.m_objectScale;

		m_bXRotate		= preprocPage.m_bXRotate;
		m_bYRotate		= preprocPage.m_bYRotate;
		m_bZRotate		= preprocPage.m_bZRotate;
		m_xModelAngle	= preprocPage.m_xModelAngle;
		m_yModelAngle	= preprocPage.m_yModelAngle;
		m_zModelAngle	= preprocPage.m_zModelAngle;
		
		m_bUseTwoLightSources = effectsPage.m_bUseTwoLightSources;
		m_bBlend		= effectsPage.m_bBlend;	
		m_nResolution	= effectsPage.m_nResolution;
		m_bFogging		= effectsPage.m_bFogging;
		m_fogDensity	= effectsPage.m_fogDensity;
		m_fogMode		= effectsPage.m_nFogMode;
		m_fog_far		= effectsPage.m_fog_far;
		m_fog_near		= effectsPage.m_fog_near;
		m_bDrawingOutlines = effectsPage.m_bDrawingOutlines;
		m_outlineWidth = effectsPage.m_outlineWidth;
		
		if (effectsPage.m_nApplyDrawingCommand == FALSE)
		{
			for (i=0; i<m_nParticles; i++)
				m_particleArray[i]->m_nApplyingCommand = 0;
		}
		else
		{
			for (i=0; i<m_nParticles; i++)
				m_particleArray[i]->m_nApplyingCommand = 1;
		}
		
		int nObjects = m_objectArray.size();
		for (i=0; i<nObjects; i++)
		{
			m_objectArray[i]->m_scale = pDoc->m_objectScale;
		}

		Invalidate();
	}

}

void CVisualizer_XView::OnXy() 
{
	// TODO: Add your command handler code here
	m_xangle = 0.0;
	m_yangle = 0.0;
	m_zangle = 0.0;

	if (m_pCurrentDialog != NULL)
	{
		m_pCurrentDialog->m_xAngle = m_xangle;
		m_pCurrentDialog->m_yAngle = m_yangle;
		m_pCurrentDialog->m_zAngle = m_zangle;
		m_pCurrentDialog->UpdateData(FALSE);
	}

	Invalidate();
}

void CVisualizer_XView::OnYz() 
{
	// TODO: Add your command handler code here
	m_xangle = -90.0;
	m_yangle = 0.0;
	m_zangle = -90.0;

	if (m_pCurrentDialog != NULL)
	{
		m_pCurrentDialog->m_xAngle = m_xangle;
		m_pCurrentDialog->m_yAngle = m_yangle;
		m_pCurrentDialog->m_zAngle = m_zangle;
		m_pCurrentDialog->UpdateData(FALSE);
	}

	Invalidate();
}

void CVisualizer_XView::OnZx() 
{
	// TODO: Add your command handler code here
	m_xangle = 0.0;
	m_yangle = 90.0;
	m_zangle = 90.0;

	if (m_pCurrentDialog != NULL)
	{
		m_pCurrentDialog->m_xAngle = m_xangle;
		m_pCurrentDialog->m_yAngle = m_yangle;
		m_pCurrentDialog->m_zAngle = m_zangle;
		m_pCurrentDialog->UpdateData(FALSE);
	}

	Invalidate();
}

void CVisualizer_XView::OnXz() 
{
	// TODO: Add your command handler code here
	m_xangle = -90.0;
	m_yangle = 0.0;
	m_zangle = 0.0;

	if (m_pCurrentDialog != NULL)
	{
		m_pCurrentDialog->m_xAngle = m_xangle;
		m_pCurrentDialog->m_yAngle = m_yangle;
		m_pCurrentDialog->m_zAngle = m_zangle;
		m_pCurrentDialog->UpdateData(FALSE);
	}

	Invalidate();
}

void CVisualizer_XView::OnYx() 
{
	// TODO: Add your command handler code here
	m_xangle = 0.0;
	m_yangle = 180.0;
	m_zangle = 90.0;

	if (m_pCurrentDialog != NULL)
	{
		m_pCurrentDialog->m_xAngle = m_xangle;
		m_pCurrentDialog->m_yAngle = m_yangle;
		m_pCurrentDialog->m_zAngle = m_zangle;
		m_pCurrentDialog->UpdateData(FALSE);
	}

	Invalidate();
}

void CVisualizer_XView::OnZy() 
{
	// TODO: Add your command handler code here
	m_xangle = 0.0;
	m_yangle = 90.0;
	m_zangle = 0.0;

	if (m_pCurrentDialog != NULL)
	{
		m_pCurrentDialog->m_xAngle = m_xangle;
		m_pCurrentDialog->m_yAngle = m_yangle;
		m_pCurrentDialog->m_zAngle = m_zangle;
		m_pCurrentDialog->UpdateData(FALSE);
	}

	Invalidate();
}

void CVisualizer_XView::OnViewParticle() 
{
	// TODO: Add your command handler code here
	CViewParticleDialog dlg;

	dlg.m_nParticleEndIndex = m_nParticleEndIndex;
	dlg.m_nParticleStartIndex = m_nParticleStartIndex;
	dlg.m_center_box.Format("%g %g %g", 
		m_region.centerx * m_Lx / m_boxSizex, 
		m_region.centery * m_Ly / m_boxSizey, 
		m_region.centerz * m_Lz / m_boxSizez);
	dlg.m_Lx = (m_region.xhi - m_region.xlo) / m_region.box_scale;
	dlg.m_Ly = (m_region.yhi - m_region.ylo) / m_region.box_scale;
	dlg.m_Lz = (m_region.zhi - m_region.zlo) / m_region.box_scale;
	dlg.m_center_sphere.Format("%g %g %g", m_region.centerx / m_region.box_scale, m_region.centery / m_region.box_scale, m_region.centerz / m_region.box_scale);
	dlg.m_radius_inner = m_region.radius_inner / m_region.box_scale;
	dlg.m_radius_outer = m_region.radius_outer / m_region.box_scale;
	dlg.m_nVolType = m_region.type;
	dlg.m_bOutside = m_region.m_bOutside;

	if (dlg.DoModal() == IDOK)
	{
		m_nParticleEndIndex = dlg.m_nParticleEndIndex;
		m_nParticleStartIndex = dlg.m_nParticleStartIndex;

		m_region.type = dlg.m_nVolType;

		if (m_region.type == 0)
		{
			sscanf(dlg.m_center_box, "%lf %lf %lf", &m_region.centerx, &m_region.centery, &m_region.centerz);

			// convert to scaled box
			m_region.centerx = m_region.centerx * m_boxSizex / m_Lx;
			m_region.centery = m_region.centery * m_boxSizey / m_Ly;
			m_region.centerz = m_region.centerz * m_boxSizez / m_Lz;

			double Lx = dlg.m_Lx  * m_boxSizex / m_Lx;
			double Ly = dlg.m_Ly  * m_boxSizey / m_Ly;
			double Lz = dlg.m_Lz  * m_boxSizez / m_Lz;
			m_region.xlo = m_region.centerx - Lx / 2.0;
			m_region.xhi = m_region.centerx + Lx / 2.0;
			m_region.ylo = m_region.centery - Ly / 2.0;
			m_region.yhi = m_region.centery + Ly / 2.0;	
			m_region.zlo = m_region.centerz - Lz / 2.0;
			m_region.zhi = m_region.centerz + Lz / 2.0;

		}
		else
		{
			sscanf(dlg.m_center_sphere, "%lf %lf %lf", &m_region.centerx, &m_region.centery, &m_region.centerz);
			m_region.centerx = m_region.centerx * m_boxSizex / m_Lx;
			m_region.centery = m_region.centery * m_boxSizey / m_Ly;
			m_region.centerz = m_region.centerz * m_boxSizex / m_Lz;

			m_region.radius_inner = dlg.m_radius_inner * m_region.box_scale;
			m_region.radius_outer = dlg.m_radius_outer * m_region.box_scale;
		}

		m_region.m_bOutside = dlg.m_bOutside;

		// by default, let all the particles be drawn
		for (int i=0; i<m_nParticles; i++)
			m_particleArray[i]->m_bDrawn = TRUE;

		Invalidate();
	}
}

///////////////////////////////////////////////////////////////////
//

void CVisualizer_XView::OnToolsClustering() 
{
	// TODO: Add your command handler code here
	
}

void CVisualizer_XView::OnTranslatingDirection() 
{
	// TODO: Add your command handler code here
	if (m_nTranslatingDirection == 0) 
		m_nTranslatingDirection = 1;
	else
		m_nTranslatingDirection = 0;
}



void CVisualizer_XView::OnUpdateNegative(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetRadio(m_nTranslatingDirection == 1);	
}

void CVisualizer_XView::OnUpdatePositive(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetRadio(m_nTranslatingDirection == 0);	
}

void CVisualizer_XView::OnViewCells() 
{
	// TODO: Add your command handler code here
	CCellsDialog dlg;

	dlg.m_ncellx = m_ncellx;
	dlg.m_ncelly = m_ncelly;
	dlg.m_ncellz = m_ncellz;

	if (dlg.DoModal() == IDOK)
	{
		m_ncellx = dlg.m_ncellx;
		m_ncelly = dlg.m_ncelly;
		m_ncellz = dlg.m_ncellz;

		if (m_ncellx == 1 && m_ncelly == 1 && m_ncellz == 1)
			m_nDrawCells = 0;

		if (m_nDrawCells == 0)
			return;

		DrawCells();
	}

}

void CVisualizer_XView::ApplyTemplate()
{
	double L[3];
		
	L[0] = m_boxSizex;
	L[1] = m_boxSizey;
	L[2] = m_boxSizez;
	
	// First time applying template
	if (m_bFirstTimeApplyingTemplate == FALSE)
	{
		CVisualizer_XApp* pApp = (CVisualizer_XApp*)AfxGetApp();

		int i, j, nParticles, nBeadsInParticle=1;
		double scale;
		std::vector<CPosition> positionArray;
		CParticle::CDrawingTemplate	drawingTemplate;
		CParticle* pParticle = new CParticle;

		if (pApp->m_sTemplateFileName.GetLength() > 0)
			nBeadsInParticle = pParticle->ReadDrawingTemplate(pApp->m_sTemplateFileName);
		
		if (m_bOverrideNumBeads == FALSE)
			m_nBeadsInParticle = nBeadsInParticle;

		drawingTemplate = pParticle->GetDrawingTemplate();

		
		for (i=m_nBeadsSkipped; i<m_particleArray.size(); i++)
		{
			pParticle = m_particleArray[i];
			for (j=0; j<pParticle->m_positionArray.size(); j++)
			{
				positionArray.push_back(pParticle->m_positionArray[j]);
				scale = pParticle->m_scale;
			}
		}
		
		nParticles = positionArray.size() / m_nBeadsInParticle;

		m_particleArray.clear();
	
		for (i=0; i<nParticles; i++)
		{
			CParticle* pNewParticle = new CParticle();
			for (j=0; j<m_nBeadsInParticle; j++)
				pNewParticle->AddSite(positionArray[j + m_nBeadsInParticle * i]);
		
			pNewParticle->SetDrawingTemplate(drawingTemplate);
			if (m_bReleasePBC)
				pNewParticle->ReleasePeriodicBoundaryConditions(L);  
			m_particleArray.push_back(pNewParticle);
		}

		if (m_bIsReadingFromFile == TRUE)
			m_bFirstTimeApplyingTemplate = TRUE;		
		
		m_bUsingTemplate = TRUE;

		m_nParticleStartIndex = 0;
		m_nParticleEndIndex = nParticles - 1;

		positionArray.clear();
		delete pParticle;
	}
	else
	{
		for (int i=0; i<m_nParticles; i++)
		{
			if (m_bReleasePBC)
				m_particleArray[i]->ReleasePeriodicBoundaryConditions(L);  
		}
		
	}
	
}

BOOL CVisualizer_XView::IsVisualized(int index)
{
	BOOL shown = TRUE;
	BOOL inrange = TRUE;

	if (m_nParticleStartIndex >= 0 && m_nParticleEndIndex >= 0 &&
			m_nParticleEndIndex >= m_nParticleStartIndex)
	{
		if (index >= m_nParticleStartIndex && index <= m_nParticleEndIndex)
			inrange = TRUE;
		else 
			inrange = FALSE;
	}

	CParticle* pParticle = m_particleArray[index];
	
	int i;
	BOOL bInside = FALSE;
	double radius_outer2 = m_region.radius_outer * m_region.radius_outer;
	double radius_inner2 = m_region.radius_inner * m_region.radius_inner;
	for (i=0; i<pParticle->m_positionArray.size(); i++)
	{
		if (m_region.type == 0)	// box
		{
			if (pParticle->m_positionArray[i][0] >= m_region.xlo && pParticle->m_positionArray[i][0] <= m_region.xhi
				&& pParticle->m_positionArray[i][1] >= m_region.ylo && pParticle->m_positionArray[i][1] <= m_region.yhi
				&& pParticle->m_positionArray[i][2] >= m_region.zlo && pParticle->m_positionArray[i][2] <= m_region.zhi)
			{
				bInside = TRUE;
				break;				
			}
		}
		else // spherical region
		{
			double r2 = (pParticle->m_positionArray[i][0] - m_region.centerx) * (pParticle->m_positionArray[i][0] - m_region.centerx) +
				(pParticle->m_positionArray[i][1] - m_region.centery) * (pParticle->m_positionArray[i][1] - m_region.centery) + 
				(pParticle->m_positionArray[i][2] - m_region.centerz) * (pParticle->m_positionArray[i][2] - m_region.centerz);
/*
			if (r2 >= radius_inner2 && r2 <= radius_outer2)
			{
				bInside = TRUE;
				break;
			}

*/
			if (r2 <= radius_outer2)
			{
				if (pParticle->m_positionArray[i][2] > 0.0
					&& pParticle->m_positionArray[i][1] > 0.0
					&& pParticle->m_positionArray[i][0] > 0.0)
				{
					if (r2 < radius_inner2)
						bInside = TRUE;
				}
				else
					bInside = TRUE;

				break;
			}

		}
	}

	// considering outside
	if (m_region.m_bOutside)
		shown = !bInside;
	else
		shown = bInside;

	shown &= inrange;
	return shown;
}

void CVisualizer_XView::OnToolsMovetoorigin() 
{
	// TODO: Add your command handler code here
		// Find the system center of mass
	int i, j, nNumPositions;
	double x, y, z, xm[3];
	xm[0] = xm[1] = xm[2] = 0.0;

	double ncount = 0.0;
	for (i=0; i<m_nParticles; i++)
	{
		if (IsVisualized(i) == FALSE)
			continue;

		nNumPositions = m_particleArray[i]->m_positionArray.size();
		for (j=0; j<nNumPositions; j++)
		{
			x = m_particleArray[i]->m_positionArray[j][0];
			y = m_particleArray[i]->m_positionArray[j][1];
			z = m_particleArray[i]->m_positionArray[j][2];
		
			xm[0] += x;
			xm[1] += y;
			xm[2] += z;

			ncount += 1.0;
		}
	}

	xm[0] /= ncount;
	xm[1] /= ncount;
	xm[2] /= ncount;

	// Move the center of mass to the origin
	for (i=0; i<m_nParticles; i++)
	{
		nNumPositions = m_particleArray[i]->m_positionArray.size();
		for (j=0; j<nNumPositions; j++)
		{
			m_particleArray[i]->m_positionArray[j][0] -= xm[0];
			m_particleArray[i]->m_positionArray[j][1] -= xm[1];
			m_particleArray[i]->m_positionArray[j][2] -= xm[2];
		}
	}

	Invalidate();
}

//////////////////////////////////////////////////////////////////

void CVisualizer_XView::OnToolsChangetype() 
{
	// TODO: Add your command handler code here
	CChangeTypeDialog dlg;
	if (dlg.DoModal() == IDOK)
	{
		int i, j;
		int nSrcType = dlg.m_nSrcType;
		int nDestType = dlg.m_nDestType;
		int nLocalIndex = dlg.m_nLocalIndex;

		for (i=0; i<m_nParticles; i++)
		{
			if (IsVisualized(i) == FALSE)
				continue;

			CParticle* pParticle = m_particleArray[i];
			for (j=0; j<pParticle->m_positionArray.size(); j++)
			{
				if (j == nLocalIndex || nLocalIndex == -1)
				{
					int nType = pParticle->m_positionArray[j].GetType();
					if (dlg.m_bSwap == FALSE)
					{
						if (nType == nSrcType)
							pParticle->m_positionArray[j].SetType(nDestType);
					}
					else  // swap two types
					{ 
						if (nType == nSrcType)
							pParticle->m_positionArray[j].SetType(nDestType);
						else if (nType == nDestType)
							pParticle->m_positionArray[j].SetType(nSrcType);
					}
				}
			}
		}
		
		Invalidate();

	}
}

void CVisualizer_XView::OnUpdateToolsChangetype(CCmdUI* pCmdUI) 
{	
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_nParticles > 0);
}

/////////////////////////////////////////////////////////////////////


void CVisualizer_XView::OnToolsAddobjectsFromfile() 
{
	// TODO: Add your command handler code here
	CObjectDialog dlg;

	CVisualizer_XDoc* pDoc = GetDocument();

	dlg.m_nBeadsInParticle = m_nBeadsInParticle;
	dlg.m_objectScale = pDoc->m_objectScale;
	if (dlg.DoModal() == IDOK)
	{
		CString fileName = dlg.m_sFileName;
		int startingParticleIdx = dlg.m_nStartingParticleIdx;
		int nNumObjectsInParticle = dlg.m_nNumObjectsInParticle;
		CString attachedIndices = dlg.m_strAttachedIndices;
		pDoc->m_objectScale = dlg.m_objectScale;
		BOOL bUseParticleType = dlg.m_bUseParticleType;
		int nObjectType = dlg.m_nObjectType;

		if (dlg.m_nBeadsInParticle > 0)
		{
			m_nBeadsInParticle = dlg.m_nBeadsInParticle;
			m_bOverrideNumBeads = TRUE;
		}
		
		if (fileName.GetLength() <= 0)
			return;

		std::ifstream ifs;
		ifs.open(fileName);

		int i, idx;
		vector<int> localIndices;
		istrstream is(attachedIndices);
		for (i=0; i<nNumObjectsInParticle; i++)
		{
			is >> idx;
			localIndices.push_back(idx);
		}

		AddObjectsFromFile(ifs, startingParticleIdx, localIndices, nNumObjectsInParticle);
	
		ifs.close();

		pDoc->m_objectScale = pDoc->m_particleScale * 2.0f;
		int nObjects = m_objectArray.size();
		for (i=0; i<nObjects; i++)
		{
			m_objectArray[i]->m_scale = pDoc->m_objectScale;
			m_objectArray[i]->m_bUseParticleType = bUseParticleType;
			m_objectArray[i]->m_nType = nObjectType; 
		}

		Invalidate();
	}
}

void CVisualizer_XView::AddObjectsFromFile(std::istream& ifs, int startingIdx, std::vector<int>& localIndices, int nNumObjectsInParticle)
{
	int i, N;
	ifs >> N;
	
	int nParticles = m_particleArray.size();
	if (N % nParticles != 0)
		return;

	int nObjects = m_objectArray.size();
	if (nObjects > 0)
	{
		for (i=0; i<nObjects; i++)
		{
			delete [] m_objectArray[i];
		}

		m_objectArray.clear();
	}

	CVisualizer_XDoc* pDoc = GetDocument();
	int id;
	double dirx, diry, dirz;
	for (i=0; i<N; i++)
	{
		CArrowObject* pObject = new CArrowObject();
		ifs >> id >> dirx >> diry >> dirz;

		pObject->SetDirection(dirx, diry, dirz);

		int particle_id = (id-startingIdx) / nNumObjectsInParticle;
		int idx = (id-startingIdx) % nNumObjectsInParticle;
		int localIndex = localIndices[idx];
		pObject->SetPosition(&m_particleArray[particle_id]->m_positionArray[localIndex]);
		pObject->m_nParticleIndex = particle_id;

		m_objectArray.push_back(pObject);
		
	}
}

void CVisualizer_XView::OnUpdateDrawingobjs(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_bDrawingObjects == TRUE && m_objectArray.size() > 0);
}

void CVisualizer_XView::OnDrawingobjs() 
{
	// TODO: Add your command handler code here
	m_bDrawingObjects = !m_bDrawingObjects;
	Invalidate();
}


void CVisualizer_XView::OnToolsRdf() 
{
	// TODO: Add your command handler code here
	if (m_pRDFDialog == NULL)
	{
		m_pRDFDialog = new CRDFDialog(this);
		
		for (int i=0; i<m_nParticles; i++)
		{
			for (int j=0; j<m_particleArray[i]->m_positionArray.size(); j++)
			{
				CPosition p = m_particleArray[i]->m_positionArray[j];
				p[0] = p[0] * m_Lx / m_boxSizex;
				p[1] = p[1] * m_Ly / m_boxSizey;
				p[2] = p[2] * m_Lz / m_boxSizez;
				m_pRDFDialog->m_positionArray.push_back(p);
			}
		}

		m_pRDFDialog->m_Lx = m_Lx;
		m_pRDFDialog->m_Ly = m_Ly;
		m_pRDFDialog->m_Lz = m_Lz;
		m_pRDFDialog->m_Lmax = m_Lx/2.0;

		m_pRDFDialog->Create();
	
	}
}

void CVisualizer_XView::OnUpdateToolsRdf(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_nParticles > 1);
}

///////////////////////////////////////////////////////////////////////////////


void CVisualizer_XView::OnEditExporttopostscript() 
{
	// TODO: Add your command handler code here
	int size = 32e6;
	int doSort = 1;
	outputEPS(size, doSort);

}

void CVisualizer_XView::outputEPS(int size, int doSort)
{
	static char BASED_CODE filter[] = "EPS Files (*.eps)|*.eps";
	CFileDialog SaveDlg(FALSE,"*.eps","mesh.eps",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,filter);

	GLenum errCode;
	const GLubyte *errString;

	if(SaveDlg.DoModal() == IDOK)
	{
		CString string = SaveDlg.GetPathName();
		char *pFilename = string.GetBuffer(MAX_PATH);

		CDC* pDC = GetDC();

		// Alloc
		GLfloat *pFeedbackBuffer = new GLfloat[size];
		ASSERT(pFeedbackBuffer);

		// need to create render context here
		HGLRC hRC = wglCreateContext(pDC->m_hDC);

		// Useful in multidoc templates
		wglMakeCurrent(pDC->m_hDC, hRC);

		// Set feedback mode
	    glFeedbackBuffer(size, GL_3D_COLOR, pFeedbackBuffer);
		glRenderMode(GL_FEEDBACK);

		if ((errCode = glGetError()) != GL_NO_ERROR) 
		{
			errString = gluErrorString(errCode);
			char s[100];
			sprintf(s, "Error before: %s", errString);
			AfxMessageBox (s);
		}
	
		// Render
		CRect rect;
		GetClientRect(&rect);
		int wsize, centerx, centery, cx, cy;
		cx = rect.Width();
		cy = rect.Height();
		wsize = (cx > cy) ? cx : cy;
		centerx = cx / 2;
		centery = cy / 2;

		glEnable(GL_DEPTH_TEST);
		
		// Set clear Z-Buffer value
		glClearDepth(1.0f);
		glDepthFunc(GL_LEQUAL);
		glEnable(GL_DEPTH_TEST);
		
		glEnable(GL_LINE_SMOOTH);
		glShadeModel(GL_SMOOTH); 
		glFrontFace(GL_CCW);
		
		// Create and enable a white directional light
		glLightfv(GL_LIGHT0, GL_DIFFUSE, m_diffuseLight0);
		glLightfv(GL_LIGHT0, GL_AMBIENT, m_ambientLight0);
		glLightfv(GL_LIGHT0, GL_SPECULAR, m_specularLight0);
		glLightfv(GL_LIGHT0, GL_POSITION, m_positionLight0);
		
		glLightfv(GL_LIGHT1, GL_DIFFUSE, m_diffuseLight1);
		glLightfv(GL_LIGHT1, GL_AMBIENT, m_ambientLight1);
		glLightfv(GL_LIGHT1, GL_SPECULAR, m_specularLight1);
		glLightfv(GL_LIGHT1, GL_POSITION, m_positionLight1);
		
		glMaterialfv(GL_FRONT, GL_SPECULAR, m_materialSpecular);
		glMaterialfv(GL_FRONT, GL_EMISSION, m_materialEmission);
		glMaterialf(GL_FRONT, GL_SHININESS, m_shininess);
		
		glFogfv(GL_FOG_COLOR, m_fogColor);          // Define the fog colour 
		glFogf(GL_FOG_DENSITY, m_fogDensity);       // How dense 
		glFogi(GL_FOG_MODE, GL_LINEAR);             // exponential decay 
		glFogf(GL_FOG_START, m_near);                 // Where we start fogging 
		glFogf(GL_FOG_END, m_far);                   // end 
		glHint(GL_FOG_HINT, GL_NICEST);             // compute per vertex 
		if (m_bFogging == TRUE)
			glEnable(GL_FOG);                           
		
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		
		if (m_bUseTwoLightSources)
			glEnable(GL_LIGHT1);
		
		glPolygonMode(GL_FRONT,GL_FILL);
		glPolygonMode(GL_BACK,GL_FILL);

		// rescale viewport for EPS files
		double ratio = 612.0 / cx;
		m_viewportScale = ratio;

		DrawScene(GL_RENDER);

		// Double buffer
		SwapBuffers(pDC->m_hDC);

		glViewport(centerx * m_viewportScale - wsize  * m_viewportScale / 2, centery * m_viewportScale - wsize  * m_viewportScale /2, 
				wsize * m_viewportScale, wsize * m_viewportScale);
		
		
		m_viewportScale = 1.0;

		GLint returned = glRenderMode(GL_RENDER);

		if ((errCode = glGetError()) != GL_NO_ERROR) 
		{
			errString = gluErrorString(errCode);
			char s[100];
			sprintf(s, "Error after: %s", errString);
			AfxMessageBox(s);
			return;
		}
		
		if (returned <= 0)
		{
			char s[100];
			sprintf(s, "Error in the returned value: %d", returned);
			AfxMessageBox(s);
			return;
		}

		if (pFilename) 
		{
			FILE* file = fopen(pFilename, "w");
			if (file) 
			{
				spewWireFrameEPS(file, doSort, returned, pFeedbackBuffer, "rendereps");
			} 
			else 
			{
				printf("Could not open %s\n", pFilename);
			}
		} 
		else 
		{
			
			printBuffer(returned, pFeedbackBuffer);
		}

	
		wglMakeCurrent(NULL, NULL);

		// Cleanup
		string.ReleaseBuffer();
		delete [] pFeedbackBuffer;

	}


/*
	CDC dc;
    CPrintDialog printDlg(FALSE);

    if (printDlg.DoModal() == IDCANCEL)         // Get printer settings from user
        return;

    dc.Attach(printDlg.GetPrinterDC());         // Attach a printer DC
    dc.m_bPrinting = TRUE;

    CString strTitle;                           // Get the application title
    strTitle.LoadString(AFX_IDS_APP_TITLE);

    DOCINFO di;                                 // Initialise print document details
    ::ZeroMemory (&di, sizeof (DOCINFO));
    di.cbSize = sizeof (DOCINFO);
    di.lpszDocName = strTitle;
	
    BOOL bPrintingOK = dc.StartDoc(&di);        // Begin a new print job

    // Get the printing extents and store in the m_rectDraw field of a 
    // CPrintInfo object
    CPrintInfo Info;
    Info.m_rectDraw.SetRect(0, 0, dc.GetDeviceCaps(HORZRES), dc.GetDeviceCaps(VERTRES));

    dc.StartPage();                         // begin new page

	double curHeight, curWidth, newHeight, newWidth;
	double ratio;
	CRect rect;

	// Get current dimensions of CEdit
	GetClientRect(&rect);
	curHeight = rect.Height();
	curWidth  = rect.Width();

	// Maintain this ratio
	ratio = curHeight / curWidth;

	// Calculate new dimensions for the bound rect of graph on new device 
	newWidth = Info.m_rectDraw.Width();
	newHeight = ratio * newWidth;

//	m_edit.m_graphCtrl.m_boundRect.SetRect(0, 0, (int)newWidth, (int)newHeight);
//	m_edit.m_graphCtrl.Draw(&dc);
	
//	CDC* pDC = GetDC();

	// need to create render context here
	HGLRC hRC = wglCreateContext(dc.GetSafeHdc());

	// Useful in multidoc templates
	wglMakeCurrent(dc.GetSafeHdc(), hRC);

	// Render
	
	glEnable(GL_DEPTH_TEST);
		
	// Set background color to black
	glClearColor(0.f, 0.f, 0.f, 1.0f);
	
	// Set clear Z-Buffer value
	glClearDepth(1.0f);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	
	glEnable(GL_LINE_SMOOTH);
	glShadeModel(GL_SMOOTH); 
	glFrontFace(GL_CCW);
	
	// Create and enable a white directional light
	glLightfv(GL_LIGHT0, GL_DIFFUSE, m_diffuseLight0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, m_ambientLight0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, m_specularLight0);
	glLightfv(GL_LIGHT0, GL_POSITION, m_positionLight0);
	
	glLightfv(GL_LIGHT1, GL_DIFFUSE, m_diffuseLight1);
	glLightfv(GL_LIGHT1, GL_AMBIENT, m_ambientLight1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, m_specularLight1);
	glLightfv(GL_LIGHT1, GL_POSITION, m_positionLight1);
	
	glMaterialfv(GL_FRONT, GL_SPECULAR, m_materialSpecular);
	glMaterialfv(GL_FRONT, GL_EMISSION, m_materialEmission);
	glMaterialf(GL_FRONT, GL_SHININESS, m_shininess);
	
	glFogfv(GL_FOG_COLOR, m_fogColor);          // Define the fog colour 
	glFogf(GL_FOG_DENSITY, m_fogDensity);       // How dense 
	glFogi(GL_FOG_MODE, GL_LINEAR);             // exponential decay 
	glFogf(GL_FOG_START, m_near);                 // Where we start fogging 
	glFogf(GL_FOG_END, m_far);                   // end 
	glHint(GL_FOG_HINT, GL_NICEST);             // compute per vertex 
	if (m_bFogging == TRUE)
		glEnable(GL_FOG);                           
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	
	if (m_bUseTwoLightSources)
		glEnable(GL_LIGHT1);
	
	glPolygonMode(GL_FRONT,GL_FILL);
	glPolygonMode(GL_BACK,GL_FILL);

	DrawScene();

	// Double buffer
	SwapBuffers(dc.m_hDC);

	dc.EndPage();

    if (bPrintingOK)
        dc.EndDoc();                            // end a print job
    else
        dc.AbortDoc();                          // abort job.

    dc.Detach();      

	wglMakeCurrent(NULL, NULL);
*/
}

void CVisualizer_XView::OnFileSave() 
{
	// TODO: Add your command handler code here
	CFileDialog dlg(FALSE, 
					"txt", 
					NULL, 
					OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
					"State Files (*.txt)|*.txt|All Files (*.*)|*.*||",
					this);



	if (dlg.DoModal() == IDOK)
	{
		CVisualizer_XDoc* pDoc = GetDocument();

		CString fileName = dlg.GetPathName();
		FILE* fp = fopen(fileName, "w");
		
		fprintf(fp, "%g %g %g\n", m_background[0], m_background[1],	m_background[2]);
		
		fprintf(fp, "%g %g %g %g\n", m_ambientLight0[0], m_ambientLight0[1], m_ambientLight0[2], m_ambientLight0[3]);
		fprintf(fp, "%g %g %g %g\n", m_diffuseLight0[0], m_diffuseLight0[1], m_diffuseLight0[2], m_diffuseLight0[3]);
		fprintf(fp, "%g %g %g %g\n", m_specularLight0[0], m_specularLight0[1], m_specularLight0[2], m_specularLight0[3]);
		fprintf(fp, "%g %g %g %g\n", m_positionLight0[0], m_positionLight0[1], m_positionLight0[2], m_positionLight0[3]);
		
		fprintf(fp, "%g %g %g %g\n", m_ambientLight1[0], m_ambientLight1[1], m_ambientLight1[2], m_ambientLight1[3]);
		fprintf(fp, "%g %g %g %g\n", m_diffuseLight1[0], m_diffuseLight1[1], m_diffuseLight1[2], m_diffuseLight1[3]);
		fprintf(fp, "%g %g %g %g\n", m_specularLight1[0], m_specularLight1[1], m_specularLight1[2], m_specularLight1[3]);
		fprintf(fp, "%g %g %g %g\n", m_positionLight1[0], m_positionLight1[1], m_positionLight1[2], m_positionLight1[3]);
		
		fprintf(fp, "%g\n", m_shininess);
		fprintf(fp, "%g %g %g\n", m_xLightAngle, m_yLightAngle, m_zLightAngle);
		fprintf(fp, "%g %g %g\n", m_targetXangle, m_targetYangle, m_targetZangle);
		fprintf(fp, "%g %g %g\n", m_xModelAngle, m_yModelAngle, m_zModelAngle);
		fprintf(fp, "%g %g %g\n", m_xangle, m_yangle, m_zangle);
		
		fprintf(fp, "%g %g %g %g %g %g %g\n", m_left, m_right, m_top, m_bottom, m_translate, m_near, m_far);
		fprintf(fp, "%g %g\n", m_particleScale, m_displacement);
		fprintf(fp, "%g %g\n", m_scale, m_targetScale);
		
		fprintf(fp, "%g %g %g %d %g %g %d\n", pDoc->m_particleScalingStep, pDoc->m_particleTranslatingStep, m_rotatingStep, 
			m_nTranslatingDirection, m_fogDensity, m_viewportScale, m_nResolution);

		fprintf(fp, "%d\n", (m_bUseTwoLightSources == TRUE) ? 1 : 0);
		fprintf(fp, "%d\n", (m_bBlend == TRUE) ? 1 : 0);
		fprintf(fp, "%d\n", (m_bLightSrc == TRUE) ? 1 : 0);
		fprintf(fp, "%d\n", (m_bBoundingBox == TRUE) ? 1 : 0);
		fprintf(fp, "%d\n", (m_bPerspective == TRUE) ? 1 : 0);
		fprintf(fp, "%d\n", (m_bXRotate == TRUE) ? 1 : 0);
		fprintf(fp, "%d\n", (m_bYRotate == TRUE) ? 1 : 0);
		fprintf(fp, "%d\n", (m_bZRotate == TRUE) ? 1 : 0);
		fprintf(fp, "%d\n", (m_bDrawingObjects == TRUE) ? 1 : 0);
		fprintf(fp, "%d\n", (m_bFogging == TRUE) ? 1 : 0);
		
		fclose(fp);
	}
}

void CVisualizer_XView::OnFileLoad() 
{
	// TODO: Add your command handler code here
	CFileDialog dlg(TRUE, 
					"txt", 
					NULL, 
					OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
					"State Files (*.txt)|*.txt|All Files (*.*)|*.*||",
					this);



	if (dlg.DoModal() == IDOK)
	{
		CVisualizer_XDoc* pDoc = GetDocument();

		CString fileName = dlg.GetPathName();
		FILE* fp = fopen(fileName, "r");
		
		double a[4];
		fscanf(fp, "%lf %lf %lf\n", &a[0], &a[1], &a[2]);
		m_background[0] = a[0];
		m_background[1] = a[1];
		m_background[2] = a[2];
		
		fscanf(fp, "%lf %lf %lf %lf\n", &a[0], &a[1], &a[2], &a[3]);
		m_ambientLight0[0] = a[0];
		m_ambientLight0[1] = a[1];
		m_ambientLight0[2] = a[2];
		m_ambientLight0[3] = a[3];

		fscanf(fp, "%lf %lf %lf %lf\n", &a[0], &a[1], &a[2], &a[3]);
		m_diffuseLight0[0] = a[0];
		m_diffuseLight0[1] = a[1];
		m_diffuseLight0[2] = a[2];
		m_diffuseLight0[3] = a[3];

		fscanf(fp, "%lf %lf %lf %lf\n", &a[0], &a[1], &a[2], &a[3]);
		m_specularLight0[0] = a[0];
		m_specularLight0[1] = a[1];
		m_specularLight0[2] = a[2];
		m_specularLight0[3] = a[3];

		fscanf(fp, "%lf %lf %lf %lf\n", &a[0], &a[1], &a[2], &a[3]);
		m_positionLight0[0] = a[0];
		m_positionLight0[1] = a[1];
		m_positionLight0[2] = a[2];
		m_positionLight0[3] = a[3];
		
		fscanf(fp, "%lf %lf %lf %lf\n", &a[0], &a[1], &a[2], &a[3]);
		m_ambientLight1[0] = a[0];
		m_ambientLight1[1] = a[1];
		m_ambientLight1[2] = a[2];
		m_ambientLight1[3] = a[3];

		fscanf(fp, "%lf %lf %lf %lf\n", &a[0], &a[1], &a[2], &a[3]);
		m_diffuseLight1[0] = a[0];
		m_diffuseLight1[1] = a[1];
		m_diffuseLight1[2] = a[2];
		m_diffuseLight1[3] = a[3];

		fscanf(fp, "%lf %lf %lf %lf\n", &a[0], &a[1], &a[2], &a[3]);
		m_specularLight1[0] = a[0];
		m_specularLight1[1] = a[1];
		m_specularLight1[2] = a[2];
		m_specularLight1[3] = a[3];

		fscanf(fp, "%lf %lf %lf %lf\n", &a[0], &a[1], &a[2], &a[3]);
		m_positionLight1[0] = a[0];
		m_positionLight1[1] = a[1];
		m_positionLight1[2] = a[2];
		m_positionLight1[3] = a[3];

		
		fscanf(fp, "%lf\n", &m_shininess);
		fscanf(fp, "%lf %lf %lf\n", &m_xLightAngle, &m_yLightAngle, &m_zLightAngle);
		fscanf(fp, "%lf %lf %lf\n", &m_targetXangle, &m_targetYangle, &m_targetZangle);
		fscanf(fp, "%lf %lf %lf\n", &m_xModelAngle, &m_yModelAngle, &m_zModelAngle);
		fscanf(fp, "%lf %lf %lf\n", &m_xangle, &m_yangle, &m_zangle);
		
		fscanf(fp, "%lf %lf %lf %lf %lf %lf %lf\n", &m_left, &m_right, &m_top, &m_bottom, &m_translate, &m_near, &m_far);
		fscanf(fp, "%lf %lf\n", &m_particleScale, &m_displacement);
		fscanf(fp, "%lf %lf\n", &m_scale, &m_targetScale);
			fscanf(fp, "%lf %lf %lf %d %lf %lf %d\n", &pDoc->m_particleScalingStep, &pDoc->m_particleTranslatingStep, &m_rotatingStep, 
			&m_nTranslatingDirection, &m_fogDensity, &m_viewportScale, &m_nResolution);
		

		int temp;
		fscanf(fp, "%d\n", &temp);
		if (temp == 1) m_bUseTwoLightSources = TRUE;
		else m_bUseTwoLightSources = FALSE;

		fscanf(fp, "%d\n", &temp);
		if (temp == 1) m_bBlend = TRUE;
		else m_bBlend = FALSE;

		fscanf(fp, "%d\n", &temp);
		if (temp == 1) m_bLightSrc = TRUE;
		else m_bLightSrc = FALSE;

		fscanf(fp, "%d\n", &temp);
		if (temp == 1) m_bBoundingBox = TRUE;
		else m_bBoundingBox = FALSE;

		fscanf(fp, "%d\n", &temp);
		if (temp == 1) m_bPerspective = TRUE;
		else m_bPerspective = FALSE;

		fscanf(fp, "%d\n", &temp);
		if (temp == 1) m_bXRotate = TRUE;
		else m_bXRotate = FALSE;

		fscanf(fp, "%d\n", &temp);
		if (temp == 1) m_bYRotate = TRUE;
		else m_bYRotate = FALSE;

		fscanf(fp, "%d\n", &temp);
		if (temp == 1) m_bZRotate = TRUE;
		else m_bZRotate = FALSE;

		fscanf(fp, "%d\n", &temp);
		if (temp == 1) m_bDrawingObjects = TRUE;
		else m_bDrawingObjects = FALSE;

		fscanf(fp, "%d\n", &temp);
		if (temp == 1) m_bFogging = TRUE;
		else m_bFogging = FALSE;
		
		fclose(fp);

		Invalidate();
	}
}

/////////////////////////////////////////////////////////////

void CVisualizer_XView::OnBod() 
{
	// TODO: Add your command handler code here
	m_bDrawBOD = !m_bDrawBOD;
	Invalidate();
}

void CVisualizer_XView::ComputeBOD()
{
	m_bDrawBOD = TRUE;

	int i, j, nPoints;
	double x0, y0, z0, x, y, z, dx, dy, dz, dist;

	vector<CPosition> position;
	vector<CPosition*> noscale_position;
	m_bodData.clear();
	for (i=0; i<m_nParticles; i++)
	{
		if (IsVisualized(i) == FALSE)
			continue;

		for (j=0; j<m_particleArray[i]->m_positionArray.size(); j++)
		{
			CPosition p = m_particleArray[i]->m_positionArray[j];

			if (p.GetType() == m_nChosenType || m_nChosenType == -1)
			{
				noscale_position.push_back(&m_particleArray[i]->m_positionArray[j]);

				p[0] = p[0] * m_Lx / m_boxSizex;
				p[1] = p[1] * m_Ly / m_boxSizey;
				p[2] = p[2] * m_Lz / m_boxSizez;
				position.push_back(p);
			}
		}
	}

	nPoints = position.size();
	
	m_bondArray.clear();
	
	if (nPoints == 0)
		return;

	int nTotalPoints = 0;
	CPosition *pos1, *pos2;
	for (i=0; i<nPoints-1; i++)
	{
		pos1 = noscale_position[i];

		x0 = position[i][0];
		y0 = position[i][1];
		z0 = position[i][2];
		
		for (j=i+1; j<nPoints; j++)
		{
		//	if (i == j) continue;

			pos2 = noscale_position[j];

			x = position[j][0];
			y = position[j][1];
			z = position[j][2];
			dx = x - x0;
			dx -= m_Lx * anint(dx / m_Lx);
			dy = y - y0;
			dy -= m_Ly * anint(dy / m_Ly);
			dz = z - z0;
			dz -= m_Lz * anint(dz / m_Lz);
			dist = sqrt(dx * dx + dy * dy + dz * dz);
			
			if (dist >= m_cut_in && dist <= m_cut_out)
			{
				CBondObject* pObject = new CBondObject();
				pObject->SetBox(m_boxSizex, m_boxSizey, m_boxSizez);
				pObject->SetPosition(pos1, pos2);
				m_bondArray.push_back(pObject);
			
				if (nTotalPoints < m_nMaxPoints)
				{
					dx /= dist;
					dy /= dist;
					dz /= dist;
					
					CPosition p = position[j];
					p[0] = dx;
					p[1] = dy;
					p[2] = dz;
					m_bodData.push_back(p);
				}

				nTotalPoints++;	
				if (nTotalPoints == m_nMaxPoints)
					break;
			}
		}
	}


	m_coordinationNumber = 2.0 * (double)nTotalPoints / (double)nPoints;

	Invalidate();
}

void CVisualizer_XView::OnToolsBod() 
{
	// TODO: Add your command handler code here
	if (m_pBODDialog == NULL)
	{
		m_pBODDialog = new CBODDialog(this);
		
		m_pBODDialog->m_cut_in = m_cut_in;
		m_pBODDialog->m_cut_out = m_cut_out;
		m_pBODDialog->m_nType = m_nChosenType+1;
		m_pBODDialog->m_nMaxPoints = m_nMaxPoints;
		m_pBODDialog->m_nWindowSize = m_nBODWindowSize;
		m_pBODDialog->m_bShowBonds = m_bDrawingBonds;

		m_pBODDialog->Create();
	}
	else m_pBODDialog->SetActiveWindow();
}

void CVisualizer_XView::OnUpdateToolsBod(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_nParticles > 0);
}

////////////////////////////////////////////////////////////////////

void CVisualizer_XView::OnDraworigin() 
{
	// TODO: Add your command handler code here
	m_bDrawOrigin = !m_bDrawOrigin;
	Invalidate();
}

void CVisualizer_XView::OnUpdateDraworigin(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_bDrawOrigin);
}

void CVisualizer_XView::OnUpdateBod(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_bDrawBOD);
}

void CVisualizer_XView::OnHelpUsersguide() 
{
	// TODO: Add your command handler code here
	CHelpDialog dlg;
	dlg.DoModal();
}

/////////////////////////////////////////////////////////////////////

void CVisualizer_XView::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	GetCursorPos(&point);
	
	CMenu *menu, *popup;
	
	menu = new CMenu();
	menu->LoadMenu(IDR_MENU_CONTEXT);
	
	popup = menu->GetSubMenu(0);		
	popup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);	

	delete menu;

	CGLEnabledView::OnRButtonUp(nFlags, point);
}

///////////////////////////////////////////////////////////////////

void CVisualizer_XView::PickParticle(CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
    GLuint* selectBuf = new GLuint[m_nParticles];
    GLint hits;
    GLint viewport[4];

	wglMakeCurrent(m_pCDC->GetSafeHdc(), m_hRC);

	int size, centerx, centery, cx, cy;
	CRect rect;
	GetClientRect(&rect);
	cx = rect.Width();
	cy = rect.Height();
	size = (cx > cy) ? cx : cy;
	centerx = cx / 2;
	centery = cy / 2;
			
	glViewport(centerx * m_viewportScale - size  * m_viewportScale / 2, centery * m_viewportScale - size  * m_viewportScale / 2, 
			size * m_viewportScale, size * m_viewportScale);
	
    glGetIntegerv(GL_VIEWPORT, viewport);
    glSelectBuffer(m_nParticles, selectBuf);
	
	glRenderMode(GL_SELECT);				// Enter the SELECT render mode
    glInitNames();
    glPushName(0);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

	GLdouble px, py;
	px = point.x;
	py = (float)viewport[1] + ((float)viewport[3] + (float)cy)/2.0 - (float)point.y;
    gluPickMatrix(px, py, 10.0, 10.0, viewport);
	
	if (m_bPerspective == TRUE)
		glFrustum(m_left, m_right, m_bottom, m_right, m_near, m_far);
	else
		glOrtho(m_left, m_right, m_bottom, m_right, m_near, m_far);
		
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	// Move the model -1.0 units along the z-axis
	glTranslatef(0.0, 0.0, m_translate);
	glRotatef(m_xangle, 1.0, 0.0, 0.0);
	glRotatef(m_yangle, 0.0, 1.0, 0.0);
	glRotatef(m_zangle, 0.0, 0.0, 1.0);
		
	glRotatef(m_xModelAngle, 1.0, 0.0, 0.0);
	glRotatef(m_yModelAngle, 0.0, 1.0, 0.0);
	glRotatef(m_zModelAngle, 0.0, 0.0, 1.0);
		
	DrawParticles(GL_SELECT);
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glFlush();

	glMatrixMode(GL_MODELVIEW);
    hits = glRenderMode(GL_RENDER);
	
 	if (hits > 0)
	{
		int i;
		for (i=0; i<m_nParticles; i++)
			m_particleArray[i]->m_bDrawn = FALSE;

		int n = 0;
		double minz = selectBuf[1];

		for(i=1; i<hits; i++)
		{
			if (selectBuf[1+i*4] < minz) 
			{
				n = i;
				minz = selectBuf[1+i*4];
			}
		}

		m_particleArray[selectBuf[3+n*4]]->m_bDrawn = TRUE;

		Invalidate();
	}

	wglMakeCurrent(NULL, NULL);

	delete [] selectBuf;
}

void CVisualizer_XView::OnPickingMode() 
{
	// TODO: Add your command handler code here
	m_bPickingMode = !m_bPickingMode;
}

void CVisualizer_XView::OnUpdatePickingMode(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_bPickingMode);
//	pCmdUI->Enable(m_nParticles > 0);
}

void CVisualizer_XView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (m_bPickingMode == FALSE)
		return;

	PickParticle(point);

	CGLEnabledView::OnLButtonDblClk(nFlags, point);
}

void CVisualizer_XView::OnFileWritetopos() 
{
	// TODO: Add your command handler code here
	// TODO: Add your command handler code here
	CFileDialog dlg(FALSE, 
					"txt", 
					NULL, 
					OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
					"POS Files (*.pos)|*.pos|All Files (*.*)|*.*||",
					this);



	if (dlg.DoModal() == IDOK)
	{
		CString fileName = dlg.GetPathName();
			
		std::ofstream ofs;
		ofs.open(fileName);

		int i, j, count=0;
	
		int nNumVisualizedBeads = 0;
		for (i=0; i<m_nParticles; i++)
		{
			if (IsVisualized(i) == TRUE)
			{
				count++;
				
				CParticle* pParticle = m_particleArray[i];
				for (j=0; j<pParticle->m_positionArray.size(); j++)
				{
					int nType = pParticle->m_positionArray[j].GetType();
					if (m_nHiddenType[nType] == FALSE)
						nNumVisualizedBeads++;
				}
			}
			
		}
		
		ofs << "box ";
		ofs << m_Lx << " " << m_Ly << " " << m_Lz << std::endl;
		ofs << "shape \"sphere X ff0000 1.0\" \n";

		for (i=0; i<m_nParticles; i++)
		{
			if (IsVisualized(i) == TRUE)
			{
				m_particleArray[i]->BoxScaling(m_boxSizex, m_boxSizey, m_boxSizez, m_Lx, m_Ly, m_Lz);
				
				int nType;
				for (j=0; j<m_particleArray[i]->m_positionArray.size(); j++)
				{
					nType = m_particleArray[i]->m_positionArray[j].GetType();
					if (m_nHiddenType[nType] == FALSE)
					{
						ofs << (m_particleArray[i]->m_positionArray[j])[0] << "\t";
						ofs << (m_particleArray[i]->m_positionArray[j])[1] << "\t";
						ofs << (m_particleArray[i]->m_positionArray[j])[2] << "\n";
					}
				}
				
				m_particleArray[i]->BoxScaling(m_Lx, m_Ly, m_Lz, m_boxSizex, m_boxSizey, m_boxSizez);
			}
		}
	
		ofs.close();
	}
}

/////////////////////////////////////////////////////////////////////////

void CVisualizer_XView::ComputeDiffraction(int nFFTSize, double peakwidth, double intensity, double zoom)
{
	int i, j;
	if (m_nFFTSize != nFFTSize)
	{
		if (m_diffData) 
		{
			for (i=0; i<m_nFFTSize; i++)
				delete [] m_diffData[i];
			delete [] m_diffData;
		}
		
		m_diffData = NULL;
		m_nFFTSize = nFFTSize;
	}

	if (m_diffData == NULL)	
	{
		m_diffData = new double* [m_nFFTSize];
		for (i=0; i<m_nFFTSize; i++)
			m_diffData[i] = new double [m_nFFTSize];
	}

	FFT fft(m_nFFTSize);
	
	for (i=0; i<m_nFFTSize; i++)
		for (j=0; j<m_nFFTSize; j++)
			m_diffData[i][j] = 0.0;

	// calculate the 2x2 shear matrix, which is formed by those two box vectors
	// that span the largest area when projected on the xy-plane
	double Lx = m_Lx;
	double Ly = m_Ly;
	double Lz = m_Lz;
	CMatrix box(Lx, 0.0, 0.0, 0.0, Ly, 0.0, 0.0, 0.0, Lz);
	
	double PI = 4.0 * atan(1.0);
	CMatrix rot, rotx, roty, rotz;
	rotx[1][1] = cos(m_xangle * PI / 180.0);
	rotx[1][2] = -sin(m_xangle * PI / 180.0);
	rotx[2][1] = -rotx[1][2];
	rotx[2][2] = rotx[1][1];

	roty[0][0] = cos(m_yangle * PI / 180.0);
	roty[0][2] = sin(m_yangle * PI / 180.0);
	roty[2][0] = -roty[0][2];
	roty[2][2] = roty[0][0];

	rotz[0][0] = cos(m_zangle * PI / 180.0);
	rotz[0][1] = -sin(m_zangle * PI / 180.0);
	rotz[1][0] = -roty[0][1];
	rotz[1][1] = roty[0][0];

	rot = rotx * roty * rotz;

	CMatrix sh = rot * box;
	double n01 = fabs(sh[0][0] * sh[1][1] - sh[0][1] * sh[1][0]);
	double n20 = fabs(sh[0][2] * sh[1][0] - sh[0][0] * sh[1][2]);
	double n12 = fabs(sh[0][1] * sh[1][2] - sh[0][2] * sh[1][1]);
	double width;

	CMatrix shearMatrix;
	if (n12 > n01 && n12 > n20) 
	{
		shearMatrix[0][0] = sh[0][1];
		shearMatrix[0][1] = sh[0][2];
		shearMatrix[1][0] = sh[1][1];
		shearMatrix[1][1] = sh[1][2];
		width = sh[2][0];
	} 
	else if (n20 > n01 && n20 > n12) 
	{
		shearMatrix[0][0] = sh[0][2];
		shearMatrix[0][1] = sh[0][0];
		shearMatrix[1][0] = sh[1][2];
		shearMatrix[1][1] = sh[1][0];
		width = sh[2][1];
	} 
	else 
	{
		shearMatrix[0][0] = sh[0][0];
		shearMatrix[0][1] = sh[0][1];
		shearMatrix[1][0] = sh[1][0];
		shearMatrix[1][1] = sh[1][1];
		width = sh[2][2];
	}
	
	// set up shearMatrix to map (roughly) on a unit square
	// maximum box dimension
	double scale = box.maximumBoxEdge();
	CMatrix origShear = shearMatrix * (1.0 / scale);
	if (fabs(shearMatrix.det()) < 1e-6) 
		return;
	
	shearMatrix = shearMatrix.inv();
	
	// position the scatterers (intensity)
	double EXPTABLECUTOFF = 20.0;
	int r = (int)sqrt(EXPTABLECUTOFF * peakwidth / 2.0) - 1;

	origShear = origShear * (1.0 / sqrt(peakwidth));
	
	// shearMatrix maps (roughly) on a square of size "size"
	shearMatrix = shearMatrix * m_nFFTSize;

	CVector p;
	int ncount = 0;
	for (i=0; i<m_nParticles; i++) 
	{
		if (IsVisualized(i) == FALSE)
			continue;

		for (j=0; j<m_particleArray[i]->m_positionArray.size(); j++)
		{
			int nType = m_particleArray[i]->m_positionArray[j].GetType();
			if (m_nHiddenType[nType] == TRUE)
				continue;

			double xi = m_particleArray[i]->m_positionArray[j][0] / m_boxSizex * Lx;
			double yi = m_particleArray[i]->m_positionArray[j][1] / m_boxSizey * Ly;
			double zi = m_particleArray[i]->m_positionArray[j][2] / m_boxSizez * Lz;
			
			// map the position of the shapes on the square [-size/2, size/2)^2
			int bound = 1;
			for (int i0 = -bound; i0 <= bound; i0++)
				for (int i1 = -bound; i1 <= bound; i1++)
					for (int i2 = -bound; i2 <= bound; i2++) 
					{
						
						p[0] = xi + box[0][0]*i0 + box[0][1]*i1 + box[0][2]*i2;
						p[1] = yi + box[1][0]*i0 + box[1][1]*i1 + box[1][2]*i2;
						p[2] = zi + box[2][0]*i0 + box[2][1]*i1 + box[2][2]*i2;
						
						p = rot * p;
						double x = shearMatrix[0][0] * p[0] + shearMatrix[0][1] * p[1];
						double y = shearMatrix[1][0] * p[0] + shearMatrix[1][1] * p[1];
						
						// fill in the particle as a Gaussian (peakwidth)
						int xr = (int)x;
						int yr = (int)y;
						for (int yy = yr - r; yy <= yr + r; yy++) 
						{
							for (int xx = xr - r ; xx <= xr + r; xx++) 
							{
								// guaranteed to be in a square [0, size)^2
								int xxx = xx % m_nFFTSize; 
								if (xxx < 0) 
									xxx += m_nFFTSize;
								
								int yyy = yy % m_nFFTSize; 
								if (yyy < 0) 
									yyy += m_nFFTSize;
								
								double dx = origShear[0][0]*(xx-x) + origShear[0][1]*(yy-y);
								double dy = origShear[1][0]*(xx-x) + origShear[1][1]*(yy-y);
								m_diffData[yyy][xxx] += fft.exp_lookup(dx * dx + dy * dy);
							}
						}
					}

			ncount++;
		}
	}

	double preFactor = fabs(175.0 / peakwidth / sqrt((double)ncount) 
		* sqrt(fabs(origShear.det())) * m_nFFTSize);

	fft.diffraction2D(m_diffData);
	shearMatrix = shearMatrix.transpose();

	double intensitySquare = intensity * intensity;

	for (int y = 0; y < m_nFFTSize; y++) 
		for (int x = 0; x < m_nFFTSize; x++) 
		{
			m_diffData[y][x] *= (intensitySquare * preFactor);
		}

}

void CVisualizer_XView::OnToolsDiffraction() 
{
	// TODO: Add your command handler code here
	if (m_pDiffractionDialog == NULL)
	{
		m_pDiffractionDialog = new CDiffractionDialog(this);
		m_pDiffractionDialog->Create();
	
	}
	else m_pDiffractionDialog->SetActiveWindow();
}

void CVisualizer_XView::OnUpdateToolsDiffraction(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_nParticles > 0);	
}

void CVisualizer_XView::OnToolsReplicate() 
{
	// TODO: Add your command handler code here
	CReplicateDialog dlg;
	if (dlg.DoModal() == IDOK)
	{
		double shiftx = dlg.m_shiftx;
		double shifty = dlg.m_shifty;
		double shiftz = dlg.m_shiftz;
		int numCopies = dlg.m_numCopies;
		int nRepX = dlg.m_nRepX;
		int nRepY = dlg.m_nRepY;
		int nRepZ = dlg.m_nRepZ;
		int nReps = nRepX * nRepY * nRepZ;

		if (numCopies == 0 )
			return;


		int i, j, n;
		int nAddedParticles = 0;
		m_Lx += shiftx; 
		m_Ly += shifty; 
		m_Lz += shiftz; 
		double scalex = m_boxSizex / m_Lx;
		double scaley = m_boxSizey / m_Ly;
		double scalez = m_boxSizez / m_Lz;
		for (n=1; n<=numCopies; n++)
		{
			for (i=0; i<m_nParticles; i++)
			{
			//	if (IsVisualized(i) == FALSE)
			//		continue;

				CParticle* pParticle = new CParticle(*m_particleArray[i]);
			
				for (j=0; j<m_particleArray[i]->m_positionArray.size(); j++)
				{
					CPosition p = pParticle->m_positionArray[j];
					p[0] = p[0] + n * shiftx * scalex;
					p[1] = p[1] + n * shifty * scaley;
					p[2] = p[2] + n * shiftz * scalez;
					pParticle->m_positionArray[j] = p;
				}

				m_particleArray.push_back(pParticle);
				nAddedParticles++;
			}
		}
	
		
		double L = m_Lx;
		if (L < m_Ly)
			L = m_Ly;
		if (L < m_Lz)
			L = m_Lz;
		
		m_boxSizex = 0.75 * m_Lx / L;
		m_boxSizey = 0.75 * m_Ly / L;
		m_boxSizez = 0.75 * m_Lz / L;
		
	//	m_nParticles = m_particleArray.size();
	//	for (i=0; i<m_nParticles; i++)
	//		((CSphere*)m_particleArray[i])->BoxScaling(m_Lx, m_Ly, m_Lz, m_boxSizex, m_boxSizey, m_boxSizez);
	
		CVisualizer_XDoc* pDoc = GetDocument();
		pDoc->m_particleScale = 0.5 / m_Lx * m_boxSizex;
		pDoc->m_objectScale = pDoc->m_particleScale;
		
		m_nParticleStartIndex = 0;
		
		
		m_region.centerx = 0.0;
		m_region.centery = 0.0;
		m_region.centerz = 0.0;
		m_region.type = 0; // box
		m_region.xlo = -m_boxSizex/2.0;
		m_region.xhi = m_boxSizex/2.0;
		m_region.ylo = -m_boxSizey/2.0;
		m_region.yhi = m_boxSizey/2.0;
		m_region.zlo = -m_boxSizez/2.0;
		m_region.zhi = m_boxSizez/2.0;
		m_region.box_scale = 0.75 / L;
		m_region.radius_inner = 0.0;
		m_region.radius_outer = L * m_region.box_scale;
		m_region.m_bOutside = FALSE;

		m_nParticleEndIndex += nAddedParticles;

		Invalidate();
	}
}

void CVisualizer_XView::OnFileWritetopov() 
{
	// TODO: Add your command handler code here
	int i;
	
	std::ofstream ofs("snapshot.pov");

	ofs << "global_settings { assumed_gamma 2.2 }" << std::endl;

	ofs << "\ncamera\n{" << std::endl;
	ofs << "\tlocation  <25, 25, -15>" << std::endl;
	ofs << "\tlook_at   <0, 0, 0>" << std::endl;
	ofs << "\tangle 58\n}" << std::endl;

	ofs << "light_source { < 20, 30, -25> color red 0.6 green 0.6 blue 0.6 }" << std::endl;

	ofs << "\nbackground { < 1, 1, 1> }\n"; 

	for (i=0; i<m_nParticles; i++)
		m_particleArray[i]->DrawPOV(ofs, m_materialAmbient, m_materialDiffuse, m_nHiddenType, m_nResolution);
		
	
	ofs.close();

}



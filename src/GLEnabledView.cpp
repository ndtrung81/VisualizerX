/*****************************************************
Copyright Notice & Disclaimer

Copyright © Alessandro Falappa

Permission to use, copy, modify, and distribute this software
and its documentation for any purpose is hereby granted without
fee, provided that the above copyright notice, author statement
appear in all copies of this software and related documentation.

If you make enhancement or you discover bugs, please let me
know

THE SOFTWARE IS PROVIDED "AS-IS" AND WITHOUT WARRANTY OF
ANY KIND, EXPRESS, IMPLIED OR OTHERWISE, INCLUDING WITHOUT
LIMITATION, ANY WARRANTY OF MERCHANTABILITY OR FITNESS FOR A
PARTICULAR PURPOSE.

IN NO EVENT SHALL ALESSANDRO FALAPPA BE LIABLE FOR ANY
SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY
KIND, OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA
OR PROFITS, WHETHER OR NOT ADVISED OF THE POSSIBILITY OF DAMAGE,
AND ON ANY THEORY OF LIABILITY, ARISING OUT OF OR IN CONNECTION
WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

///////////////////////////////////////////////
History

v 1.0: first version
v 1.1: added CGLDispList helper class
	   changed previous disp list service in StockDispList
v 1.2: added CGLTesselator helper class
	   added GLCommands pair
	   added CGLQuadric wrapper class

******************************************************/
// CGLEnabledView.cpp : implementation file of version 1.2
//

#include "stdafx.h"
/*
 NOTE ABOUT LIBRARIES INCLUSION:
 - Remember to include the appropriate libraries in the link phase
   (look at Project Settings under the Link tab)
 - If you were lucky enough to get SGI's implementation (at present it's
   not availabl nor supported) you can play with it also, just include
   that libraries. SGI's version is faster if you have no GL acceleration
   and if you own a MMX processor
 - These includes below can be moved to stdafx.h to speed up compilation
*/

#include "GLEnabledView.h"
#include <math.h>
#include <assert.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MAX_LISTS 20

// used to identify a MCD video driver (partial OGL acceleration)
#define INSTALLABLE_DRIVER_TYPE_MASK  (PFD_GENERIC_ACCELERATED|PFD_GENERIC_FORMAT)

/////////////////////////////////////////////////////////////////////////////
// Global Functions/variables
// These functions are used by CGLTesselator class

struct GarbListItem
{
	GLdouble*		pvert;
	GarbListItem*	next;
};

GarbListItem* m_garbagelist = NULL;

void AddGarbage(GLdouble * ptr)
{
	ASSERT(ptr!=NULL);
	
	// Allocate mem for new list item
	GarbListItem* temp = new GarbListItem;
	
	// Store pointer
	temp->pvert=ptr;

	// Add at head of list
	temp->next = m_garbagelist;
	m_garbagelist = temp;
}

void DeleteGarbage()
{
	if(m_garbagelist!=NULL)
	{
		GarbListItem* punt = m_garbagelist;
		GarbListItem* temp = m_garbagelist;

		// Scan the list
		while(punt!=NULL)
		{
			// Delete vertex
			delete [] punt->pvert;
			punt=punt->next;

			// Delete list item
			delete temp;
			temp = punt;
		};

		m_garbagelist = NULL;
	};
}

void CALLBACK BeginCallback(GLenum type)
{
	// Issue corresponding GL call
	glBegin(type);
}

void CALLBACK ErrorCallback(GLenum errorCode)
{
	const GLubyte *estring;
	CString mexstr;

	// Get the error descritption from OGL
	estring = gluErrorString(errorCode);

	// Prepare and show a message box
	mexstr.Format("Tessellation/Quadric Error: %s\n", estring);
	AfxMessageBox(mexstr, MB_OK | MB_ICONEXCLAMATION);

	// Replicate mex to debug trace
	TRACE("Tessellation Error: %s\n", estring);
}

void CALLBACK EndCallback()
{
	// Issue corresponding GL call
	glEnd();
}

void CALLBACK VertexCallback(GLvoid *vertex)
{
	// Issue corresponding GL call (double is used to get max precision)
	glVertex3dv((const double *)vertex);
}

void CALLBACK CombineCallback(GLdouble coords[3], GLdouble *data[4], GLfloat weight[4], GLdouble **dataOut )
{
	// Allocate memory for a new vertex
	GLdouble *vertex;
	vertex = new GLdouble[3];

	// Store reported vertex
	vertex[0] = coords[0];
	vertex[1] = coords[1];
	vertex[2] = coords[2];

	// Return vertex to OGL
	*dataOut = vertex;

	// Add vertex pointer to garbage collection routines
	AddGarbage(vertex);
}

/////////////////////////////////////////////////////////////////////////////
// CGLEnabledView

IMPLEMENT_DYNCREATE(CGLEnabledView, CView)

CGLEnabledView::CGLEnabledView(): m_dAspectRatio(1.0), m_bInsideDispList(FALSE), m_bExternDispListCall(FALSE), m_bExternGLCall(FALSE)
{
	// Define a default cursor
	m_hMouseCursor = AfxGetApp()->LoadStandardCursor(IDC_ARROW);

	// Set the disp list vector to all zeros
	for (int c=0; c<MAX_LISTS; c++) 
		m_DispListVector[c] = 0;
}

CGLEnabledView::~CGLEnabledView()
{
}


BEGIN_MESSAGE_MAP(CGLEnabledView, CView)
	//{{AFX_MSG_MAP(CGLEnabledView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_SETCURSOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGLEnabledView drawing

void CGLEnabledView::OnDraw(CDC* pDC)
{
	// Prepare a semaphore
	static BOOL 	bBusy = FALSE;

	// Use the semaphore to enter this critic section
	if	(bBusy) 
		return;
	
	bBusy = TRUE;

	// Specify the target DeviceContext of the subsequent OGL calls
	wglMakeCurrent(m_pCDC->GetSafeHdc(), m_hRC);

	// Clear background
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Call the virtual drawing procedure (to be overridden by user)
	OnDrawGL();

	// Execute OGL commands (flush the OGL graphical pipeline)
	glFinish();

	// If double buffering is used it's time to swap the buffers
	SwapBuffers(m_pCDC->GetSafeHdc());
	
	// Turn the semaphore "green"
	bBusy = FALSE;

	// Free the target DeviceContext (window)
    wglMakeCurrent(NULL, NULL);
}

void CGLEnabledView::OnDrawGL()
{
	// Draw carthesian axes
	glBegin(GL_LINES);
		// red x axis
		glColor3f(1.f,0.f,0.f);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(1.0f,0.0f,0.0f);
		glVertex3f(1.0f,0.0f,0.0f);
		glVertex3f(0.9f,0.1f,0.0f);
		glVertex3f(1.0f,0.0f,0.0f);
		glVertex3f(0.9f,-0.1f,0.0f);
		// green y axis
		glColor3f(0.f,1.f,0.f);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(0.0f,1.0f,0.0f);
		glVertex3f(0.0f,1.0f,0.0f);
		glVertex3f(0.1f,0.9f,0.0f);
		glVertex3f(0.0f,1.0f,0.0f);
		glVertex3f(-0.1f,0.9f,0.0f);
		// blue z axis
		glColor3f(0.f,0.f,1.f);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(0.0f,0.0f,1.0f);
		glVertex3f(0.0f,0.0f,1.0f);
		glVertex3f(0.0f,0.1f,0.9f);
		glVertex3f(0.0f,0.0f,1.0f);
		glVertex3f(0.0f,-0.1f,0.9f);
	glEnd();
}

/////////////////////////////////////////////////////////////////////////////
// CGLEnabledView diagnostics

#ifdef _DEBUG
void CGLEnabledView::AssertValid() const
{
	CView::AssertValid();
}

void CGLEnabledView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
	
	// Dump some infos
	CString str;
	GetWindowText(str);
	afxDump << "\nView Parameters\n\tClient Rectangle :"
			<< m_ClientRect
		    << "\n\tAspect Ratio :" 
			<< m_dAspectRatio << "\n";
	
	afxDump << "\nWindowTitle :"
		    << str
			<< "\n";
}
#endif //_DEBUG

/////////////////////////////////////////////////////////
// CGLEnabledView Constants

// these are used to construct an equilibrated 256 color palette
static unsigned char _threeto8[8] = 
{
	0, 0111>>1, 0222>>1, 0333>>1, 0444>>1, 0555>>1, 0666>>1, 0377
};

static unsigned char _twoto8[4] = 
{
	0, 0x55, 0xaa, 0xff
};

static unsigned char _oneto8[2] = 
{
	0, 255
};

static int defaultOverride[13] = 
{
	0, 3, 24, 27, 64, 67, 88, 173, 181, 236, 247, 164, 91
};

// Windows Default Palette
static PALETTEENTRY defaultPalEntry[20] = 
{
	{ 0,   0,   0,    0 },
	{ 0x80,0,   0,    0 },
	{ 0,   0x80,0,    0 },
	{ 0x80,0x80,0,    0 },
	{ 0,   0,   0x80, 0 },
	{ 0x80,0,   0x80, 0 },
	{ 0,   0x80,0x80, 0 },
	{ 0xC0,0xC0,0xC0, 0 },

	{ 192, 220, 192,  0 },
	{ 166, 202, 240,  0 },
	{ 255, 251, 240,  0 },
	{ 160, 160, 164,  0 },

	{ 0x80,0x80,0x80, 0 },
	{ 0xFF,0,   0,    0 },
	{ 0,   0xFF,0,    0 },
	{ 0xFF,0xFF,0,    0 },
	{ 0,   0,   0xFF, 0 },
	{ 0xFF,0,   0xFF, 0 },
	{ 0,   0xFF,0xFF, 0 },
	{ 0xFF,0xFF,0xFF, 0 }
};

/////////////////////////////////////////////////////////////////////////////
// CGLEnabledView initialization and palette helpers

BOOL CGLEnabledView::bSetupPixelFormat()
{
// define default desired video mode (pixel format)
	static PIXELFORMATDESCRIPTOR pfd = 
	{
        sizeof(PIXELFORMATDESCRIPTOR),	// size of this pfd
        1,								// version number
        PFD_DRAW_TO_WINDOW |			// support window
        PFD_SUPPORT_OPENGL |			// support OpenGL
        PFD_DOUBLEBUFFER,				// double buffered
        PFD_TYPE_RGBA,                  // RGBA type
        24,                             // 24-bit color depth
        0, 0, 0, 0, 0, 0,               // color bits ignored
        0,                              // no alpha buffer
        0,                              // shift bit ignored
        0,                              // no accumulation buffer
        0, 0, 0, 0,                     // accum bits ignored
        16,                             // 32-bit z-buffer
        0,                              // no stencil buffer
        0,                              // no auxiliary buffer
        PFD_MAIN_PLANE,                 // main layer
        0,                              // reserved
        0, 0, 0                         // layer masks ignored
    };

	// Let the user change some parameters if he wants
	BOOL			bDoublBuf;
	ColorsNumber	cnum;
	ZAccuracy		zdepth;
	VideoMode(cnum,zdepth,bDoublBuf);

	//Set the changes
	if (bDoublBuf) 
		pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL |PFD_DOUBLEBUFFER;
	else 
		pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL;
	
	switch(cnum)
	{
	case INDEXED:	
		pfd.cColorBits = 8;
	case THOUSANDS: 
		pfd.cColorBits = 16;
	case MILLIONS:	
		pfd.cColorBits = 24;
	case MILLIONS_WITH_TRANSPARENCY: 
		pfd.cColorBits = 32;
	};
	switch(zdepth)
	{
	case NORMAL: 
		pfd.cDepthBits = 16;
	case ACCURATE: 
		pfd.cDepthBits = 32;
	};

	// Ask the system for such video mode
    ASSERT(m_pCDC != NULL);
    
	int pixelFormat;
	if ((pixelFormat = ChoosePixelFormat(m_pCDC->GetSafeHdc(), &pfd)) == 0)
    {
        AfxMessageBox("ChoosePixelFormat failed");
        return FALSE;
    }

	// Try to set this video mode    
	if (SetPixelFormat(m_pCDC->GetSafeHdc(), pixelFormat, &pfd) == FALSE)
    {
		// The requested video mode is not available so get a default one
        pixelFormat = 1;	
		if (DescribePixelFormat(m_pCDC->GetSafeHdc(), pixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pfd) == 0)
		{
			// Neither the requested nor the default are available: fail
			AfxMessageBox("SetPixelFormat failed (no OpenGL compatible video mode)");
			return FALSE;
		}
    }

    return TRUE;
}

void CGLEnabledView::CreateRGBPalette()
{
    PIXELFORMATDESCRIPTOR pfd;
    LOGPALETTE *pPal;
    int n, i;

	// Get the initially choosen video mode
	n = ::GetPixelFormat(m_pCDC->GetSafeHdc());
    ::DescribePixelFormat(m_pCDC->GetSafeHdc(), n, sizeof(pfd), &pfd);

	// If is an indexed one...
    if (pfd.dwFlags & PFD_NEED_PALETTE)
    {
		// Construct an equilibrated palette (3 red bits, 3 green bits, 2 blue bits)
		// NOTE: this code is integrally taken from MFC example Cube
		n = 1<<pfd.cColorBits;
        pPal = (PLOGPALETTE) new char[sizeof(LOGPALETTE) + n * sizeof(PALETTEENTRY)];

        ASSERT(pPal != NULL);

        pPal->palVersion = 0x300;
        pPal->palNumEntries = n;
        for (i=0; i<n; i++)
        {
            pPal->palPalEntry[i].peRed=ComponentFromIndex(i, pfd.cRedBits, pfd.cRedShift);
            pPal->palPalEntry[i].peGreen=ComponentFromIndex(i, pfd.cGreenBits, pfd.cGreenShift);
            pPal->palPalEntry[i].peBlue=ComponentFromIndex(i, pfd.cBlueBits, pfd.cBlueShift);
            pPal->palPalEntry[i].peFlags=0;
        }

		// Fix up the palette to include the default Windows palette
        if ((pfd.cColorBits == 8)                           &&
            (pfd.cRedBits   == 3) && (pfd.cRedShift   == 0) &&
            (pfd.cGreenBits == 3) && (pfd.cGreenShift == 3) &&
            (pfd.cBlueBits  == 2) && (pfd.cBlueShift  == 6)
           )
        {
			for (i=1 ; i<=12 ; i++)
                pPal->palPalEntry[defaultOverride[i]] = defaultPalEntry[i];
        }

        m_CurrentPalette.CreatePalette(pPal);
        delete pPal;

		// Set the palette
        m_pOldPalette=m_pCDC->SelectPalette(&m_CurrentPalette, FALSE);
        m_pCDC->RealizePalette();
    }
}

unsigned char CGLEnabledView::ComponentFromIndex(int i, UINT nbits, UINT shift)
{
    unsigned char val;

    val = (unsigned char) (i >> shift);
    switch (nbits) 
	{

    case 1:
        val &= 0x1;
        return _oneto8[val];
    case 2:
        val &= 0x3;
        return _twoto8[val];
    case 3:
        val &= 0x7;
        return _threeto8[val];

    default:
        return 0;
    }
}

/////////////////////////////////////////////////////////////////////////////
// CGLEnabledView message handlers and overridables

int CGLEnabledView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1) 
		return -1;
	
	// OpenGL rendering context creation
	PIXELFORMATDESCRIPTOR pfd;
    int         n;

	// Initialize the private member
	m_pCDC= new CClientDC(this);

	// Choose the requested video mode
    if (!bSetupPixelFormat()) 
		return 0;
	
	// Ask the system if the video mode is supported
    n=::GetPixelFormat(m_pCDC->GetSafeHdc());
    ::DescribePixelFormat(m_pCDC->GetSafeHdc(),n,sizeof(pfd),&pfd);

	// Create a palette if the requested video mode has 256 colors (indexed mode)
    CreateRGBPalette();

	// Link the Win Device Context with the OGL Rendering Context
    m_hRC = wglCreateContext(m_pCDC->GetSafeHdc());

	// Specify the target DeviceContext (window) of the subsequent OGL calls
    wglMakeCurrent(m_pCDC->GetSafeHdc(), m_hRC);

	// Performs default setting of rendering mode,etc..
	OnCreateGL();

	// Free the target DeviceContext (window)
//    wglMakeCurrent(NULL,NULL);
	
	return 0;
}

void CGLEnabledView::OnCreateGL()
{
	// Perform hidden line/surface removal (enabling Z-Buffer)
	glEnable(GL_DEPTH_TEST);

	// Set background color to black
	glClearColor(0.f,0.f,0.f,1.0f );

	// Set clear Z-Buffer value
	glClearDepth(1.0f);

}

void CGLEnabledView::OnDestroy() 
{
	// Specify the target DeviceContext (window) of the subsequent OGL calls
    wglMakeCurrent(m_pCDC->GetSafeHdc(), m_hRC);

	// Remove all display lists
	for (int c=0; c<MAX_LISTS; c++) 
		if (m_DispListVector[c]) 
			glDeleteLists(m_DispListVector[c], 1);

	// Release definitely OGL Rendering Context
	if (m_hRC != NULL) 
		::wglDeleteContext(m_hRC);

	// Select our palette out of the dc
	CPalette palDefault;
	palDefault.CreateStockObject(DEFAULT_PALETTE);
	m_pCDC->SelectPalette(&palDefault, FALSE);

	// Destroy Win Device Context
	if (m_pCDC) 
		delete m_pCDC;

	wglMakeCurrent(NULL,NULL);

	// Finally call the base function
	CView::OnDestroy();	
}

BOOL CGLEnabledView::PreCreateWindow(CREATESTRUCT& cs) 
{
	// These styles are requested by OpenGL
	cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	// These styles are meant for a use of this class in a MDI application
	cs.lpszClass = AfxRegisterWndClass(CS_OWNDC | CS_HREDRAW | CS_VREDRAW);

	return CView::PreCreateWindow(cs);
}


BOOL CGLEnabledView::OnEraseBkgnd(CDC* pDC) 
{
	// OGL has his own background erasing so tell Windows to skip
	return TRUE;
}

void CGLEnabledView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// When called with a nonzero window:
	if (0 < cx && 0 < cy)
	{
		// Update the rect and the aspect ratio
		m_ClientRect.right = cx;
		m_ClientRect.bottom = cy;
		m_dAspectRatio = double(cx)/double(cy);

		// Specify the target DeviceContext of the subsequent OGL calls
		wglMakeCurrent(m_pCDC->GetSafeHdc(), m_hRC);

		// Call the virtual sizing procedure (to be overridden by user)
		OnSizeGL(cx, cy);

		// Free the target DeviceContext (window)
		wglMakeCurrent(NULL, NULL);

		// Force redraw
		Invalidate(TRUE);
	};
}

void CGLEnabledView::OnSizeGL(int cx, int cy)
{
	// set correspondence between window and OGL viewport
	glViewport(0, 0, cx, cy);

	// update the camera
 	glPushMatrix();
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(40.0, m_dAspectRatio, 0.1f, 10.0f);
		glTranslatef(0.0f, 0.0f, -4.f);
		glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

BOOL CGLEnabledView::OnSetCursor(CWnd* /*pWnd*/, UINT /*nHitTest*/, UINT /*message*/) 
{
	ASSERT(m_hMouseCursor != NULL);
	::SetCursor(m_hMouseCursor);
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CGLEnabledView public members

void CGLEnabledView::VideoMode(ColorsNumber &c, ZAccuracy &z, BOOL &dbuf)
{
	// Set default videomode
	c		= MILLIONS;
	z		= NORMAL;
	dbuf	= TRUE;
}

void CGLEnabledView::SetMouseCursor(HCURSOR mcursor)
{
	// Set the specified cursor (only if it is a valid one)
	if(mcursor != NULL) 
		m_hMouseCursor=mcursor;
}

const CString CGLEnabledView::GetInformation(InfoField type)
{
	PIXELFORMATDESCRIPTOR pfd;
	CString str("Not Available");

	// Get information about the DC's current pixel format 
	::DescribePixelFormat( m_pCDC->GetSafeHdc(), ::GetPixelFormat(m_pCDC->GetSafeHdc()),sizeof(PIXELFORMATDESCRIPTOR), &pfd ); 

	// Specify the target DeviceContext of the subsequent OGL calls
	wglMakeCurrent(m_pCDC->GetSafeHdc(), m_hRC);

	switch(type)
	{
	// Derive driver information
	case ACCELERATION: 
		if(0 == (INSTALLABLE_DRIVER_TYPE_MASK & pfd.dwFlags)) 
			str = "Fully Accelerated (ICD)"; // fully in hardware (fastest)
		else if (INSTALLABLE_DRIVER_TYPE_MASK == (INSTALLABLE_DRIVER_TYPE_MASK & pfd.dwFlags)) 
			str = "Partially Accelerated (MCD)"; // partially in hardware (pretty fast, maybe..)
		else 
			str = "Not Accelerated (Software)";	// software
		
		break;
	// Get the company name responsible for this implementation
	case VENDOR:
		str = (char*)::glGetString(GL_VENDOR);
		if (::glGetError() != GL_NO_ERROR) 
			str.Format("Not Available"); // failed!
		
		break;

	// Get the renderer name; this is specific of an hardware configuration
	case RENDERER:
		str = (char*)::glGetString(GL_RENDERER);
		if (::glGetError()!=GL_NO_ERROR) 
			str.Format("Not Available"); // failed!
		
		break;
	
	// Get the version
	case VERSION:
		str = (char*)::glGetString(GL_VERSION);
		if ( ::glGetError() != GL_NO_ERROR) 
			str.Format("Not Available"); // failed!
		break;
	
	// Return a space separated list of extensions
	case EXTENSIONS: 
		str = (char*)::glGetString(GL_EXTENSIONS);
		if (::glGetError() != GL_NO_ERROR) 
			str.Format("Not Available");// failed!
		break;
	};

	// Free the target DeviceContext (window) and return the result
	wglMakeCurrent(NULL, NULL);
	
	return str;
}

void CGLEnabledView::DrawStockDispLists()
{
	// Check if we are already inside a drawing session
	if(m_hRC == wglGetCurrentContext() && m_pCDC->GetSafeHdc() == wglGetCurrentDC())
	{
		// Draw directly all display lists
		for (int c=0; c<MAX_LISTS; c++) 
			if (m_DispListVector[c]) 
				glCallList(m_DispListVector[c]);
	}
	else
	{
		// Specify the target DeviceContext of the subsequent OGL calls
		wglMakeCurrent(m_pCDC->GetSafeHdc(), m_hRC);
		
		// Draw all display lists
		for (int c=0; c<MAX_LISTS; c++) 
			if (m_DispListVector[c]) 
				glCallList(m_DispListVector[c]);
		
		// Free the target DeviceContext (window)
		wglMakeCurrent(NULL, NULL);
	}
}

void CGLEnabledView::StartStockDListDef()
{
	// Check if we aren't inside another couple begin/end
	if (!m_bInsideDispList)
	{
		// Search a free slot
		int c;
		for (c=0; m_DispListVector[c] != 0; c++);
		
		// Check if we are inside a drawing session or not....
		if(!(m_hRC == wglGetCurrentContext() && m_pCDC->GetSafeHdc() == wglGetCurrentDC()))
		{
			// If not specify the target DeviceContext of the subsequent OGL calls
			wglMakeCurrent(m_pCDC->GetSafeHdc(), m_hRC);
			
			// Set a warning for EndDispList
			m_bExternDispListCall = TRUE;
		};

		// create a handle to the disp list (actually an integer)
		m_DispListVector[c] = glGenLists(1);
		
		// Set a semaphore
		m_bInsideDispList = TRUE;
		
		// Start the disp list: all subsequent OGL calls will be redirected to the list
		glNewList(m_DispListVector[c], GL_COMPILE);
	};
}

void CGLEnabledView::EndStockListDef()
{
	// Close the disp list
	glEndList();

	// Unset the semaphore
	m_bInsideDispList = FALSE;
	
	// if beginDispList set the warn free the target DeviceContext
	if (m_bExternDispListCall) 
		wglMakeCurrent(NULL, NULL);
}

void CGLEnabledView::ClearStockDispLists()
{
	// Check if we are referring to the right Rendering Context
	if (m_hRC == wglGetCurrentContext() && m_pCDC->GetSafeHdc() == wglGetCurrentDC())
	{
		// Delete active display lists
		for (int c=0; c<MAX_LISTS; c++) 
			if(m_DispListVector[c]) 
				glDeleteLists(m_DispListVector[c], 1);
	}
	else
	{
		// Specify the target Rendering Context of the subsequent OGL calls
		wglMakeCurrent(m_pCDC->GetSafeHdc(), m_hRC);
		
		// Delete active display lists
		for (int c=0; c<MAX_LISTS; c++) 
			if (m_DispListVector[c]) 
				glDeleteLists(m_DispListVector[c], 1);
		
		// Free the target Rendering Context (window)
		wglMakeCurrent(NULL, NULL);
	};
}

void CGLEnabledView::BeginGLCommands()
{
	// Check if we are inside a drawing session or not....
	if(!(m_hRC==wglGetCurrentContext() && m_pCDC->GetSafeHdc() == wglGetCurrentDC()))
	{
		// if not specify the target DeviceContext of the subsequent OGL calls
		wglMakeCurrent(m_pCDC->GetSafeHdc(), m_hRC);

		// Set a warning for EndGLCommands
		m_bExternGLCall = TRUE;
	}
}

void CGLEnabledView::EndGLCommands()
{
	// if BeginGLCommands set the warn free the target DeviceContext
	if (m_bExternGLCall) 
		wglMakeCurrent(NULL, NULL);
}

void CGLEnabledView::CopyToClipboard() 
{
	
}
//////////////////////////////////////////////////////////////////////
//
// Implementation of CGLEnabledView::CGLDispList class.
//
/*** DESCRIPTION

  This is actually a helper class which wraps the
  use of display list in OGL.
  It must be used inside an GLEnabledView cause
  a display list must refer to a Rendering Context.
  At present there is no support for Disp. Lists
  Sharing among multiple RCs (that is multiple MDI
  child windows).

****************************************/

//////////////////////////////////////////////////////////////////////
// Construction/Destruction

CGLEnabledView::CGLDispList::CGLDispList(): 
	m_glListId(0), m_bIsolated(FALSE)
{

}

CGLEnabledView::CGLDispList::~CGLDispList()
{
	// Remove display list
	glDeleteLists(m_glListId,1); 
}

//////////////////////////////////////////////////////////////////////
// Member functions

void CGLEnabledView::CGLDispList::Draw()
{
	// If the list is not empty...
	if (m_glListId)
	{
		if (m_bIsolated)
		{
			// Save current transformation matrix
			glPushMatrix();
	
			// Save current OGL internal state (lighting, shading, and such)
			glPushAttrib(GL_ALL_ATTRIB_BITS);
		}
		
		// Draw the list
		glCallList(m_glListId);
		
		if(m_bIsolated)
		{
			// Restore transformation matrix
			glPopMatrix();
			
			// Restore OGL internal state
			glPopAttrib();
		}
	}
}

void CGLEnabledView::CGLDispList::StartDef(BOOL bImmediateExec)
{
	//  set the context for GL calls (if needed)
	//	BeginGLCommands();
	// check if another list is under construction
	int cur;
	glGetIntegerv(GL_LIST_INDEX, &cur);
	if (cur != 0) 
	{
		TRACE("Error: Nested display list definition!");
		ASSERT(FALSE);
	}

	// If the list is empty firstly allocate one
	if (!m_glListId) 
		m_glListId = glGenLists(1);

	// Start or replace a list definition
	if (bImmediateExec) 
		glNewList(m_glListId, GL_COMPILE_AND_EXECUTE);
	else  
		glNewList(m_glListId, GL_COMPILE);
}

void CGLEnabledView::CGLDispList::EndDef()
{
	// Check the coupling with a preceding call to StartDef()
	int cur;
	glGetIntegerv(GL_LIST_INDEX, &cur);
	if	(cur != m_glListId) 
	{
		TRACE("CGLDispList:Missing StartDef() before EndDef()\n");
		return;
	}

	// Close list definition
	glEndList();

	// Free the context (if needed)
	//	EndGLCommands();
}

int	CGLEnabledView::CGLDispList::GetListID()
{
	return m_glListId;
}

//////////////////////////////////////////////////////////////////////
//
// Implementation of CGLEnabledView::CGLTesselator class.
//
/*** DESCRIPTION

  This is actually a helper class which wraps the
  use of tessellation objects in OGL (see guide).
  It must be used inside an GLEnabledView cause
  a tesselator object must refer to a Rendering Context.

****************************************/

//////////////////////////////////////////////////////////////////////
// Construction/Destruction

CGLEnabledView::CGLTesselator::CGLTesselator()
{
	// Create tessellation object
	m_tessObj = gluNewTess();
	
	// Set callback functions
	gluTessCallback(m_tessObj, GLU_TESS_BEGIN,	 (void (CALLBACK*)())&BeginCallback); 
	gluTessCallback(m_tessObj, GLU_TESS_VERTEX,	 (void (CALLBACK*)())&VertexCallback); 
	gluTessCallback(m_tessObj, GLU_TESS_END,	 (void (CALLBACK*)())&EndCallback);
	gluTessCallback(m_tessObj, GLU_TESS_COMBINE, (void (CALLBACK*)())&CombineCallback);
	gluTessCallback(m_tessObj, GLU_TESS_ERROR,	 (void (CALLBACK*)())&ErrorCallback);
}

CGLEnabledView::CGLTesselator::~CGLTesselator()
{
	// Remove tessellation object
	gluDeleteTess(m_tessObj);	
}

//////////////////////////////////////////////////////////////////////
// Member functions

void CGLEnabledView::CGLTesselator::SetWindingRule(GLdouble which)
{
	// Issue the equivalent GL call
	gluTessProperty(m_tessObj, GLU_TESS_WINDING_RULE, which); 
}

GLdouble CGLEnabledView::CGLTesselator::GetWindingRule()
{
	// Retrieve attribute
	GLdouble temp;
	gluTessProperty(m_tessObj, GLU_TESS_WINDING_RULE, temp);
	
	// Return value
	return temp;
}

void CGLEnabledView::CGLTesselator::SetFilling(BOOL bFill)
{
	// Issue the equivalent GL calls
	if (bFill) 
		gluTessProperty(m_tessObj, GLU_TESS_BOUNDARY_ONLY, GL_FALSE);
	else 
		gluTessProperty(m_tessObj, GLU_TESS_BOUNDARY_ONLY, GL_TRUE);
}

BOOL CGLEnabledView::CGLTesselator::GetFilling()
{
	// Retrieve attribute
	GLdouble temp;
	gluTessProperty(m_tessObj, GLU_TESS_BOUNDARY_ONLY, temp);
	
	// Convert to a boolean
	return (temp == GL_TRUE);
}

void CGLEnabledView::CGLTesselator::StartDef()
{
	// Start a polygon definition
	gluTessBeginPolygon(m_tessObj, NULL);

	// Start a contour definition
	gluTessBeginContour(m_tessObj);
}

void CGLEnabledView::CGLTesselator::EndDef()
{
	// End contour and polygon definition
	gluTessEndContour(m_tessObj);
	gluTessEndPolygon(m_tessObj);

	// Free new vertices created by tessellation
	::DeleteGarbage();
}

void CGLEnabledView::CGLTesselator::ContourSeparator()
{
	// Insert a contour separation
	gluTessEndContour(m_tessObj);
	gluTessBeginContour(m_tessObj);
}

void CGLEnabledView::CGLTesselator::AddVertex(GLdouble vertData[3])
{
	// IMPORTANT: the 3rd parameter must be given otherwise an access
	// violation will occur, moreover every vertex must have it's own memory
	// location till the closing of the polygon (that is you can't pass all
	// the vertices trough the same variable in a for loop).
	gluTessVertex(m_tessObj,vertData, vertData); 
}

void CGLEnabledView::CGLTesselator::AddVertexArray(GLdouble arr[][3], int size)
{
	ASSERT(arr != NULL);

	// Pass the vertices to the tessellation object
	for(int ct=0; ct<size; ct++) 
		gluTessVertex(m_tessObj, arr[ct], arr[ct]);
}

//////////////////////////////////////////////////////////////////////
//
// Implementation of CGLEnabledView::CGLQuadric class.
//
/* DESCRIPTION

  This is actually a helper class which wraps the
  use of quadric objects in OGL (see guide).
  It must be used inside an GLEnabledView cause
  a quadric object must refer to a Rendering Context.

*/

//////////////////////////////////////////////////////////////////////
// Construction/Destruction

CGLEnabledView::CGLQuadric::CGLQuadric(GLenum drwStyle,GLenum normals,GLenum side,BOOL bGenerateTxtrCoords)
{
	// Check validity of parameters
	ASSERT(normals == GLU_NONE || normals == GLU_FLAT || normals == GLU_SMOOTH);
	ASSERT(drwStyle == GLU_FILL || drwStyle == GLU_LINE || drwStyle == GLU_SILHOUETTE|| drwStyle == GLU_POINT);
	ASSERT(side == GLU_INSIDE || side == GLU_OUTSIDE);

	// Create quadric object
	m_quadrObj = gluNewQuadric();

	// Set error callback function (shared with tesselators)
	gluQuadricCallback(m_quadrObj, GLU_ERROR, (void (CALLBACK*)())&ErrorCallback);

	// Set normal generation
	gluQuadricNormals(m_quadrObj, normals);

	// Set Texture Coordinates generation
	if (bGenerateTxtrCoords) 
		gluQuadricTexture(m_quadrObj, GL_TRUE);
	else 
		gluQuadricTexture(m_quadrObj, GL_FALSE);

	// Set how the quadric will be generated
	gluQuadricDrawStyle(m_quadrObj, drwStyle);

	// Set which side of the quadric is to be considered inside
	gluQuadricOrientation(m_quadrObj, side);
}

CGLEnabledView::CGLQuadric::~CGLQuadric()
{
	// Remove quadric object
	gluDeleteQuadric(m_quadrObj);	
}

//////////////////////////////////////////////////////////////////////
// Member functions

void CGLEnabledView::CGLQuadric::SetNormals(GLenum type)
{
	// Check validity of type parameter it must be one of these:
	ASSERT(type == GLU_NONE || type == GLU_FLAT || type == GLU_SMOOTH);

	// Issue corresponding GL command
	gluQuadricNormals(m_quadrObj, type);
}

void CGLEnabledView::CGLQuadric::SetTextureCoordsGen(BOOL flag)
{
	// Issue corresponding GL commands
	if (flag) 
		gluQuadricTexture(m_quadrObj, GL_TRUE);
	else 
		gluQuadricTexture(m_quadrObj, GL_FALSE);
}

void CGLEnabledView::CGLQuadric::SetOrientation(GLenum type)
{
	// Check validity of type parameter it must be one of these:
	ASSERT(type == GLU_INSIDE || type == GLU_OUTSIDE);

	// Issue corresponding GL command
	gluQuadricOrientation(m_quadrObj, type);
}

void CGLEnabledView::CGLQuadric::SetDrawStyle(GLenum style)
{
	// Check validity of type parameter it must be one of these:
	ASSERT(style == GLU_FILL || style == GLU_LINE || style == GLU_SILHOUETTE|| style == GLU_POINT);

	// Issue corresponding GL command
	gluQuadricDrawStyle(m_quadrObj, style);
}

void CGLEnabledView::CGLQuadric::DrawSphere(GLdouble radius, int longitudeSubdiv, int latitudeSubdiv)
{
	// issue corresponding GL command
	gluSphere(m_quadrObj, radius, longitudeSubdiv, latitudeSubdiv);
}

void CGLEnabledView::CGLQuadric::DrawCylinder(GLdouble baseRadius,GLdouble topRadius,GLdouble height,int slices,int stacks)
{
	// Issue corresponding GL command
	gluCylinder(m_quadrObj, baseRadius, topRadius, height, slices, stacks);
}

void CGLEnabledView::CGLQuadric::DrawDisk(GLdouble innerRadius,GLdouble outerRadius,int slices,int loops)
{
	// Issue corresponding GL command
	gluDisk(m_quadrObj, innerRadius, outerRadius, slices, loops);
}

void CGLEnabledView::CGLQuadric::DrawPartialDisk(GLdouble innerRadius,GLdouble outerRadius,int slices,int loops,GLdouble startAngle,GLdouble sweepAngle)
{
	// Issue corresponding GL command
	gluPartialDisk(m_quadrObj, innerRadius, outerRadius, slices, loops, startAngle, sweepAngle);
}

///////////////////
// EPS
/* Copyright (c) Mark J. Kilgard, 1997. */
/* OpenGL's GL_3D_COLOR feedback vertex format. */
typedef struct _Feedback3Dcolor 
{
	GLfloat x;
	GLfloat y;
	GLfloat z;
	GLfloat red;
	GLfloat green;
	GLfloat blue;
	GLfloat alpha;
} Feedback3Dcolor;


/* How many feedback buffer GLfloats each of the three objects need. */
int objectComplexity[3] = {6000, 14000, 380000};  /* Teapot requires ~1.5 megabytes for its feedback results! */

/* Write contents of one vertex to stdout. */
void CGLEnabledView::print3DcolorVertex(GLint size, GLint* count, GLfloat* buffer)
{
	int i;
	
	printf("  ");
	for (i = 0; i < 7; i++) 
	{
		printf("%4.2f ", buffer[size - (*count)]);
		*count = *count - 1;
	}
	printf("\n");
}

void CGLEnabledView::printBuffer(GLint size, GLfloat * buffer)
{
	GLint count;
	int token, nvertices;
	
	count = size;
	while (count) 
	{
		token = buffer[size - count];
		count--;
		switch (token) 
		{
		case GL_PASS_THROUGH_TOKEN:
			printf("GL_PASS_THROUGH_TOKEN\n");
			printf("  %4.2f\n", buffer[size - count]);
			count--;
			break;
		case GL_POINT_TOKEN:
			printf("GL_POINT_TOKEN\n");
			print3DcolorVertex(size, &count, buffer);
			break;
		case GL_LINE_TOKEN:
			printf("GL_LINE_TOKEN\n");
			print3DcolorVertex(size, &count, buffer);
			print3DcolorVertex(size, &count, buffer);
			break;
		case GL_LINE_RESET_TOKEN:
			printf("GL_LINE_RESET_TOKEN\n");
			print3DcolorVertex(size, &count, buffer);
			print3DcolorVertex(size, &count, buffer);
			break;
		case GL_POLYGON_TOKEN:
			printf("GL_POLYGON_TOKEN\n");
			nvertices = buffer[size - count];
			count--;
			for (; nvertices > 0; nvertices--) 
			{
				print3DcolorVertex(size, &count, buffer);
			}
		}
	}
}

GLfloat pointSize;

static char *gouraudtriangleEPS[] =
{
	"/bd{bind def}bind def /triangle { aload pop   setrgbcolor  aload pop 5 3",
		"roll 4 2 roll 3 2 roll exch moveto lineto lineto closepath fill } bd",
		"/computediff1 { 2 copy sub abs threshold ge {pop pop pop true} { exch 2",
		"index sub abs threshold ge { pop pop true} { sub abs threshold ge } ifelse",
		"} ifelse } bd /computediff3 { 3 copy 0 get 3 1 roll 0 get 3 1 roll 0 get",
		"computediff1 {true} { 3 copy 1 get 3 1 roll 1 get 3 1 roll 1 get",
		"computediff1 {true} { 3 copy 2 get 3 1 roll  2 get 3 1 roll 2 get",
		"computediff1 } ifelse } ifelse } bd /middlecolor { aload pop 4 -1 roll",
		"aload pop 4 -1 roll add 2 div 5 1 roll 3 -1 roll add 2 div 3 1 roll add 2",
		"div 3 1 roll exch 3 array astore } bd /gouraudtriangle { computediff3 { 4",
		"-1 roll aload 7 1 roll 6 -1 roll pop 3 -1 roll pop add 2 div 3 1 roll add",
		"2 div exch 3 -1 roll aload 7 1 roll exch pop 4 -1 roll pop add 2 div 3 1",
		"roll add 2 div exch 3 -1 roll aload 7 1 roll pop 3 -1 roll pop add 2 div 3",
		"1 roll add 2 div exch 7 3 roll 10 -3 roll dup 3 index middlecolor 4 1 roll",
		"2 copy middlecolor 4 1 roll 3 copy pop middlecolor 4 1 roll 13 -1 roll",
		"aload pop 17 index 6 index 15 index 19 index 6 index 17 index 6 array",
		"astore 10 index 10 index 14 index gouraudtriangle 17 index 5 index 17",
		"index 19 index 5 index 19 index 6 array astore 10 index 9 index 13 index",
		"gouraudtriangle 13 index 16 index 5 index 15 index 18 index 5 index 6",
		"array astore 12 index 12 index 9 index gouraudtriangle 17 index 16 index",
		"15 index 19 index 18 index 17 index 6 array astore 10 index 12 index 14",
		"index gouraudtriangle 18 {pop} repeat } { aload pop 5 3 roll aload pop 7 3",
		"roll aload pop 9 3 roll 4 index 6 index 4 index add add 3 div 10 1 roll 7",
		"index 5 index 3 index add add 3 div 10 1 roll 6 index 4 index 2 index add",
		"add 3 div 10 1 roll 9 {pop} repeat 3 array astore triangle } ifelse } bd",
		NULL
};

GLfloat* CGLEnabledView::spewPrimitiveEPS(FILE* file, GLfloat* loc)
{
	int token;
	int nvertices, i;
	GLfloat red, green, blue;
	int smooth;
	GLfloat dx, dy, dr, dg, db, absR, absG, absB, colormax;
	int steps;
	Feedback3Dcolor *vertex;
	GLfloat xstep, ystep, rstep, gstep, bstep;
	GLfloat xnext, ynext, rnext, gnext, bnext, distance;
	
	token = *loc;
	loc++;
	switch (token) 
	{
	case GL_LINE_RESET_TOKEN:
	case GL_LINE_TOKEN:
		vertex = (Feedback3Dcolor *) loc;
		
		dr = vertex[1].red - vertex[0].red;
		dg = vertex[1].green - vertex[0].green;
		db = vertex[1].blue - vertex[0].blue;
		
		if (dr != 0 || dg != 0 || db != 0) 
		{
			/* Smooth shaded line. */
			dx = vertex[1].x - vertex[0].x;
			dy = vertex[1].y - vertex[0].y;
			distance = sqrt(dx * dx + dy * dy);
			
			absR = fabs(dr);
			absG = fabs(dg);
			absB = fabs(db);
			
#define Max(a,b) (((a)>(b))?(a):(b))
			
#define EPS_SMOOTH_LINE_FACTOR 0.06  /* Lower for better smooth lines. */
			
			colormax = Max(absR, Max(absG, absB));
			steps = Max(1.0, colormax * distance * EPS_SMOOTH_LINE_FACTOR);
			
			xstep = dx / steps;
			ystep = dy / steps;
			
			rstep = dr / steps;
			gstep = dg / steps;
			bstep = db / steps;
			
			xnext = vertex[0].x;
			ynext = vertex[0].y;
			rnext = vertex[0].red;
			gnext = vertex[0].green;
			bnext = vertex[0].blue;
			
			/* Back up half a step; we want the end points to be
			exactly the their endpoint colors. */
			xnext -= xstep / 2.0;
			ynext -= ystep / 2.0;
			rnext -= rstep / 2.0;
			gnext -= gstep / 2.0;
			bnext -= bstep / 2.0;
		} 
		else 
		{
			/* Single color line. */
			steps = 0;
		}
		
		fprintf(file, "%g %g %g setrgbcolor\n",
			vertex[0].red, vertex[0].green, vertex[0].blue);
		fprintf(file, "%g %g moveto\n", vertex[0].x, vertex[0].y);
		
		for (i = 0; i < steps; i++) 
		{
			xnext += xstep;
			ynext += ystep;
			rnext += rstep;
			gnext += gstep;
			bnext += bstep;
			fprintf(file, "%g %g lineto stroke\n", xnext, ynext);
			fprintf(file, "%g %g %g setrgbcolor\n", rnext, gnext, bnext);
			fprintf(file, "%g %g moveto\n", xnext, ynext);
		}
		fprintf(file, "%g %g lineto stroke\n", vertex[1].x, vertex[1].y);
		
		loc += 14;          /* Each vertex element in the feedback
		buffer is 7 GLfloats. */
		
		break;
	case GL_POLYGON_TOKEN:
		nvertices = *loc;
		loc++;
		
		vertex = (Feedback3Dcolor *) loc;
		
		if (nvertices > 0) 
		{
			red = vertex[0].red;
			green = vertex[0].green;
			blue = vertex[0].blue;
			smooth = 0;
			for (i = 1; i < nvertices; i++) 
			{
				if (red != vertex[i].red || green != vertex[i].green || blue != vertex[i].blue) {
					smooth = 1;
					break;
				}
			}
			if (smooth) 
			{
				/* Smooth shaded polygon; varying colors at vetices. */
				int triOffset;
				
				/* Break polygon into "nvertices-2" triangle fans. */
				for (i = 0; i < nvertices - 2; i++) {
					triOffset = i * 7;
					fprintf(file, "[%g %g %g %g %g %g]",
						vertex[0].x, vertex[i + 1].x, vertex[i + 2].x,
						vertex[0].y, vertex[i + 1].y, vertex[i + 2].y);
					fprintf(file, " [%g %g %g] [%g %g %g] [%g %g %g] gouraudtriangle\n",
						vertex[0].red, vertex[0].green, vertex[0].blue,
						vertex[i + 1].red, vertex[i + 1].green, vertex[i + 1].blue,
						vertex[i + 2].red, vertex[i + 2].green, vertex[i + 2].blue);
				}
			} 
			else 
			{
				/* Flat shaded polygon; all vertex colors the same. */
				fprintf(file, "newpath\n");
				fprintf(file, "%g %g %g setrgbcolor\n", red, green, blue);
				
				/* Draw a filled triangle. */
				fprintf(file, "%g %g moveto\n", vertex[0].x, vertex[0].y);
				for (i = 1; i < nvertices; i++) 
				{
					fprintf(file, "%g %g lineto\n", vertex[i].x, vertex[i].y);
				}
				fprintf(file, "closepath fill\n\n");
			}
		}
		loc += nvertices * 7;  /* Each vertex element in the
		feedback buffer is 7 GLfloats. */
		break;
	case GL_POINT_TOKEN:
		vertex = (Feedback3Dcolor *) loc;
		fprintf(file, "%g %g %g setrgbcolor\n", vertex[0].red, vertex[0].green, vertex[0].blue);
		fprintf(file, "%g %g %g 0 360 arc fill\n\n", vertex[0].x, vertex[0].y, pointSize / 2.0);
		loc += 7;           /* Each vertex element in the feedback
		buffer is 7 GLfloats. */
		break;
	default:
		/* XXX Left as an excersie to the reader. */
		printf("Incomplete implementation.  Unexpected token (%d).\n", token);
		exit(1);
	}
	return loc;
}

void CGLEnabledView::spewUnsortedFeedback(FILE * file, GLint size, GLfloat * buffer)
{
	GLfloat *loc, *end;
	
	loc = buffer;
	end = buffer + size;
	while (loc < end) 
	{
		loc = spewPrimitiveEPS(file, loc);
	}
}

typedef struct _DepthIndex {
	GLfloat *ptr;
	GLfloat depth;
} DepthIndex;

static int compare(const void *a, const void *b)
{
	DepthIndex *p1 = (DepthIndex *) a;
	DepthIndex *p2 = (DepthIndex *) b;
	GLfloat diff = p2->depth - p1->depth;
	
	if (diff > 0.0) {
		return 1;
	} else if (diff < 0.0) {
		return -1;
	} else {
		return 0;
	}
}

void CGLEnabledView::spewSortedFeedback(FILE* file, GLint size, GLfloat* buffer)
{
	int token;
	GLfloat *loc, *end;
	Feedback3Dcolor *vertex;
	GLfloat depthSum;
	int nprimitives, item;
	DepthIndex *prims;
	int nvertices, i;
	
	end = buffer + size;
	
	/* Count how many primitives there are. */
	nprimitives = 0;
	loc = buffer;
	while (loc < end) {
		token = *loc;
		loc++;
		switch (token) {
		case GL_LINE_TOKEN:
		case GL_LINE_RESET_TOKEN:
			loc += 14;
			nprimitives++;
			break;
		case GL_POLYGON_TOKEN:
			nvertices = *loc;
			loc++;
			loc += (7 * nvertices);
			nprimitives++;
			break;
		case GL_POINT_TOKEN:
			loc += 7;
			nprimitives++;
			break;
		default:
			/* XXX Left as an excersie to the reader. */
			printf("Incomplete implementation.  Unexpected token (%d).\n",
				token);
			exit(1);
		}
	}
	
	/* Allocate an array of pointers that will point back at
	primitives in the feedback buffer.  There will be one
	entry per primitive.  This array is also where we keep the
	primitive's average depth.  There is one entry per
	primitive  in the feedback buffer. */
	prims = (DepthIndex *) malloc(sizeof(DepthIndex) * nprimitives);
	
	item = 0;
	loc = buffer;
	while (loc < end) {
		prims[item].ptr = loc;  /* Save this primitive's location. */
		token = *loc;
		loc++;
		switch (token) {
		case GL_LINE_TOKEN:
		case GL_LINE_RESET_TOKEN:
			vertex = (Feedback3Dcolor *) loc;
			depthSum = vertex[0].z + vertex[1].z;
			prims[item].depth = depthSum / 2.0;
			loc += 14;
			break;
		case GL_POLYGON_TOKEN:
			nvertices = *loc;
			loc++;
			vertex = (Feedback3Dcolor *) loc;
			depthSum = vertex[0].z;
			for (i = 1; i < nvertices; i++) {
				depthSum += vertex[i].z;
			}
			prims[item].depth = depthSum / nvertices;
			loc += (7 * nvertices);
			break;
		case GL_POINT_TOKEN:
			vertex = (Feedback3Dcolor *) loc;
			prims[item].depth = vertex[0].z;
			loc += 7;
			break;
		default:
			/* XXX Left as an excersie to the reader. */
			assert(1);
		}
		item++;
	}
	assert(item == nprimitives);
	
	/* Sort the primitives back to front. */
	qsort(prims, nprimitives, sizeof(DepthIndex), compare);
	
	/* XXX Understand that sorting by a primitives average depth
	doesn't allow us to disambiguate some cases like self
	intersecting polygons.  Handling these cases would require
	breaking up the primitives.  That's too involved for this
	example.  Sorting by depth is good enough for lots of
	applications. */
	
	/* Emit the Encapsulated PostScript for the primitives in
	back to front order. */
	for (item = 0; item < nprimitives; item++) {
		(void) spewPrimitiveEPS(file, prims[item].ptr);
	}
	
	free(prims);
}

#define EPS_GOURAUD_THRESHOLD 0.1  
/* Lower for better (slower) smooth shading. */

void CGLEnabledView::spewWireFrameEPS(FILE * file, int doSort, GLint size, GLfloat * buffer, char *creator)
{
	GLfloat clearColor[4], viewport[4];
	GLfloat lineWidth;
	int i;
	
	/* Read back a bunch of OpenGL state to help make the EPS
	consistent with the OpenGL clear color, line width, point
	size, and viewport. */
	glGetFloatv(GL_VIEWPORT, viewport);
	glGetFloatv(GL_COLOR_CLEAR_VALUE, clearColor);
	glGetFloatv(GL_LINE_WIDTH, &lineWidth);
	glGetFloatv(GL_POINT_SIZE, &pointSize);
	
	/* Emit EPS header. */
	fputs("%!PS-Adobe-2.0 EPSF-2.0\n", file);
	/* Notice %% for a single % in the fprintf calls. */
	fprintf(file, "%%%%Creator: %s (using OpenGL feedback)\n", creator);
	fprintf(file, "%%%%BoundingBox: %g %g %g %g\n",
		viewport[0], viewport[1], viewport[2], viewport[3]);
	fputs("%%EndComments\n", file);
	fputs("\n", file);
	fputs("gsave\n", file);
	fputs("\n", file);
	
	/* Output Frederic Delhoume's "gouraudtriangle" PostScript
	fragment. */
	fputs("% the gouraudtriangle PostScript fragement below is free\n", file);
	fputs("% written by Frederic Delhoume (delhoume@ilog.fr)\n", file);
	fprintf(file, "/threshold %g def\n", EPS_GOURAUD_THRESHOLD);
	for (i = 0; gouraudtriangleEPS[i]; i++) {
		fprintf(file, "%s\n", gouraudtriangleEPS[i]);
	}
	
	fprintf(file, "\n%g setlinewidth\n", lineWidth);
	
	/* Clear the background like OpenGL had it. */
	fprintf(file, "%g %g %g setrgbcolor\n",
		clearColor[0], clearColor[1], clearColor[2]);
	fprintf(file, "%g %g %g %g rectfill\n\n",
		viewport[0], viewport[1], viewport[2], viewport[3]);
	
	if (doSort) {
		spewSortedFeedback(file, size, buffer);
	} else {
		spewUnsortedFeedback(file, size, buffer);
	}
	
	/* Emit EPS trailer. */
	fputs("grestore\n\n", file);
	fputs("%Add `showpage' to the end of this file to be able to print to a printer.\n",
		file);
	
	fclose(file);
}

void CGLEnabledView::outputEPS(int size, int doSort)
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

		GLint nRenderMode[1];
		
		// need to create render context here
		m_hRC = wglCreateContext(pDC->m_hDC);

		// Useful in multidoc templates
		wglMakeCurrent(pDC->m_hDC, m_hRC);

		// Set feedback mode
	    glFeedbackBuffer(size, GL_3D_COLOR, pFeedbackBuffer);
		GLint returned = glRenderMode(GL_FEEDBACK);

		if ((errCode = glGetError()) != GL_NO_ERROR) 
		{
			errString = gluErrorString(errCode);
			char s[100];
			sprintf(s, "Error before: %s", errString);
			AfxMessageBox (s);
		}
	
		// Render
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glBegin(GL_LINES);
			glVertex3f(0.f, -0.1f, 0.8f);
			glVertex3f(0.f, -0.25f, 0.9f);
		glEnd();

		OnDrawGL();

		// Double buffer
		SwapBuffers(pDC->m_hDC);

		returned = glRenderMode(GL_RENDER);

		if ((errCode = glGetError()) != GL_NO_ERROR) 
		{
			errString = gluErrorString(errCode);
			char s[100];
			sprintf(s, "Error after: %s", errString);
			AfxMessageBox (s);
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

	

		// Cleanup
		string.ReleaseBuffer();
		delete [] pFeedbackBuffer;

	}

}

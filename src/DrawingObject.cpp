// DrawingObject.cpp: implementation of the CDrawingObject class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "visualizer_x.h"
#include "DrawingObject.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDrawingObject::CDrawingObject()
{
	m_nType = 0;
	m_scale = 1.0;
	m_bUseParticleType = TRUE;
}

CDrawingObject::~CDrawingObject()
{

}

void CDrawingObject::Draw(GLfloat** materialAmbient, GLfloat** materialDiffuse, int* hiddenType, int nResolution)
{
	
}

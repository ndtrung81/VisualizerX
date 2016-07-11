// SphereObject.cpp: implementation of the CSphereObject class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "visualizer_x.h"
#include "SphereObject.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSphereObject::CSphereObject()
{

}

CSphereObject::~CSphereObject()
{

}

void CSphereObject::SetRadius(double radius)
{
	m_radius = radius;
}

void CSphereObject::SetCenter(double x, double y, double z)
{
	m_center[0] = x;
	m_center[1] = y;
	m_center[2] = z;
}


void CSphereObject::Draw(GLfloat** materialAmbient, GLfloat** materialDiffuse, int* hiddenType, int nResolution)
{
	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient[m_nType]);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse[m_nType]);
		
	glTranslatef((GLfloat)m_center[0], (GLfloat)m_center[1], (GLfloat)m_center[2]);	

	double radius = 0.02f * m_radius;
	glutSolidSphere(radius, nResolution, nResolution);
		
	glTranslatef(-(GLfloat)m_center[0], -(GLfloat)m_center[1], -(GLfloat)m_center[2]);
}

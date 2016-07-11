// SphereCommand.cpp: implementation of the CSphereCommand class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "visualizer_x.h"
#include "SphereCommand.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSphereCommand::CSphereCommand()
{
	m_center = 0x0;
	m_nResolution = 32;
}

CSphereCommand::~CSphereCommand()
{

}

void CSphereCommand::SetCenter(CPosition* center)
{
	m_center = center;
}

void CSphereCommand::SetRadius(double radius)
{
	m_radius0 = m_radius = radius;
	
//	double r = m_center->GetRadius();
//	m_center->SetRadius(radius * r);
}

void CSphereCommand::SetResolution(int nResolution)
{
	m_nResolution = nResolution;
}

void CSphereCommand::Execute(GLfloat** materialAmbient, GLfloat** materialDiffuse, int* hiddenType)
{
	int nType = m_center->GetType();
//	if (hiddenType[nType] == TRUE)
//		return;

	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient[nType]);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse[nType]);

	double pos[3];
	double radius = m_radius * m_center->GetRadius(); // m_radius * 

	pos[0] = (*m_center)[0];
	pos[1] = (*m_center)[1];
	pos[2] = (*m_center)[2];
				
	glTranslatef((GLfloat)pos[0], (GLfloat)pos[1], (GLfloat)pos[2]);	
	
	glutSolidSphere(radius, m_nResolution, m_nResolution);
		
	glTranslatef(-(GLfloat)pos[0], -(GLfloat)pos[1], -(GLfloat)pos[2]);
}

void CSphereCommand::Zoom(double scale)
{
//	m_radius = scale;
}

// ArrowObject.cpp: implementation of the CArrowObject class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "visualizer_x.h"
#include "ArrowObject.h"
#include <math.h>

#define PI	3.1415926

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CArrowObject::CArrowObject()
{
	m_magnitude = 1.0;
	m_dirx = 1.0;
	m_diry = 0.0;
	m_dirz = 0.0;
}

CArrowObject::~CArrowObject()
{

}

void CArrowObject::SetPosition(CPosition* pos)
{
	m_position = pos;
}

void CArrowObject::SetDirection(double dirx, double diry, double dirz)
{
	m_magnitude = sqrt(dirx * dirx + diry * diry + dirz * dirz);
	m_dirx = dirx / m_magnitude;
	m_diry = diry / m_magnitude;
	m_dirz = dirz / m_magnitude;
}

void CArrowObject::SetMagnitude(double magnitude)
{
	m_magnitude = magnitude;
}

void CArrowObject::Draw(GLfloat** materialAmbient, GLfloat** materialDiffuse, int* hiddenType, int nResolution)
{
	int nType = m_position->GetType();
	if (hiddenType[nType] == TRUE)
		return;

	if (m_bUseParticleType == FALSE)
		nType = m_nType;

	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient[nType]);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse[nType]);

	// Fairly easy for transformation from Cartesian coordinates to spherical coordinates
	double magnitude = sqrt(m_dirx * m_dirx + m_diry * m_diry + m_dirz * m_dirz);
	double phi = acos(m_dirz / magnitude) * 180.0 / PI;
	double theta = atan2(m_diry, m_dirx) * 180.0 / PI;
	
	double radius = (*m_position).GetRadius();
	double arrow_radius = 0.02f * m_scale; // 0.05f * 
	double arrow_length = m_magnitude * m_scale; //  0.05f * 

	GLUquadricObj* cyl, *tip;
	cyl = gluNewQuadric();
	tip = gluNewQuadric();
	glPushMatrix();
		glTranslatef((*m_position)[0], (*m_position)[1], (*m_position)[2]);
		glRotatef(theta, 0.0, 0.0, 1.0);
		glRotatef(phi, 0.0, 1.0, 0.0);
		gluCylinder(cyl, arrow_radius, arrow_radius, arrow_length, 12, 12);

		glTranslatef(0.0, 0.0, 0.8*arrow_length);
		gluCylinder(tip, 3*arrow_radius, arrow_radius, 0.2*arrow_length, 12, 12);

	glPopMatrix();

}

// BondObject.cpp: implementation of the CBondObject class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "visualizer_x.h"
#include "BondObject.h"

#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define PI 3.1415926

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBondObject::CBondObject()
{

}

CBondObject::~CBondObject()
{

}

void CBondObject::SetPosition(CPosition* pos1, CPosition* pos2)
{
	m_position1 = pos1;
	m_position2 = pos2;
}

void CBondObject::SetBox(double boxSizex, double boxSizey, double boxSizez)
{
	m_boxSizex = boxSizex;
	m_boxSizey = boxSizey;
	m_boxSizez = boxSizez;
}

void CBondObject::Draw(GLfloat** materialAmbient, GLfloat** materialDiffuse, int* hiddenType, int nResolution)
{
	int nType = m_position1->GetType();

	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient[nType]);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse[nType]);

	double dx = (*m_position2)[0] - (*m_position1)[0];
	double dy = (*m_position2)[1] - (*m_position1)[1];
	double dz = (*m_position2)[2] - (*m_position1)[2];

	if (fabs(dx) > m_boxSizex / 2.0 
		|| fabs(dy) > m_boxSizey / 2.0 
		|| fabs(dz) > m_boxSizez / 2.0)
		return;

/*	double magnitude = sqrt(dx * dx + dy * dy + dz * dz);

	// Fairly easy for transformation from Cartesian coordinates to spherical coordinates
	double phi = acos(dz / magnitude) * 180.0 / PI;
	double theta = atan2(dy, dz) * 180.0 / PI;
	
	double radius = 0.02f * 0.05; 
	GLUquadricObj* cyl;
	cyl = gluNewQuadric();

	glPushMatrix();
		glTranslatef((*m_position1)[0], (*m_position1)[1], (*m_position1)[2]);
		glRotatef(theta, 0.0, 0.0, 1.0);
		glRotatef(phi, 0.0, 1.0, 0.0);
		gluCylinder(cyl, radius, radius, magnitude, 4, 4);
	glPopMatrix();
*/
	glLineWidth(2.0f);
	glBegin(GL_LINE_STRIP);
		glVertex3f((*m_position1)[0], (*m_position1)[1], (*m_position1)[2]);
		glVertex3f((*m_position2)[0], (*m_position2)[1], (*m_position2)[2]);
	glEnd();

}

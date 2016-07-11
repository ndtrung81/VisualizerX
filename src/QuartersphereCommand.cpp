// QuartersphereCommand.cpp: implementation of the CQuartersphereCommand class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "visualizer_x.h"
#include "QuartersphereCommand.h"

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

CQuartersphereCommand::CQuartersphereCommand()
{
	m_nResolution = 16;
}

CQuartersphereCommand::~CQuartersphereCommand()
{

}

void CQuartersphereCommand::SetEndPoints(CPosition* startPoint, CPosition* endPoint)
{
	m_startPoint	= startPoint;
	m_endPoint		= endPoint;
}

void CQuartersphereCommand::SetRadius(double radius)
{
	m_radius0 = m_radius = radius;
}

void CQuartersphereCommand::Execute(GLfloat** materialAmbient, GLfloat** materialDiffuse, int* hiddenType)
{
	int nStartType = m_startPoint->GetType();
	int nEndType = m_endPoint->GetType();

	double x, y, z, phi, theta, L;
	x = (*m_endPoint)[0] -  (*m_startPoint)[0];
	y = (*m_endPoint)[1] -  (*m_startPoint)[1];
	z = (*m_endPoint)[2] -  (*m_startPoint)[2];

	L = sqrt(x * x + y * y + z * z);
	if (L < 1e-6)
		return;
	
	// Fairly easy for transformation from Cartesian coordinates to spherical coordinates
	phi = acos(z / L) * 180.0 / PI;
	theta = atan2(y, x) * 180.0 / PI;
	
	double radius_start = m_startPoint->GetRadius(); //  * m_radius 0.02f is already included in m_radius
	double radius_end = m_endPoint->GetRadius();
	
	glPushMatrix();
		glTranslatef((*m_startPoint)[0], (*m_startPoint)[1], (*m_startPoint)[2]);
	
		glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient[nStartType]);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse[nStartType]);
		glutSolidSphere(radius_start, m_nResolution, m_nResolution);

		glRotatef(theta, 0.0, 0.0, 1.0);
		glRotatef(phi, 0.0, 1.0, 0.0);
		
		glRotatef(45.0f, 1.0, 0.0, 0.0);

		glTranslatef(0.0f, 0.0f, 0.001f);
		glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient[nEndType]);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse[nEndType]);
		glutSolidSphere(radius_end, m_nResolution, m_nResolution);
	
		glRotatef(110.0f, 1.0, 0.0, 0.0); // 90.0; 110
		glTranslatef(0.0f, 0.0f, 0.001f);
		glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient[nStartType]);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse[nStartType]);
		glutSolidSphere(radius_start, m_nResolution, m_nResolution);
	
	glPopMatrix();
}


void CQuartersphereCommand::SetResolution(int resolution)
{
	m_nResolution = resolution;
}

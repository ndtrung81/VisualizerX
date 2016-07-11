// HemisphereCommand.cpp: implementation of the CHemisphereCommand class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "visualizer_x.h"
#include "HemisphereCommand.h"

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

CHemisphereCommand::CHemisphereCommand()
{
	m_nResolution = 32;
}

CHemisphereCommand::~CHemisphereCommand()
{

}

void CHemisphereCommand::SetEndPoints(CPosition* startPoint, CPosition* endPoint)
{
	m_startPoint	= startPoint;
	m_endPoint		= endPoint;
}

void CHemisphereCommand::SetRadius(double radius)
{
	m_radius0 = m_radius = radius;
}

void CHemisphereCommand::Execute(GLfloat** materialAmbient, GLfloat** materialDiffuse, int* hiddenType)
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
		
		glTranslatef(0.0f, 0.0f, 0.001f);
		glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient[nEndType]);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse[nEndType]);
		glutSolidSphere(radius_end, m_nResolution, m_nResolution);
	glPopMatrix();
}


void CHemisphereCommand::SetResolution(int resolution)
{
	m_nResolution = resolution;
}

void CHemisphereCommand::DrawHemisphere(double r, int lats, int longs, int mode) 
{
	int start, end;
	int i, j;
	if (mode == 0)
	{
		start = 0; 
		end = lats/2;
	}
	else
	{
		start = lats/2+1; 
		end = lats-1;
	}

	for(i = start; i <= end; i++) 
	{
		double lat0 = PI * (-0.5 + (double) (i - 1) / lats);
		double z0  = sin(lat0);
		double zr0 =  cos(lat0);
		
		double lat1 = PI * (-0.5 + (double) i / lats);
		double z1 = sin(lat1);
		double zr1 = cos(lat1);
		
		glBegin(GL_QUAD_STRIP);
		for(j = 0; j <= longs; j++) 
		{
			double lng = 2 * PI * (double) (j - 1) / longs;
			double x = r*cos(lng);
			double y = r*sin(lng);
			
			glNormal3f(x * zr0, y * zr0, r*z0);
			glVertex3f(x * zr0, y * zr0, r*z0);
			glNormal3f(x * zr1, y * zr1, r*z1);
			glVertex3f(x * zr1, y * zr1, r*z1);
		}
		glEnd();
	}

}
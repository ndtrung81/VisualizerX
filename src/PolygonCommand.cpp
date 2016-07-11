// PolygonCommand.cpp: implementation of the CPolygonCommand class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "visualizer_x.h"
#include "PolygonCommand.h"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

using namespace std;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPolygonCommand::CPolygonCommand()
{
	m_scale = 1.0;
	m_nType = -1;
}

CPolygonCommand::~CPolygonCommand()
{

}

void CPolygonCommand::AddVertex(CPosition* vertex)
{
	m_vertexArray.push_back(vertex);
}

void CPolygonCommand::Execute(GLfloat** materialAmbient, GLfloat** materialDiffuse, int* hiddenType)
{
	int i;
	
	int nType;
	if (m_nType < 0)
		nType = m_vertexArray[0]->GetType();
	else 
		nType = m_nType;

	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient[nType]);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse[nType]);

	float x, y, z;
	FindNormal();
	double radius = m_vertexArray[0]->GetRadius();

	glBegin(GL_POLYGON);
		glNormal3f(m_nx, m_ny, m_nz);
		for (i=0; i<m_vertexArray.size(); i++)
		{
			x = (*m_vertexArray[i])[0] + m_nx * radius;
			y = (*m_vertexArray[i])[1] + m_ny * radius;
			z = (*m_vertexArray[i])[2] + m_nz * radius;
		//	glVertex3f((*m_vertexArray[i])[0], (*m_vertexArray[i])[1], (*m_vertexArray[i])[2]);
			glVertex3f(x, y, z);
		}
	glEnd();
}

void CPolygonCommand::FindNormal()
{
	double r1[3], r2[3];
	r1[0] = (*m_vertexArray[0])[0] - (*m_vertexArray[1])[0];
	r1[1] = (*m_vertexArray[0])[1] - (*m_vertexArray[1])[1];
	r1[2] = (*m_vertexArray[0])[2] - (*m_vertexArray[1])[2];

	r2[0] = (*m_vertexArray[0])[0] - (*m_vertexArray[2])[0];
	r2[1] = (*m_vertexArray[0])[1] - (*m_vertexArray[2])[1];
	r2[2] = (*m_vertexArray[0])[2] - (*m_vertexArray[2])[2];

	// Normal vector = r1 x r2
	m_nx = r1[1] * r2[2] - r1[2] * r2[1];
	m_ny =-r1[0] * r2[2] + r1[2] * r2[0];
	m_nz = r1[0] * r2[1] - r1[1] * r2[0];

	double norm = 1.0 / sqrt(m_nx * m_nx + m_ny * m_ny + m_nz * m_nz);
	m_nx *= norm;
	m_ny *= norm;
	m_nz *= norm;
}

void CPolygonCommand::Zoom(double scale)
{
	m_scale = scale;
}


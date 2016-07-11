// Sphere.cpp: implementation of the CSphere class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "visualizer_x.h"
#include "Sphere.h"
#include <string>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

using namespace std;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSphere::CSphere()
{
	m_positionArray.push_back(CPosition(0.0, 0.0, 0.0));

	m_bDrawn = TRUE;
	m_nType = 0;
	m_radius = 0.02;
	m_nSlices = 8;
	m_nStacks = 8;
}

CSphere::~CSphere()
{

}

CSphere::CSphere(char* type, double* data)
{
	m_positionArray.push_back(CPosition(data));

	if (strcmp(type, "C") == 0 || strcmp(type, "0") == 0)		
		m_positionArray[0].SetType(0);
	else if (strcmp(type, "N") == 0 || strcmp(type, "1") == 0)	
		m_positionArray[0].SetType(1);
	else if (strcmp(type, "P") == 0 || strcmp(type, "2") == 0)	
		m_positionArray[0].SetType(2);
	else if (strcmp(type, "O") == 0 || strcmp(type, "3") == 0)	
		m_positionArray[0].SetType(3);
	else if (strcmp(type, "S") == 0 || strcmp(type, "4") == 0)	
		m_positionArray[0].SetType(4);
	else if (strcmp(type, "Mg") == 0 || strcmp(type, "5") == 0)	
		m_positionArray[0].SetType(5);
	else if (strcmp(type, "Fe") == 0 || strcmp(type, "6") == 0)	
		m_positionArray[0].SetType(6);
	else if (strcmp(type, "H") == 0 || strcmp(type, "7") == 0)	
		m_positionArray[0].SetType(7);
	else
		m_positionArray[0].SetType(0);

	m_bDrawn = TRUE;
	m_radius = 0.02;
	m_nSlices = 8;
	m_nStacks = 8;
}

void CSphere::SetCenter(double x, double y, double z)
{
	m_positionArray[0][0] = x;
	m_positionArray[0][1] = y;
	m_positionArray[0][2] = z;
}

void CSphere::BoxScaling(double Lx, double Ly, double Lz, double boxSizex, double boxSizey, double boxSizez)
{
	m_radius = 0.5 / Lx * boxSizex;
	m_positionArray[0].SetRadius(m_radius);

	CParticle::BoxScaling(Lx, Ly, Lz, boxSizex, boxSizey, boxSizez);
}
// Position.cpp: implementation of the CPosition class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "visualizer_x.h"
#include "Position.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

using namespace std;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPosition::CPosition()
{
	m_data[0] = 0.0;
	m_data[1] = 0.0;
	m_data[2] = 0.0;

	m_color[0] = 1.0;
	m_color[1] = 1.0;
	m_color[2] = 1.0;

	m_nType = 0;

	m_radius = 1.0; //0.02;
}

CPosition::CPosition(const CPosition& pos)
{
	m_data[0] = pos.m_data[0];
	m_data[1] = pos.m_data[1];
	m_data[2] = pos.m_data[2];

	m_color[0] = pos.m_color[0];
	m_color[1] = pos.m_color[1];
	m_color[2] = pos.m_color[2];

	m_nType = pos.m_nType;

	m_radius = pos.m_radius;
}

CPosition::CPosition(double x, double y, double z)
{
	m_data[0] = x;
	m_data[1] = y;
	m_data[2] = z;

	m_color[0] = 1.0;
	m_color[1] = 1.0;
	m_color[2] = 1.0;

	m_nType = 0;

	m_radius = 1.0; //0.02;
}

CPosition::CPosition(double* data)
{
	m_data[0] = data[0];
	m_data[1] = data[1];
	m_data[2] = data[2];

	m_color[0] = 1.0;
	m_color[1] = 1.0;
	m_color[2] = 1.0;

	m_nType = 0;

	m_radius = 1.0; //0.02;
}

CPosition::~CPosition()
{

}

//////////////////////////////////////////////////////////////////////
//
CPosition& CPosition::operator= (const CPosition& pos)
{
	if (this == &pos)
		return *this;

	m_data[0] = pos[0];
	m_data[1] = pos[1];
	m_data[2] = pos[2];

	m_color[0] = pos.m_color[0];
	m_color[1] = pos.m_color[1];
	m_color[2] = pos.m_color[2];

	m_nType = pos.m_nType;
	m_nPBC = 1;
	m_radius = pos.m_radius;

	return *this;
}

double CPosition::operator [] (int i) const
{
	return m_data[i];
}

double& CPosition::operator [] (int i)
{
	return m_data[i];
}

void CPosition::SetRadius(double radius)
{
	m_radius = radius;
}

double CPosition::GetRadius()
{
	return m_radius;
}

void CPosition::GetColor(double& red, double& green, double& blue)
{
	red		= m_color[0];
	green	= m_color[1];
	blue	= m_color[2];
}

void CPosition::SetColor(double red, double green, double blue)
{
	m_color[0] = red;
	m_color[1] = green;
	m_color[2] = blue;
}

int	CPosition::GetType()
{
	return m_nType;
}

void CPosition::SetType(int nType)
{
	m_nType = nType;

	switch (nType)
	{
	case 1:
		m_color[0] = 1.0;
		m_color[1] = 1.0;
		m_color[2] = 1.0;
		break;
	case 2:
		m_color[0] = 1.0;
		m_color[1] = 0.0;
		m_color[2] = 0.0;
		break;
	}
}

int	CPosition::GetPBC()
{
	return m_nPBC;
}

void CPosition::SetPBC(int nPBC)
{
	m_nPBC = nPBC;
}

void CPosition::Write(std::ostream& os)
{
	switch (m_nType)
	{
	case 0:
		os << "C\t";
		break;
	case 1:
		os << "N\t";
		break;
	case 2:
		os << "P\t";
		break;
	case 3:
		os << "O\t";
		break;
	case 4:
		os << "S\t";
		break;
	case 5:
		os << "Mg\t";
		break;
	default:
		break;
	};

	os << m_data[0] << "\t" << m_data[1] << "\t" << m_data[2] << std::endl;
}

void CPosition::Read(std::istream& is)
{
	int	nType;
	double x, y, z, red, green, blue, radius;
	char identifier[10];

	is >> identifier >> x >> y >> z;
	
	m_data[0] = x;
	m_data[1] = y;
	m_data[2] = z;
	
	while (1)
	{
		is >> identifier;
		if (strcmp(identifier, "-") == 0)
			break;
		else if (strcmp(identifier, "c") == 0)
		{
			is >> red >> green >> blue;
			SetColor(red, green, blue);
		}
		else if (strcmp(identifier, "t") == 0)
		{
			is >> nType;
			SetType(nType);
		}
		else if (strcmp(identifier, "r") == 0)
		{
			is >> radius;
			SetRadius(radius);
		}
	}
}
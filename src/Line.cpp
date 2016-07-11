// Line.cpp: implementation of the CLine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "visualizer_x.h"
#include "Line.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLine::CLine()
{

}

CLine::~CLine()
{

}

std::istream& CLine::Read(std::istream& is)
{
	std::string identifier;
	double red, green, blue;
	int	nType;
	CPosition start, end;

	is >> start[0] >> start[1] >> start[2] >> end[0] >> end[1] >> end[2];
	m_positionArray.push_back(start);
	m_positionArray.push_back(end);

	BOOL bDone = FALSE;
	while (!bDone)
	{
		is >> identifier;
		if (strcmp(identifier.data(), "c") == 0)
		{
			is >> red >> green >> blue;
			SetColor(red, green, blue);
		}
		else if (strcmp(identifier.data(), "t") == 0)
		{
			is >> nType;
			SetType(nType);
		}
		else if (strcmp(identifier.data(), "-") == 0)
		{
			bDone = TRUE;
		}
	}

	AddDrawingCommand("[LINE]\t0\t1\n");

	return is;
}

void CLine::Draw()
{
	int i;

	for (i=0; i<m_commandArray.size(); i++)
		m_commandArray[i]->Execute();
}
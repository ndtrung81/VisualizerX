// LineCommand.cpp: implementation of the CLineCommand class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "visualizer_x.h"
#include "LineCommand.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLineCommand::CLineCommand()
{
	m_startPoint = 0x0;
	m_endPoint = 0x0;
	m_width = 1.5;
}

CLineCommand::CLineCommand(const CLineCommand& command)
{
	m_startPoint	= command.m_startPoint;
	m_endPoint		= command.m_endPoint;
	m_width			= command.m_width;
}

CLineCommand::~CLineCommand()
{

}

void CLineCommand::SetEndPoints(CPosition* startPoint, CPosition* endPoint)
{
	m_startPoint	= startPoint;
	m_endPoint		= endPoint;
}

void CLineCommand::Execute(GLfloat** materialAmbient, GLfloat** materialDiffuse, int* hiddenType)
{
//	int nType = m_startPoint->GetType();
//	if (hiddenType[nType] == TRUE)
//		return;
	
	glLineWidth(m_width);

	GLfloat ambient[4], diffuse[4];
	ambient[0] = 0.0;
	ambient[1] = 0.0;
	ambient[2] = 0.0;
	ambient[3] = 1.0;

	diffuse[0] = 0.0;
	diffuse[1] = 0.0;
	diffuse[2] = 0.0;
	diffuse[3] = 1.0;

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);

	glBegin(GL_LINE_STRIP);
		glVertex3f((*m_startPoint)[0], (*m_startPoint)[1], (*m_startPoint)[2]);
		glVertex3f((*m_endPoint)[0], (*m_endPoint)[1], (*m_endPoint)[2]);
	glEnd();
}
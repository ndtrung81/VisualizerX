// DrawingCommand.cpp: implementation of the CDrawingCommand class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "visualizer_x.h"
#include "DrawingCommand.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDrawingCommand::CDrawingCommand()
{

}

CDrawingCommand::~CDrawingCommand()
{

}

void CDrawingCommand::Execute(GLfloat** materialAmbient, GLfloat** materialDiffuse, int* hiddenType)
{

}

void CDrawingCommand::ExportToPOV(std::ofstream& os)
{

}

void CDrawingCommand::Zoom(double scale)
{
}

void CDrawingCommand::SetResolution(int resolution)
{
}

void CDrawingCommand::SetColoringType(int nType)
{
	m_nType = nType;
}

CDrawingCommand* CDrawingCommand::Clone()
{
	return new CDrawingCommand();
}
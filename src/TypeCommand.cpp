// TypeCommand.cpp: implementation of the CTypeCommand class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "visualizer_x.h"
#include "TypeCommand.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTypeCommand::CTypeCommand()
{

}

CTypeCommand::~CTypeCommand()
{

}

void CTypeCommand::SetTypeIndex(CPosition* position, char* type)
{
	m_position = position;

	if (strcmp(type, "C") == 0 || strcmp(type, "1") == 0)		
		m_position->SetType(0);
	else if (strcmp(type, "N") == 0 || strcmp(type, "2") == 0)	
		m_position->SetType(1);
	else if (strcmp(type, "P") == 0 || strcmp(type, "3") == 0)	
		m_position->SetType(2);
	else if (strcmp(type, "O") == 0 || strcmp(type, "4") == 0)	
		m_position->SetType(3);
	else if (strcmp(type, "S") == 0 || strcmp(type, "5") == 0)	
		m_position->SetType(4);
	else if (strcmp(type, "Mg") == 0 || strcmp(type, "6") == 0)	
		m_position->SetType(5);
	else if (strcmp(type, "Fe") == 0 || strcmp(type, "7") == 0)	
		m_position->SetType(6);
	else if (strcmp(type, "H") == 0 || strcmp(type, "8") == 0)	
		m_position->SetType(7);
}

void CTypeCommand::Execute(GLfloat** materialAmbient, GLfloat** materialDiffuse, int* hiddenType)
{

}


// TypeCommand.h: interface for the CTypeCommand class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TYPECOMMAND_H__C6DF76FE_446E_418D_B21D_0297DC872090__INCLUDED_)
#define AFX_TYPECOMMAND_H__C6DF76FE_446E_418D_B21D_0297DC872090__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DrawingCommand.h"
#include "Position.h"

class CTypeCommand : public CDrawingCommand  
{
public:
	CTypeCommand();
	virtual ~CTypeCommand();

	void	SetTypeIndex(CPosition* position, char* type);
	
	void	Execute(GLfloat** materialAmbient, GLfloat** materialDiffuse, int* hiddenType);

protected:
	CPosition*	m_position;
	int m_nType;
};

#endif // !defined(AFX_TYPECOMMAND_H__C6DF76FE_446E_418D_B21D_0297DC872090__INCLUDED_)

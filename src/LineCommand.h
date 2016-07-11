// LineCommand.h: interface for the CLineCommand class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LINECOMMAND_H__D9A9D113_4CBC_4D76_B31F_8F923FC9EE5B__INCLUDED_)
#define AFX_LINECOMMAND_H__D9A9D113_4CBC_4D76_B31F_8F923FC9EE5B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DrawingCommand.h"
#include "Position.h"

class CLineCommand : public CDrawingCommand  
{
public:
	CLineCommand();
	CLineCommand(const CLineCommand& command);
	virtual ~CLineCommand();

	void	SetEndPoints(CPosition* startPoint, CPosition* endPoint);

	void	Execute(GLfloat** materialAmbient, GLfloat** materialDiffuse, int* hiddenType);

protected:
	CPosition* m_startPoint, *m_endPoint;
	int m_width;
};

#endif // !defined(AFX_LINECOMMAND_H__D9A9D113_4CBC_4D76_B31F_8F923FC9EE5B__INCLUDED_)

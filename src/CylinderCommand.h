// CylinderCommand.h: interface for the CCylinderCommand class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CYLINDERCOMMAND_H__D81A51CB_18FF_4655_9D20_1A2115622DCB__INCLUDED_)
#define AFX_CYLINDERCOMMAND_H__D81A51CB_18FF_4655_9D20_1A2115622DCB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DrawingCommand.h"
#include "Position.h"

class CCylinderCommand : public CDrawingCommand  
{
public:
	CCylinderCommand();
	virtual ~CCylinderCommand();

	void	Zoom(double scale);

	void	SetEndPoints(CPosition* startPoint, CPosition* endPoint);
	void	SetRadius(double radius);
	void	SetResolution(int resolution);
	
	void	Execute(GLfloat** materialAmbient, GLfloat** materialDiffuse, int* hiddenType);

protected:
	CPosition* m_startPoint, *m_endPoint;
	double m_radius, m_radius0;
	GLUquadricObj* cyl;
	int m_nResolution;
};

#endif // !defined(AFX_CYLINDERCOMMAND_H__D81A51CB_18FF_4655_9D20_1A2115622DCB__INCLUDED_)

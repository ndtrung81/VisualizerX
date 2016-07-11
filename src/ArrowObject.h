// ArrowObject.h: interface for the CArrowObject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ARROWOBJECT_H__8DF090CE_370A_4D71_A3D2_EA6F6BAA5F04__INCLUDED_)
#define AFX_ARROWOBJECT_H__8DF090CE_370A_4D71_A3D2_EA6F6BAA5F04__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DrawingObject.h"
#include "Position.h"

class CArrowObject : public CDrawingObject  
{
public:
	CArrowObject();
	virtual ~CArrowObject();

	void Draw(GLfloat** materialAmbient, GLfloat** materialDiffuse, int* hiddenType, int nResolution);

	void	SetPosition(CPosition* pos);
	void	SetDirection(double dirx, double diry, double dirz);	
	void	SetMagnitude(double magnitude);

	double m_magnitude;
	CPosition* m_position;
	double	m_dirx, m_diry, m_dirz;
	

};

#endif // !defined(AFX_ARROWOBJECT_H__8DF090CE_370A_4D71_A3D2_EA6F6BAA5F04__INCLUDED_)

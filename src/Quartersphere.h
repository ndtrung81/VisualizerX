// Quartersphere.h: interface for the CQuartersphere class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_QUARTERSPHERE_H__5EC15384_ED16_4375_AA7F_1089AB0FEAC3__INCLUDED_)
#define AFX_QUARTERSPHERE_H__5EC15384_ED16_4375_AA7F_1089AB0FEAC3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DrawingCommand.h"

class CQuartersphere : public CDrawingCommand  
{
public:
	CQuartersphere();
	virtual ~CQuartersphere();
	
	void	SetEndPoints(CPosition* startPoint, CPosition* endPoint);
	void	SetRadius(double radius);
	void	SetResolution(int resolution);
	
	void	Execute(GLfloat** materialAmbient, GLfloat** materialDiffuse, int* hiddenType);

protected:
	CPosition* m_startPoint, *m_endPoint;
	double m_radius, m_radius0;
	int m_nResolution;
};

#endif // !defined(AFX_QUARTERSPHERE_H__5EC15384_ED16_4375_AA7F_1089AB0FEAC3__INCLUDED_)

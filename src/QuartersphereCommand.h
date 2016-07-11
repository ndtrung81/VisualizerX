// QuartersphereCommand.h: interface for the CQuartersphereCommand class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_QUARTERSPHERECOMMAND_H__0EDB965F_7559_43FA_9A9F_27E2DBD501D3__INCLUDED_)
#define AFX_QUARTERSPHERECOMMAND_H__0EDB965F_7559_43FA_9A9F_27E2DBD501D3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DrawingCommand.h"
#include "Position.h"

class CQuartersphereCommand : public CDrawingCommand  
{
public:
	CQuartersphereCommand();
	virtual ~CQuartersphereCommand();

	void	SetEndPoints(CPosition* startPoint, CPosition* endPoint);
	void	SetRadius(double radius);
	void	SetResolution(int resolution);
	
	void	Execute(GLfloat** materialAmbient, GLfloat** materialDiffuse, int* hiddenType);

protected:
	CPosition* m_startPoint, *m_endPoint;
	double m_radius, m_radius0;
	int m_nResolution;
};

#endif // !defined(AFX_QUARTERSPHERECOMMAND_H__0EDB965F_7559_43FA_9A9F_27E2DBD501D3__INCLUDED_)

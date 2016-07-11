// HemisphereCommand.h: interface for the CHemisphereCommand class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HEMISPHERECOMMAND_H__AD765057_1F1E_41DD_B0C5_1F0A2E6341E2__INCLUDED_)
#define AFX_HEMISPHERECOMMAND_H__AD765057_1F1E_41DD_B0C5_1F0A2E6341E2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DrawingCommand.h"
#include "Position.h"

class CHemisphereCommand : public CDrawingCommand  
{
public:
	CHemisphereCommand();
	virtual ~CHemisphereCommand();

	void	SetEndPoints(CPosition* startPoint, CPosition* endPoint);
	void	SetRadius(double radius);
	void	SetResolution(int resolution);
	
	void	Execute(GLfloat** materialAmbient, GLfloat** materialDiffuse, int* hiddenType);

protected:
	void DrawHemisphere(double r, int lats, int longs, int mode);
	CPosition* m_startPoint, *m_endPoint;
	double m_radius, m_radius0;
	int m_nResolution;
};

#endif // !defined(AFX_HEMISPHERECOMMAND_H__AD765057_1F1E_41DD_B0C5_1F0A2E6341E2__INCLUDED_)

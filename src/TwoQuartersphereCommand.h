// TwoQuartersphereCommand.h: interface for the CTwoQuartersphereCommand class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TWOQUARTERSPHERECOMMAND_H__3CF46CBA_34BA_4A8F_A1A5_2C9F19B32F6F__INCLUDED_)
#define AFX_TWOQUARTERSPHERECOMMAND_H__3CF46CBA_34BA_4A8F_A1A5_2C9F19B32F6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DrawingCommand.h"
#include "Position.h"

class CTwoQuartersphereCommand : public CDrawingCommand  
{
public:
	CTwoQuartersphereCommand();
	virtual ~CTwoQuartersphereCommand();

	void	SetEndPoints(CPosition* startPoint, CPosition* endPoint);
	void	SetRadius(double radius);
	void	SetResolution(int resolution);
	
	void	Execute(GLfloat** materialAmbient, GLfloat** materialDiffuse, int* hiddenType);

protected:
	CPosition* m_startPoint, *m_endPoint;
	double m_radius, m_radius0;
	int m_nResolution;
};

#endif // !defined(AFX_TWOQUARTERSPHERECOMMAND_H__3CF46CBA_34BA_4A8F_A1A5_2C9F19B32F6F__INCLUDED_)

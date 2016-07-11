// SphereCommand.h: interface for the CSphereCommand class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPHERECOMMAND_H__DDC62D87_D332_45DD_8288_7B8CFB690916__INCLUDED_)
#define AFX_SPHERECOMMAND_H__DDC62D87_D332_45DD_8288_7B8CFB690916__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DrawingCommand.h"
#include "Position.h"

class CSphereCommand : public CDrawingCommand  
{
public:
	CSphereCommand();
	virtual ~CSphereCommand();

	void	Zoom(double scale);

	void	SetCenter(CPosition* center);
	void	SetRadius(double radius);
	void	SetResolution(int nResolution);

	void	Execute(GLfloat** materialAmbient, GLfloat** materialDiffuse, int* hiddenType);

protected:
	CPosition*	m_center;
	double m_radius, m_radius0;
	int m_nResolution;
};

#endif // !defined(AFX_SPHERECOMMAND_H__DDC62D87_D332_45DD_8288_7B8CFB690916__INCLUDED_)

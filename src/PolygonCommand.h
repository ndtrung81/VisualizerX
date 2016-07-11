// PolygonCommand.h: interface for the CPolygonCommand class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POLYGONCOMMAND_H__F4242E7F_923D_4910_A9D2_C8A2DC78C423__INCLUDED_)
#define AFX_POLYGONCOMMAND_H__F4242E7F_923D_4910_A9D2_C8A2DC78C423__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DrawingCommand.h"
#include "Position.h"
#include <vector>

class CPolygonCommand : public CDrawingCommand  
{
public:
	CPolygonCommand();
	virtual ~CPolygonCommand();
	
	void	AddVertex(CPosition* vertex);

	void	Execute(GLfloat** materialAmbient, GLfloat** materialDiffuse, int* hiddenType);
	void	Zoom(double scale);

protected:
	void	FindNormal();
	std::vector<CPosition*> m_vertexArray;
	double	m_nx, m_ny, m_nz;
	double	m_scale;
};

#endif // !defined(AFX_POLYGONCOMMAND_H__F4242E7F_923D_4910_A9D2_C8A2DC78C423__INCLUDED_)

// SphereObject.h: interface for the CSphereObject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPHEREOBJECT_H__9CD73680_37AB_4D3F_8E23_2686114A1262__INCLUDED_)
#define AFX_SPHEREOBJECT_H__9CD73680_37AB_4D3F_8E23_2686114A1262__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DrawingObject.h"

class CSphereObject : public CDrawingObject  
{
public:
	CSphereObject();
	virtual ~CSphereObject();

	void SetRadius(double radius);
	void SetCenter(double x, double y, double z);

	void Draw(GLfloat** materialAmbient, GLfloat** materialDiffuse, int* hiddenType, int nResolution);

	double m_radius;
	double m_center[3];
};

#endif // !defined(AFX_SPHEREOBJECT_H__9CD73680_37AB_4D3F_8E23_2686114A1262__INCLUDED_)

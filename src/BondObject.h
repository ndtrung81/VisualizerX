// BondObject.h: interface for the CBondObject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BONDOBJECT_H__0CB1273F_1E69_4F47_ADCE_AB4F4882D972__INCLUDED_)
#define AFX_BONDOBJECT_H__0CB1273F_1E69_4F47_ADCE_AB4F4882D972__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DrawingObject.h"
#include "Position.h"

class CBondObject : public CDrawingObject  
{
public:
	CBondObject();
	virtual ~CBondObject();

	void Draw(GLfloat** materialAmbient, GLfloat** materialDiffuse, int* hiddenType, int nResolution);

	void SetPosition(CPosition* pos1, CPosition* pos2);
	void SetBox(double boxSizex, double boxSizey, double boxSizez);

	CPosition* m_position1, *m_position2;
	double m_boxSizex, m_boxSizey, m_boxSizez;
};

#endif // !defined(AFX_BONDOBJECT_H__0CB1273F_1E69_4F47_ADCE_AB4F4882D972__INCLUDED_)

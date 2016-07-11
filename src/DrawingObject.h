// DrawingObject.h: interface for the CDrawingObject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRAWINGOBJECT_H__CEFB05FA_80EC_42FB_A949_53AE42D79C6A__INCLUDED_)
#define AFX_DRAWINGOBJECT_H__CEFB05FA_80EC_42FB_A949_53AE42D79C6A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDrawingObject  
{
public:
	CDrawingObject();
	virtual ~CDrawingObject();

	virtual void Draw(GLfloat** materialAmbient, GLfloat** materialDiffuse, int* hiddenType, int nResolution);

	int m_nType;
	BOOL m_bUseParticleType;
	double m_scale;
	int m_nParticleIndex;
};

#endif // !defined(AFX_DRAWINGOBJECT_H__CEFB05FA_80EC_42FB_A949_53AE42D79C6A__INCLUDED_)

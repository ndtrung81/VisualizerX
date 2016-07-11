// DrawingCommand.h: interface for the CDrawingCommand class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRAWINGCOMMAND_H__2DBF9813_AA21_4E0A_8AC2_F59C9A7114BF__INCLUDED_)
#define AFX_DRAWINGCOMMAND_H__2DBF9813_AA21_4E0A_8AC2_F59C9A7114BF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include <iostream>

class CDrawingCommand  
{
public:
	CDrawingCommand();
	virtual ~CDrawingCommand();

	virtual void	Execute(GLfloat** materialAmbient, GLfloat** materialDiffuse, int* hiddenType);
	virtual void	ExportToPOV(std::ofstream& os);
	virtual void	Zoom(double scale);
	virtual void	SetResolution(int resolution);
	virtual	void	SetColoringType(int nType);
	virtual CDrawingCommand* Clone();

	int m_nType;
};

#endif // !defined(AFX_DRAWINGCOMMAND_H__2DBF9813_AA21_4E0A_8AC2_F59C9A7114BF__INCLUDED_)

// Particle.h: interface for the CParticle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PARTICLE_H__DD57C363_57A3_45B9_91A8_264972E980DA__INCLUDED_)
#define AFX_PARTICLE_H__DD57C363_57A3_45B9_91A8_264972E980DA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning (disable : 4786) // this is to disable the warning raised by std::vector<std::string>

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Position.h"
#include "DrawingCommand.h"

typedef enum __type
{
	__TYPE0 = 1,
	__TYPE1 = 2,
	__TYPE2 = 4,
	__TYPE3 = 8,
	__TYPE4 = 16,
} _particle_type;


#define anint(x) ((x >= 0.5) ? (1.0) : (x < -0.5) ? (-1.0) : (0.0))

class CParticle  
{
public:
	CParticle();
	CParticle(const CParticle& particle);
	virtual ~CParticle();

	virtual void	Read(std::istream& is);
	virtual void	Write(std::ostream& os, BOOL* nHiddenType);
	virtual void	Zoom(double scale);
	virtual void	Translate(double tx, double ty, double tz, double boxSizex, double boxSizey, double boxSizez);
	virtual void	Draw(GLfloat** materialAmbient, GLfloat** materialDiffuse, int* hiddenType, int nResolution=16);
	virtual void	ReleasePeriodicBoundaryConditions(double* L);
	virtual	void	DrawPOV(std::ostream& os, GLfloat** materialAmbient, GLfloat** materialDiffuse, int* hiddenType, int nResolution=16);

	void	BoxScaling(double Lx, double Ly, double Lz, double boxSizex, double boxSizey, double boxSizez);
	void	AddSite(const CPosition& position);
	void	SetSite(int i, const CPosition& position);
	void	SetSite(int i, double* pos);
	void	SetType(int nType);

public:
	void FindCenterofMass(double* xm);


	struct CDrawingTemplate
	{
		CDrawingTemplate();
		CDrawingTemplate(const CDrawingTemplate& drawingTemplate);
		CDrawingTemplate& operator = (const CDrawingTemplate& drawingTemplate);
		~CDrawingTemplate();
		
		std::vector<std::string>	m_drawingCommands;		
	};

	void	AddDrawingCommand(const char* command);
	int		ReadDrawingTemplate(const char* sFileName);
	int		ReadDrawingTemplate(std::istream& is);

	void	ParseDrawingTemplate();
	void	SetDrawingTemplate(const CParticle::CDrawingTemplate& drawingTemplate);
	CParticle::CDrawingTemplate	GetDrawingTemplate();
		
public:
	std::vector<CPosition>			m_positionArray;
	std::vector<CDrawingCommand*>	m_commandArray;
	CParticle::CDrawingTemplate		m_drawingTemplate;

	int		m_nType;
	BOOL	m_bDrawn;
	int		m_nApplyingCommand;
	GLfloat m_color[3];
	double	m_scale;
	
protected:

};

#endif // !defined(AFX_PARTICLE_H__DD57C363_57A3_45B9_91A8_264972E980DA__INCLUDED_)

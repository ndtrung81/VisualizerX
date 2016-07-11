// Line.h: interface for the CLine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LINE_H__A9CEBBA1_DC0C_4F23_A0B8_F7261717FFBD__INCLUDED_)
#define AFX_LINE_H__A9CEBBA1_DC0C_4F23_A0B8_F7261717FFBD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Particle.h"

class CLine : public CParticle  
{
public:
	CLine();
	virtual ~CLine();

	virtual void	Read(std::istream& is);
	virtual void	Draw();

protected:
	
};

#endif // !defined(AFX_LINE_H__A9CEBBA1_DC0C_4F23_A0B8_F7261717FFBD__INCLUDED_)

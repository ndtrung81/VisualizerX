// Sphere.h: interface for the CSphere class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPHERE_H__657D1B35_8582_434D_8261_E5A06320535E__INCLUDED_)
#define AFX_SPHERE_H__657D1B35_8582_434D_8261_E5A06320535E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Particle.h"

class CSphere : public CParticle  
{
public:
	CSphere();
	CSphere(char* type, double* data);
	virtual ~CSphere();

	void	SetCenter(double x, double y, double z);
	void	BoxScaling(double Lx, double Ly, double Lz, double boxSizex, double boxSizey, double boxSizez);


protected:
	double	m_radius;
	int		m_nSlices, m_nStacks;
};

#endif // !defined(AFX_SPHERE_H__657D1B35_8582_434D_8261_E5A06320535E__INCLUDED_)

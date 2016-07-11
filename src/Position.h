// Position.h: interface for the CPosition class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POSITION_H__5606DEA5_9C79_437A_BC16_AEAB264DE920__INCLUDED_)
#define AFX_POSITION_H__5606DEA5_9C79_437A_BC16_AEAB264DE920__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <iostream>

class CPosition  
{
public:
	CPosition();
	CPosition(const CPosition& pos);
	CPosition(double x, double y, double z);
	CPosition(double* data);
	virtual ~CPosition();

	CPosition& operator= (const CPosition& pos);
	void	GetColor(double& red, double& green, double& blue);
	void	SetColor(double red, double green, double blue);
	int		GetType();
	void	SetType(int nType);
	int		GetPBC();
	void	SetPBC(int nPBC);

	void	SetRadius(double radius);
	double	GetRadius();

	void	Read(std::istream& is);
	void	Write(std::ostream& os);

	double operator [] (int i) const;
	double& operator [] (int i);

protected:	
	double	m_data[3];
	double	m_radius;
	double	m_color[3];
	int		m_nType;
	int		m_nPBC;
};

#endif // !defined(AFX_POSITION_H__5606DEA5_9C79_437A_BC16_AEAB264DE920__INCLUDED_)

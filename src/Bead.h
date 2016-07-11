// Bead.h: interface for the CBead class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BEAD_H__C22E8605_5C77_4F8B_9E7D_528E0FCD5DE0__INCLUDED_)
#define AFX_BEAD_H__C22E8605_5C77_4F8B_9E7D_528E0FCD5DE0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CBead  
{
public:
	CBead();
	CBead(const CBead& bead);
	CBead(double* pos);

	virtual ~CBead();

	CBead& operator = (const CBead& bead);
	
	
	double m_pos[3];
};

#endif // !defined(AFX_BEAD_H__C22E8605_5C77_4F8B_9E7D_528E0FCD5DE0__INCLUDED_)

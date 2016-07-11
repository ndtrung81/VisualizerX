// Bead.cpp: implementation of the CBead class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "visualizer_x.h"
#include "Bead.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBead::CBead()
{
	m_nType = 0;
	for (int i=0; i<3; i++)
		m_pos[i] = 0.0;
}

CBead::CBead(const CBead& bead)
{
	m_nType = bead.m_nType;
	for (int i=0; i<3; i++)
		m_pos[i] = bead.m_pos[i];
}

CBead::~CBead()
{

}

CBead& CBead::operator = (const CBead& bead)
{
	if (&bead == this)
		return *this;

	m_nType = bead.m_nType;
	for (int i=0; i<3; i++)
		m_pos[i] = bead.m_pos[i];

	return *this;
}

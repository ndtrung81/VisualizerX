// ModelessDialog.cpp: implementation of the CModelessDialog class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "visualizer_x.h"
#include "ModelessDialog.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CModelessDialog::CModelessDialog(UINT nID, CWnd* pParent) 
	: CDialog(nID, pParent)
{
	ASSERT(pParent != NULL);

	m_nID = nID;
	m_pParent = pParent;

}

CModelessDialog::~CModelessDialog()
{

}

BOOL CModelessDialog::Create()
{
	return CDialog::Create(m_nID, m_pParent);
}


void CModelessDialog::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	delete this;
}


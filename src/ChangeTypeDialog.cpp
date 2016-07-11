// ChangeTypeDialog.cpp : implementation file
//

#include "stdafx.h"
#include "visualizer_x.h"
#include "ChangeTypeDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChangeTypeDialog dialog


CChangeTypeDialog::CChangeTypeDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CChangeTypeDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChangeTypeDialog)
	m_nDestType = 0;
	m_nSrcType = 0;
	m_bSwap = FALSE;
	m_nLocalIndex = -1;
	//}}AFX_DATA_INIT
}


void CChangeTypeDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChangeTypeDialog)
	DDX_CBIndex(pDX, IDC_COMBO_DEST, m_nDestType);
	DDX_CBIndex(pDX, IDC_COMBO_SRC, m_nSrcType);
	DDX_Check(pDX, IDC_CHECK_SWAP, m_bSwap);
	DDX_Text(pDX, IDC_EDIT_INDEX, m_nLocalIndex);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChangeTypeDialog, CDialog)
	//{{AFX_MSG_MAP(CChangeTypeDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChangeTypeDialog message handlers

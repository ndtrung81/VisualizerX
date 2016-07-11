// ModelessDialog.h: interface for the CModelessDialog class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MODELESSDIALOG_H__B9CE2C8C_92E9_4DA9_BEAE_A1971B0B759C__INCLUDED_)
#define AFX_MODELESSDIALOG_H__B9CE2C8C_92E9_4DA9_BEAE_A1971B0B759C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CModelessDialog : public CDialog  
{
public:
	CModelessDialog(UINT nID, CWnd* pParent);
	virtual ~CModelessDialog();

	CWnd*	m_pParent;
	UINT	m_nID;
	BOOL	Create();	

	virtual void PostNcDestroy();
};

#endif // !defined(AFX_MODELESSDIALOG_H__B9CE2C8C_92E9_4DA9_BEAE_A1971B0B759C__INCLUDED_)

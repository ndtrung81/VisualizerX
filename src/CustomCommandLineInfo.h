// CustomCommandLineInfo.h: interface for the CCustomCommandLineInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CUSTOMCOMMANDLINEINFO_H__E1EE5782_21B8_4B8D_9F47_F8533C871FAD__INCLUDED_)
#define AFX_CUSTOMCOMMANDLINEINFO_H__E1EE5782_21B8_4B8D_9F47_F8533C871FAD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCustomCommandLineInfo : public CCommandLineInfo  
{
public:
	CCustomCommandLineInfo();
	virtual ~CCustomCommandLineInfo();

	virtual void ParseParam(const char* pszParam, BOOL bFlag, BOOL bLast);
	
	CString GetDataFileName();
	BOOL	DoesHaveInputFile();
	BOOL	DoesHaveInputData();
	int		GetDataType();
	BOOL	DoesOutputData();
protected:
	BOOL	m_bHasInputFile;
	BOOL	m_bOutputData;
	int		m_nDataType;
	BOOL	m_bHasInputData;
	CString	m_strDataFileName;
};

#endif // !defined(AFX_CUSTOMCOMMANDLINEINFO_H__E1EE5782_21B8_4B8D_9F47_F8533C871FAD__INCLUDED_)

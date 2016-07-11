// CustomCommandLineInfo.cpp: implementation of the CCustomCommandLineInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "visualizer_x.h"
#include "CustomCommandLineInfo.h"
#include <string>
#include <algorithm>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

using namespace std;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCustomCommandLineInfo::CCustomCommandLineInfo()
{
	m_bHasInputFile = FALSE;
	m_bHasInputData = FALSE;
	m_bOutputData = FALSE;
	m_nDataType = __VIS;
}

CCustomCommandLineInfo::~CCustomCommandLineInfo()
{

}

BOOL CCustomCommandLineInfo::DoesHaveInputFile()
{
	return m_bHasInputFile;
}

BOOL CCustomCommandLineInfo::DoesHaveInputData()
{
	return m_bHasInputData;
}

BOOL CCustomCommandLineInfo::DoesOutputData()
{
	return m_bOutputData;
}

BOOL CCustomCommandLineInfo::GetDataType()
{
	return m_nDataType;
}

CString CCustomCommandLineInfo::GetDataFileName()
{
	return m_strDataFileName;
}

void CCustomCommandLineInfo::ParseParam(const char* pszParam, BOOL bFlag, BOOL bLast)
{
	if (strcmp(pszParam, "s") == 0)
	{
		m_bHasInputData = TRUE;
		m_nDataType = __VIS;
	}
	else if (strcmp(pszParam, "o") == 0)
	{
		m_bOutputData = TRUE;
	}
	else if (strcmp(pszParam, "xyz") == 0)
	{
		m_bHasInputData = TRUE;
		m_nDataType = __XYZ;
	}
	else
	{
		string str(pszParam), entry, value;
		string::iterator itl, ith;
		
		itl = str.begin();
		ith = find(itl, str.end(), '=');
		
		entry.assign(itl, ith);
		value.assign(++ith, str.end());
		
		if (strcmp(entry.c_str(), "f") == 0)
		{
			m_bHasInputFile = TRUE;
			m_strDataFileName = value.data();
		}
	}
	
}

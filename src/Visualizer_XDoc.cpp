// Visualizer_XDoc.cpp : implementation of the CVisualizer_XDoc class
//

#include "stdafx.h"
#include "Visualizer_X.h"

#include "Visualizer_XDoc.h"
#include "Visualizer_XView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVisualizer_XDoc

IMPLEMENT_DYNCREATE(CVisualizer_XDoc, CDocument)

BEGIN_MESSAGE_MAP(CVisualizer_XDoc, CDocument)
	//{{AFX_MSG_MAP(CVisualizer_XDoc)
	ON_COMMAND(ID_FILE_WRITETOPOS, OnFileWritetopos)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVisualizer_XDoc construction/destruction

CVisualizer_XDoc::CVisualizer_XDoc()
{
	// TODO: add one-time construction code here
	m_particleScale = 0.72;
	m_particleScalingStep = 0.01;
	m_particleTranslatingStep = 0.05;
	m_objectScale = 1.0;
	m_minScale = 0.001;
	m_maxScale = 100.0;
	m_scaleCoeff = 0.001;
}

CVisualizer_XDoc::~CVisualizer_XDoc()
{
}

BOOL CVisualizer_XDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	
	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CVisualizer_XDoc serialization

void CVisualizer_XDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{

	
	}
	else
	{
		// TODO: add loading code here
		POSITION pos = GetFirstViewPosition();
		CVisualizer_XView* pView = (CVisualizer_XView*)GetNextView(pos);
		CFile* pFile = ar.GetFile();
		CString sFileName = pFile->GetFilePath();
		pView->ReadXYZFile(sFileName);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CVisualizer_XDoc diagnostics

#ifdef _DEBUG
void CVisualizer_XDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CVisualizer_XDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CVisualizer_XDoc commands

void CVisualizer_XDoc::OnFileWritetopos() 
{
	// TODO: Add your command handler code here
	
}

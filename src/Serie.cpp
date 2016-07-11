// Serie.cpp: implementation of the CSerie class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Visualizer_X.h"
#include "Serie.h"

#include <math.h>
#include "StrMan.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

using namespace std;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSerie::CSerie()
{
	m_bAuto		= TRUE;
	m_bDrawMarker	= FALSE;
	m_bDrawn	= TRUE;
	m_bShowLevel = FALSE;
	m_miny		= 0.0;
	m_maxy		= 1.0;
	m_nColor	= RGB(0, 0, 0);
	m_nGraphType= __LINE;
	m_nHighLightNode = -1;
	m_nLineWeight = 1;
	m_nLineType	= 0;	
	m_sFileName	= "";
	m_sName		= "Serie";
	m_value		= 0.0;
}

CSerie::CSerie(const CSerie& obj)
{
	m_bAuto		= obj.m_bAuto;
	m_bDrawMarker = obj.m_bDrawMarker;
	m_bDrawn	= obj.m_bDrawn;
	m_bShowLevel = obj.m_bShowLevel;
	m_miny		= obj.m_miny;
	m_maxy		= obj.m_maxy;
	m_nColor	= obj.m_nColor;
	m_nGraphType= obj.m_nGraphType;
	m_nHighLightNode = obj.m_nHighLightNode;
	m_nLineType	= obj.m_nLineType;
	m_nLineWeight = obj.m_nLineWeight;
	m_data		= obj.m_data;
	m_sFileName	= obj.m_sFileName;
	m_sName		= obj.m_sName;
	m_sUnit		= obj.m_sUnit;
	m_value		= obj.m_value;
}

CSerie::CSerie(const std::vector<double>& data)
{
	m_bAuto		= TRUE;
	m_bDrawMarker = FALSE;
	m_bDrawn	= TRUE;
	m_bShowLevel = FALSE;
	m_nColor	= RGB(0, 0, 0);
	m_nGraphType= __LINE;
	m_nHighLightNode = -1;
	m_nLineType	= 0;
	m_nLineWeight = 1;
	m_sFileName	= "";
	m_sName		= "Serie";
	m_sUnit		= "mm";
	m_value		= 0.0;
	m_miny		= 0.0;
	m_maxy		= 0.0;
	m_data		= data;
}

CSerie::CSerie(int nBlockLength, double delta, double min)
{
	ASSERT(nBlockLength > 0);

	int		i;
	double	value;

	m_data.resize(nBlockLength);
	for (i=0; i<nBlockLength; i++)
	{
		value = min + i * delta;
		m_data[i] = value;
	}

	m_bAuto		= TRUE;
	m_bDrawMarker = FALSE;
	m_bDrawn	= TRUE;
	m_bShowLevel = FALSE;
	m_nColor	= RGB(0, 0, 0);
	m_nGraphType= __LINE;
	m_nHighLightNode = -1;
	m_nLineWeight = 1;
	m_sFileName	= "";
	m_sName		= "Serie";
	m_sUnit		= "mm";
	m_value		= 0.0;
	m_miny		= min;
	m_maxy		= min + (nBlockLength-1)*delta;
}

CSerie::~CSerie()
{

}

CSerie& CSerie::operator=(const CSerie& obj)
{
	if (&obj == this)
		return *this;

	m_bAuto		= obj.m_bAuto;
	m_bDrawMarker = obj.m_bDrawMarker;
	m_bDrawn	= obj.m_bDrawn;
	m_bShowLevel = obj.m_bShowLevel;
	m_data		= obj.m_data;
	m_miny		= obj.m_miny;
	m_maxy		= obj.m_maxy;
	m_nColor	= obj.m_nColor;
	m_nGraphType= obj.m_nGraphType;
	m_nHighLightNode = obj.m_nHighLightNode;
	m_nLineType	= obj.m_nLineType;
	m_nLineWeight = obj.m_nLineWeight;
	m_sFileName	= obj.m_sFileName;
	m_sName		= obj.m_sName;
	m_sUnit		= obj.m_sUnit;
	m_value		= obj.m_value;

	return *this;
}

BOOL CSerie::GetDrawn()
{
	return m_bDrawn;
}

void CSerie::SetDrawn(BOOL bDrawn)
{
	m_bDrawn = bDrawn;
}

double	CSerie::GetElement(int nIndex) const
{
	return m_data[nIndex];
}

void	CSerie::SetElement(double value, int nIndex)
{
	m_data[nIndex] = value;
}

COLORREF	CSerie::GetColor() const
{
	return m_nColor;
}

void	CSerie::SetColor(COLORREF nColor)
{
	m_nColor = nColor;
}

std::string	CSerie::GetName() const
{
	return m_sName;
}

void	CSerie::SetName(const std::string& sName)
{
	m_sName = sName;
}

void CSerie::AddElement(double value)
{
	m_data.push_back(value);
}

int CSerie::GetNumElement() const
{
	return m_data.size();
}

void CSerie::RemoveElement(int nIndex)
{
	m_data.erase(m_data.begin() + nIndex);
}

void CSerie::Scale(double scaleFactor)
{
	int i, nSize;
	nSize = m_data.size();

	for (i=0; i<nSize; i++)
		m_data[i] = m_data[i] * scaleFactor;
}

//////////////////////////////////////////////////////////////////////
//

void	CSerie::Create(int nRecords, double value)
{
	ASSERT(nRecords > 0);
	
	int		i;
	
	m_data.resize(nRecords);
	for (i=0; i<nRecords; i++)
		m_data[i] = value;
}

///////////////////////////////////////////////////////////////////////////////////
//

void CSerie::Draw(CDC *pDC, CRect rect, double minx, double maxx, const CSerie& xSerie, BOOL bMultiChart, COLORREF nBackColor)
{
	if (m_bDrawn == FALSE)
		return;

	CPen drwPen, *pOldPen, shadePen;
	if (m_nLineType == 0)
		drwPen.CreatePen(PS_SOLID, m_nLineWeight, m_nColor);
	else
		drwPen.CreatePen(PS_DOT, m_nLineWeight, m_nColor);
	
	COLORREF nCurBackColor = pDC->SetBkColor(nBackColor);
	COLORREF nShadeColor = GetSysColor(COLOR_ACTIVEBORDER);
	shadePen.CreatePen(PS_SOLID, m_nLineWeight, nShadeColor);

	int i;
	int xpos, ypos, nPoints;
	int xleft, xright, ytop, ybottom;
	double xval, yval;

	m_rect	= rect;
	xleft	= rect.left;
	xright	= rect.right;
	ytop	= rect.top;
	ybottom = rect.bottom;

	nPoints = m_data.size();

	CPoint	curPoint;
	CRect	offsetRect = rect;
	CRect	bar;
	CBrush	brush, *pOldBrush;
	brush.CreateSolidBrush(m_nColor);
	pOldBrush = pDC->SelectObject(&brush);

	offsetRect.left -= 1;
	offsetRect.top -= 1;
	offsetRect.bottom += 1;
	offsetRect.right += 1;

	// Draw the serie itself
	BOOL bHighlight=FALSE;
	double	width;
	int		x1, x2;
	x1 = xleft + (xSerie.GetElement(0) - minx)*(xright - xleft)/(maxx - minx);
	x2 = xleft + (xSerie.GetElement(1) - minx)*(xright - xleft)/(maxx - minx);
	width = (x2 - x1) / 4;

	if (m_nGraphType != __BAR)
		pOldPen = pDC->SelectObject(&drwPen);
	else
		pOldPen = pDC->SelectObject(&shadePen);

	for (i=0; i<nPoints; i++)
	{
		xval = xSerie.GetElement(i);
		xpos = xleft + (xval - minx)*(xright - xleft)/(maxx - minx);
		
		yval = m_data[i];
		ypos = ybottom - (yval - m_miny)*(ybottom - ytop)/(m_maxy - m_miny);
		
		if ((i==0 && m_nGraphType != __BAR) || PtInRect(&offsetRect, CPoint(xpos, ypos)) == FALSE)	// PtInRect returns FALSE even if point on the edge 
		{
			pDC->MoveTo(xpos, ypos);
		}
		else
		{
			switch (m_nGraphType)
			{
			case __PIXEL:
				pDC->SetPixel(xpos, ypos, m_nColor);
				break;
			case __LINE:
				if (PtInRect(&offsetRect, curPoint) == TRUE)
					pDC->LineTo(xpos, ypos);
				else
					pDC->MoveTo(xpos, ypos);
				break;
			case __BAR:
				m_bDrawMarker = FALSE;
		
				bar.left = xpos - width/2;
				bar.right = xpos + width/2;
				bar.top = ypos;
				bar.bottom = ybottom;

				pDC->FillRect(&bar, &brush);

				pDC->MoveTo(bar.right+1, bar.top+2);
				pDC->LineTo(bar.right+1, bar.bottom);
				pDC->LineTo(bar.left+1, bar.bottom);
				
				break;
			default:
				break;
			}
		}
		
		curPoint.x = xpos;
		curPoint.y = ypos;

		if (i == m_nHighLightNode)
			bHighlight = TRUE;
		else
			bHighlight = FALSE;
		
		if (m_bDrawMarker && PtInRect(&offsetRect, curPoint) == TRUE)
			DrawMarker(pDC, xpos, ypos, bHighlight);
	}

	// Draw the level line
	if (m_bShowLevel == TRUE)
	{
		ypos =	ybottom - (m_value - m_miny)*(ybottom - ytop)/(m_maxy - m_miny);
		
		if (ypos <= rect.bottom && ypos >= rect.top)
		{
			pOldPen = pDC->SelectObject(&drwPen);
			pDC->MoveTo(rect.left, ypos);
			pDC->LineTo(rect.right, ypos);
		}
	}
	
	pDC->SetBkColor(nCurBackColor);
	pOldBrush = pDC->SelectObject(&brush);
	
	pDC->SelectObject(pOldPen);
	drwPen.DeleteObject();
	shadePen.DeleteObject();
}

void CSerie::DrawMarker(CDC *pDC, int xpos, int ypos, BOOL bHighlight)
{
	CRect rect;
	
	
	CBrush brush, highlightBrush, *pOldBrush;
	brush.CreateSolidBrush(m_nColor);
	highlightBrush.CreateSolidBrush(RGB(0, 160, 160));
	
	if (bHighlight == TRUE)
	{
		pOldBrush = pDC->SelectObject(&highlightBrush);
		rect.SetRect(xpos - 3, ypos - 3, xpos + 3, ypos + 3);
		pDC->FillRect(&rect, &highlightBrush);
	}
	else
	{
		rect.SetRect(xpos - 2, ypos - 2, xpos + 2, ypos + 2);
		pOldBrush = pDC->SelectObject(&brush);
		pDC->FillRect(&rect, &brush);
	}

	pDC->SelectObject(pOldBrush);
	brush.DeleteObject();
	highlightBrush.DeleteObject();
}

//////////////////////////////////////////////////////////////////////
//

double CSerie::GetMaxVal()
{
	double maxVal;
	int i;
	maxVal = m_data[0];
	for (i=0; i<m_data.size(); i++)
	{
		if (maxVal < m_data[i])
			maxVal = m_data[i];
	}

	if (maxVal < m_value && m_bShowLevel == TRUE)
		maxVal = m_value;

	return maxVal;
}

double CSerie::GetMinVal()
{
	double minVal;
	int i;
	minVal = m_data[0];
	for (i=0; i<m_data.size(); i++)
	{
		if (minVal > m_data[i])
			minVal = m_data[i];
	}

	if (minVal > m_value && m_bShowLevel == TRUE)
		minVal = m_value;
	
	return minVal;
}

double	CSerie::GetMinVal(int lowIndex, int hiIndex)
{
	double	minVal;
	int		i, nSize;
	nSize = GetNumElement();

	ASSERT(lowIndex >= 0);
	ASSERT(lowIndex <= hiIndex);
	ASSERT(hiIndex < nSize);

	minVal = GetElement(lowIndex);
	for (i=lowIndex; i<=hiIndex; i++)
	{
		if (minVal > GetElement(i))
			minVal = GetElement(i);
	}

	return minVal;
}

double	CSerie::GetMaxVal(int lowIndex, int hiIndex)
{
	double	maxVal;
	int		i, nSize;
	nSize = GetNumElement();

	ASSERT(lowIndex >= 0);
	ASSERT(lowIndex <= hiIndex);
	ASSERT(hiIndex < nSize);

	maxVal = GetElement(lowIndex);
	for (i=lowIndex; i<=hiIndex; i++)
	{
		if (maxVal < GetElement(i))
			maxVal = GetElement(i);
	}

	return maxVal;
}

double	CSerie::GetRMS()
{
	double mean, RMS = 0.0;
	int i, nSize;
	nSize = m_data.size();

	mean = GetMeanValue();
	for (i=0; i<nSize; i++)
	{
		RMS += (m_data[i] - mean) * (m_data[i] - mean);
	}

	RMS = sqrt(RMS / nSize);

	return RMS;
}

double	CSerie::GetRMS(int lowIndex, int hiIndex)
{
	double	RMS;
	int		i, nSize;
	nSize = GetNumElement();

	ASSERT(lowIndex >= 0);
	ASSERT(lowIndex <= hiIndex);
	ASSERT(hiIndex < nSize);

	RMS = 0.0;
	for (i=lowIndex; i<=hiIndex; i++)
	{
		RMS += m_data[i] * m_data[i];
	}

	RMS = sqrt(RMS / nSize);

	return RMS;
}

double	CSerie::GetMeanValue()
{
	double mean = 0.0;
	int i, nSize;
	nSize = m_data.size();
	for (i=0; i<nSize; i++)
	{
		mean += m_data[i];
	}

	mean = mean / nSize;

	return mean;
}

double	CSerie::GetMeanValue(int lowIndex, int hiIndex)
{
	double	mean;
	int		i, nSize;
	nSize = GetNumElement();

	ASSERT(lowIndex >= 0);
	ASSERT(lowIndex <= hiIndex);
	ASSERT(hiIndex < nSize);

	mean = 0.0;
	for (i=lowIndex; i<=hiIndex; i++)
	{
		mean += m_data[i];
	}

	mean = mean / nSize;

	return mean;
}

void CSerie::SetMiny(double val)
{
	m_miny = val;
}

double CSerie::GetMiny()
{
	return m_miny;
}

double CSerie::GetMaxy()
{
	return m_maxy;
}

void CSerie::SetMaxy(double val)
{
	m_maxy = val;
}

void CSerie::ResetData()
{
	m_data.clear();
}

void CSerie::SetAuto(BOOL bAuto)
{
	m_bAuto = bAuto;
}

BOOL CSerie::GetAuto()
{
	return m_bAuto;
}

CString CSerie::GetFileName() const
{
	return m_sFileName;
}

void CSerie::SetFileName(const CString &sFileName)
{
	m_sFileName = sFileName;
}


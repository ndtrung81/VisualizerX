// GraphCtrl.cpp: implementation of the CGraphCtrl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Visualizer_X.h"
#include "GraphCtrl.h"

#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

using namespace std;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGraphCtrl::CGraphCtrl()
{
	m_bAuto			= TRUE;
	m_bDrawCursor	= TRUE;
	m_bDrawLegend	= TRUE;
	m_bMultiChart	= FALSE;
	m_bGridlines	= TRUE;
	m_nFontSize		= 4;
	m_nGridColor	= GetSysColor(COLOR_ACTIVEBORDER);
	m_nGridType		= 0;
	m_nCurSerie		= 1;
	m_nCurXPos		= 1;
	m_nFrameWeight	= 1;
	m_nGridWeight	= 1;
	m_nLineWeight	= 1;
	m_nTickX		= 4;
	m_nTickY		= 2;
	m_minx			= 0.0;
	m_maxx			= 1.0;
	m_miny			= 0.0;
	m_maxy			= 1.0;
	m_largeTick = 12;
	m_smallTick = 8;
	m_largeTickXInterval = 0.1;
	m_smallTickXInterval = 0.1;
	m_largeTickYInterval = 0.1;
	m_smallTickYInterval = 0.1;
	m_nBackColor	= RGB(255, 255, 255); // GetSysColor(COLOR_ACTIVEBORDER);	// RGB(192, 192, 192);
	m_nPlotBackColor= RGB(255, 255, 255);
	m_scaleX		= 1.0;
	m_sXLabel		= "";
	m_sYLabel		= "";


	 
}

CGraphCtrl::CGraphCtrl(const CGraphCtrl& obj)
{
	m_bAuto			= obj.m_bAuto;
	m_bDrawCursor	= obj.m_bDrawCursor;
	m_bDrawLegend	= obj.m_bDrawLegend;
	m_boundRect		= obj.m_boundRect;
	m_bGridlines	= obj.m_bGridlines;	
	m_bMultiChart	= obj.m_bMultiChart;
	m_nFontSize		= obj.m_nFontSize;
	m_nBackColor	= obj.m_nBackColor;
	m_nGridWeight	= obj.m_nGridWeight;
	m_nFrameWeight	= obj.m_nFrameWeight;
	m_nLineWeight	= obj.m_nLineWeight;
	m_nPlotBackColor= obj.m_nPlotBackColor;
	m_nGridColor	= obj.m_nGridColor;
	m_nGridType		= obj.m_nGridType;
	m_nCurSerie		= obj.m_nCurSerie;
	m_nCurXPos		= obj.m_nCurXPos;
	m_nTickX		= obj.m_nTickX;
	m_nTickY		= obj.m_nTickY;
	m_minx			= obj.m_minx;
	m_maxx			= obj.m_maxx;
	m_miny			= obj.m_miny;
	m_maxy			= obj.m_maxy;
	m_largeTick		= obj.m_largeTick;
	m_smallTick		= obj.m_smallTick;
	m_largeTickXInterval = obj.m_largeTickXInterval;
	m_smallTickXInterval = obj.m_smallTickXInterval;
	m_largeTickYInterval = obj.m_largeTickYInterval;
	m_smallTickYInterval = obj.m_smallTickYInterval;
	m_scaleX		= obj.m_scaleX;
	m_sXLabel		= obj.m_sXLabel;
	m_sYLabel		= obj.m_sYLabel;
	serieVector		= obj.serieVector;
}

CGraphCtrl::~CGraphCtrl()
{

}

//////////////////////////////////////////////////////////////////////
//
CGraphCtrl& CGraphCtrl::operator=(const CGraphCtrl& obj)
{
	if (&obj == this)
		return *this;

	m_bAuto			= obj.m_bAuto;
	m_bDrawCursor	= obj.m_bDrawCursor;
	m_bDrawLegend	= obj.m_bDrawLegend;
	m_boundRect		= obj.m_boundRect;
	m_bGridlines	= obj.m_bGridlines;	
	m_bMultiChart	= obj.m_bMultiChart;
	m_nFontSize		= obj.m_nFontSize;
	m_nBackColor	= obj.m_nBackColor;
	m_nPlotBackColor= obj.m_nPlotBackColor;
	m_nGridColor	= obj.m_nGridColor;
	m_nGridType		= obj.m_nGridType;
	m_nCurSerie		= obj.m_nCurSerie;
	m_nCurXPos		= obj.m_nCurXPos;
	m_nFrameWeight	= obj.m_nFrameWeight;
	m_nGridWeight	= obj.m_nGridWeight;
	m_nLineWeight	= obj.m_nLineWeight;
	m_nTickX		= obj.m_nTickX;
	m_nTickY		= obj.m_nTickY;
	m_minx			= obj.m_minx;
	m_maxx			= obj.m_maxx;
	m_scaleX		= obj.m_scaleX;
	m_sXLabel		= obj.m_sXLabel;
	m_sYLabel		= obj.m_sYLabel;
	serieVector		= obj.serieVector;

	return *this;
}

void	CGraphCtrl::AddSerie(const CSerie& serie)
{
	serieVector.push_back(serie);
}

int		CGraphCtrl::GetNumSerie() const
{
	return serieVector.size();
}

int CGraphCtrl::GetNumDrawnSerie()
{
	int i, nDrawnSerie;
	BOOL	bDrawn;

	nDrawnSerie = 0;
	for (i=0; i<serieVector.size(); i++)
	{
		bDrawn = serieVector[i].GetDrawn();
		if (bDrawn == TRUE)
			nDrawnSerie++;
	}

	return nDrawnSerie;
}

CSerie*	CGraphCtrl::GetSerie(int nIndex)
{
	return &serieVector[nIndex];
}

void	CGraphCtrl::RemoveSerie(int nIndex)
{
	serieVector.erase(serieVector.begin() + nIndex);
}

void	CGraphCtrl::SetSerie(int nIndex, const CSerie& serie)
{
	serieVector[nIndex] = serie;
}

void CGraphCtrl::ResetData()
{
	serieVector.clear();
}

//////////////////////////////////////////////////////////////////////
//

void CGraphCtrl::SetBoundRect(const CRect &rect)
{
	m_boundRect = rect;
}

CRect CGraphCtrl::GetPlotRect()
{
	return m_plotRect;
}

double CGraphCtrl::GetOverallMiny()
{
	int i;
	double min;

	CSerie* serie;
	serie = GetSerie(1);
	min = serie->GetMinVal();

	for (i=1; i<GetNumSerie(); i++)
	{
		serie = GetSerie(i);
		if (serie->m_bDrawn == TRUE && min > serie->GetMinVal())	
			min = serie->GetMinVal();
	}

	return min;
}

double CGraphCtrl::GetOverallMaxy()
{
	int i;
	double max;

	CSerie* serie;
	serie = GetSerie(1);
	max = serie->GetMaxVal();

	for (i=1; i<GetNumSerie(); i++)
	{
		serie = GetSerie(i);
		if (serie->m_bDrawn == TRUE && max < serie->GetMaxVal())	
			max = serie->GetMaxVal();
	}

	return max;
}

void CGraphCtrl::SetAuto(BOOL bAuto)
{
	m_bAuto = bAuto;
}

BOOL CGraphCtrl::GetAuto()
{
	return m_bAuto;
}

void CGraphCtrl::SetMultiChart(BOOL bMultiChart)
{
	m_bMultiChart = bMultiChart;
}

BOOL CGraphCtrl::GetMultiChart()
{
	return m_bMultiChart;
}

double CGraphCtrl::GetMinx()
{
	return m_minx;
}

double CGraphCtrl::GetMaxx()
{
	return m_maxx;
}

void CGraphCtrl::SetMaxx(double maxx)
{
	m_maxx = maxx;
}

void CGraphCtrl::SetMinx(double minx)
{
	m_minx = minx;
}

int CGraphCtrl::GetCurXPos()
{
	return m_nCurXPos;
}

void CGraphCtrl::SetCurXPos(int xPos)
{
	m_nCurXPos = xPos;		
}

void CGraphCtrl::SetCurSerie(int nCurSerie)
{
	m_nCurSerie = nCurSerie;
}

int CGraphCtrl::GetCurSerie()
{
	return m_nCurSerie;
}

void CGraphCtrl::SetTickX(int nTickX)
{
	m_nTickX = nTickX;
}

int CGraphCtrl::GetTickX()
{
	return m_nTickX;
}

void CGraphCtrl::SetLargeTickXInterval(double dx)
{
	m_largeTickXInterval = dx;
}

void CGraphCtrl::SetSmallTickXInterval(double dx)
{
	m_smallTickXInterval = dx;
}

void CGraphCtrl::SetLargeTickYInterval(double dy)
{
	m_largeTickYInterval = dy;
}

void CGraphCtrl::SetSmallTickYInterval(double dy)
{
	m_smallTickYInterval = dy;
}

//////////////////////////////////////////////////////////////////////
// Drawing

BOOL CGraphCtrl::BeginDraw(CDC *pDC)
{
	if (pDC == NULL)
		return FALSE;

	int tickFontSize = 15;

	if (pDC->IsPrinting())
	{
		int nFontSize;
		nFontSize = 70;
		switch (m_nFontSize)
		{
		case 0:
			nFontSize = nFontSize * 0.5;
			break;
		case 1:
			nFontSize = nFontSize * 0.75;
			break;
		case 2:
			nFontSize = nFontSize * 0.8;
			break;
		case 3:
			nFontSize = nFontSize * 0.9;
			break;
		case 4:
			nFontSize = nFontSize * 1.0;
			break;
		case 5:
			nFontSize = nFontSize * 1.25;
			break;
		case 6:
			nFontSize = nFontSize * 1.5;
			break;
		case 7:
			nFontSize = nFontSize * 2.;
			break;
		case 8:
			nFontSize = nFontSize * 2.5;
			break;
		default:
			break;
		};

		m_font.CreateFont(nFontSize, 0, 0, 0, 400, FALSE, FALSE, 0,
			ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN, "Times New Roman");
	}
	else
	{
		switch (m_nFontSize)
		{
		case 0:
			tickFontSize = tickFontSize * 0.5;
			break;
		case 1:
			tickFontSize = tickFontSize * 0.75;
			break;
		case 2:
			tickFontSize = tickFontSize * 0.8;
			break;
		case 3:
			tickFontSize = tickFontSize * 0.9;
			break;
		case 4:
			tickFontSize = tickFontSize * 1.0;
			break;
		case 5:
			tickFontSize = tickFontSize * 1.25;
			break;
		case 6:
			tickFontSize = tickFontSize * 1.5;
			break;
		case 7:
			tickFontSize = tickFontSize * 2.;
			break;
		case 8:
			tickFontSize = tickFontSize * 2.5;
			break;
		default:
			break;
		};

		m_font.CreateFont(tickFontSize, 0, 0, 0, 400, FALSE, FALSE, 0,
			ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN, "Arial");
	}

	pDC->SelectObject(&m_font);

	if (pDC->IsPrinting() == FALSE)
	{
		CBrush brush;
		brush.CreateSolidBrush(m_nBackColor);

		pDC->FillRect(&m_boundRect, &brush);

		pDC->SetBkColor(m_nBackColor);
		brush.DeleteObject();
	}

	return TRUE;
}

void CGraphCtrl::EndDraw()
{
	m_font.DeleteObject();
}

void CGraphCtrl::Draw(CDC* pDC)
{
	if (!BeginDraw(pDC))
		return;
	
	COLORREF nBkColor = m_nPlotBackColor;
	CBrush brush;
	brush.CreateSolidBrush(nBkColor);
		
	if (serieVector.size() < 2)
	{
		EndDraw();
		return;
	}

	int i, nSeries;
	CSerie	*ySerie;
	CSerie	xSerie;
	nSeries = GetNumDrawnSerie() - 1;

	m_boundRect.top += 20;
	m_boundRect.right -= 2;
	// initialize the plot rect - this can be used if m_bMultiChart == FALSE
	m_plotRect = m_boundRect;
	m_plotRect.left = m_boundRect.left + m_boundRect.Width()/10;

	// rect for x labels
	CRect xLabelRect;
	xLabelRect = m_boundRect;
	xLabelRect.left = m_plotRect.left;
	xLabelRect.top = m_boundRect.bottom - m_boundRect.Height()/10;
	
	if (m_bMultiChart == TRUE)
		m_nPlotRectHeight = (m_boundRect.Height() - xLabelRect.Height()) / nSeries;
	else
		m_nPlotRectHeight = m_boundRect.Height() - xLabelRect.Height();
	
	m_plotRect.bottom = m_plotRect.top + m_boundRect.Height() - xLabelRect.Height(); 

	if (pDC->IsPrinting() == FALSE)
		pDC->FillRect(&m_plotRect, &brush);
	
	DrawTickX(pDC, xLabelRect);

	int height;
	double miny, maxy;
	// serie 0 contains x values
	xSerie = serieVector[0];
	
	int nDrawnSeries = 0;
	for (i=1; i<serieVector.size(); i++)
	{
		ySerie = &serieVector[i];
		if (ySerie->m_bDrawn == FALSE)
			continue;

		nDrawnSeries++;

		ySerie->m_nLineWeight = m_nLineWeight;
		
		CRect yLabelRect;
		// rect for y labels
		yLabelRect = m_boundRect;
		yLabelRect.left = m_boundRect.left + 5;
		yLabelRect.right = 	m_plotRect.left;
		yLabelRect.bottom = xLabelRect.top; 

		if (m_bMultiChart == TRUE)
		{
			// Calculating the plotRect for each serie
			m_plotRect.top = m_boundRect.top + (nDrawnSeries-1) * m_nPlotRectHeight;		
			m_plotRect.bottom = m_plotRect.top + m_nPlotRectHeight;
			
			// Draw seperated line
			if (nDrawnSeries < nSeries)
			{
				int nCurMode = pDC->GetROP2();
				pDC->SetROP2(R2_NOT);
				
				CPen pen, *pOldPen;
				pen.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
				pOldPen = NULL;
				if (pDC->IsPrinting() == TRUE)
					pOldPen = pDC->SelectObject(&pen);
				
				pDC->MoveTo(m_plotRect.left, m_plotRect.bottom);
				pDC->LineTo(m_plotRect.right, m_plotRect.bottom);

				if (pOldPen != NULL)
					pDC->SelectObject(pOldPen);
				pen.DeleteObject();

				pDC->SetROP2(nCurMode);
			}
			
			// Recalculate plot rect for the gaps between series
			height = m_plotRect.Height();
			m_plotRect.top += height/20;
			m_plotRect.bottom -= height/20;

			yLabelRect.top = m_plotRect.top;
			yLabelRect.bottom = m_plotRect.bottom;
			
			if (fabs(ySerie->GetMaxVal() - ySerie->GetMinVal()) < 1e-6)
			{
				maxy = GetOverallMaxy();
				ySerie->SetMaxy(maxy);
				miny = GetOverallMiny();
				ySerie->SetMiny(miny);

				ySerie->SetAuto(FALSE);
			}
			else
			{
				if (ySerie->m_bAuto == TRUE)
				{
					miny = ySerie->GetMinVal() - (ySerie->GetMaxVal() - ySerie->GetMinVal())/10.0;
					maxy = ySerie->GetMaxVal() + (ySerie->GetMaxVal() - ySerie->GetMinVal())/10.0;
					ySerie->SetMiny(miny);
					ySerie->SetMaxy(maxy);
				}
			}

			DrawTickY(pDC, ySerie->m_miny, ySerie->m_maxy, yLabelRect);
			
			ySerie->Draw(pDC, m_plotRect, m_minx, m_maxx, xSerie, m_bMultiChart, m_nBackColor);
		}
		else
		{
			// Recalculate plot rect 
			height = m_boundRect.Height();
			m_plotRect.top = m_boundRect.top + height/20;
			m_plotRect.bottom = m_boundRect.top + m_nPlotRectHeight - height/20;

			yLabelRect.top = m_plotRect.top;
			yLabelRect.bottom = m_plotRect.bottom;
		
			ySerie->SetAuto(FALSE);
			miny = GetOverallMiny();
			maxy = GetOverallMaxy();
			
			if (fabs(maxy - miny) < 1e-6)
			{
				maxy = maxy + 1.0;
				miny = miny - 1.0;
			}
			
			ySerie->SetMiny(m_miny); //miny - (maxy - miny) / 10.0);
			ySerie->SetMaxy(m_maxy); //maxy + (maxy - miny) / 10.0);
			
			miny = ySerie->GetMiny();
			maxy = ySerie->GetMaxy();
		
			DrawTickY(pDC, miny, maxy, yLabelRect);
			
			ySerie->Draw(pDC, m_plotRect, m_minx, m_maxx, xSerie, m_bMultiChart, m_nBackColor);
		}
	}

	if (pDC->IsPrinting() == FALSE && m_bDrawCursor	== TRUE)
		DrawCursor(pDC);

	// Draw x and y axes
	CPen pen, *pOldPen;
	if (pDC->IsPrinting() == TRUE)
	{
		pen.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	}
	else
		pen.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));

	pOldPen = pDC->SelectObject(&pen);
	
	pDC->MoveTo(xLabelRect.left,  xLabelRect.top);
	pDC->LineTo(xLabelRect.right, xLabelRect.top);
	
	pDC->MoveTo(xLabelRect.left-1,  m_boundRect.top);
	pDC->LineTo(xLabelRect.right, m_boundRect.top);
	
	pDC->MoveTo(xLabelRect.left, m_boundRect.top);
	pDC->LineTo(xLabelRect.left, xLabelRect.top);
	
	pDC->MoveTo(xLabelRect.right, m_boundRect.top);
	pDC->LineTo(xLabelRect.right, xLabelRect.top);
		
	pDC->SetTextAlign(TA_LEFT);
	pDC->TextOut(m_boundRect.left + 1, m_boundRect.top - 20, m_sYLabel);
	
	pDC->SelectObject(pOldPen);
		
	pen.DeleteObject();
	brush.DeleteObject();

	EndDraw();
}

void CGraphCtrl::DrawLegend(CDC *pDC, CRect rect)
{
	int i, xpos, ypos, length, nNumDrawnSeries;
	CString sName;
	COLORREF nLineColor;
	CSize textSize;
	CSerie* pSerie;

	xpos = rect.left;
	
	nNumDrawnSeries = 0;
	for (i=1; i<GetNumSerie(); i++)
	{
		pSerie = GetSerie(i);
		if (pSerie->m_bDrawn == TRUE)
			nNumDrawnSeries++;
	}

	length = rect.Width() / 10.0 / nNumDrawnSeries;
	for (i=1; i<GetNumSerie(); i++)
	{
		pSerie = GetSerie(i);
		if (pSerie->m_bDrawn == FALSE)
			continue;

		sName = pSerie->GetName().data();
		nLineColor = pSerie->GetColor();
		textSize = pDC->GetTextExtent(sName);

		CPen pen, *pOldPen;
//		if (pDC->IsPrinting() == FALSE)
//			pen.CreatePen(PS_SOLID, m_nLineWeight, nLineColor);
//		else
			pen.CreatePen(PS_SOLID, m_nLineWeight, nLineColor);

		pOldPen = pDC->SelectObject(&pen);

		// ypos for line
		ypos = rect.top + 2*rect.Height()/3;

		pDC->MoveTo(xpos, ypos);
		pDC->LineTo(xpos + length, ypos);

		// ypos for text
		ypos = rect.top + 2*rect.Height()/3 - textSize.cy/2;
		pDC->TextOut(xpos + length * 1.2, ypos, sName);

		pDC->SelectObject(pOldPen);
		pen.DeleteObject();

		xpos = xpos + (length * 1.1 + textSize.cx + rect.Width()/50);
	}

}
void CGraphCtrl::DrawTickX(CDC *pDC, CRect rect)
{
	if (m_bDrawLegend == TRUE)
		DrawLegend(pDC, rect);

	CString str;
	COLORREF nBkColor = m_nBackColor;
	CPen penTick, penGrid, *pOldPen;

	penTick.CreatePen(PS_SOLID, m_nFrameWeight, RGB(0, 0, 0));
	
	if (m_nGridType == 0)
		penGrid.CreatePen(PS_SOLID,	m_nGridWeight, m_nGridColor);
	else
		penGrid.CreatePen(PS_DOT,	m_nGridWeight, m_nGridColor);

	int i, xpos, ypostop, yposbottom;
	double xval;

	int xleft, xright;
	xleft = rect.left;
	xright = rect.right;

	yposbottom = rect.top;
	ypostop = m_plotRect.top;

	pOldPen = pDC->SelectObject(&penTick);

	// large ticks
	for (i=1; ; i++)
	{
		xval = m_minx + i*m_largeTickXInterval;
		if (xval >= m_maxx) break;

		xpos = xleft + (xval - m_minx)*(xright - xleft)/(m_maxx - m_minx);

		str.Format("%g", xval * m_scaleX);
		
		// Draw gridlines
		if (m_bGridlines == TRUE)
		{
			COLORREF nCurBackColor = pDC->SetBkColor(m_nBackColor);
			pDC->SelectObject(&penGrid);
			pDC->MoveTo(xpos, m_plotRect.top);
			pDC->LineTo(xpos, m_plotRect.bottom);
			pDC->SetBkColor(nCurBackColor);
		}

		// Draw tick
		pDC->SelectObject(&penTick);
		pDC->MoveTo(xpos, yposbottom);
		pDC->LineTo(xpos, yposbottom - m_largeTick);
		
		pDC->MoveTo(xpos, ypostop);
		pDC->LineTo(xpos, ypostop + m_largeTick);
		
		// Write Text
		pDC->SetTextAlign(TA_RIGHT);
		pDC->TextOut(xpos, yposbottom + 10, str);
		
	}

	// small ticks
	pDC->SelectObject(&penTick);
	for (i=1; ; i++)
	{
		xval = m_minx + i*m_smallTickXInterval;
		if (xval >= m_maxx) break;

		xpos = xleft + (xval - m_minx)*(xright - xleft)/(m_maxx - m_minx);

		// Draw tick
		pDC->MoveTo(xpos, yposbottom);
		pDC->LineTo(xpos, yposbottom - m_smallTick);

		pDC->MoveTo(xpos, ypostop);
		pDC->LineTo(xpos, ypostop + m_smallTick);
	}

	pDC->SetTextAlign(TA_RIGHT | TA_TOP);
	CSize size = pDC->GetTextExtent(m_sXLabel);
	pDC->TextOut(rect.right - rect.Height()/5, rect.bottom - size.cy, m_sXLabel);
	pDC->SetTextAlign(TA_LEFT);

	pDC->SelectObject(pOldPen);
	penTick.DeleteObject();
	penGrid.DeleteObject();
}

void CGraphCtrl::DrawTickY(CDC *pDC, double miny, double maxy, CRect rect)
{
	CString str;
	COLORREF nBkColor = m_nBackColor;
	CPen penTick, penGrid, *pOldPen;

//	if (pDC->IsPrinting() == FALSE)
//		penTick.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
//	else
		penTick.CreatePen(PS_SOLID, m_nFrameWeight, RGB(0, 0, 0));
	
	if (m_nGridType == 0)
		penGrid.CreatePen(PS_SOLID,	m_nGridWeight, m_nGridColor);
	else
		penGrid.CreatePen(PS_DOT,	m_nGridWeight, m_nGridColor);

	int i, xposleft, xposright, ypos;
	double yval;

	int ytop, ybottom, smallTick, largeTick;
	ytop = rect.top;
	ybottom = rect.bottom;

	xposleft = rect.right;
	xposright = m_plotRect.right;
	pOldPen = pDC->SelectObject(&penTick);
	for (i=0; ; i++)
	{
		yval = miny + i*m_largeTickYInterval;
		if (yval > maxy) break;
		ypos = ybottom - (yval - miny)*(ybottom - ytop)/(maxy - miny);
		
		str.Format("%0.1f", yval);

		if (m_bGridlines == TRUE)
		{
			COLORREF nCurBackColor = pDC->SetBkColor(m_nBackColor);
			pDC->SelectObject(&penGrid);
			pDC->MoveTo(m_plotRect.left, ypos);
			pDC->LineTo(m_plotRect.right, ypos);
			pDC->SetBkColor(nCurBackColor);
		}

		// Draw tick
		pDC->SelectObject(&penTick);
		pDC->MoveTo(xposleft, ypos);
		pDC->LineTo(xposleft + m_largeTick, ypos);
		
		pDC->MoveTo(xposright, ypos);
		pDC->LineTo(xposright - m_largeTick, ypos);

		// Write text
		pDC->SetTextAlign(TA_RIGHT);
		pDC->TextOut(xposleft - rect.Width() / 5, ypos - 6, str);
	}

	pDC->SelectObject(&penTick);
	for (i=1; ; i++)
	{
		yval = miny + i*m_smallTickYInterval;
		if (yval > maxy) break;
		ypos = ybottom - (yval - miny)*(ybottom - ytop)/(maxy - miny);
		
		// Draw tick
		pDC->MoveTo(xposleft, ypos);
		pDC->LineTo(xposleft + m_smallTick, ypos);

		pDC->MoveTo(xposright, ypos);
		pDC->LineTo(xposright - m_smallTick, ypos);
	
	}

	pDC->SelectObject(pOldPen);
	penTick.DeleteObject();
	penGrid.DeleteObject();
}

void CGraphCtrl::DrawCursor(CDC* pDC)
{
	if (pDC == NULL)
		return;

	pDC->SetROP2(R2_NOT);

	CRect rect;
	rect = m_plotRect;
	
	if (m_bMultiChart == TRUE)
	{
		rect.top = m_boundRect.top + (m_nCurSerie-1) * m_nPlotRectHeight; // +10
		rect.bottom = rect.top + m_nPlotRectHeight;	// -20
		m_plotRect = rect;
	}
	
	CSerie*	xSerie, *ySerie;
	double	xval, yval, miny, maxy;

	xSerie = GetSerie(0);
	xval = xSerie->GetElement(m_nCurXPos);
	ySerie = GetSerie(m_nCurSerie);
	yval = ySerie->GetElement(m_nCurXPos);
	
	miny = ySerie->m_miny;
	maxy = ySerie->m_maxy;

	int xpos, ypos, xleft, xright, ytop, ybottom;
	xleft = rect.left;
	xright = rect.right;
	ytop = ySerie->m_rect.top;
	ybottom = ySerie->m_rect.bottom;

	xpos = xleft + (xval - m_minx)*(xright - xleft)/(m_maxx - m_minx);
	ypos = ybottom - (yval - miny)*(ybottom - ytop)/(maxy - miny);

	if (m_bMultiChart == TRUE)
	{
		pDC->MoveTo(xpos, rect.top); // -10
		pDC->LineTo(xpos, rect.bottom); // +10

		pDC->MoveTo(rect.left, ypos);
		pDC->LineTo(rect.left + 20, ypos);
	}
	else
	{
		pDC->MoveTo(xpos, m_boundRect.top);
		pDC->LineTo(xpos, m_boundRect.bottom - m_boundRect.Height()/10);
	}
}

///////////////////////////////////////////////////////////////////////
// Event handler

void CGraphCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	int nPoints, lowCurPos, highCurPos, nSeries;
	double minx, maxx, deltax;
	CSerie* xSerie = GetSerie(0);
	nPoints = xSerie->GetNumElement();
	minx = xSerie->GetMinVal();
	maxx = xSerie->GetMaxVal();
	deltax = (maxx - minx) / (nPoints - 1);


//	lowCurPos = (m_minx - minx) / deltax;
	lowCurPos = 0;
	if (lowCurPos < 0)
		lowCurPos = 0;
	
//	highCurPos = (m_maxx - minx) / deltax;
	highCurPos = nPoints - 1;
	if (highCurPos >= nPoints - 1)
		highCurPos = nPoints - 1;

	nSeries = GetNumSerie();
	switch (nChar)
	{
	case VK_LEFT:
		if (m_nCurXPos > lowCurPos)
			m_nCurXPos--;
		else
			m_nCurXPos = lowCurPos;
		break;

	case VK_RIGHT:
		if (m_nCurXPos < highCurPos)
			m_nCurXPos++;
		else
			m_nCurXPos = highCurPos;
		break;
	
	case VK_UP:
		if (m_nCurSerie > 1)
			m_nCurSerie--;
		else
			m_nCurSerie = 1;
		break;
	
	case VK_DOWN:
		if (m_nCurSerie < nSeries-1)
			m_nCurSerie++;
		else
			m_nCurSerie = nSeries-1;
		break;

	default:
		break;
	}

}

void CGraphCtrl::GetCursorValues(double &xval, double &yval)
{
	CSerie* serie;
	serie = GetSerie(0);
	xval = serie->GetElement(m_nCurXPos);	

	serie = GetSerie(m_nCurSerie);	
	yval = serie->GetElement(m_nCurXPos);	

}

void CGraphCtrl::FindCurXPos(int xpoint)
{
	int		nPoints;
	double	minx;
	double	xval, deltax;
	CSerie* xSerie = GetSerie(0);
	
	nPoints = xSerie->GetNumElement();
	// These minx and maxx are the overall optimum (not local) of xSerie
	// while, m_minx, m_maxx are local optimum of x range for display.
	// If auto, minx = m_minx, maxx = m_maxx.  
	minx = xSerie->GetElement(0);
	deltax = xSerie->GetElement(1) - xSerie->GetElement(0);	// dx for each step
	
	int xleft, xright;
	xleft = m_plotRect.left;
	xright = m_plotRect.right;
	
	xval = m_minx + (xpoint - xleft)*(m_maxx - m_minx)/(xright - xleft);
	
	m_nCurXPos = (xval - minx) / deltax;

}













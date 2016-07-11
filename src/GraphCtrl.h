// GraphCtrl.h: interface for the CGraphCtrl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRAPHCTRL_H__10BF37FA_DC93_11D8_AD91_0002444AAF71__INCLUDED_)
#define AFX_GRAPHCTRL_H__10BF37FA_DC93_11D8_AD91_0002444AAF71__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
#include "Serie.h"

class CGraphCtrl : public CObject  
{
private:

public:
	int GetNumDrawnSerie();
	void DrawLegend(CDC* pDC, CRect rect);
	CGraphCtrl();
	CGraphCtrl(const CGraphCtrl& obj);
	virtual ~CGraphCtrl();
	CGraphCtrl& operator=(const CGraphCtrl& obj);

	void	FindCurXPos(int xpoint);
	int		GetCurSerie();
	void	SetCurSerie(int nCurSerie);
	void	SetCurXPos(int xPos);
	int		GetCurXPos();
	void	GetCursorValues(double& xval, double& yval);

	void	OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

	void	Draw(CDC* pDC);
	void	DrawCursor(CDC* pDC);
	void	DrawTickY(CDC* pDC, double miny, double maxy, CRect rect);
	void	DrawTickX(CDC* pDC, CRect rect);
	
	BOOL	GetMultiChart();
	void	SetMultiChart(BOOL bMultiChart);
	int		GetTickX();
	void	SetTickX(int nTickX);
	
	CRect	GetPlotRect();
	void	SetBoundRect(const CRect& rect);
	double	GetOverallMaxy();
	double	GetOverallMiny();

	void	EndDraw();
	BOOL	BeginDraw(CDC* pDC);
	void	SetMinx(double minx);
	void	SetMaxx(double maxx);
	void	SetMiny(double minx);
	void	SetMaxy(double maxx);
	void	SetLargeTickXInterval(double dx);
	void	SetSmallTickXInterval(double dx);
	void	SetLargeTickYInterval(double dy);
	void	SetSmallTickYInterval(double dy);
	BOOL	GetAuto();
	void	SetAuto(BOOL bAuto);
	double	GetMaxx();
	double	GetMinx();

	void	AddSerie(const CSerie& serie);
	int		GetNumSerie() const;
	CSerie*	GetSerie(int nIndex);
	void	RemoveSerie(int nIndex);
	void	SetSerie(int nIndex, const CSerie& serie);
	void	ResetData();
	
	BOOL	m_bDrawLegend;
	int		m_nGridWeight;
	int		m_nLineWeight;
	int		m_nFrameWeight;
	BOOL	m_bDrawCursor;
	double	m_scaleX;
	CString m_sXLabel;
	CString m_sYLabel;
	CFont	m_font;
	COLORREF m_nPlotBackColor;
	COLORREF m_nBackColor;
	int		m_nFontSize;
	COLORREF m_nGridColor;
	int		m_nGridType;
	int		m_nCurSerie;
	int		m_nCurXPos;
	double	m_maxx;
	double	m_minx;
	double	m_maxy;
	double	m_miny;
	int		m_nPlotRectHeight;
	CRect	m_boundRect;
	CRect	m_plotRect;
	int		m_nTickX;
	int		m_nTickY;
	int		m_smallTick;
	int		m_largeTick;
	double	m_largeTickXInterval;
	double	m_smallTickXInterval;
	double	m_largeTickYInterval;
	double	m_smallTickYInterval;
	BOOL	m_bGridlines;
	BOOL	m_bMultiChart;
	BOOL	m_bAuto;


	std::vector<CSerie> serieVector;
};

#endif // !defined(AFX_GRAPHCTRL_H__10BF37FA_DC93_11D8_AD91_0002444AAF71__INCLUDED_)

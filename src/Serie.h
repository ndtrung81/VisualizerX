// Serie.h: interface for the CSerie class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SERIE_H__A7755BA1_D42E_11D8_9301_00608CCB84D9__INCLUDED_)
#define AFX_SERIE_H__A7755BA1_D42E_11D8_9301_00608CCB84D9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>

enum _GRAPH_TYPE
{
	__PIXEL = 0,
	__LINE = 1,
	__BAR = 2
};

class CSerie : public CObject  
{
public:
	int m_nLineWeight;
	void	DrawMarker(CDC* pDC, int xPos, int yPos, BOOL bHighlight);
	
	CSerie();
	CSerie(const CSerie& obj);
	CSerie(const std::vector<double>& data);
	CSerie(int nBlockLength, double delta, double min=0.0);
	virtual ~CSerie();

	CSerie& operator=(const CSerie& obj);

	void	Create(int nRecords, double value);

	void	Draw(CDC *pDC, CRect rect, double minx, double maxx, const CSerie& xserie, BOOL bMultiChart, COLORREF nBackColor);

	void	SetFileName(const CString& sFileName);
	CString GetFileName() const;
	CString m_sFileName;
	BOOL	GetAuto();
	void	SetAuto(BOOL bAuto);
	void	ResetData();
	
	void	Scale(double scaleFactor);
	
	void	SetMaxy(double val);
	double	GetMaxy();
	double	GetMiny();
	void	SetMiny(double val);
	
	double	GetRMS();
	double	GetMeanValue();
	double	GetMinVal();
	double	GetMaxVal();
	double	GetRMS(int lowIndex, int hiIndex);
	double	GetMeanValue(int lowIndex, int hiIndex);
	double	GetMinVal(int lowIndex, int hiIndex);
	double	GetMaxVal(int lowIndex, int hiIndex);

	void	AddElement(double value);
	void	RemoveElement(int nIndex);
	int		GetNumElement() const;

	BOOL		GetDrawn();
	void		SetDrawn(BOOL bDrawn);
	double		GetElement(int nIndex) const;
	void		SetElement(double value, int nIndex);
	COLORREF	GetColor() const;
	void		SetColor(COLORREF nColor);
	std::string	GetName() const;
	void		SetName(const std::string& sName);
	
	BOOL				m_bDrawn;
	BOOL				m_bDrawMarker;
	BOOL				m_bShowLevel;
	double				m_value;
	std::string			m_sName;
	std::string			m_sUnit;	
	COLORREF			m_nColor;
	int					m_nGraphType;
	int					m_nLineType;
	CRect				m_rect;
	std::vector<double> m_data;
	int					m_nHighLightNode;

	double	m_maxy;
	double	m_miny;
	BOOL	m_bAuto;
};

#endif // !defined(AFX_SERIE_H__A7755BA1_D42E_11D8_9301_00608CCB84D9__INCLUDED_)


// FFTStatic.cpp : implementation file
//

#include "stdafx.h"
#include "visualizer_x.h"
#include "FFTStatic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFFTStatic

CFFTStatic::CFFTStatic()
{
	m_diffData = 0x0;
	m_nDiffWindowSize = 256;
}

CFFTStatic::~CFFTStatic()
{
}


BEGIN_MESSAGE_MAP(CFFTStatic, CStatic)
	//{{AFX_MSG_MAP(CFFTStatic)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFFTStatic message handlers

void CFFTStatic::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	if (m_diffData == NULL)
		return;

	CRect rect;
	GetClientRect(&rect);
	int width = rect.Width();
	int height = rect.Height();
	int size = (width <= height) ? width : height;
	m_nDiffWindowSize = size;

	int i, j, center_image, center_data;
	double value, weight=0.1;
	center_image = m_nDiffWindowSize/2;
	center_data = m_nFFTSize/2;

	COLORREF color, background = RGB(0.0, 0.0, 0.0);
	dc.FillSolidRect(0, 0, m_nDiffWindowSize, m_nDiffWindowSize, background);
	for (i=0; i<m_nDiffWindowSize; i++)
		for (j=0; j<m_nDiffWindowSize; j++)
		{
			// zoom from the center
			int ix = center_data + (int)((i - center_image) / m_zoom);
			int iy = center_data + (int)((j - center_image) / m_zoom);
			if (m_zoom > 1.0 && ix < m_nFFTSize - 1 && ix >= 1 && 
				iy < m_nFFTSize - 1 && iy >= 1)
			{
				value = (weight*m_diffData[iy-1][ix] 
					+ weight*m_diffData[iy+1][ix] 
					+ weight*m_diffData[iy][ix-1]
					+ weight*m_diffData[iy][ix+1] 
					+ m_diffData[iy][ix])/(4*weight + 1.0);
			}
			else if (ix < m_nFFTSize && ix >= 0 && iy < m_nFFTSize && iy >= 0)
				value = m_diffData[iy][ix];
			else value = 0.0;

			color = ConvertDouble2RGB(value);
			dc.SetPixel(i, j, color);
		}
}

COLORREF CFFTStatic::ConvertDouble2RGB(double value)
{
	int gray = (int)value;
	int col = (int)((gray & 0xffff) * 0.05);
	int cr = col; 
	if (cr > 255) 
		cr = 255; 
	else if (cr < 0) 
		cr = 0;
				
	int cg = col - 256; 
	if (cg > 255) 
		cg = 255; 
	else if (cg < 0) 
		cg = 0;
	
	int cb = col - 512; 
	if (cb > 255) 
		cb = 255; 
	else if (cb < 0) 
		cb = 0;
							
	return RGB(cr, cg, cb);
}

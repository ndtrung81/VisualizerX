// DiffractionDialog.cpp : implementation file
//

#include "stdafx.h"
#include "visualizer_x.h"
#include "DiffractionDialog.h"
#include "Visualizer_XView.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDiffractionDialog dialog


CDiffractionDialog::CDiffractionDialog(CWnd* pParent /*=NULL*/)
	: CResizingDialog(CDiffractionDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDiffractionDialog)
	m_intensity = 1.0;
	m_peakwidth = 1.0;
	m_zoom = 1.0;
	m_nFFTSizeIndex = 2;
	//}}AFX_DATA_INIT

	m_nID = CDiffractionDialog::IDD;
	m_pParent = pParent;

	m_diffData = 0x0;
	m_nDiffWindowSize = 256;
	
}


void CDiffractionDialog::DoDataExchange(CDataExchange* pDX)
{
	CResizingDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDiffractionDialog)
	DDX_Control(pDX, IDC_STATIC_DIFF, m_diffPlot);
	DDX_Text(pDX, IDC_EDIT_INTENSITY, m_intensity);
	DDX_Text(pDX, IDC_EDIT_PEAKWIDTH, m_peakwidth);
	DDX_Text(pDX, IDC_EDIT_ZOOM, m_zoom);
	DDX_CBIndex(pDX, IDC_COMBO_FFTSIZE, m_nFFTSizeIndex);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDiffractionDialog, CResizingDialog)
	//{{AFX_MSG_MAP(CDiffractionDialog)
	ON_BN_CLICKED(IDC_UPDATE, OnUpdateDiffraction)
	ON_WM_CLOSE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDiffractionDialog message handlers

BOOL CDiffractionDialog::Create()
{
	return CResizingDialog::Create(m_nID, m_pParent);
}

void CDiffractionDialog::OnUpdateDiffraction() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	UpdateDiffractionExt();
}

void CDiffractionDialog::UpdateDiffractionExt()
{
	m_nFFTSize = (int)pow(2.0, m_nFFTSizeIndex+6);
	((CVisualizer_XView*)m_pParent)->ComputeDiffraction(m_nFFTSize, m_peakwidth, m_intensity, m_zoom);
	m_diffData = ((CVisualizer_XView*)m_pParent)->m_diffData;

	if (m_diffData == NULL)
		return;

	ScaleData();

	m_diffPlot.m_diffData = m_diffData;
	m_diffPlot.m_nFFTSize = m_nFFTSize;
	m_diffPlot.m_zoom = m_zoom * ((double)m_nDiffWindowSize/m_nFFTSize);
	m_diffPlot.Invalidate();
}

void CDiffractionDialog::ScaleData()
{
	if (m_diffData == NULL)
		return;

	int i, j;
	for (i=0; i<m_nFFTSize; i++)
		for (j=0; j<m_nFFTSize; j++)
		{
			int c = (int)(m_diffData[i][j]);
			m_diffData[i][j] = (c > 0xffff ? (short)0xffff : (short)c);
			
		}

}

void CDiffractionDialog::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	((CVisualizer_XView*)m_pParent)->m_pDiffractionDialog = NULL;
	DestroyWindow();
}

void CDiffractionDialog::OnSize(UINT nType, int cx, int cy) 
{
	CResizingDialog::OnSize(nType, cx, cy);
	
	if (m_diffPlot.m_hWnd == NULL)
		return;

	// TODO: Add your message handler code here
	MoveControls();
}

void CDiffractionDialog::MoveControls()
{
	CRect rect;
	GetClientRect(&rect);
	int width = rect.Width();
	int height = rect.Height();
	int size;
	if (width < height - 80)
		size = width - 6;
	else
		size = height - 80;
	

	rect.top += 3;
	rect.left += 3;
	rect.right = rect.left + size;
	rect.bottom = rect.top + size;

	CRect curRect;
	m_diffPlot.GetClientRect(&curRect);
	
	m_diffPlot.MoveWindow(&rect);
	if (curRect.Width() != rect.Width() || curRect.Height() != rect.Height())
		m_diffPlot.Invalidate();

	
	int plot_width = rect.Width();
	int plot_height = rect.Height();

	CWnd* pWnd;
	
	GetClientRect(&rect);
	pWnd = GetDlgItem(IDC_STATIC_FFTSIZE);
	rect.top = plot_height + 15;
	rect.left += 3;
	rect.right = rect.left + 60;
	rect.bottom = rect.top + 14;
	pWnd->MoveWindow(&rect);

	GetClientRect(&rect);
	pWnd = GetDlgItem(IDC_COMBO_FFTSIZE);
	rect.top = plot_height + 12;
	rect.left += 70;
	rect.right = rect.left + 60;
	rect.bottom = rect.top + 14;
	pWnd->MoveWindow(&rect);

	GetClientRect(&rect);
	pWnd = GetDlgItem(IDC_STATIC_INTENSITY);
	rect.top = plot_height + 15;
	rect.left += 140;
	rect.right = rect.left + 40;
	rect.bottom = rect.top + 14;
	pWnd->MoveWindow(&rect);

	GetClientRect(&rect);
	pWnd = GetDlgItem(IDC_EDIT_INTENSITY);
	rect.top = plot_height + 12;
	rect.left += 190;
	rect.right = rect.left + 60;
	rect.bottom = rect.top + 20;
	pWnd->MoveWindow(&rect);

	GetClientRect(&rect);
	pWnd = GetDlgItem(IDC_UPDATE);
	rect.top = plot_height + 12;
	rect.right = rect.left + 3 + size;
	rect.left = rect.right - 70;
	rect.bottom = rect.top + 22;
	pWnd->MoveWindow(&rect);

	GetClientRect(&rect);
	pWnd = GetDlgItem(IDC_STATIC_PEAKWIDTH);
	rect.top = plot_height + 43;
	rect.left += 3;
	rect.right = rect.left + 60;
	rect.bottom = rect.top + 14;
	pWnd->MoveWindow(&rect);

	GetClientRect(&rect);
	pWnd = GetDlgItem(IDC_EDIT_PEAKWIDTH);
	rect.top = plot_height + 40;
	rect.left += 70;
	rect.right = rect.left + 60;
	rect.bottom = rect.top + 20;
	pWnd->MoveWindow(&rect);

	GetClientRect(&rect);
	pWnd = GetDlgItem(IDC_STATIC_ZOOM);
	rect.top = plot_height + 43;
	rect.left += 140;
	rect.right = rect.left + 50;
	rect.bottom = rect.top + 14;
	pWnd->MoveWindow(&rect);

	GetClientRect(&rect);
	pWnd = GetDlgItem(IDC_EDIT_ZOOM);
	rect.top = plot_height + 40;
	rect.left += 190;
	rect.right = rect.left + 60;
	rect.bottom = rect.top + 20;
	pWnd->MoveWindow(&rect);
}

BOOL CDiffractionDialog::OnInitDialog() 
{
	CResizingDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	HICON hIcon = AfxGetApp()->LoadIcon(IDI_DIFFRACTION);
	SetIcon(hIcon, TRUE);
	SetIcon(hIcon, FALSE);

	MoveControls();

	UpdateDiffractionExt();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDiffractionDialog::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	delete this;
}

// RDFDialog.cpp : implementation file
//

#include "stdafx.h"
#include "visualizer_x.h"
#include "RDFDialog.h"
#include "Visualizer_XView.h"
#include "Texture.h"
#include "FormatDialog.h"

#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define anint(x) ((x >= 0.5) ? (1.0) : (x < -0.5) ? (-1.0) : (0.0))

using namespace std;
/////////////////////////////////////////////////////////////////////////////
// CRDFDialog dialog

static UINT auIDToolBar[] = {
	ID_FORMAT_SAVE,
	ID_GRAPH_COPYTOCLIPBOARD,
	ID_SEPARATOR,
	ID_FORMAT_SERIES,
	ID_FORMAT_GRIDLINES,
};

CRDFDialog::CRDFDialog(CWnd* pParent /*=NULL*/)
	: CResizingDialog(CRDFDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRDFDialog)
	m_nType = 0;
	m_binSize = 0.1;
	m_Lmax = 1.0;
	m_xypos = _T("");
	m_bDrawCursor = TRUE;
	m_nDimension = 0;
	m_bInverse = FALSE;
	//}}AFX_DATA_INIT

	m_nID = CRDFDialog::IDD;
	m_pParent = pParent;

	m_bRDFCalculated = FALSE;
}


void CRDFDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRDFDialog)
	DDX_Control(pDX, IDC_SCROLL_BINSIZE, m_binsizeCtrl);
	DDX_Control(pDX, IDC_EDIT_RDFGRAPH, m_edit);
	DDX_CBIndex(pDX, IDC_COMBO_TYPE, m_nType);
	DDX_Text(pDX, IDC_EDIT_BINSIZE, m_binSize);
	DDX_Text(pDX, IDC_EDIT_LMAX, m_Lmax);
	DDX_Text(pDX, IDC_STATIC_XYPOS, m_xypos);
	DDX_Check(pDX, IDC_CHECK_CURSOR, m_bDrawCursor);
	DDX_CBIndex(pDX, IDC_COMBO_DIM, m_nDimension);
	DDX_Check(pDX, IDC_CHECK_SQ, m_bInverse);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRDFDialog, CResizingDialog)
	//{{AFX_MSG_MAP(CRDFDialog)
	ON_WM_CLOSE()
	ON_BN_CLICKED(ID_COMPUTE, OnCompute)
	ON_WM_SIZE()
	ON_COMMAND(ID_FORMAT_GRIDLINES, OnFormatGridlines)
	ON_COMMAND(ID_GRAPH_COPYTOCLIPBOARD, OnGraphCopytoclipboard)
	ON_COMMAND(ID_FORMAT_SERIES, OnFormatSeries)
	ON_CBN_SELCHANGE(IDC_COMBO_TYPE, OnSelchangeComboType)
	ON_BN_CLICKED(IDC_CHECK_CURSOR, OnCheckCursor)
	ON_WM_MOUSEMOVE()
	ON_CBN_SELCHANGE(IDC_COMBO_DIM, OnSelchangeComboDim)
	ON_COMMAND(ID_FORMAT_SAVE, OnFormatSave)
	ON_WM_VSCROLL()
	ON_BN_CLICKED(IDC_CHECK_SQ, OnCheckSq)
	//}}AFX_MSG_MAP
	ON_WM_INITMENUPOPUP()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRDFDialog message handlers

BOOL CRDFDialog::Create()
{
	return CResizingDialog::Create(m_nID, m_pParent);
}

void CRDFDialog::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	((CVisualizer_XView*)m_pParent)->m_pRDFDialog = NULL;
	DestroyWindow();
}

void CRDFDialog::Compute()
{
	int i, j, ibin, N;
	double vb, dist, dx, dy, dz, r2, bulkDensity;
	double PI = 4.0 * atan(1.0);

	UpdateData(TRUE);
	m_xypos.Format("Computing..");
	UpdateData(FALSE);

	vector<CPosition> pos;
	for (i=0; i<m_positionArray.size(); i++)
	{
		if (m_positionArray[i].GetType() == m_nType-1 || m_nType == 0) // all
			pos.push_back(m_positionArray[i]);
	}
	
	N = pos.size();
	if (N <= 1) 
	{
		m_edit.m_graphCtrl.ResetData();
		m_edit.Invalidate();
		return;
	}

	int nBins = m_Lmax / m_binSize + 1;
	double* g = new double [nBins];
	double* r = new double [nBins];
	for (i=0; i<nBins; i++)
		g[i] = 0.0;

	for (i=0; i<N-1; i++)	
	{
		for (j=i+1; j<N; j++)
		{
			dx = pos[i][0] - pos[j][0];
			dy = pos[i][1] - pos[j][1];
			dz = pos[i][2] - pos[j][2];
			
			dx -= m_Lx * anint(dx / m_Lx);
			dy -= m_Ly * anint(dy / m_Ly);
			dz -= m_Lz * anint(dz / m_Lz);
			
			if (m_nDimension == 0) // 3D
				r2 = dx * dx + dy * dy + dz * dz;
			else
				r2 = dx * dx + dy * dy;			

			dist = sqrt(r2);
			ibin = (int)(dist / m_binSize);
			if (ibin < nBins)
				g[ibin] += 2;
		}
	}

	if (m_nDimension == 0) // 3D
		bulkDensity = (double)N / (m_Lx * m_Ly * m_Lz);
	else
		bulkDensity = (double)N / (m_Lx * m_Ly);

	double factor, Nideal;
	if (m_nDimension == 0) // 3D
		factor = 4.0 * PI * pow(m_binSize, 3.0) / 3.0;
	else
		factor = PI * pow(m_binSize, 2.0);

	for (i=0; i<nBins; i++)
	{
		r[i] = (i + 0.5 + 1) * m_binSize;
		if (m_nDimension == 0) // 3D
			vb =  factor * (pow(i+1, 3.0) - pow(i, 3.0));
		else
			vb =  factor * (pow(i+1, 2.0) - pow(i, 2.0));

		Nideal = vb * bulkDensity;

		g[i] = g[i] / (N * Nideal);
	}

	
	double *q, *S;
	if (m_bInverse) 
	{
		q = new double [nBins];
		S = new double [nBins];
		structure_factor(r, g, nBins, bulkDensity, q, S);
	}

	// refresh graph	
	CSerie rSerie;

	m_edit.m_graphCtrl.ResetData();

	for (i=0; i<nBins; i++)
	{
		if (m_bInverse)
			rSerie.AddElement(q[i]);
		else
			rSerie.AddElement(r[i]);
	}

	m_edit.m_graphCtrl.AddSerie(rSerie);

	CSerie serie;
	if (m_bInverse)
		serie.m_sName = _T("S(q)");
	else
		serie.m_sName = _T("g(r)");
	serie.m_nColor = RGB(255, 0, 0);
	
	for (i=0; i<nBins; i++)
	{
		if (m_bInverse)
			serie.AddElement(S[i]);
		else
			serie.AddElement(g[i]);
	}
	
	m_edit.m_graphCtrl.AddSerie(serie);
	
	if (m_bInverse) 
	{ 
		m_edit.m_graphCtrl.m_sYLabel = "S(q)";
		m_edit.m_graphCtrl.m_sXLabel = "q";
	}
	else
	{
		m_edit.m_graphCtrl.m_sYLabel = "g(r)";
		m_edit.m_graphCtrl.m_sXLabel = "r";
	}

	m_edit.m_graphCtrl.m_bDrawLegend = FALSE;
	m_edit.m_graphCtrl.SetMultiChart(FALSE);
	m_edit.m_graphCtrl.SetAuto(TRUE);
	m_edit.m_graphCtrl.m_minx = 0.0;
	m_edit.m_graphCtrl.m_maxx = rSerie.GetMaxVal();
	m_edit.m_graphCtrl.m_miny = serie.GetMinVal();;
	m_edit.m_graphCtrl.m_maxy = 1.1 * serie.GetMaxVal();
	m_edit.m_graphCtrl.m_largeTickXInterval = (m_edit.m_graphCtrl.m_maxx - m_edit.m_graphCtrl.m_minx) / 5.0;
	m_edit.m_graphCtrl.m_smallTickXInterval = m_edit.m_graphCtrl.m_largeTickXInterval / 2.0;
	m_edit.m_graphCtrl.m_largeTickYInterval = (m_edit.m_graphCtrl.m_maxy - m_edit.m_graphCtrl.m_miny) / 5.0;
	m_edit.m_graphCtrl.m_smallTickYInterval = m_edit.m_graphCtrl.m_largeTickYInterval / 2.0;
	
	m_xypos.Format("");
	m_edit.m_graphCtrl.m_bDrawCursor = m_bDrawCursor;
	UpdateData(FALSE);
	
	m_edit.Invalidate(FALSE);

	delete [] r;
	delete [] g;
	if (m_bInverse) 
	{
		delete [] q;
		delete [] S;
	}

	m_bRDFCalculated = TRUE;
}


void CRDFDialog::OnCompute() 
{
	// TODO: Add your control notification handler code here
	Compute();
}

void CRDFDialog::OnSize(UINT nType, int cx, int cy) 
{
	CResizingDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if (m_edit.m_hWnd == NULL)
		return;

	// We need to resize the dialog to make room for control bars.
	// First, figure out how big the control bars are.
	CRect rcClientStart;
	CRect rcClientNow;
	GetClientRect(rcClientStart);
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST,
				   0, reposQuery, rcClientNow);

	// And position the control bars
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);

	MoveControls();
}

void CRDFDialog::MoveControls()
{
	CRect rect;
	GetClientRect(&rect);
	rect.top += 35;
	rect.left += 3;
	rect.right -= 3;
	rect.bottom -= 60;
	m_edit.MoveWindow(&rect);
	m_edit.Invalidate(FALSE);

	int chart_width = rect.Width();
	int chart_height = rect.Height();

	CWnd* pWnd;
	
	GetClientRect(&rect);
	pWnd = GetDlgItem(IDC_STATIC_TYPE);
	rect.top = 35 + chart_height + 15;
	rect.left += 3;
	rect.right = rect.left + 30;
	rect.bottom = rect.top + 14;
	pWnd->MoveWindow(&rect);

	GetClientRect(&rect);
	pWnd = GetDlgItem(IDC_COMBO_TYPE);
	rect.top = 35 + chart_height + 12;
	rect.left += 40;
	rect.right = rect.left + 50;
	rect.bottom = rect.top + 14;
	pWnd->MoveWindow(&rect);

	GetClientRect(&rect);
	pWnd = GetDlgItem(IDC_STATIC_BINSIZE);
	rect.top = 35 + chart_height + 15;
	rect.left += 100;
	rect.right = rect.left + 40;
	rect.bottom = rect.top + 14;
	pWnd->MoveWindow(&rect);

	GetClientRect(&rect);
	pWnd = GetDlgItem(IDC_EDIT_BINSIZE);
	rect.top = 35 + chart_height + 12;
	rect.left += 150;
	rect.right = rect.left + 40;
	rect.bottom = rect.top + 20;
	pWnd->MoveWindow(&rect);

	GetClientRect(&rect);
	pWnd = GetDlgItem(IDC_SCROLL_BINSIZE);
	rect.top = 35 + chart_height + 12;
	rect.left += 190;
	rect.right = rect.left + 15;
	rect.bottom = rect.top + 20;
	pWnd->MoveWindow(&rect);

	GetClientRect(&rect);
	pWnd = GetDlgItem(IDC_STATIC_LMAX);
	rect.top = 35 + chart_height + 15;
	rect.left += 230;
	rect.right = rect.left + 30;
	rect.bottom = rect.top + 14;
	pWnd->MoveWindow(&rect);

	GetClientRect(&rect);
	pWnd = GetDlgItem(IDC_EDIT_LMAX);
	rect.top = 35 + chart_height + 12;
	rect.left += 260;
	rect.right = rect.left + 40;
	rect.bottom = rect.top + 20;
	pWnd->MoveWindow(&rect);

	GetClientRect(&rect);
	pWnd = GetDlgItem(IDC_COMBO_DIM);
	rect.top = 35 + chart_height + 12;
	rect.left += 320;
	rect.right = rect.left + 50;
	rect.bottom = rect.top + 14;
	pWnd->MoveWindow(&rect);

	GetClientRect(&rect);
	pWnd = GetDlgItem(IDC_CHECK_CURSOR);
	rect.top = 35 + chart_height + 35;
	rect.left += 3;
	rect.right = rect.left + 80;
	rect.bottom = rect.top + 22;
	pWnd->MoveWindow(&rect);

	GetClientRect(&rect);
	pWnd = GetDlgItem(IDC_STATIC_XYPOS);
	rect.top = 35 + chart_height + 35;
	rect.left += 120;
	rect.right = rect.left + 120;
	rect.bottom = rect.top + 22;
	pWnd->MoveWindow(&rect);

	GetClientRect(&rect);
	pWnd = GetDlgItem(IDC_CHECK_SQ);
	rect.top = 35 + chart_height + 35;
	rect.left += 240;
	rect.right = rect.left + 100;
	rect.bottom = rect.top + 22;
	pWnd->MoveWindow(&rect);


	GetClientRect(&rect);
	pWnd = GetDlgItem(ID_COMPUTE);
	rect.top = 35 + chart_height + 12;
	rect.right -= 10;
	rect.left = rect.right - 70;
	rect.bottom = rect.top + 22;
	pWnd->MoveWindow(&rect);
}

void CRDFDialog::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	delete this;
}

BOOL CRDFDialog::OnInitDialog() 
{
	CResizingDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	// Create toolbar at the top of the dialog window
	m_lpaIDToolBar   = auIDToolBar;
	m_cIDToolBar     = sizeof(auIDToolBar)/sizeof(UINT);
	m_nIDBitmap      = IDR_FORMAT_TOOLBAR;

	if (m_toolbar.Create(this))
	{
		m_toolbar.LoadBitmap(m_nIDBitmap);
		m_toolbar.SetButtons(m_lpaIDToolBar, m_cIDToolBar);
	}

	m_toolbar.SetBarStyle(m_toolbar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC | CBRS_BORDER_BOTTOM | CBRS_BORDER_TOP);

	// And position the control bars
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);

	// We need to resize the dialog to make room for control bars.
	// First, figure out how big the control bars are.
	CRect rcClientStart;
	CRect rcClientNow;
	GetClientRect(rcClientStart);
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST,
				   0, reposQuery, rcClientNow);

	// Now move all the controls so they are in the same relative
	// position within the remaining client area as they would be
	// with no control bars.
	CPoint ptOffset(rcClientNow.left - rcClientStart.left,
					rcClientNow.top - rcClientStart.top);

	CRect  rcChild;
	CWnd* pwndChild = GetWindow(GW_CHILD);
	while (pwndChild)
	{
		pwndChild->GetWindowRect(rcChild);
		ScreenToClient(rcChild);
		rcChild.OffsetRect(ptOffset);
		pwndChild->MoveWindow(rcChild, FALSE);
		pwndChild = pwndChild->GetNextWindow();
	}
	// And position the control bars
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);

	m_toolbar.SetButtonStyle(4, TBBS_CHECKBOX);	// grid

	int nState = m_toolbar.GetToolBarCtrl().GetState(ID_FORMAT_GRIDLINES);
	m_toolbar.GetToolBarCtrl().SetState(ID_FORMAT_GRIDLINES, 
			nState | TBSTATE_CHECKED);
	
	

	HICON hIcon = AfxGetApp()->LoadIcon(IDR_RDF);
	SetIcon(hIcon, TRUE);
	SetIcon(hIcon, FALSE);

	MoveControls();

	m_edit.m_graphCtrl.m_sYLabel = "g(r)";
	m_edit.m_graphCtrl.m_sXLabel = "r";
	m_edit.m_graphCtrl.m_bDrawCursor = TRUE;
	m_edit.m_graphCtrl.m_nLineWeight = 2;

	m_binsizeCtrl.SetScrollRange(0, 100);
	m_binsizeCtrl.SetScrollPos(50);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CRDFDialog::OnInitMenuPopup(CMenu *pPopupMenu, UINT nIndex,BOOL bSysMenu)
{
    ASSERT(pPopupMenu != NULL);
    // Check the enabled state of various menu items.

    CCmdUI state;
    state.m_pMenu = pPopupMenu;
    ASSERT(state.m_pOther == NULL);
    ASSERT(state.m_pParentMenu == NULL);

    // Determine if menu is popup in top-level menu and set m_pOther to
    // it if so (m_pParentMenu == NULL indicates that it is secondary popup).
    HMENU hParentMenu;
    if (AfxGetThreadState()->m_hTrackingMenu == pPopupMenu->m_hMenu)
        state.m_pParentMenu = pPopupMenu;    // Parent == child for tracking popup.
    else if ((hParentMenu = ::GetMenu(m_hWnd)) != NULL)
    {
        CWnd* pParent = this;
           // Child windows don't have menus--need to go to the top!
        if (pParent != NULL &&
           (hParentMenu = ::GetMenu(pParent->m_hWnd)) != NULL)
        {
           int nIndexMax = ::GetMenuItemCount(hParentMenu);
           for (int nIndex = 0; nIndex < nIndexMax; nIndex++)
           {
            if (::GetSubMenu(hParentMenu, nIndex) == pPopupMenu->m_hMenu)
            {
                // When popup is found, m_pParentMenu is containing menu.
                state.m_pParentMenu = CMenu::FromHandle(hParentMenu);
                break;
            }
           }
        }
    }

    state.m_nIndexMax = pPopupMenu->GetMenuItemCount();
    for (state.m_nIndex = 0; state.m_nIndex < state.m_nIndexMax;
      state.m_nIndex++)
    {
        state.m_nID = pPopupMenu->GetMenuItemID(state.m_nIndex);
        if (state.m_nID == 0)
           continue; // Menu separator or invalid cmd - ignore it.

        ASSERT(state.m_pOther == NULL);
        ASSERT(state.m_pMenu != NULL);
        if (state.m_nID == (UINT)-1)
        {
           // Possibly a popup menu, route to first item of that popup.
           state.m_pSubMenu = pPopupMenu->GetSubMenu(state.m_nIndex);
           if (state.m_pSubMenu == NULL ||
            (state.m_nID = state.m_pSubMenu->GetMenuItemID(0)) == 0 ||
            state.m_nID == (UINT)-1)
           {
            continue;       // First item of popup can't be routed to.
           }
           state.DoUpdate(this, TRUE);   // Popups are never auto disabled.
        }
        else
        {
           // Normal menu item.
           // Auto enable/disable if frame window has m_bAutoMenuEnable
           // set and command is _not_ a system command.
           state.m_pSubMenu = NULL;
           state.DoUpdate(this, FALSE);
        }

        // Adjust for menu deletions and additions.
        UINT nCount = pPopupMenu->GetMenuItemCount();
        if (nCount < state.m_nIndexMax)
        {
           state.m_nIndex -= (state.m_nIndexMax - nCount);
           while (state.m_nIndex < nCount &&
            pPopupMenu->GetMenuItemID(state.m_nIndex) == state.m_nID)
           {
            state.m_nIndex++;
           }
        }
        state.m_nIndexMax = nCount;
    }
}

void CRDFDialog::OnFormatGridlines() 
{
	// TODO: Add your command handler code here
	m_edit.m_graphCtrl.m_bGridlines = !m_edit.m_graphCtrl.m_bGridlines;
	m_edit.Invalidate(FALSE);
}

void CRDFDialog::OnGraphCopytoclipboard() 
{
	// TODO: Add your command handler code here
	CMetaFileDC * m_pMetaDC = new CMetaFileDC();
	m_pMetaDC->CreateEnhanced(GetDC(), NULL, NULL, "whatever");
	m_pMetaDC->m_hAttribDC = m_edit.GetDC()->GetSafeHdc();
	//draw meta file

	//do what ever you want to do: bitmaps, lines, text...
	m_edit.m_graphCtrl.Draw(m_pMetaDC);
	

	//close meta file dc and prepare for clipboard;
	HENHMETAFILE hMF = m_pMetaDC->CloseEnhanced();

	//copy to clipboard
	OpenClipboard();
	EmptyClipboard();
	::SetClipboardData(CF_ENHMETAFILE, hMF);
	CloseClipboard();
	
	//DeleteMetaFile(hMF);
	delete m_pMetaDC;	
/*
	if(OpenClipboard()) 
	{ 
		BeginWaitCursor(); 
		
		// Snap (see below) 
		
		CSize size; 
		unsigned char *pixel = SnapClient(&size); 
		
		// Image 
		
		CTexture image; 
		
		// Link image - buffer 
		
		VERIFY(image.ReadBuffer(pixel,size.cx,size.cy,24)); 
		
		// Cleanup memory 
		
		delete [] pixel; 
		EmptyClipboard(); 
		SetClipboardData(CF_DIB,image.ExportHandle()); // short is better 
		
		CloseClipboard(); 
		EndWaitCursor(); 
	} 
*/
}

unsigned char* CRDFDialog::SnapClient(CSize *pSize) 
{ 
	BeginWaitCursor(); 
	
	// Client zone 
	
	CRect rect; 
	GetClientRect(&rect); 
	CSize size(rect.Width(),rect.Height()); 
	*pSize = size; 
	ASSERT(size.cx > 0); 
	ASSERT(size.cy > 0); 
	
	// Alloc 
	
	unsigned char *pixel = new unsigned char[3*size.cx*size.cy]; 
	ASSERT(pixel != NULL); 
	
	// Capture frame buffer 
	
	TRACE("Start reading client...\n"); 
	TRACE("Client : (%d,%d)\n",size.cx,size.cy); 
	
	CRect ClientRect,MainRect; 
	this->GetWindowRect(&ClientRect); 
	
	CWnd *pMain = AfxGetApp()->m_pMainWnd; 
	CWindowDC dc(pMain); 
	pMain->GetWindowRect(&MainRect); 
	int xOffset = ClientRect.left - MainRect.left; 
	int yOffset = ClientRect.top - MainRect.top; 
	for(int j=0;j < size.cy; j++)
		for(int i=0;i < size.cx; i++) 
		{ 
			COLORREF color = dc.GetPixel(i+xOffset,j+yOffset); // slow but reliable 
			
			pixel[3*(size.cx*(size.cy-1-j)+i)] = (BYTE)GetBValue(color); 
			pixel[3*(size.cx*(size.cy-1-j)+i)+1] = (BYTE)GetGValue(color); 
			pixel[3*(size.cx*(size.cy-1-j)+i)+2] = (BYTE)GetRValue(color); 
		}  
	EndWaitCursor(); 
	return pixel; 
} 

void CRDFDialog::OnFormatSeries() 
{
	// TODO: Add your command handler code here
	if (m_edit.m_graphCtrl.GetNumSerie() < 2)
		return;

	CFormatDialog dlg;

	dlg.m_nLineWidth	= m_edit.m_graphCtrl.m_nLineWeight;
	dlg.m_nFontSize = m_edit.m_graphCtrl.m_nFontSize;
	dlg.m_largeTickXInterval = m_edit.m_graphCtrl.m_largeTickXInterval;
	dlg.m_smallTickXInterval = m_edit.m_graphCtrl.m_smallTickXInterval;
	dlg.m_largeTickYInterval = m_edit.m_graphCtrl.m_largeTickYInterval;
	dlg.m_smallTickYInterval = m_edit.m_graphCtrl.m_smallTickYInterval;
	dlg.m_color = m_edit.m_graphCtrl.GetSerie(1)->m_nColor;	
	dlg.m_maxx = m_edit.m_graphCtrl.m_maxx;
	dlg.m_minx = m_edit.m_graphCtrl.m_minx;
	dlg.m_maxy = m_edit.m_graphCtrl.m_maxy;
	dlg.m_miny = m_edit.m_graphCtrl.m_miny;

	if (dlg.DoModal() == IDOK)
	{
		m_edit.m_graphCtrl.m_nLineWeight = dlg.m_nLineWidth;
		m_edit.m_graphCtrl.m_nFontSize = dlg.m_nFontSize;
		m_edit.m_graphCtrl.m_largeTickXInterval = dlg.m_largeTickXInterval;
		m_edit.m_graphCtrl.m_smallTickXInterval = dlg.m_smallTickXInterval;
		m_edit.m_graphCtrl.m_largeTickYInterval = dlg.m_largeTickYInterval;
		m_edit.m_graphCtrl.m_smallTickYInterval = dlg.m_smallTickYInterval;
		m_edit.m_graphCtrl.GetSerie(1)->m_nColor = dlg.m_color;
		m_edit.m_graphCtrl.m_maxx = dlg.m_maxx;
		m_edit.m_graphCtrl.m_minx = dlg.m_minx;
		m_edit.m_graphCtrl.m_maxy = dlg.m_maxy;
		m_edit.m_graphCtrl.m_miny = dlg.m_miny;

		m_edit.Invalidate();
	}


}

void CRDFDialog::OnSelchangeComboType() 
{
	// TODO: Add your control notification handler code here
//	UpdateData(TRUE);
	
//	Compute();
}

void CRDFDialog::OnCheckCursor() 
{
	// TODO: Add your control notification handler code here
	m_bDrawCursor = !m_bDrawCursor;
	m_edit.m_graphCtrl.m_bDrawCursor = m_bDrawCursor;
	m_edit.Invalidate();
}

void CRDFDialog::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (m_edit.m_graphCtrl.m_bDrawCursor == FALSE)
		return;

	if (m_edit.m_graphCtrl.GetNumSerie() < 1)
		return;

	CPoint testPoint = point;
	CRect graphRect;
	m_edit.GetWindowRect(&graphRect);
	ClientToScreen(&testPoint);

	graphRect.left += graphRect.Width() / 10;
	graphRect.bottom -= graphRect.Height() / 10;
	if (nFlags == MK_LBUTTON && PtInRect(&graphRect, testPoint))
	{
		CDC* pDC = m_edit.GetDC();
		
		double xval, yval, xvalOld, yvalOld, dx;
		int nCurROPMode;
		nCurROPMode = pDC->GetROP2();
		
		// Find current position
		m_edit.m_graphCtrl.GetCursorValues(xvalOld, yvalOld);

		pDC->SetROP2(2);
		// erase current cursor
		m_edit.m_graphCtrl.DrawCursor(pDC);
		
		// calculate new cursor position
		m_edit.ScreenToClient(&testPoint); 
		m_edit.m_graphCtrl.FindCurXPos(testPoint.x);
		
		// draw new cursor
		m_edit.m_graphCtrl.DrawCursor(pDC);
		
		// restore the old mode
		pDC->SetROP2(nCurROPMode);
		
		
		m_edit.m_graphCtrl.GetCursorValues(xval, yval);
		dx = xval - xvalOld;

		int nCurXPos = m_edit.m_graphCtrl.GetCurXPos();
		if (m_bInverse)
			m_xypos.Format("%0.3f @ q = %0.3f", yval, xval);
		else
			m_xypos.Format("%0.3f @ r = %0.3f", yval, xval);
		UpdateData(FALSE);
		
	}

	CResizingDialog::OnMouseMove(nFlags, point);
}



void CRDFDialog::OnSelchangeComboDim() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	Compute();
}

void CRDFDialog::OnFormatSave() 
{
	// TODO: Add your command handler code here
	if (m_edit.m_graphCtrl.GetNumSerie() < 2) 
		return;

	CFileDialog dlg(FALSE, 
					"txt", 
					NULL, 
					OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
					"Text Files (*.txt)|*.txt|All Files (*.*)|*.*||",
					this);



	if (dlg.DoModal() == IDOK)
	{
		CString fileName = dlg.GetPathName();
		FILE* fp = fopen(fileName, "w");

		int i, nRows;
		CSerie* r = m_edit.m_graphCtrl.GetSerie(0);
		CSerie* g = m_edit.m_graphCtrl.GetSerie(1);

		fprintf(fp, "r\tg(r)\n");
		nRows = r->GetNumElement();
		for (i=0; i<nRows; i++)
			fprintf(fp, "%g\t%g\n", r->GetElement(i), g->GetElement(i));
		

		fclose(fp);
	}
}

void CRDFDialog::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	int curPos = m_binsizeCtrl.GetScrollPos();
	
	UpdateData(TRUE);

	// Determine the new position of scroll box.
	switch (nSBCode)
	{
	case SB_LEFT:      // Scroll to far left.
		curPos = 0;
		break;

	case SB_RIGHT:      // Scroll to far right.
		curPos = 100;
		break;

	case SB_ENDSCROLL:   // End scroll.
		break;

	case SB_LINELEFT:      // Scroll left.
		if (curPos > 0)
		{
			if (m_binSize > 0.01)
				m_binSize += 0.01;
			else
				m_binSize -= 0.001;

			curPos--;
		}
		break;

	case SB_LINERIGHT:   // Scroll right.
		if (curPos < 100)
		{
			if (m_binSize > 0.01)
				m_binSize -= 0.01;
			else
				m_binSize -= 0.001;
			curPos++;
		}
		break;

	case SB_PAGELEFT:    // Scroll one page left.
		{
			// Get the page size. 
			SCROLLINFO   info;
			m_binsizeCtrl.GetScrollInfo(&info, SIF_ALL);
   
			if (curPos > 0)
				curPos = max(0, curPos - (int) info.nPage);
		}
		break;

	case SB_PAGERIGHT:      // Scroll one page right
		{
			// Get the page size. 
			SCROLLINFO   info;
			m_binsizeCtrl.GetScrollInfo(&info, SIF_ALL);

			if (curPos < 100)
				curPos = min(100, curPos + (int) info.nPage);
		}
		break;

	case SB_THUMBPOSITION: // Scroll to absolute position. nPos is the position
		curPos = nPos;      // of the scroll box at the end of the drag operation.
		break;

	case SB_THUMBTRACK:   // Drag scroll box to specified position. nPos is the
		curPos = nPos;     // position that the scroll box has been dragged to.
		break;
	}

	// Set the new position of the thumb (scroll box).
	m_binsizeCtrl.SetScrollPos(curPos);

	if (m_binSize <= 0.0)
		m_binSize = 0.001;
	
	UpdateData(FALSE);

	Compute();

	CResizingDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

// Structure factor: classical
void CRDFDialog::structure_factor(double* r, double* g, int nBins, double bulkDensity, double* q, double* S)
{
	int i, j;
	double dr = r[1] - r[0];
	
	ofstream ofs;
	double fs = 1.0 / (r[1] - r[0]);
	double fspan = fs / 2.0;
	double dq = fspan / nBins;
	double fourPI = 16.0 * atan(1.0);

	fourPI = 16.0 * atan(1.0);
/*	
    for (i=0; i<nBins; i++)
	{
		q[i] = (i + 0.5) * dq;
		
		S[i] = 0.0;
		for (j=0; j<nBins; j++)
			S[i] += (g[j] - 1) * r[j] * sin(q[i] * r[j]) * dr;

		S[i] = 1 + fourPI * bulkDensity * S[i] / q[i];
	}
*/
	double theta, sintheta, costheta, sintheta2, costheta2, theta2, theta3;
    double alpha, beta, gamma, Se, So;  
	
	
    for (i=0; i<nBins; i++)
	{
		q[i] = (i + 0.5) * dq;

		theta = q[i] * dr;
		sintheta = sin(theta);
		costheta = cos(theta);
		sintheta2 = sintheta * sintheta;
		costheta2 = costheta * costheta;
		theta2 = theta * theta;
		theta3 = theta * theta2;

		if (theta < 1e-6)
		{
			alpha	= 0.0;
			beta	= 2.0 / 3.0;
			gamma	= 4.0 / 3.0;
		}
		else
		{
           alpha	= (1.0/theta3) * (theta2 + theta * sintheta * costheta - 2.0 * sintheta2);
           beta		= (2.0/theta3) * (theta * (1.0 + costheta2) - 2.0 * sintheta * costheta);
           gamma	= (4.0/theta3) * (sintheta - theta * costheta);
		}
           
	    // The integral is g(r) * r for the 3D transform		

		// Do the sum over the even ordinates
		Se = 0.0;
		for (j=0; j<nBins; j+=2)
			Se += (g[j] - 1) * r[j] * sin(q[i] * r[j]);

		// Subtract half the first and last terms: here g[0] = 0.0
        Se -= 0.5 * ((g[nBins-1] - 1) * r[nBins-1] * sin(q[i] * r[nBins-1]));
	
		// Do the sum over the odd ordinates
		So = 0.0;
		for (j=1; j<=nBins-1; j+=2)
			So += (g[j] - 1) * r[j] * sin(q[i] * r[j]);
		
		S[i] = (-alpha * (g[nBins-1] - 1) * r[nBins-1] * cos(q[i] * r[nBins-1]) + beta * Se + gamma * So) * dr;

		// Include normalizing factor
		S[i] = 1 + fourPI * bulkDensity * S[i] / q[i];
	}
}

void CRDFDialog::OnCheckSq() 
{
	// TODO: Add your control notification handler code here
	m_bInverse = !m_bInverse;
	Compute();
}

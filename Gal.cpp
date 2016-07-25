// Gal.cpp : implementation file
//

#include "stdafx.h"
#include "Concerto.h"
#include "ConcertoDlg.h"
#include "Gal.h"


// CGal dialog

IMPLEMENT_DYNAMIC(CGal, CDialog)

CGal::CGal(CWnd* pParent /*=NULL*/)
	: CDialog(CGal::IDD, pParent)
{

}

CGal::~CGal()
{
}

void CGal::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIM, lgal);
	DDX_Control(pDX, IDCANCEL, bc);
	DDX_Control(pDX, IDOK, bo);
	DDX_Control(pDX, IDC_SPIN1, spc);
	DDX_Control(pDX, IDC_VIM, vim);
	DDX_Control(pDX, IDC_VALID, bv);
	DDX_Control(pDX, IDC_VMCI, vmci);
}


BEGIN_MESSAGE_MAP(CGal, CDialog)
	ON_WM_CTLCOLOR()
	ON_LBN_DBLCLK(IDC_LIM, &CGal::OnLbnDblclkLim)
	ON_WM_DRAWITEM()
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, &CGal::OnDeltaposSpin1)
	ON_STN_DBLCLK(IDC_VIM, &CGal::OnStnDblclickVim)
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDOK, &CGal::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CGal::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_VALID, &CGal::OnBnClickedValid)
END_MESSAGE_MAP()


// CGal message handlers

BOOL CGal::OnInitDialog()
{
	CConcertoDlg* psource=(CConcertoDlg*)GetParent();
	CString temp;
	CString temp1;
	temp="";
	selfile=-1;
	CDialog::OnInitDialog();
	listefont.CreateFont(psource->whauteur/20,//28,
		psource->wlargeur/50,//89,
		0,
		0,
		300 ,//Epaisseur
		0,
		0,
		0,
		DEFAULT_CHARSET,
		OUT_TT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		NONANTIALIASED_QUALITY,//ANTIALIASED_QUALITY,//PROOF_QUALITY,
		DEFAULT_PITCH|FF_DONTCARE,
		"ARIAL");
	butfont.CreateFont(psource->whauteur/40,//28,
		psource->wlargeur/80,//89,
		0,
		0,
		600 ,//Epaisseur
		0,
		0,
		0,
		DEFAULT_CHARSET,
		OUT_TT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		NONANTIALIASED_QUALITY,//ANTIALIASED_QUALITY,//PROOF_QUALITY,
		DEFAULT_PITCH|FF_DONTCARE,
		"ARIAL");
	//CRect wrct;
	CRect rct;
	//GetDesktopWindow( )->GetWindowRect(&wrct);
	int wlargeur=2*psource->wlargeur/3;
	int whauteur=2*psource->whauteur/5;
	SetWindowPos(&wndBottom,0,0,wlargeur,whauteur,SWP_HIDEWINDOW);
	CenterWindow();
	ShowWindow(1);
	GetClientRect(&rct);
	wlargeur=rct.Width();
	whauteur=rct.Height();
	//lgal.SetItemHeight(0,whauteur/7);
	bc.SetFont(&butfont,TRUE);
	bv.SetFont(&butfont,TRUE);
	bo.SetFont(&butfont,TRUE);
	if(mode==0||mode==2)
	{
		vim.SetWindowPos(&wndBottom,wlargeur/10,whauteur/20,8*wlargeur/10,12*whauteur/20,SWP_SHOWWINDOW);
		vmci.SetWindowPos(&wndBottom,wlargeur/10,whauteur/20,8*wlargeur/10,12*whauteur/20,SWP_HIDEWINDOW);
		spc.SetWindowPos(&wndBottom,wlargeur/10,14*whauteur/20,8*wlargeur/10,2*whauteur/20,SWP_SHOWWINDOW);
		bc.SetWindowPos(&wndBottom,(int)(wlargeur/10),(int)(17*whauteur/20),(int)(2.5*wlargeur/10),(int)(2*whauteur/20),SWP_SHOWWINDOW);
		bv.SetWindowPos(&wndBottom,(int)(3.75*wlargeur/10),(int)(17*whauteur/20),(int)(2.5*wlargeur/10),(int)(2*whauteur/20),SWP_SHOWWINDOW);
		bo.SetWindowPos(&wndBottom,(int)(6.5*wlargeur/10),(int)(17*whauteur/20),(int)(2.5*wlargeur/10),(int)(2*whauteur/20),SWP_SHOWWINDOW);
		bc.SetWindowTextA(psource->txtc[112]);//Annuler
		bv.SetWindowTextA(psource->txtc[127]);//Valider
		bo.SetWindowTextA(psource->txtc[128]);//Pas de logo
	}
	else
	{
		vim.SetWindowPos(&wndBottom,wlargeur/10,whauteur/20,8*wlargeur/10,12*whauteur/20,SWP_HIDEWINDOW);
		vmci.SetWindowPos(&wndBottom,3*wlargeur/10,whauteur/20,4*wlargeur/10,12*whauteur/20,SWP_SHOWWINDOW);
		spc.SetWindowPos(&wndBottom,wlargeur/10,14*whauteur/20,8*wlargeur/10,2*whauteur/20,SWP_SHOWWINDOW);
		bc.SetWindowPos(&wndBottom,(int)(wlargeur/10),(int)(17*whauteur/20),(int)(3*wlargeur/10),(int)(2*whauteur/20),SWP_SHOWWINDOW);
		bv.SetWindowPos(&wndBottom,(int)(wlargeur/2+wlargeur/10),(int)(17*whauteur/20),(int)(3*wlargeur/10),(int)(2*whauteur/20),SWP_SHOWWINDOW);
		bo.SetWindowPos(&wndBottom,(int)(6.5*wlargeur/10),(int)(17*whauteur/20),(int)(2.5*wlargeur/10),(int)(2*whauteur/20),SWP_HIDEWINDOW);
		bc.SetWindowTextA(psource->txtc[112]);//Annuler
		bv.SetWindowTextA(psource->txtc[127]);//Valider
	}


	lgal.ResetContent();
	if(psource->dirlist.GetCount()==0)
	{
		spc.EnableWindow(0);
		selfile=-1;
	}
	else
	{
		for(int i=0;i<psource->dirlist.GetCount();i++)
		{
			psource->dirlist.GetText(i,temp);
			lgal.AddString(temp);
		}
		selfile=0;
	}
	lgal.SetCurSel(selfile);
	if(mode==0||mode==2)
		vim.RedrawWindow(0,0,1|256|4);
	else
	{
		vmci.RedrawWindow(0,0,1|256|4);
		PlayGalAvi();
	}
	return TRUE;  // retourne TRUE, sauf si vous avez défini le focus sur un contrôle
}

HBRUSH CGal::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	return hbr;
}

void CGal::OnLbnDblclkLim()
{
}

void CGal::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CConcertoDlg* par=(CConcertoDlg*)GetParent();
	if(lpDrawItemStruct->CtlType==ODT_STATIC&&nIDCtl==IDC_VIM)
	{
		CString temp;
		CString temp1;
		CDC dc;
		RECT rct;
		int al;
		int ah;
		int OLT=0;
		int i=0;
		dc.Attach(lpDrawItemStruct->hDC);
		rct=lpDrawItemStruct->rcItem;
		dc.SelectStockObject(WHITE_BRUSH);
		dc.SelectStockObject(WHITE_PEN);
		dc.Rectangle(&rct);
		if(selfile>=0)
		{
			ah=rct.bottom-rct.top;
			al=rct.right-rct.left;
			int idx=selfile;
			OLT=DrawGalImage(&dc,OLT,al,ah,idx,0);
			i=OLT;
			while(i<rct.right)// Dessine les images à gauche
			{
				idx++;
				if(idx>lgal.GetCount()-1)
				idx=0;
				i=DrawGalImage(&dc,i,al,ah,idx,1);
			}
			i=orgim;
			idx=selfile;
			while(i>0)// Dessine les images à gauche
			{
				idx--;
				if(idx<0)
				idx=lgal.GetCount()-1;
				i=DrawGalImage(&dc,i,al,ah,idx,-1);
			}/**/
		}
		else
		{
			CFont* poldfont=dc.SelectObject(&listefont);
			dc.SetTextColor(0x0000ff);
			dc.SetBkColor(0xFFFFFF);
			dc.DrawText(par->txtm[62],&rct,DT_VCENTER|DT_CENTER|DT_SINGLELINE);//"Pas d'images disponibles"
			dc.SelectObject(poldfont);
		}
		dc.Detach();
	}
	CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
}
void CGal::PlayGalAvi() 
{
	CConcertoDlg* par=(CConcertoDlg*)GetParent();
	CString temp;
	CRect frct;
	if(SCR!=NULL)
	{
		MCIWndClose(SCR);
		MCIWndDestroy(SCR);
		SCR=NULL;
	}
	lgal.GetText(selfile,temp);
	if(mode==3)
		temp=par->workdir+temp;
	SCR=MCIWndCreate(vmci.GetSafeHwnd(),AfxGetInstanceHandle( ),WS_CHILD|WS_VISIBLE|MCIWNDF_NOOPEN|MCIWNDF_NOPLAYBAR|MCIWNDF_NOTIFYMODE|MCIWNDF_NOERRORDLG|MCIWNDF_NOMENU,temp);//|MCIWNDF_NOAUTOSIZEWINDOW
	vmci.GetWindowRect(&frct);
	if(SCR==NULL)
		MessageBox("MCI Fail");
	else
	{
		::SetWindowPos(SCR,HWND_TOPMOST,0,0,frct.Width(),frct.Height(),SWP_HIDEWINDOW);
		MCIWndPutDest(SCR,&frct);
		::SetWindowPos(SCR,HWND_TOPMOST,0,0,frct.Width(),frct.Height(),SWP_SHOWWINDOW|SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
		MCIWndPlay(SCR);
	}
}

int CGal::DrawGalImage(CDC* pdc,int OLT,int al,int ah,int idx, int pos) 
{
	CConcertoDlg* par=(CConcertoDlg*)GetParent();
	CString temp;
	CString tolt;
	CString trl;
	CString tol;
	CString tx;
	CString tox;
	CStringW wstr;
	int RH=0;
	int RL=0;
	int OH=0;
	int OL=0;
	int ox=0;
	double ratio;
	double x;
	double xs;
	double ys;
	double h;
	double l;
	RECT frct;
	Graphics gr (pdc->m_hDC);
	lgal.GetText(idx,temp);
	if(mode==0)
		wstr=temp;
	else
		wstr=par->workdir+temp;
	Image myImage(wstr);
	x=xs=(double)myImage.GetWidth( );//
	ys=(double)myImage.GetHeight( );//
	ratio=xs/ys;
	h=ah;
	l=al/2;
	ox=0;
	if(((xs*h)/ys)>(l))
	{
		RH=(int)(l*ys/xs);
		OH=((int)h-RH)/2;				
		RL=(int)l;
		ox=0;
		if(pos==0)
		{
			orgim=OL=(int)(l/2);
		}
		else
		{
			if(pos==1)
			{
				OL=(int)OLT;	// origine suivante
			}
			else
			{
				OL=(int)OLT-RL;	// origine précédente
				if(OL<0)
				{
					x=(RL+OL)*xs/RL;
					RL=OLT;
					ox=(int)(xs-x);
					OL=0;
				}
			}
		}
	}
	else
	{
		OH=(int)0;
		RL=(int)(((h*xs))/ys);
		RH=(int)h;
		ox=0;
		if(pos==0)
		{
			orgim=OL=(int)l/2+((int)l-RL)/2;
		}
		else
		{
			if(pos==1)
			{
				OL=(int)OLT;
			}
			else
			{
				OL=(int)OLT-RL;
				if(OL<0)
				{
					x=(RL+OL)*xs/RL;
					RL=OLT;
					ox=(int)(xs-x);
					OL=0;
				}
			}
		}

	}
	//if(OL>0)
	{
		RectF dest((REAL)OL,(REAL)OH,(REAL)RL,(REAL)RH);
		gr.DrawImage( &myImage,dest,(REAL)ox,0,(REAL)x,(REAL)ys,UnitPixel,0,0,0);
	}
	if(pos==0)
	{
		pdc->SelectStockObject(NULL_BRUSH);
		pdc->SelectStockObject(BLACK_PEN);
		frct.left=(LONG)OL;
		frct.right=(LONG)(OL+RL);
		frct.top=(LONG)OH;
		frct.bottom=(LONG)(OH+RH);
		pdc->DrawEdge(&frct,EDGE_SUNKEN,BF_RECT);//EDGE_RAISED
		DrawFocusRect(pdc->m_hDC,&frct);
	}
	if(pos<0)
	{
		return OL;
	}
	else
		return (OL+RL);
}

LRESULT CGal::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	return CDialog::DefWindowProc(message, wParam, lParam);
}


void CGal::OnDeltaposSpin1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	if(pNMUpDown->iDelta<0)
	{
		if(selfile<lgal.GetCount()-1)
			selfile++;
		else
			selfile=0;
	}
	else
	{
		if(selfile>0)
			selfile--;
		else
			selfile=lgal.GetCount()-1;
	}
	lgal.SetCurSel(selfile);
	if(mode==0||mode==2)
		vim.RedrawWindow(0,0,1|256|4);
	else
		PlayGalAvi(); 
	*pResult = 0;
}

void CGal::OnStnDblclickVim()
{
	CConcertoDlg* psource=(CConcertoDlg*)GetParent();
	if(psource->dirlist.GetCount()>0)
		OnOK();
	else
		OnCancel();
}

void CGal::OnMouseMove(UINT nFlags, CPoint point)
{

	CDialog::OnMouseMove(nFlags, point);
}

void CGal::OnBnClickedOk()
{
	selfile=-1;
	OnOK();
}

void CGal::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	OnCancel();
}

void CGal::OnBnClickedValid()
{
	CConcertoDlg* psource=(CConcertoDlg*)GetParent();
	if(psource->dirlist.GetCount()>0)
		OnOK();
}

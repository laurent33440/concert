// Message.cpp : implementation file
//

#include "stdafx.h"
#include "Concerto.h"
#include "ConcertoDlg.h"
#include "Ident.h"


// CIdent dialog

IMPLEMENT_DYNAMIC(CIdent, CDialog)

CIdent::CIdent(CWnd* pParent /*=NULL*/)
	: CDialog(CIdent::IDD, pParent)
	, titre(_T(""))
	, nmes1(_T(""))
	, nmes2(_T(""))
	, nmes3(_T(""))
	, nmes4(_T(""))
	, serialtxt(_T(""))
	, mes2(_T(""))
	, mes3(_T(""))
	, mes4(_T(""))
{

}

CIdent::~CIdent()
{
}

void CIdent::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, bok);
	DDX_Control(pDX, IDC_STITRE, stitre);
	DDX_Control(pDX, IDC_SNMES1, snmes1);
	DDX_Control(pDX, IDC_SNMES2, snmes2);
	DDX_Control(pDX, IDC_SNMES3, snmes3);
	DDX_Control(pDX, IDC_SNMES4, snmes4);
	DDX_Control(pDX, IDC_SERIAL, sserial);
	DDX_Control(pDX, IDC_SMES2, smes2);
	DDX_Control(pDX, IDC_SMES3, smes3);
	DDX_Control(pDX, IDC_NF525, snf);
	DDX_Control(pDX, IDC_SMES4, smes4);
	DDX_Text(pDX, IDC_STITRE, titre);
	DDX_Text(pDX, IDC_SNMES1, nmes1);
	DDX_Text(pDX, IDC_SNMES2, nmes2);
	DDX_Text(pDX, IDC_SNMES3, nmes3);
	DDX_Text(pDX, IDC_SNMES4, nmes4);
	DDX_Text(pDX, IDC_SMES2, mes2);
	DDX_Text(pDX, IDC_SMES3, mes3);
	DDX_Text(pDX, IDC_SMES4, mes4);
	DDX_Text(pDX, IDC_SERIAL, serialtxt);
	DDX_Control(pDX, IDC_PRINT_IDENT, bca);
	DDX_Control(pDX, IDC_TEAMVIEWER, bteam);
}


BEGIN_MESSAGE_MAP(CIdent, CDialog)
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDOK, &CIdent::OnBnClickedOk)
	ON_WM_PAINT()
	ON_EN_CHANGE(IDC_SERIAL, &CIdent::OnEnChangeSerial)
	ON_STN_CLICKED(IDC_SNMES1, &CIdent::OnStnClickedSnmes1)
	ON_EN_SETFOCUS(IDC_SERIAL, &CIdent::OnEnSetfocusSerial)
	ON_BN_CLICKED(IDC_PRINT_IDENT, &CIdent::OnBnClickedPrintIdent)
	ON_WM_DRAWITEM()
	ON_WM_DESTROY()
	ON_EN_UPDATE(IDC_SERIAL, &CIdent::OnEnUpdateSerial)
	ON_BN_CLICKED(IDC_TEAMVIEWER, &CIdent::OnBnClickedTeamviewer)
END_MESSAGE_MAP()


// CIdent message handlers
BOOL CIdent::OnInitDialog()
{
	CString temp;
	CConcertoDlg* ppar=(CConcertoDlg*)GetParent();
	int i;
	int xs;
	int xn;
	int h;
	//CRect wrct;
	CRect rct[9];
	//GetDesktopWindow( )->GetWindowRect(&wrct);
	wlargeur=ppar->wlargeur;;
	whauteur=ppar->whauteur/4;
	color=0;
	CDialog::OnInitDialog();
	temp=ppar->txtm[64];//Identification de la billetterie
	titre=temp;
	nmes1="SN ";
	serialtxt=ppar->serial;
	temp=ppar->txtm[65];//Version logiciel
	nmes2=temp+" ";
	temp=ppar->txtc[141];//Certificat NF 525
	nmes3=temp+" ";
	temp=ppar->txtc[142];//Categorie NF 525
	nmes4=temp+" ";
	UpdateData(FALSE);
	serialtemp=serialtxt;
	/*dlgrefcolor=AfxGetApp()->GetProfileInt("Couleur","dlgrefcolor",0x00000000);
	txtdlgrefcolor=AfxGetApp()->GetProfileInt("Couleur","txtdlgrefcolor",0x00FF0000);
	butdlgrefcolor=AfxGetApp()->GetProfileInt("Couleur","butdlgrefcolor",0x00000000);
	txtbutdlgrefcolor=AfxGetApp()->GetProfileInt("Couleur","txtbutdlgrefcolor",0x00FF0000);*/
	coloren=AfxGetApp()->GetProfileInt("Param","Color",0);
	GetDlgItem(IDC_NF525)->ModifyStyle(0, SS_OWNERDRAW);
	staticfont.CreateFont(whauteur/8, //FONT DES CHAMPS ET LISTE
		0,//wlargeur/80,
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
	butdlgfont.CreateFont(whauteur/7, //FONT DES CHAMPS ET LISTE
		0,//wlargeur/80,
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
	sserial.SetFont(&staticfont);
	CDC* pdc=GetDC();
	CFont* pof;
	pof=pdc->SelectObject(&staticfont);
	pdc->DrawText(titre,&rct[0],DT_CALCRECT);
	pdc->DrawText(nmes1,&rct[1],DT_CALCRECT);
	pdc->DrawText(nmes2,&rct[2],DT_CALCRECT);
	pdc->DrawText(nmes3,&rct[3],DT_CALCRECT);
	pdc->DrawText(nmes4,&rct[4],DT_CALCRECT);
	pdc->DrawText("XXXXXXXXXXXX",&rct[5],DT_CALCRECT);
	pdc->DrawText(mes2,&rct[6],DT_CALCRECT);
	pdc->DrawText(mes3,&rct[7],DT_CALCRECT);
	pdc->DrawText(mes4,&rct[8],DT_CALCRECT);
	pof=pdc->SelectObject(pof);
	ReleaseDC(pdc);

	i=0;
	xn=rct[1].Width();
	xs=rct[5].Width();
	h=rct[1].Height();
	if(xn<rct[2].Width())
		xn=rct[2].Width();
	if(xn<rct[3].Width())
		xn=rct[3].Width();
	if(xn<rct[4].Width())
		xn=rct[4].Width();
	if(xs<rct[6].Width())
		xs=rct[6].Width();
	if(xs<+rct[7].Width())
		xs=rct[7].Width();
	if(xs<rct[8].Width())
		xs=rct[8].Width();
	wlargeur=38*wlargeur/40;
	largeurn=21*wlargeur/40;//xn+10;
	largeurs=17*wlargeur/40;//xs+20;
	hauteur=h;
	orgh=hauteur;
	/*if(wlargeur>=(3*rct[0].Width())/2)
	{
		wlargeur=(3*rct[0].Width())/2;
		orgt = rct[0].Width()/4;
		stitre.SetWindowPos(&wndTop,orgt,orgh,rct[0].Width(),hauteur,SWP_SHOWWINDOW   );
	}
	else*/
	{
		//orgt = (wlargeur-rct[0].Width())/2;
		orgt = (wlargeur)/2;
		stitre.SetWindowPos(&wndTop,0,orgh,wlargeur,hauteur,SWP_SHOWWINDOW   );
	}

	orgn=(wlargeur-(largeurn+largeurs))/2;
	orgs=(wlargeur-(largeurn+largeurs))/2+largeurn;

	orgh+=hauteur;
	orgh+=hauteur;
	snmes1.SetWindowPos(&wndTop,orgn,orgh,largeurn,hauteur,SWP_SHOWWINDOW   );
	sserial.SetWindowPos(&wndTop,orgs,orgh,largeurs,hauteur,SWP_SHOWWINDOW   );
	orgh+=hauteur;
	orgh+=hauteur;
	snmes2.SetWindowPos(&wndTop,orgn,orgh,largeurn,hauteur,SWP_SHOWWINDOW   );
	smes2.SetWindowPos(&wndTop,orgs,orgh,largeurs,hauteur,SWP_SHOWWINDOW   );
	if(ppar->infocert&&ticimp)
	{
		orgh+=hauteur;
		orgh+=hauteur;
		snmes3.SetWindowPos(&wndTop,orgn,orgh,largeurn,hauteur,SWP_SHOWWINDOW   );
		smes3.SetWindowPos(&wndTop,orgs,orgh,largeurs,hauteur,SWP_SHOWWINDOW   );
		orgh+=hauteur;
		orgh+=hauteur;
		snmes4.SetWindowPos(&wndTop,orgn,orgh,largeurn,hauteur,SWP_SHOWWINDOW   );
		smes4.SetWindowPos(&wndTop,orgs,orgh,largeurs,hauteur,SWP_SHOWWINDOW   );
		orgh+=hauteur;
		orgh+=hauteur;
		snf.SetWindowPos(&wndTop,(wlargeur-142)/2,orgh,142,130,SWP_SHOWWINDOW   );
		orgh+=130-hauteur;

	}
	orgh+=hauteur;
	orgh+=hauteur;
	color=0;
	SetWindowPos(&wndTop,0,0,wlargeur,orgh+(3*hauteur),SWP_HIDEWINDOW   );
	CenterWindow(0);
	ShowWindow(1);
	DrawButton();
	return TRUE;  // retourne TRUE, sauf si vous avez défini le focus sur un contrôle
}

void CIdent::DrawButton()
{
	CConcertoDlg* ppar=(CConcertoDlg*)GetParent();
	CString temp1;
	CRect rct;
	CRect rect;
	int bhauteur=hauteur*2;
	bl=wlargeur/4;
	rct.top=0;
	rct.left=0;
	rct.right=bl-10;
	rct.bottom=(bhauteur)-10;
	//BOUTON MANAGER

	orgt=(wlargeur/2)+(bl/2)+(bl/4);
	bok.SetWindowPos(&wndTop,orgt,orgh,bl,bhauteur,SWP_SHOWWINDOW   );
	orgt=(wlargeur/2)-(bl/2);

	bteam.SetWindowPos(&wndTop,orgt,orgh,bl,bhauteur,SWP_SHOWWINDOW   );
	bteam.SetWindowTextA("TeamViewer");

	orgt=bl/4;
	bca.SetWindowPos(&wndTop,orgt,orgh,bl,bhauteur,SWP_SHOWWINDOW);
	bca.SetWindowTextA(ppar->txtc[129]);//"Imprimer"
	
}

HBRUSH CIdent::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	int i=pWnd->GetDlgCtrlID();
	if(i==IDC_STITRE||i==IDC_SNMES1||i==IDC_SNMES2||i==IDC_SNMES3||i==IDC_SNMES4)
	{
		hbr=(HBRUSH)GetStockObject(WHITE_BRUSH);
		pDC->SetBkColor(0xFFFFFF);
		pDC->SetTextColor(0x0);
		pDC->SelectObject(&staticfont);
	}
	if(i==IDC_SMES2||i==IDC_SMES3||i==IDC_SMES4)
	{
		hbr=(HBRUSH)GetStockObject(BLACK_BRUSH);
		pDC->SetBkColor(0);
		pDC->SetTextColor(0x00FFFFFF);//txtdlgrefcolor);
		pDC->SelectObject(&staticfont);
	}
	return hbr;
}

BOOL CIdent::OnEraseBkgnd(CDC* pDC)
{
	CRect rct;
	pDC->SelectStockObject(WHITE_BRUSH);
	GetWindowRect(&rct);
	ScreenToClient(&rct);
	pDC->Rectangle(&rct);

	return 0;//CDialog::OnEraseBkgnd(pDC);
}

void CIdent::OnStnClickedSnmes1()
{
}

void CIdent::OnBnClickedOk()
{
	CConcertoDlg* par=(CConcertoDlg* )GetParent();
	if(serialtemp!=serialtxt&&par->fadmin==1)
	{
		par->WriteConfigString("License","Serial",serialtemp);
		par->serial=serialtemp;
	}
	OnOK();
}

void CIdent::OnPaint()
{
	CPaintDC dc(this); // device context for painting

}
LRESULT CIdent::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	int i;
	CWnd* pw;
	HBRUSH hbr;
	if(message==WM_CTLCOLOREDIT)
	{
		CDC* pDC;		
		pw=CWnd::FromHandle((HWND)lParam);
		i=pw->GetDlgCtrlID();
		if(i==IDC_SERIAL)
		{
			pDC=CDC::FromHandle((HDC)wParam);
			ticketbrush.DeleteObject();
			ticketbrush.CreateSolidBrush(0);
			hbr=(HBRUSH)ticketbrush;
			pDC->SetBkColor(0);
			pDC->SetTextColor(0x00FFFFFF);
			return (LRESULT)hbr;
		}
	}
	return CDialog::DefWindowProc(message, wParam, lParam);
}


void CIdent::OnEnChangeSerial()
{
	CConcertoDlg* par=(CConcertoDlg* )GetParent();
	if(par->fadmin==1)
		sserial.GetWindowTextA(serialtemp);
	else
		sserial.SetWindowTextA(par->serial);
}

void CIdent::OnEnSetfocusSerial()
{
	CConcertoDlg* par=(CConcertoDlg* )GetParent();
	if(par->fadmin==1)
	{
		SetFocus();
	}
}

void CIdent::OnBnClickedPrintIdent()
{
	CConcertoDlg* par=(CConcertoDlg* )GetParent();
	if(serialtemp!=serialtxt&&par->fadmin==1)
	{
		par->WriteConfigString("License","Serial",serialtemp);
		par->serial=serialtemp;
	}
	par->PRMODE=1;
}

void CIdent::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CString temp;
	CString temp1;
	CDC* pdc=CDC::FromHandle(lpDrawItemStruct->hDC);
	CRect rct;
	CConcertoDlg* par=(CConcertoDlg* )GetParent();
	if(nIDCtl==IDC_TEAMVIEWER)
	{
		Graphics gr (pdc->m_hDC);
		rct=lpDrawItemStruct->rcItem;
		RectF rctf(0,0,(REAL)rct.Width(),(REAL)rct.Height());
		pdc->SelectObject(&par->geostat);
		pdc-> SetBkMode(TRANSPARENT);
		pdc->SetTextColor(0xFFFFFF);
		if(!(lpDrawItemStruct->itemState & ODS_SELECTED))
		{
			gr.DrawImage(par->pbnresbar,rctf);
		}
		else
		{
			gr.DrawImage(par->pbsresbar,rctf);
		}
		pdc->DrawText("TeamViewer",-1,&lpDrawItemStruct->rcItem,DT_CENTER|DT_SINGLELINE|DT_VCENTER );
	}
	if(nIDCtl==IDC_PRINT_IDENT)
	{
		Graphics gr (pdc->m_hDC);
		rct=lpDrawItemStruct->rcItem;
		RectF rctf(0,0,(REAL)rct.Width(),(REAL)rct.Height());
		pdc->SelectObject(&par->geostat);
		pdc-> SetBkMode(TRANSPARENT);
		pdc->SetTextColor(0xFFFFFF);
		if(!(lpDrawItemStruct->itemState & ODS_SELECTED))
		{
			gr.DrawImage(par->pbnresbar,rctf);
		}
		else
		{
			gr.DrawImage(par->pbsresbar,rctf);
		}
		pdc->DrawText(par->txtc[129],-1,&lpDrawItemStruct->rcItem,DT_CENTER|DT_SINGLELINE|DT_VCENTER );//"Imprimer"
	}
	if(nIDCtl==IDOK)
	{
		Graphics gr (pdc->m_hDC);
		rct=lpDrawItemStruct->rcItem;
		RectF rctf(0,0,(REAL)rct.Width(),(REAL)rct.Height());
		pdc->SelectObject(&par->geostat);
		pdc-> SetBkMode(TRANSPARENT);
		pdc->SetTextColor(0xFFFFFF);
		if(!(lpDrawItemStruct->itemState & ODS_SELECTED))
		{
			gr.DrawImage(par->pbnresbar,rctf);
		}
		else
		{
			gr.DrawImage(par->pbsresbar,rctf);
		}
		pdc->DrawText(par->txtc[130],-1,&lpDrawItemStruct->rcItem,DT_CENTER|DT_SINGLELINE|DT_VCENTER );//"Quitter"
	}
	if(nIDCtl==IDC_NF525&&ticimp)
	{
		Graphics gr (pdc->m_hDC);
		rct=lpDrawItemStruct->rcItem;
		RectF rctf(0,0,(REAL)rct.Width(),(REAL)rct.Height());
		gr.DrawImage(par->pnf525,rctf);
	}


	//CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);

}

void CIdent::OnDestroy()
{
	CConcertoDlg* par=(CConcertoDlg* )GetParent();
	CDialog::OnDestroy();
	par->pwidt=NULL;
}

void CIdent::OnEnUpdateSerial()
{
}

void CIdent::OnBnClickedTeamviewer()
{
	CWnd* pwnd;
	CConcertoDlg* par=(CConcertoDlg* )GetParent();
	if((pwnd=FindWindow(NULL,"TeamViewer"))!=NULL)
	{
		par->SetWindowPos(&wndBottom,0,0,0,0,SWP_NOSIZE|SWP_NOMOVE);
		//SetWindowPos(&wndBottom,0,0,0,0,SWP_NOSIZE|SWP_NOMOVE);
		//pwnd->BringWindowToTop();
		pwnd->SetWindowPos(&wndTopMost,0,0,0,0,SWP_NOSIZE|SWP_NOMOVE|SWP_SHOWWINDOW);
	}
}

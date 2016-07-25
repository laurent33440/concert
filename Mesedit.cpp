// Message.cpp : implementation file
//

#include "stdafx.h"
#include "Concerto.h"
#include "Mesedit.h"
#include "ConcertoDlg.h"


// CMesedit dialog

IMPLEMENT_DYNAMIC(CMesedit, CDialog)

CMesedit::CMesedit(CWnd* pParent /*=NULL*/)
	: CDialog(CMesedit::IDD, pParent)
	, mes1(_T(""))
{

}

CMesedit::~CMesedit()
{
}

void CMesedit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SMES1, smes1);
	DDX_Text(pDX, IDC_SMES1, mes1);
	DDX_Control(pDX, IDC_CHECK1, ccolor);
	DDX_Control(pDX, IDOK, bok);
	DDX_Control(pDX, IDC_ANNULER, bca);
	DDX_Control(pDX, IDC_ANNULER, bca);
	DDX_Control(pDX, IDC_MESEDIT, emes);
}


BEGIN_MESSAGE_MAP(CMesedit, CDialog)
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_STN_CLICKED(IDC_SMES1, &CMesedit::OnStnClickedSmes1)
	ON_BN_CLICKED(IDC_CHECK1, &CMesedit::OnBnClickedCheck1)
	ON_BN_CLICKED(IDOK, &CMesedit::OnBnClickedOk)
	ON_BN_CLICKED(IDC_ANNULER, &CMesedit::OnBnClickedCancel)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CMesedit message handlers
BOOL CMesedit::OnInitDialog()
{
	CConcertoDlg* ppt= (CConcertoDlg*)GetParent();
	CString temp;
	int i;
	int x;
	CRect wrct;
	CRect rct[3];
	GetDesktopWindow( )->GetWindowRect(&wrct);
	wlargeur=wrct.Width();
	whauteur=wrct.Height()/4;
	color=0;
	CDialog::OnInitDialog();
	dlgrefcolor=AfxGetApp()->GetProfileInt("Couleur","dlgrefcolor",0x00000000);
	txtdlgrefcolor=AfxGetApp()->GetProfileInt("Couleur","txtdlgrefcolor",0x00FF0000);
	butdlgrefcolor=AfxGetApp()->GetProfileInt("Couleur","butdlgrefcolor",0x00000000);
	txtbutdlgrefcolor=AfxGetApp()->GetProfileInt("Couleur","txtbutdlgrefcolor",0x00FF0000);
	coloren=AfxGetApp()->GetProfileInt("Param","Color",0);
	SetWindowPos(&wndTop,0,0,wlargeur,whauteur,SWP_SHOWWINDOW   );
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
	CDC* pdc=GetDC();
	CFont* pof;
	pof=pdc->SelectObject(&staticfont);
	pdc->DrawText(mes1,&rct[0],DT_CALCRECT);
	pof=pdc->SelectObject(pof);
	ReleaseDC(pdc);
	i=0;
	x=wlargeur/2;


	largeur=edtlargeur;
	hauteur=rct[0].Height();
	//SetWindowText(titre);
	bl=largeur/2;
	orgh=hauteur;
	wlargeur=edtlargeur+2*(edtlargeur/5);
	org = largeur/5;
	smes1.SetWindowPos(&wndTop,org,orgh,largeur,hauteur,SWP_SHOWWINDOW   );
	color=0;
	SetWindowPos(&wndTop,0,0,wlargeur,orgh+(7*hauteur),SWP_HIDEWINDOW   );
	CenterWindow(0);
	ShowWindow(1);
	ccolor.SetWindowPos(&wndTop,wlargeur/2,orgh+5*hauteur,bl/4,hauteur,SWP_HIDEWINDOW   );
	if(coloren)
		ccolor.ShowWindow(0);
	else
		ccolor.ShowWindow(0);
	DrawButton();
	ppt->kid=IDC_MESEDIT;
	if(ppt->Klance())
		return TRUE;  // retourne TRUE, sauf si vous avez défini le focus sur un contrôle
	else
		OnCancel();
	return TRUE;  // retourne TRUE, sauf si vous avez défini le focus sur un contrôle
}

void CMesedit::DrawButton()
{
	CDC* pdc=GetDC();
	CDC m_Cdc;
	m_Cdc.CreateCompatibleDC(NULL);
	CBitmap* tempbitmap;
	CRect rct;
	CFont* poldfont=m_Cdc.SelectObject(&butdlgfont);
	CRect rect;
	CConcertoDlg* ppt= (CConcertoDlg*)GetParent();

	int bhauteur=hauteur+hauteur/2;
	rct.top=0;
	rct.left=0;
	rct.right=bl-10;
	rct.bottom=(bhauteur)-10;

	org=wlargeur-2*bl;
	org=org/3;

	bok.SetWindowPos(&wndTop,org,orgh+4*hauteur,bl,bhauteur,SWP_SHOWWINDOW   );
	bmpok.DeleteObject();
	bmpok.CreateCompatibleBitmap(pdc,rct.Width(),rct.Height());
	tempbitmap=m_Cdc.SelectObject(&bmpok);
	m_Cdc.FillSolidRect(&rct,butdlgrefcolor);
	m_Cdc.SetTextColor(txtbutdlgrefcolor);
	if(mode==0)
		m_Cdc.DrawText("Valider",-1,&rct,DT_CENTER|DT_SINGLELINE|DT_VCENTER );
	m_Cdc.SelectObject(tempbitmap);
	bok.SetBitmap(( HBITMAP)bmpok);
	bca.SetWindowPos(&wndTop,2*org+bl,orgh+4*hauteur,bl,bhauteur,SWP_SHOWWINDOW);
	bmpca.DeleteObject();
	bmpca.CreateCompatibleBitmap(pdc,rct.Width(),rct.Height());
	tempbitmap=m_Cdc.SelectObject(&bmpca);
	m_Cdc.FillSolidRect(&rct,butdlgrefcolor);
	m_Cdc.SetTextColor(txtbutdlgrefcolor);
	m_Cdc.DrawText("Annuler",-1,&rct,DT_CENTER|DT_SINGLELINE|DT_VCENTER );
	m_Cdc.SelectObject(tempbitmap);
	bca.SetBitmap(( HBITMAP)bmpca);
	m_Cdc.SelectObject(poldfont);
	ReleaseDC(pdc);
	emes.SetWindowPos(&wndTop,org,orgh+2*hauteur,edtlargeur,hauteur+hauteur/2,SWP_SHOWWINDOW   );
	emes.SetFont(&ppt->buttonfont,1);
}

HBRUSH CMesedit::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	if(pWnd->GetDlgCtrlID()==IDC_SMES1)
	{
		ticketbrush.DeleteObject();
		ticketbrush.CreateSolidBrush(dlgrefcolor);
		hbr=(HBRUSH)ticketbrush;
		pDC->SetBkColor(dlgrefcolor);
		pDC->SetTextColor(txtdlgrefcolor);
		pDC->SelectObject(&staticfont);
	}
	if(pWnd->GetDlgCtrlID()==IDC_CHECK1)
	{
		ticketbrush.DeleteObject();
		ticketbrush.CreateSolidBrush(dlgrefcolor);
		hbr=(HBRUSH)ticketbrush;
		pDC->SetBkColor(dlgrefcolor);
		pDC->SetTextColor(txtdlgrefcolor);
		pDC->SelectObject(&staticfont);
	}

	return hbr;
}

BOOL CMesedit::OnEraseBkgnd(CDC* pDC)
{
	CRect rct;
	CBrush* ptbr;
	backrefcolorbr.DeleteObject();
	backrefcolorbr.CreateSolidBrush(dlgrefcolor);
	ptbr=pDC->SelectObject(&backrefcolorbr);
	GetWindowRect(&rct);
	ScreenToClient(&rct);
	pDC->Rectangle(&rct);
	pDC->SelectObject(ptbr);
	return 0;//CDialog::OnEraseBkgnd(pDC);
}

void CMesedit::OnStnClickedSmes1()
{
	if(color)
	{
		CColorDialog box(dlgrefcolor,CC_FULLOPEN ,NULL) ;//|CC_ENABLETEMPLATE
		box.m_cc.lpTemplateName=("Couleur du fond");
		if(box.DoModal()==IDOK)
			dlgrefcolor=box.GetColor( );
		CColorDialog boxtxt(txtdlgrefcolor,CC_FULLOPEN,NULL) ;//|CC_ENABLETEMPLATE
		boxtxt.m_cc.lpTemplateName=("Couleur du texte");
		if(boxtxt.DoModal()==IDOK)
			txtdlgrefcolor=boxtxt.GetColor( );
		RedrawWindow(0,0,1|256|4);
		AfxGetApp()->WriteProfileInt("Couleur","dlgrefcolor",dlgrefcolor);
		AfxGetApp()->WriteProfileInt("Couleur","txtdlgrefcolor",txtdlgrefcolor);
	}
}

void CMesedit::OnBnClickedCheck1()
{
	if(ccolor.GetCheck()==BST_CHECKED)
	{
		color=1;
	}
	else
	{
		color=0;
	}
}

void CMesedit::OnBnClickedOk()
{
	if(color)
	{
		CColorDialog box(butdlgrefcolor,CC_FULLOPEN ,NULL) ;//|CC_ENABLETEMPLATE
		box.m_cc.lpTemplateName=("Couleur du fond");
		if(box.DoModal()==IDOK)
			butdlgrefcolor=box.GetColor( );
		CColorDialog boxtxt(txtbutdlgrefcolor,CC_FULLOPEN,NULL) ;//|CC_ENABLETEMPLATE
		boxtxt.m_cc.lpTemplateName=("Couleur du texte");
		if(boxtxt.DoModal()==IDOK)
			txtbutdlgrefcolor=boxtxt.GetColor( );
		bok.RedrawWindow(0,0,1|256|4);
		bca.RedrawWindow(0,0,1|256|4);
		AfxGetApp()->WriteProfileInt("Couleur","butdlgrefcolor",butdlgrefcolor);
		AfxGetApp()->WriteProfileInt("Couleur","txtbutdlgrefcolor",txtbutdlgrefcolor);
	}
	else
		emes.GetWindowText(evtxt);
	OnOK();
}

void CMesedit::OnBnClickedCancel()
{
	evtxt="";
	OnCancel();
}

void CMesedit::OnPaint()
{
	CPaintDC dc(this); // device context for painting
}
LRESULT CMesedit::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	int i;
		CWnd* pw;
		HBRUSH hbr;
		CConcertoDlg* ppt= (CConcertoDlg*)GetParent();
	if(message==WM_CTLCOLOREDIT )
	{
		CDC* pDC;
		
		pw=CWnd::FromHandle((HWND)lParam);
		i=pw->GetDlgCtrlID();
		if(i==IDC_MESEDIT)
		{
			pDC=CDC::FromHandle((HDC)wParam);
			ticketbrush.DeleteObject();
			ticketbrush.CreateSolidBrush(ppt->sconfigrefcolor);
			hbr=(HBRUSH)ticketbrush;
			pDC->SetBkColor(ppt->sconfigrefcolor);
			pDC->SetTextColor(ppt->txtsconfigrefcolor);
			return (LRESULT)hbr;
		}
	}

	return CDialog::DefWindowProc(message, wParam, lParam);
}

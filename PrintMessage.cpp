// Message.cpp : implementation file
//

#include "stdafx.h"
#include "ConcertoDlg.h"
#include "Concerto.h"
#include "PrintMessage.h"


// CPrintMessage dialog

IMPLEMENT_DYNAMIC(CPrintMessage, CDialog)

CPrintMessage::CPrintMessage(CWnd* pParent /*=NULL*/)
	: CDialog(CPrintMessage::IDD, pParent)
	, mes1(_T(""))
	, mes2(_T(""))
	, mes3(_T(""))
{

}

CPrintMessage::~CPrintMessage()
{
}

void CPrintMessage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SMES1, smes1);
	DDX_Control(pDX, IDC_SMES2, smes2);
	DDX_Text(pDX, IDC_SMES1, mes1);
	DDX_Text(pDX, IDC_SMES2, mes2);
	DDX_Control(pDX, IDC_CHECK1, ccolor);
	DDX_Control(pDX, IDOK, bok);
	DDX_Control(pDX, IDC_ANNULER, bca);
	DDX_Control(pDX, IDC_SMES3, smes3);
	DDX_Text(pDX, IDC_SMES3, mes3);
}


BEGIN_MESSAGE_MAP(CPrintMessage, CDialog)
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_STN_CLICKED(IDC_SMES1, &CPrintMessage::OnStnClickedSmes1)
	ON_BN_CLICKED(IDC_CHECK1, &CPrintMessage::OnBnClickedCheck1)
	ON_BN_CLICKED(IDOK, &CPrintMessage::OnBnClickedOk)
	ON_BN_CLICKED(IDC_ANNULER, &CPrintMessage::OnBnClickedCancel)
	ON_WM_PAINT()
	ON_WM_DRAWITEM()
END_MESSAGE_MAP()


// CPrintMessage message handlers
BOOL CPrintMessage::OnInitDialog()
{
	CConcertoDlg* par=(CConcertoDlg*)GetParent();
	if(par->noprint)
		par->sp.CloseDialog();
	CString temp;
	ShowWindow(0);
	int i;
	int x;
	largeur;
	hauteur;
	//CRect wrct;
	CRect rct[3];
	//GetDesktopWindow( )->GetWindowRect(&wrct);
	wlargeur=par->wlargeur;;
	whauteur=par->whauteur/4;
	color=0;
	CDialog::OnInitDialog();
	dlgrefcolor=0xFFFFFF;
	txtdlgrefcolor=0;
	butdlgrefcolor=0xFFFFFF;
	txtbutdlgrefcolor=0;
	coloren=0;
	staticfont.CreateFont(whauteur/12, //FONT DES CHAMPS ET LISTE
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
		PROOF_QUALITY,
		DEFAULT_PITCH|FF_DONTCARE,
		"Geosanlight");
	butdlgfont.CreateFont(whauteur/10, //FONT DES CHAMPS ET LISTE
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
		PROOF_QUALITY,
		DEFAULT_PITCH|FF_DONTCARE,
		"Geosanlight");
	CDC* pdc=GetDC();
	CFont* pof;
	pof=pdc->SelectObject(&staticfont);
	pdc->DrawText(mes1,&rct[0],DT_CALCRECT);
	pdc->DrawText(mes2,&rct[1],DT_CALCRECT);
	pdc->DrawText(mes3,&rct[2],DT_CALCRECT);
	pof=pdc->SelectObject(pof);
	ReleaseDC(pdc);
	i=0;
	x=0;
	SetWindowPos(&wndTop,0,0,wlargeur,whauteur,SWP_HIDEWINDOW   );

	if(x<rct[0].Width())
		x=rct[0].Width();

	if(x<rct[1].Width())
	{
		i++;
		x=rct[1].Width();
	}
	if(x<rct[2].Width())
	{
		i++;
		x=rct[2].Width();
	}

	largeur=rct[0].Width()+10;
	hauteur=rct[0].Height();
	SetWindowText(titre);
	bl=largeur/3;
	orgh=hauteur;
	if(wlargeur>=(3*largeur)/2)
	{
		wlargeur=(3*largeur)/2;
		org = largeur/4;
	}
	else
		org = (wlargeur-largeur)/2;
	smes1.SetWindowPos(&wndTop,org,orgh,largeur,hauteur,SWP_SHOWWINDOW   );
	if(mes2!="")
	{
		orgh+=hauteur;
		orgh+=hauteur;
		smes2.SetWindowPos(&wndTop,org,orgh,largeur,hauteur,SWP_SHOWWINDOW   );
		smes3.SetWindowPos(&wndTop,org,orgh,largeur,hauteur,SWP_SHOWWINDOW   );
	}
	orgh+=hauteur;
	orgh+=hauteur;
	color=0;
	ShowWindow(0);
	SetWindowPos(&wndTop,0,0,wlargeur,orgh+(3*hauteur),SWP_HIDEWINDOW   );
	CenterWindow(0);
	ShowWindow(1);
	ccolor.SetWindowPos(&wndTop,wlargeur/2,orgh+hauteur,bl/4,hauteur,SWP_HIDEWINDOW   );
	if(coloren)
		ccolor.ShowWindow(0);
	else
		ccolor.ShowWindow(0);
	DrawButton();
	to=0;
	nbyte=1000;
//************************* DEBUT changement droit d'accès au printer *******************
	if(!par->noprint)
	{
		GetDefaultPrinter(prtname.GetBuffer(1000),&nbyte);
		prtname.ReleaseBuffer(nbyte);
		OpenPrinter(  prtname.GetBuffer(),&hPrinter,NULL);
		cbNeeded=sizeof(PRINTER_INFO_2);
		GetPrinter(hPrinter,2,&Printer[0],10000,&cbNeeded);
		pd.pDatatype=((PRINTER_INFO_2*)&Printer[0])->pDatatype;
		pd.pDevMode=((PRINTER_INFO_2*)&Printer[0])->pDevMode;
		pd.DesiredAccess=PRINTER_ALL_ACCESS;
		ClosePrinter(hPrinter);
	}
	par->PostMessageA(WM_USER+30,0,0);
//************************* FIN changement droit d'accès au printer *******************

	/*OpenPrinter(prtname.GetBuffer(), &hPrinter,&pd);
	if(!SetPrinter(hPrinter,0,0,PRINTER_CONTROL_PAUSE))
		MessageBox("Erreur de pause du spooler");
	ClosePrinter(hPrinter);*/
	//SetTimer(1,300,NULL);

	return TRUE;  // retourne TRUE, sauf si vous avez défini le focus sur un contrôle
}

void CPrintMessage::DrawButton()
{
	int bhauteur=hauteur*2;
	if(mode==0)
		bok.SetWindowPos(&wndTop,org,orgh,bl,bhauteur,SWP_SHOWWINDOW   );
	else
		bok.SetWindowPos(&wndTop,org+bl,orgh,bl,bhauteur,SWP_SHOWWINDOW   );
	if(mode==0)
	{

		bca.SetWindowPos(&wndTop,org+(2*bl),orgh,bl,bhauteur,SWP_SHOWWINDOW);
	}
	
}

HBRUSH CPrintMessage::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
	if(pWnd->GetDlgCtrlID()==IDC_SMES2)
	{
		ticketbrush.DeleteObject();
		ticketbrush.CreateSolidBrush(dlgrefcolor);
		hbr=(HBRUSH)ticketbrush;
		pDC->SetBkColor(dlgrefcolor);
		pDC->SetTextColor(txtdlgrefcolor);
		pDC->SelectObject(&staticfont);
	}
	if(pWnd->GetDlgCtrlID()==IDC_SMES3)
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

BOOL CPrintMessage::OnEraseBkgnd(CDC* pDC)
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

void CPrintMessage::OnStnClickedSmes1()
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
		/*AfxGetApp()->WriteProfileInt("Couleur","dlgrefcolor",dlgrefcolor);
		AfxGetApp()->WriteProfileInt("Couleur","txtdlgrefcolor",txtdlgrefcolor);*/
	}
}

void CPrintMessage::OnBnClickedCheck1()
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

void CPrintMessage::OnBnClickedOk()
{
	int wdg;
	CString temp;
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
		/*AfxGetApp()->WriteProfileInt("Couleur","butdlgrefcolor",butdlgrefcolor);
		AfxGetApp()->WriteProfileInt("Couleur","txtbutdlgrefcolor",txtbutdlgrefcolor);*/
	}
	else
	{
		smes1.SetWindowTextA("Annulation en cours");
		smes2.SetWindowTextA("Veuillez patienter ...");
		wdg=0;
		InterlockedExchange(&((CConcertoDlg*)GetParent())->QUIT,1);
		Sleep(300);
		smes2.SetWindowTextA("Annulation impression ...");
		OnOK();
	}
}

void CPrintMessage::OnBnClickedCancel()
{
	OnCancel();
}

void CPrintMessage::OnPaint()
{
	CPaintDC dc(this); // device context for painting
}

void CPrintMessage::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CConcertoDlg* par=(CConcertoDlg* )GetParent();
	CDC* pdc=CDC::FromHandle(lpDrawItemStruct->hDC);
	CRect rct;
	int i=lpDrawItemStruct->CtlID-IDC_0;//
	if(lpDrawItemStruct->CtlType==ODT_BUTTON)
	{
		//if(wsel==1)
		{
			pdc->SetBkMode(TRANSPARENT);
			pdc->FillSolidRect(&lpDrawItemStruct->rcItem,0xFFFFFF);
		}
		pdc->SetBkMode(TRANSPARENT);//(col);
		rct=lpDrawItemStruct->rcItem;
		RectF rctf(0,0,(REAL)rct.Width(),(REAL)rct.Height());

		pdc->SetTextColor(0);
		pdc->SelectObject(&butdlgfont);
		// **********  DESSIN du bouton
		Graphics gr (pdc->m_hDC);
		if(!(lpDrawItemStruct->itemState & ODS_SELECTED))
			gr.DrawImage(par->pbnartbo,rctf);
		else
			gr.DrawImage(par->pbsartbo,rctf);
		if(nIDCtl==IDOK)
		{
			if(mode==0)
				pdc->DrawText("OUI",-1,&rct,DT_CENTER|DT_SINGLELINE|DT_VCENTER );
			else
				pdc->DrawText("OK",-1,&rct,DT_CENTER|DT_SINGLELINE|DT_VCENTER );
		}
		if(nIDCtl==IDC_ANNULER)
		{
			if(mode==0)
				pdc->DrawText("NON",-1,&rct,DT_CENTER|DT_SINGLELINE|DT_VCENTER );
		}
	}
}

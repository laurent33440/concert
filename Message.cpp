// Message.cpp : implementation file
//

#include "stdafx.h"
#include "Concerto.h"
#include "ConcertoDlg.h"
#include "Message.h"
#include "Combo.h"


// CMessage dialog

IMPLEMENT_DYNAMIC(CMessage, CDialog)

CMessage::CMessage(CWnd* pParent /*=NULL*/)
	: CDialog(CMessage::IDD, pParent)
	, mes1(_T(""))
	, mes2(_T(""))
{

}

CMessage::~CMessage()
{
}
void CMessage::OnSetFont(CFont* pFont)
{
}

void CMessage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SMES1, smes1);
	DDX_Control(pDX, IDC_SMES2, smes2);
	DDX_Control(pDX, IDOK, bok);
	DDX_Control(pDX, IDC_ANNULER, bca);
	DDX_Control(pDX, IDC_SMES3, smes3);
	DDX_Control(pDX, IDC_PSEND, psend);
	DDX_Control(pDX, IDC_CAL, cal);
	DDX_Control(pDX, IDC_HORAIRE, hor);
	DDX_Control(pDX, IDC_REPONSE, erep);
	DDX_Control(pDX, IDC_AUTEUR, eaut);
	DDX_Control(pDX, IDC_MOTIF, srep);
}


BEGIN_MESSAGE_MAP(CMessage, CDialog)
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDOK, &CMessage::OnBnClickedOk)
	ON_BN_CLICKED(IDC_ANNULER, &CMessage::OnBnClickedCancel)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_NOTIFY(MCN_SELECT, IDC_CAL, &CMessage::OnMcnSelectMonthcalendar1)
	ON_NOTIFY(MCN_SELCHANGE, IDC_CAL, &CMessage::OnMcnSelchangeMonthcalendar1)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_HORAIRE, &CMessage::OnDtnDatetimechangeHoraire)
	ON_WM_DRAWITEM()
	ON_EN_CHANGE(IDC_REPONSE, &CMessage::OnEnChangeReponse)
	ON_EN_CHANGE(IDC_AUTEUR, &CMessage::OnEnChangeAuteur)
	ON_EN_SETFOCUS(IDC_AUTEUR, &CMessage::OnEnSetfocusAuteur)
	ON_EN_SETFOCUS(IDC_REPONSE, &CMessage::OnEnSetfocusReponse)
	ON_WM_SETCURSOR()
	ON_STN_CLICKED(IDC_MOTIF, &CMessage::OnStnClickedMotif)
END_MESSAGE_MAP()


// CMessage message handlers
BOOL CMessage::OnInitDialog()
{
	CConcertoDlg* par=(CConcertoDlg* )GetParent();
	CString temp;
	CString temph;
	CString tempw;
	int i;
	int idx;
	int x;
	int orgcaly;
	int hcal;
	largeur;
	hauteur;
	//CRect wrct;
	CRect calrect;
	CRect horrect;
	CRect rct[3];
	//GetDesktopWindow( )->GetWindowRect(&wrct);
	wlargeur=par->wlargeur;;
	whauteur=par->whauteur/4;
	color=0;
	int hx;
	int hy;
	int hh;
	int ho;
	CDialog::OnInitDialog();
	pcombo=NULL;
	dlgrefcolor=0xFFFFFF;//AfxGetApp()->GetProfileInt("Couleur","dlgrefcolor",0x00000000);
	txtdlgrefcolor=0;//AfxGetApp()->GetProfileInt("Couleur","txtdlgrefcolor",0x00FF0000);
	butdlgrefcolor=0xFFFFFF;//AfxGetApp()->GetProfileInt("Couleur","butdlgrefcolor",0x00000000);
	txtbutdlgrefcolor=0;AfxGetApp()->GetProfileInt("Couleur","txtbutdlgrefcolor",0x00FF0000);/**/
	coloren=0;//AfxGetApp()->GetProfileInt("Param","Color",0);
	staticfont.CreateFont(whauteur/10, //FONT DES CHAMPS ET LISTE
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
	butdlgfont.CreateFont(whauteur/8, //FONT DES CHAMPS ET LISTE
		wlargeur/80,
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
	heurefont.CreateFont(whauteur/6, 
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
	x=wlargeur/2;
	if(rct[0].Width()>x)
		x=rct[0].Width();

	if(rct[1].Width()>x)
	{
		x=rct[1].Width();
	}
	if(rct[2].Width()>x)
	{
		x=rct[2].Width();
	}/**/
	if(x<7*wlargeur/8)
		wlargeur=7*x/6;
	else	
		wlargeur=9*wlargeur/10;

	cal.SendMessage( WM_SETFONT, (WPARAM) butdlgfont.GetSafeHandle(), MAKELONG(1, 0));//inactif
	cal.GetMinReqRect(&calrect);

	hauteur=rct[0].Height();
	SetWindowText(titre);
	orgh=hauteur;
	largeur=6*wlargeur/7;
	bl=largeur/3;
	org = (wlargeur-largeur)/2;
	smes1.SetWindowPos(&wndTop,org,orgh,largeur,hauteur,SWP_SHOWWINDOW   );
	smes1.SetWindowTextA(mes1);
	orgcaly=orgh+4*hauteur;
	hcal=orgcaly+calrect.Height()+hauteur;
	if(mode<4||mode>5)
	{
		if(mes2!="")
		{
			orgh+=hauteur;
			orgh+=hauteur;
			smes2.SetWindowPos(&wndTop,org,orgh,largeur,hauteur,SWP_SHOWWINDOW   );
			smes2.SetWindowTextA(mes2);
		}
		if(mes3!="")
		{
			orgh+=hauteur;
			orgh+=hauteur;
			smes3.SetWindowPos(&wndTop,org,orgh,largeur,hauteur,SWP_SHOWWINDOW   );
			smes3.SetWindowTextA(mes3);
		}
		if( mode==3)
		{
			orgh+=hauteur;
			orgh+=hauteur;
			psend.SetWindowPos(&wndTop,org,orgh,largeur,hauteur,SWP_SHOWWINDOW   );
			i=idx=0;
			while((idx=buf.Find("\r\n",idx))!=-1)
			{
				i++;
				idx+=2;
			}
			plen=i;
			psend.SetStep(1);
			psend.SetRange(0,plen);
		}
		if( mode==6)
		{
			orgh+=hauteur;
			orgh+=hauteur;
			psend.SetWindowPos(&wndTop,org,orgh,largeur,hauteur,SWP_SHOWWINDOW   );
			i=idx=0;
			plen=i;
			psend.SetStep(1);
			psend.SetRange(0,((CConcertoDlg*)psource)->dirlist.GetCount());
		}
		if( mode==8)
		{
			orgh+=hauteur;
			orgh+=hauteur;
			erep.SetWindowPos(&wndTop,org,orgh,largeur,hauteur,SWP_SHOWWINDOW   );
			orgh+=hauteur;
			orgh+=hauteur;
			eaut.SetWindowPos(&wndTop,org,orgh,largeur,hauteur,SWP_SHOWWINDOW   );
			erep.SetFont(&staticfont);
			eaut.SetFont(&staticfont);
		}
		if( mode==9)
		{
			orgh+=hauteur;
			orgh+=hauteur;
			srep.SetWindowPos(&wndTop,org,orgh,largeur,hauteur,SWP_SHOWWINDOW   );
			srep.SetWindowTextA("");
		}
		cal.SetWindowPos(&wndTop,wlargeur/8,orgcaly,(6*wlargeur)/8,hcal,SWP_HIDEWINDOW   );
		if(mode!=10)
		orgh+=hauteur;
		orgh+=hauteur;
	}
	else
	{
		int orgcalx=(wlargeur-calrect.Width())/2;
		orgh+=hauteur;
		orgh+=hauteur;
		smes2.SetWindowPos(&wndTop,org,orgh,largeur,hauteur,SWP_SHOWWINDOW   );
		smes2.SetWindowTextA(mes2);
		cal.SetWindowPos(&wndTop,orgcalx,orgcaly,calrect.Width(),calrect.Height(),SWP_SHOWWINDOW   );
		orgh+=hcal;//+hauteur;
		if(mode==5)
		{
			CTime htime=CTime::GetCurrentTime();
			hor.SetFont(&heurefont,1);
			hor.SetTime(&htime);
			temp=htime.Format("%H:%M:%S  ");
			CDC* phdc =GetDC();
			CFont* pof=phdc->SelectObject(&heurefont);
			hh=phdc->DrawText(temp,&horrect,DT_CALCRECT);
			phdc->SelectObject(pof);
			ReleaseDC(phdc);
			tempw.Format("w=%u",horrect.Width());
			temph.Format("h=%u",hh);
			hx=(wlargeur-(horrect.Width()+(horrect.Width()/10)))/2;
			ho=orgcaly+calrect.Height();
			hy=ho+((orgh-ho-hh)/2);
			hor.SetWindowPos(&wndTop,hx,hy,horrect.Width()+(horrect.Width()/10),hh+(hh/5),SWP_SHOWWINDOW);
			cal.GetCurSel(seldate);
			hor.GetTime(selhor);
			date=seldate.Format("%d/%m/%Y")+selhor.Format(" à %H:%M");
			smes2.SetWindowTextA(date);	
		}
	}
	color=0;
	SetWindowPos(&wndTop,0,0,wlargeur,orgh+(3*hauteur),SWP_HIDEWINDOW   );
	CenterWindow(GetDesktopWindow( ));
	ShowWindow(1);
	DrawButton();
	if(mode==3)
	{
		bok.ShowWindow(0);
		idxstart=idxstop=0;
		SetTimer(1,20,NULL);
	}
	if(mode==6)
	{
		bok.ShowWindow(0);
		SetTimer(2,50,NULL);
	}
	if (mode==8)
	{
		erep.SetFocus();
		par->kid= erep.GetDlgCtrlID();
		par->PostMessage(WM_USER+13,0,0);
		
	}
	if (mode==9)
	{
		PostMessage(WM_USER+1,0,0);		
	}
	return FALSE;  // retourne TRUE, sauf si vous avez défini le focus sur un contrôle
}

LRESULT CMessage::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	
	if(message==WM_USER+1 )
	{
		CConcertoDlg* par=(CConcertoDlg* )GetParent();
		par->ltmp.ResetContent();
		par->ltmp.AddString("Erreur client ou utilisateur");						
		par->ltmp.AddString("Erreur matérielle");						
		par->ltmp.AddString("Formation");						
		par->ltmp.AddString("Maintenance");						
		if(par->ltmp.GetCount()>0&&pcombo==NULL)
		{
			CCombo dlg;
			srep.GetWindowRect(&dlg.rctstat);
			dlg.rctstat.top=dlg.rctstat.bottom;
			dlg.winh=(int)(par->htou/4);
			dlg.type=6;
			dlg.DoModal();
			if(dlg.sel>=0)
			{
				par->ltmp.GetText(dlg.sel,reponse);
				srep.SetWindowTextA(reponse);
				bok.EnableWindow(1);
			}
			else
			{
				reponse="";
				bok.EnableWindow(0);

			}
		}
	}

	return CDialog::DefWindowProc(message, wParam, lParam);
}


void CMessage::DrawButton()
{
	CRect rct;
	int bhauteur=hauteur*2;
	rct.top=0;
	rct.left=0;
	rct.right=bl-10;
	rct.bottom=(bhauteur)-10;
	//BOUTON MANAGER
	if(mode==0||mode==2||mode==7||mode==8||mode==9)
	{
		bok.SetWindowPos(&wndTop,org,orgh,bl,bhauteur,SWP_SHOWWINDOW   );
		bca.SetWindowPos(&wndTop,org+(2*bl),orgh,bl,bhauteur,SWP_SHOWWINDOW);
	}
	else
		if(mode!=10)
			bok.SetWindowPos(&wndTop,org+bl,orgh,bl,bhauteur,SWP_SHOWWINDOW   );
}

HBRUSH CMessage::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
	if(pWnd->GetDlgCtrlID()==IDC_MOTIF)
	{
		ticketbrush.DeleteObject();
		ticketbrush.CreateSolidBrush(dlgrefcolor);
		hbr=(HBRUSH)ticketbrush;
		pDC->SetBkColor(dlgrefcolor);
		pDC->SetTextColor(txtdlgrefcolor);
		pDC->SelectObject(&staticfont);
	}
	if(pWnd->GetDlgCtrlID()==IDC_CAL)
	{
		pDC->SelectObject(&butdlgfont);
	}
	return hbr;
}

BOOL CMessage::OnEraseBkgnd(CDC* pDC)
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
void CMessage::OnStnClickedMotif()
{
	if (mode==9&&pcombo==NULL)
	{
		PostMessage(WM_USER+1,0,0);		
	}
	// TODO: Add your control notification handler code here
}

void CMessage::OnBnClickedOk()
{
	if(mode==8&&reponse!=""&&auteur=="")
	{
		MessageBox("Veuillez entrer votre nom");
		eaut.SetFocus();
	}
	else
		OnOK();
}

void CMessage::OnBnClickedCancel()
{
	reponse="";
	auteur="";
	OnCancel();
}

void CMessage::OnPaint()
{
	CPaintDC dc(this); // device context for painting
}

void CMessage::OnTimer(UINT_PTR nIDEvent)
{
	int i=0;
	CString temp;
	DWORD len;
	if(nIDEvent==1)
	{
		idxstop=buf.Find("\r\n",idxstart);
		if(idxstop!=-1)
		{
			idxstop+=2;
			temp=buf.Mid(idxstart,idxstop-idxstart);
			WriteFile(hf,temp.GetBuffer(temp.GetLength()),temp.GetLength(),&len,NULL);
			idxstart=idxstop;
			psend.StepIt();
		}
		else
		{
			KillTimer(1);
			bok.ShowWindow(1);
			smes2.SetWindowText("Transfert des tickets terminé.");
			Sleep(500);
			OnOK();
		}
	}
	if(nIDEvent==2)
	{
		KillTimer(2);		
		if(((CConcertoDlg*)psource)->dirlist.GetCount()>0)
		{
			((CConcertoDlg*)psource)->dirlist.GetText(0,temp);
			smes2.SetWindowText("Transfert de "+temp);
			CreateDirectory(((CConcertoDlg*)psource)->targetexport+"\\"+temp,NULL);
			if(CopyFile(((CConcertoDlg*)psource)->datadir+"\\"+temp+"\\Concert.dat",((CConcertoDlg*)psource)->targetexport+"\\"+temp+"\\Concert.dat",FALSE)==0)
				((CConcertoDlg*)psource)->resultexport++;
			psend.StepIt();
			((CConcertoDlg*)psource)->dirlist.DeleteString(0);
			SetTimer(2,50,NULL);
		}
		else
		{
			OnOK();
		}
	}
	CDialog::OnTimer(nIDEvent);
}

void CMessage::OnMcnSelectMonthcalendar1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMSELCHANGE pSelChange = reinterpret_cast<LPNMSELCHANGE>(pNMHDR);
	CTime temptime;
	CTime curdate=CTime::GetCurrentTime();
	cal.GetCurSel(temptime);
				SYSTEMTIME DAT;
				SYSTEMTIME HEU;
				curdate.GetAsSystemTime(DAT);
				selhor.GetAsSystemTime(HEU);
				DAT.wHour=0;//HEU.wHour;
				DAT.wMinute=0;//HEU.wMinute;
				DAT.wSecond=0;//HEU.wSecond;
	CTime dtemp(DAT);

	if(temptime<dtemp)
	{
		cal.SetCurSel(curdate);
	}
	else
	{
		seldate=temptime;
		cal.RedrawWindow();//0,0,1|256|4);
		if(mode==4)
		{
			date=seldate.Format("%d/%m/%Y");
			smes2.SetWindowTextA(date);
		}
		if(mode==5)
		{
			date=seldate.Format("%d/%m/%Y")+selhor.Format(" à %H:%M");
			smes2.SetWindowTextA(date);
		}
	}
	*pResult = 0;
}

void CMessage::OnMcnSelchangeMonthcalendar1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMSELCHANGE pSelChange = reinterpret_cast<LPNMSELCHANGE>(pNMHDR);
	CTime temptime;
	CTime curdate=CTime::GetCurrentTime();
	cal.GetCurSel(temptime);
	SYSTEMTIME DAT;
	SYSTEMTIME HEU;
	curdate.GetAsSystemTime(DAT);
	selhor.GetAsSystemTime(HEU);
	DAT.wHour=0;//HEU.wHour;
	DAT.wMinute=0;//HEU.wMinute;
	DAT.wSecond=0;//HEU.wSecond;
	CTime dtemp(DAT);

	if(temptime<dtemp)
	{
		cal.SetCurSel(curdate);
	}
	else
	{
		cal.RedrawWindow();
		seldate=temptime;
		if(mode==4)
		{
			date=seldate.Format("%d/%m/%Y");
			smes2.SetWindowTextA(date);
		}
		if(mode==5)
		{
			date=seldate.Format("%d/%m/%Y")+selhor.Format(" à %H:%M");
			smes2.SetWindowTextA(date);
		}
	}
	*pResult = 0;
}

void CMessage::OnDtnDatetimechangeHoraire(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	hor.GetTime(selhor);
	if(mode==4)
	{
		date=seldate.Format("%d/%m/%Y");
		smes2.SetWindowTextA(date);
	}
	if(mode==5)
	{
		date=seldate.Format("%d/%m/%Y")+selhor.Format(" à %H:%M");
		smes2.SetWindowTextA(date);
	}
	*pResult = 0;
}
void CMessage::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CConcertoDlg* par=(CConcertoDlg* )GetParent();
	CDC* pdc=CDC::FromHandle(lpDrawItemStruct->hDC);
	CRect rct;
	CString temp1;
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
			{
				pdc->DrawText(par->txtc[118],-1,&rct,DT_CENTER|DT_SINGLELINE|DT_VCENTER );//"OUI"
			}
			else
				if(mode==2)
				{
					pdc->DrawText(par->txtc[23],-1,&rct,DT_CENTER|DT_SINGLELINE|DT_VCENTER );//"Code"
				}
				else
				{
					pdc->DrawText("OK",-1,&rct,DT_CENTER|DT_SINGLELINE|DT_VCENTER );
				}
		}
		if(nIDCtl==IDC_ANNULER)
		{
			if(mode==0)
			{
				pdc->DrawText(par->txtc[119],-1,&rct,DT_CENTER|DT_SINGLELINE|DT_VCENTER );//"NON"
			}
			else
				if(mode==2||mode==7||mode==8||mode==9)
				{
					pdc->DrawText(par->txtc[112],-1,&rct,DT_CENTER|DT_SINGLELINE|DT_VCENTER );//"Annuler"
				}
		}
	}
}



void CMessage::OnEnChangeReponse()
{
	erep.GetWindowTextA(reponse);
}

void CMessage::OnEnChangeAuteur()
{
	eaut.GetWindowTextA(auteur);
}

void CMessage::OnEnSetfocusAuteur()
{
	CConcertoDlg* par=(CConcertoDlg* )GetParent();
	par->kid= eaut.GetDlgCtrlID();
}

void CMessage::OnEnSetfocusReponse()
{
	CConcertoDlg* par=(CConcertoDlg* )GetParent();
	if(mode==8)
		par->kid= erep.GetDlgCtrlID();
}

BOOL CMessage::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	if(mode==9&&pcombo!=NULL&&message==WM_LBUTTONUP&&pWnd->GetSafeHwnd()==this->m_hWnd)
	{
		//MessageBox("CloseCombo");
		pcombo->CloseCombo();
		pcombo=NULL;
	}

	return CDialog::OnSetCursor(pWnd, nHitTest, message);
}


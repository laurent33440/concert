#include "stdafx.h"
#include "Concerto.h"
#include "ConcertoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

HBRUSH CConcertoDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	int x=pWnd->GetDlgCtrlID();
	if(x==IDC_NDATE||x==IDC_NPOSTE||x==IDC_NLICENSE||x==IDC_NNOM||x==IDC_NAD1||x==IDC_NAD2
		||x==IDC_NLANGUE||x==IDC_NDEVISE||x==IDC_NSIRET||x==IDC_NNAUTO||x==IDC_NNAF
		||x==IDC_NPAUTO||x==IDC_NCONSO||x==IDC_NPRIX||x==IDC_NCONS
		||x==IDC_NTVA1||x==IDC_NTVA2||x==IDC_NSPECT||x==IDC_NSERVEUR
		||x==IDC_NMENTIONT||x==IDC_NMENTIONP||x==IDC_NPAYS||x==IDC_NPREFIX
		||x==IDC_NVHORAIRE||x==IDC_NVALCONTROL||x==IDC_NLIBEL
		||x==IDC_NVALPLACE||x==IDC_NVALPWD||x==IDC_NVALPAGE||x==IDC_NVALMIX
		||x==IDC_NETC||x==IDC_AVERT1||x==IDC_AVERT2||x==IDC_AVERT3||x==IDC_TQR)
	{
		pDC->SetBkMode(TRANSPARENT);//Color(ticketresultrefcolor);
		pDC->SetTextColor(0);//txtticketresultrefcolor);
		pDC->SelectObject(&geodate);
		return  (HBRUSH)GetStockObject(WHITE_BRUSH);
	}
	if(x==IDC_TQR)
	{
		pDC->SetBkMode(TRANSPARENT);//Color(ticketresultrefcolor);
		pDC->SetTextColor(0);//txtticketresultrefcolor);
		pDC->SelectObject(&geostat);
		return  (HBRUSH)GetStockObject(WHITE_BRUSH);
	}
	if(x==IDC_GCLIENT||x==IDC_GSECUR||x==IDC_GEDIT||x==IDC_GLOG||x==IDC_NEXER)
	{
		hbr=(HBRUSH)GetStockObject(WHITE_BRUSH);
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(0x8346D5);
		pDC->SelectObject(&geodate);
	}
	if(x==IDC_NVALCONTROL)
	{
		hbr=(HBRUSH)GetStockObject(WHITE_BRUSH);//ticketbrush;
		pDC->SetBkMode(TRANSPARENT);//Color(nconfigrefcolor);
		pDC->SetTextColor(0x8346D5);
		pDC->SelectObject(&geodate);
	}
	if(x==IDC_SPOSTE||x==IDC_PRIX||x==IDC_SCONS||x==IDC_TVA1||x==IDC_TVA2
		||x==IDC_SMENTIONT||x==IDC_SMENTIONP||x==IDC_VAL1||x==IDC_VAL2||x==IDC_SPREFIX
		||x==IDC_LIBELGUICHET||x==IDC_SNOM||x==IDC_SAD1||x==IDC_SAD2||x==IDC_SSIRET||x==IDC_SNAF
		||x==IDC_LIBEL1||x==IDC_LIBEL2||x==IDC_LIBELCONS||x==IDC_SPAYS||x==IDC_SSERVEUR
		||x==IDC_NLIBEL1||x==IDC_LIBELSPECT||x==IDC_SLANGUE||x==IDC_SEXER
		||x==IDC_SDEVISE||x==IDC_SLICENSE0||x==IDC_SLICENSE1||x==IDC_SLICENSE2||
		x==IDC_SLICENSE3||x==IDC_SLICENSE4||x==IDC_SLICENSE5||x==IDC_SLICENSE6)
	{
		pDC->SetBkMode(TRANSPARENT);//Color(sconfigrefcolor);
		pDC->SetTextColor(0xFFFFFF);
		pDC->SelectObject(&geodate);
		return  (HBRUSH)GetStockObject(BLACK_BRUSH);
	}
	if(x==IDC_SEARCH||x==IDC_NAN||x==IDC_SAN||x==IDC_NMOIS||x==IDC_SMOIS)
	{
		hbr=(HBRUSH)GetStockObject(WHITE_BRUSH);//ticketbrush;
		pDC->SetBkMode(TRANSPARENT);//Color(ticketresultrefcolor);
		pDC->SetTextColor(0);//txtticketresultrefcolor);
		pDC->SelectObject(&geodate);
	}
	if(x==IDC_TEMNET||x==IDC_TEMCONTROL||x==IDC_TEMWEB)
	{
		hbr=(HBRUSH)GetStockObject(WHITE_BRUSH);//ticketbrush;
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(0);
		pDC->SelectObject(&geodate);
	}
	if(x==IDC_LNTICK||x==IDC_LDATE||x==IDC_LPRIX||x==IDC_LCANCEL)
	{
		return  (HBRUSH)GetStockObject(NULL_BRUSH);
	}
	if(x==IDC_SELSPECT)
	{
		return  (HBRUSH)GetStockObject(NULL_BRUSH);
	}

	if(x==IDC_TOTAL)
	{
		totalbrush.DeleteObject();
		totalbrush.CreateSolidBrush(0x404040);
		hbr=(HBRUSH)totalbrush;
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(0xFFFFFF);
		pDC->SelectObject(&geonum);
	}
	if(x==IDC_NTOTAL)
	{
		ntotalbrush.DeleteObject();
		ntotalbrush.CreateSolidBrush(0x0);
		hbr=(HBRUSH)ntotalbrush;
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(0xFFFFFF);
		pDC->SelectObject(&geoent);
	}
	if(x==IDC_NPAGE)
	{
		hbr=NULL;
		pDC->SetBkMode(TRANSPARENT);
		pDC->SelectObject(&ticketfont);
	}
	if(x==IDC_CODE||x==IDC_QTE||x==IDC_PTOT||x==IDC_NSCAN||x==IDC_TEMNET||x==IDC_TEMWEB||x==IDC_TEMGATE||x==IDC_TEMCONTROL)
	{
		return  (HBRUSH)GetStockObject(NULL_BRUSH);
	}
	return hbr;
}

int CConcertoDlg::SimTicketRect(CDC* pdc,CRect rct)
{
	CPoint ptst;
	CPoint pten;
	int arcd=rct.Width()/10;
	int	x0=rct.left+rct.Width()/6;
	int y0=rct.top+rct.Height()/15;
	int	x1=2*x0;
	int y1=2*y0;
	int arct=rct.Width()/28;
	CRect rcta;
	rcta.top=rct.top-arcd;
	rcta.bottom=rct.top+arcd;
	rcta.left=rct.left-arcd;
	rcta.right=rct.left+arcd;

	ptst.SetPoint(rct.left,rct.top+arcd);
	pten.SetPoint(rct.left+arcd,rct.top);
	pdc->Arc(&rcta,ptst,pten);
	pdc->MoveTo(rct.left+arcd,rct.top);
	pdc->LineTo(rct.left+4*arcd,rct.top);
	pdc->LineTo(rct.left+4*arcd,rct.top+arcd/2);
	pdc->LineTo(rct.right-4*arcd,rct.top+arcd/2);
	pdc->LineTo(rct.right-4*arcd,rct.top);
	pdc->LineTo(rct.right-arcd,rct.top);


	rcta.left=rct.right-arcd;
	rcta.right=rct.right+arcd;
	ptst.SetPoint(rct.right-arcd,rct.top);
	pten.SetPoint(rct.right,rct.top+arcd);
	pdc->Arc(&rcta,ptst,pten);
	pdc->MoveTo(rct.right,rct.top+arcd);
	pdc->LineTo(rct.right,rct.bottom-arcd);//-

	rcta.top=rct.bottom-arcd;
	rcta.bottom=rct.bottom+arcd;
	ptst.SetPoint(rct.right,rct.bottom-arcd);
	pten.SetPoint(rct.right-arcd,rct.bottom);
	pdc->Arc(&rcta,ptst,pten);
	pdc->MoveTo(rct.right-arcd,rct.bottom);
	pdc->LineTo(rct.right-4*arcd,rct.bottom);
	pdc->LineTo(rct.right-4*arcd,rct.bottom-arcd/2);
	pdc->LineTo(rct.left+4*arcd,rct.bottom-arcd/2);
	pdc->LineTo(rct.left+4*arcd,rct.bottom);
	pdc->LineTo(rct.left+arcd,rct.bottom);


	rcta.left=rct.left-arcd;
	rcta.right=rct.left+arcd;
	ptst.SetPoint(rct.left-arcd,rct.bottom);
	pten.SetPoint(rct.left,rct.bottom-arcd);
	pdc->Arc(&rcta,ptst,pten);
	pdc->MoveTo(rct.left,rct.bottom-arcd);
	pdc->LineTo(rct.left,rct.top+arcd);
	return arcd;
}

void CConcertoDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CString temp;
	CString temp1;
	CDC* pdc=CDC::FromHandle(lpDrawItemStruct->hDC);
	COLORREF col;
	CRect rct;
	int largeur;//
	int hauteur;//
	if(lpDrawItemStruct->CtlType==ODT_BUTTON)
	{
		pdc->SetBkMode(TRANSPARENT);
		pdc->FillSolidRect(&lpDrawItemStruct->rcItem,0xFFFFFF);
	}
	if(nIDCtl>=IDC_ART1&&nIDCtl<=IDC_ART16)
	{
		//CString cod;
		CString prx;
		CString nomup;
		CString nomdn;
		CPen bar(PS_SOLID,2,0xFF);
		int idx;
		//int idc;
		int i;
		i=nIDCtl-IDC_ART1;
		idx=i+1+(artrange*NAPP);
		CRect rctlib;
		CRect rct=lpDrawItemStruct->rcItem;
		CRect rctemp=rct;
		CBrush br((COLORREF)0x000000);
		CBrush brs((COLORREF)0x0000FF);
		CPen pns(PS_SOLID,3,(COLORREF)0x0000FF);
		CPen pn(PS_SOLID,3,(COLORREF)0x000000);
		if(afmode==1&&wsel==3)
		{
			pdc->SelectStockObject(NULL_BRUSH);
			if(seltouche==i)
			{
				pdc->SelectObject(&pns);

			}
			else
				pdc->SelectObject(&pn);
				//pdc->FrameRect(&rct,&br);
			pdc->RoundRect(0,0,rct.Width(),rct.Height(),30,30);
		}
		RectF rctf(0,0,(REAL)rct.Width(),(REAL)rct.Height());
		rctemp.DeflateRect(3,3,3,(rctemp.Height()/4));
		if(afmode==0||(afmode==1&&wsel==4))
			rct.DeflateRect(rct.Width()/5,rct.Height()/5);
		//rctb.Inflate(-10,-10);
		largeur=rct.Width();//ltou;//
		hauteur=rct.Height();//htou;//5.1);//
		pdc->SetBkMode(TRANSPARENT);//(col);
		pdc->SetTextColor(0);
		// **********  DESSIN du bouton
		Graphics gr (pdc->m_hDC);
		UINT x=part[idx]->GetWidth();
		UINT y=part[idx]->GetHeight();
		double rim=(double)x/(double)y;// ratio image
		double rci=(double)rctemp.Width()/(double)rctemp.Height();//ratio cible
		RectF rctb((REAL)rctemp.left,(REAL)rctemp.top,(REAL)rctemp.Width(),(REAL)rctemp.Height());
		if(rim>=rci)
		{
			REAL delta=(REAL)((double)(((double)rctemp.Height()-(double)rctemp.Width()/rim)/2));
			rctb.Inflate((REAL)0,-delta);
		}
		else
		{
			REAL delta=(REAL)((double)(((double)rctemp.Width()-(double)rctemp.Height()*rim)/2));
			rctb.Inflate(-delta,0);
		}
		if(wsel==1&&afmode==0)
		{
			if(!(lpDrawItemStruct->itemState & ODS_SELECTED)&&(perso[idx]&8)==0)
				gr.DrawImage(pbnartac,rctf);
			else
				gr.DrawImage(pbsartac,rctf);
		}
		else
		{
			if(wsel==1&&afmode==1&&!(perso[idx]&8)&&wsel==1)//&&touche non active
			{
				gr.DrawImage(part[idx],rctb);
			}
		}
		if((wsel==3&&afmode==0)||wsel==4)
		{
			if((seltouche==i&&wsel==3))
			{
				pdc->SetTextColor(0xFFFFFF);
				gr.DrawImage(pbsartbo,rctf);
			}
			else
			{
				if(wsel==4&&cselevt[idx]==1)
				{
					int idx=i+(artrange*NAPP)+1;
					pdc->SetTextColor(0xFFFFFF);
					gr.DrawImage(pbsartbo,rctf);
				}
				else
					if(!((lpDrawItemStruct->itemState & ODS_SELECTED)))
						gr.DrawImage(pbnartbo,rctf);
					else
					{
						pdc->SetTextColor(0xFFFFFF);
						gr.DrawImage(pbsartbo,rctf);
					}
			}
		}
		else
			if(wsel==3&&afmode==1)
			{
				gr.DrawImage(part[idx],rctb);
			}
		// **********  TEXTE du bouton
		if(wsel==0||wsel==1||wsel==2||wsel==3||wsel==5)
		{
			//if(wsel==1)
			//else
				//pdc->SelectObject(&buttonfont);
			if(wsel==1&&libel1[idx].Find("$",0)==0)
				nomup=libel1[idx].Mid(1);
			else
			{
				nomup=libel1[idx];
			}
			nomdn=libel2[idx];
			prx.Format("%.2f "+cur,prix[idx]);
		}
		else
		{
			//pdc->SelectObject(&buttoncontrolfont);

			nomup=clibel1[idx];
			nomdn=clibel2[idx];
		}
		pdc->SelectObject(&hatart);
		rctlib.top=0;
		rctlib.left=0;
		rctlib.right=0;
		rctlib.bottom=0;
		//Calcul de la longueur du texte
		//m_Cdc.DrawText(nom,-1,&rctlib,DT_CALCRECT|DT_CENTER|DT_SINGLELINE|DT_VCENTER|DT_NOPREFIX );

		rctlib.top=rct.top;
		rctlib.bottom=rctlib.top+(LONG)((6*hauteur/20));
		rctlib.left=rct.left;//largeur/10;
		rctlib.right=rct.right;
		//if((wsel==1&&(perso[idx]&8)==0)||wsel>1)
		if((wsel==0||wsel==1||wsel==2||wsel==3||wsel==5)&&afmode==0)
			pdc->DrawText(nomup,-1,&rctlib,DT_CENTER|DT_SINGLELINE|DT_VCENTER|DT_NOPREFIX );
		else
		{
			if(afmode==0||wsel==4)
			{
				//pdc->SelectObject(&buttoncontrolfont);
				pdc->DrawText(nomup,-1,&rctlib,DT_CENTER|DT_SINGLELINE|DT_VCENTER|DT_NOPREFIX|DT_END_ELLIPSIS);//
				//pdc->SelectObject(&buttonfont);
			}
		}
		rctlib.top=rct.top+(LONG)((7*hauteur/20));
		rctlib.bottom=rctlib.top+(LONG)((6*hauteur/20));
		if(afmode==0||(afmode==1&&wsel==4))
			pdc->DrawText(nomdn,-1,&rctlib,DT_CENTER|DT_SINGLELINE|DT_VCENTER|DT_NOPREFIX );
		rctlib.top=rct.top+(LONG)((14*hauteur/20));
		rctlib.bottom=rctlib.top+(LONG)((6*hauteur/20));
		//if(wsel==1)
		pdc->SelectObject(&hatprxart);

		if(nomup!="" || nomdn!="")
		{
			if(wsel==0||wsel==1||wsel==2||wsel==3||wsel==5)
			{
				if((perso[idx]&8)&&wsel==1&&afmode)
					;
				else				
					pdc->DrawText(prx,-1,&rctlib,DT_CENTER|DT_SINGLELINE|DT_VCENTER|DT_NOPREFIX );
			}
			else
				pdc->DrawText(cfrom[idx],-1,&rctlib,DT_CENTER|DT_SINGLELINE|DT_VCENTER|DT_NOPREFIX );//**************************************
		}
		if(	perso[idx]&8&&wsel==1&&afmode==0)//touche non active
		{
			pdc->SelectObject(&bar);
			rctlib.top=rct.top;
			rctlib.bottom=rctlib.top+(LONG)((20*hauteur/20));
			pdc->MoveTo(rctlib.left,rctlib.top);
			pdc->LineTo(rctlib.right,rctlib.bottom);
			pdc->MoveTo(rctlib.left,rctlib.bottom);
			pdc->LineTo(rctlib.right,rctlib.top);		
			
		}
	}
	if(nIDCtl>=IDC_FAM1&&nIDCtl<=IDC_FAM3)
	{
		int i;
		CRect rct=lpDrawItemStruct->rcItem;
		CBrush br((COLORREF)0x000000);
		if(etc==1&&wsel!=3)
			pdc->FrameRect(&rct,&br);
		i=nIDCtl-IDC_FAM1;
		UINT x=pbfam[i]->GetWidth();
		UINT y=pbfam[i]->GetHeight();
		rct.DeflateRect(2,2,2,2);
		double rim=(double)x/y;// ratio image
		double rci=(double)rct.Width()/(double)rct.Height();//ratio cible
		RectF rctb((REAL)rct.left,(REAL)rct.top,(REAL)rct.Width(),(REAL)rct.Height());
		if(rim>=rci)
		{
			REAL delta=(REAL)((double)(((double)rct.Height()-(double)rct.Width()/rim)/2));
			rctb.Inflate((REAL)0,-delta);
		}
		else
		{
			REAL delta=(REAL)((double)(((double)rct.Width()-(double)rct.Height()*rim)/2));
			rctb.Inflate(-delta,0);
		}
		Graphics gr (pdc->m_hDC);
		gr.DrawImage(pbfam[i],rctb);
	}
	if(nIDCtl>=IDC_RUB1&&nIDCtl<=IDC_RUB3)
	{
		int i;
		CRect rct=lpDrawItemStruct->rcItem;
		CBrush br((COLORREF)0x000000);
		if(etc==1&&wsel!=3)
			pdc->FrameRect(&rct,&br);
		i=(nIDCtl-IDC_RUB1)+((selfam-1)*3);
		UINT x=pbrub[i]->GetWidth();
		UINT y=pbrub[i]->GetHeight();
		rct.DeflateRect(2,2,2,2);
		double rim=(double)x/(double)y;// ratio image
		double rci=(double)rct.Width()/(double)rct.Height();//ratio cible
		RectF rctb((REAL)rct.left,(REAL)rct.top,(REAL)rct.Width(),(REAL)rct.Height());
		if(rim>=rci)
		{
			REAL delta=(REAL)((double)(((double)rct.Height()-(double)rct.Width()/rim)/2));
			rctb.Inflate((REAL)0,-delta);
		}
		else
		{
			REAL delta=(REAL)((double)(((double)rct.Width()-(double)rct.Height()*rim)/2));
			rctb.Inflate(-delta,0);
		}
		Graphics gr (pdc->m_hDC);
		gr.DrawImage(pbrub[i],rctb);

	}
	if(nIDCtl==IDC_NSCAN)
	{
		rct=lpDrawItemStruct->rcItem;
		pdc-> SetBkMode(TRANSPARENT);
		//pdc->SetBkColor(0xFFFFFF);
		if(SCANCOLOR==0)
			pdc->SetTextColor(controlcolor);
		else
			pdc->SetTextColor(0x0000FF);
		pdc->SelectObject(&scanfont);
		pdc->DrawText(scan,-1,&rct,SCANMODE );
	}
	if(nIDCtl==IDC_PAGE)
	{
		rctpage=lpDrawItemStruct->rcItem;
		/*RectF rctf(0,0,(REAL)rctpage.Width(),(REAL)rctpage.Height());
		Graphics grp (pdc->m_hDC);
		grp.DrawImage(pspage,rctf);
		pdc-> SetBkMode(TRANSPARENT);
		pdc->SetTextColor(0);
		pdc->SelectObject(&geopage);
		temp.Format("%u",artrange+1);
		temp=txtpage;
		pdc->DrawText(temp,-1,&rctpage,DT_CENTER|DT_SINGLELINE|DT_VCENTER );*/
	}
	if(nIDCtl==IDC_TOTAL)
	{
		CRect rct;
		rctpage=lpDrawItemStruct->rcItem;
		pdc-> SetBkMode(TRANSPARENT);
		pdc->SetTextColor(0xFFFFFF);
		pdc->FillSolidRect(&rctpage,0x404040);
		//hbr=(HBRUSH)totalbrush;
		pdc->SetBkMode(TRANSPARENT);
		pdc->SetTextColor(0xFFFFFF);
		pdc->SelectObject(&geonum);
		total.GetWindowText(temp);
		int i=pdc->DrawText(temp,-1,&rct,DT_CENTER|DT_CALCRECT );
		rctpage.top=rctpage.top+((rctpage.Height()-i)/2);
		pdc->DrawText(temp,-1,&rctpage,DT_CENTER);
	}
	if(nIDCtl==IDC_FIG||nIDCtl==IDC_FID||nIDCtl==IDC_PAGE)
	{
		CDC* pdci=butinf.GetDC();
		CDC* pdcs=butsup.GetDC();
		CDC* padc= wpage.GetDC();
		Graphics gri (pdci->m_hDC);
		Graphics grs (pdcs->m_hDC);
		Graphics grp (padc->m_hDC);
		rct=lpDrawItemStruct->rcItem;
		RectF rctfi(0,0,(REAL)rctinf.Width(),(REAL)rctinf.Height());
		RectF rctfs(0,0,(REAL)rctsup.Width(),(REAL)rctsup.Height());
		RectF rctf(0,0,(REAL)rctpage.Width(),(REAL)rctpage.Height());
		grp.DrawImage(pspage,rctf);
		padc-> SetBkMode(TRANSPARENT);
		padc->SetTextColor(0);
		padc->SelectObject(&hatprxart);//geopage);
		//temp.Format("%u",artrange+1);
		temp=txtpage;
		padc->DrawText(temp,-1,&rctpage,DT_CENTER|DT_SINGLELINE|DT_VCENTER );
		ReleaseDC(padc);
		if(nIDCtl==IDC_FIG)
		{
			if(!(lpDrawItemStruct->itemState & ODS_SELECTED))
			{
				grs.DrawImage(pbnsup,rctfs);				
				gri.DrawImage(pbninf,rctfi);
			}
			else
			{
				grs.DrawImage(pbnsup,rctfs);
				gri.DrawImage(pbsinf,rctfi);
			}
		}
		else
		{
			if(!(lpDrawItemStruct->itemState & ODS_SELECTED))
			{
				grs.DrawImage(pbnsup,rctfs);
				gri.DrawImage(pbninf,rctfi);
			}
			else
			{
				grs.DrawImage(pbssup,rctfs);
				gri.DrawImage(pbninf,rctfi);
			}		
		}
		ReleaseDC(pdci);
		ReleaseDC(pdcs);
	}
	//BOUTON MANAGER
	if(nIDCtl==IDC_MANAGER)
	{
		if(wsel==1)
		{
			Graphics gr (pdc->m_hDC);
			CRect rct=lpDrawItemStruct->rcItem;
			RectF rctf(0,0,(REAL)rct.Width(),(REAL)rct.Height());
			if(!(lpDrawItemStruct->itemState & ODS_SELECTED))
			{
				gr.DrawImage(pbnman,rctf);
			}
			else
			{
				gr.DrawImage(pbsman,rctf);
			}
		}
	}
	//BOUTON QUITTER
	if(nIDCtl==IDC_QUITTER)
	{
		Graphics gr (pdc->m_hDC);
		//CStringW wstr;
		//CString temp;
		CRect rct=lpDrawItemStruct->rcItem;
		RectF rctf(0,0,(REAL)rct.Width(),(REAL)rct.Height());
		if(wsel==1)
		{
			if(!(lpDrawItemStruct->itemState & ODS_SELECTED))
			{
				gr.DrawImage(pbnquit,rctf);
			}
			else
			{
				gr.DrawImage(pbsquit,rctf);
			}
		}
		else
		{
			if(!(lpDrawItemStruct->itemState & ODS_SELECTED))
			{
				gr.DrawImage(pbnret,rctf);
				//temp=skindir+"quitter_etat1.jpg";
			}
			else
			{
				//temp=skindir+"quitter_etat2.jpg";
				gr.DrawImage(pbsret,rctf);
			}
		}
	}
	if(nIDCtl==IDC_RETURN)
	{
		Graphics gr (pdc->m_hDC);
		//CStringW wstr;
		//CString temp;
		CRect rct=lpDrawItemStruct->rcItem;
		RectF rctf(0,0,(REAL)rct.Width(),(REAL)rct.Height());
		if(!(lpDrawItemStruct->itemState & ODS_SELECTED))
		{
			gr.DrawImage(pbnret,rctf);
			//temp=skindir+"quitter_etat1.jpg";
		}
		else
		{
			//temp=skindir+"quitter_etat2.jpg";
			gr.DrawImage(pbsret,rctf);
		}
	}
	if(nIDCtl==IDC_11)// Bouton encaisser ou Démarrer/Arreter le controle
	{
		//col=encaisserrefcolor;
		pdc->SetBkColor(0x000000);
		pdc->SetTextColor(0xFFFFFF);
		pdc->SelectObject(&geonum);
		if(wsel==4)
		{
			Graphics gr (pdc->m_hDC);
			rct=lpDrawItemStruct->rcItem;
			RectF rctf(0,0,(REAL)rct.Width(),(REAL)rct.Height());
			pdc->SelectObject(&geonum);
			pdc-> SetBkMode(TRANSPARENT);
			pdc->SetTextColor(0xFFFFFF);
			if(!(lpDrawItemStruct->itemState & ODS_SELECTED)&&wsel!=3)
			{
				gr.DrawImage(pbnresbar,rctf);
			}
			else
			{
				gr.DrawImage(pbsresbar,rctf);
			}
			if(CONTROL)//"Arrêter le contrôle"
			{
				pdc->DrawText(txtc[14],-1,&lpDrawItemStruct->rcItem,DT_CENTER|DT_SINGLELINE|DT_VCENTER );
			}
			else
			{
				pdc->DrawText(txtc[15],-1,&lpDrawItemStruct->rcItem,DT_CENTER|DT_SINGLELINE|DT_VCENTER );
			}
		}
		else
		{
			if(wsel==1)
			{
				Graphics gr (pdc->m_hDC);
				//CStringW wstr;
				//CString temp;
				CRect rct=lpDrawItemStruct->rcItem;
				RectF rctf(0,0,(REAL)rct.Width(),(REAL)rct.Height());
				if(!(lpDrawItemStruct->itemState & ODS_SELECTED))
				{
					gr.DrawImage(pbnenc,rctf);
					//temp=skindir+"btn_barre_etat1.jpg";
				}
				else
				{
					gr.DrawImage(pbsenc,rctf);
					//temp=skindir+"btn_barre_etat2.jpg";
				}
				/*wstr=temp;
				Image myImage(wstr);
				gr.DrawImage(&myImage,rctf);*/
				if(afmode==0)
					pdc->DrawText(txtc[1],-1,&lpDrawItemStruct->rcItem,DT_CENTER|DT_SINGLELINE|DT_VCENTER );
				else
				{
					if(afmode==1)
					{
						if(etb==1)
							pdc->DrawText(txtc[147],-1,&lpDrawItemStruct->rcItem,DT_CENTER|DT_SINGLELINE|DT_VCENTER );
						if(etb==2)
							pdc->DrawText(txtc[148],-1,&lpDrawItemStruct->rcItem,DT_CENTER|DT_SINGLELINE|DT_VCENTER );
					}
				}
			}
		}
	}
	if(nIDCtl>=IDC_0&&nIDCtl<=IDC_10)
	{
		pdc->SetTextColor(0xFFFFFF);
		pdc->SelectObject(&geonum);
		pdc->SetBkMode(TRANSPARENT);

		if(wsel==1)
		{
			Graphics gr (pdc->m_hDC);
			//CStringW wstr;
			//CString temp;
			CRect rct=lpDrawItemStruct->rcItem;
			RectF rctf(0,0,(REAL)rct.Width(),(REAL)rct.Height());
			if(!(lpDrawItemStruct->itemState & ODS_SELECTED))
			{
				if(nIDCtl<IDC_10)
					gr.DrawImage(pbnnum,rctf);
					//temp=skindir+"btn_chiffrevierge_etat1.jpg";
				else
					gr.DrawImage(pbnclr,rctf);
					//temp=skindir+"btn_reset_etat1.jpg";
			}
			else
			{
				if(nIDCtl<IDC_10)
					//temp=skindir+"btn_chiffrevierge_etat2.jpg";
					gr.DrawImage(pbsnum,rctf);
				else
					gr.DrawImage(pbsclr,rctf);
					//temp=skindir+"btn_reset_etat2.jpg";
			}
			//wstr=temp;
			//Image myImage(wstr);
			//gr.DrawImage(&myImage,rctf);

		}
		if(nIDCtl<IDC_10)
			pdc->DrawText(Table[nIDCtl-IDC_0],-1,&lpDrawItemStruct->rcItem,DT_CENTER|DT_SINGLELINE|DT_VCENTER );
		else
		{
			pdc->SetTextColor(0xFFFFFF);
			pdc->SelectObject(&geotitre);
			pdc->DrawText("C",-1,&lpDrawItemStruct->rcItem,DT_CENTER|DT_SINGLELINE|DT_VCENTER );
		}


	}
	if(nIDCtl==IDC_IMPORT)
	{
		Graphics gr (pdc->m_hDC);
		rct=lpDrawItemStruct->rcItem;
		RectF rctf(0,0,(REAL)rct.Width(),(REAL)rct.Height());
		pdc->SelectObject(&geodate);
		pdc-> SetBkMode(TRANSPARENT);
		if(!(lpDrawItemStruct->itemState & ODS_SELECTED)&&wsel!=2)
		{
			gr.DrawImage(pbnpomo,rctf);
			pdc->SetTextColor(0xFFFFFF);
		}
		else
		{
			gr.DrawImage(pbspomo,rctf);
			pdc->SetTextColor(0xFFFFFF);
		}
		if(wsel==4)//"Importer"
			pdc->DrawText(txtc[16],-1,&lpDrawItemStruct->rcItem,DT_CENTER|DT_SINGLELINE|DT_VCENTER );
		else
			if(wsel==5)
				pdc->DrawText("Notice",-1,&lpDrawItemStruct->rcItem,DT_CENTER|DT_SINGLELINE|DT_VCENTER );
			else
				if(!master||!fprev)//"Importer"
					pdc->DrawText(txtc[16],-1,&lpDrawItemStruct->rcItem,DT_CENTER|DT_SINGLELINE|DT_VCENTER );
	}
	if(nIDCtl==IDC_ENTRYMODE)
	{
		Graphics gr (pdc->m_hDC);
		rct=lpDrawItemStruct->rcItem;
		RectF rctf(0,0,(REAL)rct.Width(),(REAL)rct.Height());
		pdc->SelectObject(&geodate);
		pdc-> SetBkMode(TRANSPARENT);
		if(!(lpDrawItemStruct->itemState & ODS_SELECTED)&&wsel!=2)
		{
			gr.DrawImage(pbnpomo,rctf);
			pdc->SetTextColor(0xFFFFFF);
		}
		else
		{
			gr.DrawImage(pbspomo,rctf);
			pdc->SetTextColor(0xFFFFFF);
		}
		pdc->DrawText(txtc[18],-1,&lpDrawItemStruct->rcItem,DT_CENTER|DT_SINGLELINE|DT_VCENTER );
	}
	if(nIDCtl==IDC_DEL)
	{
		Graphics gr (pdc->m_hDC);
		rct=lpDrawItemStruct->rcItem;
		RectF rctf(0,0,(REAL)rct.Width(),(REAL)rct.Height());
		pdc->SelectObject(&geodate);
		pdc-> SetBkMode(TRANSPARENT);
		if(!(lpDrawItemStruct->itemState & ODS_SELECTED)&&wsel!=2)
		{
			gr.DrawImage(pbndel,rctf);
			pdc->SetTextColor(0xFFFFFF);
		}
		else
		{
			gr.DrawImage(pbsdel,rctf);
			pdc->SetTextColor(0xFFFFFF);
		}
	}
	if(nIDCtl==IDC_COPY)
	{
		Graphics gr (pdc->m_hDC);
		rct=lpDrawItemStruct->rcItem;
		RectF rctf(0,0,(REAL)rct.Width(),(REAL)rct.Height());
		if(!(lpDrawItemStruct->itemState & ODS_SELECTED))
		{
			gr.DrawImage(pbncopy,rctf);
		}
		else
		{
			gr.DrawImage(pbscopy,rctf);
		}
	}
	if(nIDCtl==IDC_PASTE)
	{
		Graphics gr (pdc->m_hDC);
		rct=lpDrawItemStruct->rcItem;
		RectF rctf(0,0,(REAL)rct.Width(),(REAL)rct.Height());
		if(!(lpDrawItemStruct->itemState & ODS_SELECTED))
		{
			gr.DrawImage(pbnpaste,rctf);
		}
		else
		{
			gr.DrawImage(pbspaste,rctf);
		}
	}
	if(nIDCtl==IDC_BILPRINT)
	{
		Graphics gr (pdc->m_hDC);
		rct=lpDrawItemStruct->rcItem;
		RectF rctf(0,0,(REAL)rct.Width(),(REAL)rct.Height());
		pdc->SelectObject(&geodate);
		pdc-> SetBkMode(TRANSPARENT);
		if(!(lpDrawItemStruct->itemState & ODS_SELECTED)&&wsel!=2)
		{
			gr.DrawImage(pbnenc,rctf);
			pdc->SetTextColor(0xFFFFFF);
		}
		else
		{
			gr.DrawImage(pbsenc,rctf);
			pdc->SetTextColor(0xFFFFFF);
		}//Afficher les résultats
		pdc->DrawText(txtc[74],-1,&lpDrawItemStruct->rcItem,DT_CENTER|DT_SINGLELINE|DT_VCENTER );
	}
	if(nIDCtl==IDC_RAZ)
	{
		Graphics gr (pdc->m_hDC);
		rct=lpDrawItemStruct->rcItem;
		RectF rctf(0,0,(REAL)rct.Width(),(REAL)rct.Height());
		pdc->SelectObject(&geodate);
		pdc-> SetBkMode(TRANSPARENT);
		if(!(lpDrawItemStruct->itemState & ODS_SELECTED)&&wsel!=2)
		{
			gr.DrawImage(pbnpomo,rctf);
			pdc->SetTextColor(0xFFFFFF);
		}
		else
		{
			gr.DrawImage(pbspomo,rctf);
			pdc->SetTextColor(0xFFFFFF);
		}
		if(fadmin==1)//"RAZ"
		{
			pdc->DrawText(txtc[19],-1,&lpDrawItemStruct->rcItem,DT_CENTER|DT_SINGLELINE|DT_VCENTER );
		}
		else//"Liste CB"
		{
			pdc->DrawText(txtc[20],-1,&lpDrawItemStruct->rcItem,DT_CENTER|DT_SINGLELINE|DT_VCENTER );
		}
	}
	if(nIDCtl==IDC_BUREAU)
	{
		Graphics gr (pdc->m_hDC);
		rct=lpDrawItemStruct->rcItem;
		RectF rctf(0,0,(REAL)rct.Width(),(REAL)rct.Height());
		RectF rctif(15,15,(REAL)rct.Width()-30,(REAL)rct.Height()-30);
		pdc->SelectObject(&geodate);
		pdc-> SetBkMode(TRANSPARENT);
		if(!(lpDrawItemStruct->itemState & ODS_SELECTED)&&wsel!=2)
		{
			gr.DrawImage(pbnpomo,rctf);
			pdc->SetTextColor(0xFFFFFF);
		}
		else
		{
			gr.DrawImage(pbspomo,rctf);
			pdc->SetTextColor(0xFFFFFF);
		}
		gr.DrawImage(pbur,rctif);
	}
	if(nIDCtl==IDC_PRINTER)
	{
		Graphics gr (pdc->m_hDC);
		rct=lpDrawItemStruct->rcItem;
		RectF rctf(0,0,(REAL)rct.Width(),(REAL)rct.Height());
		RectF rctif(15,15,(REAL)rct.Width()-30,(REAL)rct.Height()-30);
		pdc->SelectObject(&geodate);
		pdc-> SetBkMode(TRANSPARENT);
		if(!(lpDrawItemStruct->itemState & ODS_SELECTED)&&wsel!=2)
		{
			gr.DrawImage(pbnpomo,rctf);
			pdc->SetTextColor(0xFFFFFF);
		}
		else
		{
			gr.DrawImage(pbspomo,rctf);
			pdc->SetTextColor(0xFFFFFF);
		}
		gr.DrawImage(pprint,rctif);
	}
	if(nIDCtl==IDC_NET)
	{
		Graphics gr (pdc->m_hDC);
		rct=lpDrawItemStruct->rcItem;
		RectF rctf(0,0,(REAL)rct.Width(),(REAL)rct.Height());
		RectF rctif(15,15,(REAL)rct.Width()-30,(REAL)rct.Height()-30);
		pdc->SelectObject(&geodate);
		pdc-> SetBkMode(TRANSPARENT);
		if(!(lpDrawItemStruct->itemState & ODS_SELECTED)&&wsel!=2)
		{
			gr.DrawImage(pbnpomo,rctf);
			pdc->SetTextColor(0xFFFFFF);
		}
		else
		{
			gr.DrawImage(pbspomo,rctf);
			pdc->SetTextColor(0xFFFFFF);
		}
		gr.DrawImage(pnet,rctif);
	}
	if(nIDCtl==IDC_BMANAGER)
	{
		Graphics gr (pdc->m_hDC);
		rct=lpDrawItemStruct->rcItem;
		RectF rctf(0,0,(REAL)rct.Width(),(REAL)rct.Height());
		pdc->SelectObject(&geodate);
		pdc-> SetBkMode(TRANSPARENT);
		if(!(lpDrawItemStruct->itemState & ODS_SELECTED)&&wsel!=2)
		{
			gr.DrawImage(pbnpomo,rctf);
			pdc->SetTextColor(0xFFFFFF);
		}
		else
		{
			gr.DrawImage(pbspomo,rctf);
			pdc->SetTextColor(0xFFFFFF);
		}
		if(fadmin==1)//"Code revendeur"
		{
			pdc->DrawText(txtc[139],-1,&lpDrawItemStruct->rcItem,DT_CENTER|DT_SINGLELINE|DT_VCENTER );//Code Rev.
		}
		else
		{
			pdc->DrawText(txtc[24],-1,&lpDrawItemStruct->rcItem,DT_CENTER|DT_SINGLELINE|DT_VCENTER );//Code Man
		}
	}
	if(nIDCtl==IDC_BUSER)
	{
		if(!fadmin)//"Code Util"
		{
			Graphics gr (pdc->m_hDC);
			rct=lpDrawItemStruct->rcItem;
			RectF rctf(0,0,(REAL)rct.Width(),(REAL)rct.Height());
			pdc->SelectObject(&geodate);
			pdc-> SetBkMode(TRANSPARENT);
			if(!(lpDrawItemStruct->itemState & ODS_SELECTED)&&wsel!=2)
			{
				gr.DrawImage(pbnpomo,rctf);
				pdc->SetTextColor(0xFFFFFF);
			}
			else 
			{
				gr.DrawImage(pbspomo,rctf);
				pdc->SetTextColor(0xFFFFFF);
			}
			
			pdc->DrawText(txtc[26],-1,&lpDrawItemStruct->rcItem,DT_CENTER|DT_SINGLELINE|DT_VCENTER );//Code Util
		}
	}
	if(nIDCtl==IDC_LOGO)
	{
		Graphics gr (pdc->m_hDC);
		rct=lpDrawItemStruct->rcItem;
		RectF rctf(0,0,(REAL)rct.Width(),(REAL)rct.Height());
		pdc->SelectObject(&geodate);
		pdc-> SetBkMode(TRANSPARENT);
		if(!(lpDrawItemStruct->itemState & ODS_SELECTED)&&wsel!=2)
		{
			gr.DrawImage(pbnpomo,rctf);
			pdc->SetTextColor(0xFFFFFF);
		}
		else
		{
			gr.DrawImage(pbspomo,rctf);
			pdc->SetTextColor(0xFFFFFF);
		}//"Logo"
		pdc->DrawText(txtc[27],-1,&lpDrawItemStruct->rcItem,DT_CENTER|DT_SINGLELINE|DT_VCENTER );
	}
	if(nIDCtl==IDC_CONTROL)
	{
		Graphics gr (pdc->m_hDC);
		rct=lpDrawItemStruct->rcItem;
		RectF rctf(0,0,(REAL)rct.Width(),(REAL)rct.Height());
		pdc->SelectObject(&geostat);
		pdc-> SetBkMode(TRANSPARENT);
		if(!(lpDrawItemStruct->itemState & ODS_SELECTED)&&wsel!=4)
		{
			gr.DrawImage(pbnnav,rctf);
			pdc->SetTextColor(0);
		}
		else
		{
			gr.DrawImage(pbsnav,rctf);
			pdc->SetTextColor(0xFFFFFF);
		}
		if(master)//"Contrôle"
		{
			pdc->DrawText(txtc[28],-1,&lpDrawItemStruct->rcItem,DT_CENTER|DT_SINGLELINE|DT_VCENTER );
		}
		else//"Transfert"
		{
			pdc->DrawText(txtc[28],-1,&lpDrawItemStruct->rcItem,DT_CENTER|DT_SINGLELINE|DT_VCENTER );
		}
	}
	if(nIDCtl==IDC_CONFIG)
	{
		Graphics gr (pdc->m_hDC);
		rct=lpDrawItemStruct->rcItem;
		RectF rctf(0,0,(REAL)rct.Width(),(REAL)rct.Height());
		pdc->SelectObject(&geostat);
		pdc-> SetBkMode(TRANSPARENT);
		if(!(lpDrawItemStruct->itemState & ODS_SELECTED)&&wsel!=5)
		{
			gr.DrawImage(pbnnav,rctf);
			pdc->SetTextColor(0);
		}
		else
		{
			gr.DrawImage(pbsnav,rctf);
			pdc->SetTextColor(0xFFFFFF);
		}//"Config"
		pdc->DrawText(txtc[30],-1,&lpDrawItemStruct->rcItem,DT_CENTER|DT_SINGLELINE|DT_VCENTER );

	}
	if(nIDCtl==IDC_RESULT)
	{
		Graphics gr (pdc->m_hDC);
		rct=lpDrawItemStruct->rcItem;
		RectF rctf(0,0,(REAL)rct.Width(),(REAL)rct.Height());
		pdc->SelectObject(&geostat);
		pdc-> SetBkMode(TRANSPARENT);
		if(!(lpDrawItemStruct->itemState & ODS_SELECTED)&&wsel!=2)
		{
			gr.DrawImage(pbnnav,rctf);
			pdc->SetTextColor(0);
		}
		else
		{
			gr.DrawImage(pbsnav,rctf);
			pdc->SetTextColor(0xFFFFFF);
		}//"Résultat"
		pdc->DrawText(txtc[31],-1,&lpDrawItemStruct->rcItem,DT_CENTER|DT_SINGLELINE|DT_VCENTER );
	}
	if(nIDCtl==IDC_ARTICLE)
	{
		Graphics gr (pdc->m_hDC);
		rct=lpDrawItemStruct->rcItem;
		RectF rctf(0,0,(REAL)rct.Width(),(REAL)rct.Height());
		pdc->SelectObject(&geostat);
		pdc-> SetBkMode(TRANSPARENT);
		if(!(lpDrawItemStruct->itemState & ODS_SELECTED)&&wsel!=3)
		{
			gr.DrawImage(pbnnav,rctf);
			pdc->SetTextColor(0);
		}
		else
		{
			gr.DrawImage(pbsnav,rctf);
			pdc->SetTextColor(0xFFFFFF);
		}//"Articles"
		pdc->DrawText(txtc[32],-1,&lpDrawItemStruct->rcItem,DT_CENTER|DT_SINGLELINE|DT_VCENTER );
	}
	if(nIDCtl==IDC_BILCANCEL)
	{
		Graphics gr (pdc->m_hDC);
		rct=lpDrawItemStruct->rcItem;
		RectF rctf(0,0,(REAL)rct.Width(),(REAL)rct.Height());
		pdc->SelectObject(&geonum);
		pdc-> SetBkMode(TRANSPARENT);
		pdc->SetTextColor(0xFFFFFF);
		if(!(lpDrawItemStruct->itemState & ODS_SELECTED)&&wsel!=3)
		{
			gr.DrawImage(pbnresbar,rctf);
		}
		else
		{
			gr.DrawImage(pbsresbar,rctf);
		}//"Annuler le ticket sélectionné"
		pdc->DrawText(txtc[33],-1,&lpDrawItemStruct->rcItem,DT_CENTER|DT_SINGLELINE|DT_VCENTER );
	}
	if(nIDCtl==IDC_CASH_VIEW)
	{
		Graphics gr (pdc->m_hDC);
		rct=lpDrawItemStruct->rcItem;
		RectF rctf(0,0,(REAL)rct.Width(),(REAL)rct.Height());
		pdc->SelectObject(&geonum);
		pdc-> SetBkMode(TRANSPARENT);
		pdc->SetTextColor(0xFFFFFF);
		if(!(lpDrawItemStruct->itemState & ODS_SELECTED)&&wsel!=3)
		{
			gr.DrawImage(pbnresbar,rctf);
		}
		else
		{
			gr.DrawImage(pbsresbar,rctf);
		}
		if(hist==0)//Lecture billetterie
		{
			pdc->DrawText(txtc[34],-1,&lpDrawItemStruct->rcItem,DT_CENTER|DT_SINGLELINE|DT_VCENTER );
		}
		else//Impression GTZ
		{
			pdc->DrawText(txtc[35],-1,&lpDrawItemStruct->rcItem,DT_CENTER|DT_SINGLELINE|DT_VCENTER );
		}
	}
	if(nIDCtl==IDC_PLUS)
	{
		Graphics gr (pdc->m_hDC);
		rct=lpDrawItemStruct->rcItem;
		RectF rctf(0,0,(REAL)rct.Width(),(REAL)rct.Height());
		pdc->SelectObject(&geonum);
		pdc-> SetBkMode(TRANSPARENT);
		pdc->SetTextColor(0x000000);
		if(!(lpDrawItemStruct->itemState & ODS_SELECTED)&&wsel!=3)
		{
			gr.DrawImage(pbnplum,rctf);
		}
		else
		{
			gr.DrawImage(pbsplum,rctf);
		}
		pdc->DrawText("+",-1,&lpDrawItemStruct->rcItem,DT_CENTER|DT_SINGLELINE|DT_VCENTER );
	}
	if(nIDCtl==IDC_MOINS)
	{
		Graphics gr (pdc->m_hDC);
		rct=lpDrawItemStruct->rcItem;
		RectF rctf(0,0,(REAL)rct.Width(),(REAL)rct.Height());
		pdc->SelectObject(&geonum);
		pdc-> SetBkMode(TRANSPARENT);
		pdc->SetTextColor(0x000000);
		if(!(lpDrawItemStruct->itemState & ODS_SELECTED)&&wsel!=3)
		{
			gr.DrawImage(pbnplum,rctf);
		}
		else
		{
			gr.DrawImage(pbsplum,rctf);
		}
		pdc->DrawText("-",-1,&lpDrawItemStruct->rcItem,DT_CENTER|DT_SINGLELINE|DT_VCENTER );
	}
	if(nIDCtl==IDC_GARB)
	{
		Graphics gr (pdc->m_hDC);
		rct=lpDrawItemStruct->rcItem;
		RectF rctf(0,0,(REAL)rct.Width(),(REAL)rct.Height());
		pdc->SelectObject(&geonum);
		pdc-> SetBkMode(TRANSPARENT);
		pdc->SetTextColor(0xFFFFFF);
		if(!(lpDrawItemStruct->itemState & ODS_SELECTED)&&wsel!=3)
		{
			gr.DrawImage(pbnpomo,rctf);
		}
		else
		{
			gr.DrawImage(pbspomo,rctf);
		}
		pdc->DrawText("X",-1,&lpDrawItemStruct->rcItem,DT_CENTER|DT_SINGLELINE|DT_VCENTER );
	}
	if(nIDCtl==IDC_CASH_CLOSE)
	{
		Graphics gr (pdc->m_hDC);
		rct=lpDrawItemStruct->rcItem;
		RectF rctf(0,0,(REAL)rct.Width(),(REAL)rct.Height());
		pdc->SelectObject(&geonum);
		pdc-> SetBkMode(TRANSPARENT);
		pdc->SetTextColor(0xFFFFFF);
		if(!(lpDrawItemStruct->itemState & ODS_SELECTED)&&wsel!=3)
		{
			gr.DrawImage(pbnresbar,rctf);
		}
		else
		{
			gr.DrawImage(pbsresbar,rctf);
		}
		if(hist==0)
		{
			temp=txtc[36];//"Clôture billetterie"
			pdc->DrawText(temp,-1,&lpDrawItemStruct->rcItem,DT_CENTER|DT_SINGLELINE|DT_VCENTER );
		}
		else
		{
			temp=txtc[75];//Impression GTZ et Journal
			pdc->DrawText(temp,-1,&lpDrawItemStruct->rcItem,DT_CENTER|DT_SINGLELINE|DT_VCENTER );
		}
	}
	if(nIDCtl==IDC_SELSPECT)
	{
		CRect rct;
		col=0x404040;
	
		if ((lpDrawItemStruct->itemAction | ODA_SELECT) &&  (lpDrawItemStruct->itemState & ODS_SELECTED))
		{
			pdc->SetTextColor(0x8346D5);
		}
		else
		{
			pdc->SetTextColor(0xFFFFFF);
		}
		pdc->SetBkMode(TRANSPARENT);//Color(col);
		rct=lpDrawItemStruct->rcItem;
		pdc->FillSolidRect(&rct,col);
		pdc->SelectObject(&this->hatprxart);
		//temp=clibel1[i].Left(30)+"\t"+clibel2[i].Left(10)+"\t"+"illimité"+"\t"+netxt+"/"+nttxt;

		if((int)lpDrawItemStruct->itemID>-1)
		{
			lselevt.GetText(lpDrawItemStruct->itemID,temp);
			int idx=0;
			int idy=0;
			for(int i=0;i<4;i++)
			{
				rct=lpDrawItemStruct->rcItem;
				if(i==0)
					rct.DeflateRect(0,0,12*rct.Width()/20,0);
				if(i==1)
					rct.DeflateRect(8*rct.Width()/20,0,9*rct.Width()/20,0);
				if(i==2)
					rct.DeflateRect(11*rct.Width()/20,0,2*rct.Width()/20,0);
				if(i==3)
					rct.DeflateRect(18*rct.Width()/20,0,0,0);
				idy=temp.Find(";",idx);
				if(idy!=-1)
					pdc->DrawText(temp.Mid(idx,idy-idx),-1,&rct,DT_SINGLELINE|DT_VCENTER|DT_LEFT|DT_END_ELLIPSIS );
				else
					pdc->DrawText(temp.Mid(idx),-1,&rct,DT_SINGLELINE|DT_VCENTER|DT_LEFT );
				idx=idy+1;

			}
		}
		pdc->SelectStockObject(NULL_BRUSH);
	}
	if(nIDCtl==IDC_LNTICK&&fldraw&&(int)lpDrawItemStruct->itemID>=lntick.GetTopIndex( )&&(int)lpDrawItemStruct->itemID<=lntick.GetTopIndex( )+15)
	{
		CRect rct;
		col=0x404040;
	
		if ((lpDrawItemStruct->itemAction | ODA_SELECT) &&  (lpDrawItemStruct->itemState & ODS_SELECTED))
		{
			pdc->SetTextColor(0x8346D5);
		}
		else
		{
			pdc->SetTextColor(0xFFFFFF);
		}
		pdc->SetBkMode(TRANSPARENT);//Color(col);
		rct=lpDrawItemStruct->rcItem;
		pdc->FillSolidRect(&rct,col);
		pdc->SelectObject(&geodate);
		if((int)lpDrawItemStruct->itemID>-1)
		{
			lntick.GetText(lpDrawItemStruct->itemID,temp);
			CRect rct=lpDrawItemStruct->rcItem;
			pdc->DrawText(temp,-1,&rct,DT_SINGLELINE|DT_VCENTER|DT_LEFT );
		}
		pdc->SelectStockObject(NULL_BRUSH);
	}
	if(nIDCtl==IDC_LDATE&&fldraw&&(int)lpDrawItemStruct->itemID>=ldate.GetTopIndex( )&&(int)lpDrawItemStruct->itemID<=ldate.GetTopIndex( )+15)
	{
		CRect rct;
		col=0x404040;
	
		if ((lpDrawItemStruct->itemAction | ODA_SELECT) &&  (lpDrawItemStruct->itemState & ODS_SELECTED))
		{
			pdc->SetTextColor(0x8346D5);
		}
		else
		{
			pdc->SetTextColor(0xFFFFFF);
		}
		pdc->SetBkMode(TRANSPARENT);//Color(col);
		rct=lpDrawItemStruct->rcItem;
		pdc->FillSolidRect(&rct,col);
		pdc->SelectObject(&geodate);
		if((int)lpDrawItemStruct->itemID>-1)
		{
			ldate.GetText(lpDrawItemStruct->itemID,temp);
			CRect rct=lpDrawItemStruct->rcItem;
			pdc->DrawText(temp,-1,&rct,DT_SINGLELINE|DT_VCENTER|DT_RIGHT );
		}
		pdc->SelectStockObject(NULL_BRUSH);
	}
	if(nIDCtl==IDC_LPRIX&&fldraw&&(int)lpDrawItemStruct->itemID>=lprix.GetTopIndex( )&&(int)lpDrawItemStruct->itemID<=lprix.GetTopIndex( )+15)
	{
		CRect rct;
		col=0x404040;
	
		if ((lpDrawItemStruct->itemAction | ODA_SELECT) &&  (lpDrawItemStruct->itemState & ODS_SELECTED))
		{
			pdc->SetTextColor(0x8346D5);
		}
		else
		{
			pdc->SetTextColor(0xFFFFFF);
		}
		pdc->SetBkMode(TRANSPARENT);//Color(col);
		rct=lpDrawItemStruct->rcItem;
		pdc->FillSolidRect(&rct,col);
		pdc->SelectObject(&geodate);
		if((int)lpDrawItemStruct->itemID>-1)
		{
			lprix.GetText(lpDrawItemStruct->itemID,temp);
			CRect rct=lpDrawItemStruct->rcItem;
			if(wsel==5)
				pdc->DrawText(temp,-1,&rct,DT_SINGLELINE|DT_VCENTER|DT_CENTER );
			else
				pdc->DrawText(temp,-1,&rct,DT_SINGLELINE|DT_VCENTER|DT_RIGHT );
		}
		pdc->SelectStockObject(NULL_BRUSH);
	}
	if(nIDCtl==IDC_LCANCEL&&fldraw&&(int)lpDrawItemStruct->itemID>=lcancel.GetTopIndex( )&&(int)lpDrawItemStruct->itemID<=lcancel.GetTopIndex( )+15)
	{
		CRect rct;
		col=0x404040;
	
		if ((lpDrawItemStruct->itemAction | ODA_SELECT) &&  (lpDrawItemStruct->itemState & ODS_SELECTED))
		{
			pdc->SetTextColor(0x8346D5);
		}
		else
		{
			pdc->SetTextColor(0xFFFFFF);
		}
		pdc->SetBkMode(TRANSPARENT);//Color(col);
		rct=lpDrawItemStruct->rcItem;
		pdc->FillSolidRect(&rct,col);
		pdc->SelectObject(&geodate);

		if((int)lpDrawItemStruct->itemID>-1)
		{
			lcancel.GetText(lpDrawItemStruct->itemID,temp);
			CRect rct=lpDrawItemStruct->rcItem;
			pdc->DrawText(temp,-1,&rct,DT_SINGLELINE|DT_VCENTER|DT_CENTER );
		}
		pdc->SelectStockObject(NULL_BRUSH);
	}
	if(nIDCtl==IDC_CODE)
	{
		CRect rct;
		col=0x404040;
	
		if ((lpDrawItemStruct->itemAction | ODA_SELECT) &&  (lpDrawItemStruct->itemState & ODS_SELECTED))
		{
			pdc->SetTextColor(0x8346D5);
		}
		else
		{
			pdc->SetTextColor(0xFFFFFF);
		}
		pdc->SetBkMode(TRANSPARENT);//Color(col);
		rct=lpDrawItemStruct->rcItem;
		pdc->FillSolidRect(&rct,col);
		pdc->SelectObject(&geoent);
		if((int)lpDrawItemStruct->itemID>-1)
		{
			lcode.GetText(lpDrawItemStruct->itemID,temp);
			pdc->DrawText(temp,-1,&rct,DT_SINGLELINE|DT_VCENTER|DT_LEFT );
		}
		pdc->SelectStockObject(NULL_BRUSH);
	}
	if(nIDCtl==IDC_QTE)
	{
		CRect rct;
		col=0x404040;
	
		if ((lpDrawItemStruct->itemAction | ODA_SELECT) &&  (lpDrawItemStruct->itemState & ODS_SELECTED))
		{
			pdc->SetTextColor(0x8346D5);
		}
		else
		{
			pdc->SetTextColor(0xFFFFFF);
		}
		pdc->SetBkMode(TRANSPARENT);//Color(col);
		rct=lpDrawItemStruct->rcItem;
		pdc->FillSolidRect(&rct,col);
		pdc->SelectObject(&geoent);
		if((int)lpDrawItemStruct->itemID>-1)
		{
			lqte.GetText(lpDrawItemStruct->itemID,temp);
			pdc->DrawText(temp,-1,&rct,DT_SINGLELINE|DT_VCENTER|DT_CENTER );
		}
		pdc->SelectStockObject(NULL_BRUSH);
		PostMessage(WM_USER+14,0,0);
	}
	if(nIDCtl==IDC_PTOT)
	{
		CRect rct;
		col=0x404040;
	
		if ((lpDrawItemStruct->itemAction | ODA_SELECT) &&  (lpDrawItemStruct->itemState & ODS_SELECTED))
		{
			pdc->SetTextColor(0x8346D5);
		}
		else
		{
			pdc->SetTextColor(0xFFFFFF);
		}
		pdc->SetBkMode(TRANSPARENT);//Color(col);
		rct=lpDrawItemStruct->rcItem;
		pdc->FillSolidRect(&rct,col);
		pdc->SelectObject(&geoent);
		if((int)lpDrawItemStruct->itemID>-1)
		{
			lptot.GetText(lpDrawItemStruct->itemID,temp);
			CRect rct=lpDrawItemStruct->rcItem;
			pdc->DrawText(temp,-1,&rct,DT_SINGLELINE|DT_VCENTER|DT_RIGHT );
		}
		pdc->SelectStockObject(NULL_BRUSH);
	}
	if(nIDCtl==IDC_VERSION)
	{
		pdc->SetBkMode(TRANSPARENT);
		pdc->SetTextColor(0x8346D5);
		pdc->SelectObject(&geostat);
		/*if(eflag==1)
			temp.Format("Concerto\n"+temp1+" %.2f ETC",fversion/100);//version
		else*/
		temp.Format("Concert\n"+txtc[52]+" %.3f",fversion/1000);
		pdc->DrawText(temp,-1,&lpDrawItemStruct->rcItem,DT_CENTER );
	}
	if(nIDCtl==IDC_NTT)
	{
		pdc->SetBkMode(TRANSPARENT);
		pdc->SetTextColor(0xFFFFFF);
		pdc->SelectObject(&geoent);
		pdc->FillSolidRect(&lpDrawItemStruct->rcItem,0x8346D5);
		rct=lpDrawItemStruct->rcItem;
		rct.DeflateRect(0,0,0,rct.Height()/2);//"Total ticket"
		pdc->DrawText(txtc[37],-1,&rct,DT_CENTER|DT_VCENTER|DT_SINGLELINE );
		pdc->SelectObject(&geoent);
		rct=lpDrawItemStruct->rcItem;
		rct.DeflateRect(0,rct.Height()/2,0,0);
		pdc->DrawText(txtsntt,-1,&rct,DT_CENTER|DT_VCENTER|DT_SINGLELINE );
	}
	if(nIDCtl==IDC_DA)
	{
		pdc->SetBkMode(TRANSPARENT);
		pdc->SetTextColor(0xFFFFFF);
		pdc->SelectObject(&geoent);
		pdc->FillSolidRect(&lpDrawItemStruct->rcItem,0x8346D5);
		rct=lpDrawItemStruct->rcItem;
		rct.DeflateRect(0,0,0,rct.Height()/2);
		if(hist==0)//"Ouverture"
		{
			temp=txtc[38];
			pdc->DrawText(temp,-1,&rct,DT_CENTER|DT_VCENTER|DT_SINGLELINE );
		}
		else//"Clôture"
		{
			temp=txtc[39];
			temp1.Format(" N° %u",HRAZ);
			pdc->DrawText(temp+temp1,-1,&rct,DT_CENTER|DT_VCENTER|DT_SINGLELINE );
		}
		pdc->SelectObject(&geodateoc);
		rct=lpDrawItemStruct->rcItem;
		rct.DeflateRect(0,rct.Height()/2,0,0);
		pdc->DrawText(txtsda.Left(txtsda.GetLength()-3),-1,&rct,DT_CENTER|DT_VCENTER|DT_SINGLELINE );
	}
	if(nIDCtl==IDC_CA)
	{
		pdc->SetBkMode(TRANSPARENT);
		pdc->SetTextColor(0xFFFFFF);
		pdc->SelectObject(&geoent);
		pdc->FillSolidRect(&lpDrawItemStruct->rcItem,0x8346D5);
		rct=lpDrawItemStruct->rcItem;
		rct.DeflateRect(0,0,0,rct.Height()/2);//"Total CA"
		pdc->DrawText(txtc[40],-1,&rct,DT_CENTER|DT_VCENTER|DT_SINGLELINE );
		pdc->SelectObject(&geoent);
		rct=lpDrawItemStruct->rcItem;
		rct.DeflateRect(0,rct.Height()/2,0,0);
		pdc->DrawText(txtsca,-1,&rct,DT_CENTER|DT_VCENTER|DT_SINGLELINE );
	}
	if(nIDCtl==IDC_NTA)
	{
		pdc->SetBkMode(TRANSPARENT);
		pdc->SetTextColor(0xFFFFFF);
		pdc->SelectObject(&geoent);
		pdc->FillSolidRect(&lpDrawItemStruct->rcItem,0x8346D5);
		rct=lpDrawItemStruct->rcItem;
		rct.DeflateRect(0,0,0,rct.Height()/2);//"Annulé"
		pdc->DrawText(txtc[41],-1,&rct,DT_CENTER|DT_VCENTER|DT_SINGLELINE );
		rct=lpDrawItemStruct->rcItem;
		rct.DeflateRect(0,rct.Height()/2,0,0);
		pdc->SelectObject(&geoent);
		pdc->DrawText(txtsnta,-1,&rct,DT_CENTER|DT_VCENTER|DT_SINGLELINE );
	}
	if(nIDCtl==IDC_ENT1)
	{//	titreresult.AddString(" N° TICKET	 DATE	 "+prxtext+"	  "+annultext);

		pdc->SetBkMode(TRANSPARENT);
		pdc->SetTextColor(0xFFFFFF);
		pdc->SelectObject(&geoent);
		pdc->FillSolidRect(&lpDrawItemStruct->rcItem,0x000000);
		rct=lpDrawItemStruct->rcItem;
		if(wsel==2)//"N° TICKET"
			temp=txtc[42];
		if(wsel==5)//GTZ
			temp=txtc[132];
		if(wsel==1)//"LIBELLE"
			temp=txtc[43];		
		pdc->DrawText(temp,-1,&rct,DT_CENTER|DT_VCENTER|DT_SINGLELINE );
	}
	if(nIDCtl==IDC_ENT2)
	{
		pdc->SetBkMode(TRANSPARENT);
		pdc->SetTextColor(0xFFFFFF);
		pdc->SelectObject(&geoent);//geostat
		pdc->FillSolidRect(&lpDrawItemStruct->rcItem,0x000000);
		rct=lpDrawItemStruct->rcItem;
		if(wsel==2)//"DATE"
			temp=txtc[44];
		if(wsel==5)//CLOTURE
			temp=txtc[140];
		if(wsel==1)//"QTE"
			temp=txtc[46];
		pdc->DrawText(temp,-1,&rct,DT_CENTER|DT_VCENTER|DT_SINGLELINE );
	}
	if(nIDCtl==IDC_ENT3)
	{
		pdc->SetBkMode(TRANSPARENT);
		pdc->SetTextColor(0xFFFFFF);
		pdc->SelectObject(&geoent);
		pdc->FillSolidRect(&lpDrawItemStruct->rcItem,0x000000);
		rct=lpDrawItemStruct->rcItem;
		if(wsel==2)//"PRIX"
			temp=txtc[47];
		if(wsel==1)//"P.T."
			temp=txtc[48];
		pdc->DrawText(temp,-1,&rct,DT_CENTER|DT_VCENTER|DT_SINGLELINE );
	}
	if(nIDCtl==IDC_ENT4)
	{
		pdc->SetBkMode(TRANSPARENT);
		pdc->SetTextColor(0xFFFFFF);
		pdc->SelectObject(&geoent);
		pdc->FillSolidRect(&lpDrawItemStruct->rcItem,0x000000);
		rct=lpDrawItemStruct->rcItem;
		if(wsel==2)//"ANNULE"
			temp=txtc[49];
		pdc->DrawText(temp,-1,&rct,DT_CENTER|DT_VCENTER|DT_SINGLELINE );
	}
	if(nIDCtl==IDC_NPAUTO)
	{
		pdc->SetBkMode(TRANSPARENT);
		rct=lpDrawItemStruct->rcItem;
		Graphics gr (pdc->m_hDC);
		RectF rctf(0,(REAL)rct.Height()/4,(REAL)(rct.Height()-rct.Height()/2),(REAL)(rct.Height()-rct.Height()/2));
		if(fadmin)
		{
			if(paravent)
			{
				gr.DrawImage(pcheck,rctf);
			}
			else
			{
				gr.DrawImage(pncheck,rctf);
			}//"Paravent"
			temp=txtc[50];
		}
		else
		{
			if(autoprint)
			{
				gr.DrawImage(pcheck,rctf);
			}
			else
			{
				gr.DrawImage(pncheck,rctf);
			}//"Ticket auto"
			temp=txtc[51];
		}
		pdc->SelectObject(&geodate);
		pdc->SetTextColor(0x0);
		rct.DeflateRect((rct.Height()-rct.Height()/2),0,0,0);
		pdc->FillSolidRect(&rct,0xFFFFFF);
		pdc->DrawText(temp,-1,&rct,DT_LEFT|DT_VCENTER|DT_SINGLELINE );
	}

	if(nIDCtl==IDC_NNAUTO)
	{
		pdc->SetBkMode(TRANSPARENT);
		rct=lpDrawItemStruct->rcItem;
		Graphics gr (pdc->m_hDC);
		RectF rctf(0,(REAL)rct.Height()/4,(REAL)(rct.Height()-rct.Height()/2),(REAL)(rct.Height()-rct.Height()/2));
		if(fadmin)
		{
			if(fprev)
			{
				gr.DrawImage(pcheck,rctf);
			}
			else
			{
				gr.DrawImage(pncheck,rctf);
			}//"Prévente"
			temp=txtc[8];
		}
		else
		{
			if(autonews)
			{
				gr.DrawImage(pcheck,rctf);
			}
			else
			{
				gr.DrawImage(pncheck,rctf);
			}//"Impression journal"
			temp=txtc[53];
		}
		pdc->SetTextColor(0x0);
		pdc->SelectObject(&geodate);
		rct.DeflateRect(rct.Height()-rct.Height()/2,0,0,0);
		pdc->FillSolidRect(&rct,0xFFFFFF);
		pdc->DrawText(temp,-1,&rct,DT_LEFT|DT_VCENTER|DT_SINGLELINE );
	}
	if(nIDCtl==IDC_NVHORAIRE)
	{
		pdc->SetBkMode(TRANSPARENT);
		rct=lpDrawItemStruct->rcItem;
		Graphics gr (pdc->m_hDC);
		RectF rctf(0,(REAL)rct.Height()/4,(REAL)(rct.Height()-rct.Height()/2),(REAL)(rct.Height()-rct.Height()/2));
		if(horaire)
		{
			if(valhor)
			{
				gr.DrawImage(pcheck,rctf);
			}
			else
			{
				gr.DrawImage(pncheck,rctf);
			}
		}
		pdc->SetTextColor(0x0);
		pdc->SelectObject(&geodate);
		rct.DeflateRect(rct.Height()-rct.Height()/2,0,0,0);
		pdc->FillSolidRect(&rct,0xFFFFFF);
		pdc->DrawText(txtc[54],-1,&rct,DT_LEFT|DT_VCENTER|DT_SINGLELINE );
	}
	if(nIDCtl==IDC_NETC)
	{
		pdc->SetBkMode(TRANSPARENT);
		rct=lpDrawItemStruct->rcItem;
		Graphics gr (pdc->m_hDC);
		RectF rctf(0,(REAL)rct.Height()/4,(REAL)(rct.Height()-rct.Height()/2),(REAL)(rct.Height()-rct.Height()/2));
		if(fadmin)
		{
			temp=txtc[56];
			if(eflag==1)
			{
				gr.DrawImage(pcheck,rctf);
			}
			else
			{
				gr.DrawImage(pncheck,rctf);
			}
		}
		else
		{
			temp=txtc[138];
			if(exoflag==1)
			{
				gr.DrawImage(pcheck,rctf);
			}
			else
			{
				gr.DrawImage(pncheck,rctf);
			}

		}
		pdc->SetTextColor(0x0);
		pdc->SelectObject(&geodate);
		rct.DeflateRect(rct.Height()-rct.Height()/2,0,0,0);
		pdc->FillSolidRect(&rct,0xFFFFFF);
		pdc->DrawText(temp,-1,&rct,DT_LEFT|DT_VCENTER|DT_SINGLELINE );
	}
	if(nIDCtl==IDC_NVALPAGE)
	{
		pdc->SetBkMode(TRANSPARENT);
		rct=lpDrawItemStruct->rcItem;
		Graphics gr (pdc->m_hDC);
		RectF rctf(0,(REAL)rct.Height()/4,(REAL)(rct.Height()-rct.Height()/2),(REAL)(rct.Height()-rct.Height()/2));
		if(valpage)
		{
			gr.DrawImage(pcheck,rctf);
		}
		else
		{
			gr.DrawImage(pncheck,rctf);
		}
		pdc->SetTextColor(0x0);
		pdc->SelectObject(&geodate);
		rct.DeflateRect(rct.Height()-rct.Height()/2,0,0,0);
		pdc->FillSolidRect(&rct,0xFFFFFF);
		pdc->DrawText(txtc[57],-1,&rct,DT_LEFT|DT_VCENTER|DT_SINGLELINE );
	}
	if(nIDCtl==IDC_QR)
	{
		Graphics gr (pdc->m_hDC);
		rct=lpDrawItemStruct->rcItem;
		RectF rctf(0,(REAL)rct.Height()/4,(REAL)(rct.Height()-rct.Height()/2),(REAL)(rct.Height()-rct.Height()/2));		
		gr.DrawImage(pqr,rctf);
	}
	if(nIDCtl==IDC_QRPHONE)
	{
		Graphics gr (pdc->m_hDC);
		rct=lpDrawItemStruct->rcItem;
		ImageAttributes ima;
		Color lowerColor;
		Color upperColor;
		lowerColor.SetFromCOLORREF(0xEEEEEE);
		upperColor.SetFromCOLORREF(0xFFFFFF);
		ima.SetColorKey( lowerColor, upperColor,ColorAdjustTypeDefault );
		RectF rctf(0,0,(REAL)rct.Width(),(REAL)rct.Height());
		Bitmap bitm((HBITMAP)hphqr,NULL);
		gr.DrawImage(&bitm,rctf,0,0,(REAL)bitm.GetWidth(),(REAL)bitm.GetHeight(),UnitPixel,&ima,NULL,NULL);
	}
	if(nIDCtl==IDC_NVALMIX)
	{
		pdc->SetBkMode(TRANSPARENT);
		rct=lpDrawItemStruct->rcItem;
		Graphics gr (pdc->m_hDC);
		RectF rctf(0,(REAL)rct.Height()/4,(REAL)(rct.Height()-rct.Height()/2),(REAL)(rct.Height()-rct.Height()/2));
		if(fadmin)
		{
			if(nvalmix)
			{
				gr.DrawImage(pcheck,rctf);
			}
			else
			{
				gr.DrawImage(pncheck,rctf);
			}
			pdc->SetTextColor(0x0);
			pdc->SelectObject(&geodate);
			rct.DeflateRect(rct.Height()-rct.Height()/2,0,0,0);
			pdc->FillSolidRect(&rct,0xFFFFFF);
			pdc->DrawText(txtc[131],-1,&rct,DT_LEFT|DT_VCENTER|DT_SINGLELINE );
		}
		else
			if (afmode)
			{
				if(valscr)
				{
					gr.DrawImage(pcheck,rctf);
				}
				else
				{
					gr.DrawImage(pncheck,rctf);
				}
				pdc->SetTextColor(0x0);
				pdc->SelectObject(&geodate);
				rct.DeflateRect(rct.Height()-rct.Height()/2,0,0,0);
				pdc->FillSolidRect(&rct,0xFFFFFF);
				pdc->DrawText(txtc[158],-1,&rct,DT_LEFT|DT_VCENTER|DT_SINGLELINE );//Veille
			}
	}
	if(nIDCtl==IDC_NVALPWD)
	{
		pdc->SetBkMode(TRANSPARENT);
		rct=lpDrawItemStruct->rcItem;
		Graphics gr (pdc->m_hDC);
		RectF rctf(0,(REAL)rct.Height()/4,(REAL)(rct.Height()-rct.Height()/2),(REAL)(rct.Height()-rct.Height()/2));
		if(valpwd)
		{
			gr.DrawImage(pcheck,rctf);
		}
		else
		{
			gr.DrawImage(pncheck,rctf);
		}
		pdc->SetTextColor(0x0);
		pdc->SelectObject(&geodate);
		rct.DeflateRect(rct.Height()-rct.Height()/2,0,0,0);
		pdc->FillSolidRect(&rct,0xFFFFFF);
		pdc->DrawText(txtc[58],-1,&rct,DT_LEFT|DT_VCENTER|DT_SINGLELINE );
	}
	if(nIDCtl==IDC_NVALPLACE)
	{
		pdc->SetBkMode(TRANSPARENT);
		rct=lpDrawItemStruct->rcItem;
		Graphics gr (pdc->m_hDC);
		RectF rctf(0,(REAL)rct.Height()/4,(REAL)(rct.Height()-rct.Height()/2),(REAL)(rct.Height()-rct.Height()/2));
		if(nvalplace)
		{
			gr.DrawImage(pcheck,rctf);
		}
		else
		{
			gr.DrawImage(pncheck,rctf);
		}
		pdc->SetTextColor(0x0);
		pdc->SelectObject(&geodate);
		rct.DeflateRect(rct.Height()-rct.Height()/2,0,0,0);
		pdc->FillSolidRect(&rct,0xFFFFFF);
		pdc->DrawText(txtc[59],-1,&rct,DT_LEFT|DT_VCENTER|DT_SINGLELINE );
	}
	if(nIDCtl==IDC_VALPLACE)
	{
		pdc->SetBkMode(TRANSPARENT);
		rct=lpDrawItemStruct->rcItem;
		Graphics gr (pdc->m_hDC);
		RectF rctf(0,(REAL)rct.Height()/4,(REAL)(rct.Height()-rct.Height()/2),(REAL)(rct.Height()-rct.Height()/2));
		if(valplace)
		{
			gr.DrawImage(pcheck,rctf);
		}
		else
		{
			gr.DrawImage(pncheck,rctf);
		}
		pdc->SetTextColor(0x0);
		pdc->SelectObject(&geodate);
		rct.DeflateRect(rct.Height()-rct.Height()/2,0,0,0);
		pdc->FillSolidRect(&rct,0xFFFFFF);
		pdc->DrawText(txtc[59],-1,&rct,DT_LEFT|DT_VCENTER|DT_SINGLELINE );
	}
	if(nIDCtl==IDC_VALACTIF)
	{
		pdc->SetBkMode(TRANSPARENT);
		rct=lpDrawItemStruct->rcItem;
		Graphics gr (pdc->m_hDC);
		RectF rctf(0,(REAL)rct.Height()/4,(REAL)(rct.Height()-rct.Height()/2),(REAL)(rct.Height()-rct.Height()/2));
		if(!valactif)
		{
			gr.DrawImage(pcheck,rctf);
		}
		else
		{
			gr.DrawImage(pncheck,rctf);
		}
		pdc->SetTextColor(0x0);
		pdc->SelectObject(&geodate);
		rct.DeflateRect(rct.Height()-rct.Height()/2,0,0,0);
		pdc->FillSolidRect(&rct,0xFFFFFF);
		pdc->DrawText(txtc[133],-1,&rct,DT_LEFT|DT_VCENTER|DT_SINGLELINE );
	}
	if(nIDCtl==IDC_VALMIX)
	{
		pdc->SetBkMode(TRANSPARENT);
		rct=lpDrawItemStruct->rcItem;
		Graphics gr (pdc->m_hDC);
		RectF rctf(0,(REAL)rct.Height()/4,(REAL)(rct.Height()-rct.Height()/2),(REAL)(rct.Height()-rct.Height()/2));
		if(valmix)
		{
			gr.DrawImage(pcheck,rctf);
		}
		else
		{
			gr.DrawImage(pncheck,rctf);
		}
		pdc->SetTextColor(0x0);
		pdc->SelectObject(&geodate);
		rct.DeflateRect(rct.Height()-rct.Height()/2,0,0,0);
		pdc->FillSolidRect(&rct,0xFFFFFF);
		pdc->DrawText(txtc[131],-1,&rct,DT_LEFT|DT_VCENTER|DT_SINGLELINE );
	}
	if(nIDCtl==IDC_VALEXO)
	{
		pdc->SetBkMode(TRANSPARENT);
		rct=lpDrawItemStruct->rcItem;
		Graphics gr (pdc->m_hDC);
		RectF rctf(0,(REAL)rct.Height()/4,(REAL)(rct.Height()-rct.Height()/2),(REAL)(rct.Height()-rct.Height()/2));
		if(valexo>0)
		{
			gr.DrawImage(pcheck,rctf);
		}
		else
		{
			gr.DrawImage(pncheck,rctf);
			valexo=0;
		}
		pdc->SetTextColor(0x0);
		pdc->SelectObject(&geodate);
		rct.DeflateRect(rct.Height()-rct.Height()/2,0,0,0);
		pdc->FillSolidRect(&rct,0xFFFFFF);
		pdc->DrawText(txtc[92],-1,&rct,DT_LEFT|DT_VCENTER|DT_SINGLELINE );
	}
	if(nIDCtl==IDC_VALCBX)
	{
		pdc->SetBkMode(TRANSPARENT);
		rct=lpDrawItemStruct->rcItem;
		Graphics gr (pdc->m_hDC);
		CRect rcti=rct;//(rct.Height()/8,rct.Height()/8,(rct.Height()-rct.Height()/2),(rct.Height()-rct.Height()/4));
		rcti.DeflateRect(0,0,rct.Width()-(rct.Height()-rct.Height()/2),0);
		RectF rctf(0,(REAL)rct.Height()/4,(REAL)(rct.Height()-rct.Height()/2),(REAL)(rct.Height()-rct.Height()/2));
		
		gr.DrawImage(pncheck,rctf);
		pdc->SetTextColor(0x0);
		pdc->SelectObject(&geodate);
		if(cbx>0)
		{
			pl.GetText(cbx,temp);
			pdc->DrawText(temp,-1,&rcti,DT_CENTER|DT_VCENTER|DT_SINGLELINE );
		}
		rct.DeflateRect(rct.Height()-rct.Height()/2,0,0,0);
		pdc->FillSolidRect(&rct,0xFFFFFF);
		pdc->DrawText(txtc[25],-1,&rct,DT_LEFT|DT_VCENTER|DT_SINGLELINE );
	}
	if(nIDCtl==IDC_VALPASS)
	{
		pdc->SetBkMode(TRANSPARENT);
		rct=lpDrawItemStruct->rcItem;
		Graphics gr (pdc->m_hDC);
		RectF rctf(0,(REAL)rct.Height()/4,(REAL)(rct.Height()-rct.Height()/2),(REAL)(rct.Height()-rct.Height()/2));
		if(valpass>0)
		{
			gr.DrawImage(pcheck,rctf);
		}
		else
		{
			gr.DrawImage(pncheck,rctf);
		}
		pdc->SetTextColor(0x0);
		pdc->SelectObject(&geodate);
		rct.DeflateRect(rct.Height()-rct.Height()/2,0,0,0);
		pdc->FillSolidRect(&rct,0xFFFFFF);
		temp.Format(" %u ",valpass);
		if(valpass>1)
			temp=txtc[151]+temp+txtc[152];
		else
			temp=txtc[151];
		pdc->DrawText(temp,-1,&rct,DT_LEFT|DT_VCENTER|DT_SINGLELINE );
	}
	if(nIDCtl==IDC_VALENTRY)
	{
		pdc->SetBkMode(TRANSPARENT);
		rct=lpDrawItemStruct->rcItem;
		Graphics gr (pdc->m_hDC);
		RectF rctf(0,(REAL)rct.Height()/4,(REAL)(rct.Height()-rct.Height()/2),(REAL)(rct.Height()-rct.Height()/2));
		if(valentry)
		{
			gr.DrawImage(pcheck,rctf);
		}
		else
		{
			gr.DrawImage(pncheck,rctf);
		}
		pdc->SetTextColor(0x0);
		pdc->SelectObject(&geodate);
		rct.DeflateRect(rct.Height()-rct.Height()/2,0,0,0);
		pdc->FillSolidRect(&rct,0xFFFFFF);
		pdc->DrawText(txtc[4],-1,&rct,DT_LEFT|DT_VCENTER|DT_SINGLELINE );
	}
	if(nIDCtl==IDC_TEMGATE)// dessin transparent du témoin tourniquetTourniquet
	{
		CPen bar(PS_SOLID,2,0xFF);
		tgate.GetWindowTextA(temp);
		ImageAttributes ima;
		Color lowerColor;
		Color upperColor;
		lowerColor.SetFromCOLORREF(0xEEEEEE);
		upperColor.SetFromCOLORREF(0xFFFFFF);
		ima.SetColorKey( lowerColor, upperColor,ColorAdjustTypeDefault );
		Bitmap bitm((HBITMAP)hrgate,NULL);
		Graphics gr (pdc->m_hDC);
		rct=lpDrawItemStruct->rcItem;
		if(GATECON==0)
		{
			pdc->SelectObject(&bar);// On met une croix rouge sur la connexion
			pdc->MoveTo((rct.left+25)*rct.Width()/64,(rct.top+42)*rct.Height()/64);
			pdc->LineTo((rct.left+38)*rct.Width()/64,(rct.top+57)*rct.Height()/64);
			pdc->MoveTo((rct.left+25)*rct.Width()/64,(rct.top+57)*rct.Height()/64);
			pdc->LineTo((rct.left+38)*rct.Width()/64,(rct.top+42)*rct.Height()/64);
		}
		RectF rctf(0,0,(REAL)rct.Width(),(REAL)rct.Height());
		gr.DrawImage(&bitm,rctf,0,0,(REAL)bitm.GetWidth(),(REAL)bitm.GetHeight(),UnitPixel,&ima,NULL,NULL);
		gr.Flush( FlushIntentionSync );
	}

	if(nIDCtl==IDC_TEMNET)// dessin transparent du témoin WEB
	{
		tnet.GetWindowTextA(temp);
		if(temp=="HRDN")
			hr=hrnet;
		if(temp=="HRSR")
			hr=hser;
		if(temp=="HRAU")
			hr=haut;
		ImageAttributes ima;
		Color lowerColor;
		Color upperColor;
		lowerColor.SetFromCOLORREF(0xEEEEEE);
		upperColor.SetFromCOLORREF(0xFFFFFF);
		ima.SetColorKey( lowerColor, upperColor,ColorAdjustTypeDefault );
		Bitmap bitm((HBITMAP)hr,NULL);

		Graphics gr (pdc->m_hDC);
		rct=lpDrawItemStruct->rcItem;
		RectF rctf(0,0,(REAL)rct.Width(),(REAL)rct.Height());
		gr.DrawImage(&bitm,rctf,0,0,(REAL)bitm.GetWidth(),(REAL)bitm.GetHeight(),UnitPixel,&ima,NULL,NULL);
	}
	if(nIDCtl==IDC_TEMWEB)// dessin transparent du témoin radio
	{
		hr=hweb;
		ImageAttributes ima;
		Color lowerColor;
		Color upperColor;
		lowerColor.SetFromCOLORREF(0xEEEEEE);
		upperColor.SetFromCOLORREF(0xFFFFFF);
		ima.SetColorKey( lowerColor, upperColor,ColorAdjustTypeDefault );
		Bitmap bitm((HBITMAP)hr,NULL);
		Graphics gr (pdc->m_hDC);
		rct=lpDrawItemStruct->rcItem;
		RectF rctf(0,0,(REAL)rct.Width(),(REAL)rct.Height());
		gr.DrawImage(&bitm,rctf,0,0,(REAL)bitm.GetWidth(),(REAL)bitm.GetHeight(),UnitPixel,&ima,NULL,NULL);
	}

	if(nIDCtl==IDC_TEMCONTROL)// dessin transparent du témoin radio
	{
		CPen bar(PS_SOLID,2,0xFF);
		tcontrol.GetWindowTextA(temp);
		rct=lpDrawItemStruct->rcItem;
		if(temp=="HRDV")
			hr=hrdv;
		else
			if(temp=="HRDB")
				hr=hrdb;
			else
				if(temp=="HRDR")
					hr=hrdr;
				else
					if(temp=="HRDC")
					{
						if(SEARCH)
							hr=hrdc;
						else
						{
							hr=hscanblue;
							pdc->SelectObject(&bar);// On met une croix rouge sur la connexion
							pdc->MoveTo((rct.left+25)*rct.Width()/64,(rct.top+42)*rct.Height()/64);
							pdc->LineTo((rct.left+38)*rct.Width()/64,(rct.top+57)*rct.Height()/64);
							pdc->MoveTo((rct.left+25)*rct.Width()/64,(rct.top+57)*rct.Height()/64);
							pdc->LineTo((rct.left+38)*rct.Width()/64,(rct.top+42)*rct.Height()/64);
						}
					}
					else
						if(temp=="HRDRED")
							hr=hrdred;
						else
							if(temp=="HRDVERT")
								hr=hrdvert;
							else
								if(temp=="HRCONTROL")
									hr=hctn;
								else
									if(temp=="SCANUSB")
										hr=hscanusb;
									else
										if(temp=="SCANBLUE")
											hr=hscanblue;
										else
											hr=NULL;
		ImageAttributes ima;
		Color lowerColor;
		Color upperColor;
		lowerColor.SetFromCOLORREF(0xEEEEEE);
		upperColor.SetFromCOLORREF(0xFFFFFF);
		ima.SetColorKey( lowerColor, upperColor,ColorAdjustTypeDefault );
		Bitmap bitm((HBITMAP)hr,NULL);

		Graphics gr (pdc->m_hDC);
		RectF rctf(0,0,(REAL)rct.Width(),(REAL)rct.Height());
		gr.DrawImage(&bitm,rctf,0,0,(REAL)bitm.GetWidth(),(REAL)bitm.GetHeight(),UnitPixel,&ima,NULL,NULL);
		gr.Flush( FlushIntentionSync );
	}
	//CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);

}

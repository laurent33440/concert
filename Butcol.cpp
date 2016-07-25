#include "stdafx.h"
#include "Concerto.h"
#include "ConcertoDlg.h"
#include "atlimage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void CConcertoDlg::DrawBoutonArticle(int touchesel)// Dessine les boutons d'entree
{
	int i;
	float x;
	float y;
	float largeur;//
	float hauteur;//
	//Boutons ARTICLES ENTRE/SORTIE
	if(wsel==4)//Control
	{
		largeur=ltou+ltou/4+eltou/4;
		hauteur= hto;//5.1);
	}
	else//Accueil
	{
		if(wsel==0||wsel==1||wsel==3)
		{
			if(NAPP==12)
			{
				largeur=lto;
				hauteur= 4*hto/3;//5.1);//
			}
			else
			{
				if(NAPP==16)
				{
					largeur=lto;
					hauteur= hto;//5.1);//
				}
				else
				{
					if((afmode==1&&wsel==3)||afmode==0)
					{
						largeur=4*lto/3;
						hauteur= 4*hto/3;
					}
					else
					{
						if(afmode==1&&wsel==1)
						{
							largeur=5*lto/3;
							hauteur= 4*hto/3;
						}
					}
				}
			}
		}
	}

	x=elto;
	y=ohto;
	i=0;
	do
	{
		if((wsel==3&&afmode==1&&etc==1)||(wsel==3&&(seltouche==i||touchesel==i))||(wsel==4)||(wsel==1&&touchesel==i))
			((CButton*)GetDlgItem(IDC_ART1+i))->SetWindowPos(&wndBottom,(int)x,(int)y,(int)largeur,(int)hauteur,SWP_HIDEWINDOW);
		((CButton*)GetDlgItem(IDC_ART1+i))->SetWindowPos(&wndBottom,(int)x,(int)y,(int)largeur,(int)hauteur,SWP_SHOWWINDOW);
		i++;
		x+=largeur+elto;
		if(((x>4*largeur)&&(wsel==4))||((x>4*largeur)&&(wsel==0||wsel==1||wsel==3)&&(NAPP==16||NAPP==12))||((x>3*largeur)&&(wsel==0||wsel==1||wsel==3)&&NAPP==9))
		{
			if(wsel==0||wsel==1||wsel==3)
			{
				x=olto;
				y+=hauteur+ehto;
			}
			else
			{
				x=(float)wlargeur/300;
				y+=hauteur+((float)whauteur/300);
			}
		}
	}
	while((i<NAPP&&(wsel==1||wsel==3))||(i<16&&(wsel==4)));
	//seltouche=touchesel;
}

void CConcertoDlg::DrawBoutonQuitter(CString txt)// Dessine la fenetre de vente
{
	int x;
	int y;
	int largeur;
	int hauteur;
	if(wsel==1)
		largeur=(int)((float)wlargeur*3.3/19.5);	
	else
		largeur=(int)((float)wlargeur*3.0/19.5);	
	if(wsel==1)
		hauteur=(int)((float)whauteur*2.5/27);			
	else
		hauteur=(int)((float)whauteur*2.3/27);			
	if(wsel==1)
		x=(int)((float)wlargeur*16.3/19.5);
	else
		x=(int)((float)wlargeur*16.3/19.5);
	if(wsel==1)
		y=(int)((float)whauteur*24.0/27);
	else
		y=(int)((float)whauteur*0.2/27);
	butquitter.SetWindowPos(&wndBottom,x,y,largeur,hauteur,SWP_SHOWWINDOW);

}
void CConcertoDlg::DrawFamilleArticle()// Dessine les familles d'entree
{
	int i;
	int nfammax;
	int nrubmax;
	double x;
	double xr;
	double y;
	double largeur;//
	double hauteur;//
	double rhauteur;//
	double rlargeur;//
	//Boutons famille ENTRE/SORTIE

	i=0;
	do
	{
		((CButton*)GetDlgItem(IDC_ART1+i))->ShowWindow(0);
		i++;
	}
	while(i<16);
	i=0;
	do
	{
		((CButton*)GetDlgItem(IDC_0+i))->ShowWindow(0);
		i++;
	}
	while(i<12);
	i=0;
	do
	{
		((CButton*)GetDlgItem(IDC_FAM1+i))->ShowWindow(0);
		i++;
	}
	while(i<3);
	i=0;
	do
	{
		((CButton*)GetDlgItem(IDC_RUB1+i))->ShowWindow(0);
		i++;
	}
	while(i<3);
	nfammax=3;
	i=0;
	x=13*lto/8;//elto;
	xr=x;
	y=ohto;
	largeur=rlargeur=7*lto/3;
	hauteur=rhauteur= 4*hto/3;
	if(selfam==0)
	{
		do
		{
			if(selfam==i+1||selfam==0)
				((CButton*)GetDlgItem(IDC_FAM1+i))->SetWindowPos(&wndBottom,(int)x,(int)y,(int)largeur,(int)hauteur,SWP_SHOWWINDOW);
			i++;
			y+=hauteur+2*ehto;
		}
		while(i<nfammax);
	}
	else
		if(selfam>0&&selrub==0)
		{
			x=(float)(((float)wlargeur*1.5/45));
			y=(double)((double)whauteur*24.5/27);
			largeur=((float)wlargeur*3.0/19.5);	
			hauteur=((float)whauteur*2.3/27);
			breturn.SetWindowPos(&wndBottom,(int)x,(int)y,(int)largeur,(int)hauteur,SWP_SHOWWINDOW);

			/*x=(float)(((float)wlargeur*1.5/45));
			y=(double)((float)whauteur*24.5/27);
			largeur=4*lto/3;
			hauteur= 2*hto/3;
			((CButton*)GetDlgItem(IDC_FAM1+selfam-1))->SetWindowPos(&wndBottom,(int)x,(int)y,(int)largeur,(int)hauteur,SWP_SHOWWINDOW);
			*/

		}
	y=ohto;
	i=0;
	nrubmax=3;
	if(selfam>0&&selrub==0)
	{
		do	// dessine les icones de rubrique
		{
			if((selrub==i+1||selrub==0)&&selfam>0)
				((CButton*)GetDlgItem(IDC_RUB1+i))->SetWindowPos(&wndBottom,(int)xr,(int)y,(int)rlargeur,(int)rhauteur,SWP_SHOWWINDOW);
			i++;
			y+=rhauteur+2*ehto;
		}
		while(i<nrubmax);
	}
	if(selfam>0&&selrub>0&&etc==0)// dessine les boutons retour et éventuellement bouton abandon
	{
		x=(float)(((float)wlargeur*1.5/45));
		y=(double)((float)whauteur*24.5/27);
		largeur=(int)((float)wlargeur*3.0/19.5);	
		hauteur=(int)((float)whauteur*2.3/27);
		breturn.SetWindowPos(&wndBottom,(int)x,(int)y,(int)largeur,(int)hauteur,SWP_SHOWWINDOW);
		
		if(lqte.GetCount()>0)
		{
			float x=(float)(((float)wlargeur*37/45));
			double y=(double)((float)whauteur*24.5/27);
			int largeur=(int)((float)wlargeur*3.0/19.5);	
			int hauteur=(int)((float)whauteur*2.3/27);
			bdel.SetWindowPos(&wndBottom,(int)x,(int)y,(int)largeur,(int)hauteur,SWP_SHOWWINDOW);
			
		}

		/*
		x=(float)(((float)wlargeur*1.5/45));
		y=(double)((float)whauteur*24.5/27);
		largeur=4*lto/3;
		hauteur= 2*hto/3;
		((CButton*)GetDlgItem(IDC_FAM1+selfam-1))->SetWindowPos(&wndBottom,(int)x,(int)y,(int)largeur,(int)hauteur,SWP_SHOWWINDOW);
		x=(float)((float)wlargeur*32/45);
		((CButton*)GetDlgItem(IDC_RUB1+selrub-1))->SetWindowPos(&wndBottom,(int)x,(int)y,(int)largeur,(int)hauteur,SWP_SHOWWINDOW);
		*/
		artrange=((selfam-1)*3)+(selrub-1);
		artnum=1;
		DrawBoutonArticle(17);
		DrawTicket();// GDI verif
		//DrawNumButton();
		DrawTotal();
		SetTimer(8,15000,NULL);
	}
}
void CConcertoDlg::DrawBoutonQuitterBorne(CString txt)// 
{
	int x;
	int y;
	int largeur;
	int hauteur;
	largeur=(int)((float)wlargeur*3.0/19.5);	
	hauteur=(int)((float)whauteur*2.3/27);			
	x=(int)((float)wlargeur*13.0/19.5);
	y=(int)((float)whauteur*0.2/27);
	butmanager.SetWindowPos(&wndBottom,x,y,largeur,hauteur,SWP_SHOWWINDOW);

}
void CConcertoDlg::DrawButtonManager()
{
	CString temp;	//BOUTON ENTREE
	int largeur;//
	int hauteur;//
	int x;
	int y;
	if(wsel<6&&wsel>1)
		largeur=(int)(ltou);//
	else
		if(wsel==1)
			largeur=(int)((float)wlargeur*3.3/19.5);			
		else
			largeur=(int)(2*ltou);//
	if(wsel==1)
		hauteur=(int)((float)whauteur*2.5/27);			
	else
		hauteur= (int)(htou/2);//
	if(wsel<6&&wsel>1)
		x=(int)(3*ltou+3*eltou+oltou);
	else
		if(wsel==1)
			x=(int)((float)wlargeur*13.0/19.5);
		else
			x=(int)(oltou);
	if(wsel==1)
		y=(int)((float)whauteur*24.0/27);
	else
		y=(int)((4.5*htou)+(5*ehtou)+ohnum);
	//BOUTON MANAGER
	butmanager.SetWindowPos(&wndBottom,x,y,largeur,hauteur,SWP_SHOWWINDOW);
	//BOUTON QUITTER APPLICATION
	butquitter.RedrawWindow(0,0,1|256|4);
	DrawBoutonQuitter(txtc[80]);//Quitter
	
	//wsel=1;
}

void CConcertoDlg::DrawPageCom()// Dessine la fenetre de vente
{
	CRect rect;
	float x;
	float y;
	if(afmode==0&&wsel==1)
	{
		wpage.SetWindowPos(&wndBottom,(int)(elnu),(int)((float)whauteur*24.5/27),(int)(2.6*lnu),(int)(0.8*hnu),SWP_SHOWWINDOW   );
		wpage.GetWindowRect(&rect);
		x=(float)(((float)rect.Width()*2/45)+olto);
		y=(float)(((float)rect.Height()*2/15)+(float)whauteur*24.5/27);
	}
	else
	{
		if(afmode==1||wsel>1)
		{
			wpage.SetWindowPos(&wndBottom,(int)(wlargeur*15/45),(int)((float)whauteur*22.5/27),(int)(2.6*lnu),(int)(0.8*hnu),SWP_SHOWWINDOW   );
			wpage.GetWindowRect(&rect);
			x=(float)(((float)wlargeur*15.5/45));
			y=(float)(((float)rect.Height()*2/15)+(float)whauteur*22.5/27);

		}
	}

	//BOUTON DE PAGE ARTICLE <
	butinf.SetWindowPos(&wndTop,(int)x,(int)y,(int)(4*(float)rect.Width()/15),(int)(11*(float)rect.Height()/15),SWP_SHOWWINDOW);
	butinf.GetWindowRect(&rctinf);

	//BOUTON DE PAGE ARTICLE >
	if(afmode==0&&wsel==1)
		x+=(float)((float)rect.Width()*29.0/45);
	else
		if(afmode==1||wsel>1)
			x+=(float)((float)rect.Width()*29.0/45);
	butsup.SetWindowPos(&wndTop,(int)x,(int)y,(int)(4*(float)rect.Width()/15),(int)(11*(float)rect.Height()/15),SWP_SHOWWINDOW);
	butsup.GetWindowRect(&rctsup);
	if(wsel==3&&master)
	{
		x=(float)(((float)rect.Width()*17/45)+olto);
		y=(float)(((float)rect.Height()*2/15)+(float)whauteur*22.5/27);
		bcopy.SetWindowPos(&wndTop,(int)x,(int)y,(int)(4*(float)rect.Width()/15),(int)(11*(float)rect.Height()/15),SWP_SHOWWINDOW);
		x=(float)((float)rect.Width()*106/45);
		bpaste.SetWindowPos(&wndTop,(int)x,(int)y,(int)(4*(float)rect.Width()/15),(int)(11*(float)rect.Height()/15),SWP_SHOWWINDOW);
	}
}
void CConcertoDlg::UpdatePageEntree()// Dessine le N° de page
{
	CString temp;
	if(wsel!=4)
	{
		temp=pag[artrange];
		txtpage=temp;
		wpage.SetWindowTextA(temp);
		wpage.RedrawWindow(0,0,1|256|RDW_ERASE);
	}
}
void CConcertoDlg::DrawNumButton()
{
	CRect rect;
	int i;
	float x;
	float y;
	float largeur;//
	float hauteur;//
	float clargeur;//
	CRect rct;
	//Boutons CHIFFRE

	largeur=clargeur=lnu;//
	x=olnu;
	y=ohnu;
	hauteur=hnu;
	i=0;
	do
	{
		rect.left=(int)x;
		rect.top=(int)y;
		rect.right=(int)(x+largeur);
		rect.bottom=(int)(y+hauteur);
		((CButton*)GetDlgItem(IDC_0+i))->SetWindowPos(&wndBottom,(int)x,(int)y,(int)clargeur,(int)hauteur,SWP_SHOWWINDOW);
		y+=hauteur+ehnu;
		i++;
		if(i==5)
		{
			y=ohnu;
			x=olnu+lnu+elnu;
		}
		if(i==10)
		{
			x=olnu;
			clargeur=2*lnu+elnu;
		}
	}
	while(i<11);
	// i pointe sur Item ENCAISSER
	DrawTotal();
	if(!autoprint&&afmode==0)
	{
		rect.left=(int)((float)wlargeur*6.5/19.5);
		rect.top=(int)y;
		rect.right=(int)((float)wlargeur*13/19.5);
		rect.bottom=(int)(y+hauteur);
		((CButton*)GetDlgItem(IDC_0+i))->SetWindowPos(&wndBottom,rect.left,rect.top,rect.Width(),rect.Height(),SWP_SHOWWINDOW);
	}
	else
		((CButton*)GetDlgItem(IDC_0+i))->SetWindowPos(&wndBottom,rect.left,rect.top,rect.Width(),rect.Height(),SWP_HIDEWINDOW);
}

void CConcertoDlg::DrawTotal()
{// Dessine et positionne le total dans la fenetre de vente
	CString temp;
	ntotal.SetWindowPos(&wndTop,(int)olnu,(int)((double)whauteur*2.6/27),(int)(2*lnu+elnu),(int)((double)whauteur*1.1/27),SWP_SHOWWINDOW   );
	ntotal.SetWindowTextA(txtc[82]);//TOTAL

	total.SetWindowPos(&wndTop,(int)olnu,(int)((double)whauteur*3.7/27),(int)(2*lnu+elnu),(int)((double)whauteur*4/27),SWP_SHOWWINDOW   );
	total.SetWindowTextA("");
}

void CConcertoDlg::DrawTicket()// Liste de vente
{
	int largeur;
	int he=(int)((double)whauteur*1.1/27);
	int x=(int)oltou;
	int ye=(int)((double)whauteur*2.6/27);
	int y=(int)((double)whauteur*3.7/27);
	int hauteur=(int)((double)whauteur*4/27);
	largeur=(int)((double)wlargeur*8.4/19.5);

	ent1.SetWindowPos(&wndTop,x,ye,largeur,he,SWP_SHOWWINDOW   );
	lcode.SetWindowPos(&wndTop,x,y,largeur,hauteur,SWP_SHOWWINDOW   );
	lcode.SetItemHeight(0,(UINT)(htou/6));
	
	x=(int)((double)wlargeur*8.5/19.5);
	largeur=(int)((double)wlargeur*2.2/19.5);
	ent2.SetWindowPos(&wndTop,x,ye,largeur,he,SWP_SHOWWINDOW   );
	lqte.SetWindowPos(&wndBottom,x,y,largeur,hauteur,SWP_SHOWWINDOW   );
	lqte.SetItemHeight(0,(UINT)(htou/6));

	x=(int)((double)wlargeur*10.7/19.5);
	largeur=(int)((double)wlargeur*3.3/19.5);
	ent3.SetWindowPos(&wndTop,x,ye,largeur,he,SWP_SHOWWINDOW   );
	lptot.SetWindowPos(&wndTop,x,y,largeur,hauteur,SWP_SHOWWINDOW   );
	lptot.SetItemHeight(0,(UINT)(htou/6));
	//scan="";*********************************************************************************************************************************************************
	nscan.SetWindowPos(&wndTop,rctscan.left,rctscan.top,rctscan.Width(),rctscan.Height(),SWP_HIDEWINDOW   );
}

void CConcertoDlg::DrawStaticConfig()
{
	CString num;
	CString temp;
	CString temp1;
	float sph=9*htou/40;
	float spl1=oltou+5*ltou/4+eltou ;
	float spl2=oltou+(6*ltou/4)+2*eltou ;
	float spl3 ;
	float spl4 ;
	float hs=(float)((float)whauteur*0.8/27);
	int he;
	int ye;
	int xe;
	int le;
	int x;
	int xn;
	int largeur;
	int slargeur;
	int shauteur;
	float yohnum=((float)whauteur/10);
	sgc.SetWindowPos(&wndTop,(int)(oltou),(int)(ohnum),(int)(5*ltou+4*eltou),(int)(2*htou+1*ehtou),SWP_SHOWWINDOW   );
	sgc.SetWindowTextA(txtc[97]);//Client
	x=0;
	largeur=(int)((float)wlargeur*4.7/19.5);
	xn=(int)((float)wlargeur*4.7/19.5);
	slargeur=(int)((float)wlargeur*10/19.5);
	shauteur=(int)((float)whauteur*0.8/27);

	nposte.SetWindowPos(&wndTop,x,(int)(yohnum+0.7*sph),largeur,(int)(hs),SWP_SHOWWINDOW   );
	nposte.SetWindowText(txtc[68]+" :");//Poste
	sposte.SetWindowPos(&wndTop,xn,(int)(yohnum+0.7*sph),slargeur/6,shauteur,SWP_SHOWWINDOW   );
	sposte.SetWindowText(poste);//Poste
	sposte.SetFont(&geodate,0);


	x=(int)((float)wlargeur*6.5/19.5);
	largeur=(int)((float)wlargeur*2.2/19.5);
	xn=(int)((float)wlargeur*8.7/19.5);
	slargeur=(int)((float)wlargeur*6.0/19.5);

	nprefix.SetWindowPos(&wndTop,x,(int)(yohnum+0.7*sph),largeur,(int)(hs),SWP_SHOWWINDOW   );
	nprefix.SetWindowText(txtc[159]+" :");//Prefixe
	sprefix.SetWindowPos(&wndTop,xn,(int)(yohnum+0.7*sph),slargeur,shauteur,SWP_SHOWWINDOW   );
	sprefix.SetWindowText(prefix);//Prefixe ordinateur
	sprefix.SetFont(&geodate,0);
	sprefix.LimitText(9);

	x=0;
	xn=(int)((float)wlargeur*4.7/19.5);
	largeur=(int)((float)wlargeur*4.7/19.5);
	slargeur=(int)((float)wlargeur*10/19.5);
	shauteur=(int)((float)whauteur*0.8/27);

	{
		nserveur.SetWindowPos(&wndTop,x,(int)(yohnum+1.6*sph),largeur,(int)(hs),SWP_SHOWWINDOW   );
		nserveur.SetWindowText(txtc[157]+" :");//Serveur
		sserveur.SetWindowPos(&wndTop,xn,(int)(yohnum+1.6*sph),slargeur,shauteur,SWP_SHOWWINDOW   );
		sserveur.SetWindowText(serveur);//Préfixe serveur
		sserveur.SetFont(&geodate,0);
	}
	nnom.SetWindowPos(&wndTop,x,(int)(yohnum+2.5*sph),largeur,(int)(hs),SWP_SHOWWINDOW   );
	nnom.SetWindowText(txtc[69]+" :");//Nom
	snom.SetWindowPos(&wndTop,xn,(int)(yohnum+2.5*sph),slargeur,shauteur,SWP_SHOWWINDOW   );
	snom.SetFont(&geodate,0);
	snom.LimitText(23);
	snom.SetWindowText(nom);
	nad1.SetWindowPos(&wndTop,x,(int)(yohnum+3.4*sph),largeur,(int)(hs),SWP_SHOWWINDOW   );
	nad1.SetWindowText(txtc[70]+" :");//Adresse 1
	sad1.SetWindowPos(&wndTop,xn,(int)(yohnum+3.4*sph),slargeur,shauteur,SWP_SHOWWINDOW   );
	sad1.SetFont(&geodate,0);
	sad1.LimitText(25);
	sad1.SetWindowText(adresse1);
	nad2.SetWindowPos(&wndTop,x,(int)(yohnum+4.3*sph),largeur,(int)(hs),SWP_SHOWWINDOW   );
	nad2.SetWindowText(txtc[71]+" :");//Adresse 2
	sad2.SetWindowPos(&wndTop,xn,(int)(yohnum+4.3*sph),4*slargeur/5,shauteur,SWP_SHOWWINDOW   );
	sad2.SetFont(&geodate,0);
	sad2.LimitText(25);
	sad2.SetWindowText(adresse2);
	nsir.SetWindowPos(&wndTop,x,(int)(yohnum+5.2*sph),largeur,(int)(hs),SWP_SHOWWINDOW   );
	nsir.SetWindowText(txtc[72]+" :");//Siret
	ssir.SetWindowPos(&wndTop,xn,(int)(yohnum+5.2*sph),4*slargeur/9,shauteur,SWP_SHOWWINDOW   );
	ssir.SetFont(&geodate,0);
	ssir.LimitText(16);
	ssir.SetWindowText(siret);
	nnaf.SetWindowPos(&wndTop,xn+(5*slargeur/9),(int)(yohnum+5.2*sph),5*largeur/9,(int)(hs),SWP_SHOWWINDOW   );
	nnaf.SetWindowText(txtc[95]+" :");//Naf
	snaf.SetWindowPos(&wndTop,xn+(5*slargeur/9)+(5*largeur/9),(int)(yohnum+5.2*sph),3*slargeur/16,shauteur,SWP_SHOWWINDOW   );
	snaf.SetFont(&geodate,0);
	snaf.LimitText(6);
	snaf.SetWindowText(naf);
	ndevise.SetWindowPos(&wndTop,x,(int)(yohnum+6.1*sph),largeur,(int)(hs),SWP_SHOWWINDOW   );
	ndevise.SetWindowText(txtc[73]+" :");//Devise

	slargeur=(int)((float)wlargeur*4/19.5);
	sdevise.SetWindowPos(&wndTop,xn,(int)(yohnum+6.1*sph),slargeur/2,shauteur,SWP_SHOWWINDOW   );
	sdevise.SetFont(&geodate,0);
	sdevise.SetWindowText(cur);
	ntva1.SetWindowPos(&wndTop,xn+slargeur/2,(int)(yohnum+6.1*sph),20*largeur/30,(int)(hs),SWP_SHOWWINDOW   );
	ntva1.SetWindowTextA(txtc[62]+" :");//TVA
	stva1.SetWindowPos(&wndTop,xn+(slargeur/2)+(20*largeur/30),(int)(yohnum+6.1*sph),slargeur/2,shauteur,SWP_SHOWWINDOW   );
	nlangue.SetWindowPos(&wndTop,xn+(slargeur/2)+(20*largeur/30)+(slargeur/2),(int)(yohnum+6.1*sph),20*largeur/30,(int)(hs),SWP_SHOWWINDOW   );
	nlangue.SetWindowText(txtc[87]+" :");//Langue
	slangue.SetWindowPos(&wndTop,xn+(slargeur/2)+(20*largeur/30)+(slargeur/2)+(20*largeur/30),(int)(yohnum+6.1*sph),slargeur,shauteur,SWP_SHOWWINDOW   );
	slangue.SetFont(&geodate,0);
	slangue.SetWindowText(langue);
	slargeur=(int)((float)wlargeur*10/19.5);
	nmentiont.SetWindowPos(&wndTop,0,(int)(yohnum+7*sph),largeur,(int)(hs),SWP_SHOWWINDOW   );
	nmentiont.SetWindowText(txtc[60]+" :");//Mention ticket
	smentiont.SetWindowPos(&wndTop,xn,(int)(yohnum+7*sph),slargeur,shauteur,SWP_SHOWWINDOW   );
	smentiont.SetFont(&geodate,0);
	smentiont.LimitText(35);
	smentiont.SetWindowText(mentiont);
	nmentionp.SetWindowPos(&wndTop,0,(int)(yohnum+7.9*sph),largeur,(int)(hs),SWP_SHOWWINDOW   );//8
	nmentionp.SetWindowText(txtc[61]+" :");//Mention prév.
	smentionp.SetWindowPos(&wndTop,xn,(int)(yohnum+7.9*sph),slargeur,shauteur,SWP_SHOWWINDOW   );
	smentionp.SetFont(&geodate,0);
	smentionp.LimitText(35);
	smentionp.SetWindowText(mentionp);
	x=(int)((float)wlargeur*6.5/19.5);
	largeur=(int)((float)wlargeur*2.2/19.5);
	xn=(int)((float)wlargeur*8.7/19.5);
	slargeur=(int)((float)wlargeur*6.0/19.5);
	xn=(int)xn+(4*slargeur/5);
	largeur=(int)((float)wlargeur*4.7/19.5);
	slargeur=(int)(slargeur/5);
	spays.SetWindowPos(&wndTop,xn,(int)(yohnum+4.3*sph),slargeur,shauteur,SWP_SHOWWINDOW   );
	spays.SetFont(&geodate,0);
	spays.SetWindowText(pays);
	if(TVA!="")
		stva1.SetWindowText(TVA+"%");
	else
		stva1.SetWindowText("");

	stva1.SetFont(&geodate,0);
	stva2.SetFont(&geodate,0);
	sval1.SetFont(&geodate,0);
	sval2.SetFont(&geodate,0);
	largeur=(int)((float)wlargeur*4.2/19.5);
	x=(int)((float)wlargeur*15.15/19.5);
	slargeur=(int)((float)wlargeur*3.8/19.5);
	int i;
	int j=0;
	for(i=0;i<5;i++)
	{
		if(lic[i]!="")
		{
			GetDlgItem(IDC_SLICENSE0+i)->SetWindowPos(&wndTop,x,(int)(ohnum+(int)((i+1)*sph)),slargeur,shauteur,SWP_SHOWWINDOW   );
			GetDlgItem(IDC_SLICENSE0+i)->SetFont(&geodate,0);
			GetDlgItem(IDC_SLICENSE0+i)->SetWindowText(lic[i]);
			j++;
		}
		else
			break;
	}
	if (fadmin)
	{
		if(i<5)
		{
			GetDlgItem(IDC_SLICENSE0+i)->SetWindowPos(&wndTop,x,(int)(ohnum+(int)((i+1)*sph)),slargeur,shauteur,SWP_SHOWWINDOW   );
			GetDlgItem(IDC_SLICENSE0+i)->SetFont(&geodate,0);
			GetDlgItem(IDC_SLICENSE0+i)->SetWindowText("");
			j++;
		}
	}
	xn=(int)((float)wlargeur*15.0/19.5);
	largeur=(int)((float)wlargeur*4.2/19.5);
	if(j>0)
	{
		nlic.SetWindowPos(&wndTop,xn,(int)(ohnum+(int)(0.3*sph)),largeur,(int)((j+0.5)*sph),SWP_SHOWWINDOW   );
		nlic.SetFont(&geodate,0);
		nlic.SetWindowTextA(txtc[63]);//Licenses
	}
	nexer.SetWindowPos(&wndTop,xn,(int)(yohnum+7*sph),largeur,(int)((1.8)*sph),SWP_SHOWWINDOW   );
	sexer.SetWindowPos(&wndTop,x,(int)(yohnum+(int)(7.7*sph)),slargeur,shauteur,SWP_SHOWWINDOW   );
	sexer.SetFont(&geodate,0);
	sexer.SetWindowText(exermois);

	sgl.SetWindowPos(&wndTop,(int)(oltou),(int)(ohnum+2*htou+1*ehtou),(int)(5*ltou+4*eltou),(int)(1*(htou/2)+2*ehtou),SWP_SHOWWINDOW   );
	sgl.SetWindowTextA(txtc[120]);//Logiciel
	spl1=oltou+ltou/4 ;
	spl2=oltou+(ltou/2)+1*eltou ;
	spl3=oltou+(10*ltou/4)+2*eltou ;
	spl4=oltou+(11*ltou/4)+3*eltou ;

	npauto.SetWindowPos(&wndTop,(int)(oltou+5*ltou/10+eltou),(int)(ohnum+9.3*sph),(int)(11*ltou/10),(int)(hs),SWP_SHOWWINDOW   );
	if(fadmin)
	{
		npauto.SetWindowText(txtc[50]);//"Paravent"
	}
	else
	{
		npauto.SetWindowText(txtc[51]);//"Ticket auto"
	}

	nnauto.SetWindowPos(&wndTop,(int)(oltou+5*ltou/10+eltou),(int)(ohnum+10.2*sph),(int)(11*ltou/10),(int)(hs),SWP_SHOWWINDOW   );
	if(fadmin)
	{
		nnauto.SetWindowText(txtc[8]);//"Prévente"
	}
	else
	{
		nnauto.SetWindowText(txtc[53]);//"Impression journal"
	}
	lcb.SetWindowPos(&wndTop,(int)(oltou+17*ltou/10+eltou),(int)(ohnum+9.4*sph),(int)(8*ltou/10),(int)(hs),SWP_HIDEWINDOW   );
	netc.SetWindowPos(&wndTop,(int)(oltou+20*ltou/10+eltou),(int)(ohnum+9.3*sph),(int)(4*ltou/10),(int)(hs),SWP_HIDEWINDOW   );
	if(fadmin)
	{
		//netc.SetWindowPos(&wndTop,(int)(oltou+20*ltou/10+eltou),(int)(ohnum+9.3*sph),(int)(4*ltou/10),(int)(hs),SWP_SHOWWINDOW   );
		lcb.SetWindowPos(&wndTop,(int)(oltou+17*ltou/10+eltou),(int)(ohnum+9.4*sph),(int)(8*ltou/10),(int)(hs),SWP_SHOWWINDOW   );
		lcb.SetFont(&geodate);
		lcb.SetCurSel(eflag);
		ltype.SetWindowPos(&wndTop,(int)(oltou+27*ltou/10+eltou),(int)(ohnum+9.4*sph),(int)(8*ltou/10),(int)(hs),SWP_SHOWWINDOW   );
		ltype.SetFont(&geodate);
		ltype.SetCurSel(master);
	}
	if((fprev&&!fadmin))
	{
		netc.SetWindowPos(&wndTop,(int)(oltou+20*ltou/10+eltou),(int)(ohnum+9.3*sph),(int)(7*ltou/10),(int)(hs),SWP_SHOWWINDOW   );
	}
	nvhor.SetWindowPos(&wndTop,(int)(oltou+27*ltou/10+eltou),(int)(ohnum+10.2*sph),(int)(7*ltou/10),(int)(hs),SWP_HIDEWINDOW   );
	if(fadmin&&fprev)
	{
		nvhor.SetWindowPos(&wndTop,(int)(oltou+27*ltou/10+eltou),(int)(ohnum+10.2*sph),(int)(7*ltou/10),(int)(hs),SWP_SHOWWINDOW   );
		nvhor.SetWindowText(txtc[54]);//"Horaire"
	}
	if(fadmin)
	{
		nvplace.SetWindowPos(&wndTop,(int)(oltou+38*ltou/10+eltou),(int)(ohnum+9.3*sph),(int)(5*ltou/10),(int)(hs),SWP_SHOWWINDOW   );
		nvplace.SetWindowText(txtc[7]);//"Place"
		nvmix.SetWindowPos(&wndTop,(int)(oltou+20*ltou/10+eltou),(int)(ohnum+10.2*sph),(int)(5*ltou/10),(int)(hs),SWP_SHOWWINDOW   );
		nvmix.SetWindowText(txtc[131]);//"Pack"
		nvpwd.SetWindowPos(&wndTop,(int)(oltou+38*ltou/10+eltou),(int)(ohnum+10.2*sph),(int)(5*ltou/10),(int)(hs),SWP_SHOWWINDOW   );
		nvpwd.SetWindowText(txtc[58]);//"Pwd"
	}
	else
	{
		if( afmode)
		{
			nvmix.SetWindowPos(&wndTop,(int)(oltou+20*ltou/10+eltou),(int)(ohnum+10.2*sph),(int)(5*ltou/10),(int)(hs),SWP_SHOWWINDOW   );
			nvmix.SetWindowText(txtc[158]);//"scr"
		}
		
	}/**/
	if(fadmin)
	{
		nvpage.SetWindowPos(&wndTop,(int)(oltou+45*ltou/10.2+eltou),(int)(ohnum+9.3*sph),(int)(7*ltou/10),(int)(hs),SWP_SHOWWINDOW   );
		nvpage.SetWindowText(txtc[57]);//"Page"
		lnbap.SetWindowPos(&wndTop,(int)(oltou+45*ltou/10.2+eltou),(int)(ohnum+10.4*sph),(int)(4*ltou/10),(int)(hs),SWP_SHOWWINDOW   );
		lnbap.SetFont(&geodate);
		if(afmode==0)
		{
			num.Format("%u",NAPP);
			lnbap.SetCurSel(lnbap.FindStringExact(0,num));
		}
		else
			lnbap.SetCurSel(lnbap.FindStringExact(0,"B"));
	}

	sgs.SetWindowPos(&wndTop,(int)(oltou),(int)(ohnum+(5*htou/2)+2*ehtou),(int)(5*ltou+4*eltou),(int)(1*htou/2),SWP_SHOWWINDOW   );
	sgs.SetWindowTextA(txtc[122]);//Sécurité
	spl1=oltou+3*ltou/2 ;

	sge.SetWindowPos(&wndTop,(int)(oltou),(int)(ohnum+3*htou+3*ehtou),(int)(5*ltou+4*eltou),(int)(2*htou+1*ehtou),SWP_SHOWWINDOW   );
	sge.SetWindowTextA(txtc[121]);//Historique
	spl1=oltou+3*ltou+2*eltou ;
	hs=(ohnum+3*htou+sph);

	esea.SetWindowPos(&wndTop,(int)(oltou+ehtou),(int)hs/*(ohnum+7*htou/2+3*ehtou)*/,(int)((14*ltou/5)),(int)(htou/3),SWP_SHOWWINDOW   );

	nan.SetWindowPos(&wndTop,(int)(oltou),(int)(ohnum+29*htou/8+3*ehtou),(int)(ltou),(int)(htou/3),SWP_SHOWWINDOW   );
	nan.SetWindowText(txtc[83]+" :");//Année
	nmois.SetWindowPos(&wndTop,(int)(oltou),(int)(ohnum+8*htou/2+3*ehtou),(int)(ltou),(int)(htou/3),SWP_SHOWWINDOW   );
	nmois.SetWindowText(txtc[84]+" :");//Mois
	san.SetWindowPos(&wndTop,(int)(oltou+ehtou+ltou),(int)(ohnum+29*htou/8+3*ehtou),(int)(ltou),(int)(htou/3),SWP_SHOWWINDOW   );
	smois.SetWindowPos(&wndTop,(int)(oltou+ehtou+ltou),(int)(ohnum+8*htou/2+3*ehtou),(int)(ltou),(int)(htou/3),SWP_SHOWWINDOW   );

	he=(int)((float)(htou/5));
	ye=(int)hs;
	xe=(int)(oltou+14*ltou/5+2*eltou);
	le=(int)(3*ltou/5);
	hs+=htou/5;
	ent1.SetWindowPos(&wndTop,xe,ye,le,he,SWP_SHOWWINDOW   );
	lprix.SetWindowPos(&wndTop,xe,(int)hs,le,(int)(8*htou/5),SWP_SHOWWINDOW   );
	xe=(int)(oltou+3*ltou+2*eltou+2*ltou/5);
	le=(int)(3*ltou/2+ltou/10);
	ent2.SetWindowPos(&wndTop,xe,ye,le,he,SWP_SHOWWINDOW   );
	lcancel.SetWindowPos(&wndTop,xe,(int)hs,le,(int)(8*htou/5),SWP_SHOWWINDOW   );
	sgs.SetFont(&geodate,1);
	sge.SetFont(&geodate,1);
	sgc.SetFont(&geodate,1);
	sgl.SetFont(&geodate,1);
	nexer.SetFont(&geodate,1);
}
void CConcertoDlg::DrawBoutonConfig()
{
	titretext="Billetterie";	
//BOUTON ENTREE
	int largeur;//
	int hauteur;//	
	largeur=(int)(2*ltou);//
	hauteur= (int)(htou/3);//

//BOUTON AFFICHER RESULTAT
	butprint.SetWindowPos(&wndTop,(int)(oltou+ltou/2),(int)(ohnum+9*htou/2+3*ehtou),largeur,hauteur,SWP_SHOWWINDOW   );
//BOUTON NOTICE
	//largeur=(int)(0.8*ltou);//
	//hauteur= (int)(5*htou/16);//
	//bimport.SetWindowPos(&wndTop,(int)(10*oltou+2*eltou+4*ltou/3),(int)(ohnum+43*(htou/16)),largeur,hauteur,SWP_HIDEWINDOW   );
//BOUTON RAZ
	largeur=(int)(1*ltou);//0.7
	hauteur= (int)(5*htou/16);//
	if(fadmin==1)
		butraz.SetWindowPos(&wndTop,(int)(10*oltou+3*eltou+2.3*ltou),(int)(ohnum+43*(htou/16)),largeur,hauteur,SWP_SHOWWINDOW   );
	else
		butraz.SetWindowPos(&wndTop,(int)(10*oltou+3*eltou+2.3*ltou),(int)(ohnum+43*(htou/16)),largeur,hauteur,SWP_HIDEWINDOW   );
//BOUTON BUREAU WINDOWS
	if(fadmin==1)
	{
		largeur=(int)(6.21*ltou/12);//
		hauteur= (int)(5*htou/16);//
		bbur.SetWindowPos(&wndTop,(int)(oltou+(55*ltou/16)+3*eltou),(int)(ohnum+43*(htou/16)),largeur,hauteur,SWP_SHOWWINDOW   );
	}
//BOUTON PRINTER
	if(fadmin==1)
	{
		largeur=(int)(6.21*ltou/12);//
		hauteur= (int)(5*htou/16);//
		bprinter.SetWindowPos(&wndTop,(int)(oltou+(55*ltou/16)+3*eltou+largeur),(int)(ohnum+43*(htou/16)),largeur,hauteur,SWP_SHOWWINDOW   );
	}
//BOUTON RESEAU
	if(fadmin)
	{
		largeur=(int)(6.21*ltou/12);//
		hauteur= (int)(5*htou/16);//
		bnet.SetWindowPos(&wndTop,(int)(oltou+(55*ltou/16)+3*eltou+2*largeur),(int)(ohnum+43*(htou/16)),largeur,hauteur,SWP_SHOWWINDOW   );
	}
// BOUTON CODE MANAGER OU REVENDEUR
	largeur=(int)(2*ltou/3);//
	hauteur= (int)(5*htou/16);//
	if(!fadmin)
	{	
		bman.SetWindowPos(&wndTop,(int)(2*oltou),(int)(ohnum+43*(htou/16)),4*largeur/3,hauteur,SWP_SHOWWINDOW   );
		buser.SetWindowPos(&wndTop,(int)(3*oltou+4*largeur/3),(int)(ohnum+43*(htou/16)),4*largeur/3,hauteur,SWP_SHOWWINDOW);
	}
	else
	{
		if (fadmin)
		{
			bman.SetWindowPos(&wndTop,(int)(2*oltou),(int)(ohnum+43*(htou/16)),4*largeur/3,hauteur,SWP_SHOWWINDOW   );
		}
		
		if(fadmin&&eflag==1&&master)
			buser.SetWindowPos(&wndTop,(int)(3*oltou+4*largeur/3),(int)(ohnum+43*(htou/16)),4*largeur/3,hauteur,SWP_HIDEWINDOW   ); //RAZ CB ETC obsolette 
		else
			buser.SetWindowPos(&wndTop,(int)(3*oltou+4*largeur/3),(int)(ohnum+43*(htou/16)),4*largeur/3,hauteur,SWP_HIDEWINDOW   );
	}/**/
	// BOUTON CHARGEMENT LOGO
	largeur=(int)(2*ltou/3);//
	hauteur= (int)(5*htou/16);//
	blogo.SetWindowPos(&wndTop,(int)(10*oltou+1*eltou+5*ltou/3),(int)(ohnum+43*(htou/16)),largeur,hauteur,SWP_SHOWWINDOW   );
}

void CConcertoDlg::DrawBoutonResult()
{
	CString temp1;
	CString temp;
	CRect rct;
	int x;
	int ys;
	int ye;
	int y;
	int he;//
	int hs;//
	int largeur;//
	int hauteur;//	
	ldate.ResetContent();
	lprix.ResetContent();
	lntick.ResetContent();
	lcancel.ResetContent();
	he=(int)((float)whauteur*1/27);//
	hs=(int)((float)whauteur*1.9/27);//
	hauteur=(int)((float)whauteur*11.3/27);
	x=(int)oltou;
	ye=(int)((float)whauteur*3.2/27);
	y=(int)((float)whauteur*4.3/27);
	ys=y+hauteur+(int)((float)whauteur*0.2/27);
	largeur=(int)((float)wlargeur*6.9/20);//
	ent1.SetWindowPos(&wndTop,x,ye,largeur,he,SWP_SHOWWINDOW   );
	lntick.SetWindowPos(&wndTop,x,y,largeur,hauteur,SWP_SHOWWINDOW   );
	lntick.SetItemHeight(0,(UINT)(htou/6));
	if(code!=codeuser)
		sntt.SetWindowPos(&wndTop,x,ys,largeur,hs,SWP_SHOWWINDOW   );
	x=x+largeur+(int)((float)wlargeur*0.1/20);
	largeur=(int)((float)wlargeur*5.6/20);//
	ent2.SetWindowPos(&wndTop,x,ye,largeur,he,SWP_SHOWWINDOW   );
	ldate.SetWindowPos(&wndTop,x,y,largeur,hauteur,SWP_SHOWWINDOW   );
	ldate.SetItemHeight(0,(UINT)(htou/6));
	if(code!=codeuser)
		sda.SetWindowPos(&wndTop,x,ys,largeur,hs,SWP_SHOWWINDOW   );
	x=x+largeur+(int)((float)wlargeur*0.1/20);
	largeur=(int)((float)wlargeur*3.9/20);//
	ent3.SetWindowPos(&wndTop,x,ye,largeur,he,SWP_SHOWWINDOW   );
	lprix.SetWindowPos(&wndTop,x,y,largeur,hauteur,SWP_SHOWWINDOW   );
	lprix.SetItemHeight(0,(UINT)(htou/6));
	if(code!=codeuser)
		sca.SetWindowPos(&wndTop,x,ys,largeur,hs,SWP_SHOWWINDOW   );
	x=x+largeur+(int)((float)wlargeur*0.1/20);
	largeur=(int)((float)wlargeur*3.2/20);//
	ent4.SetWindowPos(&wndTop,x,ye,largeur,he,SWP_SHOWWINDOW   );
	lcancel.SetWindowPos(&wndTop,x,y,largeur,hauteur,SWP_SHOWWINDOW   );
	lcancel.SetItemHeight(0,(UINT)(htou/6));
	if(code!=codeuser)
		snta.SetWindowPos(&wndTop,x,ys,largeur,hs,SWP_SHOWWINDOW   );
	if(fsecur)
		DrawBoutonCloture();
	esea.SetWindowPos(&wndTop,(int)((float)wlargeur*0.1/19.5),(int)((float)whauteur*25.5/27),(int)((float)wlargeur*6/19.5),(int)((float)whauteur*1.5/27),SWP_SHOWWINDOW   );
	esea.SetWindowText("");
	version.SetWindowPos(&wndTop,rctver.left,rctver.top,rctver.Width(),rctver.Height(),SWP_SHOWWINDOW   );
	temp.Format("Concert/n"+txtc[52]+" %.3f",fversion/1000);
	version.SetWindowTextA(temp);
}
void CConcertoDlg::DrawBoutonCloture()
{
	int x;
	int y;
	int largeur;//
	int hauteur;//	
	largeur=(int)((float)wlargeur*14/20);//
	hauteur=(int)((float)whauteur*2/27);//
	x=(int)((float)wlargeur*3.0/20);
	y=(int)((float)whauteur*18/27);//
	if(hist==0&&code!=codeuser)
		bcancel.SetWindowPos(&wndTop,x,y,largeur,hauteur,SWP_SHOWWINDOW   );
	y=(int)((float)whauteur*20.2/27);//
	if(code!=codeuser)
	{
		bcashview.SetWindowPos(&wndTop,x,y,largeur,hauteur,SWP_HIDEWINDOW   );
		bcashview.SetWindowPos(&wndTop,x,y,largeur,hauteur,SWP_SHOWWINDOW   );
	}
	y=(int)((float)whauteur*22.4/27);//
	bcashclose.SetWindowPos(&wndTop,x,y,largeur,hauteur,SWP_HIDEWINDOW   );
	bcashclose.SetWindowPos(&wndTop,x,y,largeur,hauteur,SWP_SHOWWINDOW   );
}
void CConcertoDlg::DrawBoutonGestion()
{
	int x;
	int y;
	int largeur;//
	int hauteur;//	
	largeur=(int)((float)wlargeur*3.8/19.5);//
	hauteur= (int)((float)whauteur*2.5/27);//
	x=(int)((float)wlargeur*0.3/19.5);
	y=(int)((float)whauteur*0.2/27);//ohnum;//((4.5*htou)+(5*ehtou)+ohnum);
	bresult.SetWindowPos(&wndTop,x,y,largeur,hauteur,SWP_SHOWWINDOW   );
	x+=(int)((float)wlargeur*4.0/19.5);
	if(code!=codeuser)
		bart.SetWindowPos(&wndTop,x,y,largeur,hauteur,SWP_SHOWWINDOW   );
	x+=(int)((float)wlargeur*4.0/19.5);
	if(fprev&&code!=codeuser)//&&master
	{
		bcontrol.SetWindowPos(&wndTop,x,y,largeur,hauteur,SWP_SHOWWINDOW   );
		x+=(int)((float)wlargeur*4.0/19.5);
	}
	else
		bcontrol.SetWindowPos(&wndTop,x,y,largeur,hauteur,SWP_HIDEWINDOW   );
	if(code!=codeuser)
		bconfig.SetWindowPos(&wndTop,x,y,largeur,hauteur,SWP_SHOWWINDOW   );
	
}

void CConcertoDlg::DrawStaticArticle()
{
	CString temp1;
	CString temp;
	nlibel.SetWindowPos(&wndTop,(int)(oltou),(int)(ohnum+2*htou/16),(int)(5*ltou/5),(int)(htou/4),SWP_SHOWWINDOW   );
	nlibel.SetWindowTextA(txtc[67]+" :");//Libellé 1
	slibel2.SetFont(&geodate,1);
	slibel2.SetWindowPos(&wndTop,(int)(oltou+2*ltou+eltou),(int)(ohnum+2*htou/16),(int)(ltou+eltou),(int)(htou/4),SWP_SHOWWINDOW);
	slibel1.SetFont(&geodate,1);
	slibel1.SetWindowPos(&wndTop,(int)(oltou+ltou),(int)(ohnum+2*htou/16),(int)(ltou+eltou),(int)(htou/4),SWP_SHOWWINDOW);
	//if(fprev)
	{
		nspect.SetWindowPos(&wndBottom,(int)(oltou),(int)(ohnum+7*htou/16),(int)(4*ltou/5),(int)(htou/4),SWP_HIDEWINDOW   );
		nspect.SetWindowTextA(txtc[64]+" :");//Evènement
		spect.SetFont(&geodate,1);
		spect.SetWindowPos(&wndBottom,(int)(oltou+ltou),(int)(ohnum+7*htou/16),(int)(5*ltou/3+eltou),(int)(htou/4),SWP_SHOWWINDOW);
		guichet.SetFont(&geodate,1);
		guichet.SetWindowPos(&wndBottom,(int)(oltou+2*ltou+eltou),(int)(ohnum+7*htou/16),(int)(2.5*ltou/3),(int)(htou/4),SWP_HIDEWINDOW);
	}
	nlibelcons.SetWindowPos(&wndTop,(int)(oltou),(int)(ohnum+12*htou/16),(int)(5*ltou/5),(int)(htou/4),SWP_SHOWWINDOW   );
	slibelcons.SetFont(&geodate,1);
	slibelcons.SetWindowPos(&wndTop,(int)(oltou+ltou),(int)(ohnum+12*htou/16),(int)(2*ltou+eltou),(int)(htou/4),SWP_SHOWWINDOW);
	nlibelcons.SetWindowTextA(txtc[65]+" :");//Libellé 2

	nprix.SetWindowPos(&wndTop,(int)(oltou+3*ltou+2*ltou/3+3*eltou),(int)(ohnum+htou/12),(int)(ltou/3),(int)(htou/4),SWP_SHOWWINDOW   );
	sprix.SetWindowPos(&wndTop,(int)(oltou+4*ltou+3*eltou),(int)(ohnum+htou/12),(int)(ltou),(int)(htou/4),SWP_SHOWWINDOW);
	nprix.SetWindowTextA(txtc[85]+" :");

	ntva1.SetWindowPos(&wndTop,(int)(oltou+3*ltou+3*eltou),(int)(ohnum+5*htou/16+htou/12),(int)(ltou/2),(int)(htou/4),SWP_SHOWWINDOW   );
	ntva2.SetWindowPos(&wndTop,(int)(oltou+3*ltou+3*eltou),(int)(ohnum+10*htou/16+htou/12),(int)(ltou/2),(int)(htou/4),SWP_HIDEWINDOW   );
	stva1.SetWindowPos(&wndTop,(int)(oltou+3*ltou+ltou/2+3*eltou),(int)(ohnum+5*htou/16+htou/12),(int)(ltou/2),(int)(htou/4),SWP_SHOWWINDOW);
	stva2.SetWindowPos(&wndTop,(int)(oltou+3*ltou+ltou/2+3*eltou),(int)(ohnum+10*htou/16+htou/12),(int)(ltou/2),(int)(htou/4),SWP_HIDEWINDOW);
	sval1.SetWindowPos(&wndTop,(int)(oltou+4*ltou+3*eltou),(int)(ohnum+5*htou/16+htou/12),(int)(ltou),(int)(htou/4),SWP_SHOWWINDOW);
	sval2.SetWindowPos(&wndTop,(int)(oltou+4*ltou+3*eltou),(int)(ohnum+10*htou/16+htou/12),(int)(ltou),(int)(htou/4),SWP_HIDEWINDOW);
	nvcontrol.SetWindowPos(&wndTop,(int)(oltou+4*ltou+4*eltou),(int)(ohnum+4*htou/4),(int)(ltou),(int)(htou/3),SWP_SHOWWINDOW   );

	int idx=artnum+(artrange*12);
	if(valhor&&horaire&&entrymode[idx]==1)
	{
		nvcontrol.SetWindowText(txtc[8]);//"Prévente\nsans horaire"
	}
	else
		if(valhor&&horaire&&entrymode[idx]==2)
		{
			nvcontrol.SetWindowText(txtc[8]);//"Prévente\navec horaire"
		}
		else
			if(entrymode[idx]==1)
			{
				nvcontrol.SetWindowText(txtc[8]);//"Prévente"
			}
			else
			{
				nvcontrol.SetWindowText(txtc[4]);//"Entrée\nimmédiate"
			}

	vactif.SetWindowPos(&wndTop,(int)(oltou+4*ltou+ltou/4+4*eltou),(int)(ohnum+7*htou/4+2*ehtou),(int)(ltou),(int)(htou/4),SWP_SHOWWINDOW   );
	vactif.SetWindowTextA(txtc[133]);//"Actif"
	if(nvalplace)
	{
		vplace.SetWindowPos(&wndTop,(int)(oltou+4*ltou+ltou/4+4*eltou),(int)(ohnum+10*htou/4+2*ehtou),(int)(ltou),(int)(htou/4),SWP_SHOWWINDOW   );
		vplace.SetWindowTextA(txtc[7]);//"Place"
	}
	vmix.SetWindowPos(&wndTop,(int)(oltou+4*ltou+ltou/4+4*eltou),(int)(ohnum+10*htou/4+2*ehtou),(int)(ltou),(int)(htou/4),SWP_HIDEWINDOW   );
	if(nvalmix)
	{
		vmix.SetWindowPos(&wndTop,(int)(oltou+4*ltou+ltou/4+4*eltou),(int)(ohnum+10*htou/4+2*ehtou),(int)(ltou),(int)(htou/4),SWP_SHOWWINDOW   );
		vmix.SetWindowTextA(txtc[131]);//"Pack"
	}
	ventry.SetWindowPos(&wndTop,(int)(oltou+4*ltou+ltou/4+4*eltou),(int)(ohnum+8.5*htou/4+2*ehtou),(int)(ltou),(int)(htou/4),SWP_SHOWWINDOW   );
	vexo.SetWindowPos(&wndTop,(int)(oltou+4*ltou+ltou/4+4*eltou),(int)(ohnum+11.5*htou/4+2*ehtou),(int)(3*ltou/4),(int)(htou/4),SWP_SHOWWINDOW   );
	if(cvalpass)
		vpass.SetWindowPos(&wndTop,(int)(oltou+4*ltou+ltou/4+4*eltou),(int)(ohnum+8.5*htou/4+2*ehtou),(int)(3*ltou/4),(int)(htou/4),SWP_HIDEWINDOW   );
	else
		vpass.SetWindowPos(&wndTop,(int)(oltou+4*ltou+ltou/4+4*eltou),(int)(ohnum+8.5*htou/4+2*ehtou),(int)(3*ltou/4),(int)(htou/4),SWP_HIDEWINDOW   );
	vcbx.SetWindowPos(&wndTop,(int)(oltou+4*ltou+ltou/4+4*eltou),(int)(ohnum+13*htou/4+2*ehtou),(int)(3*ltou/4),(int)(htou/4),SWP_SHOWWINDOW   );


	ncons.SetWindowPos(&wndTop,(int)(oltou+4*ltou+4*eltou),(int)(ohnum+14*htou/4+3*ehtou),(int)(ltou),(int)(htou/4),SWP_SHOWWINDOW   );
	scons.SetWindowPos(&wndTop,(int)(oltou+4*ltou+4*eltou+ltou/5),(int)(ohnum+15*htou/4+3*ehtou),(int)(3*ltou/5),(int)(htou/4),SWP_SHOWWINDOW);
	ncons.SetWindowTextA(txtc[66]);//Nb Consos
}

void CConcertoDlg::DrawBoutonConfArticle()
{
	int largeur;//
	int hauteur;//	
	largeur=(int)((float)wlargeur*4/19.5);
	hauteur= (int)((float)whauteur*2/27);
	int	x=(int)((float)wlargeur*14.2/19.5);
	int y= (int)((float)whauteur*24.3/27);
	//BOUTON importer
	if(master&&fprev)
	{
		largeur=(int)((float)wlargeur*2.3/19.5);
		hauteur= (int)((float)whauteur*2/27);
		x=(int)((float)wlargeur*16.4/19.5);
		y=(int)(ohnum+5*htou/4+htou/12);// (int)((float)whauteur*8.5/27);
		//nvcontrol.SetWindowPos(&wndTop,(int)(oltou+4*ltou+4*eltou),(int)(ohnum+13*htou/16+htou/12),(int)(ltou),(int)(htou/2),SWP_SHOWWINDOW   );
		bentrymode.SetWindowPos(&wndTop,x,y,largeur,hauteur,SWP_SHOWWINDOW   );
	}

	// BOUTON TRANDFERT DE TICKET VERS CONTROL 
	x=(int)oltou;
	y=(int)(ohnum+(4*ehtou)+(4*htou));
	largeur=(int)(4*ltou+3*eltou);
	hauteur=(int)(htou/2);
	((CButton*)GetDlgItem(IDC_11))->SetWindowPos(&wndBottom,(int)x,(int)y,(int)largeur,(int)hauteur,SWP_HIDEWINDOW);
}

void CConcertoDlg::DrawBoutonControl()
{
	int largeur;//
	int hauteur;//
	int x;
	int y;

	//BOUTON importer évènement
	x=(int)(oltou+4*ltou+4*eltou);//(oltou+2*ltou+2*eltou+ltou/2);
	y= (int)((float)whauteur*24.4/27);
	largeur=(int)ltou;
	hauteur= (int)((float)whauteur*2/27);
	if(master)
		bimport.SetWindowPos(&wndTop,x,y,largeur,hauteur,SWP_SHOWWINDOW   );
	else
		bimport.SetWindowPos(&wndTop,x,y,largeur,hauteur,SWP_HIDEWINDOW   );

	//BOUTON supprimer sélection évènement
	largeur=(int)((float)wlargeur*2/19.5);			
	hauteur=(int)((float)whauteur*1.7/27);			
	x=(int)((float)wlargeur*13.2/19.5);	
	y=(int)((float)whauteur*24.6/27);//(ohnum+4*htou+4*ehtou);
	if(master)
		bdel.SetWindowPos(&wndTop,x,y,largeur,hauteur,SWP_SHOWWINDOW   );
	else
		bdel.SetWindowPos(&wndTop,x,y,largeur,hauteur,SWP_HIDEWINDOW   );
	largeur=(int)((float)wlargeur*12/20);//
	hauteur=(int)((float)whauteur*2/27);//
	x=(int)((float)wlargeur*4/20);
	y=(int)((float)whauteur*22.2/27);//
	((CButton*)GetDlgItem(IDC_11))->SetWindowPos(&wndTop,x,y,largeur,hauteur,SWP_SHOWWINDOW   );
	largeur=(int)(5*ltou+4*eltou);
	lselevt.SetWindowPos(&wndTop,(int)oltou,(int)ohnum,largeur,(int)htou,SWP_SHOWWINDOW   );
	lselevt.SetItemHeight(0,(UINT)(htou/5));
	lselevt.ResetContent();
	lselevt.SetFont(&geodate,0);
	lselevt.SetWindowPos(&wndTop,(int)oltou,(int)ohnum,largeur,(int)htou,SWP_SHOWWINDOW   );
}
void CConcertoDlg::DrawLettre(CString temp,CRect rct,CDC* pdc,COLORREF col,CFont* pfont,int type)
{
	pdc->SetBkMode(TRANSPARENT);
	pdc->SelectObject(pfont);
	if(temp=="X")
	{
		pdc->SetTextColor(0xFF);
		pdc->FillSolidRect(&rct,col);
	}
	else
	{
		pdc->SetTextColor(0x0);
		pdc->FillSolidRect(&rct,col);
	}
	if(type==5||type==6)
		pdc->DrawText(temp,-1,&rct,DT_LEFT|DT_VCENTER|DT_SINGLELINE );
	else
		pdc->DrawText(temp,-1,&rct,DT_CENTER|DT_VCENTER|DT_SINGLELINE );

}

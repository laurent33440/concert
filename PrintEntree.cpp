#include "stdafx.h"
#include "Concerto.h"
#include "ConcertoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int CConcertoDlg::DrawLogo(CDC* pdc,float xl1)
{
	int toporg;
	float xi;
	float yi;
	float dl;
	float dh;
	float dlw;
	float dhw;
	float oxs;
	float oys;
	CStringW wstr;
	CString temp=workdir+"\\Logo.jpg";
	CFileStatus cfs;
	if(noprint || !paravent )
		dh=100;// hauteur max du logo
	else
		dh=150;// hauteur max du logo
	if(CFile::GetStatus((LPCTSTR)temp,cfs))
	{
		logo=1;
		wstr=temp;
	}
	else
	{
		temp=workdir+"\\Logo.bmp";
		if(CFile::GetStatus((LPCTSTR)temp,cfs))
		{
			logo=1;
			wstr=temp;
		}

		else
		{
			logo=0;
			dh=10;
			goto FIN;
		}
	}
	wstr=temp;
	if(!noprint&&(printername.Find("KMGA")!=-1||printername.Find("KPSX")!=-1)||printername.Find("Citizen CL-S400DT")!=-1||noprint)
	{
		Image myImage(wstr);
		Graphics gr (pdc->m_hDC);
		xi=(float)myImage.GetWidth( );//
		yi=(float)myImage.GetHeight( );//
		dl=xl1-20;//((xl1-20));
		if(paravent)
			dl=(xl1-20)/3;//((xl1-20));
		float k=dl/(xi);// rapport destination image
		if(yi*k>dh)
		{
			k=dh/(yi);
			dlw=xi*k;
			dhw=dh;
			oxs=((dl-dlw)/2)+10;//1*xl1/8;//+10;
			oys=topline;
		}
		else
		{
			dlw=dl;
			dhw=yi*k;
			oxs=10;//1*xl1/8;
			oys=topline+(dh-dhw)/2;
		}
		CRect rect;
		if(noprint)
			rect.SetRect((int)oxs,(int)oys,(int)(oxs+dlw),(int)(oys+dhw));
		else
			rect.SetRect((int)oxs/2,(int)oys/2,(int)(oxs+dlw)/2,(int)(oys+dhw)/2);
		RectF rct((REAL)rect.left,(REAL)rect.top,(REAL)rect.Width(),(REAL)rect.Height());
		
		gr.DrawImage(&myImage,rct);
	}
FIN:;
	toporg=(int)dh;
	return toporg;//155;
}

int CConcertoDlg::PrintEntree(CDC* pdc,int idx,CString ticket,CString libelle,CString nconso,CString prix,CString tvatxt1,CString tvatxt2,CString part,CString spectacle,int fenter,CString place,int nbcons) 
{
	CString txtsign;
	CString sign;
	CString extrait;
	CString temp;
	CString temp1;
	CString temp2;
	CString temp3;
	CString ntemp;
	CString date;
	CString page;
	CString txtvaltva1;
	CString txtvaltva2;
	CString txtprixht;
	CString haut;
	CString larg;
	CString pox;
	double valtva1;
	double valtva2;
	double valht;
	double tauxtva1;	
	double tauxtva2;
	double valprix;
	float cblarg;
	float cb128larg;
	float cblmarge;
	float cb128lmarge;
	CTime ct;
	ct=CTime::GetCurrentTime();
	date=ct.Format("%d/%m/%Y  %H:%M:%S");// a corriger
	CDC m_Cdc;
	CRect rect;
	//CRect butrect;
	CFont num;
	CRect rct;
	CFont tpf;
	CFont tf;
	CFont tcf;
	CFont df;
	CFont mic;
	CFont mid;
	CFont miw;
	CFont mil;
	CFont mit;
	CFont cbfont;
	float plargeur;
	float phauteur;
	float x;
	float xl1;
	int largeur;//
	int hauteur;//
	int bc;//
	int lg;//
	int gdcx;
	XFORM xForm;
	int toporg;
	int i;
	COLORREF pencolor=0x00000000;
	COLORREF blancolor=0x00FFFFFF;
	CPen dashpen(PS_DASH,1,pencolor);
	CPen finepen(PS_SOLID,2,pencolor);
	CBrush br;
	br.CreateSolidBrush(pencolor);
	if(pdc->m_hDC!=NULL)
	{
		if(noprint)
		{
			if(paravent)
			{
				pdc->SetGraphicsMode(GM_ADVANCED);
				pdc->GetWorldTransform(&xForm);
				xForm.eM11 = (FLOAT)0; 
				xForm.eM12 = (FLOAT)+0.65; 
				xForm.eM21 = (FLOAT) -0.70; 
				xForm.eM22 = (FLOAT)0; 
				xForm.eDx  = (FLOAT) +310.0;//invxa; 
				xForm.eDy  = (FLOAT) +10;//invya; 20
				pdc->SetWorldTransform(&xForm); 
				plargeur=(float)wlargeur/1;
			}
			else
				plargeur=(float)wlargeur/2;
			gdcx=(int)plargeur;
			phauteur=(float)tsorg;
			x=0;
			lmarge=0;
			rmarge=0;
			rect.top=0;
			rect.bottom=tsorg;
			bc=(0xFFFFFF);
			rect.left=0;
			rect.right=wlargeur/2;
			pdc->SelectObject(&finepen);
			pdc->FillSolidRect(&rect,bc);
			if(paravent)
				hauteur= 700;
			else
				hauteur= 770;
		}
		else
		{
			lmarge=0;
			pdc->SetGraphicsMode(GM_ADVANCED);
			pdc->GetWorldTransform(&xForm);
			if(paravent)
			{
				if(printername.Find("KMGA")!=-1)
				{
					xForm.eM11 = (FLOAT)0.0; 
					xForm.eM12 = (FLOAT)-1.0; 
					xForm.eM21 = (FLOAT) +1.0; 
					xForm.eM22 = (FLOAT) 0.0; 
					xForm.eDx  = (FLOAT) 0.0;//invxa; 
					xForm.eDy  = (FLOAT) 800;//invya; 
				}
				else
				{
					if(printername.Find("KPSX")!=-1)
					{
						xForm.eM11 = (FLOAT) 0.0; 
						xForm.eM12 = (FLOAT) -1.0; 
						xForm.eM21 = (FLOAT) +1.0; 
						xForm.eM22 = (FLOAT) 0.0; 
						xForm.eDx  = (FLOAT) 0.0; 
						xForm.eDy  = (FLOAT) 770; 
					}
					else
					{
						if(printername.Find("Citizen CL-S400DT")!=-1)
						{
							xForm.eM11 = (FLOAT) 0.0; 
							xForm.eM12 = (FLOAT) -1.0; 
							xForm.eM21 = (FLOAT) +1.0; 
							xForm.eM22 = (FLOAT) 0.0; 
							xForm.eDx  = (FLOAT) 150; 
							xForm.eDy  = (FLOAT) 1080;
							lmarge=80;
						}
					}
				}
			}
			else
			{
				if(printername.Find("KMGA")!=-1)
				{
					xForm.eM11 = (FLOAT) -1.0; 
					xForm.eM12 = (FLOAT) 0.0; 
					xForm.eM21 = (FLOAT) 0.0; 
					xForm.eM22 = (FLOAT) -1.0; 
					xForm.eDx  = (FLOAT) invxa; 
					xForm.eDy  = (FLOAT) invya; 
				}
				else
				{
					if(printername.Find("KPSX")!=-1)
					{
						xForm.eM11 = (FLOAT) -1.0; 
						xForm.eM12 = (FLOAT) 0.0; 
						xForm.eM21 = (FLOAT) 0.0; 
						xForm.eM22 = (FLOAT) -1.0; 
						xForm.eDx  = (FLOAT) invxt;//450 
						xForm.eDy  = (FLOAT) invyt; //735
					}
					else
					{
						if(printername.Find("Citizen CL-S400DT")!=-1)
						{
							xForm.eM11 = (FLOAT) -1.0; 
							xForm.eM12 = (FLOAT) 0.0; 
							xForm.eM21 = (FLOAT) 0.0; 
							xForm.eM22 = (FLOAT) -1.0; 
							xForm.eDx  = (FLOAT) 590; //580
							xForm.eDy  = (FLOAT) 810; 
						}
					}
				}
			}
			pdc->SetWorldTransform(&xForm); 
			if(printername.Find("Citizen CL-S400DT")!=-1&&paravent)
				gdcx=3*pdc->GetDeviceCaps(HORZRES)/4;//-(2*cdc.GetDeviceCaps(PHYSICALOFFSETX)));
			else
				if(printername.Find("Citizen CL-S400DT")!=-1&&!paravent)
					gdcx=4*pdc->GetDeviceCaps(HORZRES)/8;//-(2*cdc.GetDeviceCaps(PHYSICALOFFSETX)));
				else
					gdcx=pdc->GetDeviceCaps(HORZRES);//-(2*cdc.GetDeviceCaps(PHYSICALOFFSETX)));
			if(paravent)
			{
				plargeur=(float)midline;
				hauteur= 800;
			}
			else
			{
				plargeur=(float)gdcx;
				hauteur= 1000;
			}
			phauteur=(float)pdc->GetDeviceCaps(VERTRES);//-(2*cdc.GetDeviceCaps(PHYSICALOFFSETY)));
			x=(float)pdc->GetDeviceCaps(PHYSICALOFFSETX);
		}
		largeur=(int)(plargeur/2.1);//
		if((fenter!=3&&nbcons>0)||paravent)
			num.CreateFont((int)hauteur/18,
				(int)plargeur/40,
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
		else
			num.CreateFont((int)hauteur/10,
				(int)plargeur/35,
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
		tpf.CreateFont((int)hauteur/12,
			(int)plargeur/35,
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
		tf.CreateFont((int)hauteur/15,
			(int)plargeur/35,
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
		tcf.CreateFont((int)hauteur/18,
			(int)plargeur/35,
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
		df.CreateFont((int)hauteur/15,
			(int)plargeur/25,
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
		mic.CreateFont((int)hauteur/25,
			(int)plargeur/35,
			0,
			0,
			1000 ,//Epaisseur
			0,
			0,
			0,
			DEFAULT_CHARSET,
			OUT_TT_PRECIS,
			CLIP_DEFAULT_PRECIS,
			NONANTIALIASED_QUALITY,//ANTIALIASED_QUALITY,//PROOF_QUALITY,
			DEFAULT_PITCH|FF_DONTCARE,
			"ARIAL");
		mit.CreateFont((int)hauteur/14,
			(int)plargeur/35,
			0,
			0,
			1000 ,//Epaisseur
			0,
			0,
			0,
			DEFAULT_CHARSET,
			OUT_TT_PRECIS,
			CLIP_DEFAULT_PRECIS,
			NONANTIALIASED_QUALITY,//ANTIALIASED_QUALITY,//PROOF_QUALITY,
			DEFAULT_PITCH|FF_DONTCARE,
			"ARIAL");
		mid.CreateFont((int)hauteur/25,
			(int)plargeur/50,
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
		miw.CreateFont((int)hauteur/30,
			(int)plargeur/60,
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
		if(paravent)
			mil.CreateFont((int)hauteur/35,
				(int)plargeur/100,
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
		else
			mil.CreateFont((int)hauteur/35,
				(int)plargeur/70,
				0,
				0,
				200 ,//Epaisseur
				0,
				0,
				0,
				DEFAULT_CHARSET,
				OUT_TT_PRECIS,
				CLIP_DEFAULT_PRECIS,
				NONANTIALIASED_QUALITY,//ANTIALIASED_QUALITY,//PROOF_QUALITY,
				DEFAULT_PITCH|FF_DONTCARE,
				"ARIAL");
		pdc->SetTextColor(0x000000);
		if(!noprint&&(printername.Find("KPSX")!=-1||printername.Find("KMGA")!=-1)||printername.Find("Citizen CL-S400DT")!=-1||noprint)
		{
			i=midline;
			if(noprint)
			{
				if(paravent)
					xl1=9*(float)i/8;
				else
				{
					plargeur=(float)gdcx;
					xl1=(plargeur)-rmarge;
				}
			}
			else
				if(paravent)
					xl1=(float)10*plargeur/8;
				else
					xl1=(plargeur)-rmarge;
			toporg=0;
			toporg=DrawLogo(pdc,xl1);
			if(paravent)
				toporg=0;
			float y=(float)hauteur/15;//(150);
			if(noprint)
				rct.top=toporg+(int)(y/2);
			else
				rct.top=toporg;//+(int)(y/10);
			rct.bottom=rct.top+(LONG)y;
			bc=(0xFFFFFF);
			pdc->SetBkMode(TRANSPARENT);

			if(paravent&&logo)
				rct.left=(5*(LONG)xl1)/12;
			else
				rct.left=(LONG)10;
			rct.right=(LONG)xl1-10;
			if(noprint)
				pdc->FillSolidRect(&rct,bc);
			if(paravent)
			{
				rct.top+=hauteur/20;//60;
				rct.bottom+=hauteur/12;//60;
			}
			else
			{
				rct.top+=hauteur/40;//60;
				rct.bottom+=hauteur/20;//60;
			}
			//if(!logo||paravent) // DANS TOUS LES CAS ON IMPRIME LE NOM ET LE LOGO (NF525 pour le nom)
			{
				if(paravent)
					pdc->SelectObject(&num);
				else
					if(logo==0)
						pdc->SelectObject(&tpf);
					else
						pdc->SelectObject(&mic);
				pdc->DrawText(nom,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP|DT_NOPREFIX );
				if(paravent||logo==0)
				{
					if(paravent)
					{
						rct.top+=hauteur/20;//60;
						rct.bottom+=hauteur/20;//60;
					}
					else
					{
						rct.top+=hauteur/12;//60;
						rct.bottom+=hauteur/12;//60;
					}
				}
				else
				{
					rct.top+=hauteur/30;//60;
					rct.bottom+=hauteur/30;//60;
				}
			}
			pdc->SelectObject(&miw);
			if(adresse1!="")
			{
				pdc->DrawText(adresse1,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP|DT_NOPREFIX  );
				rct.top+=hauteur/30;//40;
				rct.bottom+=hauteur/30;//40;
			}
			//if(adresse2!="")
			{
				pdc->DrawText(adresse2+" "+pays,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP|DT_NOPREFIX  );
				rct.top+=hauteur/30;//40;
				rct.bottom+=hauteur/30;//40;
			}/**/
			if(siret!=""||naf!="")
			{
				/*if(paravent)
					rct.left=((LONG)xl1)/3+10;
				else
					rct.left=(LONG)10;
				rct.right=(LONG)((xl1-10));*/
				pdc->SelectObject(&miw);
				pdc->DrawText(txtc[72]+" : "+siret+" "+txtc[95]+" : "+naf,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP|DT_NOPREFIX  );
			}
			if(paravent)
			{
				rct.top+=hauteur/30;//40;
				rct.bottom+=hauteur/30;//40;
			}
			else
			{
				rct.top+=hauteur/30;//40;
				rct.bottom+=hauteur/30;//40;
			}
			pdc->SelectObject(&miw);
			if(cvalpass&&((perso[idx]&0xF000)>>12)>1)//prevente
			{	
				temp.Format("%u",(perso[idx]&0xF000)>>12);
				temp1=txtc[153];//Valable % jours
				temp1.Replace("%",temp);
				pdc->DrawText(temp1,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP|DT_NOPREFIX  );
			}
			else
				pdc->DrawText(mentiont,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP|DT_NOPREFIX  );
			if(printername.Find("Citizen CL-S400DT")!=-1&&!paravent)
			{
				rct.left=(LONG)10;
				rct.right=(LONG)((xl1-10));
			}
			else
				if(paravent)
					rct.left=(LONG)10;
				else
					rct.left=(LONG)10;
			rct.right=(LONG)((xl1-10));
			rct.top+=hauteur/30;//40;
			rct.bottom+=hauteur/30;//40;
			if(paravent)
				pdc->SelectObject(&df);
			else
				pdc->SelectObject(&mic);
			pdc->DrawText(date,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP |DT_NOPREFIX );
			if(paravent)
			{
				rct.top+=hauteur/15;//40;
				rct.bottom+=hauteur/15;//40;
			}
			else
			{
				rct.top+=hauteur/25;//40;
				rct.bottom+=hauteur/25;//40;
			}
			if(nc==0)
			{
				if(printername.Find("Citizen CL-S400DT")!=-1&&!paravent)
				{
					rct.left=(LONG)10;
					rct.right=(LONG)((xl1-10));
				}
				else
				{
					rct.left=(LONG)10;
					rct.right=(LONG)((xl1-10));
				}
				if(paravent)
					pdc->SelectObject(&mit);
				else
					pdc->SelectObject(&mic);
				if(fenter==1)
				{
					if(atoi(prix)>0)
					{
						if(libel1[idx].Find("$",0)!=0)
							temp1=txtc[90];//"ENTREE PAYANTE"
						else
							temp1=libelle.Mid(1);
						pdc->DrawText(temp1,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP|DT_NOPREFIX );//|DT_MODIFYSTRING);*************
					}
					else
					{
						temp1=txtc[91];//"ENTREE EXO"
						pdc->DrawText(temp1,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP|DT_NOPREFIX );//"ENTREE EXO"|DT_MODIFYSTRING);*************
					}
				}
				else
					pdc->DrawText(libelle,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP|DT_END_ELLIPSIS|DT_NOPREFIX );//|DT_MODIFYSTRING);*/
					
				if(paravent)
				{
					rct.top+=hauteur/14;
					rct.bottom+=hauteur/14;
				}
				else
					if(nbcons>0&&logo)
					{
						rct.top+=hauteur/30;
						rct.bottom+=hauteur/30;
					}
					else
					{
						rct.top+=hauteur/25;
						rct.bottom+=hauteur/25;
					}
					
				if(printername.Find("Citizen CL-S400DT")!=-1&&!paravent)
					rct.left=(LONG)10;
				else
					rct.left=(LONG)10;
				if(place!="")
					rct.right=(LONG)(2*(xl1-10)/3);
				else
					rct.right=(LONG)((xl1-10));
				if(paravent)
					pdc->SelectObject(&mic);
				else
					if(nbcons>0&&logo)
						pdc->SelectObject(&mic);
					else
						pdc->SelectObject(&df);
				if(fenter==0&&atoi(prix)==0)//EXO
					temp3=txtc[92];//"EXO"
				else
					temp3=txtc[85];//"Prix"
				temp1=txtc[76];//"TTC"
				temp2=txtc[134];//"HT"
				temp=temp3+" "+prix+cur+" "+temp1;
				pdc->DrawText(temp,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP );
				if(place!="")
				{//Pl.
					rct.left=rct.right;
					rct.right=(LONG)((xl1-10));
					temp1=txtc[93];//"Pl."
					pdc->DrawText(temp1+" "+place,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP|DT_END_ELLIPSIS|DT_NOPREFIX );//|DT_MODIFYSTRING);*************
				}
				temp3=txtc[62];//"TVA"
				tauxtva1=atof(tvatxt1);
				tauxtva2=atof(tvatxt2);
				valprix=atof(prix);
				if(tauxtva2==0)
				{
					valtva1=(valprix-(valprix/(1+(tauxtva1/100))));
					valtva2=0;
				}
				else
				{
					valtva1=(val1[idx])-(val1[idx]/((1+(tva1[idx]/100))));//atof(prix)*0.16388;
					valtva2=((val2[idx])-(val2[idx]/((1+(tva2[idx]/100)))));//atof(prix)*0.16388;
				}
				valht=valprix-valtva1-valtva2;
				txtvaltva1.Format("%.2f"+cur,valtva1);
				txtvaltva2.Format("%.2f"+cur,valtva2);
				txtprixht.Format("%.2f"+cur,valht);
				if(tauxtva2==0)
					temp=temp2+":"+txtprixht+" "+temp3+" "+tvatxt1+"%:"+" "+txtvaltva1;
				else
					temp=temp2+":"+txtprixht+" "+temp3+" "+tvatxt1+"%:"+" "+txtvaltva1+" "+temp3+" "+tvatxt2+"%:"+" "+txtvaltva2;
				if(paravent||(nbcons>0&&logo))
				{
					rct.top+=hauteur/25;
					rct.bottom+=hauteur/25;
					rct.left=(LONG)10;
					rct.right=(LONG)((xl1-10));
					pdc->SelectObject(&miw);
				}
				else
				{
					rct.top+=hauteur/15;
					rct.bottom+=hauteur/15;
					rct.left=(LONG)10;
					rct.right=(LONG)((xl1-10));
					pdc->SelectObject(&miw);
				}
				pdc->DrawText(temp,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP|DT_NOPREFIX  );
			}
			rct.top+=hauteur/38;
			rct.bottom+=hauteur/38;
			rct.left=(LONG)10;
			rct.right=(LONG)((xl1-10));
			if(paravent)
				pdc->SelectObject(&tcf);
			else
				pdc->SelectObject(&mid);
			pdc->DrawText(nconso,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP|DT_END_ELLIPSIS|DT_NOPREFIX );//|DT_MODIFYSTRING);*/************
			if(paravent)
			{
				rct.top+=hauteur/20;//40;
				rct.bottom+=hauteur/20;//40;
			}
			else
			{
				rct.top+=hauteur/25;//40;
				rct.bottom+=hauteur/25;//40;
			}
			pdc->SelectObject(&mid);
			if(nc==0)
			{
				rct.left=(LONG)10;
				rct.right=(LONG)((xl1-10));
				temp="N° "+ticket;//+part;
				if(fenter!=3)
					pdc->DrawText(temp,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP|DT_NOPREFIX   );
			}
			else
			{
				rct.left=(LONG)10;
				rct.right=(LONG)((xl1-10));
				pdc->SelectObject(&tf);
				temp1=txtc[94];
				//"CONSO SUPPLEMENTAIRE";
				pdc->DrawText(temp1,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP|DT_NOPREFIX   );
				rct.top+=hauteur/30;
			}
			/*if(spectacle.Find("PLACE",0)!=-1)
			{
				rct.top+=hauteur/25;//50;
				rct.bottom+=hauteur/25;//50;
				rct.right=(LONG)lmarge+10;
				rct.left=(LONG)((xl1-10));
				pdc->SelectObject(&mid);
				pdc->DrawText(spectacle,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP );
			}
			else
			{
				if(spectacle!="")
				{
					rct.top+=hauteur/25;//50;
					rct.bottom+=hauteur/25;//50;
					rct.right=(LONG)lmarge+10;
					rct.left=(LONG)((xl1-10));
					pdc->SelectObject(&mid);
					pdc->DrawText(spectacle,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP );
				}
			}*/
			tsorg=rct.top+hauteur/30;

			if(fenter!=3&&nbcons>0)//atoi(prix)>0&&
			{
				if(paravent)
				{
					if(eflag==1)
						cb128lmarge=(float)9.5*plargeur/24;
					else
						if(eflag==2)
							cb128lmarge=(float)10.5*plargeur/24;
					cb128larg=4*plargeur/5;
					cblarg=plargeur/40;
					cblmarge=6*plargeur/18;
				}
				else
				{
					if(printername.Find("Citizen CL-S400DT")!=-1&&!paravent)
					{
						if(eflag==1)
							cb128lmarge=-900;//1*plargeur/36;
						else
							if(eflag==2)
								cb128lmarge=3*plargeur/55;
						cb128larg=plargeur*2;
						cblmarge=plargeur/5;
						cblarg=plargeur;
					}
					else
					{
						if(eflag==1)
							cb128lmarge=2*plargeur;
						else
							cb128lmarge=plargeur/5;
						cb128larg=plargeur*2;
						cblmarge=plargeur/7;
						cblarg=plargeur;
					}
				}
				if(eflag==1)//ETC
				{
					ntemp=ticket.Mid(4,2);
					temp=GetCode128A(ntemp);
					if(!paravent)
						PrintBarre128A(pdc,(int)(1*cb128lmarge/50),tsorg,(int)cb128larg,hauteur/10+tsorg,temp);
					else
						PrintBarre128A(pdc,(int)(4*cb128lmarge/6),tsorg,(int)cb128larg,hauteur/10+tsorg,temp);
					econt++;
					//AfxGetApp()->WriteProfileInt("Ntouche","eCont",econt);
				}
				else
				{
					if(eflag)//ARBAN
					{
						if(eflag==2)
							ntemp=ticket.Mid(4,2);
						else
						{
							ntemp=ticket.Mid(4,2);
						}
						temp=GetCode128A(ntemp);
						if(!paravent)
							PrintBarre128A(pdc,(int)cb128lmarge,tsorg,(int)cb128larg,hauteur/10+tsorg,temp);
						else
							PrintBarre128A(pdc,(int)(45*cb128lmarge/60),tsorg,(int)cb128larg,hauteur/10+tsorg,temp);
						temp.Format("%u",atoi(ntemp));
						acont[atoi(ntemp)]++;

						//AfxGetApp()->WriteProfileInt("Ntouche","aCont"+temp,acont[atoi(ntemp)]);
					}
					else// TOUCHE
					{
						temp=ticket.Mid(4,2);
						while(temp.GetLength()<5)
							temp="0"+temp;
						GetConsoCode(temp);
						PrintBarre(pdc,(int)(4*cblmarge/3),tsorg,(int)cblarg,hauteur/12+tsorg);
					}
				}
			}

			rct.top+=hauteur/35;
			rct.bottom=rct.top+hauteur/35;
			rct.right=(LONG)lmarge+10;
			rct.left=(LONG)((xl1-10));
			/*pdc->SelectObject(&miw);
			pdc->DrawText(mentiont,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP );*/
			if(paravent&&noprint)
			{
				pdc->SetGraphicsMode(GM_ADVANCED);
				pdc->GetWorldTransform(&xForm);
				xForm.eM11 = (FLOAT) 1; 
				xForm.eM12 = (FLOAT) 0; 
				xForm.eM21 = (FLOAT) 0; 
				xForm.eM22 = (FLOAT) 1; 
				xForm.eDx  = (FLOAT) 0.0;//invxa; 
				xForm.eDy  = (FLOAT) 0.00;//invya; 
				pdc->SetWorldTransform(&xForm); 
				i=midline;
				tsorg=3*i/4;
				pdc->SelectObject(&dashpen);
				pdc->MoveTo(0,tsorg);
				pdc->LineTo((int)xl1,tsorg);
			}
			pdc->SelectObject(&finepen);
			tsorg=midline ;
		}
		if((!QUIT&&fenter!=3)&&(!noprint||(noprint&&sp.IsWindowVisible())))
		{
			if(dopen.GetLength()==0)
			{
				CTime tim=CTime::GetCurrentTime();
				if(InitCaisse(tim)==0)// initialisation de la période si premier ticket
				{
					if(infocert)
					{
						FonctionEditeur("Erreur initialisation fichier Data");
					}
					return 0;
				}
			}
			if (nc==0&&(!noprint||(noprint&&sp.IsWindowVisible())))//test si ticket partie 1 ou simulation 2ème passe
			{
				CString TGTZ;
				CString TGTP;
				TGTZ.Format("%.2f",GTZ);
				TGTP.Format("%.2f",GTP);
				txtvaltva1.Format("%.2f",val1[idx]);
				tvatxt1.Format("%.2f",tva1[idx]);
				if(perso[idx]&4)
				{
					tvatxt2.Format("%.2f",tva2[idx]);
					txtvaltva2.Format("%.2f",val2[idx]);
					temp=ticket+" "+part+";"+date+";"+prix+";"+tvatxt1+";"+txtvaltva1+";"+tvatxt2+";"+txtvaltva2+";;"+TGTZ+";"+TGTP;
				}
				else
					if(idx==0)
						temp=ticket+" "+part+";"+date+";"+prix+";"+tvatxt1+";"+txtvaltva1+";0.00;0.00;"+libel2[idx]+";"+TGTZ+";"+TGTP;
					else
						temp=ticket+" "+part+";"+date+";"+prix+";"+tvatxt1+";"+txtvaltva1+";0.00;0.00;;"+TGTZ+";"+TGTP;
						
				// SIGNATURE TICKET
				if(infocert)
				{
					//temp1.Format("%.2f",valtva1+valtva2);
					//temp1.Replace(".","");
					temp1.Format("%.2f",tva1[idx]);
					temp2.Format("%.2f",val1[idx]);
					temp1+=","+temp2;
					temp2.Format("%.2f",tva2[idx]);
					temp1+=","+temp2;
					temp2.Format("%.2f",val2[idx]);
					temp1+=","+temp2;
					temp1.Replace(".","");
					spart[0]=temp1;
					temp1.Format("%.2f",valprix);
					temp1.Replace(".","");
					spart[1]=temp1;
					temp1=ct.Format("%Y%m%d%H%M%S");
					spart[2]=temp1;
					temp1=ticket;
					temp1.Replace(" ","");
					spart[3]=temp1;
					spart[4]=ticket.Left(1);
					spart[5]=sticket;//;
					sign=Sign(2);
					extrait=GetExtrait(sign);
					if(printername.Find("Citizen CL-S400DT")!=-1||printername.Find("KPSX")!=-1)
					{
						if(paravent)
						{
							xForm.eM11 = (FLOAT) -1.0; 
							xForm.eM12 = (FLOAT) 0.0; 
							xForm.eM21 = (FLOAT) 0.0; 
							xForm.eM22 = (FLOAT) -1.0; 
							xForm.eDx  = (FLOAT) 590; //580
							xForm.eDy  = (FLOAT) 800;
						}
						else
						{
							if(printername.Find("Citizen CL-S400DT")!=-1)
							{
								xForm.eM11 = (FLOAT) 0.0; 
								xForm.eM12 = (FLOAT) -1.0; 
								xForm.eM21 = (FLOAT) +1.0; 
								xForm.eM22 = (FLOAT) 0.0; 
								xForm.eDx  = (FLOAT) 530; 
								xForm.eDy  = (FLOAT) 750;
							}
							else
							{
								xForm.eM11 = (FLOAT) 0.0; 
								xForm.eM12 = (FLOAT) -1.0; 
								xForm.eM21 = (FLOAT) +1.0; 
								xForm.eM22 = (FLOAT) 0.0; 
								xForm.eDx  = (FLOAT) 350; 
								xForm.eDy  = (FLOAT) 600;
							}
						}
						pdc->SetWorldTransform(&xForm); 
						if(paravent)
							rct.top=30*hauteur/50;
						else
							rct.top=0;//30*hauteur/50;
						rct.bottom=rct.top+hauteur/15;
						if(lic[0]+lic[1]+lic[2]+lic[3]+lic[4]+lic[5]!="")
						{
							pdc->SelectObject(&mil);
							if(lic[3]==""&&lic[4]==""&&lic[5]=="")
							{
								rct.top+=hauteur/35;
								rct.bottom=rct.top+hauteur/35;
							}
							if(paravent)
								lg=(LONG)((xl1-10)/6);
							else
								lg=(LONG)(4*(xl1-10)/16);
							rct.left=(LONG)0;
							rct.right=lg/4;
							pdc->DrawText("Lic. :",-1,&rct,DT_LEFT|DT_SINGLELINE|DT_TOP|DT_NOPREFIX  );
							rct.left=rct.right;
							rct.right=rct.left+lg;
							pdc->DrawText(lic[0],-1,&rct,DT_LEFT|DT_SINGLELINE|DT_TOP|DT_NOPREFIX  );
							rct.left=rct.right;
							rct.right=rct.left+lg;
							pdc->DrawText(lic[1],-1,&rct,DT_LEFT|DT_SINGLELINE|DT_TOP|DT_NOPREFIX  );
							rct.left=rct.right;
							rct.right=rct.left+lg;
							pdc->DrawText(lic[2],-1,&rct,DT_LEFT|DT_SINGLELINE|DT_TOP|DT_NOPREFIX  );
							if(lic[3]!=""||lic[4]!=""||lic[5]!="")
							{
								rct.top+=hauteur/35;
								rct.bottom=rct.top+hauteur/35;
								rct.left=(LONG)((xl1-10)/20);
								rct.right=rct.left+lg;
								pdc->DrawText(lic[3],-1,&rct,DT_LEFT|DT_SINGLELINE|DT_TOP |DT_NOPREFIX);
								rct.left=rct.right;
								rct.right=rct.left+lg;
								pdc->DrawText(lic[4],-1,&rct,DT_LEFT|DT_SINGLELINE|DT_TOP |DT_NOPREFIX);
								rct.left=rct.right;
								rct.right=rct.left+lg;
								pdc->DrawText(lic[5],-1,&rct,DT_LEFT|DT_SINGLELINE|DT_TOP|DT_NOPREFIX );
							}
						}
						if(paravent)
							pdc->SelectObject(&mid);
						else
							pdc->SelectObject(&miw);
						rct.top+=hauteur/30;
						rct.bottom=rct.top+hauteur/25;
						rct.left=(LONG)10;
						if(paravent)
							rct.right=(LONG)((400));
						else
							rct.right=(LONG)((300));
						CString cat=categorie;
						if(ticimp==1)
						{
							temp1=cat+" ";
							cat=certnum;
							temp1+=cat;
							temp1+=" ";
							temp1+=extrait;
							temp2.Format(" V%.3f",fversion/1000);
							temp1+=temp2;
							printsigtxt=temp1;
							pdc->DrawText(temp1,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP|DT_NOPREFIX );
						}
					}
					temp=temp+"|"+sign+"\r\n";
				}
				else
					temp=temp+"\r\n";
				if(CWrite(opendir,temp,1))//écriture ligne de ticket
				{
					if(infocert)
					{
						sticket=sign;
					}
				}
				else
				{
					if(infocert)
					{
						FonctionEditeur("Erreur écriture fichier Data");
					}
					return 0;
				}
			}
			if(!paravent)
			{
				xForm.eM11 = (FLOAT) -1.0; 
				xForm.eM12 = (FLOAT) 0.0; 
				xForm.eM21 = (FLOAT) 0.0; 
				xForm.eM22 = (FLOAT) -1.0; 
				xForm.eDx  = (FLOAT) 590; //580
				xForm.eDy  = (FLOAT) 840; 
				pdc->SetWorldTransform(&xForm); 
			}
			InterlockedExchange(&artro,1);
			return 1;
		}
		return 0;
	}
	else
	{
		AfxMessageBox("Erreur d'impression Entree");
		return 0;
	}
}

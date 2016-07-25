#include "stdafx.h"
#include "Concerto.h"
#include "ConcertoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void CConcertoDlg::PrintConso(CDC* pdc,int idx,CString ticket,CString libelle,CString prix,CString tvatxt1,CString tvatxt2,CString part,CBitmap* pcodebarre,int fenter) 
{
	CString temp;
	CString temp1;
	CString temp2;
	CString temp3;
	CString ntemp;
	CString date;
	CString page;
	CString vsht;
	CString vsttc;
	CString haut;
	CString larg;
	CString pox;
	CString txtvaltva1;
	CString txtvaltva2;
	CString txtprixht;
	CTime ct;
	ct=CTime::GetCurrentTime();
	date=ct.Format("%d/%m/%Y  %H:%M");
	CDC m_Cdc;
	CRect rect;
	CRect butrect;
	CRect rct;
	CFont tf;
	CFont mic;
	CFont mid;
	CFont miw;
	CFont mil;
	CFont cbfont;
	double valtva1;
	double valtva2;
	double valht;
	double tauxtva1;	
	double tauxtva2;
	double valprix;
	float plargeur;
	float phauteur;
	float x;
	float y;
	float xl1;
	int largeur;//
	int hauteur;//
	int bc;//
	COLORREF pencolor=0x00000000;
	COLORREF blancolor=0x00FFFFFF;
	CPen dashpen(PS_DASH,1,pencolor);
	CPen finepen(PS_SOLID,2,pencolor);
	CBrush br;
	br.CreateSolidBrush(pencolor);
	XFORM xForm;
	if(noprint)
	{
		if(wlargeur>whauteur)				
			plargeur=(float)wlargeur/6;
		else
			plargeur=(float)wlargeur/2;
		phauteur=(float)whauteur/2;
		x=0;
		lmarge=0;
		rmarge=0;
		//cdc.Rectangle(60,5,xl1-5,340);
		rct.top=tsorg;
		rct.bottom=whauteur;
		bc=(0xFFFFFF);
		rct.left=0;
		if(wlargeur>whauteur)				
			rct.right=wlargeur/6;
		else
			rct.right=wlargeur/2;
		pdc->FillSolidRect(&rct,bc);
		hauteur= 770;
	}
	else
	{
		pdc->SetGraphicsMode(GM_ADVANCED);
		pdc->GetWorldTransform(&xForm);
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
				xForm.eDx  = (FLOAT) invxt; 
				xForm.eDy  = (FLOAT) invyt; 
			}
			else
			{
				if(printername.Find("Citizen CL-S400DT")!=-1)
				{
					xForm.eM11 = (FLOAT) -1.0; 
					xForm.eM12 = (FLOAT) 0.0; 
					xForm.eM21 = (FLOAT) 0.0; 
					xForm.eM22 = (FLOAT) -1.0; 
					if(paravent)
					{
						xForm.eDx  = (FLOAT) 680; 
						xForm.eDy  = (FLOAT) 870;
					}
					else
					{
						xForm.eDx  = (FLOAT) 640; 
						xForm.eDy  = (FLOAT) 820;
					}
				}
			}
		}
		pdc->SetWorldTransform(&xForm);
		if(printername.Find("Citizen CL-S400DT")!=-1)
			plargeur=(float)pdc->GetDeviceCaps(HORZRES)/(float)1.7;//-(2*cdc.GetDeviceCaps(PHYSICALOFFSETX)));
		else
			plargeur=(float)pdc->GetDeviceCaps(HORZRES);//-(2*cdc.GetDeviceCaps(PHYSICALOFFSETX)));
		phauteur=(float)pdc->GetDeviceCaps(VERTRES);//-(2*cdc.GetDeviceCaps(PHYSICALOFFSETY)));
		x=(float)pdc->GetDeviceCaps(PHYSICALOFFSETX);
		hauteur= 1000;
	}
	xl1=(plargeur)-rmarge;
	largeur=(int)(plargeur/2.1);//
	tf.CreateFont((int)hauteur/15,
		(int)plargeur/40,
		0,
		0,
		1 ,//Epaisseur
		0,
		0,
		0,
		DEFAULT_CHARSET,
		OUT_TT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		NONANTIALIASED_QUALITY,//ANTIALIASED_QUALITY,//PROOF_QUALITY,
		DEFAULT_PITCH|FF_DONTCARE,
		"ARIAL");
	mic.CreateFont((int)hauteur/20,
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
	mid.CreateFont((int)hauteur/16,
		(int)plargeur/35,
		0,
		0,
		1200 ,//Epaisseur
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
	cbfont.CreateFont(hauteur/35,
		0,//wlargeur/200,
		0,
		0,
		600,//Epaisseur
		0,
		0,
		0,
		DEFAULT_CHARSET,
		OUT_TT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		NONANTIALIASED_QUALITY,//ANTIALIASED_QUALITY,//PROOF_QUALITY,
		DEFAULT_PITCH|FF_DONTCARE,
		"ARIAL");
	mil.CreateFont((int)hauteur/40,
		(int)plargeur/80,
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
	if(!noprint&&(printername.Find("KPSX")!=-1||printername.Find("KMGA")!=-1)||printername.Find("Citizen CL-S400DT")!=-1||noprint)
	{
		y=(float)(150);
		int i=midline;
		if(noprint)
		{
			tsorg=3*i/4;
			pdc->SelectObject(&dashpen);
			pdc->MoveTo(0,tsorg);
			pdc->LineTo((int)xl1,tsorg);
		}
		else
			if(paravent)
				tsorg=midline+50;
			else
				tsorg=midline;

		rct.top=tsorg;
		/*if(noprint)
			rct.bottom=rct.top+(LONG)hauteur/7;
		else
			rct.bottom=rct.top+(LONG)y;*/
		tsorg+=hauteur/100;
		y=(float)(hauteur/15);
		rct.top=tsorg;
		rct.bottom=rct.top+(LONG)y;
		bc=(0xFFFFFF);
		pdc->SetBkColor(bc);
		if(printername.Find("Citizen CL-S400DT")!=-1)
		{
			rct.left=(LONG)lmarge;
			rct.right=(LONG)xl1;
		}
		else
		{
			rct.left=(LONG)lmarge+10;
			rct.right=(LONG)xl1-10;
		}
		if(part!="NUL")
		{
			pdc->SelectObject(&miw);
			pdc->DrawText(nom,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP|DT_NOPREFIX );
			rct.top+=hauteur/30;
			rct.bottom+=hauteur/30;
			pdc->SelectObject(&mil);
			pdc->DrawText(txtc[72]+" : "+siret+" "+txtc[95]+" : "+naf,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP|DT_NOPREFIX  );
			pdc->SelectObject(&miw);
			rct.top+=hauteur/40;
			rct.bottom+=hauteur/40;
			//MessageBox("x"+part+"x");
			if(part.Left(1)=="1"||part=="   ")
			{
				if(ticket.Left(1)=="P")
				{
					if(libelle.Find("$",0)==0)
						temp1=libelle.Mid(1);
					else
						if(atof(prix)==0)
							temp1=txtc[91];//"ENTREE EXO"
						else
							temp1=txtc[96];//"ENTREE PAYEE
					//temp=temp1+" :"+prix+" "+cur;
				}
				else
				{
					if(fenter==1)
					{
						if(libelle.Find("$",0)==0)
							temp1=libelle.Mid(1);
						else
						{
							if(atof(prix)==0)
								temp1=txtc[91];//"ENTREE EXO"
							else
								temp1=txtc[90];//"ENTREE PAYANTE"
						}
						//temp=temp1+" :"+prix+" "+cur;
					}
					else
						if(libelle!="")
						{
							if(libelle.Find("$",0)==0)
								temp1=libelle.Mid(1);
							else
							{
								if(atof(prix)==0)
									temp1=txtc[91];//"ENTREE EXO"
								else
									temp1=libelle;
								//temp=temp1+" :"+prix+" "+cur;
							}
						}
						else
						{
							if(atof(prix)==0)
								temp1=txtc[91];//"ENTREE EXO"
							else
								temp1=txtc[90];//"ENTREE PAYANTE"
							//temp=temp1+" :"+prix+" "+cur;
						}
				}
				pdc->DrawText(temp1+" :"+prix+" "+cur+" "+txtc[76],-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP|DT_NOPREFIX );//|DT_MODIFYSTRING);*/
			}
			if(nc==0)
			{
				rct.top+=hauteur/30;
				rct.bottom+=hauteur/30;
				if(fenter==0&&atoi(prix)==0)//EXO
					temp3=txtc[92];//"EXO"
				else
					temp3=txtc[85];//"Prix"
				temp1=txtc[76];//"TTC"
				temp2=txtc[134];//"HT"
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
				pdc->SelectObject(&mil);
				pdc->DrawText(temp,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP|DT_NOPREFIX  );
				pdc->SelectObject(&miw);
			}

			rct.top+=hauteur/40;
			rct.bottom+=hauteur/40;
			temp1=txtc[99];//"Valable le"
			pdc->DrawText("N° "+ticket+" "+part+" "+temp1+" "+date,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP|DT_NOPREFIX  );//du
			if(nc==0)
			{
				rct.top+=hauteur/30;
				rct.bottom+=hauteur/30;
				if(lic[0]+lic[1]+lic[2]+lic[3]+lic[4]+lic[5]!="")//impression licence supprimée
				{
					pdc->SelectObject(&mil);
					rct.left=(LONG)lmarge+10;
					rct.right=(LONG)((xl1-10)/4);
					pdc->DrawText(txtc[100]+":",-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP|DT_NOPREFIX  );//Lic.
					rct.left=rct.right;
					rct.right=(LONG)(2*(xl1-10)/4);
					pdc->DrawText(lic[0],-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP|DT_NOPREFIX  );
					rct.left=rct.right;
					rct.right=(LONG)(3*(xl1-10)/4);
					pdc->DrawText(lic[1],-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP|DT_NOPREFIX  );
					rct.left=rct.right;
					rct.right=(LONG)(4*(xl1-10)/4);
					pdc->DrawText(lic[2],-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP|DT_NOPREFIX  );
					if(lic[3]!=""||lic[4]!=""||lic[5]!="")
					{
						rct.top+=hauteur/50;
						rct.bottom=rct.top+hauteur/50;
						rct.left=(LONG)((xl1-10)/4);
						rct.right=(LONG)(2*(xl1-10)/4);
						pdc->DrawText(lic[3],-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP|DT_NOPREFIX  );
						rct.left=rct.right;
						rct.right=(LONG)(3*(xl1-10)/4);
						pdc->DrawText(lic[4],-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP|DT_NOPREFIX  );
						rct.left=rct.right;
						rct.right=(LONG)(4*(xl1-10)/4);
						pdc->DrawText(lic[5],-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP|DT_NOPREFIX  );
					}
				}
				rct.left=(LONG)lmarge+10;
				rct.right=(LONG)xl1;
				rct.top+=hauteur/50;
				rct.bottom+=hauteur/30;
				pdc->SelectObject(&cbfont);
				pdc->DrawText(printsigtxt,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP|DT_NOPREFIX  );//du
			}
		}

	}
	tsorg+=rct.bottom;
	//PaperCut(pdc);
	if(!noprint&&printername.Find("KPSX")==-1&&printername.Find("KMGA")==-1&&printername.Find("Citizen CL-S400DT")==-1)
		pdc->EndPage();
	else
		if(noprint)
		{
			pdc->SelectObject(&finepen);
			tsorg=rct.top+=hauteur/10;
			sp.GetClientRect(&rect);
			SimTicketRect(pdc,rect);
		}
}

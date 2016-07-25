#include "stdafx.h"
#include "Concerto.h"
#include "ConcertoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int CConcertoDlg::PrintPrevente(CDC* pdc,int idx,CString billet,CString libelle,CString prix,CString tpmtxt,CString tvatxt,CString spectacle,CString ticket,CString ntpm,CString place) 
{
	CString txtsign;
	CString sign;
	CString extrait;
	CString temp;
	CString tvatxt1;
	CString tvatxt2;
	CString temp1;
	CString temp2;
	CString temp3;
	CString ntemp;
	CString ftxt;
	CString fread;
	CString date;
	CString page;
	CString vsht;
	CString vsttc;
	CString haut;
	CString larg;
	CString pox;
	CString dir;
	CString contdir;
	CString buf;
	CString tch;
	CString tcpt;
	CString txtvaltva1;
	CString txtvaltva2;
	CString txtprixht;
	CTime ct;
	ct=CTime::GetCurrentTime();
	date=ct.Format("%d/%m/%Y  %H:%M:%S");
	CDC m_Cdc;
	CRect rect;
	//CRect butrect;
	CRect rct;
	CFont num;
	CFont df;
	CFont tf;
	CFont tpf;
	CFont mic;
	CFont mid;
	CFont miw;
	CFont mil;
	CFont mtp;
	CFont cbfont;
	float plargeur;
	float phauteur;
	float cblmarge;
	float cblarg;
	float x;
	float xl1;
	double valtva1;
	double valtva2;
	double valht;
	double tauxtva1;	
	double tauxtva2;
	double valprix;
	int largeur;//
	int hauteur;//
	int lg;//
	int bc;//
	int i;//
	int j;//
	int fi;
	int gdcx;//
	HANDLE hf;
	DWORD nbw;
	XFORM xForm;
	COLORREF pencolor=0x00000000;
	COLORREF blancolor=0x00FFFFFF;
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
			//cdc.Rectangle(60,5,xl1-5,340);
			rct.top=0;
			rct.bottom=tsorg;
			bc=(0xFFFFFF);
			rct.left=0;
			rct.right=(int)plargeur;
			pdc->FillSolidRect(&rct,bc);
			if(wlargeur>whauteur)				
			{
				cblmarge=plargeur/5;//-50;
				cblarg=5*plargeur/5;
			}
			else
			{
				cblmarge=plargeur/7;//-50;
				cblarg=5*plargeur/5;
			}
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
						xForm.eDx  = (FLOAT) invxt; 
						xForm.eDy  = (FLOAT) invyt; 
					}
					else
					{
						if(printername.Find("Citizen CL-S400DT")!=-1)
						{
							xForm.eM11 = (FLOAT) -1.00; 
							xForm.eM12 = (FLOAT) 0.0; 
							xForm.eM21 = (FLOAT) 0.0; 
							xForm.eM22 = (FLOAT) -1.00; 
							xForm.eDx  = (FLOAT) 590; 
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
			if(paravent)
			{
				cblmarge=(7*(float)gdcx)/18;
				cblarg=(float)gdcx;
			}
			else
				if(printername.Find("Citizen CL-S400DT")!=-1&&!paravent)
				{
					cblmarge=(4*(float)gdcx)/18;
					cblarg=(float)gdcx;
				}
				else
				{
					cblmarge=((float)gdcx)/7;
					cblarg=(float)gdcx;
				}
		}
		CPen dashpen(PS_DASH,1,pencolor);
		xl1=(plargeur)-rmarge;
		largeur=(int)(plargeur/2.1);//
		if(paravent)
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
			(int)plargeur/70,
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
		mil.CreateFont((int)hauteur/35,
			(int)plargeur/60,
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
		mtp.CreateFont((int)hauteur/30,
			(int)gdcx/60,
			0,
			0,
			400 ,//Epaisseur
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
		cbfont.CreateFont(hauteur/35,
			0,//wlargeur/200,
			0,
			0,
			400,//Epaisseur
			0,
			0,
			0,
			DEFAULT_CHARSET,
			OUT_TT_PRECIS,
			CLIP_DEFAULT_PRECIS,
			NONANTIALIASED_QUALITY,//ANTIALIASED_QUALITY,//PROOF_QUALITY,
			DEFAULT_PITCH|FF_DONTCARE,
			"ARIAL");
		i=midline;
		pdc->SetTextColor(0x000000);
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
		{
			if(paravent)
				xl1=(float)10*plargeur/8;
			else
				xl1=(plargeur)-rmarge;
		}	
		int toporg=DrawLogo(pdc,xl1);
		if(paravent)
			toporg=0;
		float y=(float)hauteur/15;//(150);
		if(noprint)
			rct.top=toporg+(int)(y/2);
		else
			rct.top=toporg;//+(int)(y/100);
		rct.bottom=rct.top+(LONG)y;
		if(paravent&&logo)
			rct.left=(5*(LONG)xl1)/12;
		else
			rct.left=(LONG)((10));
		rct.right=(LONG)((xl1-10));
		//rct.top+=hauteur/20;//60;
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
		if(logo==0||paravent)
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
					rct.top+=hauteur/13;//60;
					rct.bottom+=hauteur/13;//60;
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
			pdc->DrawText(adresse1,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP|DT_NOPREFIX );
			rct.top+=hauteur/30;
			rct.bottom+=hauteur/30;
		}
		if(adresse2!="")
		{
			pdc->DrawText(adresse2+" "+pays,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP|DT_NOPREFIX );
			rct.top+=hauteur/30;
			rct.bottom+=hauteur/30;
		}
		if(siret!="")
		{
			pdc->SelectObject(&miw);
			pdc->DrawText(txtc[72]+" : "+siret+" "+txtc[95]+" : "+naf,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP|DT_NOPREFIX );//Siret
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
		pdc->DrawText(mentionp,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP|DT_NOPREFIX );
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
		pdc->DrawText(date,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP |DT_NOPREFIX);
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

		rct.left=(LONG)10;
		rct.right=(LONG)((xl1-10));
		pdc->SelectObject(&mic);
		if(libel1[idx].Find("$",0)==0)// Enlève un $ éventuellement présent en première position
			libelle.Replace("$","");
		temp1=txtc[96];//"ENTREE PAYEE"
		pdc->DrawText(temp1,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP|DT_NOPREFIX);//"ENTREE PAYEE"|DT_MODIFYSTRING);
		pdc->SelectObject(&mic);
		if(paravent)
		{
			rct.top+=hauteur/25;
			rct.bottom+=hauteur/25;
		}
		else
			if(logo)
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
			if(logo)
				pdc->SelectObject(&mic);
			else
				pdc->SelectObject(&df);
		temp3=txtc[85];//"Prix"
		temp1=txtc[76];//"TTC"
		temp2=txtc[134];///"HT"
		temp=temp3+" "+prix+cur+" "+temp1;
		pdc->DrawText(temp,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP|DT_NOPREFIX );
		if(place!="")
		{//Pl.
			rct.left=rct.right;
			rct.right=(LONG)((xl1-10));
			temp1=txtc[93];//Pl.
			pdc->DrawText(temp1+" "+place,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP|DT_END_ELLIPSIS|DT_NOPREFIX);//|DT_MODIFYSTRING);*************
		}
				temp3=txtc[62];//TVA
				tauxtva1=atof(tvatxt);
				tauxtva2=0;
				valprix=atof(prix);
				valtva1=(valprix-(valprix/(1+(tauxtva1/100))));
				valtva2=0;
				valht=valprix-valtva1-valtva2;

				txtvaltva1.Format("%.2f"+cur,valtva1);
				txtvaltva2.Format("%.2f"+cur,valtva2);
				txtprixht.Format("%.2f"+cur,valht);
				if(tauxtva2==0)
					temp=temp2+":"+txtprixht+" "+temp3+" "+tvatxt+"%:"+" "+txtvaltva1;
				else
					temp=temp2+":"+txtprixht+" "+temp3+" "+tvatxt+"%:"+" "+txtvaltva1+" "+temp3+" "+tvatxt2+"%:"+" "+txtvaltva2;
				if(paravent||logo)
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
				pdc->DrawText(temp,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP|DT_NOPREFIX );
			rct.top+=hauteur/38;
			rct.bottom+=hauteur/38;
		if(printername.Find("Citizen CL-S400DT")!=-1&&!paravent)
			rct.left=0;
		else
			rct.left=(LONG)10;
		rct.right=(LONG)((xl1-10));
		if(paravent||logo==0)
			pdc->SelectObject(&tf);
		else
			pdc->SelectObject(&mic);
		pdc->DrawText(libelle,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP|DT_NOPREFIX);//|DT_MODIFYSTRING);
		rct.left=(LONG)10;
		rct.right=(LONG)((xl1-10));
		if(paravent||logo==0)
		{
			rct.top+=hauteur/15;//40;
			rct.bottom+=hauteur/15;//40;
		}
		else
		{
			rct.top+=hauteur/25;
			rct.bottom+=hauteur/25;
		}
		pdc->SelectObject(&mid);
		if(((perso[idx]&0xF000)>>12)>1)
			temp1=txtc[156];//Valable à partir du
		else
			temp1=txtc[98];//Valable le
		temp="N° "+ticket+" "+temp1+": "+ spectacle;
		pdc->DrawText(temp,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP|DT_NOPREFIX  );//Valable le
		while(ntpm.GetLength()<8)
			ntpm="0"+ntpm;
		temp=billet.Mid(4,2);
		idx=atoi(temp);
		temp=temp+ntpm;//temp+ntpm
		i=0;
		while(i<10)//Crée un N° unique en fonction de N° touche et crypt
		{
			tch=temp.Mid(9-i,1);
			j=atoi(tch);
			j=j+i;
			if(j>9)
				j=j-10;
			tch=cript[j];
			tcpt=tch+tcpt;
			i++;
		}
		buf=poste.Right(1)+temp+";\r\n";// génération N° ticket
		GetBilletCode(poste.Right(1)+tcpt);
		int cent=(int)((xl1+10)+(lmarge+10))/2;
		tsorg=rct.top+hauteur/28;
		if(paravent)
			PrintBarre(pdc,(int)(7*cblmarge/6),tsorg,(int)cblarg,hauteur/10+tsorg);
		else
			PrintBarre(pdc,(int)(4*cblmarge/3),tsorg,(int)cblarg,hauteur/12+tsorg);
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
		if(!noprint||(noprint&&sp.IsWindowVisible()))
		{
			// enregistrement ticket
			if(dopen.GetLength()==0)
			{
				CTime tim=CTime::GetCurrentTime();
				if(InitCaisse(tim)==0)
				{
					if(infocert)
					{
						FonctionEditeur("Erreur initialisation fichier Data");
					}
					return 0;
				}
			}
			CString TGTZ;
			CString TGTP;
			TGTZ.Format("%.2f",GTZ);
			TGTP.Format("%.2f",GTP);
			txtvaltva1.Format("%.2f",val1[idx]);
			tvatxt1.Format("%.2f",tva1[idx]);
			temp=ticket+"    ;"+date+";"+prix+";"+tvatxt+";"+prix+";;;;"+TGTZ+";"+TGTP;
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
				spart[5]=sticket;
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
						pdc->DrawText("Lic. :",-1,&rct,DT_LEFT|DT_SINGLELINE|DT_TOP|DT_NOPREFIX );
						rct.left=rct.right;
						rct.right=rct.left+lg;
						pdc->DrawText(lic[0],-1,&rct,DT_LEFT|DT_SINGLELINE|DT_TOP|DT_NOPREFIX );
						rct.left=rct.right;
						rct.right=rct.left+lg;
						pdc->DrawText(lic[1],-1,&rct,DT_LEFT|DT_SINGLELINE|DT_TOP|DT_NOPREFIX );
						rct.left=rct.right;
						rct.right=rct.left+lg;
						pdc->DrawText(lic[2],-1,&rct,DT_LEFT|DT_SINGLELINE|DT_TOP|DT_NOPREFIX );
						if(lic[3]!=""||lic[4]!=""||lic[5]!="")
						{
							rct.top+=hauteur/35;
							rct.bottom=rct.top+hauteur/35;
							rct.left=(LONG)((xl1-10)/20);
							rct.right=rct.left+lg;
							pdc->DrawText(lic[3],-1,&rct,DT_LEFT|DT_SINGLELINE|DT_TOP|DT_NOPREFIX );
							rct.left=rct.right;
							rct.right=rct.left+lg;
							pdc->DrawText(lic[4],-1,&rct,DT_LEFT|DT_SINGLELINE|DT_TOP|DT_NOPREFIX );
							rct.left=rct.right;
							rct.right=rct.left+lg;
							pdc->DrawText(lic[5],-1,&rct,DT_LEFT|DT_SINGLELINE|DT_TOP |DT_NOPREFIX);
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
			if(CWrite(opendir,temp,1))
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
		CString pathcontrol="";
		if((!sp.IsWindowVisible()&&noprint)||!noprint)
		{
			// ******************* Recherche d'un fichier existant ******************
			for(fi=1;fi<=16;fi++)
			{
				ftxt.Format("0%u",fi);
				pathcontrol=controldir+"\\"+poste+"tempcontrol"+ftxt.Right(2)+".dat";
				hf=(CreateFile(pathcontrol,GENERIC_READ|GENERIC_WRITE ,0,NULL,OPEN_EXISTING,FILE_FLAG_WRITE_THROUGH|FILE_ATTRIBUTE_NORMAL,NULL));
				if(hf!=INVALID_HANDLE_VALUE)
				{
					ReadFile(hf,fread.GetBuffer(11),11,&nbw,NULL);
					fread.ReleaseBuffer(nbw);
					if(fread.Mid(1,2)==buf.Mid(1,2))
						goto next;
					CloseHandle(hf);
				}
			}
			if(fi>16)
			{
				for(int fi=1;fi<=16;fi++)
				{
					ftxt.Format("0%u",fi);
					if((master&&alone==0)||master==0)
						pathcontrol=controldir+"\\"+poste+"tempcontrol"+ftxt.Right(2)+".dat";
					else
						if(alone==1)
							pathcontrol=controldir+"\\alone"+poste+"control"+ftxt.Right(2)+".dat";
					hf=(CreateFile(pathcontrol,GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING,FILE_FLAG_WRITE_THROUGH|FILE_ATTRIBUTE_NORMAL,NULL));
					if(hf==INVALID_HANDLE_VALUE)
						break; // Vérification emplacement libre pour nouveau fichier
					else
						CloseHandle(hf);
				}
			}
			hf=(CreateFile(pathcontrol,GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING,FILE_FLAG_WRITE_THROUGH|FILE_ATTRIBUTE_NORMAL,NULL));
			if(hf==INVALID_HANDLE_VALUE)
			{
reopen:;
				if((hf=(CreateFile(pathcontrol,GENERIC_READ|GENERIC_WRITE,0,NULL,CREATE_NEW,FILE_FLAG_WRITE_THROUGH|FILE_ATTRIBUTE_NORMAL,NULL)))==INVALID_HANDLE_VALUE)
				{
					Sleep(100);
					goto reopen;

				}
			}
next:;
			SetFilePointer(hf,NULL,NULL,FILE_END);
			WriteFile(hf,buf.GetBuffer(),buf.GetLength(),&nbw,NULL);
			CloseHandle(hf);
			temp=netcontdir+"\\"+poste+"tempcontrol"+ftxt.Right(2)+".dat";
			if(master==0&&netcontdir!=controldir)
			{
retry:;
				if(!CopyFile(pathcontrol,temp,FALSE))
				{
					Sleep(50);
					goto retry;
				}
				DeleteFile(pathcontrol);
			}
		}
		if(!noprint)
		{
		}
		else
		{
			pdc->SelectObject(&finepen);
			tsorg=rct.top+=hauteur/15;
			sp.GetClientRect(&rect);
			//SimTicketRect(pdc,rect);
		}
		InterlockedExchange(&artro,1);
		return 1;
	}
	else
	{
		AfxMessageBox("Erreur d'impression Entree");
		return 0;
	}
}

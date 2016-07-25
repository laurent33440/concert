#include "stdafx.h"
#include "Concerto.h"
#include "ConcertoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void CConcertoDlg::PrintCaisse(CString GTZtxt,CString ouverture,CString cloture,CString gta) 
{
	CString temp;
	CString temp1;
	CString biltxt;
	CString ntemp;
	CString date;
	CString page;
	CString vsht;
	CString vsttc;
	CString haut;
	CString larg;
	CString pox;
	CTime ct;
	ct=CTime::GetCurrentTime();
	date=ct.Format("%d/%m/%Y  %H:%M:%S");
	CDC m_Cdc;
	CRect rect;
	//CRect butrect;
	CRect rct;
	CFont tf;
	CFont tcb;
	CFont mic;
	CFont mid;
	CFont miw;
	float plargeur;
	float phauteur;
	double ht;
	double ttva;
	float x;
	float y;
	float xl1;
	float x1;
	int largeur;//
	int hauteur;//
	int bc;//
	int i;//
	int fmarge;
	XFORM xForm;
	COLORREF pencolor=0x00000000;
	COLORREF blancolor=0x00FFFFFF;
	CPen finepen(PS_SOLID,1,pencolor);
	CDC* pdc=NULL;	
	CDC* pdcw=NULL;
	InterlockedExchange(&PJOB,0);
	CPrintDialog prt(FALSE);
	if(noprint)
	{
		pdc=sp.GetDC();
	}
	else
	{	
		prt.GetDefaults();
		m_Cdc.Attach(prt.m_pd.hDC);
		pdc=&m_Cdc;
	}
	if(pdc->m_hDC!=NULL)
	{
		fmarge=0;
		if(noprint)
		{
			plargeur=(float)wlargeur/2;
			phauteur=(float)tsorg;
			x=0;
			lmarge=0;
			rmarge=0;
			//cdc.Rectangle(60,5,xl1-5,340);
			largeur=(int)(plargeur/2.1);//
			hauteur= 700;
		}
		else
		{
			InterlockedExchange(&PJOB,pdc->StartDoc("Cloture billetterie"));
			if(printername.Find("Citizen CL-S400DT")!=-1)
				plargeur=(float)pdc->GetDeviceCaps(HORZRES)/2;//-(2*cdc.GetDeviceCaps(PHYSICALOFFSETX)));
			else
				plargeur=(float)pdc->GetDeviceCaps(HORZRES)-40;//-(2*cdc.GetDeviceCaps(PHYSICALOFFSETX)));
			largeur=pdc->GetDeviceCaps(HORZRES);//-(2*cdc.GetDeviceCaps(PHYSICALOFFSETX)));
			phauteur=(float)pdc->GetDeviceCaps(VERTRES);//-(2*cdc.GetDeviceCaps(PHYSICALOFFSETY)));
			x=(float)pdc->GetDeviceCaps(PHYSICALOFFSETX);
			largeur=(int)(plargeur/2.1);//
			hauteur= 1000;
		}
		lmarge=0;
		x1=(float)lmarge+fmarge+20;
		xl1=(plargeur)-rmarge-20;
		tcb.CreateFont((int)hauteur/15,
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
		mic.CreateFont((int)hauteur/20,
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
		
		//pdc->Rectangle(60,5,xl1-5,340);
		y=(float)(150);
		rct.top=0;
		if(noprint)
			rct.bottom=(LONG)tsorg;
		else
			rct.bottom=(LONG)y;
		bc=(0xFFFFFF);
		pdc->SetBkColor(bc);
		rct.left=fmarge;
		rct.right=(LONG)xl1;
		pdc->FillSolidRect(&rct,bc);
//IMPRESSION SIMULEE
		if(noprint)//printername.Find("KPSX")==-1&&printername.Find("KMGA")==-1&&printername.Find("Citizen CL-S400")==-1)
		{
			CPen boldpen(PS_SOLID,hauteur/200,pencolor);
			if(!noprint)
			{
				pdc->StartPage();
			}
			rct.left=(LONG)x1+10;
			rct.right=(LONG)xl1-10;
			pdc->SelectObject(&tf);
			pdc->DrawText(nom,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP|DT_NOPREFIX );
			rct.top+=hauteur/50;//20;
			rct.bottom=rct.top+hauteur/7;//20;

			if(adresse1!="")
			{
				rct.top+=hauteur/25;//40;
				rct.bottom+=hauteur/25;//40;
				pdc->SelectObject(&mid);
				pdc->SelectObject(&mid);
				pdc->DrawText(adresse1,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP );
			}

			if(adresse2!="")
			{
				rct.top+=hauteur/25;//40;
				rct.bottom+=hauteur/25;//40;
				pdc->SelectObject(&mid);
				pdc->SelectObject(&mid);
				pdc->DrawText(adresse2,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP|DT_NOPREFIX  );
			}

			rct.top+=hauteur/25;//40;
			rct.bottom+=hauteur/25;//40;
			rct.left=(LONG)x1+10;
			rct.right=(LONG)((xl1-10));
			pdc->SelectObject(&miw);
			pdc->DrawText(txtc[72]+" : "+siret+" "+txtc[95]+" : "+naf,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP );//Siret

			rct.top+=hauteur/25;//40;
			rct.bottom+=hauteur/25;//40;
			pdc->SelectObject(&mid);
			biltxt=txtc[100]+" "+poste;//BILLETTERIE N°
			pdc->DrawText(biltxt,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP|DT_NOPREFIX  );

			rct.top+=hauteur/20;//50;
			rct.bottom+=hauteur/20;//50;
			pdc->SelectObject(&mid);
			if(GTZtxt!="Non clôturée")
			{
				if(hist==0)
					temp.Format(txtc[102]+" %u",RAZ);
				else
					temp.Format(txtc[102]+" %u",HRAZ);

			}
			else
			{
				temp=txtc[103];//"GTZ  : Non clôturée"
			}
			pdc->DrawText(temp,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP|DT_NOPREFIX  );

			rct.top+=hauteur/16;//60;
			rct.bottom+=hauteur/16;//60;
			pdc->SelectObject(&miw);
			pdc->SelectObject(&boldpen);
			pdc->MoveTo((int)(x1+10),rct.top-hauteur/100);
			pdc->LineTo((int)(xl1-10),rct.top-hauteur/100);
			temp=txtc[38]+": "+ouverture;//Ouverture
			pdc->DrawText(temp,-1,&rct,DT_LEFT|DT_SINGLELINE|DT_TOP|DT_NOPREFIX   );
			rct.top+=hauteur/25;//40;
			rct.bottom+=hauteur/25;//40;
			pdc->SelectObject(&miw);
			temp=txtc[39]+"    : "+cloture;//Clôture
			pdc->DrawText(temp,-1,&rct,DT_LEFT|DT_SINGLELINE|DT_TOP|DT_NOPREFIX   );

			rct.top+=hauteur/16;//60;
			rct.bottom+=hauteur/16;//60;
			pdc->SelectObject(&miw);
			pdc->SelectObject(&boldpen);
			pdc->MoveTo((int)(x1+10),rct.top-hauteur/100);
			pdc->LineTo((int)(xl1-10),rct.top-hauteur/100);
			rct.left=(LONG)x1+10;
			rct.right=(LONG)((xl1-10));
			pdc->SelectObject(&mid);
			pdc->DrawText(txtc[104],-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP|DT_NOPREFIX );//"CA VENTES"

			rct.top+=hauteur/16;//60;
			rct.bottom+=hauteur/16;//60;
			rct.left=(LONG)x1+10;
			rct.right=(LONG)(2*(xl1-10)/5);
			pdc->SelectObject(&miw);
			pdc->DrawText(txtc[105]+" : ",-1,&rct,DT_LEFT|DT_SINGLELINE|DT_TOP|DT_NOPREFIX );//TTC Encaissé

			rct.left=rct.right;
			rct.right=(LONG)(3*(xl1-10)/5);
			pdc->SelectObject(&miw);
			temp.Format("%u",nbticktot-nbtickan);
			pdc->DrawText(temp,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP|DT_NOPREFIX  );

			rct.left=rct.right;
			rct.right=(LONG)(5*(xl1-10)/5);
			pdc->SelectObject(&miw);
			temp.Format("%.2f",ca);
			pdc->DrawText(temp,-1,&rct,DT_RIGHT|DT_SINGLELINE|DT_TOP|DT_NOPREFIX  );
			ht=0;
			ttva=0;
			i=0;
			while(i<10)//catva[i]!=0&&
			{
				ht+=catva[i]/(1+(tvaca[i]/100));
				ttva+=catva[i]-(catva[i]/(1+(tvaca[i]/100)));
				i++;
			}
			rct.top+=hauteur/25;//40;
			rct.bottom+=hauteur/25;//40;
			rct.left=(LONG)x1+10;
			rct.right=(LONG)(2*(xl1-10)/5);
			pdc->SelectObject(&miw);
			pdc->DrawText(txtc[106]+" : ",-1,&rct,DT_LEFT|DT_SINGLELINE|DT_TOP|DT_NOPREFIX );//HT encaissé

			rct.left=rct.right;
			rct.right=(LONG)(5*(xl1-10)/5);
			pdc->SelectObject(&miw);
			temp.Format("%.2f",ht);
			pdc->DrawText(temp,-1,&rct,DT_RIGHT|DT_SINGLELINE|DT_TOP|DT_NOPREFIX  );


			i=0;
			while(i<10)
			{
				if(catva[i]!=0)
				{
					rct.top+=hauteur/25;//40;
					rct.bottom+=hauteur/25;//40;
					rct.left=(LONG)x1+10;
					rct.right=(LONG)(2*(xl1-10)/5);
					pdc->SelectObject(&miw);
					pdc->DrawText(txtc[107]+"   : ",-1,&rct,DT_LEFT|DT_SINGLELINE|DT_TOP|DT_NOPREFIX );//Montant TVA

					temp.Format("%.2f",tvaca[i]);
					temp=temp+"%";
					rct.left=rct.right;
					rct.right=(LONG)(3*(xl1-10)/5);
					pdc->SelectObject(&miw);
					pdc->DrawText(temp,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP|DT_NOPREFIX  );

					rct.left=rct.right;
					rct.right=(LONG)(5*(xl1-10)/5);
					pdc->SelectObject(&miw);
					temp.Format("%.2f",catva[i]-(catva[i]/(1+(tvaca[i]/100))));
					pdc->DrawText(temp,-1,&rct,DT_RIGHT|DT_SINGLELINE|DT_TOP|DT_NOPREFIX  );
				}
				i++;
			}

			rct.top+=hauteur/25;//40;
			rct.bottom+=hauteur/25;//40;
			rct.left=(LONG)x1+10;
			rct.right=(LONG)(2*(xl1-10)/5);
			pdc->SelectObject(&miw);
			pdc->DrawText(txtc[108]+" : ",-1,&rct,DT_LEFT|DT_SINGLELINE|DT_TOP|DT_NOPREFIX );//Total TVA

			rct.left=rct.right;
			rct.right=(LONG)(5*(xl1-10)/5);
			pdc->SelectObject(&miw);
			temp.Format("%.2f",ttva);
			pdc->DrawText(temp,-1,&rct,DT_RIGHT|DT_SINGLELINE|DT_TOP|DT_NOPREFIX  );
	//******************* ANNULES ******************************
			rct.top+=hauteur/14;//70;
			rct.bottom+=hauteur/14;//70;
			rct.left=(LONG)x1+10;
			rct.right=(LONG)((xl1-10));
			pdc->SelectObject(&mid);
			pdc->DrawText(txtc[109],-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP|DT_NOPREFIX );//"TICKETS ANNULES"

			rct.top+=hauteur/16;//60;
			rct.bottom+=hauteur/16;//60;
			rct.left=(LONG)x1+10;
			rct.right=(LONG)(2*(xl1-10)/5);
			pdc->SelectObject(&miw);
			pdc->DrawText(txtc[41]+" : ",-1,&rct,DT_LEFT|DT_SINGLELINE|DT_TOP|DT_NOPREFIX );//Annulés

			rct.left=rct.right;
			rct.right=(LONG)(3*(xl1-10)/5);
			pdc->SelectObject(&miw);
			temp.Format("%u",nbtickan);
			pdc->DrawText(temp,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP|DT_NOPREFIX  );

			rct.left=rct.right;
			rct.right=(LONG)(5*(xl1-10)/5);
			pdc->SelectObject(&miw);
			temp.Format("%.2f",can);
			pdc->DrawText(temp,-1,&rct,DT_RIGHT|DT_SINGLELINE|DT_TOP |DT_NOPREFIX );
			{
				rct.top+=hauteur/14;//70;
				rct.bottom+=hauteur/14;//70;
			}
			rct.left=(LONG)x1+10;
			rct.right=(LONG)((xl1-10));
			pdc->SelectObject(&mid);
			{
				pdc->DrawText(txtc[110],-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP|DT_NOPREFIX );//"CA PLU"
			}
			rct.top+=hauteur/16;//60;
			rct.bottom+=hauteur/16;//60;
			int i=0;
			do
			{
				if(hlibel1[i]==""&&hlibel2[i]=="")
					goto nextplu;
				rct.left=(LONG)x1+10;
				rct.right=(LONG)(1*(xl1-10)/10);
				pdc->SelectObject(&miw);
				temp.Format("%u",i);
				if(temp.GetLength()==1)
					temp="0"+temp;
				pdc->DrawText(temp,-1,&rct,DT_LEFT|DT_SINGLELINE|DT_TOP|DT_NOPREFIX );


				rct.left=rct.right;
				rct.right=(LONG)(6.5*(xl1-10)/10);
				pdc->SelectObject(&miw);
				pdc->DrawText(hlibel1[i]+" "+hlibel2[i],-1,&rct,DT_LEFT|DT_SINGLELINE|DT_TOP|DT_NOPREFIX );

				rct.left=rct.right;
				rct.right=(LONG)(7.5*(xl1-10)/10);
				pdc->SelectObject(&miw);
				temp.Format("%u",qteplu[i]);
				pdc->DrawText(temp,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP|DT_NOPREFIX  );

				rct.left=rct.right;
				rct.right=(LONG)(10*(xl1-10)/10);
				pdc->SelectObject(&miw);
				temp.Format("%.2f",valplu[i]);
				pdc->DrawText(temp,-1,&rct,DT_RIGHT|DT_SINGLELINE|DT_TOP|DT_NOPREFIX  );
				rct.top+=hauteur/25;//40;
				rct.bottom+=hauteur/25;//40;
	nextplu:;
				i++;
			}
			while(i<=NART);

			rct.top+=hauteur/33;//30;
			rct.bottom+=hauteur/33;//30;
			rct.left=(LONG)x1+10;
			rct.right=(LONG)(5*(xl1-10)/5);
			pdc->SelectObject(&miw);
			pdc->DrawText(txtc[110]+"  :  "+GTZtxt,-1,&rct,DT_LEFT|DT_SINGLELINE|DT_TOP|DT_NOPREFIX );//GTZ

			rct.top+=hauteur/16;//60;
			rct.bottom+=hauteur/16;//60;
			pdc->SelectObject(&miw);
			pdc->SelectObject(&boldpen);
			pdc->MoveTo((int)(x1+10),rct.top-hauteur/100);
			pdc->LineTo((int)(xl1-10),rct.top-hauteur/100);
			rct.left=(LONG)x1+10;
			rct.right=(LONG)((xl1-10));
			pdc->SelectObject(&miw);
			pdc->DrawText(date,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP|DT_NOPREFIX );
		}
//***************************************************IMPRESSION CITIZEN et KPST ***************************************************************************************
		else
		{
			CPen boldpen(PS_SOLID,hauteur/500,pencolor);			

			i=NART-NAPP+1;
			int fpres=0;
			int j;
			do
			{
				for(j=i;j<(i+NAPP)&&fpres==0;j++)
				{
					if(hlibel1[j]==""&&hlibel2[j]=="")
						continue;
					else
						fpres=1;
				}
				if(fpres)
				{
					pdc->StartPage();
					fpres=0;
					rct.top=hauteur/20;
					rct.bottom=rct.top+(LONG)y;
					rct.left=(LONG)x1+10;
					rct.right=(LONG)((xl1-10));
					pdc->SelectObject(&mid);
					if(printername.Find("KMGA")!=-1)
					{
						pdc->SetGraphicsMode(GM_ADVANCED);
						pdc->GetWorldTransform(&xForm);
						xForm.eM11 = (FLOAT) -1.0; 
						xForm.eM12 = (FLOAT) 0.0; 
						xForm.eM21 = (FLOAT) 0.0; 
						xForm.eM22 = (FLOAT) -1.0; 
						xForm.eDx  = (FLOAT) invxa; 
						xForm.eDy  = (FLOAT) invya; 
						pdc->SetWorldTransform(&xForm); 
					}
					else
					{
						if(printername.Find("KPSX")!=-1)
						{
							pdc->SetGraphicsMode(GM_ADVANCED);
							pdc->GetWorldTransform(&xForm);
							xForm.eM11 = (FLOAT) -1.0; 
							xForm.eM12 = (FLOAT) 0.0; 
							xForm.eM21 = (FLOAT) 0.0; 
							xForm.eM22 = (FLOAT) -1.0; 
							xForm.eDx  = (FLOAT) invxt; 
							xForm.eDy  = (FLOAT) invyt; 
							pdc->SetWorldTransform(&xForm); 
						}
						else
						{
							if(printername.Find("Citizen CL-S400DT")!=-1)
							{
								pdc->SetGraphicsMode(GM_ADVANCED);
								pdc->GetWorldTransform(&xForm);
								xForm.eM11 = (FLOAT) -1.0; 
								xForm.eM12 = (FLOAT) 0.0; 
								xForm.eM21 = (FLOAT) 0.0; 
								xForm.eM22 = (FLOAT) -1.0; 
								xForm.eDx  = (FLOAT) 620;
								if(paravent)
									xForm.eDy  = (FLOAT) 1140;
								else
									xForm.eDy  = (FLOAT) 820;
								pdc->SetWorldTransform(&xForm); 
							}
						}
					}
					if(valpage)
						temp="( "+pag[i/NAPP]+" )";
					else
					{
					
						temp.Format("( "+txtc[57]+" %u) ",(i/NAPP)+1);//Page
					}
					pdc->DrawText(txtc[110]+" "+temp,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP|DT_NOPREFIX );//CA PLU
					rct.top+=hauteur/20;//60;
					rct.bottom+=hauteur/20;//60;

					do
					{
						if(hlibel1[i]==""&&hlibel2[i]=="")
							goto nextkplu;
						rct.left=(LONG)x1;
						rct.right=(LONG)(1*(xl1)/8);
						pdc->SelectObject(&miw);
						temp.Format("%u",i);
						if(temp.GetLength()==1)
							temp="0"+temp;
						pdc->DrawText(temp,-1,&rct,DT_LEFT|DT_SINGLELINE|DT_TOP|DT_NOPREFIX );


						rct.left=rct.right;
						rct.right=(LONG)(6.5*(xl1)/10);
						pdc->SelectObject(&miw);
						pdc->DrawText(hlibel1[i]+" "+hlibel2[i],-1,&rct,DT_LEFT|DT_SINGLELINE|DT_TOP|DT_NOPREFIX );

						rct.left=rct.right;
						rct.right=(LONG)(7.5*(xl1)/10);
						pdc->SelectObject(&miw);
						temp.Format("%u",qteplu[i]);
						pdc->DrawText(temp,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP|DT_NOPREFIX  );

						rct.left=rct.right;
						rct.right=(LONG)(10*(xl1)/10);
						pdc->SelectObject(&miw);
						temp.Format("%.2f",valplu[i]);
						pdc->DrawText(temp,-1,&rct,DT_RIGHT|DT_SINGLELINE|DT_TOP|DT_NOPREFIX  );
						rct.top+=hauteur/25;//40;
						rct.bottom+=hauteur/25;//40;
			nextkplu:;
						i++;
						if((i-1)%NAPP==0)
						{
							i-=NAPP;
							pdc->EndPage();
							break;
						}
					}
					while(i>=0);
				}
				i-=NAPP;
			}
			while(i>=0);

			pdc->StartPage();
			if(printername.Find("KMGA")!=-1)
			{
				pdc->SetGraphicsMode(GM_ADVANCED);
				pdc->GetWorldTransform(&xForm);
				xForm.eM11 = (FLOAT) -1.0; 
				xForm.eM12 = (FLOAT) 0.0; 
				xForm.eM21 = (FLOAT) 0.0; 
				xForm.eM22 = (FLOAT) -1.0; 
				xForm.eDx  = (FLOAT) invxa; 
				xForm.eDy  = (FLOAT) invya; 
				pdc->SetWorldTransform(&xForm); 
			}
			else
				if(printername.Find("KPSX")!=-1)
				{
					pdc->SetGraphicsMode(GM_ADVANCED);
					pdc->GetWorldTransform(&xForm);
					xForm.eM11 = (FLOAT) -1.0; 
					xForm.eM12 = (FLOAT) 0.0; 
					xForm.eM21 = (FLOAT) 0.0; 
					xForm.eM22 = (FLOAT) -1.0; 
					xForm.eDx  = (FLOAT) invxt; 
					xForm.eDy  = (FLOAT) invyt; 
					pdc->SetWorldTransform(&xForm); 
				}
				else
				{
					if(printername.Find("Citizen CL-S400DT")!=-1)
					{
						pdc->SetGraphicsMode(GM_ADVANCED);
						pdc->GetWorldTransform(&xForm);
						xForm.eM11 = (FLOAT) -1.0; 
						xForm.eM12 = (FLOAT) 0.0; 
						xForm.eM21 = (FLOAT) 0.0; 
						xForm.eM22 = (FLOAT) -1.0; 
						xForm.eDx  = (FLOAT) 620;
						if(paravent)
							xForm.eDy  = (FLOAT) 1140;
						else
							xForm.eDy  = (FLOAT) 820;
						pdc->SetWorldTransform(&xForm); 
					}
				}
			rct.top=30;
			rct.bottom=(LONG)y+rct.top;
			rct.left=(LONG)x1+10;
			rct.right=(LONG)xl1-10;
			pdc->SelectObject(&tf);
			pdc->DrawText(nom,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP |DT_NOPREFIX);
			rct.top+=hauteur/50;//20;
			rct.bottom=rct.top+hauteur/7;//20;

			if(adresse1!="")
			{
				rct.top+=hauteur/25;//40;
				rct.bottom+=hauteur/25;//40;
				pdc->SelectObject(&mid);
				pdc->SelectObject(&mid);
				pdc->DrawText(adresse1,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP|DT_NOPREFIX  );
			}

			if(adresse2!="")
			{
				rct.top+=hauteur/25;//40;
				rct.bottom+=hauteur/25;//40;
				pdc->SelectObject(&mid);
				pdc->SelectObject(&mid);
				pdc->DrawText(adresse2,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP|DT_NOPREFIX  );
			}


			rct.top+=hauteur/25;//40;
			rct.bottom+=hauteur/25;//40;
			rct.left=(LONG)x1+10;
			rct.right=(LONG)((xl1-10));
			pdc->SelectObject(&miw);

			pdc->DrawText(txtc[72]+" : "+siret+" "+txtc[95]+" : "+naf,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP|DT_NOPREFIX  );//RCS

			rct.left=(LONG)x1+10;
			rct.right=(LONG)((xl1-10)/2);
			rct.top+=hauteur/25;//40;
			rct.bottom+=hauteur/25;//40;
			pdc->SelectObject(&mid);
			biltxt=txtc[68]+" "+poste;//POSTE N°
			pdc->DrawText(biltxt,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP|DT_NOPREFIX  );

			rct.left=(LONG)((xl1-10)/2);
			rct.right=(LONG)(xl1-10);
			pdc->SelectObject(&mid);
			if(GTZtxt!="Non clôturée")
			{
				if(hist==0)
					temp.Format(txtc[102]+" %u",RAZ);//GTZ N°
				else
					temp.Format(txtc[102]+" %u",HRAZ   );//GTZ N°

			}
			else
			{
				temp=txtc[103];
			}
			pdc->DrawText(temp,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP|DT_NOPREFIX  );

			rct.left=(LONG)x1+10;
			rct.right=(LONG)((xl1-10));
			rct.top+=hauteur/16;//60;
			rct.bottom+=hauteur/16;//60;
			pdc->SelectObject(&miw);
			pdc->SelectObject(&boldpen);
			pdc->MoveTo((int)(x1+10),rct.top-hauteur/100);
			pdc->LineTo((int)(xl1-10),rct.top-hauteur/100);
			temp=txtc[38]+": "+ouverture;//Ouverture+"  "+tickstart;
			pdc->DrawText(temp,-1,&rct,DT_LEFT|DT_SINGLELINE|DT_TOP|DT_NOPREFIX   );
			rct.top+=hauteur/25;//40;
			rct.bottom+=hauteur/25;//40;
			pdc->SelectObject(&miw);
			temp=txtc[39]+"    : "+cloture;//Clôture+"  "+tickstop;
			pdc->DrawText(temp,-1,&rct,DT_LEFT|DT_SINGLELINE|DT_TOP|DT_NOPREFIX   );

			rct.top+=hauteur/16;//60;
			rct.bottom+=hauteur/16;//60;
			pdc->SelectObject(&miw);
			pdc->SelectObject(&boldpen);
			pdc->MoveTo((int)(x1+10),rct.top-hauteur/100);
			pdc->LineTo((int)(xl1-10),rct.top-hauteur/100);
			rct.left=(LONG)x1+10;
			rct.right=(LONG)((xl1-10));
			pdc->SelectObject(&mid);
			pdc->DrawText(txtc[104],-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP|DT_NOPREFIX );//"CA VENTES"

			rct.top+=hauteur/20;//60;
			rct.bottom+=hauteur/20;//60;
			rct.left=(LONG)x1+10;
			rct.right=(LONG)(2.5*(xl1-10)/5);
			pdc->SelectObject(&miw);
			pdc->DrawText(txtc[105]+" : ",-1,&rct,DT_LEFT|DT_SINGLELINE|DT_TOP|DT_NOPREFIX );//TTC Encaissé

			rct.left=rct.right;
			rct.right=(LONG)(3.5*(xl1-10)/5);
			pdc->SelectObject(&miw);
			temp.Format("%u",nbticktot-nbtickan);
			pdc->DrawText(temp,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP|DT_NOPREFIX  );

			rct.left=rct.right;
			rct.right=(LONG)(5*(xl1-10)/5);
			pdc->SelectObject(&miw);
			temp.Format("%.2f",ca);
			pdc->DrawText(temp,-1,&rct,DT_RIGHT|DT_SINGLELINE|DT_TOP|DT_NOPREFIX  );
			ht=0;
			ttva=0;
			i=0;
			while(i<10)//catva[i]!=0&&
			{
				ht+=catva[i]/(1+(tvaca[i]/100));
				ttva+=catva[i]-(catva[i]/(1+(tvaca[i]/100)));
				i++;
			}
			rct.top+=hauteur/25;//40;
			rct.bottom+=hauteur/25;//40;
			rct.left=(LONG)x1+10;
			rct.right=(LONG)(3*(xl1-10)/5);
			pdc->SelectObject(&miw);
			pdc->DrawText(txtc[106]+" : ",-1,&rct,DT_LEFT|DT_SINGLELINE|DT_TOP|DT_NOPREFIX );//HT encaissé

			rct.left=rct.right;
			rct.right=(LONG)(5*(xl1-10)/5);
			pdc->SelectObject(&miw);
			temp.Format("%.2f",ht);
			pdc->DrawText(temp,-1,&rct,DT_RIGHT|DT_SINGLELINE|DT_TOP|DT_NOPREFIX  );


			i=0;
			while(i<10)
			{
				if(catva[i]!=0)
				{
					rct.top+=hauteur/25;//40;
					rct.bottom+=hauteur/25;//40;
					rct.left=(LONG)x1+10;
					rct.right=(LONG)(2.5*(xl1-10)/5);
					pdc->SelectObject(&miw);
					pdc->DrawText(txtc[107]+"   : ",-1,&rct,DT_LEFT|DT_SINGLELINE|DT_TOP|DT_NOPREFIX );//Montant TVA

					temp.Format("%.2f",tvaca[i]);
					temp=temp+"%";
					rct.left=rct.right;
					rct.right=(LONG)(3.5*(xl1-10)/5);
					pdc->SelectObject(&miw);
					pdc->DrawText(temp,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP|DT_NOPREFIX  );

					rct.left=rct.right;
					rct.right=(LONG)(5*(xl1-10)/5);
					pdc->SelectObject(&miw);
					temp.Format("%.2f",catva[i]-(catva[i]/(1+(tvaca[i]/100))));
					pdc->DrawText(temp,-1,&rct,DT_RIGHT|DT_SINGLELINE|DT_TOP|DT_NOPREFIX  );
				}
				i++;
			}

			rct.top+=hauteur/25;//40;
			rct.bottom+=hauteur/25;//40;
			rct.left=(LONG)x1+10;
			rct.right=(LONG)(2*(xl1-10)/5);
			pdc->SelectObject(&miw);
			pdc->DrawText(txtc[108]+" : ",-1,&rct,DT_LEFT|DT_SINGLELINE|DT_TOP|DT_NOPREFIX );//Total TVA

			rct.left=rct.right;
			rct.right=(LONG)(5*(xl1-10)/5);
			pdc->SelectObject(&miw);
			temp.Format("%.2f",ttva);
			pdc->DrawText(temp,-1,&rct,DT_RIGHT|DT_SINGLELINE|DT_TOP|DT_NOPREFIX  );
	//******************* ANNULES ******************************
			rct.top+=hauteur/25;//60;
			rct.bottom+=hauteur/25;//60;
			rct.left=(LONG)x1+10;
			rct.right=(LONG)((xl1-10));
			pdc->SelectObject(&mid);
			pdc->DrawText(txtc[109],-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP|DT_NOPREFIX );//"TICKETS ANNULES"

			if(paravent)
			{
				rct.top+=hauteur/20;//60;
				rct.bottom+=hauteur/20;//60;
			}
			else
			{
				rct.top+=hauteur/25;//60;
				rct.bottom+=hauteur/25;//60;
			}
			rct.left=(LONG)x1+10;
			rct.right=(LONG)(2*(xl1-10)/5);
			pdc->SelectObject(&miw);
			pdc->DrawText(txtc[41]+" : ",-1,&rct,DT_LEFT|DT_SINGLELINE|DT_TOP|DT_NOPREFIX );//Annulés

			rct.left=rct.right;
			rct.right=(LONG)(3*(xl1-10)/5);
			pdc->SelectObject(&miw);
			temp.Format("%u",nbtickan);
			pdc->DrawText(temp,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP|DT_NOPREFIX  );

			rct.left=rct.right;
			rct.right=(LONG)(5*(xl1-10)/5);
			pdc->SelectObject(&miw);
			temp.Format("%.2f",can);
			pdc->DrawText(temp,-1,&rct,DT_RIGHT|DT_SINGLELINE|DT_TOP|DT_NOPREFIX  );
			if(infocert)
			{
				if(paravent)
				{
					rct.top+=hauteur/16;//60;
					rct.bottom+=hauteur/16;//60;
				}
				else
				{
					rct.top+=hauteur/30;//60;
					rct.bottom+=hauteur/30;//60;
				}
				//if(gta!=""&&(code==codemanager||code==codeadmin||code==codereseller))
				{
					temp="GTA : "+gta;
					rct.left=(LONG)x1+10;
					rct.right=(LONG)((xl1-10)/2);
					pdc->SelectObject(&mid);
					pdc->DrawText(temp,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP|DT_NOPREFIX  );
					rct.left=(LONG)((xl1-10)/2);
					rct.right=(LONG)(xl1-10);
				}
				/*else
				{
					rct.left=(LONG)x1+10;
					rct.right=(LONG)(xl1-10);
				}*/
				temp.Format("%.2f",ca);
				temp="GTZ : "+temp;
				pdc->SelectObject(&mid);
				pdc->DrawText(temp,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP|DT_NOPREFIX  );

			}
			if(paravent)
			{
				rct.top+=hauteur/16;//60;
				rct.bottom+=hauteur/16;//60;
				pdc->SelectObject(&boldpen);
				pdc->MoveTo((int)(x1+10),rct.top-hauteur/100);
				pdc->LineTo((int)(xl1-10),rct.top-hauteur/100);
			}
			else
			{
				rct.top+=hauteur/25;//60;
				rct.bottom+=hauteur/25;//60;
				pdc->SelectObject(&boldpen);
				pdc->MoveTo((int)(x1+10),rct.top);//-hauteur/100);
				pdc->LineTo((int)(xl1-10),rct.top);//-hauteur/100);
			}
			pdc->SelectObject(&miw);
			rct.left=(LONG)x1+10;
			rct.right=(LONG)((xl1-10));
			pdc->SelectObject(&tcb);
			if(GTZtxt==txtc[78])//Non clôturée
				temp=txtc[34];//Lecture billetterie
			else
				temp=txtc[36];//Clôture billetterie
			temp.MakeUpper();
			pdc->DrawText(temp,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP|DT_NOPREFIX );

		}
		if(!noprint)
		{
			pdc->EndPage();
			pdc->EndDoc();
			pdc->Detach();
			DeleteDC(prt.m_pd.hDC);
			GlobalFree(prt.m_pd.hDevMode);
			GlobalFree(prt.m_pd.hDevNames);
			InterlockedExchange(&PJOB,0);
		}
		else
		{
			tsorg=rct.bottom;
			ReleaseDC(pdc);

		}
	}
}

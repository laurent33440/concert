#include "stdafx.h"
#include "Concerto.h"
#include "ConcertoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void CConcertoDlg::PrintNews(CString ouverture,CString cloture,CString GTZtxt,CString GTPtxt) 
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
	CString NTICK;
	CString PARTICK;
	CString DTICK;
	CString PTICK;
	CString LTICK;
	CString ATICK;
	CString TVATICK;
	CTime ct;
	ct=CTime::GetCurrentTime();
	date=ct.Format("%d/%m/%Y  %H:%M:%S");
	CDC m_Cdc;
	CRect rect;
	//CRect butrect;
	CRect rct;
	CFont tf;
	CFont mic;
	CFont mid;
	CFont miw;
	float plargeur;
	float phauteur;
	float x;
	float y;
	float xl1;
	float x1;
	int largeur;//
	int hauteur;//
	int bc;//
	int idx;
	int artidx;
	XFORM xForm;
	CDC* pdc=NULL;
	CDC* pdcw=NULL;
	COLORREF pencolor=0x00000000;
	COLORREF blancolor=0x00FFFFFF;
	CPen finepen(PS_SOLID,1,pencolor);
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
		if(noprint)
		{
			if(wlargeur>whauteur)				
				plargeur=(float)wlargeur/6;
			else
				plargeur=(float)wlargeur/2;
			phauteur=(float)whauteur;
			x=0;
			lmarge=0;
			rmarge=5;
			//cdc.Rectangle(60,5,xl1-5,340);
			largeur=(int)(plargeur/2.1);//
			hauteur= 400;
		}
		else
		{
			InterlockedExchange(&PJOB,pdc->StartDoc("Impression journal"));
			if(printername.Find("Citizen CL-S400DT")!=-1)
				plargeur=(float)pdc->GetDeviceCaps(HORZRES)/2;//-(2*cdc.GetDeviceCaps(PHYSICALOFFSETX)));
			else
				plargeur=(float)pdc->GetDeviceCaps(HORZRES);//-(2*cdc.GetDeviceCaps(PHYSICALOFFSETX)));
			phauteur=(float)pdc->GetDeviceCaps(VERTRES);//-(2*cdc.GetDeviceCaps(PHYSICALOFFSETY)));
			x=(float)pdc->GetDeviceCaps(PHYSICALOFFSETX);
			largeur=(int)(plargeur/2.1);//
			hauteur= 1000;
		}
		x1=(float)lmarge;
		xl1=(plargeur)-rmarge;
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
		
		y=(float)(150);
		rct.top=0;
		if(noprint)
		{
			rct.top=tsorg;
			rct.bottom=tsorg+(LONG)1000;
		}
		else
			rct.bottom=(LONG)y;
		bc=(0xFFFFFF);
		pdc->SetBkColor(bc);
		rct.left=0;
		rct.right=(LONG)xl1;
		pdc->FillSolidRect(&rct,bc);
		if(printername.Find("KPSX")==-1&&printername.Find("KMGA")==-1&&printername.Find("Citizen CL-S400DT")==-1)//pas d'imprimante reconnue
		{
			CPen boldpen(PS_SOLID,hauteur/200,pencolor);
			if(!noprint)
			{
				pdc->StartPage();
			}
			rct.left=(LONG)x1+10;
			rct.right=(LONG)xl1-10;
			pdc->FillSolidRect(&rct,bc);
			pdc->SelectObject(&mid);
			biltxt=txtc[113]+" "+poste;//"JOURNAL DE BILLETTERIE N°
			pdc->DrawText(biltxt,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP|DT_NOPREFIX  );

			rct.top+=60;
			rct.bottom+=60;
			pdc->SelectObject(&miw);
			pdc->SelectObject(&boldpen);
			pdc->MoveTo((int)(lmarge+10),rct.top-10);
			pdc->LineTo((int)(xl1-10),rct.top-10);
			temp=txtc[38]+": "+ouverture;//Ouverture
			pdc->DrawText(temp,-1,&rct,DT_LEFT|DT_SINGLELINE|DT_TOP|DT_NOPREFIX   );
			rct.top+=40;
			rct.bottom+=40;
			pdc->SelectObject(&miw);
			temp=txtc[39]+"    : "+cloture;//Clôture
			pdc->DrawText(temp,-1,&rct,DT_LEFT|DT_SINGLELINE|DT_TOP|DT_NOPREFIX   );
			rct.top+=hauteur/16;//40;
			rct.bottom+=hauteur/16;//40;
			pdc->MoveTo((int)(lmarge+10),rct.top-10);
			pdc->LineTo((int)(xl1-10),rct.top-10);
			rct.left=(LONG)((x1+10));
			rct.right=(LONG)(xl1-10);
			pdc->SelectObject(&mid);
			if(GTPtxt!="Non clôturée")
			{
				if(hist==0)
					temp.Format(txtc[102]+" %u",RAZ);//GTZ N°
				else
					temp.Format(txtc[102]+" %u",HRAZ);//GTZ N°
			}
			else
			{
				temp=txtc[103];//"GTZ  : Non clôturée"
			}
			pdc->DrawText(temp,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP|DT_NOPREFIX  );
			
			rct.top+=hauteur/16;//40;
			rct.bottom+=hauteur/16;//40;
			idx=cession.Find("\r\n",0);
			ouverture=cession.Mid(5,idx-5);
			idx+=2;
			int i=0;
			do
			{
				if((i=cession.Find(";",idx))!=-1)
				{
					NTICK=cession.Mid(idx,i-idx);
					PARTICK=NTICK.Right(3);
				}
				else
					break;
				idx=i+1;
				if((i=cession.Find(";",idx))!=-1)
					DTICK=cession.Mid(idx,i-idx);
				else
					break;
				idx=i+1;
				if((i=cession.Find(";",idx))!=-1)
				{
					//if(PARTICK.Find(" ",0)!=-1||PARTICK.Find("1/",0)!=-1)
						PTICK=cession.Mid(idx,i-idx);
					/*else
						PTICK="";*/
				}
				else
					break;
				idx=i+1;
				if((i=cession.Find(";",idx))==-1)
					break;
				idx=i+1;
				if((i=cession.Find("\r\n",idx))!=-1)
					ATICK=cession.Mid(idx,i-idx);
				else
					break;
				rct.left=(LONG)lmarge+10;
				rct.right=(LONG)(3*(xl1-10)/5);
				pdc->SelectObject(&miw);
				pdc->DrawText(DTICK,-1,&rct,DT_LEFT|DT_SINGLELINE|DT_TOP|DT_NOPREFIX );


				rct.left=rct.right;
				rct.right=(LONG)(xl1-10);
				pdc->SelectObject(&miw);
				pdc->DrawText(NTICK,-1,&rct,DT_LEFT|DT_SINGLELINE|DT_TOP|DT_NOPREFIX  );

				rct.top+=35;
				rct.bottom+=35;
				rct.left=(LONG)lmarge+10;

				temp=NTICK.Mid(4,2);
				artidx=atoi(temp);
				rct.left=(LONG)lmarge+10;
				rct.right=(LONG)(4*(xl1-10)/5);
				pdc->SelectObject(&miw);
				pdc->DrawText(hlibel1[artidx]+ " "+hlibel2[artidx],-1,&rct,DT_LEFT|DT_SINGLELINE|DT_TOP);

				rct.left=rct.right;
				rct.right=(LONG)(xl1-10);
				pdc->SelectObject(&miw);
				
				if(ATICK=="")
					pdc->DrawText(PTICK,-1,&rct,DT_RIGHT|DT_SINGLELINE|DT_TOP );
				else
					if(ATICK=="X")
					{
						pdc->DrawText(txtc[49],-1,&rct,DT_RIGHT|DT_SINGLELINE|DT_TOP );//"ANNULE"
					}
					else
						if(ATICK=="O")
						{
							pdc->DrawText(txtc[81],-1,&rct,DT_RIGHT|DT_SINGLELINE|DT_TOP|DT_NOPREFIX  );//"OFFERT"
						}
				rct.top+=50;
				rct.bottom+=50;
				idx=i+2;
			}
			while(i!=-1);

			rct.top+=60;
			rct.bottom+=60;
			pdc->SelectObject(&miw);
			pdc->SelectObject(&boldpen);
			pdc->MoveTo((int)(lmarge+10),rct.top-10);
			pdc->LineTo((int)(xl1-10),rct.top-10);
			//rct.top+=70;
			//rct.bottom+=70;
			rct.left=(LONG)lmarge+10;
			rct.right=(LONG)((xl1-10));
			pdc->SelectObject(&miw);
			pdc->DrawText(date,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP|DT_NOPREFIX );


			pdc->SelectObject(&finepen);
			pdc->MoveTo(300,rct.bottom-110);//410);
			pdc->LineTo(310,rct.bottom-110);//410);

			if(!noprint)
				pdc->EndPage();
			else
				tsorg=rct.bottom;
		}
		else //imprimantes trouvees
		{
			CPen boldpen(PS_SOLID,hauteur/500,pencolor);
			pdc->SelectObject(&mid);
			pdc->StartPage();
			rct.top=hauteur/100;
			rct.bottom=rct.top+(LONG)y;
			rct.left=(LONG)x1+10;
			rct.right=(LONG)((xl1-10));
			if(printername.Find("Citizen CL-S400DT")!=-1)
			{
				pdc->SetGraphicsMode(GM_ADVANCED);
				pdc->GetWorldTransform(&xForm);
				xForm.eM11 = (FLOAT) +1.0; 
				xForm.eM12 = (FLOAT) 0.0; 
				xForm.eM21 = (FLOAT) 0.0; 
				xForm.eM22 = (FLOAT) +1.0; 
				xForm.eDx  = (FLOAT) 190;
				if(paravent)
					xForm.eDy  = (FLOAT) 1200;
				else
					xForm.eDy  = (FLOAT) 840;
				xForm.eDy  = (FLOAT) 50;
				pdc->SetWorldTransform(&xForm); 
			}
			pdc->SelectObject(&mid);
			biltxt= txtc[113]+" "+poste;//"JOURNAL DE BILLETTERIE N°
			pdc->DrawText(biltxt,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP |DT_NOPREFIX );
			rct.top+=hauteur/16;//40;
			rct.bottom+=hauteur/16;//40;

			pdc->SelectObject(&miw);
			pdc->SelectObject(&boldpen);
			pdc->MoveTo((int)(x1+10),rct.top-10);
			pdc->LineTo((int)(xl1-10),rct.top-10);
			temp=txtc[38]+": "+ouverture;//Ouverture
			pdc->DrawText(temp,-1,&rct,DT_LEFT|DT_SINGLELINE|DT_TOP|DT_NOPREFIX   );
			rct.top+=hauteur/25;//40;
			rct.bottom+=hauteur/25;//40;
			pdc->SelectObject(&miw);
			temp=txtc[39]+":   "+cloture;//Clôture
			pdc->DrawText(temp,-1,&rct,DT_LEFT|DT_SINGLELINE|DT_TOP|DT_NOPREFIX   );

			rct.top+=hauteur/16;//40;
			rct.bottom+=hauteur/16;//40;
			pdc->MoveTo((int)(lmarge+10),rct.top-10);
			pdc->LineTo((int)(xl1-10),rct.top-10);
			rct.left=(LONG)((x1+10));
			rct.right=(LONG)(xl1-10);
			pdc->SelectObject(&mid);
			if(GTPtxt!="Non clôturée")
			{
				if(hist==0)
					temp.Format(txtc[1025]+" %u",RAZ);//GTZ  N°
				else
					temp.Format(txtc[102]+" %u",HRAZ);//GTZ  N°
			}
			else
			{
				temp=txtc[103];//"GTZ  : Non clôturée";
			}
			pdc->DrawText(temp,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP|DT_NOPREFIX  );
			
			rct.top+=hauteur/16;//40;
			rct.bottom+=hauteur/16;//40;
			idx=cession.Find("\r\n",0);
			ouverture=cession.Mid(5,idx-5);
			idx+=2;
			int i=0;
			do
			{
				if((i=cession.Find(";",idx))!=-1)
				{
					NTICK=cession.Mid(idx,i-idx);
					PARTICK=NTICK.Right(3);
					ATICK = NTICK.Left(1);// récupère le type de ticket A,B,P,X
				}
				else
					break;
				idx=i+1;
				if((i=cession.Find(";",idx))!=-1)
					DTICK=cession.Mid(idx,i-idx);
				else
					break;
				idx=i+1;
				if((i=cession.Find(";",idx))!=-1)
				{
					//if(PARTICK.Find(" ",0)!=-1||PARTICK.Find("1/",0)!=-1)
						PTICK=cession.Mid(idx,i-idx);
				}
				else
					break;
				idx=i+1;
				if((i=cession.Find(";",idx))==-1)
					break;
				idx=i+1;
				if((i=cession.Find("\r\n",idx))==-1)
					break;
				rct.left=(LONG)lmarge+10;
				rct.right=(LONG)(3*(xl1-10)/5);
				pdc->SelectObject(&miw);
				pdc->DrawText(DTICK,-1,&rct,DT_LEFT|DT_SINGLELINE|DT_TOP|DT_NOPREFIX );


				rct.left=rct.right;
				rct.right=(LONG)(xl1-10);
				pdc->SelectObject(&miw);
				pdc->DrawText(NTICK,-1,&rct,DT_LEFT|DT_SINGLELINE|DT_TOP|DT_NOPREFIX  );

				rct.top+=35;
				rct.bottom+=35;
				rct.left=(LONG)lmarge+10;

				temp=NTICK.Mid(4,2);
				artidx=atoi(temp);
				rct.left=(LONG)lmarge+10;
				rct.right=(LONG)(4*(xl1-10)/5);
				pdc->SelectObject(&miw);
				if(ATICK!="X")
				{
					pdc->DrawText(hlibel1[artidx]+ " "+hlibel2[artidx],-1,&rct,DT_LEFT|DT_SINGLELINE|DT_TOP|DT_NOPREFIX );
				}
				rct.left=rct.right;
				rct.right=(LONG)(xl1-10);
				pdc->SelectObject(&miw);
				if(ATICK=="")
					pdc->DrawText(PTICK,-1,&rct,DT_RIGHT|DT_SINGLELINE|DT_TOP|DT_NOPREFIX  );
				else
					if(ATICK=="X")
					{
						pdc->DrawText(txtc[49],-1,&rct,DT_RIGHT|DT_SINGLELINE|DT_TOP|DT_NOPREFIX  );//"ANNULE"
					}
				rct.top+=50;
				rct.bottom+=50;
				idx=i+2;
				if(((rct.top>botline-80&&!paravent)||(rct.top>botline+300&&paravent))&&printername.Find("Citizen CL-S400DT")!=-1)
				{
					pdc->EndPage();
					pdc->StartPage();
					rct.top=hauteur/100;
					rct.bottom=rct.top+(LONG)y;
					rct.left=(LONG)x1+10;
					rct.right=(LONG)((xl1-10));
					if(printername.Find("Citizen CL-S400DT")!=-1)
					{
						pdc->SetGraphicsMode(GM_ADVANCED);
						pdc->GetWorldTransform(&xForm);
						xForm.eM11 = (FLOAT) +1.0; 
						xForm.eM12 = (FLOAT) 0.0; 
						xForm.eM21 = (FLOAT) 0.0; 
						xForm.eM22 = (FLOAT) +1.0; 
						xForm.eDx  = (FLOAT) 190;
						if(paravent)
							xForm.eDy  = (FLOAT) 1200;
						else
							xForm.eDy  = (FLOAT) 840;
						xForm.eDy  = (FLOAT) 50;
						pdc->SetWorldTransform(&xForm); 
					}
				}
				/*else
					if(rct.top>botline-100&&(printername.Find("KPSX")!=-1||printername.Find("KMGA")!=-1))
					{
						pdc->EndPage();
						pdc->StartPage();
						rct.top=hauteur/50;
						rct.bottom=rct.top+(LONG)y;
						rct.left=(LONG)x1+10;
						rct.right=(LONG)((xl1-10));
					}*/
			}
			while(i!=-1);
			if(printername.Find("Citizen CL-S400DT")!=-1)
			{
				if((((rct.top-10)>botline-80&&!paravent)||((rct.top-10)>botline+300&&paravent)))
				{
						pdc->EndPage();
						pdc->StartPage();
						if(printername.Find("Citizen CL-S400DT")!=-1)
						{
							pdc->SetGraphicsMode(GM_ADVANCED);
							pdc->GetWorldTransform(&xForm);
							xForm.eM11 = (FLOAT) +1.0; 
							xForm.eM12 = (FLOAT) 0.0; 
							xForm.eM21 = (FLOAT) 0.0; 
							xForm.eM22 = (FLOAT) +1.0; 
							xForm.eDx  = (FLOAT) 190;
							if(paravent)
								xForm.eDy  = (FLOAT) 1200;
							else
								xForm.eDy  = (FLOAT) 840;
							xForm.eDy  = (FLOAT) 50;
							pdc->SetWorldTransform(&xForm); 
						}
				}
				if(paravent)
					rct.top=botline+300;
				else
					rct.top=botline-80;
				rct.bottom=rct.top+(LONG)y;
			}
			else
			{
				rct.top+=100;
				rct.bottom+=100;
			}
			pdc->SelectObject(&miw);
			pdc->SelectObject(&boldpen);
			pdc->MoveTo((int)(lmarge+10),rct.top-10);
			pdc->LineTo((int)(xl1-10),rct.top-10);
			rct.left=(LONG)lmarge+10;
			rct.right=(LONG)((xl1-10));
			pdc->SelectObject(&miw);
			pdc->DrawText(date,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP|DT_NOPREFIX );


			pdc->SelectObject(&finepen);
			pdc->MoveTo(300,botline);//410);
			pdc->LineTo(310,botline);//410);
			pdc->EndPage();
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
}

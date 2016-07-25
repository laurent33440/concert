#include "stdafx.h"
#include "Billet.h"
#include "BilletDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void CBilletDlg::Print()// 
{
	CString temp;
	CString page;
	CString date;
	CString vsht;
	CString vsttc;
	CDC pdc;
	CDC m_Cdc;
	CBitmap bitmap;
	CRect rect;
	CRect butrect;
	CRect rct;
	CFont* pof;
	CFont tf;
	int i;
	int idx;
	float plargeur;
	float phauteur;
	float x;
	float py;
	float f;
	float g;
	float y;
	float z;
	float x1;
	float xl1;
	float x2;
	float xl2;
	float x3;
	float xl3;
	float x4;
	float xl4;
	float x5;
	float xl5;
	float x6;
	float xl6;
	float delt;
	float s;
	int largeur;//
	int hauteur;//
	int bc;//
	CTime ct;
	CPrintDialog prt(TRUE,PD_RETURNDC|PD_ALLPAGES | PD_USEDEVMODECOPIES | PD_NOPAGENUMS |
		PD_HIDEPRINTTOFILE | PD_NOSELECTION,this);

	if(prt.DoModal()==IDOK&&prt.m_pd.hDC!=NULL)
	{
		pdc.Attach(prt.m_pd.hDC);
		plargeur=(float)pdc.GetDeviceCaps(HORZRES);//-(2*pdc.GetDeviceCaps(PHYSICALOFFSETX)));
		phauteur=(float)pdc.GetDeviceCaps(VERTRES);//-(2*pdc.GetDeviceCaps(PHYSICALOFFSETY)));
		x=pdc.GetDeviceCaps(PHYSICALOFFSETX)+(float)(plargeur/15);
		x1=x;
		xl1=(float)(plargeur/7);
		x2=x1+xl1-1;
		xl2=(float)(plargeur/4);
		x3=x2+xl2-1;
		xl3=(float)(plargeur/12);
		x4=x3+xl3-1;
		xl4=(float)(plargeur/12);
		x5=x4+xl4-1;
		xl5=(float)(plargeur/12);
		x6=x5+xl5-1;
		xl6=(float)(plargeur/5);
		//x7=x6+xl6-1;
		//xl7=(float)(plargeur/12);
		largeur=(int)(plargeur/2.1);//
		hauteur= (int)(phauteur*50/70);//(float)phauteur/1.40;
		tf.CreateFont((int)phauteur/100,
			(int)plargeur/200,
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
		pof=pdc.SelectObject(&tf);
		pdc.StartDoc("Gestion d'article");
		pdc.StartPage();
		y=(float)(phauteur/4.2);
		z=y-(float)(phauteur/40);
		ct=CTime::GetCurrentTime();
		date=ct.FormatGmt("%d/%m/%Y");
		page="Page 1";
		PrintTitre(&pdc,"Etat du stock",date,page);
		PrintEntete(&pdc,(int)y,(int)x1,(int)xl1,(int)x2,(int)xl2,(int)x3,(int)xl3,(int)x4,(int)xl4,(int)x5,(int)xl5,(int)x6,(int)xl6,(int)z);
		idx=0;
		py=phauteur/70;
		rct.top=(LONG)(y-py);
		rct.bottom=(LONG)y;
		delt=plargeur/200;
		while(idx<asl.GetCount())
		//while(libel[i]!="")
		{
			if(sort)
				i=(int)csl.GetItemData(idx);
			else
				i=(int)asl.GetItemData(idx);


			if(idx==50||idx==100)
			{
				if(idx==50)
					page="Page 2";
				if(idx==100)
					page="Page 3";
				PrintCadre(&pdc,(int)y,(int)x1,(int)xl1,(int)x2,(int)xl2,(int)x3,(int)xl3,(int)x4,(int)xl4,(int)x5,(int)xl5,(int)x6,(int)xl6,hauteur);
				pdc.EndPage();
				pdc.StartPage();
				PrintTitre(&pdc,"Etat du stock",date,page);
				PrintEntete(&pdc,(int)y,(int)x1,(int)xl1,(int)x2,(int)xl2,(int)x3,(int)xl3,(int)x4,(int)xl4,(int)x5,(int)xl5,(int)x6,(int)xl6,(int)z);
				rct.top=(LONG)(y-py);
				rct.bottom=(LONG)y;
			}
			if((idx%2)==0)
				bc=(0xFFFFFF);
			else
				bc=(0xE0E0E0);

			pdc.SetBkColor(bc);

			rct.top+=(LONG)py;
			rct.bottom+=(LONG)py;
			rct.left=(LONG)x1;
			rct.right=(LONG)(x1+xl1);
			pdc.FillSolidRect(&rct,bc);
			rct.left=(LONG)(x1+delt);
			pdc.DrawText(codart[i],-1,&rct,DT_LEFT|DT_SINGLELINE|DT_VCENTER );
			rct.left=(LONG)x2;
			rct.right=(LONG)(x2+xl2);
			pdc.FillSolidRect(&rct,bc);
			rct.left=(LONG)(x2+delt);
			pdc.DrawText(libel[i],-1,&rct,DT_LEFT|DT_SINGLELINE|DT_VCENTER|DT_NOPREFIX );
			f=(float)stock[i];
			temp.Format("%.0f",(f));
			rct.left=(LONG)x3;
			rct.right=(LONG)(x3+xl3);
			pdc.FillSolidRect(&rct,bc);
			rct.right=(LONG)(x3+xl3-delt);
			pdc.DrawText(temp,-1,&rct,DT_RIGHT|DT_SINGLELINE|DT_VCENTER );
			g=(float)stm[i];
			temp.Format("%.0f",g);
			rct.left=(LONG)x4;
			rct.right=(LONG)(x4+xl4);
			pdc.FillSolidRect(&rct,bc);
			rct.right=(LONG)(x4+xl4-delt);
			pdc.DrawText(temp,-1,&rct,DT_RIGHT|DT_SINGLELINE|DT_VCENTER );
			s=g-f;
			if(s>0)
				temp.Format("%.0f",(float)(s));
			else
				temp="0";
			rct.left=(LONG)x5;
			rct.right=(LONG)(x5+xl5);
			pdc.FillSolidRect(&rct,bc);
			rct.right=(LONG)(x5+xl5-delt);
			pdc.DrawText(temp,-1,&rct,DT_RIGHT|DT_SINGLELINE|DT_VCENTER );
			rct.left=(LONG)x6;
			rct.right=(LONG)(x6+xl6);
			pdc.FillSolidRect(&rct,bc);
			rct.left=(LONG)(x6+delt);
			pdc.DrawText(four[i],-1,&rct,DT_LEFT|DT_SINGLELINE|DT_VCENTER );
			idx++;
		}
		PrintCadre(&pdc,(int)y,(int)x1,(int)xl1,(int)x2,(int)xl2,(int)x3,(int)xl3,(int)x4,(int)xl4,(int)x5,(int)xl5,(int)x6,(int)xl6,hauteur);
 		pdc.SelectObject(pof);
		pdc.EndPage();
		pdc.EndDoc();
		pdc.Detach( );
		DeleteDC(prt.m_pd.hDC);
	}
}
void CBilletDlg::PrintCadre(CDC* pdc,int y,int x1,int xl1,int x2,int xl2,int x3,int xl3,int x4,int xl4,int x5,int xl5,int x6,int xl6,int hauteur)//int x7,int xl7,
{
	CRect rct;
	float delta=(float)x1/40;
	CBrush br((COLORREF)0);
	pdc->SetBkColor(0xFFFFFF);
	rct.top=y;
	rct.bottom=y+hauteur;
	rct.left=x1;
	rct.right=x1+xl1;
	pdc->FrameRect(&rct,&br);
	rct.left=x2;
	rct.right=x2+xl2;
	pdc->FrameRect(&rct,&br);
	rct.left=x3;
	rct.right=x3+xl3;
	pdc->FrameRect(&rct,&br);
	rct.left=x4;
	rct.right=x4+xl4;
	pdc->FrameRect(&rct,&br);
	rct.left=x5;
	rct.right=x5+xl5;
	pdc->FrameRect(&rct,&br);
	rct.left=x6;
	rct.right=x6+xl6;
	pdc->FrameRect(&rct,&br);
	/*rct.left=x7;
	rct.right=x7+xl7;
	pdc->FrameRect(&rct,&br);*/
}
void CBilletDlg::PrintEntete(CDC* pdc,int y,int x1,int xl1,int x2,int xl2,int x3,int xl3,int x4,int xl4,int x5,int xl5,int x6,int xl6,int z)//int x7,int xl7,
{
	CRect rct;	
	pdc->SelectStockObject(BLACK_PEN);
	rct.top=z;
	rct.bottom=y;
	rct.left=x1;
	rct.right=x1+xl1;
	pdc->Rectangle(&rct);
	pdc->SetTextColor(0x00);
	pdc->DrawText("Code",-1,&rct,DT_CENTER|DT_SINGLELINE|DT_VCENTER );
	rct.left=x2;
	rct.right=x2+xl2;
	pdc->Rectangle(&rct);
	pdc->DrawText("Article",-1,&rct,DT_CENTER|DT_SINGLELINE|DT_VCENTER );
	rct.left=x3;
	rct.right=x3+xl3;
	pdc->Rectangle(&rct);
	pdc->DrawText(stocktext,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_VCENTER );
	rct.left=x4;
	rct.right=x4+xl4;
	pdc->Rectangle(&rct);
	pdc->DrawText(stockmintext,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_VCENTER );
	rct.left=x5;
	rct.right=x5+xl5;
	pdc->Rectangle(&rct);
	pdc->DrawText(commandetext,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_VCENTER );
	rct.left=x6;
	rct.right=x6+xl6;
	pdc->Rectangle(&rct);
	pdc->DrawText("Fournisseur",-1,&rct,DT_CENTER|DT_SINGLELINE|DT_VCENTER );
}
void CBilletDlg::PrintTitre(CDC* pdc,CString Titre,CString Date,CString Page)
{
	CRect rct;
	CFont ttf;
	CFont tdf;
	CFont taf;
	CFont* pof;
	pdc->SetTextColor(0x00);
	float plargeur=(float)pdc->GetDeviceCaps(HORZRES);
	float phauteur=(float)pdc->GetDeviceCaps(VERTRES);
	tdf.CreateFont((int)phauteur/80,
		(int)plargeur/120,
		0,
		0,
		10 ,//Epaisseur
		0,
		0,
		0,
		DEFAULT_CHARSET,
		OUT_TT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		NONANTIALIASED_QUALITY,//ANTIALIASED_QUALITY,//PROOF_QUALITY,
		DEFAULT_PITCH|FF_DONTCARE,
		"ARIAL");
	ttf.CreateFont((int)phauteur/50,
		(int)plargeur/80,
		0,
		0,
		800 ,//Epaisseur
		0,
		0,
		0,
		DEFAULT_CHARSET,
		OUT_TT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		NONANTIALIASED_QUALITY,//ANTIALIASED_QUALITY,//PROOF_QUALITY,
		DEFAULT_PITCH|FF_DONTCARE,
		"ARIAL");
	taf.CreateFont((int)phauteur/30,
		(int)plargeur/50,
		0,
		0,
		800 ,//Epaisseur
		0,
		0,
		0,
		DEFAULT_CHARSET,
		OUT_TT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		NONANTIALIASED_QUALITY,//ANTIALIASED_QUALITY,//PROOF_QUALITY,
		DEFAULT_PITCH|FF_DONTCARE,
		"ARIAL");
	rct.left=(LONG)(plargeur/3);
	rct.right=(LONG)(plargeur/1.5);
	rct.top=(LONG)(pdc->GetDeviceCaps(PHYSICALOFFSETY)+(float)(phauteur/15));
	rct.bottom=(LONG)(rct.top+(float)(phauteur/30));
	pof=pdc->SelectObject(&taf);
	pdc->DrawText("Gestion d'article",-1,&rct,DT_CENTER|DT_SINGLELINE|DT_VCENTER );
	rct.left=(LONG)(plargeur/1.3);
	rct.right=(LONG)(plargeur/1.1);
	pdc->SelectObject(&tdf);
	pdc->DrawText(Date,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_VCENTER );
	rct.left=(LONG)(plargeur/3);
	rct.right=(LONG)(plargeur/1.5);
	rct.top+=(LONG)(phauteur/30);
	rct.bottom=(LONG)(rct.top+(float)(phauteur/30));
	pdc->SelectObject(&ttf);
	pdc->DrawText(Titre,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_VCENTER );
	rct.left=(LONG)(plargeur/1.3);
	rct.right=(LONG)(plargeur/1.1);
	rct.top=(LONG)(phauteur-(float)(phauteur/25));
	rct.bottom=(LONG)(rct.top+(phauteur/40));
	pdc->SelectObject(&tdf);
	pdc->DrawText(Page,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_VCENTER );
 	pdc->SelectObject(pof);
}
void CBilletDlg::PrintValeur(CDC* pdc,CString vht,CString vttc)
{
	CRect rct;
	CFont ttf;
	CFont tdf;
	CFont taf;
	CFont* pof;
	pdc->SetTextColor(0x00);
	float plargeur=(float)pdc->GetDeviceCaps(HORZRES);
	float phauteur=(float)pdc->GetDeviceCaps(VERTRES);
	tdf.CreateFont((int)phauteur/60,
		(int)plargeur/120,
		0,
		0,
		100 ,//Epaisseur
		0,
		0,
		0,
		DEFAULT_CHARSET,
		OUT_TT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		NONANTIALIASED_QUALITY,//ANTIALIASED_QUALITY,//PROOF_QUALITY,
		DEFAULT_PITCH|FF_DONTCARE,
		"ARIAL");
	rct.left=(LONG)(plargeur/3);
	rct.right=(LONG)(plargeur/1.5);
	rct.top=pdc->GetDeviceCaps(PHYSICALOFFSETY)+(int)(phauteur/15);
	rct.top+=(LONG)(phauteur/15);
	rct.bottom=rct.top+(LONG)(phauteur/40);
	rct.left=pdc->GetDeviceCaps(PHYSICALOFFSETX)+(int)(plargeur/5);
	rct.right=(LONG)(plargeur/2);
	pof=pdc->SelectObject(&tdf);
	pdc->DrawText("Valeur du stock H.T. : "+vht+" €",-1,&rct,DT_CENTER|DT_SINGLELINE|DT_VCENTER );
	rct.left=(LONG)(plargeur/2);
	rct.right=(LONG)(plargeur/1.2);
	pdc->SelectObject(&tdf);
	pdc->DrawText("Valeur du stock T.T.C. : "+vttc+" €",-1,&rct,DT_CENTER|DT_SINGLELINE|DT_VCENTER );
 	pdc->SelectObject(pof);

}

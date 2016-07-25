#include "stdafx.h"
#include "Concerto.h"
#include "ConcertoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void CConcertoDlg::PrintControl(CDC* pdc,CString ticket) 
{
	CString temp;
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
	date=ct.Format("%d/%m/%Y  %H:%M");
	CDC m_Cdc;
	CRect rect;
	CRect butrect;
	CRect rct;
	CFont tf;
	CFont mic;
	CFont mid;
	CFont miw;
	CFont cbfont;
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
	CPen finepen(PS_SOLID,1,pencolor);
	CBrush br;
	br.CreateSolidBrush(pencolor);
	if(noprint)
	{
			if(wlargeur>whauteur)				
				plargeur=(float)wlargeur/5;
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
		plargeur=(float)pdc->GetDeviceCaps(HORZRES);//-(2*cdc.GetDeviceCaps(PHYSICALOFFSETX)));
		phauteur=(float)pdc->GetDeviceCaps(VERTRES);//-(2*cdc.GetDeviceCaps(PHYSICALOFFSETY)));
		x=(float)pdc->GetDeviceCaps(PHYSICALOFFSETX);
		largeur=(int)(plargeur/2.1);//
		hauteur= 1000;
	}
	{
		CPen boldpen(PS_SOLID,hauteur/300,pencolor);
		//x1=(float)lmarge;
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
		if(!noprint)
			pdc->StartPage();
		pdc->SelectObject(&boldpen);
		y=(float)(tsorg+150);
		rct.top=tsorg+hauteur/100;//10;
		if(noprint)
			rct.bottom=rct.top+(hauteur/8);
		else
			rct.bottom=(LONG)y;
		bc=(0xFFFFFF);
		pdc->SetBkColor(bc);
		rct.left=(LONG)lmarge+10;
		rct.right=(LONG)xl1-10;
		pdc->FillSolidRect(&rct,bc);
		pdc->SelectObject(&miw);
		pdc->DrawText(nom,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP );
		rct.top+=30;
		rct.bottom+=30;
		pdc->SelectObject(&miw);
		pdc->DrawText(date,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP );
		rct.top+=hauteur/33;//30;
		rct.bottom+=hauteur/33;//30;
		pdc->SelectObject(&miw);
		temp="TICKET N° "+ticket;

		pdc->DrawText(temp,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP );

		rct.top+=hauteur/33;//30;
		rct.bottom+=hauteur/33;//30;
		pdc->SelectObject(&mid);
		pdc->DrawText("TICKET CONTROLE",-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP );
		int memtop=rct.top;
		rct.top=tsorg+hauteur/200;//5;
		int membottom=rct.bottom;
		rct.bottom=membottom-hauteur/12;//85;
		rct.right=(LONG)lmarge+5;
		rct.left=(LONG)((xl1-5));
		pdc->SelectObject(&boldpen);
		pdc->SelectStockObject(NULL_BRUSH);
		pdc->Rectangle(&rct);//60,5,xl1-5,340
		rct.top=memtop+hauteur/28;//35;
		rct.bottom=membottom+hauteur/28;//35;
		rct.right=(LONG)lmarge+10;
		rct.left=(LONG)((xl1-10));
		pdc->SelectObject(&miw);
		pdc->DrawText("  Valable uniquement pour cette soirée  ",-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP );
		pdc->SelectObject(&finepen);
		pdc->MoveTo(300,rct.bottom-hauteur/12);//80);//410);
		pdc->LineTo(310,rct.bottom-hauteur/12);//80);//410);
		if(!noprint)
			pdc->EndPage(); 
		else
			tsorg=rct.bottom;//-hauteur/15;//65;
	}
}

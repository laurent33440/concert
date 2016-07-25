
// EAN128A.cpp : fichier d'implémentationCode barre
//

#include "stdafx.h"
#include "Concerto.h"
#include "ConcertoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define startcode 104;
#define stopcode 106;


CString CConcertoDlg::GetCode128A(CString touche)
{
	CString temp;
	CString	temp1;
	SYSTEMTIME syst;
	int	sc;
	if(edate=="")
	{
		CTime tim=CTime::GetCurrentTime();
		tim.GetAsSystemTime(syst);

		syst.wSecond=0;
		syst.wMinute=0;
		syst.wHour=(WORD)atoi(GetConfigString("Client","eSeuil","5"));//5 heure par défaut
		CTime seuil(syst,-1);// date
		if(tim<seuil)	// test du seuil de passage de date pour les nouveaux tickets
		{
			CTimeSpan sts(1,0,0,0); 
			tim-=sts;
		}
		if(eflag==1)
			edate=tim.Format("%y%m%d");
		else
		{
			edate.Format("%u",RAZ);
			edate=edate.Right(3);
			while(edate.GetLength()<3)
				edate="0"+edate;
		}
		WriteConfigString("Client","eDate",edate);
	}
	int i=1;
	if(eflag==1) //ETC
	{
		temp1.Format("0000000%u",econt);
		i = (perso[atoi(touche)]& 0xff0000)>>16;
		
		touche.Format("%u",i);
		while(touche.GetLength()<2)
			touche="0"+touche;
		temp="RT"+touche+poste.Right(1);
		temp=temp+temp1.Right(5)+edate;
	}
	else
	{
		temp1.Format("000%u",acont[atoi(touche)]);
		//temp1.Format("000%u",ntou);		
		temp="X"+touche+poste.Right(1);
		temp=temp+temp1.Right(3)+edate;
	}

	sc=startcode;
	for(i=0;i<temp.GetLength();i++)
		sc+=(temp.GetAt(i)-32)*(i+1);
	echeck=sc%103;
	return temp;	
}

void CConcertoDlg::PrintBarre128A(CDC* pdc,int x,int y,int cx,int cy,CString cb)
{//x et y = origine du code cx et cy = dimension du code pdc = device context
	CString temp;
	int i;
	int h=((cy-y)*5)/10;//254
	int l=cx/4;
	int xt=x;//(int)lmarge+17;//77;
	int yt=0;
	int pas=2;//cx/200;
	if(paravent)
		pas=2;
	else
		if(printername.Find("Citizen CL-S400DT")!=-1&&!paravent)
			pas=2;
	int t=startcode;
	y=y+(cy-y)/8;//y+12
	CPen pen1(PS_SOLID,pas,RGB(0,0,0));
	pdc->SelectObject(&pen1);
	xt=Scan128A(pdc,TCV[t],xt,y,h,pas);//Startcode

	for(i=0;i<cb.GetLength();i++)
	{
		/*t=cb.GetAt(i)-32;
		if(t>=107||t<0)*/
		t=cb.GetAt(i)-32;
		if(t>=107||t<0)
		{
			temp.Format("Erreur code 128 -> %u",t);
			MessageBox(temp);
			break;
		}
		xt=Scan128A(pdc,TCV[t],xt,y,h,pas);
	}
	xt=Scan128A(pdc,TCV[echeck],xt,y,h,pas);//Checkcode

	xt=Scan128A(pdc,TCV[106],xt,y,h,pas);//StopcodeRT
}

int CConcertoDlg::Scan128A(CDC* pdc,CString temp,int xt,int y,int h,int pas)
{
	for(int i=0;i<temp.GetLength();i++)
	{
		if(temp.GetAt(i)=='1')
		{
			pdc->MoveTo(xt,y);
			pdc->LineTo(xt,y+h);
			xt+=pas;
		}
		else
			xt+=pas;
	}
	return xt;
}




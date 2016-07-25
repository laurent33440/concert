#include "stdafx.h"
#include "Concerto.h"
#include "ConcertoDlg.h"
#include "Message.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void CConcertoDlg::ExportArticle()
{
	int i;
	CString temp;
	CString art;
	CString article;
	CString client;
	CString couleur;
	CString buf;
	DWORD ln;
	DWORD rln;
	CMessage msd;
	CString disk=DiskSel(1);
	if(disk!="")
	{
		article="";
		i=1;
		while(i<NART)
		{
			article=article+libel1[i]+";";
			article=article+libel2[i]+";";
			article=article+libelcons[i]+";";
			article=article+libelspect[i]+";";
			temp.Format("%.2f",prix[i]);
			article=article+temp+";";
			temp.Format("%.2f",tva[i]);
			article=article+temp+";";
			temp.Format("%u",perso[i]);
			article=article+temp+";";
			temp.Format("%u",conso[i]);
			article=article+temp+";";
			temp.Format("%u",valcontrol[i]);
			article=article+temp+"\r\n";
			i++;
		}
		buf="*ARTICLE*\r\n"+article+"*CLIENT*\r\n";

		client=nom+";";
		client+=adresse1+";";
		client+=adresse2+";";
		client+=siret+";";
		temp.Format("%u",autonews);
		client+=temp+";";
		temp.Format("%u",autoprint);
		client+=temp+";";
		client+=TVA+";";
		client+=cur+";";
		client+=lic[0]+";";
		client+=lic[1]+";";
		client+=lic[2]+";";
		client+=lic[3]+";";
		client+=lic[4]+";";
		client+=lic[5]+";";
		client+=lic[6]+";";
		client+=mentiont+";";
		client+=mentionp;
		temp.Format("%u",fprev);
		client+=temp+";";
		temp.Format("%u",nvalplace);
		client+=temp+";";
		temp.Format("%u",valpwd);
		client+=temp+";";
		temp.Format("%u",valpage);
		client+=temp+";";
		temp.Format("%u",NART);
		client+=temp+";";
		temp.Format("%u",NAPP);
		client+=temp;
		buf+=client;
		buf+="\r\n";

		HANDLE hf=CreateFile(disk+"Article Concert.dat",FILE_ALL_ACCESS,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
		ln=buf.GetLength();
		WriteFile(hf,buf.GetBuffer(ln),ln,&rln,NULL);
		CloseHandle(hf);
		msd.mes1="Les articles ont été tranférés";
		msd.mes2="sur le disque "+disk;
		msd.mes3=" ";
		msd.mode=1;
		msd.DoModal();
	}
}


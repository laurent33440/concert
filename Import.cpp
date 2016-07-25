#include "stdafx.h"
#include "Concert.h"
#include "ConcertDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



void CConcertDlg::ImportArticle()
{
	int i;
	int idx;
	int j;
	int k;
	CString couleur;
	CString col;
	CString temp;
	CString art;
	CString article;
	CString client;
	CString buf;
	CString disk;
	DWORD ln;
	DWORD rln;
	CMessage msd;
	char ch=' ';
	CFileStatus rStatus;
	CFileException fex;
	j=GetLogicalDriveStrings(500,disk.GetBuffer(500));
	disk.ReleaseBuffer(j);
	i=0;
	do
	{
		if((i<j-1)&&disk.GetAt(i)==0)
			disk.SetAt(i,'_');
		i++;
	}
	while(i<j);
	disk.ReleaseBuffer(-1);
	disk="_"+disk;
debut:;
	do
	{
		if((i=disk.ReverseFind('_'))!=-1)
		{
			temp=disk.Mid(i+1,3);
		}
		else
		{	
			disk="";
			break;
		}
		if(GetDriveType(temp)==DRIVE_REMOVABLE||GetDriveType(temp)==DRIVE_FIXED)
			break;
		disk=disk.Left(i);
	}
	while(disk.GetLength()>3);
	if(disk.GetLength()>=3)
	{
		msd.mes3="  ";
		msd.mes1="Voulez-vous utiliser le disque "+temp;
		msd.mes2=" ";
		msd.mode=0;
		if(msd.DoModal()==IDCANCEL)
		{
			disk=disk.Left(i);
			goto debut;
		}
		disk=temp;
		HANDLE hf;
		if((hf=CreateFile(disk+"Article.dat",GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL))==INVALID_HANDLE_VALUE)
		{
			msd.mes3=" ";
			msd.mes1="Aucun fichier articles trouvé !";
			msd.mes2="Veuillez recommencer.";
			msd.mode=1;
			msd.DoModal();
			goto fin;
		}
		ln=64000;
		ReadFile(hf,buf.GetBuffer(ln),ln,&rln,NULL);
		CloseHandle(hf);
		buf.ReleaseBuffer(rln);
		i=buf.Find("*ARTICLE*");
		j=buf.Find("*CLIENT*");
		k=buf.Find("*COULEUR*");
		article=buf.Mid(i+11,j-i-11);
		client=buf.Mid(j+10,buf.GetLength()-j-10);
		couleur=buf.Mid(k+11,buf.GetLength()-k-11);
		idx=0;
		i=1;
		CWinApp* pa=AfxGetApp();
		while(i<NART)
		{
			art.Format("%u",i);
			if((j=article.Find(";",idx))==-1)
				break;
			libel1[i]=article.Mid(idx,j-idx);
			pa->WriteProfileString(art,"LIBELLE1",libel1[i]);
			idx=j+1;
			if((j=article.Find(";",idx))==-1)
				break;
			libel2[i]=article.Mid(idx,j-idx);
			pa->WriteProfileString(art,"LIBELLE2",libel2[i]);
			idx=j+1;
			if((j=article.Find(";",idx))==-1)
				break;
			libelcons[i]=article.Mid(idx,j-idx);
			pa->WriteProfileString(art,"LIBELCONS",libelcons[i]);
			idx=j+1;
			if((j=article.Find(";",idx))==-1)
				break;
			libelspect[i]=article.Mid(idx,j-idx);
			pa->WriteProfileString(art,"LIBELSPECT",libelspect[i]);
			idx=j+1;
			if((j=article.Find(";",idx))==-1)
				break;
			prix[i]=(float)atof(article.Mid(idx,j-idx));
			pa->WriteProfileInt(art,"PRIX",(int)(prix[i]*100));
			idx=j+1;
			if((j=article.Find(";",idx))==-1)
			tva[i]=(float)atof(article.Mid(idx,j-idx));
			pa->WriteProfileInt(art,"TVA",(int)(tva[i]*100));
			idx=j+1;
			if((j=article.Find(";",idx))==-1)
				break;
			perso[i]=atoi(article.Mid(idx,j-idx));
			pa->WriteProfileInt(art,"PERSO",perso[i]);
			idx=j+1;
			if((j=article.Find(";",idx))==-1)
				break;
			conso[i]=atoi(article.Mid(idx,j-idx));
			pa->WriteProfileInt(art,"CONSO",conso[i]);
			idx=j+1;
			if((j=article.Find("\r\n",idx))==-1)
				break;
			valcontrol[i]=atoi(article.Mid(idx,j-idx));
			pa->WriteProfileInt(art,"VCONSO",valcontrol[i]);
			idx=j+2;
			i++;
		}
		idx=0;
		if((j=client.Find(";",idx))==-1)
			goto fin;
		nom=client.Mid(idx,j-idx);
		pa->WriteProfileString("Client","Nom",nom);
		idx=j+1;
		if((j=client.Find(";",idx))==-1)
			goto fin;
		adresse1=client.Mid(idx,j-idx);
		pa->WriteProfileString("Client","Adresse1",adresse1);
		idx=j+1;
		if((j=client.Find(";",idx))==-1)
			goto fin;
		adresse2=client.Mid(idx,j-idx);
		pa->WriteProfileString("Client","Adresse2",adresse2);
		idx=j+1;
		if((j=client.Find(";",idx))==-1)
			goto fin;
		adresse3=client.Mid(idx,j-idx);
		pa->WriteProfileString("Client","Adresse3",adresse3);
		idx=j+1;
		if((j=client.Find(";",idx))==-1)
			goto fin;
		siret=client.Mid(idx,j-idx);
		pa->WriteProfileString("Client","Siret",siret);
		idx=j+1;
		if((j=client.Find(";",idx))==-1)
			goto fin;
		temp=client.Mid(idx,j-idx);
		valad1=atoi(temp);
		pa->WriteProfileInt("Param","ValAdresse1",valad1);
		idx=j+1;
		if((j=client.Find(";",idx))==-1)
			goto fin;
		temp=client.Mid(idx,j-idx);
		valad2=atoi(temp);
		pa->WriteProfileInt("Param","ValAdresse2",valad2);
		idx=j+1;
		if((j=client.Find(";",idx))==-1)
			goto fin;
		temp=client.Mid(idx,j-idx);
		autonews=atoi(temp);
		pa->WriteProfileInt("Param","autonews",autonews);
		idx=j+1;
		if((j=client.Find("\r\n",idx))==-1)
			goto fin;
		temp=client.Mid(idx,j-idx);
		autoprint=atoi(temp);
		pa->WriteProfileInt("Param","Autoprint",autoprint);
		idx=j+1;
		if((j=client.Find("\r\n",idx))==-1)
			goto fin;
		temp=client.Mid(idx,j-idx);
		master=atoi(temp);
		pa->WriteProfileInt("Param","Master",master);
		idx=0;
		i=0;
		while(i<NART)
		{
			temp.Format("%u",i);

			if((j=couleur.Find(";",idx))==-1)
				break;
			col="butartrefcolor"+temp;
			butartrefcolor[i]=atoi(couleur.Mid(idx,j-idx));
			pa->WriteProfileInt("Couleur",col,butartrefcolor[i]);
			idx=j+1;
			if((j=couleur.Find("\r\n",idx))==-1)
				break;
			col="txtbutartrefcolor"+temp;
			txtbutartrefcolor[i]=atoi(couleur.Mid(idx,j-idx));
			pa->WriteProfileInt("Couleur",col,txtbutartrefcolor[i]);
			idx=j+2;
			i++;
		}
		msd.mes1="Les articles ont été chargés";
		msd.mes2="dans la billetterie "+disk;
		msd.mes3=" ";
		msd.mode=1;
		msd.DoModal();
	}
	else
	{
		msd.mes3=" ";
		msd.mes1="Aucun disque sélectionné !";
		msd.mes2="Veuillez recommencer.";
		msd.mode=1;
		msd.DoModal();
	}
fin:;
	OnBnClickedArticle();
}

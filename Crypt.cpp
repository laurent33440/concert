#include "stdafx.h"
#include "Concerto.h"
#include "ConcertoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int CConcertoDlg::CWrite(CString path,CString txt, int mode) 
{
	char ch=1;
	DWORD nbw;
	CString temp;
	CString ner;
	CString temp1="";
	CString temp2="";
	CString temp3="";
	CString buf;
	CString fname;
	FILEINFO fi;
	CString filetime;
	CString filesize;
	CString fdate;
	CString fsize;
	DWORD64 key;
	DWORD64 pathkey;
	DWORD64 privatekey=0x4FC86E5C65F73A84;
	CFileStatus cfs;
	HANDLE hf;
	int wdg;
	buf=txt;
	int idx=path.ReverseFind('\\');
	fname=path.Mid(idx+1);
	if(path.Find("Auditinfo",0)!=-1||path.Find("csys.avs",0)!=-1||path.Find("Exercice.dat",0)!=-1||path.Find("csat.avs",0)!=-1)
		pathkey=0x4FC86E5C659;
	else
	{
		temp=path.Mid(idx+3);
		pathkey=_atoi64(temp);
	}
	key=pathkey+privatekey;
	temp.Format("%I64X",key);
	if(crypted==1||path.Find("csys.avs",0)!=-1)
	{
		for(int i=0;i<buf.GetLength();i++)
		{
			buf.SetAt(i,buf.GetAt(i)+(UCHAR)(key&0x7F));	
			key=_rotr64(key,1);
		}
	}
	wdg=0;
retry_open:;
	if(mode==1||mode==3)
	{
		if(pathkey==0x4FC86E5C659)
		{
			temp=path;
			hf=(CreateFile(temp,GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL));
			if(hf==INVALID_HANDLE_VALUE)
				goto erreur_open;
			if(SetFilePointer(hf,0,NULL,FILE_END)==INVALID_SET_FILE_POINTER)
			{
				CloseHandle(hf);
				goto erreur_open;
			}
		}
		else
		{
			temp=path+"\\Concert.dat";
			hf=(CreateFile(temp,GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL));
			if(hf==INVALID_HANDLE_VALUE)
				goto erreur_open;
			if(SetFilePointer(hf,0,NULL,FILE_END)==INVALID_SET_FILE_POINTER)
			{
				CloseHandle(hf);
				goto erreur_open;
			}
		}
	}
	else
	{
		if(pathkey==0x4FC86E5C659)// Fichier crypté
		{
			temp=path;
			hf=(CreateFile(temp,GENERIC_READ|GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL));
		}
		else
		{
			temp=path+"\\Concert.dat";
			hf=(CreateFile(temp,GENERIC_READ|GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL));
		}
	}
	if(hf!=INVALID_HANDLE_VALUE)
	{
		if(WriteFile(hf,buf.GetBuffer(),buf.GetLength(),&nbw,NULL))
			FlushFileBuffers(hf);
		else
		{



		}
		if(pathkey!=0x4FC86E5C659)
		{
			fi=GetTimeSizeInfo(hf);
			filesize.Format("%u",fi.size);	
			filetime.Format("%lld",fi.time);
			WriteConfigString("Infocert","Datatime",filetime);
			WriteConfigString("Infocert","Datasize",filesize);
		}
		if(path.Find("Exercice.dat",0)!=-1&&temp.Find(datadir,0)!=-1)
		{
			fi=GetTimeSizeInfo(hf);
			filesize.Format("%u",fi.size);	
			filetime.Format("%lld",fi.time);
			WriteConfigString("Infocert","Exertime",filetime);
			WriteConfigString("Infocert","Exersize",filesize);
		}
		if(path.Find("csat.avs",0)!=-1&&temp.Find(sysdir,0)!=-1)
		{
			fi=GetTimeSizeInfo(hf);
			filesize.Format("%u",fi.size);	
			filetime.Format("%lld",fi.time);
			WriteConfigString("Infocert","Cattime",filetime);
			WriteConfigString("Infocert","Catsize",filesize);
		}
		if(path.Find("Auditinfo",0)!=-1)
		{
			fi=GetTimeSizeInfo(hf);
			filesize.Format("%u",fi.size);	
			filetime.Format("%lld",fi.time);
			WriteConfigString("Infocert","Infotime",filetime);
			WriteConfigString("Infocert","Infosize",filesize);
		}
		CloseHandle(hf);
		return 1;
	}
	else
	{
erreur_open:;
		Sleep(100);
		wdg++;
		if(wdg<20)
			goto retry_open;
		ner.Format("%u",GetLastError());
		MessageBox("Erreur d'ouverture écriture N° "+ner+" "+temp);
		return 0;
	}
}

CString CConcertoDlg::CRead(CString path) 
{
	HANDLE hf;
	CString buf="Erreur de lecture fichier";
	CString temp;
	CString fname;
	CString fdate;
	CString fsize;
	DWORD nbw;
	DWORD64 key;
	DWORD64 pathkey;   //0x4FC86E0000000000;
	DWORD64 privatekey=0x4FC86E5C65F73A84;
	int idx=path.ReverseFind('\\');
	fname=path.Mid(idx+1);
	CFileStatus cfs;
	CString filetime;
	CString filesize;
	int wdg;
	if(path.Find("Auditinfo",0)!=-1||path.Find("csys.avs",0)!=-1||path.Find("Exercice.dat",0)!=-1||path.Find("csat.avs",0)!=-1)
	{
		pathkey=0x4FC86E5C659;	// fichier de gestion
		temp="Erreur de traitement "+fname;
	}
	else
	{	// Fichier de données de vente
		temp=path.Mid(idx+3);
		pathkey=_atoi64(temp);
	}
	wdg=0;
retry:;
	key=pathkey+privatekey;
	if(pathkey==0x4FC86E5C659)
		hf=(CreateFile(path,GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL));
	else
		hf=(CreateFile(path+"\\Concert.dat",GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL));
	buf.Preallocate(GetFileSize(hf,0)+100);
	if(hf!=INVALID_HANDLE_VALUE)
	{
		if(!ReadFile(hf,buf.GetBuffer(GetFileSize(hf,0)),GetFileSize(hf,0),&nbw,NULL))
		{
			CloseHandle(hf);
			return "";
		}
		buf.ReleaseBuffer(nbw);
		CloseHandle(hf);
		if(buf.Find("Open",0)==0|| buf.Find("Config file",0)==0|| buf.Find("Audit file",0)==0|| buf.Find("avs file",0)==0|| buf.Find("Exercice file",0)==0|| buf.Find("Cat file",0)==0)// mets tous les fichiers cryptés
		{
			if(crypted==1||path.Find("csys.avs",0)!=-1)
			{
				if(buf.Find("avs file",0)==0)
				{
					buf.Replace("avs file","Config file");
					for(int i=0;i<buf.GetLength();i++)
					{
						buf.SetAt(i,buf.GetAt(i)+(UCHAR)(key&0x7F));	
						key=_rotr64(key,1);
					}
					if(pathkey==0x4FC86E5C659)
						hf=(CreateFile(path,GENERIC_READ|GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL));
					else
						hf=(CreateFile(path+"\\Concert.dat",GENERIC_READ|GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL));
					//SetFilePointer(hf,NULL,NULL,FILE_END);
					if(hf!=INVALID_HANDLE_VALUE)
					{
						WriteFile(hf,buf.GetBuffer(),buf.GetLength(),&nbw,NULL);
						FlushFileBuffers(hf);
						CloseHandle(hf);
						goto retry;
					}
				}
				else
				{
					for(int i=0;i<buf.GetLength();i++)
					{
						buf.SetAt(i,buf.GetAt(i)+(UCHAR)(key&0x7F));	
						key=_rotr64(key,1);
					}
				}
			}
		}
		else
		{
			for(int i=0;i<buf.GetLength();i++)
			{
				buf.SetAt(i,buf.GetAt(i)-(UCHAR)(key&0x7F));
				key=_rotr64(key,1);
			}
			if((buf.Find("Open",0)!=0||buf.GetAt(15)!=' ')&&(path.Find("Auditinfo",0)==-1&&path.Find("csys.avs",0)==-1&&path.Find("Exercice.dat",0)==-1&&path.Find("csat.avs",0)==-1))
			{
				buf="";
				temp=path.Mid(idx+1);
				if(wsel!=1)
				{
					AfxMessageBox("La cession "+temp+" a été corrompue");
					FonctionEditeur("Le fichier concert.dat de "+dopen+" est corrompu");
				}
				if(wsel!=1)
					AfxMessageBox("La cession "+temp+" a été corrompue");
				if(wsel==1)
				{//20150129122242
					AfxMessageBox("La cession "+temp+" a été corrompue\nUn nouveau fichier de ticket sera ouvert.");
					CopyFile(path+"\\Concert.dat",path+"\\Concert corrompu.dat",FALSE);// sauvegarde du fichier corrompu
					temp=securedir+"\\Data\\"+dopen;
					CopyFile(path+"\\Concert.dat",temp+"\\Concert corrompu.dat",FALSE);// sauvegarde du fichier corrompu surD
					temp=backupdir+"\\Data\\"+dopen;
					CopyFile(path+"\\Concert.dat",temp+"\\Concert corrompu.dat",FALSE);// sauvegarde du fichier corrompu surD
					buf="Open "+dopen.Mid(6,2)+"/"+dopen.Mid(4,2)+"/"+dopen.Left(4)+" "+dopen.Mid(8,2)+":"+dopen.Mid(10,2)+":"+dopen.Mid(12,2);
						temp.Format("%u",(int)fversion);
					buf+=";"+temp;
					temp.Format("%u",(int)RAZ+1);
					buf+=";"+temp;
					buf+=";"+GetConfigString("License","Serial","");
					buf+=";"+nom;	
					buf+=";"+adresse1;	
					buf+=";"+adresse2;	
					buf+=";"+siret;	
					buf+=";"+naf;	
					buf+="\r\n";
					CWrite(opendir,buf,0);
					FonctionEditeur("Le fichier concert.dat de "+dopen+" est corrompu. Un nouveau fichier est créé");
				}
			}
			else // mets tous les fichiers non cryptés
			{
				if(crypted==0&&path.Find("csys.avs",0)!=-1&&path.Find("csat.avs",0)!=-1)
				{
					if(pathkey==0x4FC86E5C659)
						temp=path;
					else
						temp=path+"\\Concert.dat";
					hf=(CreateFile(temp,GENERIC_READ|GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL));
					if(hf!=INVALID_HANDLE_VALUE)
					{

						WriteFile(hf,buf.GetBuffer(),buf.GetLength(),&nbw,NULL);
						FlushFileBuffers(hf);
						CloseHandle(hf);
					}
					else
						AfxMessageBox("Erreur d'ouverture lecture "+temp);
				}
			}
		}
	}
	else
	{
		Sleep(100);
		wdg++;
		if(wdg<20)
			goto retry;
		if(pathkey==0x4FC86E5C659&&fdate!="20120601000000")
			DefautIntegrite("Le fichier "+path+" est absent");
		else
			if(fdate!="20120601000000")
				DefautIntegrite("Le fichier "+path+"\\Concert.dat est absent");
	}
	return buf;
}


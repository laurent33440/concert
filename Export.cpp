#include "stdafx.h"
#include "Concerto.h"
#include "ConcertoDlg.h"
#include "Message.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


int CConcertoDlg::ExportData(CString tmois,CString tan)
{
	int j;
	CString temp;
	CString temp1;
	CString disk="";
	CString tempdisk;
	CString target;
	CMessage msd;
	CFileFind cfd;
	CFileFind cff;
	int result;
	int k=atoi(tan);
	j=atoi(tmois);
	if(j==0)
	{
		j=1;
		tmois="01";
	}
	CTime startdate(k,j,1,0,0,0,-1);
	k++;
	CTime stopdate(k,j,1,0,0,0,-1);
		//if(disk.GetLength()>=3)
	disk=controldir+"\\FISCAL";
	CreateDirectory(disk,NULL);
	disk+="\\";
	result=cff.FindFile(datadir+"\\*.*",0 );
	dirlist.ResetContent();
	while(result)
	{
		result=cff.FindNextFile();
		if (cff.IsDots())
		 continue;
		if(cff.IsDirectory())
		{
			temp1=cff.GetFileName();
			CTime*pcurdate = new CTime(atoi(temp1.Mid(0,4)),atoi(temp1.Mid(4,2)),1,0,0,0,-1);
			if(*pcurdate>=startdate && *pcurdate<stopdate)
			{
				if(cff.GetFileName()!=dopen)
					dirlist.AddString(cff.GetFileName());
			}
			delete pcurdate;
		}
	}
	if(dirlist.GetCount()>0)
	{
		targetexport=disk+"Resultats "+tmois+"-"+tan+" Concermatic Poste "+poste;
		CreateDirectory(targetexport,NULL);
		resultexport=0;
		msd.mes1="Exportation des résultats "+tmois+"-"+tan;
		msd.mes2="Transfert en cours ...";
		msd.mes3="  ";
		msd.mode=6;
		msd.psource=this;
		msd.DoModal();
		msd.mes1="Exportation des résultats "+tmois+"-"+tan;
		msd.mes3="  ";
		msd.mode=1;
		if(resultexport==0)
			msd.mes2="Tranfert sur le disque terminé avec succès";
		else
		{
			msd.mes2="Des erreurs ont été détectées.";
			msd.mes3="Veuillez recommencer.";
		}
	}
	else
	{
		msd.mes1="Exportation des résultats "+tmois+"-"+tan;
		msd.mode=1;
		msd.mes2="Pas de résultat pour la période.";
		msd.mes3="Veuillez modifier votre choix.";
		resultexport=0;
	}
	msd.DoModal();
	return resultexport;
}
int CConcertoDlg::ExportArchData(CString std,CString end)
{
	CZipArchive zip;
	int i=0;
	int idx;
	int idy;
	int k;
	int j;
	CString st;
	CString temp;
	CString temp1;
	CString txttvaca;
	CString txtcatva;
	CString target;
	CString dir;
	CFileFind cfa;
	CFileFind cfd;
	CFileFind cff;
	CFileFind cfz;
	CString zipliste="Liste des fichiers\r\n";
	int resulta;
	int resz;
	double cumulp;
	double xcatva[10];
	double xtvaca[10];
	double tvaca;
	double catva;
	while(i<10)
	{
		xcatva[i]=0;
		xtvaca[i]=0;
		i++;
	}
	resultexport=0;
	HANDLE hf;
	DWORD len;
	CTime tim=CTime::GetCurrentTime();
	CTime startdate(atoi(std.Mid(6,4)),atoi(std.Mid(3,2)),atoi(std.Mid(0,2)),0,0,0,-1);
	CTime stopdate(atoi(end.Mid(6,4)),atoi(end.Mid(3,2)),atoi(end.Mid(0,2)),0,0,0,-1);
	resulta=cfa.FindFile(archdir+"\\*.*",0 );
	dirlist.ResetContent();
	tl.ResetContent();
	while(resulta)
	{
		resulta=cfa.FindNextFile();
		if (cfa.IsDots())
		 continue;
		if(cfa.IsDirectory())
		{
			FindArchData(startdate,stopdate,cfa.GetFilePath());
		}
	}
	cfa.Close();
	FindArchData(startdate,stopdate,workdir);

	if(dirlist.GetCount()>0)
	{
		if((hf=CreateFile(archdir+"\\Archive.dat",GENERIC_READ|GENERIC_WRITE,0,NULL,CREATE_NEW,FILE_ATTRIBUTE_NORMAL,NULL))!=INVALID_HANDLE_VALUE)
		{
			temp=tim.Format("%Y%d%m%H%M%S");
			zip.Open(archdir+"\\Export fiscal "+nom+ " POSTE "+poste+" "+temp+".zip", CZipArchive::zipCreate);
			// set the compression method
			zip.SetPassword("65748392",-1);
			zip.SetEncryptionMethod(CZipCryptograph::encWinZipAes256);
			st="";
			for(i=0;i<tl.GetCount();i++)
			{
				dirlist.GetText(i,target);
				tl.GetText(i,temp1);
				j=target.ReverseFind('\\');
				dir=target.Right(target.GetLength()-j-1);
				zip.AddNewFile(target+"\\Concert.dat",dir+"\\Concert.dat",-1, zip.zipsmSafeSmart, 65536);
				//20140710205205;Close 10/07/2014 20:59:45 NGTZ 1 GTP 335.00 GTZ 335.00;20.00%;335.00
				zipliste+=dir+"\\Concert.dat\r\n";

				if((idx=temp1.Find("GTZ ",0))!=-1)
				{
					idx=idx+4;
					idy=temp1.Find(";",idx);
					idx=idy+1;//Début TVA
					while((idy=temp1.Find(";",idx))!=-1)//||(idy=temp1.Find("\r\n",idx))!=-1)
					{
						txttvaca=temp1.Mid(idx,idy-idx);
						tvaca=atof(temp1.Mid(idx,idy-idx));
						idx=idy+1;
						if((idy=temp1.Find(";",idx))!=-1||(idy=temp1.Find("|",idx))!=-1||(idy=temp1.Find("\r\n",idx))!=-1)
							catva=atof(temp1.Mid(idx,idy-idx));
						txtcatva=temp1.Mid(idx,idy-idx);
						k=0;
						while(k<10)
						{// récupérarion des TVA de chaque cloture
							if(tvaca==xtvaca[k])
							{
								break;
							}
							k++;
						}
						if(k>=10)
						{
							k=0;
							while(k<10)
							{
								if(xtvaca[k]==0)
								{
									xtvaca[k]=tvaca;
									break;
								}
								k++;
							}
						}
						xcatva[k]+=catva;
						if((idy=temp1.Find(";",idx))!=-1)
							idx=idy+1;
						else
							break;//if((idy=temp1.Find("\r\n",idx))!=-1)
						//MessageBox("new cycle");
								//idx=idy+2;

					}
				}
				else
				{
					st="erreur d'achivage";
					goto ERREUR;
				}
				st+=temp1;
			}
			st="";
			cumulp=0;
			for(i=0;i<10;i++)
			{
				if(xtvaca[i]>0)
				{
					cumulp+=xcatva[i];
					temp.Format("%.2f",xtvaca[i]);
					temp1.Format("%.2f",xcatva[i]);
					st+=temp+";"+temp1+";";
				}
			}		
			temp1.Format("%.2f",cumulp);
			st+=temp1+";";
			temp1=tim.Format("%Y%m%d%H%M%S");
			st+=temp1+";";
			st+=poste+";";
			st+="ArchiveExport";
			temp="";
			if(infocert)
			{
				for(i=0;i<10;i++)
				{
					if(xtvaca[i]!=0)
					{
						temp1.Format("%.2f",xtvaca[i]);
						temp+=temp1+",";
						temp1.Format("%.2f",xcatva[i]);
						temp+=temp1+",";
					}
				}
				temp=temp.Left(temp.GetLength()-1);// enlève la virgule de fin
				temp.Replace(".","");
				spart[0]=temp;// TTC par TVA
				temp1.Format("%.2f",cumulp);
				temp1.Replace(".","");
				spart[1]=temp1;// grand total période
				temp1=tim.Format("%Y%m%d%H%M%S");
				spart[2]=temp1;// date
				spart[3]=poste;// identification
				spart[4]="ArchiveExport";//Type d'opération
				spart[5]=sarchd;//Type d'opération
				sarchd=Sign(8);// Signature archive
				WriteConfigString("Infocert","SignArchExport",sarchd);
			}
			st+="|"+sarchd+"\r\n";
ERREUR:;
			resz=cfz.FindFile(workdir+"\\Auditinfo*.dat",0);
			while(resz)
			{
				resz=cfz.FindNextFileA();
				if (cfz.IsDots())
				 continue;
				if(cfz.IsDirectory())
				 continue;
				zipliste+=cfz.GetFileName()+"\r\n";
			}
			cfz.Close();
			zipliste+="Archive.dat\r\nDonnées archive\r\n";
			st=zipliste+st;
			if(!WriteFile(hf,st.GetBuffer(st.GetLength()),st.GetLength(),&len,NULL))
			{
				MessageBox("Erreur écriture Archive.dat");
				resultexport++;
			}
			FlushFileBuffers(hf);
			CloseHandle(hf);
			Sleep(100);
			zip.AddNewFile(archdir+"\\Archive.dat",-1,false, zip.zipsmSafeSmart, 65536);
			temp=tim.Format("%Y%d%m%H%M%S");
			Exportation(" Export "+nom+ " POSTE "+poste+" du "+std+" au "+end);
			zip.AddNewFiles(workdir,"Auditinfo*.dat",false,-1,true, zip.zipsmSafeSmart, 65536);
			temp="Veuillez contacter la société Dine O Quick au 01 46 42 18 61 pour toute info complémentaire.\r\n"+sarchd;
			zip.SetGlobalComment(temp,ZIP_DEFAULT_CODE_PAGE);
			zip.FlushBuffers();
			zip.Close();
			DeleteFile(archdir+"\\Archive.dat");
		}
	}
	return resultexport;
}

void CConcertoDlg::FindArchData(CTime startdate,CTime stopdate,CString path)
{
	CString temp;
	CString temp1;
	CString rep;
	CString temp2;;
	int idx;
	int idy;
	int idz;
	CFileStatus cfs;
	temp1=path+"\\Data\\Exercice.dat";
	temp=CRead(temp1);
	if((idx=temp.Find("Open ",0))!=-1)
	{
		if((idy=temp.Find("\r\n",idx))!=-1)
		{
			idx=idy+2;
			while(temp.Mid(idx,5)!="Close")
			{
				if((idz=temp.Find("\r\n",idx))==-1)
					break;
				rep=temp.Mid(idx,14);
				if(rep=="")
					break;
				CTime reptim(atoi(rep.Left(4)),atoi(rep.Mid(4,2)),atoi(rep.Mid(6,2)),0,0,0,-1);
				if(reptim>=startdate&&reptim<=stopdate)
				{
					temp2=path+"\\Data\\"+rep;
					if(CFile::GetStatus(temp2+"\\Concert.dat",cfs))
						dirlist.SetItemData(dirlist.AddString(temp2),1);
					else
						dirlist.SetItemData(dirlist.AddString(temp2),0);
					tl.AddString(temp.Mid(idx,idz+2-idx));
				}
				idx=idz+2;				
			}
		}
	}
}



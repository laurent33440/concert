#include "stdafx.h"
#include "Concerto.h"
#include "ConcertoDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void CConcertoDlg::ImportFichierExterne(CString source)
{
	CString dir;
	HANDLE hfr;
	HANDLE hf;
	CString buf;
	CString temp;
	CString ftxt;
	CString ticket;;
	CString liste;
	CString nart;
	CString impposte;
	CString implibel1;
	CString implibel2;
	CString imptitre;
	CString date;
	CString jour;
	CString mois;
	CString an;
	int i;
	int idxstart=0;
	int idxstop=0;
	int idxmem=0;
	int idxcaract=0;
	DWORD len;
	hfr=CreateFile(source,GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if(ReadFile(hfr,buf.GetBuffer(GetFileSize(hfr,NULL)),GetFileSize(hfr,NULL),&len,NULL))
	{
		buf.ReleaseBuffer(len);
		CloseHandle(hfr);
		//MessageBox(source);
		if(source.Find(".mev",0)!=-1)
		{
			if((idxstart=buf.Find("<title>",0))!=-1)
			{
				if((idxcaract=buf.Find("&#202;",0))!=-1)
				{
					temp=buf.Left(idxcaract)+"Ê";	
					buf=temp+buf.Mid(idxcaract+6);
				}				
				if((idxstop=buf.Find("</title>",idxstart))!=-1)//(idxstop=buf.Find("@",idxstart))!=-1||
				{
					
					imptitre=buf.Mid(idxstart+7,(idxstop-idxstart-7));
					imptitre=imptitre.Left(40);
					if((idxstart=buf.Find("<date>",idxstop))!=-1)
					{
						if((idxstop=buf.Find("</date>",idxstart))!=-1)
						{
							temp=buf.Mid(idxstart+6,10);
							date=temp.Right(2);
							date=date+temp.Mid(4,4);
							date=date+temp.Left(4);
						}
					}
				}
			}			
			while(TRUE)
			{
				idxstart=idxstop;
				if((idxstart=buf.Find("<ticket>",idxstart))!=-1)
				{
					if((idxstop=buf.Find("</ticket>",idxstart))!=-1)
					{
						ticket=buf.Mid(idxstart+8,12);
						liste+=ticket+" \r\n";
					}
					else break;
				}
				else break;
			}
		}
		else
		{
			idxstart=0;
			if((idxstop=buf.Find("\r\n",idxstart))!=-1)
			{
				impposte=buf.Mid(idxstart,(idxstop-idxstart));
				idxstart=idxstop+2;
				if((idxstop=buf.Find("\r\n",idxstart))!=-1)
				{
					implibel1=buf.Mid(idxstart,(idxstop-idxstart));
					idxstart=idxstop+2;
					if((idxstop=buf.Find("\r\n",idxstart))!=-1)
					{
						implibel2=buf.Mid(idxstart,(idxstop-idxstart));
						imptitre=implibel1+" "+implibel2;
						idxstart=idxstop+2;
						if((idxstop=buf.Find("\r\n",idxstart))!=-1)
						{
							temp=buf.Mid(idxstart,(idxstop-idxstart));
							if((idxstop=temp.Find("/",0))!=-1)
							{
								if(idxstop>1)
									jour=temp.Mid(idxstop-2,2);
								else
									jour="";
								idxstop++;
								idxmem=idxstop;
								idxstart=idxstop;
								if((idxstop=temp.Find("/",idxstart))!=-1)
								{
									mois=temp.Mid(idxmem,idxstop-idxmem);
									idxstop++;
									i=atoi(temp.Mid(idxstop,temp.GetLength()-idxstop));
									an.Format("%u",i);
								}
								else
								{
									mois="";
									an="";
								}
								date=jour+"/"+mois+"/"+an;
							}
							else
								date="";
						}
						/*if(date=="")
							lba.SetItemData(lba.AddString(titre),idx);
						else
							lba.SetItemData(lba.AddString(titre+" le "+date),idx);*/
					}
				}
			}
			if((idxstart=buf.Find("ticket",idxstart))!=-1)
			{
				idxstart+=8;
				liste=buf.Right(buf.GetLength()-idxstart);
			}




			for(int fi=1;fi<=16;fi++)
			{
				ftxt.Format("0%u",fi);					
				hf=(CreateFile(controldir+"\\tempcontrol"+ftxt.Right(2)+".dat",GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,FILE_FLAG_WRITE_THROUGH|FILE_ATTRIBUTE_NORMAL,NULL));
				if(hf==INVALID_HANDLE_VALUE)
					break; // Vérification emplacement libre pour nouveau fichier
				else
					CloseHandle(hf);
			}
			hf=(CreateFile(controldir+"\\tempcontrol"+ftxt.Right(2)+".dat",GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,FILE_FLAG_WRITE_THROUGH|FILE_ATTRIBUTE_NORMAL,NULL));
			if(hf==INVALID_HANDLE_VALUE)
			{
				hf=(CreateFile(controldir+"\\tempcontrol"+ftxt.Right(2)+".dat",GENERIC_READ | GENERIC_WRITE,0,NULL,CREATE_NEW,FILE_FLAG_WRITE_THROUGH|FILE_ATTRIBUTE_NORMAL,NULL));
			}
	retry:;
			SetFilePointer(hf,NULL,NULL,FILE_END);
			buf=liste;
			if(!WriteFile(hf,buf.GetBuffer(),buf.GetLength(),&len,NULL))
			{
				goto retry;
			}
			if(len<(DWORD)buf.GetLength())
			{
				buf=buf.Mid(len);
				goto retry;
			}
			CloseHandle(hf);
			DeleteFile(source);
		}
		if(source.Find(".mev",0)==-1)
		{
			i=1; // **** RECHERCHE DE FICHIERS DU MEME ARTICLE ****
			while(i<=16)
			{
				if(clibel1[i]==imptitre&&clibel2[i]==date)//&&cfrom[i]=="Billetterie N°"+impposte)
				{
					temp.Format("0%u",i);
					dir=controldir+"\\"+temp.Right(2);
					CreateDirectory(dir,NULL);
					hf=(CreateFile(dir+"\\Controle.dat",GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL));
					SetFilePointer(hf,0,0,FILE_END);
					break;
				}
				i++;
			}
		}
		if(i>16||source.Find(".mev",0)!=-1)
		{
			i=1;// **** OU CREATION D'UN NOUVEAU FICHIER ****
			while(i<=16)
			{
				temp.Format("0%u",i);
				dir=controldir+"\\"+temp.Right(2);
				CreateDirectory(dir,NULL);
				hf=(CreateFile(dir+"\\Controle.dat",GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL));
				if(hf==INVALID_HANDLE_VALUE)
				{
					hf=(CreateFile(dir+"\\Controle.dat",GENERIC_READ|GENERIC_WRITE,0,NULL,CREATE_NEW,FILE_ATTRIBUTE_NORMAL,NULL));
					break;
				}
				else
					CloseHandle(hf);
				i++;
			}
		}
		if(i<=16)//**** SI dans les limites de la mémoire ****
		{
			if(hf==INVALID_HANDLE_VALUE)
				MessageBox("hf==INVALID_HANDLE_VALUE");
			if(WriteFile(hf,liste.GetBuffer(liste.GetLength()),liste.GetLength(),&len,NULL))
			{
				clibel1[i]=imptitre;
				clibel2[i]=date;
				if(source.Find(".mev",0)!=-1)
					cfrom[i]="MOXITY WEB";
				else
					cfrom[i]="Billetterie N°"+impposte;
				ctot[i]=0;
				cselevt[i]=0;
				CString nart;
				nart.Format("%u",i);
				AfxGetApp()->WriteProfileString(nart,"CLIBELLE1",clibel1[i]);
				AfxGetApp()->WriteProfileString(nart,"CLIBELLE2",clibel2[i]);
				AfxGetApp()->WriteProfileString(nart,"CFROM",cfrom[i]);
				AfxGetApp()->WriteProfileInt(nart,"CTOT",ctot[i]);
				AfxGetApp()->WriteProfileInt(nart,"CONTROLE",cselevt[i]);
				//DrawBoutonImport();
				DrawBoutonArticle(17);
				DeleteFile(source);//*************************************************************************
			}
			else
				MessageBox("Erreur écriture du fichier contrôle");
		}
		CloseHandle(hf);
	}
	else
		MessageBox("Erreur lecture du fichier contrôle");
	CloseHandle(hfr);
	InterlockedExchange(&FREFCONTROL,1);//Flag demandant de rafraichir la liste de controle avec timer 13
	SetTimer(13,1000,NULL);
}
void CConcertoDlg::SearchWEBShop()
{
	CFileFind ff;
	CString temp;
	CString path;
	CTime tim=CTime::GetCurrentTime();
	CString stamp=tim.Format("%Y%m%d%H%M%S");	
	CInternetSession session("stamp");
	session.SetOption(INTERNET_OPTION_RESET_URLCACHE_SESSION,0);
	CStdioFile* ps;
	CString hbuf;
	CString buf;
	HANDLE hf;
	DWORD len;
	CString servername="http://"+serveur+"/sales"; // Chemin de base du serveur de fichiers de vente de la boutique
	CString remotefile=servername+"/controle.php?idborne="+serial+"&act=gmt"; // Chemin relatif de l'URL du fichier controle à télécharger
	try
	{
		ps=session.OpenURL(remotefile);
		if(ps!=NULL)
		{
			UINT nRead;	
			hbuf=buf="";
			while(TRUE)
			{
				nRead=ps->Read(hbuf.GetBuffer(1024),1024);
				if(nRead==0)
					break;
				hbuf.ReleaseBuffer(nRead);
				buf+=hbuf;
				hbuf="";				
			}
			ps->Close();
			delete ps;
			if( buf==serial&&FWEB==0)
			{
				path=controldir+"\\Web.log";
				temp=tim.Format("%d/%m/%Y %H:%M:%S")+" url="+remotefile+" Connexion OK "+"\r\n";
				hf=(CreateFile(path,GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL));
				if(hf!=INVALID_HANDLE_VALUE)
				{
					SetFilePointer(hf,NULL,NULL,FILE_END);
					WriteFile(hf,temp.GetBuffer(temp.GetLength()),temp.GetLength(),&len,NULL);
					CloseHandle(hf);			
				}
			}
			if( buf==serial)
				InterlockedExchange(&FWEB,1);
			else
			{
				InterlockedExchange(&FWEB,0);
			}
		}
	}
	catch (CInternetException* pEx) // traitement des erreurs d'accès internet
	{
		pEx->GetErrorMessage(temp.GetBuffer(10000),10000,0);
		temp.ReleaseBuffer(-1);
		path=controldir+"\\Web.log";
		temp=tim.Format("%d/%m/%Y %H:%M:%S")+" url="+remotefile+" Erreur = "+temp+"\r\n";

		hf=(CreateFile(path,GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL));
		if(hf!=INVALID_HANDLE_VALUE)
		{
			SetFilePointer(hf,NULL,NULL,FILE_END);
			WriteFile(hf,temp.GetBuffer(temp.GetLength()),temp.GetLength(),&len,NULL);
			CloseHandle(hf);			
		}
		InterlockedExchange(&FWEB,0);
	}
	session.Close();
}

int CConcertoDlg::SearchWEBFile()
{
	CFileFind ff;
	CString temp;
	CString num;
	CInternetSession session("session");
	session.SetOption(INTERNET_OPTION_RESET_URLCACHE_SESSION,0);
	CString liste;
	int ret=0;
	int i;
	int idx;
	int idy;
	int idz;
	int ida;
	HANDLE hf;
	DWORD len;
	CTime tim=CTime::GetCurrentTime();
	CStdioFile* ps;
	CString buf;
	CString artbuf;
	CString artlibelle1;
	CString artlibelle2;
	CString artlibelcons;
	double artprix;
	double arttva1;
	double artval1;
	double arttva2;
	double artval2;
	int artperso;
	int artconso;
	int artmode;
	CString horaire="";
	CString path;
	CString hbuf;
	CString refer;
	CString servername="http://"+serveur+"/sales"; // Chemin de base du serveur de fichiers de vente de la boutique
	CString filename;
	CString remotefile=servername+"/controle.php?idborne="+serial+"&act=gmi"; // Chemin relatif de l'URL du fichier controle à télécharger
	CString remoteartfile=servername+"/controle.php?idborne="+serial+"&act=gma"; // Chemin relatif de l'URL du fichier article à télécharger
	CString statusfile="pimpTheFiles/pimpSalesFiles.php?f=";  // Chemin relatif de l'URL du renvoi de status de téléchargement à la boutique?
	try
	{
		ps=session.OpenURL(remotefile);
		if(ps!=NULL)
		{
			UINT nRead;	
			hbuf=buf="";
			while(TRUE)
			{
				nRead=ps->Read(hbuf.GetBuffer(1024),1024);
				if(nRead==0)
					break;
				hbuf.ReleaseBuffer(nRead);
				buf+=hbuf;
				hbuf="";				
			}
			ps->Close();
			buf.Replace("|","\r\n");
			if(buf.GetLength()>0)
			{
				temp=buf.Left(30);
				if(temp.Find("Event=",0)==0)//test si format de fichier approprié( on doit trouver Event= dans les 30 premiers caractères
				{
					idx=6;
					if((idy=buf.Find("\r\n",idx))==-1)// si pas de retour ligne
					{
						temp=servername+"/"+statusfile+filename+" mauvais format des données";
						if(MessageBox("Voulez-vous notifier le mauvais format des données du fichier "+filename,"Fichier non enregitré",MB_YESNO)==IDYES)//affiche le contenu de l'URL
						{
							ps=session.OpenURL(temp);
							if(ps==NULL)
								MessageBox("Status de "+filename+" non mis à jour");
							ps->Close();
						}
						session.Close();
						return 0;
					}
					filename=temp.Mid(idx,idy-idx);
					buf=buf.Mid(idy+2);
					hf=CreateFile(controldir+"\\ExportSHOP-"+filename+".csv",GENERIC_READ|GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
					if(hf!=INVALID_HANDLE_VALUE)
					{
						if(!WriteFile(hf,buf.GetBuffer(buf.GetLength()),buf.GetLength(),&len,NULL))// par précaution
						{	// si on ne peut pas écrire le fichier, on efface le fichier local qui a été ouvert
							CloseHandle(hf);
							DeleteFile(controldir+"\\ExportSHOP-"+filename+".csv");
						}
						else
						{	//sinon on donne l'ordre au serveur qu'il peut effacer le fichier source
							ps->Close();
							CloseHandle(hf);

							//******** LECTURE DU FICHIER ARTICLE ASSOCIE ********
							/*remoteartfile=servername+"/controle.php?idborne=12&act=gma";
							ps=session.OpenURL(remoteartfile);
							if(ps!=NULL)
							{
								nRead;	
								hbuf=artbuf="";
								while(TRUE)
								{
									nRead=ps->Read(hbuf.GetBuffer(1024),1024);
									if(nRead==0)
										break;
									hbuf.ReleaseBuffer(nRead);
									artbuf+=hbuf;
									hbuf="";				
								}
							}
							else
								goto ARTERROR;
							artbuf.Replace("|","\r\n");
							MessageBox(artbuf);
							if(artbuf.Find("*ARTICLE*\r\n",idx)==0)// Reconnaissance d'un fichier article par la balise
							{
								idx=11;
								if(artbuf.Find("horaire=",idx)!=-1)
								{
									idx+=8;//point sur contenu de horaire
									idy=artbuf.Find("\r\n",idx);
									horaire=artbuf.Mid(idx,idy-idx);
									MessageBox(horaire,"HORAIRE");
									idx=idy+2;
								}
								else
									goto ARTERROR;
								while((idz=artbuf.Find("\r\n",idx))!=-1)// Passe en revue les lignes d'article
								{
									if((idy=artbuf.Find(";",idx))!=-1&&idy<=idz)// N° de l'article
									{
										temp=artbuf.Mid(idx,idy-idx);
										ida=atoi(temp);// index de l'article
										idx=idy+2;
									}
									else
										goto ARTERROR;
									if((idy=artbuf.Find(";",idx))!=-1&&idy<=idz)// N° de l'article
									{
										artlibelle1=artbuf.Mid(idx,idy-idx);
										idx=idy+2;
									}
									else
										goto ARTERROR;
									if((idy=artbuf.Find(";",idx))!=-1&&idy<=idz)// N° de l'article
									{
										artlibelle2=artbuf.Mid(idx,idy-idx);
										idx=idy+2;
									}
									else
										goto ARTERROR;
									if((idy=artbuf.Find(";",idx))!=-1&&idy<=idz)// N° de l'article
									{
										artlibelcons=artbuf.Mid(idx,idy-idx);
										idx=idy+2;
									}
									else
										goto ARTERROR;
									if((idy=artbuf.Find(";",idx))!=-1&&idy<=idz)// N° de l'article
									{
										artlibelcons=artbuf.Mid(idx,idy-idx);
										idx=idy+2;
									}
									else
										goto ARTERROR;
									if((idy=artbuf.Find(";",idx))!=-1&&idy<=idz)// N° de l'article
									{
										artprix=atof(artbuf.Mid(idx,idy-idx));
										idx=idy+2;
									}
									else
										goto ARTERROR;
									if((idy=artbuf.Find(";",idx))!=-1&&idy<=idz)// N° de l'article
									{
										arttva1=atof(artbuf.Mid(idx,idy-idx));
										idx=idy+2;
									}
									else
										goto ARTERROR;
									if((idy=artbuf.Find(";",idx))!=-1&&idy<=idz)// N° de l'article
									{
										artval1=atof(artbuf.Mid(idx,idy-idx));
										idx=idy+2;
									}
									else
										goto ARTERROR;
									if((idy=artbuf.Find(";",idx))!=-1&&idy<=idz)// N° de l'article
									{
										arttva2=atof(artbuf.Mid(idx,idy-idx));
										idx=idy+2;
									}
									else
										goto ARTERROR;
									if((idy=artbuf.Find(";",idx))!=-1&&idy<=idz)// N° de l'article
									{
										artval2=atof(artbuf.Mid(idx,idy-idx));
										idx=idy+2;
									}
									else
										goto ARTERROR;
									if((idy=artbuf.Find(";",idx))!=-1&&idy<=idz)// N° de l'article
									{
										artperso=atoi(artbuf.Mid(idx,idy-idx));
										idx=idy+2;
									}
									else
										goto ARTERROR;
									if((idy=artbuf.Find(";",idx))!=-1&&idy<=idz)// N° de l'article
									{
										artconso=atoi(artbuf.Mid(idx,idy-idx));
										idx=idy+2;
									}
									else
										goto ARTERROR;
									if((idy=artbuf.Find("\r\n",idx))!=-1&&idy<=idz)// N° de l'article
									{
										artmode=atoi(artbuf.Mid(idx,idy-idx));
										idx=idy+2;
									}
									else
										goto ARTERROR;
									libel1[ida]=artlibelle1;
									libel2[ida]=artlibelle2;
									libelcons[ida]=artlibelcons;
									prix[ida]=artprix;
									tva1[ida]=arttva1;
									val1[ida]=artval1;
									tva2[ida]=arttva2;
									val2[ida]=artval2;
									perso[ida]=artperso;
									conso[ida]=artconso;
									entrymode[ida]=artmode;
									libelspect[ida]="";
								}
							}
							else
							{
ARTERROR:;						
								MessageBox("Erreur de format WEB");
								session.Close();
								return 0;
							}*/
							i=ImportFichierAtrium(controldir+"\\ExportSHOP-"+filename+".csv");
							if(horaire!="")
							{
								choraire[i]=2;
								idz=horaire.Find(" ",0);
								cdate[i]=horaire.Mid(0,idz);
								cheure[i]=horaire.Mid(idz+1);
							}
							else
							{
								choraire[i]=0;
								idz=horaire.Find(" ",0);
								cdate[i]="";
								cheure[i]="";
							}
							cselevt[i]=1;
							num.Format("%u",i);
							AfxGetApp()->WriteProfileString(num,"CDATE",cdate[i]);
							AfxGetApp()->WriteProfileString(num,"CHEURE",cheure[i]);			
							AfxGetApp()->WriteProfileInt(num,"CONTROLE",cselevt[i]);
							AfxGetApp()->WriteProfileInt(num,"CHORAIRE",choraire[i]);
							if(CONTROL==0)
								InterlockedExchange(&CONTROL,1);
							tcontrol.SetWindowTextA("HRCONTROL"); // On remplace l'antenne par le QR
							PostMessage(WM_USER+9,0,0);
							((CButton*)GetDlgItem(IDC_11))->SetWindowText("");
							RefreshControle();
							if(wsel==4)
							{
								InterlockedExchange(&FREFCONTROL,1);//Flag demandant de rafraichir la liste de controle avec timer 13
								SetTimer(13,1000,NULL);
							}
							ret=1;
							/*if(MessageBox("Voulez-vous notifier la réception du fichier "+filename,"Fichier enregitré",MB_YESNO)==IDYES)//affiche le contenu de l'URL
							{
								ps=session.OpenURL(temp);
								temp=servername+"/"+statusfile+filename;
								if(ps==NULL)
									MessageBox("Status de "+filename+" non mis à jour");
								ps->Close();
							}*/
						}
					}
				}
				else
					SetTimer(17,30000,NULL);
			}
		}
	}
	catch (CInternetException* pEx) // traitement des erreurs d'accès internet
	{
		pEx->GetErrorMessage(temp.GetBuffer(10000),10000,0);
		temp.ReleaseBuffer(-1);
		path=controldir+"\\Web.log";
		temp=tim.Format("%d/%m/%Y %H:%M:%S")+" url="+remotefile+" Erreur = "+temp+"\r\n";
		hf=(CreateFile(path,GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL));
		if(hf!=INVALID_HANDLE_VALUE)
		{
			SetFilePointer(hf,NULL,NULL,FILE_END);
			WriteFile(hf,temp.GetBuffer(temp.GetLength()),temp.GetLength(),&len,NULL);
			CloseHandle(hf);			
		}
	}
	session.Close();
	return ret;
}

void CConcertoDlg::ImportTicketExterne()
{
	BOOL result;
	CFileFind ff;
	int i;
	CString temp;
	if(serveur!="")
	{
		pimp.SetRange(0,10);
		pimp.SetStep(1);
		pimp.SetPos(0);
		pimp.SetWindowPos(&wndTop,wlargeur/20,(int)((double)whauteur*25.5/27),wlargeur/4,(int)((double)whauteur*0.6/27),SWP_HIDEWINDOW);
		pimp.ShowWindow(1);
		SetTimer(15,200,NULL);
			SearchWEBFile();// Cherche un fichier de controle sur le serveur WEB
		pimp.ShowWindow(0);
		KillTimer(15);
	}
	outpath=netcontdir+"\\*.*";//"X:\\*.*";
	i=0;
	result=ff.FindFile(outpath,0);
	while(result)
	{
		result=ff.FindNextFile();
		if (ff.IsDots())
		 continue;
		if (ff.IsDirectory())
		 continue;
		if(ff.GetFileName().Find(".weez",0)!=-1||ff.GetFileName().Find(".mev",0)!=-1||ff.GetFileName().Find(".FIL",0)!=-1||ff.GetFileName().Find("Ticket",0)!=-1||ff.GetFileName().Find(".csv",0)!=-1)
		{
			if(ff.GetFileName().Find(".mev",0)!=-1||ff.GetFileName().Find(".dat",0)!=-1)
			{
				ImportFichierExterne(ff.GetFilePath());
				RefreshControle();
			}
			if(ff.GetFileName().Find(".weez",0)!=-1)
			{
				ImportFichierWeez(ff.GetFilePath());
				RefreshControle();
			}
			if(ff.GetFileName().Find(".FIL",0)!=-1)
			{
				ImportFichierFil(ff.GetFilePath());
				RefreshControle();
			}
			if(ff.GetFileName().Find(".csv",0)!=-1&&ff.GetFileName().Find("DIGITICK",0)!=-1)
			{
				int j=ImportFichierDigitick(ff.GetFilePath());
				RefreshControle();
			}
			if(ff.GetFileName().Find(".csv",0)!=-1&&ff.GetFileName().Find("Export",0)!=-1)
			{
				int j=ImportFichierAtrium(ff.GetFilePath());
				RefreshControle();
			}
			i++;
		}
	}
	ff.Close();
}

void CConcertoDlg::ImportFichierFil(CString source)
{
	CString dir;
	HANDLE hfr;
	HANDLE hf;
	CString buf;
	CString temp;
	CString ticket;;
	CString liste;
	CString nart;
	CString impposte;
	CString implibel1;
	CString implibel2;
	CString imptitre;
	CString date;
	CString jour;
	CString mois;
	CString an;
	int i;
	int idxstart=0;
	int idxstop=0;
	int idxmem=0;
	int idxmoisstart=0;
	int idxmoisstop=0;
	DWORD len;
	DWORD nbt;
	hfr=CreateFile(source,GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if(ReadFile(hfr,buf.GetBuffer(GetFileSize(hfr,NULL)),GetFileSize(hfr,NULL),&len,NULL))
	{
		buf.ReleaseBuffer(len);
		CloseHandle(hfr);
		if((idxstart=buf.Find("\r\n",0))!=-1)
		{
			idxstop=idxstart-10;
			date=buf.Mid(idxstop,10);
			if((idxstart=buf.Find("Prévente",0))!=-1)
			{
				idxstart+=8;
				imptitre=buf.Mid(idxstart,idxstop-idxstart);
			}
		}
		idxstart=0;
		nbt=0;
		while(TRUE)
		{
			if((idxstop=buf.Find("\r\n",idxstart))!=-1)
			{
				ticket=buf.Mid(idxstart,13);
				liste+=ticket+" \r\n";
				idxstart=idxstop+2;
				nbt++;
			}
			else break;
		}
		i=1; // **** RECHERCHE DE FICHIERS DU MEME ARTICLE ****
		while(i<=16)
		{
			if(clibel1[i]==imptitre&&clibel2[i]==date)//&&cfrom[i]=="Billetterie N°"+impposte)
			{
				temp.Format("0%u",i);
				dir=controldir+"\\"+temp.Right(2);
				CreateDirectory(dir,NULL);
				hf=(CreateFile(dir+"\\Controle.dat",GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL));
				CloseHandle(hf);
				DeleteFile(dir+"\\Controle.dat");
				RemoveDirectory(dir);
				break;
			}
			i++;
		}
		i=1;// **** OU CREATION D'UN NOUVEAU FICHIER ****
		while(i<=16)
		{
			temp.Format("0%u",i);
			dir=controldir+"\\"+temp.Right(2);
			CreateDirectory(dir,NULL);
			hf=(CreateFile(dir+"\\Controle.dat",GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL));
			if(hf==INVALID_HANDLE_VALUE)
			{
				hf=(CreateFile(dir+"\\Controle.dat",GENERIC_READ|GENERIC_WRITE,0,NULL,CREATE_NEW,FILE_ATTRIBUTE_NORMAL,NULL));
				break;
			}
			else
				CloseHandle(hf);
			i++;
		}
		if(i<=16)//**** SI dans les limites de la mémoire ****
		{
			if(WriteFile(hf,liste.GetBuffer(liste.GetLength()),liste.GetLength(),&len,NULL))
			{
				clibel1[i]=imptitre;
				clibel2[i]=date;
				cfrom[i]="PLACEMINUTE";
				ctot[i]=nbt;
				cselevt[i]=0;
				CString nart;
				nart.Format("%u",i);
				AfxGetApp()->WriteProfileString(nart,"CLIBELLE1",clibel1[i]);
				AfxGetApp()->WriteProfileString(nart,"CLIBELLE2",clibel2[i]);
				AfxGetApp()->WriteProfileString(nart,"CFROM",cfrom[i]);
				AfxGetApp()->WriteProfileInt(nart,"CTOT",ctot[i]);
				AfxGetApp()->WriteProfileInt(nart,"CONTROLE",cselevt[i]);
				//DrawBoutonImport();
				DrawBoutonArticle(17);
				DeleteFile(source);//*************************************************************************
			}
			else
				MessageBox("Erreur écriture du fichier contrôle");
		}
		CloseHandle(hf);
	}
	else
		MessageBox("Erreur lecture du fichier contrôle Fill");
	CloseHandle(hfr);
}

void CConcertoDlg::ImportFichierWeez(CString source)
{
	CString nm[12][2];
	nm[0][0]="Janvier";
	nm[0][1]="01";
	nm[1][0]="Février";
	nm[1][1]="02";
	nm[2][0]="Mars";
	nm[2][1]="03";
	nm[3][0]="Avril";
	nm[3][1]="04";
	nm[4][0]="Mai";
	nm[4][1]="05";
	nm[5][0]="Juin";
	nm[5][1]="06";
	nm[6][0]="Juillet";
	nm[6][1]="07";
	nm[7][0]="Août";
	nm[7][1]="08";
	nm[8][0]="Septembre";
	nm[8][1]="09";
	nm[9][0]="Octobre";
	nm[9][1]="10";
	nm[10][0]="Novembre";
	nm[10][1]="11";
	nm[11][0]="Décembre";
	nm[11][1]="12";
	CString dir;
	HANDLE hfr;
	HANDLE hf;
	CString buf;
	CString temp;
	CString ticket;;
	CString liste;
	CString nart;
	CString impposte;
	CString implibel1;
	CString implibel2;
	CString imptitre;
	CString date;
	CString jour;
	CString mois;
	CString an;
	int i;
	int idxstart=0;
	int idxstop=0;
	int idxmem=0;
	int idxmoisstart=0;
	int idxmoisstop=0;
	DWORD len;
	DWORD nbt;
	hfr=CreateFile(source,GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if(ReadFile(hfr,buf.GetBuffer(GetFileSize(hfr,NULL)),GetFileSize(hfr,NULL),&len,NULL))
	{
		buf.ReleaseBuffer(len);
		CloseHandle(hfr);
		//MessageBox(source);
		if((idxstart=buf.Find("`",idxstart))!=-1)
		{
			nbt=atoi(buf.Left(idxstart));
			idxstart+=2;
			if((idxstop=buf.Find("`",idxstart))!=-1)//(idxstop=buf.Find("@",idxstart))!=-1||
			{
				
				imptitre=buf.Mid(idxstart,idxstop-idxstart);
				idxstart=idxstop+2;
				if((idxstop=buf.Find("`",idxstart))!=-1)
				{
					temp=buf.Mid(idxstart,idxstop-idxstart);
					idxstart=temp.Find(" ",0);
					date=temp.Mid(idxstart+1);
					for(i=0;i<12;i++)
					{
						if(date.Find(nm[i][0],0)!=-1)
						{
							date.Replace(nm[i][0],nm[i][1]);
							date.Replace(" ","-");
							break;
						}
					}
				}
				idxstop=buf.Find("`",idxstop++);
				idxstart=idxstop+2;
				idxstop=buf.Find("`",idxstart);
			}
		}			
		while(TRUE)
		{
			idxstart=idxstop+2;
			if((idxstop=buf.Find(";",idxstart))!=-1)
			{
				ticket=buf.Mid(idxstart,idxstop-idxstart);
				liste+=ticket+" \r\n";
				idxstop=buf.Find("`",idxstop);
			}
			else break;
		}
		i=1; // **** RECHERCHE DE FICHIERS DU MEME ARTICLE ****
		while(i<=16)
		{
			if(clibel1[i]==imptitre&&clibel2[i]==date)//&&cfrom[i]=="Billetterie N°"+impposte)
			{
				temp.Format("0%u",i);
				dir=controldir+"\\"+temp.Right(2);
				CreateDirectory(dir,NULL);
				hf=(CreateFile(dir+"\\Controle.dat",GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL));
				CloseHandle(hf);
				DeleteFile(dir+"\\Controle.dat");
				RemoveDirectory(dir);
				break;
			}
			i++;
		}
		i=1;// **** OU CREATION D'UN NOUVEAU FICHIER ****
		while(i<=16)
		{
			temp.Format("0%u",i);
			dir=controldir+"\\"+temp.Right(2);
			CreateDirectory(dir,NULL);
			hf=(CreateFile(dir+"\\Controle.dat",GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL));
			if(hf==INVALID_HANDLE_VALUE)
			{
				hf=(CreateFile(dir+"\\Controle.dat",GENERIC_READ|GENERIC_WRITE,0,NULL,CREATE_NEW,FILE_ATTRIBUTE_NORMAL,NULL));
				break;
			}
			else
				CloseHandle(hf);
			i++;
		}
		if(i<=16)//**** SI dans les limites de la mémoire ****
		{
			if(WriteFile(hf,liste.GetBuffer(liste.GetLength()),liste.GetLength(),&len,NULL))
			{
				clibel1[i]=imptitre;
				clibel2[i]=date;
				cfrom[i]="WeezEvent";
				ctot[i]=nbt;
				cselevt[i]=0;
				CString nart;
				nart.Format("%u",i);
				AfxGetApp()->WriteProfileString(nart,"CLIBELLE1",clibel1[i]);
				AfxGetApp()->WriteProfileString(nart,"CLIBELLE2",clibel2[i]);
				AfxGetApp()->WriteProfileString(nart,"CFROM",cfrom[i]);
				AfxGetApp()->WriteProfileInt(nart,"CTOT",ctot[i]);
				AfxGetApp()->WriteProfileInt(nart,"CONTROLE",cselevt[i]);
				//DrawBoutonImport();
				DrawBoutonArticle(17);
				DeleteFile(source);//*************************************************************************
			}
			else
				MessageBox("Erreur écriture du fichier contrôle");
		}
		CloseHandle(hf);
	}
	else
		MessageBox("Erreur lecture du fichier contrôle WeezEvent");
	CloseHandle(hfr);
}



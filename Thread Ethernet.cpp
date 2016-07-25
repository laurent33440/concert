#include "stdafx.h"
#include "Concerto.h"
#include "ConcertoDlg.h"
#include "shlobj.h"
#pragma comment (lib, "setupapi.lib")

// Maj articles sur esclave concert : arret controle, demande fichier fiscal, maj images bornes
DWORD WINAPI ArticleScanThread(LPVOID lpParameter)
{
	CConcertoDlg* PCF=  (CConcertoDlg*)lpParameter;
	CString temp;
	CString temp1;
	CString txt;
	CString buf;
	CString tmois;
	CString txtstdate;
	CString txtendate;
	CString tan;
	CString txtrub;
	CString txtpar;
	CString txtval;
	int tempo=0;
	CString	filebuf="";
	PCF->STOPRS=FALSE;
	int j=0;
	int k=0;
	int i=0;
	int idx=0;
	int idy=0;
	int idz=0;
	CFileStatus sfil;
	HANDLE hf;
	DWORD len;
	CFileFind ff;
	while(TRUE)
	{
		if(CFile::GetStatus(PCF->controldir+"\\raz.dat",sfil))// RAZ des controles et arret si en cours (fichier issu de concert office)
		{
			PCF->hist=0;
			if(PCF->CONTROL)
			{
				PCF->ValideControl();// si en controle on arrete
			}
			if(PCF->dopen!="")
			{
				PCF->flagraz=1;
				PCF->FillTicketList(PCF->opendir);
				PCF->OnBnClickedCashClose();
				PCF->flagraz=0;
			}
			DeleteFile(PCF->controldir+"\\raz.dat");
		}
		if(CFile::GetStatus(PCF->controldir+"\\fiscal.dat",sfil))
		{// Teste si présence fichier de demande de fichier fiscal
			if((hf=CreateFile(PCF->controldir+"\\fiscal.dat",GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL))!=INVALID_HANDLE_VALUE)
			{
				ReadFile(hf,buf.GetBuffer(GetFileSize(hf,NULL)),GetFileSize(hf,NULL),&len,NULL);
				CloseHandle(hf);
				buf.ReleaseBuffer(len);
				idx=0;
				if((idx=buf.Find("start=",0))==0)
				{
					idx=6;
					if((idy=buf.Find("\r\n",idx))!=1)
					{
						txtstdate=buf.Mid(idx,idy-idx);
						if((idx=buf.Find("stop=",idy))!=-1)
						{
							idx+=5;
							if((idy=buf.Find("\r\n",idx))!=1)
							{
								txtendate=buf.Mid(idx,idy-idx);
								DeleteFile(PCF->controldir+"\\fiscal.dat");
								PCF->ExportArchData(txtstdate,txtendate);
							}
						}
					}
				}
			}
		}

		if(CFile::GetStatus(PCF->controldir+"\\updater.dat",sfil))
		{// Teste si présence nouveau fichier de configuration image pour la borne
			if((hf=CreateFile(PCF->controldir+"\\updater.dat",GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL))!=INVALID_HANDLE_VALUE)
			{
				ReadFile(hf,buf.GetBuffer(GetFileSize(hf,NULL)),GetFileSize(hf,NULL),&len,NULL);
				CloseHandle(hf);
				buf.ReleaseBuffer(len);
				DeleteFile(PCF->controldir+"\\updater.dat");
				idx=0;
				if((idx=buf.Find("Updater file",0))==0)
				{
					txtrub="";
					idx=buf.Find("\r\n",idx)+2;
					while(idx<(int)len)
					{
						idy=buf.Find("=",idx);
						idz=buf.Find("[",idx);
						if(idz!=-1&&(idz<idy))	
						{
							idx=idz+1;
							if((idy=buf.Find("]",idx))!=-1)						
							{
								txtrub=buf.Mid(idx,idy-idx);
								idx=buf.Find("\r\n",idy);
								if(idx!=-1)
									idx+=2;
								else
									break;
							}
						}
						else
						{
							idy=buf.Find("=",idx);
							idz=buf.Find("[",idx);
							if(idy!=-1&&(idy<idz||idz==-1))
							{
								txtpar=buf.Mid(idx,idy-idx);
								idx=idy+1;
								idy=buf.Find("\r\n",idx);
								if(idy!=-1)
								{
									txtval=buf.Mid(idx,idy-idx);
									idx=idy+2;
									PCF->WriteConfigString(txtrub,txtpar,txtval);
									idx=idy+2;
								}
								else
									break;
							}
							else
								if(idz==-1&&idy==-1)
									break;
						}
					}
				}
			}
		}

		temp=PCF->controldir+"\\Article.dat";
		if(CFile::GetStatus(temp,sfil))// Si le fichier existe - DEUXIEME PASSAGE le fichier exite : maj 
		{
			if(	PCF->artro==0)// Si pas encore de vente en mémoire
			{
				PCF->ImportArticle(PCF->controldir+"\\");	// Importation des articles de ce fichier
				DeleteFile(temp);							// Effacement du fichier
				if(PCF->wsel==1||PCF->wsel==3)
				{
					for(i=0;i<PCF->lna.GetCount();i++)
					{
						PCF->lna.GetText(i,temp);
						if(temp=="article")
						{
							j=(int)PCF->lna.GetItemData(i);// N° article ayant été modifié

							k=j-(PCF->artrange*PCF->NAPP);
							if(k>0&&k<=PCF->NAPP)
							{
								PCF->DrawBoutonArticle(k-1);
								if(PCF->wsel==3)
								{
									PCF->FillStat(j);// recharge les statics du bouton sélectionné par artnum
								}
							}
						}
						if(temp=="page"&&PCF->lna.GetItemData(i)==PCF->artrange)
							PCF->UpdatePageEntree();
					}
					if(PCF->memnom!=PCF->nom&&PCF->wsel==1)
					{
						PCF->memnom==PCF->nom;
						PCF->RedrawWindow(0,0,1|256|4);
					}
					if(PCF->memafmode!=PCF->afmode)
					{
						PCF->memafmode=PCF->afmode;
						if( PCF->wsel==1)
							PCF->DrawWindowConcert();
					}
				}
				if(PCF->wsel==5)
					PCF->DrawStaticConfig();
			}
		}
		else // PREMIER passage : récupération du fichier pour cette machine
		{
			temp=PCF->netcontdir+"\\Article"+PCF->poste+".dat";
			if(CFile::GetStatus(temp,sfil))	//Si fichier article présent pour cette machine
			{
				CopyFile(PCF->netcontdir+"\\Article"+PCF->poste+".dat",PCF->controldir+"\\Article.dat",FALSE);	// S'approprie le fichier dans Article.dat
				DeleteFile(PCF->netcontdir+"\\Article"+PCF->poste+".dat");										// Efface le fichier source du maitre
			}
		}
		if(!PCF->master)//si esclave
		{
			temp=PCF->controldir+"\\Article.dat";	// Si fichier article.dat présent

			if(CFile::GetStatus(temp,sfil))	//on place un flag fart à 1 pour indiquer la présence d'un fichier article
				PCF->fart=1; 
			else
			{
				PCF->fart=0;				// à 0
				PCF->fartaf=0;				// On repositionne le flag de clignotement à 0
			}
		}
		Sleep(1000);
	}
	_endthreadex( 0 );
	return 0;
}

DWORD WINAPI  ScanNetThread(LPVOID lpParameter)// Recherche d'un maitre
{
	CConcertoDlg* PCF=  (CConcertoDlg*)lpParameter;
	CString dir;
	CString temp;
	CString temp1;
	CString poste;
	int i;
	int fstat=0;
	CFileStatus sfil;
	CFileFind cfd;
	while(TRUE)
	{
		fstat=0;
		for(i=0;i<PCF->lmac.GetCount()&&PCF->master==0;i++)//passe en revue les machines détectées
		{
			if(PCF->lmac.GetItemData(i)==1)// Test si c'est un maitre dans la liste
			{
				PCF->lmac.GetText(i,dir);
				int j=dir.ReverseFind('\\');
				dir=dir.Left(j);
				fstat=1;
				if(PCF->wsel==1&&PCF->FTEM==1)//&&PCF->fart==0)//&&PCF->ftnet==0)//&&CFile::GetStatus(cfd.GetFilePath(),sfil)
				{
					if(!PCF->tnet.IsWindowVisible())// allume le témoin dans l'onglet des ventes s'il nétait pas visible
						PCF->tnet.ShowWindow(1);
				}	
				PCF->netcontdir=dir;// Mémorise le répertoire du maitre pour les actions futures
				break;
			}
			Sleep(100);
		}
		if(PCF->master)
		{
			PCF->netcontdir=PCF->controldir;
			if(PCF->wsel==1&&PCF->FTEM==1)//&&PCF->ftnet==0)
			{
				if(!PCF->tnet.IsWindowVisible())
					PCF->tnet.ShowWindow(1);
			}
		} 
		if(PCF->FTEM==0||PCF->FWEB==0||PCF->wsel>1||PCF->serveur=="")
			PCF->tweb.ShowWindow(0);
		if(PCF->FTEM==1&&PCF->FWEB&&PCF->serveur!="")
			if(!PCF->tweb.IsWindowVisible())
				PCF->tweb.ShowWindow(1);
		if((!PCF->master&&fstat==0)||PCF->wsel>1)// pas trouvé de maitre ou écran>1 éteint le logo
		{
			if(PCF->tnet.IsWindowVisible())
				PCF->tnet.ShowWindow(0);
		}
		if(!PCF->master&&fstat==0)
			Sleep(1000);// 1 s esclave
		else
			Sleep(5000); // 5 s maitre
	}
	_endthreadex( 0 );
	return 0;
}

//Pour le maitre:
//rempli la liste des fichiers de controle. Demande le rafraichissement de la liste de controle si chgt ds fichier Control.dat 
DWORD WINAPI  ControlFileThread(LPVOID lpParameter)
{
	CConcertoDlg* PCF=  (CConcertoDlg*)lpParameter;
	CString temp;
	CString ordi;
	int i;// n° controle
	int j;
	int idx;// n° touche ds fichier de controle
	CString targetdir;
	CString buf;
	CString path;
	CString ftest;
	CString ftxt;
	HANDLE hf;
	DWORD nbw;
	CFileStatus sfcol[17];
	CFileStatus sfil;
	CFileFind cff;
	BOOL stat;
	CString	pathcontrol;
	for(j=0;j<=16;j++)
	{
		sfcol[j].m_size=555555; // met la taille arbitrairement à 555555 pour les status non encore initialisé par des fichiers absents
	}

	while(TRUE) //ne concerne que les maitres et/ou autonomes
	{
		PCF->ltctl.ResetContent();
		if((PCF->master&&PCF->alone==0))
			pathcontrol="tempcontrol";
		else
			if(PCF->master&&PCF->alone==1)
				pathcontrol="alone"+PCF->poste+"control";
		stat=cff.FindFile(PCF->controldir+"\\*.*",0);//il y a des fichier dans controle dir
		while(stat&&PCF->master)//rempli la liste des fichiers de controle
		{
			stat=cff.FindNextFileA();
			if(cff.IsDots()||cff.IsDirectory())
				continue;
			if(cff.GetFileName().Find(pathcontrol,0)!=-1)
			{
				PCF->ltctl.AddString(cff.GetFilePath());
			}
		}
		cff.Close();
		if(PCF->ltctl.GetCount()>0&&PCF->master)//traite les fichiers de la liste
		{
			for(j=0;j<PCF->ltctl.GetCount();j++)
			{
				PCF->ltctl.GetText(j,temp);
				hf=(CreateFile(temp,GENERIC_READ,0,NULL,OPEN_EXISTING,GENERIC_READ |FILE_FLAG_DELETE_ON_CLOSE|FILE_ATTRIBUTE_NORMAL,NULL));
				if(hf!=INVALID_HANDLE_VALUE)
				{
					ReadFile(hf,buf.GetBuffer(GetFileSize(hf,NULL)),GetFileSize(hf,NULL),&nbw,NULL);
					buf.ReleaseBuffer(nbw);
					CloseHandle(hf);
					temp=buf.Mid(1,2);// Récupère le N° de la touche
					idx=atoi(temp);
					if((i=PCF->target[idx])==0)//si aucune correspondance
					{
						i=1;
						while(i<=16)
						{
							if(PCF->clibel1[i]==""&&PCF->clibel2[i]=="")
							{
								PCF->target[idx]=i;//associe
								temp.Format("%u",idx);
								AfxGetApp()->WriteProfileInt(temp,"TARGET",i);//sauve le n° article
								break;
							}
							i++;
						}
					}
					if(i>16)	// plus de place pour un controle en mémoire*************************** a gérer un jour ******************************
						i=0;
					//PCF->RefreshControle();
					temp.Format("0%u",i);
					targetdir=PCF->controldir+"\\"+temp.Right(2);
					CreateDirectory(targetdir,NULL);// Création éventuelle du répertoire de controle
					CreateDirectory(PCF->backupdir+"\\Control\\"+temp.Right(2),NULL);// Création éventuelle du répertoire de controle
retry:;				//ouverture et création eventuelle du repertoire de controle
					hf=(CreateFile(targetdir+"\\Controle.dat",GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL));
					if(hf==INVALID_HANDLE_VALUE)
					{
						hf=(CreateFile(targetdir+"\\Controle.dat",GENERIC_READ | GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL));
						if(hf!=INVALID_HANDLE_VALUE)
						{
							PCF->cselevt[i]=0;// Déselectionne le controle de la liste pour un nouvel élément
							PCF->ctot[i]=0;
						}
						else
						{
							Sleep(100);
							goto retry;
						}

					}
					else
						PCF->ctot[i]++;
					SetFilePointer(hf,NULL,NULL,FILE_END);
					WriteFile(hf,buf.GetBuffer(),buf.GetLength(),&nbw,NULL);
					CloseHandle(hf);
					if(PCF->securedir!="")//backup Control.dat
					{
							temp=PCF->securedir+"\\Control\\"+temp.Right(2);
							CreateDirectory(temp,NULL);
							if(CopyFile(targetdir+"\\Controle.dat",temp+"\\Controle.dat",FALSE)==0)
								PCF->MessageBox("Erreur de sauvegarde D");
					}

					PCF->clibel1[i]=PCF->libel1[idx]+PCF->libel2[idx];
					PCF->clibel2[i]=PCF->libelspect[idx];
					PCF->choraire[i]=PCF->entrymode[idx];
					PCF->cfrom[i]="INTERNE";
					temp.Format("%u",i);
					AfxGetApp()->WriteProfileString(temp,"CLIBELLE1",PCF->clibel1[i]);
					AfxGetApp()->WriteProfileString(temp,"CLIBELLE2",PCF->clibel2[i]);
					AfxGetApp()->WriteProfileString(temp,"CFROM",PCF->cfrom[i]);
					AfxGetApp()->WriteProfileInt(temp,"CTOT",PCF->ctot[i]);
					AfxGetApp()->WriteProfileInt(temp,"CONTROLE",PCF->cselevt[i]);
					AfxGetApp()->WriteProfileInt(temp,"CHORAIRE",PCF->choraire[i]);
					PCF->RefreshControle();
					InterlockedExchange(&PCF->FREFCONTROL,1);//Flag demandant de rafraichir la liste de controle avec timer 13
					PCF->SetTimer(13,1000,NULL);
				}
			}
		}
		if(PCF->fprev&&PCF->master)// si on est en prévente
		{
			for(i=1;i<=16&&(PCF->PRMODE!=5&&PCF->PRMODE!=6);i++)// Passe en revue tous les fichiers controle
			{
				temp.Format("0%u",i);
				temp=temp.Right(2);
				if(CFile::GetStatus(PCF->controldir+"\\"+temp+"\\Controle.dat",sfil))// si le fichier existe
				{
					if(sfcol[i].m_size!=sfil.m_size&&(PCF->PRMODE!=5&&PCF->PRMODE!=6))// Si le fichier controle du maitre a changé
					{
						sfcol[i].m_size=sfil.m_size;//remet en mémoire les dernires paramètres du fichier
						InterlockedExchange(&PCF->FREFCONTROL,1);//Flag demandant de rafraichir la liste de controle avec timer 13
						PCF->SetTimer(13,1000,NULL);
					}
				}
				else
				{// si le fichier n'existe pas
					if(sfcol[i].m_size>0&&(PCF->PRMODE!=5&&PCF->PRMODE!=6))
					{
						sfcol[i].m_size=0;// Remet la taille à 0
						InterlockedExchange(&PCF->FREFCONTROL,1);//Flag demandant de rafraichir la liste de controle avec timer 13
						PCF->SetTimer(13,1000,NULL);
					}
				}
				Sleep(100);
			}
		}
		Sleep(500);
	}
}

//traite le fichier Controle.cfg ainsi que ses evolutions
DWORD WINAPI  BackupControlFileThread(LPVOID lpParameter)
{
	CConcertoDlg* PCF=  (CConcertoDlg*)lpParameter;
	CString temp;
	CString ordi;
	int i;
	int idx;
	int idy;
	int frb; //flag redessine bouton
	int j;
	CString buf;
	CString nart;
	CString dir;
	HANDLE hf;
	DWORD nbw;
	CFileStatus sfil;
	CFileStatus sfcol[16];
	CFileStatus sfol;
	sfil=sfol;
	while(TRUE)
	{
		//esclave et Controle.cfg existe et prevente autorisée
		if(PCF->netcontdir!=PCF->controldir&&!PCF->master&&CFile::GetStatus(PCF->controldir+"\\Controle.cfg",sfil)&&PCF->fprev)
		{
			frb=0;
			if(sfil.m_size!=sfol.m_size||sfil.m_mtime!=sfol.m_mtime)
			{// si changement dans le fichier controle.cfg
				sfol=sfil;
				hf=(CreateFile(PCF->controldir+"\\Controle.cfg",GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL));
				if(hf!=INVALID_HANDLE_VALUE)// ouvre le fichier Controle.cfg
				{//PREVENTE AVEC CONSO;04/03/2015 DJ OK;1;INTERNE;0;;;0;0.00
					ReadFile(hf,buf.GetBuffer(GetFileSize(hf,NULL)),GetFileSize(hf,NULL),&nbw,NULL);
					buf.ReleaseBuffer(nbw);
					CloseHandle(hf);
					//Recharge en mémoire tous les paramètres de controle
					i=1;
					idx=0;
					idy=0;
					while(idx<buf.GetLength())
					{
						nart.Format("%u",i);
						if((idy=buf.Find(";",idx))==-1)
							break;
						temp=buf.Mid(idx,idy-idx);
						if(PCF->cfrom[i].Find("EXPORT")!=-1&&temp=="")
						{
							PCF->shopidx=i;
							InterlockedExchange(&PCF->PRMODE,5);//Imprime le rapport ATRIUM
							Sleep(100);
							while(PCF->PRMODE!=0)
								Sleep(200);/**/
						}
						else
						{
							if(PCF->cfrom[i]=="WEB DIGITICK"&&temp=="")
							{
								PCF->digidx=i;
								InterlockedExchange(&PCF->PRMODE,6);// Imprime le rapport DIGITICK
								Sleep(100);
								while(PCF->PRMODE!=0)
									Sleep(200);
							}
							else
							{
								if(PCF->cfrom[i]==""&&temp.Find("EXPORT",0)!=-1)// ATRIUM ou NOCTIS ou SHOP
								{
									PCF->cas[i]=0;
									AfxGetApp()->WriteProfileInt(nart,"CAS",(int)PCF->cas[i]*100);
									PCF->cscan[i]=0;
									AfxGetApp()->WriteProfileInt(nart,"CSCAN",(int)PCF->cscan[i]);
								}
								else
								{
									if(PCF->cfrom[i]==""&&temp=="WEB DIGITICK")
									{
										PCF->cas[i]=0;
										AfxGetApp()->WriteProfileInt(nart,"CAS",(int)PCF->cas[i]*100);
										PCF->cscan[i]=0;
										AfxGetApp()->WriteProfileInt(nart,"CSCAN",(int)PCF->cscan[i]);
									}
									else
									{
										if(PCF->cfrom[i]!=""&&temp=="")
										{
											temp.Format("%u",i);
											if(temp.GetLength()==1)
												temp="0"+temp;
											dir=PCF->workdir+"\\Control\\"+temp;
											DeleteFile(dir+"\\Controle.dat");
										}
									}										
								}
							}
						}
						if(temp!=PCF->cfrom[i])
							frb=1;
						PCF->cfrom[i]=temp;
						AfxGetApp()->WriteProfileString(nart,"CFROM",PCF->cfrom[i]);
						idx=idy+1;
						if((idy=buf.Find(";",idx))==-1)
							break;
						temp=PCF->clibel1[i];
						PCF->clibel1[i]=buf.Mid(idx,idy-idx);
						AfxGetApp()->WriteProfileString(nart,"CLIBELLE1",PCF->clibel1[i]);
						if(temp!=PCF->clibel1[i])
							frb=1;
						idx=idy+1;
						if((idy=buf.Find(";",idx))==-1)
							break;
						temp=PCF->clibel2[i];
						PCF->clibel2[i]=buf.Mid(idx,idy-idx);
						AfxGetApp()->WriteProfileString(nart,"CLIBELLE2",PCF->clibel2[i]);
						if(temp!=PCF->clibel2[i])
							frb=1;
						idx=idy+1;
						if((idy=buf.Find(";",idx))==-1)
							break;
						PCF->choraire[i]=atoi(buf.Mid(idx,idy-idx));
						AfxGetApp()->WriteProfileInt(nart,"CHORAIRE",PCF->choraire[i]);
						idx=idy+1;
						if((idy=buf.Find(";",idx))==-1)
							break;
						PCF->ctot[i]=atoi(buf.Mid(idx,idy-idx));
						AfxGetApp()->WriteProfileInt(nart,"CTOT",PCF->ctot[i]);
						idx=idy+1;
						if((idy=buf.Find(";",idx))==-1)
							break;
						PCF->cdate[i]=buf.Mid(idx,idy-idx);
						AfxGetApp()->WriteProfileString(nart,"CDATE",PCF->cdate[i]);
						idx=idy+1;
						if((idy=buf.Find(";",idx))==-1)
							break;
						PCF->cheure[i]=buf.Mid(idx,idy-idx);
						AfxGetApp()->WriteProfileString(nart,"CHEURE",PCF->cheure[i]);
						idx=idy+1;
						if((idy=buf.Find(";",idx))==-1)
							break;
						j=PCF->cselevt[i];
						PCF->cselevt[i]=atoi(buf.Mid(idx,idy-idx));
						AfxGetApp()->WriteProfileInt(nart,"CONTROLE",PCF->cselevt[i]);
						if(j!=PCF->cselevt[i])
							frb=1;
						idx=idy+1;
						if((idy=buf.Find(";",idx))==-1)
							break;
						idx=idy+1;
						if((idy=buf.Find("\r\n",idx))==-1)
							break;
						j=atoi(buf.Mid(idx,idy-idx));
						PCF->target[j]=i;
						temp.Format("%u",j);
						AfxGetApp()->WriteProfileInt(temp,"TARGET",PCF->target[j]);
						i++;
						idx=idy+2;
					}
					if(PCF->fprev)// si on est en prévente
					{
						for(i=1;i<=16;i++)// Passe en revue tous les fichiers controle
						{
							temp.Format("0%u",i);
							temp=temp.Right(2);
							// si esclave et Control.dat de ce poste sur le maitre
							if(PCF->netcontdir!=PCF->controldir&&CFile::GetStatus(PCF->netcontdir+"\\"+temp+"\\Controle.dat",sfil))
							{
								CreateDirectory(PCF->controldir+"\\"+temp,NULL);
								if(sfcol[i].m_size!=sfil.m_size)// Si le fichier controle du maitre a changé
								{//Recopie le fichier controle du maitre dans l'esclave
									//Sleep(3000);// Délai d'attente cache réseau sinon nouveau fichier non pris en compte
									CopyFile(PCF->netcontdir+"\\"+temp+"\\Controle.dat",PCF->controldir+"\\"+temp+"\\Controle.dat",FALSE);
									sfcol[i]=sfil;//remet en mémoire les dernires paramètres du fichier
								}
								if(PCF->cfrom[i].Find("SHOP",0)!=-1&&PCF->cselevt[i]==1&&PCF->CONTROL==0)
								{
									InterlockedExchange(&PCF->CONTROL,1);
									if(PCF->wsel==4)
									{
										PCF->GetDlgItem(IDC_11)->SetWindowText(""); // Redessine le bouton avec le bon texte
										PCF->GetDlgItem(IDC_11)->RedrawWindow(0,0,1|256|4); // Redessine le bouton avec le bon texte
										//PCF->RefreshControlList();
									}									
									else
									{
										if(PCF->wsel==1)
										{
											PCF->tcontrol.GetWindowTextA(temp);
											if(temp!="HRCONTROL")
												PCF->tcontrol.SetWindowTextA("HRCONTROL");
											PCF->PostMessage(WM_USER+9,0,0);//RedrawWindow(0,0,1|256|4);
										}
									}
								}
							}
							else
							{
								sfcol[i].m_size=0;
							}
							Sleep(500);
						}
					}
				}
				if(PCF->wsel==4||PCF->wsel==1)
				{
					InterlockedExchange(&PCF->FREFCONTROL,1);//Flag demandant de rafraichir la liste de controle avec timer 13
					PCF->SetTimer(13,1000,NULL);
				}
				if(PCF->wsel==4&&frb==1) // si en onglet controle
				{
					PCF->DrawBoutonArticle(17);// Redessine tous les boutons de controle
					frb=0;
				}
				else
				{
					if((PCF->wsel==4||PCF->wsel==1)&&PCF->lselevt.GetCount()==0&&PCF->CONTROL==1)
					{
						PCF->ValideControl();//arret controle
						if(PCF->wsel==4)
						{
							PCF->GetDlgItem(IDC_11)->SetWindowText(""); // Redessine le bouton avec le bon texte
							PCF->GetDlgItem(IDC_11)->RedrawWindow(0,0,1|256|4); // Redessine le bouton avec le bon texte
						}
					}
				}
			}
		}
		else
			sfol.m_size=0;
		Sleep(1000);
	}
}

DWORD WINAPI  RNThread(LPVOID lpParameter)
{
	CConcertoDlg* PCF=  (CConcertoDlg*)lpParameter;
	CString ordi;
	CString temp;
	CString num;
	int j;
	CFileFind cff;
	CFileStatus sfil;
	BOOL stat;
	int idx=0;//n° poste
	while(TRUE)//recherche n° poste
	{
		if(GetCurrentThreadId()==PCF->RNThreadID[idx])
			break;
		idx++;
		if(idx>=9)
			idx=0;
		Sleep(50);
	}
	ordi.Format("0%u",idx+1);
	ordi=ordi.Right(2);
	ordi="\\\\"+PCF->prefix+"_"+ordi+"\\Control\\*.*";
	num.Format("Poste %u = ",idx+1);
	while(TRUE)
	{
		stat=cff.FindFile(ordi,0);
		DWORD ret=GetLastError();
		if(stat==0)
		{
			temp.Format("%u",ret);
			cff.Close();
			//PCF->MessageBox(num+temp);
			while(PCF->FLMAC)
				Sleep(100);
			InterlockedExchange(&PCF->FLMAC,1);
			if((j=PCF->lmac.FindStringExact(0,ordi))!=LB_ERR )
			{
				PCF->lmac.SetItemData(j,-1);// notifie dans la liste des machine que ce poste est déconnecté
				//PCF->lmac.DeleteString(j);
			}
			InterlockedExchange(&PCF->FLMAC,0);
		}
		else
		{
			while(stat)
			{
				stat=cff.FindNextFileA();
				if(cff.IsDots()&&cff.GetFileName()==".")
				{
					if(PCF->alone==0)
					{
						if(PCF->lmac.FindStringExact(0,ordi)==-1)
						{
							if(CFile::GetStatus(ordi.Left(ordi.GetLength()-3)+"\\Status.dat",sfil))//Entrée dans la liste des machines
							{
								while(PCF->FLMAC)
									Sleep(100);
								InterlockedExchange(&PCF->FLMAC,1);
								if(sfil.m_size==0)
									PCF->lmac.SetItemData(PCF->lmac.AddString(ordi),1);//pour un maitre
								else
									PCF->lmac.SetItemData(j,2);//pour un autonome
								InterlockedExchange(&PCF->FLMAC,0);
							}
							else
							{
								while(PCF->FLMAC)
									Sleep(100);
								InterlockedExchange(&PCF->FLMAC,1);
								PCF->lmac.SetItemData(PCF->lmac.AddString(ordi),0);//pour un esclave
								InterlockedExchange(&PCF->FLMAC,0);
							}
							break;
						}
						else//autonome
						{
							if((j=PCF->lmac.FindStringExact(0,ordi))!=-1)
							{
								if(CFile::GetStatus(ordi.Left(ordi.GetLength()-3)+"\\Status.dat",sfil))//Mise à jour d'un maitre ou esclave dans la liste
								{
									while(PCF->FLMAC)
										Sleep(100);
									InterlockedExchange(&PCF->FLMAC,1);
									if(sfil.m_size==0)
										PCF->lmac.SetItemData(j,1);//pour un maitre
									else
										PCF->lmac.SetItemData(j,2);//pour un autonome
									InterlockedExchange(&PCF->FLMAC,0);
								}
								else
								{
									while(PCF->FLMAC)
										Sleep(100);
									InterlockedExchange(&PCF->FLMAC,1);
									PCF->lmac.SetItemData(j,0);//pour un esclave
									InterlockedExchange(&PCF->FLMAC,0);
								}
							}
						}
					}
					else	// autonome
					{
						if(PCF->lmac.FindStringExact(0,ordi)==-1)
						{
							if(CFile::GetStatus(ordi.Left(ordi.GetLength()-3)+"\\Status.dat",sfil))//Entrée dans la liste des machines
								if(sfil.m_size>0)
								{
									while(PCF->FLMAC)
										Sleep(100);
									InterlockedExchange(&PCF->FLMAC,1);
									PCF->lmac.SetItemData(PCF->lmac.AddString(ordi),2);//pour un maitre autonome
									InterlockedExchange(&PCF->FLMAC,0);
								}
							break;
						}
						else
						{
							while(PCF->FLMAC)
								Sleep(100);
							InterlockedExchange(&PCF->FLMAC,1);
							if((j=PCF->lmac.FindStringExact(0,ordi))!=-1)
							{
								if(CFile::GetStatus(ordi.Left(ordi.GetLength()-3)+"\\Status.dat",sfil))//Mise à jour d'un maitre ou esclave dans la liste
									if(sfil.m_size>0)
									{
										PCF->lmac.SetItemData(j,2);//pour un maitre autonome
									}
							}
							InterlockedExchange(&PCF->FLMAC,0);
						}
					}
				}
			}
			cff.Close();
		}
		if(ret==ERROR_BAD_NETPATH)
			Sleep(10000);
		else
			Sleep(1000);
	}
}
DWORD WINAPI ImageScanThread(LPVOID lpParameter)	// détection et maj fichier image dans esclave
{
	CConcertoDlg* PCF=  (CConcertoDlg*)lpParameter;
	CString temp;
	CFileStatus sfil;
	while(TRUE)
	{
		if(PCF->afmode==1&&!PCF->master)//****************************************************************************************************************************************************************************
		{
			temp=PCF->netcontdir+"\\Borne"+PCF->poste+".dat";
			if(CFile::GetStatus(temp,sfil))
			{
				CopyFile(PCF->netcontdir+"\\Borne"+PCF->poste+".dat",PCF->controldir+"\\Borne.dat",FALSE);
				DeleteFile(PCF->netcontdir+"\\Borne"+PCF->poste+".dat");
			}
			temp=PCF->controldir+"\\Borne.dat";
			if(CFile::GetStatus(temp,sfil))
			{
				PCF->ImportImage(PCF->controldir+"\\");
				DeleteFile(temp);
			}
		}
		Sleep(1000);
	}
	_endthreadex( 0 );
	return 0;
}

DWORD WINAPI GetMCIModeThread(LPVOID lpParameter)	// Détection de fin de video pour redémarrer
{
	CConcertoDlg* PCF=  (CConcertoDlg*)lpParameter;
	CString temp;
	while(TRUE)
	{
		int i;
		if(PCF->FTEM==0&&PCF->SCR!=NULL)
		{
			MCIWndGetMode(PCF->SCR, &i,sizeof(int));
			if(i==MCI_MODE_STOP)
			{
				MCIWndHome(PCF->SCR);
			}
			MCIWndPlay(PCF->SCR);
		}
		if(PCF->afmode==0)
		{	
			PCF->PostMessage(WM_USER+7,0,0);
		}
		Sleep(200);
	}
	_endthreadex( 0 );
	return 0;
}

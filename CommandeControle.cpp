#include "stdafx.h"
#include "ConcertoDlg.h"
#include "Concerto.h"
#include "Num.h"
#include "Message.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void CConcertoDlg::OnBnClickedControl()
{
	
	if(code==codeadmin||code==codereseller||code==codemanager||code=="65748392"||code=="29384756")
	{
		CloseKeyboard();
		hist=0;
		artnum=1;
		artrange=0;
		seltouche=0;
		DrawWindowControl();
		RefreshControlList();
		bdel.ShowWindow(0);
	}
}

void CConcertoDlg::ValideControl()
{
	int i=0;
	int idx=0;
	if(CONTROL) // Si on est déjà en Contrôle arrêt du service
	{	
		
		InterlockedExchange(&CONTROL,0);
		Sleep(100);
		if(scaninter=="BLUE")
			InterlockedExchange(&BASCULE,0);
		InterlockedExchange(&PAUSERS,0);
		tcontrol.SetWindowTextA("HSCANBLUE"); // On remplace le QR par le scanner;
		scan="";
		SCANMODE=DT_CENTER|DT_SINGLELINE|DT_VCENTER;
		SCANCOLOR=0;
		nscan.ShowWindow(0);
		nscan.SetWindowTextA("");
		nscan.ShowWindow(0);
		// On efface les traces d'affichage du scanner sous le titre
		viewscan=0;
		PostMessage(WM_USER+9,0,0);//RedrawWindow(0,0,1|256|4);
		/*if(master&&wsel==4)
			OnBnClickedQuitter();*/
	}
	else // Sinon mise en marche du service
	{
		if(lselevt.GetCount()>0)
		{
			if(scaninter=="BLUE"||scaninter=="USB")// Test de clé Bluetooth ou scanner USB
			{
				InterlockedExchange(&CONTROL,1);
				scan="";
				SCANMODE=DT_CENTER|DT_SINGLELINE|DT_VCENTER;
				SCANCOLOR=0;
				tcontrol.SetWindowTextA("HRCONTROL"); // On remplace l'antenne par le QR
				PostMessage(WM_USER+9,0,0);//RedrawWindow(0,0,1|256|4);

				OnBnClickedQuitter(); // On revient à l'écran des ventes
			}
			else
			{// Si pas de clé ou scanner USB avertissement d'erreur
				MessageBox(txtm[100]+"\n"+txtm[59]);
				tcontrol.ShowWindow(0);
			}
		}
	}
}

void CConcertoDlg::DelSelEvt()// Efface un élément de la liste de controle
{
	CString temp;
	CString dir;
	CString sourcedir;
	CString targetdir;
	CString num;
	CString buf;
	CString nart;
	int fatrium=0;
	int i=0;
	int wdg=0;
	int j=0;
	int idx=0;
	DWORD nbw;
	HANDLE hf;
	KillTimer(13);
	CMessage* pdlg;
	//while(i<lselevt.GetCount())
	if((i=lselevt.GetCurSel())!=-1)
	{
		pdlg=new CMessage(this);
		pwlog=pdlg;
		
		idx=(int)lselevt.GetItemData(i);// Retrouve le N° index mémoire controle
		temp=txtm[49];//"Voulez-vous supprimer le fichier de contrôle";
		pdlg->mes1=temp;
		pdlg->mes2=clibel1[idx];
		pdlg->mes3=clibel2[idx]+" ?";
		pdlg->mode=0;
		if(pdlg->DoModal()==IDOK)
		{
			pdlg->DestroyWindow();
			delete pdlg;
			num.Format("%u",idx);
			if(num.GetLength()==1)
				num="0"+num;
			dir=controldir+"\\"+num;
			buf="";
retry:;
			hf=(CreateFile(dir+"\\Controle.dat",GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL));
			if(hf==INVALID_HANDLE_VALUE)
			{
				MessageBox("Erreur ouverture "+dir+"\\Controle.dat");
				wdg++;
				Sleep(100);
				if(wdg<5)
					goto retry;
			}
			else
			{
				if(ReadFile(hf,buf.GetBuffer(GetFileSize(hf,NULL)),GetFileSize(hf,NULL),&nbw,NULL))
				{
					buf.ReleaseBuffer(nbw);
				}
				else
					MessageBox(dir+"\\Controle.dat non lu.");
				CloseHandle(hf);
				if(buf.Find("X\r\n",0)!=-1)
				{
					if(cfrom[idx].Find("EXPORT",0)!=-1)// ATRIUM
					{
						if(cfrom[idx].Find("SHOP",0)!=-1)
							SetTimer(17,30000,NULL);
						shopidx=idx;
						if(noprint)
							PrintAtriumList();
						else
							InterlockedExchange(&PRMODE,5);
						Sleep(300);
						while(PRMODE!=0)
							Sleep(300);// Délai avant effacement des fichier de controle pour l'esclave
					}
					else
						if(cfrom[idx]=="WEB DIGITICK")
						{
							digidx=idx;
							if(noprint)
								PrintDigitickList();
							else
								InterlockedExchange(&PRMODE,6);
							Sleep(300);
							while(PRMODE!=0)
								Sleep(300);// Délai avant effacement des fichier de controle pour l'esclave
						}
						else
							ClearControl(idx);
					DeleteControleFile(dir+"\\Controle.dat");
					DeleteFile(backupdir+"\\Control\\"+num+"\\Controle.dat");
					DeleteFile(securedir+"\\Control\\"+num+"\\Controle.dat");
				}
				else
				{
					pdlg=new CMessage(this);
					temp=txtm[50];//Attention
					pdlg->mes1=temp+": "+clibel1[idx];
					temp=txtm[51];//"n'a jamais été utilisé"
					pdlg->mes2=temp;
					temp=txtm[52];//"Voulez-vous le supprimer quand même ?"
					pdlg->mes3=temp;
					pdlg->mode=0;
					if(pdlg->DoModal()==IDOK)
					{
						pdlg->DestroyWindow();
						delete pdlg;
						pwlog=NULL;
						if(cfrom[idx].Find("EXPORT",0)!=-1)// ATRIUM ou SHOP
						{
							if(cfrom[idx].Find("SHOP",0)!=-1)
								SetTimer(17,30000,NULL);
							shopidx=idx;
							if(noprint)
								PrintAtriumList();
							else
								InterlockedExchange(&PRMODE,5);// Demande impression log SHOP
							Sleep(300);
							while(PRMODE!=0)//Attend la fin de l'impression
								Sleep(300);// Délai avant effacement des fichier de controle pour l'esclave
						}
						else
						{
							if(cfrom[idx]=="WEB DIGITICK")
							{
								digidx=idx;
								if(noprint)
									PrintDigitickList();
								else
									InterlockedExchange(&PRMODE,6);
								Sleep(300);
								while(PRMODE!=0)
									Sleep(300);// Délai avant effacement des fichier de controle pour l'esclave
							}
							else
							{
								ClearControl(idx);
							}
						}
						DeleteControleFile(dir+"\\Controle.dat");
						DeleteFile(backupdir+"\\Control\\"+num+"\\Controle.dat");
						DeleteFile(securedir+"\\Control\\"+num+"\\Controle.dat");
					}
					else
					{
						pdlg->DestroyWindow();
						delete pdlg;
						pwlog=NULL;
					}
				}
			}
		}
		else
		{
			pdlg->DestroyWindow();
			delete pdlg;
			pwlog=NULL;
		}
	}
	lselevt.SetCurSel(-1);
	bdel.ShowWindow(0);
	Sleep(1000);// Délai avant mise à jour du fichier de config controle pour l'esclave
	DrawBoutonArticle(17);
	RefreshControle();
	RefreshControlList();
	if(lselevt.GetCount()==0&&CONTROL==1)
	{// Arrête le controle si plus d'élément dans la liste
		if(wsel==4)
		{
			ValideControl();
			GetDlgItem(IDC_11)->SetWindowTextA("");
			GetDlgItem(IDC_11)->RedrawWindow(0,0,1|256|4); // Redessine le bouton avec le bon texte
		}
		else
		{
			InterlockedExchange(&CONTROL,0);
			if(wsel==1)
			{
				PostMessage(WM_USER+9,0,0);//RedrawWindow(0,0,1|256|4);
			}
		}

	}
}

void CConcertoDlg::DeleteControleFile(CString path)
{
	CString buf;
	CString temp;
	DWORD nbw;
	int i;
	HANDLE hf=(CreateFile(controldir+"\\Descript.dat",GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL));
	if(hf!=INVALID_HANDLE_VALUE)
	{
		ReadFile(hf,buf.GetBuffer(GetFileSize(hf,NULL)),GetFileSize(hf,NULL),&nbw,NULL);
		buf.ReleaseBuffer(nbw);
	}
	else
		buf="";
	if((i=buf.Find(path,0))!=-1)
	{
		if(i>0)
			temp=buf.Left(i);
		else
			temp="";
		if((i=buf.Find("\r\n",i))!=-1)
		{
			buf=temp+buf.Mid(i+2);
			SetFilePointer(hf,NULL,NULL,FILE_BEGIN);
			if(buf.GetLength()>0)
			{
				WriteFile(hf,buf.GetBuffer(buf.GetLength()),buf.GetLength(),&nbw,NULL);
			}
			SetEndOfFile(hf);
		}
	}
	CloseHandle(hf);
	DeleteFile(path);
}

void CConcertoDlg::AddNewEvt(int idx)
{
	CString num;
	CString temp;
	CMessage dlg;
	temp=txtm[53];//Date et heure limite de l'évènement
	dlg.mes1="*** "+temp+" ***";
	dlg.mes2=" ";
	dlg.mes3=" ";
	dlg.mode=5;
	if((clibel1[idx]!=""||clibel2[idx]!=""))
	{
		num.Format("%u",idx);
		if(cselevt[idx]==1)
		{
			cselevt[idx]=0;
			if(cfrom[idx].Find("SHOP",0)==-1)
			{
				cdate[idx]="";
				cheure[idx]="";
				AfxGetApp()->WriteProfileString(num,"CDATE",cdate[idx]);
				AfxGetApp()->WriteProfileString(num,"CHEURE",cheure[idx]);
			}
			AfxGetApp()->WriteProfileInt(num,"CONTROLE",cselevt[idx]);
		}
		else
		{
			if(valhor&&horaire&&choraire[idx]==2&&cfrom[idx].Find("SHOP",0)==-1)
			{
				dlg.DoModal();
				CTime tim=CTime::GetCurrentTime();
				SYSTEMTIME DAT;
				SYSTEMTIME HEU;
				dlg.seldate.GetAsSystemTime(DAT);
				dlg.selhor.GetAsSystemTime(HEU);
				DAT.wHour=HEU.wHour;
				DAT.wMinute=HEU.wMinute;
				DAT.wSecond=HEU.wSecond;
				CTime dtemp(DAT);
				if(tim>=dtemp)
				{
					cdate[idx]="";
					cheure[idx]="";
					cselevt[idx]=0;
				}
				else
				{
					cdate[idx]=dlg.seldate.Format("%d/%m/%Y");
					cheure[idx]=dlg.selhor.Format("%H:%M");
					cselevt[idx]=1;					
				}
				AfxGetApp()->WriteProfileString(num,"CDATE",cdate[idx]);
				AfxGetApp()->WriteProfileString(num,"CHEURE",cheure[idx]);			
			}
			else
			{
				cselevt[idx]=1;
				if(cfrom[idx].Find("SHOP",0)==-1)
				{
					cdate[idx]="";
					cheure[idx]="";
					AfxGetApp()->WriteProfileString(num,"CDATE",cdate[idx]);
					AfxGetApp()->WriteProfileString(num,"CHEURE",cheure[idx]);			
				}
				else
					if(valhor&&horaire&&choraire[idx]==2&&cfrom[idx].Find("SHOP",0)!=-1)
					{
						


					}
			}
			AfxGetApp()->WriteProfileInt(num,"CONTROLE",cselevt[idx]);
		}
		RefreshControlList();
		RefreshControle();
		//AfxGetApp()->WriteProfileInt(num,"CTOT",ctot[idx]);
	}
}

void CConcertoDlg::OnLbnSelchangeSelspect()
{
	//if(wsel==6)
	{
		//lselevt.SetSel(-1,FALSE);
	}
	if(lselevt.GetCurSel()!=-1&&master)
		bdel.ShowWindow(1);
	else
		bdel.ShowWindow(0);
	lselevt.RedrawWindow(0,0,1|256|4);
}

void CConcertoDlg::ClearControl(int idx)
{
	CString temp;
	CString nart;
	nart.Format("%u",idx);
	clibel1[idx]="";
	AfxGetApp()->WriteProfileString(nart,"CLIBELLE1","");
	clibel2[idx]="";
	AfxGetApp()->WriteProfileString(nart,"CLIBELLE2","");
	cfrom[idx]="";
	AfxGetApp()->WriteProfileString(nart,"CFROM","");
	ctot[idx]=0;
	AfxGetApp()->WriteProfileInt(nart,"CTOT",0);
	cselevt[idx]=0;
	AfxGetApp()->WriteProfileInt(nart,"CONTROLE",0);
	choraire[idx]=0;
	AfxGetApp()->WriteProfileInt(nart,"CHORAIRE",0);
	cdate[idx]="";
	AfxGetApp()->WriteProfileString(nart,"CDATE",cdate[idx]);
	cheure[idx]="";
	AfxGetApp()->WriteProfileString(nart,"CHEURE",cheure[idx]);
	cas[idx]=0;
	AfxGetApp()->WriteProfileInt(nart,"CAS",0);
	int i=1;
	while(i<=100)
	{
		if(target[i]==idx)
		{
			target[i]=0;
			temp.Format("%u",i);
			AfxGetApp()->WriteProfileInt(temp,"TARGET",0);
		}
		i++;
	}
	ne[idx]=0;
}

void CConcertoDlg::RefreshControlList()
{
	CString source;
	HANDLE hf;
	CString buf;
	CString temp;
	CString temp1;
	CString netxt;
	CString nttxt;
	CString dir;
	CString fread;
	CString jour;
	CString mois;
	CString an;
	int nt;
	int tne;// Nombre temporaire de controle grillé
	int idx;
	int fidx;
	int filecnt=0;
	lselevt.ResetContent();
	int j;
	DWORD len;
	int i=1;
	while(i<=16)
	{
		temp.Format("0%u",i);
		dir=controldir+"\\"+temp.Right(2);
		hf=(CreateFile(dir+"\\Controle.dat",GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL));
		if(hf!=INVALID_HANDLE_VALUE)
		{
			filecnt++;
			ReadFile(hf,fread.GetBuffer(13),13,&len,NULL);
			fread.ReleaseBuffer(len);
			CloseHandle(hf);
			idx=atoi(fread.Mid(1,2));//Retrouve le N° de la touche de prevente
			if(idx>0&&idx<=NART&&target[idx]==0&&fread.Find("\r\n",0)!=-1&&cfrom[i].Find("EXPORT",0)==-1)	// reconnaissance ticket ARBAN non inséré dans la liste
			{
				j=1;
				while(j<=16) // Recherche d'un emplacement mémoire controle de libre
				{
					if(clibel1[j]==""&&clibel2[j]=="")
						break;
					j++;
				}
				target[idx]=j;// met le N° de mémoire controle dans le N° de touche
				temp.Format("%u",idx);
				AfxGetApp()->WriteProfileInt(temp,"TARGET",j);
				clibel1[j]=libel1[idx]+libel2[idx];// Génère le libellé de la mémoire controle
				clibel2[j]=libelspect[idx];
				cfrom[j]="INTERNE";
				cselevt[j]=0;
				choraire[j]=entrymode[idx];
				cdate[j]="";
				cheure[j]="";
				cas[j]=0;
				ne[j]=0;
				temp.Format("%u",j);
				AfxGetApp()->WriteProfileString(temp,"CLIBELLE1",clibel1[j]);
				AfxGetApp()->WriteProfileString(temp,"CLIBELLE2",clibel2[j]);
				AfxGetApp()->WriteProfileString(temp,"CFROM",cfrom[j]);
				AfxGetApp()->WriteProfileInt(temp,"CTOT",ctot[j]);
				AfxGetApp()->WriteProfileInt(temp,"CONTROLE",cselevt[j]);
				AfxGetApp()->WriteProfileInt(temp,"CHORAIRE",choraire[j]);
				AfxGetApp()->WriteProfileString(temp,"CDATE",cdate[j]);
				AfxGetApp()->WriteProfileString(temp,"CHEURE",cheure[j]);
				AfxGetApp()->WriteProfileInt(temp,"CAS",(int)(cas[j]*100));
			}
			else	// cas ticket Moxity, Weezevent
			{
				if(idx==0)//&&master
				{
					hf=(CreateFile(controldir+"\\Descript.dat",GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL));
					if(hf!=INVALID_HANDLE_VALUE)
					{
						ReadFile(hf,buf.GetBuffer(GetFileSize(hf,NULL)),GetFileSize(hf,NULL),&len,NULL);
						buf.ReleaseBuffer(len);
						CloseHandle(hf);
					}
					else
						buf="";
					temp=dir+"\\Controle.dat";
					if((idx=buf.Find(temp,0))!=-1)	//test si on trouve ce fichier dans le log des fichiers WEB
					{
						if((fidx=buf.Find(";",idx))!=-1)
						{
							idx=fidx+1;
							if((fidx=buf.Find(";",idx))!=-1)
							{
								temp=buf.Mid(idx,fidx-idx);
								j=1;
								while(j<=16) // Recherche de l'inscription de ce fichier
								{
									if(clibel1[j]==temp)
										break;
									j++;
								}
								if(j>16)
								{
									j=1;
									while(j<=16) // Recherche d'un emplacement de libre
									{
										if(clibel1[j]==""&&clibel2[j]=="")
											break;
										j++;
									}
									clibel1[j]=temp;
									idx=fidx+1;
									if((fidx=buf.Find(";",idx))!=-1)
									{
										temp=buf.Mid(idx,fidx-idx);
										clibel2[j]=temp;
										idx=fidx+1;
										if((fidx=buf.Find("\r\n",idx))!=-1)
										{
											temp=buf.Mid(idx,fidx-idx);
											cfrom[j]=temp;
										}
									}
									cselevt[j]=0;
									choraire[j]=2;
									cdate[j]="";
									cheure[j]="";
									cas[j]=0;
									ne[j]=0;
									temp.Format("%u",j);
									AfxGetApp()->WriteProfileInt(temp,"TARGET",i);
									AfxGetApp()->WriteProfileString(temp,"CLIBELLE1",clibel1[j]);
									AfxGetApp()->WriteProfileString(temp,"CLIBELLE2",clibel2[j]);
									AfxGetApp()->WriteProfileString(temp,"CFROM",cfrom[j]);
									AfxGetApp()->WriteProfileInt(temp,"CTOT",ctot[j]);
									AfxGetApp()->WriteProfileInt(temp,"CONTROLE",cselevt[j]);
									AfxGetApp()->WriteProfileInt(temp,"CHORAIRE",choraire[j]);
									AfxGetApp()->WriteProfileString(temp,"CDATE",cdate[j]);
									AfxGetApp()->WriteProfileString(temp,"CHEURE",cheure[j]);
									AfxGetApp()->WriteProfileInt(temp,"CAS",(int)(cas[j]*100));
									temp=dir+"\\Controle.dat";
								}
							}
						}
					}
				}
			}
		}
		i++;
	}
	contfile=filecnt;
	i=1;
	while(i<=16)// Recherche les fichiers marqués sélectionné et les ajoute dans la liste de controle
	{
		if(cselevt[i]>0)
		{
			temp.Format("0%u",i);
			dir=controldir+"\\"+temp.Right(2);
			nt=0;
			tne=0;
			idx=0;
			hf=CreateFile(dir+"\\Controle.dat",GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
			if(ReadFile(hf,buf.GetBuffer(GetFileSize(hf,NULL)),GetFileSize(hf,NULL),&len,NULL))
			{
				buf.ReleaseBuffer(len);
				CloseHandle(hf);
				while((idx=buf.Find("\r\n",idx))!=-1)
				{
					nt++;
					if(buf.GetAt(idx-1)=='X')
						tne++;
					idx+=2;
				}			
			}
			else
			{
				nt=tne=0;
			}
			nttxt.Format("%u",nt);
			netxt.Format("%u",tne);
			if(valhor&&horaire&&choraire[i]==2)//limite
			{
				temp=clibel1[i].Left(30)+";"+clibel2[i].Left(10)+";"+txtc[88]+": "+cdate[i]+" à "+cheure[i]+";"+netxt+"/"+nttxt;
			}
			else
				/*if(valhor&&horaire)
				{
					temp=clibel1[i].Left(30)+";"+clibel2[i].Left(10)+";"+temp+";"+netxt+"/"+nttxt;
				}
				else*/
				{
					temp=clibel1[i].Left(30)+";"+clibel2[i].Left(10)+";"+" "+";"+netxt+"/"+nttxt;
				}

			lselevt.SetItemData(lselevt.AddString(temp),i);
			if(cfrom[i].Find("SHOP",0)!=-1)
			{
				InterlockedExchange(&CONTROL,1);
				if(wsel==4)
				{
					GetDlgItem(IDC_11)->SetWindowTextA("");
					GetDlgItem(IDC_11)->RedrawWindow(0,0,1|256|4); // Redessine le bouton avec le bon texte
				}
			}

			bdel.ShowWindow(0);
			ctot[i]=nt;
			if(tne!=ne[i])
			{
				ne[i]=tne;
				RefreshControle();
			}
		}
		i++;
	}
	if(lselevt.GetCount()==0&&CONTROL==1)
	{
		bdel.ShowWindow(0);
		if(wsel==1)
			ValideControl();
		else
			if(wsel==4)
			{
				ValideControl();
				GetDlgItem(IDC_11)->SetWindowTextA("");
			}
	}
}

void CConcertoDlg::OnBnClickedDel()
{
	if(wsel==4)
		DelSelEvt();
	else
	{
		if(wsel==1&&afmode)
		{
			SetTimer(8,100,NULL);
		}
	}
}
void CConcertoDlg::RefreshControle()
{
	int i;
	int j;
	CString temp;
	CString controle;
	CString buf;
	DWORD ln;
	DWORD rln;
	controle="";
	HANDLE hf;
	int wdg=0;
	if(master&&alone==0)
	{
		i=1;
		while(i<=16)
		{
			controle+=cfrom[i]+";";
			controle+=clibel1[i]+";";
			controle+=clibel2[i]+";";
			temp.Format("%u",choraire[i]);
			controle+=temp+";";
			temp.Format("%u",ctot[i]);
			controle+=temp+";";
			controle+=cdate[i]+";";
			controle+=cheure[i]+";";
			temp.Format("%u",cselevt[i]);
			controle+=temp+";";
			temp.Format("%u",0);
			controle+=temp+";";
			j=1;
			while(j<=NART)
			{
				if(target[j]==i)
					break;
				j++;
			}
			if(j<=NART)
				temp.Format("%u",j);
			else
				temp="0";
			controle+=temp+"\r\n";
			i++;
		}
		buf=controle;
retry:;
		hf=CreateFile(controldir+"\\Controle.cfg",GENERIC_READ|GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
		if(hf!=INVALID_HANDLE_VALUE)
		{
			ln=buf.GetLength();
			WriteFile(hf,buf.GetBuffer(ln),ln,&rln,NULL);
			CloseHandle(hf);
			if(lmac.GetCount()>0)
			{
				for(i=0;i<lmac.GetCount(); i++)
				{
					if(lmac.GetItemData(i)==0)
					{
						lmac.GetText(i,temp);
						temp=temp.Left(temp.GetLength()-3)+"Controle.cfg";
						CopyFile(controldir+"\\Controle.cfg",temp,FALSE);
					}
				}
			}
		}
		else
		{
			Sleep(100);
			goto retry;
		}
	}
}
void CConcertoDlg::SendBarmaticSpooler(int idx)
{
	CString temp1;
	CString place="";
	if(nvalplace&&(perso[idx]&2))
	{
retry_place1:;							
		if(master)
			placepath=controldir+"\\Place.dat";
		else
		{
			if(netcontdir!=""&&netcontdir!=controldir)
				placepath=netcontdir+"\\Place.dat";
			else
			{
				CMessage dlg;
				dlg.mes1=txtm[75];//La billetterie n'est pas connectée.
				dlg.mes2=txtm[76];//Veuillez recommencer
				dlg.mes3=txtm[77];
				dlg.mode=1;
				dlg.DoModal();
				goto abort;
			}
		}
		CNum* pnum=new CNum ();
		if(pnum==NULL)
			MessageBox("num place==NULL");
		else
		{
			pnum->wlargeur=(int)((float)(wlargeur/2));
			pnum->whauteur=whauteur/3;
			pnum->nID=IDC_DUM;
			pnum->chiffre = 6;
			pnum->mode=3;
			pnum->nombre="";
			pnum->txtmessage=txtc[59];//Place
			pnum->DoModal();
			place=pnum->nombre;
			delete pnum;
			int ret=SearchPlace(place);
			if(ret==0)
				goto retry_place1;
			else
			{
				if(ret==-1)
				{
					place="";
					goto abort;
				}
			}
			SPX[SPW]=1;
			SPT[SPW]=idx;
			STT[SPW]=place;
			IncSpoolIndex(&SPW);
			InterlockedIncrement(&SPN);
		}
	}
	else
	{
		place="";
		SPX[SPW]=1;
		SPT[SPW]=idx;
		STT[SPW]=place;
		IncSpoolIndex(&SPW);
		InterlockedIncrement(&SPN);
	}
	RefreshControle();
	RefreshControlList();
abort:;
}

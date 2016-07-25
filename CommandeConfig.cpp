#include "stdafx.h"
#include "ConcertoDlg.h"
#include "Concerto.h"
#include "Num.h"
#include "Gal.h"
#include "Message.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void CConcertoDlg::OnBnClickedConfig()
{
		CloseKeyboard();
		WritePrivateProfileString("Main","Site","1",workdir+"\\FreeVK.ini");
		WritePrivateProfileString("Main","Colors","4",workdir+"\\FreeVK.ini");
		WritePrivateProfileString("Main","AutoClick","1",workdir+"\\FreeVK.ini");
		WritePrivateProfileString("Main","FitWidth","1",workdir+"\\FreeVK.ini");
		WritePrivateProfileString("Main","AlphaBlend","255",workdir+"\\FreeVK.ini");
		WritePrivateProfileString("Main","TMainFormTop","720",workdir+"\\FreeVK.ini");
		WritePrivateProfileString("Main","TMainFormLeft","0",workdir+"\\FreeVK.ini");
		WritePrivateProfileString("Main","TMainFormHeight","300",workdir+"\\FreeVK.ini");
		WritePrivateProfileString("Main","TMainFormWidth","1280",workdir+"\\FreeVK.ini");
		WritePrivateProfileString("Main","TMainFormState","0",workdir+"\\FreeVK.ini");
		WritePrivateProfileString("Main","Keyboard","3",workdir+"\\FreeVK.ini");
		DrawWindowConfig();
}
void CConcertoDlg::OnBnClickedBilprint()
{
	CDC cdc;
	CTime tim;
	if(ldate.GetCount()>0)
	{
		ldate.GetText(ldate.GetCurSel(),histpath);
		hist=1;
		DrawWindowResultat();
	}
}

void CConcertoDlg::OnStnClickedNnauto()
{
	CString temp1;
	CString temp;
	CString num;
	if(fadmin)
	{
		if(master)
		{
			if(fprev)
			{
				fprev=0;
				valhor=0;
				horaire=0;
				if(master)
				{
					for(int i=0;i<100;i++)
					{
						num.Format("%u",i);
						target[i]=0;
						AfxGetApp()->WriteProfileInt(num,"TARGET",0);
						entrymode[i]=0;
						AfxGetApp()->WriteProfileInt(num,"VALCONSO",entrymode[i]);
						AfxGetApp()->WriteProfileInt(num,"VCONSO",entrymode[i]);
					}
				}
			}
			else
			{
				fprev=1;
				valhor=0;
				horaire=1;
			}
			temp.Format("%u",fprev);
			WriteConfigString("Client","Prevente",temp);
			//bcontrol.ShowWindow(fprev);//****************************************************************************************************************
			temp.Format("%u",horaire);
			WriteConfigString("Client","Horaire",temp);
			temp.Format("%u",valhor);
			WriteConfigString("Client","ValHor",temp);
			nvhor.SetWindowTextA("Horaire");
			FART=1;
			RefreshArticle();
			DrawWindowConfig();
		}
	}
	else
	{
		if(autonews)
			autonews=0;
		else
			autonews=1;
		temp.Format("%u",autonews);
		WriteConfigString("Client","Autonews",temp);
	}
	nnauto.SetWindowText("Impression journal ou Prevente");
}

void CConcertoDlg::OnStnClickedNpauto()
{
	CString temp1;
	if(fadmin)
	{
		if(paravent)
			paravent=0;
		else
			paravent=1;
		temp1.Format("%u",paravent);
		WriteConfigString("Client","Paravent",temp1);
	}
	else
	{
		if(autoprint)
		{
			autoprint=0; 
			lcode.ResetContent();
			lqte.ResetContent();
			lptot.ResetContent();
			sprix.SetWindowTextA("");
		}
		else
			autoprint=1;
		temp1.Format("%u",autoprint);

		WriteConfigString("Client","Autoprint",temp1);
	}
	npauto.SetWindowText(txtc[51]);//"Ticket auto");
}

void CConcertoDlg::OnBnClickedGlog()
{
}
void CConcertoDlg::OnStnClickedSposte()
{
	int i;
	CString temp;
	CString ordi;;
	CString temp1;
	{
		if(fadmin)
		{
			CloseKeyboard();
			if(lntick.GetCount()!=0)
			{
				CMessage* pdlg=new CMessage ();
				temp1=txtm[18];//La billetterie doit être cloturée
				pdlg->mes1=temp1;
				pdlg->mes2=" ";
				pdlg->mes3=" ";
				pdlg->mode=1;
				pdlg->DoModal();
				pdlg->DestroyWindow();
				delete pdlg;
			}
			else
			{
				sposte.GetWindowTextA(temp);
				CNum* pnum=new CNum ();
				pnum->wlargeur=(int)((float)(wlargeur/2));
				pnum->whauteur=whauteur/3;
				pnum->nID=IDC_SPOSTE;
				pnum->chiffre = 1;
				pnum->mode=1;
				pnum->nombre="";
				pnum->DoModal();
				if(atoi(pnum->nombre)>0&&atoi(pnum->nombre)<10)//N° poste 1 à 10
				{
					ordi="\\\\"+prefix+"_"+pnum->nombre+"\\Control\\*.*";
					for(i=0;i<lmac.GetCount();i++)
					{
						lmac.GetText(i,temp);
						if(ordi==temp)
						{
							if(lmac.GetItemData(i)>=0&&lmac.GetItemData(i)<=2)
							{
								temp1=txtm[23];							
								MessageBox(temp1);//Ce N° de poste existe déjà sur le réseau!
								sposte.SetWindowTextA(poste);
								goto FIN;
							}
						}

					}					
					poste=pnum->nombre;
					WriteConfigString("Client","Poste",pnum->nombre);
					InitMachineName();
				}
				else
					sposte.SetWindowTextA(temp);
FIN:;
				pnum->DestroyWindow();
				delete pnum;
			}
		}
	}
}
void CConcertoDlg::OnEnSetfocusSnom()
{
	CString temp;
	if(fadmin&&master)
	{
		snom.GetWindowTextA(libelsave);
		kid=snom.GetDlgCtrlID();
			PostMessage(WM_USER+13,0,0);
	}
	else
	{
		sdum.SetFocus();
	}
}

void CConcertoDlg::OnEnSetfocusSserveur()
{
	CString temp;
	if(fadmin)
	{
		sserveur.GetWindowTextA(libelsave);
		kid=sserveur.GetDlgCtrlID();
			PostMessage(WM_USER+13,0,0);
	}
	else
	{
		sdum.SetFocus();
	}
}
void CConcertoDlg::OnEnSetfocusSprefix()
{
	CString temp;
	if(fadmin)
	{
		sprefix.GetWindowTextA(libelsave);
		kid=sprefix.GetDlgCtrlID();
			PostMessage(WM_USER+13,0,0);
	}
	else
	{
		sdum.SetFocus();
	}
}
void CConcertoDlg::OnEnSetfocusSad1()
{
	CString temp;
	if(fadmin&&master)
	{
		sad1.GetWindowTextA(libelsave);
		kid=sad1.GetDlgCtrlID();
			PostMessage(WM_USER+13,0,0);
	}
	else
	{
		sdum.SetFocus();
	}
}

void CConcertoDlg::OnEnSetfocusSad2()
{
	CString temp;
	if(fadmin&&master)
	{
		sad2.GetWindowTextA(libelsave);
		kid=sad2.GetDlgCtrlID();
			PostMessage(WM_USER+13,0,0);
	}
	else
	{
		sdum.SetFocus();
	}
}

void CConcertoDlg::OnEnSetfocusSnaf()
{
	CString temp;
	if(fadmin&&master)
	{
		snaf.GetWindowTextA(libelsave);
		kid=snaf.GetDlgCtrlID();
			PostMessage(WM_USER+13,0,0);
	}
	else
	{
		sdum.SetFocus();
	}
}


void CConcertoDlg::OnEnSetfocusSsiret()
{
	CString temp;
	if(fadmin&&master)
	{
		ssir.GetWindowTextA(libelsave);
		kid=ssir.GetDlgCtrlID();
			PostMessage(WM_USER+13,0,0);
	}
	else
	{
		sdum.SetFocus();
	}
}

void CConcertoDlg::OnEnSetfocusSlicense0()
{
	CString temp;
	if(fadmin&&master)
	{
		slic0.GetWindowTextA(libelsave);
		kid=slic0.GetDlgCtrlID();
			PostMessage(WM_USER+13,0,0);
	}
	else
	{
		sdum.SetFocus();
	}
}

void CConcertoDlg::OnEnSetfocusSlicense1()
{
	CString temp;
	if(fadmin&&master)
	{
		slic1.GetWindowTextA(libelsave);
		kid=slic1.GetDlgCtrlID();
			PostMessage(WM_USER+13,0,0);
	}
	else
	{
		sdum.SetFocus();
	}
}

void CConcertoDlg::OnEnSetfocusSlicense2()
{
	CString temp;
	if(fadmin&&master)
	{
		slic2.GetWindowTextA(libelsave);
		kid=slic2.GetDlgCtrlID();
			PostMessage(WM_USER+13,0,0);
	}
	else
	{
		sdum.SetFocus();
	}
}

void CConcertoDlg::OnEnSetfocusSlicense3()
{
	CString temp;
	if(fadmin&&master)
	{
		slic3.GetWindowTextA(libelsave);
		kid=slic3.GetDlgCtrlID();
			PostMessage(WM_USER+13,0,0);
	}
	else
	{
		sdum.SetFocus();
	}
}

void CConcertoDlg::OnEnSetfocusSlicense4()
{
	CString temp;
	if(fadmin&&master)
	{
		slic4.GetWindowTextA(libelsave);
		kid=slic4.GetDlgCtrlID();
			PostMessage(WM_USER+13,0,0);
	}
	else
	{
		sdum.SetFocus();
	}
}

void CConcertoDlg::OnEnSetfocusSlicense5()
{
	CString temp;
	if(fadmin&&master)
	{
		slic5.GetWindowTextA(libelsave);
		kid=slic5.GetDlgCtrlID();
			PostMessage(WM_USER+13,0,0);
			//Klance();
	}
	else
	{
		sdum.SetFocus();
	}
}

void CConcertoDlg::OnEnSetfocusSlicense6()
{
	CString temp;
	if(fadmin&&master)
	{
		slic6.GetWindowTextA(libelsave);
		kid=slic6.GetDlgCtrlID();
			PostMessage(WM_USER+13,0,0);
	}
	else
	{
		sdum.SetFocus();
	}
}

void CConcertoDlg::OnEnSetfocusSmentiont()
{
	CString temp;
	if(master)
	{
		smentiont.GetWindowTextA(libelsave);
		kid=smentiont.GetDlgCtrlID();
			PostMessage(WM_USER+13,0,0);
	}
}

void CConcertoDlg::OnEnSetfocusSmentionp()
{
	CString temp;
	if(master)
	{
		smentionp.GetWindowTextA(libelsave);
		kid=smentionp.GetDlgCtrlID();
		PostMessage(WM_USER+13,0,0);
	}
}

void CConcertoDlg::OnStnClickedSexer()
{
	CString temp;
	CString st;
	if(wsel==0)
	{
		CCombo dlg;
retry:;
		sexer.GetWindowRect(&dlg.rctstat);
		dlg.rctstat.top=dlg.rctstat.bottom;
		dlg.winh=(int)(htou/4);
		dlg.type=2;
		//av1.RedrawWindow(0,0,1|256|4);
		dlg.DoModal();
		if(dlg.sel>=0)
		{
			lmois.SetCurSel(dlg.sel);
			lmois.GetText(dlg.sel,exermois);
			sexer.SetWindowText(exermois);
			WriteConfigString("Infocert","MoisExercice",exermois);
			if(wsel==0&&fraz==0)	// initialisation mois pendant ouverture
			{
				InitOldExercice();
				wsel=0;
			}
			else
			{
				CTime tim=CTime::GetCurrentTime();
				int yr;
				if(atoi(exermois)>tim.GetMonth())
					yr=tim.GetYear()-1;
				else
					yr=tim.GetYear();
				dexer.Format("%u",yr);
				WriteConfigString("Infocert","Exercice",dexer);
				temp=dexer+"\r\n";
				CWrite(sysdir+"\\csat.avs",temp,1);
				st="Exercice file "+dexer+"\r\n";
				st+=tim.Format("Open %d/%m/%Y %H:%M:%S");
				st+="\r\n";
				CWrite(datadir+"\\Exercice.dat",st,0);				
				FonctionEditeur("Initialisation date d'exercice "+exermois+"/"+dexer);				
				fraz=0;
				DrawWindowConcert();
				SetTimer(18,2000,NULL);
				SetTimer(17,30000,NULL);// Lance la recherche des fichiers WEB toutes les 30 secondes car pas de fichiers en controle
			}
		}
		else
			goto retry;
	}
}

void CConcertoDlg::InitOldExercice()
{
	int x;
	int idx;
	int idy;
	int idl;
	int corerror=0;
	int coperror=0;
	CString st;
	CString stc;
	CString buf;
	CString temp;
	CString temp1;
	CString temp2;
	CString sdir;
	CString xdir;
	CString tdir;
	CString spath;
	CString filetime;
	CString filesize;
	CString ngtz;
	CString gtp;
	CString pdate;
	double xcatva[10][30];
	double xtvaca[10][30];
	double cumul=0;
	double cumulp[30];
	double tmp;
	int yr;
	int fcours=0;
	CString tpath;
	CString ant;
	CFileStatus ff;
	CTime tim=CTime::GetCurrentTime();
	CFileFind cff;
	CString an=tim.Format("%Y");
	CString mois=tim.Format("%m");
	BOOL result;
	CFileStatus cfs;
	FILEINFO fi;
	HANDLE hf;
	int nbfile=0;
	int i;
	int k;
	int idal;
	int j;
	x=0;
	while(x<10)
	{
		i=0;
		while(i<30)
		{
			xcatva[x][i]=0;
			xtvaca[x][i]=0;
			i++;
		}
		x++;
	}
	x=0;
	while(x<30)
	{
		cumulp[x]=0.00;
		x++;
	}
	if(atoi(exermois)>tim.GetMonth())
		yr=tim.GetYear()-1;
	else
		yr=tim.GetYear();
	dexer.Format("%u",yr);
	WriteConfigString("Infocert","Exercice",dexer);
	FonctionEditeur("Initialisation date d'exercice "+exermois+"/"+dexer);
	st="Exercice file "+dexer+"\r\n";
	st+=tim.Format("Open %d/%m/%Y %H:%M:%S");
	st+="\r\n";
	CWrite(datadir+"\\Exercice.dat",st,0);
	CreateDirectory(securedir+"\\Data",NULL);
	CreateDirectory(backupdir+"\\Data",NULL);
	CreateDirectory(securedir+"\\Control",NULL);
	CreateDirectory(backupdir+"\\Control",NULL);
	CreateDirectory(securedir+"\\Archive",NULL);
	CreateDirectory(backupdir+"\\Archive",NULL);
	CopyFile(datadir+"\\Exercice.dat",securedir+"\\Data\\Exercice.dat",FALSE);
	CopyFile(datadir+"\\Exercice.dat",backupdir+"\\Data\\Exercice.dat",FALSE);
	CTime reftim(yr,atoi(exermois),1,8,0,0,-1);
	temp=reftim.Format(" date de référence : %d/%m/%Y %H:%M:%S");
	initavert0="Votre mois de début d'exercice";
	initavert1="Intégration de vos anciens fichiers en cours";
	initavert2="Veuillez patienter...";
	av1.SetWindowText(initavert0);
	av2.SetWindowText(initavert1);
	av3.SetWindowText(initavert2);
	//RedrawWindow(0,0,1|256|4);
	result=cff.FindFile(datadir+"\\*.*",0);
	tl.ResetContent();
	sl.ResetContent();
	dl.ResetContent();
	while(result)
	{
		result=cff.FindNextFile();
		if (cff.IsDots())
		 continue;
		if (cff.IsDirectory())
		{
			sl.AddString(cff.GetFileName());
			nbfile++;
		}
	}
	cff.Close();
	RedrawWindow(0,0,1|256|4);
	pimp.SetRange(0,nbfile+1);
	pimp.SetStep(1);
	pimp.CenterWindow();
	pimp.ShowWindow(1);
	for(i=0;i<sl.GetCount();i++)// Analyse des dates d'ouvertures périodes
	{
		sl.GetText(i,spath);
		temp=spath;//.Mid(spath.ReverseFind('\\')+1);
		CTime scantim(atoi(temp.Left(4)),atoi(temp.Mid(4,2)),atoi(temp.Mid(6,2)),atoi(temp.Mid(8,2)),atoi(temp.Mid(10,2)),atoi(temp.Mid(10,2)),-1);
		if(scantim<reftim)
		{
			for(j=1;j<30;j++)
			{
				CTime reftim1(reftim.GetYear()-j,atoi(exermois),1,8,0,0,-1);
				if(scantim>reftim1)
				{
					ant.Format("%u",reftim1.GetYear());
					if((idal=dl.FindStringExact(-1,ant))==LB_ERR)
					{
						CreateDirectory(securedir+"\\Archive",NULL);// Création répertoire archive
						CreateDirectory(backupdir+"\\Archive",NULL);// Création répertoire archive
						CreateDirectory(archdir+"\\"+ant,NULL);// Création répertoire archive de l'année
						CreateDirectory(archdir+"\\"+ant+"\\Data",NULL);// Création répertoire archive de l'année
						CreateDirectory(securedir+"\\Archive\\"+ant,NULL);// Création répertoire archive de l'année
						CreateDirectory(securedir+"\\Archive\\"+ant+"\\Data",NULL);// Création répertoire archive de l'année
						CreateDirectory(backupdir+"\\Archive\\"+ant,NULL);// Création répertoire archive de l'année
						CreateDirectory(backupdir+"\\Archive\\"+ant+"\\Data",NULL);// Création répertoire archive de l'année
						idal=dl.AddString(ant);
						st="Exercice file "+ant+"\r\n";
						st+=tim.Format("Open %d/%m/%Y %H:%M:%S");
						st+="\r\n";
						temp2=ant+"\r\n";
						CWrite(sysdir+"\\csat.avs",temp2,1);
						CWrite(archdir+"\\"+ant+"\\Data\\Exercice.dat",st,0);				
						CopyFile(archdir+"\\"+ant+"\\Data\\Exercice.dat",securedir+"\\Archive\\"+ant+"\\Data\\Exercice.dat",FALSE);				
						CopyFile(archdir+"\\"+ant+"\\Data\\Exercice.dat",backupdir+"\\Archive\\"+ant+"\\Data\\Exercice.dat",FALSE);				
					}
					dl.SetItemData(idal,j);
					tdir=archdir+"\\"+ant+"\\Data\\"+spath;
					sdir=securedir+"\\Archive\\"+ant+"\\Data\\"+spath;
					xdir=backupdir+"\\Archive\\"+ant+"\\Data\\"+spath;
					CreateDirectory(tdir,NULL);// Création répertoire archive de l'année
					CreateDirectory(sdir,NULL);// Création répertoire archive de l'année
					CreateDirectory(xdir,NULL);// Création répertoire archive de l'année
					idl=tl.AddString(tdir);
					if(CopyFile(datadir+"\\"+spath+"\\Concert.dat",tdir+"\\Concert.dat",FALSE)&&
						CopyFile(datadir+"\\"+spath+"\\Concert.dat",sdir+"\\Concert.dat",FALSE)&&
						CopyFile(datadir+"\\"+spath+"\\Concert.dat",xdir+"\\Concert.dat",FALSE))
					{
						tl.SetItemData(idl,1);
					}
					else
					{
						MessageBox("Erreur de copie du fichier "+spath);
						tl.SetItemData(idl,0);
					}
					sl.SetItemData(i,tl.GetItemData(idl));
					//if(tl.GetItemData(idl)!=0)
					{
						tl.GetText(idl,tpath);
						buf=CRead(tdir);
						if(buf=="")
						{
							stc="Corrompu";
							corerror++;
						}
						else
						{
							FillTicketList(tdir);
							
							x=0;
							while(x<10)
							{
								k=0;
								while(k<10)
								{
									if(tvaca[x]==xtvaca[k][j])
									{
										xcatva[k][j]+=catva[x];
										break;
									}
									else
									{
										while(k<10)
										{
											if(xtvaca[k][j]==0)
											{
												xtvaca[k][j]=tvaca[x];
												xcatva[k][j]+=catva[x];
												break;
											}
											k++;
										}
										break;
									}
								}
								x++;
							}
							idx=buf.Find("Close",0);
							idy=buf.Find("\r\n",idx);
							temp1=buf.Mid(idx,idy-idx);
							temp1.Replace("GTZ","GTP");
							temp1.Replace("RAZ","NGTZ");
							if(cesver<459)
								idy=buf.Find("GTZ",idx);
							else
								idy=buf.Find("GTP",idx);
							idx=idy+4;
							idy=buf.Find("\r\n",idx);
							gtp=buf.Mid(idx,idy-idx);
							tmp=atof(gtp);
							if(tmp>cumulp[j])
								cumulp[j]=tmp;
							//idx=temp1.Find("NGTZ",0);
							stc=temp1+" GTZ "+txtsca;

							/*idx+=5;
							idy=temp1.Find("GTP",idx)-1;
							ngtz=temp1.Mid(idx,idy-idx);
							stc=ngtz+";"+txtsca+";"+gtp;*/
							for(x=0;x<10;x++)
							{
								if(tvaca[x]>0)
								{
									temp.Format("%.2f",tvaca[x]);
									temp1.Format("%.2f",catva[x]);
									stc+=";"+temp+";"+temp1;
								}
							}
						}
						st=spath+";"+stc+"\r\n";
						CWrite(archdir+"\\"+ant+"\\Data\\Exercice.dat",st,1);
						CopyFile(archdir+"\\"+ant+"\\Data\\Exercice.dat",securedir+"\\Archive\\"+ant+"\\Data\\Exercice.dat",FALSE);
						CopyFile(archdir+"\\"+ant+"\\Data\\Exercice.dat",backupdir+"\\Archive\\"+ant+"\\Data\\Exercice.dat",FALSE);
					}
					cumul=0;
					for(x=0;x<10;x++)
						cumul+=xcatva[x][j];
					break;
				}
			}
		}
		else
		{	// exercice en cours
			if(fcours==0)
			{
				fcours=1;
			}
			j=0;
			sl.SetItemData(i,10);
			tdir=datadir+"\\"+spath;
			buf=CRead(tdir);
			if(buf=="")
			{
				stc="Corrompu";
				corerror++;
			}
			else
			{	// récupération date de cloture
				FillTicketList(tdir);
				
				x=0;
				while(x<10)
				{
					k=0;
					while(k<10)
					{
						if(tvaca[x]==xtvaca[k][j])
						{
							xcatva[k][j]+=catva[x];
							break;
						}
						else
						{
							while(k<10)
							{
								if(xtvaca[k][j]==0)
								{
									xtvaca[k][j]=tvaca[x];
									xcatva[k][j]+=catva[x];
									break;
								}
								k++;
							}
							break;
						}
					}
					x++;
				}
				idx=buf.Find("Close",0);
				idy=buf.Find("\r\n",idx);
				temp1=buf.Mid(idx,idy-idx);
				temp1.Replace("GTZ","GTP");
				temp1.Replace("RAZ","NGTZ");
				if(cesver<459)
					idy=buf.Find("GTZ",idx);
				else
					idy=buf.Find("GTP",idx);

				idx=idy+4;
				idy=buf.Find("\r\n",idx);
				gtp=buf.Mid(idx,idy-idx);
				tmp=atof(gtp);
				if(tmp>cumulp[j])
					cumulp[j]=tmp;
				stc=temp1+" GTZ "+txtsca;
				for(x=0;x<10;x++)
				{
					if(tvaca[x]>0)
					{
						temp.Format("%.2f",tvaca[x]);
						temp1.Format("%.2f",catva[x]);
						stc+=";"+temp+";"+temp1;
					}
				}

			}
			st=spath+";"+stc+"\r\n";
			if(idx!=-1)
			{	// remplissage fichier exercice avec périodes trouvées
				CWrite(datadir+"\\Exercice.dat",st,1);
				CopyFile(datadir+"\\Exercice.dat",securedir+"\\Data\\Exercice.dat",FALSE);
				CopyFile(datadir+"\\Exercice.dat",backupdir+"\\Data\\Exercice.dat",FALSE);
			}
		}
		pimp.StepIt();
		Sleep(20);
	}
	if(sl.GetCount()>0)
	{
		temp2.Format("%u",catidx);
		WriteConfigString("Infocert","Catidx",temp2);
	}
//Close 24/06/2015 16:54:07 NGTZ 2 GTP 95.00 GTZ 10.00 GTA 10.00;20.00%;1.67|HwDnQyrlUkmW4eF3xN8ARPD1YlRHfsZjFTyuQU3PPjXEFh_WlN0iuaqO2STx_Q_Mdg74DzOktgWCT_PUK4yYPeCAXBtPsoq91Sq5tjN4cEPA9MFAm_w3aSRqanXTDtrSpPcdScst4nHfoi0Kh3Jncc_GGcpgX08IyxAXDlt6gYc1igIiJGlzTZoBc1f-KxZrow3qas8tZiT9o-rdldq-EKVzYB5ozfiIwzkhFAJkmvRrr70NKZeXLtdEogmA_eJLj28jWt_VYoxzXb6oXs-5_UiWbqkmWqxFbPzswIauHIAhSWr_eEF-wqYiJl8L1VgH--nVH1igcuojA2Zb2ehzpw==
	temp2="Cat file\r\n";
	CWrite(sysdir+"\\csat.avs",temp2,0);

	for(i=0;i<dl.GetCount();i++)// Fermeture des périodes annuelles
	{
		dl.GetText(i,ant);
		idal=(int)dl.GetItemData(i);
		cumul=0;
		for(x=0;x<10;x++)
			cumul+=xcatva[x][idal];
		st=tim.Format("Close %d/%m/%Y %H:%M:%S ");
		st+="NGTZ "+ant+";";// cumul grand total exercice
		temp1.Format("GTP %.2f",cumulp[idal]);
		st+=" "+temp1;// cumul grand total perpétuel
		temp1.Format("GTZ %.2f",cumul);
		st+=" "+temp1;// cumul grand total annuel 
		temp1.Format("GTA %.2f",GTE);
		st+=" "+temp1;// cumul grand total annuel précédent
		temp1.Format("%u",(int)(cumul*100));
		WriteConfigString("Param","GTE",temp1);// Mise en mémoire de la période annuelle
		for(x=0;x<10;x++)
		{
			if(xcatva[x][idal]>0)
			{
				temp.Format("%.2f",xtvaca[x][idal]);
				temp1.Format("%.2f",xcatva[x][idal]);
				st+=";"+temp+"%;"+temp1;
			}
		}		
		temp2=ant+"\r\n";
		CWrite(sysdir+"\\csat.avs",temp2,1);
		st=st+"\r\n";
		CWrite(archdir+"\\"+ant+"\\Data\\Exercice.dat",st,1);
		CopyFile(archdir+"\\"+ant+"\\Data\\Exercice.dat",securedir+"\\Archive\\"+ant+"\\Data\\Exercice.dat",FALSE);
		CopyFile(archdir+"\\"+ant+"\\Data\\Exercice.dat",backupdir+"\\Archive\\"+ant+"\\Data\\Exercice.dat",FALSE);
		result=cff.FindFile(archdir+"\\"+ant+"\\Data\\*.*",0);
		while(result)
		{
			result=cff.FindNextFileA();
			if(cff.IsDots())
				continue;
			if(cff.IsDirectory())
			{
				temp2.Format("%u;",catidx);
				temp2+="\\Data\\"+cff.GetFileName()+"\\Concert.dat;";
				if((hf=CreateFile(cff.GetFilePath()+"\\Concert.dat",GENERIC_READ,0,NULL,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL)))
				{
					fi=GetTimeSizeInfo(hf);
					CloseHandle(hf);
					filesize.Format("%u",fi.size);	
					filetime.Format("%lld",fi.time);
					temp2+=filesize+";"+filetime+"\r\n";
					CWrite(sysdir+"\\csat.avs",temp2,1);
					catidx++;
				}
				continue;
			}
			temp2.Format("%u;",catidx);
			temp2+="\\Data\\"+cff.GetFileName()+";";
			if((hf=CreateFile(cff.GetFilePath(),GENERIC_READ,0,NULL,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL))!=INVALID_HANDLE_VALUE)
			{
				fi=GetTimeSizeInfo(hf);
				CloseHandle(hf);
				filesize.Format("%u",fi.size);	
				filetime.Format("%lld",fi.time);
				temp2+=filesize+";"+filetime+"\r\n";
				CWrite(sysdir+"\\csat.avs",temp2,1);
				catidx++;
			}
		}
		cff.Close();
	}
	idx=0;
	for(i=0;i<sl.GetCount();i++)// Suppression des fichiers et répertoires déplacés
	{
		sl.GetText(i,temp);		
		if(sl.GetItemData(i)!=0&&sl.GetItemData(i)!=10)
		{
			DeleteFile(datadir+"\\"+temp+"\\Concert.dat");
			DeleteFile(securedir+"\\Data\\"+temp+"\\Concert.dat");
			DeleteFile(backupdir+"\\Data\\"+temp+"\\Concert.dat");
			RemoveDirectory(datadir+"\\"+temp);
			RemoveDirectory(securedir+"\\Data\\"+temp);
			RemoveDirectory(backupdir+"\\Data\\"+temp);
		}
		else
			if(sl.GetItemData(i)==0)
				coperror++;
	}
	temp2=dexer+"\r\n";
	CWrite(sysdir+"\\csat.avs",temp2,1);
	result=cff.FindFile(datadir+"\\*.*",0);
	while(result)
	{
		result=cff.FindNextFileA();
		if(cff.IsDots())
			continue;
		if(cff.IsDirectory())
		{
			temp2.Format("%u;",catidx);
			temp2+="\\Data\\"+cff.GetFileName()+"\\Concert.dat;";
			if((hf=CreateFile(cff.GetFilePath()+"\\Concert.dat",GENERIC_READ,0,NULL,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL))!=INVALID_HANDLE_VALUE)
			{
				fi=GetTimeSizeInfo(hf);
				CloseHandle(hf);
				filesize.Format("%u",fi.size);	
				filetime.Format("%lld",fi.time);
				temp2+=filesize+";"+filetime+"\r\n";
				CWrite(sysdir+"\\csat.avs",temp2,1);
				catidx++;
			}
			continue;
		}
	}
	cff.Close();
	sexer.ShowWindow(0);
	pimp.ShowWindow(0);
	initavert0="Vos anciens fichiers ont été intégrés";
	st.Format("%u",corerror);
	temp.Format("%u",coperror);
	if(coperror>0&&corerror==0)
		initavert1=temp+" erreur de copie de fichier";
	else
		if(corerror>0&&coperror==0)
			initavert1=st+" fichier corrompus";
		else
			if(corerror>0&&coperror>0)
				initavert1=st+" fichier corrompu et "+temp+" erreur de copie de fichier";
			else
				initavert1="Aucune erreur détectée";
	if(corerror>0||coperror>0)
	{
		initavert2="Veuillez contacter votre revendeur pour une maintenance";
		FonctionEditeur("Intégration des anciens fichiers avec des erreurs");
	}
	else
	{
		FonctionEditeur("Intégration des anciens fichiers sans erreurs");

	}
	InterlockedExchange(&fexeran,0);
	wsel=0;
	RedrawWindow(0,0,1|256|4);
	av1.SetWindowText(initavert0);
	av2.SetWindowText(initavert1);
	av3.SetWindowText(initavert2);
	Sleep(5000);
}

void CConcertoDlg::OnBnClickedLogo()
{
	CFileFind ff;
	int i;
	char ch='D';
	CString temp;
	CString ftxt;
	dirlist.ResetContent();
	CGal gal;
	if(!master)
		gal.mode=0;
	else
		gal.mode=2;
	INT_PTR result;
	ftxt=netcontdir;
	FindTypeFile(ftxt,"jpg");
	FindTypeFile(ftxt,"bmp");
	result=gal.DoModal();
	if(result==IDOK&&gal.selfile>=0)
	{
		dirlist.GetText(gal.selfile,logopath);
		if(logopath.Find(".jpg",0))
		{
			if(master)
				CopyFile(workdir+logopath,workdir+"\\Logo.jpg",FALSE);
			else
			{
				CopyFile(logopath,workdir+"\\Logo.jpg",FALSE);
				temp=logopath;
				temp.Replace("\\\\","");
				i=temp.Find("\\",0);
				temp=temp.Mid(i);
				CopyFile(logopath,workdir+temp,FALSE);
				logopath=temp;
			}
		}

		if(logopath.Find(".bmp",0))
		{
			if(master)
				CopyFile(workdir+logopath,workdir+"\\Logo.bmp",FALSE);	
			else
			{
				CopyFile(logopath,workdir+"\\Logo.bmp",FALSE);	
				temp=logopath;
				temp.Replace("\\\\","");
				i=temp.Find("\\",0);
				temp=temp.Mid(i);
				CopyFile(logopath,workdir+temp,FALSE);
				logopath=temp;			
			}
		}
		PrintIdent();
	}
	else
	{
		if(result==IDOK&&gal.selfile<0)
		{
			DeleteFile(workdir+"\\Logo.jpg");
			DeleteFile(workdir+"\\Logo.bmp");
			logopath="";
			PrintIdent();
		}
	}
	WriteConfigString("Param","LogoPath",logopath);
}
	
void CConcertoDlg::FindTypeFile(CString dir,CString ext)	
{	
	BOOL result;
	CFileFind ff;
	result=ff.FindFile(dir+"\\*.*",0);
	CString temp;
	while(result)
	{
		result=ff.FindNextFile();
		if (ff.IsDots())
		 continue;
		if (ff.IsDirectory())
		{
			FindTypeFile(ff.GetFilePath(),ext);
			continue;
		}
		if(ff.GetFileName().Find(ext,0)!=-1)
		{
			temp=ff.GetFilePath();
			if((master&&ff.GetFilePath().Find(workdir,0)!=-1))
				temp.Replace(workdir,"");
			dirlist.AddString(temp);
		}
	}
	ff.Close();	
}

void CConcertoDlg::OnBnClickedBprinter()
{
	CString temp;
	CloseKeyboard();
	if(fadmin)
	{
		Maintenance("Administration imprimante");
		STARTUPINFO csui;
		ZeroMemory( &csui, sizeof(csui) );
		csui.cb = sizeof(csui);
		ZeroMemory( &printcpi, sizeof(printcpi) );
		CString temp;
		GetStartupInfo(&csui);
		temp="control.exe printers";
		CreateProcess(NULL,temp.GetBuffer(),NULL,NULL,FALSE,NORMAL_PRIORITY_CLASS,NULL,NULL,&csui,&printcpi);
		//SetWindowPos(&wndBottom,0,0,0,0,SWP_NOSIZE|SWP_NOMOVE);
		SetTimer(4,500,NULL);
		bprinter.EnableWindow(0);
	}
}

void CConcertoDlg::OnBnClickedBnet()
{
	CString temp;
	CString sysdir;
	CloseKeyboard();
	STARTUPINFO csui;
	PROCESS_INFORMATION cpi;
	OSVERSIONINFO VersionInfo;
	VersionInfo.dwOSVersionInfoSize=sizeof(OSVERSIONINFO);
	CWnd* pwnd;
	GetVersionEx(&VersionInfo);
	if(fadmin)
	{
		Maintenance("Administration réseau");
		ZeroMemory( &csui, sizeof(csui) );
		csui.cb = sizeof(csui);
		ZeroMemory( &cpi, sizeof(cpi) );
		GetStartupInfo(&csui);
		temp.ReleaseBuffer(GetWindowsDirectory(temp.GetBuffer(MAX_PATH),MAX_PATH));
		temp+="\\explorer.exe";
		CreateProcess(NULL,temp.GetBuffer(),NULL,NULL,FALSE,NORMAL_PRIORITY_CLASS,NULL,NULL,&csui,&cpi);
		CloseHandle(cpi.hProcess);
		CloseHandle(cpi.hThread);
		ZeroMemory( &csui, sizeof(csui) );
		csui.cb = sizeof(csui);
		ZeroMemory( &netcpi, sizeof(netcpi) );
		CString temp;
		GetStartupInfo(&csui);
		sysdir.ReleaseBuffer(GetSystemDirectory(sysdir.GetBuffer(MAX_PATH),MAX_PATH));
		temp="Control.exe /name Microsoft.NetworkAndSharingCenter";
		CreateProcess(NULL,temp.GetBuffer(),NULL,NULL,FALSE,NORMAL_PRIORITY_CLASS,NULL,NULL,&csui,&netcpi);
		//SetWindowPos(&wndBottom,0,0,0,0,SWP_NOSIZE|SWP_NOMOVE);
		SetTimer(5,8000,NULL);
		Klance();
		bnet.EnableWindow(0);
		bprinter.EnableWindow(0);
		Sleep(1000);
		if((pwnd=FindWindow("Shell_TrayWnd",0))!= NULL)
			pwnd->ShowWindow(0);
		if((pwnd=FindWindow("Button",txtc[2]))!=NULL)//Démarrer
			pwnd->ShowWindow(0);
	}
}

void CConcertoDlg::OnBnClickedBcode()
{
	CMessage* pdlg;
	CNum* pnum;
	CString codetemp;
	CString temp1;
	CString temp;
	CloseKeyboard();
	{
RETRY_CODE:;
		pnum=new CNum();
		pnum->wlargeur=(int)((float)(wlargeur/2));
		pnum->whauteur=whauteur/3;
		pnum->nID=0;
		if(fadmin==1)
			pnum->chiffre = 7;
		else
			pnum->chiffre = 6;
		pnum->mode=4;
		pnum->nombre="";
		if(fadmin==1)
			temp1=txtm[93];//Votre code revendeur
		else
			temp1=txtm[24];//Votre code manager
		pnum->txtmessage=temp1;//"Votre code revendeur/manager"
		pnum->DoModal();
		if((pnum->nombre.GetLength()<4&&(fadmin==0||fadmin==2)||(pnum->nombre.GetLength()<7&&fadmin==1)||(pnum->nombre==codeuser&&(fadmin==0||fadmin==2))))
		{
			pnum->DestroyWindow();
			delete(pnum);
			pdlg=new CMessage();
			if(fadmin==1)
				temp1=txtm[25];//Votre code doit comporter 7 caractères
			else
				temp1=txtm[26];//Votre code doit comporter 4 caractères
			pdlg->mes1=temp1;
			temp1=txtm[27];//Voulez-vous recommencer ?
			pdlg->mes2=temp1;
			pdlg->mes3="";
			pdlg->mode=0;
			if(pdlg->DoModal()==IDCANCEL)
			{
				pdlg->DestroyWindow();
				delete(pdlg);
				goto ABORT_CODE;
			}
			else
			{
				pdlg->DestroyWindow();
				delete(pdlg);
				goto RETRY_CODE;
			}
		}
		else
		{
			codetemp=pnum->nombre;
			pnum->DestroyWindow();
			delete(pnum);
		}
		pnum=new CNum();
		pnum->wlargeur=(int)((float)(wlargeur/2));
		pnum->whauteur=whauteur/3;
		pnum->nID=0;
		if(fadmin==1)
			pnum->chiffre = 7;
		else
			pnum->chiffre = 6;
		pnum->mode=4;
		pnum->nombre="";
		temp1=txtm[28];//"Confirmer votre code"
		pnum->txtmessage=temp1;
		pnum->DoModal();
		if(pnum->nombre!=codetemp)
		{
			pnum->DestroyWindow();
			delete(pnum);
			pdlg=new CMessage();
			temp1=txtm[29];
			pdlg->mes1=temp1;//"Votre code est incorrect"
			temp1=txtm[30];	
			pdlg->mes2=temp1;//Voulez-vous recommencer ?
			pdlg->mes3="";
			pdlg->mode=0;
			if(pdlg->DoModal()==IDCANCEL)
			{
				pdlg->DestroyWindow();
				delete(pdlg);
				goto ABORT_CODE;
			}
			else
			{
				pdlg->DestroyWindow();
				delete(pdlg);
				goto RETRY_CODE;
			}
		}
		else
		{
			if(fadmin==1)
			{
				WriteConfigString("Code","Revendeur",codetemp);
				codereseller=codetemp;
			}
			else
			{
				WriteConfigString("Code","ManagerCode",codetemp);
				codemanager=codetemp;
			}
			pnum->DestroyWindow();
			delete(pnum);
		}
	}
ABORT_CODE:;

}
void CConcertoDlg::OnBnClickedBuser()
{
	CMessage* pdlg;
	CNum* pnum;
	CString codetemp;
	CString temp;
	CString temp1;
	if(!fadmin)
	{
		CloseKeyboard();
RETRY_CODE:;
		pnum=new CNum();
		pnum->wlargeur=(int)((float)(wlargeur/2));
		pnum->whauteur=whauteur/3;
		pnum->nID=0;
		pnum->chiffre = 6;
		pnum->mode=4;
		pnum->nombre="";
		temp1=txtm[31];//"Votre code utilisateur"
		pnum->txtmessage=temp1;
		pnum->nombre="";
		pnum->DoModal();
		if(pnum->nombre.GetLength()<4||pnum->nombre==codemanager)
		{
			pnum->DestroyWindow();
			delete(pnum);
			pdlg=new CMessage();
			temp1=txtm[26];//"Votre code doit comporter 4 caractères";
			pdlg->mes1=temp1;
			temp1=txtm[30];//"Voulez-vous recommencer ?";
			pdlg->mes2=temp1;
			pdlg->mes3="";
			pdlg->mode=0;
			if(pdlg->DoModal()==IDCANCEL)
			{
				pdlg->DestroyWindow();
				delete(pdlg);
				goto ABORT_CODE;
			}
			else
			{
				pdlg->DestroyWindow();
				delete(pdlg);
				goto RETRY_CODE;
			}
		}
		else
		{
			codetemp=pnum->nombre;
			pnum->DestroyWindow();
			delete(pnum);
		}
		pnum=new CNum();
		pnum->wlargeur=(int)((float)(wlargeur/2));
		pnum->whauteur=whauteur/3;
		pnum->nID=0;
		pnum->chiffre = 6;
		pnum->mode=4;
		pnum->nombre="";
		temp1=txtm[28];	//"Votre code utilisateur"
		pnum->txtmessage=temp1;
		pnum->nombre="";
		pnum->DoModal();
		if(pnum->nombre!=codetemp)
		{
			pnum->DestroyWindow();
			delete(pnum);
			pdlg=new CMessage();
			temp1=txtm[29];	//"Votre code est incorrect";
			pdlg->mes1=temp1;
			temp1=txtm[30];//"Voulez-vous recommencer ?";
			pdlg->mes2=temp1;
			pdlg->mes3="";
			pdlg->mode=0;
			if(pdlg->DoModal()==IDCANCEL)
			{
				pdlg->DestroyWindow();
				delete(pdlg);
				goto ABORT_CODE;
			}
			else
			{
				pdlg->DestroyWindow();
				delete(pdlg);
				goto RETRY_CODE;
			}
		}
		else
		{
			pnum->DestroyWindow();
			delete(pnum);
			WriteConfigString("Code","UserCode",codetemp);
			codeuser=codetemp;
		}
ABORT_CODE:;
	}
	/*else
	{
		if(master&&fadmin)
		{
			for(int i=0;i<20;i++)
			{
				temp.Format("%u",i);
				AfxGetApp()->WriteProfileString("Prix",temp,"");
				pl.ResetContent();
			}
			FART=1;
			RefreshArticle();
		}
	}*/
}


void CConcertoDlg::OnStnClickedSan()
{
	CString temp;
	CloseKeyboard();
	CCombo dlg;
	sdl.ResetContent();
	sdl.AddString(dexer);
	CFileFind cff;
	BOOL result=cff.FindFile(archdir+"\\*.*",0);
	while(result)
	{
		result=cff.FindNextFileA();
		if(cff.IsDirectory()&&!cff.IsDots())
			sdl.AddString(cff.GetFileName());
	}		
	san.GetWindowRect(&dlg.rctstat);
	dlg.rctstat.top=dlg.rctstat.bottom;
	dlg.winh=(int)(htou/4);
	dlg.type=4;
	dlg.DoModal();
	if(dlg.sel>=0)
	{
		sdl.GetText(dlg.sel,temp);
		san.SetWindowTextA(temp);
		if(temp==dexer)
			searchdir=datadir;
		else
			searchdir=archdir+"\\"+temp+"\\data";
		searchan=temp;
		FillCessionList();
	}
}

void CConcertoDlg::OnStnClickedSmois()
{
	CString temp;
	CloseKeyboard();

	smois.GetWindowText(libelsave);
	smois.SetWindowText("");
	CNum dlg;
	dlg.mode=1;
	dlg.pw=0;
	dlg.wlargeur=(int)((float)(wlargeur/2));
	dlg.whauteur=whauteur/3;
	dlg.nID=IDC_SMOIS;
	dlg.chiffre=2;
	if(dlg.DoModal()==IDOK)
	{
		smois.GetWindowTextA(searchmois);
		FillCessionList();
	}
}
void CConcertoDlg::OnBnClickedBureau()
{
	CString temp;
	CString temp1;
	CString temp2;
	int idx;
	if(fadmin)
	{
		CloseKeyboard();		
		InterlockedExchange(&QUIT,1);
		InterlockedExchange(&END,1);
		InterlockedExchange(&STOP,1);
		BackupConcertRegistry();
		BackupConcertControl();
		if(backupdir!="")
		{	// on sauvegarde sur la clé le fichier clôturé
			if(CopyFile(securedir+"\\Concert.bra",backupdir+"\\Concert.bra",FALSE)==0)
				MessageBox("Erreur de sauvegarde X");
		}
		if(infocert)
		{
			temp1=txtm[1];//Disque de sauvegarde absent!
			temp2=txtm[2];//Veuillez contacter votre revendeur.
			
			Maintenance("Sortie sur le bureau Windows");
			temp.Format("%u",auditfile);
			if(CopyFile(workdir+"\\Auditinfo"+temp+".dat",backupdir+"\\Auditinfo"+temp+".dat",FALSE)==0)
			{
				MessageBox(temp1+"\n"+temp2);
			}
			if(CopyFile(workdir+"\\Auditinfo"+temp+".dat",securedir+"\\Auditinfo"+temp+".dat",FALSE)==0)
			{
				MessageBox(temp1+"\n"+temp2);
			}
		}
		if(CONTROL)
		{
			InterlockedExchange(&CONTROL,0);
			if(scaninter=="BLUE")
				InterlockedExchange(&BASCULE,0);
		}
		if(scaninter=="BLUE")
		{
			temp="---\r\n";
			SendRS(temp);
		}
		Sleep(500);
		for(idx=0;idx<9;idx++)
		{
			TerminateThread(hRNThread[idx],0);
			CloseHandle(hRNThread);
		}
		TerminateThread(hRSGateReadThread,0);
		CloseHandle(hRSGateReadThread);
		TerminateThread(hRSReadThread,0);
		CloseHandle(hRSReadThread);
		TerminateThread(hRSSearchThread,0);
		CloseHandle(hRSSearchThread);
		DeleteFile(controldir+"\\Status.dat");		
		TerminateThread(hRSScanThread,0);
		CloseHandle(hRSScanThread);
		CloseHandle(HRS);
		TerminateThread(hwpt,0);
		TerminateThread(hpjt,0);
		TerminateThread(hsjt,0);
		CloseHandle(hwpt);		
		CloseHandle(hpjt);
		CloseHandle(hsjt);
		OnOK();
	}
}

void CConcertoDlg::OnBnClickedRaz()
{
	CZipArchive zip;
	CString temp;
	CString temp1;
	int sec;
	CNum* pnum;
	CMessage* pdlg;
	//CFileFind ff;
	//CFileFind cff;
	CTime tim=CTime::GetCurrentTime();
	CString date=tim.Format("%Y%m%d");
	sec=atoi(date)+1020304;
	date.Format("%u",sec);
	CString dir;
	CString dirc;
	int wdg;
	if(fadmin==1)
	{
		wdg=0;
retry_code:;
		pnum=new CNum();
		if(!fdev)
		{
			pnum->wlargeur=(int)((float)(wlargeur/2));
			pnum->whauteur=whauteur/3;
			pnum->nID=0;
			pnum->txtmessage=txtm[39];//"Entrer votre code";
			pnum->mode=4;
			pnum->nombre="";
			pnum->chiffre=9;
			pnum->DoModal();
		}
		else
			pnum->nombre=codeadmin;
		if(pnum->nombre==codeadmin) 
		{
			pnum->DestroyWindow();
			delete(pnum);
			pdlg=new CMessage();

			user="administrateur";
			Habilitation("Accès RAZ machine "+user);
			temp1=txtm[33];//Vous allez effacer toutes les données !
			pdlg->mes1=temp1;
			temp1=txtm[34];//;"Est-ce vraiment votre intention?"
			pdlg->mes2=temp1;
			temp1=txtm[35];//;"Si oui vous devrez réentrer votre code."
			pdlg->mes3=temp1;
			pdlg->mode=0;
			if(pdlg->DoModal()==IDOK)
			{
				pdlg->DestroyWindow();
				delete(pdlg);
				wdg=0;
retry_code_super:;
				pnum=new CNum();
				if(!fdev)
				{
					temp=txtm[39];//"Entrer votre code";
					pnum->wlargeur=(int)((float)(wlargeur/2));
					pnum->whauteur=whauteur/3;
					pnum->nID=0;
					pnum->txtmessage=temp;
					pnum->mode=4;
					pnum->nombre="";
					pnum->chiffre=9;
					pnum->DoModal();
				}
				else
					pnum->nombre=coderazadmin;
				if(pnum->nombre==coderazadmin)
				{
					pnum->DestroyWindow();
					delete(pnum);
					CTime tim=CTime::GetCurrentTime();
					temp=tim.Format("%Y%m%d %H%M%S");
					temp="D:\\RAZ "+nom+" du "+temp;
					//CreateDirectory(temp,NULL);
					zip.Open(temp+".zip", CZipArchive::zipCreate);
					temp=tim.Format("%Y%m%d%H%M%S");
					if(hrun)// Ferme le fichier run.dat et l'efface avant la sauvegarde
					{
						if(CloseHandle(hrun))
						{
							hrun=NULL;
							DeleteFile(controldir+"\\Run.dat");
						}
					}

					Sauvegarde(temp);
					zip.SetPassword("65748392",-1);
					zip.SetEncryptionMethod(CZipCryptograph::encWinZipAes256);
					if(zip.AddNewFiles(workdir,"*.*",true,-1,false, zip.zipsmSafeSmart, 65536))
					{
						if(zip.AddNewFiles(securedir,"*.*",true,-1,false, zip.zipsmSafeSmart, 65536))
						{
							if(zip.AddNewFiles(backupdir,"*.*",true,-1,false, zip.zipsmSafeSmart, 65536))
							{
								zip.FlushBuffers();
								zip.Close();
							}
							else
							{
								zip.FlushBuffers();
								zip.Close();
								goto ERREUR;
							}
						}
						else
						{
							zip.FlushBuffers();
							zip.Close();
							goto ERREUR;
						}
					}
					else
					{
						zip.FlushBuffers();
						zip.Close();
						goto ERREUR;
					}
					
					int i=0;
					while(i<100)
					{
						temp.Format("T%u",i);
						ntou[i]=1;
						AfxGetApp()->WriteProfileInt("Ntouche",temp,1);
						target[i]=0;
						temp.Format("%u",i);
						AfxGetApp()->WriteProfileInt(temp,"TARGET",0);
						i++;
					}
					i=0;
					while(i<=16)
					{
						ClearControl(i)	;
						i++;
					}
					nbillet=1;
					WriteConfigString("Client","Billet","1");
					WriteConfigString("License","Date",tim.Format("%Y%m%d"));
					if(licstat!="Persistent")
						WriteConfigString("License","Status","Valide");
					WriteConfigString("License","Période","0");
					fsecur=1;
					WriteConfigString("Param","GTT","0.00");
					WriteConfigString("Param","GTP","0");
					WriteConfigString("Param","GTZ","0");
					WriteConfigString("Param","GTA","0");
					GTP=0;
					GTZ=0;
					GTA=0;
					FWEB=0;
					WriteConfigString("Param","NGTZ","0");
					RAZ=0;
					edate="";
					WriteConfigString("Client","eDate",edate);
					econt=0;
					AfxGetApp()->WriteProfileInt("Ntouche","eCont",econt);
					for(i=0;i<=NART;i++)
					{
						temp.Format("%u",i);
						acont[i]=AfxGetApp()->WriteProfileInt("Ntouche","aCont"+temp,0);
					}
					// VIDAGE des Répertoire de données
					DeleteDirectory(datadir,1);
					DeleteDirectory(backupdir,1 );
					DeleteDirectory(securedir,1 );
					DeleteDirectory(workdir+"\\Archive",1);
					DeleteDirectory(controldir,1 );
					DeleteDirectory(securedir,1 );
					DeleteDirectory(backupdir,1 );
					if(master)
					{	// cré un fichier marquant la machine comme maître
						HANDLE hf=CreateFile(controldir+"\\Status.dat",GENERIC_READ|GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
						if(hf!=INVALID_HANDLE_VALUE)
						{
							if(alone)
							{
								DWORD len;
								temp="Alone";
								WriteFile(hf,temp.GetBuffer(temp.GetLength()),temp.GetLength(),&len,NULL);
							}
							CloseHandle(hf);
						}
					}
					CreateDirectory(backupdir+"\\Data",NULL);
					CreateDirectory(backupdir+"\\Archive",NULL);
					CreateDirectory(backupdir+"\\Control",NULL);
					CreateDirectory(securedir+"\\Data",NULL);
					CreateDirectory(securedir+"\\Archive",NULL);
					CreateDirectory(securedir+"\\Control",NULL);
					lprix.ResetContent();
					ldate.ResetContent();
					lcancel.ResetContent();
					smois.SetWindowTextA("");
					san.SetWindowTextA("");
					dopen="";
					WriteConfigString("Param","Ouverture",dopen);
					DeleteFile(datadir+"\\Exercice.dat");
					for(i=1;i<=auditfile;i++)
					{
						temp.Format("%u",i);
						DeleteFile(workdir+"\\Auditinfo"+temp+".dat");
						DeleteFile(backupdir+"\\Auditinfo"+temp+".dat");
						DeleteFile(securedir+"\\Auditinfo"+temp+".dat");
					}
					dexer="";
					catidx=1;
					auditfile=0;
					naudit=1;
					WriteConfigString("Infocert","Naudit",temp);
					WriteConfigString("Infocert","Exercice",dexer);
					WriteConfigString("Infocert","Catidx","1");
					WriteConfigString("Infocert","MoisExercice","00");
					WriteConfigString("Infocert","Auditfile","0");
					WriteConfigString("Infocert","Infotime","");
					WriteConfigString("Infocert","Infosize","");
					WriteConfigString("Infocert","Datatime","");
					WriteConfigString("Infocert","Datasize","");
					WriteConfigString("Infocert","Exertime","");
					WriteConfigString("Infocert","Exersize","");
					WriteConfigString("Infocert","AuditIntégrité","");
					WriteConfigString("Infocert","SignTicket","");
					WriteConfigString("Infocert","SignGtticket","");
					WriteConfigString("Infocert","SignGtpz","");
					WriteConfigString("Infocert","SignGtpa","");
					WriteConfigString("Infocert","SignArchPeriode","");
					WriteConfigString("Infocert","SignArchExercice","");
					WriteConfigString("Infocert","SignArchExport","");
					WriteConfigString("Infocert","SignAudit","");
					WriteConfigString("Param","Spool","");
					sarchd="";
					sarche="";
					sarchp="";
					saudit="";
					sticket="";
					sgtpz="";
					sgtpa="";
					temp=txtm[48];//"La billetterie a été remise à 0";
					pdlg=new CMessage();					
					pdlg->mes1=temp;
					pdlg->mes2=" ";
					pdlg->mes3=" ";
					pdlg->mode=1;
					pdlg->DoModal();
					pdlg->DestroyWindow();
					delete(pdlg);
					total.SetWindowTextA("");
					lcode.ResetContent();
					lqte.ResetContent();
					lptot.ResetContent();
					lsel=-1;
					InterlockedExchange(&artro,0);
					ClearWindow();
					temp="Cat file\r\n";
					CWrite(sysdir+"\\csat.avs",temp,0);
					if(infocert==1)
					{
						StartTerminal();
						VersionLogiciel();
						FonctionEditeur("RAZ machine");
					}
					InterlockedExchange(&fexeran,1);
					int x=(int)((float)wlargeur*15.15/19.5);
					float yohnum=((float)whauteur/10);	
					int slargeur=(int)((float)wlargeur*3.8/19.5);
					int shauteur=(int)((float)whauteur*0.8/27);;
					float sph=9*htou/40;
					CRect titrct(wlargeur/2-wlargeur/20,whauteur/5,wlargeur/10,whauteur/3);
					wsel=0;
					RedrawWindow(0,0,1|256|4);
					initavert0="Veuillez renseigner le mois de début d'exercice";
					initavert1="";
					initavert2="";
					av1.SetWindowText(initavert0);
					av2.SetWindowText(initavert1);
					av3.SetWindowText("");
					//nexer.SetWindowPos(&wndTop,xn,(int)(yohnum+7*sph),largeur,(int)((1.8)*sph),SWP_SHOWWINDOW   );
					sexer.SetWindowPos(&wndTop,(3*wlargeur/4),whauteur/3+whauteur/20,wlargeur/10,whauteur/20,SWP_SHOWWINDOW   );
					sexer.SetFont(&geodate,0);
					sexer.SetWindowText(exermois);
					sexer.EnableWindow(1);
					fraz=1;
					// Recrée le fichier run.dat (marque qu'une application Concert tourne déjà)
					hrun=CreateFile(controldir+"\\Run.dat",GENERIC_READ|GENERIC_WRITE,0,NULL,CREATE_NEW,FILE_ATTRIBUTE_NORMAL,NULL);
					KillTimer(18);
					KillTimer(17);
					FWEB=0;
					OnStnClickedSexer();
				}
				else
				{
					temp=pnum->nombre;
					pnum->DestroyWindow();
					delete(pnum);
					if(temp=="")
						goto FIN;
					user="Echec authentification";
					wdg++;
					if(wdg>5)
					{
						wsel=1;
						OnOK();
						if(!fdev)
						{
							SystemShutdown();
						}
					}
					else
					{
						Habilitation("Accès RAZ machine "+user);
						goto retry_code_super;
					}
				}
			}
			else
			{
				pdlg->DestroyWindow();
				delete(pdlg);
			}
		}
		else
		{
			temp=pnum->nombre;
			pnum->DestroyWindow();
			delete(pnum);
			if(temp=="")
				goto FIN;

			user="Echec authentification";
			wdg++;
			if(wdg>5)
			{
				wsel=1;
				OnOK();
				if(!fdev)
				{
					SystemShutdown();
				}
			}
			else
			{
				Habilitation("Accès RAZ machine "+user);
				goto retry_code;
			}
		}
		goto FIN;
ERREUR:;
		MessageBox("Erreur de sauvegarde de la billetterie\r\nVeuillez recommencer");
		DeleteFile(temp+".zip");
FIN:;
	}
	else
	{
		if(!simul)
			PRMODE=4;
		DisplayCBList();	
	}
}
void CConcertoDlg::OnStnClickedSdevise()
{
	CString temp;
	CCombo dlg;
	if(fadmin&&master&&pays!="FR")
	{
		CloseKeyboard();
		sdevise.GetWindowRect(&dlg.rctstat);
		dlg.rctstat.top=dlg.rctstat.bottom;
		dlg.winh=(int)(htou/4);
		dlg.type=0;
		dlg.DoModal();
		if(dlg.sel>=0)
		{
			ldevise.SetCurSel(dlg.sel);
			ldevise.GetText(dlg.sel,cur);
			sdevise.SetWindowText(cur);
			SaveStaticConfig();
		}
	}
}
void CConcertoDlg::OnStnClickedSlangue()
{
	CString temp;
	CCombo dlg;
	int i;
	if(fadmin&&master&&pays!="FR")
	{
		CloseKeyboard();
		slangue.GetWindowRect(&dlg.rctstat);
		dlg.rctstat.top=dlg.rctstat.bottom;
		dlg.winh=(int)(htou/4);
		dlg.type=1;
		dlg.DoModal();
		if(dlg.sel>=0)
		{
			llangue.SetCurSel(dlg.sel);
			llangue.GetText(dlg.sel,langue);

			slangue.SetWindowText(langue);
			SaveStaticConfig();
			langfile=workdir+"\\"+langue+".lng";
			for(i=1;i<8;i++)
			{
				temp.Format("%u",i);
				jourtxt[i-1].ReleaseBuffer(GetPrivateProfileString("Jour",temp,"",jourtxt[i-1].GetBuffer(100),100,langfile));
			}
			for(i=1;i<TXTC;i++)
			{
				temp.Format("%u",i);
				txtc[i].ReleaseBuffer(GetPrivateProfileString("Controle",temp,"",txtc[i].GetBuffer(100),100,langfile));//"ENTREE PAYANTE"
			}
			for(i=1;i<TXTM;i++)
			{
				temp.Format("%u",i);
				txtm[i].ReleaseBuffer(GetPrivateProfileString("Message",temp,"",txtm[i].GetBuffer(100),100,langfile));//"ENTREE PAYANTE"
			}
			Table[11]=txtc[1];//ENCAISSER
			lcb.ResetContent();
			lcb.AddString(txtc[155]+" "+txtc[154]);
			lcb.AddString(txtc[155]+" "+"ETC");
			lcb.AddString(txtc[155]+" "+"ARBAN");

			ltype.ResetContent();
			ltype.AddString(txtc[144]);
			ltype.AddString(txtc[55]);
			ltype.AddString(txtc[145]);
			DrawWindowConfig();
		}
	}
	// TODO: Add your control notification handler code here
}
void CConcertoDlg::OnStnClickedSpays()
{
	CString temp;
	CCombo dlg;
	if(fadmin&&master)
	{
		CloseKeyboard();
		spays.GetWindowRect(&dlg.rctstat);
		dlg.rctstat.top=dlg.rctstat.bottom;
		dlg.winh=(int)(htou/4);
		dlg.type=3;
		dlg.DoModal();
		if(dlg.sel>=0)
		{
			lpays.SetCurSel(dlg.sel);
			lpays.GetText(dlg.sel,pays);
			spays.SetWindowText(pays);
			if(pays=="FR")
			{
				langue="French";
				langfile=workdir+"\\"+langue+".lng";
				for(int i=1;i<8;i++)
				{
					temp.Format("%u",i);
					jourtxt[i-1].ReleaseBuffer(GetPrivateProfileString("Jour",temp,"",jourtxt[i-1].GetBuffer(100),100,langfile));
				}
				for(int i=1;i<TXTC;i++)
				{
					temp.Format("%u",i);
					txtc[i].ReleaseBuffer(GetPrivateProfileString("Controle",temp,"",txtc[i].GetBuffer(100),100,langfile));//"ENTREE PAYANTE"
				}
				for(int i=1;i<TXTM;i++)
				{
					temp.Format("%u",i);
					txtm[i].ReleaseBuffer(GetPrivateProfileString("Message",temp,"",txtm[i].GetBuffer(100),100,langfile));//"ENTREE PAYANTE"
				}
				Table[11]=txtc[1];//ENCAISSER
				lcb.ResetContent();
				lcb.AddString(txtc[155]+" "+txtc[154]);
				lcb.AddString(txtc[155]+" "+"ETC");
				lcb.AddString(txtc[155]+" "+"ARBAN");

				ltype.ResetContent();
				ltype.AddString(txtc[144]);
				ltype.AddString(txtc[55]);
				ltype.AddString(txtc[145]);
				cur="€";
				infocert=1;
			}
			else
				infocert=0;
			SaveStaticConfig();
			DrawWindowConfig();
		}
	}
	// TODO: Add your control notification handler code here
}
void CConcertoDlg::DeleteDirectory(CString path, int mode)
{
	CFileFind ff;
	BOOL result=ff.FindFile(path+"\\*.*",0 );
	while(result)
	{
		result=ff.FindNextFile();
		if (ff.IsDots())
		 continue;
		if(ff.IsDirectory())
		{
			DeleteDirectory(ff.GetFilePath(),0);
			continue;
		}
		if(ff.GetFileName()!="Logo Dino.jpg"&&ff.GetFilePath()!=workdir+logopath&&ff.GetFilePath()!=workdir+scrpath&&ff.GetFileName()!="Run.dat")
		{
			DeleteFile(ff.GetFilePath());
		}
	}
	ff.Close();
	if(mode==0)
		RemoveDirectory(path);
}
void CConcertoDlg::OnCbnSelchangeLtype()
{
	CString temp;
	CString temp1;
	DWORD len;
	int i=0;
	CloseKeyboard();
	int memmaster=master;
	master=ltype.GetCurSel();
	if(master==0)
	{
		alone=0;
		lnbap.EnableWindow(0);
		lcb.EnableWindow(0);
		if(fprev)
		{
			nvhor.ShowWindow(1);
			nvhor.SetWindowTextA(txtc[54]);//"Horaire"
		}
	}
	else
	{
		if(master==1)
		{
			alone=0;
			for(i=0;i<lmac.GetCount();i++)
			{
				if(lmac.GetItemData(i)==1)
				{
					temp1=txtm[36];
					temp=txtm[68];
					if(MessageBox(temp1+"\n"+temp,0,MB_OKCANCEL)==IDOK)//Un maître existe déjà sur le réseau!
					{													//Rendre autonome ?				
						alone=1;
						ltype.SetCurSel(2);

					}
					else
					{
						alone=0;
						temp.Format("%u",alone);
						WriteConfigString("Client","Alone",temp);
						master=memmaster;
						ltype.SetCurSel(master);					
						goto FIN;
					}
				}
			}
			horaire=1;
			valhor=0;
			lnbap.EnableWindow(1);
			lcb.EnableWindow(1);
			if(fprev)
			{
				nvhor.ShowWindow(1);
				nvhor.SetWindowTextA(txtc[54]);//"Horaire"
			}
		}
		else
			if(master==2)
			{
				alone=1;
				horaire=1;
				valhor=0;
				lnbap.EnableWindow(1);
				lcb.EnableWindow(1);
				if(fprev)
				{
					nvhor.ShowWindow(1);
					nvhor.SetWindowTextA(txtc[54]);//"Horaire"
				}
			}
	}
	if(master)
	{
		if(alone==0)
			tnet.SetWindowTextA("HRSR");
		else
			if(alone==1)
				tnet.SetWindowTextA("HRAU");/**/
	}
	else
		tnet.SetWindowTextA("HRDN");
	temp.Format("%u",alone);
	WriteConfigString("Client","Alone",temp);
	temp.Format("%u",master);
	WriteConfigString("Client","Master",temp);
	temp.Format("%u",horaire);
	WriteConfigString("Client","Horaire",temp);
	temp.Format("%u",valhor);
	WriteConfigString("Client","ValHor",temp);
	if(master)
	{
		HANDLE hf=CreateFile(controldir+"\\Status.dat",GENERIC_READ|GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
		if(hf!=INVALID_HANDLE_VALUE)
		{
			if(alone)
			{
				temp="Alone";
				WriteFile(hf,temp.GetBuffer(temp.GetLength()),temp.GetLength(),&len,NULL);
			}
			CloseHandle(hf);
		}
	}
	else
	{
		alone=0;
		temp.Format("%u",alone);
		WriteConfigString("Client","Alone",temp);
		DeleteFile(controldir+"\\Status.dat");

	}
	DrawBoutonGestion();
FIN:;
}

void CConcertoDlg::OnStnClickedNvalhor()
{
	CString temp;
	if(master)
	{
		CloseKeyboard();		
		if(horaire&&fadmin)
		{
			if(valhor)
			{
				valhor=0;
			}
			else
			{
				valhor=1;
			}
			nvhor.SetWindowText("Horaire");//(Texte traduit dans ControlColor)
			temp.Format("%u",valhor);
			WriteConfigString("Client","ValHor",temp);
			FART=1;
			RefreshArticle();
		}
		else
		{
			nvhor.SetWindowText("Contrôle");//(Texte traduit dans ControlColor)
		}
	}
}
void CConcertoDlg::OnStnClickedNvalplace()
{
	CString temp;
	if(master)
	{
		CloseKeyboard();		
		if(nvalplace)
		{
			nvalplace=0;
		}
		else
		{
			nvalplace=1;
		}
		nvplace.SetWindowText("Place");
		temp.Format("%u",nvalplace);
		WriteConfigString("Client","ValPlace",temp);
		FART=1;
		RefreshArticle();
	}
}
void CConcertoDlg::OnStnClickedNvalmix()
{
	CString temp;
	if(master&&fadmin)
	{
		CloseKeyboard();		
		if(nvalmix)
		{
			nvalmix=0;
		}
		else
		{
			nvalmix=1;
		}
		nvmix.SetWindowText("Pack");
		temp.Format("%u",nvalmix);
		WriteConfigString("Client","ValMix",temp);
		FART=1;
		RefreshArticle();
	}
	else
	{
		if(!fadmin&&afmode)
		{
			CloseKeyboard();		
			if(valscr)
			{
				valscr=0;
			}
			else
			{
				valscr=1;
				CFileFind ff;
				char ch='D';
				CString temp;
				CString ftxt;
				dirlist.ResetContent();
				CGal gal;
				if(master)
					gal.mode=3;
				else
					gal.mode=1;
				INT_PTR result;
				ftxt=netcontdir;
				FindTypeFile(ftxt,"avi");
				FindTypeFile(ftxt,"AVI");
				result=gal.DoModal();
				if(result==IDOK&&gal.selfile>=0)
				{
					dirlist.GetText(gal.selfile,scrpath);
					if(scrpath.Find(".avi",0))
					{
						if(master)
							CopyFile(workdir+scrpath,workdir+"\\scr.avi",FALSE);
						else
							CopyFile(scrpath,workdir+"\\scr.avi",FALSE);
					}
				}
				else
				{
					if(result==IDOK&&gal.selfile<0)
					{
						DeleteFile(workdir+"\\scr.avi");
						scrpath="";
					}
				}
				WriteConfigString("Param","ScrPath",scrpath);
			}
			nvmix.SetWindowText("Veille");
			temp.Format("%u",valscr);
			WriteConfigString("Client","ValScr",temp);
			FART=1;
			RefreshArticle();
		}
	}
}
void CConcertoDlg::OnStnClickedNvalpwd()
{
	CString temp;
	if(master)
	{
		CloseKeyboard();		
		if(valpwd)
		{
			valpwd=0;
		}
		else
		{
			valpwd=1;
		}
		nvpwd.SetWindowText("Pwd");
		temp.Format("%u",valpwd);
		WriteConfigString("Client","ValPwd",temp);
		FART=1;
		RefreshArticle();
	}
}

void CConcertoDlg::OnStnClickedNvalpage()
{
	CString temp;
	if(master)
	{
		CloseKeyboard();		
		if(valpage)
		{
			valpage=0;
		}
		else
		{
			valpage=1;
		}
		nvpage.SetWindowText("Pwd");
		temp.Format("%u",valpage);
		WriteConfigString("Client","ValPage",temp);
		FART=1;
		RefreshArticle();
	}
}

void CConcertoDlg::OnStnClickedNetc()
{
	CString temp;
	if(master)
	{
		if(fadmin)
		{
			CloseKeyboard();		
			if(eflag==1||eflag==0)
			{
				eflag=2;
				buser.ShowWindow(0);
				for(int i=0;i<=NART;i++)
				{
					temp.Format("%u",i);
					acont[i]=AfxGetApp()->GetProfileInt("Ntouche","aCont"+temp,0);
				}
			}
			else
			{
				eflag=1;
				if(master)
					buser.ShowWindow(1);
				econt=0;
				AfxGetApp()->WriteProfileInt("Ntouche","eCont",econt);
			}
			edate="";
			WriteConfigString("Client","eDate",edate);
			netc.SetWindowText("ETC");
			temp.Format("%u",eflag);
			WriteConfigString("Client","Eflag",temp);
			FART=1;
			RefreshArticle();	
		}
	}
	if(!fadmin)
	{
		CloseKeyboard();		
		if(exoflag==1)
		{
			exoflag=0;
		}
		else
		{
			exoflag=1;
		}
		temp.Format("%u",exoflag);
		WriteConfigString("Client","Exoflag",temp);
		netc.SetWindowText("Exo");
	}
}

void CConcertoDlg::OnCbnSelchangeLnbap()//Mode fonctionnement billetterie nombre d'article par page
{
	CString temp;
	int nart=0;
	if(master)
	{
		memafmode=afmode;
		CloseKeyboard();		
		lnbap.GetLBText(lnbap.GetCurSel(),temp);
		if(temp!="B")//mode billetetterie
		{
			NAPP=atoi(temp);
			for(nart=0;nart<100;nart+=NAPP);
				nart-=NAPP;
			NART=nart;
			afmode=0;
		}
		else// mode borne
		{
			nart=NART=81;
			NAPP=9;
			afmode=1;
			autoprint=0;
			temp.Format("%u",autoprint);
			WriteConfigString("Client","Autoprint",temp);
		}
		if(afmode!=memafmode)
			DrawWindowConfig();
		temp.Format("%u",NAPP);
		WriteConfigString("Client","NAPP",temp);
		temp.Format("%u",nart);
		WriteConfigString("Client","NART",temp);	
		temp.Format("%u",afmode);
		WriteConfigString("Param","AfMode",temp);
		FART=1;
		RefreshArticle();
	}
}
void CConcertoDlg::InitMachineName()
{
	CString temp;
	InterlockedExchange(&STOP,1);
	int wdg=WaitThread(1);
	InterlockedExchange(&PAUSERS,1);
	InterlockedExchange(&SEARCH,0);
	InterlockedExchange(&CONTROL,0);
	InterlockedExchange(&BASCULE,0);
	if(scaninter=="BLUE")
	{
		temp="---\r\n";
		SendRS(temp);
	}
	Sleep(500);
	//TerminateThread(hRSScanThread,0);
		TerminateThread(hRSReadThread,0);
		CloseHandle(hRSReadThread);
		TerminateThread(hRSSearchThread,0);
		CloseHandle(hRSSearchThread);
	TerminateThread(hRSScanThread,0);
	CloseHandle(hRSScanThread);
	TerminateThread(hArticleScanThread,0);
	CloseHandle(hArticleScanThread);
	TerminateThread(hControlFileThread,0);
	CloseHandle(hControlFileThread);
	TerminateThread(hBackupControlFileThread,0);
	CloseHandle(hBackupControlFileThread);
	TerminateThread(hScanNetThread,0);
	CloseHandle(hScanNetThread);
	for(int idx=0;idx<9;idx++)
	{
		TerminateThread(hRNThread[idx],0);
		CloseHandle(hRNThread);
	}
	CloseHandle(HRS);
	if(wdg<50)
	{
		InterlockedExchange(&QUIT,1);
		InterlockedExchange(&END,1);
		WaitThread(0);
	}
	else
	{
		if(!simul)
		{
			int pwdg=0;
			HANDLE    hPrinter;// handle to printer object
			DWORD size;//0x4000
			DWORD cbNeeded;
			DWORD nbyte=1000;
			GetDefaultPrinter(printername.GetBuffer(1000),&nbyte);
			printername.ReleaseBuffer(nbyte);
			OpenPrinter(  printername.GetBuffer(),&hPrinter,NULL);
			size=GetNbPrinterByte(hPrinter,2);
			GetPrinter(hPrinter,2,Printer,size,&cbNeeded);
			pd.pDatatype=((PRINTER_INFO_2*)Printer)->pDatatype;
			pd.pDevMode=((PRINTER_INFO_2*)Printer)->pDevMode;
			pd.DesiredAccess=PRINTER_ALL_ACCESS;
			ClosePrinter(hPrinter);
		}
	}
	SaveStaticConfig();
	SetComputerNameEx(ComputerNamePhysicalDnsHostname,prefix+"_"+poste);
	OnOK();
	SystemRestart();
}

void CConcertoDlg::OnCbnSelchangeLcb()
{
	CString temp;
	int i=0;
	if(fadmin)
	{
		CloseKeyboard();		
		eflag=lcb.GetCurSel();
		if(eflag==2)
		{
			buser.ShowWindow(0);
			for(int i=0;i<=NART;i++)
			{
				temp.Format("%u",i);
				acont[i]=AfxGetApp()->GetProfileInt("Ntouche","aCont"+temp,0);
			}
		}
		else
		{
			if(eflag==1)
			{
				if(master)
					buser.ShowWindow(1);
				econt=0;
				AfxGetApp()->WriteProfileInt("Ntouche","eCont",econt);
			
				edate="";
				WriteConfigString("Client","eDate",edate);
				netc.SetWindowText("ETC");
			}
			else
				buser.ShowWindow(0);
		}
		temp.Format("%u",eflag);
		WriteConfigString("Client","Eflag",temp);
		FART=1;
		RefreshArticle();
	}
}

void CConcertoDlg::SaveStaticConfig()
{
	fsave=1;// annonce la sauvegarde des paramètres modifiés
	CString temp;
	CString num;
	int i;
	int j;
	snom.GetWindowText(temp);
	nom=temp;
	WriteConfigString("Client","Nom",temp);
	sad1.GetWindowText(temp);
	adresse1=temp;
	WriteConfigString("Client","Adresse1",temp);
	sad2.GetWindowText(temp);
	adresse2=temp;
	WriteConfigString("Client","Adresse2",temp);
	ssir.GetWindowText(temp);
	siret=temp;
	WriteConfigString("Client","Siret",temp);
	snaf.GetWindowText(temp);
	naf=temp;
	WriteConfigString("Client","Naf",temp);
	WriteConfigString("Client","Devise",cur);
	WriteConfigString("Client","Langue",langue);
	WriteConfigString("Client","Pays",pays);
	smentiont.GetWindowText(temp);
	mentiont=temp;
	WriteConfigString("Client","MentionT",mentiont);
	smentionp.GetWindowText(temp);
	mentionp=temp;
	WriteConfigString("Client","MentionP",mentionp);
	sexer.GetWindowText(temp);
	exermois=temp;
	WriteConfigString("Infocert","MoisExercice",exermois);
	j=0;
	for(i=0;i<5;i++)
	{
		GetDlgItem(IDC_SLICENSE0+i)->GetWindowText(temp);
		if(temp!="")
		{
			num.Format("%u",j);
			lic[j]=temp;
			WriteConfigString("Client","License "+num,lic[j]);
			j++;
		}
		else
		{
			num.Format("%u",j);
			lic[j]="";
			WriteConfigString("Client","License "+num,lic[j]);
		}
	}
	if(j<5)
	{
		num.Format("%u",j);
		lic[j]="";
		WriteConfigString("Client","License "+num,lic[j]);
	}
	sserveur.GetWindowText(serveur);
	WriteConfigString("Client","Serveur",serveur);
	for(i=1;i<5;i++)
		GetDlgItem(IDC_SLICENSE0+i)->ShowWindow(0);
	int largeur=(int)((float)wlargeur*4.2/19.5);
	int x=(int)((float)wlargeur*15.15/19.5);
	int slargeur=(int)((float)wlargeur*3.8/19.5);
	float sph=9*htou/40;
	int shauteur=(int)((float)whauteur*0.8/27);
	j=0;
	for(i=0;i<5&&wsel==5;i++)
	{
		if(lic[i]!="")
		{
			GetDlgItem(IDC_SLICENSE0+i)->SetWindowPos(&wndTop,x,(int)(ohnum+(int)((i+1)*sph)),slargeur,shauteur,SWP_SHOWWINDOW   );
			GetDlgItem(IDC_SLICENSE0+i)->SetFont(&geodate,0);
			GetDlgItem(IDC_SLICENSE0+i)->SetWindowText(lic[i]);
			j++;
		}
		else
			break;
	}
	if (fadmin)
	{
		if(i<5&&wsel==5)
		{
			GetDlgItem(IDC_SLICENSE0+i)->SetWindowPos(&wndTop,x,(int)(ohnum+(int)((i+1)*sph)),slargeur,shauteur,SWP_SHOWWINDOW   );
			GetDlgItem(IDC_SLICENSE0+i)->SetFont(&geodate,0);
			GetDlgItem(IDC_SLICENSE0+i)->SetWindowText("");
			j++;
		}
	}
	if(j>0&&wsel==5)
	{
		int xn=(int)((float)wlargeur*15.0/19.5);
		largeur=(int)((float)wlargeur*4.2/19.5);
		nlic.SetWindowPos(&wndTop,xn,(int)(ohnum+(int)(0.3*sph)),largeur,(int)((j+0.5)*sph),SWP_SHOWWINDOW   );
		nlic.SetFont(&geodate,0);
		nlic.SetWindowTextA(txtc[63]);//Licenses
	}
	FART=1;
	RefreshArticle();
}

void CConcertoDlg::PrintIdent()
{
	CString temp;
	CString temp1;
	CString ntemp;
	CString date;
	CString page;
	CString vsht;
	CString vsttc;
	CString haut;
	CString larg;
	CString pox;
	CString mes2;
	CString mes3;
	CString mes4;
	/*if(eflag==1)
		mes2.Format(" %.2f  ETC",fversion/100);
	else*/
	mes2.Format(" %.3f",fversion/1000);
	mes3.Format(" %u",RAZ+1);
	mes4.Format(" %u",ntou[0]);
	CTime ct;
	ct=CTime::GetCurrentTime();
	date=ct.Format("%d/%m/%Y  %H:%M");
	CDC m_Cdc;
	CRect rect;
	//CRect butrect;
	CRect rct;
	CFont tf;
	CFont mic;
	CFont mid;
	CFont miw;
	float plargeur;
	float phauteur;
	float x;
	float xl1;
	float xl2;
	int largeur;//
	int hauteur;//
	int bc;//
	int i;
	float y;
	int toporg;
	int gdcx;
	COLORREF pencolor=0x00000000;
	COLORREF blancolor=0x00FFFFFF;
	CPen finepen(PS_SOLID,2,pencolor);
	CPen dashpen(PS_DASH,1,pencolor);
	XFORM xForm;
	CBrush br;
	CDC cdc;
	CDC* pdc;
	br.CreateSolidBrush(pencolor);
	CPrintDialog prt(FALSE);
	{	
		if(noprint)
		{
			cdc.Attach((pdc=sp.GetDC())->m_hDC);
			if(wlargeur>whauteur)				
				plargeur=(float)wlargeur/6;
			else
				plargeur=(float)wlargeur/2;
			x=0;
			lmarge=0;
			rmarge=5;
			//cdc.Rectangle(60,5,xl1-5,340);
			i=botline;
			hauteur= 3*i/4;
			rct.top=0;
			rct.bottom=hauteur;
			bc=(0xFFFFFF);
			rct.left=0;
			if(wlargeur>whauteur)				
				rct.right=wlargeur/6;
			else
				rct.right=wlargeur/2;
			if(wlargeur>whauteur)				
				sp.SetWindowPos(&wndTopMost,0,0,wlargeur/6,hauteur/*95*/,SWP_HIDEWINDOW);
			else
				sp.SetWindowPos(&wndTopMost,0,0,wlargeur/2,hauteur,SWP_HIDEWINDOW);
			sp.CenterWindow();
			sp.GetClientRect(&rect);
			sp.ShowWindow(1);
			cdc.FillSolidRect(&rect,bc);
			if(paravent)
				plargeur=(float)400;
			if(paravent)
				hauteur= 700;
			else
				hauteur= 770;
		}
		else
		{
			prt.GetDefaults();
			if(prt.m_pd.hDC!=NULL)//&&prt.GetDeviceName()==printername)
			{	
				cdc.Attach(prt.m_pd.hDC);
				InterlockedExchange(&PJOB,cdc.StartDoc("Impression Identification"));
			}
			if(printername.Find("Citizen CL-S400DT")!=-1)
				gdcx=cdc.GetDeviceCaps(HORZRES)/2;//-(2*cdc.GetDeviceCaps(PHYSICALOFFSETX)));
			else
				gdcx=cdc.GetDeviceCaps(HORZRES);//-(2*cdc.GetDeviceCaps(PHYSICALOFFSETX)));
			if(paravent)
				plargeur=(float)midline;
			else
				plargeur=(float)gdcx;
			phauteur=(float)cdc.GetDeviceCaps(VERTRES);//-(2*cdc.GetDeviceCaps(PHYSICALOFFSETY)));
			x=(float)cdc.GetDeviceCaps(PHYSICALOFFSETX);
			hauteur= 1000;
			cdc.SetGraphicsMode(GM_ADVANCED);
			cdc.GetWorldTransform(&xForm);
			if(paravent)
			{
				if(printername.Find("KMGA")!=-1)
				{
					xForm.eM11 = (FLOAT)0.0; 
					xForm.eM12 = (FLOAT)-1.0; 
					xForm.eM21 = (FLOAT) +1.0; 
					xForm.eM22 = (FLOAT) 0.0; 
					xForm.eDx  = (FLOAT) 0.0;//invxa; 
					xForm.eDy  = (FLOAT) 790;//invya; 
				}
				else
				{
					if(printername.Find("KPSX")!=-1)
					{
						xForm.eM11 = (FLOAT) 0.0; 
						xForm.eM12 = (FLOAT) -1.0; 
						xForm.eM21 = (FLOAT) +1.0; 
						xForm.eM22 = (FLOAT) 0.0; 
						xForm.eDx  = (FLOAT) 0; 
						xForm.eDy  = (FLOAT) invyt; 
					}
					else
					{
						if(printername.Find("Citizen CL-S400DT")!=-1)
						{
							xForm.eM11 = (FLOAT) 0.0; 
							xForm.eM12 = (FLOAT) -1.0; 
							xForm.eM21 = (FLOAT) +1.0; 
							xForm.eM22 = (FLOAT) 0.0; 
							xForm.eDx  = (FLOAT) 160; 
							xForm.eDy  = (FLOAT) 1080; 
						}
					}
				}
			}
			else
			{
				if(printername.Find("KMGA")!=-1)
				{
					xForm.eM11 = (FLOAT) -1.0; 
					xForm.eM12 = (FLOAT) 0.0; 
					xForm.eM21 = (FLOAT) 0.0; 
					xForm.eM22 = (FLOAT) -1.0; 
					xForm.eDx  = (FLOAT) invxa; 
					xForm.eDy  = (FLOAT) invya; 
				}
				else
				{
					if(printername.Find("KPSX")!=-1)
					{
						xForm.eM11 = (FLOAT) -1.0; 
						xForm.eM12 = (FLOAT) 0.0; 
						xForm.eM21 = (FLOAT) 0.0; 
						xForm.eM22 = (FLOAT) -1.0; 
						xForm.eDx  = (FLOAT) invxt; 
						xForm.eDy  = (FLOAT) invyt; 
					}
					else
					{
						if(printername.Find("Citizen CL-S400DT")!=-1)
						{
							xForm.eM11 = (FLOAT) -1.0; 
							xForm.eM12 = (FLOAT) 0.0; 
							xForm.eM21 = (FLOAT) 0.0; 
							xForm.eM22 = (FLOAT) -1.0; 
							xForm.eDx  = (FLOAT) 590; 
							xForm.eDy  = (FLOAT) 810; 
						}
					}
				}
			}
			cdc.SetWorldTransform(&xForm);
		}
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
			(int)plargeur/70,
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

		if(paravent)
			xl1=(float)10*plargeur/8;
		else
			xl1=(plargeur)-rmarge;
		xl2=xl1/2;
		largeur=(int)(plargeur/2.1);		
		bc=(0xFFFFFF);
		cdc.SetTextColor(0);

		if(!noprint)
				cdc.StartPage();
		else
		{
			cdc.FillSolidRect(0,0,wlargeur/2,rct.bottom,bc);
			if(paravent)
			{
				pdc->SetGraphicsMode(GM_ADVANCED);
				pdc->GetWorldTransform(&xForm);
				xForm.eM11 = (FLOAT)0; 
				xForm.eM12 = (FLOAT)+1.0; 
				xForm.eM21 = (FLOAT) -1.0; 
				xForm.eM22 = (FLOAT)0; 
				if(wlargeur>whauteur)
				{
					xForm.eDx  = (FLOAT) +320.0;//invxa; 
					xForm.eDy  = (FLOAT) +30;//invya; 
				}
				else
				{
					xForm.eDx  = (FLOAT) +300.0;//invxa; 
					xForm.eDy  = (FLOAT) +30;//invya; 
				}
				pdc->SetWorldTransform(&xForm); 
			}
		}
		toporg=DrawLogo(&cdc,xl1);
		if(paravent)
			toporg=0;
		y=(float)hauteur/15;
		if(noprint)
			rct.top=toporg+(int)(y/2);
		else
			rct.top=toporg;//+(int)(y/3);
		rct.bottom=rct.top+(int)y;
		cdc.SetBkMode(TRANSPARENT);
		if(paravent&&logo)
			rct.left=(5*(LONG)xl1)/12;
		else
			rct.left=(LONG)10;
		rct.right=(LONG)xl1-10;
		if(noprint)
			cdc.FillSolidRect(&rct,bc);
		cdc.SelectObject(&tf);
		if(paravent&&logo)
			rct.left=(5*(LONG)xl1)/12;
		else
			rct.left=(LONG)10;
		rct.right=(LONG)xl1-10;
		if(paravent)
		{
			rct.top+=hauteur/20;//60;
			rct.bottom+=hauteur/12;//60;
		}
		else
		{
			rct.top+=hauteur/40;//60;
			rct.bottom+=hauteur/30;//60;
		}

		if(nom=="")
		{
			cdc.DrawText("CONCERT",-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP|DT_NOPREFIX );
		}
		else
			cdc.DrawText(nom,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP|DT_NOPREFIX );
		rct.top+=hauteur/16;//60;
		rct.bottom+=hauteur/16;//60;
		cdc.SelectObject(&mid);
		if(adresse1!="")
		{
			if(paravent)
				rct.left=((LONG)xl1)/3+10;
			else
				rct.left=(LONG)10;
			rct.right=(LONG)(xl1-10);//(LONG)((xl1-10)/2);
			cdc.DrawText(adresse1,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP );
		}
		if(adresse2!="")
		{
			rct.top+=hauteur/25;//40;
			rct.bottom+=hauteur/25;//40;
			cdc.DrawText(adresse2,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP );
		}
		if(siret!=""||naf!="")
		{
			rct.top+=hauteur/25;//40;
			rct.bottom+=hauteur/25;//40;
			cdc.DrawText(txtc[72]+" : "+siret+"  "+txtc[95]+" : "+naf,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP );
		}
		//rct.left=(LONG)lmarge+10;
		if(poste!="")
		{
			rct.top+=hauteur/15;//50;
			rct.bottom+=hauteur/15;//50;
			cdc.DrawText(txtc[68]+" "+poste,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP );//Poste
		}
		if(MAJ==1)
		{
			rct.top+=hauteur/20;//50;
			rct.bottom+=hauteur/20;//50;
			//rct.left=(LONG)lmarge+10;
			rct.right=(LONG)xl1-10;
			cdc.SelectObject(&mid);
			temp1=txtm[37];//Mise à jour version
			temp=temp1+" "+mes2;
			cdc.DrawText(temp,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP );
			MAJ=0;
			WriteConfigString("Param","MAJ","0");
		}
		rct.top+=hauteur/15;//50;
		rct.bottom+=hauteur/15;//50;
		//rct.left=(LONG)lmarge+10;
		rct.right=(LONG)xl1-10;
		cdc.SelectObject(&mid);
		if(printername.Find("KPSX")!=-1||printername.Find("KMGA")!=-1||noprint)
		{
			temp.Format("Démarrage  N° %u du ",start);
			cdc.DrawText(temp+date,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP );
			rct.top=toporg;
			rct.bottom=515;
			rct.right=(LONG)lmarge+5;
			rct.left=(LONG)((xl1-5));
			cdc.SelectStockObject(NULL_BRUSH);
		}
		else
		{
			cdc.DrawText(date,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP );
			rct.top+=hauteur/20;//50;
			rct.bottom+=hauteur/20;//50;
			rct.left=(LONG)lmarge+10;
			rct.right=(LONG)(xl1-10)/2;
		}
		if(paravent)
		{
			if(noprint)
			{
				xForm.eM11 = (FLOAT) 1; 
				xForm.eM12 = (FLOAT) 0; 
				xForm.eM21 = (FLOAT) 0; 
				xForm.eM22 = (FLOAT) 1; 
				xForm.eDx  = (FLOAT) 0.0;//invxa; 
				xForm.eDy  = (FLOAT) 0.00;//invya; 
			}
			else
			{
				if(printername.Find("KMGA")!=-1)
				{
					xForm.eM11 = (FLOAT) -1.0; 
					xForm.eM12 = (FLOAT) 0.0; 
					xForm.eM21 = (FLOAT) 0.0; 
					xForm.eM22 = (FLOAT) -1.0; 
					xForm.eDx  = (FLOAT) invxa; 
					xForm.eDy  = (FLOAT) invya; 
				}
				else
				{
					if(printername.Find("KPSX")!=-1)
					{
						xForm.eM11 = (FLOAT) -1.0; 
						xForm.eM12 = (FLOAT) 0.0; 
						xForm.eM21 = (FLOAT) 0.0; 
						xForm.eM22 = (FLOAT) -1.0; 
						xForm.eDx  = (FLOAT) invxt; 
						xForm.eDy  = (FLOAT) invyt; 
					}
					else
					{
						if(printername.Find("Citizen CL-S400DT")!=-1)
						{
							xForm.eM11 = (FLOAT) -1.0; 
							xForm.eM12 = (FLOAT) 0.0; 
							xForm.eM21 = (FLOAT) 0.0; 
							xForm.eM22 = (FLOAT) -1.0; 
							xForm.eDx  = (FLOAT) 710; 
							xForm.eDy  = (FLOAT) 810; 
							if(paravent)
							{
								xForm.eDx  = (FLOAT) 780; 
								xForm.eDy  = (FLOAT) 810;
							}
							else
							{
								xForm.eDx  = (FLOAT) 640; 
								xForm.eDy  = (FLOAT) 800;
							}
						}
					}
				}
			}
			cdc.SetWorldTransform(&xForm); 
		}
		if(noprint)
		{
			i=midline;
			tsorg=3*i/4;
			cdc.SelectObject(&dashpen);
			cdc.MoveTo(0,tsorg);
			cdc.LineTo((int)xl1,tsorg);
			rct.top=tsorg;
			rct.bottom=rct.top+(LONG)y;
			cdc.SelectObject(&mic);
			rct.left=0;
			rct.right=(LONG)(xl1-10)/2;
		}
		else
		{
			if(printername.Find("KPSX")!=-1||printername.Find("KMGA")!=-1||printername.Find("Citizen CL-S400DT")!=-1)
			{
				tsorg=midline;
				rct.top=tsorg;
				rct.bottom=rct.top+(LONG)y;
				cdc.SelectObject(&mic);
				rct.left=0;
				if(printername.Find("Citizen CL-S400DT")!=-1||printername.Find("KPSX")!=-1)
					rct.right=(LONG)(xl1-10)/2;
			}
		}
		rct.top+=hauteur/30;//40;
		rct.bottom+=hauteur/30;//40;
		cdc.SelectObject(&mid);
		temp=txtc[77]+" : ";//Billetterie
		cdc.DrawText(temp,-1,&rct,DT_RIGHT|DT_SINGLELINE|DT_TOP  );
		rct.left=rct.right;
		rct.right=(LONG)((xl1-10));
		cdc.DrawText(serial,-1,&rct,DT_LEFT|DT_SINGLELINE|DT_TOP  );

		rct.top+=hauteur/25;//40;
		rct.bottom+=hauteur/25;//40;
		rct.left=(LONG)lmarge+10;
		rct.right=(LONG)(xl1-10)/2;
		cdc.SelectObject(&mid);
		cdc.DrawText(txtc[52]+" : ",-1,&rct,DT_RIGHT|DT_SINGLELINE|DT_TOP);//Version
		rct.left=rct.right;
		rct.right=(LONG)((xl1-10));

		cdc.DrawText(mes2,-1,&rct,DT_LEFT|DT_SINGLELINE|DT_TOP);

		if(infocert&&ticimp)
		{
			rct.top+=hauteur/25;//40;
			rct.bottom+=hauteur/25;//40;
			rct.left=(LONG)lmarge+10;
			rct.right=(LONG)(xl1-10)/2;
			cdc.SelectObject(&mid);
			cdc.DrawText(txtc[143]+" : ",-1,&rct,DT_RIGHT|DT_SINGLELINE|DT_TOP );//NF 525
			rct.left=rct.right;
			rct.right=(LONG)((xl1-10));
			temp1=categorie;
			temp1+=" "+certnum;
			cdc.DrawText(temp1,-1,&rct,DT_LEFT|DT_SINGLELINE|DT_TOP );
		}
		rct.top+=hauteur/25;//40;
		rct.bottom+=hauteur/25;//40;
		rct.left=(LONG)lmarge+10;
		rct.right=(LONG)(xl1-10)/2;
		temp1=txtc[68];//Poste
		temp1.MakeUpper();
		temp1+=" : ";
		cdc.SelectObject(&mid);
		cdc.DrawText(temp1,-1,&rct,DT_RIGHT|DT_SINGLELINE|DT_TOP );
		rct.left=rct.right;
		rct.right=(LONG)((xl1-10));
		if(master==0)
			temp1=txtc[144];//"Esclave"
		else
			if(master==1&&alone==0)
				temp1=txtc[55];//Maître"
			else
				temp1=txtc[145];//Maître auto.
		cdc.DrawText(temp1,-1,&rct,DT_LEFT|DT_SINGLELINE|DT_TOP );
		if((printername.Find("KMGA")!=-1||printername.Find("KPSX")!=-1)||printername.Find("Citizen CL-S400DT")!=-1||noprint)
		{
			cdc.SelectObject(&finepen);
			//cdc.MoveTo(300,botline);//300);
			//cdc.LineTo(310,botline);//310);
		}
		else
		{
			int memtop=rct.top;
			rct.top=toporg;
			int membottom=rct.bottom;
			rct.bottom=membottom-hauteur/10;//95;
			rct.right=(LONG)lmarge+5;
			rct.left=(LONG)((xl1-5));
			cdc.SelectObject(&finepen);
			cdc.SelectStockObject(NULL_BRUSH);
			cdc.Rectangle(&rct);//60,5,xl1-5,340
			rct.top=memtop+hauteur/33;//30;
			rct.bottom=membottom+hauteur/33;//30;
			rct.right=(LONG)lmarge+10;
			rct.left=(LONG)((xl1-10));
			cdc.SelectObject(&miw);
			//cdc.DrawText("",-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP );
			cdc.SelectObject(&finepen);
			cdc.MoveTo(300,rct.bottom-hauteur/9);//110);//410);
			cdc.LineTo(310,rct.bottom-hauteur/9);//110);//410);
		}
		if(!noprint)
		{
			cdc.EndPage();
			cdc.EndDoc();
			cdc.Detach();
			DeleteDC(prt.m_pd.hDC);
			GlobalFree(prt.m_pd.hDevMode);
			GlobalFree(prt.m_pd.hDevNames);
			InterlockedExchange(&PJOB,0);
		}
		else
		{
			cdc.SelectObject(&finepen);
			sp.GetClientRect(&rect);
			int i=SimTicketRect(&cdc,rect);
			cdc.SelectObject(&dashpen);
			Sleep(100);
			cdc.Detach();
			ReleaseDC(pdc);
		}
	}
}

void CConcertoDlg::PrintCBList()
{
	CString temp;
	CString temp1;
	CString ntemp;
	CString date;
	CString page;
	CString vsht;
	CString vsttc;
	CString haut;
	CString larg;
	CString pox;
	CString mes2;
	CString mes3;
	CString mes4;
	/*if(eflag==1)
		mes2.Format(" %.2f  ETC",fversion/100);
	else*/
	mes2.Format(" %.3f",fversion/1000);
	mes3.Format(" %u",RAZ+1);
	mes4.Format(" %u",ntou[0]);
	CTime ct;
	ct=CTime::GetCurrentTime();
	date=ct.Format("%d/%m/%Y  %H:%M");
	CDC m_Cdc;
	CRect rect;
	//CRect butrect;
	CRect rct;
	CFont tf;
	CFont mic;
	CFont mid;
	CFont miw;
	float plargeur;
	float phauteur;
	float x;
	float xl1;
	float xl2;
	int largeur;//
	int hauteur;//
	int bc;//
	int i;
	float y;
	int toporg;
	int gdcx;
	COLORREF pencolor=0x00000000;
	COLORREF blancolor=0x00FFFFFF;
	CPen finepen(PS_SOLID,2,pencolor);
	CPen dashpen(PS_DASH,1,pencolor);
	XFORM xForm;
	CBrush br;
	CDC cdc;
	CDC* pdc;
	br.CreateSolidBrush(pencolor);
	CPrintDialog prt(FALSE);
	{	
		if(noprint)
		{
			cdc.Attach((pdc=sp.GetDC())->m_hDC);
			if(wlargeur>whauteur)				
				plargeur=(float)wlargeur/6;
			else
				plargeur=(float)wlargeur/2;
			x=0;
			lmarge=0;
			rmarge=5;
			//cdc.Rectangle(60,5,xl1-5,340);
			i=botline;
			hauteur= 3*i/4;
			rct.top=0;
			rct.bottom=hauteur;
			bc=(0xFFFFFF);
			rct.left=0;
			if(wlargeur>whauteur)				
				rct.right=wlargeur/6;
			else
				rct.right=wlargeur/2;
			if(wlargeur>whauteur)				
				sp.SetWindowPos(&wndTopMost,0,0,wlargeur/6,hauteur/*95*/,SWP_HIDEWINDOW);
			else
				sp.SetWindowPos(&wndTopMost,0,0,wlargeur/2,hauteur,SWP_HIDEWINDOW);
			sp.CenterWindow();
			sp.GetClientRect(&rect);
			sp.ShowWindow(1);
			cdc.FillSolidRect(&rect,bc);
			if(paravent)
				plargeur=(float)400;
			if(paravent)
				hauteur= 700;
			else
				hauteur= 770;
		}
		else
		{
			prt.GetDefaults();
			if(prt.m_pd.hDC!=NULL)//&&prt.GetDeviceName()==printername)
			{	
				cdc.Attach(prt.m_pd.hDC);
				InterlockedExchange(&PJOB,cdc.StartDoc("Impression CB liste"));
			}
			if(printername.Find("Citizen CL-S400DT")!=-1)
				gdcx=cdc.GetDeviceCaps(HORZRES)/2;//-(2*cdc.GetDeviceCaps(PHYSICALOFFSETX)));
			else
				gdcx=cdc.GetDeviceCaps(HORZRES);//-(2*cdc.GetDeviceCaps(PHYSICALOFFSETX)));
			if(paravent)
				plargeur=(float)midline;
			else
				plargeur=(float)gdcx;
			phauteur=(float)cdc.GetDeviceCaps(VERTRES);//-(2*cdc.GetDeviceCaps(PHYSICALOFFSETY)));
			x=(float)cdc.GetDeviceCaps(PHYSICALOFFSETX);
			hauteur= 1000;
			cdc.SetGraphicsMode(GM_ADVANCED);
			cdc.GetWorldTransform(&xForm);
			if(printername.Find("KMGA")!=-1)
			{
				xForm.eM11 = (FLOAT) -1.0; 
				xForm.eM12 = (FLOAT) 0.0; 
				xForm.eM21 = (FLOAT) 0.0; 
				xForm.eM22 = (FLOAT) -1.0; 
				xForm.eDx  = (FLOAT) invxa; 
				xForm.eDy  = (FLOAT) invya; 
			}
			else
			{
				if(printername.Find("KPSX")!=-1)
				{
					xForm.eM11 = (FLOAT) -1.0; 
					xForm.eM12 = (FLOAT) 0.0; 
					xForm.eM21 = (FLOAT) 0.0; 
					xForm.eM22 = (FLOAT) -1.0; 
					xForm.eDx  = (FLOAT) invxt; 
					xForm.eDy  = (FLOAT) invyt; 
				}
				else
				{
					if(printername.Find("Citizen CL-S400DT")!=-1)
					{
						xForm.eM11 = (FLOAT) -1.0; 
						xForm.eM12 = (FLOAT) 0.0; 
						xForm.eM21 = (FLOAT) 0.0; 
						xForm.eM22 = (FLOAT) -1.0; 
						if(paravent)
						{
							xForm.eDy  = (FLOAT) 1150;
							xForm.eDx  = (FLOAT) 680;

						}
						else
						{
							xForm.eDy  = (FLOAT) 790; 
							xForm.eDx  = (FLOAT) 590;

						}
					}
				}
			}
			cdc.SetWorldTransform(&xForm);
		}
		tf.CreateFont((int)hauteur/17,
			(int)plargeur/60,
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
			(int)plargeur/70,
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

		xl1=(plargeur)-rmarge;
		xl2=xl1/2;
		largeur=(int)(plargeur/2.1);		
		bc=(0xFFFFFF);
		cdc.SetTextColor(0);

		if(!noprint)
				cdc.StartPage();
		else
		{
			cdc.FillSolidRect(0,0,wlargeur/2,rct.bottom,bc);
			if(paravent)
			{
				pdc->SetGraphicsMode(GM_ADVANCED);
				pdc->GetWorldTransform(&xForm);
				xForm.eM11 = (FLOAT)0; 
				xForm.eM12 = (FLOAT)+1.0; 
				xForm.eM21 = (FLOAT) -1.0; 
				xForm.eM22 = (FLOAT)0; 
				if(wlargeur>whauteur)
				{
					xForm.eDx  = (FLOAT) +320.0;//invxa; 
					xForm.eDy  = (FLOAT) +30;//invya; 
				}
				else
				{
					xForm.eDx  = (FLOAT) +300.0;//invxa; 
					xForm.eDy  = (FLOAT) +30;//invya; 
				}
				pdc->SetWorldTransform(&xForm); 
			}
		}
		/*toporg=DrawLogo(&cdc,xl1);
		if(paravent)*/
			toporg=0;
		y=(float)hauteur/15;

			if(noprint)
				rct.top=toporg+(int)(y/2);
			else
				rct.top=toporg;//+(int)(y/3);
		rct.bottom=rct.top+(int)y;
		cdc.SetBkMode(TRANSPARENT);
		rct.left=(LONG)10;
		rct.right=(LONG)xl1-10;
		cdc.FillSolidRect(&rct,bc);
		cdc.SelectObject(&tf);
		temp1=txtm[38];//LISTE DES CODE-BARRES ETC
		cdc.DrawText(temp1,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP );
		rct.top+=hauteur/30;//60;
		rct.bottom+=hauteur/30;//60;
		cdc.SelectObject(&mid);
		rct.left=(LONG)lmarge+10;
		cdc.SelectObject(&mid);
		for(i=0;i<pl.GetCount();i++)
		{
			rct.top+=hauteur/30;//40;
			rct.bottom+=hauteur/30;//40;
			rct.left=(LONG)lmarge+10;
			rct.right=(LONG)(xl1-10)/2;
			pl.GetText(i,temp);
			ntemp.Format("CB N° %u    ",i+1);
			cdc.DrawText(ntemp,-1,&rct,DT_RIGHT|DT_SINGLELINE|DT_TOP  );
			rct.left=rct.right;
			rct.right=(LONG)((xl1-10));
			cdc.DrawText(temp+" "+cur,-1,&rct,DT_LEFT|DT_SINGLELINE|DT_TOP  );
		}


		if((printername.Find("KMGA")!=-1||printername.Find("KPSX")!=-1)||printername.Find("Citizen CL-S400DT")!=-1||noprint)
		{
			cdc.SelectObject(&finepen);
			//cdc.MoveTo(300,botline);//300);
			//cdc.LineTo(310,botline);//310);
		}
		else
		{
			int memtop=rct.top;
			rct.top=toporg;
			int membottom=rct.bottom;
			rct.bottom=membottom-hauteur/10;//95;
			rct.right=(LONG)lmarge+5;
			rct.left=(LONG)((xl1-5));
			cdc.SelectObject(&finepen);
			cdc.SelectStockObject(NULL_BRUSH);
			cdc.Rectangle(&rct);//60,5,xl1-5,340
			rct.top=memtop+hauteur/33;//30;
			rct.bottom=membottom+hauteur/33;//30;
			rct.right=(LONG)lmarge+10;
			rct.left=(LONG)((xl1-10));
			cdc.SelectObject(&miw);
			//cdc.DrawText("",-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP );
			cdc.SelectObject(&finepen);
			cdc.MoveTo(300,rct.bottom-hauteur/9);//110);//410);
			cdc.LineTo(310,rct.bottom-hauteur/9);//110);//410);
		}
		if(!noprint)
		{
			cdc.EndPage();
			cdc.EndDoc();
			cdc.Detach();
			DeleteDC(prt.m_pd.hDC);
			GlobalFree(prt.m_pd.hDevMode);
			GlobalFree(prt.m_pd.hDevNames);
			InterlockedExchange(&PJOB,0);
		}
		else
		{
			cdc.SelectObject(&finepen);
			sp.GetClientRect(&rect);
			int i=SimTicketRect(&cdc,rect);
			cdc.SelectObject(&dashpen);
			Sleep(100);
			cdc.Detach();
			ReleaseDC(pdc);
		}
	}
}

void CConcertoDlg::DisplayCBList()
{// Imprime la liste des prix affectés aux codes barre ETC
	CString temp;
	CString temp1;
	CString ntemp;
	CString date;
	CString page;
	CString vsht;
	CString vsttc;
	CString haut;
	CString larg;
	CString pox;
	CString mes2;
	CString mes3;
	CString mes4;
	/*if(eflag==1)
		mes2.Format(" %.2f  ETC",fversion/100);
	else*/
	mes2.Format(" %.2f",fversion/100);
	mes3.Format(" %u",RAZ+1);
	mes4.Format(" %u",ntou[0]);
	CTime ct;
	ct=CTime::GetCurrentTime();
	date=ct.Format("%d/%m/%Y  %H:%M");
	CDC m_Cdc;
	CRect rect;
	//CRect butrect;
	CRect rct;
	CFont tf;
	CFont mic;
	CFont mid;
	CFont miw;
	float plargeur;
	float x;
	float xl1;
	float xl2;
	int largeur;//
	int hauteur;//
	int bc;//
	int i;
	float y;
	int toporg;
	COLORREF pencolor=0x00000000;
	COLORREF blancolor=0x00FFFFFF;
	CPen finepen(PS_SOLID,2,pencolor);
	CPen dashpen(PS_DASH,1,pencolor);
	CBrush br;
	CDC cdc;
	CDC* pdc;
	br.CreateSolidBrush(pencolor);
	cdc.Attach((pdc=sp.GetDC())->m_hDC);
	if(wlargeur>whauteur)				
		plargeur=(float)wlargeur/6;
	else
		plargeur=(float)wlargeur/3;
	x=0;
	lmarge=0;
	rmarge=5;
	//cdc.Rectangle(60,5,xl1-5,340);
	i=botline;
	hauteur= 3*i/4;
	rct.top=0;
	rct.bottom=hauteur;
	bc=(0xFFFFFF);
	rct.left=0;
	if(wlargeur>whauteur)				
		rct.right=wlargeur/6;
	else
		rct.right=wlargeur/2;
	if(wlargeur>whauteur)				
		sp.SetWindowPos(&wndTopMost,0,0,wlargeur/6,hauteur/*95*/,SWP_HIDEWINDOW);
	else
		sp.SetWindowPos(&wndTopMost,0,0,wlargeur/3,hauteur,SWP_HIDEWINDOW);
	sp.CenterWindow();
	sp.GetClientRect(&rect);
	sp.ShowWindow(1);
	cdc.FillSolidRect(&rect,bc);
	//plargeur=(float)400;
	//hauteur= 770;
	tf.CreateFont((int)hauteur/17,
		(int)plargeur/60,
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
		(int)plargeur/70,
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

	xl1=(plargeur)-rmarge;
	xl2=xl1/2;
	largeur=(int)(plargeur/2.1);		
	bc=(0xFFFFFF);
	cdc.SetTextColor(0);

	cdc.FillSolidRect(0,0,wlargeur/2,rct.bottom,bc);
	toporg=0;
	y=(float)hauteur/15;

	rct.top=toporg+(int)(y/2);
	rct.bottom=rct.top+(int)y;
	cdc.SetBkMode(TRANSPARENT);
	rct.left=(LONG)10;
	rct.right=(LONG)xl1-10;
	cdc.FillSolidRect(&rct,bc);
	cdc.SelectObject(&tf);
	cdc.DrawText(txtm[38],-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP );//LISTE DES CODE-BARRES ETC
	rct.top+=hauteur/30;//60;
	rct.bottom+=hauteur/30;//60;
	cdc.SelectObject(&mid);
	rct.left=(LONG)lmarge+10;
	cdc.SelectObject(&mid);
	for(i=0;i<pl.GetCount();i++)
	{
		rct.top+=hauteur/30;//40;
		rct.bottom+=hauteur/30;//40;
		rct.left=(LONG)lmarge+10;
		rct.right=(LONG)(xl1-10)/2;
		pl.GetText(i,temp);
		ntemp.Format("CB N° %u    ",i+1);
		cdc.DrawText(ntemp,-1,&rct,DT_RIGHT|DT_SINGLELINE|DT_TOP  );
		rct.left=rct.right;
		rct.right=(LONG)((xl1-10));
		cdc.DrawText(temp+" "+cur,-1,&rct,DT_LEFT|DT_SINGLELINE|DT_TOP  );
	}
	cdc.SelectObject(&finepen);
	sp.GetClientRect(&rect);
	SimTicketRect(&cdc,rect);
	cdc.SelectObject(&dashpen);
	Sleep(100);
	cdc.Detach();
	ReleaseDC(pdc);
}

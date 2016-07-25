// ConcertDlg.cpp : fichier d'implémentation
#include "stdafx.h"
#include "ConcertoDlg.h"
#include "Concerto.h"
#include "Num.h"
#include "Message.h"
#include "Ident.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void CConcertoDlg::OnBnClickedResult()
{
		CloseKeyboard();
		hist=0;
		DrawWindowResultat();
}

void CConcertoDlg::OnBnClickedBilcancel()
{
	CString txt;
	CString nbil;
	CString billet;
	CString touche;
	CString buf;
	CString cession;
	CString prx;
	CString tvatxt;
	CString part;
	CString temp;
	CString temp1;
	CString numi;
	CString numidx;
	CString bilan;
	int sel;
	int idx;
	int idstart;
	int idstop;
	int artidx;
	int idxprx;
	int tidx;
	//LONG spr_print_finished;
	DWORD fs;
	DWORD rs;
	DWORD ra;
	CTime ct=CTime::GetCurrentTime();
	sel=lntick.GetCurSel();
	tsorg=0;
	if(sel!=-1)//
	{
		lntick.GetText(sel,nbil);
		tidx=lntick.GetTopIndex( );
		nbil=nbil.Left(nbil.GetLength()-3);// supprime les 3 espaces présent dans la liste(futur utilisation...)
		lprix.GetText(sel,prx);
		buf=CRead(opendir);
		if(buf=="")
		{
			if(infocert)// Si erreur de lecture du fichier de la période Concert.dat
				FonctionEditeur("Pas d'information sur cette période");
			MessageBox("Pas d'information sur cette periode");
		}
		else
		{
			fs=buf.GetLength();
			cession.Preallocate(fs);
			rs=ra=0;
			cession=buf;

			idx=0;
			if((idstart=cession.Find(nbil,idx))!=-1)
			{
				idx=idstart;
				part=cession.Mid(idx+17,3);// n° parties du ticket 
				artidx=atoi(nbil.Mid(4,2));
				idx=cession.Find(";",idx);//N° ticket
				idx++;
				idx=cession.Find(";",idx);//date
				idx++;
				idxprx=idx;
				idx=cession.Find(";",idx);//prix
				prx=cession.Mid(idxprx,idx-idxprx);
				idx++;
				idx=cession.Find(";",idx);// TVA1
				idx++;
				idx=cession.Find(";",idx);// VAL1
				idx++;
				idx=cession.Find(";",idx);// TVA2
				idx++;
				idx=cession.Find(";",idx);// VAL2
				idx++;
				idx=cession.Find(";",idx);// X
				idstop=cession.Find(";",idx);
				bilan=cession.Mid(idstart,idstop-idstart);
				//MessageBox("1= "+bilan);
				if(cession.Find(nbil,idstop)==-1 && (nbil.Find("X",0)==-1))// ticket non trouve dans une ligne d'annulation
				{
					
				
					if(infocert==1)// Fenetre de dialogue du motif d'annulation
					{
						CMessage dlg;
						dlg.mes1="Motif d'annulation";
						dlg.mes2="";
						dlg.mes3="";
						dlg.mode=9;
						if(dlg.DoModal()==IDOK)// Si on répond OK
						{
							//remplir les données du ticket
							libel1[0] = txtc[160]+" ";//"Annulation ";
							libel2[0] = nbil;
							libel2[0].Trim(" ");
							libelcons[0]=dlg.reponse;
							prix[0] = -atof(prx);
							tva1[0] = tva1[artidx];
							val1[0] = -val1[artidx];
							tva2[0] = tva2[artidx];
							val2[0] = -val2[artidx];
							conso[0]=0;
							perso[0]=0;
							entrymode[0]=0; // mode vente immediate
							//imprime ticket
							//spr_print_finished = SPR+1;
							SPX[SPW]=1;//Nombre de ticket à imprimer
							SPT[SPW]=0;//N° d'article à imprimer
							STT[SPW]="";//N° de place à imprimer vide ** a gerer si place ***
							IncSpoolIndex(&SPW);// Envoi le ticket au thread d'impression
							InterlockedIncrement(&SPN);//Incrémente buffer d'impression
							while(SPN>0 )
							{
								Sleep(100);
							}
							temp=dlg.reponse;
							AnnuleTicket("Annulation ticket "+nbil+" "+temp);// Marquage dans la piste d'audit de l'annulation avec son motif
							dlg.DestroyWindow();
							if(fgate&&ngopen>0&&(perso[artidx]&1)==1)// Test si l'annulation ticket est une entrée.
								ngopen--;// Retire une permission de passage pour le tourniquet
							// Attention : si on annule un "ticket produit" fournissant des EXOs donc des entrées, il est impossible de savoir combien on en a imprimé
							//(sortie clavier numérique en cours de vente)
							// Les tickets EXO dans ce cas ne sont pas annulés mais leur valeur est de toute façon à 0 donc sans intérêt pour la comptabilité.
							// A gérer par le vendeur
						}
						else
						{
							dlg.DestroyWindow();								
							goto ABORT;
						}
					}
				}
				else
					goto ABORT;
				if(infocert)
				{	// Préparation des éléments de la signature de la ligne ticket
					//temp1.Format("%.2f",valeur);
					//temp1.Replace(".","");
					artidx=0;//force memoire annulation
					temp1.Format("%.2f",tva1[artidx]);
					temp.Format("%.2f",val1[artidx]);
					temp1+=",-"+temp;
					temp.Format("%.2f",tva2[artidx]);
					temp1+=","+temp;
					temp.Format("%.2f",val2[artidx]);
					temp1+=",-"+temp;
					temp1.Replace(".","");
					double valeur=-val1[artidx]-val2[artidx];


					spart[0]=temp1;
					temp1.Format("%.2f",valeur);
					temp1.Replace(".","");
					spart[1]=temp1;
					temp1=ct.Format("%Y%m%d%H%M%S");
					spart[2]=temp1;
					temp1=nbil;
					temp1.Replace(" ","");
					spart[3]=temp1;
					spart[4]=nbil.Left(1);
					spart[5]=sticket;
					CString sign=Sign(2);
					bilan+="|"+sign+"\r\n";
					sticket=sign;
					WriteConfigString("Infocert","SignTicket",sticket);// Mémorisation de la signature de la dernière ligne
				}
				else
					bilan+="\r\n";
				FillTicketList(opendir);// Mise à jour de la liste dans les résultats
				lntick.SetTopIndex(tidx);
				ldate.SetTopIndex(tidx);
				lprix.SetTopIndex(tidx);
				lcancel.SetTopIndex(tidx);
				esea.SetWindowTextA("");
			}
			else
			{	
				if(infocert)// Si erreur de lecture du fichier de la période Concert.dat
					FonctionEditeur("Pas d'information sur cette ligne");
				MessageBox("Ligne non trouvée !");
			}
ABORT:;
		}		
	}
}

void CConcertoDlg::OnLbnSelchangeLntick()
{
	int sel;
	CString txt="";	
	if(wsel==2)
	{
		sel=lntick.GetCurSel();
		if(sel!=-1)
		{
			ldate.SetCurSel(sel);
			lprix.SetCurSel(sel);
			lcancel.SetCurSel(sel);
			lntick.GetText(sel,txt);
			esea.SetWindowTextA(txt);
		}
		lntick.RedrawWindow(0,0,1|256|4);
		ldate.RedrawWindow(0,0,1|256|4);
		lprix.RedrawWindow(0,0,1|256|4);
		lcancel.RedrawWindow(0,0,1|256|4);
	}
}

void CConcertoDlg::OnLbnSelchangeLdate()
{
	int sel;
	CString txt="";	
	{
		sel=ldate.GetCurSel();
		if(sel!=-1)
		{
			lntick.SetCurSel(sel);
			lprix.SetCurSel(sel);
			lcancel.SetCurSel(sel);
			lntick.GetText(sel,txt);
			esea.SetWindowTextA(txt);
		}
		lntick.RedrawWindow(0,0,1|256|4);
		ldate.RedrawWindow(0,0,1|256|4);
		lprix.RedrawWindow(0,0,1|256|4);
		lcancel.RedrawWindow(0,0,1|256|4);
	}
}

void CConcertoDlg::OnLbnSelchangeLprix()
{
	CString txt="";	
	CString raz;
	CString temp;
	CString ouverture;
	int sel=lprix.GetCurSel();//GTZ
	temp=txtc[140];//OUVERTURE
	if(sel!=-1)
	{
		lcancel.SetCurSel(sel);
		if(wsel==5)
		{
			lprix.GetText(sel,raz);
			lcancel.GetText(sel, ouverture);
			ldate.SetCurSel(sel);
			txt=temp+" N° "+raz+" "+ouverture;
			lprix.RedrawWindow(0,0,1|256|4);
			lcancel.RedrawWindow(0,0,1|256|4);
			ldate.RedrawWindow(0,0,1|256|4);
		}
		else
		{
			lntick.SetCurSel(sel);
			ldate.SetCurSel(sel);
			lntick.GetText(sel,txt);
			lntick.RedrawWindow(0,0,1|256|4);
			lprix.RedrawWindow(0,0,1|256|4);
			lcancel.RedrawWindow(0,0,1|256|4);
			ldate.RedrawWindow(0,0,1|256|4);
		}
	}
	esea.SetWindowTextA(txt);
}

void CConcertoDlg::OnLbnSelchangeLcancel()
{
	CString txt;
	CString temp;
	CString raz;
	CString ouverture;
	int sel=lcancel.GetCurSel();//GTZ
	temp=txtc[140];//OUVERTURE
	if(sel!=-1)
	{
		lprix.SetCurSel(sel);
		lcancel.SetCurSel(sel);
		ldate.SetCurSel(sel);
		if(wsel==5)
		{
			lprix.GetText(sel,raz);
			lcancel.GetText(sel, ouverture);
			txt=temp+" N° "+raz+" "+ouverture;
			lprix.RedrawWindow(0,0,1|256|4);
			lcancel.RedrawWindow(0,0,1|256|4);
			ldate.RedrawWindow(0,0,1|256|4);
		}
		else
		{
			lntick.SetCurSel(sel);
			lntick.GetText(sel,txt);
			lntick.RedrawWindow(0,0,1|256|4);
			ldate.RedrawWindow(0,0,1|256|4);
			lprix.RedrawWindow(0,0,1|256|4);
			lcancel.RedrawWindow(0,0,1|256|4);
		}
	}
	esea.SetWindowTextA(txt);
}

void CConcertoDlg::OnStnClickedSearch()
{// Recherche un ticket dans la liste des résultats
	CString temp;
	int ifind;
	int sel;
	if(wsel==2)// Si en onglet résultat
	{
		esea.GetWindowText(libelsave);
		esea.SetWindowText("");
		CNum dlg;
		dlg.mode=0;
		dlg.pw=0;
		dlg.wlargeur=(int)((float)(wlargeur/2));
		dlg.whauteur=whauteur/3;
		dlg.nID=IDC_SEARCH;
		dlg.chiffre=8;
		if(dlg.DoModal()==IDOK)
		{// recherche le N° de ticket dans la cession affichée correspondant aux chiffres fournis
			esea.GetWindowTextA(temp);
			ifind=cession.Find(temp+"   ",0);
			ifind=cession.Find(";",ifind);
			temp=cession.Mid(ifind-19,19);
			sel=lntick.FindString(0,temp);
			if(sel!=LB_ERR)
			{// Si N° trouvé sélectionne la ligne dans les listes de drésultat
				lntick.SetCurSel(sel);
				ldate.SetCurSel(sel);
				lprix.SetCurSel(sel);
				lcancel.SetCurSel(sel);
				lntick.GetText(sel,temp);
				esea.SetWindowTextA(temp);
			}
			lntick.RedrawWindow(0,0,1|256|4);
			ldate.RedrawWindow(0,0,1|256|4);
			lprix.RedrawWindow(0,0,1|256|4);
			lcancel.RedrawWindow(0,0,1|256|4);
		}
		else
			esea.SetWindowText(libelsave);
	}
}

void CConcertoDlg::OnBnClickedCashView()
{// Déclenche l'impression "lecture" de la période affichée
	CDC cdc;
	CString temp;
	CString temp1;
	DWORD size;//0x4000
	HANDLE    hPrinter;// handle to printer object
	DWORD cbNeeded;
	int ids=0;
	int idx=0;
	//CPrintDialog prt(FALSE);
	if((hist==0&&dopen=="")||PRMODE>0)
		goto FIN;
	if(!noprint)
	{
		OpenPrinter(printername.GetBuffer(),&hPrinter,NULL);
		size=GetNbPrinterByte(hPrinter,5);
		GetPrinter(hPrinter,5,Printer,size,&cbNeeded);
TEST_IMPRIMANTE:;
		if((((PRINTER_INFO_5*)Printer)->Attributes&PRINTER_ATTRIBUTE_WORK_OFFLINE))
		{
			CMessage dlg;
			dlg.mes1="Imprimante débranchée de son port initial";
			dlg.mes2="Veuillez la reconnecter et cliquer";
			dlg.mes3="sur OUI pour tester la connection.";
			dlg.mode=0;
			if(dlg.DoModal()==IDOK)
			{
				size=GetNbPrinterByte(hPrinter,5);
				GetPrinter(hPrinter,5,Printer,size,&cbNeeded);
				goto TEST_IMPRIMANTE;
			}
			else
			{
				ClosePrinter(hPrinter);
				goto FIN;
			}
		}
		ClosePrinter(hPrinter);
	}
	if(hist==0)
		temp=DirToDate(dopen).Format("%d/%m/%Y  %H:%M:%S");
	if(noprint)
	{
		if(wlargeur>whauteur)				
			sp.SetWindowPos(&wndTopMost,0,0,wlargeur/6,whauteur,SWP_HIDEWINDOW);
		else
			sp.SetWindowPos(&wndTopMost,0,0,wlargeur/2,whauteur,SWP_HIDEWINDOW);
		sp.CenterWindow();
		sp.SetWindowTextA(txtc[34]);//Lecture billetterie
		tsorg=0;
	}
PRINT:;
	temp1=txtc[78];//Non clôturée
	if(hist==0)// impression clôture en cours
	{
		cash1=temp1;
		cash2=temp;
		cash3=temp1;
		InterlockedExchange(&PRMODE,2);//PrintCaisse(&cdc,temp1,temp,temp1);		
	}
	else
	{// impression cloture déjà archivée

		temp.Format("%.2f",HGTZ);					
		if((ids=cession.Find("RAZ",0))!=-1||(ids=cession.Find("GTZ",0))!=-1)
		{	// Close 27/09/2012 10:37:26 GTZ 1 GTP 3.00
			ids++;
			if((idx=cession.Find("GTZ",0))!=-1||(idx=cession.Find("GTP",0))!=-1)
				hraz=cession.Mid(ids,ids-idx);
			else
				hraz="";
		}
		else
			hraz="";
		cash1=temp;
		cash2=houverture;
		cash3=hcloture;
		InterlockedExchange(&PRMODE,2);//PrintCaisse(&cdc,temp,houverture,hcloture);		
			
		ids=0;
		/*CString date=poste;
		if((ids=cession.Find("Close",0))!=-1)
		{	// Close 27/09/2012 10:37:26 GTZ 1 GTP 3.00
			ids+=6;
			date+=cession.Mid(ids+6,4);
			date+=cession.Mid(ids+3,2);
			date+=cession.Mid(ids,2);
			date+=cession.Mid(ids+11,2);
			date+=cession.Mid(ids+14,2);
			date+=cession.Mid(ids+17,2);
		}*/
	}
	if(noprint)
	{
		if(!sp.IsWindowVisible())
		{
			if(wlargeur>whauteur)				
				sp.SetWindowPos(&wndTopMost,0,0,wlargeur/6,tsorg,SWP_SHOWWINDOW);
			else
				sp.SetWindowPos(&wndTopMost,0,0,wlargeur/2,tsorg,SWP_SHOWWINDOW);
			sp.CenterWindow();
			goto PRINT;
		}
		Sleep(500);
	}
FIN:;
}

void CConcertoDlg::OnBnClickedCashClose()
{
	CDC cdc;
	CTime tim;
	CString temp;
	CString temp1;
	CString temp2;
	CString temp3;
	CString temp4;
	CString buf;
	DWORD size;//0x4000
	HANDLE    hPrinter;// handle to printer object
	DWORD cbNeeded;
	if((hist==0&&dopen=="")||PRMODE>0||fclot>0)
		goto FIN;
	bcashclose.ShowWindow(0);//Désactive les boutons
	bcashview.ShowWindow(0);
	bcancel.ShowWindow(0);
	if(!noprint)
	{
		OpenPrinter(printername.GetBuffer(),&hPrinter,NULL);
		size=GetNbPrinterByte(hPrinter,5);
		GetPrinter(hPrinter,5,Printer,size,&cbNeeded);
TEST_IMPRIMANTE:;
		if((((PRINTER_INFO_5*)Printer)->Attributes&PRINTER_ATTRIBUTE_WORK_OFFLINE))
		{
			CMessage ilg;
			ilg.mes1="Imprimante débranchée de son port initial";
			ilg.mes2="Veuillez la reconnecter et cliquer";
			ilg.mes3="sur OUI pour tester la connection.";
			ilg.mode=0;
			if(ilg.DoModal()==IDOK)
			{
				size=GetNbPrinterByte(hPrinter,5);
				GetPrinter(hPrinter,5,Printer,size,&cbNeeded);
				goto TEST_IMPRIMANTE;
			}
			else
			{
				MessageBox("L'impresssion sera simulée\nVous pouvez réimprimer les résultats\n en sélectionnant la journée dans les archives.");
				StartSimulPrinter(2);
			}
		}
		ClosePrinter(hPrinter);
	}
	if(hist==0&&flagraz==0)
	{
		CMessage dlg;
		temp=txtm[40];//"La billetterie va être cloturée.";
		dlg.mes1=temp;
		temp=txtm[41];//"Voulez-vous continuer ?";
		dlg.mes2=temp;
		dlg.mes3="";
		dlg.mode=0;
		if(dlg.DoModal()==IDCANCEL)
		{
			dlg.DestroyWindow();
			goto FIN;
		}
		dlg.DestroyWindow();
	}
	if(hist==0)
	{
		CashClose();
		fclot=1;
		hist=1;
	}
	else
		if(hist==1)
			fclot=2;
		else
			fclot=0;
	FillTicketList(histpath);
	if(flagraz==0)
		DrawWindowResultat();
	InterlockedExchange(&artro,0);
	OnBnClickedCashView();//Impression des résultat
	if((autonews&&fclot==1)||fclot==2)
	{
		Sleep(500);// Attente pour que CashView soit pris en compte avant
		CashPrint();// impression du journal
	}
	if((flagraz==1&&wsel>1&&fclot==1))
	{
		OnBnClickedQuitter();// si automatisation RAZ par Concert Office revient à l'écran de vente
		fclot=0;
	}
	else
	{
		fclot=0;
		Sleep(3000);
FIN:;
		if(wsel==2)
		{
			bcashclose.ShowWindow(1);// réactive les boutons
			bcashview.ShowWindow(1);
		}
	}
}

int CConcertoDlg::CashClose()
{// Opération de fermeture de cession
	CTime tim;
	CMessage dlg;
	CString temp;
	if(hist==0)
	{
		//GTP+=ca;
		RAZ++;
		cash1.Format("%.2f",GTZ);
		cash2=DirToDate(dopen).Format("%d/%m/%Y  %H:%M:%S");
		tim=CTime::GetCurrentTime();
		cash3=tim.Format("%d/%m/%Y  %H:%M:%S");
		cash4.Format("%u",RAZ);
		if(!CloseCaisse(tim))
		{
			RAZ--;
			return 0;
		}
		temp.Format("%u",RAZ);
		WriteConfigString("Param","NGTZ",temp);
		econt=0;
		AfxGetApp()->WriteProfileInt("Ntouche","eCont",0);
		for(int i=0;i<=NART;i++)
		{
			temp.Format("%u",i);
			AfxGetApp()->WriteProfileInt("Ntouche","aCont"+temp,0);
			acont[i]=0;
		}
		edate="";
		WriteConfigString("Client","eDate",edate);
		temp=tim.Format(poste+"%Y%m%d%H%M%S");
		InterlockedExchange(&artro,0);
	}
	else
	{
		cash1.Format("%.2f",HGTZ);
		cash2=houverture;
		cash3=hcloture;
		cash4=hraz;
	}
	return 1;
}

void CConcertoDlg::CashPrint()
{
	CString temp1;
	CDC cdc;
	CMessage dlg;
	CString temp;
	if(noprint)
	{
		if(wlargeur>whauteur)				
			sp.SetWindowPos(&wndTopMost,0,0,wlargeur/6,whauteur,SWP_HIDEWINDOW);
		else
			sp.SetWindowPos(&wndTopMost,0,0,wlargeur/2,whauteur,SWP_HIDEWINDOW);
		sp.CenterWindow();
		sp.SetWindowTextA(txtc[36]);//"Cloture billetterie");
		tsorg=0;
	}
PRINT:;
	if(!noprint)
	{
		InterlockedExchange(&PRMODE,3);//PrintNews(&cdc,cash2,cash3,cash1,cash4);
	}
	if(noprint)
	{
		if(!sp.IsWindowVisible())
		{
			if(wlargeur>whauteur)				
				sp.SetWindowPos(&wndTopMost,0,0,wlargeur/6,tsorg,SWP_SHOWWINDOW);
			else
				sp.SetWindowPos(&wndTopMost,0,0,wlargeur/2,tsorg,SWP_SHOWWINDOW);
			sp.CenterWindow();
			goto PRINT;
		}
		Sleep(500);
	}
}

void CConcertoDlg::OnStnClickedVersion()
{
	CIdent* pdlg;
	pdlg= new CIdent(NULL);
	pwidt=pdlg;
	pdlg->fadmin=fadmin;
	/*if(eflag==1)
		pdlg->mes2.Format(" %.2f  ETC",fversion/100);
	else*/
	pdlg->mes2.Format(" %.3f",fversion/1000);
	pdlg->mes3=certnum;
	pdlg->mes4=categorie;
	pdlg->marge=lmarge;
	pdlg->DoModal();
	pdlg->DestroyWindow();
	delete pdlg;
	if(pwjob==NULL)
		pwidt=NULL;
}

#include "stdafx.h"
#include "ConcertoDlg.h"
#include "Concerto.h"

void CConcertoDlg::UpgradeETC()
{
	CString temp, temp1;
	CString nart;
	float OldVersion; 
	int i, j;

	temp=GetConfigString("Param","OldVersion","");
	OldVersion = (float) atof(temp);
	if(OldVersion < fversion)
	{
		// Chargement de la liste des prix pour les codebarre ETC
		ltmp.ResetContent();
		for(i=0;i<20;i++)
		{
			temp.Format("%u",i);
			if((temp1=AfxGetApp()->GetProfileString("Prix",temp,""))!="")// base de registre  : prix ETC définis
			{
				ltmp.AddString(temp1);
			}
		}
		for(i=1;i<NART;i++) //cherche les associations prix ETC == prix article  
		{
			nart.Format("%u",i);
			temp.Format("%.2f",prix[i]);
			j=ltmp.FindStringExact(-1,temp);
			j++;
			perso[i]+=j*0x10000;
			AfxGetApp()->WriteProfileInt(nart,"PERSO",perso[i]);//marque l'index du prix ETC associé à cette article
		}

	}
}

int CConcertoDlg::InitUserVariable()
{	// initialisation des variables à partir de la base de registre
	int i;
	int idx;
	int idy;
	int idz;
	HANDLE hsecur;
	CString num;
	CString num1;
	CString num2;
	CString temp;
	CString temp1;
	CString temp2;
	CString vol;
	CStringW wstr;
	if((hsecur=(CreateFile(sysdir+"\\csys.avs",GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL)))==INVALID_HANDLE_VALUE)
	{	// Test de la présence du fichier enfoui (pour éviter les copies logicielle)
		goto ERREUR;
	}
	CloseHandle(hsecur);
	//Initialisation des variables
	fexeran=0;
	if(infocert==1)
	{// Test arrêt non conforme de l'application et N° de ticket non imprimé
		num=GetConfigString("Param","Spool","");
		if(num.Find("Impression ticket",0)!=-1)
		{
			temp=CRead(auditinfopath);
			idx=idy=idz=0;
			while(TRUE)
			{
				if((idy=temp.Find("\r\n",idx))!=-1)
				{
					idz=idx;
					idx=idy+2;
				}
				else
					break;
			}
			temp1=temp.Mid(idz);
			if((idy=temp1.Find(";",0))!=-1)
			{
				if(temp1.Mid(idy+1,2)!="40")
				{
					/*i=atoi(num.Right(8));
					num1.Format("0000000%u",i+1);
					num2.Format("0000000%u",i+2);
					num1=num1.Right(8);
					num2=num2.Right(8);*/

					CMessage* pdlg;
					pdlg= new CMessage(this);
					pwlog=pdlg;
					pdlg->mes1=txtm[86];//La billetterie s'est arrêtée anormalement.
					//pdlg->mes2=txtm[87]+" "+num1+" "+num2;;//Les ticket se terminant par
					//pdlg->mes3=txtm[88];//n'ont peut-être pas été imprimés
					pdlg->mes2=txtm[101];//Vérifier les tickets
					pdlg->mes3=txtm[102];//en cours d'impression.
					pdlg->mode=1;
					pdlg->DoModal();
					pdlg->DestroyWindow();
					delete pdlg;
					WriteConfigString("Param","Spool","");
					FonctionEditeur(txtm[86]);//La billetterie s'est arrêtée anormalement.
				}		
			}
		}
		else
		{
			temp=CRead(auditinfopath);
			idx=idy=idz=0;
			while(TRUE)
			{
				if((idy=temp.Find("\r\n",idx))!=-1)
				{
					idz=idx;
					idx=idy+2;
				}
				else
					break;
			}
			temp1=temp.Mid(idz);
			if((idy=temp1.Find(";",0))!=-1)
			{
				if(temp1.Mid(idy+1,2)!="40")
				{
					CMessage* pdlg;
					pdlg= new CMessage(this);
					pwlog=pdlg;
					pdlg->mes1=txtm[86];//La billetterie s'est arrêtée anormalement.
					pdlg->mes2=txtm[101];//Vérifier les tickets
					pdlg->mes3=txtm[102];//en cours d'impression.
					pdlg->mode=1;
					pdlg->DoModal();
					pdlg->DestroyWindow();
					delete pdlg;
					FonctionEditeur(txtm[86]);//La billetterie s'est arrêtée anormalement.
				}
			}
		}
	// Inscription démarage de l'application dans la piste d'audit	
		if(StartTerminal()==0||VersionLogiciel()==0)
			goto ERREUR;
	}
	updatedir=workdir+"\\Update";
	CreateDirectory(updatedir,NULL);

	temp1=txtm[1];//Disque de sauvegarde absent!
	temp2=txtm[2];//Veuillez contacter votre revendeur.
	if((temp=DiskSel())=="X:\\")
	{	// Test de la présence du disque de sauvegarde
		GetVolumeInformation(temp,vol.GetBuffer(20),20,NULL,NULL,NULL,NULL,0);
		vol.ReleaseBuffer(-1);
		if(vol!="BACKUPARBAN")
		{
			if(infocert)
				FonctionEditeur(temp1);
			MessageBox(temp1+"\n"+temp2);
		}
		else
		{
			temp.Replace("\\","");
			backupdir=temp;

			CreateDirectory(temp+"\\Data",NULL);
			CreateDirectory(temp+"\\Control",NULL);
		}
	}
	else
	{
		if(infocert)
			FonctionEditeur(temp1);
		MessageBox(temp1+"\n"+temp2);
	}

	// Chargement des textes des pages
	for(i=0;i<20;i++)
	{
		temp.Format("P%u",i+1);
		temp1.Format("%u",i+1);
		pag[i]=AfxGetApp()->GetProfileString(temp,"Titre",temp1);
		jour[i]=AfxGetApp()->GetProfileString(temp,"Jour",temp1);
	}

	i=0;
	do	// Chargement des N° de Ticket par touche
	{
		temp.Format("T%u",i);
		ntou[i]=AfxGetApp()->GetProfileInt("Ntouche",temp,0);
		i++;
	}
	while(i<100);
	HKEY hk;
	if(RegOpenKeyEx(HKEY_CURRENT_USER,"Software\\BARMATIC France\\Concert\\Ntouche",0,KEY_ALL_ACCESS,&hk)== ERROR_SUCCESS)
	{// Effacement touche >100 inexistantes pour correction bug
		i=100;
		do
		{
			temp.Format("T%u",i);
			RegDeleteValue(hk,temp);
			i++;
		}
		while(i<10000);
		RegCloseKey(hk);
	}

	licstat=GetConfigString("License","Status","None");
	if(licstat!="Persistent")
	{
		if(licstat!="Expirée")
		{	// Test du fichier de license enfoui avec sa date de validité ou son statut permanent
			licper=GetConfigString("License","Période","0");
			licdate=GetConfigString("License","Date","20010101");
			CTime tod=CTime::GetCurrentTime();
			CTimeSpan tspan(15,0,0,0);
			CTime tim(atoi(licdate.Left(4))+1+atoi(licper),atoi(licdate.Mid(4,2)),atoi(licdate.Mid(6,2)),0,0,0,-1);
			if(tod>tim)
			{
				WriteConfigString("License","Status","Expirée");
				fsecur=0; // Le logiciel est marqué invalide et les résultats ne seront plus visibles
			}
			else
			{
				CTime test=tim-tspan;// Date limite - 15 jours
				if(test<tod)
					fsecur=3;	// Le logiciel est marqué en préparation de renouvellement license avec  message à chaque résultat
				else
					fsecur=1; // Le logiciel est marqué valide
			}
		}
		else
			fsecur=0; // Le logiciel est marqué invalide et les résultats ne seront plus visibles
	}
	else
		fsecur=1;

	for(i=0;i<100;i++)
	{
		temp.Format("%u",i);
		acont[i]=AfxGetApp()->GetProfileInt("Ntouche","aCont"+temp,0);
	}
	for(i=0;i<17;i++)
	{
		ne[i]=55555;
	}
	econt=AfxGetApp()->GetProfileInt("Ntouche","eCont",0);

	lmarge=(float)(60);
	// Modification de style des boutons et static en OWNERDRAW
	for(i=IDC_ART1;i<=IDC_ART12;i++)
	{
		((CButton*)GetDlgItem(i))->SetButtonStyle( BS_OWNERDRAW);
	}
	for(i=IDC_0;i<=IDC_11;i++)
	{
		((CButton*)GetDlgItem(i))->SetButtonStyle( BS_OWNERDRAW);
	}
	//((CButton*)GetDlgItem(IDC_FIG))->SetButtonStyle( BS_OWNERDRAW);
	//((CButton*)GetDlgItem(IDC_FID))->SetButtonStyle( BS_OWNERDRAW);
	((CButton*)GetDlgItem(IDC_MANAGER))->SetButtonStyle( BS_OWNERDRAW);
	((CButton*)GetDlgItem(IDC_QUITTER))->SetButtonStyle( BS_OWNERDRAW);
	((CButton*)GetDlgItem(IDC_IMPORT))->SetButtonStyle( BS_OWNERDRAW);
	((CButton*)GetDlgItem(IDC_ENTRYMODE))->SetButtonStyle( BS_OWNERDRAW);
	((CButton*)GetDlgItem(IDC_CONTROL))->SetButtonStyle( BS_OWNERDRAW);
	((CButton*)GetDlgItem(IDC_BILPRINT))->SetButtonStyle( BS_OWNERDRAW);
	((CButton*)GetDlgItem(IDC_RAZ))->SetButtonStyle( BS_OWNERDRAW);
	((CButton*)GetDlgItem(IDC_BUREAU))->SetButtonStyle( BS_OWNERDRAW);
	((CButton*)GetDlgItem(IDC_PRINTER))->SetButtonStyle( BS_OWNERDRAW);
	((CButton*)GetDlgItem(IDC_NET))->SetButtonStyle( BS_OWNERDRAW);
	((CButton*)GetDlgItem(IDC_BMANAGER))->SetButtonStyle( BS_OWNERDRAW);
	((CButton*)GetDlgItem(IDC_BUSER))->SetButtonStyle( BS_OWNERDRAW);
	((CButton*)GetDlgItem(IDC_LOGO))->SetButtonStyle( BS_OWNERDRAW);
	((CButton*)GetDlgItem(IDC_CONFIG))->SetButtonStyle( BS_OWNERDRAW);
	((CButton*)GetDlgItem(IDC_BILCANCEL))->SetButtonStyle( BS_OWNERDRAW);
	((CButton*)GetDlgItem(IDC_CASH_VIEW))->SetButtonStyle( BS_OWNERDRAW);
	((CButton*)GetDlgItem(IDC_CASH_CLOSE))->SetButtonStyle( BS_OWNERDRAW);
	((CButton*)GetDlgItem(IDC_RESULT))->SetButtonStyle( BS_OWNERDRAW);
	((CButton*)GetDlgItem(IDC_ARTICLE))->SetButtonStyle( BS_OWNERDRAW);
	((CButton*)GetDlgItem(IDC_DEL))->SetButtonStyle( BS_OWNERDRAW);
	((CButton*)GetDlgItem(IDC_COPY))->SetButtonStyle( BS_OWNERDRAW);
	((CButton*)GetDlgItem(IDC_PASTE))->SetButtonStyle( BS_OWNERDRAW);
	GetDlgItem(IDC_VERSION)->ModifyStyle(0, SS_OWNERDRAW);
	GetDlgItem(IDC_CA)->ModifyStyle(0, SS_OWNERDRAW);
	GetDlgItem(IDC_DA)->ModifyStyle(0, SS_OWNERDRAW);
	GetDlgItem(IDC_NTA)->ModifyStyle(0, SS_OWNERDRAW);
	GetDlgItem(IDC_NTT)->ModifyStyle(0, SS_OWNERDRAW);
	GetDlgItem(IDC_ENT1)->ModifyStyle(0, SS_OWNERDRAW);
	GetDlgItem(IDC_ENT2)->ModifyStyle(0, SS_OWNERDRAW);
	GetDlgItem(IDC_ENT3)->ModifyStyle(0, SS_OWNERDRAW);
	GetDlgItem(IDC_ENT4)->ModifyStyle(0, SS_OWNERDRAW);
	GetDlgItem(IDC_NPAUTO)->ModifyStyle(0, SS_OWNERDRAW);
	GetDlgItem(IDC_NNAUTO)->ModifyStyle(0, SS_OWNERDRAW);
	GetDlgItem(IDC_NVHORAIRE)->ModifyStyle(0, SS_OWNERDRAW);
	GetDlgItem(IDC_NVALPLACE)->ModifyStyle(0, SS_OWNERDRAW);
	GetDlgItem(IDC_NVALMIX)->ModifyStyle(0, SS_OWNERDRAW);
	GetDlgItem(IDC_VALPLACE)->ModifyStyle(0, SS_OWNERDRAW);
	GetDlgItem(IDC_VALEXO)->ModifyStyle(0, SS_OWNERDRAW);
	GetDlgItem(IDC_VALCBX)->ModifyStyle(0, SS_OWNERDRAW);
	GetDlgItem(IDC_VALPASS)->ModifyStyle(0, SS_OWNERDRAW);
	GetDlgItem(IDC_VALMIX)->ModifyStyle(0, SS_OWNERDRAW);
	GetDlgItem(IDC_VALENTRY)->ModifyStyle(0, SS_OWNERDRAW);
	GetDlgItem(IDC_VALACTIF)->ModifyStyle(0, SS_OWNERDRAW);
	GetDlgItem(IDC_NSCAN)->ModifyStyle(0, SS_OWNERDRAW);
	GetDlgItem(IDC_TEMNET)->ModifyStyle(0, SS_OWNERDRAW);
	GetDlgItem(IDC_TEMWEB)->ModifyStyle(0, SS_OWNERDRAW);
	GetDlgItem(IDC_TEMCONTROL)->ModifyStyle(0, SS_OWNERDRAW);
	GetDlgItem(IDC_TEMGATE)->ModifyStyle(0, SS_OWNERDRAW);
	GetDlgItem(IDC_NVALPWD)->ModifyStyle(0, SS_OWNERDRAW);
	GetDlgItem(IDC_NVALPAGE)->ModifyStyle(0, SS_OWNERDRAW);
	GetDlgItem(IDC_NETC)->ModifyStyle(0, SS_OWNERDRAW);
	GetDlgItem(IDC_TOTAL)->ModifyStyle(0, SS_OWNERDRAW);
	GetDlgItem(IDC_QR)->ModifyStyle(0, SS_OWNERDRAW);
	GetDlgItem(IDC_QRPHONE)->ModifyStyle(0, SS_OWNERDRAW);
	// Chargement des articles*************************************************************************************************************
	if(TVA=="")
		global=0;
	else
	{
		tva1[0]=atof(TVA);
		TVA.Format("%.2f",tva1[0]);
		global=1;
	}
	i=1;
	do
	{
		num.Format("%u",i);
		perso[i]=AfxGetApp()->GetProfileInt(num,"PERSO",1);
		artim[i]=AfxGetApp()->GetProfileString(num,"IMAGE","");
		libel1[i]=AfxGetApp()->GetProfileString(num,"LIBELLE1","");
		libel2[i]=AfxGetApp()->GetProfileString(num,"LIBELLE2","");
		libelspect[i]=AfxGetApp()->GetProfileString(num,"LIBELSPECT","");
		libelcons[i]=AfxGetApp()->GetProfileString(num,"LIBELCONS","");
		prix[i]=(double)(AfxGetApp()->GetProfileInt(num,"PRIX",0))/100;
		if(global)
		{
			tva1[i]=atof(TVA);
		}
		else
		{
			tva1[i]=(double)(AfxGetApp()->GetProfileInt(num,"TVA",9999))/100;
		}
		tva2[i]=(double)(AfxGetApp()->GetProfileInt(num,"TVA2",9999))/100;
		val1[i]=(double)(AfxGetApp()->GetProfileInt(num,"VAL1",0))/100;
		val2[i]=(double)(AfxGetApp()->GetProfileInt(num,"VAL2",0))/100;
		if((perso[i]&4)&&val1[i]==0&&val2[i]==0)
		{
			val1[i]=2*prix[i]/3;
			val2[i]=prix[i]/3;
			AfxGetApp()->WriteProfileInt(num,"VAL1",(int)(val1[i]*100));
			AfxGetApp()->WriteProfileInt(num,"VAL2",(int)(val2[i]*100));
		}
		else
			if((perso[i]&4)==0)
			{
				val1[i]=prix[i];
				AfxGetApp()->WriteProfileInt(num,"VAL1",(int)(val1[i]*100));
			}
		if(tva1[i]==99.99)
		{
			tva1[i]=20.0;
			AfxGetApp()->WriteProfileInt(num,"TVA",(int)(tva1[i]*100));
		}
		if(tva2[i]==99.99)
		{
			tva2[i]=10.0;
			AfxGetApp()->WriteProfileInt(num,"TVA2",(int)(tva2[i]*100));
		}
		conso[i]=AfxGetApp()->GetProfileInt(num,"CONSO",0);
		entrymode[i]=AfxGetApp()->GetProfileInt(num,"VCONSO",0);
		entrymode[i]=AfxGetApp()->GetProfileInt(num,"VALCONSO",0);
		spectsel[i]=AfxGetApp()->GetProfileInt(num,"SPECT",0);
		if(spectsel[i]>NART||spectsel[i]<0)
		{
			spectsel[i]=0;
			AfxGetApp()->WriteProfileInt(num,"SPECT",spectsel[i]);
		}
		target[i]=AfxGetApp()->GetProfileInt(num,"TARGET",0);
		cas[i]=(double)(AfxGetApp()->GetProfileInt(num,"CAS",0))/100;
		cscan[i]=AfxGetApp()->GetProfileInt(num,"CSCAN",0);
		ctot[i]=AfxGetApp()->GetProfileInt(num,"CTOT",0);
		cselevt[i]=AfxGetApp()->GetProfileInt(num,"CONTROLE",0);
		clibel1[i]=AfxGetApp()->GetProfileString(num,"CLIBELLE1","");
		clibel2[i]=AfxGetApp()->GetProfileString(num,"CLIBELLE2","");
		cfrom[i]=AfxGetApp()->GetProfileString(num,"CFROM","");
		choraire[i]=AfxGetApp()->GetProfileInt(num,"CHORAIRE",0);
		cdate[i]=AfxGetApp()->GetProfileString(num,"CDATE","");
		cheure[i]=AfxGetApp()->GetProfileString(num,"CHEURE","");
		cas[i]=(double)(AfxGetApp()->GetProfileInt(num,"CAS",0))/100;
		i++;
	}
	while(i<100);
	for(i=1;i<=NART;i++)
	{
		wstr=workdir+artim[i];
		part[i]=Image::FromFile(wstr,0);
	}
	goto FIN;
ERREUR:;
	return 0;
FIN:;
	return 1;
}

FILEINFO CConcertoDlg::GetFileInfo(CString path)
{
	FILEINFO fi;
	HANDLE hf;
	int i=0;
retry:;
	if((hf=(CreateFile(path,GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL)))!=INVALID_HANDLE_VALUE)
	{	
		fi=GetTimeSizeInfo( hf);
		CloseHandle(hf);
	}
	else
	{
		i++;
		Sleep(100);
		if(i<10)
			goto retry;
		else
		{
			fi.size=0;
			fi.time=0;
		}
	}
	return fi;
}
FILEINFO CConcertoDlg::GetTimeSizeInfo(HANDLE hf)
{
	FILEINFO fi;
	FILETIME ft;
	if(hf!=INVALID_HANDLE_VALUE)
	{	
		fi.size=GetFileSize(hf,NULL);
		if(GetFileTime(hf,NULL,NULL,&ft))
		{
			CFileTime cft(ft);
			//cft.LocalToUTC();
			fi.time=cft.GetTime();			
		}
		else
			fi.time=0;
	}
	else
	{
		fi.size=0;
		fi.time=0;
	}
	return fi;
}

void CConcertoDlg::VerifyFileIntegrity()
{
	int idx=0;
	int idy;
	int idz;
	FILEINFO fi;
	ULONGLONG tim;
	CString temp;
	CString temp1;
	CString temp2;
	CString temp3;
	CString ligne;
	CString fsize;
	CString csize;
	CString fdate;
	CString cdate;
	CString annee;
	CString source;
	CString scansource;
	CString repdir;
	CString filedir;
	CString index;
	CFileStatus cfs;
	ULONGLONG inftim;
	ULONGLONG suptim;
	ULONGLONG spt=100000000;
	repdir=auditinfopath;
	fdate=GetConfigString("Infocert","Infotime","");
	fsize=GetConfigString("Infocert","Infosize","");
	if(fdate!=""&&fsize!="")
	{
		fi=GetFileInfo(repdir);
		csize.Format("%u",fi.size);	
		inftim=fi.time-spt;
		suptim=fi.time+spt;
		tim=_atoi64(fdate);
		if(tim<inftim||tim>suptim||csize!=fsize)
		{
			WriteConfigString("Infocert","AuditIntégrité","Le fichier "+repdir+" a été modifié en dehors de l'application");
			PostMessage(WM_USER+18,0,0);
		}
	}
	pimp.StepIt();
	repdir=sysdir+"\\csat.avs";
	fdate=GetConfigString("Infocert","Cattime","");
	fsize=GetConfigString("Infocert","Catsize","");
	if(fdate!=""&&fsize!="")
	{
		fi=GetFileInfo(repdir);
		csize.Format("%u",fi.size);	
		inftim=fi.time-spt;
		suptim=fi.time+spt;
		tim=_atoi64(fdate);
		if(tim<inftim||tim>suptim||csize!=fsize)
		{
			DefautIntegrite("Le fichier "+repdir+" a été modifié en dehors de l'application");
		}
	}
	pimp.StepIt();
	repdir=datadir+"\\Exercice.dat";
	fdate=GetConfigString("Infocert","Exertime","");
	fsize=GetConfigString("Infocert","Exersize","");
	if(fdate!=""&&fsize!="")
	{
		fi=GetFileInfo(repdir);
		csize.Format("%u",fi.size);	
		inftim=fi.time-spt;
		suptim=fi.time+spt;
		tim=_atoi64(fdate);
		if(tim<inftim||tim>suptim||csize!=fsize)
		{
			DefautIntegrite("Le fichier "+repdir+" a été modifié en dehors de l'application");
		}
	}
	pimp.StepIt();
	if(dopen!="")
	{
		repdir=opendir+"\\Concert.dat";
		fdate=GetConfigString("Infocert","Datatime","");
		fsize=GetConfigString("Infocert","Datasize","");
		if(fdate!=""&&fsize!="")
		{
			fi=GetFileInfo(repdir);
			csize.Format("%u",fi.size);	
			inftim=fi.time-spt;
			suptim=fi.time+spt;
			tim=_atoi64(fdate);
			if(tim<inftim||tim>suptim||csize!=fsize)
			{
				DefautIntegrite("Le fichier "+repdir+" a été modifié en dehors de l'application");
			}
		}
	}
RELOOP:;
	idx=catfile.Find("Cat file\r\n",0);
	if(idx!=-1)
		idy=10;
	else
		goto END;
	while(idx!=-1)
	{
		idx=catfile.Find("\r\n",idy);
		if(idx==-1)
			goto END;
		ligne=catfile.Mid(idy,idx-idy);
		if(ligne.GetLength()==4)// Repère des année archivée ou non
		{
			annee=ligne;
			idy=idx+2;
			if(annee<dexer)
				source=archdir+"\\"+annee;
			else
				source=workdir;
			idx=catfile.Find("\r\n",idy);
			if(idx==-1)
				goto END;
			ligne=catfile.Mid(idy,idx-idy);
		}
		idy=idx+2;
		idx=ligne.Find(";",0);
		index=ligne.Left(idx);
		idx++;
		idz=ligne.Find(";",idx);
		temp1=ligne.Mid(idx,idz-idx);
		if(temp1.Find("Auditinfo",0)!=-1)
			scansource=workdir;
		else
			scansource=source;
		filedir=ligne.Mid(idx,idz-idx);
		repdir=scansource+"\\"+filedir;
		idx=idz+1;
		idz=ligne.Find(";",idx);
		fsize=ligne.Mid(idx,idz-idx);
		idx=idz+1;
		fdate=ligne.Mid(idx);
		fi=GetFileInfo(repdir);
		csize.Format("%u",fi.size);	
		tim=_atoi64(fdate);
		inftim=tim-spt;
		suptim=tim+spt;
		temp1.Format("%lld",fi.time);
		temp2.Format("%lld",inftim);
		temp3.Format("%lld",suptim);
		if(fdate!="0"&&fsize!="0"&&(fi.time<inftim||fi.time>suptim||csize!=fsize))
		{
			DefautIntegrite("Le fichier "+repdir+" a été modifié en dehors de l'application");
		}
		else
		{
			if(fdate=="0"&&fsize=="0"&&(fi.time<inftim||fi.time>suptim||csize!=fsize)&&ligne.Find("Auditinfo",0)==-1)
			{
				fsize.Format("%u",fi.size);	
				fdate.Format("%lld",fi.time);
				temp=index+";"+filedir+";"+fsize+";"+fdate;
				catfile.Replace(ligne,temp);
				CWrite(sysdir+"\\csat.avs",catfile,0);
				goto RELOOP;
			}	
		}
		pimp.StepIt();
		Sleep(20);
	}
END:;
}

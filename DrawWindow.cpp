#include "stdafx.h"
#include "Concerto.h"
#include "ConcertoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void CConcertoDlg::DrawWindowGeneral(CDC* pDC)// Dessine la fenetre d'acceuil
{
	CString temp1;
	CRect	rct;
	CRect	calcrct;
	int h;
	if(pDC!=NULL)
	{
		etdate=0;
		rct.top=0;
		rct.bottom=whauteur;
		rct.left=0;
		rct.right=wlargeur;
		if(wsel==1||wsel==0)
		{
			GetWindowRect(&rct);
			Graphics gr (pDC->m_hDC);
			RectF rctf(0,0,(REAL)rct.Width(),(REAL)rct.Height());
			gr.DrawImage(pecrac,rctf);
			if(wsel==0)
			{
				CRect titrct(0,whauteur/5,wlargeur,whauteur/3);
				pDC->SelectObject(&geotitre);
				pDC->SetTextColor(0x0);
				pDC->SetBkMode(TRANSPARENT);
				if(afmode==0)
					pDC->DrawText("Q-ENTRY V2F",-1,&titrct,DT_CENTER|DT_SINGLELINE|DT_VCENTER );
				else
					pDC->DrawText("BORNE V2F",-1,&titrct,DT_CENTER|DT_SINGLELINE|DT_VCENTER );
				if(infocert&&ticimp)
				{
					pDC->SelectObject(&geodate);
					//RectF rctn(10,(REAL)(rct.Height()-100),(REAL)(wlargeur/7),(REAL)90);
					double ratioi=259.0/283.0;
					double wi=wlargeur/7.0;
					double hi=wi*ratioi;
					Rect rctn(10,(whauteur-(int)hi)-10,(int)wi,(int)hi);
					gr.DrawImage(pnf525,rctn);
					titrct.left=wlargeur/6;
					titrct.right=wlargeur/3;
					titrct.top=whauteur/2+9*whauteur/20;
					titrct.bottom=whauteur/2+10*whauteur/20;
					temp1=categorie;
					temp1+=" "+certnum;
					temp1="NF 525 : "+temp1;
					pDC->DrawText(temp1,-1,&titrct,DT_CENTER|DT_SINGLELINE|DT_VCENTER );
				}
				av1.ShowWindow(1);
				av2.ShowWindow(1);
				av3.ShowWindow(1);
			}
		}
		else
			pDC->FillSolidRect(&rct,0xFFFFFF);

		switch(wsel)
		{
			case 1:
			{
				pDC->SetBkMode(TRANSPARENT);
				pDC->SelectObject(&geotitre);
				pDC->SetTextColor(0xFFFFFF);
				pDC->SetBkMode(OPAQUE);
				pDC->SetBkColor(0);
				rct.top=0;
				rct.left=(LONG)((float)wlargeur*5.8/19.5);
				rct.right=(LONG)((float)wlargeur*14/19.5);
				rct.bottom=(LONG)((float)whauteur*1.6/27);
				if(nom=="")
				{
					pDC->FillSolidRect(&rct,0);
					if(afmode==0)
						pDC->DrawText("Q-ENTRY V2F",-1,&rct,DT_CENTER|DT_SINGLELINE|DT_VCENTER );
					else
						pDC->DrawText("BORNE V2F",-1,&rct,DT_CENTER|DT_SINGLELINE|DT_VCENTER );
			
				}
				else
				{
					h=pDC->DrawText(nom,-1,&calcrct,DT_CALCRECT );
					rct.top=0;
					rct.bottom=h+(h/5);
					rct.left=(wlargeur-(calcrct.Width()+calcrct.Width()/10))/2;
					rct.right=rct.left+calcrct.Width()+(calcrct.Width()/10);

					pDC->FillSolidRect(&rct,0);
					pDC->DrawText(nom,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_VCENTER|DT_NOPREFIX );
				}
				break;
			}

		}
	}
}

void CConcertoDlg::DrawWindowConcert()// Dessine la fenetre de vente
{
	CString temp;
	wsel=1;
	int i;
	int j=NART/NAPP;

	if(afmode==0||(etc==1&&afmode==1))
		DrawButtonManager();
	else
	{
		butquitter.ShowWindow(0);
		butmanager.ShowWindow(0);
		wpage.ShowWindow(0);
	}
	//if(valpage)	// Positionnement auto sur page du jour de la semaine
	for(i=0;i<j;i++)
	{
		temp=pag[i];
		temp.MakeLower();
		if(temp.Find(pagejour,0)!=-1)
		{
			artrange=i;
			break;
		}
	}
	if(i>=j)
		artrange=fpage;
	titretext=nom;
	i=0;
	do
	{
		((CButton*)GetDlgItem(IDC_0+i))->ShowWindow(0);
		i++;
	}
	while(i<12);
	i=0;
	do
	{
		((CButton*)GetDlgItem(IDC_ART1+i))->ShowWindow(0);
		i++;
	}
	while(i<16);
	i=0;
	do
	{
		((CButton*)GetDlgItem(IDC_FAM1+i))->ShowWindow(0);
		i++;
	}
	while(i<3);
	i=0;
	do
	{
		((CButton*)GetDlgItem(IDC_RUB1+i))->ShowWindow(0);
		i++;
	}
	while(i<3);

	/*CDC* pdc=GetDC();
	OnEraseBkgnd(pdc);
	ReleaseDC(pdc);*/
	//butquitter.RedrawWindow(0,0,1|256|4);
	KillTimer(4);
	KillTimer(5);
	KillTimer(6);
	KillTimer(8);
	av1.ShowWindow(0);
	av2.ShowWindow(0);
	av3.ShowWindow(0);
	nprefix.ShowWindow(0);
	sprefix.ShowWindow(0);
	bresult.ShowWindow(0);
	bplus.ShowWindow(0);
	bminus.ShowWindow(0);
	bpoub.ShowWindow(0);
	bpaste.ShowWindow(0);
	bcopy.ShowWindow(0);
	breturn.ShowWindow(0);
	slibelcons.EnableWindow(0);
	slibel1.EnableWindow(0);
	slibel2.EnableWindow(0);
	spect.EnableWindow(0);
	guichet.EnableWindow(0);
	nmentiont.ShowWindow(0);
	nmentionp.ShowWindow(0);
	smentiont.ShowWindow(0);
	smentionp.ShowWindow(0);
	total.ShowWindow(0);
	ntotal.ShowWindow(0);
	nlic.ShowWindow(0);
	slic0.ShowWindow(0);
	slic1.ShowWindow(0);
	slic2.ShowWindow(0);
	slic3.ShowWindow(0);
	slic4.ShowWindow(0);
	slic5.ShowWindow(0);
	slic6.ShowWindow(0);
	bart.ShowWindow(0);
	bconfig.ShowWindow(0);
	bcontrol.ShowWindow(0);
	butraz.ShowWindow(0);
	bcancel.ShowWindow(0);
	npage.ShowWindow(0);
	sda.ShowWindow(0);
	sca.ShowWindow(0);
	sntt.ShowWindow(0);
	esea.ShowWindow(0);
	snta.ShowWindow(0);
	ent1.ShowWindow(0);
	ent2.ShowWindow(0);
	ent3.ShowWindow(0);
	ent4.ShowWindow(0);
	nlibel.ShowWindow(0);
	slibel1.ShowWindow(0);
	slibel2.ShowWindow(0);
	slibelcons.ShowWindow(0);
	nlibelcons.ShowWindow(0);
	sprix.ShowWindow(0);
	nprix.ShowWindow(0);
	vexo.ShowWindow(0);
	vcbx.ShowWindow(0);
	vpass.ShowWindow(0);
	ntva1.ShowWindow(0);
	sval1.ShowWindow(0);
	stva1.ShowWindow(0);
	ntva2.ShowWindow(0);
	stva2.ShowWindow(0);
	sval2.ShowWindow(0);
	lntick.ShowWindow(0);
	ldate.ShowWindow(0);
	lprix.ShowWindow(0);
	lcancel.ShowWindow(0);
	lcode.ShowWindow(0);
	lqte.ShowWindow(0);
	lptot.ShowWindow(0);
	bcashview.ShowWindow(0);
	bcashclose.ShowWindow(0);
	butprint.ShowWindow(0);
	nsir.ShowWindow(0);
	ssir.ShowWindow(0);
	snaf.ShowWindow(0);
	nnaf.ShowWindow(0);
	nad1.ShowWindow(0);
	sad1.ShowWindow(0);
	nad2.ShowWindow(0);
	sad2.ShowWindow(0);
	ndevise.ShowWindow(0);
	sdevise.ShowWindow(0);
	nlangue.ShowWindow(0);
	slangue.ShowWindow(0);
	nnom.ShowWindow(0);
	snom.ShowWindow(0);
	nposte.ShowWindow(0);
	sposte.ShowWindow(0);
	sgl.ShowWindow(0);
	sgc.ShowWindow(0);
	sgs.ShowWindow(0);
	sge.ShowWindow(0);
	nnauto.ShowWindow(0);
	npauto.ShowWindow(0);
	nan.ShowWindow(0);
	san.ShowWindow(0);
	nmois.ShowWindow(0);
	smois.ShowWindow(0);
	bbur.ShowWindow(0);
	nvpwd.ShowWindow(0);
	nvpage.ShowWindow(0);
	nvplace.ShowWindow(0);
	nvmix.ShowWindow(0);
	ventry.ShowWindow(0);
	lnbap.ShowWindow(0);
	vplace.ShowWindow(0);
	vmix.ShowWindow(0);
	vactif.ShowWindow(0);
	ncons.ShowWindow(0);
	scons.ShowWindow(0);
	version.ShowWindow(0);
	bimport.ShowWindow(0);
	tcontrol.ShowWindow(0);
	nserveur.ShowWindow(0);
	sserveur.ShowWindow(0);
	spect.ShowWindow(0);
	nspect.ShowWindow(0);
	sexer.ShowWindow(0);
	nexer.ShowWindow(0);
	guichet.ShowWindow(0);
	boffert.ShowWindow(0);
	netc.ShowWindow(0);
	lcb.ShowWindow(0);
	ltype.ShowWindow(0);
	nvhor.ShowWindow(0);
	nvcontrol.ShowWindow(0);
	bentrymode.ShowWindow(0);
	tnet.ShowWindow(0);
	tgate.ShowWindow(0);
	bdel.ShowWindow(0);
	bman.ShowWindow(0);
	buser.ShowWindow(0);
	blogo.ShowWindow(0);
	bnet.ShowWindow(0);
	bprinter.ShowWindow(0);
	lselevt.ShowWindow(0);
	nscan.ShowWindow(0);
	spays.ShowWindow(0);
	npays.ShowWindow(0);
	butinf.ShowWindow(0);
	butsup.ShowWindow(0);
	wqr.ShowWindow(0);
	phqr.ShowWindow(0);
	wtqr.ShowWindow(0);
	if((siret==""||naf==""||nom==""||(adresse1==""&&adresse2==""))&&infocert)
	{
		wpage.ShowWindow(0);
		initavert0="Veuillez renseigner toutes les infos société";
		initavert1="avant mise en route de la billetterie.";
		initavert2="Contacter votre installateur.";
		av1.ShowWindow(1);
		av2.ShowWindow(1);
		av3.ShowWindow(1);
		av1.SetWindowText(initavert0);
		av2.SetWindowText(initavert1);
		av3.SetWindowText(initavert2);
		DrawButtonManager();
	}
	else
	{

		ndate.SetWindowPos(&wndTop,rctdate.left,rctdate.top,rctdate.Width(),rctdate.Height(),SWP_SHOWWINDOW   );
		if(afmode==0)
		{
			DrawBoutonArticle(17);// GDI verif
			DrawTicket();// GDI verif
			DrawPageCom();// GDI verif
			UpdatePageEntree();// GDI verif
			DrawNumButton();// GDI verif			
			if(HRSG)
				tgate.ShowWindow(fgate);
		}
		else
		{
			selfam=selrub=etb=0;
			DrawFamilleArticle();
			if(HRSG&&FTEM)
				tgate.ShowWindow(fgate);
			SetTimer(11,20000,NULL);
		}
		RedrawWindow(0,0,1|256|RDW_ERASE);
		calc="";
		etdate=0;
	}
}
void CConcertoDlg::DrawQRCode(CString qrparam)
{
	CStringW wstr;
	CFileStatus cfs;
	CString temp;
	CString temp1;
	CString tmpdate;
	CString tmprx;
	STARTUPINFO csui;
	PROCESS_INFORMATION cpi;
	HANDLE hf;
	DWORD len;
	CString qrtxtpath;
	CString qrtargetpath;
	CString txtdec;
	int enlen;
	int ncode;
	int i;
	int j;
	int S;
	int m;
	int M;
	int Y;
	int	d;
	int H;
	CString pncode;
	delete pqr;
	qrtargetpath=workdir+"\\QR.bmp";
	DeleteFile(qrtargetpath);
	qrtxtpath=workdir+"\\QR.txt";
	DeleteFile(qrtxtpath);
	total.GetWindowText(temp);
	qrtext="http://"+serveur+"/qrcode/flashqr.php?tran="+qrparam;
	if((hf=CreateFile(qrtxtpath,GENERIC_READ|GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL))!=INVALID_HANDLE_VALUE)
	{
		if(!WriteFile(hf,qrtext.GetBuffer(),qrtext.GetLength(),&len,NULL))
		{
			CloseHandle(hf);
			goto FIN;
		}
		FlushFileBuffers(hf);
		CloseHandle(hf);
	}
	else
		goto FIN;
	ZeroMemory( &csui, sizeof(csui) );
	csui.cb = sizeof(csui);
	ZeroMemory( &cpi, sizeof(cpi) );
	GetStartupInfo(&csui);
	temp=workdir+"\\QR.exe";
	CreateProcess(NULL,temp.GetBuffer(),NULL,NULL,FALSE,NORMAL_PRIORITY_CLASS,NULL,NULL,&csui,&cpi);
	CloseHandle(cpi.hProcess);
	CloseHandle(cpi.hThread);
	Sleep(300);
	wstr=qrtargetpath;
	pqr=Image::FromFile(wstr,0);
	float x=(float)(((float)wlargeur*15/45));
	float y=(float)((float)whauteur*8/27);
	float largeur=(float)wlargeur*20/45;
	float hauteur=(float)whauteur*10/27;
	wqr.SetWindowPos(&wndBottom,(int)x,(int)y,(int)largeur,(int)hauteur,SWP_SHOWWINDOW);
	x=(float)(((float)wlargeur*8/45));
	y=(float)((float)whauteur*18.5/27);
	largeur=(float)wlargeur*29/45;
	hauteur=(float)whauteur*2/27;
	wtqr.SetWindowPos(&wndBottom,(int)x,(int)y,(int)largeur,(int)hauteur,SWP_SHOWWINDOW);
	wtqr.SetWindowText(txtc[149]);
	txtdec=qrparam;
	ncode=0;
	enlen=Base64DecodeGetRequiredLength(txtdec.GetLength());//ATL_BASE64_FLAG_NOCRLF
	if(!Base64Decode(txtdec.GetBuffer(txtdec.GetLength()),txtdec.GetLength(),(BYTE*)temp.GetBuffer(enlen),&enlen))//ATL_BASE64_FLAG_NOCRLF
	{
		temp.Format("%X",GetLastError());//NTE_BAD_KEY
		MessageBox("Erreur N° "+temp+" Base64Decode");
		temp="ERREUR Décodage";
	}
	else
	{
		temp.ReleaseBuffer(enlen);
	}
	i=temp.ReverseFind(';');
	tmpdate=temp.Mid(i+1);
	temp1=temp.Left(i);
	i=temp1.ReverseFind(';');
	tmprx=temp1.Mid(i+1);
	d=atoi(tmpdate.Mid(0,2))*14;
	m=atoi(tmpdate.Mid(2,2))*6;
	Y=atoi(tmpdate.Mid(4,4))*2;
	H=atoi(tmpdate.Mid(8,2))*5;
	M=atoi(tmpdate.Mid(10,2))*19;
	S=atoi(tmpdate.Mid(12,2))*151;
	j=d+m+Y+H+M+S+(atoi(tmprx)*11)+287;
	pncode.Format("%u",j);
	pncode=pncode.Right(4);
	temp1.Format("%u",atoi(tmprx));
	//CODAGE PINCODE DE RETOUR
	//j=(tim.GetSecond()*151)+(tim.GetMinute()*19)+(tim.GetHour()*5)+(tim.GetYear()*2)+(tim.GetMonth()*6)+(tim.GetDay()*14)+(atoi(qtotal)*11)+287;
	//DATE SOUS FORME DDMMYYYYHHMMSS
	//qtotal=partie entière du prix à payer
	if(fdev)
	{
		scan=pncode;//+" | "+pcode+" | "+qrparam;

		nscan.SetWindowPos(&wndTopMost,rctscan.left,rctscan.top,rctscan.Width(),rctscan.Height(),SWP_SHOWWINDOW   );
		SCANMODE=DT_CENTER|DT_END_ELLIPSIS|DT_NOPREFIX;
		SCANCOLOR=0;
		nscan.ShowWindow(0);
		nscan.SetWindowTextA("");
		nscan.ShowWindow(1);
		SetTimer(10,20000,NULL);
	}

FIN:;
}
void CConcertoDlg::DrawQRPhone()
{
	float x=(float)(((float)wlargeur*19.5/45));
	float y=(float)((float)whauteur*20.5/27);
	float largeur=(float)wlargeur*6/45;
	float hauteur=(float)whauteur*4/27;
	phqr.SetWindowPos(&wndBottom,(int)x,(int)y,(int)largeur,(int)hauteur,SWP_SHOWWINDOW);
}

void CConcertoDlg::DrawWindowResultat()
{
	CString temp1;
	CString temp;
	CString temps;
	CString tempm;
	wsel=2;
	titretext=txtc[31];//Résultat
	DrawPageCom();
	UpdatePageEntree();
	DrawBoutonGestion();
	KillTimer(4);
	KillTimer(6);
	KillTimer(8);
	DrawBoutonQuitter(txtc[77]);//Billetterie
	av1.ShowWindow(0);
	av2.ShowWindow(0);
	av3.ShowWindow(0);
	nprefix.ShowWindow(0);
	sprefix.ShowWindow(0);
	slibelcons.EnableWindow(0);
	slibel1.EnableWindow(0);
	slibel2.EnableWindow(0);
	spect.EnableWindow(0);
	guichet.EnableWindow(0);
	nmentiont.ShowWindow(0);
	nmentionp.ShowWindow(0);
	smentiont.ShowWindow(0);
	smentionp.ShowWindow(0);
	nlic.ShowWindow(0);
	slic0.ShowWindow(0);
	slic1.ShowWindow(0);
	slic2.ShowWindow(0);
	slic3.ShowWindow(0);
	slic4.ShowWindow(0);
	slic5.ShowWindow(0);
	slic6.ShowWindow(0);
	wpage.ShowWindow(0);
	bplus.ShowWindow(0);
	bminus.ShowWindow(0);
	bpoub.ShowWindow(0);
	bpaste.ShowWindow(0);
	bcopy.ShowWindow(0);
	breturn.ShowWindow(0);
	bcancel.ShowWindow(0);
	butinf.ShowWindow(0);
	butsup.ShowWindow(0);
	butraz.ShowWindow(0);
	lcode.ShowWindow(0);
	lqte.ShowWindow(0);
	lptot.ShowWindow(0);
	total.ShowWindow(0);
	ntotal.ShowWindow(0);
	ndate.ShowWindow(0);
	nlibel.ShowWindow(0);
	slibel1.ShowWindow(0);
	slibel2.ShowWindow(0);
	slibelcons.ShowWindow(0);
	nlibelcons.ShowWindow(0);
	sprix.ShowWindow(0);
	nlangue.ShowWindow(0);
	slangue.ShowWindow(0);
	ent1.ShowWindow(0);
	ent2.ShowWindow(0);
	ent3.ShowWindow(0);
	ent4.ShowWindow(0);
	nprix.ShowWindow(0);
	ntva1.ShowWindow(0);
	sval1.ShowWindow(0);
	stva1.ShowWindow(0);
	ntva2.ShowWindow(0);
	nserveur.ShowWindow(0);
	sserveur.ShowWindow(0);
	snaf.ShowWindow(0);
	nnaf.ShowWindow(0);
	stva2.ShowWindow(0);
	sval2.ShowWindow(0);
	nvpwd.ShowWindow(0);
	nvpage.ShowWindow(0);
	npage.ShowWindow(0);
	butprint.ShowWindow(0);
	nsir.ShowWindow(0);
	ssir.ShowWindow(0);
	nad1.ShowWindow(0);
	sad1.ShowWindow(0);
	nad2.ShowWindow(0);
	sad2.ShowWindow(0);
	ndevise.ShowWindow(0);
	sdevise.ShowWindow(0);
	nposte.ShowWindow(0);
	sposte.ShowWindow(0);
	nnom.ShowWindow(0);
	snom.ShowWindow(0);
	nvplace.ShowWindow(0);
	nvmix.ShowWindow(0);
	vplace.ShowWindow(0);
	vmix.ShowWindow(0);
	sgl.ShowWindow(0);
	sgc.ShowWindow(0);
	sgs.ShowWindow(0);
	sge.ShowWindow(0);
	vexo.ShowWindow(0);
	vcbx.ShowWindow(0);
	vpass.ShowWindow(0);
	netc.ShowWindow(0);
	nnauto.ShowWindow(0);
	npauto.ShowWindow(0);
	nan.ShowWindow(0);
	san.ShowWindow(0);
	nmois.ShowWindow(0);
	smois.ShowWindow(0);
	bbur.ShowWindow(0);
	ncons.ShowWindow(0);
	ventry.ShowWindow(0);
	lnbap.ShowWindow(0);
	scons.ShowWindow(0);
	bimport.ShowWindow(0);
	spect.ShowWindow(0);
	nspect.ShowWindow(0);
	guichet.ShowWindow(0);
	boffert.ShowWindow(0);
	nvhor.ShowWindow(0);
	vactif.ShowWindow(0);
	nvcontrol.ShowWindow(0);
	bentrymode.ShowWindow(0);
	bdel.ShowWindow(0);
	tcontrol.ShowWindow(0);
	tnet.ShowWindow(0);
	tgate.ShowWindow(0);
	bman.ShowWindow(0);
	buser.ShowWindow(0);
	blogo.ShowWindow(0);
	bnet.ShowWindow(0);
	bprinter.ShowWindow(0);
	lselevt.ShowWindow(0);
	nscan.ShowWindow(0);
	sexer.ShowWindow(0);
	nexer.ShowWindow(0);
	spays.ShowWindow(0);
	npays.ShowWindow(0);
	wqr.ShowWindow(0);
	phqr.ShowWindow(0);
	wtqr.ShowWindow(0);
	lcb.ShowWindow(0);
	ltype.ShowWindow(0);
	ndate.SetWindowPos(&wndTop,rctdate.left,rctdate.top,rctdate.Width(),rctdate.Height(),SWP_SHOWWINDOW   );
	int i=0;
	do
	{
		((CButton*)GetDlgItem(IDC_ART1+i))->ShowWindow(0);
		i++;
	}
	while(i<16);
	i=0;
	do
	{
		((CButton*)GetDlgItem(IDC_0+i))->ShowWindow(0);
		i++;
	}
	while(i<12);
	i=0;
	do
	{
		((CButton*)GetDlgItem(IDC_FAM1+i))->ShowWindow(0);
		i++;
	}
	while(i<3);
	i=0;
	do
	{
		((CButton*)GetDlgItem(IDC_RUB1+i))->ShowWindow(0);
		i++;
	}
	while(i<3);
	if(fsecur==0)
	{
		CMessage* pdlg;
		pdlg=new CMessage();
		pdlg->mes1="*** "+txtm[58]+" ***";//Votre logiciel doit être mis à jour
		pdlg->mes2=txtm[59];//"Contacter BARMATIC France ";
		pdlg->mes3=txtm[60];//"Tel: 01 46 42 18 61";
		pdlg->mode=2;	
		if(pdlg->DoModal()==IDOK)
		{
			CTime tim=CTime::GetCurrentTime();
			temp=tim.Format("%Y%m%d");
			int sec=atoi(temp)+1020304;
			int mec=atoi(temp)+9080706;
			temps.Format("%u",sec);
			tempm.Format("%u",mec);
			CNum* pnum;
			pnum=new CNum();
			pnum->wlargeur=(int)((float)(wlargeur/2));
			pnum->whauteur=whauteur/3;
			pnum->nID=0;
			pnum->chiffre =8;
			pnum->mode=4;
			pnum->nombre="";
			pnum->txtmessage="";
			pnum->DoModal();
			if(pnum->nombre==temps)
			{
				fsecur=1;
				licper=GetConfigString("License","Période","0");
				licdate=GetConfigString("License","Date","20010101");
				CTimeSpan tspan(15,0,0,0);
RETRY_LIC1:
				CTime tod(atoi(licdate.Left(4))+1+atoi(licper),atoi(licdate.Mid(4,2)),atoi(licdate.Mid(6,2)),0,0,0,-1);
				CTime test=tod-tspan;
				if(test<tim)
				{
					i=atoi(licper)+1;
					licper.Format("%u",i);
					WriteConfigString("License","Période",licper);
					goto RETRY_LIC1;
				}
				WriteConfigString("License","Status","Valide");
				WriteConfigString("License","Période",licper);
			}
			else
				if(pnum->nombre==tempm)
				{
					WriteConfigString("License","Status","Persistent");
					fsecur=1;
				}
				else
					if(pnum->nombre=="65748392")
					{
						WriteConfigString("License","Status","Persistent");
						fsecur=1;
					}
					else
						WriteConfigString("License","Status","Expirée");
			pnum->DestroyWindow();
			delete(pnum);		
		}
		else
		{
			pdlg->DestroyWindow();
			delete(pdlg);		
			WriteConfigString("License","Status","Expirée");
		}
	}
	else
	{
		if(fsecur==3)
		{
			CMessage* pdlg;
			pdlg=new CMessage();
			pdlg->mes1="*** "+txtm[58]+" ***";//Votre logiciel doit être mis à jour
			pdlg->mes2=txtm[99];//"Contacter rapidement BARMATIC France ";
			pdlg->mes3=txtm[60];//"Tel: 01 46 42 18 61";
			pdlg->mode=1;	
			pdlg->DoModal();
		}
	}
	if(fclot==0)
		DrawBoutonResult();
	RedrawWindow(0,0,1|256|RDW_ERASE);

	lntick.ResetContent();
	if(fsecur)
	{
		if(hist==0&&dopen!="")
			FillTicketList(opendir);
		else
		{
			if(hist!=0)
				FillTicketList(histpath);
			else
				FillTicketList("");
		}
		if((i=lntick.GetCount())>0)
		{
			lntick.SetCurSel(i-1);
			InterlockedExchange(&artro,1);
		}
		else
			InterlockedExchange(&artro,0);
		OnLbnSelchangeLntick();
	}
	etdate=0;
}

void CConcertoDlg::FillTicketList(CString filename)// fichier Concert.dat du jour et de l'heure de la cession
{
	CString temp1;
	HRAZ=0;
	CString buf;
	CString txt;
	CString temp;
	CString num;
	CString ouverture;
	CString cloture;
	CString stva[10];
	CString NumTicket;
	int fan;
	int idx;
	int idxmem;
	int idy;
	int idz;
	int artidx;
	int htouche;
	int i;
	int x;
	int j;
	int flagroupe;
	int erreur=0;
	DWORD rs;
	DWORD ra;
	double cat;
	double ttvaca;
	double ttvaca2;
	double valtick1;
	double valtick2;
	lntick.ResetContent();
	ldate.ResetContent();
	lprix.ResetContent();
	lcancel.ResetContent();
	txt="";
	txtsntt=txt;
	sntt.SetWindowTextA(txtsntt);
	txtsnta=txt;
	snta.SetWindowTextA(txtsnta);
	txtsca=txt;
	sca.SetWindowTextA(txtsca);
	txtsda=txt;
	sda.SetWindowText(txtsda);
	tvacumul=0;
	fldraw=0;	
	if(filename=="")
		InterlockedExchange(&artro,0);
	else
	{
		//if(fdev==1)//log on dev
		//{
		//	CString tmp;
		//	Logger* log = Logger::getInstance(this);
		//	tmp = filename.GetString();
		//	log->Log(tmp);
		//}
		cession=CRead(filename);
		if(cession=="")
		{
			temp1=txtm[61];//"Pas d'information sur cette cession");
			MessageBox(temp1);
		}
		else
		{
			x=0;
			while(x<10)
			{
				catva[x]=0;
				tvaca[x]=0;
				x++;
			}
			i=0;
			do
			{
				qteplu[i]=0;
				valplu[i]=0;
				i++;
			}
			while(i<=NART);
			
			
			rs=ra=0;
			i=1;
			do
			{
				hlibel1[i]="";
				hlibel2[i]="";
				i++;
			}
			while(i<=NART);
			nbticktot=0;
			nbtickan=0;
			ca=can=cof=0;
			idx=cession.Find("\r\n",0);
			temp=cession.Left(idx);// on réduit à la première ligne
			if((idy=temp.Find(";",0))!=-1) //premiere ligne Concert.dat
			{
				cesver=atoi(temp.Mid(idy+1,3));//version au centieme
				ouverture=temp.Mid(5,idy-5);//
			}
			else
			{
				cesver=0; // ??
				ouverture=temp.Mid(5);

			}
			houverture=ouverture;
			idx+=2;
			idxmem=idx;// positionnement premier ticket en mémoire 
			ltmp.ResetContent();
			
			if(cesver<500)
			{
				do	// Recherche des tickets annulés répertoriés dans ltmp
				{
					if((i=cession.Find(";",idx))!=-1)
					{
						txt=cession.Mid(idx,i-idx);
					}
					else
							break;
					idx=i+1;
					if((i=cession.Find(";",idx))==-1)//******** DATE ***********
						break;
					idx=i+1;
					if((i=cession.Find(";",idx))==-1)//********* PRIX **********
						break;
					idx=i+1;
					if((i=cession.Find(";",idx))==-1)//********* TVA1 ************
						break;
					idx=i+1;
					if(cesver>=459)
					{
						if((i=cession.Find(";",idx))==-1)//********* VAL1 ************
							break;
						idx=i+1;
						if((i=cession.Find(";",idx))==-1)//********* TVA2 ************
							break;
						idx=i+1;
						if((i=cession.Find(";",idx))==-1)//********* VAL2 ************
							break;
						idx=i+1;
						if((i=cession.Find(";",idx))==-1)//********* X ************
							break;
						if(cession.Mid(idx,i-idx).Find("X",0)!=-1)
							ltmp.AddString(txt);
						idx=i+1;
						if((i=cession.Find("\r\n",idx))==-1)
							break;
						idx=i+2;
					}
					else
					{
	LOOPX:;
						if(cession.Mid(idx,1)=="X")
						{
							ltmp.AddString(txt);
							idx+=3;
							goto ENDLOOP;
						}
						if(cession.Mid(idx,2)=="\r\n")
						{
							idx+=2;
							goto ENDLOOP;
						}
						if((i=cession.Find(";",idx))==-1)//********* SECONDE TVA **********
							break;
						idx=i+1;
						goto LOOPX;
	ENDLOOP:;						
					}
				}
				while(i!=-1);
			}
			else // recupere l'ensemble des ticket annules version >500
			{
				do	// Recherche des tickets annulés répertoriés dans ltmp
				{
					if((i=cession.Find(";",idx))!=-1)
					{
						txt=cession.Mid(idx,i-idx);
					}
					else
							break;
					idx=i+1;
					if((i=cession.Find(";",idx))==-1)//********fin DATE ***********
						break;
					idx=i+1;
					if((i=cession.Find(";",idx))==-1)//********* PRIX **********
						break;
					idx=i+1;
					if((i=cession.Find(";",idx))==-1)//********* TVA1 ************
						break;
					idx=i+1;
					
					if((i=cession.Find(";",idx))==-1)//********* VAL1 ************
						break;
					idx=i+1;
					if((i=cession.Find(";",idx))==-1)//********* TVA2 ************
						break;
					idx=i+1;
					if((i=cession.Find(";",idx))==-1)//********* Val2 ou Debut n° ticket annule ************
						break;
					idx=i+1;
					int j ; 
					if((j=cession.Find(";",idx))==-1)//********* fin n° ticket annule ************
						break;
					if(j != i+1)
					{
						CString numTicketAnnule = cession.Mid(i+1,j-i-1);
						numTicketAnnule.Trim(" ");
						ltmp.AddString(numTicketAnnule);
						nbtickan++;
					}	
					idx=j+1;
					if((i=cession.Find("\r\n",idx))==-1)
						break;
					idx=i+2;
				}
				while(i!=-1);
				
			}
			idx=idxmem;// Reprise de la mémoire premier ticket
			do
			{
				if(cession.Find("Close",idx)!=idx&&(i=cession.Find(";",idx))!=-1)
				{// Recherche ticket
					txt=cession.Mid(idx,i-idx);
					NumTicket = txt;
					NumTicket.Trim(" ");
					fan=ltmp.FindStringExact(0,txt);
					if(fan==-1)// recherche d'un ticket annulé dans la liste
						lntick.AddString(txt);// si non inscription dans la liste d'affichage
					htouche=atoi(txt.Mid(4,2));
					hlibel1[htouche]="PPP";				
					nbticktot++;
					temp=txt.Mid(4,2);
					artidx=atoi(temp);
					/*if(txt.Find("   ",0)==-1)
					{
						if(txt.Find("1/",0)!=-1)
							flagroupe=0;
						else
							flagroupe=1;
					}
					else*/
						flagroupe=0;
				}
				else
				{
					if((i=cession.Find("Close",idx))!=-1)
					{
						txt=cession.Mid(idx,100);
						cloture=txt.Mid(6,19);
						hcloture=cloture;
						if((i=txt.Find("RAZ",0))!=-1||(i=txt.Find("NGTZ",0))!=-1)
						{
							if(txt.Find("RAZ",0)!=-1)
								i+=4;
							else
								i+=5;
							if((idx=txt.Find(" ",i))!=-1)
							{
								temp=txt.Mid(i,idx-i);
								//MessageBox("-"+temp+"-");
								HRAZ=atoi(temp);
							}
							else
								idx=i;
						}
						if((i=txt.Find("GTZ",idx))!=-1||(i=txt.Find("GTP",idx))!=-1)
						{
							i+=4;
							if((idz=txt.Find(";",i))!=-1&&(idy=txt.Find("GTA",i))!=-1)
							{
								idy+=4;
								cash5=txt.Mid(idy,idz-idy);
							}
							else
								cash5="";

							if((idx=txt.Find("\r\n",i))!=-1||(idx=txt.Find(";",i))!=-1||(idx=txt.Find(" ",i))!=-1)
							{
								temp=txt.Mid(i,idx-i);
								//MessageBox("-"+temp+"-");
								HGTZ=atof(temp);
								i=idx+1;
								if(hist==1&&((idx=cession.Find("Start Articles",0))!=-1))//Recherche liste d'articles
								{
LOOPART:;							//MessageBox(cession.Mid(idx));
									if((idx=cession.Find("\t",idx))!=-1)
									{
										htouche=atoi(cession.Mid(idx-2,2));
										idx++;
										idy=cession.Find("	",idx);
										idy=idy-idx;
										hlibel1[htouche]=cession.Mid(idx,idy);
										idx=cession.Find("	",idx)+1;
										idy=cession.Find("	",idx);
										idy=idy-idx;
										hlibel2[htouche]=cession.Mid(idx,idy);
										idx=cession.Find("\r\n",idx)+2;
										temp.Format("%u",htouche);
										//MessageBox(temp+" "+hlibel1[htouche]+" "+hlibel2[htouche]);
										goto LOOPART;
									}
								}
								else
								{
									if(hist==1)
									{
										i=1;
										do
										{
											num.Format("0%u",i);
											num=num.Right(2);
											if(hlibel1[i]=="PPP")
											{
												if(libel1[i]==""&&libel2[i]=="")
												{
													hlibel1[i]="Touche N° "+num;
													hlibel2[i]="";
												}
												else
												{
													hlibel1[i]=libel1[i];
													hlibel2[i]=libel2[i];
												}

											}
											else
											{
												hlibel1[i]=libel1[i];
												hlibel2[i]=libel2[i];
											}
											//MessageBox(hlibel1[i]+" "+hlibel2[i]);
											i++;
										}
										while(i<=NART);
									}
								}
							}
							else
								MessageBox("Pas de \\r\\n");
						}
						else
							MessageBox("Pas de GTP");
						goto END_LIST;
					}
					else
					{
						i=1;
						do
						{
							num.Format("%u",i);
							hlibel1[i]=libel1[i];
							hlibel2[i]=libel2[i];
							//MessageBox(hlibel1[i]+" "+hlibel2[i]);
							i++;
						}
						while(i<=NART);
						break;
					}
				}
				idx=i+1;
				if((i=cession.Find(";",idx))!=-1)// date ticket
				{
					if(fan==-1)
						ldate.AddString(cession.Mid(idx,i-idx));
				}
				else
					break;
				idx=i+1;
				if((i=cession.Find(";",idx))!=-1)// prix ticket
				{
					if(fan==-1)
						lprix.AddString(cession.Mid(idx,i-idx));
					cat=atof(cession.Mid(idx,i-idx));
				}
				else
					break;
				idx=i+1;
				if((i=cession.Find(";",idx))!=-1)// TVA1 TICKET
				{
					ttvaca=(atof(cession.Mid(idx,i-idx)));
				}
				else
					break;
				idx=i+1;
				if(fan!=-1)
					ltmp.DeleteString(fan);
				if(cesver>=459)
				{
					if((i=cession.Find(";",idx))!=-1)// VAL1 TICKET
					{
						//MessageBox(cession.Mid(idx,i-idx));
						valtick1=(atof(cession.Mid(idx,i-idx)));
					}
					else
						break;
					idx=i+1;
					if((i=cession.Find(";",idx))!=-1)// TVA2 TICKET
					{
						//MessageBox(cession.Mid(idx,i-idx));
						ttvaca2=(atof(cession.Mid(idx,i-idx)));
					}
					else
						break;
					idx=i+1;
					if((i=cession.Find(";",idx))!=-1)// VAL2 TICKET
					{
						//MessageBox(cession.Mid(idx,i-idx));
						valtick2=(atof(cession.Mid(idx,i-idx)));
					}
					else
						break;
					idx=i+1;
					if((i=cession.Find(";",idx))!=-1)// X
					{
						if(cesver>=500)
						{
							//MessageBox("|"+NumTicket+"|");
							if((j=ltmp.FindStringExact(-1,NumTicket))!=-1)
							{
								ltmp.DeleteString(j);
								lcancel.AddString("X");
							}
							else
							{
								lcancel.AddString("");
							}
						}
						else
						{
							//MessageBox(cession.Mid(idx,i-idx));
							if(cession.Mid(idx,i-idx)=="X")
							{
								lcancel.AddString(cession.Mid(idx,1));
								nbtickan++;
								nbticktot--;
								can=can+cat;
								ca=ca-cat;
								x=0;
								while(x<10&&ttvaca!=tvaca[x]&&tvaca[x]>0)
								{
									x++;
								}
								if(x<10)
								{
									if(perso[artidx]&4)
									{
										catva[x]-=(val1[artidx]);
										tvaca[x]=ttvaca;
										stva[x].Format(" %.2f ",tvaca[x]);
										x=0;
										while(x<10&&ttvaca2!=tvaca[x]&&tvaca[x]>0)
										{
											x++;
										}
										if(x<10)
										{
											catva[x]-=val2[artidx];
											tvaca[x]=ttvaca2;
											stva[x].Format(" %.2f ",tvaca[x]);
										}
									}
									else
									{
										catva[x]-=cat;
										tvaca[x]=ttvaca;
										stva[x].Format(" %.2f ",tvaca[x]);
									}
								}
								else 
									break;
								qteplu[artidx]--;
								valplu[artidx]-=cat;
								idx=i+1;
								if((i=cession.Find("\r\n",idx))==-1)
									break;
								idx=i+2;
								goto ENDCA;
							}
							else
							{
								if(fan==-1)
									lcancel.AddString("");
							}
						}
					}
					else
						break;
					idx=i+1;
					if((i=cession.Find("\r\n",idx))==-1)
						break;
					idx=i+2;
					goto ADDCA;
				}
				else
				{
LOOPCA:;
					if(cession.Mid(idx,1)=="X")
					{
						lcancel.AddString(cession.Mid(idx,1));
						nbtickan++;
						can=can+cat;
						idx+=3;
						goto ENDCA;
					}
					if(cession.Mid(idx,2)=="\r\n")
					{
						if(fan==-1)
							lcancel.AddString("");
						if(!(perso[artidx]&4))
							ttvaca2=0;
						idx+=2;
						goto ADDCA;
					}
					// cas avec TVA Pack en plus
					i=cession.Find(";",idx);
					ttvaca2=atof(cession.Mid(idx,i-idx));
					temp.Format(" %.2f ",ttvaca2);
					idx=i+1;
					goto LOOPCA;
				}
ADDCA:;						
				qteplu[artidx]++;
				valplu[artidx]+=cat;
				ca=ca+cat;
				x=0;
				while(x<10&&ttvaca!=tvaca[x]&&tvaca[x]>0)
				{
					x++;
				}
				if(x<10)
				{
					if(perso[artidx]&4)
					{
						if(cesver>=459)
							catva[x]+=(valtick1);
						else
							catva[x]+=(2*cat/3);
						tvaca[x]=ttvaca;
						stva[x].Format(" %.2f ",tvaca[x]);
						x=0;
						while(x<10&&ttvaca2!=tvaca[x]&&tvaca[x]>0)
						{
							x++;
						}
						if(x<10)
						{
							if(cesver>=459)
								catva[x]+=(valtick2);
							else
								catva[x]+=(1*cat/3);
							tvaca[x]=ttvaca2;
							stva[x].Format(" %.2f ",tvaca[x]);
						}
					}
					else
					{
						catva[x]+=cat;
						tvaca[x]=ttvaca;
						stva[x].Format(" %.2f ",tvaca[x]);
					}
				}
				else 
					break;
ENDCA:;
			}
			while(i!=-1);
END_LIST:;
			fldraw=1;
			lcancel.RedrawWindow(0,0,1|1|256|4);
			ldate.RedrawWindow(0,0,1|1|256|4);
			lprix.RedrawWindow(0,0,1|1|256|4);
			lntick.RedrawWindow(0,0,1|1|256|4);
		}
		tvacumul=0;
		i=0;
		while(i<10)//catva[i]!=0&&
		{
			tvacumul+=catva[i]-(catva[i]/(1+(tvaca[i]/100)));
			i++;
		}
		if(cesver>=500)
		{
			nbticktot -= nbtickan;
		}
		txt.Format("%u",nbticktot-nbtickan);
		txtsntt=txt;
		sntt.SetWindowTextA(txtsntt);
		txt.Format("%u",nbtickan);
		txtsnta=txt;
		snta.SetWindowTextA(txtsnta);
		txt.Format("%.2f",ca);
		txtsca=txt;

		sca.SetWindowTextA(txtsca);
		if(hist==0)
			txtsda=(ouverture);
		else
		{
			txtsda=cloture;
		}
		sda.SetWindowText(txtsda);
	}
	if(lntick.GetCount()>0)
		InterlockedExchange(&artro,1);
	else
		InterlockedExchange(&artro,0);
}


void CConcertoDlg::DrawWindowConfig()
{
	CString cmois;
	CString can;
	CString temp;
	titretext=txtc[30];//Config
	wsel=5;
	DrawPageCom();
	UpdatePageEntree();
	DrawBoutonGestion();
	DrawBoutonQuitter(txtc[77]);//Billetterie
	KillTimer(4);
	KillTimer(6);
	KillTimer(8);
	av1.ShowWindow(0);
	av2.ShowWindow(0);
	av3.ShowWindow(0);
	nprefix.ShowWindow(0);
	sprefix.ShowWindow(0);
	slibelcons.EnableWindow(0);
	slibel1.EnableWindow(0);
	slibel2.EnableWindow(0);
	spect.EnableWindow(0);
	guichet.EnableWindow(0);
	nmentiont.ShowWindow(0);
	nmentionp.ShowWindow(0);
	smentiont.ShowWindow(0);
	smentionp.ShowWindow(0);
	bplus.ShowWindow(0);
	bminus.ShowWindow(0);
	bpoub.ShowWindow(0);
	bpaste.ShowWindow(0);
	bcopy.ShowWindow(0);
	breturn.ShowWindow(0);
	nlic.ShowWindow(0);
	slic0.ShowWindow(0);
	slic1.ShowWindow(0);
	slic2.ShowWindow(0);
	slic3.ShowWindow(0);
	slic4.ShowWindow(0);
	slic5.ShowWindow(0);
	slic6.ShowWindow(0);
	bbur.ShowWindow(0);
	lntick.ShowWindow(0);
	ldate.ShowWindow(0);
	lprix.ShowWindow(0);
	lcancel.ShowWindow(0);
	wpage.ShowWindow(0);
	butinf.ShowWindow(0);
	butsup.ShowWindow(0);
	bcancel.ShowWindow(0);
	bcashview.ShowWindow(0);
	bcashclose.ShowWindow(0);
	butprint.ShowWindow(0);
	lcode.ShowWindow(0);
	lqte.ShowWindow(0);
	lptot.ShowWindow(0);
	total.ShowWindow(0);
	ntotal.ShowWindow(0);
	nlibel.ShowWindow(0);
	slibel1.ShowWindow(0);
	slibel2.ShowWindow(0);
	slibelcons.ShowWindow(0);
	netc.ShowWindow(0);
	vexo.ShowWindow(0);
	vpass.ShowWindow(0);
	nlibelcons.ShowWindow(0);
	nserveur.ShowWindow(0);
	sserveur.ShowWindow(0);
	sprix.ShowWindow(0);
	nprix.ShowWindow(0);
	nlangue.ShowWindow(0);
	slangue.ShowWindow(0);
	ntva1.ShowWindow(0);
	sval1.ShowWindow(0);
	stva1.ShowWindow(0);
	ntva2.ShowWindow(0);
	stva2.ShowWindow(0);
	sval2.ShowWindow(0);
	snaf.ShowWindow(0);
	nnaf.ShowWindow(0);
	nvpwd.ShowWindow(0);
	nvpage.ShowWindow(0);
	nvplace.ShowWindow(0);
	nvmix.ShowWindow(0);
	lnbap.ShowWindow(0);
	vplace.ShowWindow(0);
	vmix.ShowWindow(0);
	vactif.ShowWindow(0);
	npage.ShowWindow(0);
	sda.ShowWindow(0);
	esea.ShowWindow(0);
	sca.ShowWindow(0);
	sntt.ShowWindow(0);
	snta.ShowWindow(0);
	ent1.ShowWindow(0);
	ent2.ShowWindow(0);
	ent3.ShowWindow(0);
	ent4.ShowWindow(0);
	lcb.ShowWindow(0);
	ltype.ShowWindow(0);
	ncons.ShowWindow(0);
	scons.ShowWindow(0);
	ventry.ShowWindow(0);
	vcbx.ShowWindow(0);
	version.ShowWindow(0);
	bimport.ShowWindow(0);
	spect.ShowWindow(0);
	nspect.ShowWindow(0);
	guichet.ShowWindow(0);
	boffert.ShowWindow(0);
	nvhor.ShowWindow(0);
	bentrymode.ShowWindow(0);
	nvcontrol.ShowWindow(0);
	bdel.ShowWindow(0);
	tcontrol.ShowWindow(0);
	tgate.ShowWindow(0);
	tnet.ShowWindow(0);
	bman.ShowWindow(0);
	buser.ShowWindow(0);
	blogo.ShowWindow(0);
	bnet.ShowWindow(0);
	bprinter.ShowWindow(0);
	ndate.ShowWindow(0);
	sexer.ShowWindow(0);
	nexer.ShowWindow(0);
	spays.ShowWindow(0);
	npays.ShowWindow(0);
	wqr.ShowWindow(0);
	phqr.ShowWindow(0);
	wtqr.ShowWindow(0);
	lselevt.ShowWindow(0);
	nscan.ShowWindow(0);
	DrawBoutonConfig();
	DrawStaticConfig();
	int i=0;
	do
	{
		((CButton*)GetDlgItem(IDC_ART1+i))->ShowWindow(0);
		i++;
	}
	while(i<16);
	i=0;
	do
	{
		((CButton*)GetDlgItem(IDC_0+i))->ShowWindow(0);
		i++;
	}
	while(i<12);
	i=0;
	do
	{
		((CButton*)GetDlgItem(IDC_FAM1+i))->ShowWindow(0);
		i++;
	}
	while(i<3);
	i=0;
	do
	{
		((CButton*)GetDlgItem(IDC_RUB1+i))->ShowWindow(0);
		i++;
	}
	while(i<3);
	smois.SetWindowTextA(searchmois);
	san.SetWindowTextA(searchan);
	RedrawWindow(0,0,1|256|RDW_ERASE);
	FillCessionList();
}

void CConcertoDlg::FillCessionList()
{
	CString temp1;
	CString buf;
	CString cur;
	CString date;
	CString raz;
	CString temp;
	CString atemp;
	CString mtemp;
	CString ouverture;
	int i;
	int memi;
	int j;
	int erreur=0;
	lprix.ResetContent();
	lcancel.ResetContent();
	ldate.ResetContent();
	lntick.ResetContent();
	fldraw=1;
	CFileFind ff;
	BOOL result =ff.FindFile(searchdir+"\\*.*",0 );
	while(result)
	{
		result=ff.FindNextFile();
		if (ff.IsDots())
         continue;
		if(ff.IsDirectory())
		{
			//MessageBox(ff.GetFilePath()+"\\Concert.dat");
			buf=CRead(ff.GetFilePath());
			if(buf=="")
			{
				temp1=txtm[61];//"Pas d'information sur cette cession");
				MessageBox(temp1);
			}
			else
			{
				if(buf.GetLength()>70)
				{
					if((i=buf.Find("\r\nClose"))!=-1)
					{
						i=i+2;
						memi=i;
						date=buf.Mid(5,19);
						temp=date.Mid(6,4);
						smois.GetWindowTextA(mtemp);
						cur=date.Mid(3,2);
						if(!(cur!=mtemp && mtemp!=""))//
						{
							lcancel.AddString(date);
							if((i=buf.Find("RAZ",i))!=-1)
							{
								if((j=buf.Find("GTZ",i+3))!=-1)
								{
									raz=buf.Mid(i+4,j-5-i);
									lprix.AddString(raz);
									ldate.AddString(ff.GetFilePath());
								}
							}
							else
								if((i=buf.Find("NGTZ",memi))!=-1)
								{
									if((j=buf.Find("GTP",i+4))!=-1)
									{
										raz=buf.Mid(i+5,j-5-i);
										lprix.AddString(raz);
										ldate.AddString(ff.GetFilePath());
									}
								}
						}
					}
				}
				if(lcancel.GetCount()>0)
				{
					i=lcancel.GetCount()-1;
					lprix.GetText(i,raz);
					lcancel.GetText(i,ouverture);
					ldate.SetCurSel(lprix.SetCurSel(lcancel.SetCurSel(i)));//GTZ
					esea.SetWindowText(txtc[140]+" N° "+raz+" "+ouverture);//OUVERTURE
					lprix.RedrawWindow(0,0,1|256|4);
					lcancel.RedrawWindow(0,0,1|256|4);
				}
				else
					esea.SetWindowText("");
			}
		}
	}
	ff.Close();
	fldraw=1;	
}


void CConcertoDlg::DrawWindowArticle()
{
	CString txt;
	CString temp;
	titretext=txtc[32];//Articles
	wsel=3;
	//CDC* pdc=GetDC();
	//OnEraseBkgnd(pdc);
	//ReleaseDC(pdc);
	DrawBoutonGestion();
	DrawBoutonQuitter(txtc[77]);//Billetterie
	KillTimer(6);
	KillTimer(8);
	av1.ShowWindow(0);
	av2.ShowWindow(0);
	av3.ShowWindow(0);
	nprefix.ShowWindow(0);
	sprefix.ShowWindow(0);
	slibelcons.EnableWindow(0);
	slibel1.EnableWindow(0);
	slibel2.EnableWindow(0);
	spect.EnableWindow(0);
	guichet.EnableWindow(0);
	nmentiont.ShowWindow(0);
	nmentionp.ShowWindow(0);
	smentiont.ShowWindow(0);
	smentionp.ShowWindow(0);
	bplus.ShowWindow(0);
	bminus.ShowWindow(0);
	bpoub.ShowWindow(0);
	bpaste.ShowWindow(0);
	bcopy.ShowWindow(0);
	breturn.ShowWindow(0);
	lntick.ShowWindow(0);
	ldate.ShowWindow(0);
	lprix.ShowWindow(0);
	lcancel.ShowWindow(0);
	butprint.ShowWindow(0);
	bimport.ShowWindow(0);
	bcancel.ShowWindow(0);
	butraz.ShowWindow(0);
	bcashview.ShowWindow(0);
	bcashclose.ShowWindow(0);
	ndate.ShowWindow(0);
	lcode.ShowWindow(0);
	lqte.ShowWindow(0);
	lptot.ShowWindow(0);
	total.ShowWindow(0);
	ntotal.ShowWindow(0);
	sda.ShowWindow(0);
	esea.ShowWindow(0);
	sca.ShowWindow(0);
	sntt.ShowWindow(0);
	snta.ShowWindow(0);
	ent1.ShowWindow(0);
	ent2.ShowWindow(0);
	ent3.ShowWindow(0);
	ent4.ShowWindow(0);
	nsir.ShowWindow(0);
	ssir.ShowWindow(0);
	nad1.ShowWindow(0);
	sad1.ShowWindow(0);
	nad2.ShowWindow(0);
	sad2.ShowWindow(0);
	ndevise.ShowWindow(0);
	sdevise.ShowWindow(0);
	nnom.ShowWindow(0);
	snom.ShowWindow(0);
	nposte.ShowWindow(0);
	sposte.ShowWindow(0);
	sgl.ShowWindow(0);
	sgc.ShowWindow(0);
	sgs.ShowWindow(0);
	sge.ShowWindow(0);
	nnauto.ShowWindow(0);
	nvplace.ShowWindow(0);
	nvmix.ShowWindow(0);
	vplace.ShowWindow(0);
	vmix.ShowWindow(0);
	npauto.ShowWindow(0);
	nan.ShowWindow(0);
	san.ShowWindow(0);
	nmois.ShowWindow(0);
	smois.ShowWindow(0);
	bbur.ShowWindow(0);
	spect.ShowWindow(0);
	nspect.ShowWindow(0);
	guichet.ShowWindow(0);
	boffert.ShowWindow(0);
	version.ShowWindow(0);
	nserveur.ShowWindow(0);
	sserveur.ShowWindow(0);
	ventry.ShowWindow(0);
	nlangue.ShowWindow(0);
	slangue.ShowWindow(0);
	nvhor.ShowWindow(0);
	lnbap.ShowWindow(0);
	snaf.ShowWindow(0);
	nnaf.ShowWindow(0);
	netc.ShowWindow(0);
	nvpwd.ShowWindow(0);
	nvpage.ShowWindow(0);
	nvcontrol.ShowWindow(0);
	bentrymode.ShowWindow(0);
	bdel.ShowWindow(0);
	vactif.ShowWindow(0);
	tcontrol.ShowWindow(0);
	tnet.ShowWindow(0);
	tgate.ShowWindow(0);
	bman.ShowWindow(0);
	vexo.ShowWindow(0);
	vcbx.ShowWindow(0);
	vpass.ShowWindow(0);
	buser.ShowWindow(0);
	blogo.ShowWindow(0);
	bnet.ShowWindow(0);
	bprinter.ShowWindow(0);
	nlic.ShowWindow(0);
	slic0.ShowWindow(0);
	slic1.ShowWindow(0);
	slic2.ShowWindow(0);
	slic3.ShowWindow(0);
	slic4.ShowWindow(0);
	slic5.ShowWindow(0);
	slic6.ShowWindow(0);
	lselevt.ShowWindow(0);
	nscan.ShowWindow(0);
	sexer.ShowWindow(0);
	nexer.ShowWindow(0);
	spays.ShowWindow(0);
	npays.ShowWindow(0);
	ntva1.ShowWindow(0);
	sval1.ShowWindow(0);
	stva1.ShowWindow(0);
	lcb.ShowWindow(0);
	ltype.ShowWindow(0);
	ntva2.ShowWindow(0);
	stva2.ShowWindow(0);
	sval2.ShowWindow(0);
	wqr.ShowWindow(0);
	phqr.ShowWindow(0);
	wtqr.ShowWindow(0);
	int i=0;
	do
	{
		((CButton*)GetDlgItem(IDC_ART1+i))->ShowWindow(0);
		i++;
	}
	while(i<16);
	i=0;
	do
	{
		((CButton*)GetDlgItem(IDC_0+i))->ShowWindow(0);
		i++;
	}
	while(i<12);
	i=0;
	do
	{
		((CButton*)GetDlgItem(IDC_FAM1+i))->ShowWindow(0);
		i++;
	}
	while(i<3);
	i=0;
	do
	{
		((CButton*)GetDlgItem(IDC_RUB1+i))->ShowWindow(0);
		i++;
	}
	while(i<3);
	ndate.SetWindowPos(&wndTop,rctdate.left,rctdate.top,rctdate.Width(),rctdate.Height(),SWP_SHOWWINDOW   );
	DrawStaticArticle();
	DrawBoutonArticle(17);
	DrawBoutonConfArticle();
	DrawPageCom();
	UpdatePageEntree();
	RedrawWindow(0,0,1|256|RDW_ERASE);
	etdate=0;

}

void CConcertoDlg::DrawWindowControl()
{
	CString txt;
	CString temp;
	titretext=txtc[18];//Contrôle
	wsel=4;
	DrawPageCom();
	UpdatePageEntree();
	DrawBoutonGestion();
	DrawBoutonQuitter(txtc[77]);//Billetterie
	KillTimer(4);
	KillTimer(5);
	KillTimer(6);
	KillTimer(8);
	nprefix.ShowWindow(0);
	sprefix.ShowWindow(0);
	slibelcons.EnableWindow(0);
	slibel1.EnableWindow(0);
	slibel2.EnableWindow(0);
	spect.EnableWindow(0);
	guichet.EnableWindow(0);
	nmentiont.ShowWindow(0);
	nmentionp.ShowWindow(0);
	smentiont.ShowWindow(0);
	smentionp.ShowWindow(0);
	bplus.ShowWindow(0);
	bminus.ShowWindow(0);
	bpoub.ShowWindow(0);
	bpaste.ShowWindow(0);
	bcopy.ShowWindow(0);
	breturn.ShowWindow(0);
	lntick.ShowWindow(0);
	ldate.ShowWindow(0);
	lprix.ShowWindow(0);
	lcancel.ShowWindow(0);
	butprint.ShowWindow(0);
	bcancel.ShowWindow(0);
	bimport.ShowWindow(0);
	snaf.ShowWindow(0);
	nnaf.ShowWindow(0);
	butraz.ShowWindow(0);
	bcashview.ShowWindow(0);
	bcashclose.ShowWindow(0);
	ndate.ShowWindow(0);
	lcode.ShowWindow(0);
	lqte.ShowWindow(0);
	lptot.ShowWindow(0);
	total.ShowWindow(0);
	nlangue.ShowWindow(0);
	slangue.ShowWindow(0);
	ntotal.ShowWindow(0);
	sda.ShowWindow(0);
	esea.ShowWindow(0);
	sca.ShowWindow(0);
	sntt.ShowWindow(0);
	nvpwd.ShowWindow(0);
	wpage.ShowWindow(0);
	butinf.ShowWindow(0);
	butsup.ShowWindow(0);
	nvpage.ShowWindow(0);
	npage.ShowWindow(0);
	nvplace.ShowWindow(0);
	nvmix.ShowWindow(0);
	nserveur.ShowWindow(0);
	sserveur.ShowWindow(0);
	vplace.ShowWindow(0);
	vmix.ShowWindow(0);
	snta.ShowWindow(0);
	vexo.ShowWindow(0);
	vcbx.ShowWindow(0);
	vpass.ShowWindow(0);
	ent1.ShowWindow(0);
	ent2.ShowWindow(0);
	ent3.ShowWindow(0);
	ent4.ShowWindow(0);
	nsir.ShowWindow(0);
	ssir.ShowWindow(0);
	nad1.ShowWindow(0);
	sad1.ShowWindow(0);
	nad2.ShowWindow(0);
	sad2.ShowWindow(0);
	ndevise.ShowWindow(0);
	sdevise.ShowWindow(0);
	nnom.ShowWindow(0);
	netc.ShowWindow(0);
	snom.ShowWindow(0);
	nposte.ShowWindow(0);
	sposte.ShowWindow(0);
	sgl.ShowWindow(0);
	sgc.ShowWindow(0);
	sgs.ShowWindow(0);
	sge.ShowWindow(0);
	nnauto.ShowWindow(0);
	npauto.ShowWindow(0);
	nan.ShowWindow(0);
	san.ShowWindow(0);
	nmois.ShowWindow(0);
	smois.ShowWindow(0);
	bbur.ShowWindow(0);
	spect.ShowWindow(0);
	nspect.ShowWindow(0);
	guichet.ShowWindow(0);
	lcb.ShowWindow(0);
	ltype.ShowWindow(0);
	boffert.ShowWindow(0);
	version.ShowWindow(0);
	nlibel.ShowWindow(0);
	slibel1.ShowWindow(0);
	slibel2.ShowWindow(0);
	slibelcons.ShowWindow(0);
	nlibelcons.ShowWindow(0);
	sprix.ShowWindow(0);
	nprix.ShowWindow(0);
	ntva1.ShowWindow(0);
	sval1.ShowWindow(0);
	stva1.ShowWindow(0);
	ntva2.ShowWindow(0);
	stva2.ShowWindow(0);
	sval2.ShowWindow(0);
	vactif.ShowWindow(0);
	ncons.ShowWindow(0);
	scons.ShowWindow(0);
	lnbap.ShowWindow(0);
	nvhor.ShowWindow(0);
	nvcontrol.ShowWindow(0);
	bentrymode.ShowWindow(0);
	bdel.ShowWindow(0);
	tcontrol.ShowWindow(0);
	tnet.ShowWindow(0);
	tgate.ShowWindow(0);
	bman.ShowWindow(0);
	buser.ShowWindow(0);
	blogo.ShowWindow(0);
	bnet.ShowWindow(0);
	bprinter.ShowWindow(0);
	nlic.ShowWindow(0);
	slic0.ShowWindow(0);
	slic1.ShowWindow(0);
	slic2.ShowWindow(0);
	slic3.ShowWindow(0);
	slic4.ShowWindow(0);
	slic5.ShowWindow(0);
	slic6.ShowWindow(0);
	lselevt.ShowWindow(0);
	nscan.ShowWindow(0);
	sexer.ShowWindow(0);
	nexer.ShowWindow(0);
	ventry.ShowWindow(0);
	spays.ShowWindow(0);
	npays.ShowWindow(0);
	nvpage.ShowWindow(0);
	wqr.ShowWindow(0);
	phqr.ShowWindow(0);
	wtqr.ShowWindow(0);
	int i=0;
	do
	{
		((CButton*)GetDlgItem(IDC_ART1+i))->ShowWindow(0);
		i++;
	}
	while(i<16);
	i=0;
	do
	{
		((CButton*)GetDlgItem(IDC_0+i))->ShowWindow(0);
		i++;
	}
	while(i<12);
	i=0;
	do
	{
		((CButton*)GetDlgItem(IDC_FAM1+i))->ShowWindow(0);
		i++;
	}
	while(i<3);
	i=0;
	do
	{
		((CButton*)GetDlgItem(IDC_RUB1+i))->ShowWindow(0);
		i++;
	}
	while(i<3);
	ndate.SetWindowPos(&wndTop,rctdate.left,rctdate.top,rctdate.Width(),rctdate.Height(),SWP_SHOWWINDOW   );
	DrawBoutonControl();
	DrawBoutonArticle(17);
	RedrawWindow(0,0,1|256|RDW_ERASE);
	InterlockedExchange(&FREFCONTROL,1);//Flag demandant de rafraichir la liste de controle avec timer 13
	SetTimer(13,1000,NULL);
	etdate=0;
}

void CConcertoDlg::ClearWindow()
{
	CString txt;
	CString temp;
	wsel=0;
	ntva1.ShowWindow(0);
	sval1.ShowWindow(0);
	stva1.ShowWindow(0);
	ntva2.ShowWindow(0);
	stva2.ShowWindow(0);
	sval2.ShowWindow(0);
	nprefix.ShowWindow(0);
	sprefix.ShowWindow(0);
	nmentiont.ShowWindow(0);
	nmentionp.ShowWindow(0);
	smentiont.ShowWindow(0);
	smentionp.ShowWindow(0);
	bconfig.ShowWindow(0);
	bresult.ShowWindow(0);
	bart.ShowWindow(0);
	bconfig.ShowWindow(0);
	bcontrol.ShowWindow(0);
	butquitter.ShowWindow(0);
	lntick.ShowWindow(0);
	ldate.ShowWindow(0);
	lprix.ShowWindow(0);
	lcancel.ShowWindow(0);
	butinf.ShowWindow(0);
	butsup.ShowWindow(0);
	butprint.ShowWindow(0);
	bplus.ShowWindow(0);
	bminus.ShowWindow(0);
	bpoub.ShowWindow(0);
	breturn.ShowWindow(0);
	bimport.ShowWindow(0);
	bcancel.ShowWindow(0);
	butraz.ShowWindow(0);
	bcashview.ShowWindow(0);
	bcashclose.ShowWindow(0);
	ndate.ShowWindow(0);
	lcode.ShowWindow(0);
	lqte.ShowWindow(0);
	lptot.ShowWindow(0);
	total.ShowWindow(0);
	ntotal.ShowWindow(0);
	sda.ShowWindow(0);
	vpass.ShowWindow(0);
	esea.ShowWindow(0);
	sca.ShowWindow(0);
	lcb.ShowWindow(0);
	ltype.ShowWindow(0);
	sntt.ShowWindow(0);
	snta.ShowWindow(0);
	ent1.ShowWindow(0);
	ent2.ShowWindow(0);
	ent3.ShowWindow(0);
	ent4.ShowWindow(0);
	nsir.ShowWindow(0);
	ssir.ShowWindow(0);
	nad1.ShowWindow(0);
	sad1.ShowWindow(0);
	nad2.ShowWindow(0);
	sad2.ShowWindow(0);
	ndevise.ShowWindow(0);
	sdevise.ShowWindow(0);
	nnom.ShowWindow(0);
	snom.ShowWindow(0);
	nposte.ShowWindow(0);
	sposte.ShowWindow(0);
	sgl.ShowWindow(0);
	sgc.ShowWindow(0);
	sgs.ShowWindow(0);
	sge.ShowWindow(0);
	nnauto.ShowWindow(0);
	vexo.ShowWindow(0);
	vcbx.ShowWindow(0);
	nvplace.ShowWindow(0);
	nvmix.ShowWindow(0);
	vplace.ShowWindow(0);
	vmix.ShowWindow(0);
	npauto.ShowWindow(0);
	nan.ShowWindow(0);
	san.ShowWindow(0);
	nmois.ShowWindow(0);
	smois.ShowWindow(0);
	bbur.ShowWindow(0);
	spect.ShowWindow(0);
	nspect.ShowWindow(0);
	guichet.ShowWindow(0);
	snaf.ShowWindow(0);
	nnaf.ShowWindow(0);
	boffert.ShowWindow(0);
	version.ShowWindow(0);
	nlangue.ShowWindow(0);
	slangue.ShowWindow(0);
	ventry.ShowWindow(0);
	nvhor.ShowWindow(0);
	lnbap.ShowWindow(0);
	netc.ShowWindow(0);
	nserveur.ShowWindow(0);
	sserveur.ShowWindow(0);
	nvpwd.ShowWindow(0);
	nvpage.ShowWindow(0);
	nvcontrol.ShowWindow(0);
	bentrymode.ShowWindow(0);
	bdel.ShowWindow(0);
	vactif.ShowWindow(0);
	tcontrol.ShowWindow(0);
	tnet.ShowWindow(0);
	tgate.ShowWindow(0);
	bman.ShowWindow(0);
	buser.ShowWindow(0);
	blogo.ShowWindow(0);
	bnet.ShowWindow(0);
	bprinter.ShowWindow(0);
	nlic.ShowWindow(0);
	slic0.ShowWindow(0);
	slic1.ShowWindow(0);
	slic2.ShowWindow(0);
	slic3.ShowWindow(0);
	slic4.ShowWindow(0);
	slic5.ShowWindow(0);
	slic6.ShowWindow(0);
	lselevt.ShowWindow(0);
	nscan.ShowWindow(0);
	sexer.ShowWindow(0);
	nexer.ShowWindow(0);
	spays.ShowWindow(0);
	npays.ShowWindow(0);
	wpage.ShowWindow(0);
	etdate=0;
	wqr.ShowWindow(0);
	phqr.ShowWindow(0);
	wtqr.ShowWindow(0);
	etdate=0;
	int i=0;
	do
	{
		((CButton*)GetDlgItem(IDC_ART1+i))->ShowWindow(0);
		i++;
	}
	while(i<16);
	i=0;
	do
	{
		((CButton*)GetDlgItem(IDC_0+i))->ShowWindow(0);
		i++;
	}
	while(i<12);
	i=0;
	do
	{
		((CButton*)GetDlgItem(IDC_FAM1+i))->ShowWindow(0);
		i++;
	}
	while(i<3);
	i=0;
	do
	{
		((CButton*)GetDlgItem(IDC_RUB1+i))->ShowWindow(0);
		i++;
	}
	while(i<3);
	ndate.SetWindowPos(&wndTop,rctdate.left,rctdate.top,rctdate.Width(),rctdate.Height(),SWP_SHOWWINDOW   );
	RedrawWindow(0,0,1|256|RDW_ERASE);

}

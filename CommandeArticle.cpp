#include "stdafx.h"
#include "ConcertoDlg.h"
#include "Concerto.h"
#include "Num.h"
#include "Message.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void CConcertoDlg::OnBnClickedArticle()
{
		CloseKeyboard();
		hist=0;
		artnum=1;
		artrange=fpage;
		seltouche=0;
		//ClearStat();
		DrawWindowArticle();
		//FillStat(1);
		//UpdateEntreeListe(1);
		WritePrivateProfileString("Main","Site","1",workdir+"\\FreeVK.ini");
		WritePrivateProfileString("Main","Colors","4",workdir+"\\FreeVK.ini");
		WritePrivateProfileString("Main","AutoClick","1",workdir+"\\FreeVK.ini");
		WritePrivateProfileString("Main","FitWidth","1",workdir+"\\FreeVK.ini");
		WritePrivateProfileString("Main","AlphaBlend","255",workdir+"\\FreeVK.ini");
		WritePrivateProfileString("Main","TMainFormTop","650",workdir+"\\FreeVK.ini");
		WritePrivateProfileString("Main","TMainFormLeft","0",workdir+"\\FreeVK.ini");
		WritePrivateProfileString("Main","TMainFormHeight","300",workdir+"\\FreeVK.ini");
		WritePrivateProfileString("Main","TMainFormWidth","1280",workdir+"\\FreeVK.ini");
		WritePrivateProfileString("Main","TMainFormState","0",workdir+"\\FreeVK.ini");
		WritePrivateProfileString("Main","Keyboard","3",workdir+"\\FreeVK.ini");

		OnBnClickedArt1();
}
void CConcertoDlg::OnBnClickedCopy()
{	// Copie les paramètres de l'article dans le presse papier
	int i=artnum+(artrange*NAPP);	// Index article sélectionné
	perso[0]=perso[i];
	artim[0]=artim[i];
	libel1[0]=libel1[i];
	libel2[0]=libel2[i];
	libelspect[0]=libelspect[i];
	libelcons[0]=libelcons[i];
	prix[0]=prix[i];
	tva1[0]=tva1[i];
	tva2[0]=tva2[i];
	val1[0]=val1[i];
	val2[0]=val2[i];
	conso[0]=conso[i];
	entrymode[0]=entrymode[i];
	spectsel[0]=spectsel[i];
	artim[0]=artim[i];
	idxcopy=i;	// Mémoire de l'index de l'article copié
}
void CConcertoDlg::OnBnClickedPaste()
{	// Copie les paramètres du  presse papier dans l'article
	int i=artnum+(artrange*NAPP);
	CStringW wstr;	
	CString temp;	
	if(artro==0||fadmin)
	{
		if(i>0&&i!=idxcopy)
		{
			perso[i]=perso[0];
			artim[i]=artim[0];
			libel1[i]=libel1[0];
			libel2[i]=libel2[0];
			libelspect[i]=libelspect[0];
			libelcons[i]=libelcons[0];
			prix[i]=prix[0];
			tva1[i]=tva1[0];
			tva2[i]=tva2[0];
			val1[i]=val1[0];
			val2[i]=val2[0];
			conso[i]=conso[0];
			entrymode[i]=entrymode[0];
			spectsel[i]=spectsel[0];
			artim[i]=artim[0];
			wstr=workdir+artim[i];
			delete part[i];
			part[i]=Image::FromFile(wstr,0);
			temp.Format("%u",i);
			AfxGetApp()->WriteProfileString(temp,"IMAGE",artim[i]);
			FillStat(i);
			if(afmode)
			{
				InterlockedExchange(&FIM,1);				
				RefreshImage();
			}
			SaveStaticArticle();
		}
	}
	else
	{
		CMessage dlg;
		CString temp1;
		temp1=txtm[18];//"La billetterie doit être cloturée";
		dlg.mes1=temp1;
		dlg.mes2=" ";
		dlg.mes3=" ";
		dlg.mode=1;
		dlg.DoModal();
	}
}

void CConcertoDlg::OnEnSetfocusLibel1()
{
	CString temp;
	int idx=artnum+(artrange*NAPP);
	if(wsel==3&&((idx<82&&serveur!="")||serveur==""))
	{
		if(master||(fadmin&&master))//
		{
			slibel1.GetWindowTextA(libelsave);//libel[artnum]
			kid=slibel1.GetDlgCtrlID();
			PostMessage(WM_USER+13,0,0);
		}
		else
		{
			sdum.SetFocus();
		}
	}
	else
		sdum.SetFocus();
}

void CConcertoDlg::OnEnSetfocusLibel2()
{
	CString temp;
	int idx=artnum+(artrange*NAPP);
	if(wsel==3&&((idx<82&&serveur!="")||serveur==""))
	{	
		if(master||(fadmin&&master))
		{
			slibel2.GetWindowTextA(libelsave);//libel[artnum]
			kid=slibel2.GetDlgCtrlID();
			PostMessage(WM_USER+13,0,0);
		}
		else
			sdum.SetFocus();
	}
	else
		sdum.SetFocus();
}

void CConcertoDlg::OnEnMaxtextLibel1()//passage auto sur l'edit libel 2
{
	CloseKeyboard();
	slibel2.SetFocus();
	slibel2.PostMessage(memmes,memw,meml);	
}
void CConcertoDlg::OnEnSetfocusLibelspect()
{
	CMessage dlg;
	CString timetxt;
	CloseKeyboard();

	int idx=artnum+(artrange*NAPP);
	if(wsel==3&&fprev)
	{	
		if(master||(fadmin&&master))
		{
			spect.GetWindowTextA(timetxt);
			spect.GetWindowTextA(libelsave);//libel[artnum]
			CString temp1;
			temp1=txtm[17];//Sélection de la date de l'évènement
			dlg.mes1="*** "+temp1+" ***";
			dlg.mes2=" ";
			dlg.mes3=" ";
			dlg.mode=4;	
			if(entrymode[idx]==0)
			{
				kid=spect.GetDlgCtrlID();
				PostMessage(WM_USER+13,0,0);
			}
			else
			{
				if(dlg.DoModal()==IDOK&&wsel==3&&entrymode[idx]>=1)
				{
					CTime curdate=CTime::GetCurrentTime();
					CTime date(curdate.GetYear(),curdate.GetMonth(),curdate.GetDay(),0,0,0,-1);
					if(dlg.seldate>=date)
					{
						spect.SetSel(0,-1,FALSE);
						spect.ReplaceSel(dlg.date,FALSE );
						SaveStaticArticle();
					}
				}
			}
		}
		else
			sdum.SetFocus();
	}
	else
		sdum.SetFocus();
}

void CConcertoDlg::OnEnSetfocusLibelguichet()
{
	CString temp;
	int idx=artnum+(artrange*NAPP);
	if(wsel==3&&fprev)
	{
		if(master||(fadmin&&master))
		{
			guichet.GetWindowTextA(libelsave);//libel[artnum]
			kid=guichet.GetDlgCtrlID();
			PostMessage(WM_USER+13,0,0);
			//Klance();
		}
		else
			sdum.SetFocus();
	}
	else
		sdum.SetFocus();
}

void CConcertoDlg::OnEnSetfocusLibelcons()
{
	int idx=artnum+(artrange*NAPP);
	if(wsel==3&&((idx<82&&serveur!="")||serveur==""))
	{	
		if((master&&entrymode[idx]==0)||(fadmin&&master))
		{
			slibelcons.GetWindowTextA(libelsave);//libel[artnum]
			kid=slibelcons.GetDlgCtrlID();
			PostMessage(WM_USER+13,0,0);
			//Klance();
		}
		else
			sdum.SetFocus();
	}
	else
		sdum.SetFocus();
}

void CConcertoDlg::OnStnClickedPrix()
{
	int idx=artnum+(artrange*NAPP);
	double prx;
	if((master||fadmin)&&((idx<82&&serveur!="")||serveur==""))
	{
		if((artro==0||fadmin)&&master)
		{
			CloseKeyboard();
			sprix.GetWindowTextA(libelsave);
			CNum* pnum=new CNum ();
			pnum->wlargeur=(int)((float)(wlargeur/2));
			pnum->whauteur=whauteur/3;
			pnum->nID=IDC_PRIX;
			pnum->chiffre = 6;
			pnum->mode=3;
			pnum->nombre="";
			pnum->DoModal();
			if(pnum->nombre=="")
				pnum->nombre=libelsave;
			prx=atof(pnum->nombre);
			delete pnum;
			if(perso[idx]==1)
			{
				val1[idx]=prx;
				val2[idx]=0;
			}
			else
			{
				if(tva1[idx]==0||tva2[idx]==0)
				{
					if(tva1[idx]==0)
						val2[idx]=prx-val1[idx];
					if(tva2[idx]==0)
						val1[idx]=prx-val2[idx];
				}
				else
				{
					if(prix[idx]>0)
					{
						val1[idx]=val1[idx]*(prx/prix[idx]);
						val2[idx]=prx-val1[idx];
					}
				}
			}
			prix[idx]=prx;
			SaveStaticArticle();
		}
		else
		{
			if(master)
			{
				CMessage dlg;
				CString temp1;
				temp1=txtm[18];//"La billetterie doit être cloturée";
				dlg.mes1=temp1;
				dlg.mes2=" ";
				dlg.mes3=" ";
				dlg.mode=1;
				dlg.DoModal();
			}
		}
	}
}
void CConcertoDlg::OnStnClickedVal1()
{
	int idx=artnum+(artrange*NAPP);
	if((master||fadmin)&&perso[idx]&4&&tva1[idx]>0&&((idx<82&&serveur!="")||serveur==""))
	{
		if((artro==0||fadmin)&&master)
		{
			CloseKeyboard();
			sval1.GetWindowTextA(libelsave);
			CNum* pnum=new CNum ();
			pnum->wlargeur=(int)((float)(wlargeur/2));
			pnum->whauteur=whauteur/3;
			pnum->nID=IDC_VAL1;
			pnum->chiffre = 6;
			pnum->mode=3;
			pnum->nombre="";
			pnum->DoModal();
			if(atof(pnum->nombre)<=prix[idx]&&pnum->nombre!="")
			{
				if(pnum->nombre!="2/3")
					val1[idx]=atof(pnum->nombre);
				else
					val1[idx]=2*prix[idx]/3;
				val2[idx]=prix[idx]-val1[idx];
				SaveStaticArticle();
			}
			else
				sval1.SetWindowTextA(libelsave);
			delete pnum;
		}
		else
		{
			if(master)
			{
				CMessage dlg;
				CString temp1;
				temp1=txtm[18];//"La billetterie doit être cloturée";
				dlg.mes1=temp1;
				dlg.mes2=" ";
				dlg.mes3=" ";
				dlg.mode=1;
				dlg.DoModal();
			}
		}
	}
}
void CConcertoDlg::OnStnClickedVal2()
{
	int idx=artnum+(artrange*NAPP);
	if((master||fadmin)&&tva2[idx]>0&&((idx<82&&serveur!="")||serveur==""))
	{
		if((artro==0||fadmin)&&master)
		{
			CloseKeyboard();
			sval2.GetWindowTextA(libelsave);
			CNum* pnum=new CNum ();
			pnum->wlargeur=(int)((float)(wlargeur/2));
			pnum->whauteur=whauteur/3;
			pnum->nID=IDC_VAL2;
			pnum->chiffre = 6;
			pnum->mode=3;
			pnum->nombre="";
			pnum->DoModal();
			if(atof(pnum->nombre)<=prix[idx]&&pnum->nombre!="")
			{
				if(pnum->nombre!="1/3")
					val2[idx]=atof(pnum->nombre);
				else
					val2[idx]=prix[idx]/3;
				val1[idx]=prix[idx]-val2[idx];
				SaveStaticArticle();
			}
			else
				sval2.SetWindowTextA(libelsave);
			delete pnum;
		}
		else
		{
			if(master)
			{
				CMessage dlg;
				CString temp1;
				temp1=txtm[18];//"La billetterie doit être cloturée";
				dlg.mes1=temp1;
				dlg.mes2=" ";
				dlg.mes3=" ";
				dlg.mode=1;
				dlg.DoModal();
			}
		}
	}
}

void CConcertoDlg::OnStnClickedScons()
{
	CString temp;
	CString temp1;
	int idx=artnum+(artrange*NAPP);
	CString nart;
	nart.Format("%u",idx);
	if((master||fadmin)&&((idx<82&&serveur!="")||serveur==""))
	{
		if((artro==0||fadmin)&&master)
		{
			CloseKeyboard();
			CNum* pnum=new CNum ();
			pnum->wlargeur=(int)((float)(wlargeur/2));
			pnum->whauteur=whauteur/3;
			pnum->nID=IDC_SCONS;
			pnum->chiffre = 2;
			pnum->mode=0;
			pnum->nombre="";
			pnum->DoModal();
			delete pnum;
			scons.GetWindowText(temp);
			BYTE bcons;
			if(valexo>0)
			{
				conso[idx]=(conso[idx]&0xFF00)+atoi(temp); //nb exo
				bcons=(BYTE)(((conso[idx]&0xFF00)>>8));
				bcons++;
			}
			else
			{
				conso[idx]=atoi(temp); //nb item
				bcons=(BYTE)(conso[idx]&0xFF);
			}
			/*temp1.Format(" bcons= %u",bcons);
			temp.Format(" conso= %u -> ",conso[idx]);
			MessageBox(temp+temp1);*/

			if(bcons==0)
			{
				vcbx.ShowWindow(0); // cache la liste ETC
			}
			else
			{
				if(eflag == 1)
				{
					vcbx.ShowWindow(1);
					cbx = (perso[idx]& 0xff0000)>>16;
					if(cbx <= pl.GetCount())
					{
						vcbx.SetWindowText("");//redessine
					}
				}
			}
			AfxGetApp()->WriteProfileInt(nart,"CONSO",conso[idx]);
			SaveStaticArticle();

		}
		else
		{
			if(master)
			{
				CMessage dlg;
				CString temp1;
				temp1=txtm[18];//"La billetterie doit être cloturée";
				dlg.mes1=temp1;
				dlg.mes2=" ";
				dlg.mes3=" ";
				dlg.mode=1;
				dlg.DoModal();
			}
		}
	}
}

void CConcertoDlg::OnStnClickedValplace()
{
	int idx=artnum+(artrange*NAPP);
	CString temp1;
	if(master&&((idx<82&&serveur!="")||serveur==""))
	{
		if((artro==0||fadmin))
		{
			CloseKeyboard();		
			if(valplace)
			{
				valplace=0;
			}
			else
			{
				valplace=1;
			}
			temp1=txtc[59];//"Place"
			vplace.SetWindowTextA(temp1);
			SaveStaticArticle();
		}
		else
		{
			CMessage dlg;
			temp1=txtm[18];//"La billetterie doit être cloturée";
			dlg.mes1=temp1;
			dlg.mes2=" ";
			dlg.mes3=" ";
			dlg.mode=1;
			dlg.DoModal();
		}
	}
}
void CConcertoDlg::OnStnClickedValactif()
{
	CString temp1;
	int idx=artnum+(artrange*NAPP);
	if((idx<82&&serveur!="")||serveur=="")
	{
		if(artro==0||fadmin)
		{
			CloseKeyboard();		
			if(valactif)
			{
				valactif=0;
			}
			else
			{
				valactif=1;
			}
			temp1=txtc[133];//"Actif"
			vactif.SetWindowTextA(temp1);
			SaveStaticArticle();
		}
		else
		{
			CMessage dlg;
			temp1=txtm[18];//"La billetterie doit être cloturée";
			dlg.mes1=temp1;
			dlg.mes2=" ";
			dlg.mes3=" ";
			dlg.mode=1;
			dlg.DoModal();
		}
	}
}
void CConcertoDlg::OnStnClickedVpass()
{
	int idx=artnum+(artrange*NAPP);
	CString temp;
	int j;
	if(master&&cvalpass&&((idx<82&&serveur!="")||serveur==""))
	{
		if((artro==0||fadmin))
		{
			CloseKeyboard();		
			if(valpass)
			{
				valpass=0;
				vexo.ShowWindow(0);
				ncons.ShowWindow(0);
				scons.ShowWindow(0);
				valexo=0;
			}
			else
			{
				ltmp.ResetContent();
				for(j=2;j<=7;j++)
				{
					temp.Format("%u ",j);
					ltmp.SetItemData(ltmp.AddString(temp+txtc[152]),j);						
				}
				CCombo dlg;
				vpass.GetWindowRect(&dlg.rctstat);
				dlg.rctstat.top=dlg.rctstat.bottom;
				dlg.winh=(int)(htou/4);
				dlg.type=5;
				dlg.DoModal();
				if(dlg.sel>=0)
				{
					valpass=(int)ltmp.GetItemData(dlg.sel);
					vpass.ShowWindow(1);
					vexo.ShowWindow(1);
				}
				else
				{
					valpass=0;
					vexo.ShowWindow(0);
					ncons.ShowWindow(0);
					scons.ShowWindow(0);
				}
				dlg.DestroyWindow();
			}
			vpass.SetWindowTextA("");
			SaveStaticArticle();
		}
		else
		{
			CMessage dlg;
			dlg.mes1=txtm[18];//"La billetterie doit être cloturée";
			dlg.mes2=" ";
			dlg.mes3=" ";
			dlg.mode=1;
			dlg.DoModal();
		}
	}
}

// case EXO cochée
void CConcertoDlg::OnStnClickedVexo()
{
	int idx=artnum+(artrange*NAPP);
	CString temp1;
	CString temp;
	CString temp2;
	CString nart;
	nart.Format("%u",idx);
	int j;
	if(master&&((idx<82&&serveur!="")||serveur==""))
	{
		if((artro==0||fadmin))
		{
			CloseKeyboard();		
			if(valexo) //exo coché
			{
				valexo=0;
				if(entrymode[idx]==0) // entree immediate 
				{
					ncons.ShowWindow(1);
					ncons.SetWindowTextA(txtc[66]);//Nb Items
					conso[idx]=((conso[idx]>>8)+1)&0x00FF;
					temp1.Format("%u",conso[idx]);
					scons.ShowWindow(1);
				}
				else
				{
					ncons.ShowWindow(0);
					ncons.SetWindowTextA(txtc[66]);//Nb Items
					conso[idx]=0;
					temp1.Format("%u",conso[idx]);
					scons.ShowWindow(0);
				}
			}
			else
			{
				ltmp.ResetContent();
				for(j=1;j<=NART;j++)// cherche EXO
				{
					if((prix[j]==0&&(libel1[j]!=""||libel2[j]!=""))&&((entrymode[idx]==0&&((conso[j]&0x00FF)==0&&(perso[j]&1)))||(entrymode[idx]>0&&(conso[j]&0x00FF)>0)))
						ltmp.SetItemData(ltmp.AddString(libel1[j]+libel2[j]),j);	// les EXO					
				}
				if(ltmp.GetCount()>0)
				{
					valexo=0;
					CCombo dlg;
					vexo.GetWindowRect(&dlg.rctstat);
					dlg.rctstat.top=dlg.rctstat.bottom;
					dlg.winh=(int)(htou/4);
					dlg.type=5;
					dlg.DoModal();
					if(dlg.sel>=0)
						valexo=(int)ltmp.GetItemData(dlg.sel); // n°article qui est exo 1..99
					dlg.DestroyWindow();
					if(valexo>0)
					{
						if(entrymode[idx]==0)// entree immediate 
						{
							ncons.ShowWindow(1);
							ncons.SetWindowTextA(txtc[146]);//Nb Exo
							BYTE bcons=conso[idx]-1;
							conso[idx]=bcons;
							conso[idx]=(conso[idx]<<8)&0xFF00;
							temp1.Format("%u",conso[idx]&0x00FF);
							scons.ShowWindow(1);
						}
						else
						{
							ncons.ShowWindow(0);
							conso[idx]=1;
							temp1.Format("%u",conso[idx]&0x00FF);
							scons.ShowWindow(0);
						}
					}
					else
					{
						valexo=0;
						if(entrymode[idx]>0)
						{
							conso[idx]=0;
							ncons.ShowWindow(0);
							scons.ShowWindow(0);
							temp1.Format("%u",conso[idx]&0x00FF);
						}
						temp1.Format("%u",conso[idx]);
					}
				}
				else
				{
					valexo=0;
				}
			}
			if(eflag==1)
			{
				BYTE bcons;
				if(valexo>0)
				{
					bcons=(BYTE)(((conso[idx]&0xFF00)>>8));
					bcons++;
				}
				else
					bcons=(BYTE)(conso[idx]&0xFF);
				/*temp2.Format(" bcons= %u",bcons);
				temp.Format(" conso= %u -> ",conso[idx]);
				MessageBox(temp+temp2);*/
				if(bcons>0)
				{
					vcbx.ShowWindow(1);
					cbx = (perso[idx]& 0xff0000)>>16;
					if(cbx <= pl.GetCount())
					{
						vcbx.SetWindowText("");//redessine
					}
				}
				else
					vcbx.ShowWindow(0);
			}

			vexo.SetWindowTextA(txtc[133]);
			AfxGetApp()->WriteProfileInt(nart,"CONSO",conso[idx]);
			scons.SetWindowTextA(temp1);
			SaveStaticArticle();

		}
		else
		{
			CMessage dlg;
			temp1=txtm[18];//"La billetterie doit être cloturée";
			dlg.mes1=temp1;
			dlg.mes2=" ";
			dlg.mes3=" ";
			dlg.mode=1;
			dlg.DoModal();
		}
	}
}
void CConcertoDlg::OnStnClickedVcbx()
{
	int idx=artnum+(artrange*NAPP);
	CString temp1;
	CString nart;
	nart.Format("%u",idx);
	int j;
	if(master&&((idx<82&&serveur!="")||serveur==""))
	{
		if((artro==0||fadmin))
		{
			CloseKeyboard();		
			ltmp.ResetContent();
			for(int i=0; i<pl.GetCount() ; i++)
			{
				pl.GetText(i, temp1);
				ltmp.AddString(temp1);// A à T
			}
			if(ltmp.GetCount()>0)
			{
				CCombo dlg;
				vcbx.GetWindowRect(&dlg.rctstat); // recupere la taille de vactiv idem vbx
				dlg.rctstat.DeflateRect(0,0,dlg.rctstat.Width()-(dlg.rctstat.Height()-dlg.rctstat.Height()/2),0);// largeur de liste a la taille de la lettre
				dlg.winh=(int)(htou/7);//hauteur entre les lettres
				dlg.type=7;
				dlg.DoModal();
				if(dlg.sel>=0)
				{
					cbx=dlg.sel;
				}
				dlg.DestroyWindow();
			}
			else
			{
				cbx=0;
			}
			vcbx.SetWindowTextA("");
			SaveStaticArticle();
		}
		else
		{
			CMessage dlg;
			temp1=txtm[18];//"La billetterie doit être cloturée";
			dlg.mes1=temp1;
			dlg.mes2=" ";
			dlg.mes3=" ";
			dlg.mode=1;
			dlg.DoModal();
		}
	}
}

void CConcertoDlg::OnStnClickedVentry()
{
	CString temp1;
	int idx=artnum+(artrange*NAPP);
	CString nart;
	nart.Format("%u",idx);
	if(master&&((idx<82&&serveur!="")||serveur==""))
	{
		if((artro==0||fadmin))
		{
			CloseKeyboard();		
			if(valentry)
			{
				valentry=0;
				if(nvalmix==1)
					vmix.ShowWindow(1);
				vexo.ShowWindow(1);
				valmix=0;
				valexo=0;
				valpass=0;
				vplace.ShowWindow(0);
				vpass.ShowWindow(0);
				conso[idx]=1;
				val2[idx]=0;
				tva2[idx]=0;
				temp1.Format("%u",conso[idx]);
				ncons.ShowWindow(1);
				ncons.SetWindowTextA(txtc[66]);//Nb Exo
				scons.ShowWindow(1);
				scons.SetWindowTextA(temp1);
				//nvcontrol.SetWindowText(txtc[161]);//  ATL PRODUIT
			}
			else
			{
				valentry=1;
				if(nvalplace)
					vplace.ShowWindow(1);
				valmix=0;
				vmix.ShowWindow(0);
				vexo.ShowWindow(0);
				valpass=0;
				vpass.ShowWindow(0);
				ncons.ShowWindow(1);
				ncons.SetWindowTextA(txtc[66]);//Nb Item
				conso[idx]=1;
				temp1.Format("%u",conso[idx]);
				scons.ShowWindow(1);
				scons.SetWindowTextA(temp1);
				val2[idx]=0;
				tva2[idx]=0;
				ntva1.SetWindowTextA(txtc[62]+" :");//TVA
				ntva2.ShowWindow(0);//TVA
				stva2.ShowWindow(0);//TVA
				sval2.ShowWindow(0);//TVA
				//nvcontrol.SetWindowText(txtc[4]+"\n"+txtc[5]);// ATL ENTREE IMMEDIATE
			}
			ventry.SetWindowTextA(txtc[133]);
			AfxGetApp()->WriteProfileInt(nart,"CONSO",conso[idx]);
			SaveStaticArticle();
		}
		else
		{
			CMessage dlg;
			dlg.mes1=txtm[18];//"La billetterie doit être cloturée";
			dlg.mes2=" ";
			dlg.mes3=" ";
			dlg.mode=1;
			dlg.DoModal();
		}
	}
}
void CConcertoDlg::OnStnClickedValmix()
{
	CString temp1;
	int idx=artnum+(artrange*NAPP);
	if(master&&((idx<82&&serveur!="")||serveur==""))
	{
		if((artro==0||fadmin))
		{
			CloseKeyboard();		
			temp1=txtc[62];//TVA
			if(valmix)
			{
				valmix=0;
				ntva1.SetWindowTextA(temp1+" :");
				ntva2.ShowWindow(0);
				stva2.ShowWindow(0);
				sval2.ShowWindow(0);
				val1[idx]=prix[idx];
			}
			else
			{
				valmix=1;
				val2[idx]=0;
				tva2[idx]=0;
				ntva1.SetWindowTextA(temp1+"1 :");//TVA
				ntva2.SetWindowTextA(temp1+"2 :");//TVA
				ntva2.ShowWindow(1);
				stva2.ShowWindow(1);
				sval2.ShowWindow(1);
			}
			temp1=txtc[131];//"Pack"
			vmix.SetWindowTextA(temp1);
			SaveStaticArticle();
		}
		else
		{
			CMessage dlg;
			temp1=txtm[18];
			dlg.mes1=temp1;//"La billetterie doit être cloturée";
			dlg.mes2=" ";
			dlg.mes3=" ";
			dlg.mode=1;
			dlg.DoModal();
		}
	}
}

void CConcertoDlg::OnEnSetfocusNlibel1()
{
	CloseKeyboard();
	SetFocus();
}

void CConcertoDlg::OnBnClickedImport()	//Importation de fichier de boutique WEB
{
	if(wsel==4&&master)	// Uniquement pour les maitres
		ImportTicketExterne();
}

void CConcertoDlg::OnStnClickedTva1()
{
	int idx=artnum+(artrange*NAPP);
	int i;
	if(wsel==5&&fadmin&&master&&artro==0)
	{
		CloseKeyboard();
		CNum* pnum=new CNum ();
		pnum->wlargeur=(int)((float)(wlargeur/2));
		pnum->whauteur=whauteur/3;
		pnum->nID=IDC_TVA1;
		pnum->chiffre = 4;
		pnum->mode=3;
		pnum->nombre="";
		pnum->DoModal();
		WriteConfigString("Client","TVA",pnum->nombre);
		TVA=pnum->nombre;
		delete pnum;
		if(TVA=="")
		{
			global=0;
		}
		else
		{
			global=1;
			tva1[0]=atof(TVA);
			TVA.Format("%.2f",tva1[0]);
			i=1;
			while(i<=NART)
			{
				if((idx<82&&serveur!="")||serveur=="")
					tva1[i]=atof(TVA);	
				i++;
			}
		}
		if(TVA!="")
			stva1.SetWindowTextA(TVA+"%");
		else
			stva1.SetWindowTextA("");
		FART=1;
		RefreshArticle();
	}
	else
	{
		if((master||fadmin)&&((idx<82&&serveur!="")||serveur==""))
		{
			if(wsel==3&&global==0)
			{
				if((artro==0||fadmin)&&master)
				{
					CloseKeyboard();
					CNum* pnum=new CNum ();
					pnum->wlargeur=(int)((float)(wlargeur/2));
					pnum->whauteur=whauteur/3;
					pnum->nID=IDC_TVA1;
					pnum->chiffre = 4;
					pnum->mode=3;
					pnum->nombre="";
					pnum->DoModal();
					SaveStaticArticle();
					delete pnum;
				}
				else
				{
					if(master)
					{
						CMessage dlg;
						CString temp1;
						temp1=txtm[18];//"La billetterie doit être cloturée";
						dlg.mes1=temp1;
						dlg.mes2=" ";
						dlg.mes3=" ";
						dlg.mode=1;
						dlg.DoModal();
					}
				}
			}
		}
	}
}
void CConcertoDlg::OnStnClickedTva2()
{
	int idx=artnum+(artrange*NAPP);
	if((master||fadmin)&&((idx<82&&serveur!="")||serveur==""))
	{
		if(wsel==3&&valmix)
		{
			if((artro==0||fadmin)&&master)
			{
				CloseKeyboard();
				CNum* pnum=new CNum ();
				pnum->wlargeur=(int)((float)(wlargeur/2));
				pnum->whauteur=whauteur/3;
				pnum->nID=IDC_TVA2;
				pnum->chiffre = 4;
				pnum->mode=3;
				pnum->nombre="";
				pnum->DoModal();
				delete pnum;
				SaveStaticArticle();
			}
			else
			{
				if(master)
				{
					CMessage dlg;
					CString temp1;
					temp1=txtm[18];//"La billetterie doit être cloturée";
					dlg.mes1=temp1;
					dlg.mes2=" ";
					dlg.mes3=" ";
					dlg.mode=1;
					dlg.DoModal();
				}
			}
		}
	}
}


void CConcertoDlg::OnBnClickedEntryMode()
{
	int idx=artnum+(artrange*NAPP);
	int i;
	CString temp;
	CString nart;
	CString temp1;
	CString temp2;
	if((master||fadmin)&&((idx<82&&serveur!="")||serveur==""))
	{
		CloseKeyboard();		
		if(artro==0||fadmin)//&&(entrymode[idx]>0)
		{
			entrymode[idx]++;
			if(((entrymode[idx]>=3&&valhor&&horaire)||(entrymode[idx]>=2&&valhor==0)))//mode entree immédiate
			{
				entrymode[idx]=0;
				target[idx]=0;
				//guichet.SetWindowTextA("");
				slibelcons.ShowWindow(1);
				nlibelcons.ShowWindow(1);
				ncons.ShowWindow(1);
				scons.ShowWindow(1);
				conso[idx]=1;
				scons.SetWindowTextA("1");
				valpass=0;
				valexo=0;
				temp1=txtc[4];//"Entrée
				temp2=txtc[5];//immédiate"
				nvcontrol.SetWindowText(temp1+"\n"+temp2);
				nspect.ShowWindow(0);
				spect.ShowWindow(0);
				guichet.ShowWindow(0);
				ventry.ShowWindow(1);
				vpass.ShowWindow(0);
				valmix=0;
				valentry=1;
				vmix.ShowWindow(0);
				vexo.ShowWindow(0);
				vpass.ShowWindow(0);
				val1[idx]=prix[idx];
				if(nvalplace)
					vplace.ShowWindow(1);
				else
					vplace.ShowWindow(0);
				slibel2.EnableWindow(1);
				scons.EnableWindow(1);
				vcbx.ShowWindow(1);
				cbx=0;
			}
			i=target[idx];
			if(i>0)
			{
				choraire[i]=entrymode[idx];
				temp.Format("%u",i);
				AfxGetApp()->WriteProfileInt(temp,"CHORAIRE",choraire[i]);
			}
			if(entrymode[idx]>0)//cas de prevente interne
			{
				if(entrymode[idx]==1)
					target[idx]=0;
				vmix.ShowWindow(0);
				ventry.	ShowWindow(0);
				vexo.ShowWindow(0);
				vcbx.ShowWindow(0);
				if(entrymode[idx]<2)
					valexo=0;
				if(cvalpass)
				{
					vpass.ShowWindow(1);
					valpass=(perso[idx]&0xF000)>>12;
					if(valpass>1)
					{
						vexo.ShowWindow(1);
					}
					else
					{
						vexo.ShowWindow(0);
					}
				}
				else
				{
					vpass.ShowWindow(0);
					vexo.ShowWindow(0);
				}
				vplace.ShowWindow(0);
				valplace=0;
				val2[idx]=0;
				tva2[idx]=0;
				sval2.ShowWindow(0);
				stva2.ShowWindow(0);
				ntva2.ShowWindow(0);
				temp1=txtc[8];
				if(valhor&&horaire&&entrymode[idx]==1)	
				{
					nvcontrol.SetWindowText(temp1+"\n"+txtc[9]);//"Prévente\nsans horaire");
				}
				else
				{
					if(valhor&&horaire&&entrymode[idx]==2)	
					{
						nvcontrol.SetWindowText(temp1+"\n"+txtc[10]);//avec horaire"
					}
					else
						nvcontrol.SetWindowText(temp1);//"Prévente");

				}
				nlibelcons.ShowWindow(0);
				slibelcons.ShowWindow(0);
				ncons.ShowWindow(0);
				scons.ShowWindow(0);
				nspect.SetWindowTextA(txtc[11]+" :");//Date event
				nspect.ShowWindow(1);
				spect.SetWindowPos(&wndTop,(int)(oltou+ltou),(int)(ohnum+7*htou/16),(int)(2.5*ltou/3+eltou),(int)(htou/4),SWP_SHOWWINDOW);
				guichet.SetWindowPos(&wndTop,(int)(oltou+2*ltou+eltou),(int)(ohnum+7*htou/16),(int)(2.5*ltou/3),(int)(htou/4),SWP_SHOWWINDOW);
				spect.EnableWindow(1);
				guichet.EnableWindow(1);
				scons.EnableWindow(0);
			}
			SaveStaticArticle();
		}
		else
		{
			if(master)
			{
				CloseKeyboard();
				CMessage dlg;
				CString temp1;
				temp1=txtm[18];//"La billetterie doit être cloturée"
				dlg.mes1=temp1;;
				dlg.mes2=" ";
				dlg.mes3=" ";
				dlg.mode=1;
				dlg.DoModal();
			}

		}
	}
}
void CConcertoDlg::OnStnClickedPage()
{
	CString temp;
	if(wsel==3&&master&&valpage)
	{
		libelsave=txtpage;
		txtpage="";
		kid=wpage.GetDlgCtrlID();
		PostMessage(WM_USER+13,0,0);
	}
}

CString CConcertoDlg::DiskSel()	// Recherche du disque de sauvegarde
{
	int i;
	int j;
	CString temp;
	CMessage msd;
	char ch=' ';
	CString disk;
	j=GetLogicalDriveStrings(500,disk.GetBuffer(500)); // Retrouve la liste des diques
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
		if(GetDriveType(temp)==DRIVE_REMOVABLE||(GetDriveType(temp)==DRIVE_FIXED&&fdev==1))
		{
			if(temp=="X:\\")
			{
				return temp;
			}
		}
		disk=disk.Left(i);
	}
	while(disk.GetLength()>3);
	return "";
}

void CConcertoDlg::RefreshArticle()
{
	int i;
	int nbrt;
	CString temp;
	CString art;
	CString article;
	CString client;
	CString couleur;
	CString buf;
	DWORD ln;
	DWORD rln;
	article="";
	HANDLE hf;
	if(FART&&master&&alone==0)
	{
		i=1;
		while(i<=NART)
		{
			article=article+libel1[i]+";";		// Libellé champ 1 +;
			article=article+libel2[i]+";";		// Libellé champ 2 +;
			article=article+libelcons[i]+";";	// Libellé champ conso +;
			article=article+libelspect[i]+";";	// Sans objet laisser vide +;

			temp.Format("%.2f",prix[i]);		// Prix TTC payé par le client +;
			article=article+temp+";";

			temp.Format("%.2f",tva1[i]);		// Taux TVA N° 1 ( en principe "20.00" Respecter le format x.xx) +;
			article=article+temp+";";
	
			temp.Format("%.2f",val1[i]);		// Valeur TTC au taux N°1 (Respecter le format x.xx) +;
			article=article+temp+";";

			temp.Format("%.2f",tva2[i]);		//  Taux TVA N° 2 ( en principe "10.00" sinon "0.00" si non utilisé Respecter le format x.xx) +;
			article=article+temp+";";

			temp.Format("%.2f",val2[i]);		// Valeur TTC au taux N°2 ("0.00" si non utilisé Respecter le format x.xx)+;
			article=article+temp+";";

			temp.Format("%u",perso[i]);			// paramètre de personnalisation du type d'article ("1"=entrée ou"0"=Item conso puis ajouter 4 si 2 TVA puis ajouter 8) +;
			article=article+temp+";";			

			temp.Format("%u",conso[i]);			// Nombre d'item acheté du même article "0" à "x" donnant droit à x-1 items supplémentaires + nombre d'exo;
			article=article+temp+";";

			temp.Format("%u",entrymode[i]);		// Type d'entrée : laissé a "0" +\r\n
			article=article+temp+"\r\n";
			i++;
		}
		buf="*ARTICLE*\r\n"+article+"*CLIENT*\r\n";

		client=nom+";";
		client+=adresse1+";";
		client+=adresse2+";";
		client+=siret+";";
		temp.Format("%u",autonews);
		client+=temp+";";
		temp.Format("%u",autoprint);
		client+=temp+";";
		client+=TVA+";";
		client+=cur+";";
		client+=lic[0]+";";
		client+=lic[1]+";";
		client+=lic[2]+";";
		client+=lic[3]+";";
		client+=lic[4]+";";
		client+=lic[5]+";";
		client+=lic[6]+";";
		client+=mentiont+";";
		client+=mentionp+";";
		temp.Format("%u",fprev);
		client+=temp+";";
		temp.Format("%u",nvalplace);
		client+=temp+";";
		temp.Format("%u",valpwd);
		client+=temp+";";
		temp.Format("%u",valpage);
		client+=temp+";";
		temp.Format("%u",NART);
		client+=temp+";";
		temp.Format("%u",NAPP);
		client+=temp+";";
		temp.Format("%u",eflag);
		client+=temp+";";
		temp.Format("%u",nvalmix);
		client+=temp+";";
		client+=langue+";";
		client+=pays+";";
		client+=serveur+";";
		temp.Format("%u",afmode);
		client+=temp+";";
		temp.Format("%u",horaire);
		client+=temp+";";
		temp.Format("%u",valhor);
		client+=temp+";";
		client+=naf;
		buf+=client;
		buf+="\r\n*PAGE*\r\n";
		for(i=0;i<20;i++)
		{
			buf+=pag[i]+";"+jour[i]+"\r\n";
		}
		buf+="\r\n*PRIX*\r\n";
		for(i=0;i<pl.GetCount();i++)
		{
			pl.GetText(i,temp);
			buf+=temp+"\r\n";
		}
		for(i=i;i<20;i++)// met des retour pour les prix vides
		{
			buf+="\r\n";
		}
		for(i=0;i<10;i++)
		{
			temp.Format("0%u",i);
			temp=temp.Right(2);
			nbrt=0;
			if(temp!=poste)
			{
retry:;
				hf=CreateFile(controldir+"\\Article"+temp+".dat",GENERIC_READ|GENERIC_WRITE,0,NULL,CREATE_NEW,FILE_ATTRIBUTE_NORMAL,NULL);
				if(hf!=INVALID_HANDLE_VALUE)
				{
					ln=buf.GetLength();
					WriteFile(hf,buf.GetBuffer(ln),ln,&rln,NULL);
					CloseHandle(hf);
				}
				else
				{
					Sleep(100);
					DeleteFile(controldir+"\\Article"+temp+".dat");
					goto retry;
				}
			}
		}
	}
	if (master)
	{
		InitFileArticle();
		FART=0;
	}
}
void CConcertoDlg::RefreshImage()
{// Un maître crée 9 fichiers de configuration d'image borne pour les esclaves
	int i;
	int nbrt;
	CString temp;
	CString buf="*ARTICLE*\r\n";
	DWORD ln;
	DWORD rln;
	HANDLE hf;
	if(FIM&&master&&alone==0)
	{
		i=1;
		while(i<=NART)
		{
			buf=buf+artim[i]+"\r\n";
			i++;
		}
		buf=buf+"*FAMILLE*\r\n";
		i=0;
		while(i<3)
		{
			buf=buf+famim[i]+"\r\n";
			i++;
		}
		buf=buf+"*RUBRIQUE*\r\n";
		i=0;
		while(i<9)
		{
			buf=buf+rubim[i]+"\r\n";
			i++;
		}
		for(i=0;i<10;i++)
		{
			temp.Format("0%u",i);
			temp=temp.Right(2);
			nbrt=0;
			if(temp!=poste)
			{
retry:;
				hf=CreateFile(controldir+"\\Borne"+temp+".dat",GENERIC_READ|GENERIC_WRITE,0,NULL,CREATE_NEW,FILE_ATTRIBUTE_NORMAL,NULL);
				if(hf!=INVALID_HANDLE_VALUE)
				{
					ln=buf.GetLength();
					WriteFile(hf,buf.GetBuffer(ln),ln,&rln,NULL);
					CloseHandle(hf);
				}
				else
				{
					Sleep(100);
					DeleteFile(controldir+"\\Borne"+temp+".dat");
					goto retry;
				}
			}
		}
		InterlockedExchange(&FIM,0);
	}
}

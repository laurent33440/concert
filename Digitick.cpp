#include "stdafx.h"
#include "Concerto.h"
#include "ConcertoDlg.h"

void CConcertoDlg::SendDigitickSpooler()
{
	CString temp1;
	CString place="";
	int j;
	for(j=1;j<=NART;j++)
	{
		if(prix[j]==0&&(libel1[j]!=""||libel2[j]!="")&&(conso[j])==0&&(perso[j]&1))
			break;						
	}
	if(j<=NART)
	{
		if(nvalplace&&(perso[j]&2))
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
					CString temp1;
					CString temp2;
					CString temp3;
					temp1=txtm[75];//Le gestionnaire de place n'est pas connecté.
					temp2=txtm[76];//L'impression est annulée.
					temp3=txtm[77];//Veuillez vérifier votre connection.
					dlg.mes1=temp1;
					dlg.mes2=temp2;
					dlg.mes3=temp3;
					dlg.mode=1;
					dlg.DoModal();
					goto abort;
				}
			}
			temp1=txtc[59];//Place
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
				pnum->txtmessage=temp1;
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
				SPT[SPW]=j;
				STT[SPW]=place;
				IncSpoolIndex(&SPW);
				InterlockedIncrement(&SPN);
			}
		}
		else
		{
			place="";
			SPX[SPW]=1;
			SPT[SPW]=j;
			STT[SPW]=place;
			IncSpoolIndex(&SPW);
			InterlockedIncrement(&SPN);
		}
		RefreshControle();
		RefreshControlList();
	}
abort:;
}

int CConcertoDlg::ControlDigitick(CString billet,int remove)
{
	CString temp;
	CString ligne;
	int istop=0;
	int istart=0;
	int idx=0;
	int idy=0;
	int idz=0;
	int wdg=0;
	HANDLE hf;
	CString touche;
	CString ntouche;
	CString dir;
	CString buf;
	CString buftail;
	CString bufhead;
	DWORD nbw;
	int i=1;
	valid=0;
	while(i<=16)
	{
		temp.Format("%u",i);
		if(AfxGetApp()->GetProfileInt(temp,"CONTROLE",0)==1)
		{
			if(temp.GetLength()==1)
				temp="0"+temp;
			if(master==0&&controldir==netcontdir)
			{
				MessageBox("Serveur controle absent");
				break;
			}
			if(master)
				dir=controldir+"\\"+temp;
			else
				dir=netcontdir+"\\"+temp;
retry:;
			hf=(CreateFile(dir+"\\Controle.dat",GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL));
			if(hf==INVALID_HANDLE_VALUE)
			{
				Sleep(100);
				wdg++;
				if(wdg<10)
					goto retry;
				break;
			}
			else
			{
				if(ReadFile(hf,buf.GetBuffer(GetFileSize(hf,NULL)),GetFileSize(hf,NULL),&nbw,NULL))
				{
					buf.ReleaseBuffer(nbw);
					istart=0;
					if((istop=buf.Find(billet,istart))!=-1)
					{
						if(remove==0)
						{						
							istart=buf.Find("\r\n",istop);
							if(buf.GetAt(istart-1)=='X')
							{
								CloseHandle(hf);
								valid=-1;
								return valid;
							}
							buf.Insert(istart,"X");
							ligne="-"+buf.Mid(istop,istart-istop+1)+"-";
							SetFilePointer(hf,NULL,NULL,FILE_BEGIN);
							WriteFile(hf,buf.GetBuffer(buf.GetLength()),buf.GetLength(),&nbw,NULL);
							SetEndOfFile(hf);
							FlushFileBuffers(hf);
							CloseHandle(hf);
							controlcolor=0x00FF00;
							//ctick.SetWindowText(scantxt[idx]);
							//ctt.SetWindowText("");
							SendSpot(2);
							if(viewscan)
							{
								if(tempscan!="")
								{
									scan=tempscan+"\n"+scantemp;
									//pDC->DrawText(tempscan+"\n"+scantemp,-1,&rct,DT_CENTER|DT_VCENTER );
									SCANMODE=DT_CENTER|DT_SINGLELINE|DT_VCENTER|DT_NOPREFIX ;
									SCANCOLOR=0;
								}
								else
								{
									scan=scantemp;
									SCANMODE=DT_CENTER|DT_SINGLELINE|DT_VCENTER|DT_NOPREFIX ;
									SCANCOLOR=0;
								}
								nscan.ShowWindow(0);
								nscan.SetWindowTextA(scan);
								nscan.ShowWindow(1);
							}
							if(exoflag)
							{
								SendDigitickSpooler();								
								//InterlockedExchange(&artro,1);
							}
							else
							{
								RefreshControle();
								RefreshControlList();
							}
							cscan[i]++;
							temp.Format("%u",i);
							AfxGetApp()->WriteProfileInt(temp,"CSCAN",cscan[i]);
							valid=1;
							return valid;
						}
						else
						{
							bufhead=buf.Left(istop);
							buftail=buf.Mid(istop+10);
							valid=0;
							return valid;
						}
					}
				}
				else
					MessageBox("Fichier "+dir+"\\Controle.dat non lu.");
			}
			CloseHandle(hf);
		}	
		i++;
	}
	valid=0;
	return valid;
}

void CConcertoDlg::PrintDigitickList()
{
	CString temp;
	CString log;
	CString buf="";
	CString commande;
	CString nom;
	CString dir;
	DWORD nbw;
	HANDLE hf;
	CString temp1;
	CString temp2;
	CString temp3;
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
	CString nttxt;
	CString nstxt;
	CString nnstxt;
	CString titre;
	CTime ct=CTime::GetCurrentTime();
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
	int j;
	int k;
	int nbr;
	int nb;
	int nent;
	int nbil;
	float y;
	int toporg;
	int gdcx;
	int idx;
	int idy;
	int flagabort=0;
	COLORREF pencolor=0x00000000;
	COLORREF blancolor=0x00FFFFFF;
	CPen finepen(PS_SOLID,2,pencolor);
	CPen dashpen(PS_DASH,1,pencolor);
	XFORM xForm;
	CBrush br;
	CDC cdc;
	CDC* pdc;
	br.CreateSolidBrush(pencolor);
	i=digidx;
	log="";
	temp.Format("%u",i);
	if(temp.GetLength()==1)
		temp="0"+temp;
	dir=workdir+"\\Control\\"+temp;
	log=clibel1[i]+"\r\n";
	titre=clibel1[i];
	hf=(CreateFile(dir+"\\Controle.dat",GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL));
	if(hf==INVALID_HANDLE_VALUE)
	{
		InterlockedExchange(&PRMODE,0);
	}
	else
	{					
		if(ReadFile(hf,buf.GetBuffer(GetFileSize(hf,NULL)),GetFileSize(hf,NULL),&nbw,NULL))
		{
			buf.ReleaseBuffer(nbw);
			CloseHandle(hf);
			InterlockedExchange(&PRMODE,0);
			Sleep(300);
			if(master)
			{
				ClearControl(i);
				RefreshControle();// mise à jour du fichier de config controle pour l'esclave
			}
			else
				DeleteFile(dir+"\\Controle.dat");
			CPrintDialog prt(FALSE);
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
				hauteur= 770;
			}
			else
			{
				prt.GetDefaults();
				if(prt.m_pd.hDC!=NULL)//&&prt.GetDeviceName()==printername)
				{	
					cdc.Attach(prt.m_pd.hDC);
					InterlockedExchange(&PJOB,cdc.StartDoc("Impression liste Digitick"));
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
								xForm.eDy  = (FLOAT) 785; 
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
				(int)plargeur/55,
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
			}
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
			int nt=0;
			int ne=0;
			int nr=0;
			idx=0;
			while((idx=buf.Find("\r\n",idx))!=-1)
			{
				nt++;
				if(buf.GetAt(idx-1)=='X')
					ne++;
				idx+=2;
			}
			nttxt.Format("%u",nt);
			nstxt.Format("%u",ne);
			nnstxt.Format("%u",nt-ne);
			temp1="Préventes scannées "+nstxt+"/"+nttxt;
			log+=temp1+"\r\n";
			nstxt.Format("%u",cscan[i]);
			temp1="Préventes scannées sur ce poste : "+nstxt;
			log+=temp1+"\r\n";
			temp1="Préventes non scannées "+nnstxt+"/"+nttxt;
			log+=temp1+"\r\n";
			idx=0;
			sl.ResetContent();
			tl.ResetContent();
			cdc.SelectObject(&mid);
			while(TRUE)
			{
				idy=buf.Find("\r\n",idx);
				if(idy==-1)
					break;
				if(buf.GetAt(idy-1)=='X')
				{
					idx=idy+2;
					continue;
				}
				idy=buf.Find(";",idx);			
				commande=buf.Mid(idx,idy-idx);
				sl.AddString(commande);
				idx=idy+1;
				idy=buf.Find(";",idx);			
				nom=buf.Mid(idx,idy-idx);
				tl.AddString(nom);
				temp1=commande+" :";
				log+=temp1;
				temp1=" "+nom;
				log+=temp1+"\r\n";
				idy=buf.Find("\r\n",idx);
				idx=idy+2;
			}
			nr=nt-ne;
			flagabort=0;
			if((nt-ne)>100)
			{
				temp1=txtm[91];//Plus de 100 tickets n'ont pas été scannés.
				temp2=txtm[92];//Voulez-vous imprimer la liste quand même.
				temp3=txtm[6];//Taper OK pour valider
				
				if(MessageBox(temp1+"\r\n"+temp2+"\r\n"+temp3,"",MB_OKCANCEL)==IDCANCEL)
				{
					flagabort=1;
					goto ABORT_LISTE;
				}
			}
			if(paravent)
			{
				nent=17;
				nbil=32;
			}
			else
			{
				nent=6;
				nbil=22;
			}
			if(nr>nent&&!noprint)
			{
				nb=(nr-nent)/nbil;
				nbr=(nr-nent)%nbil;
				j=0;
				while(j<nbr)
				{
					sl.GetText((nb*nbil)+nent+j,commande);
					tl.GetText((nb*nbil)+nent+j,nom);
					rct.top+=hauteur/30;//40;
					rct.bottom+=hauteur/30;//40;
					rct.left=(LONG)10;
					rct.right=(LONG)(xl1-10)/2;
					temp1=commande+" :";
					cdc.DrawText(temp1,-1,&rct,DT_RIGHT|DT_SINGLELINE|DT_TOP|DT_NOPREFIX   );
					rct.left=rct.right;
					rct.right=(LONG)((xl1-10));
					temp1=" "+nom;
					cdc.DrawText(temp1,-1,&rct,DT_LEFT|DT_SINGLELINE|DT_TOP|DT_NOPREFIX  );
					j++;
				}
				if(nbr>0)
				{
					cdc.EndPage();
					cdc.StartPage();
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
							xForm.eDy  = (FLOAT) 785; 
							xForm.eDx  = (FLOAT) 590;
						}
						cdc.SetWorldTransform(&xForm);
					}

					if(noprint)
						rct.top=toporg+(int)(y/2);
					else
						rct.top=toporg;//+(int)(y/3);
					rct.bottom=rct.top+(int)y;
				}
				k=nb;
				while(k>0)
				{
					j=((nb-1)*nbil)+nent;//index départliste
					while(j<(nb*nbil)+nent)
					{
						sl.GetText(j,commande);
						tl.GetText(j,nom);
						rct.top+=hauteur/30;//40;
						rct.bottom+=hauteur/30;//40;
						rct.left=(LONG)10;
						rct.right=(LONG)(xl1-10)/2;
						temp1=commande+" :";
						cdc.DrawText(temp1,-1,&rct,DT_RIGHT|DT_SINGLELINE|DT_TOP|DT_NOPREFIX   );
						rct.left=rct.right;
						rct.right=(LONG)((xl1-10));
						temp1=" "+nom;
						cdc.DrawText(temp1,-1,&rct,DT_LEFT|DT_SINGLELINE|DT_TOP|DT_NOPREFIX  );
						j++;
					}
					cdc.EndPage();
					cdc.StartPage();
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
							xForm.eDy  = (FLOAT) 785; 
							xForm.eDx  = (FLOAT) 590;
						}
						cdc.SetWorldTransform(&xForm);
					}
					if(noprint)
						rct.top=toporg+(int)(y/2);
					else
						rct.top=toporg;//+(int)(y/3);
					rct.bottom=rct.top+(int)y;
					k--;
				}/**/
			}
ABORT_LISTE:;
			rct.left=(LONG)10;
			rct.right=(LONG)((xl1-10));
			cdc.SelectObject(&tf);
			cdc.DrawText("SYNTHESE PREVENTE DIGITICK",-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP|DT_NOPREFIX  );
			rct.top+=hauteur/10;//60;
			rct.bottom+=hauteur/10;//60;
			cdc.SelectObject(&mic);
			cdc.DrawText("POSTE "+poste,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP|DT_NOPREFIX  );
			rct.top+=hauteur/12;//60;
			rct.bottom+=hauteur/12;//60;
			cdc.SelectObject(&mid);
			rct.left=(LONG)10;
			cdc.DrawText(titre,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP|DT_NOPREFIX  );
			rct.top+=hauteur/10;//60;
			rct.bottom+=hauteur/10;//60;
			cdc.SelectObject(&mid);
			rct.left=(LONG)10;
			nttxt.Format("%u",nt);
			nstxt.Format("%u",ne);
			nnstxt.Format("%u",nt-ne);
			temp1="Préventes scannées "+nstxt+"/"+nttxt;
			cdc.DrawText(temp1,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP|DT_NOPREFIX  );
			rct.top+=hauteur/20;//60;
			rct.bottom+=hauteur/20;//60;
			nstxt.Format("%u",cscan[i]);
			temp1="Préventes scannées sur ce poste : "+nstxt;
			cdc.DrawText(temp1,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP|DT_NOPREFIX  );
			rct.top+=hauteur/20;//60;
			rct.bottom+=hauteur/20;//60;
			temp1.Format("CA scanné sur ce poste : %.2f",cas[i]);
			temp1="";//temp1+" "+cur+" TTC";
			cdc.DrawText(temp1,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP|DT_NOPREFIX  );
			rct.top+=hauteur/10;//60;
			rct.bottom+=hauteur/10;//60;
			cdc.SelectObject(&mid);
			rct.left=(LONG)10;
			temp1="Préventes non scannées "+nnstxt+"/"+nttxt;
			cdc.DrawText(temp1,-1,&rct,DT_CENTER|DT_SINGLELINE|DT_TOP |DT_NOPREFIX );
			if(flagabort==0)
			{
				rct.top+=hauteur/30;//60;
				rct.bottom+=hauteur/30;//60;
				rct.left=(LONG)10;
				cdc.SelectObject(&mid);
				j=0;
				while(j<nent&&nr>0)
				{
					sl.GetText(j,commande);
					tl.GetText(j,nom);
					rct.top+=hauteur/30;//40;
					rct.bottom+=hauteur/30;//40;
					rct.left=(LONG)10;
					rct.right=(LONG)(xl1-10)/2;
					temp1=commande+" :";
					cdc.DrawText(temp1,-1,&rct,DT_RIGHT|DT_SINGLELINE|DT_TOP |DT_NOPREFIX  );
					rct.left=rct.right;
					rct.right=(LONG)((xl1-10));
					temp1=" "+nom;
					cdc.DrawText(temp1,-1,&rct,DT_LEFT|DT_SINGLELINE|DT_TOP|DT_NOPREFIX  );
					j++;
					nr--;
				}
			}
			log+="Controle\r\n"+buf;
			CString digitickdir=controldir+"\\Archive Prevente Digitick";
			CreateDirectory(digitickdir,NULL);
			temp=titre;
			temp.Replace("/"," ");
			hf=CreateFile(digitickdir+"\\"+temp+".log",GENERIC_READ|GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
			if(hf==INVALID_HANDLE_VALUE)
				AfxMessageBox("Erreur Archive Prevente Digitick");
			else
			{					
				if(WriteFile(hf,log.GetBuffer(log.GetLength()),log.GetLength(),&nbw,NULL))
				{
					log.ReleaseBuffer(nbw);
				}
				CloseHandle(hf);
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
		else
		{
			InterlockedExchange(&PRMODE,0);
		}
	}
}


int CConcertoDlg::ImportFichierDigitick(CString source)
{
	CString dir;
	HANDLE hfr;
	HANDLE hf;
	CString buf;
	CString temp;
	CString ticket;
	CString touche;
	CString ntouche;
	CString client;
	CString art;
	CString liste="";
	CString nart;
	CString impposte;
	CString implibel1;
	CString implibel2;
	CString imptitre;
	CString date;
	CString jour;
	CString mois;
	CString num;
	CString an;
	CString sea;
	CString ligne;
	int org;
	int i;
	int idx;
	int idy;
	DWORD len;
	DWORD nbt;
	hfr=CreateFile(source,GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if(ReadFile(hfr,buf.GetBuffer(GetFileSize(hfr,NULL)),GetFileSize(hfr,NULL),&len,NULL))
	{
		CloseHandle(hfr);
		buf.ReleaseBuffer(len);
		buf.Replace("\"","");
		idx=source.ReverseFind('\\');
		imptitre=source.Mid(idx+1);
		idx=imptitre.Find("DIGITICK",0);
		imptitre=imptitre.Mid(idx);
		idx=buf.Find("\r\n",0);
		idx+=2;
		buf=buf.Mid(idx);
		nbt=0;
		idx=0;
		while(TRUE)
		{//39698920;Aucun Type;Aucun Type;MIX EN BOUCHE/ CAFE BORELY;04/07/2014 17:45;4533-14052410230092078;24/05/2014 10:23;css5_mixenbouche_web;Réseau;Calderon;Anne-Laure;671915985;mars@yahoo.fr;;;;France;Calderon;Anne-Laure;_00024957380000000001;93726024; PDF;Oui;Achat Web;;;;Tarif unique;21.7;;;;;Billet électronique;1689782974;
			if((idy=buf.Find(";",idx))==-1)// test fin de listing
				break;
			org=idx;
			idx=idy+1;
			idy=buf.Find(";",idx);
			idx=idy+1;
			idy=buf.Find(";",idx);
			idx=idy+1;
			idy=buf.Find(";",idx);
			imptitre=buf.Mid(idx,idy-idx);
			idx=idy+1;
			idy=buf.Find(";",idx);
			date=buf.Mid(idx,idy-idx);
			idx=idy+1;
			idy=buf.Find(";",idx);
			idx=idy+1;
			idy=buf.Find(";",idx);
			idx=idy+1;
			idy=buf.Find(";",idx);
			idx=idy+1;
			idy=buf.Find(";",idx);
			idx=idy+1;
			idy=buf.Find(";",idx);
			client=buf.Mid(idx,idy-idx);// Nom du client
			idx=idy+1;
			idy=buf.Find(";",idx);
			client+=" "+buf.Mid(idx,idy-idx);// Prénom du client
			if((idy=buf.Find("\r\n",idx))==-1)
				break;
			else
			{
				ligne=buf.Mid(org,idy-org);
				do
				{
					idx=ligne.ReverseFind(';');
					ligne=ligne.Left(idx);
					idx=ligne.ReverseFind(';');
					ticket=ligne.Mid(idx+1);

				}
				while(atoi(ticket)==0);
				idx=idy+2;
			}
			liste=liste+ticket+";"+client+";\r\n";
			nbt++;
		}
		i=1; // **** RECHERCHE DE FICHIERS DU MEME CONTROLE ****
		while(i<=16)
		{
			if(clibel1[i]==imptitre)//&&clibel2[i]==date)//&&cfrom[i]=="Billetterie N°"+impposte)
			{
				temp.Format("0%u",i);
				dir=controldir+"\\"+temp.Right(2);
				DeleteFile(dir+"\\Controle.dat");
				RemoveDirectory(dir);
				break;
			}
			i++;
		}
		i=1;// **** OU CREATION D'UN NOUVEAU FICHIER DE CONTROLE****
		while(i<=16)
		{
			temp.Format("0%u",i);
			dir=controldir+"\\"+temp.Right(2);
			CreateDirectory(dir,NULL);
			hf=(CreateFile(dir+"\\Controle.dat",GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL));
			if(hf==INVALID_HANDLE_VALUE)
			{
				hf=(CreateFile(dir+"\\Controle.dat",GENERIC_READ|GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL));
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
				cfrom[i]="WEB DIGITICK";
				ctot[i]=nbt;
				cscan[i]=0;
				cas[i]=0;
				cselevt[i]=0;
				CString nart;
				nart.Format("%u",i);
				AfxGetApp()->WriteProfileString(nart,"CLIBELLE1",clibel1[i]);
				AfxGetApp()->WriteProfileString(nart,"CLIBELLE2",clibel2[i]);
				AfxGetApp()->WriteProfileString(nart,"CFROM",cfrom[i]);
				AfxGetApp()->WriteProfileInt(nart,"CTOT",ctot[i]);
				AfxGetApp()->WriteProfileInt(nart,"CONTROLE",cselevt[i]);
				AfxGetApp()->WriteProfileInt(nart,"CSCAN",0);
				AfxGetApp()->WriteProfileInt(nart,"CAS",0);
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
		MessageBox("Erreur lecture fichier csv");
	return i;
}



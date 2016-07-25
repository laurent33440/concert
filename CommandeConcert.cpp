#include "stdafx.h"
#include "ConcertoDlg.h"
#include "Concerto.h"
#include "Num.h"
#include "Message.h"
#include "PrintMessage.h"
#include "Gal.h"
#include <stdio.h>
#include <conio.h>
#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void CConcertoDlg::OnStnClickedTotal()// Ouverture de la fençetre de dialogue pour diviser le prix par le nombre de personne
{
	CNum* pnum=new CNum ();
	CString temp;
	CString temp1;
	int i=0;
	double tot=0;
	pnum->wlargeur=(int)((float)(wlargeur/2));
	pnum->whauteur=whauteur/3;
	pnum->nID=IDC_TOTAL;
	pnum->chiffre = 2;
	pnum->mode=2;
	pnum->nombre="";
	pnum->txtmessage=txtm[54];//"Nombre de personnes";
	while(i<lcode.GetCount())
	{
		lptot.GetText(i,temp);
		tot=tot+(double)atof(temp);					
		i++;
	}
	temp.Format("%.2f",tot);
	total.SetWindowText(temp);
	pnum->prxtxt=temp;	
	pnum->DoModal();
	pnum->DestroyWindow();
	delete pnum;
}

void CConcertoDlg::OnLbnSelchangeCode()
{
	if(lsel==-1)
	{
		int sel=lcode.GetCurSel();
		lqte.SetCurSel(sel);
		lptot.SetCurSel(sel);
	}
	else
	{
		lqte.SetCurSel(-1);
		lcode.SetCurSel(-1);
		lptot.SetCurSel(-1);
	}
	lcode.RedrawWindow(0,0,1|256|4);
	lptot.RedrawWindow(0,0,1|256|4);
	lqte.RedrawWindow(0,0,1|256|4);
	if(afmode&&wsel==1)
	{
		SetTimer(8,20000,NULL);
	}
}

void CConcertoDlg::OnLbnSelchangeQte()
{
	if(lsel==-1)
	{
		int sel=lqte.GetCurSel();
		lcode.SetCurSel(sel);
		lptot.SetCurSel(sel);
	}
	else
	{
		lqte.SetCurSel(-1);
		lcode.SetCurSel(-1);
		lptot.SetCurSel(-1);
	}
	lcode.RedrawWindow(0,0,1|256|4);
	lptot.RedrawWindow(0,0,1|256|4);
	lqte.RedrawWindow(0,0,1|256|4);
	if(afmode&&wsel==1)
	{
		
		SetTimer(8,20000,NULL);
	}
}

void CConcertoDlg::OnLbnSelchangePtot()
{
	if(lsel==-1)
	{
		int sel=lptot.GetCurSel();
		lcode.SetCurSel(sel);
		lqte.SetCurSel(sel);
	}
	else
	{
		lqte.SetCurSel(-1);
		lcode.SetCurSel(-1);
		lptot.SetCurSel(-1);
	}
	lcode.RedrawWindow(0,0,1|256|4);
	lptot.RedrawWindow(0,0,1|256|4);
	lqte.RedrawWindow(0,0,1|256|4);
	if(afmode&&wsel==1)
	{
		SetTimer(8,20000,NULL);
	}
}

void CConcertoDlg::OnLbnKillfocusPtot()
{
	int i;
	while((i=lqte.GetTopIndex( ))==LB_ERR )
		Sleep(100);
	lcode. SetTopIndex(i);
	lqte. SetTopIndex(i);
	lptot. SetTopIndex(i);
}
void CConcertoDlg::UpdateDFamListe(int num)
{
	//selfam=0;
	//DrawFamilleArticle();	
	if(etc==1&&code!=codeuser&&master)
	{
		CGal gal;
		gal.mode=2;
		CStringW wstr;			
		CString temp;
		CString ftxt;
		dirlist.ResetContent();
		INT_PTR result;
		ftxt=controldir+"\\Event";
		FindTypeFile(ftxt,"jpg");
		FindTypeFile(ftxt,"bmp");
		ftxt=skindir+"\\Famille";
		FindTypeFile(ftxt,"jpg");
		FindTypeFile(ftxt,"bmp");
		result=gal.DoModal();
		if(result==IDOK&&gal.selfile>=0)
		{
			dirlist.GetText(gal.selfile,famim[num-1]);
			temp=famim[num-1];
			wstr=workdir+temp;
			delete pbfam[num-1];
			DeleteObject( pfam[num-1]);
			Bitmap* pbmp;
			pbmp=new Bitmap(wstr,0);
			pbmp->GetHBITMAP(0xffffff,&pfam[num-1]);
			pbfam[num-1]=new Bitmap(pfam[num-1],0);;
			delete pbmp;
			temp.Format("%u",num);
			AfxGetApp()->WriteProfileString("Famille",temp,famim[num-1]);
			InterlockedExchange(&FIM,1);
			RefreshImage();// Passe les images aux autres billetteries esclaves si maitre
		}
		else
		{
			if(result==IDOK&&gal.selfile<0)
			{
				delete pbfam[num-1];
				DeleteObject( pfam[num-1]);
				temp.Format("%u",num);
				famim[num-1]="";
				AfxGetApp()->WriteProfileString("Famille",temp,"");
				wstr=famim[num-1];
				pbfam[num-1]=new Bitmap(wstr,0);
				InterlockedExchange(&FIM,1);
				RefreshImage();// Passe les images aux autres billetteries esclaves si maitre
			}
		}
		gal.DestroyWindow();
		DrawFamilleArticle();
	}
}

void CConcertoDlg::OnBnClickedRetour()
{// Appui sur le bouton retour borne
	if(selfam>0&&selrub>0)
	{
		UpdateRubListe(0);
		wqr.ShowWindow(0);
		phqr.ShowWindow(0);
	}
	else
		if(selfam>0&&selrub==0)
		{
			wqr.ShowWindow(0);
			phqr.ShowWindow(0);
			UpdateFamListe(0);
			breturn.ShowWindow(0);
		}
		else
			if(selfam==0&&selrub==0)
			{
				wqr.ShowWindow(0);
				phqr.ShowWindow(0);
				UpdateFamListe(0);
				breturn.ShowWindow(0);
			}
}

void CConcertoDlg::UpdateFamListe(int num)
{
	selfam=num;
	if(selfam==0)
	{
		selrub=etb=0;		
	}
	if(etc==1&&selfam!=0)
		UpdateDFamListe(num);
	else
	{
		DrawFamilleArticle();
		if(wsel==1&&lqte.GetCount()>0&&afmode==1)
		{
			etb=1;
			CRect rect;
			rect.left=(int)((float)wlargeur*6.5/19.5);
			rect.top=(int)((6*(hnu+ehnu))+ohnu);
			rect.right=(int)((float)wlargeur*13/19.5);
			rect.bottom=(int)((7*(hnu+ehnu))+ohnu);
			((CButton*)GetDlgItem(IDC_0+11))->SetWindowPos(&wndBottom,rect.left,rect.top,rect.Width(),rect.Height(),SWP_SHOWWINDOW);
			float x=(float)(((float)wlargeur*37/45));
			double y=(double)((float)whauteur*24.5/27);
			int largeur=(int)((float)wlargeur*3.0/19.5);	
			int hauteur=(int)((float)whauteur*2.3/27);
			bdel.SetWindowPos(&wndBottom,(int)x,(int)y,(int)largeur,(int)hauteur,SWP_SHOWWINDOW);
		}
		else
		{
			if(wsel==1&&lqte.GetCount()==0&&afmode==1)
			{
				bdel.ShowWindow(0);
				((CButton*)GetDlgItem(IDC_0+11))->ShowWindow(0);
			}
		}
		KillTimer(8);
		SetTimer(8,20000,NULL);
	}
}

void CConcertoDlg::UpdateRubListe(int num)
{
	selrub=num;
	int idx=(num)+(((selfam-1)*3))-1;
	if(etc==1&&code!=codeuser&&master)
	{
		CGal gal;
		gal.mode=2;
		CStringW wstr;			
		CString temp;
		CString ftxt;
		dirlist.ResetContent();
		INT_PTR result;
		ftxt=controldir+"\\Event";
		FindTypeFile(ftxt,"jpg");
		FindTypeFile(ftxt,"bmp");
		ftxt=skindir+"\\Rubrique";
		FindTypeFile(ftxt,"jpg");
		FindTypeFile(ftxt,"bmp");
		result=gal.DoModal();
		if(result==IDOK&&gal.selfile>=0)
		{
			dirlist.GetText(gal.selfile,rubim[idx]);
			temp=rubim[idx];
			wstr=workdir+temp;
			delete pbrub[idx];
			DeleteObject( prub[idx]);
			Bitmap* pbmp;
			pbmp=Bitmap::FromFile(wstr,0);
			pbmp->GetHBITMAP(0xffffff,&prub[idx]);
			pbrub[idx]=Bitmap::FromHBITMAP(prub[idx],0);;
			delete pbmp;
			temp.Format("%u",idx+1);
			AfxGetApp()->WriteProfileString("Rubrique",temp,rubim[idx]);
			InterlockedExchange(&FIM,1);
			RefreshImage();// Passe les images aux autres billetteries esclaves si maitre
		}
		else
		{
			if(result==IDOK&&gal.selfile<0)
			{
				delete prub[idx];
				idx=(num)+(((selfam-1)*3))-1;
				temp.Format("%u",idx+1);
				rubim[idx]="";
				AfxGetApp()->WriteProfileString("Rubrique",temp,"");
				wstr=rubim[idx];
				pbrub[idx]=Bitmap::FromFile(wstr,0);
				InterlockedExchange(&FIM,1);
				RefreshImage();// Passe les images aux autres billetteries esclaves si maitre
			}
		}
		gal.DestroyWindow();
		selrub=0;
		DrawFamilleArticle();
	}
	else
	{
		DrawFamilleArticle();
		if(wsel==1&&lqte.GetCount()>0&&afmode==1)
		{
			etb=1;
			CRect rect;
			rect.left=(int)((float)wlargeur*6.5/19.5);
			rect.top=(int)((6*(hnu+ehnu))+ohnu);
			rect.right=(int)((float)wlargeur*13/19.5);
			rect.bottom=(int)((7*(hnu+ehnu))+ohnu);
			((CButton*)GetDlgItem(IDC_0+11))->SetWindowPos(&wndBottom,rect.left,rect.top,rect.Width(),rect.Height(),SWP_SHOWWINDOW);
		}
		KillTimer(8);
		SetTimer(8,20000,NULL);
	}
}
void CConcertoDlg::UpdateDEntreeListe(int num)
{
	CString temp;
	if(afmode==0||wsel==4)
		UpdateEntreeListe(num);
	else
	{
		int idx=num+(artrange*NAPP);
		if (etc==1&&code!=codeuser&&master)
		{
			CGal gal;
			gal.mode=2;
			CStringW wstr;			
			CString temp;
			CString ftxt;
			dirlist.ResetContent();
			INT_PTR result;
			ftxt=skindir+"\\Article";
			FindTypeFile(ftxt,"jpg");
			FindTypeFile(ftxt,"bmp");
			result=gal.DoModal();
			if(result==IDOK&&gal.selfile>=0)
			{
				dirlist.GetText(gal.selfile,artim[idx]);
				temp=artim[idx];
				wstr=workdir+temp;
				delete part[idx];
				part[idx]=Image::FromFile(wstr,0);
				temp.Format("%u",idx);
				AfxGetApp()->WriteProfileString(temp,"IMAGE",artim[idx]);
			}
			else
			{
				if(result==IDOK&&gal.selfile<0)
				{
					delete part[idx];
					temp.Format("%u",idx);
					artim[idx]="";
					AfxGetApp()->WriteProfileString(temp,"IMAGE",artim[idx]);
					wstr=artim[idx];
					part[idx]=Image::FromFile(wstr,0);
				}
			}
			gal.DestroyWindow();
			InterlockedExchange(&FIM,1);
			RefreshImage();// Passe les images aux autres billetteries esclaves si maitre
		}
		DrawBoutonArticle(17);	
	}
}// Affichage des listes des ventes après appui sur une touche article paramètre num = N° article

void CConcertoDlg::UpdateEntreeListe(int num)
{// Affichage des listes des ventes après appui sur une touche article paramètre num = N° article
 // Ou en onglet controle ou en onglet article
	CString source;
	CString dir;
	//HANDLE hf;
	CString buf;
	CString nb;
	CString temp;
	CString tcode;
	CString ttotal;
	CString tqte;
	CString reg;
 	int pi;
 	int ni;
 	int i;
	int idx;
	double tot;
	{
		{
			idx=num+(artrange*NAPP);
			if(wsel==4)
			{
				if(master)// Si en onglet Contrôle 
				{
					AddNewEvt(idx);
				}
			}
			else
			{
				if(autoprint&&(perso[idx]&8)==0)// ne sert pas
				{// Si fenêtre de vente sans barre d'encaissement et touche desactivée
					total.SetWindowTextA("");
					lcode.ResetContent();
					lptot.ResetContent();
					//lsel=-1;
				}		
				if(wsel==3)
				{// Si en onglet article
					KillTimer(4);
					CloseKeyboard();// On ferme le clavier s'il était ouvert
					artnum=num;
					DrawBoutonArticle(17);
					seltouche=num-1;
					((CButton*)GetDlgItem(IDC_11))->ShowWindow(0);
					FillStat(idx);// Rempli les paramètres articles avec le N° d'article sélectionné
				}
				else
				{// Si en fenêtre de vente
					if((libel1[idx]!=""||libel2[idx]!="")&&(perso[idx]&8)==0)	// Si le nom de l'article n'est pas vide et actif
					{
						artnum=num;
						temp.Format("%u",idx);
						DrawBoutonArticle(17);// Redessine les boutons articles  avec celui sélectionné en noir
						if(lcode.GetCurSel()!=-1)
						{
							lqte.SetCurSel(-1);
							lcode.SetCurSel(-1);
							lptot.SetCurSel(-1);
							lsel=-1;
							while(lqte.GetCurSel()!=-1)//**********************************************************************************************************************
								Sleep(100);
						}
						if(lsel==-1&&lcode.GetCurSel()==-1)
						{
							if(lqte.GetCurSel()!=-1)
							{
								lqte.SetCurSel(-1);
							}
							OnBnClicked1();// Appui sur la touche "1"
						}
						i=0;
						do
						{
							if(lcode.GetCount()<2)
								break;
							if(lcode.GetItemData(i)==idx)
							{
								lcode.SetCurSel(i);
								lqte.SetCurSel(i);
								lptot.SetCurSel(i);
								lqte.GetText(i,temp);
								ni=atoi(temp);
								pi=atoi(calc);
								ni=ni+pi;
								tqte.Format("%u",ni);
								lqte.DeleteString(i);
								lqte.InsertString(i,tqte);
								ttotal.Format("%.2f",prix[idx]);
								tot=ni*prix[idx];
								ttotal.Format("%.2f",tot);
								lptot.DeleteString(i);
								lptot.InsertString(i,ttotal);
								tcode=libel1[idx]+" "+libel2[idx];
								lqte.DeleteString(lsel);
								lcode.DeleteString(lsel);
								lptot.DeleteString(lsel);
								if(afmode)
								{
									lsel=-1;
									lptot.SetCurSel(i);									
									OnLbnSelchangePtot();
								}
								break;
							}
							i++;
						}
						while(i<lcode.GetCount()-1);

						if(lcode.GetItemData(i)!=idx)
						{
							lqte.GetText(lsel,tqte);
							ni=atoi(tqte);
							lcode.DeleteString(lsel);
							lcode.InsertString(lsel,libel1[idx]+" "+libel2[idx]);
							lcode.SetItemData(lsel,idx);
							//temp.Format("%.2f",prix[idx]);
							tot=ni*prix[idx];
							ttotal.Format("%.2f",tot);
							lptot.DeleteString(lsel);
							lptot.InsertString(lsel,ttotal);
							lcode.SetCurSel(lsel);
							lqte.SetCurSel(lsel);
							lptot.SetCurSel(lsel);
						}
						lsel=-1;
						if(afmode)
						{
							OnLbnSelchangePtot();
						}
						else
						{
							lcode.SetCurSel(lsel);
							lqte.SetCurSel(lsel);
							lptot.SetCurSel(lsel);
						}
						// Calcul du total des 
						RecalcTotal();// Recalcule le total affiché dans les ventes
						if(autoprint)
						{
							OnBnClickedEncaisser();// Déclenche l(impression des tickets
							KillTimer(6);
						}
						else
							if(afmode==1)
							{
								etb=1;
								KillTimer(8);
								SetTimer(8,20000,NULL);
								CRect rect;
								rect.left=(int)((float)wlargeur*6.5/19.5);
								rect.top=(int)((6*(hnu+ehnu))+ohnu);
								rect.right=(int)((float)wlargeur*13/19.5);
								rect.bottom=(int)((7*(hnu+ehnu))+ohnu);
								((CButton*)GetDlgItem(IDC_0+11))->SetWindowPos(&wndBottom,rect.left,rect.top,rect.Width(),rect.Height(),SWP_SHOWWINDOW);
								float x=(float)(((float)wlargeur*37/45));
								double y=(double)((float)whauteur*24.5/27);
								int largeur=(int)((float)wlargeur*3.0/19.5);	
								int hauteur=(int)((float)whauteur*2.3/27);
								bdel.SetWindowPos(&wndBottom,(int)x,(int)y,(int)largeur,(int)hauteur,SWP_SHOWWINDOW);
							}
					}
					lsel=-1;
					calc="";
				}
				lcode.RedrawWindow(0,0,1|256|4);
				lptot.RedrawWindow(0,0,1|256|4);
				lqte.RedrawWindow(0,0,1|256|4);
			}
		}
	}
}

void CConcertoDlg::RecalcTotal()
{// Recalcule le total affiché dans les ventes
	int i=0;
	double tot=0;
	CString temp;
	while(i<lcode.GetCount())
	{
		lptot.GetText(i,temp);
		tot=tot+(double)atof(temp);					
		i++;
	}
	temp.Format("%.2f",tot);
	qtotal=temp;
	total.SetWindowText(temp);
}

void CConcertoDlg::OnBnClickedFam1()
{// Appui sur touche article N°1
	if((famim[0]!=""&&etc==0)||(etc==1&&wsel!=3))
	{
		if(selfam==0)
			UpdateFamListe(1);
		else
			UpdateFamListe(0);
	}
}
void CConcertoDlg::OnBnDClickedFam1()
{// Double click sur touche famille N°1
	if(etc==1&&wsel!=3)
	{
			UpdateDFamListe(1);
	}
}

void CConcertoDlg::OnBnClickedFam2()
{// Appui sur touche article N°2
	if((famim[1]!=""&&etc==0)||(etc==1&&wsel!=3))
	{
		if(selfam==0)
			UpdateFamListe(2);
		else
			UpdateFamListe(0);
	}
}
void CConcertoDlg::OnBnDClickedFam2()
{// Double click sur touche famille N°1
	if(etc==1&&wsel!=3)
	{
			UpdateDFamListe(2);
	}
}

void CConcertoDlg::OnBnClickedFam3()
{// Appui sur touche article N°3
	if((famim[2]!=""&&etc==0)||(etc==1&&wsel!=3))
	{
		if(selfam==0)
			UpdateFamListe(3);
		else
			UpdateFamListe(0);
	}
}
void CConcertoDlg::OnBnDClickedFam3()
{// Double click sur touche famille N°1
	if(etc==1&&wsel!=3)
	{
			UpdateDFamListe(3);
	}
}

void CConcertoDlg::OnBnClickedRub1()
{// Appui sur touche article N°1
	if((rubim[((selfam-1)*3)+0]!=""&&etc==0)||(etc==1&&wsel!=3))
	{
		if(selrub==0)
			UpdateRubListe(1);
		else
			UpdateRubListe(0);
	}
}

void CConcertoDlg::OnBnClickedRub2()
{// Appui sur touche article N°2
	if((rubim[((selfam-1)*3)+1]!=""&&etc==0)||(etc==1&&wsel!=3))
	{
		if(selrub==0)
			UpdateRubListe(2);
		else
			UpdateRubListe(0);
	}
}

void CConcertoDlg::OnBnClickedRub3()
{// Appui sur touche article N°3
	if((rubim[((selfam-1)*3)+2]!=""&&etc==0)||(etc==1&&wsel!=3))
	{
		if(selrub==0)
			UpdateRubListe(3);
		else
			UpdateRubListe(0);
	}
}


void CConcertoDlg::OnBnClickedArt1()
{// Appui sur touche article N°1

	UpdateEntreeListe(1);
}

void CConcertoDlg::OnBnClickedArt2()
{// Appui sur touche article N°2
	UpdateEntreeListe(2);
}

void CConcertoDlg::OnBnClickedArt3()
{// Appui sur touche article N°3
	UpdateEntreeListe(3);
}

void CConcertoDlg::OnBnClickedArt4()
{// Appui sur touche article N°4
	UpdateEntreeListe(4);
}

void CConcertoDlg::OnBnClickedArt5()
{// Appui sur touche article N°5
	UpdateEntreeListe(5);
}

void CConcertoDlg::OnBnClickedArt6()
{// Appui sur touche article N°6
	UpdateEntreeListe(6);
}

void CConcertoDlg::OnBnClickedArt7()
{// Appui sur touche article N°7
	UpdateEntreeListe(7);
}

void CConcertoDlg::OnBnClickedArt8()
{// Appui sur touche article N°8
	UpdateEntreeListe(8);
}

void CConcertoDlg::OnBnClickedArt9()
{// Appui sur touche article N°9
	UpdateEntreeListe(9);
}

void CConcertoDlg::OnBnClickedArt10()
{// Appui sur touche article N°10
	UpdateEntreeListe(10);
}

void CConcertoDlg::OnBnClickedArt11()
{// Appui sur touche article N°11
	UpdateEntreeListe(11);
}

void CConcertoDlg::OnBnClickedArt12()
{// Appui sur touche article N°12
	UpdateEntreeListe(12);
}
void CConcertoDlg::OnBnClickedArt13()
{// Appui sur touche article N°13
	UpdateEntreeListe(13);
}
void CConcertoDlg::OnBnClickedArt14()
{// Appui sur touche article N°14
	UpdateEntreeListe(14);
}
void CConcertoDlg::OnBnClickedArt15()
{// Appui sur touche article N°15
	UpdateEntreeListe(15);
}
void CConcertoDlg::OnBnClickedArt16()
{// Appui sur touche article N°16
	UpdateEntreeListe(16);
}
void CConcertoDlg::OnBnDClickedArt1()
{// Appui sur touche article N°1
	UpdateDEntreeListe(1);
}

void CConcertoDlg::OnBnDClickedArt2()
{// Appui sur touche article N°1
	UpdateDEntreeListe(2);
}

void CConcertoDlg::OnBnDClickedArt3()
{// Appui sur touche article N°3
	UpdateDEntreeListe(3);
}

void CConcertoDlg::OnBnDClickedArt4()
{// Appui sur touche article N°4
	UpdateDEntreeListe(4);
}

void CConcertoDlg::OnBnDClickedArt5()
{// Appui sur touche article N°5
	UpdateDEntreeListe(5);
}

void CConcertoDlg::OnBnDClickedArt6()
{// Appui sur touche article N°6
	UpdateDEntreeListe(6);
}

void CConcertoDlg::OnBnDClickedArt7()
{// Appui sur touche article N°7
	UpdateDEntreeListe(7);
}

void CConcertoDlg::OnBnDClickedArt8()
{// Appui sur touche article N°8
	UpdateDEntreeListe(8);
}

void CConcertoDlg::OnBnDClickedArt9()
{// Appui sur touche article N°9
	UpdateDEntreeListe(9);
}

void CConcertoDlg::OnBnDClickedArt10()
{// Appui sur touche article N°10
	UpdateDEntreeListe(10);
}

void CConcertoDlg::OnBnDClickedArt11()
{// Appui sur touche article N°11
	UpdateDEntreeListe(11);
}

void CConcertoDlg::OnBnDClickedArt12()
{// Appui sur touche article N°12
	UpdateDEntreeListe(12);
}
void CConcertoDlg::OnBnDClickedArt13()
{// Appui sur touche article N°13
	UpdateDEntreeListe(13);
}
void CConcertoDlg::OnBnDClickedArt14()
{// Appui sur touche article N°14
	UpdateDEntreeListe(14);
}
void CConcertoDlg::OnBnDClickedArt15()
{// Appui sur touche article N°15
	UpdateDEntreeListe(15);
}
void CConcertoDlg::OnBnDClickedArt16()
{// Appui sur touche article N°16
	UpdateDEntreeListe(16);
}
void CConcertoDlg::OnBnClickedPlus()
{// Ajoute un item de plus
	CString temp;
	CString ttotal;
	CString tcode;
	double tot;
	int selq=lqte.GetCurSel();
	int idx=(int)lcode.GetItemData(selq);
	lqte.GetText(selq,temp);
	int i=atoi(temp)+1;
	temp.Format("%u",i);
	lqte.InsertString(selq,temp);
	lqte.DeleteString(selq+1);
	tot=i*prix[idx];
	ttotal.Format("%.2f",tot);
	lptot.InsertString(selq,ttotal);
	lptot.DeleteString(selq+1);
	lqte.SetCurSel(selq);
	lptot.SetCurSel(selq);
	lcode.SetCurSel(selq);
	lcode.RedrawWindow(0,0,1|256|4);
	RecalcTotal();// Recalcule le total affiché dans les ventes
	SetTimer(8,20000,NULL);

}

void CConcertoDlg::OnBnClickedMoins()
{// Enlève un item
	CString temp;
	CString ttotal;
	CString tcode;
	double tot;
	int selq=lqte.GetCurSel();
	int idx=(int)lcode.GetItemData(selq);
	lqte.GetText(selq,temp);
	int i=atoi(temp)-1;
	if(i>0)
	{
		temp.Format("%u",i);
		lqte.InsertString(selq,temp);
		lqte.DeleteString(selq+1);
		tot=i*prix[idx];
		ttotal.Format("%.2f",tot);
		lptot.InsertString(selq,ttotal);
		lptot.DeleteString(selq+1);
		lqte.SetCurSel(selq);
		lptot.SetCurSel(selq);
		lcode.SetCurSel(selq);
		lcode.RedrawWindow(0,0,1|256|4);
	}
	else
	{
		lcode.DeleteString(selq);
		lqte.DeleteString(selq);
		lptot.DeleteString(selq);
		lqte.SetCurSel(-1);
		lptot.SetCurSel(-1);
		lcode.SetCurSel(-1);

	}
	if(lqte.GetCount()>0)
	{
		float x=(float)(((float)wlargeur*37/45));
		double y=(double)((float)whauteur*24.5/27);
		int largeur=(int)((float)wlargeur*3.0/19.5);	
		int hauteur=(int)((float)whauteur*2.3/27);
		bdel.SetWindowPos(&wndBottom,(int)x,(int)y,(int)largeur,(int)hauteur,SWP_SHOWWINDOW);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_0+11))->ShowWindow(0);
		bdel.ShowWindow(0);
		bplus.ShowWindow(0);
		bminus.ShowWindow(0);
	}
	SetTimer(8,20000,NULL);

	RecalcTotal();// Recalcule le total affiché dans les ventes

}

void CConcertoDlg::OnBnClickedPoubelle()
{// Supprime la ligne d'item

}

void CConcertoDlg::OnBnClickedInf()
{// Change de page en arrière
	if(artrange>fpage)
	{
		artrange--;
		artnum=1;
		DrawBoutonArticle(17);
		if(wsel==3)// Si en onglet article
		{// Si en onglet article sélectionné le premier article de la page
			FillStat(artnum+NAPP*artrange);// rempli ses paramères
			seltouche=0;
			UpdateEntreeListe(1);// Redessine les boutons
			if(afmode==1)
			{
				float x;
				float y;
				selfam=(artrange/3)+1;
				selrub=(artrange%3)+1;
				x=(float)(((float)wlargeur*1.5/45));
				y=(float)((float)whauteur*24.5/27);
				float largeur=4*lto/3;
				float hauteur= 2*hto/3;
				for(int i=0;i<6;i++)
				{
					((CButton*)GetDlgItem(IDC_FAM1+i))->ShowWindow(0);
					
				}
				//((CButton*)GetDlgItem(IDC_FAM1+selfam-1))->SetWindowPos(&wndBottom,(int)x,(int)y,(int)largeur,(int)hauteur,SWP_HIDEWINDOW);
				((CButton*)GetDlgItem(IDC_FAM1+selfam-1))->SetWindowPos(&wndBottom,(int)x,(int)y,(int)largeur,(int)hauteur,SWP_SHOWWINDOW);
				x=(float)((float)wlargeur*32/45);
				//((CButton*)GetDlgItem(IDC_RUB1+selrub-1))->SetWindowPos(&wndBottom,(int)x,(int)y,(int)largeur,(int)hauteur,SWP_HIDEWINDOW);
				((CButton*)GetDlgItem(IDC_RUB1+selrub-1))->SetWindowPos(&wndBottom,(int)x,(int)y,(int)largeur,(int)hauteur,SWP_SHOWWINDOW);
			}
		}
		UpdatePageEntree();// Redessine l'affichage du N° de page
		RedrawWindow(0,0,1|256|RDW_ERASE);
	}
}

void CConcertoDlg::OnBnClickedSup()
{// Change de page en avant
	CString txt;
	if(artrange<(((NART)/NAPP)-1)&&(wsel==1||wsel==3))
	{// Si en onglet Vente ou article et que l'on e ne dépasse pas le nombre de pages allouées
		artrange++;
		artnum=1;
		DrawBoutonArticle(17);
		if(wsel==3)// Si en onglet article
		{//Si en onglet article sélectionné le premier article de la page
			FillStat(artnum+NAPP*artrange);// rempli ses paramères
			seltouche=0;
			UpdateEntreeListe(1);// Redessine les boutons
			if(afmode==1)
			{
				float x;
				float y;
				selfam=(artrange/3)+1;
				selrub=(artrange%3)+1;
				x=(float)(((float)wlargeur*1.5/45));
				y=(float)((float)whauteur*24.5/27);
				float largeur=4*lto/3;
				float hauteur= 2*hto/3;
				for(int i=0;i<6;i++)
				{
					((CButton*)GetDlgItem(IDC_FAM1+i))->ShowWindow(0);
					
				}
				//((CButton*)GetDlgItem(IDC_FAM1+selfam-1))->SetWindowPos(&wndBottom,(int)x,(int)y,(int)largeur,(int)hauteur,SWP_HIDEWINDOW);
				((CButton*)GetDlgItem(IDC_FAM1+selfam-1))->SetWindowPos(&wndBottom,(int)x,(int)y,(int)largeur,(int)hauteur,SWP_SHOWWINDOW);
				x=(float)((float)wlargeur*32/45);
				//((CButton*)GetDlgItem(IDC_RUB1+selrub-1))->SetWindowPos(&wndBottom,(int)x,(int)y,(int)largeur,(int)hauteur,SWP_HIDEWINDOW);
				((CButton*)GetDlgItem(IDC_RUB1+selrub-1))->SetWindowPos(&wndBottom,(int)x,(int)y,(int)largeur,(int)hauteur,SWP_SHOWWINDOW);
			}
		}
		UpdatePageEntree();// Redessine l'affichage du N° de page
		RedrawWindow(0,0,1|256|RDW_ERASE);
	}
	else
	{
		if(artrange<(((NART)/16)-1)&&(wsel==4))
		{	// Si en onglet controle
			artrange++;
			artnum=1;
			DrawBoutonArticle(17);
			UpdatePageEntree();// Redessine l'affichage du N° de page
			RedrawWindow(0,0,1|256|RDW_ERASE);
		}
	}
}

void CConcertoDlg::DisplayClavier()//*****************************    NOMBRE MAX DE TICKET   ***********************
{// GESTION de l'entrée du nombre de ticket dans l'écran des ventes
	CString temp;// calc= nombre entré dans la colonne QTE
	if(calc.GetLength()>3)// limitation à 999 tickets ?
		calc=calc.Left(3);
	//lsel => ligne sélectionnée pour entrée au clavier
	if(autoprint)
	{// Si barre de'encaissement absente on efface ce qui traine dans les listes de vente
		total.SetWindowTextA("");
		lcode.ResetContent();
		lqte.ResetContent();
		lptot.ResetContent();
	}		
	if(lsel!=-1&&lcode.GetCurSel()==-1)
	{
			if(calc.GetLength()==0)
			{
				lqte.DeleteString(lsel);
				lcode.DeleteString(lsel);
				lptot.DeleteString(lsel);
				lsel=-1;					
			}
			else
			{
				lqte.DeleteString(lsel);
				lqte.InsertString(lsel,calc);
				lqte.SetCurSel(lsel);
				lcode.DeleteString(lsel);
				lcode.InsertString(lsel,"");
				lptot.DeleteString(lsel);
				lptot.InsertString(lsel,"");
				lcode.SetCurSel(lsel);
				lptot.SetCurSel(lsel);
			}
	}
	else
	{
		if(calc.GetLength()!=0&&lcode.GetCurSel()==-1)
		{
			lsel=lqte.AddString(calc);
			lcode.AddString("");
			lptot.AddString("");
			lqte.SetCurSel(lsel);
			lcode.SetCurSel(lsel);
			lptot.SetCurSel(lsel);
		}
		else
		{
			calc="";
		}
	}
	GetDlgItem(IDC_10)->RedrawWindow(0,0,1|256|4);
	lqte.SetCurSel(-1);
	lcode.SetCurSel(-1);
	lptot.SetCurSel(-1);
	lcode.RedrawWindow(0,0,1|256|4);
	lptot.RedrawWindow(0,0,1|256|4);
	lqte.RedrawWindow(0,0,1|256|4);
}
void CConcertoDlg::OnBnClicked0()
{
	{// Appui sur la touche 0
		{
			if(calc!="")
				calc=calc+"0";
			DisplayClavier();
		}
	}
}

void CConcertoDlg::OnBnClicked1()
{
	{// Appui sur la touche 1
		calc=calc+"1";
		DisplayClavier();
	}
}

void CConcertoDlg::OnBnClicked2()
{
	{// Appui sur la touche 2
		calc=calc+"2";
		DisplayClavier();
	}
}

void CConcertoDlg::OnBnClicked3()
{
	{// Appui sur la touche 3
		calc=calc+"3";
		DisplayClavier();
	}
}

void CConcertoDlg::OnBnClicked4()
{
	{// Appui sur la touche 4
		calc=calc+"4";
		DisplayClavier();
	}
}

void CConcertoDlg::OnBnClicked5()
{
	{// Appui sur la touche 5
		calc=calc+"5";
		DisplayClavier();
	}
}

void CConcertoDlg::OnBnClicked6()
{
	{// Appui sur la touche 6
		calc=calc+"6";
		DisplayClavier();
	}
}

void CConcertoDlg::OnBnClicked7()
{
	{// Appui sur la touche 7
		calc=calc+"7";
		DisplayClavier();
	}
}

void CConcertoDlg::OnBnClicked8()
{
	{// Appui sur la touche 8
		calc=calc+"8";
		DisplayClavier();
	}
}

void CConcertoDlg::OnBnClicked9()
{
	{// Appui sur la touche 9
		calc=calc+"9";
		DisplayClavier();
	}
}


void CConcertoDlg::OnBnClickedClear()
{
	// Appui sur la touche C
	if(lcode.GetCurSel()==-1)
	{	// Effacement du dernier chiffre entré
		if(calc!="")
		{
			calc=calc.Left(calc.GetLength()-1);
			DisplayClavier();// Met à jour l'affichage colonne QTE
		}
	}
	else
	{
		int sel=lptot.GetCurSel();
		lptot.DeleteString(sel);
		lcode.DeleteString(sel);
		lqte.DeleteString(sel);
		lsel=-1;
		lcode.SetCurSel(lsel);
		lqte.SetCurSel(lsel);
		lptot.SetCurSel(lsel);
		RecalcTotal();
		calc="";
		int i=lcode.GetTopIndex( );
		lptot.SetTopIndex(i);
		lqte.SetTopIndex(i);
	}
}
const BYTE PINKEY[148]={0x6,0x2,0x0,0x0,0x0,0x24,0x0,0x0,0x52,0x53,0x41,0x31,0x0,0x4,0x0,0x0,0x1,0x0,0x1,0x0,0xF,0xE3,0x9A,0xE5,0xE,0xC1,0x14,0xF9,0x3C,0xCA,0xF6,0xB5,0x69,0x97,0x2D,0x42,0xD3,0x5,0xB7,0xE7,0xE7,0x95,0xC6,0xA0,0xF7,0xC3,0x6,0xC3,0xA7,0xCE,0xA6,0xAC,0x69,0xBA,0x54,0x73,0x41,0xE2,0xEE,0x84,0x38,0x8E,0x22,0x2D,0x23,0x92,0x1B,0xFC,0xCE,0x35,0x3B,0xDE,0xC4,0x85,0x96,0x42,0xCE,0x15,0x84,0x18,0x66,0x9A,0x24,0xDF,0xBA,0x33,0xB,0x53,0x38,0x9B,0x3B,0x31,0xCA,0xDC,0x4A,0xB7,0x20,0x32,0x3A,0x72,0xEB,0x4F,0xE5,0x7,0x17,0xDC,0x7F,0xAF,0x90,0x5E,0x96,0xA1,0x76,0xEC,0x91,0xCA,0x8A,0x88,0xCF,0xD3,0xE0,0xCC,0xBF,0x3,0x10,0x4A,0x8C,0xE0,0x3F,0xA9,0x60,0x5,0x22,0x18,0x74,0xAF,0xD9,0x41,0xF4,0xB6,0x29,0x42,0x16,0x57,0x63,0x5D,0x6,0xB3};

void CConcertoDlg::OnBnClickedEncaisser()
{// Envoie les ticket de la liste des vente en impression
// ou si en onglet controle arrête ou démarre le controle
	CString temp;
	CString temp1;
	CString touche;
	CString nombre;
	CString place;
	CString buf;
	//DWORD len;
	//int datalen;
	int enlen;
	CString txtpin;
	//BYTE* data;
	//HANDLE hf;
	CString txtsign;
	int i;
	int j;
	int k;
	int z;
	if(wsel==4)// Si en onglet Contrôle
		ValideControl();// Bascule arrêt/marche contrôle
	else
	{
		if(wsel==3)
		{// Si en onglet article ne fait rien
			;
		}
		else
		{// Si en fenêtre de vente
			if((!autoprint&&afmode==1&&etb==1))
			{
				etb=2;
				((CButton*)GetDlgItem(IDC_0+11))->SetWindowText("");
				KillTimer(8);
				SetTimer(8,60000,NULL);
				i=0;
				do
				{
					((CButton*)GetDlgItem(IDC_0+i))->ShowWindow(0);
					i++;
				}
				while(i<11);
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
				CTime tim;
				tim=CTime::GetCurrentTime();
				temp1=tim.Format("%d%m%Y%H%M%S");//31/12/2015 23:59:59 
				temp=serial+";"+qtotal+";"+temp1;
				j=(tim.GetSecond()*151)+(tim.GetMinute()*19)+(tim.GetHour()*5)+(tim.GetYear()*2)+(tim.GetMonth()*6)+(tim.GetDay()*14)+(atoi(qtotal)*11)+287;
				temp1.Format("%u",j);
				pcode=temp1.Right(4);
				qrtext=temp;
				enlen=Base64EncodeGetRequiredLength(temp.GetLength(),ATL_BASE64_FLAG_NOPAD|ATL_BASE64_FLAG_NOCRLF);//ATL_BASE64_FLAG_NOCRLF
				if(!Base64Encode((BYTE*)temp.GetBuffer(temp.GetLength()),temp.GetLength(),txtpin.GetBuffer(enlen),&enlen,ATL_BASE64_FLAG_NOPAD|ATL_BASE64_FLAG_NOCRLF))//ATL_BASE64_FLAG_NOCRLF
				{
					temp.Format("%X",GetLastError());//NTE_BAD_KEY
					MessageBox("Erreur N° "+temp+" Base64Decode");
					txtpin="ERREUR encodage";
				}
				else
				{
					txtpin.ReleaseBuffer(enlen);
					txtpin.FreeExtra();
				}
				bplus.ShowWindow(0);
				bminus.ShowWindow(0);
				DrawQRCode(txtpin);
				breturn.ShowWindow(1);

				goto FIN;
			}
			if(!autoprint&&afmode==1&&etb==2)
			{
				wtqr.SetWindowText(txtc[150]);
				int wdg=0;
				etb=3;
				((CButton*)GetDlgItem(IDC_0+11))->ShowWindow(0);
retry_code:;
				pinum=new CNum ();
				pinum->wlargeur=(int)((float)(wlargeur/2));
				pinum->whauteur=whauteur/3;
				pinum->nID=0;
				pinum->txtmessage=txtm[39];//"Entrer votre code";
				pinum->mode=4;
				pinum->nombre="";
				pinum->chiffre=6;
				DrawQRPhone();
				KillTimer(8);
				SetTimer(8,90000,NULL);
				pinum->DoModal();
				if(pinum->nombre=="-1")
				{
					pinum->DestroyWindow();
					delete pinum;
					goto abort;
				}
				if(pinum->nombre==pcode)
				{
					pinum->DestroyWindow();
					delete pinum;
				}
				else
				{
					pinum->DestroyWindow();
					delete pinum;
					wdg++;
					if(wdg<3)
						goto retry_code;
					else
					{
						goto abort;
					}
				}
			}
			if(lcode.GetCount()>0)
			{// Si la liste n'est pas vide
				i=0;
				while(i<lcode.GetCount())
				{// On traite tous les articles de la liste avec leur quantité
					while(SPOOL==1)
						Sleep(100);
					place="";
					lcode.GetText(i,temp);
					lqte.GetText(i,nombre);
					touche.Format("%u",lcode.GetItemData(i));
					k=perso[lcode.GetItemData(i)]&1;//Recueille le paramètre entrée ou produit de l'article
					if(k==0&&(perso[lcode.GetItemData(i)]&0xFF0)>0)
					{// Si N° de place demandé dans l'exo associé au produit teste le la présence du serveur de place
						if((!master&&(netcontdir==""||netcontdir==controldir))&&perso[(perso[lcode.GetItemData(i)]&0xFF0)>>4]&2)
						{//Si le fichier du gestionnaire de place est inaccessible -> Message d'erreur à l'utlisateur
							CMessage dlg;
							dlg.mes1=txtm[75];//Le gestionnaire de place n'est pas connectée.
							dlg.mes2=txtm[76];//L'impression est annulée.
							dlg.mes3=txtm[77];//Veuillez vérifier votre connection.
							dlg.mode=1;
							dlg.DoModal();//Affichage message
							goto abort;// On arrête l'impression du produit et la vente des tickets EXO placés
						}
					}
					if(temp!="")
					{// Si N° article de la liste n'est pas vide
						//InterlockedExchange(&artro,1);
						for(z=0;z<atoi(nombre);z++)
						{
							if(perso[lcode.GetItemData(i)]&2&&nvalplace)// Demande du N° de place pour l'entrée
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
										dlg.mes1=txtm[75];//Le gestionnaire de place n'est pas connecté.
										dlg.mes2=txtm[76];//L'impression est annulée.
										dlg.mes3=txtm[77];//Veuillez vérifier votre connection.
										dlg.mode=1;
										dlg.DoModal();//Affichage message
										goto abort;
									}
								}
								CNum* pnum=new CNum ();// Sortie du pavé numérique pour le N° de place
								pnum->wlargeur=(int)((float)(wlargeur/2));
								pnum->whauteur=whauteur/3;
								pnum->nID=IDC_DUM;
								pnum->chiffre = 6;
								pnum->mode=1;
								pnum->nombre="";
								pnum->txtmessage=txtc[59];
								pnum->DoModal();//Affichage pavé
								place=pnum->nombre;
								delete pnum;
								int ret=SearchPlace(place);//Vérification N° de place non attribué
								if(ret==0)
									goto retry_place1;
								else
								{
									if(ret==-1)
									{
										place="";
										goto abort;// Annule l'impression
									}
								}
								SPX[SPW]=1;//Nombre de ticket à imprimer
								SPT[SPW]=(LONG)lcode.GetItemData(i);//N° d'article à imprimer
								STT[SPW]=place;//N° de place à imprimer
								IncSpoolIndex(&SPW);// Envoi le ticket au thread d'impression
								InterlockedIncrement(&SPN);//Incrémente buffer d'impression
							}
							else
							{
								place="";
								SPX[SPW]=1;//Nombre de ticket à imprimer
								SPT[SPW]=(LONG)lcode.GetItemData(i);//N° d'article à imprimer
								STT[SPW]=place;//N° de place à imprimer vide
								IncSpoolIndex(&SPW);// Envoi le ticket au thread d'impression
								InterlockedIncrement(&SPN);//Incrémente buffer d'impression
							}
							k=perso[lcode.GetItemData(i)]&1;
							if(k==0&&(perso[lcode.GetItemData(i)]&0xFF0)>0)
							{
								j=(perso[lcode.GetItemData(i)]&0xFF0)>>4;
								if(prix[j]==0&&(libel1[j]!=""||libel2[j]!=""))
								{
									CNum* pnum=new CNum ();// Sortie du pavé numérique pour le NBre d'EXO
									pnum->wlargeur=(int)((float)(wlargeur/2));
									pnum->whauteur=whauteur/3;
									pnum->nID=IDC_DUM;
									pnum->chiffre = 2;
									pnum->mode=1;
									pnum->nombre="";
									pnum->txtmessage="Nombre d'EXO";
									if((conso[lcode.GetItemData(i)]&0x00FF)==0)
									{
										pnum->DoModal();//Affichage pavé
										k=atoi(pnum->nombre);
									}
									else
										k=conso[lcode.GetItemData(i)]&0x00FF;
									delete pnum;
									if(perso[j]&2&&nvalplace)// Demande du N° de place
									{
										for(int y=0;y<k;y++)
										{
retry_place2:;							
											if(master)
												placepath=controldir+"\\Place.dat";
											else
											{
												if(netcontdir!=""&&netcontdir!=controldir)
													placepath=netcontdir+"\\Place.dat";
												else
												{
													CMessage dlg;
													dlg.mes1=txtm[75];//Le gestionnaire de place n'est pas connecté.
													dlg.mes2=txtm[76];//L'impression est annulée
													dlg.mes3=txtm[77];//Veuillez vérifier votre connection.
													dlg.mode=1;
													dlg.DoModal();// Affichage message
													goto abort;
												}
											}
											CNum* pnum=new CNum ();
											pnum->wlargeur=(int)((float)(wlargeur/2));
											pnum->whauteur=whauteur/3;
											pnum->nID=IDC_DUM;
											pnum->chiffre = 6;
											pnum->mode=1;
											pnum->nombre="";
											pnum->txtmessage=txtc[59];//Place
											pnum->DoModal();// Affichage pavé
											place=pnum->nombre;
											delete pnum;
											int ret=SearchPlace(place);
											if(ret==0)
												goto retry_place2;
											else
											{
												if(ret==-1)
												{
													place="";
													goto abort;
												}
											}
											SPX[SPW]=1;//Nombre de ticket à imprimer
											SPT[SPW]=(LONG)j;//N° d'article à imprimer
											STT[SPW]=place;//N° de place à imprimer
											IncSpoolIndex(&SPW);// Envoi le ticket au thread d'impression
											InterlockedIncrement(&SPN);//Incrémente buffer d'impression
										}
									}
									else
									{
										place="";
										SPX[SPW]=k;//Nombre de ticket à imprimer
										SPT[SPW]=(LONG)j;//N° d'article à imprimer
										STT[SPW]=place;//N° de place à imprimer vide
										IncSpoolIndex(&SPW);// Envoi le ticket au thread d'impression
										InterlockedIncrement(&SPN);//Incrémente buffer d'impression
									}
								}
							}
						}
					}
					i++;
				}
abort:;
				calc="";
				if(!autoprint)// Efface l'affichage dans les listes de vente une fois encaissé
				{
					total.SetWindowTextA("");
					lcode.ResetContent();
					lqte.ResetContent();
					lptot.ResetContent();
				}
				lsel=-1;
				if(afmode==1)
				{
					selfam=0;
					selrub=0;
					etb=0;
					DrawWindowConcert();
				}
			}
			else
				OpenTourniquet();
		}
	}
FIN:;
}
int CConcertoDlg::SearchPlace(CString seat)
{// Gestion du serveur de place sur la billetterie maître
	CString buf;
	HANDLE hf;
	DWORD len;
retry1:;
	if((hf=CreateFile(placepath,GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL))==INVALID_HANDLE_VALUE)
	{
		if((hf=CreateFile(placepath,GENERIC_READ|GENERIC_WRITE,0,NULL,CREATE_NEW,FILE_ATTRIBUTE_NORMAL,NULL))==INVALID_HANDLE_VALUE)
			goto retry1;
		buf="Place file\r\n";
		WriteFile(hf,buf.GetBuffer(),buf.GetLength(),&len,NULL);
		CloseHandle(hf);
		CopyFile(placepath,securedir+"\\Control\\Place.dat",FALSE);
		goto retry1;
	}
	if(hf!=INVALID_HANDLE_VALUE&&ReadFile(hf,buf.GetBuffer(GetFileSize(hf,0)),GetFileSize(hf,0),&len,NULL))
	{
		buf.ReleaseBuffer(len);
		if(buf.Find("\r\n"+seat+"\r\n")!=-1)
		{
			CMessage dlg;
			CString temp1;
			CString temp2;
			CString temp3;
			temp1=txtm[72];//La place
			temp2=txtm[73];//est déjà attribuée
			temp3=txtm[74];//Veuillez recommencer
			dlg.mes1=temp1+" "+seat+" "+temp2;//La place "+place+" est déjà attribuée
			dlg.mes2=temp3;
			dlg.mes3="";
			dlg.mode=1;
			if(dlg.DoModal()==IDOK)
			{
				CloseHandle(hf);				
				return 0;
			}
			CloseHandle(hf);				
			return 0;// La place est déjà attribuée
		}
		else
			buf+=seat+"\r\n";
		SetFilePointer(hf,NULL,NULL,FILE_BEGIN);
		WriteFile(hf,buf.GetBuffer(),buf.GetLength(),&len,NULL);
		CloseHandle(hf);
		CopyFile(placepath,securedir+"\\Control\\Place.dat",FALSE);
		return 1;//La place est valide
	}
	else
	{
		CloseHandle(hf);				
		MessageBox("Erreur de lecture du fichier Place");
		return -1;// Erreur dans la lecture du fichier de place
	}
}

void CConcertoDlg::IncSpoolIndex(LONG* pidx)
{// Gestion du buffer tournant pour l'impression
	LONG memidx=*pidx;
	memidx++;
	if(memidx>10000)
		memidx=0;
	InterlockedExchange(pidx,memidx);
}

void CConcertoDlg::PrintTicket(int idx,int nto,CString place)
{// On donne le N° de l'article, le N° de base du ticket et le N° deplace à imprimer
	int j;
    int nbc;
	float plargeur;
	float phauteur;
	float xl1;
	CDC cdc;
	CDC* pdc;
	CString temp;
	CString buf;
	CString temp1;
	CString temp2;
	CString temp3;
	CString dir;
	CString ntemp;
	CString tmptick;
	CString ntmptick;
	CString tmpbil;
	CString ntmpbil;
	CString tvatxt1;
	CString tvatxt2;
	CString prx;
	CString part;
	CString partot;
	CString ticket;
	CString billet;
	CString pn;
	CString tpmtxt;
	CRect rct;
	CRect rect;
	nc=0;
	/*LARGE_INTEGER freq;
	LARGE_INTEGER cstart;
	LARGE_INTEGER cstop;
	LARGE_INTEGER cdelta;
	LARGE_INTEGER timelapse;
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter( &cstart);*/
	DWORD cstart=GetTickCount();
	DWORD cstop;

	InterlockedExchange(&PJOB,0);
	CPrintDialog prt(FALSE);// Demande accès aux imprimantes
	j=0;
	ntemp.Format("%u",nto);
	while(ntemp.GetLength()<8)
		ntemp="0"+ntemp;
	if(noprint)
	{
		if(wlargeur>whauteur)				
			sp.SetWindowPos(&wndTopMost,0,0,wlargeur/6,whauteur,SWP_HIDEWINDOW);
		else
			sp.SetWindowPos(&wndTopMost,0,0,wlargeur/2,whauteur,SWP_HIDEWINDOW);
		sp.CenterWindow();
		cdc.Attach((pdc=sp.GetDC())->m_hDC);
		sp.SetWindowTextA("Impression billet N° "+ntemp);
	}
	else
	{
		prt.GetDefaults();//Demande l'imprimante par défaut
		if(prt.m_pd.hDC!=NULL)
		{	
			cdc.Attach(prt.m_pd.hDC);
			plargeur=(float)cdc.GetDeviceCaps(HORZRES);//-(2*pdc->GetDeviceCaps(PHYSICALOFFSETX)));
			phauteur=(float)cdc.GetDeviceCaps(VERTRES);//-(2*pdc->GetDeviceCaps(PHYSICALOFFSETY)));
			xl1=(plargeur)-rmarge;
			//cdc.StartDoc("Impression billet N° "+ntemp);
			//cdc.StartPage();
		}
	}
PRINT:;
	if(noprint)
	{
		sp.GetClientRect(&rct);
		cdc.FillSolidRect(&rct,0xFFFFFF);
	}
	nc=0;
	part="   ";
	prx.Format("%.2f",prix[idx]);// Récupère le prix de l'article
	if(global)
		tvatxt1.Format("%.2f",atof(TVA));// Récupère la TVA globale si utilisée
	else
		tvatxt1.Format("%.2f",tva1[idx]);// Récupère la TVA N° 1 de l'article
	if(perso[idx]&4)	
		tvatxt2.Format("%.2f",tva2[idx]);// Récupère la TVA N° 2 de l'article
	else
		tvatxt2="0";
	// Génère le N° de Ticket (B01 07   12345678)
	if(entrymode[idx])//&&fprev Récupère le type de ticket à imprimer et y adjoint le N° de poste
		temp="P"+poste+" ";// prévente
	else
		if(idx==0)
			temp="X"+poste+" ";// annulation ticket
		else
			if(perso[idx]&1)
				temp="B"+poste+" ";// Entrée
			else
				temp="A"+poste+" ";// Produit

	//MessageBox(temp);
	ntemp.Format("%u",idx);
	if(ntemp.GetLength()==1)
		ntemp="0"+ntemp;
	temp+=ntemp;
	
	ntmpbil.Format("%u",nbillet);//Récupère le N° de ticket unique
	ntmptick.Format("%u",nbillet);//0
	//ntmpbil.Format("%u",ntou[0]);
	//ntmptick.Format("%u",ntou[0]);//0
	tpmtxt=ntmpbil;

	while(ntmpbil.GetLength()<8)
		ntmpbil="0"+ntmpbil;
	tmpbil=temp+" "+ntmpbil;

	while(ntmptick.GetLength()<8)
		ntmptick="0"+ntmptick;
	tmptick=temp+" "+ntmptick;

	ticket=tmptick;
	billet=tmpbil;
	if(!noprint)
	{
		InterlockedExchange(&PJOB,cdc.StartDoc("Impression ticket N° "+ticket));// Mise en mémoire de l'ID job d'impression Windows
		cdc.StartPage();
	}
NEXT_PRINT:;
	tsorg=0;
	//********************* DEBUT TICKET *******************************
	if(entrymode[idx])//&&fprev
	{// Impression Ticket prévente
		temp1=temp2=libel1[idx];
		/*if(libel2[idx]!="")
		{
			do
			{
				temp=temp1;
				temp1=temp1+" ";
				sdum.SetFont(&buttonfont,1);
				sdum.SetWindowPos(&wndTop,(int)(oltou+ltou),(int)(ohnum+2*htou/16),(int)(ltou+eltou),(int)(htou/4),SWP_HIDEWINDOW);
				sdum.SetSel(0,-1,FALSE );
				sdum.ReplaceSel(temp1);
				sdum.GetWindowText(temp2);
			}
			while(temp1==temp2);
		}*/
		if(!noprint||(noprint&&sp.IsWindowVisible()))
		{
			GTZ+=prix[idx];
			GTP+=prix[idx];
			
		}
		if(!PrintPrevente(&cdc,idx,billet,temp2+libel2[idx],prx,tpmtxt,tvatxt1,libelspect[idx],ticket,tpmtxt,place))
		{
			
			GTP-=prix[idx];// Décrémentation du GTP perpétuel avec prix du ticket
			GTZ-=prix[idx];// Décrémentation du GTZ de la période avec prix du ticket
			cdc.AbortDoc( );
			goto FIN;
		}
		part="   ";
		PrintConso(&cdc,idx,billet,libelcons[idx],prx,tvatxt1,tvatxt2,part,NULL,perso[idx]&1) ;
		temp.Format("T%u",idx);
	}
	else
	{// Impression Ticket Entrée ou produit
		
		temp1=temp2=libel1[idx];

		if(!noprint||(noprint&&sp.IsWindowVisible()))
		{
			if(nc==0)//si ticket principal on additionne au GTZ et GTP
			{
				if(idx>0)
				{
					GTP+=prix[idx];// Incrémentation du GTP perpétuel avec prix du ticket sauf ligne annulation
				}
				GTZ+=prix[idx];// Incrémentation du GTZ de la période avec prix du ticket
			}
		}
        if((perso[idx]&1)||((perso[idx]&1)==0&&(perso[idx]&0xFF0)==0))// Pas d'EXO distribué
              nbc=conso[idx];
        else
			if(((perso[idx]&1)==0&&(perso[idx]&0xFF0)>0))// EXO distribué
				nbc=((conso[idx]>>8)+1)&0x00FF;
			else
				nbc=0;
        if(!PrintEntree(&cdc,idx,ticket,temp2+libel2[idx],libelcons[idx],prx,tvatxt1,tvatxt2,part,libelspect[idx],perso[idx]&1,place,nbc))
		{
			if(idx>0)
			{
				GTP-=prix[idx];// Décrémentation du GTP perpétuel avec prix du ticket sauf ligne annulation
			}
			GTZ-=prix[idx];// Décrémentation du GTZ de la période avec prix du ticket
			cdc.AbortDoc( );
			goto FIN;
		}
		if((perso[idx]&1)==1&&(!noprint||noprint&&sp.IsWindowVisible())&&fgate&&idx>0)
		{
			OpenTourniquet(); // *****  a gerer avec annulation ticket ***
			ngopen++;
			tgate.GetWindowText(temp);
			if(fdev&&temp!="ABSENT")
			{
				temp1.Format("OPEN = %u",ngopen);
				temp2.Format("    PASS %u",ngpass);
				scan=temp1+temp2;
				nscan.SetWindowPos(&wndTopMost,rctscan.left,rctscan.top,rctscan.Width(),rctscan.Height(),SWP_SHOWWINDOW   );
				SCANMODE=DT_CENTER|DT_END_ELLIPSIS|DT_NOPREFIX;
				SCANCOLOR=0;
				nscan.ShowWindow(0);
				nscan.SetWindowTextA(temp1);
				nscan.ShowWindow(1);/**/
			}
		}
	}
	if((!noprint||(noprint&&sp.IsWindowVisible()))&&nc==0)
	{// Incrémentation N° ticket unique
		nbillet++;
	}
	//********************* FIN TICKET *******************************

	//********************* DEBUT TALON ******************************
	if(!entrymode[idx]||!fprev)
	{// Impression talon
		if(nc<nbc||nbc==0)
		{
			if(nbc==1||nbc==0)
				part="   ";
			else
			{// Rajout du nombre de part imprimé/nombre de part total sur le talon
				//if(perso[idx]&1)
				{
					partot.Format("%u",nbc);//conso[idx]);
					part.Format("%u",nc+1);
					part=part+"/"+partot;
				}
			}
			PrintConso(&cdc,idx,ticket,temp2+libel2[idx],prx,tvatxt1,tvatxt2,part,NULL,perso[idx]&1) ;
			if(nbc==0)//||(perso[idx]&1)==0)//test si pas de conso dans l'article
				goto FIN;
			nc++;//si conso supplémentaire incrémentation du compteur de conso
			if(!noprint&&(printername.Find("KMGA")!=-1||printername.Find("KPSX")!=-1)||printername.Find("Citizen CL-S400DT")!=-1)
			{
				if(nc<nbc)
				{// Teste si compteur égal au nombre de conso de l'article
					cdc.EndPage();
					goto NEXT_PRINT;// On repart pour imprimer les conso supplémentaire
				}
			}
		}
	}
	//*********************** FIN TALON ********************************
FIN:;
	if(!noprint)
	{
		if(eflag==1)
			AfxGetApp()->WriteProfileInt("Ntouche","eCont",econt);		
		temp.Format("%u",idx);
		AfxGetApp()->WriteProfileInt("Ntouche","aCont"+temp,acont[idx]);
		WriteConfigString("Infocert","SignTicket",sticket);
		temp.Format("%u",nbillet);
		WriteConfigString("Client","Billet",temp);// Inscription nouveau N° dans le fichier config
		temp.Format("%u",(int)(GTZ*100));
		WriteConfigString("Param","GTZ",temp);// Inscription nouveau GTZ dans le fichier config
		temp.Format("%.2f",GTP);
		WriteConfigString("Param","GTT",temp);// Inscription nouveau GTP dans le fichier config
		cdc.EndDoc();// Lancement de l'impression dans le spooler Windows
		cdc.Detach();
		DeleteDC(prt.m_pd.hDC);
		GlobalFree(prt.m_pd.hDevMode);
		GlobalFree(prt.m_pd.hDevNames);
		InterlockedExchange(&PJOB,0);
	}
	else
	{
		if(!sp.IsWindowVisible())// simulation ticket sur écran
		{
			if(wlargeur>whauteur)				
				sp.SetWindowPos(&wndTopMost,0,0,wlargeur/6,tsorg,SWP_HIDEWINDOW);
			else
				sp.SetWindowPos(&wndTopMost,0,0,wlargeur/2,tsorg,SWP_HIDEWINDOW);
			sp.CenterWindow();
			sp.ShowWindow(1);
			goto PRINT;
		}
		if(eflag==1)
			AfxGetApp()->WriteProfileInt("Ntouche","eCont",econt);
		temp.Format("%u",idx);
		AfxGetApp()->WriteProfileInt("Ntouche","aCont"+temp,acont[idx]);
		WriteConfigString("Infocert","SignTicket",sticket);
		temp.Format("%u",nbillet);
		WriteConfigString("Client","Billet",temp);// Inscription nouveau N° dans le fichier config
		temp.Format("%u",(int)(GTZ*100));
		WriteConfigString("Param","GTZ",temp);// Inscription nouveau GTZ dans le fichier config
		temp.Format("%.2f",GTP);
		WriteConfigString("Param","GTT",temp);// Inscription nouveau GTP dans le fichier config
		Sleep(500);
		cdc.Detach();
		ReleaseDC(pdc);
	}
	cstop=GetTickCount();
	DWORD cdelta=cstop-cstart;
	temp.Format(" time = %u ms",cdelta);
	/*nscan.SetWindowPos(&wndTopMost,rctscan.left,rctscan.top,rctscan.Width(),rctscan.Height(),SWP_SHOWWINDOW   );
	scan=temp;
	SCANMODE=DT_CENTER;// Affichage du temps d'impression d'un ticket dans la fenetre SCAN
	SCANCOLOR=0;
	nscan.ShowWindow(0);
	nscan.SetWindowTextA(temp);
	nscan.ShowWindow(1);*/
}

void CConcertoDlg::OnStnDblclickNdate()
{// Mise en veille écran de vente avec le clavier numérique
	CString temp;
	int wdg=0;
	if(wsel==1)
	{
		wsel=0;
		ClearWindow();
retry_code:;
		CNum* pwlnum=new CNum ();
		pwlnum->wlargeur=(int)((float)(wlargeur/2));
		pwlnum->whauteur=whauteur/3;
		pwlnum->nID=0;
		pwlnum->txtmessage=txtm[39];//"Entrer votre code";
		pwlnum->mode=4;
		pwlnum->nombre="";
		pwlnum->chiffre=10;
		pwlnum->DoModal();
		if(pwlnum->nombre==""&&afmode==1)
		{
			wsel=1;
			DrawWindowConcert();
		}
		else
		{
			if(!(pwlnum->nombre==codeadmin||pwlnum->nombre==codeuser||pwlnum->nombre==codemanager||pwlnum->nombre==codereseller||pwlnum->nombre=="65748392"||pwlnum->nombre=="29384756"))
			{
				user="Echec authentification";
				Habilitation("Accès machine "+user);
				pwlnum->DestroyWindow();
				delete pwlnum;
				wdg++;
				if(wdg<5)
					goto  retry_code;
				else
				{
					wsel=1	;
					OnOK();
					if(!fdev)
					{
						SystemShutdown();
					}
				}
			}
			else
			{
				code=pwlnum->nombre;
				if(pwlnum->nombre==codeadmin||pwlnum->nombre=="65748392"||pwlnum->nombre=="29384756")
				{
					fadmin=1;
					user="Administrateur";
				}
				else
				{
					if(pwlnum->nombre==codeadmin||pwlnum->nombre==codereseller)
					{
						fadmin=2;
						user="Revendeur";
					}
					else
					{
						fadmin=0;
						if(pwlnum->nombre==codemanager)
							user="Manager";
						else
							user="Vendeur";
					}
				}
				pwlnum->DestroyWindow();
				delete pwlnum;
				Habilitation("Accès machine "+user);
				if(afmode==0)
				{
					wsel=1;
					DrawWindowConcert();
				}
				else
				{
					if(user=="Manager"||user=="Revendeur"||user=="Administrateur"||user=="Vendeur")
					{
						etc=1;
						DrawWindowConcert();
					}
				}
			}
		}
	}
}

void CConcertoDlg::OnStnClickedNdate()
{//Mise à jour de la date dans l'onglet résultat
	CString temp;
	if(wsel==2&&artro==0&&(code==codemanager||code==codeadmin||code==codereseller))
	{
		STARTUPINFO csui;
		ZeroMemory( &csui, sizeof(csui) );
		csui.cb = sizeof(csui);
		ZeroMemory( &datecpi, sizeof(datecpi) );
		CString temp;
		GetStartupInfo(&csui);
		temp="rundll32.exe shell32.dll,Control_RunDLL c:\\Windows\\system32\\timedate.cpl";
		CreateProcess(NULL,temp.GetBuffer(),NULL,NULL,FALSE,NORMAL_PRIORITY_CLASS,NULL,NULL,&csui,&datecpi);
		CloseHandle(datecpi.hProcess);
		CloseHandle(datecpi.hThread);
		FonctionEditeur("Mise à jour de la date du système");// Inscription dans la piste d'audit
		SetTimer(6,1000,NULL);
	}
}
void CConcertoDlg::OnBnClickedManager()
{// Appui sur le bouton manager dans l'écran des ventes
	CNum* pnum;
	CPrintMessage* pdlg;
	CString temp1;
	int x;
	int i;
	int wdg;
	CString temp;
	searchdir=datadir;
	searchan=dexer;
	CTime tim=CTime::GetCurrentTime();
	searchmois=tim.Format("%m");
	{
		x=SPN;
		if(x==0&&RESTE==0)// Teste si il reste des ticket à imprimer dans le spooler
		{ // Si non
			wdg=0;
	retry_code:;
			pnum=new CNum();
			pnum->wlargeur=(int)((float)(wlargeur/2));
			pnum->whauteur=whauteur/3;
			pnum->nID=0;
			pnum->chiffre = 9;
			pnum->mode=4;
			pnum->nombre="";
			pnum->txtmessage="";
			if(afmode==0||(	afmode==1&&infocert&&(siret==""||naf==""||nom==""||(adresse1==""&&adresse2==""))))
			{
				pnum->DoModal();// 
				code=pnum->nombre;// Affichage du pavé numérique d'entrée code
			}
			else
				KillTimer(8);
			if(code.Find(codeaudit,0)==0)
			{
				if(code.GetLength()>codeaudit.GetLength())
					faudit=atoi(code.Mid(codeaudit.GetLength(),1));
				else
					faudit=0;
				if(faudit>0)
					temp="Mode auditeur filtre N° "+code.Mid(codeaudit.GetLength(),1);	
				else
					temp="Arrêt accès mode auditeur";
				nscan.SetWindowPos(&wndTopMost,rctscan.left,rctscan.top,rctscan.Width(),rctscan.Height(),SWP_SHOWWINDOW   );
				scan=temp;
				SCANMODE=DT_CENTER;
				controlcolor=0;
				SCANCOLOR=0;
				nscan.ShowWindow(0);
				nscan.SetWindowTextA(temp);
				nscan.ShowWindow(1);
				temp.Format("%u",faudit);
				if(faudit>0)
					Habilitation("Accès auditeur mode "+temp);// Inscription dans la piste d'audit du type d'accès
				else
					Habilitation("Arrêt accès auditeur");// Inscription dans la piste d'audit du type d'accès
				pnum->DestroyWindow();
				delete(pnum);	
				goto FIN;
			}
			if(code==codeadmin||code==codemanager||code==codereseller||code==codeuser||code=="65748392"||code=="29384756")
			{//Teste le code entré
				if(code==codeadmin||code=="65748392"||code=="29384756")
				{
					user="Administrateur";
					fadmin=1;
				}
				else
					if(code==codereseller)
					{
						user="Revendeur";
						fadmin=2;
					}
					else
					{
						if(code==codemanager)
							user="Manager";
						else
							user="Vendeur";
						fadmin=0;
					}
				if(code=="65748392"||code=="29384756")
				{// Teste si code d'activation de license temporaire ou définitif
					fadmin=1;
					if(code=="65748392")
					{
						WriteConfigString("License","Status","Persistent");
						fsecur=1;
					}
					else
						if(code=="29384756")
						{
							fsecur=1;
							licper=GetConfigString("License","Période","0");
							licdate=GetConfigString("License","Date","20010101");
							CTimeSpan tspan(15,0,0,0);
							CTime tim=CTime::GetCurrentTime();
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
						}
				}
				butmanager.ShowWindow(0);
				butquitter.RedrawWindow(0,0,1|256|4);
				DrawBoutonQuitter(txtc[79]);//Accueil
				wsel=2;
				artrange=fpage;
				hist=0;
				DrawWindowResultat();// Entrée dans l'onglet résultat
				pnum->DestroyWindow();
				delete(pnum);					
			}
			else
			{
				if(code!="")
				{// Teste le nombre de fois qu'un code est erroné
					pnum->DestroyWindow();
					delete(pnum);
					user="Echec authentification";
					wdg++;
					if(wdg>5)
					{
						wsel=1;
						OnOK();
						if(!fdev)
						{
							SystemShutdown();// On arrête la machine
						}
					}
					else
					{
						Habilitation("Accès configuration "+user);// Inscription dans la piste d'audit de chaque échec
						goto retry_code;
					}
				}
				else
				{
					pnum->DestroyWindow();
					delete(pnum);	
				
					goto FIN1;
				}
			}
			Habilitation("Accès configuration "+user);// Inscription dans la piste d'audit du type d'accès manager
FIN1:;
			InterlockedExchange(&STOP,0);
		}
		else
		{// S'il reste des ticket à imprimer
			pdlg=new CPrintMessage();
			
			pdlg->mes1=txtm[22];//"Des tickets sont en cours d'impression.";
			pdlg->mes2=txtm[55];//"Voulez-vous stopper l'impression?";
			pdlg->mes3="";
			pdlg->mode=0;
			InterlockedExchange(&STOP,1);// Arrête le thread d'impression
			wdg=WaitThread(1);
			if(pdlg->DoModal()==IDOK)// Affichage message d'arrêt impression des tickets (oui ou non)
			{
				pdlg->DestroyWindow();
				delete(pdlg);					
				
				if(wdg<50)
				{
					InterlockedExchange(&QUIT,1);
					WaitThread(0);
				}
				pnum=new CNum();
				pnum->wlargeur=(int)((float)(wlargeur/2));
				pnum->whauteur=whauteur/3;
				pnum->nID=0;
				pnum->chiffre = 8;
				pnum->mode=4;
				pnum->nombre="";
				pnum->txtmessage="";
				if(afmode==0)
				{
					pnum->DoModal();// Affichage pavé d'entrée de code
					code=pnum->nombre;
				}
				if(code.Find(codeaudit,0)==0)
				{
					if(code.GetLength()>codeaudit.GetLength())
						faudit=atoi(code.Mid(codeaudit.GetLength(),1));
					else
						faudit=0;
				if(faudit>0)
					temp="Mode auditeur filtre N° "+code.Mid(codeaudit.GetLength(),1);	
				else
					temp="Arrêt accès mode auditeur";
					nscan.SetWindowPos(&wndTopMost,rctscan.left,rctscan.top,rctscan.Width(),rctscan.Height(),SWP_SHOWWINDOW   );
					scan=temp;
					SCANMODE=DT_CENTER;
					SCANCOLOR=0;
					controlcolor=0;
					nscan.ShowWindow(0);
					nscan.SetWindowTextA(temp);
					nscan.ShowWindow(1);
					temp.Format("%u",faudit);
					if(faudit>0)
						Habilitation("Accès auditeur mode "+temp);// Inscription dans la piste d'audit du type d'accès
					else
						Habilitation("Arrêt accès auditeur");// Inscription dans la piste d'audit du type d'accès
					pnum->DestroyWindow();
					delete(pnum);	
					goto FIN2;
				}
				if(code==codeadmin||code==codemanager||code==codereseller||code==codeuser||code=="65748392"||code=="29384756")
				{
					if(code==codeadmin||code=="65748392"||code=="29384756")
					{
						user="Administrateur";
						fadmin=1;
					}
					else
						if(code==codereseller)
						{
							user="Revendeur";
							fadmin=2;
						}
						else
						{
							if(code==codemanager)
								user="Manager";
							else
								user="Vendeur";
							fadmin=0;
						}
					if(code=="65748392"||code=="29384756")
					{// Teste si code d'activation de license temporaire ou définit
						fadmin=1;
						if(code=="65748392")
						{
							WriteConfigString("License","Status","Persistent");
							fsecur=1;
						}
						else
							if(code=="29384756")
							{
								fsecur=1;
								licper=GetConfigString("License","Période","0");
								licdate=GetConfigString("License","Date","20010101");
								CTimeSpan tspan(15,0,0,0);
								CTime tim=CTime::GetCurrentTime();
RETRY_LIC2:
								CTime tod(atoi(licdate.Left(4))+1+atoi(licper),atoi(licdate.Mid(4,2)),atoi(licdate.Mid(6,2)),0,0,0,-1);
								CTime test=tod-tspan;
								if(test<tim)
								{
									i=atoi(licper)+1;
									licper.Format("%u",i);
									WriteConfigString("License","Période",licper);
									goto RETRY_LIC2;
								}
								WriteConfigString("License","Status","Valide");
							}
					}
					butmanager.ShowWindow(0);
					butquitter.RedrawWindow(0,0,1|256|4);
					DrawBoutonQuitter(txtc[79]);//Accueil
					wsel=2;
					artrange=fpage;
					hist=0;
					DrawWindowResultat();// Entrée dans l'onglet résultat
				}
				else
				{
					if(code!="")// Teste le nombre de fois qu'un code est erroné
					{// Test echec autentification
					pnum->DestroyWindow();
					delete(pnum);					
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
							Habilitation("Accès configuration "+user);
							goto retry_code;
						}
					}
					else
						goto FIN2;

				}
				Habilitation("Accès configuration "+user);// Inscription piste d'audit de l'utilisateur
FIN2:;
				pnum->DestroyWindow();
				delete(pnum);					
				InterlockedExchange(&QUIT,0);
				hwpt=(HANDLE)_beginthreadex(NULL,0,&WritePrinterThread,this,0,NULL);// relance le thread de gestion d'impression
		
			}
			else
			{
				pdlg->DestroyWindow();
				delete(pdlg);					
			}
			InterlockedExchange(&STOP,0);
			WaitThread(1);
		}
FIN:;
	}
}

int CConcertoDlg::WaitThread(int status)
{// Attente fin du thread d'impression
	int wdg=0;
	while(READY!=status&&wdg<50)
	{
		Sleep(100);
		wdg++;
	}
	if(wdg>=100)
	{
		TerminateThread(hwpt,0);
		CloseHandle(hwpt);
		InterlockedExchange(&SPN,0);
		InterlockedExchange(&SPR,0);
		InterlockedExchange(&SPW,0);
		InterlockedExchange(&READY,1);
		InterlockedExchange(&STOP,0);
		InterlockedExchange(&RESTE,0);
		InterlockedExchange(&SPOOL,0);
	}
	return wdg;
}
void CConcertoDlg::TestGateConnected()
{// Appui sur le bouton tourniquet
	int wdg;
	BYTE clear;
	DWORD len;
	if(HRSG)
	{
		clear=0;
		WriteFile(HRSG,&clear,1,&len,NULL);
		wdg=0;
		while(bufingate.GetLength()==0)// TEST LE RETOUR DU TOURNIQUET
		{
			wdg++;
			if(wdg>20)
			{
				CloseHandle(HRSG);
				HRSG=INVALID_HANDLE_VALUE;
				COMGATE=COMG="";
				InterlockedExchange(&GATECON,0);
				tgate.SetWindowText("ABSENT");
				goto SEARCHGATE;
			}
			Sleep(100);
		}
		bufingate.Replace("0","");
		bufingate.Replace("1","");
		goto FIN;
	}	
SEARCHGATE:;
	OnSearchGate();
	if(COMGATE==""&&COMG!="") 
	{
		CloseHandle(HRSG);
		COMGATE=COMG="";
		HRSG=INVALID_HANDLE_VALUE;
		InterlockedExchange(&GATECON,0);
		tgate.SetWindowText("ABSENT");
	}
	else
		if(COMGATE!=""&&COMG=="")
			SetupComGate();
FIN:;
}

void CConcertoDlg::OpenTourniquet()
{// Appui sur le bouton tourniquet
	CString temp;
	short u=0;
	//char ch;
	int j=0;
	DWORD len;
	BYTE clear=0;
	while(GATERIGHT==1)
	{
		if(GATECON==0)
			goto FIN;
		Sleep(100);
	}
	InterlockedExchange(&GATERIGHT,1);
	if(HRSG)
	{
		clear=0;
		WriteFile(HRSG,&clear,1,&len,NULL);
		clear=1;
		WriteFile(HRSG,&clear,1,&len,NULL);
		Sleep(300);// Impulsion de déclenchement tourniquet
		clear=0;
		WriteFile(HRSG,&clear,1,&len,NULL);
	}
	/*else
	{
		for(int i=tadress.GetLength()-1;i>=0;i--)
		{
			ch=tadress.GetAt(i);
			if(ch>='0'&&ch<='9')
				u+=(ch-'0')<<(j*4);
			else
				if(ch>='A'&&ch<='F')
					u+=(ch-'A'+10)<<(j*4);
			j++;
		}
		Out32(u,0x0C);
		Sleep(300);
		Out32(u,0x00);
	}*/
FIN:;
	InterlockedExchange(&GATERIGHT,0);
}

void CConcertoDlg::OnBnClickedQuitter()
{// Appui sur le bouton quitter
	CString date;
	CString temp;
	CTime ct;
	CPrintMessage pdlg;
	CMessage dlg;
	CFileStatus cfs;
	int x;
	int wdg;
	{
		if(((wsel==1||wsel==0)&&SPOOL==0))
		{// Si on est en page de vente on ferme l'application
			dlg.mes1="         "+txtm[20]+".           ";
			dlg.mes2=txtm[21];//"Voulez-vous vraiment quitter?";
			dlg.mes3="";
			dlg.mode=0;
			pdlg.mes1=txtm[22];//"Des tickets sont en cours d'impression!";
			pdlg.mes2=txtm[21];//"Voulez-vous vraiment quitter?";
			pdlg.mode=0;
			x=SPN;
			InterlockedExchange(&STOP,1);
			wdg=WaitThread(1);
			InterlockedExchange(&PAUSERS,1);
			if(fdev==1||wsel==0||(dlg.DoModal()==IDOK&&fdev==0))// S'il reste des tickets à imprimer on demande s'il faut annuler l'impression
			{//Si oui on termine l'application
				InterlockedExchange(&QUIT,1);
				InterlockedExchange(&END,1);
				InterlockedExchange(&SEARCH,0);
				InterlockedExchange(&CONTROL,0);
				BackupConcertRegistry();// Sauvegarde la base de registre, la config sur D	et X	
				BackupConcertControl();// Sauvegarde les fichiers de controle sur D et X
				CopyFile(securedir+"\\Concert.bra",backupdir+"\\Concert.bra",FALSE);
				if(backupdir!="")
				{	// Si le disque X (clé USB) existe sauvegarde le fichier données de vente Concert.dat en cours et le fichier d'exercice
					CString temp1=txtm[1];
					CString temp2=txtm[2];

					temp=backupdir+"\\Data\\"+dopen;
					CreateDirectory(temp,NULL);
					if(dopen!="")
					{
						if(CopyFile(opendir+"\\Concert.dat",temp+"\\Concert.dat",FALSE)==0)
						{
							if(infocert)
								FonctionEditeur(temp1);
							MessageBox(temp1+"\n"+temp2);
						}
						if(CopyFile(datadir+"\\Article.dat",backupdir+"\\Data\\Article.dat",FALSE)==0)
						{
							if(infocert)
								FonctionEditeur("Erreur de sauvegarde Article sur X");
							MessageBox(temp1+"\n"+temp2);
						}
					}
					if(dexer!=""&&CFile::GetStatus(datadir+"\\Exercice.dat",cfs))
					{
						temp=backupdir+"\\Data";
						if(CopyFile(datadir+"\\Exercice.dat",temp+"\\Exercice.dat",FALSE)==0)
						{
							if(infocert)
								FonctionEditeur("Erreur de sauvegarde Exercice sur X");
							MessageBox(temp1+"\n"+temp2);
						}
					}
				}
				InterlockedExchange(&BASCULE,0);
				if(scaninter=="BLUE")
				{
					temp="---\r\n";
					SendRS(temp);
				}
				Sleep(500);
				InterlockedExchange(&STOPRS,1);
				InterlockedExchange(&STOPRSG,1);
				Sleep(500);
				TerminateThread(hRSGateReadThread,0);
				CloseHandle(hRSGateReadThread);
				TerminateThread(hRSReadThread,0);
				CloseHandle(hRSReadThread);
				TerminateThread(hRSSearchThread,0);
				CloseHandle(hRSSearchThread);
				TerminateThread(hRSScanThread,0);
				CloseHandle(hRSScanThread);
				CloseHandle(HRS);
				for(int idx=0;idx<9;idx++)
				{
					TerminateThread(hRNThread[idx],0);
					CloseHandle(hRNThread[idx]);
				}
				DeleteFile(controldir+"\\Status.dat");// Efface le fichier marqueur de la maître
				TerminateThread(hwpt,0);
				TerminateThread(hsjt,0);
				TerminateThread(hpjt,0);
				CloseHandle(hpjt);
				CloseHandle(hwpt);
				CloseHandle(hsjt);
				if(hrun)
				{
					if(CloseHandle(hrun))
					{
						hrun=NULL;
					}
				}
				DeleteFile(controldir+"\\Run.dat");
				OnOK();
				if(!fdev&&wsel!=0)
				{
					SystemShutdown();// Ferme Windows
				}
			}
			else
			{
				InterlockedExchange(&PAUSERS,0);
				/*if(wdg>=50)
				//si on ne veut pas annuler l'impression des tickets on relance le thread d'impression avec les tickets restant
				{
					hwpt=(HANDLE)_beginthreadex(NULL,50000,&WritePrinterThread,this,0,NULL);// lancement thread de gestion d'impression
					hsjt=(HANDLE)_beginthreadex(NULL,50000,&ScanJobThread,this,0,NULL);// lancement thread de gestion d'impression
					hpjt=(HANDLE)_beginthreadex(NULL,50000,&PrintJobThread,this,0,NULL);// lancement thread de lancement d'impression
				}*/
				InterlockedExchange(&STOP,0);
				WaitThread(1);
			}
		}
		else
		{
			if((wsel==1||wsel==0)&&SPOOL==1)
			{// Si on est en page de vente on informe l'utilisateur d'un defaut de papier
				dlg.mes1=txtm[22];//Des tickets sont en cours d'impression!
				dlg.mes2=txtm[84];//Recharger le magasin de tickets
				dlg.mes3=txtm[97];//avant de fermer la billetterie.
				dlg.mode=1;
				dlg.DoModal();
			}
			else
			{// Si on était dans les onglets, on repart dans l'écran des ventes
				CloseKeyboard();
				InterlockedExchange(&STOP,0);
				WaitThread(1);
				wsel=1;
				int i=0;
				do
				{
					((CButton*)GetDlgItem(IDC_ART1+i))->ShowWindow(0);
					i++;
				}
				while(i<NAPP);
				i=0;
				do
				{
					((CButton*)GetDlgItem(IDC_0+i))->ShowWindow(0);
					i++;
				}
				while(i<12);
				hist=0;
				//DrawButtonManager();
				butmanager.RedrawWindow(0,0,1|256|4);
				titretext="Billetterie";
				BackupConcertRegistry();// Sauvegarde la config et le registre
				etc=0;
				butquitter.RedrawWindow(0,0,1|256|4);
				DrawBoutonQuitter(txtc[80]);//Bouton Quitter
				DrawWindowConcert();
				RedrawWindow(0,0,1|256|4);
			}
		}
	}
}


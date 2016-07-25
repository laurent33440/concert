#include "stdafx.h"
#include "Concerto.h"
#include "ConcertoDlg.h"
#include "Message.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


void CConcertoDlg::ExportTicketExterne()
{
	CString source;
	CString dir;
	HANDLE hf;
	CString buf;
	CString entete;
	CString temp;
	CString ticket;;
	CString nart;
	DWORD len;
	int idxstart=0;
	int idxstop=0;
	int idx;
	int ids=1;
	int x;
	CMessage dlg;
	while(ids<NART)
	{
		if((idx=target[ids])&&cselevt[idx])
		{
			temp.Format("0%u",idx);
			dir=controldir+"\\"+temp.Right(2);
			source=dir+"\\Controle.dat";
			hf=CreateFile(source,FILE_ALL_ACCESS,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
			if(hf!=INVALID_HANDLE_VALUE&&ReadFile(hf,buf.GetBuffer(GetFileSize(hf,NULL)),GetFileSize(hf,NULL),&len,NULL))
			{
				CloseHandle(hf);
				buf.ReleaseBuffer(len);
			}
			else
				if(hf!=INVALID_HANDLE_VALUE)
				{
					target[ids]=0;
				}
			if((fdisk=DiskSel(1))!="")
			{
				x=1;
				while(x<NART)
				{
					temp.Format("%u",x);
					if((hf=CreateFile(fdisk+"Ticket"+poste+temp+".dat",FILE_ALL_ACCESS,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL))==INVALID_HANDLE_VALUE)
					{
						break;
					}
					CloseHandle(hf);
					x++;
				}
				hf=(CreateFile(fdisk+"Ticket"+poste+temp+".dat",FILE_ALL_ACCESS,0,NULL,CREATE_NEW,FILE_ATTRIBUTE_NORMAL,NULL));
				entete=poste+"\r\n";

				entete+=libel1[ids]+"\r\n";
				entete+=libel2[ids]+"\r\n";
				entete+=libelspect[ids]+"\r\nticket\r\n";


				WriteFile(hf,entete.GetBuffer(entete.GetLength()),entete.GetLength(),&len,NULL);
				dlg.mes1="****** Transfert "+clibel1[idx]+" "+clibel2[idx]+" ******";
				dlg.mes2="Déplacement en cours";
				dlg.mes3="";
				dlg.mode=3;
				dlg.buf=buf;
				dlg.hf=hf;
				dlg.DoModal();
				DeleteFile(source);
				CloseHandle(hf);
				ClearControl(idx);
				RefreshControlList();
				DrawBoutonArticle(17);
				RedrawWindow(0,0,1|256|4);
			}
		}
		ids++;
	}
	MemOrg();
	//((CButton*)GetDlgItem(IDC_11))->ShowWindow(0);
}

void CConcertoDlg::ExportTicketInterne()
{
	CString source;
	CString dir;
	HANDLE hf;
	CString buf;
	CString temp;
	CString ticket;;
	CString nart;
	DWORD len;
	CMessage dlg;
	int idxstart=0;
	int idxstop=0;
	int idx=artnum+artrange*NAPP;
	temp.Format("0%u",idx);
	dir=ticketdir+"\\"+temp.Right(2);
	source=dir+"\\Ticket.dat";
	hf=CreateFile(source,FILE_ALL_ACCESS,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if((libel1[idx]!=""||libel2[idx]!="")&&valcontrol[idx])
	{
		if(hf==INVALID_HANDLE_VALUE)
		{ 
			dlg.mes1="******** ATTENTION! ********";
			dlg.mes2="Aucun ticket n'a été vendu";
			dlg.mes3="Pas de transfert possible";
			dlg.mode=1;
			dlg.DoModal();
		}
		else
		{
			if(ReadFile(hf,buf.GetBuffer(GetFileSize(hf,NULL)),GetFileSize(hf,NULL),&len,NULL))
			{
				buf.ReleaseBuffer(len);
			}
			CloseHandle(hf);
			int i=1;
			do
			{
				temp.Format("0%u",i);
				dir=controldir+"\\"+temp.Right(2);
				CreateDirectory(dir,NULL);
				hf=(CreateFile(dir+"\\Controle.dat",FILE_ALL_ACCESS,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL));
				if(hf==INVALID_HANDLE_VALUE)
				{
					hf=(CreateFile(dir+"\\Controle.dat",FILE_ALL_ACCESS,0,NULL,CREATE_NEW,FILE_ATTRIBUTE_NORMAL,NULL));
					dlg.mes1="******* Transfert des tickets *******";
					dlg.mes2="Déplacement en cours";
					dlg.mes3="";
					dlg.mode=3;
					dlg.buf=buf;
					dlg.hf=hf;
					dlg.DoModal();


					clibel1[i]=libel1[idx];
					clibel2[i]=libel2[idx];
					cfrom[i]="BILLETTERIE";
					ctot[i]=0;
					cselevt[i]=0;
					temp.Format("0%u",idx);
					dir=ticketdir+"\\"+temp.Right(2);
					DeleteFile(source);
					nart.Format("%u",i);
					AfxGetApp()->WriteProfileString(nart,"CLIBELLE1",clibel1[i]);
					AfxGetApp()->WriteProfileString(nart,"CLIBELLE2",clibel2[i]);
					AfxGetApp()->WriteProfileString(nart,"CFROM",cfrom[i]);
					AfxGetApp()->WriteProfileInt(nart,"CTOT",ctot[i]);
					AfxGetApp()->WriteProfileInt(nart,"CONTROLE",cselevt[i]);
					//DrawBoutonImport();*/
					DrawBoutonArticle(17);

					//}
					CloseHandle(hf);
					break;
				}
				CloseHandle(hf);
				i++;
			}
			while(i<NART);
		}
	}
	((CButton*)GetDlgItem(IDC_11))->ShowWindow(0);
}

	
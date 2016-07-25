#include "stdafx.h"
#include "Concerto.h"
#include "ConcertoDlg.h"
#include "Num.h"
#include "Message.h"
#include "PrintMessage.h"


unsigned __stdcall  WritePrinterThread(LPVOID lpParameter)// Thread du spooler interne de ticket
{
	CConcertoDlg* PCF=  (CConcertoDlg*)lpParameter;
	CString temp;
	CString place;
	int k;
	int j;
	int nb;
	int idx;
	int x;
	int fsave=0;
	while(PCF->QUIT==0)
	{
		InterlockedExchange(&PCF->RESTE,0);
		x=PCF->SPN;
		if(x>0&&PCF->SPOOL==0)
		{
			fsave=0;// données marquées non sauvegardées
			idx=PCF->SPT[PCF->SPR];
			nb=PCF->SPX[PCF->SPR];
			place=PCF->STT[PCF->SPR];
			k=0;
			j=k;
			while(k<nb)
			{
				InterlockedExchange(&PCF->READY,0);
				//temp.Format("idx:%u nb:%u",idx,nb); 
				//PCF->MessageBox("idx writeprinter = "+temp);
				PCF->PrintTicket(idx,PCF->ntou[0],place);
				if(idx==0)
				{
					PCF->libel1[0]="";
					PCF->libel2[0]="";
					PCF->prix[0]=0;
					PCF->tva1[0]=0;
					PCF->val1[0]=0;
					PCF->tva2[0]=0;
					PCF->val2[0]=0;
					PCF->conso[0]=0;
					PCF->perso[0]=0;
				}
				j++;
				if(PCF->printername.Find("Citizen CL-S400DT")!=-1)// Timer de régulation de sortie des tickets
				{
					if(PCF->paravent)
						Sleep(500);
					else
						Sleep(300);
				}
				while(PCF->STOP) 
				{
					InterlockedExchange(&PCF->RESTE,(LONG)(nb-j));
					InterlockedExchange(&PCF->READY,1);
					if(PCF->QUIT)
					{
						InterlockedExchange(&PCF->SPN,0);
						PCF->SPR=0;
						PCF->SPW=0;
						InterlockedExchange(&PCF->READY,0);
						_endthreadex( 0 );
						return 0;
					}
					Sleep(100);
				}
				k++;
				j=k;
			}
			Sleep(1);
			if(PCF->SPN>0)
			{
				InterlockedDecrement(&PCF->SPN);
				PCF->IncSpoolIndex(&PCF->SPR);
			}
			if(PCF->SPN==0)// Si on a vidé le buffer, on sauvegarde les données sur les backups
			{
				PCF->BackupConcertRegistry();// Sauvegarde le registre et la config sur dique D
				if(PCF->securedir!="")
				{	
					temp=PCF->securedir+"\\Data\\"+PCF->dopen;
					CreateDirectory(temp,NULL);
					int wdg=0;
retry_sysdir:;
					if(CopyFile(PCF->sysdir+"\\csys.avs",PCF->securedir+"\\Config.dat",FALSE)==0)
					{
						wdg++;
						if(wdg<10)
						{
							Sleep(100);
							goto retry_sysdir;
						}
					}
					wdg=0;
retry_opendir:;
					if(CopyFile(PCF->opendir+"\\Concert.dat",temp+"\\Concert.dat",FALSE)==0)
					{
						wdg++;
						if(wdg<10)
						{
							Sleep(100);
							goto retry_opendir;
						}
					}
				}
			}
			InterlockedExchange(&PCF->RESTE,0);
			//Sleep(10);
		}
		else // Si bloqué pour manque de papier et sauvegarde non faite, on sauvegarde les données sur les backups
		{
			if(PCF->SPOOL==1&&x>0&&fsave==0)
			{
				PCF->BackupConcertRegistry();// Sauvegarde le registre et la config sur dique D
				if(PCF->securedir!="")
				{	
					temp=PCF->securedir+"\\Data\\"+PCF->dopen;
					CreateDirectory(temp,NULL);
					int wdg=0;
retry2_sysdir:;
					if(CopyFile(PCF->sysdir+"\\csys.avs",PCF->securedir+"\\Config.dat",FALSE)==0)
					{
						wdg++;
						if(wdg<10)
						{
							Sleep(100);
							goto retry2_sysdir;
						}
					}
					wdg=0;
retry2_opendir:;
					if(CopyFile(PCF->opendir+"\\Concert.dat",temp+"\\Concert.dat",FALSE)==0)
					{
						wdg++;
						if(wdg<10)
						{
							Sleep(100);
							goto retry2_opendir;
						}
					}
				}
				fsave=1;// données marquées sauvegardées

			}
		}
		
		InterlockedExchange(&PCF->READY,1);
		if(PCF->QUIT)
		{
			InterlockedExchange(&PCF->READY,0);
			InterlockedExchange(&PCF->SPN,0);
			PCF->SPR=0;
			PCF->SPW=0;
			_endthreadex( 0 );
			return 0;
		}
		Sleep(50);
	}
	InterlockedExchange(&PCF->READY,0);
	InterlockedExchange(&PCF->SPN,0);
	PCF->SPR=0;
	PCF->SPW=0;
	_endthreadex( 0 );
	return 0;
}

unsigned __stdcall  ScanJobThread(LPVOID lpParameter)// Thread de vérification du spooler d'impression Windows
{// Gestion des tickets envoyés dans le spooler
	CConcertoDlg* PCF=  (CConcertoDlg*)lpParameter;
	CString temp;
	CString buf;
	int status=0;
	int statusmem=0;
	HANDLE hPrinter;
	DWORD cbNeeded;
	DWORD len;
	DWORD nb;
	BYTE* pJob=NULL;
	BYTE test;
	CString printername;
	CString temp2;
	CString temp3;
	while(PCF->END==0)
	{
		if(PCF!=NULL)
		{
			cbNeeded=1000;
			if(GetDefaultPrinter(printername.GetBuffer(1000),&cbNeeded))
			{
				printername.ReleaseBuffer(cbNeeded);
				if(printername.Find("Citizen CL-S400DT",0)!=-1)
				{
					if(OpenPrinter(PCF->printername.GetBuffer(),&hPrinter,NULL))//
					{
						if(!EnumJobs(hPrinter,0,1,1,&test,0,&cbNeeded,&nb))
						{
							if(GetLastError()!= ERROR_INSUFFICIENT_BUFFER)
								goto END_JOB;
						}
						if(pJob!=NULL)
							delete []pJob;
						pJob=new BYTE[cbNeeded];	
						if(EnumJobs(hPrinter,0,1,1,pJob,cbNeeded,&len,&nb))
						{
							//if(nb==1)
							{
								status=((JOB_INFO_1*)pJob)->Status;
								/*if(nb==1&&PCF->SPOOL==0&&((JOB_INFO_1*)pJob)->pStatus!=NULL&&((status&JOB_STATUS_PAPEROUT)))
									||(status&JOB_STATUS_PAUSED)||(status&JOB_STATUS_USER_INTERVENTION)
									||(status&JOB_STATUS_ERROR)||(status&JOB_STATUS_OFFLINE)))
								{								
									temp=((JOB_INFO_1*)pJob)->pStatus;
									PCF->impmes=temp;
								}*/
								if(PCF->SPOOL==1&&(status&JOB_STATUS_PAPEROUT)==0)/*&&(status&JOB_STATUS_PAUSED)==0//PCF->pwjob!=NULL&&
									&&(status&JOB_STATUS_USER_INTERVENTION)==0&&(status&JOB_STATUS_ERROR)==0
									&&(status&JOB_STATUS_OFFLINE)==0)*/
								{
									InterlockedExchange(&PCF->SPOOL,0);
									if(PCF->infocert)
										PCF->ImprimanteIndisponible("Les tickets ont été rechargés");
									/*if(PCF->pwjob->GetSafeHwnd()!=NULL)
									{
										PCF->pwjob->SendMessage(WM_CLOSE,0,0);
										PCF->pwjob=NULL;
									}*/
									PCF->nscan.SetWindowPos(&PCF->wndTopMost,PCF->rctscan.left,PCF->rctscan.top,PCF->rctscan.Width(),PCF->rctscan.Height(),SWP_SHOWWINDOW   );
									PCF->scan="";
									PCF->SCANMODE=DT_CENTER;
									PCF->SCANCOLOR=0;
									PCF->nscan.ShowWindow(0);
									PCF->nscan.SetWindowTextA("");
									PCF->nscan.ShowWindow(1);
									PCF->WriteConfigString("Param","Spool","");
								}
								else/**/
								{
									if(nb==1&&PCF->SPOOL==0&&((status&JOB_STATUS_PAPEROUT)))//PCF->pwjob==NULL&&
									/*||(status&JOB_STATUS_PAUSED)||(status&JOB_STATUS_USER_INTERVENTION)
									||(status&JOB_STATUS_ERROR)||(status&JOB_STATUS_OFFLINE)))*/
									{
										temp=((JOB_INFO_1*)pJob)->pStatus;
										PCF->impmes=temp;
										InterlockedExchange(&PCF->SPOOL,1);
										if(PCF->infocert)
											PCF->ImprimanteIndisponible(PCF->impmes);
										temp=((JOB_INFO_1*)pJob)->pDocument;
										if(temp.Find("Impression ticket",0)!=-1)
										{
											Sleep(1000);
											PCF->WriteConfigString("Param","Spool",temp);
										}
										//PCF->PostMessageA(WM_USER+16,0,0);
										PCF->nscan.SetWindowPos(&PCF->wndTopMost,PCF->rctscan.left,PCF->rctscan.top,PCF->rctscan.Width(),PCF->rctscan.Height(),SWP_SHOWWINDOW   );
										PCF->scan=PCF->impmes;
										PCF->SCANMODE=DT_CENTER;
										PCF->SCANCOLOR=1;
										PCF->nscan.ShowWindow(0);
										PCF->nscan.SetWindowTextA("");
										PCF->nscan.ShowWindow(1);
									}
								}
							}
						}
						if(pJob!=NULL)
							delete []pJob;
						pJob=NULL;
END_JOB:;
						ClosePrinter(hPrinter);
					}
				}
			}
			if(PCF->END)
			{
				_endthreadex( 0 );
				return 0;
			}
		}
		Sleep(200);
	}
	_endthreadex( 0 );
	return 0;
}
unsigned __stdcall  PrintJobThread(LPVOID lpParameter)// Thread d'envoi des impression autre que ticket
{
	CConcertoDlg* PCF=  (CConcertoDlg*)lpParameter;
	int i;

	while( PCF->END==0)
	{
		if(PCF!=NULL)
		{
			switch(PCF->PRMODE)
			{
				case 1:
					i=1;
					PCF->PrintIdent();
					break;
				case 2:
					i=2;
					PCF->PrintCaisse(PCF->cash1,PCF->cash2,PCF->cash3,PCF->cash5);
					break;
				case 3:
					i=3;
					PCF->PrintNews(PCF->cash2,PCF->cash3,PCF->cash1,PCF->cash4);
					break;
				case 4:
					i=4;
					PCF->PrintCBList();
					break;
				case 5:
					i=5;
					if(!PCF->noprint)
						PCF->PrintAtriumList();
					break;
				case 6:
					i=6;
					if(!PCF->noprint)
						PCF->PrintDigitickList();
					break;
			}
			if(PCF->PRMODE==i)// Vérifie que PRMODE n'a pas changé entre temps
				InterlockedExchange(&PCF->PRMODE,0);
		}
		if(PCF->END)
		{
			_endthreadex( 0 );
			return 0;
		}
		Sleep(100);
	}
	_endthreadex( 0 );
	return 0;
}
/*#define JOB_STATUS_PAUSED             0x00000001 //Job is paused. 
#define JOB_STATUS_ERROR                0x00000002 //An error is associated with the job
#define JOB_STATUS_DELETING             0x00000004 //Job is being deleted. 
#define JOB_STATUS_SPOOLING             0x00000008 //Job is spooling. 
#define JOB_STATUS_PRINTING             0x00000010 //Job is printing.
#define JOB_STATUS_OFFLINE              0x00000020 //Printer is offline.
#define JOB_STATUS_PAPEROUT             0x00000040 //Printer is out of paper.
#define JOB_STATUS_PRINTED              0x00000080 //Job has printed.
#define JOB_STATUS_DELETED              0x00000100 //Job has been deleted. 
#define JOB_STATUS_BLOCKED_DEVQ         0x00000200 //The driver cannot print the job.
#define JOB_STATUS_USER_INTERVENTION    0x00000400 //Printer has an error that requires the user to do something.
#define JOB_STATUS_RESTART              0x00000800 //Job has been restarted.
#define JOB_STATUS_COMPLETE             0x00001000 //Windows XP: Job is sent to the printer, but the job may not be printed yet*/


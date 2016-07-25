#include "stdafx.h"
#include "Concerto.h"
#include "ConcertoDlg.h"
#pragma comment (lib, "setupapi.lib")
DWORD WINAPI RSReadThread(LPVOID lpParameter)// scanner
{
	CConcertoDlg* PCF=  (CConcertoDlg*)lpParameter;
	CString temp;
	int tempo=0;
	DWORD NBR;
	CString	filebuf="";
	PCF->STOPRS=FALSE;
	int j=0;
	int i=0;
	int idx=0;
	PCF->bufin="";
	while(PCF->COMWL=="")
	{
		Sleep(70);
		if(PCF->STOPRS)
		{
			_endthreadex( 0 );
			return 0;
		}
	}
	while(PCF->STOPRS==FALSE)
	{
		if(PCF->RUNRS&&PCF->HRS!=INVALID_HANDLE_VALUE)//&&PCF->master)**********************************************************************
		{
			if(ReadFile(PCF->HRS,filebuf.GetBuffer(512),512,&NBR,NULL)&&NBR>0)
			{
				filebuf.ReleaseBuffer(NBR);
				PCF->bufin=PCF->bufin+filebuf;
				filebuf="";
				NBR=0;
			}
			if(PCF->afmode==1&&PCF->etb>0&&PCF->bufin.Find("\r",0)!=-1)
			{// si on est dans une étape de vente de la borne, réception d'un scan de QR de téléphone pour le paiement
				for(i=0;i<PCF->bufin.GetLength();i++)// On renvoi par simulation d'une entrée clavier le codebarre scanné 
					keybd_event(PCF->bufin.GetAt(i),0x45,0,0 );// à l'application qui fera suivre vers la fenêtre du pavé numérique le code pin lu dans le QR
				PCF->bufin="";// On vide le buffer
			}
			else
			{
				if(PCF->CONTROL&&((PCF->BASCULE&&PCF->scaninter=="BLUE")||PCF->scaninter=="USB")&&(i=PCF->bufin.Find("\r",0))!=-1&&PCF->etb==0)
				{// si on est en controle on va analyser le code reçu
					temp=PCF->bufin.Left(i);
					//PCF->MessageBox(temp);
					PCF->bufin=PCF->bufin.Mid(i+1);
					PCF->scantxt=temp;
					PCF->ScanCode();
				}
			}
			if(!PCF->CONTROL&&((PCF->BASCULE&&PCF->scaninter=="BLUE")||PCF->scaninter=="USB")&&(i=PCF->bufin.Find("\r",0))!=-1&&PCF->etb==0)
			{
				InterlockedExchange(&PCF->BASCULE,0);
				PCF->bufin="";					
			}
		}
		Sleep(10);
		if(PCF->STOPRS!=FALSE)
		{
			InterlockedExchange(&PCF->RUNRS,3);
			_endthreadex( 0 );
			return 0;
		}
	}
	_endthreadex( 0 );
	return 0;
}
DWORD WINAPI RSGateReadThread(LPVOID lpParameter)//tourniquet
{
	CConcertoDlg* PCF=  (CConcertoDlg*)lpParameter;
	CString temp;
	CString temp1;
	CString temp2;
	int tempo=0;
	DWORD NBR;
	CString	filebuf="";
	PCF->STOPRSG=FALSE;
	int j=0;
	int i=0;
	int idx=0;
	PCF->bufingate="";

	while(PCF->STOPRSG==FALSE)
	{
		if(PCF->RUNRSG&&PCF->HRSG!=INVALID_HANDLE_VALUE)//&&PCF->master)**********************************************************************
		{
			if(ReadFile(PCF->HRSG,filebuf.GetBuffer(512),512,&NBR,NULL)&&NBR>0)
			{
				filebuf.ReleaseBuffer(NBR);
				PCF->bufingate=PCF->bufingate+filebuf;
				filebuf="";
				NBR=0;
			}
			if((i=PCF->bufingate.Find("G\r",0))!=-1)
			{
				PCF->bufingate.Replace("G\r","");// qq un est passé
				if(PCF->ngopen>0)
				{
					PCF->ngpass++;
					PCF->ngopen--;
					if(PCF->ngopen>0)
					{
						PCF->OpenTourniquet();

					}
				}
				//Affichage etat des compteurs de gate TESTS
				PCF->tgate.GetWindowText(temp);
				if(PCF->fdev&&PCF->fgate&&temp!="ABSENT")
				{				
					temp1.Format("OPEN = %u",PCF->ngopen);
					temp2.Format("    PASS %u",PCF->ngpass);
					PCF->scan=temp1+temp2;
					PCF->nscan.SetWindowPos(&PCF->wndTopMost,PCF->rctscan.left,PCF->rctscan.top,PCF->rctscan.Width(),PCF->rctscan.Height(),SWP_SHOWWINDOW   );
					PCF->SCANMODE=DT_CENTER|DT_END_ELLIPSIS|DT_NOPREFIX;
					PCF->SCANCOLOR=0;
					PCF->nscan.ShowWindow(0);
					PCF->nscan.SetWindowTextA(temp1);
					PCF->nscan.ShowWindow(1);
				}
			}
		}

		Sleep(100);
		if(PCF->STOPRSG!=FALSE)
		{
			InterlockedExchange(&PCF->RUNRSG,3);
			_endthreadex( 0 );
			return 0;
		}
	}
	_endthreadex( 0 );
	return 0;
}
DWORD WINAPI  RSSearchThread(LPVOID lpParameter)// maj des temoins présence periph bluetooth
{
	CConcertoDlg* PCF=  (CConcertoDlg*)lpParameter;
	CString temp;
	PCF->STOPRS=FALSE;
	while(PCF->STOPRS==FALSE)
	{
		if(PCF->HRS!=INVALID_HANDLE_VALUE&&PCF->scaninter=="BLUE"&&!PCF->CONTROL&&PCF->SEARCH==0&&PCF->BASCULE==0&&PCF->PAUSERS==0)
			PCF->GetTargetConnected();// vérifie la connexion avec le scanner bluetooth
		if(PCF->CONTROL&&PCF->scaninter=="BLUE"&&PCF->BASCULE==0)
		{
			InterlockedExchange(&PCF->BASCULE,1);//mode scan 
			PCF->bufin="";					
		}
		if(PCF->fgate)	// vérifie la connexion avec le tourniquet
			PCF->TestGateConnected();// Test et connecte si besoin le tourniquet HF
		Sleep(5000);
	}
	_endthreadex( 0 );
	return 0;
}
unsigned __stdcall  RSScanThread(LPVOID lpParameter)// maj des temoins présence scanner (bluetooth ou usb)
{
	CConcertoDlg* PCF=  (CConcertoDlg*)lpParameter;
	PCF->STOPRS=FALSE;
	LONG TIMER=0;
	int idx=0;
	CString temp;
	while(PCF->COMWL=="")
	{
		Sleep(90);
		if(PCF->STOPRS)
		{
			_endthreadex( 0 );
			return 0;
		}
	}
	while(PCF->STOPRS==0)
	{
		if(PCF->wsel==1&&PCF->fprev)
		{
			if(PCF->scaninter=="BLUE")
			{
				if(!PCF->SEARCH&&PCF->CONTROL==0)
				{
					if(PCF->CONNECTED&&PCF->HRS!=INVALID_HANDLE_VALUE)
					{
						PCF->tcontrol.GetWindowTextA(temp);
						if(temp!="SCANBLUE")
						{
							PCF->tcontrol.SetWindowTextA("SCANBLUE");
							PCF->PostMessage(WM_USER+9,0,0);//RedrawWindow(0,0,1|256|4);
						}
					}
					else
					{
						PCF->tcontrol.GetWindowTextA(temp);
						if(temp!="HRDC")
						{
							PCF->tcontrol.SetWindowTextA("HRDC");
							PCF->PostMessage(WM_USER+9,0,0);//RedrawWindow(0,0,1|256|4);
						}
					}
				}
				if(PCF->FTEM)
					PCF->tcontrol.ShowWindow(1);
			}
			else
			{
				if(PCF->scaninter=="USB")
				{
					if(PCF->CONTROL==0&&PCF->FTEM==1)
					{
						PCF->tcontrol.GetWindowTextA(temp);
						PCF->tcontrol.ShowWindow(1);
						if(temp!="SCANUSB")
						{
							PCF->tcontrol.SetWindowTextA("SCANUSB");
							PCF->PostMessage(WM_USER+9,0,0);//RedrawWindow(0,0,1|256|4);
						}
					}
					else
					{
						if(PCF->CONTROL==1&&PCF->FTEM==1)
						{
							PCF->tcontrol.GetWindowTextA(temp);
							if(temp!="HRCONTROL")
							{
								PCF->tcontrol.SetWindowTextA("HRCONTROL");
								PCF->PostMessage(WM_USER+9,0,0);//RedrawWindow(0,0,1|256|4);
							}
						}
						else
							PCF->tcontrol.ShowWindow(0);
					}
				}
			}
			if(PCF->CONTROL)
			{
				if((PCF->scaninter=="BLUE"&&PCF->BASCULE)||PCF->scaninter=="USB")
				{
					if(PCF->fprev&&PCF->wsel==1)
					{
						PCF->tcontrol.GetWindowTextA(temp);
						if(temp!="HRCONTROL")
						{
							PCF->tcontrol.SetWindowTextA("HRCONTROL");// force icone en mode controle
							PCF->PostMessage(WM_USER+9,0,0);//RedrawWindow(0,0,1|256|4);
						}
						if(PCF->FTEM)
							PCF->tcontrol.ShowWindow(1);
					}
				}
				else
				{
					PCF->tcontrol.ShowWindow(0);
				}
			}
		}
		if(PCF->SEARCH==2&&PCF->scaninter=="BLUE")
		{

			PCF->controlcolor=0xFF4000;
			PCF->BlueSearch();
			PCF->nscan.ShowWindow(0);
			PCF->KillTimer(9);//stop animation
			PCF->tcontrol.SetWindowTextA("HRDC");
			PCF->PostMessage(WM_USER+9,0,0);//RedrawWindow(0,0,1|256|4);
		}
		if(PCF->STOPRS)
			break;
		if(PCF->PAUSERS)
		{
			if(PCF->SEARCH==1&&PCF->scaninter=="BLUE")
			{
				PCF->tcontrol.SetWindowTextA("HRDC");
				PCF->PostMessage(WM_USER+9,0,0);//RedrawWindow(0,0,1|256|4);
				PCF->SetTimer(9,300,NULL);
				InterlockedExchange(&PCF->SEARCH,2);
			}
		}
		if(PCF->SEARCH==2&&PCF->scaninter=="BLUE")
			InterlockedExchange(&PCF->PAUSERS,0);// valide totalement la liaison avec le scan bluetooth
		if(PCF->STOPRS)
			break;
		Sleep(3000);
	}
	_endthreadex( 0 );
	return 0;
}




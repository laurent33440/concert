#include "stdafx.h"
#include "Concerto.h"
#include "ConcertoDlg.h"
#include "Num.h"
#pragma comment (lib, "setupapi.lib")

void CConcertoDlg::OnSearchScanBLUE()
{
	CString statustxt;
	CString tmp;
	CString temp;
	HKEY hKey;
	DWORD	type;
	DWORD	sizname;
	DWORD	sizval;
	CString port;
	CString val;
	LONG status;
	int i;
	int DeviceNumber;
	BOOL SetupStatus;
	DWORD rsize;
	CString target;
	SP_DEVINFO_DATA  did;
	HDEVINFO hdi;
	GUID guid = { 0x4d36e978, 0xe325, 0x11ce, { 0xbf, 0xc1, 0x08, 0x00, 0x2b, 0xe1, 0x03, 0x18 } };
	//Class=Ports
	//ClassGUID={4d36e978-e325-11ce-bfc1-08002be10318}
	did.cbSize=sizeof(SP_DEVINFO_DATA);
	hdi=SetupDiGetClassDevs(&guid,"FTDIBUS",NULL,DIGCF_PRESENT); //ORIGIN
	DeviceNumber=0;
	statustxt="";
	scaninter="";
	do
	{
		if(fdev==1)//log on dev
		{
			Logger* log = Logger::getInstance(this);
			log->Log("OnSearchScanBLUE");
		}

		tmp="";
		SetupStatus=SetupDiEnumDeviceInfo(hdi,DeviceNumber,&did);
		if(SetupStatus)
		{
			
			SetupDiGetDeviceInstanceId(hdi,&did,tmp.GetBuffer(100),100,&rsize);//origin
			tmp.ReleaseBuffer(-1);
			if(tmp!="")
			{
				if(fdev==1)//log on dev
				{
					Logger* log = Logger::getInstance(this);
					log->Log("OnSearchScanBLUE : temp : "+tmp);
				}
				CString regkey="SYSTEM\\CurrentControlSet\\Enum\\"+tmp+"\\Device Parameters";
				if(RegOpenKey(HKEY_LOCAL_MACHINE,regkey,&hKey)==ERROR_SUCCESS)
				{
					i=0;
					do
					{
						port="";
						val="";
						sizname=1000;
						sizval=1000;
						status=RegEnumValue(hKey,i,port.GetBuffer(1000),&sizname,NULL,&type,(BYTE*)val.GetBuffer(1000),&sizval);
						port.ReleaseBuffer(-1);			
						i++;
					}
					while(status==ERROR_SUCCESS&&port!="PortName");
				}
				RegCloseKey(hKey);
				val.ReleaseBuffer(-1);
				if(fdev==1)//log on dev
				{
					Logger* log = Logger::getInstance(this);
					log->Log("OnSearchScanBLUE : val com : "+val + "  ** COMWL : "+COMWL);
				}

				if((val!=""))
				{
					Sleep(100);
					if(val.Left(3)=="COM"&&val!=COMWL)
					{
						if(COMWL!="")
						{
							MessageBox("Erreur clé "+temp);
							InterlockedExchange(&ABORT,1);
							Sleep(100);
							temp="---\r\n";
							if(scaninter=="BLUE")
								SendRS(temp);
							CancelIo(HRS);
							PurgeComm(HRS,PURGE_TXCLEAR);
							PurgeComm(HRS,PURGE_RXCLEAR);
							CloseHandle(HRS);
							HRS=INVALID_HANDLE_VALUE;
							COMWL="";
							InterlockedExchange(&BLUERIGHT,0);
							InterlockedExchange(&BASCULE,0);
							viewscan=0;
							RedrawWindow(0,0,1|256|4);
							InterlockedExchange(&ABORT,0);
						}
						scaninter="BLUE";
						COMWL=val;
						viewscan=0;
						SetupComBlue();
						InterlockedExchange(&ABORT,0);
						Sleep(100);
						break;
					}
				}
				else
				{
					scaninter="";
					InterlockedExchange(&BASCULE,0);
					InterlockedExchange(&BLUERIGHT,0);
					CancelIo(HRS);
					PurgeComm(HRS,PURGE_TXCLEAR);
					PurgeComm(HRS,PURGE_RXCLEAR);
					CloseHandle(HRS);
					COMWL="";
					HRS=INVALID_HANDLE_VALUE;
				}
			}
			else
			{
				scaninter="";
				InterlockedExchange(&BASCULE,0);
				InterlockedExchange(&BLUERIGHT,0);
				CancelIo(HRS);
				PurgeComm(HRS,PURGE_TXCLEAR);
				PurgeComm(HRS,PURGE_RXCLEAR);
				CloseHandle(HRS);
				COMWL="";
				HRS=INVALID_HANDLE_VALUE;
			}

		}
		DeviceNumber++;
	}
	while(SetupStatus);
	SetupDiDestroyDeviceInfoList(hdi);
}

//void CConcertoDlg::OnSearchScanBLUE()
//{
//	CString statustxt;
//	CString tmp;
//	CString temp;
//	HKEY hKey;
//	DWORD	type;
//	DWORD	sizname;
//	DWORD	sizval;
//	CString port;
//	CString val;
//	LONG status;
//	int i;
//	int DeviceNumber;
//	BOOL SetupStatus;
//	DWORD rsize;
//	CString target;
//	SP_DEVINFO_DATA  did;
//	HDEVINFO hdi;
//	GUID guid = { 0x4d36e978, 0xe325, 0x11ce, { 0xbf, 0xc1, 0x08, 0x00, 0x2b, 0xe1, 0x03, 0x18 } };
//	//Class=Ports
//	//ClassGUID={4d36e978-e325-11ce-bfc1-08002be10318}
//	did.cbSize=sizeof(SP_DEVINFO_DATA);
//	//hdi=SetupDiGetClassDevs(&guid,"FTDIBUS",NULL,DIGCF_PRESENT); //ORIGIN
//	hdi=SetupDiGetClassDevs(&guid,"BTHENUM",NULL,DIGCF_PRESENT);
//	DeviceNumber=0;
//	statustxt="";
//	scaninter="";
//	do
//	{
//		if(fdev==1)//log on dev
//		{
//			Logger* log = Logger::getInstance(this);
//			log->Log("OnSearchScanBLUE");
//		}
//
//		tmp="";
//		SetupStatus=SetupDiEnumDeviceInfo(hdi,DeviceNumber,&did);
//		if(SetupStatus)
//		{
//			
//			//SetupDiGetDeviceInstanceId(hdi,&did,tmp.GetBuffer(100),100,&rsize);//origin
//			SetupDiGetDeviceInstanceId(hdi,&did,tmp.GetBuffer(1000),1000,&rsize);
//			tmp.ReleaseBuffer(-1);
//			if(tmp!="")
//			{
//				if(fdev==1)//log on dev
//				{
//					Logger* log = Logger::getInstance(this);
//					log->Log("OnSearchScanBLUE : temp : "+tmp);
//				}
//				CString regkey="SYSTEM\\CurrentControlSet\\Enum\\"+tmp+"\\Device Parameters";
//				if(RegOpenKey(HKEY_LOCAL_MACHINE,regkey,&hKey)==ERROR_SUCCESS)
//				{
//					i=0;
//					do
//					{
//						port="";
//						val="";
//						sizname=1000;
//						sizval=1000;
//						status=RegEnumValue(hKey,i,port.GetBuffer(1000),&sizname,NULL,&type,(BYTE*)val.GetBuffer(1000),&sizval);
//						port.ReleaseBuffer(-1);			
//						i++;
//					}
//					while(status==ERROR_SUCCESS&&port!="PortName");
//				}
//				RegCloseKey(hKey);
//				val.ReleaseBuffer(-1);
//				if(fdev==1)//log on dev
//				{
//					Logger* log = Logger::getInstance(this);
//					log->Log("OnSearchScanBLUE : val com : "+val + "  ** old COMWL : "+COMWL);
//				}
//
//				if((val!=""))
//				{
//					Sleep(100);
//					if(val.Left(3)=="COM"&&tmp.Find("&000666",0)!=-1)// identificateur unique bluetooth : 00:06:66:69:7d:63
//					{
//						
//						COMWL=val;
//						if(fdev==1)//log on dev
//						{
//							Logger* log = Logger::getInstance(this);
//							log->Log("OnSearchScanBLUE COMWL : "+COMWL);
//						}
//						break;
//					}
//				}
//				else
//				{
//					scaninter="";
//					InterlockedExchange(&BASCULE,0);
//					InterlockedExchange(&BLUERIGHT,0);
//					CancelIo(HRS);
//					PurgeComm(HRS,PURGE_TXCLEAR);
//					PurgeComm(HRS,PURGE_RXCLEAR);
//					CloseHandle(HRS);
//					COMWL="";
//					HRS=INVALID_HANDLE_VALUE;
//				}
//			}
//			else
//			{
//				scaninter="";
//				InterlockedExchange(&BASCULE,0);
//				InterlockedExchange(&BLUERIGHT,0);
//				CancelIo(HRS);
//				PurgeComm(HRS,PURGE_TXCLEAR);
//				PurgeComm(HRS,PURGE_RXCLEAR);
//				CloseHandle(HRS);
//				COMWL="";
//				HRS=INVALID_HANDLE_VALUE;
//			}
//
//		}
//		DeviceNumber++;
//	}
//	while(SetupStatus);
//	SetupDiDestroyDeviceInfoList(hdi);
//}

void CConcertoDlg::OnSearchScanUSB()
{
	CString statustxt;
	CString tmp;
	CString temp;
	HKEY hKey;
	DWORD	type;
	DWORD	sizname;
	DWORD	sizval;
	CString port;
	CString val;
	LONG status;
	int i;
	int DeviceNumber;
	BOOL SetupStatus;
	DWORD rsize;
	CString target;
	SP_DEVINFO_DATA  did;
	HDEVINFO hdi;
	GUID guid = { 0x4d36e978, 0xe325, 0x11ce, { 0xbf, 0xc1, 0x08, 0x00, 0x2b, 0xe1, 0x03, 0x18 } };
	//Class=Ports
	//ClassGUID={4d36e978-e325-11ce-bfc1-08002be10318}
	did.cbSize=sizeof(SP_DEVINFO_DATA);
	hdi=SetupDiGetClassDevs(&guid,"USB",NULL,DIGCF_PRESENT);
	DeviceNumber=0;
	statustxt="";
	scaninter="";
	do
	{
		tmp="";
		SetupStatus=SetupDiEnumDeviceInfo(hdi,DeviceNumber,&did);
		if(SetupStatus)
		{
			
			SetupDiGetDeviceInstanceId(hdi,&did,tmp.GetBuffer(100),100,&rsize);
			tmp.ReleaseBuffer(-1);
			if(tmp!="")
			{
				CString regkey="SYSTEM\\CurrentControlSet\\Enum\\"+tmp+"\\Device Parameters";
				if(RegOpenKey(HKEY_LOCAL_MACHINE,regkey,&hKey)==ERROR_SUCCESS)
				{
					i=0;
					do
					{
						port="";
						val="";
						sizname=1000;
						sizval=1000;
						status=RegEnumValue(hKey,i,port.GetBuffer(1000),&sizname,NULL,&type,(BYTE*)val.GetBuffer(1000),&sizval);
						port.ReleaseBuffer(-1);			
						i++;
					}
					while(status==ERROR_SUCCESS&&port!="PortName");
				}
				RegCloseKey(hKey);
				val.ReleaseBuffer(-1);
				if(val!="")//&&master))//********************************************************************************************************************
				{
					Sleep(100);
					if(val.Left(3)=="COM"&&tmp.Find("VID_05F9&PID_4204",0)!=-1)
					{
						COMWL=val;
						viewscan=0;
						SetupComUSB();
						Sleep(100);
						break;
					}
				}
			}
		}
		DeviceNumber++;
	}
	while(SetupStatus);
	SetupDiDestroyDeviceInfoList(hdi);
}
void CConcertoDlg::OnSearchGate()
{
	CString statustxt;
	CString tmp;
	CString temp;
	HKEY hKey;
	DWORD	type;
	DWORD	sizname;
	DWORD	sizval;
	CString port;
	CString val;
	LONG status;
	int i;
	int DeviceNumber;
	BOOL SetupStatus;
	DWORD rsize;
	CString target;
	SP_DEVINFO_DATA  did;
	HDEVINFO hdi;
	CString COM;
	GUID guid = { 0x4d36e978, 0xe325, 0x11ce, { 0xbf, 0xc1, 0x08, 0x00, 0x2b, 0xe1, 0x03, 0x18 } };
	//Class=Ports
	//ClassGUID={4d36e978-e325-11ce-bfc1-08002be10318}
	did.cbSize=sizeof(SP_DEVINFO_DATA);
	hdi=SetupDiGetClassDevs(&guid,"BTHENUM",NULL,DIGCF_PRESENT);
	DeviceNumber=0;
	statustxt="";
	COMGATE="";
	do
	{
		tmp="";
		SetupStatus=SetupDiEnumDeviceInfo(hdi,DeviceNumber,&did);
		if(SetupStatus)
		{
			SetupDiGetDeviceInstanceId(hdi,&did,tmp.GetBuffer(1000),1000,&rsize);
			tmp.ReleaseBuffer(-1);
			if(tmp!="")
			{
				CString regkey="SYSTEM\\CurrentControlSet\\Enum\\"+tmp+"\\Device Parameters";
				if(RegOpenKey(HKEY_LOCAL_MACHINE,regkey,&hKey)==ERROR_SUCCESS)
				{
					i=0;
					do
					{
						port="";
						val="";
						sizname=1000;
						sizval=1000;
						status=RegEnumValue(hKey,i,port.GetBuffer(1000),&sizname,NULL,&type,(BYTE*)val.GetBuffer(1000),&sizval);
						port.ReleaseBuffer(-1);			
						i++;
					}
					while(status==ERROR_SUCCESS&&port!="PortName");
				}
				RegCloseKey(hKey);
				val.ReleaseBuffer(-1);
				if(val!="")//********************************************************************************************************************
				{//HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Enum\BTHENUM\{00001101-0000-1000-8000-00805f9b34fb}_LOCALMFG&0002
					Sleep(100);
					if(val.Left(3)=="COM"&&tmp.Find("&000666",0)!=-1)// 00:06:66:7f:b7:ce
					{
						COMGATE=val;
						break;
					}
				}
			}
		}
		DeviceNumber++;
	}
	while(SetupStatus);
	SetupDiDestroyDeviceInfoList(hdi);
}

void CConcertoDlg::SetupComUSB()
{
	DCB	param;
	CString temp;
	COMMTIMEOUTS cto;
	CString Error;
	CancelIo(HRS);
	CloseHandle(HRS);
	HRS= INVALID_HANDLE_VALUE;
	InterlockedExchange(&RUNRS,0);
	HRS=CreateFile("\\\\.\\"+COMWL,GENERIC_READ|GENERIC_WRITE,NULL,NULL,OPEN_EXISTING,0,NULL);
	if(HRS== INVALID_HANDLE_VALUE)//
	{
		COMWL="";
		scaninter="";
	}
	else
	{
		cto.ReadIntervalTimeout=1;
		cto.ReadTotalTimeoutMultiplier=1;
		cto.ReadTotalTimeoutConstant=1;//10
		cto.WriteTotalTimeoutMultiplier=1;
		cto.WriteTotalTimeoutConstant=1;
		SetCommTimeouts(HRS,&cto);
		GetCommState(HRS,&param);
		param.BaudRate=9600;           
		param.fBinary=1;          // binary mode, no EOF check   
		param.fParity=1;          // enable parity checking      
		param. fOutxCtsFlow=0;      // CTS output flow control     
		param. fOutxDsrFlow=0;      // DSR output flow control     
		param. fDtrControl=DTR_CONTROL_DISABLE;//DTR_CONTROL_ENABLE;// DTR flow control type       
		param. fDsrSensitivity=0;   // DSR sensitivity             
		param. fTXContinueOnXoff=1; // XOFF continues Tx           
		param. fOutX= 0;        // XON/XOFF out flow control       
		param. fInX= 0;         // XON/XOFF in flow control        
		param. fErrorChar= 0;   // enable error replacement        
		param. fNull= 0;        // enable null stripping           
		param. fRtsControl=RTS_CONTROL_DISABLE;   // RTS flow control                
		param. fAbortOnError=0; // abort reads/writes on error     
		param. ByteSize=8;// number of bits/byte, 4-8        
		param. Parity=NOPARITY;// 0-4=no,odd,even,mark,space      
		param. StopBits=ONESTOPBIT;// 0,1,2 = 1, 1.5, 2               
		param.ErrorChar=1; 
		SetupComm(HRS,512,512);
		CancelIo(HRS);
		PurgeComm(HRS,PURGE_TXCLEAR);
		PurgeComm(HRS,PURGE_RXCLEAR);
		SetCommState(HRS,&param);
		scaninter="USB";
		InterlockedExchange(&RUNRS,1);
		Sleep(500);
	}
}
void CConcertoDlg::SetupComBlue()
{
	DCB	param;
	CString temp;
	COMMTIMEOUTS cto;
	CString Error;
	CancelIo(HRS);
	CloseHandle(HRS);
	HRS= INVALID_HANDLE_VALUE;
	InterlockedExchange(&RUNRS,0);
	HRS=CreateFile("\\\\.\\"+COMWL,GENERIC_READ|GENERIC_WRITE,NULL,NULL,OPEN_EXISTING,0,NULL);
	if(HRS== INVALID_HANDLE_VALUE)//
	{
		MessageBox("Le port n'a pas pu être ouvert");
		scaninter="";
		COMWL="";
	}
	else
	{
		cto.ReadIntervalTimeout=1;
		cto.ReadTotalTimeoutMultiplier=1;
		cto.ReadTotalTimeoutConstant=1;//10
		cto.WriteTotalTimeoutMultiplier=1;
		cto.WriteTotalTimeoutConstant=1;
		SetCommTimeouts(HRS,&cto);
		GetCommState(HRS,&param);
		param.BaudRate=115000;
		//param.BaudRate=4800; 
		param.fBinary=1;          // binary mode, no EOF check   
		param.fParity=1;          // enable parity checking      
		param. fOutxCtsFlow=0;      // CTS output flow control     
		param. fOutxDsrFlow=0;      // DSR output flow control     
		param. fDtrControl=DTR_CONTROL_DISABLE;//DTR_CONTROL_ENABLE;// DTR flow control type       
		param. fDsrSensitivity=0;   // DSR sensitivity             
		param. fTXContinueOnXoff=1; // XOFF continues Tx           
		param. fOutX= 0;        // XON/XOFF out flow control       
		param. fInX= 0;         // XON/XOFF in flow control        
		param. fErrorChar= 0;   // enable error replacement        
		param. fNull= 0;        // enable null stripping           
		param. fRtsControl=RTS_CONTROL_DISABLE;   // RTS flow control                
		param. fAbortOnError=0; // abort reads/writes on error     
		param. ByteSize=8;// number of bits/byte, 4-8        
		param. Parity=NOPARITY;// 0-4=no,odd,even,mark,space      
		param. StopBits=ONESTOPBIT;// 0,1,2 = 1, 1.5, 2               
		param.ErrorChar=1; 
		SetupComm(HRS,512,512);
		CancelIo(HRS);
		PurgeComm(HRS,PURGE_TXCLEAR);
		PurgeComm(HRS,PURGE_RXCLEAR);
		SetCommState(HRS,&param);
		InterlockedExchange(&RUNRS,1);
		Sleep(500);
		temp="---\r\n";
		SendRS(temp);
		Sleep(500);
	}
}
void CConcertoDlg::SetupComGate()
{
	CString temp;
	COMMTIMEOUTS cto;
	CString Error;
	CancelIo(HRSG);
	BYTE clear=0;
	DCB	param;
	CloseHandle(HRSG);
	HRSG= INVALID_HANDLE_VALUE;
	InterlockedExchange(&RUNRSG,0);
	COMG=COMGATE;
	HRSG=CreateFile("\\\\.\\"+COMG,GENERIC_READ|GENERIC_WRITE,NULL,NULL,OPEN_EXISTING,0,NULL);
	if(HRSG== INVALID_HANDLE_VALUE)//
	{
		COMG=COMGATE="";
		//MessageBox("COM : "+ COMG+" ABSENT");
		InterlockedExchange(&GATECON,0);
		tgate.SetWindowText("ABSENT");
		if(FTEM&&wsel==1)
			tgate.ShowWindow(fgate);//****************
	}
	else
	{
		cto.ReadIntervalTimeout=1;
		cto.ReadTotalTimeoutMultiplier=1;
		cto.ReadTotalTimeoutConstant=1;//10
		cto.WriteTotalTimeoutMultiplier=1;
		cto.WriteTotalTimeoutConstant=1;
		SetCommTimeouts(HRSG,&cto);
		GetCommState(HRSG,&param);
		param.BaudRate=9600;           
		param.fBinary=1;          // binary mode, no EOF check   
		param.fParity=1;          // enable parity checking      
		param. fOutxCtsFlow=0;      // CTS output flow control     
		param. fOutxDsrFlow=0;      // DSR output flow control     
		param. fDtrControl=DTR_CONTROL_DISABLE;//DTR_CONTROL_ENABLE;// DTR flow control type       
		param. fDsrSensitivity=0;   // DSR sensitivity             
		param. fTXContinueOnXoff=1; // XOFF continues Tx           
		param. fOutX= 0;        // XON/XOFF out flow control       
		param. fInX= 0;         // XON/XOFF in flow control        
		param. fErrorChar= 0;   // enable error replacement        
		param. fNull= 0;        // enable null stripping           
		param. fRtsControl=RTS_CONTROL_DISABLE;   // RTS flow control                
		param. fAbortOnError=0; // abort reads/writes on error     
		param. ByteSize=8;// number of bits/byte, 4-8        
		param. Parity=NOPARITY;// 0-4=no,odd,even,mark,space      
		param. StopBits=ONESTOPBIT;// 0,1,2 = 1, 1.5, 2               
		param.ErrorChar=1; 
		SetupComm(HRSG,512,512);
		CancelIo(HRSG);
		PurgeComm(HRSG,PURGE_TXCLEAR);
		PurgeComm(HRSG,PURGE_RXCLEAR);
		SetCommState(HRSG,&param);
		InterlockedExchange(&RUNRSG,1);
		Sleep(500);

		if(wsel==1&&FTEM)//&&fprev
		{
			InterlockedExchange(&GATECON,1);
			tgate.SetWindowText("PRESENT");
			tgate.ShowWindow(fgate);//****************
			CRect rect;
			tgate.GetWindowRect(&rect);
			rect.DeflateRect(-5,-5);
			RedrawWindow(&rect,0,1|256|4);
		}
	}
}
void CConcertoDlg::GetBlueRight()
{// Vérifie que l'accès à la configuration de la clé bluetooth n'est pas utilié par un autre thread
	while(BLUERIGHT&&scaninter=="BLUE"&&HRS!=INVALID_HANDLE_VALUE )
		Sleep(100);
	if(HRS!=INVALID_HANDLE_VALUE )
		InterlockedExchange(&BASCULE,0);
	if(scaninter=="BLUE"&&HRS!=INVALID_HANDLE_VALUE)
		InterlockedExchange(&BLUERIGHT,1);
	else
		InterlockedExchange(&BLUERIGHT,0);
}
void CConcertoDlg::ReleaseBlueRight()
{// Relache le flag d'accès à la configuration de la clé
	if(CONTROL)
		InterlockedExchange(&BASCULE,1);
	InterlockedExchange(&BLUERIGHT,0);
	Sleep(500);
	if(!CONTROL)
	{
		bufin="";
		PurgeComm(HRS,PURGE_TXCLEAR);
		PurgeComm(HRS,PURGE_RXCLEAR);
	}
}
void CConcertoDlg::InitKey(int mode)
{
	CString temp;
	CString buf;
	CString com;
	int i=0;

	GetBlueRight();
	if(!BLUERIGHT)
		goto ERRCOM;
	bufin="";
	com="@@@";
	if(!SendRS(com))
		goto ERRCOM;
	buf="\r\n";
	temp=GetRetStat(0,buf,"");
	if(temp.Find("CMD",0)==-1)
		goto ERRSTAT;
	//if(master)
		com="SN,CONCERT SERVEUR\r\n";//***********************************************************************************************************
	//else
		//com="SN,CONCERT CLIENT\r\n";
	if(!SendRS(com))
		goto ERRCOM;
	buf="\r\n";
	temp=GetRetStat(0,buf,"");
	if(temp.Find("AOK",0)==-1)
		goto ERRSTAT;
	if(mode)
		com="SM,3\r\n";
	else
		com="SM,0\r\n";
	if(!SendRS(com))
		goto ERRCOM;
	buf="\r\n";
	temp=GetRetStat(0,buf,"");
	if(temp.Find("AOK",0)==-1)
		goto ERRSTAT;
	/*if(master)
		com="SD,55AA\r\n";
	else*/
		com="SD,1F00\r\n";
	if(!SendRS(com))
		goto ERRCOM;
	buf="\r\n";
	temp=GetRetStat(0,buf,"");
	if(temp.Find("AOK",0)==-1)
		goto ERRSTAT;
	com="ST,255\r\n";
	if(!SendRS(com))
		goto ERRCOM;
	buf="\r\n";
	temp=GetRetStat(0,buf,"");
	if(temp.Find("AOK",0)==-1)
		goto ERRSTAT;
	com="SU,11\r\n";
	if(!SendRS(com))
		goto ERRCOM;
	buf="\r\n";
	temp=GetRetStat(0,buf,"");
	if(temp.Find("AOK",0)==-1)
		goto ERRSTAT;
	com="SP,0556206113\r\n";
	if(!SendRS(com))
		goto ERRCOM;
	buf="\r\n";
	temp=GetRetStat(0,buf,"");
	if(temp.Find("AOK",0)==-1)
		goto ERRSTAT;
	com="S$,@\r\n";
	if(!SendRS(com))
		goto ERRCOM;
	buf="\r\n";
	temp=GetRetStat(0,buf,"");
	if(temp.Find("AOK",0)==-1)
		goto ERRSTAT;
	com="R,1\r\n";
	if(!SendRS(com))
		goto ERRCOM;
	buf="Reboot";
	temp=GetRetStat(0,buf,"");
	if(temp.Find("Reboot",0)==-1)
		goto ERRSTAT;
	//COMWL="";
	//InterlockedExchange(&WIRELESS[idx],0);
	//InterlockedExchange(&CONNECTED[idx],0);
	//InterlockedExchange(&BLUETARGET[idx],0);
	InterlockedExchange(&BASCULE,0);
	PurgeComm(HRS,PURGE_TXCLEAR);
	PurgeComm(HRS,PURGE_RXCLEAR);
	goto EXIT;
ERRCOM:;
	//KillTimer(9);
	BlueReset();
	scaninter="";
	//InterlockedExchange(&CONNECTED[idx],0);
	InterlockedExchange(&BASCULE,0);
	COMWL="";
	tcontrol.ShowWindow(0);//************	
	tcontrol.SetWindowTextA("HRDB");//************				
	//MessageBox("Erreur COM");
	goto EXIT;
ERRSTAT:;
	//KillTimer(9);
	BlueReset();
	//InterlockedExchange(&CONNECTED[idx],0);
	InterlockedExchange(&BASCULE,0);
	tcontrol.SetWindowTextA("HRDB");	//************		
	//MessageBox("Erreur STAT");
EXIT:;
	ReleaseBlueRight();
}
void CConcertoDlg::GetTargetAdress()
{//Inscrit l'adresse bluetooth du premier scanner trouvé dans la clé indexée idx
	CString temp;
	CString tmp;
	CString buf;
	CString com;
	int i;
//	int wdg;
	GetBlueRight();// demande le droit d'accèder à cette clé
	if(!BLUERIGHT)
		goto ERRCOM;
	SetTimer(9,300,NULL);//animation icone
	i=0;
	while(i<4)
	{// démarre le mode configuration de la clé
		com="@@@";
		bufin="";
		if(!SendRS(com))
			goto ERRCOM;
		buf="\r\n";
		temp=GetRetStat(0,buf,"");
		if(temp.Find("CMD",0)!=-1)
			break;
		Sleep(500);
		i++;
	}
	if(i>=4)
		goto ERRSTAT;
	com="IR\r\n";
	if(!SendRS(com))// Recherche de périphérique scanner bluetooth 55AA
		goto ERRCOM;
	buf="Inquiry, COD=55AA\r\n";
	temp=GetRetStat(0,buf,"");
	if(temp!=buf)
		goto ERRSTAT;
	buf="Inquiry Done   No Devices Found";
	temp=GetRetStat(0,"Inquiry Done\r\n","No Devices Found\r\n");
	if(temp.Find("No Devices Found",0)!=-1)
	{
		//tcontrol.SetWindowTextA("HRDB");//*******************			
	}
	else
	{
		if(((i=temp.Find("SPOT",0))!=-1)&&i>13)
		{//Vérifie le nom du périphérique
			blueadress=temp.Mid(i-13,12);// adresse du scanner 
			if(fdev==1)//log on dev
			{
				Logger* log = Logger::getInstance(this);
				log->Log("GetTargetAdress : "+blueadress);
			}
			com="SR,"+blueadress+"\r\n";
			if(!SendRS(com))// inscrit dans la clé l'adresse du périphérique auquel se connecter automatiquement
				goto ERRCOM;
			buf="\r\n";
			temp=GetRetStat(0,buf,"");
			if(temp.Find("AOK",0)==-1)
				goto ERRSTAT;
		}
		else
		{
			tcontrol.ShowWindow(0);
		}
	}
	com="---\r\n";// ferme l'accès configuration de la clé
	SendRS(com);
	buf="\r\n";
	temp=GetRetStat(0,buf,"");
	if(temp.Find("END",0)==-1)
		goto ERRSTAT;
	goto EXIT;
ERRCOM:;
	BlueReset();
	scaninter="";
	COMWL="";
	tcontrol.ShowWindow(0);//********************
	tcontrol.SetWindowTextA("HRDB");//*****************			
	total.SetWindowTextA("Erreur écriture GetTargetAdress = "+com);
	MessageBox("Erreur écriture GetTargetAdress = "+com+" buf ="+buf);
	goto EXIT;
ERRSTAT:;
	BlueReset();
	tcontrol.SetWindowTextA("HRDB");			
EXIT:;
	//KillTimer(9);
	ReleaseBlueRight();
}
BOOL CConcertoDlg::SendRS(CString com)
{
	DWORD len;
	DWORD lenout;
	CString temp=com;
	lenout=(DWORD)temp.GetLength();
	if(HRS!=INVALID_HANDLE_VALUE )
	{
		WriteFile(HRS,temp.GetBuffer(lenout),lenout,&len,NULL);
		if(len==lenout)
		{
			return TRUE;
		}
		else
		{
			CancelIo(HRS);
			CloseHandle(HRS);
			HRS= INVALID_HANDLE_VALUE;
			InterlockedExchange(&RUNRS,0);
			InterlockedExchange(&BASCULE,0);
			InterlockedExchange(&BLUERIGHT,0);
			scaninter="";
			COMWL="";
			tcontrol.ShowWindow(0);
			PostMessage(WM_USER+8,0,0);
		}
	}
	return FALSE;
}
CString CConcertoDlg::GetRetStat(int len,CString balise1,CString balise2)
{//Renvoi le status de retour du périphérique sollicité
	CString temp;
	int wdg=0;
	while(wdg<200&&scaninter=="BLUE"&&!ABORT)
	{
		if((len!=0&&bufin.GetLength()>=len)||(len==0&&balise1!=""&&bufin.Find(balise1)!=-1)||(len==0&&balise2!=""&&bufin.Find(balise2)!=-1))
			break;
		wdg++;
		Sleep(100);
	}
	temp=bufin;
	bufin="";
	if(wdg<200&&scaninter=="BLUE"&&!ABORT)
	{
		return temp;
	}
	else
	{
		return"";
	}
}
void CConcertoDlg::SendSpot(BYTE code)
{// Envoi la couleur du résultat du controle vers l'embase du scanner par la clé bluetooth
	DWORD len;
	CString temp;
	BYTE clear=0;
	if(scaninter=="BLUE"&&BASCULE)
	{
		GetBlueRight();
		WriteFile(HRS,&clear,1,&len,NULL);
		//temp=GetRetStat(1,"","");
		WriteFile(HRS,&code,1,&len,NULL);
		ReleaseBlueRight();
	}
}

void CConcertoDlg::BlueReset()
{// Envoi d'une commande stopant le mode configuration de la clé bluetooth
	CString temp;
	GetBlueRight();
	CString com="---\r\n";
	if(scaninter=="BLUE")
		SendRS(com);
	Sleep(100);
	ReleaseBlueRight();
}



void CConcertoDlg::OnStnClickedTemradio()
{
	;
}
void CConcertoDlg::OnStnClickedTemcontrol()
{
	if(CONTROL)
		;//ValideControl();
	else
	{
		CString com="---\r\n";
		if(!SEARCH&&scaninter=="BLUE")
		{
			CMessage dlg;
			CNum num;
			CString temp1;
			CString temp2;
			CString temp3;
			num.wlargeur=(int)((float)(wlargeur/2));
			num.whauteur=whauteur/3;
			num.nID=0;
			num.chiffre = 8;
			num.mode=4;
			num.nombre="";
			num.txtmessage="";
			num.DoModal();
			if(num.nombre!=codeadmin&&num.nombre!=codemanager)
				goto END;
			dlg.mes1=txtm[14];//"Recherche automatique des scanners";
			dlg.mes2=txtm[15];//"Pour annuler la recherche en cours";
			dlg.mes3=txtm[16];//"cliquer de nouveau sur l'antenne";
			dlg.mode=7;
			if(dlg.DoModal()==IDOK)
			{
				InterlockedExchange(&SEARCH,1);
				InterlockedExchange(&PAUSERS,1);
				tcontrol.SetWindowTextA("HRDC");//************	
				PostMessage(WM_USER+9,0,0);//RedrawWindow(0,0,1|256|4);
			}
		}
		else
		{
			if(SEARCH&&scaninter=="BLUE")
			{		
				InterlockedExchange(&SEARCH,0);
				PostMessage(WM_USER+9,0,0);//RedrawWindow(0,0,1|256|4);
			}
		}
	}
END:;
}
void CConcertoDlg::BlueSearch()
{// Recherche d'un périphérique pour la clé indexée idx
	CString temp1;
	CString temp;
	if(SEARCH==2&&STOPRS==0&&PAUSERS==0)
	{
		nscan.ShowWindow(0);
		scan=txtc[114];//"Recherche Scanner en cours";
		nscan.SetWindowTextA(scan);
		nscan.ShowWindow(1);
		blueadress="";
		//Sleep(2000);
		if(scaninter=="BLUE")
		{// Si port COM ouvert
			InitKey(0);// Déconnecte la clé du scanner
			Sleep(1000);
			GetTargetAdress();
			Sleep(1000);
			InitKey(1);// Reconnecte la clé au scanner
			Sleep(1000);
			if(blueadress=="")
			{//Si pas d'adresse reconnu on marque la clé non connectée
				blueadress =txtc[116];// "non connecté";
			}
		}
		else
		{
			blueadress = txtc[117];//"non utilisé";
		}
		nscan.ShowWindow(0);
		scan=txtc[115]+" : "+blueadress;//"Scanner N°"
		nscan.SetWindowTextA(scan);
		nscan.ShowWindow(1);
		SEARCH=0;
		Sleep(1000);
	}

}
void CConcertoDlg::GetTargetConnected()
{// Cherche à savoir si le scanner est connecté sur la clé bluetooth résultat dans CONNECTED[idx]	
	CString temp;
	CString tmp;
	CString buf;
	LONG TEMPCONNECTED;
	//SetTimer(9,300,NULL);
	int i;
	CString com;
	GetBlueRight();
	if(!BLUERIGHT)
		goto ERRCOM;
	bufin="";
	i=0;
	while(i<4)
	{
		com="@@@";
		if(!SendRS(com))
			goto ERRCOM;
		buf="\r\n";
		temp=GetRetStat(0,buf,"");
		if(temp.Find("CMD",0)!=-1)
			break;
		Sleep(1000);
		i++;
	}
	if(i>=4)
	{
		goto ERRSTAT;
	}
	bufin="";
	com="GK\r\n";
	if(!SendRS(com))
		goto ERRCOM;
	buf="\r\n";
	temp=GetRetStat(0,buf,"");
	//KillTimer(9);
	if(temp.Find("1",0)!=-1)
	{
		TEMPCONNECTED=1;
	}
	else
	{
		TEMPCONNECTED=0;
	}
	//InterlockedExchange(&BLUETARGET[idx],1);
	goto FIN;	
ERRCOM:;
	//KillTimer(9);
	TEMPCONNECTED=0;
	goto FIN;
ERRSTAT:;
	//KillTimer(9);
	TEMPCONNECTED=0;

FIN:;
	com="---\r\n";
	SendRS(com);
	buf="\r\n";
	temp=GetRetStat(0,buf,"");
	bufin="";	
	InterlockedExchange(&CONNECTED,TEMPCONNECTED);
	ReleaseBlueRight();
}



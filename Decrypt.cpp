#include "stdafx.h"
#include "Concerto.h"
#include "ConcertoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define crypwrite 0			// Génération clés

HCRYPTPROV CConcertoDlg::InitCrypto(int mode)
{

	HCRYPTPROV hProv;
	HCRYPTKEY hKey;
	DWORD len;
	BYTE* data;
	HANDLE hf;
	CString txtsign;
	CString appdir;
	CString temp;
	GetModuleFileName(NULL,appdir.GetBuffer(256),256);
	appdir.ReleaseBuffer(-1);
	appdir=appdir.Left(appdir.ReverseFind('\\'));
retry:;
	if(CryptAcquireContext(&hProv,NULL,NULL,PROV_RSA_FULL,CRYPT_NEWKEYSET)&&ticimp)
	{
		if(crypwrite==0)
		{
			if(mode==0)
			{
				len=0x494;
				if(!CryptImportKey(hProv,SIGN2048,len,NULL,CRYPT_EXPORTABLE,&hKey))
					AfxMessageBox("CryptImportKey ERROR",0,0);
			}
			else
			{
				len=0x254;
				if(!CryptImportKey(hProv,SIGN1024,len,NULL,CRYPT_EXPORTABLE,&hKey))
					AfxMessageBox("CryptImportKey ERROR",0,0);
			}
		}
		else
		{
			hKey=NULL;
			if(mode==0)
			{
				if(!CryptGenKey(hProv,AT_SIGNATURE,0x08000000|CRYPT_EXPORTABLE,&hKey))
					AfxMessageBox("CryptGenKey ERROR",0,0);
			}
			else
			{
				if(!CryptGenKey(hProv,AT_SIGNATURE,0x04000000|CRYPT_EXPORTABLE,&hKey))
					AfxMessageBox("CryptGenKey ERROR",0,0);
			}
			if(hKey!=NULL)
			{
				len=0;
				if(CryptExportKey(hKey,0,PRIVATEKEYBLOB,0,NULL,&len))
				{
					data=new BYTE[len];
					if(CryptExportKey(hKey,0,PRIVATEKEYBLOB,0,data,&len))
					{
						if(mode==0)
							hf=CreateFile(appdir+"\\PRIVATEKEYBLOB2048.avx",FILE_ALL_ACCESS,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
						else
							hf=CreateFile(appdir+"\\PRIVATEKEYBLOB1024.avx",FILE_ALL_ACCESS,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
						if(hf!=INVALID_HANDLE_VALUE)
						{
							txtsign="{";
							for(int i=0;i<(int)len;i++)
							{
								temp.Format("0x%X,",*(data+i));
								txtsign	+=temp;
							}
							txtsign.SetAt(txtsign.GetLength()-1,'}');
							WriteFile(hf,data,len,&len,NULL);
							FlushFileBuffers(hf);
							CloseHandle(hf);
							if(mode==0)
								hf=CreateFile(appdir+"\\PRIVATEKEYBLOB2048.txt",FILE_ALL_ACCESS,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
							else
								hf=CreateFile(appdir+"\\PRIVATEKEYBLOB1024.txt",FILE_ALL_ACCESS,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
							if(hf!=INVALID_HANDLE_VALUE)
							{
								WriteFile(hf,txtsign.GetBuffer(txtsign.GetLength()),txtsign.GetLength(),&len,NULL);
								FlushFileBuffers(hf);
								CloseHandle(hf);
							}
						}
					}
					else
						AfxMessageBox("CryptExportPrivateKey ERROR",0,0);
					delete []data;
				}
				else
					AfxMessageBox("CryptExportPrivateKey ERROR",0,0);
				if(CryptExportKey(hKey,0,PUBLICKEYBLOB,0,NULL,&len))
				{
					data=new BYTE[len];
					if(CryptExportKey(hKey,0,PUBLICKEYBLOB,0,data,&len))
					{
						if(mode==0)
							hf=CreateFile(appdir+"\\PUBLICKEYBLOB2048.avx",FILE_ALL_ACCESS,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
						else
							hf=CreateFile(appdir+"\\PUBLICKEYBLOB1024.avx",FILE_ALL_ACCESS,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
						if(hf!=INVALID_HANDLE_VALUE)
						{
							WriteFile(hf,data,len,&len,NULL);
							FlushFileBuffers(hf);
							CloseHandle(hf);
						}
					}
					else
						AfxMessageBox("CryptExportPublicKey ERROR",0,0);
					delete []data;
				}
				else
					AfxMessageBox("CryptExportPublicKey ERROR",0,0);
			}
		}
	}
	else
	{
		if(GetLastError()==NTE_EXISTS)
		{
			CryptAcquireContext(&hProv,NULL,NULL,PROV_RSA_FULL,CRYPT_DELETEKEYSET);
			hProv=NULL;
			Sleep(100);
			goto retry;
		}
	}
	return hProv;
}
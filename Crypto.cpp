#include "stdafx.h"
#include "Concerto.h"
#include "ConcertoDlg.h"
#include "Key.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define crypwrite 0			//1 = Génération clés 0 = utilisation des clés


void CConcertoDlg::InitCrypto(int mode)
{
	HCRYPTPROV hProv;
	HCRYPTKEY hKey;
	int len;
	DWORD datalen;
	DWORD txtlen;
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
				len=sizeof(SIGN2048);
				if(!CryptImportKey(hProv,SIGN2048,len,NULL,0,&hKey))
					AfxMessageBox("CryptImportKey ERROR",0,0);
			}
			else
			{
				len=sizeof(SIGN1024);
				if(!CryptImportKey(hProv,SIGN1024,len,NULL,0,&hKey))
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
				datalen=0;
				if(CryptExportKey(hKey,0,PRIVATEKEYBLOB,0,NULL,&datalen))
				{
					data=new BYTE[datalen];
					if(CryptExportKey(hKey,0,PRIVATEKEYBLOB,0,data,&datalen))
					{
						if(mode==0)
							hf=CreateFile(appdir+"\\PRIVATEKEYBLOB2048.avx",FILE_ALL_ACCESS,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
						else
							hf=CreateFile(appdir+"\\PRIVATEKEYBLOB1024.avx",FILE_ALL_ACCESS,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
						if(hf!=INVALID_HANDLE_VALUE)
						{
							txtsign="{";
							for(int i=0;i<(int)datalen;i++)
							{
								temp.Format("0x%X,",*(data+i));
								txtsign	+=temp;
							}
							txtsign.SetAt(txtsign.GetLength()-1,'}');
							WriteFile(hf,data,datalen,&datalen,NULL);
							FlushFileBuffers(hf);
							CloseHandle(hf);
							if(mode==0)
								hf=CreateFile(appdir+"\\PRIVATEKEYBLOB2048.txt",FILE_ALL_ACCESS,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
							else
								hf=CreateFile(appdir+"\\PRIVATEKEYBLOB1024.txt",FILE_ALL_ACCESS,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
							if(hf!=INVALID_HANDLE_VALUE)
							{
								WriteFile(hf,txtsign.GetBuffer(txtsign.GetLength()),txtsign.GetLength(),&txtlen,NULL);
								FlushFileBuffers(hf);
								CloseHandle(hf);
							}
						}
						if(mode==0)
							hf=CreateFile(appdir+"\\PRIVATEKEYBLOB2048.nfo",GENERIC_READ|GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
						else
							hf=CreateFile(appdir+"\\PRIVATEKEYBLOB1024.nfo",GENERIC_READ|GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
						if(hf!=INVALID_HANDLE_VALUE)
						{
							len=Base64EncodeGetRequiredLength(datalen,ATL_BASE64_FLAG_NONE);//ATL_BASE64_FLAG_NOCRLF
							if(!Base64Encode(data,datalen,txtsign.GetBuffer(len),&len,ATL_BASE64_FLAG_NONE))//ATL_BASE64_FLAG_NOCRLF
							{
								temp.Format("%X",GetLastError());//NTE_BAD_KEY
								MessageBox("Erreur N° "+temp+" Base64Decode");
								txtsign="ERREUR PRIVATE NFO";
							}
							else
								txtsign.ReleaseBuffer(len);/**/
							WriteFile(hf,txtsign.GetBuffer(txtsign.GetLength()),txtsign.GetLength(),&txtlen,NULL);
							FlushFileBuffers(hf);
							CloseHandle(hf);
						}
					}
					else
						AfxMessageBox("CryptExportPrivateKey ERROR",0,0);
					delete []data;
				}
				else
					AfxMessageBox("CryptExportPrivateKey ERROR",0,0);
				if(CryptExportKey(hKey,0,PUBLICKEYBLOB,0,NULL,&datalen))
				{
					data=new BYTE[datalen];
					if(CryptExportKey(hKey,0,PUBLICKEYBLOB,0,data,&datalen))
					{
						if(mode==0)
							hf=CreateFile(appdir+"\\PUBLICKEYBLOB2048.txt",FILE_ALL_ACCESS,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
						else
							hf=CreateFile(appdir+"\\PUBLICKEYBLOB1024.txt",FILE_ALL_ACCESS,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
							txtsign="{";
							for(int i=0;i<(int)datalen;i++)
							{
								temp.Format("0x%X,",*(data+i));
								txtsign	+=temp;
							}
							txtsign.SetAt(txtsign.GetLength()-1,'}');
						if(hf!=INVALID_HANDLE_VALUE)
						{
							WriteFile(hf,txtsign.GetBuffer(txtsign.GetLength()),txtsign.GetLength(),&txtlen,NULL);
							FlushFileBuffers(hf);
							CloseHandle(hf);
						}
						if(mode==0)
							hf=CreateFile(appdir+"\\PUBLICKEYBLOB2048.avx",FILE_ALL_ACCESS,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
						else
							hf=CreateFile(appdir+"\\PUBLICKEYBLOB1024.avx",FILE_ALL_ACCESS,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
						if(hf!=INVALID_HANDLE_VALUE)
						{
							WriteFile(hf,data,datalen,&txtlen,NULL);
							FlushFileBuffers(hf);
							CloseHandle(hf);
						}
						if(mode==0)
							hf=CreateFile(appdir+"\\PUBLICKEYBLOB2048.nfo",GENERIC_READ|GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
						else
							hf=CreateFile(appdir+"\\PUBLICKEYBLOB1024.nfo",GENERIC_READ|GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
						if(hf!=INVALID_HANDLE_VALUE)
						{
							len=Base64EncodeGetRequiredLength(datalen,ATL_BASE64_FLAG_NONE);//ATL_BASE64_FLAG_NOCRLF
							if(!Base64Encode(data,datalen,txtsign.GetBuffer(len),&len,ATL_BASE64_FLAG_NONE))//ATL_BASE64_FLAG_NOCRLF
							{
								temp.Format("%X",GetLastError());//NTE_BAD_KEY
								MessageBox("Erreur N° "+temp+" Base64Decode");
								txtsign="ERREUR PUBLIC NFO";
							}
							else
								txtsign.ReleaseBuffer(len);/**/
							WriteFile(hf,txtsign.GetBuffer(txtsign.GetLength()),txtsign.GetLength(),&txtlen,NULL);
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
	if(mode==0)
		hProv2048=hProv;
	else
		hProv1024=hProv;
}

void CConcertoDlg::DeleteCrypto()
{
	if(ticimp==1)
	{
		
		CryptAcquireContext(&hProv2048,NULL,NULL,PROV_RSA_FULL,CRYPT_DELETEKEYSET);
		CryptAcquireContext(&hProv1024,NULL,NULL,PROV_RSA_FULL,CRYPT_DELETEKEYSET);
	}
}


/*void CConcertoDlg::GetPublicSignInfo()
{
	CString temp;
	CString txtsign;
	DWORD datalen;
	int len;
	HANDLE hf;
	datalen=276;
	hf=CreateFile(appdir+"\\PUBLICKEYBLOB2048.nfo",GENERIC_READ|GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	if(hf!=INVALID_HANDLE_VALUE)
	{
		len=Base64EncodeGetRequiredLength(datalen,ATL_BASE64_FLAG_NONE);//ATL_BASE64_FLAG_NOCRLF
		if(!Base64Encode(PUBLICKEYBLOB2048,datalen,txtsign.GetBuffer(len),&len,ATL_BASE64_FLAG_NONE))//ATL_BASE64_FLAG_NOCRLF
		{
			temp.Format("%X",GetLastError());//NTE_BAD_KEY
			MessageBox("Erreur N° "+temp+" Base64Decode");
			txtsign="ERREUR 2048";
		}
		else
			txtsign.ReleaseBuffer(len);
		WriteFile(hf,txtsign.GetBuffer(txtsign.GetLength()),txtsign.GetLength(),&datalen,NULL);
		FlushFileBuffers(hf);
		CloseHandle(hf);
	}
	datalen=148;
	hf=CreateFile(appdir+"\\PUBLICKEYBLOB1024.nfo",GENERIC_READ|GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	if(hf!=INVALID_HANDLE_VALUE)
	{
		len=Base64EncodeGetRequiredLength(datalen,ATL_BASE64_FLAG_NONE);//ATL_BASE64_FLAG_NOCRLF
		if(!Base64Encode(PUBLICKEYBLOB1024,datalen,txtsign.GetBuffer(len),&len,ATL_BASE64_FLAG_NONE))//ATL_BASE64_FLAG_NOCRLF
		{
			temp.Format("%X",GetLastError());//NTE_BAD_KEY
			MessageBox("Erreur N° "+temp+" Base64Decode");
			txtsign="ERREUR 1024";
		}
		else
			txtsign.ReleaseBuffer(len);
		WriteFile(hf,txtsign.GetBuffer(txtsign.GetLength()),txtsign.GetLength(),&datalen,NULL);
		FlushFileBuffers(hf);
		CloseHandle(hf);
	}
}*/

CString CConcertoDlg::GetDocSignature(CString signtxt, int type)
{
	CString resencode;
	CString signature=signtxt;
	CString temp;
	DWORD datalen;
	int len;
	HCRYPTHASH  hHash;
	BYTE* pdata;
	if(CryptCreateHash(hProv1024,CALG_MD5,0,0,&hHash))
	{
		if(CryptHashData(hHash,(BYTE*) signtxt.GetBuffer(signtxt.GetLength()),signtxt.GetLength(),0))
		{
			if(CryptSignHash(hHash,AT_SIGNATURE,NULL,0,NULL,&datalen))
			{
				pdata= new BYTE[datalen];
				if(CryptSignHash(hHash,AT_SIGNATURE,NULL,0,pdata,&datalen))
				{
					len=Base64EncodeGetRequiredLength(datalen,ATL_BASE64_FLAG_NOCRLF);
					if(Base64Encode(pdata,datalen,resencode.GetBuffer(len),&len,ATL_BASE64_FLAG_NOCRLF))
					{
						resencode.ReleaseBuffer(len);
						resencode.Replace("+","-");// Conversion URL
						resencode.Replace("/","_");// Conversion URL
					}
					else
						resencode="Erreur";	
				}
				else
					MessageBox("Erreur CryptSignHash signature");
				delete []pdata;
			}
			else
				MessageBox("Erreur CryptHashData signature à 0");
		}
		else
			MessageBox("Erreur CryptHashData signature");
		CryptDestroyHash(hHash);
	}
	else
	{
		temp.Format("%X",GetLastError());//NTE_BAD_KEY
		MessageBox("Erreur N° "+temp+" CryptCreateHash signature");
	}

	return resencode;//"";
}
CString CConcertoDlg::GetFileSignature(CString signtxt, int type)
{
	CString resencode;
	CString signature=signtxt;
	CString temp;
	DWORD datalen;
	int len;
	HCRYPTHASH  hHash;
	BYTE* pdata;
	if(CryptCreateHash(hProv2048,CALG_MD5,0,0,&hHash))
	{
		if(CryptHashData(hHash,(BYTE*) signtxt.GetBuffer(signtxt.GetLength()),signtxt.GetLength(),0))
		{
			if(CryptSignHash(hHash,AT_SIGNATURE,NULL,0,NULL,&datalen))
			{
				pdata= new BYTE[datalen];
				if(CryptSignHash(hHash,AT_SIGNATURE,NULL,0,pdata,&datalen))
				{
					len=Base64EncodeGetRequiredLength(datalen,ATL_BASE64_FLAG_NOCRLF);
					if(Base64Encode(pdata,datalen,resencode.GetBuffer(len),&len,ATL_BASE64_FLAG_NOCRLF))
					{
						resencode.ReleaseBuffer(len);
						resencode.Replace("+","-");// Conversion URL
						resencode.Replace("/","_");// Conversion URL
					}
					else
						resencode="Erreur";	
				}
				else
					MessageBox("Erreur CryptSignHash signature");
		
				delete []pdata;
			}
			else
				MessageBox("Erreur CryptHashData signature à 0");
		}
		else
			MessageBox("Erreur CryptHashData signature");
		CryptDestroyHash(hHash);
	}
	else
	{
		temp.Format("%X",GetLastError());
		MessageBox("Erreur N° "+temp+" CryptCreateHash signature");
	}
	return resencode;//"";
}

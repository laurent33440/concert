// Concert.cpp : Définit les comportements de classe pour l'application.
//

#include "stdafx.h"
#include "Concerto.h"
#include "ConcertoDlg.h"
#include <tlhelp32.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// CConcertApp

BEGIN_MESSAGE_MAP(CConcertoApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// construction CConcertApp

CConcertoApp::CConcertoApp()
{
	// TODO : ajoutez ici du code de construction,
	// Placez toutes les initialisations significatives dans InitInstance
}


// Seul et unique objet CConcertApp

CConcertoApp theApp;


// initialisation de CConcertApp

BOOL CConcertoApp::InitInstance()
{
	STARTUPINFO csui;
	PROCESS_INFORMATION cpi;
	CString temp;
	CString dir;
	int wdg=0;
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	CConcertoDlg dlg;
	AfxOleInit();
	// InitCommonControlsEx() est requis sur Windows XP si le manifeste de l'application
	// spécifie l'utilisation de ComCtl32.dll version 6 ou ultérieure pour activer les
	// styles visuels.  Dans le cas contraire, la création de fenêtres échouera.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// À définir pour inclure toutes les classes de contrôles communs à utiliser
	// dans votre application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);
	GetModuleFileName(NULL,dlg.appdir.GetBuffer(MAX_PATH),MAX_PATH);
	dlg.appdir.ReleaseBuffer(-1);
	dlg.appdir=dlg.appdir.Left(dlg.appdir.ReverseFind('\\'));
	dir=dlg.appdir+"\\Control";
	dlg.hrun=CreateFile(dir+"\\Run.dat",GENERIC_READ|GENERIC_WRITE,0,NULL,CREATE_NEW,FILE_ATTRIBUTE_NORMAL,NULL);
	if(dlg.hrun==INVALID_HANDLE_VALUE)// Si une application Concert tourne déjà on ferme)
	{
		return FALSE;
	}/**/
	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();
	// Get the LUID for the shutdown privilege. 


	// Initialisation standard
	// Si vous n'utilisez pas ces fonctionnalités et que vous souhaitez réduire la taille
	// de votre exécutable final, vous devez supprimer ci-dessous
	// les routines d'initialisation spécifiques dont vous n'avez pas besoin.
	// Changez la clé de Registre sous laquelle nos paramètres sont enregistrés
	// TODO : modifiez cette chaîne avec des informations appropriées,
	// telles que le nom de votre société ou organisation
	SetRegistryKey(_T("BARMATIC France"));
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	m_pMainWnd = &dlg;
	
	while(::FindWindow(NULL,"EXPLOCK")==NULL)
	{
		wdg++;
		if(wdg>15)
			break;
		Sleep(500);
	}
	/*

	if(::FindWindow(NULL,"EXPLOCK")==NULL)// Recherche si le bloqueur d'explorer Windows a été lancé
	{// Si non tente de le relancer
		ZeroMemory( &csui, sizeof(csui) );
		csui.cb = sizeof(csui);
		ZeroMemory( &cpi, sizeof(cpi) );
		GetStartupInfo(&csui);
		temp=dlg.appdir+"\\Explock.exe";
		CreateProcess(NULL,temp.GetBuffer(),NULL,NULL,FALSE,NORMAL_PRIORITY_CLASS,NULL,NULL,&csui,&cpi);// Le lance
		CloseHandle(cpi.hProcess);
		CloseHandle(cpi.hThread);
		ZeroMemory( &csui, sizeof(csui) );
		csui.cb = sizeof(csui);
		ZeroMemory( &cpi, sizeof(cpi) );
		GetStartupInfo(&csui);
		temp="cmd.exe /c taskkill /f /im explorer.exe";// sécurité bureau windows
		CreateProcess(NULL,temp.GetBuffer(),NULL,NULL,FALSE,NORMAL_PRIORITY_CLASS,NULL,NULL,&csui,&cpi);//Ferme l'explorer windows
		CloseHandle(cpi.hProcess);
		CloseHandle(cpi.hThread);
	}
	*/
	dlg.RUNRS=0;
	dlg.STOPRS=0;
	dlg.STOP=0;
	dlg.READY=0;
	dlg.QUIT=0;
	dlg.END=0;
	dlg.SPOOL=0;
	dlg.CONTROL=0;
	dlg.SPN=0;
	dlg.SPR=0;
	dlg.SPW=0;
	dlg.InitCrypto(0);
	dlg.InitCrypto(1);
	INT_PTR nResponse = dlg.DoModal();
	if(dlg.hrun)
	{
		if(CloseHandle(dlg.hrun))
		{
			dlg.hrun=NULL;
		}
	}
	DeleteFile(dir+"\\Run.dat");	// Efface le fichier attestant du lancement de cette application
	DeleteFile(dir+"\\Status.dat");	// Efface le fichier attestant que c'est un maître si besoin
	dlg.DeleteCrypto();				// Ferme l'accès à la cryptographie
	GdiplusShutdown(gdiplusToken);	// Ferme l'accès au service GdiPlus
	if (nResponse == IDOK)			// à la fermeture de la fenêtre d'application test si un update est présent
	{
		if(dlg.fupdate&&!dlg.fadmin)// si flag update est présent car fichier update a été détecté et préparé
		{
			ZeroMemory( &csui, sizeof(csui) );
			csui.cb = sizeof(csui);
			ZeroMemory( &cpi, sizeof(cpi) );
			GetStartupInfo(&csui);
			temp.Format(" -p%u",rarcrypt);

			dlg.copyupdate+=temp;
			temp.Format("%u",(int)dlg.fversion);
			dlg.WriteConfigString("Param","OldVersion",temp);// sauvegarde la version venant d'être utilisée
			temp=dlg.copyupdate;
			Sleep(500);
			CreateProcess(NULL,temp.GetBuffer(),NULL,NULL,FALSE,BELOW_NORMAL_PRIORITY_CLASS,NULL,NULL,&csui,&cpi);// lance l'autodécompressible d'update
		}
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO : placez ici le code définissant le comportement lorsque la boîte de dialogue est
		//  fermée avec Annuler
	}
	return FALSE;
}

BOOL CConcertoApp::SystemShutdown()	// fonction de fermeture de Windows donc extinction de la billetterie
{
   HANDLE hToken; 
   TOKEN_PRIVILEGES tkp; 
 
   // Get a token for this process. 
 
   if (!OpenProcessToken(GetCurrentProcess(), 
        TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) 
      return( FALSE ); 
 
   // Get the LUID for the shutdown privilege. 
 
   LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, 
        &tkp.Privileges[0].Luid); 
 
   tkp.PrivilegeCount = 1;  // one privilege to set    
   tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED; 
 
   // Get the shutdown privilege for this process. 
 
   AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, 
        (PTOKEN_PRIVILEGES)NULL, 0); 
 
   if (GetLastError() != ERROR_SUCCESS) 
      return FALSE; 
 
   // Shut down the system and force all applications to close. 
 
   if (!ExitWindowsEx(EWX_POWEROFF | EWX_FORCEIFHUNG, 
               SHTDN_REASON_MAJOR_OTHER |
			   SHTDN_REASON_MINOR_OTHER |
			   SHTDN_REASON_FLAG_PLANNED)) 
		return FALSE; 

   return TRUE;
}

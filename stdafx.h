// stdafx.h : fichier Include pour les fichiers Include système standard,
// ou les fichiers Include spécifiques aux projets qui sont utilisés fréquemment,
// et sont rarement modifiés

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN		// Exclure les en-têtes Windows rarement utilisés
#endif

// Modifiez les définitions suivantes si vous devez cibler une plate-forme avant celles spécifiées ci-dessous.
// Reportez-vous à MSDN pour obtenir les dernières informations sur les valeurs correspondantes pour les différentes plates-formes.
#ifndef WINVER				// Autorise l'utilisation des fonctionnalités spécifiques à Windows XP ou version ultérieure.
#define WINVER 0x0501		// Attribuez la valeur appropriée à cet élément pour cibler d'autres versions de Windows.
#endif

#ifndef _WIN32_WINNT		// Autorise l'utilisation des fonctionnalités spécifiques à Windows XP ou version ultérieure.                   
#define _WIN32_WINNT 0x0501	// Attribuez la valeur appropriée à cet élément pour cibler d'autres versions de Windows.
#endif						

#ifndef _WIN32_WINDOWS		// Autorise l'utilisation des fonctionnalités spécifiques à Windows 98 ou version ultérieure.
#define _WIN32_WINDOWS 0x0410 // Attribuez la valeur appropriée à cet élément pour cibler Windows Me ou version ultérieure.
#endif

#ifndef _WIN32_IE			// Autorise l'utilisation des fonctionnalités spécifiques à Internet Explorer 6.0 ou version ultérieure.
#define _WIN32_IE 0x0600	// Attribuez la valeur appropriée à cet élément pour cibler d'autres versions d'Internet Explorer.
#endif

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// certains constructeurs CString seront explicites

// désactive le masquage MFC de certains messages d'avertissement courants et par ailleurs souvent ignorés
#define _AFX_ALL_WARNINGS

#define _CRT_RAND_S
#include <ZipArchive.h>
#include <afxwin.h>         // composants MFC principaux et standard
#include <afxext.h>         // extensions MFC
#include "Winspool.h"
#include "Setupapi.h"
#include "Windows.h"
#include "Winbase.h"
#include <Mmsystem.h>
#include <math.h>
#include <atlcrypt.h>        // Classes MFC Automation
#include <WinCrypt.h>
#include <afxdisp.h>        // Classes MFC Automation
#include <gdiplus.h>
#include <gl\Gl.h>
#include <gl\Glu.h>
#include "Sddl.h"
#include "Aclapi.h"
#include "Ntsecapi.h"
#include "Shobjidl.h"
//#include "qrencode.h"
#include <stdlib.h>
#include <limits.h>
#include "Vfw.h"
#include <afxinet.h>
#include <stdio.h>

using namespace Gdiplus;


#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>		// Prise en charge MFC pour les contrôles communs Internet Explorer 4
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// Prise en charge des MFC pour les contrôles communs Windows
#endif // _AFX_NO_AFXCMN_SUPPORT


#include <afxsock.h>		// extensions du socket MFC
#include <atlenc.h>		// extensions du socket MFC

#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif

const CString TCV[107] = {
"11011001100",
"11001101100",
"11001100110",
"10010011000",
"10010001100",
"10001001100",
"10011001000",
"10011000100",
"10001100100",
"11001001000",
"11001000100",
"11000100100",
"10110011100",
"10011011100",
"10011001110",
"10111001100",
"10011101100",
"10011100110",
"11001110010",
"11001011100",
"11001001110",
"11011100100",
"11001110100",
"11101101110",
"11101001100",
"11100101100",
"11100100110",
"11101100100",
"11100110100",
"11100110010",
"11011011000",
"11011000110",
"11000110110",
"10100011000",
"10001011000",
"10001000110",
"10110001000",
"10001101000",
"10001100010",
"11010001000",
"11000101000",
"11000100010",
"10110111000",
"10110001110",
"10001101110",
"10111011000",
"10111000110",
"10001110110",
"11101110110",
"11010001110",
"11000101110",
"11011101000",
"11011100010",
"11011101110",
"11101011000",
"11101000110",
"11100010110",
"11101101000",
"11101100010",
"11100011010",
"11101111010",
"11001000010",
"11110001010",
"10100110000",
"10100001100",
"10010110000",
"10010000110",
"10000101100",
"10000100110",
"10110010000",
"10110000100",
"10011010000",
"10011000010",
"10000110100",
"10000110010",
"11000010010",
"11001010000",
"11110111010",
"11000010100",
"10001111010",
"10100111100",
"10010111100",
"10010011110",
"10111100100",
"10011110100",
"10011110010",
"11110100100",
"11110010100",
"11110010010",
"11011011110",
"11011110110",
"11110110110",
"10101111000",
"10100011110",
"10001011110",
"10111101000",
"10111100010",
"11110101000",
"11110100010",
"10111011110",
"10111101110",
"11101011110",
"11110101110",
"11010000100",
"11010010000",
"11010011100",
"1100011101011"
};


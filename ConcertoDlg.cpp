// ConcertDlg.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "Concerto.h"
#include "ConcertoDlg.h"
#include "Num.h"
#pragma comment (lib, "setupapi.lib")
#include "Npapi.h"
#include "Winerror.h"
#include <ZipArchive.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// boîte de dialogue CConcertoDlg

CConcertoDlg::CConcertoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConcertoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CConcertoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MANAGER, butmanager);//
	DDX_Control(pDX, IDC_QUITTER, butquitter);//
	DDX_Control(pDX, IDC_RETURN, breturn);//
	DDX_Control(pDX, IDC_FIG, butinf);//
	DDX_Control(pDX, IDC_FID, butsup);//
	DDX_Control(pDX, IDC_PLUS, bplus);//
	DDX_Control(pDX, IDC_MOINS, bminus);//
	DDX_Control(pDX, IDC_GARB, bpoub);//
	DDX_Control(pDX, IDC_RAZ, butraz);//
	DDX_Control(pDX, IDC_PAGE, wpage);//
	DDX_Control(pDX, IDC_LIBEL1, slibel1);//
	DDX_Control(pDX, IDC_LIBEL2, slibel2);//
	DDX_Control(pDX, IDC_NCONSO, nlibelcons);//
	DDX_Control(pDX, IDC_LIBELCONS, slibelcons);//
	DDX_Control(pDX, IDC_NLIBEL, nlibel);//
	DDX_Control(pDX, IDC_NPAGE, npage);//
	DDX_Control(pDX, IDC_NDATE, ndate);//
	DDX_Control(pDX, IDC_NPRIX, nprix);//
	DDX_Control(pDX, IDC_TOTAL, total);//
	DDX_Control(pDX, IDC_NTOTAL, ntotal);
	DDX_Control(pDX, IDC_0, b0);
	DDX_Control(pDX, IDC_CODE, lcode);
	DDX_Control(pDX, IDC_QTE, lqte);
	DDX_Control(pDX, IDC_PTOT, lptot);
	DDX_Control(pDX, IDC_LNTICK, lntick);
	DDX_Control(pDX, IDC_LDATE, ldate);
	DDX_Control(pDX, IDC_LPRIX, lprix);
	DDX_Control(pDX, IDC_LCANCEL, lcancel);
	DDX_Control(pDX, IDC_BILCANCEL, bcancel);
	DDX_Control(pDX, IDC_DEL, bdel);
	DDX_Control(pDX, IDC_BILPRINT, butprint);
	DDX_Control(pDX, IDC_CASH_VIEW, bcashview);
	DDX_Control(pDX, IDC_CASH_CLOSE, bcashclose);
	DDX_Control(pDX, IDC_RESULT, bresult);
	DDX_Control(pDX, IDC_ARTICLE, bart);
	DDX_Control(pDX, IDC_CONFIG, bconfig);
	DDX_Control(pDX, IDC_ENT1, ent1);
	DDX_Control(pDX, IDC_ENT2, ent2);
	DDX_Control(pDX, IDC_ENT3, ent3);
	DDX_Control(pDX, IDC_ENT4, ent4);
	DDX_Control(pDX, IDC_CA, sca);
	DDX_Control(pDX, IDC_DA, sda);
	DDX_Control(pDX, IDC_NTT, sntt);
	DDX_Control(pDX, IDC_NTA, snta);
	DDX_Control(pDX, IDC_SEARCH, esea);
	DDX_Control(pDX, IDC_NPOSTE, nposte);
	DDX_Control(pDX, IDC_NSERVEUR, nserveur);
	DDX_Control(pDX, IDC_NPREFIX, nprefix);
	DDX_Control(pDX, IDC_NNOM, nnom);
	DDX_Control(pDX, IDC_NAD1, nad1);
	DDX_Control(pDX, IDC_NAD2, nad2);
	DDX_Control(pDX, IDC_NDEVISE, ndevise);
	DDX_Control(pDX, IDC_SPOSTE, sposte);
	DDX_Control(pDX, IDC_SSERVEUR, sserveur);
	DDX_Control(pDX, IDC_SPREFIX, sprefix);
	DDX_Control(pDX, IDC_SNOM, snom);
	DDX_Control(pDX, IDC_SAD1, sad1);
	DDX_Control(pDX, IDC_SAD2, sad2);
	DDX_Control(pDX, IDC_NSIRET, nsir);
	DDX_Control(pDX, IDC_SSIRET, ssir);
	DDX_Control(pDX, IDC_NNAF, nnaf);
	DDX_Control(pDX, IDC_SNAF, snaf);
	DDX_Control(pDX, IDC_GSECUR, sgs);
	DDX_Control(pDX, IDC_GLOG, sgl);
	DDX_Control(pDX, IDC_GCLIENT, sgc);
	DDX_Control(pDX, IDC_GEDIT, sge);
	DDX_Control(pDX, IDC_NNAUTO, nnauto);
	DDX_Control(pDX, IDC_NPAUTO, npauto);
	DDX_Control(pDX, IDC_NAN, nan);
	DDX_Control(pDX, IDC_SAN, san);
	DDX_Control(pDX, IDC_NMOIS, nmois);
	DDX_Control(pDX, IDC_SMOIS, smois);
	DDX_Control(pDX, IDC_BUREAU, bbur);
	DDX_Control(pDX, IDC_NET, bnet);
	DDX_Control(pDX, IDC_PRINTER, bprinter);
	DDX_Control(pDX, IDC_SCONS, scons);
	DDX_Control(pDX, IDC_NCONS, ncons);
	DDX_Control(pDX, IDC_VERSION, version);
	DDX_Control(pDX, IDC_IMPORT, bimport);
	DDX_Control(pDX, IDC_NTVA1, ntva1);
	DDX_Control(pDX, IDC_NTVA2, ntva2);
	DDX_Control(pDX, IDC_TVA1, stva1);
	DDX_Control(pDX, IDC_TVA2, stva2);
	DDX_Control(pDX, IDC_VAL1, sval1);
	DDX_Control(pDX, IDC_VAL2, sval2);
	DDX_Control(pDX, IDC_PRIX, sprix);
	DDX_Control(pDX, IDC_LIBELSPECT, spect);
	DDX_Control(pDX, IDC_LIBELGUICHET, guichet);
	DDX_Control(pDX, IDC_NSPECT, nspect);
	DDX_Control(pDX, IDC_NETC, netc);
	DDX_Control(pDX, IDC_CONTROL, bcontrol);
	DDX_Control(pDX, IDC_SELSPECT, lselevt);
	DDX_Control(pDX, IDC_NVHORAIRE, nvhor);
	DDX_Control(pDX, IDC_NVALCONTROL, nvcontrol);
	DDX_Control(pDX, IDC_ENTRYMODE, bentrymode);
	DDX_Control(pDX, IDC_TEMNET, tnet);
	DDX_Control(pDX, IDC_TEMWEB, tweb);
	DDX_Control(pDX, IDC_TEMCONTROL, tcontrol);
	DDX_Control(pDX, IDC_TEMGATE, tgate);
	DDX_Control(pDX, IDC_DIRLIST, dirlist);
	DDX_Control(pDX, IDC_LOGO, blogo);
	DDX_Control(pDX, IDC_BMANAGER, bman);
	DDX_Control(pDX, IDC_BUSER, buser);
	DDX_Control(pDX, IDC_NSCAN, nscan);
	DDX_Control(pDX, IDC_NDEVISE, ndevise);
	DDX_Control(pDX, IDC_SDEVISE, sdevise);
	DDX_Control(pDX, IDC_LDEVISE, ldevise);
	DDX_Control(pDX, IDC_NLANGUE, nlangue);
	DDX_Control(pDX, IDC_SLANGUE, slangue);
	DDX_Control(pDX, IDC_LLANGUE, llangue);
	DDX_Control(pDX, IDC_NPAYS, npays);
	DDX_Control(pDX, IDC_SPAYS, spays);
	DDX_Control(pDX, IDC_LPAYS, lpays);
	DDX_Control(pDX, IDC_LCB, lcb);
	DDX_Control(pDX, IDC_LTYPE, ltype);
	DDX_Control(pDX, IDC_NLICENSE, nlic);
	DDX_Control(pDX, IDC_SLICENSE0, slic0);
	DDX_Control(pDX, IDC_SLICENSE1, slic1);
	DDX_Control(pDX, IDC_SLICENSE2, slic2);
	DDX_Control(pDX, IDC_SLICENSE3, slic3);
	DDX_Control(pDX, IDC_SLICENSE4, slic4);
	DDX_Control(pDX, IDC_SLICENSE5, slic5);
	DDX_Control(pDX, IDC_SLICENSE6, slic6);
	DDX_Control(pDX, IDC_SMENTIONT, smentiont);
	DDX_Control(pDX, IDC_SMENTIONP, smentionp);
	DDX_Control(pDX, IDC_NMENTIONT, nmentiont);
	DDX_Control(pDX, IDC_NMENTIONP, nmentionp);
	DDX_Control(pDX, IDC_LMAC, lmac);
	DDX_Control(pDX, IDC_NVALPLACE, nvplace);
	DDX_Control(pDX, IDC_NVALMIX, nvmix);
	DDX_Control(pDX, IDC_VALPLACE, vplace);
	DDX_Control(pDX, IDC_VALMIX, vmix);
	DDX_Control(pDX, IDC_VALENTRY, ventry);
	DDX_Control(pDX, IDC_VALEXO, vexo);
	DDX_Control(pDX, IDC_VALCBX, vcbx);
	DDX_Control(pDX, IDC_VALPASS, vpass);
	DDX_Control(pDX, IDC_VALACTIF, vactif);
	DDX_Control(pDX, IDC_LNEWART, lna);
	DDX_Control(pDX, IDC_LTMP, ltmp);
	DDX_Control(pDX, IDC_PIMP, pimp);
	DDX_Control(pDX, IDC_NVALPWD, nvpwd);
	DDX_Control(pDX, IDC_NVALPAGE, nvpage);
	DDX_Control(pDX, IDC_LNBAP, lnbap);
	DDX_Control(pDX, IDC_PRICELIST,pl);
	DDX_Control(pDX, IDC_NEXER, nexer);
	DDX_Control(pDX, IDC_SEXER,sexer);
	DDX_Control(pDX, IDC_LMOIS,lmois);
	DDX_Control(pDX, IDC_SOURCELIST,sl);
	DDX_Control(pDX, IDC_TARGETLIST,tl);
	DDX_Control(pDX, IDC_SOURCEDIRLIST,dl);
	DDX_Control(pDX, IDC_SOURCEDATA,rl);
	DDX_Control(pDX, IDC_SDL,sdl);
	DDX_Control(pDX, IDC_SDUM,sdum);
	DDX_Control(pDX, IDC_AVERT1,av1);
	DDX_Control(pDX, IDC_AVERT2,av2);
	DDX_Control(pDX, IDC_AVERT3,av3);
	DDX_Control(pDX, IDC_QR, wqr);
	DDX_Control(pDX, IDC_QRPHONE, phqr);
	DDX_Control(pDX, IDC_TQR, wtqr);
	DDX_Control(pDX, IDC_LTCONTROL, ltctl);
	DDX_Control(pDX, IDC_COPY, bcopy);
	DDX_Control(pDX, IDC_PASTE, bpaste);
}

// gestionnaires de messages pour CConcertoDlg
BEGIN_MESSAGE_MAP(CConcertoDlg, CDialog)
	//}}AFX_MSG_MAP
ON_WM_PAINT()
ON_WM_QUERYDRAGICON()
ON_WM_DESTROY()
ON_WM_LBUTTONDOWN()
ON_WM_LBUTTONUP()
ON_WM_MOUSEMOVE()
ON_WM_RBUTTONDOWN()
ON_WM_ERASEBKGND()
ON_WM_DRAWITEM()
ON_WM_TIMER()
ON_WM_CTLCOLOR()
ON_WM_VSCROLL()
ON_WM_SETCURSOR()
ON_BN_DOUBLECLICKED(IDC_FAM1, &CConcertoDlg::OnBnDClickedFam1)
ON_BN_DOUBLECLICKED(IDC_FAM2, &CConcertoDlg::OnBnDClickedFam2)
ON_BN_DOUBLECLICKED(IDC_FAM3, &CConcertoDlg::OnBnDClickedFam3)
ON_BN_CLICKED(IDC_FAM1, &CConcertoDlg::OnBnClickedFam1)
ON_BN_CLICKED(IDC_FAM2, &CConcertoDlg::OnBnClickedFam2)
ON_BN_CLICKED(IDC_FAM3, &CConcertoDlg::OnBnClickedFam3)
ON_BN_CLICKED(IDC_RUB1, &CConcertoDlg::OnBnClickedRub1)
ON_BN_CLICKED(IDC_RUB2, &CConcertoDlg::OnBnClickedRub2)
ON_BN_CLICKED(IDC_RUB3, &CConcertoDlg::OnBnClickedRub3)
ON_BN_CLICKED(IDC_ART1, &CConcertoDlg::OnBnClickedArt1)
ON_BN_CLICKED(IDC_ART2, &CConcertoDlg::OnBnClickedArt2)
ON_BN_CLICKED(IDC_ART3, &CConcertoDlg::OnBnClickedArt3)
ON_BN_CLICKED(IDC_ART4, &CConcertoDlg::OnBnClickedArt4)
ON_BN_CLICKED(IDC_ART5, &CConcertoDlg::OnBnClickedArt5)
ON_BN_CLICKED(IDC_ART6, &CConcertoDlg::OnBnClickedArt6)
ON_BN_CLICKED(IDC_ART7, &CConcertoDlg::OnBnClickedArt7)
ON_BN_CLICKED(IDC_ART8, &CConcertoDlg::OnBnClickedArt8)
ON_BN_CLICKED(IDC_ART9, &CConcertoDlg::OnBnClickedArt9)
ON_BN_CLICKED(IDC_ART10, &CConcertoDlg::OnBnClickedArt10)
ON_BN_CLICKED(IDC_ART11, &CConcertoDlg::OnBnClickedArt11)
ON_BN_CLICKED(IDC_ART12, &CConcertoDlg::OnBnClickedArt12)
ON_BN_CLICKED(IDC_ART13, &CConcertoDlg::OnBnClickedArt13)
ON_BN_CLICKED(IDC_ART14, &CConcertoDlg::OnBnClickedArt14)
ON_BN_CLICKED(IDC_ART15, &CConcertoDlg::OnBnClickedArt15)
ON_BN_CLICKED(IDC_ART16, &CConcertoDlg::OnBnClickedArt16)
ON_BN_CLICKED(IDC_PLUS, &CConcertoDlg::OnBnClickedPlus)
ON_BN_CLICKED(IDC_MOINS, &CConcertoDlg::OnBnClickedMoins)
ON_BN_CLICKED(IDC_GARB, &CConcertoDlg::OnBnClickedPoubelle)
ON_BN_CLICKED(IDC_MANAGER, &CConcertoDlg::OnBnClickedManager)
ON_BN_CLICKED(IDC_QUITTER, &CConcertoDlg::OnBnClickedQuitter)
ON_BN_CLICKED(IDC_RETURN, &CConcertoDlg::OnBnClickedRetour)
ON_BN_CLICKED(IDC_FIG, &CConcertoDlg::OnBnClickedInf)
ON_BN_CLICKED(IDC_FID, &CConcertoDlg::OnBnClickedSup)
ON_BN_CLICKED(IDC_PASTE, &CConcertoDlg::OnBnClickedPaste)
ON_BN_CLICKED(IDC_COPY, &CConcertoDlg::OnBnClickedCopy)
ON_BN_CLICKED(IDC_0, &CConcertoDlg::OnBnClicked0)
ON_BN_CLICKED(IDC_1, &CConcertoDlg::OnBnClicked1)
ON_BN_CLICKED(IDC_2, &CConcertoDlg::OnBnClicked2)
ON_BN_CLICKED(IDC_3, &CConcertoDlg::OnBnClicked3)
ON_BN_CLICKED(IDC_4, &CConcertoDlg::OnBnClicked4)
ON_BN_CLICKED(IDC_5, &CConcertoDlg::OnBnClicked5)
ON_BN_CLICKED(IDC_6, &CConcertoDlg::OnBnClicked6)
ON_BN_CLICKED(IDC_7, &CConcertoDlg::OnBnClicked7)
ON_BN_CLICKED(IDC_8, &CConcertoDlg::OnBnClicked8)
ON_BN_CLICKED(IDC_9, &CConcertoDlg::OnBnClicked9)
ON_BN_DOUBLECLICKED(IDC_ART1, &CConcertoDlg::OnBnDClickedArt1)
ON_BN_DOUBLECLICKED(IDC_ART2, &CConcertoDlg::OnBnDClickedArt2)
ON_BN_DOUBLECLICKED(IDC_ART3, &CConcertoDlg::OnBnDClickedArt3)
ON_BN_DOUBLECLICKED(IDC_ART4, &CConcertoDlg::OnBnDClickedArt4)
ON_BN_DOUBLECLICKED(IDC_ART5, &CConcertoDlg::OnBnDClickedArt5)
ON_BN_DOUBLECLICKED(IDC_ART6, &CConcertoDlg::OnBnDClickedArt6)
ON_BN_DOUBLECLICKED(IDC_ART7, &CConcertoDlg::OnBnDClickedArt7)
ON_BN_DOUBLECLICKED(IDC_ART8, &CConcertoDlg::OnBnDClickedArt8)
ON_BN_DOUBLECLICKED(IDC_ART9, &CConcertoDlg::OnBnDClickedArt9)
ON_BN_DOUBLECLICKED(IDC_ART10, &CConcertoDlg::OnBnDClickedArt10)
ON_BN_DOUBLECLICKED(IDC_ART11, &CConcertoDlg::OnBnDClickedArt11)
ON_BN_DOUBLECLICKED(IDC_ART12, &CConcertoDlg::OnBnDClickedArt12)
ON_BN_DOUBLECLICKED(IDC_ART13, &CConcertoDlg::OnBnDClickedArt13)
ON_BN_DOUBLECLICKED(IDC_ART14, &CConcertoDlg::OnBnDClickedArt14)
ON_BN_DOUBLECLICKED(IDC_ART15, &CConcertoDlg::OnBnDClickedArt15)
ON_BN_DOUBLECLICKED(IDC_ART16, &CConcertoDlg::OnBnDClickedArt16)
ON_BN_CLICKED(IDC_10, &CConcertoDlg::OnBnClickedClear)
ON_BN_CLICKED(IDC_11, &CConcertoDlg::OnBnClickedEncaisser)
ON_BN_CLICKED(IDC_RAZ, &CConcertoDlg::OnBnClickedRaz)
ON_BN_DOUBLECLICKED(IDC_0, &CConcertoDlg::OnBnClicked0)
ON_BN_DOUBLECLICKED(IDC_1, &CConcertoDlg::OnBnClicked1)
ON_BN_DOUBLECLICKED(IDC_2, &CConcertoDlg::OnBnClicked2)
ON_BN_DOUBLECLICKED(IDC_3, &CConcertoDlg::OnBnClicked3)
ON_BN_DOUBLECLICKED(IDC_4, &CConcertoDlg::OnBnClicked4)
ON_BN_DOUBLECLICKED(IDC_5, &CConcertoDlg::OnBnClicked5)
ON_BN_DOUBLECLICKED(IDC_6, &CConcertoDlg::OnBnClicked6)
ON_BN_DOUBLECLICKED(IDC_7, &CConcertoDlg::OnBnClicked7)
ON_BN_DOUBLECLICKED(IDC_8, &CConcertoDlg::OnBnClicked8)
ON_BN_DOUBLECLICKED(IDC_9, &CConcertoDlg::OnBnClicked9)
ON_BN_DOUBLECLICKED(IDC_10, &CConcertoDlg::OnBnClickedClear)
ON_BN_DOUBLECLICKED(IDC_11, &CConcertoDlg::OnBnClickedEncaisser)
ON_BN_DOUBLECLICKED(IDC_RAZ, &CConcertoDlg::OnBnClickedRaz)
ON_BN_CLICKED(IDC_CASH_CLOSE, &CConcertoDlg::OnBnClickedCashClose)
ON_BN_CLICKED(IDC_CASH_VIEW, &CConcertoDlg::OnBnClickedCashView)
ON_BN_CLICKED(IDC_BILPRINT, &CConcertoDlg::OnBnClickedBilprint)
ON_BN_CLICKED(IDC_BILCANCEL, &CConcertoDlg::OnBnClickedBilcancel)
ON_BN_CLICKED(IDC_RESULT, &CConcertoDlg::OnBnClickedResult)
ON_BN_CLICKED(IDC_ARTICLE, &CConcertoDlg::OnBnClickedArticle)
ON_BN_CLICKED(IDC_CONFIG, &CConcertoDlg::OnBnClickedConfig)
ON_BN_CLICKED(IDC_ENTRYMODE, &CConcertoDlg::OnBnClickedEntryMode)
ON_BN_CLICKED(IDC_LOGO, &CConcertoDlg::OnBnClickedLogo)
ON_BN_CLICKED(IDC_BMANAGER, &CConcertoDlg::OnBnClickedBcode)
ON_BN_CLICKED(IDC_BUSER, &CConcertoDlg::OnBnClickedBuser)
ON_BN_CLICKED(IDC_NET, &CConcertoDlg::OnBnClickedBnet)
ON_BN_CLICKED(IDC_PRINTER, &CConcertoDlg::OnBnClickedBprinter)
ON_BN_CLICKED(IDC_DEL, &CConcertoDlg::OnBnClickedDel)
ON_BN_CLICKED(IDC_CONTROL, &CConcertoDlg::OnBnClickedControl)
ON_BN_CLICKED(IDC_GLOG, &CConcertoDlg::OnBnClickedGlog)
ON_BN_CLICKED(IDC_BUREAU, &CConcertoDlg::OnBnClickedBureau)
ON_BN_CLICKED(IDC_IMPORT, &CConcertoDlg::OnBnClickedImport)

ON_STN_CLICKED(IDC_NDATE, &CConcertoDlg::OnStnClickedNdate)
ON_STN_CLICKED(IDC_SEARCH, &CConcertoDlg::OnStnClickedSearch)
ON_STN_CLICKED(IDC_SPOSTE, &CConcertoDlg::OnStnClickedSposte)
ON_STN_CLICKED(IDC_SAN, &CConcertoDlg::OnStnClickedSan)
ON_STN_CLICKED(IDC_SMOIS, &CConcertoDlg::OnStnClickedSmois)
ON_STN_CLICKED(IDC_PRIX, &CConcertoDlg::OnStnClickedPrix)
ON_STN_CLICKED(IDC_TVA1, &CConcertoDlg::OnStnClickedTva1)
ON_STN_CLICKED(IDC_TVA2, &CConcertoDlg::OnStnClickedTva2)
ON_STN_CLICKED(IDC_VAL1, &CConcertoDlg::OnStnClickedVal1)
ON_STN_CLICKED(IDC_VAL2, &CConcertoDlg::OnStnClickedVal2)
ON_STN_CLICKED(IDC_SCONS, &CConcertoDlg::OnStnClickedScons)
ON_STN_CLICKED(IDC_NPAUTO, &CConcertoDlg::OnStnClickedNpauto)
ON_STN_CLICKED(IDC_NNAUTO, &CConcertoDlg::OnStnClickedNnauto)
ON_STN_CLICKED(IDC_TEMNET, &CConcertoDlg::OnStnClickedTemradio)
ON_STN_CLICKED(IDC_TEMCONTROL, &CConcertoDlg::OnStnClickedTemcontrol)
ON_STN_DBLCLK(IDC_NAN, &CConcertoDlg::OnStnDblclickNan)
ON_STN_CLICKED(IDC_SDEVISE, &CConcertoDlg::OnStnClickedSdevise)
ON_STN_CLICKED(IDC_NVHORAIRE, &CConcertoDlg::OnStnClickedNvalhor)
ON_STN_CLICKED(IDC_VERSION, &CConcertoDlg::OnStnClickedVersion)
ON_STN_CLICKED(IDC_NVALPLACE, &CConcertoDlg::OnStnClickedNvalplace)
ON_STN_CLICKED(IDC_VALPLACE, &CConcertoDlg::OnStnClickedValplace)
ON_STN_CLICKED(IDC_VALMIX, &CConcertoDlg::OnStnClickedValmix)
ON_STN_CLICKED(IDC_VALACTIF, &CConcertoDlg::OnStnClickedValactif)
ON_STN_CLICKED(IDC_NVALMIX, &CConcertoDlg::OnStnClickedNvalmix)
ON_STN_CLICKED(IDC_VALENTRY, &CConcertoDlg::OnStnClickedVentry)
ON_STN_CLICKED(IDC_VALEXO, &CConcertoDlg::OnStnClickedVexo)
ON_STN_CLICKED(IDC_VALCBX, &CConcertoDlg::OnStnClickedVcbx)
ON_STN_CLICKED(IDC_VALPASS, &CConcertoDlg::OnStnClickedVpass)
ON_STN_CLICKED(IDC_PAGE, &CConcertoDlg::OnStnClickedPage)
ON_STN_CLICKED(IDC_NVALPWD, &CConcertoDlg::OnStnClickedNvalpwd)
ON_STN_CLICKED(IDC_NVALPAGE, &CConcertoDlg::OnStnClickedNvalpage)
ON_STN_CLICKED(IDC_NETC, &CConcertoDlg::OnStnClickedNetc)
ON_STN_CLICKED(IDC_TOTAL, &CConcertoDlg::OnStnClickedTotal)
ON_STN_CLICKED(IDC_SLANGUE, &CConcertoDlg::OnStnClickedSlangue)
ON_STN_CLICKED(IDC_SPAYS, &CConcertoDlg::OnStnClickedSpays)
ON_STN_CLICKED(IDC_SEXER, &CConcertoDlg::OnStnClickedSexer)

ON_EN_SETFOCUS(IDC_LIBEL1, &CConcertoDlg::OnEnSetfocusLibel1)
ON_EN_SETFOCUS(IDC_LIBEL2, &CConcertoDlg::OnEnSetfocusLibel2)
ON_EN_SETFOCUS(IDC_SNOM, &CConcertoDlg::OnEnSetfocusSnom)
ON_EN_SETFOCUS(IDC_SSERVEUR, &CConcertoDlg::OnEnSetfocusSserveur)
ON_EN_SETFOCUS(IDC_SPREFIX, &CConcertoDlg::OnEnSetfocusSprefix)
ON_EN_SETFOCUS(IDC_SAD1, &CConcertoDlg::OnEnSetfocusSad1)
ON_EN_SETFOCUS(IDC_SAD2, &CConcertoDlg::OnEnSetfocusSad2)
ON_EN_SETFOCUS(IDC_SSIRET, &CConcertoDlg::OnEnSetfocusSsiret)
ON_EN_SETFOCUS(IDC_SNAF, &CConcertoDlg::OnEnSetfocusSnaf)
ON_EN_SETFOCUS(IDC_NLIBEL1, &CConcertoDlg::OnEnSetfocusNlibel1)
ON_EN_SETFOCUS(IDC_LIBELSPECT, &CConcertoDlg::OnEnSetfocusLibelspect)
ON_EN_SETFOCUS(IDC_LIBELCONS, &CConcertoDlg::OnEnSetfocusLibelcons)
ON_EN_SETFOCUS(IDC_SLICENSE0, &CConcertoDlg::OnEnSetfocusSlicense0)
ON_EN_SETFOCUS(IDC_SLICENSE1, &CConcertoDlg::OnEnSetfocusSlicense1)
ON_EN_SETFOCUS(IDC_SLICENSE2, &CConcertoDlg::OnEnSetfocusSlicense2)
ON_EN_SETFOCUS(IDC_SLICENSE3, &CConcertoDlg::OnEnSetfocusSlicense3)
ON_EN_SETFOCUS(IDC_SLICENSE4, &CConcertoDlg::OnEnSetfocusSlicense4)
ON_EN_SETFOCUS(IDC_SLICENSE5, &CConcertoDlg::OnEnSetfocusSlicense5)
ON_EN_SETFOCUS(IDC_SLICENSE6, &CConcertoDlg::OnEnSetfocusSlicense6)
ON_EN_MAXTEXT(IDC_LIBEL1, &CConcertoDlg::OnEnMaxtextLibel1)
ON_EN_SETFOCUS(IDC_LIBELGUICHET, &CConcertoDlg::OnEnSetfocusLibelguichet)
ON_EN_SETFOCUS(IDC_SMENTIONT, &CConcertoDlg::OnEnSetfocusSmentiont)
ON_EN_SETFOCUS(IDC_SMENTIONP, &CConcertoDlg::OnEnSetfocusSmentionp)

ON_LBN_SELCHANGE(IDC_CODE, &CConcertoDlg::OnLbnSelchangeCode)
ON_LBN_SELCHANGE(IDC_QTE, &CConcertoDlg::OnLbnSelchangeQte)
ON_LBN_SELCHANGE(IDC_PTOT, &CConcertoDlg::OnLbnSelchangePtot)
ON_LBN_SELCHANGE(IDC_LPRIX, &CConcertoDlg::OnLbnSelchangeLprix)
ON_LBN_SELCHANGE(IDC_LCANCEL, &CConcertoDlg::OnLbnSelchangeLcancel)
ON_LBN_SELCHANGE(IDC_LDATE, &CConcertoDlg::OnLbnSelchangeLdate)
ON_LBN_KILLFOCUS(IDC_PTOT, &CConcertoDlg::OnLbnKillfocusPtot)
ON_LBN_SELCHANGE(IDC_LNTICK, &CConcertoDlg::OnLbnSelchangeLntick)
ON_LBN_SELCHANGE(IDC_SELSPECT, &CConcertoDlg::OnLbnSelchangeSelspect)
ON_CBN_SELCHANGE(IDC_LNBAP, &CConcertoDlg::OnCbnSelchangeLnbap)
ON_CBN_SELCHANGE(IDC_LCB, &CConcertoDlg::OnCbnSelchangeLcb)
ON_CBN_SELCHANGE(IDC_LTYPE, &CConcertoDlg::OnCbnSelchangeLtype)
ON_STN_DBLCLK(IDC_NDATE, &CConcertoDlg::OnStnDblclickNdate)
ON_WM_CLOSE()
ON_WM_ENDSESSION()
ON_WM_MOUSEACTIVATE()
END_MESSAGE_MAP()


DWORD CConcertoDlg::GetNbPrinterByte(HANDLE hPrinter,DWORD level)
{	// renvoi le nombre d'octets necessaire pour la fonction GetPrinter suivant son niveau
	DWORD cbNeeded;
	BYTE test;
	if(Printer!=NULL)
		delete []Printer;
	Printer=NULL;
	GetPrinter(hPrinter,level,&test,0,&cbNeeded);
	Printer=new BYTE[cbNeeded];
	return cbNeeded;
}

void CConcertoDlg::StartSimulPrinter(int np)
{
	noprint=np;
}
CString CConcertoDlg::GetConfigString(CString rubrique,CString item,CString defaut)
{// Retrouve le paramètre item dans sa rubrique
	CString temp="";
	int idx;
	int idy;
retry_rubrique:;
	if((idx=configtext.Find("\r\n["+rubrique+"]",0))!=-1)
	{
		if((idy=configtext.Find("\r\n"+item+"=",idx))!=-1)
		{
			idx=configtext.Find("=",idy)+1;
			idy=configtext.Find("\r\n",idx);
			temp=configtext.Mid(idx,idy-idx);
			return temp;
		}
		else
		{// S'il ne le trouve pas crée l'item avec sa valeur par défaut
			WriteConfigString(rubrique,item,defaut);
			goto retry_rubrique;
		}
	}
	else
	{// S'il ne le trouve pas crée la rubrique  puis l'item avec sa valeur par défaut
		WriteConfigString(rubrique,item,defaut);
		goto retry_rubrique;
	}
}
void CConcertoDlg::WriteConfigString(CString rubrique,CString item,CString data)
{
	CString temp="";
	int idx;
	int idy;
retry_rubrique:;
	if((idy=configtext.Find("\r\n["+rubrique+"]",0))!=-1)
	{
		idx=configtext.Find("\r\n",idy);
		if((idy=configtext.Find("\r\n"+item+"=",idx))!=-1)
		{
			idx=configtext.Find("=",idy)+1;
			idy=configtext.Find("\r\n",idx);
			configtext.Delete(idx,idy-idx);
			configtext.Insert(idx,data);
		}
		else
		{// S'il ne le trouve pas crée l'item avec sa valeur
			if((idx=configtext.Find("\r\n["+rubrique+"]",0))!=-1)
			{
				if((idy=configtext.Find("[",idx+4))!=-1)
					configtext.Insert(idy,item+"="+data+"\r\n");
				else
					configtext+=item+"="+data+"\r\n";
			}
		}
	}
	else
	{// S'il ne le trouve pas crée la rubrique
		configtext+="["+rubrique+"]\r\n";
		goto retry_rubrique;
	}
	CWrite(configpath,configtext,0);//Ecrit dans le fichier de config
	/*if(rubrique!="Infocert")// pour test
		MessageBox(rubrique+"->"+item+"="+configtext);*/
}
void CConcertoDlg::InitVariable()
{	//Charge tous les paramètres du fichier de config dans les variables

	CString temp;
	// Section Infocert	
	catidx=atoi(GetConfigString("Infocert","Catidx","1"));//N° d'index du fichier catalogue des données
	auditfile=atoi(GetConfigString("Infocert","Auditfile","0"));//N° d'index du fichier d'audit AuditinfoX.dat
	temp.Format("%u",auditfile);
	auditinfopath=workdir+"\\Auditinfo"+temp+".dat";// Répertoire du fichier AuditinfoX.dat
	naudit=atoi(GetConfigString("Infocert","Naudit","1"));//N° d'audit pour la prochaine écriture
	certnum="0004";
	WriteConfigString("Infocert","Certnum",certnum);//N° certificat infocert
	dexer=GetConfigString("Infocert","Exercice","");//Année d'exercice
	pays=GetConfigString("Infocert","Pays","FR");// Pays 
	exermois=GetConfigString("Infocert","MoisExercice","00");//Mois d'exercice
	sticket=GetConfigString("Infocert","SignTicket","");// Dernière signature du ticket
	sgtticket=GetConfigString("Infocert","SignGtticket","");// Dernière signature du grand total ticket
	sgtpz=GetConfigString("Infocert","SignGtpz","");// Dernière signature de la période
	sgtpa=GetConfigString("Infocert","SignGtpa","");// Dernière signature de l'exercice
	sarchp=GetConfigString("Infocert","SignArchPeriode","");// Dernière signature de l'archive
	sarche=GetConfigString("Infocert","SignArchExercice","");// Dernière signature de l'archive
	sarchd=GetConfigString("Infocert","SignArchExport","");// Dernière signature de l'archive
	saudit=GetConfigString("Infocert","SignAudit","");// Dernière signature du fichier d'audit
	// Section Code d'accès
	codeadmin=GetConfigString("Code","Administrateur","79314862");//Code administrateur Barmatic
	if(codeadmin=="200061")
	{
		codeadmin="79314862";
		WriteConfigString("Code","Administrateur",codeadmin);//Code administrateur Barmatic
	}
	coderazadmin=GetConfigString("Code","RazAdministrateur","79314268");//Code administrateur RAZ Barmatic
	if(coderazadmin=="160002")
	{
		coderazadmin="79314268";
		WriteConfigString("Code","RazAdministrateur",coderazadmin);//Code administrateur Barmatic
	}
	codereseller=GetConfigString("Code","Revendeur","");// Code revendeur attribué lors de la vente
	if(codereseller=="")
	{
		codereseller="7931486";
		WriteConfigString("Code","Revendeur",codereseller);//Code revendeur Barmatic
	}
	codemanager=GetConfigString("Code","ManagerCode","0123");// Code Manager
	codeuser=GetConfigString("Code","UserCode","1234");// Code utilisateur
	codeaudit=GetConfigString("Code","AuditCode","19283746");// Code auditeur
	// Section paramètres client
	afmode=atoi(GetConfigString("Param","AfMode","0"));//mode billetterie/Borne
	prefix=GetConfigString("Client","Prefix","");// Réseau billetterie
	if(prefix==""&&afmode==0)
	{
		prefix="CONCERT";
		WriteConfigString("Client","Prefix","CONCERT");
	}
	else
		if(prefix==""&& afmode==1)
		{
			prefix="BORNE";
			WriteConfigString("Client","Prefix","BORNE");
		}

	nom=GetConfigString("Client","Nom","");// Nom de la Société
	prefix=GetConfigString("Client","Prefix","CONCERT");// Nom du préfixe ordinateur
	serveur=GetConfigString("Client","Serveur","www.demo-dineoquick.com");// Nom du derveur WEB de paiement
	adresse1=GetConfigString("Client","Adresse1","");// Adresse 1 de la société
	adresse2=GetConfigString("Client","Adresse2","");// Adresse 2 de la société
	siret=GetConfigString("Client","Siret","");// N° de siret de la société
	naf=GetConfigString("Client","Naf","");// N° de siret de la société
	langue=GetConfigString("Client","Langue","French");//Langue du logiciel
	langfile=workdir+"\\"+langue+".lng";
	cur=GetConfigString("Client","Devise","€");// Monnaie utilisée dans le logiciel
	for(int i=0;i<6;i++)
	{// Chargement des licence spectacle
		temp.Format("%u",i);
		lic[i]=GetConfigString("Client","License "+temp,"");
	}
	poste=GetConfigString("Client","Poste","01");// N° de poste
	mentiont=GetConfigString("Client","MentionT","");// Mention ticket Entrée
	mentionp=GetConfigString("Client","MentionP","");// Mention ticket Prévente
	NART=atoi(GetConfigString("Client","NART","96"));// Nombre d'article max
	NAPP=atoi(GetConfigString("Client","NAPP","16"));// Nombre d'article par page
	nvalplace=atoi(GetConfigString("Client","ValPlace","0"));// Validation de place
	nvalmix=atoi(GetConfigString("Client","ValMix","0"));// Validation des packs à 2 TVA
	valscr=atoi(GetConfigString("Client","ValScr","0"));// Validation de l'écran d'accueil  en veille animé
	valpage=atoi(GetConfigString("Client","ValPage","0"));// Validation de personnalisation des pages avec sélectionauto du jour
	valpwd=atoi(GetConfigString("Client","ValPwd","0"));// Validation du code au démarrage de la machine
	TVA=GetConfigString("Client","TVA","");//TVA globale sur TVA1 ou non
	horaire=atoi(GetConfigString("Client","Horaire","1"));	// Case à cocher présente dans la config
	valhor=atoi(GetConfigString("Client","ValHor","0"));	// Etat de la Validation de l'horaire en prévente
	nvalplace=atoi(GetConfigString("Client","ValPlace","0"));// Validation du N° de place
	cvalpass=atoi(GetConfigString("Client","ValPass","0"));// Validation du pass dans les articles
	autonews=atoi(GetConfigString("Client","Autonews","1"));
	fgate=atoi(GetConfigString("Client","Tourniquet","0"));
	if(afmode==0)
		autoprint=atoi(GetConfigString("Client","Autoprint","1"));
	else
	{
		autoprint=0;
			temp.Format("%u",autoprint);
		WriteConfigString("Client","Autoprint",temp);
	}
	eflag=atoi(GetConfigString("Client","Eflag","0"));
	exoflag=atoi(GetConfigString("Client","Exoflag","1"));
	nbillet=atoi(GetConfigString("Client","Billet","1"));
	fpage=atoi(GetConfigString("Client","FirstPage","0"));
	// Section paramètres machine
	RAZ=atoi(GetConfigString("Param","NGTZ","0"));// N° de GTZ en cours
	temp=GetConfigString("Param","GTT","");// NEW Grand total perpétuel
	if(temp=="")// S'il n'existe pas on prend le GTP dans le registre et on le transfert dans GTT
	{
		GTP=(double)(atoi(GetConfigString("Param","GTP","0")))/100;//Ancien Grand total perpétuel
		temp.Format("%.2f",GTP);
		WriteConfigString("Param","GTT",temp);
		WriteConfigString("Param","GTP","0");
	}
	else
		GTP=atof(temp);
	GTZ=(double)(atoi(GetConfigString("Param","GTZ","0"))/100);// Grantotal période en cours
	GTA=(double)(atoi(GetConfigString("Param","GTA","0"))/100);// Grantotal période précédente mensuelle
	GTE=(double)(atoi(GetConfigString("Param","GTE","0"))/100);// Grantotal période précédente annuelle
	edate=GetConfigString("Client","eDate","");	// Date utilisée dans les code barres ETC
	MAJ=atoi(GetConfigString("Param","MAJ","0"));// Flag indiquant qu'une mise à jour vient d'être faite
	simul=atoi(GetConfigString("Param","Simul","0"));// Mode simulation d'impression sur ticket écran
	fdev=atoi(GetConfigString("Param","Dev","0"));// Mode développement permettant de sortir sans arrêter Windows
	master=atoi(GetConfigString("Client","Master","0"));// Mode maître si 1
	alone=atoi(GetConfigString("Client","Alone","0"));// Si 1 mode maître autonome
	fprev=atoi(GetConfigString("Client","Prevente","0"));// Prévente autorisée si 1
	start=atoi(GetConfigString("Param","Start","0"));// Nombre de fois ou la machine a été démarrée
	paravent=atoi(GetConfigString("Client","Paravent","0"));// Fonctionnement mode paravent si 1
	dopen=GetConfigString("Param","Ouverture","");// Date de la dernière ouverture de période non cloturée AAAAmmJJHHMMSS
	logopath=GetConfigString("Param","LogoPath","");// Nom du fichier jpeg du logo sélectionné (protégé contre l'effacement en cas de RAZ)
	if(logopath.Find(workdir,0)!=-1)
		logopath.Replace(workdir,"");
	WriteConfigString("Param","LogoPath",logopath);// Nom du fichier jpeg du logo sélectionné (protégé contre l'effacement en cas de RAZ)
	scrpath=GetConfigString("Param","ScrPath","");
	serial=GetConfigString("License","Serial","");// N° de série de la machine
}

BOOL CConcertoDlg::OnInitDialog()
{
	SetWindowText("Concert");
	//*************************************** START VERSION ***********************************************
	fversion=5001;
	//*************************************** END VERSION *************************************************
	CString num;
	CString drivername;
	CString txt;
	CString temp;
	CString temp1;
	CString temp2;
	CString temp3;
	CString	pi1;
	CString	sourcedir;
	HANDLE hf;
	CFileStatus cfs;
	int i;
	int j;
	int wdg;
	CFileFind cff;
	CString servername;
	CRect rect;
	HANDLE    hPrinter;// handle to printer object
	DWORD size;//0x4000
	DWORD cbNeeded;
	DWORD nbyte=1000;
	CStringW wstr;
	CTime tim=CTime::GetCurrentTime();

	// initialisation répertoires de travail
	sysdir.ReleaseBuffer(GetSystemDirectory(sysdir.GetBuffer(MAX_PATH), MAX_PATH));
	GetModuleFileName(NULL,sourcedir.GetBuffer(256),256);
	sourcedir.ReleaseBuffer(-1);
	workdir=sourcedir.Left(sourcedir.ReverseFind('\\'));
	appdirname=workdir.Mid(workdir.ReverseFind('\\')+1);
	skindir=workdir+"\\Skin\\";
	controldir=workdir+"\\Control";
	datadir=workdir+"\\Data";
	netcontdir="";
	CreateDirectory(controldir,NULL);
	CreateDirectory(datadir,NULL);
	CreateDirectory(controldir+"\\Event",NULL);
	CreateDirectory(skindir+"Rubrique",NULL);
	CreateDirectory(skindir+"Famille",NULL);
	CreateDirectory(skindir+"Article",NULL);
	securedir="D:\\Secure";
	backupdir="X:";
	archdir=workdir+"\\Archive";
	CreateDirectory(archdir,NULL);
	CreateDirectory(securedir,NULL);
	CreateDirectory(securedir+"\\Data",NULL);
	CreateDirectory(backupdir+"\\Data",NULL);
	CreateDirectory(securedir+"\\Archive",NULL);
	CreateDirectory(backupdir+"\\Archive",NULL);
	CreateDirectory(securedir+"\\Control",NULL);
	CreateDirectory(backupdir+"\\Control",NULL);
	configpath=sysdir+"\\csys.avs";
	configtext=CRead(configpath);
	codeuser=AfxGetApp()->GetProfileString("Client","UserCode","none");
	codemanager=AfxGetApp()->GetProfileString("Client","Code","none");
	// Section Parmètres Client
	langue=AfxGetApp()->GetProfileString("Client","Langue","none");
	lic[0]=AfxGetApp()->GetProfileString("Client","License 0","none");
	lic[1]=AfxGetApp()->GetProfileString("Client","License 1","none");
	lic[2]=AfxGetApp()->GetProfileString("Client","License 2","none");
	lic[3]=AfxGetApp()->GetProfileString("Client","License 3","none");
	lic[4]=AfxGetApp()->GetProfileString("Client","License 4","none");
	lic[5]=AfxGetApp()->GetProfileString("Client","License 5","none");	
	cur=AfxGetApp()->GetProfileString("Client","Devise","none");
	langue=AfxGetApp()->GetProfileString("Client","Langue","none");
	edate=AfxGetApp()->GetProfileString("Client","eDate","none");
	mentiont=AfxGetApp()->GetProfileString("Client","MentionT","none");
	mentionp=AfxGetApp()->GetProfileString("Client","MentionP","none");
	nom=AfxGetApp()->GetProfileString("Client","Nom","none");
	adresse1=AfxGetApp()->GetProfileString("Client","Adresse1","none");
	adresse2=AfxGetApp()->GetProfileString("Client","Adresse2","none");
	siret=AfxGetApp()->GetProfileString("Client","Siret","none");
	poste=AfxGetApp()->GetProfileString("Client","Poste","none");
	NART=AfxGetApp()->GetProfileInt("Client","NART",0);
	NAPP=AfxGetApp()->GetProfileInt("Client","NAPP",0);
	nvalplace=AfxGetApp()->GetProfileInt("Param","ValPlace",-1);
	eflag=AfxGetApp()->GetProfileInt("Client","Eflag",-1);
	nvalmix=AfxGetApp()->GetProfileInt("Client","ValMix",-1);
	valpage=AfxGetApp()->GetProfileInt("Client","ValPage",-1);
	valpwd=AfxGetApp()->GetProfileInt("Client","ValPwd",-1);
	fprev=AfxGetApp()->GetProfileInt("Param","Prevente",-1);
	valhor=AfxGetApp()->GetProfileInt("Param","ValHor",-1);
	horaire=AfxGetApp()->GetProfileInt("Param","Horaire",-1);
	TVA=AfxGetApp()->GetProfileString("Client","TVA","none");
	autonews=AfxGetApp()->GetProfileInt("Param","Autonews",-1);
	autoprint=AfxGetApp()->GetProfileInt("Param","Autoprint",-1);
	serial=	AfxGetApp()->GetProfileString("Param","Serial","none");
	paravent=AfxGetApp()->GetProfileInt("Param","Paravent",-1);
	master=AfxGetApp()->GetProfileInt("Param","Master",-1);
	alone=AfxGetApp()->GetProfileInt("Param","Alone",-1);
	MAJ=AfxGetApp()->GetProfileInt("Param","MAJ",-1);
	// Section paramètre de fonctionnement
	RAZ=AfxGetApp()->GetProfileInt("Client","RAZ",-1);
	i=AfxGetApp()->GetProfileInt("Client","GTZ",(int)-1);
	GTX=(double)(i)/100;
	dopen=AfxGetApp()->GetProfileString("Param","Ouverture","none");
	start=AfxGetApp()->GetProfileInt("Param","Start",-1);
	fdev=AfxGetApp()->GetProfileInt("Param","Dev",-1);
	simul=AfxGetApp()->GetProfileInt("Param","Simul",-1);
	faudit=0;
	FTEM=1;
	fraz=0;
	HKEY hk;
	if(RegOpenKeyEx(HKEY_CURRENT_USER,"Software\\BARMATIC France\\Concert\\Client",0,KEY_ALL_ACCESS,&hk)== ERROR_SUCCESS)
	{// Test données venant d'une version
		if(codemanager!="none")
		{
			RegDeleteValue(hk,"Code");
			WriteConfigString("Code","ManagerCode",codemanager);
		}
		if(codeuser!="none")
		{
			RegDeleteValue(hk,"UserCode");
			WriteConfigString("Code","UserCode",codeuser);
		}
		if(nom!="none")
		{
			RegDeleteValue(hk,"Nom");
			WriteConfigString("Client","Nom",nom);
		}
		if(adresse1!="none")
		{
			RegDeleteValue(hk,"Adresse1");
			WriteConfigString("Client","Adresse1",adresse1);
		}
		if(adresse2!="none")
		{
			RegDeleteValue(hk,"Adresse2");
			WriteConfigString("Client","Adresse2",adresse2);
		}
		if(siret!="none")
		{
			RegDeleteValue(hk,"Siret");
			WriteConfigString("Client","Siret",siret);
		}
		if(poste!="none")
		{
			RegDeleteValue(hk,"Poste");
			WriteConfigString("Client","Poste",poste);
		}
		if(langue!="none")
		{
			RegDeleteValue(hk,"Langue");
			WriteConfigString("Client","Langue",langue);
		}
		if(cur!="none")
		{
			RegDeleteValue(hk,"Devise");
			WriteConfigString("Client","Devise",cur);
		}
		for(i=0;i<6;i++)
		{
			temp.Format("%u",i);
			if(lic[i]!="none"||lic[i]=="")
			{
				RegDeleteValue(hk,"License "+temp);
				WriteConfigString("Client","License "+temp,lic[i]);
			}
		}
		if(edate!="none")
		{
			RegDeleteValue(hk,"eDate");
			WriteConfigString("Client","eDate",edate);
		}
		if(mentiont!="none")
		{
			RegDeleteValue(hk,"MentionT");
			WriteConfigString("Client","MentionT",mentiont);
		}
		if(mentionp!="none")
		{
			RegDeleteValue(hk,"MentionP");
			WriteConfigString("Client","MentionP",mentionp);
		}
		if(NART!=0)
		{
			RegDeleteValue(hk,"NART");
			temp.Format("%u",NART);
			WriteConfigString("Client","NART",temp);
		}
		if(NAPP!=0)
		{
			RegDeleteValue(hk,"NAPP");
			temp.Format("%u",NAPP);
			WriteConfigString("Client","NAPP",temp);
		}
		if(nvalplace!=-1)
		{
			RegDeleteValue(hk,"ValPlace");
			temp.Format("%u",nvalplace);
			WriteConfigString("Client","ValPlace",temp);
		}
		if(eflag!=-1)
		{
			RegDeleteValue(hk,"Eflag");
			temp.Format("%u",eflag);
			WriteConfigString("Client","Eflag",temp);
		}
		if(nvalmix!=-1)
		{
			RegDeleteValue(hk,"ValMix");
			temp.Format("%u",nvalmix);
			WriteConfigString("Client","ValMix",temp);
		}
		if(valpage!=-1)
		{
			RegDeleteValue(hk,"ValPage");
			temp.Format("%u",valpage);
			WriteConfigString("Client","ValPage",temp);
		}
		if(valpwd!=-1)
		{
			RegDeleteValue(hk,"ValPwd");
			temp.Format("%u",valpwd);
			WriteConfigString("Client","ValPwd",temp);
		}
		if(TVA!="none")
		{
			RegDeleteValue(hk,"TVA");
			WriteConfigString("Client","TVA",TVA);
		}
		if(RAZ!=-1)
		{
			RegDeleteValue(hk,"RAZ");
			temp.Format("%u",RAZ);
			WriteConfigString("Param","NGTZ",temp);
		}
		if(GTX>=0)
		{
			GTP=GTX;
			RegDeleteValue(hk,"GTZ");
			temp.Format("%.2f",GTP);
			WriteConfigString("Param","GTT",temp);
			WriteConfigString("Param","GTP","0");
			WriteConfigString("Param","GTZ","0");
			WriteConfigString("Param","GTA","0");
		}
		RegCloseKey(hk);
	}
	if(RegOpenKeyEx(HKEY_CURRENT_USER,"Software\\BARMATIC France\\Concert\\Param",0,KEY_ALL_ACCESS,&hk)== ERROR_SUCCESS)
	{
		if(MAJ!=-1)
		{
			RegDeleteValue(hk,"MAJ");
			temp.Format("%u",MAJ);
			WriteConfigString("Param","MAJ",temp);
		}
		if(simul!=-1)
		{
			RegDeleteValue(hk,"Simul");
			temp.Format("%u",simul);
			WriteConfigString("Param","Simul",temp);
		}
		if(fdev!=-1)
		{
			RegDeleteValue(hk,"Dev");
			temp.Format("%u",fdev);
			WriteConfigString("Param","Dev",temp);
		}
		if(alone!=-1)
		{
			RegDeleteValue(hk,"Alone");
			temp.Format("%u",alone);
			WriteConfigString("Client","Alone",temp);
		}
		if(start!=-1)
		{
			RegDeleteValue(hk,"Start");
			temp.Format("%u",start);
			WriteConfigString("Param","Start",temp);
		}
		if(master!=-1)
		{
			RegDeleteValue(hk,"Master");
			temp.Format("%u",master);
			WriteConfigString("Client","Master",temp);
		}
		if(paravent!=-1)
		{
			RegDeleteValue(hk,"Paravent");
			temp.Format("%u",paravent);
			WriteConfigString("Client","Paravent",temp);
		}
		if(dopen!="none")
		{
			RegDeleteValue(hk,"Ouverture");
			WriteConfigString("Param","Ouverture",dopen);
		}
		if(serial!="none")
		{
			RegDeleteValue(hk,"Serial");
			WriteConfigString("License","Serial",serial);
		}
		if(fprev!=-1)
		{
			RegDeleteValue(hk,"Prevente");
			temp.Format("%u",fprev);
			WriteConfigString("Client","Prevente",temp);
		}
		if(valhor!=-1)
		{
			RegDeleteValue(hk,"ValHor");
			temp.Format("%u",valhor);
			WriteConfigString("Client","ValHor",temp);
		}
		if(nvalplace!=-1)
		{
			RegDeleteValue(hk,"ValPlace");
			temp.Format("%u",nvalplace);
			WriteConfigString("Client","ValPlace",temp);
		}
		if(horaire!=-1)
		{
			RegDeleteValue(hk,"Horaire");
			temp.Format("%u",horaire);
			WriteConfigString("Client","Horaire",temp);
		}
		if(autonews!=-1)
		{
			RegDeleteValue(hk,"Autonews");
			temp.Format("%u",autonews);
			WriteConfigString("Client","Autonews",temp);
		}

		if(autoprint!=-1)
		{
			RegDeleteValue(hk,"Autoprint");
			temp.Format("%u",autoprint);
			WriteConfigString("Client","Autoprint",temp);
		}

		RegCloseKey(hk);
	}
	//configtext=CRead(configpath);
	InitVariable();
	if(fversion<459)
		infocert=0;
	else
		if(pays=="FR"&&cur=="€")// si on travaille en france et français uniquement
			infocert=1;
	if(dopen!="")
	{	// Si le fichier data a déjà été créé on marque les ventes commencées.
		opendir=datadir+"\\"+dopen;
		InterlockedExchange(&artro,1);// On ne peut plus modifier les articles
	}
	else
		InterlockedExchange(&artro,0);// Ventes non commencées: on peut modifier les articles
	Printer=NULL;	
	STOP=0;
	fart=fartaf=0;
	noprint=0; 
	pcombo=NULL;
	flagraz=0;
	// Chargement des images de l'application
	temp=skindir+"NF525.jpg";
	wstr=temp;
	pnf525=Image::FromFile(wstr,0);

	temp=skindir+"btnpage_gauche_etat1.png";
	wstr=temp;
	pbninf=Image::FromFile(wstr,0);

	temp=skindir+"btnpage_gauche_etat2.png";
	wstr=temp;
	pbsinf=Image::FromFile(wstr,0);

	temp=skindir+"btnpage_droit_etat1.png";
	wstr=temp;
	pbnsup=Image::FromFile(wstr,0);

	temp=skindir+"btnpage_droit_etat2.png";
	wstr=temp;
	pbssup=Image::FromFile(wstr,0);

	temp=skindir+"manager_etat1.jpg";
	wstr=temp;
	pbnman=Image::FromFile(wstr,0);

	temp=skindir+"manager_etat2.jpg";
	wstr=temp;
	pbsman=Image::FromFile(wstr,0);

	temp=skindir+"quitter_etat1.jpg";
	wstr=temp;
	pbnquit=Image::FromFile(wstr,0);

	temp=skindir+"quitter_etat2.jpg";
	wstr=temp;
	pbsquit=Image::FromFile(wstr,0);

	temp=skindir+"quitter_etat1.jpg";
	wstr=temp;
	pbnquit=Image::FromFile(wstr,0);
	temp=skindir+"quitter_etat2.jpg";
	wstr=temp;
	pbsquit=Image::FromFile(wstr,0);

	temp=skindir+"btn_barre_etat1.jpg";
	wstr=temp;
	pbnenc=Image::FromFile(wstr,0);

	temp=skindir+"btn_barre_etat2.jpg";
	wstr=temp;
	pbsenc=Image::FromFile(wstr,0);

	temp=skindir+"btn_copy_etat1.jpg";
	wstr=temp;
	pbncopy=Image::FromFile(wstr,0);

	temp=skindir+"btn_copy_etat2.jpg";
	wstr=temp;
	pbscopy=Image::FromFile(wstr,0);

	temp=skindir+"btn_paste_etat1.jpg";
	wstr=temp;
	pbnpaste=Image::FromFile(wstr,0);

	temp=skindir+"btn_paste_etat2.jpg";
	wstr=temp;
	pbspaste=Image::FromFile(wstr,0);

	temp=skindir+"BTN_COLOR_ROSE_etat1.jpg";
	wstr=temp;
	pbnartac=Image::FromFile(wstr,0);

	temp=skindir+"BTN_COLOR_ROSE_etat2.jpg";
	wstr=temp;
	pbsartac=Image::FromFile(wstr,0);

	temp=skindir+"btn_chiffrevierge_etat1.jpg";
	wstr=temp;
	pbnnum=Image::FromFile(wstr,0);

	temp=skindir+"btn_chiffrevierge_etat2.jpg";
	wstr=temp;
	pbsnum=Image::FromFile(wstr,0);

	temp=skindir+"btn_pluminus_etat1.jpg";
	wstr=temp;
	pbnplum=new Image(wstr,0);

	temp=skindir+"btn_pluminus_etat2.jpg";
	wstr=temp;
	pbsplum=new Image(wstr,0);

	temp=skindir+"btn_reset_etat1.jpg";
	wstr=temp;
	pbnclr=Image::FromFile(wstr,0);

	temp=skindir+"btn_reset_etat2.jpg";
	wstr=temp;
	pbsclr=Image::FromFile(wstr,0);

	temp=skindir+"effacer_etat1.jpg";
	wstr=temp;
	pbndel=Image::FromFile(wstr,0);

	temp=skindir+"effacer_etat2.jpg";
	wstr=temp;
	pbsdel=Image::FromFile(wstr,0);

	temp=skindir+"btn_article_etat1.jpg";
	wstr=temp;
	pbnartbo=Image::FromFile(wstr,0);

	temp=skindir+"btn_article_etat2.jpg";
	wstr=temp;
	pbsartbo=Image::FromFile(wstr,0);

	temp=skindir+"btn_import_export_mode_etat1.jpg";
	wstr=temp;
	pbnpomo=Image::FromFile(wstr,0);

	temp=skindir+"btn_import_export_mode_etat2.jpg";
	wstr=temp;
	pbspomo=Image::FromFile(wstr,0);

	temp=skindir+"btn_navigation_etat1.jpg";
	wstr=temp;
	pbnnav=Image::FromFile(wstr,0);

	temp=skindir+"btn_navigation_etat2.jpg";
	wstr=temp;
	pbsnav=Image::FromFile(wstr,0);

	temp=skindir+"retour_etat1.jpg";
	wstr=temp;
	pbnret=Image::FromFile(wstr,0);

	temp=skindir+"retour_etat2.jpg";
	wstr=temp;
	pbsret=Image::FromFile(wstr,0);

	temp=skindir+"btn_gd-barre_etat1.jpg";
	wstr=temp;
	pbnresbar=Image::FromFile(wstr,0);

	temp=skindir+"btn_gd-barre_etat2.jpg";
	wstr=temp;
	pbsresbar=Image::FromFile(wstr,0);

	temp=skindir+"fond-blanc.jpg";
	wstr=temp;
	pecrac=Image::FromFile(wstr,0);

	temp=skindir+"support_btnpage.jpg";
	wstr=temp;
	pspage=Image::FromFile(wstr,0);

	temp=skindir+"arcdecercle.jpg";
	wstr=temp;
	parcdc=Image::FromFile(wstr,0);

	temp=skindir+"windows noir.jpg";
	wstr=temp;
	pbur=Image::FromFile(wstr,0);

	temp=skindir+"printer noir.jpg";
	wstr=temp;
	pprint=Image::FromFile(wstr,0);

	temp=skindir+"net noir.jpg";
	wstr=temp;
	pnet=Image::FromFile(wstr,0);

	//Chargement des images de checkbox
	temp=skindir+"check.jpg";
	wstr=temp;
	pcheck=Image::FromFile(wstr,0);

	temp=skindir+"ncheck.jpg";
	wstr=temp;
	pncheck=Image::FromFile(wstr,0);
	Bitmap* pbmp;

	for(i=0;i<3;i++)
	{
		temp1.Format("%u",i+1);
		famim[i]=AfxGetApp()->GetProfileString("Famille",temp1,"");
		if(famim[i].GetAt(0)=='?')
			wstr=famim[i].Mid(1);
		else
			wstr=workdir+famim[i];
		pbmp= new Bitmap(wstr,0);
		if(pbmp->GetHBITMAP(0xffffff,&pfam[i])==Ok)
		{
			if(famim[i].GetAt(0)=='?')
			{
				famim[i]=famim[i].Mid(1);
				AfxGetApp()->WriteProfileString("Famille",temp1,famim[i]);
			}
			pbfam[i]=new Bitmap(pfam[i],0);
		}
		else
		{
			if(famim[i]!="")
			{
				delete pbmp;
				temp=skindir+"\\Famille\\Image new.jpg";
				wstr=temp;
				pbmp= new Bitmap(wstr,0);
				pbmp->GetHBITMAP(0xffffff,&pfam[i]);
				pbfam[i]=new Bitmap(pfam[i],0);
				if(famim[i].GetAt(0)!='?')
				{
					famim[i]="?"+famim[i];
					AfxGetApp()->WriteProfileString("Famille",temp1,famim[i]);
				}
			}
			else
			{
				wstr=famim[i];
				pbfam[i]=new Bitmap(wstr,0);
			}
		}
		if(pbmp)
			delete pbmp;
	}
	for(i=0;i<9;i++)
	{
		temp1.Format("%u",i+1);//123456789
		rubim[i]=AfxGetApp()->GetProfileString("Rubrique",temp1,"");
		if(rubim[i].GetAt(0)=='?')
			wstr=rubim[i].Mid(1);
		else
			wstr=workdir+rubim[i];
		pbmp=new Bitmap(wstr,0);
		if(pbmp->GetHBITMAP(0xffffff,&prub[i])==Ok)
		{
			if(rubim[i].GetAt(0)=='?')
			{
				rubim[i]=rubim[i].Mid(1);
				AfxGetApp()->WriteProfileString("Rubrique",temp1,rubim[i]);
			}
			pbrub[i]= new Bitmap(prub[i],0);
		}
		else
		{
			if(rubim[i]!="")
			{
				delete pbmp;
				temp=skindir+"\\Rubrique\\Image new.jpg";
				wstr=temp;
				pbmp= new Bitmap(wstr,0);
				pbmp->GetHBITMAP(0xffffff,&prub[i]);
				pbrub[i]=new Bitmap(prub[i],0);
				if(rubim[i].GetAt(0)!='?')
				{
					rubim[i]="?"+rubim[i];
					AfxGetApp()->WriteProfileString("Rubrique",temp1,rubim[i]);
				}
			}
			else
			{
				wstr=rubim[i];
				pbrub [i]=new Bitmap(wstr,0);
			}
		}
		if(pbmp)
			delete pbmp;
	}
//*********************************************************************************************************************
	for(i=1;i<TXTC;i++)
	{
		temp.Format("%u",i);
		txtc[i].ReleaseBuffer(GetPrivateProfileString("Controle",temp,"",txtc[i].GetBuffer(100),100,langfile));
	}
	for(i=1;i<8;i++)
	{
		temp.Format("%u",i);
		jourtxt[i-1].ReleaseBuffer(GetPrivateProfileString("Jour",temp,"",jourtxt[i-1].GetBuffer(100),100,langfile));
	}
	for(i=1;i<TXTM;i++)
	{
		temp.Format("%u",i);
		txtm[i].ReleaseBuffer(GetPrivateProfileString("Message",temp,"",txtm[i].GetBuffer(100),100,langfile));
	}
//*********************************************************************************************************************
	Table[11]=txtc[1];//ENCAISSER
	// Récupération des dimensions du bureau
	GetDesktopWindow( )->GetWindowRect(&rect);
	if(rect.Width()!=768&&rect.Height()!=1366)
	{
		if(rect.Width()!=600&&rect.Height()!=1024)
		{
			rect.left=0;
			rect.right=(rect.Height()*768)/1366;
		}
	}
	wlargeur=rect.Width();
	whauteur=rect.Height();
	wsel=artrange=0;
	calc="";
	viewscan=0;
	wsel=0;
	selfam=selrub=etb=0;
	fexermois=0;//Flag de demande cloture mensuelle
	// Préparation des variables globales de dimensions et dessin
	oltou=(float)wlargeur/400;
	eltou=(float)wlargeur/300;
	ehtou=(float)whauteur/300;
	ohnum=((float)whauteur/10)+(whauteur/150);
	ltou=((float)wlargeur-(6*eltou))/5;//+wlargeur/4.8;
	htou=((float)whauteur-ohnum-(5*ehtou))/5;
	
	klto=(float)(((float)wlargeur*14.5)/19.5);
	khto=(float)(((float)whauteur*14*12)/(27*16));
	olto=(float)(klto/200);
	ohto=(float)(((float)whauteur*8.3)/27);
	elto=klto/200;
	ehto=khto/50;
	lto=(klto-olto-(4*elto))/4;//+wlargeur/4.8;
	hto=(khto-(2*ehto))/3;

	ohnu=ohto;
	klnu=(float)(((float)wlargeur*5)/19.5);
	khnu=(float)(((float)whauteur*14)/27);
	elnu=klnu/100;
	ehnu=khnu/50;
	olnu=klto+elnu;
	lnu=(klnu-(3*elnu))/2;
	hnu=(khnu-(5*ehnu))/6;


	//ticketbrush.CreateSolidBrush(ticketrefcolor);
	//pagebrush.CreateSolidBrush(pagerefcolor);
	// Préparation des fonts globales de l'application
	hatprxart.CreateFont(whauteur/40,// FONT DES BOUTONS DE CAISSE
		wlargeur/120,
		0,
		0,
		600,//Epaisseur900
		0,
		0,
		0,
		DEFAULT_CHARSET,
		OUT_TT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		PROOF_QUALITY,//ANTIALIASED_QUALITY,//PROOF_QUALITY,
		DEFAULT_PITCH |FF_DONTCARE,
		"Verdana");//"Haettenschweiler");
	hatart.CreateFont(whauteur/45,// FONT DES BOUTONS DE CAISSE
		wlargeur/130,
		0,
		0,
		0,//600,//Epaisseur900
		0,
		0,
		0,
		DEFAULT_CHARSET,
		OUT_TT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		PROOF_QUALITY,//ANTIALIASED_QUALITY,//PROOF_QUALITY,
		DEFAULT_PITCH |FF_DONTCARE,
		"Haettenschweiler");
	geotitre.CreateFont(whauteur/21,// FONT DES BOUTONS DE CAISSE
		wlargeur/45,
		0,
		0,
		FW_BOLD,//600,//Epaisseur900
		0,
		0,
		0,
		DEFAULT_CHARSET,
		OUT_TT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		PROOF_QUALITY,//ANTIALIASED_QUALITY,//PROOF_QUALITY,
		DEFAULT_PITCH|FF_DONTCARE,
		"GeosansLight");
	geostat.CreateFont(whauteur/35,// FONT DES BOUTONS DE CAISSE
		wlargeur/70,
		0,
		0,
		FW_BOLD,//600,//Epaisseur900
		0,
		0,
		0,
		DEFAULT_CHARSET,
		OUT_TT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		PROOF_QUALITY,//ANTIALIASED_QUALITY,//PROOF_QUALITY,
		DEFAULT_PITCH|FF_DONTCARE,
		"GeosansLight");
	geodate.CreateFont(whauteur/40,// FONT DES BOUTONS DE CAISSE
		wlargeur/120,
		0,
		0,
		FW_BOLD,//Epaisseur900
		0,
		0,
		0,
		DEFAULT_CHARSET,
		OUT_TT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		PROOF_QUALITY,
		DEFAULT_PITCH|FF_DONTCARE,
		"GeosansLight");
	geoent.CreateFont(whauteur/45,// FONT DES BOUTONS DE CAISSE
		wlargeur/100,
		0,
		0,
		FW_BOLD,//Epaisseur900
		0,
		0,
		0,
		DEFAULT_CHARSET,
		OUT_TT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		PROOF_QUALITY,
		DEFAULT_PITCH|FF_DONTCARE,
		"GeosansLight");
	geodateoc.CreateFont(whauteur/45,// FONT DES BOUTONS DE CAISSE
		wlargeur/100,
		0,
		0,
		FW_BOLD,//Epaisseur900
		0,
		0,
		0,
		DEFAULT_CHARSET,
		OUT_TT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		PROOF_QUALITY,
		DEFAULT_PITCH|FF_DONTCARE,
		"GeosansLight");
	geonum.CreateFont(whauteur/25,// FONT DES BOUTONS DE CAISSE
		wlargeur/50,
		0,
		0,
		0,//Epaisseur900
		0,
		0,
		0,
		DEFAULT_CHARSET,
		OUT_TT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		PROOF_QUALITY,//ANTIALIASED_QUALITY,//PROOF_QUALITY,
		DEFAULT_PITCH|FF_DONTCARE,
		"GeosansLight");
	geopage.CreateFont(whauteur/20,// FONT DES BOUTONS DE CAISSE
		wlargeur/30,
		0,
		0,
		0,//600,//Epaisseur900
		0,
		0,
		0,
		DEFAULT_CHARSET,
		OUT_TT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		PROOF_QUALITY,//ANTIALIASED_QUALITY,//PROOF_QUALITY,
		DEFAULT_PITCH|FF_DONTCARE,
		"GeosansLight");
	butnumfont.CreateFont(whauteur/20,
		wlargeur/30,
		0,
		0,
		600,//Epaisseur
		0,
		0,
		0,
		DEFAULT_CHARSET,
		OUT_TT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		NONANTIALIASED_QUALITY,//ANTIALIASED_QUALITY,//PROOF_QUALITY,
		DEFAULT_PITCH|FF_DONTCARE,
		"ARIAL");

	ticketfont.CreateFont(whauteur/30, //FONT DES CHAMPS ET LISTE
		wlargeur/80,
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
	ticketentreefont.CreateFont(whauteur/30,// FONT DU TICKET
		wlargeur/90,
		0,
		0,
		FW_BOLD,//
		0,
		0,
		0,
		DEFAULT_CHARSET,
		OUT_TT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		CLEARTYPE_QUALITY,//PROOF_QUALITY,//ANTIALIASED_QUALITY,//NONANTIALIASED_QUALITY,
		DEFAULT_PITCH|FF_DONTCARE,
		"ARIAL");
	pagefont.CreateFont(whauteur/12,// FONT DU N° de PAGE
		wlargeur/20,
		0,
		0,
		1000 ,//Epaisseur
		0,
		0,
		0,
		DEFAULT_CHARSET,
		OUT_TT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		NONANTIALIASED_QUALITY,//ANTIALIASED_QUALITY,//PROOF_QUALITY,
		DEFAULT_PITCH|FF_DONTCARE,
		"ARIAL");
	controlfont.CreateFont(whauteur/8,// FONT DU N° de PAGE
		wlargeur/17,
		0,
		0,
		1000 ,//Epaisseur
		0,
		0,
		0,
		DEFAULT_CHARSET,
		OUT_TT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		NONANTIALIASED_QUALITY,//ANTIALIASED_QUALITY,//PROOF_QUALITY,
		DEFAULT_PITCH|FF_DONTCARE,
		"ARIAL");
	totaltitrefont.CreateFont(whauteur/25,// FONT DES BOUTONS D'ACCEUIL
		wlargeur/60,
		0,
		0,
		1000,//Epaisseur
		0,
		0,
		0,
		DEFAULT_CHARSET,
		OUT_TT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		NONANTIALIASED_QUALITY,//ANTIALIASED_QUALITY,//PROOF_QUALITY,
		DEFAULT_PITCH|FF_DONTCARE,
		"ARIAL");
	totalfont.CreateFont(whauteur/15,// FONT DES BOUTONS D'ACCEUIL
		wlargeur/50,
		0,
		0,
		1000,//Epaisseur
		0,
		0,
		0,
		DEFAULT_CHARSET,
		OUT_TT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		NONANTIALIASED_QUALITY,//ANTIALIASED_QUALITY,//PROOF_QUALITY,
		DEFAULT_PITCH|FF_DONTCARE,
		"ARIAL");

	butcdefont.CreateFont(whauteur/30,// FONT DES BOUTONS D'ACCEUIL
		0,//wlargeur/70,
		0,
		0,
		FW_NORMAL,//600,//Epaisseur
		0,
		0,
		0,
		DEFAULT_CHARSET,
		OUT_TT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		NONANTIALIASED_QUALITY,//ANTIALIASED_QUALITY,//PROOF_QUALITY,
		DEFAULT_PITCH|FF_DONTCARE,
		"ARIAL");
	buttonfont.CreateFont(whauteur/30,// FONT DES BOUTONS DE CAISSE
		wlargeur/80,
		0,
		0,
		900,//Epaisseur
		0,
		0,
		0,
		DEFAULT_CHARSET,
		OUT_TT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		NONANTIALIASED_QUALITY,//ANTIALIASED_QUALITY,//PROOF_QUALITY,
		DEFAULT_PITCH|FF_DONTCARE,
		"ARIAL");
	buttoncontrolfont.CreateFont(whauteur/30,// FONT DES BOUTONS DE CAISSE
		wlargeur/150,
		0,
		0,
		600,//Epaisseur900
		0,
		0,
		0,
		DEFAULT_CHARSET,
		OUT_TT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		NONANTIALIASED_QUALITY,//ANTIALIASED_QUALITY,//PROOF_QUALITY,
		DEFAULT_PITCH|FF_DONTCARE,
		"ARIAL");
	titlefont.CreateFont(whauteur/14,//FONT DU TITRE DE LA PAGE
		0,//wlargeur/40,
		0,
		0,
		FW_BOLD,//1000,//Epaisseur
		0,
		0,
		0,
		DEFAULT_CHARSET,
		OUT_TT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		NONANTIALIASED_QUALITY,//ANTIALIASED_QUALITY,//PROOF_QUALITY,
		DEFAULT_PITCH|FF_DONTCARE,
		"ARIAL");
	combfont.CreateFont(whauteur/38,
		wlargeur/120,
		0,
		0,
		600,//Epaisseur
		0,
		0,
		0,
		DEFAULT_CHARSET,
		OUT_TT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		NONANTIALIASED_QUALITY,//ANTIALIASED_QUALITY,//PROOF_QUALITY,
		DEFAULT_PITCH|FF_DONTCARE,
		"ARIAL");
	scanfont.CreateFont(whauteur/30,//25
		wlargeur/100,//55
		0,
		0,
		600,//Epaisseur
		0,
		0,
		0,
		DEFAULT_CHARSET,
		OUT_TT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		NONANTIALIASED_QUALITY,//ANTIALIASED_QUALITY,//PROOF_QUALITY,
		DEFAULT_PITCH|FF_DONTCARE,
		"ARIAL");
	boutnumfont.CreateFont(whauteur/20,
		wlargeur/30,
		0,
		0,
		600,//Epaisseur
		0,
		0,
		0,
		DEFAULT_CHARSET,
		OUT_TT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		NONANTIALIASED_QUALITY,//ANTIALIASED_QUALITY,//PROOF_QUALITY,
		DEFAULT_PITCH|FF_DONTCARE,
		"ARIAL");
	CDialog::OnInitDialog();
	rctscan.top=(LONG)whauteur/18;
	rctscan.left=(LONG)(oltou+2*ltou/3+eltou);
	rctscan.right=(LONG)(oltou+4*ltou+4*eltou+ltou/3);
	rctscan.bottom=(LONG)(whauteur/11);
	nscan.SetWindowPos(&wndTop,rctscan.left,rctscan.top,rctscan.Width(),rctscan.Height(),SWP_HIDEWINDOW   );
	wsel=0;
	if(master)
	{
		if(alone==0)
			tnet.SetWindowTextA("HRSR");
		else
			if(alone==1)
				tnet.SetWindowTextA("HRAU");/**/
	}
	else
		tnet.SetWindowTextA("HRDN");
	lcb.ResetContent();
	lcb.AddString(txtc[155]+" "+txtc[154]);
	lcb.AddString(txtc[155]+" "+"ETC");
	lcb.AddString(txtc[155]+" "+"ARBAN");

	ltype.ResetContent();
	ltype.AddString(txtc[144]);
	ltype.AddString(txtc[55]);
	ltype.AddString(txtc[145]);

	lmois.ResetContent();
	lmois.AddString("01");
	lmois.AddString("02");
	lmois.AddString("03");
	lmois.AddString("04");
	lmois.AddString("05");
	lmois.AddString("06");
	lmois.AddString("07");
	lmois.AddString("08");
	lmois.AddString("09");
	lmois.AddString("10");
	lmois.AddString("11");
	lmois.AddString("12");
	while(!IsWindow(this->GetSafeHwnd()))
		Sleep(100);// Attente de la création de la fenêtre principale
	if(sp.GetSafeHwnd()==NULL)
	{	// lancement de la fenêtre de simulation du ticket
		sp.Create(IDD_SIMPRINT,this);
		if(wlargeur>whauteur)
			sp.SetWindowPos(&wndTopMost,0,0,wlargeur/6,3*whauteur/3,SWP_HIDEWINDOW);
		else
			sp.SetWindowPos(&wndTopMost,0,0,wlargeur/2,3*whauteur/3,SWP_HIDEWINDOW);
		sp.CenterWindow();
	}
	av1.SetWindowPos(&wndTop,wlargeur/4,whauteur/3+whauteur/20,2*wlargeur/4,whauteur/20,SWP_HIDEWINDOW   );
	av2.SetWindowPos(&wndTop,0,whauteur/2+whauteur/20,wlargeur,whauteur/20,SWP_HIDEWINDOW   );
	av3.SetWindowPos(&wndTop,0,whauteur/2+3*whauteur/20,wlargeur,whauteur/20,SWP_HIDEWINDOW   );
	av1.SetWindowText("");
	av2.SetWindowText("");
	av3.SetWindowText("");
	SetWindowPos(&wndTopMost,0,0,wlargeur,whauteur,SWP_SHOWWINDOW   );//wxwy
	CenterWindow(0);
	RedrawWindow(0,0,1|256|4);
	catfile=CRead(sysdir+"\\csat.avs");
	if(catfile=="Erreur de lecture fichier")
	{
		if(dexer=="")
		{
			temp="Cat file\r\n";
			CWrite(sysdir+"\\csat.avs",temp,0);
			initavert0="Veuillez renseigner le mois de début d'exercice";
			//initavert1="";
			//initavert2="";
			RedrawWindow(0,0,1|256|4);
			//nexer.SetWindowPos(&wndTop,xn,(int)(yohnum+7*sph),largeur,(int)((1.8)*sph),SWP_SHOWWINDOW   );
			sexer.SetWindowPos(&wndTop,3*wlargeur/4,whauteur/3+whauteur/20,wlargeur/10,whauteur/20,SWP_SHOWWINDOW   );
			sexer.SetFont(&geodate,0);
			sexer.SetWindowText("01");
			sexer.EnableWindow(1);
			OnStnClickedSexer();
			catfile=CRead(sysdir+"\\csat.avs");
		}
		else
		{
			temp="Cat file\r\n"+dexer+"\r\n";
			CWrite(sysdir+"\\csat.avs",temp,0);
			catfile=temp;
		}
	}
	int idx=0;
	int nbfile=0;
	while(idx!=-1)
	{
		if((idx=catfile.Find("\r\n",idx))!=-1)
			nbfile++;
		else
			break;
		idx+=2;
	}
	pimp.SetRange(0,nbfile+6);
	pimp.SetWindowPos(&wndTop,wlargeur/20,(int)((double)whauteur*25.5/27),wlargeur/4,(int)((double)whauteur*0.6/27),SWP_HIDEWINDOW);
	pimp.CenterWindow();
	pimp.SetStep(1);
	pimp.ShowWindow(1);
	temp=GetConfigString("License","Version","");
	initavert1=txtm[71];//Vérification de la version
	av1.SetWindowText("");
	av2.SetWindowText(initavert1);
	av3.SetWindowText("");
	pimp.StepIt();
	//av2.RedrawWindow(0,0,1|256|4);
	//RedrawWindow(0,0,1|256|4);
	Sleep(300);
	if(temp!=""&&atoi(temp)!=(int)fversion&&MAJ==0)
		MessageBox("Erreur de version !\r\nVeuillez contacter votre revendeur.");
	temp.Format(" %.3f",fversion/1000);
	if(MAJ==0)
	{
		initavert1=txtm[94];//Concert version
		initavert1+=" "+temp;
	}
	else
		initavert1=txtm[95];//"Mise à jour de Concert en cours"
	av1.SetWindowText("");
	av2.SetWindowText(initavert1);
	av3.SetWindowText("");
	pimp.StepIt();
	//av2.RedrawWindow(0,0,1|256|4);

	//RedrawWindow(0,0,1|256|4);
	Sleep(300);
	user="Non autentifié";
	wdg=0 ;
	initavert1=txtm[57];//Chargement des paramètres
	initavert2="";
	av1.SetWindowText("");
	av2.SetWindowText(initavert1);
	av3.SetWindowText("");
	pimp.StepIt();
	//av2.RedrawWindow(0,0,1|256|4);
	//RedrawWindow(0,0,1|256|4);
	Sleep(300);
	initavert1=txtm[96];//Vérification de vos fichiers en cours
	initavert2="";
	av1.SetWindowText("");
	av2.SetWindowText(initavert1);
	av3.SetWindowText("");
	pimp.StepIt();
	//av2.RedrawWindow(0,0,1|256|4);
	//RedrawWindow(0,0,1|256|4);
	Sleep(300);
	if(InitUserVariable()==0)
	{
		wsel=1	;
		OnBnClickedQuitter();
		return TRUE;
	}
	VerifyFileIntegrity();
	//pimp.SetStep(1);
	Sleep(500);
	pimp.ShowWindow(1);

retry_code:;
	if(valpwd)
	{	// Test si on est en mode demande de mot de passe à l'ouverture
		CNum* pwlnum=new CNum ();
		pwlnum->wlargeur=(int)((float)(wlargeur/2));
		pwlnum->whauteur=whauteur/3;
		pwlnum->nID=0;
		pwlnum->txtmessage=txtm[39];//"Entrer votre code";
		pwlnum->mode=4;
		pwlnum->nombre="";
		pwlnum->chiffre=8;
		pwlnum->DoModal();
		if(!(pwlnum->nombre==codeadmin||pwlnum->nombre==codeuser||pwlnum->nombre==codemanager||pwlnum->nombre==codereseller))
		{
			user="Echec authentification";
			Habilitation("Accès machine "+user);
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
				return FALSE;
			}
		}
		else
		{
			if(pwlnum->nombre==codeadmin)
				user="Administrateur";
			else
				if(pwlnum->nombre==codemanager)
					user="Manager";
			    else
				    if(pwlnum->nombre==codereseller)
					   user="Revendeur";
				    else
					    user="Vendeur";
		}
		delete pwlnum;
	}
	// Chargement de la liste des prix alphabétique pour les codebarre ETC
	pl.ResetContent();
	pl.AddString(" ");
	char c;
	for(i=1;i<21;i++)
	{
		c = i+0x40;
		temp=c;
		pl.AddString(temp);
	}

	Habilitation("Accès machine "+user);
	// Chargement de la page de démarrage avec son progress bar et avertissement
	pagejour=jourtxt[tim.GetDayOfWeek()-1];	
	titretext=nom;
	CFileFind ff;
	BOOL result;
	float f;
	result=ff.FindFile(controldir+"\\*.*",0);
	while(result)
	{
		result=ff.FindNextFile();
		if (ff.IsDots())
		 continue;
		if (ff.IsDirectory())
		 continue;
		if(ff.GetFileName().Find("Concertupdate",0)!=-1&&ff.GetFileName().Find("arb",0)!=-1)
		{
			i=ff.GetFileName().Find("_",0);
			j=ff.GetFileName().Find(".",0);//Concertupdate_462.arb ou Concertupdate_4621.arb
			
			temp=ff.GetFileName().Mid(i+1,j-i-1);// Gestion 1 digit en plus
			f=(float)atof(temp);
			if(f>=459)
				DeleteFile(workdir+"\\Auditinfo.dat");
			if(f>=fversion)
			{
				fileversion.Format("%.3f",fversion/1000);
				fupdate=1;
				fileupdate=ff.GetFilePath();
				copyupdate=workdir+"\\Update\\"+ff.GetFileName().Left(ff.GetFileName().GetLength()-3)+"exe";
				break;
			}
		}
	}
	ff.Close();
	if(fupdate==0)
	{
		SHGetSpecialFolderPath(GetSafeHwnd(),temp.GetBuffer(MAX_PATH),CSIDL_DESKTOPDIRECTORY  ,0);
		temp.ReleaseBuffer(-1);
		result=ff.FindFile(temp+"\\*.*",0);
		while(result)
		{
			result=ff.FindNextFile();
			if (ff.IsDots())
			 continue;
			if (ff.IsDirectory())
			 continue;
			if(ff.GetFileName().Find("Concertupdate",0)!=-1&&ff.GetFileName().Find("arb",0)!=-1)
			{
				i=ff.GetFileName().Find("_",0);
				j=ff.GetFileName().Find(".",0);//Concertupdate_462.arb ou Concertupdate_4621.arb
				temp=ff.GetFileName().Mid(i+1,j-i-1);
				f=(float)atof(temp);
				if(f>=459)
					DeleteFile(workdir+"\\Auditinfo.dat");
				if(f>=fversion)
				{
					fileversion.Format("%.3f",fversion/1000);
					fupdate=1;
					fileupdate=ff.GetFilePath();
					copyupdate=workdir+"\\Update\\"+ff.GetFileName().Left(ff.GetFileName().GetLength()-3)+"exe";
					break;
				}
			}
		}
		ff.Close();
	}
	if(fupdate==1)
	{
		fadmin=0;
		initavert1=txtm[56];//Voulez-vous stopper l'impression?
		initavert1+="...";
		initavert2="";
		av1.SetWindowText("");
		av2.SetWindowText(initavert1);
		av3.SetWindowText("");
		//av2.RedrawWindow(0,0,1|256|4);
		//RedrawWindow(0,0,1|256|4);
		EnableWindow(0);
		BackupConcertRegistry();
		BackupConcertControl();
		temp1=txtm[1];//Disque de sauvegarde absent!
		temp2=txtm[2];//Veuillez contacter votre revendeur.
		if(backupdir!="")
		{	// on sauvegarde sur la clé le fichier base de registre
			if(CopyFile(securedir+"\\Concert.bra",backupdir+"\\Concert.bra",FALSE)==0)
				MessageBox(temp1+"\n"+temp2);
		}
		DeleteFile(controldir+"\\Status.dat");
		WriteConfigString("Param","MAJ","1");
		MAJ=1;
		CopyFile(fileupdate,copyupdate,FALSE);
		if(infocert)
		{
			Maintenance("Mise à jour en cours version "+fileversion);
		}
		Sleep(2000);
		DeleteFile(fileupdate);
		BackupConcertRegistry();
		BackupConcertControl();
		if(backupdir!="")
		{	// on sauvegarde sur la clé le fichier clôturé ou non
			if(CopyFile(securedir+"\\Concert.bra",backupdir+"\\Concert.bra",FALSE)==0)
				MessageBox(temp1+"\n"+temp2);
		}
		OnOK();
		return FALSE;
	}
	else
	{
		if(MAJ==1)
		{
			temp.Format(" %.3f",fversion/1000);
			initavert1=txtm[37];//Mise à jour version
			initavert1+=temp;
			initavert2="";
			initavert0="";
			av1.SetWindowText("");
			av2.SetWindowText(initavert1);
			av3.SetWindowText("");
			//av2.RedrawWindow(0,0,1|256|4);
			//RedrawWindow(0,0,1|256|4);
			temp.Format("%u",(int)fversion);
			fileversion.Format("%.3f",fversion/1000);
			WriteConfigString("License","Version",temp);
			Maintenance("Mise à jour terminée vers "+fileversion);
			UpgradeETC(); //si version <5.000 génére liste correspondance
			Sleep(3000);
		}
	}
	rctdate.top=(int)((float)whauteur*25/27);
	rctdate.left=(int)((float)wlargeur*6.6/19.5);
	rctdate.bottom =whauteur;
	rctdate.right=(int)((float)wlargeur*12.9/19.5);

	rctver.top=(int)((float)whauteur*24.5/26.5);
	rctver.left=(int)((float)wlargeur*14/20);
	rctver.bottom =whauteur;
	rctver.right=(int)((float)wlargeur);
	initavert1=txtm[98];//Vérification de l'imprimante...
	initavert2="";
	av1.SetWindowText("");
	av2.SetWindowText(initavert1);
	av3.SetWindowText("");
	//RedrawWindow(0,0,1|256|4);

TEST_IMPRIMANTE:;// Vérification des imprimantes nécessaires
	if(!simul)
	{
		nbyte=1000;
		GetDefaultPrinter(printername.GetBuffer(1000),&nbyte);
		printername.ReleaseBuffer(nbyte);
		OpenPrinter(  printername.GetBuffer(),&hPrinter,NULL);
		size=GetNbPrinterByte(hPrinter,2);
		GetPrinter(hPrinter,2,Printer,size,&cbNeeded);
		//((PRINTER_INFO_2*)Printer)->Attributes&=PRINTER_ATTRIBUTE_ENABLE_BIDI;
		pd.pDatatype=((PRINTER_INFO_2*)Printer)->pDatatype;
		pd.pDevMode=((PRINTER_INFO_2*)Printer)->pDevMode;
		pd.DesiredAccess=PRINTER_ALL_ACCESS;
		SetPrinter(hPrinter,2,Printer,0);
		size=GetNbPrinterByte(hPrinter,5);
		GetPrinter(hPrinter,5,Printer,size,&cbNeeded);
		if((((PRINTER_INFO_5*)Printer)->Attributes&PRINTER_ATTRIBUTE_WORK_OFFLINE)&&(printername.Find("KPSX")!=-1||printername.Find("Citizen CL-S400DT")!=-1))
		{
			CMessage* pdlg;
			CString temp1;
			CString temp2;
			CString temp3;
			pdlg= new CMessage(this);
			pwlog=pdlg;
			pdlg->mes1=txtm[7];//Imprimante débranchée de son port initial
			pdlg->mes2=txtm[8];//Veuillez la reconnecter et cliquer
			pdlg->mes3=txtm[9];//sur OUI pour retester la connection
			pdlg->mode=0;
			if(pdlg->DoModal()==IDOK)
			{
				ClosePrinter(hPrinter);
				delete pdlg;
				pwlog=NULL;
				goto TEST_IMPRIMANTE;
			}
			else
			{
				delete pdlg;
				pwlog=NULL;
				MessageBox(txtm[10]+"\r\r"+txtm[11]);
				if(infocert)
					ImprimanteIndisponible("Imprimante dédiée hors ligne");
				OnOK();
				if(!fdev)
				{
					SystemShutdown();
				}
				return TRUE; /**/
			}
		}
		else
			noprint=0;
		ClosePrinter(hPrinter);
		Sleep(100);
retry_OpenPrinter1:;		
		hPrinter=NULL;
		wdg=0;
		// Retest des imprimantes	
		if((printername.Find("KPSX")!=-1||printername.Find("Citizen CL-S400DT")!=-1))
		{
			OpenPrinter( printername.GetBuffer(),&hPrinter,&pd);
		}
		else
		{
			Sleep(500);
			goto retry_OpenPrinter1;
		}
		if(Printer!=NULL)// Mise en place des éléments d'impression avancés et mode du port dans le spooler
		{
			size=GetNbPrinterByte(hPrinter,5);
			GetPrinter(hPrinter,5,Printer,size,&cbNeeded);
			((PRINTER_INFO_5*)Printer)->Attributes&=~PRINTER_ATTRIBUTE_QUEUED;// Imprimr de suite pendant spoolage
			((PRINTER_INFO_5*)Printer)->Attributes&=~PRINTER_ATTRIBUTE_DIRECT;// Spooler utilisé
			((PRINTER_INFO_5*)Printer)->Attributes|=PRINTER_ATTRIBUTE_ENABLE_BIDI;// Mode bidirectionnel
			((PRINTER_INFO_5*)Printer)->Attributes|=PRINTER_ATTRIBUTE_ENABLE_DEVQ;// Windows garde les documents non envoyé à l'imprimante(Sécurité en cas de coupure alimentation)
			((PRINTER_INFO_5*)Printer)->Attributes&=~PRINTER_ATTRIBUTE_KEEPPRINTEDJOBS;// Ne garde pas les documents imprimés
			((PRINTER_INFO_5*)Printer)->Attributes|=PRINTER_ATTRIBUTE_DO_COMPLETE_FIRST;// Imprime d'abord les doc dans le spooler
			if(!SetPrinter(hPrinter,5,Printer,NULL))
			{// Si les éléments ne peuvent pas être mis en place la machine s'arrête par sécurité
				MessageBox(txtm[10]+"\r\r"+txtm[11]);
				if(infocert)
					ImprimanteIndisponible("L'imprimante ne se configure pas");
				OnOK();
				if(!fdev)
				{
					SystemShutdown();
				}
				return TRUE; 
			}
			lmarge=0;
			rmarge=0;
			ClosePrinter(hPrinter);
		// Initialisation des imprimantes KMGA et KPSX
			if((printername.Find("KPSX")!=-1||printername.Find("Citizen CL-S400DT")!=-1||printername.Find("KMGA")!=-1))
			{
				if(printername.Find("KMGA")!=-1)
				{

					//************** Général matériel ***************
					BYTE m0[2]={0x1F,0x74};	//Set Paper Width
					//PrinterCommande(m0,2);
		
					BYTE m1[4]={0x1F,0x03,0x08,0x03};	//Set Paper Width
					PrinterCommande(m1,4);
					BYTE m2[4]={0x1F,0x03,0x82,0x05};	//SET MINIMUM TICKET LENGTH = 1
					PrinterCommande(m2,4);
					BYTE m3[4]={0x1F,0x03,0x87,0x01};	//SET TOP OF FORM SCANMODE = 1
					PrinterCommande(m3,4);
					BYTE m4[7]={0x1F,0x0C,0x53,0x50,0x46,0xB4,0x00};// SET MAX PPRINTER SPEED 150 mm/s
					PrinterCommande(m4,7);
					BYTE m5[6]={0x1F,0x0B,0x4E,0x52,0x4A,0x64};//SET DENSITY
					PrinterCommande(m5,6);
					BYTE m6[4]={0x1D,0x73,0x10,0x00};//SET DENSITY
					PrinterCommande(m6,4);
					BYTE m7[4]={0x1F,0x0A,0x9B,0x64};	//Set Paper Feed Motor Current
					PrinterCommande(m7,4);
					BYTE m8[5]={0x1F,0xEC,0x00,0x00,0x00};//Send Presenter Command
					PrinterCommande(m8,5);
				//1F EC n sL sH
					//************** TICKET TOF ***************

					BYTE p8[4]={0x1F,0x03,0x97,0x0D};	//TOF ADD DISTANCE = 10 mm mini
					PrinterCommande(p8,4);
					if(paravent)
					{
						BYTE p9[4]={0x1F,0x03,0x98,0x97};	//TOF MARK DISTANCE = 151 mm
						PrinterCommande(p9,4);
					}
					else
					{
						BYTE p9[4]={0x1F,0x03,0x98,0x65};	//TOF MARK DISTANCE = 101 mm
						PrinterCommande(p9,4);
					}
					BYTE p10[4]={0x1F,0x03,0x99,0x01};	//SET CUT TO MARK DISTANCE = 101 mm 0x64 0x5D//5D")
					PrinterCommande(p10,4);

					if(paravent)
					{
						BYTE p11[4]={0x1F,0x03,0xD2,0x35};	//SENSOR CUT DISTANCE = 24 mm  AJUSTAGE D2COUPE TICKET
						PrinterCommande(p11,4);
					}
					else
					{
						BYTE p11[4]={0x1F,0x03,0xD2,0x34};	//SENSOR CUT DISTANCE = 24 mm  AJUSTAGE D2COUPE TICKET
						PrinterCommande(p11,4);
					}

					BYTE p12[4]={0x1F,0x03,0xDC,0x01};	//Set Cut After Auto Load Option
					PrinterCommande(p12,4);

					if(paravent)
					{
						BYTE p13[4]={0x1f ,0x03 ,0xd5 ,0x0A};// BLAK MARK à 5mm
						PrinterCommande(p13,4);
					}
					else
					{
						BYTE p13[4]={0x1f ,0x03 ,0xd5 ,0x05};// BLAK MARK à 5mm
						PrinterCommande(p13,4);
					}
					BYTE s0[3]={0x1D,0x61,0x01};	//demande de status
					PrinterCommande(s0,3);

					BYTE p15[4]={0x1F ,0x03 ,0x03 ,0x00};//PAPER LOW Option
					PrinterCommande(p15,4);
					BYTE p14[4]={0x1D ,0x73 ,0x05 ,0xFF};//OPTO Sensor threshold centre
					PrinterCommande(p14,4);
					BYTE p19[4]={0x1D ,0x73 ,0x01 ,0xA0};//OPTO Sensor Output
					PrinterCommande(p19,4);
					BYTE p16[4]={0x1D ,0x73 ,0x0D ,0xFF};//OPTO Sensor threshold extreme
					PrinterCommande(p16,4);
					BYTE p17[4]={0x1F ,0x03 ,0x8F ,0x00};//PAPER TYPE LOTTERY
					PrinterCommande(p17,4);
					BYTE p18[4]={0x1F ,0x03 ,0x0B ,0x00};//PREHEATING SCANMODE
					PrinterCommande(p18,4);
					BYTE p20[4]={0x1f ,0x03 ,0xD4 ,00};	//TOF Sensor au centre
					PrinterCommande(p20,4);
					BYTE p22[4]={0x1f ,0x0A ,0x9B ,0x64};	//Courant moteur
					PrinterCommande(p22,4);

					BYTE r1[2]={0x1D,0xFF};//Reboot printer
					PrinterCommande(r1,2);
					Sleep(3000);
					start++;
					temp.Format("%u",start);
					WriteConfigString("Param","Start",temp);

				}
				else
				{
					if(printername.Find("KPSX")!=-1)//************************************************************************************************
					{


						//************** Général matériel ***************
						BYTE s0[3]={0x1D,0x61,0x01};	//status auto
						PrinterCommande(s0,3);
			
						BYTE m1[4]={0x1F,0x03,0x08,0x03};	//Set Paper Width
						PrinterCommande(m1,4);
						BYTE m2[4]={0x1F,0x03,0x82,0x04};	//SET MINIMUM TICKET LENGTH = 100mm
						PrinterCommande(m2,4);
						BYTE m3[4]={0x1F,0x03,0x87,0x01};	//SET TOP OF FORM SCANMODE = 1
						PrinterCommande(m3,4);
						BYTE m4[7]={0x1F,0x0C,0x53,0x50,0x46,0xB4,0x00};// SET MAX PPRINTER SPEED 100 mm/s
						PrinterCommande(m4,7);
						BYTE m5[6]={0x1F,0x0B,0x4E,0x52,0x4A,0x64};//SET DENSITY 100%
						PrinterCommande(m5,6);
						BYTE m6[4]={0x1D,0x73,0x10,0x00};//OPTO Sensor threshold centre
						PrinterCommande(m6,4);

						//************** TICKET TOF ***************
						BYTE p7[4]={0x1F,0x03,0x88,0x00};	//Second Paper Out Sensor Option
						PrinterCommande(p7,4);

						BYTE p8[4]={0x1F,0x03,0x97,0x00};	//TOF ADD DISTANCE = 10 mm mini0D
						PrinterCommande(p8,4);
						BYTE p9[4]={0x1F,0x03,0x98,0x68};	//TOF MARK DISTANCE = 101 mm
						PrinterCommande(p9,4);
						BYTE p10[4]={0x1F,0x03,0x99,0x00};	//SET CUT TO MARK DISTANCE = 101 mm 0x64 0x5D//5D")
						PrinterCommande(p10,4);
						BYTE p11[4]={0x1F,0x03,0xD2,0x3E};	//SENSOR CUT DISTANCE = 54 mm réglage sortie du papier
						PrinterCommande(p11,4);
						BYTE p12[4]={0x1F,0x03,0xDC,0x01};	//Set Cut After Auto Load Option
						PrinterCommande(p12,4);
						BYTE p13[4]={0x1f ,0x03 ,0xd5 ,0x05};// BLAK MARK à 5mm
						PrinterCommande(p13,4);
						BYTE p14[4]={0x1D ,0x73 ,0x05 ,0xFF};//OPTO Sensor threshold extreme FF
						PrinterCommande(p14,4);
						BYTE p15[4]={0x1F ,0x03 ,0x03 ,0x00};//PAPER LOW Option
						PrinterCommande(p15,4);
						BYTE p16[4]={0x1D ,0x73 ,0x0D ,0xFF};//OPTO Sensor threshold extreme
						PrinterCommande(p16,4);
						BYTE p17[4]={0x1F ,0x03 ,0x8F ,0x00};//PAPER TYPE LOTTERY
						PrinterCommande(p17,4);
						BYTE p18[4]={0x1F ,0x03 ,0x0B ,0x00};//PREHEATING SCANMODE
						PrinterCommande(p18,4);
						BYTE p19[4]={0x1D ,0x73 ,0x01 ,0x82};//OPTO Sensor Output
						PrinterCommande(p19,4);
						BYTE p20[4]={0x1f ,0x03 ,0xD4 ,0x00};	//TOF Sensor au centre
						PrinterCommande(p20,4);
						BYTE p21[4]={0x1f ,0x0A ,0xB0 ,0x0A};	//Maintien frein 10s
						PrinterCommande(p21,4);
						BYTE p22[4]={0x1f ,0x0A ,0x9B ,0x40};	//Courant moteur//32
						PrinterCommande(p22,4);

						BYTE r1[2]={0x1D,0xFF};//Reboot printer
						PrinterCommande(r1,2);
						Sleep(1000);
						pimp.StepIt();
						Sleep(1000);
						pimp.StepIt();
						Sleep(1000);
						pimp.StepIt();
						Sleep(1000);
						pimp.StepIt();
						Sleep(1000);
						start++;
						temp.Format("%u",start);
						WriteConfigString("Param","Start",temp);
					}
					else
					{
						if(printername.Find("Citizen CL-S400DT")!=-1)//************************************************************************************************
						{
							/*for(i=0;i<28;i++)
							{
								pimp.StepIt();
								Sleep(10);
							}*/
							start++;
							temp.Format("%u",start);
							WriteConfigString("Param","Start",temp);
						}
					}

				}
				CDC cdcprt;	// CDC du printer
				CPrintDialog prt(FALSE);// Demande accès aux imprimantes
				prt.GetDefaults();//Demande l'imprimante par défaut
				if(prt.m_pd.hDC!=NULL)
				{	
					cdcprt.Attach(prt.m_pd.hDC);
					cdcmem=cdcprt.SaveDC();
					cdcprt.Detach();
					DeleteDC(prt.m_pd.hDC);
					GlobalFree(prt.m_pd.hDevMode);
					GlobalFree(prt.m_pd.hDevNames);
				}
			}
		}
		else
		{
			Sleep(500);
			goto retry_OpenPrinter1;
		}
	}
	else
		noprint=1;
	pimp.SetPos(nbfile+5);
	pimp.RedrawWindow(0,0,1|256|4);
	//av2.RedrawWindow(0,0,1|256|4);
	Sleep(500);
	pimp.ShowWindow(0);
	idxcopy=0;
	fsave=1;
	SPOOL=0;
	FART=0;
	ABORT=0;
	PAUSERS=0;
	QUIT=0;
	END=0;
	SEARCH=0;
	RUNRS=1;
	RUNRSG=1;
	PJOB=0;
	pwjob=NULL;
	pwidt=NULL;
	PRMODE=0;
	ngopen=ngpass=0;// Remise à 0 des compteurs de gestion du tourniquet
	hsjt=(HANDLE)_beginthreadex(NULL,0,&ScanJobThread,this,0,NULL);// lancement thread de gestion d'impression OK
	hpjt=(HANDLE)_beginthreadex(NULL,0,&PrintJobThread,this,0,NULL);// lancement thread de lancement d'impression OK
	hwpt=(HANDLE)_beginthreadex(NULL,0,&WritePrinterThread,this,0,NULL);// lancement thread de gestion d'impression OK
	//SetThreadPriority(hwpt,15);
	Sleep(500);
	if(MAJ==0)
		PRMODE=1; // Sort le ticket de démarrage
	// Définir l'icône de cette boîte de dialogue. L'infrastructure effectue cela automatiquement
	//  lorsque la fenêtre principale de l'application n'est pas une boîte de dialogue
	SetIcon(m_hIcon, TRUE);			// Définir une grande icône
	SetIcon(m_hIcon, FALSE);		// Définir une petite icône

	//Chargement des tables

	Table[0]="0";
	Table[1]="1";
	Table[2]="2";
	Table[3]="3";
	Table[4]="4";
	Table[5]="5";
	Table[6]="6";
	Table[7]="7";
	Table[8]="8";
	Table[9]="9";
	Table[10]="C";

	Table[11]=txtc[1];//ENCAISSER
	Table[12]=".";
	Table[13]="-/+";
	i=0;
	do
	{
		barre[i]='?';
		i++;
	}
	while(i<256);

	barre[224]='0';
	barre[38]='1';
	barre[233]='2';
	barre[34]='3';
	barre[39]='4';
	barre[40]='5';
	barre[45]='6';
	barre[232]='7';
	barre[95]='8';
	barre[231]='9';
	barre[13]=13;

	cript[0]="4";
	cript[1]="9";
	cript[2]="1";
	cript[3]="6";
	cript[4]="8";
	cript[5]="0";
	cript[6]="7";
	cript[7]="2";
	cript[8]="5";
	cript[9]="3";
	//Chargement des listes devise
	ldevise.ResetContent();
	ldevise.AddString("€");
	ldevise.AddString("$");
	ldevise.AddString("£");
	ldevise.AddString("FCFA"); 
	ldevise.AddString("DH"); 

	llangue.ResetContent();
	llangue.AddString("French");
	llangue.AddString("German");
	llangue.AddString("English");
	llangue.AddString("Spanish"); 
	llangue.AddString("Portuguese"); 
	llangue.AddString("Italian"); 
	llangue.AddString("Dutch");

	lpays.ResetContent();
	lpays.AddString("FR");
	lpays.AddString("D");
	lpays.AddString("GB");
	lpays.AddString("SP"); 
	lpays.AddString("P"); 
	lpays.AddString("I"); 
	lpays.AddString("NL"); 
	lpays.AddString("B"); 
	lpays.AddString("CH"); 
	lpays.AddString("MA"); 



	trackosk=0;
	int y=(int)(whauteur-20);
	int hauteur= (int)(htou/8);//
	rndray=wlargeur/76;
	fupdate=0;
	fadmin=0;
	flagnot=0;
	lsel=-1;
	lcode.SetCurSel(lsel);
	lqte.SetCurSel(lsel);
	lptot.SetCurSel(lsel);
	calc="";
	hist=0;
// Chargement des images ANTENNE

	hphqr.LoadBitmap(IDB_QRPHONE);//(IDB_CONTROLN);;
	hctn.LoadBitmap(IDB_QRVIEWSCAN);//(IDB_CONTROLN);;
	hrdr.LoadBitmap(IDB_RADIOR);
	hrgate.LoadBitmap(IDB_GATE);
	hrdb.LoadBitmap(IDB_RADIO);
	hrdv.LoadBitmap(IDB_RADIOV);
	hrdc.LoadBitmap(IDB_RADIOC);
	hrdvert.LoadBitmap(IDB_RADIOVERT);
	hrdred.LoadBitmap(IDB_RADIORED);
	hscanblue.LoadBitmap(IDB_SCANBLUE);
	hscanusb.LoadBitmap(IDB_SCANUSB);
	hrnet.LoadBitmap(IDB_RESEAU);
	hser.LoadBitmap(IDB_SERVEUR);
	haut.LoadBitmap(IDB_SAUTO);
	hweb.LoadBitmap(IDB_WEB);
// Chargement des listes évènement
// Lancement des timers et des threads de surveillance, RS232, ethernet et spooler d'imprimante
	SetWindowText("Concert");
	//controlcolor=titlerefcolor;
	SCANMODE=DT_CENTER|DT_SINGLELINE|DT_VCENTER;
	SCANCOLOR=0;
	tnet.SetWindowPos(&wndTop,(int)(oltou+5*ltou+2*eltou-ltou/2.7),5,(int)(ltou/2.7),(int)(whauteur/25),SWP_HIDEWINDOW   );
	tweb.SetWindowPos(&wndTop,(int)(oltou+5*ltou+2*eltou-ltou/2.7),(int)(15+(whauteur/25)),(int)(ltou/2.7),(int)(whauteur/25),SWP_HIDEWINDOW   );
	tcontrol.SetWindowPos(&wndTop,(int)(5),5,(int)(ltou/2.7),(int)(whauteur/25),SWP_HIDEWINDOW   );
	tgate.SetWindowPos(&wndTop,(int)(5),(int)(15+(whauteur/25)),(int)(ltou/2.7),(int)(whauteur/25),SWP_HIDEWINDOW   );
	DeleteFile(controldir+"\\Status.dat");
	i=0;
	FWEB=0;
	SCR=NULL;
	COMWL="";
	COMG=COMGATE="";
	scaninter="";
	BLUERIGHT=0;
	GATERIGHT=0;
	GATECON=0;
	HRSG=INVALID_HANDLE_VALUE;
	tgate.SetWindowText("ABSENT");
	hRSGateReadThread = (HANDLE)CreateThread(NULL,0,&RSGateReadThread,this,CREATE_SUSPENDED,&RSGateReadThreadID);
	hRSReadThread = (HANDLE)CreateThread(NULL,0,&RSReadThread,this,CREATE_SUSPENDED,&RSReadThreadID);
	hRSSearchThread = (HANDLE)CreateThread(NULL,0,&RSSearchThread,this,CREATE_SUSPENDED,&RSSearchThreadID);
	HRS=INVALID_HANDLE_VALUE;
	BASCULE=0;
	ResumeThread(hRSGateReadThread);
	ResumeThread(hRSReadThread);
	ResumeThread(hRSSearchThread);
	if(master)
	{	// cré un fichier marquant la machine comme maître
		hf=CreateFile(controldir+"\\Status.dat",GENERIC_READ|GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
		if(hf!=INVALID_HANDLE_VALUE)
		{
			if(alone)
			{
				DWORD len;
				temp="Alone";
				WriteFile(hf,temp.GetBuffer(temp.GetLength()),temp.GetLength(),&len,NULL);
			}
			CloseHandle(hf);
		}
	}
	else // sinon on efface le fichier au cas où il existerait encore
		DeleteFile(controldir+"\\Status.dat");
	SetTimer(16,10000,NULL);// Lance la recherche d'un scanner HF
	netcontdir=controldir;
	hRSScanThread = (HANDLE)_beginthreadex(NULL,0,&RSScanThread,this,CREATE_SUSPENDED ,NULL);	// lancement thread d'affichage
	hArticleScanThread = (HANDLE)CreateThread(NULL,0,&ArticleScanThread,this,0,NULL);// OK
	hImageScanThread = (HANDLE)CreateThread(NULL,0,&ImageScanThread,this,0,NULL);// OK
	hControlFileThread = (HANDLE)CreateThread(NULL,0,&ControlFileThread,this,0,NULL);// OK
	hBackupControlFileThread = (HANDLE)CreateThread(NULL,0,&BackupControlFileThread,this,0,NULL);// OK
	i=0;
	while(i<9)
	{
		hRNThread[i] = (HANDLE)CreateThread(NULL,0,&RNThread,this,0,&RNThreadID[i]);// OK
		i++;
	}

	hScanNetThread = (HANDLE)CreateThread(NULL,0,&ScanNetThread,this,0,NULL);// OK
	ResumeThread(hRSScanThread);/**/// KO
	contfile=memcontfile=0;
	if(MAJ==1)
	{	// récupère l'info comme quoi une mise à jour a été faite lors de la dernière fermeture
		{		
			PRMODE=1;
		}
	}
	pimp.ShowWindow(0);// on cache le progress de démarrage
	for(i=1;i<=16;i++)
	{
		if(cselevt[i]==1&&cfrom[i].Find("SHOP",0)!=-1)
		{
			InterlockedExchange(&CONTROL,1);
			tcontrol.SetWindowTextA("HRCONTROL"); // On remplace l'antenne par le QR
			PostMessage(WM_USER+9,0,0);//RedrawWindow(0,0,1|256|4);
			break;
		}	
	}
	for(i=1;i<=16;i++)
	{
		if(cfrom[i].Find("SHOP",0)!=-1)
		{
			break;
		}	
	}
	InterlockedExchange(&FREFCONTROL,1);//Flag demandant de rafraichir la liste de controle avec timer 13
	SetTimer(13,1000,NULL);

	if(i>16)
		SetTimer(17,30000,NULL);// Lance la recherche des fichiers WEB toutes les 30 secondes car pas de fichiers en controle
	SetTimer(11,30000,NULL);
	SetTimer(18,5000,NULL);// Lance le test de connexion WEB
	SetTimer(12,1000,NULL);//Timer de clignotement du logo réseau en présence de nouveau article et caisse non-cloturée
	SetTimer(2,1000,NULL);
	SetTimer(3,2000,NULL);
	if(!master)
		lnbap.EnableWindow(0);
	if(!master)
		lcb.EnableWindow(0);
	
	if(exermois=="00")
	{
		InterlockedExchange(&fexeran,1);
		int x=(int)((float)wlargeur*15.15/19.5);
		float yohnum=((float)whauteur/10);	
		int slargeur=(int)((float)wlargeur*3.8/19.5);
		int shauteur=(int)((float)whauteur*0.8/27);;
		float sph=9*htou/40;
		CRect titrct(wlargeur/2-wlargeur/20,whauteur/5,wlargeur/10,whauteur/3);
		wsel=0;
		RedrawWindow(0,0,1|256|4);

		initavert0="Veuillez renseigner le mois de début d'exercice";
		initavert1="";
		initavert2="";
		av1.SetWindowText(initavert0);
		av2.SetWindowText(initavert1);
		av3.SetWindowText(initavert2);
		//nexer.SetWindowPos(&wndTop,xn,(int)(yohnum+7*sph),largeur,(int)((1.8)*sph),SWP_SHOWWINDOW   );
		sexer.SetWindowPos(&wndTop,3*wlargeur/4,whauteur/3+whauteur/20,wlargeur/10,whauteur/20,SWP_SHOWWINDOW   );
		sexer.SetFont(&geodate,0);
		sexer.SetWindowText(exermois);
		sexer.EnableWindow(1);
		OnStnClickedSexer();
	}
	wsel=1;
	if(master&&wsel==1)
	{
		tnet.ShowWindow(1);
		if(alone==0)
			tnet.SetWindowTextA("HRSR");
		else
			if(alone==1)
				tnet.SetWindowTextA("HRAU");
	}

	Logger* log = Logger::getInstance(this);
	if(fdev==1)//log on dev
	{
		log->Log("=========== STARTING LOG CONCERTO ===========");
	}else{ // erase LOG if exists
		log->DeleteLog();
	}

	DrawWindowConcert();

	return TRUE;  // retourne TRUE, sauf si vous avez défini le focus sur un contrôle
}



void CConcertoDlg::PrinterCommande(BYTE* pcom,DWORD len)
{	// Routine d'écriture dans les KMGA et KPSX
		CString temp;
		HANDLE hPrinter;
		DWORD wlen;
        DOC_INFO_1 DocInfo;
		DocInfo.pDocName = "Commande directe";
		DocInfo.pOutputFile = NULL;
		DocInfo.pDatatype = "RAW";
		//temp="\x1D\x56\x02\x32";
		pimp.StepIt();
		
		if(OpenPrinter(  printername.GetBuffer(),&hPrinter,NULL)&&hPrinter!=INVALID_HANDLE_VALUE)
		{
			if(StartDocPrinter( hPrinter, 1, (LPBYTE)&DocInfo )!=0) 
			{
				if(StartPagePrinter( hPrinter))
				{
					if(!WritePrinter(hPrinter,pcom,len,&wlen)&&wlen!=len)
						MessageBox("Erreur WritePrinter");
				}
			}
		}
		EndPagePrinter( hPrinter);
		EndDocPrinter(hPrinter);
		ClosePrinter(hPrinter);
}

int CConcertoDlg::InitCaisse(CTime date)
{	// Initialisation de la caisse lors de l'impression du premier ticket après une cloture période
	CString temp;
	CString temp1;
	CString temp2;
	CString temp3;
	int njour ;
	int sec;
	int min=59;
	CString st;
	CString se;
	CTime tim;
	CTime tom;
	CFileFind cff;
	CFileStatus cfs;
	tim=date;
	temp=date.Format("%H");
	njour=date.GetDay();
retry:;
	st="";
	if(temp>="00"&&temp<="04")//test période après minuit et avant 5H
	{
		CTimeSpan sts(0,1,0,0); 
		tom=tim;
		while(tom.GetDay()==njour)// Retour 1 jour en arrière entre minuit et 5H
		{
			tom-=sts;
		}
		for(sec=59;sec>=0;sec--)
		{
			temp2.Format("0%u",sec);
			temp2=temp2.Right(2);
			temp3.Format("0%u",min);
			temp3=temp3.Right(2);
			temp1=tom.Format("%Y%m%d")+"23"+temp3+temp2;
			if(CFile::GetStatus(datadir+"\\"+temp1,cfs))
				continue;
			else
				break;
		}
		if(sec>=60)
		{
			MessageBox("Initialisation caisse impossible");
			if(infocert)
			{
				FonctionEditeur("Erreur création fichier Data");
			}
			dopen="";
			return 0;
		}
		CTime tam(tim.GetYear(),tim.GetMonth(),tim.GetDay(),23,min,sec,-1);
		while(tam.GetDay()==njour)// Retour 1 jour en arrière entre minuit et 5H
		{
			tam-=sts;
			tim=tam;
		}
	}
	dopen=tim.Format("%Y%m%d%H%M%S");
	opendir=datadir+"\\"+dopen;
	st=tim.Format("Open %d/%m/%Y %H:%M:%S");
	if(!CreateDirectory(opendir,NULL))
	{
		if(GetLastError()==ERROR_ALREADY_EXISTS)
		{
			min--;
			goto retry;
		}
		else
		{
			dopen="";
			return 0;
		}
	}
	temp.Format("%u",(int)fversion);
	st+=";"+temp;
	temp.Format("%u",(int)RAZ+1);
	st+=";"+temp;
	st+=";"+GetConfigString("License","Serial","");
	st+=";"+nom;	
	st+=";"+adresse1;	
	st+=";"+adresse2;	
	st+=";"+siret;	
	st+=";"+naf;	
	st+="\r\n";
	if(dexer=="")
	{
		CTime reftim(tim.GetYear(),atoi(exermois),1,8,0,0,-1);
		if(tim>=reftim)
			dexer=tim.Format("%Y");
		else
			dexer.Format("%u",tim.GetYear()-1);
		WriteConfigString("Infocert","Exercice",dexer);
		se="Exercice file "+dexer+"\r\n"+tim.Format("Open %d/%m/%Y %H:%M:%S");
		temp.Format("%u",(int)fversion);
		se+=";"+temp;
		se+=";"+dexer;
		se+=";"+GetConfigString("License","Serial","");
		se+=";"+nom;	
		se+=";"+adresse1;	
		se+=";"+adresse2;	
		se+=";"+siret;	
		se+=";"+naf;	
		se+="\r\n";
		if(!CWrite(datadir+"\\Exercice.dat",se,0))
		{
			if(infocert)
			{
				FonctionEditeur("Erreur écriture fichier Exercice");
			}
			dopen="";
			return 0;
		}
	}
	if(!CWrite(opendir,st,0))
	{
		if(infocert)
		{
			FonctionEditeur("Erreur ouverture fichier Data");
		}
		dopen="";
		return 0;
	}
	WriteConfigString("Param","Ouverture",dopen);
	temp1=txtm[1];//Disque de sauvegarde absent!
	temp2=txtm[2];//Veuillez contacter votre revendeur.
	InitFileArticle();
	BackupConcertRegistry();
	if(securedir!="")
	{	
		temp=securedir+"\\Data\\"+dopen;
		CreateDirectory(temp,NULL);

		if(CopyFile(opendir+"\\Concert.dat",temp+"\\Concert.dat",FALSE)==0)
		{
			if(infocert)
				FonctionEditeur(temp1);
			MessageBox("Concert.dat : "+temp1+"\n"+temp2);
		}
		temp=securedir+"\\Data";
		if(dexer!=""&&CFile::GetStatus(datadir+"\\Exercice.dat",cfs))
		{
			if(CopyFile(datadir+"\\Exercice.dat",temp+"\\Exercice.dat",FALSE)==0)
			{
				if(infocert)
					FonctionEditeur("Erreur de sauvegarde Exercice sur D");
				MessageBox("Erreur de sauvegarde Exercice sur D");
			}
		}
		if(CopyFile(datadir+"\\Article.dat",temp+"\\Article.dat",FALSE)==0)
		{
			if(infocert)
				FonctionEditeur("Erreur de sauvegarde Article sur D");
			MessageBox("Erreur de sauvegarde Article sur D");
		}
		if(infocert)
		{
			temp.Format("%u",auditfile);
			if(CopyFile(workdir+"\\Auditinfo"+temp+".dat",securedir+"\\Auditinfo"+temp+".dat",FALSE)==0)
			{
				MessageBox(temp1+"\n"+temp2);
			}
		}
	}
	if(backupdir!="")
	{	
		temp=backupdir+"\\Data\\"+dopen;
		CreateDirectory(temp,NULL);
		if(CopyFile(opendir+"\\Concert.dat",temp+"\\Concert.dat",FALSE)==0)
		{
			if(infocert)
				FonctionEditeur(temp1);
			MessageBox("Concert.dat : "+temp1+"\n"+temp2);
		}
		temp=backupdir+"\\Data";
		if(dexer!=""&&CFile::GetStatus(datadir+"\\Exercice.dat",cfs))
		{
			if(CopyFile(datadir+"\\Exercice.dat",temp+"\\Exercice.dat",FALSE)==0)
			{
				if(infocert)
					FonctionEditeur("Erreur de sauvegarde Exercice sur X");
				MessageBox("Erreur de sauvegarde Exercice sur X");
			}
		}
		if(CopyFile(datadir+"\\Article.dat",temp+"\\Article.dat",FALSE)==0)
		{
			if(infocert)
				FonctionEditeur("Erreur de sauvegarde Article sur X");
			MessageBox("Erreur de sauvegarde Article sur X");
		}
		if(CopyFile(securedir+"\\Concert.bra",backupdir+"\\Concert.bra",FALSE)==0)
		{
			if(infocert)
				FonctionEditeur(temp1);
			MessageBox("Concert.bra : "+temp1+"\n"+temp2);
		}
		if(infocert)
		{
			temp.Format("%u",auditfile);
			if(CopyFile(workdir+"\\Auditinfo"+temp+".dat",backupdir+"\\Auditinfo"+temp+".dat",FALSE)==0)
			{
				MessageBox(temp1+"\n"+temp2);
			}
		}
	}
	return 1;
}
void CConcertoDlg::InitFileArticle()
{
	DWORD nbw;
	CString temp;
	//if(master)
	{	// Si c'est une maître on crée un fichier article dans le répertoire Data pour la remontée Office
		int i=1;
		CString buf;
		CString article="";
		i=1;
		while(i<=NART)
		{
			article=article+libel1[i]+";";
			article=article+libel2[i]+";";
			article=article+libelcons[i]+";";
			article=article+libelspect[i]+";";
			temp.Format("%.2f",prix[i]);
			article=article+temp+";";
			temp.Format("%.2f",tva1[i]);
			article=article+temp+";";
			temp.Format("%u",perso[i]);
			article=article+temp+";";
			temp.Format("%u",conso[i]);
			article=article+temp+";";
			temp.Format("%u",entrymode[i]);
			article=article+temp;
			temp.Format(";%.2f",val1[i]);
			article=article+temp;
			if(perso[i]&4)
				temp.Format(";%.2f",tva2[i]);
			else
				temp="";
			article=article+temp;
			if(perso[i]&4)
				temp.Format(";%.2f",val2[i]);
			else
				temp="";
			article=article+temp+"\r\n";
			i++;
		}

		CString client=nom+";";
		client+=adresse1+";";
		client+=adresse2+";";
		client+=siret+";";
		temp.Format("%u",autonews);
		client+=temp+";";
		temp.Format("%u",autoprint);
		client+=temp+";";
		client+=TVA+";";
		client+=cur+";";
		client+=lic[0]+";";
		client+=lic[1]+";";
		client+=lic[2]+";";
		client+=lic[3]+";";
		client+=lic[4]+";";
		client+=lic[5]+";";
		client+=lic[6]+";";
		client+=mentiont+";";
		client+=mentionp+";";
		temp.Format("%u",fprev);
		client+=temp+";";
		temp.Format("%u",nvalplace);
		client+=temp+";";
		temp.Format("%u",valpwd);
		client+=temp+";";
		temp.Format("%u",valpage);
		client+=temp+";";
		client+=langue+";";
		client+=pays+";";
		client+=serveur+";";
		temp.Format("%u",afmode);
		client+=temp+";";
		temp.Format("%u",horaire);
		client+=temp+";";
		temp.Format("%u",valhor);
		client+=temp+";";
		client+=naf;
		CString tpage="";
		i=0;
		while(i<20)
		{
			tpage=tpage+pag[i]+";"+jour[i]+"\r\n";
			i++;
		}
		buf="*ARTICLE*\r\n"+article+"*CLIENT*\r\n"+client+"\r\n*PAGE*\r\n"+tpage;
	retry1:;
		HANDLE hf=CreateFile(datadir+"\\Article.dat",GENERIC_READ|GENERIC_WRITE,0,NULL,CREATE_NEW,FILE_ATTRIBUTE_NORMAL,NULL);
		if(hf!=INVALID_HANDLE_VALUE)
		{
			WriteFile(hf,buf.GetBuffer(buf.GetLength()),buf.GetLength(),&nbw,NULL);
			CloseHandle(hf);
		}
		else
		{
			Sleep(100);
			DeleteFile(datadir+"\\Article.dat");
			goto retry1;
		}
	}
}

int CConcertoDlg::CloseCaisse(CTime tim)
{	// Fonction de clôture d'une caisse dans les résultats avec en paramètre la date de clôture
	CString temp;
	CString extrait;
	CString temp1;
	CString temp2;
	CString temp3;
	CString clotext;
	CString sign;
	CString archtva;
	CString num;
	CString px;
	CString vl1;
	CString tv1;
	CString vl2;
	CString tv2;
	CString archtxt;
	CString zipliste="Liste des fichiers\r\n";
	CZipArchive zip;
	HANDLE hf;
	DWORD len;
	CFileFind cfz;
	BOOL resz;
	FILEINFO fi;
	CString st=tim.Format("Close %d/%m/%Y %H:%M:%S");
	temp.Format("%u",RAZ);
	// on ajoute la ligne de fermeture avec le N° de GTZ et le cumul de chiffe d'affaire
	st+=" NGTZ "+temp;
	temp.Format("%.2f",GTP);
	st+=" GTP "+temp;
	temp.Format("%.2f",GTZ);
	st+=" GTZ "+temp;
	temp.Format("%.2f",GTA);
	st+=" GTA "+temp;
	int i=0;
	archtxt="";
	archtva="";

	//Close 03/05/2015 16:44:54 NGTZ 6 GTP 59335.00 GTZ 27000.0027000.00%;4500.00|
	while(i<10)
	{
		if(tvaca[i]!=0)
		{
			temp.Format("%.2f",tvaca[i]);
			st+=";"+temp+";";
			archtxt+=temp+";";
			archtva+=temp+",";
			temp.Format("%.2f",catva[i]);//-(catva[i]/(1+(tvaca[i]/100))));
			st+=temp;
			temp.Format("%.2f",catva[i]);
			archtxt+=temp+";";
			archtva+=temp+",";
		}
		i++;
	}
	temp1.Format("GTZ %.2f",ca);
	archtxt+=temp1+";";
	temp1=tim.Format("%Y%m%d%H%M%S");
	archtxt+=temp1+";";
	archtxt+="POSTE "+poste+";";
	archtxt+="ArchivePeriode";
	if(infocert)
	{
		archtva=archtva.Left(archtva.GetLength()-1);
		temp1=archtva;
		temp1.Replace(".","");
		spart[0]=temp1;
		temp1.Format("%.2f",ca);
		temp1.Replace(".","");
		spart[1]=temp1;
		temp1=tim.Format("%Y%m%d%H%M%S");
		spart[2]=temp1;
		temp1.Format("%u",RAZ);
		spart[3]=temp1;
		spart[4]=sgtpz;
		sign=Sign(4);
		st+="|"+sign+"\r\n";
	}
	else
		st+="\r\n";
	clotext=st;
	st+="Start Articles\r\n";
	// On crée une rubrique article à rajouter après les ventes pour pouvoir libeller les lignes de vente dans la centrale
	i=1;
	do
	{
		num.Format("0%u",i);
		num=num.Right(2);
		px.Format("%.2f",prix[i]);
		vl1.Format("%.2f",val1[i]);
		vl2.Format("%.2f",val2[i]);
		tv1.Format("%.2f",tva1[i]);
		tv2.Format("%.2f",tva2[i]);

		if(libel1[i]!=""||libel2[i]!="")
		{
			temp= num+"\t"+libel1[i]+"\t"+libel2[i]+"\t"+px+"\t"+tv1+"\t"+tv2+"\t"+vl1+"\t"+vl2+"\r\n";
			st+=temp;
		}
		i++;
	}
	while(i<=NART);
	st+="End Articles\r\n";
	if(master)
	{
		DeleteFile(controldir+"\\Place.dat");
		DeleteFile(securedir+"\\Control\\Place.dat");
		DeleteFile(backupdir+"\\Control\\Place.dat");
	}
	opendir=datadir+"\\"+dopen;
	if(CWrite(opendir,st,1))
	{
		if(infocert)
		{
			sgtpz=sign;
			WriteConfigString("Infocert","SignGtpz",sgtpz);
		}
		st=dopen+";"+clotext;
		if(!CWrite(datadir+"\\Exercice.dat",st,1))
		{
			if(infocert)
			{
				FonctionEditeur("Erreur écriture fichier Exercice");
			}
			//return 0;
		}

	}
	else
	{
		if(infocert)
		{
			FonctionEditeur("Erreur écriture fichier Data");
		}
		return 0;
	}
	if(infocert)
	{
		temp1=archtva;
		temp1.Replace(".","");
		temp1.Replace(" ","");
		spart[0]=temp1;
		temp1.Format("%.2f",ca);
		temp1.Replace(".","");
		spart[1]=temp1;
		temp1=tim.Format("%Y%m%d%H%M%S");
		spart[2]=temp1;
		spart[3]=poste;
		spart[4]="ArchivePeriode";
		spart[5]=sarchp;
		sign=Sign(6);
		sarchp=sign;
		WriteConfigString("Infocert","SignArchPeriode",sarchp);
		archtxt+="|"+sign+"\r\n";
	}
	else
		archtxt+="\r\n";
	temp1=txtm[1];//Disque de sauvegarde absent!
	temp2=txtm[2];//Veuillez contacter votre revendeur.
	Sleep(300);// Sauvegarde du fichier sur clé de sauvegarde
	if(securedir!="")
	{	// on sauvegarde sur le disque D le fichier clôturé
		temp=securedir+"\\Data\\"+dopen;
		CreateDirectory(temp,NULL);
		if(CopyFile(opendir+"\\Concert.dat",temp+"\\Concert.dat",FALSE)==0)
		{
			if(infocert)
				FonctionEditeur("Erreur de sauvegarde D");
			MessageBox("Erreur de sauvegarde D");
		}
		temp=securedir+"\\Data";
		if(CopyFile(datadir+"\\Exercice.dat",temp+"\\Exercice.dat",FALSE)==0)
		{
			if(infocert)
				FonctionEditeur("Erreur de sauvegarde D");
			MessageBox("Erreur de sauvegarde D");
		}
		if(CopyFile(datadir+"\\Article.dat",temp+"\\Article.dat",FALSE)==0)
		{
			if(infocert)
				FonctionEditeur("Erreur de sauvegarde D");
			MessageBox("Erreur de sauvegarde D");
		}
		if(infocert)
		{
			temp.Format("%u",auditfile);
			if(CopyFile(workdir+"\\Auditinfo"+temp+".dat",securedir+"\\Auditinfo"+temp+".dat",FALSE)==0)
			{
				MessageBox(temp1+"\n"+temp2);
			}
		}
	}
	if(backupdir!="")
	{	// on sauvegarde sur la clé le fichier clôturé
		temp=backupdir+"\\Data\\"+dopen;
		CreateDirectory(temp,NULL);
		if(CopyFile(opendir+"\\Concert.dat",temp+"\\Concert.dat",FALSE)==0)
		{
			if(infocert)
				FonctionEditeur(temp1);
			MessageBox(temp1+"\n"+temp2);
		}
		temp=backupdir+"\\Data";
		if(CopyFile(datadir+"\\Exercice.dat",temp+"\\Exercice.dat",FALSE)==0)
		{
			if(infocert)
				FonctionEditeur("Erreur de sauvegarde X");
			MessageBox("Erreur de sauvegarde X");
		}
		if(CopyFile(datadir+"\\Article.dat",temp+"\\Article.dat",FALSE)==0)
		{
			if(infocert)
				FonctionEditeur("Erreur de sauvegarde X");
			MessageBox("Erreur de sauvegarde X");
		}
		if(infocert)
		{
			temp.Format("%u",auditfile);
			if(CopyFile(workdir+"\\Auditinfo"+temp+".dat",backupdir+"\\Auditinfo"+temp+".dat",FALSE)==0)
			{
				MessageBox(temp1+"\n"+temp2);
			}
		}
	}
	CloturePeriode();
	zip.Open(datadir+"\\Archive fiscal periode "+dopen+" Poste  "+poste+".zip", CZipArchive::zipCreate);
	// set the compression method
	zip.SetPassword("65748392",-1);
	zip.SetEncryptionMethod(CZipCryptograph::encWinZipAes256);
	zip.AddNewFile(opendir+"\\Concert.dat",dopen+"\\Concert.dat",-1, zip.zipsmSafeSmart, 65536);
	zipliste+=dopen+"\\Concert.dat\r\n";
	zip.AddNewFile(datadir+"\\Exercice.dat",-1,false, zip.zipsmSafeSmart, 65536);
	zipliste+="Exercice.dat\r\n";
	zip.AddNewFiles(workdir,"Auditinfo*.dat",false,-1,true, zip.zipsmSafeSmart, 65536);
	resz=cfz.FindFile(workdir+"\\Auditinfo*.dat",0);
	while(resz)
	{
		resz=cfz.FindNextFileA();
		if (cfz.IsDots())
		 continue;
		if(cfz.IsDirectory())
		 continue;
		zipliste+=cfz.GetFileName()+"\r\n";
	}
	cfz.Close();
	zipliste+="Archive.dat\r\nDonnées archive\r\n";
	if((hf=CreateFile(archdir+"\\Archive.dat",GENERIC_READ|GENERIC_WRITE,0,NULL,CREATE_NEW,FILE_ATTRIBUTE_NORMAL,NULL))!=INVALID_HANDLE_VALUE)
	{
		archtxt=zipliste+archtxt;
		WriteFile(hf,archtxt.GetBuffer(archtxt.GetLength()),archtxt.GetLength(),&len,NULL);
		CloseHandle(hf);
	}
	zip.AddNewFile(archdir+"\\Archive.dat",-1,false, zip.zipsmSafeSmart, 65536);

	temp="Veuillez contacter la société Dine O Quick au 01 46 42 18 61 pour toute info complémentaire.\r\n"+sarchp;
	zip.SetGlobalComment(temp,ZIP_DEFAULT_CODE_PAGE);
	zip.FlushBuffers();
	zip.Close();
	if(CopyFile(datadir+"\\Archive fiscal periode "+dopen+" Poste  "+poste+".zip",backupdir+"\\data\\Archive fiscal periode "+dopen+" Poste  "+poste+".zip",FALSE)==0)
	{
		if(infocert)
			FonctionEditeur("Erreur de sauvegarde X");
		MessageBox("Erreur de sauvegarde X");
	}
	if(CopyFile(datadir+"\\Archive fiscal periode "+dopen+" Poste  "+poste+".zip",securedir+"\\data\\Archive fiscal periode "+dopen+" Poste  "+poste+".zip",FALSE)==0)
	{
		if(infocert)
			FonctionEditeur("Erreur de sauvegarde D");
		MessageBox("Erreur de sauvegarde D");
	}
	DeleteFile(archdir+"\\Archive.dat");
	ArchivePeriode();
	Sleep(100);

	CString filesize;
	CString filetime;
	fi=GetFileInfo(opendir+"\\concert.dat");
	filesize.Format("%u",fi.size);	
	filetime.Format("%lld",fi.time);
	temp.Format("%u;",catidx);
	temp+="Data\\"+dopen+"\\Concert.dat;"+filesize+";"+filetime+"\r\n";
	CWrite(sysdir+"\\csat.avs",temp,1);
	if(filesize=="0"&&filetime=="0")
	{
		FonctionEditeur("Erreur accès fichier Data\\"+dopen+"\\Concert.dat pour inscription catalogue");
	}
	catidx++;

	fi=GetFileInfo(datadir+"\\Archive fiscal periode "+dopen+" Poste  "+poste+".zip");
	filesize.Format("%u",fi.size);	
	filetime.Format("%lld",fi.time);
	temp.Format("%u;",catidx);
	temp+="Data\\Archive fiscal periode "+dopen+" Poste  "+poste+".zip;"+filesize+";"+filetime+"\r\n";
	CWrite(sysdir+"\\csat.avs",temp,1);
	catidx++;
	temp.Format("%u;",catidx);
	WriteConfigString("Infocert","Catidx",temp);

	// On efface la date d'ouverture
	histpath=opendir;
	dopen="";
	GTA=GTZ;
	temp.Format("%u",(int)(GTA*100));
	WriteConfigString("Param","GTA",temp);// Mise en mémoire de la période précédente
	GTZ=0;
	WriteConfigString("Param","GTZ","0");
	WriteConfigString("Param","Ouverture","");
	// On sauvegarde la base de registre dans la clé
	BackupConcertRegistry();
	BackupConcertControl();
	if(backupdir!="")
	{	// on sauvegarde sur la clé la base dregistre
		if(CopyFile(securedir+"\\Concert.bra",backupdir+"\\Concert.bra",FALSE)==0)
		{
			if(infocert)
				FonctionEditeur(temp1);
			MessageBox(temp1+"\n"+temp2);
		}
	}
	return 1;
}

void CConcertoDlg::BackupConcertControl()
{	// Sauvegarde des controles sur la clé
	CFileFind cfd;
	BOOL statd;
	CFileStatus cfsource;
	CFileStatus cftarget;
	CString target;
	CString source;
	statd=cfd.FindFile(controldir+"\\*.*");
	while(statd)
	{
		statd=cfd.FindNextFile();
		if(cfd.IsDots())
			continue;
		if(cfd.IsDirectory()&&CFile::GetStatus(cfd.GetFilePath()+"\\Control.dat",cfsource))
		{
			target=backupdir+"\\Control\\"+cfd.GetFileName()+"\\Control.dat";
			CFile::GetStatus(target,cftarget);
			if(cftarget.m_size!=cfsource.m_size)
			{
				CopyFile(cfd.GetFilePath()+"\\Control.dat",target,FALSE);
			}
			continue;
		}
		if(master&&cfd.GetFileName()=="Place.dat")
		{
			target=backupdir+"\\Control\\Place.dat";
			CopyFile(cfd.GetFilePath(),target,FALSE);
		}
	}
	cfd.Close();
}

void CConcertoDlg::BackupConcertRegistry()
{	// Sauvegarde de la base de registre sur le disque D
	HKEY hk;
	HANDLE hToken; 
	TOKEN_PRIVILEGES tkp; 
	int i;
	if (!OpenProcessToken(GetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) 
		goto ERREUR_REGISTRE_PRIVILEGE; 
 
	LookupPrivilegeValue(NULL, SE_BACKUP_NAME,&tkp.Privileges[0].Luid); 
 
	tkp.PrivilegeCount = 1;  // one privilege to set    
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED; 
	AdjustTokenPrivileges(hToken, FALSE, &tkp, 0,(PTOKEN_PRIVILEGES)NULL, 0); 
    if (GetLastError() != ERROR_SUCCESS) 
		goto ERREUR_REGISTRE_ADJUST_PRIVILEGE;; 

	if(RegOpenKeyEx(HKEY_CURRENT_USER,"Software\\BARMATIC France\\Concert",0,KEY_READ,&hk)!=ERROR_SUCCESS)
		goto ERREUR_REGISTRE_OPEN;; 
retry:;
	if((i=RegSaveKeyEx(hk,securedir+"\\Concert0.bra",NULL,REG_LATEST_FORMAT))!=ERROR_SUCCESS)
	{
		DeleteFile(securedir+"\\Concert0.bra");
		goto retry;
	}
	RegCloseKey(hk);

	//CopyFile(backupdir+"\\Concert.bra",backupdir+"\\Concert.bak",FALSE);
	//Sleep(100);
	CopyFile(securedir+"\\Concert0.bra",securedir+"\\Concert.bra",FALSE);
	Sleep(100);
	DeleteFile(securedir+"\\Concert0.bra");
	goto FIN;
ERREUR_REGISTRE_PRIVILEGE:;
	if(infocert)
		FonctionEditeur("Erreur token d'accès au registre");
	MessageBox("Erreur d'accès au registre privilege");
	goto FIN;
ERREUR_REGISTRE_ADJUST_PRIVILEGE:;
	if(infocert)
		FonctionEditeur("Erreur adjust d'accès au registre");
	MessageBox("Erreur adjust au registre privilege");
	goto FIN;
ERREUR_REGISTRE_OPEN:;
	if(infocert)
		FonctionEditeur("Erreur open d'accès au registre");
	MessageBox("Erreur open au registre open");
FIN:;
	CloseHandle(hToken);
	CopyFile(sysdir+"\\csat.avs",securedir+"\\Cat.dat",FALSE);
	CopyFile(sysdir+"\\csat.avs",backupdir+"\\Cat.dat",FALSE);
	CopyFile(configpath,securedir+"\\Config.dat",FALSE);
	CopyFile(configpath,backupdir+"\\Config.dat",FALSE);
}

CTime CConcertoDlg::DirToDate(CString date)
{
	CString temp;
	int jour;
	int mois;
	int an;
	int heure;
	int minute;
	int seconde;
	an=atoi(date.Left(4));
	date=date.Right(date.GetLength()-4);
	mois=atoi(date.Left(2));
	date=date.Right(date.GetLength()-2);
	jour=atoi(date.Left(2));
	date=date.Right(date.GetLength()-2);
	heure=atoi(date.Left(2));
	date=date.Right(date.GetLength()-2);
	minute=atoi(date.Left(2));
	date=date.Right(date.GetLength()-2);
	seconde=atoi(date.Left(2));
	CTime tim(an,mois,jour,heure,minute,seconde,-1);
	return tim;
}

void CConcertoDlg::OnPaint()
{
	CPaintDC dc(this); // contexte de périphérique pour la peinture
	CRect rect;
	GetClientRect(&rect);
	if (IsIconic())
	{

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Centrer l'icône dans le rectangle client
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Dessiner l'icône
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{	// on redessine le fond de la fenêtre
		CDC* pDC=&dc;
		CDialog::OnPaint();
		DrawWindowGeneral(&dc);//pDC);
		if(wsel==0)
		{
		}
	}
}

// Le système appelle cette fonction pour obtenir le curseur à afficher lorsque l'utilisateur fait glisser
//  la fenêtre réduite.
HCURSOR CConcertoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CConcertoDlg::OnDestroy()
{	// On rend visible la barre de tâche et le bouton démarrer
	CString temp;
	CString temp1;	
	CString temp2;
	CWnd* pbar;
	KillTimer(2);
	KillTimer(4);
	KillTimer(5);
	KillTimer(8);
	KillTimer(11);
	KillTimer(12);
	KillTimer(13);
	temp1=txtm[1];//Disque de sauvegarde absent!
	temp2=txtm[2];//Veuillez contacter votre revendeur.
	if(infocert==1)
		StopTerminal();
	if(infocert)
	{
		temp.Format("%u",auditfile);
		if(CopyFile(workdir+"\\Auditinfo"+temp+".dat",backupdir+"\\Auditinfo"+temp+".dat",FALSE)==0)
		{
			MessageBox(temp1+"\n"+temp2);
		}
		if(CopyFile(workdir+"\\Auditinfo"+temp+".dat",securedir+"\\Auditinfo"+temp+".dat",FALSE)==0)
		{
			MessageBox(temp1+"\n"+temp2);
		}
	}
	if((pbar=FindWindow("Shell_TrayWnd",0))!= NULL)
		pbar->ShowWindow(1);
	if((pbar=FindWindow("Button",txtc[2]))!=NULL)//Démarrer
		pbar->ShowWindow(1);
	if(hrun)
	{
		if(CloseHandle(hrun))
		{
			hrun=NULL;
		}
	}
	DeleteFile(controldir+"\\Run.dat");
	DeleteFile(controldir+"\\Status.dat");
	CDialog::OnDestroy();

}

void CConcertoDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	CDialog::OnLButtonDown(nFlags, point);
}

void CConcertoDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	CDialog::OnMouseMove(nFlags, point);
}
int CConcertoDlg::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	KillTimer(11);
	if(SCR&&FTEM==0)
	{
		TerminateThread(hGetMCIModeThread,0);
		CloseHandle(hGetMCIModeThread);
		MCIWndClose(SCR);
		MCIWndDestroy(SCR);
		SCR=NULL;
		InterlockedExchange(&FTEM,1);
		Sleep(300);
		DrawWindowConcert();
		if(master&&wsel==1)
		{
			if(HRSG)
				tgate.ShowWindow(fgate);
			tnet.ShowWindow(1);
			if(alone==0)
				tnet.SetWindowTextA("HRSR");
			else
				if(alone==1)
					tnet.SetWindowTextA("HRAU");
		}
	}
	return CDialog::OnMouseActivate(pDesktopWnd, nHitTest, message);
}

void CConcertoDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	CDialog::OnLButtonUp(nFlags, point);
}

void CConcertoDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	CDialog::OnRButtonDown(nFlags, point);
}

BOOL CConcertoDlg::OnEraseBkgnd(CDC* pDC)
{
	return CDialog::OnEraseBkgnd(pDC);
}
void CConcertoDlg::TestClotureAnnuelle()
{
	CZipArchive zip;
	CString olddexer;
	CString temp;
	CString temp1;
	CString sign;
	CString extrait;
	CString archtxt;
	CString targetdir;
	CString targetdirsecure;
	CString targetdirbackup;
	CString source;
	CString target;
	CString tdir;
	CString spath;
	CString archtva;
	CString buf;
	CString ngtz;
	CString gtp;
	CString st;
	CString zipliste="Liste des fichiers\r\n";
	int result;
	int resz;
	int corerror=0;
	CFileFind ff;
	CFileFind cff;
	CFileFind cfz;
	HANDLE hf;
	DWORD len;
	FILEINFO fi;
	int i;
	int idx;
	int idy;
	int k;
	int x;
	double xcatva[10];
	double xtvaca[10];
	double cumul=0;//cumul exercice
	double cumulp=0;// cumul perpétuel
	double cumult=0;// cumul TVA
	CTime tim=CTime::GetCurrentTime();
	i=0;
	while(i<10)
	{
		xcatva[i]=0;
		xtvaca[i]=0;
		i++;
	}
	if(dexer!=""&&fexeran==0)// teste si le traitement est déjà en cours et que le mois d'exercice est déjà valide
	{
		InterlockedExchange(&fexeran,1);// Met un flag indiquant que le traitement est en cours
		int mois;
		int an;
		mois=atoi(exermois);
		an=atoi(dexer)+1;
		CTime timexer(an,mois,1,8,0,0,-1);
		CTime timref(tim.GetYear(),tim.GetMonth(),tim.GetDay(),tim.GetHour(),0,0,-1);
		temp=timexer.Format(" exr = %d/%m/%Y %H:%M:%S");
		temp1=timref.Format(" ref = %d/%m/%Y %H:%M:%S");
		//MessageBox(temp+temp1);

		if(timref>=timexer&&dopen!="")// test les dates et si la période est ouverte
		{
			CMessage* pdlg;
			pdlg= new CMessage(this);
			pwlog=pdlg;

			temp1=txtm[69];//
			pdlg->mes1=temp1;//La clôture annuelle doit être réalisée.
			temp1=txtm[70];
			pdlg->mes2=temp1;//La billetterie va être clôturée.
			temp1=txtm[6];
			pdlg->mes3=temp1;//Taper OK pour valider
			pdlg->mode=1;
			if(pdlg->DoModal()==IDOK)
			{
				hist=0;
				flagraz=1;
				FillTicketList(opendir);
				OnBnClickedCashClose();
				flagraz=0;
			}
			delete pdlg;
			pwlog=NULL;
			InterlockedExchange(&fexeran,2);
		}
		else
			if(timref<timexer)// si les dates ne sont pas arrivées à échéance on abandonne
				InterlockedExchange(&fexeran,0);
		if(timref>=timexer&&fexeran>0)
		{
			targetdir=archdir+"\\"+dexer;
			targetdirsecure=securedir+"\\Archive"+"\\"+dexer;
			targetdirbackup=backupdir+"\\Archive"+"\\"+dexer;
			// Prépare les répertoires d'archivage
			CreateDirectory(targetdir,NULL);
			CreateDirectory(targetdir+"\\Data",NULL);
			CreateDirectory(securedir+"\\Archive",NULL);
			CreateDirectory(securedir+"\\Archive"+"\\"+dexer,NULL);
			CreateDirectory(backupdir+"\\Archive",NULL);
			CreateDirectory(backupdir+"\\Archive"+"\\"+dexer,NULL);
			CreateDirectory(targetdirsecure+"\\Data",NULL);
			CreateDirectory(targetdirbackup+"\\Data",NULL);
			st=tim.Format("Close %d/%m/%Y %H:%M:%S ");//Fermeture de l'exercice et préparation de la signature
			result=cff.FindFile(datadir+"\\*.*",0);
			sl.ResetContent();
			while(result)
			{
				result=cff.FindNextFile();
				if (cff.IsDots())
				 continue;
				if (cff.IsDirectory())
				{
					sl.AddString(cff.GetFileName());
				}
			}
			cff.Close();
			for(i=0;i<sl.GetCount();i++)// Analyse des dates d'ouvertures périodes
			{
				sl.GetText(i,spath);
				temp=spath;//.Mid(spath.ReverseFind('\\')+1);
				sl.SetItemData(i,10);
				tdir=datadir+"\\"+spath;
				buf=CRead(tdir);
				if(buf=="")
				{
					st="Corrompu";
					corerror++;
				}
				else
				{	// récupération date de chaque cloture
					FillTicketList(tdir);						
					x=0;
					while(x<10)
					{
						k=0;
						while(k<10)
						{// récupérarion des TVA de chaque cloture
							if(tvaca[x]==xtvaca[k])
							{
								break;
							}
							k++;
						}
						if(k>=10)
						{
							k=0;
							while(k<10)
							{
								if(xtvaca[k]==0)
								{
									xtvaca[k]=tvaca[x];
									break;
								}
								k++;
							}
						}
						xcatva[k]+=catva[x];
						x++;
					}
					temp="";
					idx=buf.Find("Close",0);
					idy=buf.Find("\r\n",idx);
					temp1=buf.Mid(idx,idy-idx);
					temp1.Replace("GTZ","GTP");
					temp1.Replace("RAZ","NGTZ");
					if(cesver<459)
						idy=buf.Find("GTZ",idx);
					else
						idy=buf.Find("GTP",idx);
					idx=idy+4;
					idy=buf.Find("\r\n",idx);
					gtp=buf.Mid(idx,idy-idx);
					if(atof(gtp)>cumulp)// récupération du cumul perpétuel le plus élevé
						cumulp=atof(buf.Mid(idx,idy-idx));
				}
			}
//Close 24/06/2015 16:54:07 NGTZ 2 GTP 95.00 GTZ 10.00 GTA 10.00;20.00%;1.67|

			cumul=0;
			for(x=0;x<10;x++)// récupération des éléments de cloture annuelle pour la signature
				if(xcatva[x]>0)
					cumul+=xcatva[x];
			temp1.Format("%.2f",cumulp);
			st+="NGTZ "+dexer+" GTP "+temp1;// N° grand total exercice
			temp1.Format("GTZ %.2f",cumul);
			st+=" "+temp1;// cumul grand total exercice
			temp1.Format("GTA %.2f",GTE);
			st+=" "+temp1;// cumul grand total exercice
			WriteConfigString("Param","GTE",temp1);// Mise en mémoire de la période annuelle
			archtxt=archtva="";
			
			for(x=0;x<10;x++)
			{
				if(xtvaca[x]>0)
				{
					temp.Format("%.2f",xtvaca[x]);
					temp1.Format("%.2f",xcatva[x]);
					st+=";"+temp+";"+temp1;
					archtva=temp+","+temp1+",";
					archtxt+=temp+";"+temp1+";";
				}
			}
			temp1.Format("GTZ %.2f",cumul);
			archtxt+=temp1+";";
			archtxt+=tim.Format("%Y%m%d%H%M%S");
			archtxt+=";POSTE "+poste+";ArchiveExercice";
			if(infocert)// signature de la ligne
			{
				
				cumult=0;
				for(x=0;x<10;x++)
				{
					if(xcatva[x]>0)
						cumult+=xcatva[x];
				}		
				archtva.Replace(".","");
				archtva=archtva.Left(archtva.GetLength()-1);
				spart[0]=archtva;
				temp1.Format("%.2f",cumul);
				temp1.Replace(".","");
				spart[1]=temp1;
				temp1=tim.Format("%Y%m%d%H%M%S");
				spart[2]=temp1;
				spart[3]=dexer;
				spart[4]=sgtpa;
				sign=Sign(5);
				sgtpa=sign;
				WriteConfigString("Infocert","SignGtpa",sgtpa);
			}
			else
				sign=sgtpa="";
			st+="|"+sign+"\r\n";
			CWrite(datadir+"\\Exercice.dat",st,1);
			// Déplacement des fichiers dans le répertoire de l'archive de l'année d'exercice
			tl.ResetContent();
			sl.ResetContent();
			dl.ResetContent();
			// Prépare la liste des fichiers à archiver
			sl.SetItemData(sl.AddString(datadir+"\\Exercice.dat"),0);
			tl.SetItemData(tl.AddString(targetdir+"\\Data\\Exercice.dat"),0);
			sl.SetItemData(sl.AddString(datadir+"\\Article.dat"),0);
			tl.SetItemData(tl.AddString(targetdir+"\\Data\\Article.dat"),0);
			sl.SetItemData(sl.AddString(datadir+"\\Article.dat"),0);
			tl.SetItemData(tl.AddString(targetdirsecure+"\\Data\\Article.dat"),0);
			sl.SetItemData(sl.AddString(datadir+"\\Exercice.dat"),0);
			tl.SetItemData(tl.AddString(targetdirsecure+"\\Data\\Exercice.dat"),0);
			sl.SetItemData(sl.AddString(datadir+"\\Article.dat"),0);
			tl.SetItemData(tl.AddString(targetdirbackup+"\\Data\\Article.dat"),0);
			sl.SetItemData(sl.AddString(datadir+"\\Exercice.dat"),0);
			tl.SetItemData(tl.AddString(targetdirbackup+"\\Data\\Exercice.dat"),0);
			result =ff.FindFile(datadir+"\\*.*",0 );
			while(result)
			{
				result=ff.FindNextFile();
				if (ff.IsDots())
				 continue;
				if(ff.IsDirectory())
				{
					CreateDirectory(targetdirbackup+"\\Data\\"+ff.GetFileName(),NULL);
					CreateDirectory(targetdirsecure+"\\Data\\"+ff.GetFileName(),NULL);
					CreateDirectory(targetdir+"\\Data\\"+ff.GetFileName(),NULL);
					sl.SetItemData(sl.AddString(ff.GetFilePath()+"\\Concert.dat"),0);
					tl.SetItemData(tl.AddString(targetdir+"\\Data\\"+ff.GetFileName()+"\\Concert.dat"),0);
					dl.SetItemData(dl.AddString(ff.GetFileName()),0);

					sl.SetItemData(sl.AddString(ff.GetFilePath()+"\\Concert.dat"),0);
					tl.SetItemData(tl.AddString(targetdirbackup+"\\Data\\"+ff.GetFileName()+"\\Concert.dat"),0);

					sl.SetItemData(sl.AddString(ff.GetFilePath()+"\\Concert.dat"),0);
					tl.SetItemData(tl.AddString(targetdirsecure+"\\Data\\"+ff.GetFileName()+"\\Concert.dat"),0);
				}
				if(ff.GetFileName().Find(".zip",0)!=-1)
				{
					sl.SetItemData(sl.AddString(datadir+"\\"+ff.GetFileName()),0);
					tl.SetItemData(tl.AddString(targetdir+"\\Data\\"+ff.GetFileName()),0);

					sl.SetItemData(sl.AddString(datadir+"\\"+ff.GetFileName()),0);
					tl.SetItemData(tl.AddString(targetdirbackup+"\\Data\\"+ff.GetFileName()),0);

					sl.SetItemData(sl.AddString(datadir+"\\"+ff.GetFileName()),0);
					tl.SetItemData(tl.AddString(targetdirsecure+"\\Data\\"+ff.GetFileName()),0);
				}
			}
			ff.Close();
			for(i=0;i<sl.GetCount();i++) // Copie la liste des fichiers d'archivage
			{
				sl.GetText(i,source);
				tl.GetText(i,target);
				tl.SetItemData(i,CopyFile(source,target,FALSE));
			}
			result=1;
			for(i=0;i<tl.GetCount();i++)// test si des erreurs de copie ont été détectées
			{
				if(tl.GetItemData(i)==0)
				{
					result=0;
					if(infocert)
						FonctionEditeur("Erreur d'archivage");
					MessageBox("Erreur d'archivage\nVeuillez recommencer");
					break;
				}
			}
			if(result)// Si pas d'erreur de copie on peut effacer les fichiers source
			{
				for(i=0;i<sl.GetCount();i++)
				{
					sl.GetText(i,source);
					DeleteFile(source);
				}
				for(i=0;i<dl.GetCount();i++)
				{
					dl.GetText(i,source);
					temp=workdir+"\\Data\\"+source;
					DeleteFile(temp+"\\Concert.dat");
					RemoveDirectory(temp);
					temp=securedir+"\\Data\\"+source;
					DeleteFile(temp+"\\Concert.dat");
					RemoveDirectory(temp);
					temp=backupdir+"\\Data\\"+source;
					DeleteFile(temp+"\\Concert.dat");
					RemoveDirectory(temp);
				}
				DeleteFile(workdir+"\\Data\\Article.dat");
				DeleteFile(workdir+"\\Data\\Exercice.dat");
				DeleteFile(backupdir+"\\Data\\Article.dat");
				DeleteFile(backupdir+"\\Data\\Exercice.dat");
				DeleteFile(securedir+"\\Data\\Article.dat");
				DeleteFile(securedir+"\\Data\\Exercice.dat");
				if(infocert)
					ClotureExercice();// marquage de fin d'exercice dans la piste d'audit
				if(infocert)
				{
					spart[0]=archtva;
					temp1.Format("%.2f",cumul);
					temp1.Replace(".","");
					spart[1]=temp1;
					temp1=tim.Format("%Y%m%d%H%M%S");
					spart[2]=temp1;
					spart[3]=poste;//sgtpz;
					spart[4]="ArchiveExercice";
					spart[5]=sarche;
					sign=Sign(7);
					sarche=sign;
					WriteConfigString("Infocert","SignArchExercice",sarche);
					archtxt+="|"+sign+"\r\n";
				}
				else
					archtxt+="\r\n";
				ArchiveExercice();
				zip.Open(archdir+"\\"+dexer+"\\Archive fiscal exercice "+dexer+" "+poste+".zip", CZipArchive::zipCreate);
				// set the compression method
				zip.SetPassword("65748392",-1);
				zip.SetEncryptionMethod(CZipCryptograph::encWinZipAes256);
				if(zip.AddNewFiles(archdir+"\\"+dexer,"*.dat",true,-1,true, zip.zipsmSafeSmart, 65536))
				{
					resz=cfz.FindFile(archdir+"\\"+dexer+"\\Data\\*.*",0);
					while(resz)
					{
						resz=cfz.FindNextFileA();
						if (cfz.IsDots())
						 continue;
						if(cfz.IsDirectory())
							zipliste+="Data\\"+cfz.GetFileName()+"\\Concert.dat\r\n";
					}
					cfz.Close();
					resz=cfz.FindFile(archdir+"\\"+dexer+"\\Data\\*.dat",0);
					while(resz)
					{
						resz=cfz.FindNextFileA();
						if (cfz.IsDots())
						 continue;
						if(cfz.IsDirectory())
						 continue;
						zipliste+="Data\\"+cfz.GetFileName()+"\r\n";
					}
					cfz.Close();
				}
				zip.AddNewFiles(workdir,"Auditinfo*.dat",false,-1,true, zip.zipsmSafeSmart, 65536);
				resz=cfz.FindFile(workdir+"\\Auditinfo*.dat",0);
				while(resz)
				{
					resz=cfz.FindNextFileA();
					if (cfz.IsDots())
					 continue;
					if(cfz.IsDirectory())
					 continue;
					zipliste+=cfz.GetFileName()+"\r\n";
				}
				cfz.Close();
				zipliste+="Archive.dat\r\nDonnées archive\r\n";
				if((hf=CreateFile(archdir+"\\Archive.dat",GENERIC_READ|GENERIC_WRITE,0,NULL,CREATE_NEW,FILE_ATTRIBUTE_NORMAL,NULL))!=INVALID_HANDLE_VALUE)
				{
					archtxt=zipliste+archtxt;
					WriteFile(hf,archtxt.GetBuffer(archtxt.GetLength()),archtxt.GetLength(),&len,NULL);
					CloseHandle(hf);
				}
				zip.AddNewFile(archdir+"\\Archive.dat",-1,false, zip.zipsmSafeSmart, 65536);
				temp="Veuillez contacter la société Dine O Quick au 01 46 42 18 61 pour toute info complémentaire.\r\n"+sarche;
				zip.SetGlobalComment(temp,ZIP_DEFAULT_CODE_PAGE);
				zip.FlushBuffers();
				zip.Close();
				DeleteFile(archdir+"\\Archive.dat");
				olddexer=dexer;
				int ann=atoi(dexer)+1;
				dexer.Format("%u",ann);; // Mise à jour de l'année d'exercice
				WriteConfigString("Infocert","Exercice",dexer);
				temp.Format("%u",auditfile);// et sauvegarde de la piste dans le dossier d'archivage
				CopyFile(workdir+"\\Auditinfo"+temp+".dat",targetdirbackup+"\\Auditinfo"+temp+".dat",FALSE);
				CopyFile(workdir+"\\Auditinfo"+temp+".dat",targetdirsecure+"\\Auditinfo"+temp+".dat",FALSE);
				CopyFile(workdir+"\\Auditinfo"+temp+".dat",targetdir+"\\Auditinfo"+temp+".dat",FALSE);
			}
			CString se="Exercice file "+dexer+"\r\n";// Création du nouveau fichier d'exercice
			se+=tim.Format("Open %d/%m/%Y %H:%M:%S");
			temp.Format("%u",(int)fversion);
			se+=";"+temp;
			se+=";"+dexer;
			se+=";"+GetConfigString("License","Serial","");
			se+=";"+nom;	
			se+=";"+adresse1;	
			se+=";"+adresse2;	
			se+=";"+siret;	
			se+=";"+naf;	
			se+="\r\n";
			CWrite(datadir+"\\Exercice.dat",se,0);				
			CopyFile(datadir+"\\Exercice.dat",securedir+"\\Data\\Exercice.dat",FALSE);				
			CopyFile(datadir+"\\Exercice.dat",backupdir+"\\Data\\Exercice.dat",FALSE);
			CString filesize;
			CString filetime;
			temp1.Format("Auditinfo%u.dat;",auditfile);
			fi=GetFileInfo(auditinfopath);
			filesize.Format("%u",fi.size);	
			filetime.Format("%lld",fi.time);
			temp.Format("%u;",catidx);
			temp+=temp1+filesize+";"+filetime+"\r\n";
			CWrite(sysdir+"\\csat.avs",temp,1);
			catidx++;
			temp.Format("%u",catidx);
			WriteConfigString("Infocert","Catidx",temp);
			fi=GetFileInfo(targetdir+"\\Data\\Exercice.dat");
			filesize.Format("%u",fi.size);	
			filetime.Format("%lld",fi.time);
			temp.Format("%u;",catidx);
			temp+="Data\\Exercice.dat;"+filesize+";"+filetime+"\r\n";
			CWrite(sysdir+"\\csat.avs",temp,1);
			catidx++;
			temp.Format("%u",catidx);
			WriteConfigString("Infocert","Catidx",temp);
			temp=dexer+"\r\n";
			CWrite(sysdir+"\\csat.avs",temp,1);
			
			auditfile++;
			CString auditfileindex;
			auditfileindex.Format("%u",auditfile);
			WriteConfigString("Infocert","Auditfile",auditfileindex);
			auditinfopath=workdir+"\\Auditinfo"+auditfileindex+".dat";
			//auditfileindex.Format("%u",auditfile);
			CWrite(auditinfopath,"Audit file\r\n",0);
			InitialisationDonnee();
		
			if (wsel==0)// Message utilisateur indiquant que la cloture annuelle a été faite si faite au démarrage de la billetterie
			{
				initavert1=txtm[78];
				initavert0="";
				initavert2="";
				av1.SetWindowText(initavert0);
				av2.SetWindowText(initavert1);
				av3.SetWindowText(initavert2);
				av1.ShowWindow(1);
				av2.ShowWindow(1);
				av3.ShowWindow(1);

				//RedrawWindow(0,0,1|256|4);
				Sleep(5000);
			}
			else// Message utilisateur indiquant que la cloture annuelle a été faite si faite pendant utilisation
			{
				CMessage* pdlg;
				pdlg= new CMessage(this);
				pwlog=pdlg;
				pdlg->mes1=txtm[78];//La clôture annuelle a été réalisée.
				pdlg->mes2=txtm[79];//Les données ont étés archivées.
				pdlg->mes3=txtm[6];//Taper OK pour valider
				pdlg->mode=1;
				pdlg->DoModal();
				delete pdlg;
				pwlog=NULL;
			}
			InterlockedExchange(&fexeran,0);// On enlève le flag de cloture en cours
		}
	}
}
void CConcertoDlg::TestClotureMensuelle()
{
	CTime tim=CTime::GetCurrentTime();
	int mois;
	int an;
	CString temp1;
	CString temp2;
	CString temp3;
	CString temp4;
	mois=atoi(dopen.Mid(4,2));
	an=atoi(dopen.Mid(0,4));

	if(dopen!=""&&fexermois==0&&(tim.GetYear()>an||tim.GetMonth()>mois)&&tim.GetHour()>=8)
	{
		fexermois=1;
		CMessage* pdlg;
		pdlg= new CMessage(this);
		pwlog=pdlg;

		temp1=txtm[90];
		pdlg->mes1=temp1;//La clôture mensuelle doit être réalisée.
		temp1=txtm[70];
		pdlg->mes2=temp1;//La billetterie va être clôturée.
		temp1=txtm[6];
		pdlg->mes3=temp1;//Taper OK pour valider
		pdlg->mode=1;
		if(pdlg->DoModal()==IDOK)
		{
			hist=0;
			flagraz=1;
			FillTicketList(opendir);
			OnBnClickedCashClose();
			flagraz=0;
			fexermois=0;
		}
		delete pdlg;
		pwlog=NULL;
	}
}
void CConcertoDlg::RedrawQteAdjust() //Redessine les boutons + et - de la liste de vente borne
{
		CRect rect;
		lqte.GetWindowRect(&rect);
		int x=(rect.left+(rect.Width()*2/3)-3);
		int y=(rect.top+lqte.GetItemHeight(0)*(lqte.GetCurSel()-lqte.GetTopIndex( )));
		int largeur=rect.Width()/3;
		int hauteur= lqte.GetItemHeight(0);
		((CButton*)GetDlgItem(IDC_PLUS))->SetWindowPos(&wndTop,(int)x,(int)y,(int)largeur,(int)hauteur,SWP_SHOWWINDOW);
		x=rect.left;
		((CButton*)GetDlgItem(IDC_MOINS))->SetWindowPos(&wndTop,(int)x,(int)y,(int)largeur,(int)hauteur,SWP_SHOWWINDOW);
		bplus.RedrawWindow(0,0,1|256|4);
		bminus.RedrawWindow(0,0,1|256|4);
}


LRESULT CConcertoDlg::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	if(message==WM_USER+7)
	{	// 
		KillTimer(11);
		if(SCR&&FTEM==0)
		{
			TerminateThread(hGetMCIModeThread,0);
			CloseHandle(hGetMCIModeThread);
			MCIWndClose(SCR);
			MCIWndDestroy(SCR);
			SCR=NULL;
			InterlockedExchange(&FTEM,1);
			Sleep(300);
			if(wsel==1)
			{
				DrawWindowConcert();
				if(master)
				{
					if(HRSG)
						tgate.ShowWindow(fgate);
					tnet.ShowWindow(1);
					if(alone==0)
						tnet.SetWindowTextA("HRSR");
					else
						if(alone==1)
							tnet.SetWindowTextA("HRAU");
				}
			}
		}
		return 0;
	}
	if(message==WM_USER+8)
	{	// 
		OnSearchScanUSB();
		if(scaninter=="")
			OnSearchScanBLUE();
		return 0;
	}
	if(message==WM_USER+9)
	{	// On redessine le temoin control uniquement sur son emplacement
		CRect rect;
		tcontrol.GetWindowRect(&rect);
		rect.DeflateRect(-5,-5);
		RedrawWindow(&rect,0,1|256|4);
		return 0;
	}
	if(message==WM_USER+10)
	{	// On repositionne chaque liste sur le même index
		int i;
		i=lptot.GetTopIndex( );
		lcode.SetTopIndex(i);
		lqte.SetTopIndex(i);
		return 0;
	}
	if(message==WM_USER+11)
	{	// On repositionne chaque liste sur le même index
		int i;
		i=lcancel.GetTopIndex( );
		if(i!=-1)
		{

			if(wsel==2)
			{
				lntick.SetTopIndex(i);
			}
			ldate.SetTopIndex(i);
			lprix.SetTopIndex(i);
		}
		return 0;
	}
	if(message==WM_USER+12)
	{	// Traitement du timer toutes les secondes
		int i;
		CString temp;
		CTime tim=CTime::GetCurrentTime();// Récupère la date et heure courante
		TestClotureMensuelle();// Teste et effectue la cloture mensuelle si nécessaire
		TestClotureAnnuelle();// Teste et effectue la cloture annuelle si nécessaire
		if(wsel<5)
		{	//Met à jour le static date et heure
			temp=tim.Format("%d/%m/%Y\n%H:%M:%S");
			CDC *pdc=ndate.GetDC();
			CRect elrct=rctdate;
			if(etdate==0)// Dessine la date dans le demi cercle du bas sauf en écran config
			{
				RectF rctf((REAL)0,0,(REAL)rctdate.Width(),(REAL)rctdate.Height());
				Graphics gr(pdc->m_hDC);
				gr.DrawImage(parcdc,rctf);
				etdate=1;
			}
			pdc->SelectObject(&geodate);
			elrct.left=0;
			elrct.top=0;
			elrct.right=rctdate.Width();
			elrct.bottom=rctdate.Height();
			elrct.DeflateRect(0,rctdate.Height()/4,0,0);
			pdc->SetBkMode(OPAQUE);
			pdc->SetTextColor(0xFFFFFF);
			pdc->SetBkColor(0x000000);
			pdc->SelectStockObject(NULL_BRUSH);
			pdc->DrawText(temp,&elrct,DT_CENTER);
			ReleaseDC(pdc);
		}
		for(i=1;i<=16;i++)
		{	// Test aussi si les horaire programmés en contrôle sont échus sur chaque controle
			if(valhor&&horaire&&choraire[i]==2&&cselevt[i]>0&&cdate[i]!=""&&cheure[i]!="")
			{
				CTime date(atoi(cdate[i].Right(4)),atoi(cdate[i].Mid(3,2)),atoi(cdate[i].Left(2)),atoi(cheure[i].Left(2)),atoi(cheure[i].Right(2)),0,-1);
				if(tim>date)// compare la date en mémoire du contrôle avec la date courante
				{
					cselevt[i]=0;// les enlève automatiquement de la liste de contrôle
					if(cfrom[i].Find("SHOP",0)!=-1)
					{
						cdate[i]="";
						cheure[i]="";
						SetTimer(17,10000,NULL);
					}
					temp.Format("%u",i);
					AfxGetApp()->WriteProfileInt(temp,"CONTROLE",cselevt[i]);
					if(wsel==4||wsel==1)
					{
						RefreshControle();
						if(wsel==4)
							RefreshControlList();
					}
				}
			}
		}
		return 0;
	}
	if(message==WM_USER+13)
	{	// Lancement du clavier tactile
		Klance();
		return 0;
	}
	if(message==WM_USER+14)
	{	// Dessine bouton +/-
		int fiv=lqte.GetTopIndex( );
		int ics=lqte.GetCurSel();
		if(ics!=-1&&wsel==1&&afmode&&ics>=fiv&&ics<fiv+5&&etb<2)
		{
			lptot.SetTopIndex(fiv);
			RedrawQteAdjust();
		}
		else
		{
			bplus.ShowWindow(0);
			bminus.ShowWindow(0);
		}
		return 0;
	}
	if(message==WM_USER+15)
	{	
		CString temp1;
		CString temp2;
		CString temp3;
		CMessage* pdlg= new CMessage();
		temp1=txtm[7];
		temp2=txtm[8];
		temp3=txtm[9];
		pdlg->mes1=temp1;//Imprimante débranchée de son port initial
		pdlg->mes2=temp2;//Veuillez la reconnecter et cliquer
		pdlg->mes3=temp3;//sur OUI pour retester la connection
		pdlg->mode=0;
		if(pdlg->DoModal()==IDOK)
		{
			delete pdlg;
		}
		else
		{
			delete pdlg;
			noprint=1;
		}
		return 0;
	}
	if(message==WM_USER+16)
	{	
		CString temp1;
		CString temp2;
		CString temp3;
		if(pwidt!=NULL)
		{
			pwidt->OnBnClickedOk();
			//delete pdlg;
			//pwjob=NULL;
			return 0;/**/
		}
		CMessage* pdlg= new CMessage();
		temp1=txtm[83];//L'imprimante requiert votre intervention
		if(impmes=="Hors ligne")		
			temp2=txtm[89];//Des tickets n'ont peut-être pas été imprimés
		else
			temp2=txtm[84];//Recharger le magasin de tickets
		pdlg->mes2=temp1;//L'imprimante requiert votre intervention
		pdlg->mes3=temp2;//Recharger le magasin de tickets
		pdlg->mes1=impmes;//Cliquer sur OK pour redémarer
		pdlg->mode=10;
		pwjob=pdlg;
		Sleep(200);
		pdlg->DoModal();
		pdlg->DestroyWindow();
		delete pdlg;
		pwjob=NULL;
		return 0;
	}
	if(message==WM_USER+17)
	{	
		PrintIdent();
		return 0;
	}
	if(message==WM_USER+18)
	{	
		DefautIntegrite(GetConfigString("Infocert","AuditIntégrité",""));
		return 0;
	}

	if(message==WM_CTLCOLORLISTBOX )
	{	// COMMANDE DE SELECTION DANS LES LISTES COUPLEES PAR CELLE QUI A L'ASCENCEUR	
		int i;
		CWnd* pw;
		CDC* pDC;
		pw=CWnd::FromHandle((HWND)lParam);
		i=pw->GetDlgCtrlID();
		switch(i)
		{
		case IDC_LCANCEL:
			{
				pDC=CDC::FromHandle((HDC)wParam);
				CRect rct;
				lcancel.GetClientRect(&rct);
				pDC->FillSolidRect(&rct,0x404040);
				lartbrush.DeleteObject();
				lartbrush.CreateSolidBrush(0x404040);
				HBRUSH hbr=(HBRUSH)lartbrush;
				PostMessage(WM_USER+11);
				return (LRESULT)hbr;
			}
		case IDC_LNTICK:
			{
				pDC=CDC::FromHandle((HDC)wParam);
				CRect rct;
				lntick.GetClientRect(&rct);
				pDC->FillSolidRect(&rct,0x404040);
				lartbrush.DeleteObject();
				lartbrush.CreateSolidBrush(0x404040);
				HBRUSH hbr=(HBRUSH)lartbrush;
				return (LRESULT)hbr;
			}
		case IDC_LDATE:
			{
				pDC=CDC::FromHandle((HDC)wParam);
				CRect rct;
				ldate.GetClientRect(&rct);
				pDC->FillSolidRect(&rct,0x404040);
				lartbrush.DeleteObject();
				lartbrush.CreateSolidBrush(0x404040);
				HBRUSH hbr=(HBRUSH)lartbrush;
				return (LRESULT)hbr;
			}
		case IDC_LPRIX:
			{
				pDC=CDC::FromHandle((HDC)wParam);
				CRect rct;
				lprix.GetClientRect(&rct);
				pDC->FillSolidRect(&rct,0x404040);
				lartbrush.DeleteObject();
				lartbrush.CreateSolidBrush(0x404040);
				HBRUSH hbr=(HBRUSH)lartbrush;
				return (LRESULT)hbr;
			}
		case IDC_SELSPECT:
			{
				pDC=CDC::FromHandle((HDC)wParam);
				CRect rct;
				lselevt.GetClientRect(&rct);
				pDC->FillSolidRect(&rct,0x404040);
				lartbrush.DeleteObject();
				lartbrush.CreateSolidBrush(0x404040);
				HBRUSH hbr=(HBRUSH)lartbrush;
				PostMessage(WM_USER+11);
				return (LRESULT)hbr;
			}
		case IDC_CODE:
			{
				pDC=CDC::FromHandle((HDC)wParam);
				CRect rct;
				lcode.GetClientRect(&rct);
				pDC->FillSolidRect(&rct,0x404040);
				lartbrush.DeleteObject();
				lartbrush.CreateSolidBrush(0x404040);
				HBRUSH hbr=(HBRUSH)lartbrush;
				return (LRESULT)hbr;
			}
		case IDC_QTE:
			{
				pDC=CDC::FromHandle((HDC)wParam);
				CRect rct;
				lqte.GetClientRect(&rct);
				pDC->FillSolidRect(&rct,0x404040);
				lartbrush.DeleteObject();
				lartbrush.CreateSolidBrush(0x404040);
				HBRUSH hbr=(HBRUSH)lartbrush;
				return (LRESULT)hbr;
			}
		case IDC_PTOT:
			{
				pDC=CDC::FromHandle((HDC)wParam);
				CRect rct;
				lptot.GetClientRect(&rct);
				pDC->FillSolidRect(&rct,0x404040);
				lartbrush.DeleteObject();
				lartbrush.CreateSolidBrush(0x404040);
				HBRUSH hbr=(HBRUSH)lartbrush;
				PostMessage(WM_USER+10);
				return (LRESULT)hbr;
			}
		}
	}

	return CDialog::DefWindowProc(message, wParam, lParam);
}

void CConcertoDlg::CloseKeyboard()
{	// Fermeture du process du clavier tactile
	DWORD code;
	BOOL status;
	sdum.SetFocus();
	CString temp1;
	if(FindWindow(NULL,txtc[12])!=NULL)//Clavier tactile
	{
		KillTimer(1);
		FindWindow(NULL,txtc[12])->SendMessage(WM_CLOSE,0,0);
		while((status=GetExitCodeProcess(kpri.hProcess,&code))&&code==STILL_ACTIVE)
			Sleep(100);
		if(status)
		{
			/*if(wsel==5&&fsave==0)
				SaveStaticConfig();
			if(wsel==3&&fsave==0)
				SaveStaticArticle();*/
			CloseHandle(kpri.hProcess);
			CloseHandle(kpri.hThread);
			sdum.SetFocus();
			//SetFocus();
			trackosk=0;
		}
		else
			MessageBox("process en cours");
	}
}

void CConcertoDlg::OnTimer(UINT_PTR nIDEvent)
{
	CString temp;
	CString temp1;
	int i=0;
	if(nIDEvent==1)
	{	// Test la fermeture extérieure à l'application du clavier tactile
		if(FindWindow(NULL,txtc[12])==NULL)
		{
			if(trackosk==1)
			{	// On sauve les articles ou la config  si un texte a été changé et non sauvegardé
				KillTimer(1);
				sdum.SetFocus();// passe le focus dans un controle invisible  (dummy) pour l'enlever de l'edit
				if(kpri.hThread)
					CloseHandle(kpri.hThread);
				if(kpri.hProcess)
					CloseHandle(kpri.hProcess);
				trackosk=0;
				if(wsel==3&&fsave==0)// si article
					SaveStaticArticle();
				if(wsel==5&&fsave==0)
				{
					if(kid==IDC_SPREFIX)// Si champ préfixe annule le changement
						sprefix.SetWindowTextA(prefix);
					else
						SaveStaticConfig();
				}
			}
		}
		else
		{
			trackosk=1;
		}
	}

	if(nIDEvent==2)
	{	// Chaque seconde
		KillTimer(2);
		PostMessage(WM_USER+12,0,0);// Traitement des affichages heure et cloture automatique annuelle
		SetTimer(2,1000,NULL);
	}

	if(nIDEvent==3)// ********* a supprimer ***********
	{
		KillTimer(3);
		sdum.SetFocus();
	}

	if(nIDEvent==4)
	{
		CWnd* pwnd;
		if((pwnd=FindWindow("CabinetWClass",NULL))==NULL)
		{
			CloseHandle(printcpi.hProcess);
			CloseHandle(printcpi.hThread);
			KillTimer(4);
			SetWindowPos(&wndTopMost,0,0,0,0,SWP_NOSIZE|SWP_NOMOVE|SWP_SHOWWINDOW);
			bnet.EnableWindow(1);
			bprinter.EnableWindow(1);
		}
		else
			SetWindowPos(pwnd,0,0,0,0,SWP_NOSIZE|SWP_NOMOVE);
	}

	if(nIDEvent==5)
	{
		CWnd* pwnd;
		KillTimer(5);
		if((pwnd=FindWindow("CabinetWClass",NULL))==NULL)
		{
			STARTUPINFO csui;
			PROCESS_INFORMATION cpi;
			ZeroMemory( &csui, sizeof(csui) );
			csui.cb = sizeof(csui);
			ZeroMemory( &cpi, sizeof(cpi) );
			GetStartupInfo(&csui);
			CloseHandle(netcpi.hProcess);
			CloseHandle(netcpi.hThread);
			temp="cmd.exe /c taskkill /f /im explorer.exe";
			CreateProcess(NULL,temp.GetBuffer(),NULL,NULL,FALSE,NORMAL_PRIORITY_CLASS,NULL,NULL,&csui,&cpi);
			SetWindowPos(&wndTopMost,0,0,0,0,SWP_NOSIZE|SWP_NOMOVE|SWP_SHOWWINDOW);
			bnet.EnableWindow(1);
			bprinter.EnableWindow(1);
			CloseKeyboard();
		}
		else
		{
			SetTimer(5,500,NULL);
			SetWindowPos(pwnd,0,0,0,0,SWP_NOSIZE|SWP_NOMOVE);
		}

	}

	if(nIDEvent==6)
	{	
		CWnd* pwnd;
		if((pwnd=FindWindow(NULL,"Date et heure"))!=NULL)// ATTENTION AU TEXTE WINDOWS version étrangère
		{
			SetWindowPos(pwnd,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
			pwnd->SetWindowPos(&wndTopMost,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
		}
		else
		{
			SetWindowPos(&wndTopMost,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
			KillTimer(6);
		}
	}

	if(nIDEvent==7)
	{	// Sert à animer l'antenne du récepteur radio de contrôle des tickets a supprimer ***************************
		nbctc--;
		if(nbctc==0)
		{
			KillTimer(7);
			if(!CONTROL)
				tcontrol.SetWindowText("HRDV");//*********
		}
	}
	if(nIDEvent==8)// PAGE
	{	
		KillTimer(8);
		if(etb==3)
		{
			pinum->nombre="-1";
			pinum->EndDialog(0);
		}
		else
		{
			if(etb<3)
			{
				calc="";
				total.SetWindowTextA("");
				lcode.ResetContent();
				lqte.ResetContent();
				lptot.ResetContent();
			}
			selfam=0;
			selrub=0;
			etb=0;
			DrawWindowConcert();
		}
		SetTimer(11,20000,NULL);
	}
	if(nIDEvent==9)// PAGE
	{	// Animation de l'antenne radio en recherche de Station de contrôle
		tcontrol.GetWindowTextA(temp);//**************
		if(temp=="HRDB")
			tcontrol.SetWindowText("HRDR");//**************
		else
			if(temp=="HRDR")
				tcontrol.SetWindowText("HRDB");//**************
	}
	if(nIDEvent==10)
	{	// Effacement pincode dans scan après 10 secondes du pincode en mode dev=1
		KillTimer(10);
		scan="";
		nscan.ShowWindow(0);
		nscan.SetWindowTextA("");
		nscan.ShowWindow(0);
	}
	if(nIDEvent==11)
	{	// Enclenchement ecran de veille après 10 secondes inactivité
		KillTimer(11);
		if(afmode&&valscr)
		{
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
			temp=workdir+"\\scr.avi";
			SCR=MCIWndCreate(GetSafeHwnd(),AfxGetInstanceHandle( ),WS_CHILD|WS_VISIBLE|MCIWNDF_NOOPEN|MCIWNDF_NOPLAYBAR|MCIWNDF_NOTIFYMODE|MCIWNDF_NOERRORDLG|MCIWNDF_NOMENU,temp);//|MCIWNDF_NOAUTOSIZEWINDOW
 			if(SCR==NULL)
				MessageBox("MCI Fail");
			else
			{
				InterlockedExchange(&FTEM,0);
				tnet.ShowWindow(0);
				tweb.ShowWindow(0);
				tcontrol.ShowWindow(0);
				tgate.ShowWindow(0);
				ndate.ShowWindow(0);
				CRect rct;
				GetWindowRect(&rct);
				::SetWindowPos(SCR,HWND_TOPMOST,0,0,wlargeur,whauteur,SWP_HIDEWINDOW);
				//MCIWndSetOwner(SCR,GetSafeHwnd());
				MCIWndPutDest(SCR,&rct);
				::SetWindowPos(SCR,HWND_TOPMOST,0,0,wlargeur,whauteur,SWP_SHOWWINDOW|SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
				MCIWndPlay(SCR);
				hGetMCIModeThread = (HANDLE)CreateThread(NULL,0,&GetMCIModeThread,this,0,NULL);				
			}
		}
	}
	if(nIDEvent==12)
	{	// Clignotement du symbole réseau sur l'esclave en cas de modification article requise par la maître si la clôture n'a pas été faite
		if(fart&&!master&&wsel==1)
		{
			if(fartaf)
			{
				tnet.ShowWindow(0);	//************
				fartaf=0;
			}
			else
			{
				tnet.ShowWindow(1);	//************
				fartaf=1;
			}
		}
	}

	if(nIDEvent==13)
	{	// Rafraîchit en "temps réel" le nombre d'entrée dans la liste de contrôle
		KillTimer(13);
		if(FREFCONTROL)
		{
			RefreshControlList();
			InterlockedExchange(&FREFCONTROL,0);
		}
		if(contfile!=memcontfile&&wsel==4)
		{
			memcontfile=contfile;
			DrawBoutonArticle(13);				
		}
	}

	if(nIDEvent==14)
	{	

	}

	if(nIDEvent==15)// progress bar au démarrage
	{	
		pimp.StepIt();		
	}

	if(nIDEvent==16)// Lance la recherche d'un scanner absent
	{	
		KillTimer(16);
		if(scaninter==""&&fprev)
		{
			OnSearchScanUSB();
			if(scaninter=="")
				OnSearchScanBLUE();
		}
		SetTimer(16,15000,NULL); 
	}
	if(nIDEvent==17&&master&&serveur!="")// Lance la recherchedes des fichiers WEB toutes les 15 secondes
	{	
		KillTimer(17);
		SearchWEBFile();// Cherche un fichier de controle sur le serveur WEB si aucun chargé
	}
	if(nIDEvent==18&&serveur!="")
	{	
		KillTimer(18);
		SearchWEBShop();// Vérifie une connection boutique WEB
		if(FWEB==1)
			SetTimer(18,300000,NULL);// Retestera la connection dans 5 minutes
		else
			SetTimer(18,10000,NULL);// Retestera la connection dans 10 secondes
	}
	CDialog::OnTimer(nIDEvent);
}

BOOL CConcertoDlg::SystemShutdown()
{	// Routine de demande d'arrêt de Window par l'utilisateur
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
 	if (!InitiateSystemShutdown(NULL,"Fermeture de la Billetterie",1,FALSE,FALSE))
		return FALSE; 

   /*if (!ExitWindowsEx(EWX_POWEROFF | EWX_FORCEIFHUNG, 
               SHTDN_REASON_MAJOR_OTHER |
			   SHTDN_REASON_MINOR_OTHER |
			   SHTDN_REASON_FLAG_PLANNED)) 
		return FALSE; */
	CloseHandle(hToken);
	return TRUE;
}
BOOL CConcertoDlg::SystemRestart()
{	// Routine de demande de redémarrage de Window après un changement de N° de poste
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
 	if (!InitiateSystemShutdown(NULL,"Fermeture de la Billetterie",1,FALSE,TRUE))
		return FALSE; 

   /*if (!ExitWindowsEx(EWX_POWEROFF | EWX_FORCEIFHUNG, 
               SHTDN_REASON_MAJOR_OTHER |
			   SHTDN_REASON_MINOR_OTHER |
			   SHTDN_REASON_FLAG_PLANNED)) 
		return FALSE; */
	CloseHandle(hToken);

	return TRUE;
}


int CConcertoDlg::Klance()
{	// Lancement du process du clavier tactile
	CMessage* pdlg;
	CString temp;
	CString temp1;
	CString temp2;
	if((artro==0||fadmin||wsel==5)&&trackosk==0)
	{ //Test si des ventes ont commencées, si on n'est pas en mode installateur ou si le clavier est déjà lancé
		/*if(CONTROL)
		{	// Rejette la demande en cas de contrôle des ticket déjà lancé
			temp1=txtm[3];
			temp2=txtm[4];
			sdum.SetFocus();
			pdlg=new CMessage(this) ;
			pdlg->mes1=temp1;//" Le contrôle doit être arrêté ";
			pdlg->mes2=temp2;//"avant de modifier les articles";
			pdlg->mes3=" ";
			pdlg->mode=1;
			pwlog=pdlg;
			pdlg->DoModal();
			delete pdlg;
			pwlog=NULL;
			sdum.SetFocus();
			return 0;
		}*/
		if(GetDlgItem(kid)->GetSafeHwnd()!=NULL)// Redonne le focus au controle sélectionné
			GetDlgItem(kid)->SetFocus();
		if(trackosk==0)// Si le clavier n'est pas actif
		{
			ZeroMemory( &ksui, sizeof(ksui) );
			ksui.cb = sizeof(ksui);
			ZeroMemory( &kpri, sizeof(kpri) );
			GetStartupInfo(&ksui);
			CreateProcess(workdir+"\\FreeVK.exe",NULL,NULL,NULL,FALSE,NORMAL_PRIORITY_CLASS,NULL,NULL,&ksui,&kpri);
			CWnd* pwnd;
			while((pwnd=FindWindow(NULL,"Free Virtual Keyboard (www.FreeVirtualKeyboard.com)"))==NULL)
				Sleep(100);
			pwnd->SetWindowText(txtc[12]);//Clavier tactile
			trackosk=1;//flag clavier actif à 1
			fsave=0;// flag indiquant une sauvegarde du controle vide
			SetTimer(1,200,NULL);
		}
		return 1;
	}
	else
	{
		if(trackosk==0)
		{	// Rejette la demande de clavier si des ventes ont déjà commencées
			sdum.SetFocus();
			temp=txtm[18];
			pdlg=new CMessage(this) ;
			pdlg->mes1=temp;//"La billetterie doit être cloturée";
			pdlg->mes2=" ";
			pdlg->mes3=" ";
			pdlg->mode=1;
			pwlog=pdlg;
			pdlg->DoModal();
			delete pdlg;
			pwlog=NULL;
		}
		return 0;
	}
}

int CConcertoDlg::Control(CString billet,int remove)
{	// Routine de contrôle des tickets par le scanner
	CString temp;
	int istop=0;
	int istart=0;
	HANDLE hf;
	CString dir;
	CString buf;
	CString buftail;
	CString bufhead;
	DWORD nbw;
	int i=1;
	int j;
	int idx;
	int idy;
	int inb;
	int k;
	valid=0;
	CTime time=CTime::GetCurrentTime();
	CString day=time.Format("%d");
	while(i<=16)
	{
		temp.Format("%u",i);
		if(cselevt[i]==1)
		{
			if(temp.GetLength()==1)
				temp="0"+temp;
			dir=netcontdir+"\\"+temp;
			hf=(CreateFile(dir+"\\Controle.dat",GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL));
			if(hf==INVALID_HANDLE_VALUE)
				;
			else
			{
				if(ReadFile(hf,buf.GetBuffer(GetFileSize(hf,NULL)),GetFileSize(hf,NULL),&nbw,NULL))
				{
					buf.ReleaseBuffer(nbw);
					istart=0;
					if((istop=buf.Find(billet,istart))!=-1)
					{	// On recherche le N° de ticket
						if(remove==0)
						{						
							idx=atoi(billet.Mid(1,2));//N° article
							if((inb=(perso[idx]&0xF000)>>12)>1)
							{
								for(j=0;j<inb;j++)
								{
									idy=buf.Find(";",istop);
									temp=buf.Mid(idy+1,2);
									if(temp==day)
										break;
									if(temp=="\r\n")
									{
										k=(perso[idx]&0xFF0)>>4;
										if(k>0)
											SendBarmaticSpooler(k);
										if(j==inb-1)
											buf.Insert(idy+1,day+";X");// On grille le jour et la ligne dans le fichier de contrôle en cours
										else
											buf.Insert(idy+1,day+";");// On grille le jour dans le fichier de contrôle en cours
										goto RECORD;
									}
									istop=idy+3;
								}
								CloseHandle(hf);
								valid=-1;
								return valid;
							}
							else
							{
								idy=buf.Find(";",istop);
								if(buf.GetAt(idy+1)=='X')
								{	// Ticket déjà grillé
									CloseHandle(hf);
									valid=-1;
									return valid;
								}
								buf.Insert(idy+1,'X');// On grille le ticket avec un "X" dans le fichier de contrôle en cours
							}
RECORD:
							SetFilePointer(hf,NULL,NULL,FILE_BEGIN);
							WriteFile(hf,buf.GetBuffer(buf.GetLength()),buf.GetLength(),&nbw,NULL);
							SetEndOfFile(hf);	
							CloseHandle(hf);
							if(master)
								RefreshControlList();
							valid=1;
							return valid;
						}
						else
						{// On ne touche pas au fichier
							bufhead=buf.Left(istop);
							buftail=buf.Mid(istop+14);
							//MessageBox(bufhead+"xxx"+buftail);
							valid=0;
							return valid;
						}
					}

				}
				else
					MessageBox(dir+"\\Controle.dat non lu.");
			}
			CloseHandle(hf);
		}	
		i++;
	}
	valid=0;
	return valid;
}
int CConcertoDlg::ControlMoxity(CString billet,int remove)
{
	CString temp;
	int istop=0;
	int istart=0;
	HANDLE hf;
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
			dir=netcontdir+"\\"+temp;
			hf=(CreateFile(dir+"\\Controle.dat",GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL));
			if(hf==INVALID_HANDLE_VALUE)
				;
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
							if(buf.GetAt(istop+12)=='X')
							{
								CloseHandle(hf);
								valid=-1;
								return valid;
							}
							buf.SetAt(istop+12,'X');
							SetFilePointer(hf,NULL,NULL,FILE_BEGIN);
							WriteFile(hf,buf.GetBuffer(buf.GetLength()),buf.GetLength(),&nbw,NULL);
							SetEndOfFile(hf);	
							CloseHandle(hf);
							if(master)
								RefreshControlList();
							valid=1;
							return valid;
						}
						else
						{
							bufhead=buf.Left(istop);
							buftail=buf.Mid(istop+15);
							//MessageBox(bufhead+"xxx"+buftail);
							valid=0;
							return valid;
						}
					}
				}
				else
					MessageBox(dir+"\\Controle.dat non lu.");
			}
			CloseHandle(hf);
		}	
		i++;
	}
	valid=0;
	return valid;
}
int CConcertoDlg::ControlTicketplace(CString billet,int remove)
{
	CString temp;
	int istop=0;
	int istart=0;
	HANDLE hf;
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
			dir=netcontdir+"\\"+temp;
			hf=(CreateFile(dir+"\\Controle.dat",GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL));
			if(hf==INVALID_HANDLE_VALUE)
				;
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
							if(buf.GetAt(istop+13)=='X')
							{
								CloseHandle(hf);
								valid=-1;
								return valid;
							}
							buf.SetAt(istop+13,'X');
							SetFilePointer(hf,NULL,NULL,FILE_BEGIN);
							WriteFile(hf,buf.GetBuffer(buf.GetLength()),buf.GetLength(),&nbw,NULL);
							SetEndOfFile(hf);	
							CloseHandle(hf);
							if(master)
								RefreshControlList();
							valid=1;
							return valid;
						}
						else
						{
							bufhead=buf.Left(istop);
							buftail=buf.Mid(istop+15);
							//MessageBox(bufhead+"xxx"+buftail);
							valid=0;
							return valid;
						}
					}
				}
				else
					MessageBox(dir+"\\Controle.dat non lu.");
			}
			CloseHandle(hf);
		}	
		i++;
	}
	valid=0;
	return valid;
}

BOOL CConcertoDlg::PreTranslateMessage( MSG* pMsg )// Commande provenant du clavier
{
	CString temp;
	CString num;
	CString post;
	CString tcpt;
	CString tch;
	CString tp1;
	CString tp2;
	int i;
	if(pMsg->message==WM_CHAR)// Ejecte tous les ; des champs articles ou config
	{
		if((CHAR)pMsg->wParam==';')
			return TRUE;
		if(kid==IDC_SPREFIX)//  / \ [ ] : | < > + = ; , ?  
		{
			if((CHAR)pMsg->wParam=='/'||(CHAR)pMsg->wParam=='\\'||(CHAR)pMsg->wParam=='['||(CHAR)pMsg->wParam==']'||(CHAR)pMsg->wParam==':'||(CHAR)pMsg->wParam=='|'
				||(CHAR)pMsg->wParam=='<'||(CHAR)pMsg->wParam=='>'||(CHAR)pMsg->wParam=='+'||(CHAR)pMsg->wParam=='='||(CHAR)pMsg->wParam==';'||(CHAR)pMsg->wParam==','
				||(CHAR)pMsg->wParam=='?'||(CHAR)pMsg->wParam==' '||(CHAR)pMsg->wParam=='^'||(CHAR)pMsg->wParam=='¨'||(CHAR)pMsg->wParam=='\''||(CHAR)pMsg->wParam=='"')
				return TRUE;
		}
	}
	if(pMsg->message==WM_CHAR&&(CHAR)pMsg->wParam==9&&wsel==3)	// Si TAB efface l'article sélectionné
	{
		CloseKeyboard();
		RedrawWindow(0,0,1|256|4);
		CMessage* pdlg;
		CString temp1;
		CString temp2;
		temp1=txtm[5];
		temp2=txtm[6];
		pdlg= new CMessage(this);
		pdlg->mes1=temp1;//"Voulez-vous supprimer l'article sélectionné ?";
		pdlg->mes2=temp2;//"Taper OK pour valider";
		pdlg->mes3=" ";
		pdlg->mode=7;
		pwlog=pdlg;
		if(pdlg->DoModal()==IDOK)
		{
			int idx=artnum+(artrange*NAPP);
			ClearStat(idx);
		}
		pdlg->DestroyWindow();
		delete pdlg;
		pwlog=NULL;
		return TRUE;
	}
	if(pMsg->message==WM_CHAR&&(CHAR)pMsg->wParam==13) // si Entrée
	{
		CloseKeyboard();
		{
			if(wsel==5&&fsave==0) // Si Config
			{
				if(kid==IDC_SPREFIX)// Si champ préfixe redémarre le système avec nouveau nom d'ordinateur
				{
					sprefix.GetWindowTextA(temp);
					CString ordi="\\\\"+temp+"_"+poste+"\\Control\\*.*";
					for(i=0;i<lmac.GetCount();i++)
					{
						lmac.GetText(i,temp);
						if(ordi==temp&&(int)(lmac.GetItemData(i))>=0)
						{
							MessageBox(txtm[23]);//Ce N° de poste existe déjà sur le réseau!
							sprefix.SetWindowTextA(prefix);
							goto FIN;
						}
					}
					sprefix.GetWindowTextA(prefix);			
					WriteConfigString("Client","Prefix",prefix);
					InitMachineName();
				}
				else
					SaveStaticConfig(); // sinon sauvegarde la config
FIN:;						
			}
			if(wsel==3&&fsave==0)
			{
				if(kid==IDC_PAGE)
				{
					temp.Format("P%u",artrange+1);
					AfxGetApp()->WriteProfileString(temp,"Titre",txtpage);
					pag[artrange]=txtpage;
				}
				SaveStaticArticle();			
			}
		}
		return TRUE;
	}
	if(pMsg->message==WM_KEYDOWN&&(CHAR)pMsg->wParam==27)
	{
		if(kid==IDC_PAGE)// annulation des changements entrés dans le controle et retour au texte original
		{
			txtpage=libelsave;
			wpage.SetWindowTextA(txtpage);
			wpage.RedrawWindow(0,0,1|256|RDW_ERASE);
		}
		if(kid==IDC_SPREFIX)// Si champ préfixe annule nouveau nom d'ordinateur
		{
			sprefix.SetWindowTextA(prefix);
		}
		CloseKeyboard();
		GetDlgItem(kid)->SetWindowTextA(libelsave);
		return TRUE;
	}
	if(pMsg->message==WM_KEYDOWN&&(CHAR)pMsg->wParam==8)
	{
		if(kid==IDC_PAGE)// Gère le retour arrière du texte de page( pas un edit)
		{
			txtpage=txtpage.Left(txtpage.GetLength()-1);
			wpage.SetWindowTextA(txtpage);
			wpage.RedrawWindow(0,0,1|256|RDW_ERASE);
			return TRUE;
		}
	}
	if(pMsg->message==WM_CHAR&&(CHAR)pMsg->wParam!=13)
	{	
		memw=pMsg->wParam;
		meml=pMsg->lParam;
		memmes=pMsg->message;
		if(kid==IDC_PAGE)
		{
			txtpage+=(CHAR)pMsg->wParam;
			wpage.SetWindowTextA(txtpage);
			wpage.RedrawWindow(0,0,1|256|RDW_ERASE);
		}
	}
	return FALSE;
}

void CConcertoDlg::ScanCode()
{
	CString temp;
	CString temp1;
	CString num;
	CString post;
	CString tcpt;
	CString tch;
	CString tp1;
	CString tp2;
	int i;
	int j;
	//CRect rct;
	if(scantxt.GetLength()==13)
	{
	//************* Control ticket TICKETPLACE ***************
		tempscan="TICKETPLACE";
		scantemp=scantxt;
		if(ControlTicketplace(scantxt,0)>0)
		{
			controlcolor=0x00FF00;
			//ctick.SetWindowText(scantxt[idx]);
			//ctt.SetWindowText("");
			SendSpot(2);
			goto FIN;
		}
		else
		{
			if(valid<0)
			{
				if(scantxt.Mid(0,1)!="1"&&scantxt.Mid(0,1)!="2")
				{
					controlcolor=0x0000FF;
					SendSpot(1);
					goto FIN;
				}
			}
			else
			{
				tempscan="";
MOXITY:;		
				if(scantxt.Mid(0,1)!="2")
				{
					scantemp=scantxt.Left(12);
					valid=0;
					controlcolor=0x0000FF;
					SendSpot(1);
					goto FIN;
				}
				post=scantxt.Mid(1,1);
				if(post=="0")
				{
	//************* Control ticket MOXITY ***************
					tempscan="MOXITY";
					scantemp=scantxt.Left(12);
					if(ControlMoxity(scantxt.Left(12),0)>0)
					{
						controlcolor=0x00FF00;
						SendSpot(2);
						goto FIN;
					}
					else
					{
						if(valid<0)
						{
							controlcolor=0x0000FF;
							SendSpot(1);
						}
						else
						{
							controlcolor=0x0000FF;
							SendSpot(1);
						}
						goto FIN;
					}
				}
	//************* Control ticket BARMATIC ***************
				scantemp=scantxt.Left(12);
				tempscan="";
				scantxt=scantxt.Mid(2,10);
				i=0;
				temp="";
				while(i<10)
				{
					tch=scantxt.Mid(9-i,1);
					for(j=0;j<10;j++)
					{
						if(cript[j]==tch)
							break;
					}
					j=j-i;
					if(j<0)
						j=10+j;
					tch.Format("%u",j);
					temp=tch+temp;
					i++;
				}
				num=temp.Mid(2,8);
				temp=temp.Left(2);

				tempscan=txtc[8]+" "+titretext+" ";//Prévente %nom 
				if(Control(post+temp+num,0)>0)
				{
					controlcolor=0x00FF00;
					SendSpot(2);
				}
				else
				{
					if(valid<0)
					{
						controlcolor=0x0000FF;
						SendSpot(1);

					}
					else
					{
						controlcolor=0x0000FF;
						SendSpot(1);
					}
				}
			}
		}
	}	
	else
	{
		if((i=scantxt.Find("moxity.com/s/",0))!=-1)
		{
			tempscan=scantxt.Left(i+10);
			temp=scantxt.Mid(i+13);
			double x=36;
			double res=0; 
			UCHAR ch;
			i=0;
			j=temp.GetLength()-1;
			while(j>=0)
			{
				ch=temp.GetAt(j);
				if(ch>57)
					ch-=39;
				ch-=0x30;
				res=res+(pow(x,i)*ch);
				i++;
				j--;
			}
			
			temp1.Format("%.f",res);
			//MessageBox(temp1);
			scantxt=temp1+"0";
			goto MOXITY;
		}
		else
			if(scantxt.GetLength()==7)
			{
	//************* Control ticket WEEZEVENT ***************
				tempscan="WeezEvent";
				scantemp=scantxt;
				temp=scantxt;
				if(ControlWeezEvent(scantxt,0)>0)
				{
					controlcolor=0x00FF00;
					SendSpot(2);
					goto FIN;
				}
				else
				{
					if(valid<0)
					{
						controlcolor=0x0000FF;
						SendSpot(1);
					}
					else
					{
						controlcolor=0x0000FF;
						SendSpot(1);
					}
					goto FIN;
				}
			}
			else
			{
				if(scantxt.GetLength()>=13)
				{
	//************* Control ticket BOUTIQUE WEB DINEOQUICK/ATRIUM ***************
					tempscan="WEB";;
					scantemp=scantxt;
					if(ControlAtrium(scantxt,0)>0)
					{
						goto SKIP;
					}
					else
					{
						if(valid<0)
						{
							controlcolor=0x0000FF;
							SendSpot(1);
						}
						else
						{
							controlcolor=0x0000FF;
							SendSpot(1);
						}
						goto FIN;
					}
					
				}
				else
					if(scantxt.GetLength()==10)
					{
	//************* Control ticket DIGITICK ***************
						tempscan="Digitick";
						scantemp=scantxt;
						if(ControlDigitick(scantxt,0)>0)
						{
							goto SKIP;
						}
						else
						{
							if(valid<0)
							{
								controlcolor=0x0000FF;
								SendSpot(1);
							}
							else
							{
								controlcolor=0x0000FF;
								SendSpot(1);
							}
							goto FIN;
						}
						
					}
					else
					{
						int code=1;
						scantemp=scantxt;
						tempscan="";
						controlcolor=0x0000FF;
						if(scantxt=="viewscan")
						{
	//************* Control SCAN QR ECRAN BASCULE ARRET/MARCHE AFFICHAGE DU CODE ***************
							if(viewscan)
							{				
								viewscan=0;
								scantemp=titretext;
							}
							else
							{
								viewscan=1;
								CString temp1;
								temp1=txtc[13];
								scantemp=temp1;//"Attente code";			
							}
							code=3;
						}
						SendSpot(code);//3);
					}
				}
	}
FIN:;
	if((!viewscan&&scantemp==titretext)||viewscan)
	{
		;
	}
	if(wsel==1)//affiche le code scanné en vert ou en rouge suivant validité
	{
		if(tempscan!="")
		{
			scan=tempscan+"\n"+scantemp;
			SCANMODE=DT_CENTER|DT_SINGLELINE|DT_VCENTER;
		}
		else
		{
			scan=scantemp;
			SCANMODE=DT_CENTER|DT_SINGLELINE|DT_VCENTER;
		}
		nscan.SetWindowPos(&wndTopMost,rctscan.left,rctscan.top,rctscan.Width(),rctscan.Height(),SWP_HIDEWINDOW   );
		nscan.SetWindowTextA("");
		RedrawWindow(&rctscan,NULL,1|256|4);
		nscan.SetWindowTextA(scan);
		nscan.ShowWindow(1);
		SetTimer(10, 10000, NULL);// affichage pendant 10 secondes
	}
	else
		nscan.ShowWindow(0);
SKIP:;
	nbctc=2;
	SetTimer(7,300,NULL);
}

void CConcertoDlg::OnStnDblclickNan()
{
	CString tempan;
	CString tempmois;
	san.GetWindowText(tempan);
	smois.GetWindowText(tempmois);
	ExportData(tempmois,tempan);
}

CString CConcertoDlg::CheckCurDataFile(CString cession)
{
	int idx;
	int idy;
	int ntic=0;
	CString temp;
	if(cession.Find("Open",0)==-1&&(idx=cession.Find("Open",0))>0)
		return "Erreur Format";
	if((idx=cession.Find("\r\n",0))==-1)
		return "Erreur Format";
	idx+=2;
	if(cession.Mid(idx,1)!="B"&&cession.Mid(idx,1)!="P")
		return cession;
	if((idy=cession.Find("\r\n",idx))==-1)
		return "Erreur Format";
	ntic=atoi(cession.Mid(idx+8,8));//initialisation N° ticket de départ
	ntic++;
	idx=idy+2;
	while((idy=cession.Find("\r\n",idx))!=-1)
	{
		if(cession.Mid(idx,1)!="B"&&cession.Mid(idx,1)!="P")
		{
			idy=idx;
			if((idx=cession.Find("B",idx))==-1||(idx=cession.Find("P",idx))==-1)
			{
				cession.SetAt(idy,0);
				cession.ReleaseBuffer(-1);
			}
			else
			{
				cession=cession.Left(idy)+cession.Mid(idx);
			}
			idx=idy;
			continue;
		}
		temp.Format("00000000%u",ntic);
		temp=temp.Right(8);
		if(cession.Mid(idx+8,8)==temp)
		{
			if(cession.Mid(idx+20,1)==";"&&cession.Mid(idx+38,1)==";")
			{
				idx=idy+2;
				ntic++;
			}
			else
			{
				return "Erreur Format";
			}
		}
		else
		{
			cession=cession.Left(idx)+cession.Mid(idy+2);
			continue;
		}
	}
	return cession;
}

int CConcertoDlg::ControlWeezEvent(CString billet,int remove)
{
	CString temp;
	int istop=0;
	int istart=0;
	HANDLE hf;
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
			dir=netcontdir+"\\"+temp;
			hf=(CreateFile(dir+"\\Controle.dat",GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL));
			if(hf==INVALID_HANDLE_VALUE)
				;
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
							if(buf.GetAt(istop+7)=='X')
							{
								CloseHandle(hf);
								valid=-1;
								return valid;
							}
							buf.SetAt(istop+7,'X');
							SetFilePointer(hf,NULL,NULL,FILE_BEGIN);
							WriteFile(hf,buf.GetBuffer(buf.GetLength()),buf.GetLength(),&nbw,NULL);
							SetEndOfFile(hf);	
							CloseHandle(hf);
							if(master)
								RefreshControlList();
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
					MessageBox(dir+"\\Controle.dat non lu.");
			}
			CloseHandle(hf);
		}	
		i++;
	}
	valid=0;
	return valid;
}

void CConcertoDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{

	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}


BOOL CConcertoDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	if(pcombo!=NULL&&message==WM_LBUTTONUP&&pWnd->GetSafeHwnd()==this->m_hWnd)
	{
		//MessageBox("CloseCombo");
		pcombo->CloseCombo();
		pcombo=NULL;
	}

	return CDialog::OnSetCursor(pWnd, nHitTest, message);
}



void CConcertoDlg::OnClose()
{
	wsel=0;
	if(hrun)
	{
		if(CloseHandle(hrun))
		{
			hrun=NULL;
		}
	}
	DeleteFile(controldir+"\\Run.dat");
	DeleteFile(controldir+"\\Status.dat");
	OnBnClickedQuitter();
}

void CConcertoDlg::OnEndSession(BOOL bEnding)
{
	CDialog::OnEndSession(bEnding);

	if(hrun)
	{
		if(CloseHandle(hrun))
		{
			hrun=NULL;
		}
	}
	DeleteFile(controldir+"\\Run.dat");
	DeleteFile(controldir+"\\Status.dat");
	// TODO: Add your message handler code here
}
void CConcertoDlg::FillStat(int index)
{	// Rempli les static d'articles avec l'index  envoyé ou efface si les champ de libellé sont vides
	CString text;
	CString temp;
	CString temp1;
	CString temp2;
	CString nart;
	CString date;
	CString jour;
	CString mois;
	CString an;
	int i;
	int idxstart=0;
	int idxstop=0;
	int idxmem=0;
	slibelcons.EnableWindow(0);
	slibel1.EnableWindow(0);
	slibel2.EnableWindow(0);
	spect.EnableWindow(0);
	guichet.EnableWindow(0);
	slibel1.SetWindowTextA(libel1[index]);
	slibel2.SetWindowTextA(libel2[index]);
	if(libel1[index]==""&&libel2[index]=="")//article vide
	{
		libelcons[index]="";
		prix[index]=0;
		perso[index]=1;
		valmix=0;
		valentry=1;
		valexo=0;
		valactif=0;
		valpass=0;
		if(nvalplace)
			vplace.ShowWindow(1);
		valplace=0;
		vplace.SetWindowTextA("");
		vactif.SetWindowTextA("");
		conso[index]=1;
		libelspect[index]="";
		spectsel[index]=0;
		sprix.SetWindowTextA("");
		sval1.SetWindowTextA("");
		sval2.SetWindowTextA("");
		stva1.SetWindowTextA("");
		stva2.SetWindowTextA("");
		scons.SetWindowTextA("");
		entrymode[index]=0;
		slibelcons.SetWindowTextA("");
		spect.SetWindowTextA("");
		guichet.SetWindowTextA("");
		nart.Format("%u",index);
		temp=txtc[62];//TVA
		vmix.ShowWindow(0);
		ventry.ShowWindow(1);
		vexo.ShowWindow(0);
		vpass.ShowWindow(0);
		vmix.SetWindowTextA(temp);
		ventry.SetWindowTextA(temp);
		temp1=txtc[4];//Entrée
		temp2=txtc[5];//immédiate
		nvcontrol.SetWindowText(temp1+"\n"+temp2);
		temp=txtc[62];//TVA
		ntva1.SetWindowTextA(temp+"1 :");//TVA
		ntva2.SetWindowTextA(temp+"2 :");//TVA
		ntva2.ShowWindow(0);
		stva2.ShowWindow(0);
		sval2.ShowWindow(0);
		nlibelcons.ShowWindow(1);
		slibelcons.ShowWindow(1);
		ncons.ShowWindow(1);
		scons.ShowWindow(1);
		text.Format("%u",conso[index]);
		scons.SetWindowTextA(text);
		nspect.ShowWindow(0);
		spect.SetWindowPos(&wndTop,(int)(oltou+ltou),(int)(ohnum+7*htou/16),(int)(5*ltou/3+eltou),(int)(htou/4),SWP_HIDEWINDOW);
		guichet.SetWindowPos(&wndTop,(int)(oltou+2*ltou+eltou),(int)(ohnum+7*htou/16),(int)(2.5*ltou/3),(int)(htou/4),SWP_HIDEWINDOW);
		AfxGetApp()->WriteProfileString(nart,"LIBELLE1","");
		AfxGetApp()->WriteProfileString(nart,"LIBELLE2","");
		AfxGetApp()->WriteProfileString(nart,"LIBELCONS","");
		AfxGetApp()->WriteProfileString(nart,"LIBELSPECT","");
		AfxGetApp()->WriteProfileInt(nart,"PERSO",1);
		AfxGetApp()->WriteProfileInt(nart,"CONSO",1);
		AfxGetApp()->WriteProfileInt(nart,"PRIX",0);
		AfxGetApp()->WriteProfileInt(nart,"VCONSO",0);
		AfxGetApp()->WriteProfileInt(nart,"VALCONSO",0);
		if(global)
			AfxGetApp()->WriteProfileInt(nart,"TVA",(DWORD)(atof(TVA)*100));
		else
			AfxGetApp()->WriteProfileInt(nart,"TVA",2000);
		AfxGetApp()->WriteProfileInt(nart,"TVA2",1000);
		AfxGetApp()->WriteProfileInt(nart,"SPECT",0);
		AfxGetApp()->WriteProfileInt(nart,"CONTROLE",0);
		slibelcons.EnableWindow(1);
		slibel1.EnableWindow(1);
		slibel2.EnableWindow(1);
		scons.EnableWindow(1);
	}
	else
	{
		slibelcons.SetWindowTextA(libelcons[index]);
		valexo=(perso[index]&0xFF0)>>4;
		if(valexo==0)
			text.Format("%u",conso[index]&0x00FF);
		else
			text.Format("%u",conso[index]&0x00FF);

		scons.SetWindowTextA(text);
		CString temp1;
		if(perso[index]&1)
			valentry=1;
		else
			valentry=0;
		if((perso[index]&2)&&nvalplace)
			valplace=1;
		else
			valplace=0;
		if((perso[index]&4)&&nvalmix)
			valmix=1;
		else
			valmix=0;
		if((perso[index]&8))
			valactif=1;
		else
			valactif=0;
		vpass.ShowWindow(0);
		valpass=0;
		if(entrymode[index]>0)//prévente sans horaire,prévente avec horaire
		{
			vplace.ShowWindow(0);
			vmix.ShowWindow(0);
			ventry.ShowWindow(0);
			if(cvalpass)//coche Pass active
			{
				vpass.ShowWindow(1);
				if((valpass=(perso[index]&0xF000)>>12)>1)//Exo associé?
				{
					vexo.ShowWindow(1);
				}
				else
				{
					vexo.ShowWindow(0);
				}
			}
			else
			{
				vexo.ShowWindow(0);
				vpass.ShowWindow(0);
			}
		}
		else//entree immediate ou produit
		{
			ventry.ShowWindow(1);
			if(valentry==0)
			{
				if(nvalmix)
					vmix.ShowWindow(1);
				vexo.ShowWindow(1);
				vplace.ShowWindow(0);
				vpass.ShowWindow(0);
				valplace=0;
				ncons.ShowWindow(1);
				ncons.SetWindowTextA(txtc[66]);//Nb Items
				scons.ShowWindow(1);
			}
			else
			{
				ncons.ShowWindow(1);
				ncons.SetWindowTextA(txtc[66]);//Nb Items
				scons.ShowWindow(1);
				vexo.ShowWindow(0);
				vpass.ShowWindow(0);
				vmix.ShowWindow(0)   ;
				if(nvalplace)
					vplace.ShowWindow(1);
			}

		}
		
		vpass.SetWindowTextA(temp1);
		vexo.SetWindowTextA(temp1);
		vactif.SetWindowTextA(temp1);
		ventry.SetWindowTextA(temp1);
		temp1=txtc[62];//TVA
		if(valmix&&nvalmix)
		{
			ntva1.SetWindowTextA(temp1+"1 :");//TVA
			ntva2.SetWindowTextA(temp1+"2 :");//TVA
			ntva2.ShowWindow(1);
			sval2.ShowWindow(1);
			stva2.ShowWindow(1);
		}
		else
		{
			ntva1.SetWindowTextA(temp1+" :");//TVA
			ntva2.ShowWindow(0);
			stva2.ShowWindow(0);
			sval2.ShowWindow(0);
		}

		temp1=txtc[7];//Place
		vplace.SetWindowTextA(temp1);
		temp1=txtc[131];//Pack
		vmix.SetWindowTextA(temp1);
		text.Format("%.2f",prix[index]);
		sprix.SetWindowTextA(text);
		text.Format("%.2f",tva1[index]);
		if(global)
		{
			stva1.SetWindowTextA(TVA+"%");
			text.Format("%.2f",val1[index]);
			sval1.SetWindowTextA(text);
		}
		else
		{
			stva1.SetWindowTextA(text+"%");
			text.Format("%.2f",val1[index]);
			sval1.SetWindowTextA(text);
		}
		text.Format("%.2f",tva2[index]);
		stva2.SetWindowTextA(text+"%");
		text.Format("%.2f",val2[index]);
		sval2.SetWindowTextA(text);
		if(entrymode[index])
		{
			nlibelcons.ShowWindow(0);
			slibelcons.ShowWindow(0);
			ncons.ShowWindow(0);
			scons.ShowWindow(0);
		}
		else
		{
			nlibelcons.ShowWindow(1);
			slibelcons.ShowWindow(1);
			if(valexo>0&&valentry==0)//pas une entree et exo
			{
				ncons.ShowWindow(1);
				ncons.SetWindowTextA(txtc[146]);//Nb Exo
				scons.ShowWindow(1);
			}
			if(valexo==0&&valentry==0)//pas une entree pas d'exo
			{
				scons.ShowWindow(1);
				ncons.SetWindowTextA(txtc[66]);//Nb Items
				ncons.ShowWindow(1);
			}
			if(valentry==1)
			{
				scons.ShowWindow(1);
				ncons.SetWindowTextA(txtc[66]);//Nb Items
				ncons.ShowWindow(1);
			}
		}
		if(entrymode[index]>0)//nvcontrol.GetCheck())
		{
			CString temp1;
			CString temp2;
			CString temp3;
			temp1=txtc[8];//Prévente
			temp2=txtc[9];//sans horaire
			temp3=txtc[10];//avec horaire
			if(valhor&&horaire&&entrymode[index]==1)			
				nvcontrol.SetWindowText(temp1+"\n"+temp2);
			else
			{
				if(valhor&&horaire&&entrymode[index]==2)			
					nvcontrol.SetWindowText(temp1+"\n"+temp3);
				else
					nvcontrol.SetWindowText(temp1);
			}
			temp1=txtc[11];//Date event 
			nspect.SetWindowTextA(temp1+" :");
			nspect.ShowWindow(1);
			spect.SetWindowPos(&wndTop,(int)(oltou+ltou),(int)(ohnum+7*htou/16),(int)(2.5*ltou/3+eltou),(int)(htou/4),SWP_SHOWWINDOW);
			guichet.SetWindowPos(&wndTop,(int)(oltou+2*ltou+eltou),(int)(ohnum+7*htou/16),(int)(2.5*ltou/3),(int)(htou/4),SWP_SHOWWINDOW);
			temp=libelspect[index];
			if((idxstop=temp.Find("/",0))!=-1)
			{
				if(idxstop>1)
					jour=temp.Mid(idxstop-2,2);
				else
					jour="";
				idxstop++;
				idxmem=idxstop;
				idxstart=idxstop;
				if((idxstop=temp.Find("/",idxstart))!=-1)
				{
					mois=temp.Mid(idxmem,idxstop-idxmem);
					idxstop++;
					i=atoi(temp.Mid(idxstop,temp.GetLength()-idxstop));
					an.Format("%u",i);
				}
				else
				{
					mois="";
					an="";
				}
				date=jour+"/"+mois+"/"+an;
			}
			else
				date="";
			spect.SetWindowTextA(date);
			if((idxstop=temp.Find(" ",0))!=-1)
				guichet.SetWindowTextA(temp.Mid(idxstop+1));
			else
				guichet.SetWindowTextA("");
			spect.EnableWindow(1);
			guichet.EnableWindow(1);
			slibel1.EnableWindow(1);
			slibel2.EnableWindow(1);
			//slibel2.EnableWindow(0);
		}
		else
		{
			CString temp1;
			CString temp2;
			CString temp3;
			temp1=txtc[4];//Entrée
			temp2=txtc[5];//immédiate
			nvcontrol.SetWindowText(temp1+"\n"+temp2);
			nspect.ShowWindow(0);
			spect.SetWindowPos(&wndTop,(int)(oltou+ltou),(int)(ohnum+7*htou/16),(int)(5*ltou/3+eltou),(int)(htou/4),SWP_HIDEWINDOW);
			guichet.SetWindowPos(&wndTop,(int)(oltou+2*ltou+eltou),(int)(ohnum+7*htou/16),(int)(2.5*ltou/3),(int)(htou/4),SWP_HIDEWINDOW);
			slibelcons.EnableWindow(1);
			slibel1.EnableWindow(1);
			slibel2.EnableWindow(1);
			scons.EnableWindow(1);
		}
	}
	if(eflag==1)// Code Barre ETC
	{
		BYTE bcons;
		if(valexo>0)//exo (n°article) associe à l'article
		{
			bcons=(BYTE)(((conso[index]&0xFF00)>>8));//recupere ne nb de conso de l'article dans le cas ou il est associé à un exo
			bcons++;
		}
		else // pas d'exo associe
			bcons=(BYTE)(conso[index]&0xFF);//nb conso
		if(index == 38 || index == 55){
 			temp1.Format(" bcons= %u",bcons);
			temp.Format(" conso= %u -> ",conso[index]);
			MessageBox(temp+temp1);
		}
		if(bcons>0) //nb conso >0
		{
			vcbx.ShowWindow(1);
			cbx = (perso[index]& 0xff0000)>>16;
			if(index == 38|| index == 55){
 				temp1.Format(" bcons= %u",bcons);
				temp.Format(" cbx= %u :: lp get count : %u ",cbx,pl.GetCount());
				MessageBox(temp+temp1);
			}
			if(cbx <= pl.GetCount())
			{
				vcbx.SetWindowText("");//redessine
			}
		}
		else
			vcbx.ShowWindow(0);
	}
	else
		vcbx.ShowWindow(0);
}

void CConcertoDlg::ClearStat(int i)
{	// Efface tous les statics d'un article
	CStringW wstr;
	CString temp;
	libel1[i]="";
	libel2[i]="";
	artim[i]="";
	wstr=workdir+artim[i];
	if(part[i])
		delete part[i];
	part[i]=Image::FromFile(wstr,0);
	temp.Format("%u",i);
	AfxGetApp()->WriteProfileString(temp,"IMAGE",artim[i]);
	FillStat(i);
	if(afmode)
	{
		InterlockedExchange(&FIM,1);
		RefreshImage();
	}
	SaveStaticArticle();
}

void CConcertoDlg::SaveStaticArticle()
{
	fsave=1;
	CString temp;
	CString temp1;
	int i;
	int j;
	int idx=artnum+(artrange*NAPP);
	double ptemp;
	CString nart;
	nart.Format("%u",idx);
	slibel1.GetWindowText(temp);
	libel1[idx]=temp;
	AfxGetApp()->WriteProfileString(nart,"LIBELLE1",temp);
	slibel2.GetWindowText(temp);
	libel2[idx]=temp;
	AfxGetApp()->WriteProfileString(nart,"LIBELLE2",temp);
	spect.GetWindowText(temp);
	libelspect[idx]=temp;
	AfxGetApp()->WriteProfileString(nart,"LIBELSPECT",temp);
	slibelcons.GetWindowText(temp);
	libelcons[idx]=temp;
	AfxGetApp()->WriteProfileString(nart,"LIBELCONS",temp);
	sprix.GetWindowText(temp);
	ptemp=atof(temp);
	temp.Format("%.2f",ptemp);
	/*if(eflag==1&&pl.FindStringExact(0,temp)==-1)
	{	// Si mode >ETC  et prix non répertorié on essaye de le rajouter dans la liste
		if(pl.GetCount()<20)//Uniquement si on a mois de 20 prix et qu'une conso au moins est incluse
		{	
			temp1.Format("%u",pl.AddString(temp));
			AfxGetApp()->WriteProfileString("Prix",temp1,temp);
			prix[idx]=atof(temp);
			AfxGetApp()->WriteProfileInt(nart,"PRIX",(int)(prix[idx]*100));
		}
		else //gestion de la liste des code barre en cas de plus de 20 prix dans la liste
		{
			int jmax=pl.GetCount();
			for(j=0;j<jmax;j++)
			{
				pl.GetText(j,temp1);
				for(i=1;i<=NART;i++)// on parcoure la liste et on regarde si le prix existe encore dans les articles
				{
					temp.Format("%.2f",prix[i]);
					if(temp==temp1&&i!=idx)
					{
						break; // on passe au prix suivant
					}
				}
				if(i>NART)// si le prix n'existe plus on a donc un emplacement de libre où on peut rajouter ce nouveau prix
				{
					prix[idx]=ptemp;
					AfxGetApp()->WriteProfileInt(nart,"PRIX",(int)(ptemp*100));
					pl.DeleteString(j);
					temp.Format("%.2f",ptemp);
					pl.InsertString(j,temp);
					temp1.Format("%u",j);
					AfxGetApp()->WriteProfileString("Prix",temp1,temp);
					temp1.Format("%u",j+1);
					MessageBox("La valeur de la reprise N°"+temp1+" doit être modifiée sur la caisse");
					break;
				}
			}
			if(j==jmax&&jmax==pl.GetCount())
			{
				MessageBox("Plus d'espace nécessaire pour une nouvelle valeur.\n Solution :\n - Aligner le prix sur celui d'un article existant.\n - Supprimer un article inutile. ");
				scons.SetWindowText("0");
				conso[idx]=0;
				AfxGetApp()->WriteProfileInt(nart,"CONSO",0);
			}				
		}
	}
	else*/
	{
		prix[idx]=ptemp;
		AfxGetApp()->WriteProfileInt(nart,"PRIX",(int)(prix[idx]*100));
	}
	//sprix.SetWindowText(temp);
	stva1.GetWindowText(temp);
	if(temp!="")
	{
		if(atoi(temp)>30)
			temp="20";
		if(temp=="")
			temp="20.0";
		tva1[idx]=atof(temp);
		AfxGetApp()->WriteProfileInt(nart,"TVA",(int)(tva1[idx]*100));
	}
	temp.Format("%.2f",tva1[idx]);
	stva1.SetWindowText(temp+"%");

	temp.Format("%.2f",val1[idx]);
	sval1.SetWindowText(temp);
	ptemp=atof(temp)*100;
	AfxGetApp()->WriteProfileInt(nart,"VAL1",(int)ptemp);
	if(valmix)
	{
		stva2.GetWindowText(temp);
		if(temp!="")
		{
			if(atof(temp)>30)
				temp="10";
			if(temp=="")
				temp="10.0";
			if(atof(temp)==0)
			{
				val2[idx]=0;
				val1[idx]=prix[idx];
				temp1.Format("%.2f",val1[idx]);
				sval1.SetWindowText(temp1);
				ptemp=atof(temp1)*100;
				AfxGetApp()->WriteProfileInt(nart,"VAL1",(int)ptemp);
			}
			tva2[idx]=atof(temp);
			AfxGetApp()->WriteProfileInt(nart,"TVA2",(int)(tva2[idx]*100));
			temp.Format("%.2f",val2[idx]);
			sval2.SetWindowText(temp);
			ptemp=atof(temp)*100;
			AfxGetApp()->WriteProfileInt(nart,"VAL2",(int)ptemp);
		}
		temp.Format("%.2f",tva2[idx]);
		stva2.SetWindowText(temp+"%");
	}
	else
	{
		val2[idx]=0;
		tva2[idx]=0;
		temp.Format("%.2f",tva2[idx]);
		stva2.SetWindowText(temp+"%");
		temp.Format("%.2f",val2[idx]);
		sval2.SetWindowText(temp);
		AfxGetApp()->WriteProfileInt(nart,"VAL2",(int)0);
		AfxGetApp()->WriteProfileInt(nart,"TVA2",(int)0);
	}
	if(cvalpass==0)
	{
		vpass.ShowWindow(0);
		valpass=0;
	}
	perso[idx]=valentry+(valplace*2)+(valmix*4)+(valactif*8)+(valexo*0x10)+(valpass*0x1000)+(cbx*0x10000);//+(xxx*0x10000000)
	AfxGetApp()->WriteProfileInt(nart,"PERSO",perso[idx]);
	spect.GetWindowText(libelspect[idx]);
	guichet.GetWindowText(temp);
	if(temp!="")
		libelspect[idx]=libelspect[idx]+" "+temp;
	AfxGetApp()->WriteProfileString(nart,"LIBELSPECT",libelspect[idx]);
	AfxGetApp()->WriteProfileInt(nart,"VALCONSO",entrymode[idx]);
	AfxGetApp()->WriteProfileInt(nart,"VCONSO",entrymode[idx]);
	if(entrymode[idx])
		scons.SetWindowText("1");
	FART=1;
	RefreshArticle();// Passe les articles aux autres billetteries esclaves si maitre
	//SetFocus();
	//FillStat(idx);
	DrawBoutonArticle(17);//Pour prendre en compte le changement éventuel d'un libellé ou d'une image
}

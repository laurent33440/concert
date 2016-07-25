// Message.cpp : implementation file
//

#include "stdafx.h"
#include "Concerto.h"
#include "ConcertoDlg.h"
#include "ImportMessage.h"


// CImport dialog

IMPLEMENT_DYNAMIC(CImport, CDialog)

CImport::CImport(CWnd* pParent /*=NULL*/)
	: CDialog(CImport::IDD, pParent)
	, nmes1(_T(""))
	, nmes2(_T(""))
	, nmes3(_T(""))
{

}

CImport::~CImport()
{
}

void CImport::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, bok);
	DDX_Control(pDX, IDC_STITRE, stitre);
	DDX_Control(pDX, IDC_SNMES1, snmes1);
	DDX_Control(pDX, IDC_SNMES2, snmes2);
	DDX_Control(pDX, IDC_SNMES3, snmes3);
	DDX_Control(pDX, IDC_LBASE, lba);
	DDX_Text(pDX, IDC_STITRE, entete);
	DDX_Text(pDX, IDC_SNMES1, nmes1);
	DDX_Text(pDX, IDC_SNMES2, nmes2);
	DDX_Text(pDX, IDC_SNMES3, nmes3);
	DDX_Control(pDX, IDCANCEL, bca);
}


BEGIN_MESSAGE_MAP(CImport, CDialog)
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDOK, &CImport::OnBnClickedOk)
	ON_STN_CLICKED(IDC_SNMES1, &CImport::OnStnClickedSnmes1)
	ON_BN_CLICKED(IDCANCEL, &CImport::OnBnClickedCancel)
	ON_LBN_SELCHANGE(IDC_LBASE, &CImport::OnLbnSelchangeLbase)
END_MESSAGE_MAP()


// CImport message handlers
BOOL CImport::OnInitDialog()
{
	CConcertoDlg* ppar=(CConcertoDlg*)GetParent();
	CString temp;
	int i;
	int j;
	int xn;
	int h;
	CRect wrct;
	CRect rct[9];
	GetDesktopWindow( )->GetWindowRect(&wrct);
	wlargeur=wrct.Width();
	whauteur=wrct.Height()/4;
	color=0;
	CDialog::OnInitDialog();
	entete="IMPORTATION DE BASE DE BILLETS";
	nmes1="Sélectionner les évènements à importer";
	nmes2="";
	nmes3="";
	UpdateData(FALSE);
	dlgrefcolor=AfxGetApp()->GetProfileInt("Couleur","dlgrefcolor",0x00000000);
	txtdlgrefcolor=AfxGetApp()->GetProfileInt("Couleur","txtdlgrefcolor",0x00FF0000);
	butdlgrefcolor=AfxGetApp()->GetProfileInt("Couleur","butdlgrefcolor",0x00000000);
	txtbutdlgrefcolor=AfxGetApp()->GetProfileInt("Couleur","txtbutdlgrefcolor",0x00FF0000);
	coloren=AfxGetApp()->GetProfileInt("Param","Color",0);
	staticfont.CreateFont(whauteur/8, //FONT DES CHAMPS ET LISTE
		0,//wlargeur/80,
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
	butdlgfont.CreateFont(whauteur/7, //FONT DES CHAMPS ET LISTE
		0,//wlargeur/80,
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
	CDC* pdc=GetDC();
	CFont* pof;
	pof=pdc->SelectObject(&staticfont);
	pdc->DrawText(entete,&rct[0],DT_CALCRECT);
	pdc->DrawText(nmes1,&rct[1],DT_CALCRECT);
	pdc->DrawText(nmes2,&rct[2],DT_CALCRECT);
	pdc->DrawText(nmes3,&rct[3],DT_CALCRECT);
	pof=pdc->SelectObject(pof);
	ReleaseDC(pdc);

	i=0;
	xn=rct[1].Width();
	h=rct[1].Height();
	largeurn=xn+10;
	hauteur=h;
	orgh=hauteur;
	{
		orgt = (wlargeur/2)-(rct[0].Width()/2);
		orgm = (wlargeur/2)-(rct[1].Width()/2);
		stitre.SetWindowPos(&wndTop,orgt,orgh,rct[0].Width(),hauteur,SWP_SHOWWINDOW   );
	}

	orgn=(wlargeur-(largeurn))/2;
	orgh+=hauteur;
	orgh+=hauteur;
	snmes1.SetWindowPos(&wndTop,orgm,orgh,largeurn,hauteur,SWP_SHOWWINDOW   );
	orgh+=hauteur;
	orgh+=hauteur;
	orgn=(wlargeur/2)-(8*wlargeur/20);
	lba.SetWindowPos(&wndTop,orgn,orgh,4*wlargeur/5,((int)ppar->htou/5)*6,SWP_SHOWWINDOW   );
	lba.SetItemHeight(0,(UINT)(ppar->htou/5));
	orgh+=((int)ppar->htou/5)*6;
	orgh+=hauteur;
	color=0;
	SetWindowPos(&wndTop,0,0,wlargeur,orgh+(3*hauteur),SWP_HIDEWINDOW   );
	CenterWindow(0);
	ShowWindow(1);
	DrawButton();
	if((i=SearchBase())>0)
	{
		j=0;
		do
		{
			GetEvtName(j);
			j++;
		}
		while(j<i);
	}
	sel=-1;
	return TRUE;  // retourne TRUE, sauf si vous avez défini le focus sur un contrôle
}

void CImport::DrawButton()
{
	CDC* pdc=GetDC();
	CDC m_Cdc;
	m_Cdc.CreateCompatibleDC(NULL);
	CBitmap* tempbitmap;
	CRect rct;
	CRect rect;
	int bhauteur=hauteur*2;
	CFont* poldfont=m_Cdc.SelectObject(&butdlgfont);
	bl=wlargeur/3;
	rct.top=0;
	rct.left=0;
	rct.right=bl-10;
	rct.bottom=(bhauteur)-10;
	//BOUTON MANAGER

	orgt=(wlargeur/2)+(bl/4);
	bok.SetWindowPos(&wndTop,orgt,orgh,bl,bhauteur,SWP_SHOWWINDOW   );
	bmpok.DeleteObject();
	bmpok.CreateCompatibleBitmap(pdc,rct.Width(),rct.Height());
	tempbitmap=m_Cdc.SelectObject(&bmpok);
	m_Cdc.FillSolidRect(&rct,butdlgrefcolor);
	m_Cdc.SetTextColor(txtbutdlgrefcolor);
	m_Cdc.DrawText("Valider",-1,&rct,DT_CENTER|DT_SINGLELINE|DT_VCENTER );
	m_Cdc.SelectObject(tempbitmap);
	bok.SetBitmap(( HBITMAP)bmpok);

	orgt=(wlargeur/2)-(bl/4)-bl;
	bca.SetWindowPos(&wndTop,orgt,orgh,bl,bhauteur,SWP_SHOWWINDOW);
	bmpca.DeleteObject();
	bmpca.CreateCompatibleBitmap(pdc,rct.Width(),rct.Height());
	tempbitmap=m_Cdc.SelectObject(&bmpca);
	m_Cdc.FillSolidRect(&rct,butdlgrefcolor);
	m_Cdc.SetTextColor(txtbutdlgrefcolor);
	m_Cdc.DrawText("Annuler",-1,&rct,DT_CENTER|DT_SINGLELINE|DT_VCENTER );
	m_Cdc.SelectObject(tempbitmap);
	bca.SetBitmap(( HBITMAP)bmpca);
	m_Cdc.SelectObject(poldfont);
	ReleaseDC(pdc);
	
}

HBRUSH CImport::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	CConcertoDlg* ppar=(CConcertoDlg*)GetParent();
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	int i=pWnd->GetDlgCtrlID();
	if(i==IDC_STITRE||i==IDC_SNMES1||i==IDC_SNMES2||i==IDC_SNMES3)
	{
		hbr=(HBRUSH)GetStockObject(WHITE_BRUSH);
		pDC->SetBkColor(0xFFFFFF);
		pDC->SetTextColor(0);
		pDC->SelectObject(&ppar->geostat);
	}
	if(pWnd->GetDlgCtrlID()==IDC_LBASE)
	{
		hbr=(HBRUSH)GetStockObject(BLACK_BRUSH);
		pDC->SetBkColor(0);
		pDC->SetTextColor(0xFFFFFF);
		pDC->SelectObject(&ppar->geodate);
	}

	return hbr;
}

BOOL CImport::OnEraseBkgnd(CDC* pDC)
{
	CRect rct;
	GetWindowRect(&rct);
	ScreenToClient(&rct);
	pDC->SelectStockObject(WHITE_BRUSH);
	pDC->Rectangle(&rct);

	return 0;//CDialog::OnEraseBkgnd(pDC);
}

void CImport::OnStnClickedSnmes1()
{
}

void CImport::OnBnClickedOk()
{
	OnOK();
}

void CImport::OnPaint()
{
	CPaintDC dc(this); // device context for painting

}
LRESULT CImport::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	int i;
	CWnd* pw;
	HBRUSH hbr;
	CConcertoDlg* ppar=(CConcertoDlg*)GetParent();
	if(message==WM_CTLCOLORLISTBOX )// COMMANDE DE SELECTION ENTRE LES LISTES DONNEE PAR CELLE QUI A L'ASCENCEUR
	{
		CDC* pDC;
		pw=CWnd::FromHandle((HWND)lParam);
		i=pw->GetDlgCtrlID();
		pDC=CDC::FromHandle((HDC)wParam);
		ticketbrush.DeleteObject();
		ticketbrush.CreateSolidBrush(ppar->sconfigrefcolor);
		hbr=(HBRUSH)GetStockObject(BLACK_BRUSH);
		pDC->SetBkColor(0);
		pDC->SetTextColor(0xFFFFFF);
		return (LRESULT)hbr;
	}
	return CDialog::DefWindowProc(message, wParam, lParam);
}


void CImport::OnBnClickedCancel()
{
	sel=-1;
	OnCancel();
}

int CImport::SearchBase()
{
	BOOL result;
	CFileFind ff;
	int i;
	outpath="X:\\*.*";
	char ch='D';
	CString temp;
	i=0;
	do
	{
		outpath.SetAt(0,ch);
		result=ff.FindFile(outpath,0);
		while(result)
		{
			result=ff.FindNextFile();
			if (ff.IsDots())
			 continue;
			if (ff.IsDirectory())
			 continue;
			if(ff.GetFileName().Find(".mev",0)!=-1||ff.GetFileName().Find("Ticket",0)!=-1)
			{
				source[i]=ff.GetFilePath();
				i++;
			}
		}
		ff.Close();
		ch++;
	}
	while(ch!='Z'&&i<100);
	return i;
}

void CImport::GetEvtName(int idx)
{
	HANDLE hf;
	CString buf;
	CString temp;
	CString jour;
	CString mois;
	CString an;
	DWORD len;
	int idxstart;
	int idxstop;
	int idxmem;
	int i;
	hf=CreateFile(source[idx],FILE_ALL_ACCESS,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if(ReadFile(hf,buf.GetBuffer(GetFileSize(hf,NULL)),GetFileSize(hf,NULL),&len,NULL))
	{
		buf.ReleaseBuffer(len);
		if(source[idx].Find("Ticket",0)==-1)
		{
			if((idxstart=buf.Find("<title>",0))!=-1)
				if((idxstop=buf.Find("@",idxstart))!=-1||(idxstop=buf.Find("</title>",idxstart))!=-1)
				{
					titre=buf.Mid(idxstart+7,(idxstop-idxstart-7));
					if((idxstart=buf.Find("<date>",idxstop))!=-1)
						if((idxstop=buf.Find("</date>",idxstart))!=-1)
						{
							temp=buf.Mid(idxstart+6,10);
							date=temp.Right(2);
							date=date+temp.Mid(4,4);
							date=date+temp.Left(4);
							lba.SetItemData(lba.AddString(titre+" le "+date),idx);
						}
				}
		}
		else
		{
			idxstart=0;
			if((idxstop=buf.Find("\r\n",idxstart))!=-1)
			{
				poste=buf.Mid(idxstart,(idxstop-idxstart));
				idxstart=idxstop+2;
				if((idxstop=buf.Find("\r\n",idxstart))!=-1)
				{
					libel1=buf.Mid(idxstart,(idxstop-idxstart));
					idxstart=idxstop+2;
					if((idxstop=buf.Find("\r\n",idxstart))!=-1)
					{
						libel2=buf.Mid(idxstart,(idxstop-idxstart));
						titre=libel1+" "+libel2;
						idxstart=idxstop+2;
						if((idxstop=buf.Find("\r\n",idxstart))!=-1)
						{
							temp=buf.Mid(idxstart,(idxstop-idxstart));
							if((idxstop=temp.Find("/",0))!=-1)
							{
								if(idxstop>2)
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
						}
						if(date=="")
							lba.SetItemData(lba.AddString(titre),idx);
						else
							lba.SetItemData(lba.AddString(titre+" le "+date),idx);
					}
				}
			}
		}
	}
	CloseHandle(hf);
}

void CImport::OnLbnSelchangeLbase()
{
	sel=(int)lba.GetItemData(lba.GetCurSel());
}

// Num.cpp : implementation file
//

#include "stdafx.h"
#include "Concerto.h"
#include "ConcertoDlg.h"
#include "Num.h"


// CNum dialog

IMPLEMENT_DYNAMIC(CNum, CDialog)

CNum::CNum(CWnd* pParent /*=NULL*/)
	: CDialog(CNum::IDD, pParent)
	{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

}

CNum::~CNum()
{
}

void CNum::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SNUM, wnum);
	DDX_Control(pDX, IDC_SMESSAGE, smessage);
}

BEGIN_MESSAGE_MAP(CNum, CDialog)
	ON_BN_CLICKED(IDC_10, &CNum::OnBnClicked0)
	ON_BN_CLICKED(IDC_6, &CNum::OnBnClicked1)
	ON_BN_CLICKED(IDC_7, &CNum::OnBnClicked2)
	ON_BN_CLICKED(IDC_8, &CNum::OnBnClicked3)
	ON_BN_CLICKED(IDC_3, &CNum::OnBnClicked4)
	ON_BN_CLICKED(IDC_4, &CNum::OnBnClicked5)
	ON_BN_CLICKED(IDC_5, &CNum::OnBnClicked6)
	ON_BN_CLICKED(IDC_0, &CNum::OnBnClicked7)
	ON_BN_CLICKED(IDC_1, &CNum::OnBnClicked8)
	ON_BN_CLICKED(IDC_2, &CNum::OnBnClicked9)
	ON_BN_CLICKED(IDC_9, &CNum::OnBnClickedPM)
	ON_BN_CLICKED(IDC_11, &CNum::OnBnClickedPD)
	ON_BN_CLICKED(IDC_12, &CNum::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_13, &CNum::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CNum::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CNum::OnBnClickedOk)
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_CTLCOLOR()
	ON_STN_CLICKED(IDC_SNUM, &CNum::OnStnClickedSnum)
	ON_WM_DRAWITEM()
	ON_BN_DOUBLECLICKED(IDC_0, &CNum::OnBnClicked7)
	ON_BN_DOUBLECLICKED(IDC_1, &CNum::OnBnClicked8)
	ON_BN_DOUBLECLICKED(IDC_2, &CNum::OnBnClicked9)
	ON_BN_DOUBLECLICKED(IDC_3, &CNum::OnBnClicked4)
	ON_BN_DOUBLECLICKED(IDC_4, &CNum::OnBnClicked5)
	ON_BN_DOUBLECLICKED(IDC_5, &CNum::OnBnClicked5)
	ON_BN_DOUBLECLICKED(IDC_6, &CNum::OnBnClicked1)
	ON_BN_DOUBLECLICKED(IDC_7, &CNum::OnBnClicked2)
	ON_BN_DOUBLECLICKED(IDC_8, &CNum::OnBnClicked3)
	ON_BN_DOUBLECLICKED(IDC_9, &CNum::OnBnClickedPM)
	ON_BN_DOUBLECLICKED(IDC_10, &CNum::OnBnClicked0)
	ON_BN_DOUBLECLICKED(IDC_11, &CNum::OnBnClickedPD)
	ON_BN_DOUBLECLICKED(IDC_12, &CNum::OnBnClickedCancel)
	ON_BN_DOUBLECLICKED(IDC_13, &CNum::OnBnClickedOk)
END_MESSAGE_MAP()



BOOL CNum::OnInitDialog()
{
	CStringW wstr;
	CString temp;
	CDialog::OnInitDialog();
	snumrefcolor=0;
	backnumrefcolor=0xFFFFFF;
	butnumrefcolor=0;
	txtsnumrefcolor=0;
	txtbacknumrefcolor=0xFFFFFF;
	txtbutnumrefcolor=0;
	color=0;
	CString sourcedir;
	CString workdir;
	GetModuleFileName(NULL,sourcedir.GetBuffer(256),256);
	sourcedir.ReleaseBuffer(-1);
	workdir=sourcedir.Left(sourcedir.ReverseFind('\\')+1);
	CString skindir=workdir+"Skin\\";

	temp=skindir+"btn_article_etat1.jpg";
	wstr=temp;
	pbnartbo=Image::FromFile(wstr,0);
	temp=skindir+"btn_article_etat2.jpg";
	wstr=temp;
	pbsartbo=Image::FromFile(wstr,0);
	Table[0]="7";
	Table[1]="8";
	Table[2]="9";
	Table[3]="4";
	Table[4]="5";
	Table[5]="6";
	Table[6]="1";
	Table[7]="2";
	Table[8]="3";
	Table[9]="-/+";
	Table[10]="0";
	Table[11]=".";
	Table[12]="C";
	Table[13]="OK";
	if(txtmessage!="")
		offset=(whauteur/7);
	else
		offset=0;
	numflag=0;
	butnumfont.CreateFont(whauteur/10,
		0,
		0,
		0,
		700,//Epaisseur
		0,
		0,
		0,
		DEFAULT_CHARSET,
		OUT_TT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		PROOF_QUALITY,
		DEFAULT_PITCH|FF_DONTCARE,
		"GeosansLight");
	mesnumfont.CreateFont(whauteur/10,
		0,
		0,
		0,
		700,//Epaisseur
		0,
		0,
		0,
		DEFAULT_CHARSET,
		OUT_TT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		PROOF_QUALITY,
		DEFAULT_PITCH|FF_DONTCARE,
		"GeosansLight");
	SetWindowPos(&wndTop,0,0,wlargeur,whauteur+offset,SWP_HIDEWINDOW   );//wxwy
	CenterWindow(0);
	ShowWindow(1);
	DrawNumButton();
	if(mode==2)
	{
		wnum.SetWindowTextA(prxtxt+" / ");
	}
	nombre="";
	if(mode==4)
		wnum.ModifyStyle(SS_RIGHT,SS_CENTER,0);
	return TRUE;  // retourne TRUE, sauf si vous avez défini le focus sur un contrôle
}
void CNum::Display()
{
	CString temp;
	CString tot;
	CString div;
	int i=0;
	double pxdiv;
	if(mode==2)
	{
		if(atoi(nombre)>=1)
		{	
			pxdiv=atof(prxtxt);
			div.Format("%.2f",pxdiv/atoi(nombre));
			temp=prxtxt+" / "+nombre+" = "+div;
		}
		else
			temp=prxtxt+" / ";
		wnum.SetWindowTextA(temp);
		if(atoi(nombre)>1)
		{	pxdiv=atof(prxtxt);
			div.Format("%.2f",pxdiv/atoi(nombre));
			temp=prxtxt+"\n/ "+nombre+"\n"+div;
		}
		else
			temp=prxtxt;
		GetParent()->GetDlgItem(nID)->SetWindowTextA(temp);
	}
	else
	{
		if(mode<4)
		{
			wnum.SetWindowTextA(nombre);
			if(nID!=IDC_DUM)
			{
				GetParent()->GetDlgItem(nID)->SetWindowTextA(nombre);
			}
			if(nID==IDC_VAL1||nID==IDC_VAL2)
			{
				GetDlgItem(IDC_9)->EnableWindow(0);
				GetDlgItem(IDC_9)->SetWindowText("");
			}

		}
		else
		{
			i=0;
			temp="";
			while(i<nombre.GetLength())
			{
				temp+="*";
				i++;
			}
			wnum.SetWindowTextA(temp);
		}
	}
}
BOOL CNum::PreTranslateMessage( MSG* pMsg )// Commande provenant du scanner ou du clavier
{
	CString temp;
	CString num;
	CString post;
	CString tcpt;
	CString tch;
	CString tp1;
	CString tp2;
	if(pMsg->message==WM_CHAR&&(CHAR)pMsg->wParam==8)
	{
		if(nombre.GetLength()>0)
		nombre=nombre.Left(nombre.GetLength()-1);
		Display();
		return TRUE;
	}
	if(pMsg->message==WM_CHAR&&(CHAR)pMsg->wParam==13)
	{
		OnBnClickedOk();
		return TRUE;
	}
	if(pMsg->message==WM_KEYDOWN&&(CHAR)pMsg->wParam==27)
	{
		OnBnClickedCancel();
		return TRUE;
	}
	if(pMsg->message==WM_CHAR&&(CHAR)pMsg->wParam!=13)
	{
		if(((CHAR)pMsg->wParam>=0x30&&(CHAR)pMsg->wParam<=0x39)||(CHAR)pMsg->wParam=='.')
		{
			if((nombre.GetLength()<chiffre&&mode!=2)||(mode==2&&nombre.GetLength()<chiffre))
				if(nombre=="0"&&mode<1)
					nombre=(CHAR)pMsg->wParam;
				else
					nombre+=(CHAR)pMsg->wParam;
				Display();
		}
		return TRUE;
	}
	return FALSE;
}


void CNum::OnBnClicked0()
{
	if((nombre.GetLength()<chiffre&&mode!=2)||(mode==2&&nombre.GetLength()<chiffre))
		nombre+="0";
	Display();
}

void CNum::OnBnClicked1()
{
	if((nombre.GetLength()<chiffre&&mode!=2)||(mode==2&&nombre.GetLength()<chiffre))
		if(nombre=="0"&&mode<1)
			nombre="1";
		else
			nombre+="1";
		Display();
}

void CNum::OnBnClicked2()
{
	if(((nombre.GetLength()<chiffre&&mode!=2)||(mode==2&&nombre.GetLength()<chiffre)))
		if(nombre=="0"&&mode<1)
			nombre="2";
		else
			nombre+="2";
	Display();
}

void CNum::OnBnClicked3()
{
	if(((nombre.GetLength()<chiffre&&mode!=2)||(mode==2&&nombre.GetLength()<chiffre)))
		if(nombre=="0"&&mode<1)
			nombre="3";
		else
			nombre+="3";
	Display();
}

void CNum::OnBnClicked4()
{
	if(((nombre.GetLength()<chiffre&&mode!=2)||(mode==2&&nombre.GetLength()<chiffre)))
		if(nombre=="0"&&mode<1)
			nombre="4";
		else
		nombre+="4";
	Display();
}

void CNum::OnBnClicked5()
{
	if(((nombre.GetLength()<chiffre&&mode!=2)||(mode==2&&nombre.GetLength()<chiffre)))
		if(nombre=="0"&&mode<1)
			nombre="5";
		else
			nombre+="5";
	Display();
}

void CNum::OnBnClicked6()
{
	if(((nombre.GetLength()<chiffre&&mode!=2)||(mode==2&&nombre.GetLength()<chiffre)))
		if(nombre=="0"&&mode<1)
			nombre="6";
		else
			nombre+="6";
	Display();
}

void CNum::OnBnClicked7()
{
	if(((nombre.GetLength()<chiffre&&mode!=2)||(mode==2&&nombre.GetLength()<chiffre)))
		if(nombre=="0"&&mode<1)
			nombre="7";
		else
			nombre+="7";
	Display();
}

void CNum::OnBnClicked8()
{
	if(((nombre.GetLength()<chiffre&&mode!=2)||(mode==2&&nombre.GetLength()<chiffre)))
		if(nombre=="0"&&mode<1)
			nombre="8";
		else
			nombre+="8";
	Display();
}

void CNum::OnBnClicked9()
{
	if(((nombre.GetLength()<chiffre&&mode!=2)||(mode==2&&nombre.GetLength()<chiffre)))
		if(nombre=="0"&&mode<1)
			nombre="9";
		else
			nombre+="9";
	Display();
}
void CNum::OnBnClickedPM()
{
	if(mode==3)
	{
		if(nID==IDC_VAL1&&nombre=="")
		{
			nombre="2/3";
			OnOK();
		}
		else
			if(nID==IDC_VAL2&&nombre=="")
			{
				nombre="1/3";
				OnOK();
			}
			/*else
			{
				if(nID!=IDC_VAL1&&nID!=IDC_VAL2)
					if(nombre.GetLength()<chiffre)
						if(nombre.GetAt(0)=='-')
							nombre=nombre.Right(nombre.GetLength()-1);
						else
							nombre="-"+nombre;
				Display();
			}*/
	}
}

void CNum::OnBnClickedPD()
{
	if(mode==3)
	{
		if(nombre.GetLength()<chiffre)
			nombre+=".";
		Display();
	}
}

void CNum::OnBnClickedCancel()
{
	if(mode!=2)
	{
		nombre=nombre.Left(nombre.GetLength()-1);
		Display();
		if(nID==IDC_VAL1||nID==IDC_VAL2)
		{
			GetDlgItem(IDC_9)->EnableWindow(1);
			GetDlgItem(IDC_9)->SetWindowText("");
	}
	else
	{
		nombre="";
		Display();
		}
	}
}

void CNum::OnBnClickedOk()
{
	if(mode==1)
	{
		if(nombre.GetLength()==1)
			nombre="0"+nombre;
		if(nID!=IDC_DUM)
		{
			GetParent()->GetDlgItem(nID)->SetWindowTextA(nombre);
		}
	}
	OnOK();
}

BOOL CNum::OnEraseBkgnd(CDC* pDC)
{
	CBrush backnumrefcolorbr(0xFFFFFF);
	CBrush* ptbr;
	CBrush OrigBrush;

	ptbr=pDC->SelectObject(&backnumrefcolorbr);
	pDC->Rectangle(0,0,wlargeur,whauteur+offset);
	pDC->SelectObject(ptbr);
	backnumrefcolorbr.DeleteObject();

	return 0;//CDialog::OnEraseBkgnd(pDC);
}
void CNum::DrawNumButton()
{
	CRect rect;
	int i;
	int x;
	int y;
	int largeur;//
	int hauteur;//

	//Calcul de la position et dimension des boutons suivant taille de la fenêtre
	if(txtmessage!="")
	{
		smessage.SetWindowPos(&wndBottom,(int)((float)(wlargeur/65)),(int)((float)(whauteur/70)),(int)((float)(wlargeur/1.04)),(int)((float)(whauteur/7)),SWP_SHOWWINDOW);
		smessage.SetWindowText(txtmessage);
	}
	else
	{
		smessage.ShowWindow(0);
	}
	wnum.SetWindowPos(&wndBottom,(int)((float)(wlargeur/65)),(int)((float)(whauteur/70)+offset),(int)((float)(wlargeur/1.04)),(int)((float)(whauteur/7)),SWP_SHOWWINDOW);

	//Boutons CHIFFRE

	largeur=(int)((float)(wlargeur/3.2));//
	hauteur= (int)((float)(whauteur/6.5));//
	i=0;
	x=(int)((float)(wlargeur/65));
	y=(int)((float)(whauteur/6)+offset);
	do
	{
		rect.left=x;
		rect.top=y;
		rect.right=(x)+largeur;
		rect.bottom=(y)+hauteur;
		if(i==12)
			largeur=(int)((float)(1.53*(largeur)));
		((CButton*)GetDlgItem(IDC_0+i))->SetWindowPos(&wndBottom,x,y,largeur,hauteur,SWP_HIDEWINDOW);
		((CButton*)GetDlgItem(IDC_0+i))->SetWindowPos(&wndBottom,x,y,largeur,hauteur,SWP_SHOWWINDOW);
		x+=(int)((float)(largeur+wlargeur/65));
		if(x>3*largeur)
		{
			x=(int)((float)(wlargeur/65));
			y+=(int)((float)(hauteur+(whauteur/100)));
		}
		i++;
	}
	while(i<14);
}

void CNum::OnLButtonDown(UINT nFlags, CPoint point)
{
	CDialog::OnLButtonDown(nFlags, point);
}

HBRUSH CNum::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if(pWnd->GetDlgCtrlID()==IDC_SNUM)
	{
		pDC->SetBkColor(0);
		pDC->SetTextColor(0xFFFFFF);
		pDC->SelectObject(&mesnumfont);
		return (HBRUSH)GetStockObject(BLACK_BRUSH);
	}
	if(pWnd->GetDlgCtrlID()==IDC_SMESSAGE)
	{
		pDC->SetBkColor(0xFFFFFF);
		pDC->SetTextColor(0);
		pDC->SelectObject(&mesnumfont);
		return (HBRUSH)GetStockObject(WHITE_BRUSH);
	}
	return hbr;
}

void CNum::OnStnClickedSnum()
{
}

void CNum::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	HDC dc=lpDrawItemStruct->hDC;
	CRect rct;
	int i=lpDrawItemStruct->CtlID-IDC_0;//
	if(nIDCtl>=IDC_0&&nIDCtl<=IDC_13)
	{
		SetBkMode(dc,TRANSPARENT);//(col);
		rct=lpDrawItemStruct->rcItem;
		RectF rctf(0,0,(REAL)rct.Width(),(REAL)rct.Height());
		SetTextColor(dc,0);
		SelectObject(dc,butnumfont);
		// **********  DESSIN du bouton
		Graphics gr (dc);
		if(!(lpDrawItemStruct->itemState & ODS_SELECTED))
			gr.DrawImage(pbnartbo,rctf);
		else
			if(mode!=4)
				gr.DrawImage(pbsartbo,rctf);
		if((mode==0||mode==2||mode==4||mode==1)&&(i==9||i==11))
			DrawText(dc,"",-1,&rct,DT_CENTER|DT_SINGLELINE|DT_VCENTER );
		else
		{
			if(mode==3&&nID==IDC_VAL1&&i==9&&nombre=="")
				DrawText(dc,"2/3",-1,&rct,DT_CENTER|DT_SINGLELINE|DT_VCENTER );
			else
				if(mode==3&&nID==IDC_VAL2&&i==9&&nombre=="")
					DrawText(dc,"1/3",-1,&rct,DT_CENTER|DT_SINGLELINE|DT_VCENTER );
				else
					if(mode==3&&(nID==IDC_VAL1||nID==IDC_VAL2)&&i==9&&nombre!="")
						DrawText(dc,"",-1,&rct,DT_CENTER|DT_SINGLELINE|DT_VCENTER );
					else
						DrawText(dc,Table[i],-1,&rct,DT_CENTER|DT_SINGLELINE|DT_VCENTER );
		}
	}
}

LRESULT CNum::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{


	return CDialog::DefWindowProc(message, wParam, lParam);
}

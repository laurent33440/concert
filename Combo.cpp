// Combo.cpp : implementation file
//

#include "stdafx.h"
#include "Concerto.h"
#include "ConcertoDlg.h"
#include "Combo.h"


// CCombo dialog

IMPLEMENT_DYNAMIC(CCombo, CDialog)

CCombo::CCombo(CWnd* pParent /*=NULL*/)
	: CDialog(CCombo::IDD, pParent)
{

}

CCombo::~CCombo()
{
}

void CCombo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LCOL, lcol);
}


BEGIN_MESSAGE_MAP(CCombo, CDialog)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_WM_DRAWITEM()
	ON_LBN_SELCHANGE(IDC_LCOL, &CCombo::OnLbnSelchangeLcol)
	ON_WM_SHOWWINDOW()
	ON_WM_TIMER()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CCombo message handlers

void CCombo::OnPaint()
{
	CPaintDC dc(this); // device context for painting
}
BOOL CCombo::OnInitDialog()
{
	CString temp;
	CStringW wstr;
	CConcertoDlg* par;
	if(type==6)
		par=(CConcertoDlg*)(GetParent()->GetParent());
	else
		par=(CConcertoDlg*)GetParent();
	par->pcombo=NULL;

	CDialog::OnInitDialog();
	if( type==0)
	{
		for(int i=0;i<par->ldevise.GetCount();i++)
		{
			par->ldevise.GetText(i,temp);
			lcol.AddString(temp);
		}
	}
	else
		if( type==1)
		{
			for(int i=0;i<par->llangue.GetCount();i++)
			{
				par->llangue.GetText(i,temp);
				lcol.AddString(temp);
			}
		}
		else
			if( type==2)
			{
				if(par->lmois.GetCount()==0)
					MessageBox("Pas de mois");
				else
				{
					for(int i=0;i<par->lmois.GetCount();i++)
					{
						par->lmois.GetText(i,temp);
						lcol.AddString(temp);
					}
				}
			}
			else
				if( type==3)
				{
					for(int i=0;i<par->lpays.GetCount();i++)
					{
						par->lpays.GetText(i,temp);
						lcol.AddString(temp);
					}
				}
				else
					if( type==4)
					{
						for(int i=0;i<par->sdl.GetCount();i++)
						{
							par->sdl.GetText(i,temp);
							lcol.AddString(temp);
						}
					}
					else
						if( type==5||type==6||type==7)
						{
							for(int i=0;i<par->ltmp.GetCount();i++)
							{
								par->ltmp.GetText(i,temp);
								lcol.AddString(temp);
							}
						}
	lcol.SetItemHeight(0,winh);
	if(type<7){ //calle la liste au dessous du statique
		rctstat.bottom=rctstat.top+lcol.GetCount()*winh;
	}
	else //calle la liste au dessus du statique
	{
		rctstat.bottom=rctstat.top;
		rctstat.top= rctstat.bottom-lcol.GetCount()*winh;
	}
	lcol.SetWindowPos(&wndTop,0,0,rctstat.Width(),rctstat.Height(),SWP_SHOWWINDOW);
	
	SetWindowPos(&wndTop,rctstat.left,rctstat.top,rctstat.Width(),rctstat.Height(),SWP_HIDEWINDOW);
	sel=-1;
	ShowWindow(1);
	SetTimer(1,500,NULL);
	return TRUE;  // retourne TRUE, sauf si vous avez défini le focus sur un contrôle
}
HBRUSH CCombo::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if(nCtlColor==CTLCOLOR_DLG)
		return (HBRUSH)GetStockObject(NULL_BRUSH);
	return hbr;
}

void CCombo::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CString temp;
	CDC dc;
	CRect rct;
	COLORREF col;
	CConcertoDlg* par;
	if(type==6)
		par=(CConcertoDlg*)(GetParent()->GetParent());
	else
		par=(CConcertoDlg*)GetParent();
		
	if(nIDCtl==IDC_LCOL)//&&lpDrawItemStruct->CtlType==ODT_COMBOBOX)
	{
		CString temp;
		dc.Attach(lpDrawItemStruct->hDC);
		switch(type)
		{
			case 0:
			{
				if(lpDrawItemStruct->itemID>=0)
				{
					lcol.GetText(lpDrawItemStruct->itemID,temp);
					rct=lpDrawItemStruct->rcItem;
					col=0xffffff;
					dc.FillSolidRect(&rct,col);
					par->DrawLettre(temp,&rct,&dc,col,&par->geostat,type);
				}
				break;
			}
			case 1:
			{
				if(lpDrawItemStruct->itemID>=0)
				{
					lcol.GetText(lpDrawItemStruct->itemID,temp);
					rct=lpDrawItemStruct->rcItem;
					col=0xffffff;
					dc.FillSolidRect(&rct,col);
					par->DrawLettre(temp,&rct,&dc,col,&par->geodate,type);
				}
				break;
			}
			case 2:
			{
				if(lpDrawItemStruct->itemID>=0)
				{
					lcol.GetText(lpDrawItemStruct->itemID,temp);
					rct=lpDrawItemStruct->rcItem;
					col=0xffffff;
					dc.FillSolidRect(&rct,col);
					par->DrawLettre(temp,&rct,&dc,col,&par->geodate,type);
				}
				break;
			}
			case 3:
			{
				if(lpDrawItemStruct->itemID>=0)
				{
					lcol.GetText(lpDrawItemStruct->itemID,temp);
					rct=lpDrawItemStruct->rcItem;
					col=0xffffff;
					dc.FillSolidRect(&rct,col);
					par->DrawLettre(temp,&rct,&dc,col,&par->geodate,type);
				}
				break;
			}
			case 4:
			{
				if(lpDrawItemStruct->itemID>=0)
				{
					lcol.GetText(lpDrawItemStruct->itemID,temp);
					rct=lpDrawItemStruct->rcItem;
					col=0xffffff;
					dc.FillSolidRect(&rct,col);
					par->DrawLettre(temp,&rct,&dc,col,&par->geodate,type);
				}
				break;
			}
			case 5:
			{
				if(lpDrawItemStruct->itemID>=0)
				{
					lcol.GetText(lpDrawItemStruct->itemID,temp);
					rct=lpDrawItemStruct->rcItem;
					col=0xffffff;
					dc.FillSolidRect(&rct,col);
					par->DrawLettre(temp,&rct,&dc,col,&par->geodate,type);
				}
				break;
			}
			case 6:
			{
				if(lpDrawItemStruct->itemID>=0)
				{
					lcol.GetText(lpDrawItemStruct->itemID,temp);
					rct=lpDrawItemStruct->rcItem;
					col=0xffffff;
					dc.FillSolidRect(&rct,col);
					par->DrawLettre(temp,&rct,&dc,col,&par->geodate,type);
				}
				break;
			}
			case 7:
			{
				if(lpDrawItemStruct->itemID>=0)
				{
					lcol.GetText(lpDrawItemStruct->itemID,temp);
					rct=lpDrawItemStruct->rcItem;
					col=0xffffff;
					dc.FillSolidRect(&rct,col);
					par->DrawLettre(temp,&rct,&dc,col,&par->geodate,type);
				}
				break;
			}
			
		}
		dc.Detach();
	}
}

void CCombo::OnLbnSelchangeLcol()
{
	CString temp;
	if((sel=lcol.GetCurSel())!=-1)
	{
		OnOK();
	}
}
void CCombo::CloseCombo()
{
	CString temp;
	sel=-1;
	OnOK();
}

void CCombo::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);
	// TODO: Add your message handler code here
}

void CCombo::OnTimer(UINT_PTR nIDEvent)
{
	if(nIDEvent==1)
	{
		KillTimer(1);
		CConcertoDlg* par;
		CMessage* mar;
		if(type<6)
		{
			par=(CConcertoDlg*)GetParent();
			par->pcombo=this;
		}
		else
		{
			mar=(CMessage*)GetParent();
			mar->pcombo=this;
		}
	}
	// TODO: Add your message handler code here and/or call default

	CDialog::OnTimer(nIDEvent);
}

void CCombo::OnDestroy()
{
	CDialog::OnDestroy();

	CConcertoDlg* par;
	CMessage* mar;
	if(type=6)
	{
		mar=(CMessage*)GetParent();
		mar->pcombo=NULL;
	}
	else
	{
		par=(CConcertoDlg*)GetParent();
		par->pcombo=NULL;
	}
}

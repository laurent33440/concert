// SimPrint.cpp : implementation file
//

#include "stdafx.h"
#include "Concerto.h"
#include "ConcertoDlg.h"
#include "SimPrint.h"


// CSimPrint dialog

IMPLEMENT_DYNAMIC(CSimPrint, CDialog)

CSimPrint::CSimPrint(CWnd* pParent /*=NULL*/)
	: CDialog(CSimPrint::IDD, pParent)
{

}

CSimPrint::~CSimPrint()
{
}

void CSimPrint::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSimPrint, CDialog)
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


// CSimPrint message handlers

void CSimPrint::OnLButtonUp(UINT nHitTest, CPoint point)
{
	CDialog::OnNcLButtonUp(nHitTest, point);
	CloseDialog();
}
void CSimPrint::CloseDialog()
{
	CConcertoDlg* par=(CConcertoDlg*)GetParent();
	OnOK();

}

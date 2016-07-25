#pragma once
#include "afxwin.h"


// CNum dialog

class CNum : public CDialog
{
	DECLARE_DYNAMIC(CNum)

public:
	CNum(CWnd* pParent = NULL);   // standard constructor
	virtual ~CNum();
	void	DrawNumButton();
	void Display();
	int		wlargeur;
	int		whauteur;
	CString		nombre;
	CString txtmessage;
	COLORREF	backnumrefcolor;
	COLORREF	butnumrefcolor;
	COLORREF	snumrefcolor;
	COLORREF	txtbacknumrefcolor;
	COLORREF	txtbutnumrefcolor;
	COLORREF	txtsnumrefcolor;
	LONG numflag;
	int color;
	int coloren;
	int mode;
	int chiffre;
	int	pw;
	int nID;
	int offset;
	int idxdraw;
	CFont butnumfont;
	CFont mesnumfont;
	CString Table[14];
	CString prxtxt;
	CBitmap workbitmap[14];
	CBrush	snumbrush;
	Image* pbsartbo;
	Image* pbnartbo;

// Dialog Data
	enum { IDD = IDD_NUM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual BOOL PreTranslateMessage( MSG* pMsg );

public:
	CStatic smessage;
	CStatic wnum;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClicked0();
	afx_msg void OnBnClicked1();
	afx_msg void OnBnClicked2();
	afx_msg void OnBnClicked3();
	afx_msg void OnBnClicked4();
	afx_msg void OnBnClicked5();
	afx_msg void OnBnClicked6();
	afx_msg void OnBnClicked7();
	afx_msg void OnBnClicked8();
	afx_msg void OnBnClicked9();
	afx_msg void OnBnClickedPM();
	afx_msg void OnBnClickedPD();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnStnClickedSnum();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
};

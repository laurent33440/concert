#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CPrintMessage dialog

class CPrintMessage : public CDialog
{
	DECLARE_DYNAMIC(CPrintMessage)

public:
	CPrintMessage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPrintMessage();

// Dialog Data
	enum { IDD = IDD_PRINTMESSAGE };
	void DrawButton();
	CString titre;
	int color;
	int orgh;
	int org;
	int bl;
	int largeur;
	int hauteur;
	int coloren;
	int to;
	HANDLE hPrinter;
	DWORD nbyte;
	BYTE Printer[10000];
	DWORD cbNeeded;
	PRINTER_DEFAULTS pd;
	int oldnb;
	CString prtname;

	CBrush backrefcolorbr;

	CBitmap bmpok;
	CBitmap bmpca;
	CFont staticfont;
	CFont butdlgfont;
	COLORREF dlgrefcolor;
	COLORREF txtdlgrefcolor;
	COLORREF butdlgrefcolor;
	COLORREF txtbutdlgrefcolor;
	int wlargeur;
	int whauteur;
	int mode;
	CBrush ticketbrush;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CStatic smes1;
	CStatic smes2;
	CString mes1;
	CString mes2;
	CString mes3;
	CButton ccolor;
	CButton bok;
	CButton bca;
	CStatic smes3;
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnStnClickedSmes1();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

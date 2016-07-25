#pragma once
#include "afxwin.h"


// CMessage dialog

class CMesedit : public CDialog
{
	DECLARE_DYNAMIC(CMesedit)

public:
	CMesedit(CWnd* pParent = NULL);   // standard constructor
	virtual ~CMesedit();

// Dialog Data
	enum { IDD = IDD_MESEDIT };
	void DrawButton();
	CString titre;
	int color;
	int orgh;
	int org;
	int bl;
	int largeur;
	int hauteur;
	int coloren;
	int edtlargeur;
	CBrush backrefcolorbr;
	CString evtxt;
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
	CTime seldate;
	CBrush ticketbrush;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	CStatic smes1;
	CString mes1;
	CButton ccolor;
	CButton bok;
	CButton bca;
	CEdit emes;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnStnClickedSmes1();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnPaint();
};

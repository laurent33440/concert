#pragma once
#include "afxwin.h"


// CMessage dialog

class CIdent : public CDialog
{
	DECLARE_DYNAMIC(CIdent)

public:
	CIdent(CWnd* pParent = NULL);   // standard constructor
	virtual ~CIdent();

// Dialog Data
	enum { IDD = IDD_IDENT };
	void DrawButton();
	int color;
	int orgh;
	int orgs;
	int orgn;
	int orgt;
	int bl;
	int largeurn;
	int largeurs;
	int hauteur;
	int coloren;
	int fadmin;
	float marge;
	CBrush backrefcolorbr;
	CString serialtemp;

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
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	CEdit sserial;
	CStatic snf;
	CStatic stitre;
	CStatic snmes1;
	CStatic snmes2;
	CStatic snmes3;
	CStatic snmes4;
	CStatic smes2;
	CStatic smes3;
	CStatic smes4;
	CString titre;
	CString serialtxt;
	CString nmes1;
	CString nmes2;
	CString nmes3;
	CString nmes4;
	CString mes2;
	CString mes3;
	CString mes4;
	CButton bok;
	CButton bca;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnStnClickedSnmes1();
	afx_msg void OnBnClickedCheck1();
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnPaint();
	afx_msg void OnEnChangeSerial();
	afx_msg void OnEnSetfocusSerial();
	afx_msg void OnBnClickedPrintIdent();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnDestroy();
	afx_msg void OnEnUpdateSerial();
	afx_msg void OnBnClickedTeamviewer();
	CButton bteam;
};

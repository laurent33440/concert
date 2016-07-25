#pragma once
#include "afxwin.h"


// CMessage dialog

class CImport : public CDialog
{
	DECLARE_DYNAMIC(CImport)

public:
	CImport(CWnd* pParent = NULL);   // standard constructor
	virtual ~CImport();

// Dialog Data
	enum { IDD = IDD_IMPORT };
	void DrawButton();
	int SearchBase();
	void GetEvtName(int);
	int color;
	int orgh;
	int orgn;
	int orgm;
	int orgt;
	int bl;
	int largeurn;
	int hauteur;
	int coloren;
	int sel;
	CString titre;
	CString libel1;
	CString libel2;
	CString entete;
	CString date;
	CString poste;
	CString outpath;
	CString source[100];
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
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	CStatic stitre;
	CStatic snmes1;
	CStatic snmes2;
	CStatic snmes3;
	CString nmes1;
	CString nmes2;
	CString nmes3;
	CButton ccolor;
	CButton bok;
	CButton bca;
	CListBox lba;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg void OnStnClickedSnmes1();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnLbnSelchangeLbase();
};

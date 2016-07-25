#pragma once
#include "afxwin.h"
#include "afxdtctl.h"
#include "Combo.h"


// CMessage dialog

class CMessage : public CDialog
{
	DECLARE_DYNAMIC(CMessage)

public:
	CMessage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CMessage();

// Dialog Data
	enum { IDD = IDD_MESSAGE };
	void DrawButton();
	CString titre;
	int color;
	int orgh;
	int org;
	int bl;
	int idxstart;
	int idxstop;
	int largeur;
	int hauteur;
	int coloren;
	int plen;
	HANDLE hf;
	CBrush backrefcolorbr;
	CString date;
	CCombo* pcombo;
	CTime seldate;
	CBitmap bmpok;
	CBitmap bmpca;
	CFont staticfont;
	CFont butdlgfont;
	CFont heurefont;
	COLORREF dlgrefcolor;
	COLORREF txtdlgrefcolor;
	COLORREF butdlgrefcolor;
	COLORREF txtbutdlgrefcolor;
	int wlargeur;
	int whauteur;
	int mode;
	CString buf;
	CString reponse;
	CString auteur;
	CBrush ticketbrush;
	CTime selhor;
	CString mes1;
	CString mes2;
	CString mes3;
	PVOID psource;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
    virtual void OnSetFont(CFont* pFont);

	DECLARE_MESSAGE_MAP()
public:
	CStatic smes1;
	CStatic smes2;
	CButton bok;
	CButton bca;
	CStatic smes3;
	CProgressCtrl psend;
	CMonthCalCtrl cal;
	CDateTimeCtrl hor;
	CEdit erep;
	CEdit eaut;
	CStatic srep;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnStnClickedSmes1();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnMcnSelectMonthcalendar1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnMcnSelchangeMonthcalendar1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDtnDatetimechangeHoraire(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnDtnDatetimechangeDate(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeReponse();
	afx_msg void OnEnChangeAuteur();
	afx_msg void OnEnSetfocusAuteur();
	afx_msg void OnEnSetfocusReponse();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnStnClickedMotif();
};

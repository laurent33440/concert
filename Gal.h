#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CGal dialog

class CGal : public CDialog
{
	DECLARE_DYNAMIC(CGal)

public:
	CGal(CWnd* pParent = NULL);   // standard constructor
	virtual ~CGal();

// Dialog Data
	enum { IDD = IDD_GALERIE };
	int selfile;
	CFont butfont;
	CFont listefont;
	CBrush backrefcolorbr;
	CBrush butbrush;
	int DrawGalImage(CDC* pdc,int OLT,int al,int ah,int idx,int pos); 
	void PlayGalAvi(); 
	int orgim;
	int mode;
	HWND SCR; //Handle  fenetre MCI milieu

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnLbnSelchangeLim();
	afx_msg void OnLbnDblclkLim();
	CListBox lgal;
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	CButton bc;
	CButton bo;
	afx_msg void OnDeltaposSpin1(NMHDR *pNMHDR, LRESULT *pResult);
	CSpinButtonCtrl spc;
	CStatic vim;
	afx_msg void OnStnDblclickVim();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedValid();
	CButton bv;
	CStatic vmci;
};

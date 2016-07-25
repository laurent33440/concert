#pragma once
#include "afxwin.h"
#include "afxdtctl.h"
#include "Resource.h"
// CCombo dialog

class CCombo : public CDialog
{
	DECLARE_DYNAMIC(CCombo)

public:
	CCombo(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCombo();
// Dialog Data
	enum { IDD = IDD_COMB };
	void CloseCombo();
	CRect rctstat;
	CBrush combobrush;
	int winh;
	int sel;
	int type;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

public:
	CListBox lcol;
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnLbnSelchangeLcol();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
};

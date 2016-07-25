#pragma once


// CSimPrint dialog

class CSimPrint : public CDialog
{
	DECLARE_DYNAMIC(CSimPrint)

public:
	CSimPrint(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSimPrint();
	void CloseDialog();

// Dialog Data
	enum { IDD = IDD_SIMPRINT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonUp(UINT nHitTest, CPoint point);
};

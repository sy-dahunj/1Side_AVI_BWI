// SplashDlg.h : ��� ����
//
#pragma once

// CSplashDlg ��ȭ �����Դϴ�.

class CSplashDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSplashDlg)

public:
	CSplashDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CSplashDlg();

	// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SPLASH_DLG };
	CLabelCS	m_Label[4];
	CPictureCS	m_Image[2];

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

private:
	CBitmap	m_bmpImage[2];

private:
	void Initial_Controls();
};

///////////////////////////////////////////////////////////////////////////////

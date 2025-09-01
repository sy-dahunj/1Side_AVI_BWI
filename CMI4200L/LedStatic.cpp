// LedStatic.cpp : ���� ����
//
#include "stdafx.h"
#include "LedStatic.h"

// const COLORREF CLOUD_BLUE = RGB(128, 184, 223);
// const COLORREF WHITE = RGB(255, 255, 255);
// const COLORREF BLACK = RGB(1, 1, 1);
// const COLORREF DK_GRAY = RGB(128, 128, 128);
// const COLORREF LT_GRAY = RGB(192, 192, 192);
// const COLORREF YELLOW = RGB(255, 255, 0);
// const COLORREF DK_YELLOW = RGB(128, 128, 0);
// const COLORREF RED = RGB(255, 0, 0);
// const COLORREF DK_RED = RGB(128, 0, 0);
// const COLORREF BLUE = RGB(0, 0, 255);
// const COLORREF DK_BLUE = RGB(0, 0, 128);
// const COLORREF CYAN = RGB(0, 255, 255);
// const COLORREF DK_CYAN = RGB(0, 128, 128);
// const COLORREF GREEN = RGB(0, 255, 0);
// const COLORREF DK_GREEN = RGB(0, 128, 0);
// const COLORREF MAGENTA = RGB(255, 0, 255);
// const COLORREF DK_MAGENTA = RGB(128, 0, 128);

IMPLEMENT_DYNAMIC(CLedStatic, CStatic)

CLedStatic::CLedStatic()
{
	m_colorOn = RGB(255, 255, 255);	// White (Default On Color)
	m_colorOff = RGB(0, 0, 0);		// Black (Default Off Color)
	m_bStatus = FALSE;
}

CLedStatic::~CLedStatic()
{
}

BEGIN_MESSAGE_MAP(CLedStatic, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()

// CLedStatic �޽��� ó�����Դϴ�.

void CLedStatic::OnPaint()
{
	CPaintDC dc(this);	// �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	// �׸��� �޽����� ���ؼ��� CStatic::OnPaint()��(��) ȣ������ ���ʽÿ�.
	CRect rectctrl;
	GetClientRect(&rectctrl);

	CBitmap *pOldTempBitmap;
	CDC tempDC;
	tempDC.CreateCompatibleDC(&dc);

	CBitmap tempBitmap;
	tempBitmap.CreateCompatibleBitmap(&dc, rectctrl.Width(), rectctrl.Height());

	pOldTempBitmap = tempDC.SelectObject(&tempBitmap);

	if (m_bStatus) tempDC.FillRect(rectctrl, &CBrush(m_colorOn));
	else tempDC.FillRect(rectctrl, &CBrush(m_colorOff));

	dc.BitBlt(rectctrl.left, rectctrl.top, rectctrl.right, rectctrl.bottom,	&tempDC, 0, 0, SRCCOPY);

	tempDC.SelectObject(pOldTempBitmap);
}

void CLedStatic::SetColor(COLORREF colorOn, COLORREF colorOff)
{
	m_colorOn = colorOn;
	m_colorOff = colorOff;
	Invalidate();
}

BOOL CLedStatic::GetStatus()
{
	return m_bStatus;
}

void CLedStatic::On()
{
	m_bStatus = TRUE;
	Invalidate();
}

void CLedStatic::Off()
{
	m_bStatus = FALSE;
	Invalidate();
}

///////////////////////////////////////////////////////////////////////////////

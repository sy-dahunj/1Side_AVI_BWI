
// FileSenderClient.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CFileSenderClientApp:
// �� Ŭ������ ������ ���ؼ��� FileSenderClient.cpp�� �����Ͻʽÿ�.
//

class CFileSenderClientApp : public CWinApp
{
public:
	CFileSenderClientApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

//extern CFileSenderClientApp theApp;
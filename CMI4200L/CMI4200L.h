// CMI4200L.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.

// CCMI4200LApp:
// �� Ŭ������ ������ ���ؼ��� CMI4200L.cpp�� �����Ͻʽÿ�.
//
class CCMI4200LApp : public CWinApp
{
public:
	CCMI4200LApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CCMI4200LApp theApp;

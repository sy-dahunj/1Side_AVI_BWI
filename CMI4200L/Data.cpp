// Data.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Data.h"
//#include "MIController.h"


// CData

CData::CData()
{
}

CData::~CData()
{
}


// CData ��� �Լ�

void CData::Serialize(CArchive &ar)
{
	if(ar.IsStoring())
	{
		// ��Ʈ��ũ�� �۽�
		ar << m_strData;
	}
	else
	{
		// ��Ʈ��ũ���� ����
		ar >> m_strData;
	}
}

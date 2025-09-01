// Data.cpp : 구현 파일입니다.
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


// CData 멤버 함수

void CData::Serialize(CArchive &ar)
{
	if(ar.IsStoring())
	{
		// 네트워크로 송신
		ar << m_strData;
	}
	else
	{
		// 네트워크에서 수신
		ar >> m_strData;
	}
}

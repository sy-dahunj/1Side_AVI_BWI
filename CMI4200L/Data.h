#pragma once

// CData 명령 대상입니다.

class CData : public CObject
{
public:
	CData();
	virtual ~CData();

public:
	virtual void Serialize(CArchive &ar);

	CString m_strData;

};



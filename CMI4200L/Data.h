#pragma once

// CData ��� ����Դϴ�.

class CData : public CObject
{
public:
	CData();
	virtual ~CData();

public:
	virtual void Serialize(CArchive &ar);

	CString m_strData;

};



#pragma once
#include "mobject.h"

class StartCADObj
{
public:
	StartCADObj(void);
public:
	virtual ~StartCADObj(void);

public:
	void StartUpCAD();
	void SetTabIndex( CString tablIndex );
	CString GetTabIndex();

private:
	void GetActiveAcadDoc(BOOL bAcadR14);
	BOOL WriteFileToCAD(CMObject &refDoc, CString strDrawFileName);
	void DeleteSupportPath();
	void AddSupportPath(const CString &strInsPath);
	CString GetArxFilePath(CString strCADVersion);

	// ���ܣ�Unicode -> Ansi
	// ���룺UNICODE�ַ���
	// �������Ӧ��ANSI�ַ���
	// ��ע���������´ε����ͷ��ϴε��÷�����ڴ棬Ҫ��ȫ����ڴ���ʹ��ConvertUnicodeToAnsi(NULL);
	//		��ȷ�����ý��ʹ����Ϻ���ٴε��ñ�������
	char* ConvertUnicodeToAnsi( IN const wchar_t* pwUNICODE );

private:
	CString m_strTabIndex;
	CMObject m_ObjAcadApp;
	CMObject m_ObjAcadDoc;
	
};


// PCFDriverModel.h: interface for the PCFDriverModel class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PCFDRIVERMODEL_H__E300CAD6_E2BD_4A58_94A2_8AC1FDA85D6B__INCLUDED_)
#define AFX_PCFDRIVERMODEL_H__E300CAD6_E2BD_4A58_94A2_8AC1FDA85D6B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "UnitInfo.h"
#include "FCFComponentMgr.h"

class AFX_EXT_CLASS PCFDriverModel  
{
public:
	PCFJunsMgr& GetJunMgr();
	PCFPipesMgr& GetPipeMgr();
	BOOL Read(CStdioFile &file);
	PCFDriverModel();
	virtual ~PCFDriverModel();

private:
	void ReadFile(CStdioFile& File,char* pMemory);
	void ParseStringToWord(const char* pMemory,DWORD dwFileLength);
	BOOL Decompose(const  CString strSign,CStringArray& strSet);
	BOOL FindRange(const CString& strStart , int& nStart , int& nEnd);
	BOOL IsPCFKeyWord( const CString& strKeyWord ) ;//��������ͷ�����ϡ��ܵ�
	void GetSubStringSet(int nStart,int nEnd,CStringArray& strSet);
private:
	CStringArray m_strSetForWord ;

private:
	UnitInfo m_unitInfo;
	PCFComponentMgr m_ComponentMgr;

private:
	void InitPipeline();
	void InitModel();
	void InitUnitInfo();
	const static CString m_strHeaderSign   ;//ͷ��־
	const static CString m_strMaterialSign ;//���ϱ�־
	const static CString m_strPipelineSign ;//���߱�־
	const static CString m_strFileEndSign  ;//pcf�������
};

#endif // !defined(AFX_PCFDRIVERMODEL_H__E300CAD6_E2BD_4A58_94A2_8AC1FDA85D6B__INCLUDED_)

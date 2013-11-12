// Branch.h: interface for the Branch class.
/*
 * Copyright (C), 2006,��ɳ���������˾CAE������
 * All rights reserved.
 *
  �ļ����ƣ�Branch.h
  ժҪ��    
  author  : LSP          
*/
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BRANCH_H__9140932E_187A_453A_972F_AFC6E8AA3E72__INCLUDED_)
#define AFX_BRANCH_H__9140932E_187A_453A_972F_AFC6E8AA3E72__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Jun.h"
#include "Transient.h"

class Branch : public Jun  
{
public:
	CBitmap& GetBitMap();
	static void Instance();
	NameArray& GetArray();
	static Component* CreatBranch();
	Branch();
	virtual ~Branch();
//	Branch(const Branch &ref);
//	Branch& operator=(const Branch &ref);

private:
	ScenarioObject* DoClone();

public:
	void SaveData();
	void InitData();
	BOOL Show(UnitSubSystem &UnitSys,ComponentManager *pManager,BOOL bDlgReadOnly);
	BOOL Save(Junperisist *pPersistent);
	BOOL Read(Junperisist *pPersistent);
	CString GetTypeName();
	int GetID();
	static const int m_nTypeID;
private:
	BOOL CanLink(int nMaxLink,int nKey);
private:
	void EmptyPipeInfo();
	void DelLinkPipeInfo(UINT nKey);
	void AddLinkPipeInfo(UINT nKey);
	static NameArray s_StateName;
    static CBitmap m_bitmap;
	static CString s_typeName;
public:
	void Status(ComponentStatus &ref,BOOL bTrans=TRUE);
	virtual Transient* GetTransient();
	static TableFlyWeight<4> ms_PipeInfo;
	static ArrayFlyWeight<3> ms_ImposeFlow;				//�������ͣ�0�����������1������������\��С\��λ
	static StrFlyWeight ms_DistanceUnit;
	static Transient    ms_Transient;          //˲�乲������

private:
	int m_nTran1Num;				//˲�����ݱ�1��������
	int m_nTran2Num;				//˲�����ݱ�2��������

};

inline CBitmap& Branch::GetBitMap()
{
	return m_bitmap;
}

inline NameArray& Branch::GetArray()
{
	return s_StateName;
}
#endif // !defined(AFX_BRANCH_H__9140932E_187A_453A_972F_AFC6E8AA3E72__INCLUDED_)

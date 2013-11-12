// AssignedFlow.h: interface for the AssignedFlow class.
/*
 * Copyright (C), 2006,��ɳ���������˾CAE������
 * All rights reserved.
 *
  �ļ����ƣ�AssignedFlow.h
  ժҪ��    
  author  : LSP          
*/
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ASSIGNEDFLOW_H__D408514A_CB54_4131_9314_884CED99275A__INCLUDED_)
#define AFX_ASSIGNEDFLOW_H__D408514A_CB54_4131_9314_884CED99275A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Jun.h"
#include "Transient.h"

class AssignedFlow : public Jun  
{
public:
	CBitmap& GetBitMap();
	static void Instance();
	NameArray& GetArray();
	static Component* CreatAssignedFlow();
	AssignedFlow();
	virtual ~AssignedFlow();

private:
	ScenarioObject* DoClone();

public:
	void SaveData();
	void InitData();
	BOOL Show(UnitSubSystem &UnitSys,ComponentManager *pManager,BOOL bDlgReadOnly = FALSE);
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
    static ArrayFlyWeight<3> ms_Flow;				//��������\��С\��λ
	static StrFlyWeight      ms_FlowDir;			//0���������룬1����������
	static StrFlyWeight      ms_K;					//��ʧϵ��Kֵ
	static ArrayFlyWeight<4> ms_InitPress;			//�㶨����Ϊ0�ĳ�ʼ��ѹ����0��û��ѡ��-1ѡ�У�\ѹ�����ͣ�0ˮͷ��1��ѹ����\ѹ��ֵ\��λ
	static Transient         ms_Transient;          //˲�乲������

private:
	int m_nTran1Num;				//˲�����ݱ�1��������
	int m_nTran2Num;				//˲�����ݱ�2��������
};

inline CBitmap& AssignedFlow::GetBitMap()
{
	return m_bitmap;
}

inline NameArray& AssignedFlow::GetArray()
{
	return s_StateName;
}
#endif // !defined(AFX_ASSIGNEDFLOW_H__D408514A_CB54_4131_9314_884CED99275A__INCLUDED_)

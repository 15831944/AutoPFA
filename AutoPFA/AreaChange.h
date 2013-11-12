// AreaChange.h: interface for the AreaChange class.
/*
 * Copyright (C), 2006,��ɳ���������˾CAE������
 * All rights reserved.
 *
  �ļ����ƣ�AreaChange.h
  ժҪ��    �쾶���Ǿֲ�����Ԫ���������쾶�����ӹܵ������ͬ���Ծ����쾶�������仯��
            ������Ҫ��ϸ��ģ�쾶�ܣ���ģ�쾶�������Ҫ��ʱ�õ�kϵ������������ӹܵ��������
			ͬʱ������Ӧ���ӹܵ�����ı��Զ�����Kϵ����
            
  author  : LSP          
*/
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AREACHANGE_H__85DE6716_4E8C_4283_AC07_1FEDF638BCBF__INCLUDED_)
#define AFX_AREACHANGE_H__85DE6716_4E8C_4283_AC07_1FEDF638BCBF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Jun.h"

class AreaChange : public Jun  
{
public:
	CBitmap& GetBitMap();
	static void Instance();
	NameArray& GetArray();
	static Component* CreatAreaChange();
	AreaChange();
	virtual ~AreaChange();

public:
	void SaveData();
	void InitData();
	BOOL Show(UnitSubSystem &UnitSys,ComponentManager *pManager, BOOL bDlgReadOnly = FALSE);
	BOOL Save(Junperisist *pPersistent);
	BOOL Read(Junperisist *pPersistent);
	CString GetTypeName();
	int GetID();
	static const int m_nTypeID;
	
private:
	ScenarioObject* DoClone();
	BOOL CanLink(int nMaxLink,int nKey);
private:
	void EmptyPipeInfo();
	void DelLinkPipeInfo(UINT nKey);
	void AddLinkPipeInfo(UINT nKey);
	static NameArray s_StateName;
    static CBitmap m_bitmap;
	static CString s_typeName;

public:
	static int AreaType(double dAreaUp,double dAreaDown);
	static void CalcK(double dAreaUp,double dAreaDown,int nRetype,double BaseArea);
	void Status(ComponentStatus &ref,BOOL bTrans=TRUE);
	static StrFlyWeight ms_Type;			//�쾶�����ͣ�0��Բ׶��1��Բ����2���û����壩
	static StrFlyWeight ms_Dir;				//��1��������2�����ţ�
	static StrFlyWeight ms_Angle;			//�Ƕ�
	static StrFlyWeight ms_K;				//Kϵ��ֵ
	static ArrayFlyWeight<3> ms_BasisArea;	//��ʧģ�͵��������
};

inline CBitmap& AreaChange::GetBitMap()
{
	return m_bitmap;
}

inline NameArray& AreaChange::GetArray()
{
	return s_StateName;
}
#endif // !defined(AFX_AREACHANGE_H__85DE6716_4E8C_4283_AC07_1FEDF638BCBF__INCLUDED_)

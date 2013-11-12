// VacuumBreaker.h: interface for the VacuumBreaker class.
/*
 * Copyright (C), 2006,��ɳ���������˾CAE������
 * All rights reserved.
 *
  �ļ����ƣ�VacuumBreaker.h
  ժҪ��    
  author  : LSP          
*/
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VACUUMBREAKER_H__9D914E85_2295_4910_A6B7_930E79D045C1__INCLUDED_)
#define AFX_VACUUMBREAKER_H__9D914E85_2295_4910_A6B7_930E79D045C1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Jun.h"

class VacuumBreaker : public Jun  
{
public:
	CBitmap& GetBitMap();
	static void Instance();
	NameArray& GetArray();
	static Component* CreatVacuumBreaker();
    VacuumBreaker();
	virtual ~VacuumBreaker();

private:
	ScenarioObject* DoClone();

public:
	void DelLinkPipeInfo(UINT nKey);
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
	void AddLinkPipeInfo(UINT nKey);
	static NameArray s_StateName;
    static CBitmap m_bitmap;
	static CString s_typeName;

public:
	void Status(ComponentStatus &ref, BOOL bTrans=TRUE);
	static ArrayFlyWeight<3> ms_CrackPress;				 //���ѵ�ѹ������0��ˮͷ��1��ѹ��/ѹ��ֵ/ѹ����λ
	static NumFlyWeight      ms_OrificeInCdA;			 //�׿�ȫ�����������ֵ/��λ
	static NumFlyWeight      ms_OrificeOutCdA;			 //�������ֵ/��λ
	static ArrayFlyWeight<3> ms_LiquidTemp;				 //�����¶�ѡ��0��ϵͳ����1���û�ָ���¶�/�¶�ֵ/��λ
	static ArrayFlyWeight<9> ms_GasProperty;			 //��������0������1����������/������/Cp/Cv/�����¶�/����ѹ��/�ڲ���ʼ��������������/��λ
	static StrFlyWeight      ms_ConnectPipe;			 //���ӹܵ���0�������ܵ�1��һ���ܵ�
	static StrFlyWeight      ms_ValveType;			     //��������
	static NumFlyWeight      ms_InterMediateCdA;		 //�׿�ȫ����ý���������ֵ/��λ
	static ArrayFlyWeight<3> ms_MediateActivation;		 //ý��׿ڼ����׼0��ѹ����ͬ1�����ٲ�ͬ/��׼ֵ/׼ֵ�ĵ�λ
	

};

inline CBitmap& VacuumBreaker::GetBitMap()
{
	return m_bitmap;
}

inline NameArray& VacuumBreaker::GetArray()
{
	return s_StateName;
}

#endif // !defined(AFX_VACUUMBREAKER_H__9D914E85_2295_4910_A6B7_930E79D045C1__INCLUDED_)

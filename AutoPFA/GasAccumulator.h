// GasAccumulator.h: interface for the GasAccumulator class.
/*
 * Copyright (C), 2006,��ɳ���������˾CAE������
 * All rights reserved.
 *
  �ļ����ƣ�GasAccumulator.h
  ժҪ��    
  author  : LSP          
*/
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GASACCUMULATOR_H__AD458CF6_07DC_4FDD_845B_F4297072550A__INCLUDED_)
#define AFX_GASACCUMULATOR_H__AD458CF6_07DC_4FDD_845B_F4297072550A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Jun.h"

class GasAccumulator : public Jun  
{
public:
	CBitmap& GetBitMap();
	static void Instance();
	NameArray& GetArray();
	static Component* CreatGasAccumulator();
	GasAccumulator();
	virtual ~GasAccumulator();

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
	void AddLinkPipeInfo(UINT nKey);
private:
	void EmptyPipeInfo();
	static NameArray s_StateName;
    static CBitmap m_bitmap;
	static CString s_typeName;

public:
	void Status(ComponentStatus &ref,BOOL bTrans=TRUE);
	static StrFlyWeight ms_Polytropic;					//�仯�ĳ���
	static NumFlyWeight ms_InitVolume;					//��ʼ���������\��λ
	static ArrayFlyWeight<5> ms_Orifice;				//ѡ�н����װ�ģ�ͱ��\������ϵ��\������ϵ��\���ֵ\��λ
	static ArrayFlyWeight<10> ms_ShortPipe;				//0��û��ѡ��̹ܵ�ģ�ͣ�-1��ѡ��̹ܵ�ģ��
														//�̹ܵ�Ħ��ϵ��
														//�̹ܵ���ֱ��\��λ
														//�̹ܵ����\��λ
														//�̹ܵ�����\��λ
														//�̹ܵ���߱仯\��λ
	static ArrayFlyWeight<4> ms_InitPress;				//0:û��ѡ�����þ�̬������ѹ����-1:û��ѡ�����þ�̬������ѹ��
														//0��ѹ������Ϊˮͷ��1��ѹ������Ϊѹ��
														//ѹ����С\��λ
	static StrFlyWeight ms_MaxVolume;					//������
	static StrFlyWeight ms_MinVolume;					//��С���
	static ArrayFlyWeight<3> ms_GasVolume;				//���ͣ�0����ʼ��ָ�������1����ʼ��ָ��ѹ����
														//�ο�����ѹ��\��λ
									

};

inline CBitmap& GasAccumulator::GetBitMap()
{
	return m_bitmap;
}

inline NameArray& GasAccumulator::GetArray()
{
	return s_StateName;
}

#endif // !defined(AFX_GASACCUMULATOR_H__AD458CF6_07DC_4FDD_845B_F4297072550A__INCLUDED_)

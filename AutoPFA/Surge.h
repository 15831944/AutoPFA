// Surge.h: interface for the Surge class.
/*
 * Copyright (C), 2006,��ɳ���������˾CAE������
 * All rights reserved.
 *
  �ļ����ƣ�Surge.h
  ժҪ��    
  author  : LSP          
*/
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SURGE_H__9E3C7D91_E02B_4DA8_9DF7_147E3B639767__INCLUDED_)
#define AFX_SURGE_H__9E3C7D91_E02B_4DA8_9DF7_147E3B639767__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Jun.h"
#include "Transient.h"

class Surge : public Jun  
{
public:
	CBitmap& GetBitMap();
	static void Instance();
	NameArray& GetArray();
	static Component* CreatSurge();
	Surge();
	virtual ~Surge();

private:
	ScenarioObject* DoClone();

public:
	void AddLinkPipeInfo(UINT nKey);
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
	static NameArray s_StateName;
    static CBitmap m_bitmap;
	static CString s_typeName;

public:
	void Status(ComponentStatus &ref,BOOL bTrans=TRUE);
	virtual Transient* GetTransient();
	static TableFlyWeight<4> ms_PipeInfo;
	static StrFlyWeight ms_DistanceUnit;
	static NumFlyWeight ms_SurgeHeight;					//��ѹ���ĸ߶�\��λ
	static NumFlyWeight ms_ConstArea;					//�����ֵ\��λ
	static NumFlyWeight ms_SurfacePress;				//����ѹ��\��λ
	static ArrayFlyWeight<5> ms_Orifice;				//ѡ�н����װ�ģ�ͱ��\������ϵ��\������ϵ��\���ֵ\��λ
	static ArrayFlyWeight<10> ms_ShortPipe;				//0��û��ѡ��̹ܵ�ģ�ͣ�-1��ѡ��̹ܵ�ģ��
														//�̹ܵ�Ħ��ϵ��
														//�̹ܵ���ֱ��\��λ
														//�̹ܵ����\��λ
														//�̹ܵ�����\��λ
														//�̹ܵ���߱仯\��λ
	static StrFlyWeight ms_OneWay;						//��One-Way Surge Tank��0��û��ѡ��-1ѡ������ģ��ֹ�ط������Ļ���ޡ�
	static ArrayFlyWeight<4> ms_Vessel;					//ģ���������0��û��ѡ��-1��ѡ��
														//������ܵ��ܵ��ĸ߶�\��λ
														//���ĳ���
	static StrFlyWeight ms_Variable;					//��ǣ�ѡ������㶨0������仯1
	static ArrayFlyWeight<3> ms_InitSurfaceH;			//�ȶ�״̬��ʼ������߶�0��û��ѡ��-1��ѡ��
														//�߶�ֵ\��λ
	static ArrayFlyWeight<5> ms_CheckValve;				//ֹ�ط�����ϵ��
														//ֹ�ط���ʼλ��0����1���ر�
														//�򿪷���Deltaѹ����ˮͷ��ѹ������0��ˮͷ1��ѹ��
														//ѹ��ֵ\��λ
	static Transient         ms_Transient;          //˲�乲������
	static TransDataTable<2>    ms_AreaTable;

private:
	int m_nTran1Num;				//˲�����ݱ�1��������
	int m_nTran2Num;				//˲�����ݱ�2��������
private:
	int m_VariableAreaNum;								//�仯���������
									

};

inline CBitmap& Surge::GetBitMap()
{
	return m_bitmap;
}

inline NameArray& Surge::GetArray()
{
	return s_StateName;
}

#endif // !defined(AFX_SURGE_H__9E3C7D91_E02B_4DA8_9DF7_147E3B639767__INCLUDED_)

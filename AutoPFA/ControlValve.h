// ControlValve.h: interface for the ControlValve class.
/*
 * Copyright (C), 2006,��ɳ���������˾CAE������
 * All rights reserved.
 *
  �ļ����ƣ�ControlValve.h
  ժҪ��    
  author  : LSP          
*/
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONTROLVALVE_H__9081409C_5E0F_4F54_B57C_71DD6E78C1E8__INCLUDED_)
#define AFX_CONTROLVALVE_H__9081409C_5E0F_4F54_B57C_71DD6E78C1E8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Jun.h"
#include "Transient.h"

class ControlValve : public Jun  
{
public:
	CBitmap& GetBitMap();
	static void Instance();
	NameArray& GetArray();
	static Component* CreatControlValve();
	ControlValve();
	virtual ~ControlValve();

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
	void Status(ComponentStatus &ref,BOOL bTrans=TRUE);
	virtual Transient* GetTransient();
	static ArrayFlyWeight<5> ms_ControlSet;		//��������0��PRF 1��PSV 2��FCV 3��PDCV
												//���Ƶ��������0��ˮͷ/ˮͷ��ʧ/�������1��ѹ��/ѹ����ʧ/��������
												//0��ͣ��ѹ��1����̬ѹ��
												//���Ƶ����ֵ
												//���Ƶ������λ
	static StrFlyWeight ms_ModelType;			//��ʧģ��(0������ϵ��ģ�ͣ�1��Kϵ��ģ�� -2��ʹ��ϵ�����ֵ)
	static StrFlyWeight ms_KOrCv;				//K��Cvϵ��ֵ
	static ArrayFlyWeight<4> ms_failAction;		//�ȶ�״̬���ǿ���0��û��ѡ�� 1��ѡ��
												//ʹ��Ĭ�ϵ���Ϊ  0��û��ѡ�� 1��ѡ��
												//����ѹ���������0��ȫ���� 1���ر�
												//����ѹ����������0��ȫ���� 1���ر�
	static Transient    ms_Transient;          //����˲�乲������
	static Transient    ms_FailTransient;      //��/�ر�˲�乲������
	static TransDataTable<3> ms_KorCvData;
private:
	int m_nTran1Num;				//˲�����ݱ�1��������
	int m_nTran2Num;				//˲�����ݱ�2��������
	int m_nFailTran1Num;			//˲�����ݱ�1��������
	int m_nFailTran2Num;			//˲�����ݱ�2��������
	int m_nKorCvData;               //���ſ���vs����ϵ����

	

};

inline CBitmap& ControlValve::GetBitMap()
{
	return m_bitmap;
}

inline NameArray& ControlValve::GetArray()
{
	return s_StateName;
}

#endif // !defined(AFX_CONTROLVALVE_H__9081409C_5E0F_4F54_B57C_71DD6E78C1E8__INCLUDED_)

// Valve.h: interface for the Valve class.
/*
 * Copyright (C), 2006,��ɳ���������˾CAE������
 * All rights reserved.
 *
  �ļ����ƣ�Valve.h
  ժҪ��    
  author  : LSP          
*/
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VALVE_H__8E7ABB22_6A07_4D35_89B7_7030BE975511__INCLUDED_)
#define AFX_VALVE_H__8E7ABB22_6A07_4D35_89B7_7030BE975511__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Jun.h"
#include "Transient.h"

class Valve : public Jun  
{
public:
	CBitmap& GetBitMap();
	static void Instance();
	NameArray& GetArray();
	static Component* CreatValve();
	Valve();
	virtual ~Valve();

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
	static StrFlyWeight ms_Type;							//����(0����ͨ���ţ�-1��ѡ�з���Ϊ���ڷ���)
    static ArrayFlyWeight<13> ms_Curve;						//��ʧģ�����ߡ�
	static ArrayFlyWeight<3>  ms_ExitPress;					//����ѹ������0��ˮͷ1��ѹ��
															//����ѹ��\��λ
	static StrFlyWeight ms_KOrCv;							//K��Cvϵ��ֵ
	static ArrayFlyWeight<3> ms_BasisArea;					//��ʧģ�͵��������0��Ĭ�����ιܵ������1�����ιܵ����2���û�ָ�����3���û�ָ��ֱ��
															//ֵ/��λ
	static Transient         ms_Transient;					//˲�乲������

private:
	int m_nTran1Num;				//˲�����ݱ�1��������
	int m_nTran2Num;				//˲�����ݱ�2��������
private:
	int m_nCurve;
};

inline CBitmap& Valve::GetBitMap()
{
	return m_bitmap;
}

inline NameArray& Valve::GetArray()
{
	return s_StateName;
}

#endif // !defined(AFX_VALVE_H__8E7ABB22_6A07_4D35_89B7_7030BE975511__INCLUDED_)

// Reservoir.h: interface for the Reservoir class.
/*
 * Copyright (C), 2006,��ɳ���������˾CAE������
 * All rights reserved.
 *
  �ļ����ƣ�Reservoir.h
  ժҪ��    
  author  : LSP          
*/
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RESERVOIR_H__C35D23BE_1ED7_4C79_960D_57ECAD4D66E6__INCLUDED_)
#define AFX_RESERVOIR_H__C35D23BE_1ED7_4C79_960D_57ECAD4D66E6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Jun.h"
#include "Transient.h"

class Reservoir : public Jun  
{
public:
	CBitmap& GetBitMap();
	static void Instance();
	NameArray& GetArray();
	static Component* CreatReservoir();
	Reservoir();
	virtual ~Reservoir();

private:
	ScenarioObject* DoClone();

public:
	void DelLinkPipeInfo(UINT nKey);
	void SaveData();
	void InitData();
	BOOL Show(UnitSubSystem &UnitSys,ComponentManager *pManager, BOOL bReadOnly = FALSE);
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
	static TableFlyWeight<6> ms_PipeInfo;
	static NumFlyWeight ms_EleOrDepthUnit;                //0δ֪\�ܵ���߻���ȵ�λ
	static NumFlyWeight ms_SurfacePress;				 //����ѹ��ֵ\��λ
	static NumFlyWeight ms_Teamperature;			     //�����¶�\��λ
	static NumFlyWeight ms_Density;						 //�����ܶ�\��λ
	static StrFlyWeight ms_EleOrDepthType;				 //�ܵ���ˮ�����ӵ��߻����
	static Transient         ms_Transient;          //˲�乲������

private:
	int m_nTran1Num;				//˲�����ݱ�1��������
	int m_nTran2Num;				//˲�����ݱ�2��������

};

inline CBitmap& Reservoir::GetBitMap()
{
	return m_bitmap;
}

inline NameArray& Reservoir::GetArray()
{
	return s_StateName;
}


#endif // !defined(AFX_RESERVOIR_H__C35D23BE_1ED7_4C79_960D_57ECAD4D66E6__INCLUDED_)

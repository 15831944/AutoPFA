// SprayDischarge.h: interface for the SprayDischarge class.
/*
 * Copyright (C), 2006,��ɳ���������˾CAE������
 * All rights reserved.
 *
  �ļ����ƣ�SprayDischarge.h
  ժҪ��    
  author  : LSP          
*/
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPRAYDISCHARGE_H__AA330A64_BE04_4BEF_A445_AD53300E5523__INCLUDED_)
#define AFX_SPRAYDISCHARGE_H__AA330A64_BE04_4BEF_A445_AD53300E5523__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Jun.h"
#include "Transient.h"

class SprayDischarge : public Jun  
{
public:
	CBitmap& GetBitMap();
	static void Instance();
	NameArray& GetArray();
	static Component* CreatSprayDischarge();
	SprayDischarge();
	virtual ~SprayDischarge();

private:
	ScenarioObject* DoClone();

public:
	void AddLinkPipeInfo(UINT nKey);
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
	static NameArray s_StateName;
    static CBitmap m_bitmap;
	static CString s_typeName;
	
public:
	void Status(ComponentStatus &ref,BOOL bTrans=TRUE);
	virtual Transient* GetTransient();
	static StrFlyWeight ms_Type;							//Spray����0������ܿ�1������
    static ArrayFlyWeight<13> ms_Curve;						//��ʧģ�����ߡ�
	static ArrayFlyWeight<3> ms_ExitArea;					//�����ڵ����\�����λ\����
	static StrFlyWeight ms_KOrCv;							//K��Cvϵ��ֵ
	static ArrayFlyWeight<3>  ms_ExitPress;					//����ѹ������0��ˮͷ1��ѹ��
															//����ѹ��\��λ
	static Transient         ms_Transient;          //˲�乲������
	//6.0�¹ܵ�����������Kϵ���͹ܵ��˿���ڵ���
	static TableFlyWeight<4> ms_PipeInfo;
	static StrFlyWeight ms_DistanceUnit;			//�ܵ��˿���ڵ��߾��뵥λ
private:
	int m_nTran1Num;				//˲�����ݱ�1��������
	int m_nTran2Num;				//˲�����ݱ�2��������
private:
	int m_nCurve;	
	

};

inline CBitmap& SprayDischarge::GetBitMap()
{
	return m_bitmap;
}

inline NameArray& SprayDischarge::GetArray()
{
	return s_StateName;
}

#endif // !defined(AFX_SPRAYDISCHARGE_H__AA330A64_BE04_4BEF_A445_AD53300E5523__INCLUDED_)

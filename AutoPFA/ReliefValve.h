// ReliefValve.h: interface for the ReliefValve class.
/*
 * Copyright (C), 2006,��ɳ���������˾CAE������
 * All rights reserved.
 *
  �ļ����ƣ� ReliefValve.h
  ժҪ��    
  author  : LSP          
*/
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RELIEFVALVE_H__EA245972_1BBC_4AB9_A7B4_0BCCAAD971FB__INCLUDED_)
#define AFX_RELIEFVALVE_H__EA245972_1BBC_4AB9_A7B4_0BCCAAD971FB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Jun.h"
#include "Transient.h"

class ReliefValve : public Jun  
{
public:
	CBitmap& GetBitMap();
	static void Instance();
	NameArray& GetArray();
	static Component* CreatReliefValve();
	ReliefValve();
	virtual ~ReliefValve();

private:
	ScenarioObject* DoClone();

public:
	void DelLinkPipeInfo(UINT nKey);
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
	static NameArray s_StateName;
    static CBitmap m_bitmap;
	static CString s_typeName;

public:
	void Status(ComponentStatus &ref,BOOL bTrans=TRUE);
	virtual Transient* GetTransient();
	static StrFlyWeight ms_Type;							//����(1:�ڲ���ȫ����internal relief��2:���ڰ�ȫ����exit relief��3:��Ƕ��ȫ����inline relief��)
    static ArrayFlyWeight<13> ms_Curve;						//��ʧģ�����ߡ�
	static ArrayFlyWeight<5>  ms_CrackExitPress;			//ѹ��/ˮͷ����0������ˮͷ1������ѹ��2��ˮͷ��3��ѹ����
															//����ѹ��\��λ
															//����ѹ��\��λ
	static StrFlyWeight ms_KOrCv;							//K��Cvϵ��ֵ
	static ArrayFlyWeight<3> ms_BasisArea;					//��ʧģ�͵��������0��Ĭ�����ιܵ������1�����ιܵ����2���û�ָ�����3���û�ָ��ֱ��
													    	//ֵ/��λ
	static Transient         ms_Transient;                  //˲�乲������

private:
	int m_nTran1Num;				//˲�����ݱ�1��������
	int m_nTran2Num;				//˲�����ݱ�2�������� 
private:
	int m_nCurve;
};

inline CBitmap& ReliefValve::GetBitMap()
{
	return m_bitmap;
}

inline NameArray& ReliefValve::GetArray()
{
	return s_StateName;
}

#endif // !defined(AFX_RELIEFVALVE_H__EA245972_1BBC_4AB9_A7B4_0BCCAAD971FB__INCLUDED_)

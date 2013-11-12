// CheckValve.h: interface for the CheckValve class.
/*
 * Copyright (C), 2006,��ɳ���������˾CAE������
 * All rights reserved.
 *
  �ļ����ƣ�CheckValve.h
  ժҪ��    
  author  : LSP          
*/
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HECKVALVE_H__A4DEF5D9_9D96_420C_AB57_11B4D6D60E64__INCLUDED_)
#define AFX_HECKVALVE_H__A4DEF5D9_9D96_420C_AB57_11B4D6D60E64__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Jun.h"
#include "Transient.h"

class CheckValve : public Jun  
{
public:
	CBitmap& GetBitMap();
	static void Instance();
	NameArray& GetArray();
	static Component* CreatCheckValve();
	CheckValve();
	virtual ~CheckValve();

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
	void EmptyPipeInfo();
	void AddLinkPipeInfo(UINT nKey);
	BOOL CanLink(int nMaxLink,int nKey);
	static NameArray s_StateName;
    static CBitmap m_bitmap;
	static CString s_typeName;

public:
	void Status(ComponentStatus &ref,BOOL bTrans=TRUE);
	virtual Transient* GetTransient();
    static ArrayFlyWeight<13> ms_Curve;						//��ʧģ�����ߡ�
	static ArrayFlyWeight<3>  ms_ReOpenPress;		        //���´򿪷���Delta(ѹ����ˮͷ)0��ˮͷ1��ѹ��\ѹ��ֵ\
															//ѹ��\��λ
	static StrFlyWeight ms_KOrCv;							//K��Cvϵ��ֵ
	static ArrayFlyWeight<3> ms_BasisArea;					//��ʧģ�͵��������0��Ĭ�����ιܵ������1�����ιܵ����2���û�ָ�����3���û�ָ��ֱ��
															//ֵ/��λ
	static NumFlyWeight ms_CloseVel;						//�رշ��ŵ���С�����ٶ�\�ٶȵ�λ
	static Transient         ms_Transient;          //˲�乲������

private:
	int m_nTran1Num;				//˲�����ݱ�1��������
	int m_nTran2Num;				//˲�����ݱ�2��������

private:
	int m_nCurve;

};

inline CBitmap& CheckValve::GetBitMap()
{
	return m_bitmap;
}

inline NameArray& CheckValve::GetArray()
{
	return s_StateName;
}

#endif // !defined(AFX_HECKVALVE_H__A4DEF5D9_9D96_420C_AB57_11B4D6D60E64__INCLUDED_)

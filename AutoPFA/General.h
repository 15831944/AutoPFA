// General.h: interface for the General class.
/*
 * Copyright (C), 2006,��ɳ���������˾CAE������
 * All rights reserved.
 *
  �ļ����ƣ�General.h
  ժҪ��    
  author  : LSP          
*/
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GENERAL_H__F8221EB2_68CA_499B_AADD_CECECBDC9129__INCLUDED_)
#define AFX_GENERAL_H__F8221EB2_68CA_499B_AADD_CECECBDC9129__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Jun.h"

class General : public Jun  
{
public:
	CBitmap& GetBitMap();
	static void Instance();
	NameArray& GetArray();
	static Component* CreatGeneral();
	General();
	virtual ~General();

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
	static StrFlyWeight ms_Type;							//����(0)
	static ArrayFlyWeight<13> ms_Curve;						//��ʧģ�����ߡ�
	static StrFlyWeight ms_KOrCv;							//K��Cvϵ��ֵ
	static ArrayFlyWeight<3> ms_BasisArea;					//��ʧģ�͵��������0��Ĭ�����ιܵ������1�����ιܵ����2���û�ָ�����3���û�ָ��ֱ��
											        	//ֵ/��λ
private:
	int m_nCurve;

};

inline CBitmap& General::GetBitMap()
{
	return m_bitmap;
}

inline NameArray& General::GetArray()
{
	return s_StateName;
}

#endif // !defined(AFX_GENERAL_H__F8221EB2_68CA_499B_AADD_CECECBDC9129__INCLUDED_)

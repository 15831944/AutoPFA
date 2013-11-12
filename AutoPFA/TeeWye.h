// TeeWye.h: interface for the TeeWye class.
/*
 * Copyright (C), 2006,��ɳ���������˾CAE������
 * All rights reserved.
 *
  �ļ����ƣ�TeeWye.h
  ժҪ��    
  author  : LSP          
*/
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEEWYE_H__822B8F4F_A77C_4F5D_B4C9_CC5FA0AD57EC__INCLUDED_)
#define AFX_TEEWYE_H__822B8F4F_A77C_4F5D_B4C9_CC5FA0AD57EC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Jun.h"

class TeeWye : public Jun  
{
public:
	CBitmap& GetBitMap();
	static void Instance();
	NameArray& GetArray();
	static Component* CreatTeeWye();
    TeeWye();
	virtual ~TeeWye();

private:
	ScenarioObject* DoClone();

public:
	void SaveData();
	void InitData();
	BOOL Show(UnitSubSystem &UnitSys,ComponentManager *pManager, BOOL bDlgReadOnly = FALSE);
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
	void AddLinkPipeInfo(UINT nKey);
	static NameArray s_StateName;
    static CBitmap m_bitmap;
	static CString s_typeName;

public:
	void SetPipeID(int ID[],int ndat = 3);
	void GetPipeID(int ID[]);
	void Status(ComponentStatus &ref,BOOL bTrans=TRUE);
	static StrFlyWeight ms_Type;			    //���ͣ�0�����ֱ��ͨ1��Բ��ֱ��ͨ2������ı�3���Գƣ�
	static StrFlyWeight ms_Angle;			    //�Ƕ�
	static StrFlyWeight ms_Model;				//��ʧģ�����ͣ�1����ģ��2����ϸģ�ͣ�
};

inline CBitmap& TeeWye::GetBitMap()
{
	return m_bitmap;
}

inline NameArray& TeeWye::GetArray()
{
	return s_StateName;
}

#endif // !defined(AFX_TEEWYE_H__822B8F4F_A77C_4F5D_B4C9_CC5FA0AD57EC__INCLUDED_)

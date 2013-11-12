// LiquidAccumulator.h: interface for the LiquidAccumulator class.
/*
 * Copyright (C), 2006,��ɳ���������˾CAE������
 * All rights reserved.
 *
  �ļ����ƣ�LiquidAccumulator.h
  ժҪ��    
  author  : LSP          
*/
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LIQUIDACCUMULATOR_H__9295DC76_56CE_4308_9838_4E63E02BFDAF__INCLUDED_)
#define AFX_LIQUIDACCUMULATOR_H__9295DC76_56CE_4308_9838_4E63E02BFDAF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Jun.h"

class LiquidAccumulator : public Jun  
{
public:
	CBitmap& GetBitMap();
	static void Instance();
	NameArray& GetArray();
	static Component* CreatLiquidAccumulator();
	LiquidAccumulator();
	virtual ~LiquidAccumulator();

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
	static NumFlyWeight ms_Elastic;				//����ֵ\���Ե�λ
	static NumFlyWeight ms_InitVolume;				//��ʼ���ֵ\��ʼ���ֵ��λ

};

inline CBitmap& LiquidAccumulator::GetBitMap()
{
	return m_bitmap;
}

inline NameArray& LiquidAccumulator::GetArray()
{
	return s_StateName;
}

#endif // !defined(AFX_LIQUIDACCUMULATOR_H__9295DC76_56CE_4308_9838_4E63E02BFDAF__INCLUDED_)

// Bend.h: interface for the Bend class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BEND_H__27584C15_B212_4B0C_9AA9_43987634D5AC__INCLUDED_)
#define AFX_BEND_H__27584C15_B212_4B0C_9AA9_43987634D5AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Jun.h"

class Bend : public Jun  
{
public:
	CBitmap& GetBitMap();
	static void Instance();
	NameArray& GetArray();
	static Component* CreatBend();
	Bend();
	virtual ~Bend();
	
private:
	ScenarioObject* DoClone();

public:
	void Status(ComponentStatus &ref,BOOL bTrans=TRUE);
	void DelLinkPipeInfo(UINT nKey);
	void AddLinkPipeInfo(UINT nKey);
	void SaveData();
	void InitData();
	BOOL Save(Junperisist *pPersistent);
	BOOL Read(Junperisist *pPersistent);
	BOOL Show(UnitSubSystem &UnitSys,ComponentManager *pManager,BOOL bDlgReadOnly = FALSE);
	CString GetTypeName();
	int GetID();
	static const int m_nTypeID;
public:
	static StrFlyWeight ms_Type;					 //��ͷ���ͣ�0��Ϊ�⻬��ͷ��1Ϊ��׼��ͷ��2ΪMitre Bend,3,Ϊ�û�ָ����
	static StrFlyWeight ms_AngleType;
	static StrFlyWeight ms_Angle;					//�Ƕ�
	static StrFlyWeight ms_RD;
	static StrFlyWeight ms_K;						//Kϵ��ֵ
	static NumFlyWeight ms_RestriFlowArea;			//��ȷ���������Restricted Flow Area)�����ֺ͵�λ
	static ArrayFlyWeight<3> ms_BasisArea;			//��ʧģ�͵��������
private:
	BOOL CanLink(int nMaxLink,int nKey);
	void EmptyPipeInfo();
private:
	static NameArray s_StateName;
    static CBitmap m_bitmap;
	static CString s_typeName;

};
inline CBitmap& Bend::GetBitMap()
{
	return m_bitmap;
}

inline NameArray& Bend::GetArray()
{
	return s_StateName;
}
#endif // !defined(AFX_BEND_H__27584C15_B212_4B0C_9AA9_43987634D5AC__INCLUDED_)

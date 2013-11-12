// Jun.h: interface for the Jun class.
/*
 * Copyright (C), 2006,��ɳ���������˾CAE������
 * All rights reserved.
 *
  �ļ����ƣ�Jun.h
  ժҪ��    
  author  : LSP          
*/
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_JUN_H__A42D91AC_827B_4313_8723_18CBD215DF19__INCLUDED_)
#define AFX_JUN_H__A42D91AC_827B_4313_8723_18CBD215DF19__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Component.h"
class Transient;
class Junperisist;
typedef CMap<int,int,CString,CString> KeyMap;
class Jun : public Component  
{
public:
	virtual void SaveData();
	virtual void InitData();
	virtual void SaveAllData();
	virtual void InitAllData();
	virtual BOOL Read(Junperisist *pPersistent);
	virtual BOOL Save(Junperisist *pPersistent);
	virtual BOOL Show(UnitSubSystem &UnitSys,ComponentManager *pManager, BOOL bReadOnlyDlg = FALSE)=0;
	int GetID()=0;
	int GetType();
	NameArray& GetArray()=0;
	static void Instance(NameArray &array);
	Jun();
	virtual ~Jun();
	Jun(const Jun &ref);
	Jun& operator=(const Jun &ref);
	
public:
	virtual CBitmap& GetBitMap()=0;
	void Draw(CDC* pDc,WorkSpaceRef &ref);
	BOOL Pick(CRect rc);
	BOOL Pick(CPoint point,int Size=0);
	void CenterPt(CPoint pt);
	CPoint CenterPt();
	Graphics* GetGarph();
	Manipulator* CreatManipulator(ComponentManager *pManager,int Size,BOOL bSingle = TRUE);

public:
	void EmptyLinkPipe(ComponentManager *pManager);
	void EmptyLinkPipe();
	void ChangePosition(ComponentManager *pManager,CPoint pt,int nSize);
	void DelLinkPipe(int nKey);
    BOOL AddLinkPipe(int nKey);
	//����������߼����ӹ�ϵɾ�����ӹܵ���Ϣ
	virtual void DelLinkPipeInfo(UINT nKey)=0;
	static PtFlyWeight  ms_CenterPt;
	static NumFlyWeight ms_InletEle;
	static NumFlyWeight ms_OutletEle;
	static PipeIDFlyWeight ms_PipeID;
	static StrFlyWeight ms_DisignFactor;			//��ʧ�������
	static StrFlyWeight ms_RawKey;
	static TransDataTable<2> ms_RawData;
	static ArrayFlyWeight<3> ms_InitGuess;			//��ʼ������²����ͣ�0��1��\��С\��λ
	static ArrayFlyWeight<3> ms_SpecialMark;		//ָ���ر��������ͱ��/Ĭ��Ϊ��ä�ܻ�رյķ���Ĭ�ϡ�J�ͱ�š�

public:
	virtual Transient* GetTransient();
	void SetPressType(CString strType);
	virtual void SetDesignFactor(CString strFactor);
	static const CmbDataItem ms_BasisArea[4];
	static const CmbDataItem ms_Condition[5];   //˲�䴥������
	static const CmbDataItem ms_ValveStatus[4];   //˲�䴥������
	static const CmbDataItem ms_PipePort[2];   //�ܵ��˿�
	static const CmbDataItem ms_EventType[24];   //�����¼�
	static const CmbDataItem ms_CurveType[2];   //�����������
	static KeyMap IDMap;
	
protected:
	int ConnectPipeNum();
	void AddPipeInfo(TableFlyWeight<4> &ref,int Key);
	void DelPipeInfo(TableFlyWeight<4> &ref,int nKey);
	BOOL IsExistOutPipe();
	BOOL IsExistInPipe();
	
private:
	virtual BOOL CanLink(int nMaxLink,int nKey)=0;
	ScenarioObject* DoClone() = 0;
	void MoveLinkPipe(ComponentManager *pManager,CPoint pt);
	void AddLinkPipe(ComponentManager *pManager,int nSize);
	//���ӹܵ���ڵ����ӹܿڵ���ʧϵ������Ϣ
	virtual void AddLinkPipeInfo(UINT nKey)=0;
	//�������Ԫ����ܵ���������Ϣ
	virtual void EmptyPipeInfo()=0;

protected:
	static void InitCurve(ArrayFlyWeight<13> &ref);
	void SetSpecial(int nSpecial);
	int m_nLinkPipeNum;
	
	template<class T> static int CreatKey(CMap<int,int,T,T>& map)
	{
		T temp;
		int nKey = 1;
		while(map.Lookup(nKey,temp))
			nKey++;
		return nKey;
	}
public:
	void Status(ComponentStatus &ref,BOOL bTrans=TRUE);
	static void AddID(CString ID);
	static CString CreatID();
	static void CreatRawKey();
};

inline int Jun::GetType()
{
	return 2;//����Ԫ��
}


#endif // !defined(AFX_JUN_H__A42D91AC_827B_4313_8723_18CBD215DF19__INCLUDED_)

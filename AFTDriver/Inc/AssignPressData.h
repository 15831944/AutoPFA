// AssignPressData.h: interface for the AssignPressData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ASSIGNPRESSDATA_H__4D1AA093_206D_4497_9DDC_383DC01098DA__INCLUDED_)
#define AFX_ASSIGNPRESSDATA_H__4D1AA093_206D_4497_9DDC_383DC01098DA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Junction.h"
#include "RowObjectFace.h"
#include "JunTransData.h"

class AFX_EXT_CLASS AssignPressData : public JunctionData  
{
public:
	static JunctionData* Creator();
	AssignPressData();
	virtual ~AssignPressData();
public:
	ListImp<StrArray<4> > PipeInfo();
	void PipeInfo(const ListImp<StrArray<4> >& strValue);
	CString DistanceUnit();
	void DistanceUnit(CString strValue);
	StrArray<3> Pressure();
	void Pressure(const StrArray<3>& strValue);

private:
	void AppendArray();
	void InitExtra(CString strData);
	virtual CString GetDefaultData();
public:
	JunTransData m_TranData;	
private:
	TableData<3> m_linkPipeK;			//52������ӽڵ�����ܵ�ʱ�ܵ��˿�kϵ��
										//53������ӽڵ������ܵ�ʱ�ܵ��˿�kϵ��
										//54���ܵ��˿���ڵ��߾���
	RowObjectFace<3> m_Press;			//ѹ������0��ͣ��ѹ��1����ֹѹ��\ֵ\��λ 
	RowObjectFace<1> m_EleUnit;			//�ܵ��˿���ڵ��߾��뵥λ
	//JunTransData m_TranData;			//
	RowObjectFace<10> m_Fth2;

};

#endif // !defined(AFX_ASSIGNPRESSDATA_H__4D1AA093_206D_4497_9DDC_383DC01098DA__INCLUDED_)

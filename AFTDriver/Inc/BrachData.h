// BrachData.h: interface for the BrachData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BRACHDATA_H__6F8FC7E4_7841_4B83_9626_773A27530C7C__INCLUDED_)
#define AFX_BRACHDATA_H__6F8FC7E4_7841_4B83_9626_773A27530C7C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Junction.h"
#include "JunTransData.h"
//��֧Ԫ��
class AFX_EXT_CLASS BrachData : public JunctionData  
{
public:
	static JunctionData* Creator();
	BrachData();
	virtual ~BrachData();
public:
	ListImp<StrArray<4> > PipeInfo();
	void PipeInfo(const ListImp<StrArray<4> >& strValue);
	StrArray<3> ImposeFlow();
	void ImposeFlow(const StrArray<3>& strValue);
	CString DistanceUnit();
	void DistanceUnit(CString strValue);

private:
	void AppendArray();
	void InitExtra(CString strData);
	virtual CString GetDefaultData();

public:
    JunTransData m_TranData;			//û�����ں���RowObjectFace<5> m_Periodic;
private:
	TableData<3> m_linkPipeK;			//52������ӽڵ�����ܵ�ʱ�ܵ��˿�kϵ��
										//53������ӽڵ������ܵ�ʱ�ܵ��˿�kϵ��
										//54���ܵ��˿���ڵ��߾���
	RowObjectFace<3> m_ImposeFlow;		//��������\��С\��λ
	RowObjectFace<1> m_EleUnit;			//�ܵ��˿���ڵ��߾��뵥λ
	//JunTransData m_TranData;			//û�����ں���RowObjectFace<5> m_Periodic;
	RowObjectFace<3> m_FthSourceTempture;  //�Ƿ�ѡ��/��С/��λ
	RowObjectFace<1> m_FthUnknow;          //none


	
};

#endif // !defined(AFX_BRACHDATA_H__6F8FC7E4_7841_4B83_9626_773A27530C7C__INCLUDED_)

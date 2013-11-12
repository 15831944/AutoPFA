// AssignFlowData.h: interface for the AssignFlowData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ASSIGNFLOWDATA_H__AFC48AF4_8E07_46C7_B693_1640110329E9__INCLUDED_)
#define AFX_ASSIGNFLOWDATA_H__AFC48AF4_8E07_46C7_B693_1640110329E9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "RowObjectFace.h"
#include "Junction.h"
#include "JunTransData.h"
//ָ������
class AFX_EXT_CLASS AssignFlowData : public JunctionData  
{
public:
	static JunctionData* Creator();
	AssignFlowData();
	virtual ~AssignFlowData();
public:
	StrArray<3> Flow();
	void Flow(const StrArray<3>& strValue);
	CString FlowDir();
	void FlowDir(CString strValue);
	CString K();
	void K(CString strValue);
	StrArray<4> InitPress();
	void InitPress(const StrArray<4>& strValue);

private:
	void AppendArray();
	virtual CString GetDefaultData();
	void InitExtra(CString strData);
public:
	JunTransData m_TranData;
private:
	RowObjectFace<3> m_Flow;				//��������\��С\��λ
	RowObjectFace<1> m_FlowDir;				//0���������룬1����������
	RowObjectFace<1> m_K;					//��ʧϵ��Kֵ	
	//m_TranData
	RowObjectFace<4> m_InitPress;			//�㶨����Ϊ0�ĳ�ʼ��ѹ����0��û��ѡ��-1ѡ�У�\ѹ�����ͣ�0ˮͷ��1��ѹ����\ѹ��ֵ\��λ
	RowObjectFace<2> m_FthUnknown1;			//0,None;

};

#endif // !defined(AFX_ASSIGNFLOWDATA_H__AFC48AF4_8E07_46C7_B693_1640110329E9__INCLUDED_)

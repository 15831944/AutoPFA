// PCFAssignFlow.h: interface for the AssignFlowData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PCFASSIGNFLOW_H__AFC48AF4_8E07_46C7_B693_1640110329E9__INCLUDED_)
#define AFX_PCFASSIGNFLOW_H__AFC48AF4_8E07_46C7_B693_1640110329E9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//ָ������
#include "PCFJun.h"
#include "RowObjectFace.h"
#include "JunTransData.h"
#include "Junction.h"

class AFX_EXT_CLASS PCFAssignFlow : public PCFJun  
{
public:
// 	void SetFlowDir( bool dFlowDir );
// 	bool GetFlowDir();
// 	void SetK( double dK );
// 	double GetK();
	CString GetK();
	void SetK(CString strValue);
	StrArray<4> GetAssignInitPress();
	void SetAssignInitPress(const StrArray<4>& strValue);
	CString GetAssignFlowDir();
	void SetAssignFlowDir(CString strValue);

	StrArray<3> GetAssignFlow();
	void SetAssignFlow(const StrArray<3>& strValue);

	static PCFJun* Creator();
	PCFAssignFlow();
	virtual ~PCFAssignFlow();
	void Init( const CStringArray& wordArray );

//	JunTransData m_TranData;
private:
	RowObjectFace<3> m_Flow;				//��������\��С\��λ
//	bool m_FlowDir;				//0���������룬1����������
//	double m_K;					//��ʧϵ����
	RowObjectFace<1> m_FlowDir;				//0���������룬1����������
	RowObjectFace<1> m_K;					//��ʧϵ��Kֵ	
	//m_TranData
//	RowObjectFace<4> m_InitPress;			//�㶨����Ϊ0�ĳ�ʼ��ѹ����0��û��ѡ��-1ѡ�У�\ѹ�����ͣ�0ˮͷ��1��ѹ����\ѹ��ֵ\��λ
};
#endif // !defined(AFX_PCFASSIGNFLOW_H__AFC48AF4_8E07_46C7_B693_1640110329E9__INCLUDED_)



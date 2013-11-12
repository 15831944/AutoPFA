// CalcAssignFlow.h: interface for the CalcAssignFlow class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CALCASSIGNFLOW_H__2EA86D2A_08BB_4592_93D2_2836EF588C49__INCLUDED_)
#define AFX_CALCASSIGNFLOW_H__2EA86D2A_08BB_4592_93D2_2836EF588C49__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CalcJun.h"
#include "CalcTransData.h"

class AFX_EXT_CLASS CalcAssignFlow : public CalcJun  
{
public:
	ostream& Write(ostream& CalcOut);
	static CalcJun* Creator();
	CalcAssignFlow();
	virtual ~CalcAssignFlow();

public:
	void K(double dValue);
	void FlowDir(int nValue);
	void FlowType(int nValue);
	void Flow(double dValue);
	void SelInitPress(int nValue);
	void InitPressType(int nValue);
	void InitPress(double dValue);

	double K();
	int FlowType();
	double Flow();
	int SelInitPress();
	int InitPressType();
	double InitPress();
private:
	double   m_dK;						//��ʧϵ��Kֵ
	int      m_nFlowDir;				//0���������룬1����������
	int      m_nFlowType;				//��������\��С
	double   m_dFlow;				    //��������\��С
	int      m_bSelInitPress;           //�㶨����Ϊ0�ĳ�ʼ��ѹ����0��û��ѡ��1ѡ�У�
	int      m_nInitPressType;			//ѹ�����ͣ�0ˮͷ��1��ѹ����
	double   m_dInitPress;				//��ʼ��ѹ��

public:
	CalcTransData m_TranData;
};

#endif // !defined(AFX_CALCASSIGNFLOW_H__2EA86D2A_08BB_4592_93D2_2836EF588C49__INCLUDED_)

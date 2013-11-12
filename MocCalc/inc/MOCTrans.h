// MOCTrans.h: interface for the MOCTrans class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MOCTRANS_H__4C1ACEF8_F59A_48F0_9AF6_B98577B724A6__INCLUDED_)
#define AFX_MOCTRANS_H__4C1ACEF8_F59A_48F0_9AF6_B98577B724A6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CalcTrans;
class MOCComponentMgr;
class TransOutModel;

#include "MOCTransOutControl.h"

class MOCTrans  
{
public:
	BOOL InitTrans(MOCComponentMgr &mgr);
	void CalcImpulse(MOCComponentMgr &mgr,TransOutModel &model);
	BOOL Read(CalcTrans& data);
	MOCTrans();
	virtual ~MOCTrans();
public:
	int Frequency();
	BOOL Cavitation();
	BOOL VariableR();
	BOOL Artificial();
	double Criteria();
	double MinFlow();
	double StartTime();
private:
	double m_StartTime;				    //˲̬ģ�⿪ʼʱ��
	double m_StopTime;					//˲̬ģ�����ʱ��
	int m_Frequency;					//�����������Ƶ��
	int m_Cavitation;					//0����������Ѩ���ڣ�1�����Ǵ�����Ѩ
	int m_VariableR;					//0���ܵ�����ϵ��ʹ����̬����ϵ����1�����ݵ�ǰ˲̬��������ܵ�����ϵ��
	int m_Artificial;					//ֹͣ���������⵽�˹�˲����0��������˹�˲�䣬1������˹�˲��
	double m_Criteria;					//�㶨����������˲������ʼ���ݱ�׼�������ٷ��������磺0.5%��"0.5"��ʾ��
	double m_MinFlow;					//��������ֵ��׼�����������ڱ�׼��������������Ϊ����Ϊ0��
	int m_TotalSteps;					//˲̬ģ���ܼ��㲽��
	double m_TimeStep;					//���ƹܵ�ʱ�䲽��
	MOCTransOutControl m_outControl;

};

#endif // !defined(AFX_MOCTRANS_H__4C1ACEF8_F59A_48F0_9AF6_B98577B724A6__INCLUDED_)

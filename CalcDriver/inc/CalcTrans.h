// CalcTrans.h: interface for the CalcTrans class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CALCTRANS_H__A8977787_23E2_46CD_AF15_F18C10ACAB45__INCLUDED_)
#define AFX_CALCTRANS_H__A8977787_23E2_46CD_AF15_F18C10ACAB45__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class AFX_EXT_CLASS CalcTrans  
{
public:
	CalcTrans();
	virtual ~CalcTrans();

public:
	void StartTime(double dValue);
	void StopTime(double dValue);
	void TimeStep(double dValue);
	void Frequency(int nValue);
	void Cavitation(int nValue);
	void VariableR(int nValue);
	void Artificial(int nValue);
	void Criteria(double dValue);
	void MinFlow(double dValue);
	void TotalSteps(int nValue);

	double StartTime();
	double StopTime();
	double TimeStep();
	int Frequency();
	int Cavitation();
	int VariableR();
	int Artificial();
	double Criteria();
	double MinFlow();
	int TotalSteps();
	friend ostream& operator<< (ostream &CalcOut,const CalcTrans &ref);
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

};

#endif // !defined(AFX_CALCTRANS_H__A8977787_23E2_46CD_AF15_F18C10ACAB45__INCLUDED_)

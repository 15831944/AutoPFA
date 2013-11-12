// TransControlPerisistent.h: interface for the TransControlPerisistent class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRANSCONTROLPERISISTENT_H__3563DA52_E878_4E76_90B6_4A2EE3E6A37C__INCLUDED_)
#define AFX_TRANSCONTROLPERISISTENT_H__3563DA52_E878_4E76_90B6_4A2EE3E6A37C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class AFX_EXT_CLASS TransControlPerisistent  
{
public:
	TransControlPerisistent();
	virtual ~TransControlPerisistent();

public:
	CString StartTime();
	void StartTime(CString strValue);
	CString StopTime();
	void StopTime(CString strValue);
	CString TimeUnit();
	void TimeUnit(CString strValue);
	CString Frequency();
	void Frequency(CString strValue);
	CString Cavitation();
	void Cavitation(CString strValue);
	CString VariableR();
	void VariableR(CString strValue);
	CString Artificial();
	void Artificial(CString strValue);
	CString Criteria();
	void Criteria(CString strValue);
	CString MinFlow();
	void MinFlow(CString strValue);
	CString MinFlowUnit();
	void MinFlowUnit(CString strValue);
	CString TotalSteps();
	void TotalSteps(CString strValue);


	CString TimeStep();
	void TimeStep( CString strValue );
	CString TimeStepUnits();
	void TimeStepUnits( CString strValue );
	CString DifferenceMethod();
	void DifferenceMethod( CString strValue );
	CString RelativeTolerance();
	void RelativeTolerance( CString strValue );
	CString AbsoluteTolerance();
	void AbsoluteTolerance( CString strValue );
	CString AbsoluteToleranceUnits();
	void AbsoluteToleranceUnits( CString strValue );
	CString MaxIterations();
	void MaxIterations( CString strValue );
	CString Relaxation();
	void Relaxation( CString strValue );

private:
	CString m_StartTime;				//˲̬ģ�⿪ʼʱ��
	CString m_StopTime;					//˲̬ģ�����ʱ��
	CString m_TimeUnit;					
	CString m_Frequency;				//�����������Ƶ��
	CString m_Cavitation;				//0����������Ѩ���ڣ�1�����Ǵ�����Ѩ
	CString m_VariableR;				//0���ܵ�����ϵ��ʹ����̬����ϵ����1�����ݵ�ǰ˲̬��������ܵ�����ϵ��
	CString m_Artificial;				//ֹͣ���������⵽�˹�˲����0��������˹�˲�䣬1������˹�˲��
	CString m_Criteria;					//�㶨����������˲������ʼ���ݱ�׼�������ٷ��������磺0.5%��"0.5"��ʾ��
	CString m_MinFlow;					//��������ֵ��׼�����������ڱ�׼��������������Ϊ����Ϊ0��
	CString m_MinFlowUnit;				//
	CString m_TotalSteps;				//˲̬ģ���ܼ��㲽��

	CString  m_TimeStep;
	CString  m_TimeStepUnits;
	CString  m_DifferenceMethod;
	CString  m_RelativeTolerance;
	CString  m_AbsoluteTolerance;
	CString  m_AbsoluteToleranceUnits;
	CString  m_MaxIterations;
	CString  m_Relaxation; 

};
/*------------------------------------------*/
inline CString TransControlPerisistent::StartTime()
{
	return m_StartTime;
}
inline void TransControlPerisistent::StartTime(CString strValue)
{
	m_StartTime = strValue;
}
/*------------------------------------------*/
inline CString TransControlPerisistent::StopTime()
{
	return m_StopTime;
}
inline void TransControlPerisistent::StopTime(CString strValue)
{
	m_StopTime = strValue;
}
/*------------------------------------------*/
inline CString TransControlPerisistent::TimeUnit()
{
	return m_TimeUnit;
}
inline void TransControlPerisistent::TimeUnit(CString strValue)
{
	m_TimeUnit = strValue;
}
/*------------------------------------------*/
inline CString TransControlPerisistent::Frequency()
{
	return m_Frequency;
}
inline void TransControlPerisistent::Frequency(CString strValue)
{
	m_Frequency = strValue;
}
/*------------------------------------------*/
inline CString TransControlPerisistent::Cavitation()
{
	return m_Cavitation;
}
inline void TransControlPerisistent::Cavitation(CString strValue)
{
	m_Cavitation = strValue;
}
/*------------------------------------------*/
inline CString TransControlPerisistent::VariableR()
{
	return m_VariableR;
}
inline void TransControlPerisistent::VariableR(CString strValue)
{
	m_VariableR = strValue;
}
/*------------------------------------------*/
inline CString TransControlPerisistent::Artificial()
{
	return m_Artificial;
}
inline void TransControlPerisistent::Artificial(CString strValue)
{
	m_Artificial = strValue;
}
/*------------------------------------------*/
inline CString TransControlPerisistent::Criteria()
{
	return m_Criteria;
}
inline void TransControlPerisistent::Criteria(CString strValue)
{
	m_Criteria = strValue;
}
/*------------------------------------------*/
inline CString TransControlPerisistent::MinFlow()
{
	return m_MinFlow;
}
inline void TransControlPerisistent::MinFlow(CString strValue)
{
	m_MinFlow = strValue;
}
/*------------------------------------------*/
inline CString TransControlPerisistent::MinFlowUnit()
{
	return m_MinFlowUnit;
}
inline void TransControlPerisistent::MinFlowUnit(CString strValue)
{
	m_MinFlowUnit = strValue;
}
/*------------------------------------------*/
inline CString TransControlPerisistent::TotalSteps()
{
	return m_TotalSteps;
}
inline void TransControlPerisistent::TotalSteps(CString strValue)
{
	m_TotalSteps = strValue;
}



/*------------------------------------------*/
inline CString TransControlPerisistent::TimeStep()
{
	return m_TimeStep;
}
inline void TransControlPerisistent::TimeStep(CString strValue)
{
	m_TimeStep = strValue;
}
/*------------------------------------------*/
inline CString TransControlPerisistent::TimeStepUnits()
{
	return m_TimeStepUnits;
}
inline void TransControlPerisistent::TimeStepUnits(CString strValue)
{
	m_TimeStepUnits = strValue;
}
/*------------------------------------------*/
inline CString TransControlPerisistent::DifferenceMethod()
{
	return m_DifferenceMethod;
}
inline void TransControlPerisistent::DifferenceMethod(CString strValue)
{
	m_DifferenceMethod = strValue;
}
/*------------------------------------------*/
inline CString TransControlPerisistent::RelativeTolerance()
{
	return m_RelativeTolerance;
}
inline void TransControlPerisistent::RelativeTolerance(CString strValue)
{
	m_RelativeTolerance = strValue;
}
/*------------------------------------------*/
inline CString TransControlPerisistent::AbsoluteTolerance()
{
	return m_AbsoluteTolerance;
}
inline void TransControlPerisistent::AbsoluteTolerance(CString strValue)
{
	m_AbsoluteTolerance = strValue;
}
/*------------------------------------------*/
inline CString TransControlPerisistent::AbsoluteToleranceUnits()
{
	return m_AbsoluteToleranceUnits;
}
inline void TransControlPerisistent::AbsoluteToleranceUnits(CString strValue)
{
	m_AbsoluteToleranceUnits = strValue;
}
/*------------------------------------------*/
inline CString TransControlPerisistent::MaxIterations()
{
	return m_MaxIterations;
}
inline void TransControlPerisistent::MaxIterations(CString strValue)
{
	m_MaxIterations = strValue;
}
/*------------------------------------------*/
inline CString TransControlPerisistent::Relaxation()
{
	return m_Relaxation;
}
inline void TransControlPerisistent::Relaxation(CString strValue)
{
	m_Relaxation = strValue;
}
#endif // !defined(AFX_TRANSCONTROLPERISISTENT_H__3563DA52_E878_4E76_90B6_4A2EE3E6A37C__INCLUDED_)

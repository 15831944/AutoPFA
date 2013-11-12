// CalcPeriodic.h: interface for the CalcPeriodic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CALCPERIODIC_H__40B48C07_1EB2_4437_A7AA_946050359B43__INCLUDED_)
#define AFX_CALCPERIODIC_H__40B48C07_1EB2_4437_A7AA_946050359B43__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class AFX_EXT_CLASS CalcPeriodic  
{
public:
	CalcPeriodic();
	virtual ~CalcPeriodic();
public:
	BOOL Periodic();
	BOOL Chop();
	double Frequency();
	double Amplitude();
	void Periodic(int nValue);
	void Chop(int nValue);
	void Frequency(double dValue);
	void Amplitude(double dValue);
	friend	ostream& operator<< (ostream &CalcOut,const CalcPeriodic &ref);
private:
	int 	m_bPeriodic;			//0������������û��ѡ��1������������ѡ��
	int 	m_bChop;				//û��ѡ��ʹ�����Һ����ľ���ֵ��1��ѡ��ʹ�����Һ����ľ���ֵ
	double	m_dFrequency;			//���Һ���Ƶ��
	double	m_dAmplitude;			//���Һ������

};

#endif // !defined(AFX_CALCPERIODIC_H__40B48C07_1EB2_4437_A7AA_946050359B43__INCLUDED_)

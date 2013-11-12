// MOCPeriodic.h: interface for the MOCPeriodic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MOCPERIODIC_H__FC02FB0C_1342_4D47_AA52_9C054F8479BE__INCLUDED_)
#define AFX_MOCPERIODIC_H__FC02FB0C_1342_4D47_AA52_9C054F8479BE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
class CalcPeriodic;
#include "MOCTable.h"

class MOCPeriodic  
{
public:
	BOOL IsSelPeriodic();
	double GetTransY(double dX);
	void Tran(PFUNTRAN pTran);
	void Read(CalcPeriodic& periodic);
	MOCPeriodic();
	virtual ~MOCPeriodic();

private:
	BOOL 	m_bPeriodic;			//0������������û��ѡ��1������������ѡ��
	BOOL 	m_bChop;				//û��ѡ��ʹ�����Һ����ľ���ֵ��1��ѡ��ʹ�����Һ����ľ���ֵ
	double	m_dFrequency;			//���Һ���Ƶ��
	double	m_dAmplitude;			//���Һ������
};

#endif // !defined(AFX_MOCPERIODIC_H__FC02FB0C_1342_4D47_AA52_9C054F8479BE__INCLUDED_)

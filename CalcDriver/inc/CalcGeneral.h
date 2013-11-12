// CalcGeneral.h: interface for the CalcGeneral class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CALCGENERAL_H__2E6ECEDD_0220_48C6_A9D7_DD8B9B09D63B__INCLUDED_)
#define AFX_CALCGENERAL_H__2E6ECEDD_0220_48C6_A9D7_DD8B9B09D63B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CalcJun.h"
#include "CalcCurve.h"

class AFX_EXT_CLASS CalcGeneral : public CalcJun  
{
public:
	ostream& Write(ostream& CalcOut);
	static CalcJun* Creator();
	CalcGeneral();
	virtual ~CalcGeneral();

public:
	void LossType(int nValue);
	void K(double dValue);
	void BasisAreaType(int nValue);
	void BasisArea(double dValue);
	
	int LossType();
	double K();
	int BasisAreaType();
	double BasisArea();
private:
	int      m_nLossType;                       //1��Kϵ���㶨��2��Kϵ���仯��3����������
	double   m_dK;								//Kϵ��ֵ
	int      m_nBasisAreaType;					//��ʧģ�͵��������0��Ĭ�����ιܵ������1�����ιܵ����2���û�ָ�����3���û�ָ��ֱ��
	double   m_dBasisArea;						//���Ŷorֱ��
public:
	CalcCurve m_Curve;
};

#endif // !defined(AFX_CALCGENERAL_H__2E6ECEDD_0220_48C6_A9D7_DD8B9B09D63B__INCLUDED_)

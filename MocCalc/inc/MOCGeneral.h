// MOCGeneral.h: interface for the MOCGeneral class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MOCGENERAL_H__EA2A860F_5B82_48CC_A07E_950D9FE3F54E__INCLUDED_)
#define AFX_MOCGENERAL_H__EA2A860F_5B82_48CC_A07E_950D9FE3F54E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MOCJun.h"
#include "MOCPolynomial.h"

class MOCGeneral : public MOCJun  
{
public:
	BOOL Read(CalcJun *pData);
	static MOCJun* Creator();
	MOCGeneral();
	virtual ~MOCGeneral();

private:
	void CalcStm();
	BOOL InitEndInfo();

private:
	void ImpulseRCurve();
	void CalcImpulse(MOCTrans &trans,double dTime);
	void UpdataEnd();
	void StmRCurve();
	double CalcRCurve(double dPress);
	double CalcMass(double dPress);
	double GetCurPress(double dX);
	double GetCurK();
	int      m_nLossType;                       //1��Kϵ���㶨��2��Kϵ���仯��3����������
	double   m_dK;								//Kϵ��ֵ
	int      m_nBasisAreaType;					//��ʧģ�͵��������0��Ĭ�����ιܵ������1�����ιܵ����2���û�ָ�����3���û�ָ��ֱ��
	double   m_dBasisArea;						//���Ŷorֱ��
	MOCPolynomial m_Polynomial;
	double m_dCurMass;
};

#endif // !defined(AFX_MOCGENERAL_H__EA2A860F_5B82_48CC_A07E_950D9FE3F54E__INCLUDED_)

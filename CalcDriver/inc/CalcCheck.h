// CalcCheck.h: interface for the CalcCheck class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CALCCHECK_H__82A5102B_D397_4F9D_86E9_BA884AD2ABDA__INCLUDED_)
#define AFX_CALCCHECK_H__82A5102B_D397_4F9D_86E9_BA884AD2ABDA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CalcJun.h"
#include "CalcTransData.h"

class AFX_EXT_CLASS CalcCheck : public CalcJun  
{
public:
	ostream& Write(ostream& CalcOut);
	static CalcJun* Creator();
	CalcCheck();
	virtual ~CalcCheck();
public:
	void LossType(int nValue);
	void KOrCv(double dValue);
	void BasisAreaType(int nValue);
	void BasisArea(double dValue);
	void ReOpenPressType(int nValue);
	void ReOpenPress(double dValue);
	void CloseVel(double dValue);
	
	int LossType();
	double KOrCv();
	int BasisAreaType();
	double BasisArea();
	int ReOpenPressType();
	double ReOpenPress();
	double CloseVel();
private:
	int    m_nLossType;						    //��ʧģ��0������ϵ��ģ�ͣ�1��Kϵ��ģ��			                                           
	double m_dKOrCv;					        //K��Cvϵ��ֵ
    int    m_nBasisAreaType;					//��ʧģ�͵��������0��Ĭ�����ιܵ������1�����ιܵ����2���û�ָ�����3���û�ָ��ֱ��
	double m_dBasisArea;						//���Ŷorֱ��
	int    m_nReOpenPressType;					//���´򿪷���Delta(ѹ����ˮͷ)0��ˮͷ1��ѹ��
	double m_dReOpenPress;					    //ѹ��ֵ	
	double m_dCloseVel;					        //�رշ��ŵ���С�����ٶ�\�ٶȵ�λ

public:
	CalcTransData m_TranData;
};

#endif // !defined(AFX_CALCCHECK_H__82A5102B_D397_4F9D_86E9_BA884AD2ABDA__INCLUDED_)

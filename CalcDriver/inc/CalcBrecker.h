// CalcBrecker.h: interface for the CalcBrecker class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CALCBRECKER_H__98B0AAB3_6345_4334_9407_7E377F562CC4__INCLUDED_)
#define AFX_CALCBRECKER_H__98B0AAB3_6345_4334_9407_7E377F562CC4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CalcJun.h"

class AFX_EXT_CLASS CalcBrecker : public CalcJun  
{
public:
	ostream& Write(ostream& CalcOut);
	static CalcJun* Creator();
	CalcBrecker();
	virtual ~CalcBrecker();

public:
	void Type(int nValue);
	void OrificeInCdA(double dValue);
	void OrificeOutCdA(double dValue);
	void InterMediateCdA(double dValue);
	void MediateActivationType(int nValue);
	void MediateActivation(double dValue);
	void CrackPressType(int nValue);
	void CrackPress(double dValue);
	void LiquidTempType(int nValue);
	void LiquidTemp(double dValue);
	void GasWeight(double dValue);
	void CpCv(double dValue);
	void GasTemp(double dValue);
	void GasPress(double dValue);
	void GasMass(double dValue);
	void ConnectPipe(int nValue);

	int Type();
	double OrificeInCdA();
	double OrificeOutCdA();
	double InterMediateCdA();
	int MediateActivationType();
	double MediateActivation();
	int CrackPressType();
	double CrackPress();
	int LiquidTempType();
	double LiquidTemp();
	double GasWeight();
	double CpCv();
	double GasTemp();
	double GasPress();
	double GasMass();
	int ConnectPipe();
private:
	int			m_nType;			             //��������0:����ƻ��������ͷ�1:����ƻ�2:�����ͷ�3:����ƻ������׶������ͷ�
	double      m_dOrificeInCdA;		         //�׿�ȫ�����������ֵ
	double      m_dOrificeOutCdA;			     //�������ֵ/��λ
	double      m_dInterMediateCdA;			     //�׿�ȫ����ý���������ֵ
	int		    m_nMediateActivationType;		 //ý��׿ڼ����׼0��ѹ����ͬ1�����ٲ�ͬ
	double      m_dMediateActivation;            //��׼ֵ
	int 		m_nCrackPressType;				 //���ѵ�ѹ������0��ˮͷ��1��ѹ��
	double		m_dCrackPress;				     //���ѵ�ѹ��
	int         m_nLiquidTempType;				 //0��ϵͳ����1���û�ָ���¶�
	double		m_dLiquidTemp;					 //�����¶�
	double		m_dGasWeight;					 //��������
	double      m_dCpCv;                         //Cp/Cv
	double      m_dGasTemp;						 //�����¶�
	double      m_dGasPress;				     //����ѹ��
	double      m_dGasMass;						 //�ڲ���ʼ��������������
	int			m_nConnectPipe;					 //���ӹܵ���0�������ܵ�1��һ���ܵ�
};


#endif // !defined(AFX_CALCBRECKER_H__98B0AAB3_6345_4334_9407_7E377F562CC4__INCLUDED_)

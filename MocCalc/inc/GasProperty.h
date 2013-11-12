// GasProperty.h: interface for the GasProperty class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GASPROPERTY_H__5C814EF6_87A6_41BD_B14D_03BE9373DA12__INCLUDED_)
#define AFX_GASPROPERTY_H__5C814EF6_87A6_41BD_B14D_03BE9373DA12__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
class CalcBrecker;

class GasProperty  
{
public:
	GasProperty();
	virtual ~GasProperty();
public:
	double LiquidTemp();
	double r();
	double GasTemp();
	double GasPress();
	double GasMolMass();
	double GasFlow();
	void GasMolMass(double dMass);
	double GasInitVolume(double dPress);//���ݳ�ʼ��������̬ѹ���ó�ʼ���
	void GasFlow(double dGasFlow);
	void Read(CalcBrecker &Data);
	double Sonicin(double dCdAin);
	double SonicOut(double dCdAOut,double dPress);
	double SubSonicin(double dCdAin,double dPress);
	double SubSonicOut(double dCdAOut,double dPress);
	double SubSonicInC1(double dCdAin);
	double SubSonicOutC1(double dCdAOut);
	double a();
	double b();
private:
	double Sonic(double dCdA,double dT,double dPress);
	double		m_dLiquidTemp;					 //�����¶�
	double		m_dGasWeight;					 //��������
	double      m_dCpCv;                         //Cp/Cv
	double      m_dGasTemp;						 //�����¶�
	double      m_dGasPress;				     //����ѹ��
	double      m_dGasMass;						 //�ڲ���ʼ��������������
	double      m_dOldGasFlow;                   //������������
	
};

#endif // !defined(AFX_GASPROPERTY_H__5C814EF6_87A6_41BD_B14D_03BE9373DA12__INCLUDED_)

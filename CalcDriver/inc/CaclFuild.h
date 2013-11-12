// CaclFuild.h: interface for the CaclFuild class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CACLFUILD_H__BE21F9AB_E924_4175_927A_9B57C735E852__INCLUDED_)
#define AFX_CACLFUILD_H__BE21F9AB_E924_4175_927A_9B57C735E852__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class AFX_EXT_CLASS CalcFuild  
{
public:
	CalcFuild();
	virtual ~CalcFuild();

public:
	void Temperature(double dValue);
	void Density(double dValue);
	void Viscos(double dValue);
	void Modulus(double dValue);
	void VaporPress(double dValue);
	void AtmosphericPress(double dValue);
	void Gravity(double dValue);
	void ReTransLam(double dValue);
	void ReTransTurb(double dValue);
	double Temperature()const;
	double Density()const;
	double Viscos()const;
	double Modulus()const;
	double VaporPress()const;
	double AtmosphericPress()const;
	double Gravity()const;
	double ReTransLam()const;
	double ReTransTurb()const;
	friend ostream& operator<<(ostream &CalcOut,const CalcFuild &ref);
private:
	double m_dTemperature;					//�����¶�
	double m_dDensity;						//�����ܶ�
	double m_dViscosity;					//�����˶�ճ��
	double m_dBulkModulus;					//�������ģ��
	double m_dVaporPressure;				//��������ѹ��
	double m_dAtmosphericPressure;			//����ѹ��
    double m_dGravity;						//�������ٶ�
	double m_dReTransLam;					//������ټ��
	double m_dReTransTurb;					//������ټ��
};


#endif // !defined(AFX_CACLFUILD_H__BE21F9AB_E924_4175_927A_9B57C735E852__INCLUDED_)

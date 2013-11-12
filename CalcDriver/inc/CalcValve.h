// CalcValve.h: interface for the CalcValve class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CALCVALVE_H__521AA035_FC83_4E18_B345_2A4802DE3CF0__INCLUDED_)
#define AFX_CALCVALVE_H__521AA035_FC83_4E18_B345_2A4802DE3CF0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CalcJun.h"
#include "CalcTransData.h"

class AFX_EXT_CLASS CalcValve : public CalcJun  
{
public:
	ostream& Write(ostream& CalcOut);
	static CalcJun* Creator();
	CalcValve();
	virtual ~CalcValve();
public:
	void LossType(int nValue);
	void KOrCv(double dValue);
	void BasisAreaType(int nValue);
	void BasisArea(double dValue);
	void Type(int nValue);
	void ExitPressType(int nValue);
	void ExitPress(double dValue);

	int LossType();
	double KOrCv();
	int BasisAreaType();
	double BasisArea();
	int Type();
	int ExitPressType();
	double ExitPress();
private:
	int      m_nLossType;                       //��ʧģ��0������ϵ��ģ�ͣ�1��Kϵ��ģ��
	double   m_dKOrCv;						    //K��Cvϵ��ֵ
	int      m_nBasisAreaType;					//��ʧģ�͵��������0��Ĭ�����ιܵ������1�����ιܵ����2���û�ָ�����3���û�ָ��ֱ��
	double   m_dBasisArea;						//���Ŷorֱ��
	int		 m_nType;						    //����(0����ͨ���ţ�1��ѡ�з���Ϊ���ڷ���)
	int      m_nExitPressType;					//����ѹ������0��ˮͷ1��ѹ��
	double   m_dExitPress;					    //����ѹ��

public:
	CalcTransData m_TranData;

};

#endif // !defined(AFX_CALCVALVE_H__521AA035_FC83_4E18_B345_2A4802DE3CF0__INCLUDED_)

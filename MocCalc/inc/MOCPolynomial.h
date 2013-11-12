// MOCPolynomial.h: interface for the MOCPolynomial class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MOCPOLYNOMIAL_H__51E552DB_47AA_451C_AAAA_3AFBCB96E57B__INCLUDED_)
#define AFX_MOCPOLYNOMIAL_H__51E552DB_47AA_451C_AAAA_3AFBCB96E57B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
class CalcCurve;
#include "MOCTable.h"

class MOCPolynomial  
{
public:
	
	void Read(CalcCurve &curve);
	MOCPolynomial();
	virtual ~MOCPolynomial();
	
public:
	double GetY(MOCCurveData & data,double dX);
	int CurveType();
	int XAxisType();
	int YAxisType();
	double MaxX();
	int Order();
private:
	double GetY(double dX);
	int m_nCurveType;			//��������: �������ͣ�-2��Kֵ�仯��1��ѹ����ʧ����ʽ��2��ѹ����ʧ�ڲ�ֵ��
	int m_nXAxisType;			//X������������ֱ��
	int m_nYAxisType;			//Y������������ֱ��
	double m_dMaxX;				//�����Ա������������ֵ
    int    m_nOrder;			//������Ͻ���
	double m_dPrame[5];		    //��ʽ�еĲ����ͳ���a��b��c��d��e��ֵ

};

#endif // !defined(AFX_MOCPOLYNOMIAL_H__51E552DB_47AA_451C_AAAA_3AFBCB96E57B__INCLUDED_)

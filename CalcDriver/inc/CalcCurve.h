// CalcCurve.h: interface for the CalcCurve class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CALCCURVE_H__2FBC8CD9_0E97_495C_8BC7_34EF993ECC24__INCLUDED_)
#define AFX_CALCCURVE_H__2FBC8CD9_0E97_495C_8BC7_34EF993ECC24__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class AFX_EXT_CLASS CalcCurve  
{
public:
	CalcCurve();
	virtual ~CalcCurve();
public:
	void CurveType(int nValue);
	void XAxisType(int nValue);
	void YAxisType(int nValue);
	void MaxX(double dValue);
	void Order(int nValue);
	void A(double dValue);
	void B(double dValue);
	void C(double dValue);
	void D(double dValue);
	void E(double dValue);
	int CurveType();
	int XAxisType();
	int YAxisType();
	double MaxX();
	int Order();
	void Prame(double dPrame[])const;//
	friend	ostream& operator<< (ostream &CalcOut,const CalcCurve &ref);
private:
	int m_nCurveType;			//��������: �������ͣ�-2��Kֵ�仯��1��ѹ����ʧ����ʽ��2��ѹ����ʧ�ڲ�ֵ��
	int m_nXAxisType;			//X������������ֱ��
	int m_nYAxisType;			//Y������������ֱ��
	double m_dMaxX;				//�����Ա������������ֵ
    int    m_nOrder;			//������Ͻ���
	double m_dPrame[5];		//��ʽ�еĲ����ͳ���a��b��c��d��e��ֵ
};

#endif // !defined(AFX_CALCCURVE_H__2FBC8CD9_0E97_495C_8BC7_34EF993ECC24__INCLUDED_)

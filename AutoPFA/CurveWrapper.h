// CurveWrapper.h: interface for the CurveWrapper class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CURVEWRAPPER_H__A0EBF073_F061_4171_807F_7B6B6D8CD23C__INCLUDED_)
#define AFX_CURVEWRAPPER_H__A0EBF073_F061_4171_807F_7B6B6D8CD23C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "ArrayFlyWeight.h"
#include "TransDataTable.h"
class PageChart;

class CurveWrapper  
{
public:
	void SetLossType(int nType);
	int GetLossType();
	void SetYAxisType(int nType);
	int GetYAxisType();
	void SetYAxisUnit(CString strUnit);
	CString GetYAxisUnit();
	void SetXAxisType(int nType);
	int GetXAxisType();
	void SetXAxisUnit(CString strUnit);
	CString GetXAxisUnit();
	void MaxValue(double dValue);
	double MaxValue();
	void CurveType(int nType);
	int CurveType();
	void PrameNum(int nNum);
	int PrameNum();
	void GetPrame(double dPrame[]);
	void SetPrame(double dPrame[]);
	void CurveWrapper::InitChart(PageChart &Page,TransDataTable<2> &rawData);
	CurveWrapper(ArrayFlyWeight<13> &Curve);
	virtual ~CurveWrapper();

private:
	ArrayFlyWeight<13>& m_Curve;		//��ʧģ��(0������ϵ��ģ�ͣ�1��Kϵ��ģ��3��������ϵ��)
										//Y������������ֱ��[]
										//Y�������λ[]
										//X������������ֱ��[]
										//X�������λ[]
										//x�����ȡֵ[]
										//��������[�������ͣ�-2��Kֵ�仯��1��ѹ����ʧ����ʽ��2��ѹ����ʧ�ڲ�ֵ��]
										//��ʽ�в����ͳ����ĸ���[]
										//��ʽ�еĲ����ͳ���a��b��c��d��e��ֵ[]

};

#endif // !defined(AFX_CURVEWRAPPER_H__A0EBF073_F061_4171_807F_7B6B6D8CD23C__INCLUDED_)

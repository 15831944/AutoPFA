// PumpConfigData.h: interface for the PumpConfigData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PUMPCONFIGDATA_H__3099EAFC_48FD_462B_9D09_75B414ACCE13__INCLUDED_)
#define AFX_PUMPCONFIGDATA_H__3099EAFC_48FD_462B_9D09_75B414ACCE13__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "RowObjectFace.h"

class AFX_EXT_CLASS PumpConfigData  
{
public:
	void InitObject();
	RowObject& GetObject();
	CString InitData(CString strData);
	PumpConfigData();
	virtual ~PumpConfigData();
public:
	CString Name();
	void Name(CString strValue);
	CString RPM();
	void RPM(CString strValue);
	StrArray<2> ImpellerDia();
	void ImpellerDia(const StrArray<2>& strValue);
	CString MaxFlow();
	void MaxFlow(CString strValue);
	StrArray<7> Curve1();
	void Curve1(const StrArray<7>& strValue);
	CString ID();
	void ID(CString strValue);
	StrArray<7> Curve2();
	void Curve2(const StrArray<7>& strValue);
	CString Affiniity();
	void Affiniity(CString strValue);
	StrArray<7> Curve3();
	void Curve3(const StrArray<7>& strValue);
	StrArray<3> CurveEndFlow();
	void CurveEndFlow(const StrArray<3>& strValue);
	StrArray<2> BEP();
	void BEP(const StrArray<2>& strValue);
private:
	RowObject m_Object;
	RowObjectFace<1>	m_Name;					//�ýṹ��������
	RowObjectFace<1>	m_RPM;					//�õ�RPMֵ
	RowObjectFace<2>	m_ImpellerDia;			//�õ�Ҷ��ֱ��\��λ
	RowObjectFace<1>	m_MaxFlow;				//�ýṹ��ͼ�ε�X�����ֵ
	VariableFace<7,1>   m_Curve1;				//H-Q�������ͣ�1��ѹ����ʧ����ʽ��2��ѹ����ʧ�ڲ�ֵ��
												//��ʽ�в����ͳ����ĸ���
												//��ʽ�еĲ����ͳ���a��b��c��d��e��ֵ
	RowObjectFace<1>	m_ID;					//��ǣ�RDS+Num����[RAW DATA SETS]��[RAW DATA REFERENCES]�еı��ID
	VariableFace<7,1>	m_Curve2;				//HNPSHR�������ͣ�1��ѹ����ʧ����ʽ��2��ѹ����ʧ�ڲ�ֵ��
												//��ʽ�в����ͳ����ĸ���
												//��ʽ�еĲ����ͳ���a��b��c��d��e��ֵ
	RowObjectFace<1>	m_Affiniity ;			//NPSHR Affiniity Exponent At Operating Speed ��Kֵ
	RowObjectFace<1>	m_UnKown;				//-9999
	VariableFace<7,1>	m_Curve3;				//BEP�������ͣ�1��ѹ����ʧ����ʽ��2��ѹ����ʧ�ڲ�ֵ��
												//��ʽ�в����ͳ����ĸ���
												//��ʽ�еĲ����ͳ���a��b��c��d��e��ֵ
	RowObjectFace<3>	m_CurveEndFlow;			//�������ͣ�0�����������1������������\����ֵ\��λ
	RowObjectFace<2>	m_BEP;					//��ѹ�Ч��BEP��ֵ\��λ
};
inline RowObject& PumpConfigData::GetObject()
{
	return m_Object;
}


#endif // !defined(AFX_PUMPCONFIGDATA_H__3099EAFC_48FD_462B_9D09_75B414ACCE13__INCLUDED_)

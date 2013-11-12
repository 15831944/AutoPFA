// onfigItemPerisist.h: interface for the ConfigItemPerisist class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ONFIGITEMPERISIST_H__262439FB_E49F_484B_ABFB_422882510F26__INCLUDED_)
#define AFX_ONFIGITEMPERISIST_H__262439FB_E49F_484B_ABFB_422882510F26__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "TwoDTablePersistent.h"


class AFX_EXT_CLASS ConfigItemPerisist  
{
public:
	ConfigItemPerisist();
	virtual ~ConfigItemPerisist();
    ConfigItemPerisist(const ConfigItemPerisist &ref);
	ConfigItemPerisist& operator=(const ConfigItemPerisist &ref);
public:
	CString Name();
	void Name(CString strValue);
	CString RPM();
	void RPM(CString strValue);
	StrArray<2>& ImpellerDia();
	void ImpellerDia(const StrArray<2>& strValue);
	CString MaxFlow();
	void MaxFlow(CString strValue);
	StrArray<7>& Curve1();
	void Curve1(const StrArray<7>& strValue);
	CString ID();
	void ID(CString strValue);
	StrArray<7>& Curve2();
	void Curve2(const StrArray<7>& strValue);
	CString Affiniity();
	void Affiniity(CString strValue);
	StrArray<7>& Curve3();
	void Curve3(const StrArray<7>& strValue);
	StrArray<3>& CurveEndFlow();
	void CurveEndFlow(const StrArray<3>& strValue);
	StrArray<2>& BEP();
	void BEP(const StrArray<2>& strValue);
public:
	RawDataPersistent m_RawData;
private:
	CString		 m_Name;				//�ýṹ��������
	CString		 m_RPM;					//�õ�RPMֵ
	StrArray<2>  m_ImpellerDia;			//�õ�Ҷ��ֱ��\��λ
	CString		 m_MaxFlow;				//�ýṹ��ͼ�ε�X�����ֵ
	StrArray<7>  m_Curve1;				//H-Q�������ͣ�1��ѹ����ʧ����ʽ��2��ѹ����ʧ�ڲ�ֵ��
										//��ʽ�в����ͳ����ĸ���
										//��ʽ�еĲ����ͳ���a��b��c��d��e��ֵ
	CString		 m_ID;					//��ǣ�RDS+Num����[RAW DATA SETS]��[RAW DATA REFERENCES]�еı��ID
	StrArray<7>  m_Curve2;				//HNPSHR�������ͣ�1��ѹ����ʧ����ʽ��2��ѹ����ʧ�ڲ�ֵ��
										//��ʽ�в����ͳ����ĸ���
										//��ʽ�еĲ����ͳ���a��b��c��d��e��ֵ
	CString		 m_Affiniity ;			//NPSHR Affiniity Exponent At Operating Speed ��Kֵ
	StrArray<7>  m_Curve3;				//BEP�������ͣ�1��ѹ����ʧ����ʽ��2��ѹ����ʧ�ڲ�ֵ��
										//��ʽ�в����ͳ����ĸ���
										//��ʽ�еĲ����ͳ���a��b��c��d��e��ֵ
	StrArray<3>  m_CurveEndFlow;		//�������ͣ�0�����������1������������\����ֵ\��λ
	StrArray<2>  m_BEP;					//��ѹ�Ч��BEP��ֵ\��λ

};

/*------------------------------------------*/
inline CString ConfigItemPerisist::Name()
{
	return m_Name;
}
inline void ConfigItemPerisist::Name(CString strValue)
{
	m_Name = strValue;
}
/*------------------------------------------*/
inline CString ConfigItemPerisist::RPM()
{
	return m_RPM;
}
inline void ConfigItemPerisist::RPM(CString strValue)
{
	m_RPM = strValue;
}
/*------------------------------------------*/
inline StrArray<2>& ConfigItemPerisist::ImpellerDia()
{
	return m_ImpellerDia;
}
inline void ConfigItemPerisist::ImpellerDia(const StrArray<2>& strValue)
{
	m_ImpellerDia = strValue;
}
/*------------------------------------------*/
inline CString ConfigItemPerisist::MaxFlow()
{
	return m_MaxFlow;
}
inline void ConfigItemPerisist::MaxFlow(CString strValue)
{
	m_MaxFlow = strValue;
}
/*------------------------------------------*/
inline StrArray<7>& ConfigItemPerisist::Curve1()
{
	return m_Curve1;
}
inline void ConfigItemPerisist::Curve1(const StrArray<7>& strValue)
{
	m_Curve1 = strValue;
}
/*------------------------------------------*/
inline CString ConfigItemPerisist::ID()
{
	return m_ID;
}
inline void ConfigItemPerisist::ID(CString strValue)
{
	m_ID = strValue;
}
/*------------------------------------------*/
inline StrArray<7>& ConfigItemPerisist::Curve2()
{
	return m_Curve2;
}
inline void ConfigItemPerisist::Curve2(const StrArray<7>& strValue)
{
	m_Curve2 = strValue;
}
/*------------------------------------------*/
inline CString ConfigItemPerisist::Affiniity()
{
	return m_Affiniity;
}
inline void ConfigItemPerisist::Affiniity(CString strValue)
{
	m_Affiniity = strValue;
}
/*------------------------------------------*/
inline StrArray<7>& ConfigItemPerisist::Curve3()
{
	return m_Curve3;
}
inline void ConfigItemPerisist::Curve3(const StrArray<7>& strValue)
{
	m_Curve3 = strValue;
}
/*------------------------------------------*/
inline StrArray<3>& ConfigItemPerisist::CurveEndFlow()
{
	return m_CurveEndFlow;
}
inline void ConfigItemPerisist::CurveEndFlow(const StrArray<3>& strValue)
{
	m_CurveEndFlow = strValue;
}

/*------------------------------------------*/
inline StrArray<2>& ConfigItemPerisist::BEP()
{
	return m_BEP;
}
inline void ConfigItemPerisist::BEP(const StrArray<2>& strValue)
{
	m_BEP = strValue;
}

#endif // !defined(AFX_ONFIGITEMPERISIST_H__262439FB_E49F_484B_ABFB_422882510F26__INCLUDED_)

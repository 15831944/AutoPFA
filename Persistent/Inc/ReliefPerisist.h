// ReliefPerisist.h: interface for the ReliefPerisist class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RELIEFPERISIST_H__44C20EB4_803F_4410_B99B_5513C87A03ED__INCLUDED_)
#define AFX_RELIEFPERISIST_H__44C20EB4_803F_4410_B99B_5513C87A03ED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Junperisist.h"
#include "TransDataPersistent.h"

class AFX_EXT_CLASS ReliefPerisist : public Junperisist  
{
public:
	static Junperisist* CreatRelief();
	ReliefPerisist();
	virtual ~ReliefPerisist();
	
public:
	CString Type();
	void Type(CString strValue);
	StrArray<13>& Curve();
	void Curve(const StrArray<13>& strValue);
	StrArray<5>& CrackExitPress();
	void CrackExitPress(const StrArray<5>& strValue);
	CString KOrCv();
	void KOrCv(CString strValue);
	StrArray<3>& BasisArea();
	void BasisArea(const StrArray<3>& strValue);
private:
	CString		m_Type;							//����(1:�ڲ���ȫ����internal relief��2:���ڰ�ȫ����exit relief��3:��Ƕ��ȫ����inline relief��)
    StrArray<13>m_Curve;						//��ʧģ�����ߡ�
	StrArray<5> m_CrackExitPress;				//ѹ��/ˮͷ����0������ˮͷ1������ѹ��2��ˮͷ��3��ѹ����
												//����ѹ��\��λ
												//����ѹ��\��λ
	CString		m_KOrCv;						//K��Cvϵ��ֵ
	StrArray<3> m_BasisArea;					//��ʧģ�͵��������0��Ĭ�����ιܵ������1�����ιܵ����2���û�ָ�����3���û�ָ��ֱ��
												//ֵ/��λ
public:
	TransDataPersistent m_TransPersistent;
};
/*------------------------------------------*/
inline CString ReliefPerisist::Type()
{
	return m_Type;
}
inline void ReliefPerisist::Type(CString strValue)
{
	m_Type = strValue;
}
/*------------------------------------------*/
inline StrArray<13>& ReliefPerisist::Curve()
{
	return m_Curve;
}
inline void ReliefPerisist::Curve(const StrArray<13>& strValue)
{
	m_Curve = strValue;
}
/*------------------------------------------*/
inline StrArray<5>& ReliefPerisist::CrackExitPress()
{
	return m_CrackExitPress;
}
inline void ReliefPerisist::CrackExitPress(const StrArray<5>& strValue)
{
	m_CrackExitPress = strValue;
}

/*------------------------------------------*/
inline CString ReliefPerisist::KOrCv()
{
	return m_KOrCv;
}
inline void ReliefPerisist::KOrCv(CString strValue)
{
	m_KOrCv = strValue;
}
/*------------------------------------------*/
inline StrArray<3>& ReliefPerisist::BasisArea()
{
	return m_BasisArea;
}
inline void ReliefPerisist::BasisArea(const StrArray<3>& strValue)
{
	m_BasisArea = strValue;
}
#endif // !defined(AFX_RELIEFPERISIST_H__44C20EB4_803F_4410_B99B_5513C87A03ED__INCLUDED_)

// BreakerPerisist.h: interface for the BreakerPerisist class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BREAKERPERISIST_H__81D90514_DCCB_4461_B123_F660C753AF7F__INCLUDED_)
#define AFX_BREAKERPERISIST_H__81D90514_DCCB_4461_B123_F660C753AF7F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Junperisist.h"

class AFX_EXT_CLASS BreakerPerisist : public Junperisist  
{
public:
	static Junperisist* CreatBreaker();
	BreakerPerisist();
	virtual ~BreakerPerisist();
public:
	StrArray<3>& CrackPress();
	void CrackPress(const StrArray<3>& strValue);
	StrArray<2>& OrificeInCdA();
	void OrificeInCdA(const StrArray<2>& strValue);
	StrArray<2>& OrificeOutCdA();
	void OrificeOutCdA(const StrArray<2>& strValue);
	StrArray<3>& LiquidTemp();
	void LiquidTemp(const StrArray<3>& strValue);
	StrArray<9>& GasProperty();
	void GasProperty(const StrArray<9>& strValue);
	CString ConnectPipe();
	void ConnectPipe(CString strValue);
	CString ValveType();
	void ValveType(CString strValue);
	StrArray<2>& InterMediateCdA();
	void InterMediateCdA(const StrArray<2>& strValue);
	StrArray<3>& MediateActivation();
	void MediateActivation(const StrArray<3>& strValue);

private:
	StrArray<3>		m_CrackPress;				 //���ѵ�ѹ������0��ˮͷ��1��ѹ��/ѹ��ֵ/ѹ����λ
	StrArray<2>     m_OrificeInCdA;				 //�׿�ȫ�����������ֵ/��λ
	StrArray<2>     m_OrificeOutCdA;			 //�������ֵ/��λ
	StrArray<3>		m_LiquidTemp;				 //�����¶�ѡ��0��ϵͳ����1���û�ָ���¶�/�¶�ֵ/��λ
	StrArray<9>		m_GasProperty;				 //��������0������1����������/������/Cp/Cv/�����¶�/����ѹ��/�ڲ���ʼ��������������/��λ
	CString			m_ConnectPipe;				 //���ӹܵ���0�������ܵ�1��һ���ܵ�
	CString			m_ValveType;			     //��������
	StrArray<2>     m_InterMediateCdA;			 //�׿�ȫ����ý���������ֵ/��λ
	StrArray<3>		m_MediateActivation;		 //ý��׿ڼ����׼0��ѹ����ͬ1�����ٲ�ͬ/��׼ֵ/׼ֵ�ĵ�λ

};

/*------------------------------------------*/
inline StrArray<3>& BreakerPerisist::CrackPress()
{
	return m_CrackPress;
}
inline void BreakerPerisist::CrackPress(const StrArray<3>& strValue)
{
	m_CrackPress = strValue;
}
/*------------------------------------------*/
inline StrArray<2>& BreakerPerisist::OrificeInCdA()
{
	return m_OrificeInCdA;
}
inline void BreakerPerisist::OrificeInCdA(const StrArray<2>& strValue)
{
	m_OrificeInCdA = strValue;
}
/*------------------------------------------*/
inline StrArray<2>& BreakerPerisist::OrificeOutCdA()
{
	return m_OrificeOutCdA;
}
inline void BreakerPerisist::OrificeOutCdA(const StrArray<2>& strValue)
{
	m_OrificeOutCdA = strValue;
}
/*------------------------------------------*/
inline StrArray<3>& BreakerPerisist::LiquidTemp()
{
	return m_LiquidTemp;
}
inline void BreakerPerisist::LiquidTemp(const StrArray<3>& strValue)
{
	m_LiquidTemp = strValue;
}
/*------------------------------------------*/
inline StrArray<9>& BreakerPerisist::GasProperty()
{
	return m_GasProperty;
}
inline void BreakerPerisist::GasProperty(const StrArray<9>& strValue)
{
	m_GasProperty = strValue;
}
/*------------------------------------------*/
inline CString BreakerPerisist::ConnectPipe()
{
	return m_ConnectPipe;
}
inline void BreakerPerisist::ConnectPipe(CString strValue)
{
	m_ConnectPipe = strValue;
}
/*------------------------------------------*/
inline CString BreakerPerisist::ValveType()
{
	return m_ValveType;
}
inline void BreakerPerisist::ValveType(CString strValue)
{
	m_ValveType = strValue;
}
/*------------------------------------------*/
inline StrArray<2>& BreakerPerisist::InterMediateCdA()
{
	return m_InterMediateCdA;
}
inline void BreakerPerisist::InterMediateCdA(const StrArray<2>& strValue)
{
	m_InterMediateCdA = strValue;
}
/*------------------------------------------*/
inline StrArray<3>& BreakerPerisist::MediateActivation()
{
	return m_MediateActivation;
}
inline void BreakerPerisist::MediateActivation(const StrArray<3>& strValue)
{
	m_MediateActivation = strValue;
}
#endif // !defined(AFX_BREAKERPERISIST_H__81D90514_DCCB_4461_B123_F660C753AF7F__INCLUDED_)

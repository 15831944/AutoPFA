// ValvePerisist.h: interface for the ValvePerisist class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VALVEPERISIST_H__EF0383F6_54E6_4192_BFC8_E0830A299C27__INCLUDED_)
#define AFX_VALVEPERISIST_H__EF0383F6_54E6_4192_BFC8_E0830A299C27__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Junperisist.h"
#include "TransDataPersistent.h"

 class AFX_EXT_CLASS ValvePerisist : public Junperisist  
{
public:
	static Junperisist* CreatValve();
	ValvePerisist();
	virtual ~ValvePerisist();
public:
	CString Type();
	void Type(CString strValue);
	StrArray<13>& Curve();
	void Curve(const StrArray<13>& strValue);
	StrArray<3>& ExitPress();
	void ExitPress(const StrArray<3>& strValue);
	CString KOrCv();
	void KOrCv(CString strValue);
	StrArray<3>& BasisArea();
	void BasisArea(const StrArray<3>& strValue);
private:
	CString		 m_Type;						//����(0����ͨ���ţ�-1��ѡ�з���Ϊ���ڷ���)
    StrArray<13> m_Curve;						//��ʧģ�����ߡ�
	StrArray<3>  m_ExitPress;					//����ѹ������0��ˮͷ1��ѹ��
												//����ѹ��\��λ
	CString		 m_KOrCv;						//K��Cvϵ��ֵ
	StrArray<3>  m_BasisArea;					//��ʧģ�͵��������0��Ĭ�����ιܵ������1�����ιܵ����2���û�ָ�����3���û�ָ��ֱ��
												//ֵ/��λ
public:
	TransDataPersistent m_TransPersistent;
};
/*------------------------------------------*/
inline CString ValvePerisist::Type()
{
	return m_Type;
}
inline void ValvePerisist::Type(CString strValue)
{
	m_Type = strValue;
}
/*------------------------------------------*/
inline StrArray<13>& ValvePerisist::Curve()
{
	return m_Curve;
}
inline void ValvePerisist::Curve(const StrArray<13>& strValue)
{
	m_Curve = strValue;
}
/*------------------------------------------*/
inline StrArray<3>& ValvePerisist::ExitPress()
{
	return m_ExitPress;
}
inline void ValvePerisist::ExitPress(const StrArray<3>& strValue)
{
	m_ExitPress = strValue;
}

/*------------------------------------------*/
inline CString ValvePerisist::KOrCv()
{
	return m_KOrCv;
}
inline void ValvePerisist::KOrCv(CString strValue)
{
	m_KOrCv = strValue;
}
/*------------------------------------------*/
inline StrArray<3>& ValvePerisist::BasisArea()
{
	return m_BasisArea;
}
inline void ValvePerisist::BasisArea(const StrArray<3>& strValue)
{
	m_BasisArea = strValue;
}
#endif // !defined(AFX_VALVEPERISIST_H__EF0383F6_54E6_4192_BFC8_E0830A299C27__INCLUDED_)

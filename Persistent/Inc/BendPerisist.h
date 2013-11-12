// BendPerisist.h: interface for the BendPerisist class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BENDPERISIST_H__364BC445_D448_4601_BCD0_DF25DA5EF156__INCLUDED_)
#define AFX_BENDPERISIST_H__364BC445_D448_4601_BCD0_DF25DA5EF156__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Junperisist.h"

class AFX_EXT_CLASS BendPerisist : public Junperisist  
{
public:
	static Junperisist* CreatBend();
	BendPerisist();
	virtual ~BendPerisist();
public:
	CString Type();
	void Type(CString strValue);
	CString Angle();
	void Angle(CString strValue);
	CString RD();
	void RD(CString strValue);
	CString K();
	void K(CString strValue);
	StrArray<2>& RestriFlowArea();
	void RestriFlowArea(const StrArray<2>& strValue);
	StrArray<3>& BasisArea();
	void BasisArea(const StrArray<3>& strValue);
private:
	CString m_bendType;				//��ͷ���ͣ�0��Ϊ�⻬��ͷ��1Ϊ��׼��ͷ��2ΪMitre Bend,3,Ϊ�û�ָ����
    CString m_angle;				//�Ƕȣ�Ϊ���ٶȣ�
	CString m_rD;					//r/D
	CString m_K;					//������ʧ��K��
    StrArray<2> m_RestriFlowArea;	//��ȷ���������Restricted Flow Area)�����ֺ͵�λ
	StrArray<3> m_BasisArea;		//��ʧģ�͵��������0��Ĭ�����ιܵ������1�����ιܵ����2���û�ָ�����3���û�ָ��ֱ��

};
/*------------------------------------------*/
inline CString BendPerisist::Type()
{
	return m_bendType;
}
inline void BendPerisist::Type(CString strValue)
{
	m_bendType = strValue;
}
/*------------------------------------------*/
inline CString BendPerisist::Angle()
{
	return m_angle;
}
inline void BendPerisist::Angle(CString strValue)
{
	m_angle = strValue;
}
/*------------------------------------------*/
inline CString BendPerisist::RD()
{
	return m_rD;
}
inline void BendPerisist::RD(CString strValue)
{
	m_rD = strValue;
}
/*------------------------------------------*/
inline CString BendPerisist::K()
{
	return m_K;
}
inline void BendPerisist::K(CString strValue)
{
	m_K = strValue;
}
/*------------------------------------------*/
inline StrArray<2>& BendPerisist::RestriFlowArea()
{
	return m_RestriFlowArea;
}
inline void BendPerisist::RestriFlowArea(const StrArray<2>& strValue)
{
	m_RestriFlowArea = strValue;
}
/*------------------------------------------*/
inline StrArray<3>& BendPerisist::BasisArea()
{
	return m_BasisArea;
}
inline void BendPerisist::BasisArea(const StrArray<3>& strValue)
{
	m_BasisArea = strValue;
}

#endif // !defined(AFX_BENDPERISIST_H__364BC445_D448_4601_BCD0_DF25DA5EF156__INCLUDED_)

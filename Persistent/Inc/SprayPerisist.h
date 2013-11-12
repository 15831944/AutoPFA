// SprayPerisist.h: interface for the SprayPerisist class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPRAYPERISIST_H__10D63E3D_B858_49F9_AA02_E8367845B6B7__INCLUDED_)
#define AFX_SPRAYPERISIST_H__10D63E3D_B858_49F9_AA02_E8367845B6B7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Junperisist.h"
#include "TransDataPersistent.h"

class AFX_EXT_CLASS SprayPerisist : public Junperisist  
{
public:
	static Junperisist* CreatSpray();
	SprayPerisist();
	virtual ~SprayPerisist();
public:
	CString Type();
	void Type(CString strValue);
	StrArray<13>& Curve();
	void Curve(const StrArray<13>& strValue);
	StrArray<3>& ExitArea();
	void ExitArea(const StrArray<3>& strValue);
	CString KOrCv();
	void KOrCv(CString strValue);
	StrArray<3>& ExitPress();
	void ExitPress(const StrArray<3>& strValue);
	//6.0�¹ܵ��������Kϵ������������Ϣ
	ListImp<StrArray<4> >& PipeInfo();
	ListImp<StrArray<4> >& PipeInfoToStd();
	void PipeInfo(const ListImp<StrArray<4> >& strValue,int nCount);
	void PipeInfo(const ListImp<StrArray<4> >& strValue);
	CString DistanceUnit();
void DistanceUnit(CString strValue);
private:
	CString		m_Type;							//Spray����0������ܿ�1������
    StrArray<13>m_Curve;						//��ʧģ�����ߡ�
	StrArray<3> m_ExitArea;						//�����ڵ����\�����λ\����
	CString		m_KOrCv;						//K��Cvϵ��ֵ
	StrArray<3> m_ExitPress;					//����ѹ������0��ˮͷ1��ѹ��
												//����ѹ��\��λ

	TablePerisist<4> m_PipeInfo;             	//6.0�¹ܵ��������Kϵ������������Ϣ
	CString			 m_DistanceUnit;			//�ܵ��˿���ڵ��߾��뵥λ
	
public:
	TransDataPersistent m_TransPersistent;
	
};
/*6.0�¹ܵ��������Kϵ������������Ϣ*/
inline ListImp<StrArray<4> >& SprayPerisist::PipeInfo()
{
	return m_PipeInfo.GetData();
}
inline void SprayPerisist::PipeInfo(const ListImp<StrArray<4> >& strValue,int nCount)
{
	m_PipeInfo.SetData(strValue,nCount);
}
inline void SprayPerisist::PipeInfo(const ListImp<StrArray<4> >& strValue)
{
	m_PipeInfo.SetData(strValue);
}
/*6.0�¹ܵ��������Kϵ������������Ϣ*/
inline CString SprayPerisist::DistanceUnit()
{
	return m_DistanceUnit;
}
inline void SprayPerisist::DistanceUnit(CString strValue)
{
	m_DistanceUnit = strValue;
}

/*------------------------------------------*/
inline CString SprayPerisist::Type()
{
	return m_Type;
}
inline void SprayPerisist::Type(CString strValue)
{
	m_Type = strValue;
}
/*------------------------------------------*/
inline StrArray<13>& SprayPerisist::Curve()
{
	return m_Curve;
}
inline void SprayPerisist::Curve(const StrArray<13>& strValue)
{
	m_Curve = strValue;
}
/*------------------------------------------*/
inline StrArray<3>& SprayPerisist::ExitArea()
{
	return m_ExitArea;
}
inline void SprayPerisist::ExitArea(const StrArray<3>& strValue)
{
	m_ExitArea = strValue;
}

/*------------------------------------------*/
inline CString SprayPerisist::KOrCv()
{
	return m_KOrCv;
}
inline void SprayPerisist::KOrCv(CString strValue)
{
	m_KOrCv = strValue;
}
/*------------------------------------------*/
inline StrArray<3>& SprayPerisist::ExitPress()
{
	return m_ExitPress;
}
inline void SprayPerisist::ExitPress(const StrArray<3>& strValue)
{
	m_ExitPress = strValue;
}
#endif // !defined(AFX_SPRAYPERISIST_H__10D63E3D_B858_49F9_AA02_E8367845B6B7__INCLUDED_)

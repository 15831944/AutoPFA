// SurgePerisist.h: interface for the SurgePerisist class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SURGEPERISIST_H__32A2B74F_3B0F_47C7_9E53_BCA03BA39F9A__INCLUDED_)
#define AFX_SURGEPERISIST_H__32A2B74F_3B0F_47C7_9E53_BCA03BA39F9A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Junperisist.h"
#include "TransDataPersistent.h"

class AFX_EXT_CLASS SurgePerisist : public Junperisist  
{
public:
	static Junperisist* CreatSurge();
	SurgePerisist();
	virtual ~SurgePerisist();

public:
	ListImp<StrArray<4> >& PipeInfoToStd();
    ListImp<StrArray<4> >& PipeInfo();
	void PipeInfo(const ListImp<StrArray<4> >& strValue,int nCount);
	void PipeInfo(const ListImp<StrArray<4> >& strValue);
	CString DistanceUnit();
	void DistanceUnit(CString strValue);
	StrArray<2>& SurgeHeight();
	void SurgeHeight(const StrArray<2>& strValue);
	StrArray<2>& ConstArea();
	void ConstArea(const StrArray<2>& strValue);
	StrArray<2>& SurfacePress();
	void SurfacePress(const StrArray<2>& strValue);
	StrArray<5>& Orifice();
	void Orifice(const StrArray<5>& strValue);
	StrArray<10>& ShortPipe();
	void ShortPipe(const StrArray<10>& strValue);
	CString OneWay();
	void OneWay(CString strValue);
	StrArray<4>& Vessel();
	void Vessel(const StrArray<4>& strValue);
	CString Variable();
	void Variable(CString strValue);
	void VariableArea(const ListImp<StrArray<2> >& strValue);
	StrArray<3>& InitSurfaceH();
	void InitSurfaceH(const StrArray<3>& strValue);
	StrArray<5>& Check();
	void Check(const StrArray<5>& strValue);
private:
	TablePerisist<4> m_PipeInfo;
	CString			 m_DistanceUnit;
	StrArray<2>		 m_SurgeHeight;					//��ѹ���ĸ߶�\��λ
	StrArray<2>		 m_ConstArea;					//�����ֵ\��λ
	StrArray<2>		 m_SurfacePress;				//����ѹ��\��λ
	StrArray<5>		 m_Orifice;						//ѡ�н����װ�ģ�ͱ��\������ϵ��\������ϵ��\���ֵ\��λ
	StrArray<10>	 m_ShortPipe;					//0��û��ѡ��̹ܵ�ģ�ͣ�-1��ѡ��̹ܵ�ģ��
													//�̹ܵ�Ħ��ϵ��
													//�̹ܵ���ֱ��\��λ
													//�̹ܵ����\��λ
													//�̹ܵ�����\��λ
													//�̹ܵ���߱仯\��λ
	CString			 m_OneWay;						//��One-Way Surge Tank��0��û��ѡ��-1ѡ������ģ��ֹ�ط������Ļ���ޡ�
	StrArray<4>		 m_Vessel;						//ģ���������0��û��ѡ��-1��ѡ��
													//������ܵ��ܵ��ĸ߶�\��λ
													//���ĳ���
	CString			 m_Variable;					//��ǣ�ѡ������㶨0������仯1
	//TwoDTablePersistent m_AreaTable
	StrArray<3>		 m_InitSurfaceH;				//�ȶ�״̬��ʼ������߶�0��û��ѡ��-1��ѡ��
													//�߶�ֵ\��λ
	StrArray<5>		 m_CheckValve;					//ֹ�ط�����ϵ��
													//ֹ�ط���ʼλ��0����1���ر�
													//�򿪷���Deltaѹ����ˮͷ��ѹ������0��ˮͷ1��ѹ��
													//ѹ��ֵ\��λ
public:
	TwoDTablePersistent m_AreaTable;
	TransDataPersistent m_TransPersistent;
};
/*------------------------------------------*/
inline ListImp<StrArray<4> >& SurgePerisist::PipeInfo()
{
	return m_PipeInfo.GetData();
}
inline void SurgePerisist::PipeInfo(const ListImp<StrArray<4> >& strValue,int nCount)
{
	m_PipeInfo.SetData(strValue,nCount);
}
inline void SurgePerisist::PipeInfo(const ListImp<StrArray<4> >& strValue)
{
	m_PipeInfo.SetData(strValue);
}
/*------------------------------------------*/
inline CString SurgePerisist::DistanceUnit()
{
	return m_DistanceUnit;
}
inline void SurgePerisist::DistanceUnit(CString strValue)
{
	m_DistanceUnit = strValue;
}
/*------------------------------------------*/
inline StrArray<2>& SurgePerisist::SurgeHeight()
{
	return m_SurgeHeight;
}
inline void SurgePerisist::SurgeHeight(const StrArray<2>& strValue)
{
	m_SurgeHeight = strValue;
}
/*------------------------------------------*/
inline StrArray<2>& SurgePerisist::ConstArea()
{
	return m_ConstArea;
}
inline void SurgePerisist::ConstArea(const StrArray<2>& strValue)
{
	m_ConstArea = strValue;
}
/*------------------------------------------*/
inline StrArray<2>& SurgePerisist::SurfacePress()
{
	return m_SurfacePress;
}
inline void SurgePerisist::SurfacePress(const StrArray<2>& strValue)
{
	m_SurfacePress = strValue;
}
/*------------------------------------------*/
inline StrArray<5>& SurgePerisist::Orifice()
{
	return m_Orifice;
}
inline void SurgePerisist::Orifice(const StrArray<5>& strValue)
{
	m_Orifice = strValue;
}
/*------------------------------------------*/
inline StrArray<10>& SurgePerisist::ShortPipe()
{
	return m_ShortPipe;
}
inline void SurgePerisist::ShortPipe(const StrArray<10>& strValue)
{
	m_ShortPipe = strValue;
}
/*------------------------------------------*/
inline CString SurgePerisist::OneWay()
{
	return m_OneWay;
}
inline void SurgePerisist::OneWay(CString strValue)
{
	m_OneWay = strValue;
}
/*------------------------------------------*/
inline StrArray<4>& SurgePerisist::Vessel()
{
	return m_Vessel;
}
inline void SurgePerisist::Vessel(const StrArray<4>& strValue)
{
	m_Vessel = strValue;
}

/*------------------------------------------*/
inline CString SurgePerisist::Variable()
{
	return m_Variable;
}
inline void SurgePerisist::Variable(CString strValue)
{
	m_Variable = strValue;
}

/*------------------------------------------*/
inline StrArray<3>& SurgePerisist::InitSurfaceH()
{
	return m_InitSurfaceH;
}
inline void SurgePerisist::InitSurfaceH(const StrArray<3>& strValue)
{
	m_InitSurfaceH = strValue;
}
/*------------------------------------------*/
inline StrArray<5>& SurgePerisist::Check()
{
	return m_CheckValve;
}
inline void SurgePerisist::Check(const StrArray<5>& strValue)
{
	m_CheckValve = strValue;
}

#endif // !defined(AFX_SURGEPERISIST_H__32A2B74F_3B0F_47C7_9E53_BCA03BA39F9A__INCLUDED_)

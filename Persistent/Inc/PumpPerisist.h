// PumpPerisist.h: interface for the PumpPerisist class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PUMPPERISIST_H__C691AFF8_E3D7_45A0_9C42_136047A0EBAD__INCLUDED_)
#define AFX_PUMPPERISIST_H__C691AFF8_E3D7_45A0_9C42_136047A0EBAD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Junperisist.h"
#include "TransDataPersistent.h"
#include "onfigPerisist.h"

class AFX_EXT_CLASS PumpPerisist : public Junperisist  
{
public:
	static Junperisist* CreatPump();
	PumpPerisist();
	virtual ~PumpPerisist();
public:
	CString PumpType();
	void PumpType(CString strValue);
	StrArray<3>& PumpFlow();
	void PumpFlow(const StrArray<3>& strValue);
	CString SpeedRatio();
	void SpeedRatio(CString strValue);
	StrArray<4>& PumpControl();
	void PumpControl(const StrArray<4>& strValue);
	CString ControlApply();
	void ControlApply(CString strValue);
	CString PressType();
	void PressType(CString strValue);
	StrArray<4>& SubmergePump();
	void SubmergePump(const StrArray<4>& strValue);
	CString ExitCheck();
	void ExitCheck(CString strValue);
	StrArray<2>& CloseVel();
	void CloseVel(const StrArray<2>& strValue);
	CString AntiReverse();
	void AntiReverse(CString strValue);
	StrArray<3>& ReOpenPress();
	void ReOpenPress(const StrArray<3>& strValue);
	CString PumpSet();
	void PumpSet(CString strValue);
private:
	CString		m_PumpType;				//��ģ�͵�����0�������ߣ�1��ָ���������2��ָ����������
	StrArray<3>	m_PumpFlow;				//��������\������С\��λ
	CString		m_SpeedRatio;			//���ٱõ�������Ա����ߵ����ʣ�1����ʾ100%��
	StrArray<4>	m_PumpControl;			//���Ʊ����ͣ�0��û�п��ƣ�1�������ѹ��/ˮͷ���ƣ�3�������ѹ��/ˮͷ���ƣ�2����������
										//���Ƶ��������0��ˮͷ/ˮͷ��ʧ/�������1��ѹ��/ѹ����ʧ/��������
										//���Ƶ����ֵ
										//���Ƶ������λ
	CString		m_ControlApply;         //���ƶ�Ӧ��������ã�0�����ǿ���1��ѹ��������������2��ѹ�����ڿ������ã�
	CString		m_PressType;			//0��ͣ��ѹ��1����̬ѹ��
	StrArray<4>	m_SubmergePump;         //0��Ǳˮ��û��ѡ��-1��Ǳˮ��ѡ��
										//ѹ��������0��ˮͷ1��ѹ��
										//�����ѹ��ֵ
										//�����ѹ����λ
	CString		m_ExitCheck;			//-1��ѡ�����ֹ�ط���0��û��ѡ�����ֹ�ط�
	StrArray<2>	m_CloseVel;		        //�رշ��ŵ���С�ٶ�\�ٶȵ�λ
	CString		m_antiReverse;			//-1��û��ѡ�����Ʊ÷�ת��0ѡ�����Ʊ÷�ת
	StrArray<3>	m_ReOpenPress;			//���´򿪷���Delta(ѹ����ˮͷ)0��ˮͷ1��ѹ��\ѹ��ֵ\��λ
	CString     m_PumpSet;				//�û��飬�����ã��õ������������ã�����+�õ�����,0:����
public:
	ConfigPerisist m_ConfigPerisist;
	TransDataPersistent m_TransPersistent;

};

/*------------------------------------------*/
inline CString PumpPerisist::PumpType()
{
	return m_PumpType;
}
inline void PumpPerisist::PumpType(CString strValue)
{
	m_PumpType = strValue;
}
/*------------------------------------------*/
inline StrArray<3>& PumpPerisist::PumpFlow()
{
	return m_PumpFlow;
}
inline void PumpPerisist::PumpFlow(const StrArray<3>& strValue)
{
	m_PumpFlow = strValue;
}
/*------------------------------------------*/
inline CString PumpPerisist::SpeedRatio()
{
	return m_SpeedRatio;
}
inline void PumpPerisist::SpeedRatio(CString strValue)
{
	m_SpeedRatio = strValue;
}
/*------------------------------------------*/
inline StrArray<4>& PumpPerisist::PumpControl()
{
	return m_PumpControl;
}
inline void PumpPerisist::PumpControl(const StrArray<4>& strValue)
{
	m_PumpControl = strValue;
}
/*------------------------------------------*/
inline CString PumpPerisist::ControlApply()
{
	return m_ControlApply;
}
inline void PumpPerisist::ControlApply(CString strValue)
{
	m_ControlApply = strValue;
}
/*------------------------------------------*/
inline CString PumpPerisist::PressType()
{
	return m_PressType;
}
inline void PumpPerisist::PressType(CString strValue)
{
	m_PressType = strValue;
}
/*------------------------------------------*/
inline StrArray<4>& PumpPerisist::SubmergePump()
{
	return m_SubmergePump;
}
inline void PumpPerisist::SubmergePump(const StrArray<4>& strValue)
{
	m_SubmergePump = strValue;
}
/*------------------------------------------*/
inline CString PumpPerisist::ExitCheck()
{
	return m_ExitCheck;
}
inline void PumpPerisist::ExitCheck(CString strValue)
{
	m_ExitCheck = strValue;
}
/*------------------------------------------*/
inline StrArray<2>& PumpPerisist::CloseVel()
{
	return m_CloseVel;
}
inline void PumpPerisist::CloseVel(const StrArray<2>& strValue)
{
	m_CloseVel = strValue;
}
/*------------------------------------------*/
inline CString PumpPerisist::AntiReverse()
{
	return m_antiReverse;
}
inline void PumpPerisist::AntiReverse(CString strValue)
{
	m_antiReverse = strValue;
}
/*------------------------------------------*/
inline StrArray<3>& PumpPerisist::ReOpenPress()
{
	return m_ReOpenPress;
}
inline void PumpPerisist::ReOpenPress(const StrArray<3>& strValue)
{
	m_ReOpenPress = strValue;
}
/*------------------------------------------*/
inline CString PumpPerisist::PumpSet()
{
	return m_PumpSet;
}
inline void PumpPerisist::PumpSet(CString strValue)
{
	m_PumpSet = strValue;
}
#endif // !defined(AFX_PUMPPERISIST_H__C691AFF8_E3D7_45A0_9C42_136047A0EBAD__INCLUDED_)

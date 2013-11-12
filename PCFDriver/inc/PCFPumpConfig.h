// PCFPumpConfig.h: interface for the PCFPumpConfig class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PCFPUMPCONFIG_H__BB86F2C1_D484_4FE3_8243_7B95397A1300__INCLUDED_)
#define AFX_PCFPUMPCONFIG_H__BB86F2C1_D484_4FE3_8243_7B95397A1300__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "PCFPumpConfigData.h"
class AFX_EXT_CLASS PCFPumpConfig  
{
public:
	Iterator<PCFPumpConfigData>* CreatIterator()const;
public:
	CString PressType();
	void PressType(CString strValue);
	CString PressUnit();
	void PressUnit(CString strValue);
	CString FlowType();
	void FlowType(CString strValue);
	CString FlowUnit();
	void FlowUnit(CString strValue);
	CString PowerType();
	void PowerType(CString strValue);
	CString PowerUnit();
	void PowerUnit(CString strValue);
	CString Type();
	void Type(CString strValue);
	void Num(int nValue);
	CString InitData(CString strData);
	PCFPumpConfig();
	virtual ~PCFPumpConfig();
public:
	PCFPumpConfigData* CreatConfigData();
	RowObjectFace<1> m_PressType;			//�ýṹѹ��������0��ˮͷ1��ѹ��
	RowObjectFace<1> m_PressUnit;			//�ýṹѹ����λ
	RowObjectFace<1> m_FlowType;			//�ýṹ��������0���������1����������
	RowObjectFace<1> m_FlowUnit;			//�ýṹ������λ
	RowObjectFace<1> m_PowerType;			//Ч�ʻ��ʲ���0��Ч��1������
	RowObjectFace<1> m_PowerUnit;			//Ч�ʻ��ʲ�����λ
	RowObjectFace<1> m_Type;				//�ù��췽��0���� n��Multiple Configuations�ýṹ����ѡ��n��Ϊ��ǰ
	RowObjectFace<1> m_Num;					//�ýṹ���������(1)
	ListImp<PCFPumpConfigData> m_list;
	
	CString InitList(CString strData);
	int GetNum();
};

#endif // !defined(AFX_PCFPUMPCONFIG_H__BB86F2C1_D484_4FE3_8243_7B95397A1300__INCLUDED_)

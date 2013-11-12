// Configuration.h: interface for the Configuration class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONFIGURATION_H__E20047CF_C54D_436F_B170_373FB4F70F5F__INCLUDED_)
#define AFX_CONFIGURATION_H__E20047CF_C54D_436F_B170_373FB4F70F5F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "StrFlyWeight.h"
#include "ScenarioObject.h"
#include "onfigPerisist.h"
#include "TransDataTable.h"

class Configuration  
{
public:
	Configuration();
	virtual ~Configuration();

public:
	StrFlyWeight m_PressType;			//�ýṹѹ��������0��ˮͷ1��ѹ��
	StrFlyWeight m_PressUnit;			//�ýṹѹ����λ
	StrFlyWeight m_FlowType;			//�ýṹ��������0���������1����������
	StrFlyWeight m_FlowUnit;			//�ýṹ������λ
	StrFlyWeight m_PowerType;			//Ч�ʻ��ʲ���0��Ч��1������
	StrFlyWeight m_PowerUnit;			//Ч�ʻ��ʲ�����λ
	StrFlyWeight m_Num;

	//
	StrFlyWeight m_Name;				//�ýṹ��������
	StrFlyWeight m_RPM;					//�õ�RPMֵ
	NumFlyWeight m_ImpellerDia;			//�õ�Ҷ��ֱ��\��λ
	StrFlyWeight m_MaxFlow;				//�ýṹ��ͼ�ε�X�����ֵ
	ArrayFlyWeight<7> m_Curve1;			//H-Q�������ͣ�1��ѹ����ʧ����ʽ��2��ѹ����ʧ�ڲ�ֵ��
										//��ʽ�в����ͳ����ĸ���
										//��ʽ�еĲ����ͳ���a��b��c��d��e��ֵ
	StrFlyWeight m_ID;					//��ǣ�RDS+Num����[RAW DATA SETS]��[RAW DATA REFERENCES]�еı��ID
	TransDataTable<4> m_RawData;
	ArrayFlyWeight<7> m_Curve2;			//HNPSHR�������ͣ�1��ѹ����ʧ����ʽ��2��ѹ����ʧ�ڲ�ֵ��
										//��ʽ�в����ͳ����ĸ���
										//��ʽ�еĲ����ͳ���a��b��c��d��e��ֵ
	StrFlyWeight m_Affiniity ;			//NPSHR Affiniity Exponent At Operating Speed ��Kֵ
	ArrayFlyWeight<7> m_Curve3;			//BEP�������ͣ�1��ѹ����ʧ����ʽ��2��ѹ����ʧ�ڲ�ֵ��
										//��ʽ�в����ͳ����ĸ���
										//��ʽ�еĲ����ͳ���a��b��c��d��e��ֵ
	ArrayFlyWeight<3>  m_CurveEndFlow;	//�������ͣ�0�����������1������������\����ֵ\��λ
	NumFlyWeight  m_BEP;				//��ѹ�Ч��BEP��ֵ\��λ

	CString CreatID();
public:
	static void GetPrame(ArrayFlyWeight<7>& curve,double dPrame[]);
	CString PowerTitle();
	CString PressTitle();
	CString FlowTitle();
	
	void InitData(ScenarioObject *pObject);
	BOOL SaveData(ScenarioObject *pObject,int &num1,int &num2,int &num3);
	int Instance(NameArray &array,int nKey);
	BOOL Save(ConfigPerisist &Persistent,int num1,int num2,int num3);
	BOOL Read(ConfigPerisist &Persistent);

private:
	int m_nKey;


};

#endif // !defined(AFX_CONFIGURATION_H__E20047CF_C54D_436F_B170_373FB4F70F5F__INCLUDED_)

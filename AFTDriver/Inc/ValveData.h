// ValveData.h: interface for the ValveData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VALVEDATA_H__D7C6FCB8_DE06_43E7_ACAA_5855F859491B__INCLUDED_)
#define AFX_VALVEDATA_H__D7C6FCB8_DE06_43E7_ACAA_5855F859491B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//����
#include "Junction.h"
#include "JunTransData.h"

class AFX_EXT_CLASS ValveData : public JunctionData  
{
public:
	static JunctionData* Creator();
	ValveData();
	virtual ~ValveData();
public:
	CString Type();
	void Type(CString strValue);
	StrArray<13> Curve();
	void Curve(const StrArray<13>& strValue);
	StrArray<3> ExitPress();
	void ExitPress(const StrArray<3>& strValue);
	CString KOrCv();
	void KOrCv(CString strValue);
	StrArray<3> BasisArea();
	void BasisArea(const StrArray<3>& strValue);
private:
	void AppendArray();
	void InitExtra(CString strData);
	virtual CString GetDefaultData();
public:
	JunTransData m_TranData;	
private:
	RowObjectFace<1> m_Type;			//����(0���ڲ����ţ�-1�����ڷ���)
	VariableFace<13,7> m_Curve;			//��ʧģ��(0������ϵ��ģ�ͣ�1��Kϵ��ģ��)
										//Y������������ֱ��[]
										//Y�������λ[]
										//X������������ֱ��[]
										//X�������λ[]
										//x�����ȡֵ[]
										//��������[�������ͣ�-2��Kֵ�仯��1��ѹ����ʧ����ʽ��2��ѹ����ʧ�ڲ�ֵ��]
										//��ʽ�в����ͳ����ĸ���[]
										//��ʽ�еĲ����ͳ���a��b��c��d��e��ֵ[]
	RowObjectFace<3> m_ExitPress;		//����ѹ������0��ˮͷ1��ѹ��\ѹ��ֵ\��λ
	RowObjectFace<1> m_KOrCv;			//K��Cvϵ��ֵ
	RowObjectFace<3> m_BasisArea;		//��ʧģ�͵��������0��Ĭ�����ιܵ������1�����ιܵ����2���û�ָ�����3���û�ָ��ֱ��
										//ֵ
										//��λ
	RowObjectFace<2> m_UnKown;			//1��δ֪��\0��δ֪��
	//JunTransData m_TranData;			//û�����ں���RowObjectFace<5> m_Periodic;
	RowObjectFace<1> m_UnKown3;         //0��δ֪��
	RowObjectFace<4> m_Fth2;            //������4��,����3��Ϊ4.CHANGE BY wenzk
	RowObjectFace<10> m_Fth3;

};

#endif // !defined(AFX_VALVEDATA_H__D7C6FCB8_DE06_43E7_ACAA_5855F859491B__INCLUDED_)

// JunTransData.h: interface for the JunTransData class.
/*
 * Copyright (C), 2006,��ɳ���������˾CAE������
 * All rights reserved.
 *
  �ļ����ƣ�JunTransData.h
  ժҪ��    AFT˲������
  author  : LSP          
*/
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_JUNTRANSDATA_H__04CCC98C_2A08_4E0E_968D_54ED1BCA43D9__INCLUDED_)
#define AFX_JUNTRANSDATA_H__04CCC98C_2A08_4E0E_968D_54ED1BCA43D9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "RowObjectFace.h"
#include "TableData.h"

class AFX_EXT_CLASS JunTransData  
{
public:
	RowObjectFace<3>& FourQuadrantData();
	RowObjectFace<1>& SpeedData();
	RowObjectFace<2>& RotateInertiaData();
	RowObjectFace<1>& TranModelData();
	RowObjectFace<8>& TranTriger2Data();
	RowObjectFace<8>& TranTriger1Data();
	RowObjectFace<5>& PeriodicData();
	RowObjectFace<1>& TransTypeData();
	RowObjectFace<1>& Repeat2Data();
	RowObjectFace<1>& Repeat1Data();
	RowObjectFace<1>& SpecialData();
	RowObjectFace<1>& ValueTypeData();
	JunTransData();
	virtual ~JunTransData();

public:
    CString ValueType();
	void ValueType(CString strValue);
	CString Special();
	void Special(CString strValue);
	CString Repeat1();
	void Repeat1(CString strValue);
	CString Repeat2();
	void Repeat2(CString strValue);
	CString TranType();
	void TranType(CString strValue);
	StrArray<5> Periodic();
	void Periodic(const StrArray<5>& strValue);
	StrArray<8> TranTriger1();
	void TranTriger1(const StrArray<8>& strValue);
	StrArray<8> TranTriger2();
	void TranTriger2(const StrArray<8>& strValue);
	CString TranModel();
	void TranModel(CString strValue);
	CString Speed();
	void Speed(CString strValue);
	StrArray<2> RotateInertia();
	void RotateInertia(const StrArray<2>& strValue);
	StrArray<3> FourQuadrant();
	void FourQuadrant(const StrArray<3>& strValue);

private:
	RowObjectFace<1> m_ValueType;		//1��0:����ֵ��1����Ժ㶨����ֵ
	RowObjectFace<1> m_Special;			//2��0��˲̬�ر�����ѡ�С�û�С���1��˲̬�ر�����ѡ������˲̬���ݡ�����Ծ���ڵ��ر���������2���ֱ�鿴�ر�������Ӧ�����֣�
	RowObjectFace<1> m_Repeat1;			//3��0����һ��˲���ظ�ûѡ�У�-1ѡ�У�
	RowObjectFace<1> m_Repeat2;			//4��0���ڶ���˲���ظ�ûѡ�У�-1ѡ�У�
	RowObjectFace<1> m_TranType;		//5��0:ʱ�䣬1�������¼���2�������¼�ѭ��3�����������¼�
	RowObjectFace<5> m_Periodic;		//1��0��������û��ѡ��-1������������ѡ��
										//2��0��û��ѡ��ʹ�����Һ����ľ���ֵ��-1��ѡ��ʹ�����Һ����ľ���ֵ
										//3�����Һ���Ƶ��
										//4�����Һ������
										//5�����Һ��������λ
	RowObjectFace<8> m_TranTriger1;     //�¼�����
										//��������
										//ֵ
										//��λ
										//�ܵ���ڴ����¼�Ϊ1���ܵ����ڴ����¼�Ϊ2����һ���ܵ���
										//�����¼��Ĺܵ���ţ���һ���ܵ���
										//�ܵ���ڴ����¼�Ϊ1���ܵ����ڴ����¼�Ϊ2���ڶ����ܵ���
										//�����¼��Ĺܵ���ţ��ڶ����ܵ���
	RowObjectFace<8> m_TranTriger2;

	//��˲������
	RowObjectFace<1> m_TranModel;				//��˲��ģ��
	RowObjectFace<2> m_RotateInertia;			//ת���������ã��綯�������壩\ת��������λ
	RowObjectFace<1> m_Speed;					//�öת��
	RowObjectFace<3> m_FourQuadrantData;        //����������Դ���\���������ݵ�����\�Ƕ�ѡ��0��1��
public:
	TwoDTable m_Trans1Table;			//none��δ֪��\1��δ֪��
										//˲̬������������һ��˲̬��
									    //��һ�����ݵ�λ\�ڶ������ݵ�λ
										//����
	TwoDTable m_Trans2Table;			//none��δ֪��\1��δ֪��
										//˲̬������������һ��˲̬��
									    //��һ�����ݵ�λ\�ڶ������ݵ�λ
										//����'

	ThreeDTable m_FourquadTable;        //��ʹ�õĵ����������ݱ�
											
};

inline RowObjectFace<1>& JunTransData::ValueTypeData()
{
	return m_ValueType;
}

inline RowObjectFace<1>& JunTransData::SpecialData()
{
	return m_Special;
}

inline RowObjectFace<1>& JunTransData::Repeat1Data()
{
	return m_Repeat1;
}

inline RowObjectFace<1>& JunTransData::Repeat2Data()
{
	return m_Repeat2;	
}

inline RowObjectFace<1>& JunTransData::TransTypeData()
{
	return m_TranType;
}

inline RowObjectFace<5>& JunTransData::PeriodicData()
{
	return m_Periodic;
}

inline RowObjectFace<8>& JunTransData::TranTriger1Data()
{
	return m_TranTriger1;
}

inline RowObjectFace<8>& JunTransData::TranTriger2Data()
{
	return m_TranTriger2;
}

inline RowObjectFace<1>& JunTransData::TranModelData()
{
	return m_TranModel;
}

inline RowObjectFace<2>& JunTransData::RotateInertiaData()
{
	return m_RotateInertia;
}

inline RowObjectFace<1>& JunTransData::SpeedData()
{
	return m_Speed;
}

inline RowObjectFace<3>& JunTransData::FourQuadrantData()
{
	return m_FourQuadrantData;
}

#endif // !defined(AFX_JUNTRANSDATA_H__04CCC98C_2A08_4E0E_968D_54ED1BCA43D9__INCLUDED_)

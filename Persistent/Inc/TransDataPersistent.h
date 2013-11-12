// TransDataPersistent.h: interface for the TransDataPersistent class.
/*
 * Copyright (C), 2006,��ɳ���������˾CAE������
 * All rights reserved.
 *
  �ļ����ƣ�TransDataPersistent.h
  ժҪ��    ˲������
  author  : LSP          
*/
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRANSDATAPERSISTENT_H__AF9BA607_F926_486A_A725_7C0542E9067B__INCLUDED_)
#define AFX_TRANSDATAPERSISTENT_H__AF9BA607_F926_486A_A725_7C0542E9067B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "TwoDTablePersistent.h"

class AFX_EXT_CLASS TransDataPersistent  
{
public:
	TransDataPersistent();
	virtual ~TransDataPersistent();
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
	StrArray<5>& Periodic();
	void Periodic(const StrArray<5>& strValue);
	StrArray<8>& TranTriger1();
	void TranTriger1(const StrArray<8>& strValue);
	StrArray<8>& TranTriger2();
	void TranTriger2(const StrArray<8>& strValue);
	CString TranModel();
	void TranModel(CString strValue);
	CString Speed();
	void Speed(CString strValue);
	StrArray<2>& RotateInertia();
	void RotateInertia(const StrArray<2>& strValue);
	StrArray<3>& FourQuadrant();
	void FourQuadrant(const StrArray<3>& strValue);
	

private:
    CString m_ValueType;				//1��0:����ֵ��1����Ժ㶨����ֵ
	CString m_Special;					//2��0��˲̬�ر�����ѡ�С�û�С���1��˲̬�ر�����ѡ������˲̬���ݡ�����Ծ���ڵ��ر���������2���ֱ�鿴�ر�������Ӧ�����֣�
	CString m_Repeat1;					//3��0����һ��˲���ظ�ûѡ�У�-1ѡ�У�
	CString m_Repeat2;					//4��0���ڶ���˲���ظ�ûѡ�У�-1ѡ�У�
	CString m_TranType;					//5��0:ʱ�䣬1�������¼���2�������¼�ѭ��3�����������¼�
	StrArray<5> m_Periodic;				//1��0��������û��ѡ��-1������������ѡ��
										//2��0��û��ѡ��ʹ�����Һ����ľ���ֵ��-1��ѡ��ʹ�����Һ����ľ���ֵ
										//3�����Һ���Ƶ��
										//4�����Һ������
										//5�����Һ��������λ
	StrArray<8> m_TranTriger1;			 //�¼�����
										//��������
										//ֵ
										//��λ
										//�ܵ���ڴ����¼�Ϊ1���ܵ����ڴ����¼�Ϊ2����һ���ܵ���
										//�����¼��Ĺܵ���ţ���һ���ܵ���
										//�ܵ���ڴ����¼�Ϊ1���ܵ����ڴ����¼�Ϊ2���ڶ����ܵ���
										//�����¼��Ĺܵ���ţ��ڶ����ܵ���
	StrArray<8> m_TranTriger2;

	//��˲������
	CString m_TranModel;				//��˲��ģ��
	StrArray<2> m_RotateInertia;			//ת���������ã��綯�������壩\ת��������λ
	CString m_Speed;					//�öת��
	StrArray<3> m_FourQuadrantData;        //����������Դ���\���������ݵ���
public:
	TwoDTablePersistent m_Trans1Table;									
	TwoDTablePersistent m_Trans2Table;	
	ThreeDTablePersistent m_FourquadTable;
									
};
/*------------------------------------------*/
inline CString TransDataPersistent::ValueType()
{
	return m_ValueType;
}
inline void TransDataPersistent::ValueType(CString strValue)
{
	m_ValueType = strValue;
}
/*------------------------------------------*/
inline CString TransDataPersistent::Special()
{
	return m_Special;
}
inline void TransDataPersistent::Special(CString strValue)
{
	m_Special = strValue;
}
/*------------------------------------------*/
inline CString TransDataPersistent::Repeat1()
{
	return m_Repeat1;
}
inline void TransDataPersistent::Repeat1(CString strValue)
{
	m_Repeat1 = strValue;
}
/*------------------------------------------*/
inline CString TransDataPersistent::Repeat2()
{
	return m_Repeat2;
}
inline void TransDataPersistent::Repeat2(CString strValue)
{
	m_Repeat2 = strValue;
}
/*------------------------------------------*/
inline CString TransDataPersistent::TranType()
{
	return m_TranType;
}
inline void TransDataPersistent::TranType(CString strValue)
{
	m_TranType = strValue;
}
/*------------------------------------------*/
inline StrArray<5>& TransDataPersistent::Periodic()
{
	return m_Periodic;
}
inline void TransDataPersistent::Periodic(const StrArray<5>& strValue)
{
	m_Periodic = strValue;
}
/*------------------------------------------*/
inline StrArray<8>& TransDataPersistent::TranTriger1()
{
	return m_TranTriger1;
}
inline void TransDataPersistent::TranTriger1(const StrArray<8>& strValue)
{
	m_TranTriger1 = strValue;
}
/*------------------------------------------*/
inline StrArray<8>& TransDataPersistent::TranTriger2()
{
	return m_TranTriger2;
}
inline void TransDataPersistent::TranTriger2(const StrArray<8>& strValue)
{
	m_TranTriger2 = strValue;
}

/*------------------------------------------*/
inline CString TransDataPersistent::TranModel()
{
	return m_TranModel;
}
inline void TransDataPersistent::TranModel(CString strValue)
{
	m_TranModel = strValue;
}
/*------------------------------------------*/
inline CString TransDataPersistent::Speed()
{
	return m_Speed;
}
inline void TransDataPersistent::Speed(CString strValue)
{
	m_Speed = strValue;
}
/*------------------------------------------*/
inline StrArray<2>& TransDataPersistent::RotateInertia()
{
	return m_RotateInertia;
}
inline void TransDataPersistent::RotateInertia(const StrArray<2>& strValue)
{
	m_RotateInertia = strValue;
}
/*------------------------------------------*/
inline StrArray<3>& TransDataPersistent::FourQuadrant()
{
	return m_FourQuadrantData;
}
inline void TransDataPersistent::FourQuadrant(const StrArray<3>& strValue)
{
	m_FourQuadrantData = strValue;
}
#endif // !defined(AFX_TRANSDATAPERSISTENT_H__AF9BA607_F926_486A_A725_7C0542E9067B__INCLUDED_)

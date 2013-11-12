// Transient.h: interface for the Transient class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRANSIENT_H__B0917ED4_96B0_4518_8594_49E6CA326280__INCLUDED_)
#define AFX_TRANSIENT_H__B0917ED4_96B0_4518_8594_49E6CA326280__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "StrFlyWeight.h"
#include "TransDataTable.h"
#include "TransDataPersistent.h"
#include "ScenarioObject.h"

class Transient  
{
public:
	Transient();
	virtual ~Transient();
public:
	const StrFlyWeight& ValueType();
	void ValueType(const StrFlyWeight& ref);
	const StrFlyWeight& Special();
	void Special(const StrFlyWeight& ref);
	const StrFlyWeight& Repeat1();
	void Repeat1(const StrFlyWeight& ref);
	const StrFlyWeight& Repeat2();
	void Repeat2(const StrFlyWeight& ref);
	const StrFlyWeight& TranType();
	void TranType(const StrFlyWeight& ref);
    const ArrayFlyWeight<5>& Periodic();
	void Periodic(const ArrayFlyWeight<5>& ref);
	const ArrayFlyWeight<8>& TranTriger1();
	void TranTriger1(const ArrayFlyWeight<8>& ref);
	const ArrayFlyWeight<8>& TranTriger2();
	void TranTriger2(const ArrayFlyWeight<8>& ref);

public:
	StrFlyWeight m_ValueType;				//1��0:����ֵ��1����Ժ㶨����ֵ
	StrFlyWeight m_Special;					//2��0��˲̬�ر�����ѡ�С�û�С���1��˲̬�ر�����ѡ������˲̬���ݡ�����Ծ���ڵ��ر���������2���ֱ�鿴�ر�������Ӧ�����֣�
	StrFlyWeight m_Repeat1;					//3��0����һ��˲���ظ�ûѡ�У�-1ѡ�У�
	StrFlyWeight m_Repeat2;					//4��0���ڶ���˲���ظ�ûѡ�У�-1ѡ�У�
	StrFlyWeight m_TranType;					//5��0:ʱ�䣬1�������¼���2�������¼�ѭ��3�����������¼�
	ArrayFlyWeight<5> m_Periodic;				//1��0��������û��ѡ��-1������������ѡ��
										//2��0��û��ѡ��ʹ�����Һ����ľ���ֵ��-1��ѡ��ʹ�����Һ����ľ���ֵ
										//3�����Һ���Ƶ��
										//4�����Һ������
										//5�����Һ��������λ
	ArrayFlyWeight<8> m_TranTriger1;			 //�¼�����
										//��������
										//ֵ
										//��λ
										//�ܵ���ڴ����¼�Ϊ1���ܵ����ڴ����¼�Ϊ2����һ���ܵ���
										//�����¼��Ĺܵ���ţ���һ���ܵ���
										//�ܵ���ڴ����¼�Ϊ1���ܵ����ڴ����¼�Ϊ2���ڶ����ܵ���
										//�����¼��Ĺܵ���ţ��ڶ����ܵ���
	ArrayFlyWeight<8> m_TranTriger2;
public:
	void InitData(ScenarioObject *pObject);
	BOOL SaveData(ScenarioObject *pObject,int &num1,int &num2);
	int Instance(NameArray &array,int nKey);
	BOOL Save(TransDataPersistent &Persistent,int num1,int num2);
	BOOL Read(TransDataPersistent &Persistent);
	TransDataTable<2> m_Trans1Table;									
	TransDataTable<2> m_Trans2Table;
protected:
	
	void InitData(ScenarioObject *pObject,int &nKey);
	BOOL SaveData(ScenarioObject *pObject,int &num1,int &num2,int &nKey);
	int m_nKey;

};

/*----------------------------------------------*/
inline const StrFlyWeight& Transient::ValueType()
{
	return m_ValueType;
}
/*----------------------------------------------*/
inline void Transient::ValueType(const StrFlyWeight& ref)
{
	m_ValueType = ref;
}

/*----------------------------------------------*/
inline const StrFlyWeight& Transient::Special()
{
	return m_Special;
}
/*----------------------------------------------*/
inline void Transient::Special(const StrFlyWeight& ref)
{
	m_Special = ref;
}

/*----------------------------------------------*/
inline const StrFlyWeight& Transient::Repeat1()
{
	return m_Repeat1;
}
/*----------------------------------------------*/
inline void Transient::Repeat1(const StrFlyWeight& ref)
{
	m_Repeat1 = ref;
}

/*----------------------------------------------*/
inline const StrFlyWeight& Transient::Repeat2()
{
	return m_Repeat2;
}
/*----------------------------------------------*/
inline void Transient::Repeat2(const StrFlyWeight& ref)
{
	m_Repeat2 = ref;
}

/*----------------------------------------------*/
inline const StrFlyWeight& Transient::TranType()
{
	return m_TranType;
}
/*----------------------------------------------*/
inline void Transient::TranType(const StrFlyWeight& ref)
{
	m_TranType = ref;
}

/*----------------------------------------------*/
inline const ArrayFlyWeight<5>& Transient::Periodic()
{
	return m_Periodic;
}
/*----------------------------------------------*/
inline void Transient::Periodic(const ArrayFlyWeight<5>& ref)
{
	m_Periodic = ref;
}

/*----------------------------------------------*/
inline const ArrayFlyWeight<8>& Transient::TranTriger1()
{
	return m_TranTriger1;
}
/*----------------------------------------------*/
inline void Transient::TranTriger1(const ArrayFlyWeight<8>& ref)
{
	m_TranTriger1 = ref;
}

/*----------------------------------------------*/
inline const ArrayFlyWeight<8>& Transient::TranTriger2()
{
	return m_TranTriger2;
}
/*----------------------------------------------*/
inline void Transient::TranTriger2(const ArrayFlyWeight<8>& ref)
{
	m_TranTriger2 = ref;
}
#endif // !defined(AFX_TRANSIENT_H__B0917ED4_96B0_4518_8594_49E6CA326280__INCLUDED_)

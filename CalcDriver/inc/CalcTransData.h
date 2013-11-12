// CalcTransData.h: interface for the CalcTransData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CALCTRANSDATA_H__03896490_6ACD_4B78_8519_C51C18213DF1__INCLUDED_)
#define AFX_CALCTRANSDATA_H__03896490_6ACD_4B78_8519_C51C18213DF1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "CalcPeriodic.h"
#include "CalcTable.h"
#include "CalcTriger.h"

class AFX_EXT_CLASS CalcTransData  
{
public:
	CalcTransData();
	virtual ~CalcTransData();
public:
	int ValueType();
	BOOL Special();
	BOOL Repeat1();
	BOOL Repeat2();
	int TranType();
	void ValueType(int nValue);
	void Special(int nValue);
	void Repeat1(int nValue);
	void Repeat2(int nValue);
	void TranType(int nValue);
	friend ostream& operator<< (ostream &CalcOut,CalcTransData &ref);

private:
	int m_nValueType;				//1��0:����ֵ��1����Ժ㶨����ֵ
	int m_bSpecial;					//2��0��˲̬�ر�����ѡ�С�û�С���1��˲̬�ر�����ѡ������˲̬���ݡ�����Ծ���ڵ��ر���������2���ֱ�鿴�ر�������Ӧ�����֣�
	int m_bRepeat1;					//3��0����һ��˲���ظ�ûѡ�У�-1ѡ�У�
	int m_bRepeat2;					//4��0���ڶ���˲���ظ�ûѡ�У�-1ѡ�У�
	int m_nTranType;				//5��0:ʱ�䣬1�������¼���2�������¼�ѭ��3�����������¼�
public:
	CalcPeriodic m_Periodic;
	CalcTriger   m_Triger1;
	CalcTriger   m_Triger2;
	TransTable m_TranData1;
	TransTable m_TranData2;

};

#endif // !defined(AFX_CALCTRANSDATA_H__03896490_6ACD_4B78_8519_C51C18213DF1__INCLUDED_)

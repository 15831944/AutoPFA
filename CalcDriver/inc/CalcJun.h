// CalcJun.h: interface for the CalcJun class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CALCJUN_H__8A7A11AE_8DC5_4601_8415_A6153DB1F10D__INCLUDED_)
#define AFX_CALCJUN_H__8A7A11AE_8DC5_4601_8415_A6153DB1F10D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "CalcTable.h"

class AFX_EXT_CLASS CalcJun  
{
public:
	virtual ostream& Write(ostream& CalcOut)=0;
	CalcJun();
	virtual ~CalcJun();
	friend ostream& operator<< (ostream &CalcOut,CalcJun &ref);

public:
	void PipeID(ListImp<StrArray<1> >& list);
	void CurveData(const ListImp<StrArray<2> >& ref);
	void Name(CString strName);
	void ID(int nValue);
	void Key(int nValue);
	void InEle(double dValue);
	void OutEle(double dValue);
	void DesignFactor(double dValue);
	void InitGuessType(int nValue);
	void InitGuess(double dValue);
	void SpecialMark(int nValue);

	CString Name();
	int ID();
	int Key();
	double InEle();
	double OutEle();
	double DesignFactor();
	int InitGuessType();
	double InitGuess();
	int SpecialMark();
	ListImp<StrArray<1> >& PipeID();
	ListImp<StrArray<2> >& CurveData();

protected:
	CString m_strName;
	int m_nTypeID;				//�ڵ����ͱ��ID
	int m_nKey;					//�ڵ�Ԫ�����
	double m_dInEle;			//�ڵ���ڱ��
	double m_dOutEle;			//�ڵ���ڱ��
	double m_dDesignFactor;		//��ʧ�������
	int    m_nInitGuessType;	//��ʼ���²�ѹ�����ͣ�0��ѹͷ��1ѹ����
	double m_dInitGuess;		//��ʼ���²�ֵ
	int    m_nSpecialMark;		//1.�ڵ���ض�����0:������1���رգ�2����û�п���3������
	PipeIDList m_PipeID;		//
	CalcTable<2> m_CurveData;
protected:
//	ostream& WriteOption(ostream& CalcOut);
//	ostream& WriteJun(ostream& CalcOut);
};

#endif // !defined(AFX_CALCJUN_H__8A7A11AE_8DC5_4601_8415_A6153DB1F10D__INCLUDED_)

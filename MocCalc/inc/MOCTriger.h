// MOCTriger.h: interface for the MOCTriger class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MOCTRIGER_H__38AB7FC2_56FC_4363_A88D_4CBC58102C1D__INCLUDED_)
#define AFX_MOCTRIGER_H__38AB7FC2_56FC_4363_A88D_4CBC58102C1D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "MOCTable.h"
#include "CalcTable.h"
#include "MOCTrigerStrategyMgr.h"

class CalcTriger;

class MOCTriger  
{
public:
	BOOL TrigerStatus(double dTime,double dStart);
	double GetTransY(double dX);
	void Triger(BOOL bTriger);
	BOOL IsTriger();
	double GetTransY(double dX,double dStmY);
	void Init(MOCComponentMgr &mgr);
	void InitFixTrans(MOCComponentMgr &mgr,int nKey,int nEventType,int nConditionType);
	double GetTransY(double dX,double dStmY,double dStart);
	void Tran(PFUNTRAN2 pTran,double d);
	void Tran(PFUNTRAN pTran);
	void Read(CalcTriger &triger,TransTable &table);
	void Repeat(BOOL bValue);
	MOCTriger();
	virtual ~MOCTriger();

private:
	BOOL HasData();

private:
	int m_nEventType;                //�¼�����
	int m_nConditionType;			 //��������
	double	m_dValue;				 //ֵ
	int m_nPort1;					 //�ܵ���ڴ����¼�Ϊ1���ܵ����ڴ����¼�Ϊ2
	int m_nComponentID1;			 //�����¼���������
	int m_nPort2;					 //�ܵ���ڴ����¼�Ϊ1���ܵ����ڴ����¼�Ϊ2
	int m_nComponentID2;			 //�����¼���������	

	BOOL m_bRepeat;					//0��˲���ظ�ûѡ�У�1ѡ�У�
	DataTable m_table;
	MOCTrigerStrategyMgr m_mgr;
	BOOL m_bTriger;
};

#endif // !defined(AFX_MOCTRIGER_H__38AB7FC2_56FC_4363_A88D_4CBC58102C1D__INCLUDED_)

// MOCAssignFlow.h: interface for the MOCAssignFlow class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MOCASSIGNFLOW_H__1EE43EE1_C3FE_42CC_807D_884B5A890EC6__INCLUDED_)
#define AFX_MOCASSIGNFLOW_H__1EE43EE1_C3FE_42CC_807D_884B5A890EC6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MOCJun.h"
#include "MOCTranData.h"

class MOCAssignFlow : public MOCJun  
{
public:
	BOOL Read(CalcJun *pData);
	static MOCJun* Creator();
	MOCAssignFlow();
	virtual ~MOCAssignFlow();

private:
	BOOL InitEndInfo();
	
private:
	void CalcImpulse(MOCTrans &trans,double dTime);
	BOOL InitTranData(MOCComponentMgr &mgr);
	void UpdataEnd();
	void CalcStm();
	void CalcStm(double dFlow,double dPress);
	double   m_dK;						//��ʧϵ��Kֵ
	double   m_dFlow;				    //��С
	double   m_dInitPress;				//��ʼ��ѹ��
	int      m_bSelInitPress;           //�㶨����Ϊ0�ĳ�ʼ��ѹ����0��û��ѡ��1ѡ�У�

	MOCTranData m_tranData;
};

#endif // !defined(AFX_MOCASSIGNFLOW_H__1EE43EE1_C3FE_42CC_807D_884B5A890EC6__INCLUDED_)

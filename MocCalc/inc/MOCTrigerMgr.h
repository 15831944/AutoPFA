// MOCTrigerMgr.h: interface for the MOCTrigerMgr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MOCTRIGERMGR_H__7FA9E12A_B0C0_4F79_9A34_1989E619BCB5__INCLUDED_)
#define AFX_MOCTRIGERMGR_H__7FA9E12A_B0C0_4F79_9A34_1989E619BCB5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "MOCTriger.h"
class CalcTransData;

class MOCTrigerMgr  
{
public:
	int TrigerStatus(double dTime,double dStart);
	double GetTransY(double dX);
	void InitFixTrans(MOCComponentMgr &mgr,int nKey,int nEventType);
	void Init(MOCComponentMgr &mgr);
	double GetTransY(double dX,double dStmY,double dStart);
	void Tran(PFUNTRAN2 pTran, double d);
	void TranRel(PFUNTRAN2 pTran, double d);
	void Tran(PFUNTRAN pTran);
	void Read(CalcTransData &transdata);
	MOCTrigerMgr();
	virtual ~MOCTrigerMgr();

private:
	int m_nValueType;				//0:����ֵ��1����Ժ㶨����
	int m_nTranType;				//0:ʱ�䣬1�������¼���2�������¼�ѭ��3�����������¼�
	MOCTriger m_triger1;
	MOCTriger m_triger2;
};

#endif // !defined(AFX_MOCTRIGERMGR_H__7FA9E12A_B0C0_4F79_9A34_1989E619BCB5__INCLUDED_)

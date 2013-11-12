// MOCTranData.cpp: implementation of the MOCTranData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MOCTranData.h"
#include "CalcTransData.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MOCTranData::MOCTranData()
{
	m_bSpecial = FALSE;
}

MOCTranData::~MOCTranData()
{

}

void MOCTranData::Read(CalcTransData &transdata)
{
	m_bSpecial = transdata.Special();
	m_periodic.Read(transdata.m_Periodic);
	m_trigerMgr.Read(transdata);
}

void MOCTranData::Tran(PFUNTRAN pTran)
{
	m_trigerMgr.Tran(pTran);
	m_periodic.Tran(pTran);
}

void MOCTranData::TranRel(PFUNTRAN2 pTran, double d)
{
	m_trigerMgr.TranRel(pTran,d);
}

void MOCTranData::Tran(PFUNTRAN2 pTran, double d)
{
	m_trigerMgr.Tran(pTran,d);
}
/*---------------------------------------------------
 dX:˲̬���ݱ��һ�е�ֵ
 dStmY����̬��˲̬���ݱ�ڶ��ж�Ӧ������ֵ����������˲���˲̬���ݱ�ʹ�����ֵʹ���������
 dStart��˲��ģ�⿪ʼʱ�䣬��ʱ��Ϊ���ֵʹ��
 ���أ�˲�䵱ǰ����ʹ�õĲ���
----------------------------------------------------*/
double MOCTranData::GeTransY(double dX, double dStmY,double dStart)
{
	if(m_bSpecial)
	{//����˲̬����
		return dStmY;
	}
	else
	{
		if(m_periodic.IsSelPeriodic())
		{//ѡ��ʹ�����Һ���
			return m_periodic.GetTransY(dX);
		}
		else
		{//ѡ��ʹ�ô���˲��
			return m_trigerMgr.GetTransY(dX,dStmY,dStart);
		}
	}
}

void MOCTranData::Init(MOCComponentMgr &mgr)
{
	m_trigerMgr.Init(mgr);
}

void MOCTranData::InitFixTrans(MOCComponentMgr &mgr,int nKey,int nEventType)
{
	m_trigerMgr.InitFixTrans(mgr,nKey,nEventType);
}

BOOL MOCTranData::IsIgnoreTrans()
{
	return m_bSpecial;
}

int MOCTranData::TrigerStatus(double dTime,double dStart)
{
	return m_trigerMgr.TrigerStatus(dTime,dStart);
}

double MOCTranData::GeTransY(double dX)
{
	return m_trigerMgr.GetTransY(dX);
}
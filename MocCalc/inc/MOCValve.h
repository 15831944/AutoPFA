// MOCValve.h: interface for the MOCValve class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MOCVALVE_H__17AC9243_0B66_45A9_998F_9D13EF8CF849__INCLUDED_)
#define AFX_MOCVALVE_H__17AC9243_0B66_45A9_998F_9D13EF8CF849__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MOCJun.h"
#include "MOCTranData.h"

class MOCValve : public MOCJun  
{
public:
	void UpdataEnd();
	BOOL Read(CalcJun *pData);
	static MOCJun* Creator();
	MOCValve();
	virtual ~MOCValve();

private:
	void CalcStm();
	void CalcStmK(double dK);
	void CalcStmCv(double dCv);
	BOOL InitEndInfo();

private:
	void CalcImpulse(MOCTrans &trans,double dTime);
	BOOL InitTranData(MOCComponentMgr &mgr);
	int      m_nLossType;                       //��ʧģ��0������ϵ��ģ�ͣ�1��Kϵ��ģ��
	double   m_dKOrCv;						    //K��Cvϵ��ֵ
	int      m_nBasisAreaType;					//��ʧģ�͵��������0��Ĭ�����ιܵ������1�����ιܵ����2���û�ָ�����3���û�ָ��ֱ��
	double   m_dBasisArea;						//���Ŷorֱ��
	int		 m_nType;						    //����(0����ͨ���ţ�1��ѡ�з���Ϊ���ڷ���)
	double   m_dExitPress;					    //����ѹ��

	double   m_dOutFlow;                       //���ڷ�������������

	MOCTranData m_tranData;
};

#endif // !defined(AFX_MOCVALVE_H__17AC9243_0B66_45A9_998F_9D13EF8CF849__INCLUDED_)

// MOCCheck.h: interface for the MOCCheck class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MOCCHECK_H__C656B9D0_1827_4017_80A2_FC8B0F38628B__INCLUDED_)
#define AFX_MOCCHECK_H__C656B9D0_1827_4017_80A2_FC8B0F38628B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MOCJun.h"
#include "MOCTranData.h"

class MOCCheck : public MOCJun  
{
public:
	void Close(BOOL bClose);
	int CheckStatus();
	BOOL Read(CalcJun *pData);
	static MOCJun* Creator();
	MOCCheck();
	virtual ~MOCCheck();

private:
	void CalcStm();
	void CalcStmK(double dK);
	void CalcStmCv(double dCv);
	BOOL InitEndInfo();
	void UpdataEnd();
	BOOL InitTranData(MOCComponentMgr &mgr);

private:
	void TestStatus();
	BOOL IsCloseTriger();
	BOOL IsReOpenTriger();
	void CalcImpulse(MOCTrans &trans,double dTime);
	int    m_nLossType;						    //��ʧģ��0������ϵ��ģ�ͣ�1��Kϵ��ģ��			                                           
	double m_dKOrCv;					        //K��Cvϵ��ֵ
    int    m_nBasisAreaType;					//��ʧģ�͵��������0��Ĭ�����ιܵ������1�����ιܵ����2���û�ָ�����3���û�ָ��ֱ��
	double m_dBasisArea;						//���Ŷorֱ��
	double m_dReOpenPress;					    //ѹ��ֵ	
	double m_dCloseVel;					        //�رշ��ŵ���С�����ٶ�\�ٶȵ�λ

	BOOL m_bClose;                              //Ѹ�ٴ򿪺͹ر�
	int m_nCheckStatus;                         //0:�򿪣�1���رգ�3����ʼ�򿪣�4����ʼ�ر�
	
	MOCTranData m_tranData;
};

#endif // !defined(AFX_MOCCHECK_H__C656B9D0_1827_4017_80A2_FC8B0F38628B__INCLUDED_)

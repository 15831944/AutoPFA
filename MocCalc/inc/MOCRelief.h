// MOCRelief.h: interface for the MOCRelief class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MOCRELIEF_H__02D82FF7_33B5_46FE_8337_E1943A24BA79__INCLUDED_)
#define AFX_MOCRELIEF_H__02D82FF7_33B5_46FE_8337_E1943A24BA79__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MOCJun.h"
#include "MOCTranData.h"

class MOCRelief : public MOCJun  
{
public:
	void Crack(BOOL bCrack);
	int ReliefStatus();
	BOOL Read(CalcJun *pData);
	static MOCJun* Creator();
	MOCRelief();
	virtual ~MOCRelief();

private:
	void CalcStm();
	void CalcStmClose();
	void CalcStmOpen(double dKOrCv);
	BOOL InitEndInfo();
	BOOL InitTranData(MOCComponentMgr &mgr);
private:
	void TestStatus();
	BOOL IsCloseTriger();
	BOOL IsCrackTriger();
	void CalcInterValve(double dKOrCv);
	void CalcExitValve(double dKOrCv);
	void CalcImpulse(MOCTrans &trans,double dTime);
	void UpdataEnd();
	void CalcCloseInline();
	void CalcCloseValve();
	double GetCurCv();
	int		 m_nType;							//����(1:�ڲ���ȫ����internal relief��2:���ڰ�ȫ����exit relief��3:��Ƕ��ȫ����inline relief��)
	int      m_nLossType;						//��ʧģ��(0������ϵ��ģ�ͣ�1��Kϵ��ģ��3��������ϵ��)
	double   m_dKOrCv;						    //K��Cvϵ��ֵ
	int      m_nBasisAreaType;					//��ʧģ�͵��������0��Ĭ�����ιܵ������1�����ιܵ����2���û�ָ�����3���û�ָ��ֱ��
	double   m_dBasisArea;						//���Ŷorֱ��
									            //0. ����ˮͷ, 2. ˮͷ��,  1������ѹ��, 3��ѹ����.
	BOOL     m_bDeltaPress;					    //Tureѹ����
	double	 m_dCrackPress;				        //���ѵ�ѹ��
	double   m_dExitPress;					    //����ѹ��

	double m_dOutFlow;
	BOOL m_bCrack;
	int m_nReliefStatus;

	MOCTranData m_tranData;

	short m_iCalcStatus ;//����״̬:��ʼ״̬Ϊ-1�����ڵ���0ʱΪ�ǳ�ʼ״̬���ڷǳ�ʼ״̬�У�
						//�ر�״̬��Ϊ0����״̬Ϊ1
};

#endif // !defined(AFX_MOCRELIEF_H__02D82FF7_33B5_46FE_8337_E1943A24BA79__INCLUDED_)

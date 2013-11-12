// MOCSpray.h: interface for the MOCSpray class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MOCSPRAY_H__2D114CA1_5636_4FF6_AA92_D472456BA602__INCLUDED_)
#define AFX_MOCSPRAY_H__2D114CA1_5636_4FF6_AA92_D472456BA602__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MOCJun.h"
#include "MOCTranData.h"

class MOCSpray : public MOCJun  
{
public:
	double GetOutVolumeFlow();
	BOOL Read(CalcJun *pData);
	static MOCJun* Creator();
	MOCSpray();
	virtual ~MOCSpray();

private:
	void CalcStm();
	void CalcStm(double dKOrCv);
	BOOL InitEndInfo();

private:
	void Result(JunTranOut &out, int nStep);
	void CalcImpulse(MOCTrans &trans,double dTime);
	BOOL InitTranData(MOCComponentMgr &mgr);
	void UpdataEnd();
	double SprayBasisArea();
	static double TranDcToK(double dDc,double dRatio);
	static double TranKfToK(double dKf,double dBasisArea);
	int  m_nLossType;						//0������ϵ��1��Kϵ��(fire sprinklers Kֵ�Ķ����ǣ� K = Q/sqrt(dP)
	double  m_dExitArea;						//�׿ڵ����
	double	m_dKOrCv;					    	//K��Cvϵ��ֵ
	double  m_dExitPress;					    //����ѹ��
	double  m_nHoleNum;
	
	double m_dOutFlow;

	MOCTranData m_tranData;

	ListImp<StrArray<4> >    m_PipeInfo;//6.0�¶���Ĺܵ�K
};

#endif // !defined(AFX_MOCSPRAY_H__2D114CA1_5636_4FF6_AA92_D472456BA602__INCLUDED_)

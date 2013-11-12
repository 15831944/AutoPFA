// MOCPump.h: interface for the MOCPump class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MOCPUMP_H__6827635F_F264_448A_A3B3_5E6E109A714C__INCLUDED_)
#define AFX_MOCPUMP_H__6827635F_F264_448A_A3B3_5E6E109A714C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MOCJun.h"
#include "MOCJunControl.h"
#include "PumpTransModelMgr.h"

class MOCPump : public MOCJun  
{
public:
	double GetSpeed();
	void UpdataEnd();
	BOOL Read(CalcJun *pData);
	static MOCJun* Creator();
	MOCPump();
	virtual ~MOCPump();

private:
	void CalcStm();
	BOOL InitEndInfo();
	BOOL InitTranData(MOCComponentMgr &mgr);

private:
	void CalcImpulse(MOCTrans &trans,double dTime);
	void TranControlValue(int nControl);	
	
private:
	void Result(JunTranOut &out, int nStep);
	int 		m_nPumpType;			//��ģ�͵�����0�������ߣ�1��ָ���������2��ָ����������
	double   	m_dPumpFlow;			//������С
	int         m_nPumpSet;				//�û��飬�����ã��õ������������ã�����+�õ�����,1:����
	int			m_nTranModel;			//��˲��ģ��
	double		m_dSpeedRatio;			//���ٱõ�������Ա����ߵ����ʣ�1����ʾ100%��
	double   	m_dControlValue;		//���Ƶ����ֵ
	MOCPumpModel m_Model;
	MOCJunControl m_Control;
	MOCPumpInertia m_Inertia;
	MOCFourQuadrantData m_FourQuadrantData;
	MOCPumpConfig m_config;
	MOCTranData m_tranData;
	PumpTransModelMgr m_mgr;
};

#endif // !defined(AFX_MOCPUMP_H__6827635F_F264_448A_A3B3_5E6E109A714C__INCLUDED_)

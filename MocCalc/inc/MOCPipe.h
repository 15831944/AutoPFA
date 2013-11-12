// MOCPipe.h: interface for the MOCPipe class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MOCPIPE_H__8FC702B0_058C_48C2_AE0C_76CF888BA842__INCLUDED_)
#define AFX_MOCPIPE_H__8FC702B0_058C_48C2_AE0C_76CF888BA842__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MOCComponent.h"
#include "EndInfo.h"
#include "MOCSteady.h"
#include "MOCTrans.h"
#include "MOCStationMgr.h"
#include "PipeTranOut.h"

class CalcPipe;
class PipeStmOut;


class MOCPipe : public MOCComponent  
{
public:
	void Result(PipeTranOut &out,int nStep);
	void CalcImpulse(MOCTrans &trans);
	BOOL InitStation();
	void CheckTol(MOCSteady &Steady);
	void Result(PipeStmOut &out);
	void CalcStm();
	void InitEndInfo();
	EndInfo* GetOutEnd();
	EndInfo* GetInEnd();
	double CalcArea();
	BOOL Read(CalcPipe &data);
	MOCPipe();
	virtual ~MOCPipe();
	double CalcR(double dF,double dEndK,int nSectionNum=1);
	double FrictionCalc();
	double B();
	double CalcR();
	double GetDeltaG();
private:
	double CalcRe();
private:
	double GetFLoss(double dF);
	double GetHLoss();
	double GetOutStaticPress();
	double GetInStaticPress();
	double GetOutStagPress();
	double GetInStagPress();
	double GetVelocity();
	double GetVolumeFlow();
	double GetMassFlow();
	double GetFK(double dF);
	double GetK(double dF);
	int m_nInJunID;				    //��ڽڵ��ID��
	int m_nOutJunID;				//���ڽڵ��ID��
	double m_dInDia;				//�ܵ��ھ�
	double m_dLen;				    //�ܵ�����
	double m_dInitFlow;				//��ʼ����������
	double m_dPipeFactor;			//�ܵ�Ħ����������ӣ�
	double m_dFitFactor;			//�ܵ�������ʧ�������
	double m_dLocalK;				//�ܹ��ֲ���Kϵ��
	int    m_nFrictionModel;		//Friction Model����:
	double m_dFriction;				//Ħ��ϵ����С
	int    m_nSectionNum;			//�ܶηֶ���ȡ��
	double m_dB;                    //B
	MOCStationMgr m_stationMgr;

	EndInfo m_InEnd;
	EndInfo m_OutEnd;
	double m_dInOldPress;
	double m_dOutOldPress;
	double m_dInOldFlow;
	double m_dOutOldFlow;	
};

#endif // !defined(AFX_MOCPIPE_H__8FC702B0_058C_48C2_AE0C_76CF888BA842__INCLUDED_)

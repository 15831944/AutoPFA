// TripWhitInertia.cpp: implementation of the TripWhitInertia class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MOCFluid.h"
#include "TripWhitInertia.h"
#include "PumpTransModelMgr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TripWhitInertia::TripWhitInertia()
{
}

TripWhitInertia::~TripWhitInertia()
{
}

void TripWhitInertia::CalcImpulse(PumpTransModelMgr &mgr,MOCTrans &trans,double dTime,double dSpeedRatio,int nSet)
{
	IneriaTripSpeed(mgr,nSet);
	mgr.CalcImpulse(nSet);
}

double TripWhitInertia::CalcSpeed(PumpTransModelMgr &mgr,double dSpeedOld,double dTorqueOld,double dTorqueNew)
{
	double dT = MOCFluid::SetpTime();
	double dRotateInertia = mgr.GetInertia().RotateInertia();
	double dSpeedNew = dSpeedOld-(dTorqueOld+dTorqueNew)*15*dT/PI/dRotateInertia; 
	return dSpeedNew;
}

void TripWhitInertia::IneriaTripSpeed(PumpTransModelMgr &mgr,int nSet)
{
	EndListRef &jun = mgr.GetEndList();
	MOCPumpInertia &Inertia = mgr.GetInertia();
	MOCPumpModel &Model = mgr.GetModel();
	MOCPumpConfig &config = mgr.GetConfig();
	double dSpeedR = Inertia.Speed();
	double dSpeedOld = mgr.GetCurSpeedRatio()*dSpeedR;
	double dMass = Model.MassFlow();
	double dRisePress = Model.RisePress();
	double dTorqueOld = Model.GetTorque(config,dSpeedR,dSpeedOld,dMass,dRisePress);
	double dTorqueNew = dTorqueOld;
	double dTorque1 = 0;
	double dSpeed1 = 0;
	double dSpeed2 = 0;
	double dSpeedNew = 0;
	double dSpeedNew1 = 0;
	int i=0;
	do 
	{//˹�ٷ�ɭ�����㣨AitKen���ٵ�����
		dSpeedNew1 = dSpeedNew;
		dSpeed1 = CalcSpeed(mgr,dSpeedOld,dTorqueOld,dTorqueNew);//�����ת��
		Model.CalcQH(jun,config,dSpeed1/dSpeedR,nSet,dMass,dMass,dRisePress);//���ݼ����ת�ټ���������ѹ������
		dTorque1 = Model.GetTorque(config,dSpeedR,dSpeed1,dMass,dRisePress);//���������õ����ʼ����ת��
		dSpeed2 = CalcSpeed(mgr,dSpeedOld,dTorqueOld,dTorque1);
		if(fabs(dSpeed2-2*dSpeed1+dSpeedOld)<1E-8)
		{
			dSpeedNew = dSpeedOld;
		}
		else
		{
			dSpeedNew = dSpeedOld - pow(dSpeed1-dSpeedOld,2)/(dSpeed2-2*dSpeed1+dSpeedOld);
		}
		Model.CalcQH(jun,config,dSpeedNew/dSpeedR,nSet,dMass,dMass,dRisePress);
		dTorqueNew = Model.GetTorque(config,dSpeedR,dSpeedNew,dMass,dRisePress);
		i++;
	} while(fabs(dSpeedNew-dSpeedNew1)>1E-6&&i<100);
	if(i>90)
	{
		ASSERT(FALSE);
		return;
	}
	mgr.SetCurSpeedRatio(dSpeedNew/dSpeedR);
}

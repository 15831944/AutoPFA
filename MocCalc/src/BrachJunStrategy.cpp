// BrachJunStrategy.cpp: implementation of the BrachJunStrategy class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BrachJunStrategy.h"
#include "EndListRef.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

BrachJunStrategy::BrachJunStrategy()
{

}

BrachJunStrategy::~BrachJunStrategy()
{

}

BrachJunStrategy* BrachJunStrategy::Instance()
{
	static BrachJunStrategy strategy;
	return &strategy;
}

void BrachJunStrategy::Calc(EndListRef &jun,double dOutMass)
{
	double dNewPress = CalcPress(jun,dOutMass);
	dNewPress = jun.CheckVaporPress(dNewPress);
	if(jun.IsVapor())
	{//�γ���Ѩ
		jun.StaticPressStrategy(dNewPress);
		jun.VaporVolume(jun.DetalVaporVolume(dOutMass)+jun.VaporVolume());
	}
	else
	{
		double dMass = jun.CollapseMass();
		dNewPress = CalcPress(jun,dOutMass-dMass);
		dNewPress = jun.CheckVaporPress(dNewPress);
		if(jun.IsVapor())
		{//��Ѩ��С
			jun.StaticPressStrategy(dNewPress);
			jun.VaporVolume(jun.DetalVaporVolume(dOutMass-dMass));
		}
		else
		{//��Ѩ��ʧ
			jun.Collapse();
			jun.StagPressStrategy(dNewPress);
		}
	}
}


double BrachJunStrategy::CalcPress(EndListRef &jun,double dOutMass)
{
	double dSc = jun.Sc();
	double dSb = jun.Sb();
	return (dSc + dOutMass) / dSb;
}

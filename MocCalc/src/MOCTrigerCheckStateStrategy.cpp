// MOCTrigerCheckStateStrategy.cpp: implementation of the MOCTrigerCheckStateStrategy class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MOCTrigerCheckStateStrategy.h"
#include "MOCCheck.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MOCTrigerCheckStateStrategy::MOCTrigerCheckStateStrategy()
{

}

MOCTrigerCheckStateStrategy::~MOCTrigerCheckStateStrategy()
{

}

MOCTrigerStrategy* MOCTrigerCheckStateStrategy::Creator()
{
	static MOCTrigerCheckStateStrategy strategy;
	return &strategy;
}

BOOL MOCTrigerCheckStateStrategy::IsTriger(MOCTrigerStrategyMgr &mgr, double dCurTime,double dStartTime)
{
	int nType = mgr.ConditionType();
	int nKey = mgr.ComponentID1();
	MOCCheck *pJun = dynamic_cast<MOCCheck*>(mgr.LookUpJun(nKey));
	if(pJun != NULL)
	{
		if(pJun->CheckStatus() == nType)
		{
			mgr.TrigerTime(dCurTime);
			if(!mgr.HasTranData())
			{
				if(3==nType)//��ʼ��
				{
					pJun->Close(FALSE);
				}
				if(4==nType)//��ʼ�ر�
				{
					pJun->Close(TRUE);
				}
			}
			return TRUE;
		}
	}
	return FALSE;
}

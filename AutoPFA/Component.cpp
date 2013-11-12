// Component.cpp: implementation of the Component class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AutoPFA.h"
#include "Component.h"
#include "StrFlyWeight.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
StrFlyWeight Component::ms_Name;
void Component::Instance(NameArray &array)
{
	ScenarioObject::InitAttr(array,IDS_COMPONENTNAME,1,1);
}

Component::Component()
{

}
Component::Component(const Component &ref):ScenarioObject(ref)
{
}

Component& Component::operator=(const Component &ref)
{
	//�ж��Ը�ֵ
	if(this == &ref)
		return *this;
    //���û��ำֵ
	ScenarioObject::operator =(ref);
	//�ͷŶ��ڴ�
	//���·�����ڴ�
	//��ֵ
	return *this;
}
Component::~Component()
{

}

CString Component::GetName(Scenario *pScenario)
{
	CString strName;
	const FlyWeight *pFly = LookUp(1,pScenario);
	if(pFly != NULL)
	{
		pFly->GetValue(strName);
	}
	return strName;
}

void Component::SetName(CString strName)
{
	ms_Name.SetValue(strName);
	SetValue(ms_Name,1);
}

CString Component::GetName()
{
	GetValue(ms_Name,1);
	return ms_Name.GetValue();
}

BOOL Component::IsDefine(BOOL bTrans)
{
	ComponentStatus status(GetArray());
	InitData();
	Status(status,bTrans);
	return status.IsDefine();
}

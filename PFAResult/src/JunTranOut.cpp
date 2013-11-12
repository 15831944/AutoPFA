// JunTranOut.cpp: implementation of the JunTranOut class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "JunTranOut.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

JunTranOut::JunTranOut()
{
}

JunTranOut::~JunTranOut()
{

}

void JunTranOut::GetArrayData(double dArray[], int nKey, OutDataAttr &attr)
{//nKeyΪ��������
	m_list.ToDuoble(dArray,nKey,attr.Key());
	for(int i=0;i<GetArrayNum();i++)
	{
		dArray[i] = attr.TranData(dArray[i]);
	}
}

int JunTranOut::GetArrayNum()
{
	return m_list.GetCount();
}

JunOut* JunTranOut::Creator(int nStep)
{
	JunOut *pOut = new JunOut;
	pOut->Step(nStep);
	m_list.AddItem(pOut);
	return pOut;
}
void JunTranOut::Instance(OutAttrArray &array, UnitSubSystem &unitsys)
{
	ComponentStmOut::InitAttr(array,unitsys,8,Time,_T("ʱ��"));
	ComponentStmOut::InitAttr(array,unitsys,1,PercentFractional,_T("��ת��"));
	ComponentStmOut::InitAttr(array,unitsys,2,Volume,_T("���������"));
	ComponentStmOut::InitAttr(array,unitsys,3,Pressure,_T("������ѹ��"));
	ComponentStmOut::InitAttr(array,unitsys,4,MassFlow,_T("����������������"));

	ComponentStmOut::InitAttr(array,unitsys,5,VolumetricFlow,_T("���������������"));
	ComponentStmOut::InitAttr(array,unitsys,6,Length,_T("��ѹ������߶�"));
	ComponentStmOut::InitAttr(array,unitsys,7,Length,_T("��ѹ������HGL"));
}

Iterator<JunOut>* JunTranOut::CreatIterator()
{
	return m_list.CreatIterator();
}



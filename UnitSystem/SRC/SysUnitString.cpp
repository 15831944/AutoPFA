// SysUnitString.cpp: implementation of the UnitString class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SysUnitString.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

UnitString::UnitString(CString strSymbol)
{
	m_strSymbol = strSymbol;
	m_bUsed = TRUE;
}

UnitString::UnitString(const UnitString &ref)
{
	m_strSymbol = ref.m_strSymbol;
	m_bUsed = ref.m_bUsed;
}

UnitString& UnitString::operator=(const UnitString &ref)
{
	//�ж��Ը�ֵ
	if(this == &ref)
		return *this;
    //���û��ำֵ
	//�ͷŶ��ڴ�
	//���·�����ڴ�
	//��ֵ
	m_strSymbol = ref.m_strSymbol;
	m_bUsed = ref.m_bUsed;
	return *this;
}
UnitString::~UnitString()
{

}

BOOL UnitString::IsUsed()
{
	return m_bUsed;
}

void UnitString::SetUsed(BOOL bUsed)
{
	m_bUsed = bUsed;
}

UnitString* UnitString::Creat(CString strSymbol)
{
	return new UnitString(strSymbol);
}

BOOL UnitString::IsStringEqual(CString strSymbol)
{
	return !m_strSymbol.CompareNoCase(strSymbol);
}


UnitString* UnitString::Clone()
{
	return new UnitString(*this);
}

// UnitSubSystem.cpp: implementation of the UnitSubSystem class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "UnitSubSystem.h"
#include "QuantityManager.h"
#include <vector>
#include "UnitSystemShareHeader.h"

using namespace std;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

UnitSubSystem::UnitSubSystem():m_Area(_T("�����λ"),Area,_T("Area"))
,m_Density(_T("�ܶȵ�λ"),Density,_T("Density"))	
,m_Diameter(_T("ֱ����λ"),Diameter,_T("Diameter"))	
,m_HeadGradient(_T("ˮͷ�¶ȵ�λ"),HeadGradient,_T("HeadGradient"))
,m_Inertia(_T("���Ե�λ"),Inertia,_T("Inertia"))		
,m_Length(_T("���ȵ�λ"),Length,_T("Length"))	
,m_MassFlow(_T("����������λ"),MassFlow,_T("MassFlow"))
,m_Mass(_T("������λ"),Mass,_T("Mass"))		
,m_PercentFractional(_T("�ٷ���/С��"),PercentFractional,_T("PercentFractional")) 
,m_Power(_T("���ʵ�λ"),Power,_T("Power"))			
,m_PressGradient(_T("ѹ���¶ȵ�λ"),PressGradient,_T("PressGradient"))
,m_Pressure(_T("ѹ����λ"),Pressure,_T("Pressure"))	
,m_Resistance(_T("������λ"),Resistance,_T("Resistance"))		
,m_Temperature(_T("�¶ȵ�λ"),Temperature,_T("Temperature"))
,m_Time(_T("ʱ�䵥λ"),Time,_T("Time"))	
,m_Torque(_T("ת�ص�λ"),Torque,_T("Torque"))		
,m_Velocity(_T("�ٶȵ�λ"),Velocity,_T("Velocity"))
,m_Viscosity(_T("ճ�ȵ�λ"),Viscosity,_T("Viscosity"))	
,m_Volume(_T("�����λ"),Volume,_T("Volume"))	
,m_VolumetricFlow(_T("���������λ"),VolumetricFlow,_T("VolumetricFlow"))	
,m_WeightperLength(_T("Weight per Length��λ"),WeightperLength,_T("WeightperLength"))
,m_PressPerMeter(_T("Press Per Meter��λ"),PressPerMeter,_T("PressPerMeter")) 
{
	InitArrayRef();
}

UnitSubSystem::UnitSubSystem(const UnitSubSystem &ref)
{
	InitArrayRef();
	Assigned(ref.m_arrayRef);
}

UnitSubSystem& UnitSubSystem::operator=(const UnitSubSystem &ref)
{
	//�ж��Ը�ֵ
	if(this == &ref)
		return *this;
    //���û��ำֵ
	//�ͷŶ��ڴ�
	//���·�����ڴ�
	//��ֵ
	InitArrayRef();
	Assigned(ref.m_arrayRef);
	return *this;
}

UnitSubSystem::~UnitSubSystem()
{
}

//ע�����еĵ�λ
void UnitSubSystem::InitArrayRef()
{
	m_arrayRef.SetSize(21);
	m_arrayRef.SetAt(0,&m_Area);
	m_arrayRef.SetAt(1,&m_Density);
	m_arrayRef.SetAt(2,&m_Diameter);
	m_arrayRef.SetAt(3,&m_HeadGradient);
	m_arrayRef.SetAt(4,&m_Inertia);
	m_arrayRef.SetAt(5,&m_Length);
	m_arrayRef.SetAt(6,&m_MassFlow);
	m_arrayRef.SetAt(7,&m_Mass);
	m_arrayRef.SetAt(8,&m_PercentFractional);
	m_arrayRef.SetAt(9,&m_Power);
	m_arrayRef.SetAt(10,&m_PressGradient);
	m_arrayRef.SetAt(11,&m_Pressure);
	m_arrayRef.SetAt(12,&m_Resistance);
	m_arrayRef.SetAt(13,&m_Temperature);
	m_arrayRef.SetAt(14,&m_Time);
	m_arrayRef.SetAt(15,&m_Torque);
	m_arrayRef.SetAt(16,&m_Velocity);
	m_arrayRef.SetAt(17,&m_Viscosity);
	m_arrayRef.SetAt(18,&m_Volume);
	m_arrayRef.SetAt(19,&m_VolumetricFlow);
	m_arrayRef.SetAt(20,&m_WeightperLength);
}

void UnitSubSystem::Init()
{
	TCHAR exeFullPath[MAX_PATH];
	::GetModuleFileName(NULL,exeFullPath,MAX_PATH);
	CString strPath(exeFullPath);
	int index = strPath.ReverseFind('\\');
	ASSERT(index != -1);
	strPath = strPath.Left(index+1);
	strPath += _T("QuantityConfig.txt");
	
	QuantityManager& qm = QuantityManager::Instance();
	qm.SetConfigFilePathCString( strPath );
	//string strTemp = strPath.GetBuffer( 0 );   // ԭ���ķ��������������Խ��
	//qm.SetConfigFilePath( strTemp );
	qm.Init();
	vector< UeStdString > set;
	UeStdString strdefault;
	UeStdString  strQuantity;
    vector<UeStdString>* pSetVector = NULL; 
	UnitType *pUnitType = NULL;
	for(int i=0;i<m_arrayRef.GetSize();i++)
	{
	    pUnitType = m_arrayRef.GetAt(i);
	    ASSERT(pUnitType != NULL);
	    set.clear();
	    strQuantity = pUnitType->GetStrID().GetBuffer(0);
	    pSetVector = qm.GetPFASet(strQuantity);
        vector< UeStdString >::iterator iter = pSetVector->begin();
	    for (;iter != pSetVector->end(); iter++)
	    {
		set.push_back(*iter);
	    }
		pSetVector = NULL;
	    qm.GetDefaultUnitString(strdefault,strQuantity);
	    pUnitType->InitSymbol(set);
	    pUnitType->SetCurSymbol(strdefault.c_str());
	    pUnitType->SetStdSymbol(strdefault.c_str());
		
	}
	
}

BOOL UnitSubSystem::FindUnit(UnitTypeID id,UnitType *&pUnitType)
{
	for(int i=0;i<m_arrayRef.GetSize();i++)
	{
		pUnitType = m_arrayRef.GetAt(i);
		ASSERT(pUnitType != NULL);
		if(id == pUnitType->GetTypeID())
		{
			return TRUE;
		}
	}
	return FALSE;
}

BOOL UnitSubSystem::FilterString(UnitTypeID id,CString strSymbol,BOOL bUsed)
{
	UnitType *pUnitType = NULL;
	if(FindUnit(id,pUnitType))
	{
		return pUnitType->FilterString(strSymbol,bUsed);
	}
	else
	{
		return FALSE;
	}
}
BOOL UnitSubSystem::SetDefUnitString(UnitTypeID id,CString strSymbol)
{
	UnitType *pUnitType = NULL;
	if(FindUnit(id,pUnitType))
	{
		pUnitType->SetCurSymbol(strSymbol);
		return TRUE;
	}
	else
	{
		return FALSE;
	}

}


UnitTypeArrayRef& UnitSubSystem::GetUnitArray()
{
	return m_arrayRef;
}

void UnitSubSystem::Assigned(const UnitTypeArrayRef &ref)
{
	UnitType *pUnitRef = NULL;
	UnitType *pUnitType = NULL;
	for(int i=0;i<ref.GetSize();i++)
	{
		pUnitRef = ref.GetAt(i);
		pUnitType = m_arrayRef.GetAt(i);
		ASSERT(pUnitType != NULL);
		ASSERT(pUnitRef != NULL);
		*pUnitType = *pUnitRef;	
	}
}

BOOL UnitSubSystem::FindSymbolArray(UnitTypeID id,SymbolArray &array)
{
	UnitType *pUnitType = NULL;
	if(FindUnit(id,pUnitType))
	{
		pUnitType->GetUsedArray(array);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
//�û������������ݵ�Ĭ�ϵ�λ��
CString UnitSubSystem::FindCurSymbol(UnitTypeID id)
{
	CString strRet;
	UnitType *pUnitType = NULL;
	if(FindUnit(id,pUnitType))
	{
		ASSERT(pUnitType != NULL);
		strRet = pUnitType->GetCurSymbol();
	}
	return strRet;
}
//����ʹ�õı�׼��λ
CString UnitSubSystem::FindStdSymbol(UnitTypeID id)
{
	CString strRet;
	UnitType *pUnitType = NULL;
	if(FindUnit(id,pUnitType))
	{
		ASSERT(pUnitType != NULL);
		strRet = pUnitType->GetStdSymbol();
	}
	return strRet;
}

double UnitSubSystem::StdToCur(UnitTypeID id,double d)
{
	CString strCurUnit = FindCurSymbol(id);
	return StdToSelUnit(d,strCurUnit);
}

double UnitSubSystem::StdToSelUnit(double d,CString strUnit)
{
	double dOut = 0.0;
	QuantityManager& qm = QuantityManager::Instance();
	if(!qm.TransformFromStd(dOut,strUnit.GetBuffer(0),d))
	{
		dOut = d;
	}
	return dOut;
}

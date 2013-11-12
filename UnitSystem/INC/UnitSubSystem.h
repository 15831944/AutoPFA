// UnitSubSystem.h: interface for the UnitSubSystem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UNITSUBSYSTEM_H__2E4301F3_5F41_4083_AEBA_DE6BB82F8053__INCLUDED_)
#define AFX_UNITSUBSYSTEM_H__2E4301F3_5F41_4083_AEBA_DE6BB82F8053__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "UnitType.h"
class QuantityManager;

typedef CArray<UnitType*,UnitType*>UnitTypeArrayRef;


class AFX_EXT_CLASS UnitSubSystem  
{
public:
	UnitSubSystem();
	UnitSubSystem(const UnitSubSystem &ref);
	UnitSubSystem& operator=(const UnitSubSystem &ref);
	virtual ~UnitSubSystem();

public:
	double StdToSelUnit(double d,CString strUnit);
	double StdToCur(UnitTypeID id,double d);
	CString FindCurSymbol(UnitTypeID id);
	CString FindStdSymbol(UnitTypeID id);
	BOOL FindSymbolArray(UnitTypeID id,SymbolArray &array);
	
	UnitTypeArrayRef& GetUnitArray();
	BOOL SetDefUnitString(UnitTypeID id,CString strSymbol);
	BOOL FilterString(UnitTypeID id,CString strSymbol,BOOL bUsed);
	void Init();
	BOOL FindUnit(UnitTypeID id,UnitType *&pUnitType);

	

private:
	void Assigned(const UnitTypeArrayRef &ref);
	void InitArrayRef();
	UnitType m_Area;			//�����λ
	UnitType m_Density;			//�ܶȵ�λ
	UnitType m_Diameter;		//ֱ����λ
	UnitType m_HeadGradient;	//ˮͷ�¶ȵ�λ
	UnitType m_Inertia;			//���Ե�λ
	UnitType m_Length;			//���ȵ�λ
	UnitType m_MassFlow;		//����������λ
	UnitType m_Mass;			//������λ
	UnitType m_PercentFractional;  //�ٷ���/С��
	UnitType m_Power;			//���ʵ�λ
	UnitType m_PressGradient;	//Pressure Gradient��λ
	UnitType m_Pressure;		//ѹ����λ
	UnitType m_Resistance;		//������λ
	UnitType m_Temperature;		//�¶ȵ�λ
	UnitType m_Time;			//ʱ�䵥λ
	UnitType m_Torque;			//ת�ص�λ
	UnitType m_Velocity;		//�ٶȵ�λ
	UnitType m_Viscosity;		//�˶�ճ�ȵ�λ
	UnitType m_Volume;			//�����λ
	UnitType m_VolumetricFlow;	//���������λ
	UnitType m_WeightperLength; //Weight per Length��λ
	UnitType m_PressPerMeter;
  
    UnitTypeArrayRef m_arrayRef;
};

#endif // !defined(AFX_UNITSUBSYSTEM_H__2E4301F3_5F41_4083_AEBA_DE6BB82F8053__INCLUDED_)

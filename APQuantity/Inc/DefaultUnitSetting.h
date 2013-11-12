// DefaultUnitSetting.h: interface for the DefaultUnitSetting class.
//
//////////////////////////////////////////////////////////////////////
/*************************************************
	Copyright (C), 1988-2006, UESOFT Co., Ltd.
	File name:DefaultUnitSetting.h
	Author:���(lobby)
	Version:1.0
	Date:2006.12.05
	Description:��������һ�����̵�Ĭ�ϵ�λ����
	Function List:  
    1. int GetXXXDefaultUnit() const
	���ظù�����XXX��������Ĭ�ϵ�λ����
	2. void SetXXXDefaultUnit( int nUnit)
	����һ��int�ͱ�����Ϊ������
	���øù�����XXX��λ��Ĭ�ϵ�λ����
	3. void SetXXXDefaultUnit(const StdString& strUnit)
	����һ���ַ���������Ϊ������
	���øù�����XXX��λ��Ĭ�ϵ�λ����
	����������ʹ�÷����������ж�����̣��϶���ĳ����A�Ķ���������
	һ�����̣�����A��Ӧ����һ��DefaultUnitSetting��Ա���󡣶�����
	���þ��Ƕ��������̵����á�
*************************************************/
#if !defined(AFX_DEFAULTUNITSETTING_H__C61FF3F0_E614_47AD_A710_611FD45091A5__INCLUDED_)
#define AFX_DEFAULTUNITSETTING_H__C61FF3F0_E614_47AD_A710_611FD45091A5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "unithead.h"
#include "Quantity_share.h"

class QUANTITY_API DefaultUnitSetting  
{
public:
	DefaultUnitSetting();
	virtual ~DefaultUnitSetting();

public:
	int GetAngleDefaultUnit() const
	{
		return this->m_nAngleDefaultUnit;
	}
	int GetAreaDefaultUnit() const
	{
		return this->m_nAreaDefaultUnit;
	}
	int GetDensityDefaultUnit() const
	{
		return this->m_nDensityDefaultUnit;
	}
	int GetForceDefaultUnit() const
	{
		return this->m_nForceDefaultUnit;
	}
	int GetLengthDefaultUnit() const
	{
		return this->m_nLengthDefaultUnit;
	}
	int GetMassDefaultUnit() const
	{
		return this->m_nMassDefaultUnit;
	}
	int GetPowerDefaultUnit() const
	{
		return this->m_nPowerDefaultUnit;
	}
	int GetPressureDefaultUnit() const
	{
		return this->m_nPressureDefaultUnit;
	}
	int GetSpeedDefaultUnit() const
	{
		return this->m_nSpeedDefaultUnit;
	}
	int GetTemperatureDefaultUnit() const
	{
		return this->m_nTemperatureDefaultUnit;
	}
	int GetTimeDefaultUnit() const
	{
		return this->m_nTimeDefaultUnit;
	}
	int GetVolumnDefaultUnit() const
	{
		return this->m_nVolumnDefaultUnit;
	}
	int GetWorkDefaultUnit() const
	{
		return this->m_nWorkDefaultUnit;
	}

	void SetAngleDefaultUnit( int nUnit )
	{
		ASSERT( nUnit >= 0 && nUnit < ANGLE_UNIT_NUM );
		this->m_nAngleDefaultUnit = nUnit;
	}
	void SetAreaDefaultUnit( int nUnit )
	{
		ASSERT( nUnit >= 0 && nUnit < AREA_UNIT_NUM );
		this->m_nAreaDefaultUnit = nUnit;
	}
	void SetDensityDefaultUnit( int nUnit )
	{
		ASSERT( nUnit >= 0 && nUnit < DENSITY_UNIT_NUM );
		this->m_nDensityDefaultUnit = nUnit;
	}
	void SetForceDefaultUnit( int nUnit )
	{
		ASSERT( nUnit >= 0 && nUnit < FORCE_UNIT_NUM );
		this->m_nForceDefaultUnit = nUnit;
	}
	void SetLengthDefaultUnit( int nUnit )
	{
		ASSERT( nUnit >= 0 && nUnit < LENGTH_UNIT_NUM );
		this->m_nLengthDefaultUnit = nUnit;
	}
	void SetMassDefaultUnit( int nUnit )
	{
		ASSERT( nUnit >= 0 && nUnit < MASS_UNIT_NUM );
		this->m_nMassDefaultUnit = nUnit;
	}
	void SetPowerDefaultUnit( int nUnit )
	{
		ASSERT( nUnit >= 0 && nUnit < POWER_UNIT_NUM );
		this->m_nPowerDefaultUnit = nUnit;
	}
	void SetPressureDefaultUnit( int nUnit )
	{
		ASSERT( nUnit >= 0 && nUnit < PRESSURE_UNIT_NUM );
		this->m_nPressureDefaultUnit = nUnit;
	}
	void SetSpeedDefaultUnit( int nUnit )
	{
		ASSERT( nUnit >= 0 && nUnit < SPEED_UNIT_NUM );
		this->m_nSpeedDefaultUnit = nUnit;
	}
	void SetTemperatureDefaultUnit( int nUnit )
	{
		ASSERT( nUnit >= 0 && nUnit < TEMPERATURE_UNIT_NUM );
		this->m_nTemperatureDefaultUnit = nUnit;
	}
	void SetTimeDefaultUnit( int nUnit )
	{
		ASSERT( nUnit >= 0 && nUnit < TIME_UNIT_NUM );
		this->m_nTimeDefaultUnit = nUnit;
	}
	void SetVolumnDefaultUnit( int nUnit )
	{
		ASSERT( nUnit >= 0 && nUnit < VOLUMN_UNIT_NUM );
		this->m_nVolumnDefaultUnit = nUnit;
	}
	void SetWorkDefaultUnit( int nUnit )
	{
		ASSERT( nUnit >= 0 && nUnit < WORK_UNIT_NUM );
		this->m_nWorkDefaultUnit = nUnit;
	}



	void SetAngleDefaultUnit( const StdString& strUnit )
	{
		int nUnit = AngleTrans::UnitStringToUnitClass( strUnit );
		ASSERT( nUnit >= 0 && nUnit < ANGLE_UNIT_NUM );
		this->m_nAngleDefaultUnit = nUnit;
	}
	void SetAreaDefaultUnit( const StdString& strUnit )
	{
		int nUnit = AreaTrans::UnitStringToUnitClass( strUnit );
		ASSERT( nUnit >= 0 && nUnit < AREA_UNIT_NUM );
		this->m_nAreaDefaultUnit = nUnit;
	}
	void SetDensityDefaultUnit( const StdString& strUnit )
	{
		int nUnit = DensityTrans::UnitStringToUnitClass( strUnit );
		ASSERT( nUnit >= 0 && nUnit < DENSITY_UNIT_NUM );
		this->m_nDensityDefaultUnit = nUnit;
	}
	void SetForceDefaultUnit( const StdString& strUnit )
	{
		int nUnit = ForceTrans::UnitStringToUnitClass( strUnit );
		ASSERT( nUnit >= 0 && nUnit < FORCE_UNIT_NUM );
		this->m_nForceDefaultUnit = nUnit;
	}
	void SetLengthDefaultUnit( const StdString& strUnit )
	{
		int nUnit = LengthTrans::UnitStringToUnitClass( strUnit );
		ASSERT( nUnit >= 0 && nUnit < LENGTH_UNIT_NUM );
		this->m_nLengthDefaultUnit = nUnit;
	}
	void SetMassDefaultUnit( const StdString& strUnit )
	{
		int nUnit = MassTrans::UnitStringToUnitClass( strUnit );
		ASSERT( nUnit >= 0 && nUnit < MASS_UNIT_NUM );
		this->m_nMassDefaultUnit = nUnit;
	}
	void SetPowerDefaultUnit( const StdString& strUnit )
	{
		int nUnit = PowerTrans::UnitStringToUnitClass( strUnit );
		ASSERT( nUnit >= 0 && nUnit < POWER_UNIT_NUM );
		this->m_nPowerDefaultUnit = nUnit;
	}
	void SetPressureDefaultUnit( const StdString& strUnit )
	{
		int nUnit = PressureTrans::UnitStringToUnitClass( strUnit );
		ASSERT( nUnit >= 0 && nUnit < PRESSURE_UNIT_NUM );
		this->m_nPressureDefaultUnit = nUnit;
	}
	void SetSpeedDefaultUnit( const StdString& strUnit )
	{
		int nUnit = SpeedTrans::UnitStringToUnitClass( strUnit );
		ASSERT( nUnit >= 0 && nUnit < SPEED_UNIT_NUM );
		this->m_nSpeedDefaultUnit = nUnit;
	}
	void SetTemperatureDefaultUnit( const StdString& strUnit )
	{
		int nUnit = TemperatureTrans::UnitStringToUnitClass( strUnit );
		ASSERT( nUnit >= 0 && nUnit < TEMPERATURE_UNIT_NUM );
		this->m_nTemperatureDefaultUnit = nUnit;
	}
	void SetTimeDefaultUnit( const StdString& strUnit )
	{
		int nUnit = TimeTrans::UnitStringToUnitClass( strUnit );
		ASSERT( nUnit >= 0 && nUnit < TIME_UNIT_NUM );
		this->m_nTimeDefaultUnit = nUnit;
	}
	void SetVolumnDefaultUnit( const StdString& strUnit )
	{
		int nUnit = VolumnTrans::UnitStringToUnitClass( strUnit );
		ASSERT( nUnit >= 0 && nUnit < VOLUMN_UNIT_NUM );
		this->m_nVolumnDefaultUnit = nUnit;
	}
	void SetWorkDefaultUnit( const StdString& strUnit )
	{
		int nUnit = WorkTrans::UnitStringToUnitClass( strUnit );
		ASSERT( nUnit >= 0 && nUnit < WORK_UNIT_NUM );
		this->m_nWorkDefaultUnit = nUnit;
	}
private:
	int m_nAngleDefaultUnit;
	int m_nAreaDefaultUnit;
	int m_nDensityDefaultUnit;
	int m_nForceDefaultUnit;
	int m_nLengthDefaultUnit;
	int m_nMassDefaultUnit;
	int m_nPowerDefaultUnit;
	int m_nPressureDefaultUnit;
	int m_nSpeedDefaultUnit;
	int m_nTemperatureDefaultUnit;
	int m_nTimeDefaultUnit;
	int m_nVolumnDefaultUnit;
	int m_nWorkDefaultUnit;

};

#endif // !defined(AFX_DEFAULTUNITSETTING_H__C61FF3F0_E614_47AD_A710_611FD45091A5__INCLUDED_)

#include "StdAfx.h"
#include "PressureTrans.h"
#include <assert.h>

/*
SIStd�����������ǡ����ʱ�׼��
*/

/****************************************************
pressureTransRatio��̬�����ŵ���ѹǿ�����������õ�
�����е�λ���׼��λ֮��ı�����ϵ��
****************************************************/

IMPLEMENT_UNITSTRING( PressureTrans );

double PressureTrans::pressureTransRatio[PRESSURE_UNIT_NUM]
					= {1.0,1000.0,1000000.0
					,9.80665,98066.5,100000.0
					,101325,9.80665,133.322
					,6894.76,6894.76,1E+9,9.80665E+10,47.88};

const StdString PressureTrans::UnitStringArray[PRESSURE_UNIT_NUM]
					={_T("Pa"),_T("KPa"),_T("MPa"),_T("kgf/m_2"),_T("kgf/cm_2"),_T("bar"),
					_T("atm"),_T("mmH2o"),_T("mmHg"),_T("psi"),_T("lb/sq.in"),_T("kN/mm_2"),
					_T("1E+6kgf/cm_2"),_T("lb/sq.ft")};


/*************************************************
  Function: TransFromStd
  Description:�����������������ĵ�λ���׼��λ֮��ı�����ϵ
  Calls:��
  Called By:      // ���ñ������ĺ����嵥
  Table Accessed: ��
  Table Updated: ��
  Input: PressureUnit desUnit,����һ��ѹǿ��λ���ͣ�
  ��������ȷ���뷶Χ��0-9�������߽磩
  Output: ��
  Return: ���ر�����ϵ��һ��double������
  Others: ��
*************************************************/

double PressureTrans::TransFromStd( int desUnit)
{
	//ASSERT(desUnit >= 0 && desUnit <= 8);
	if (desUnit >= 0 && desUnit <= PRESSURE_UNIT_NUM - 1)
	{
		return 1.0/PressureTrans::pressureTransRatio[desUnit];
	}
	else
	{
		assert(0);
		return 0;
	}
}

/*************************************************
  Function: TransToStd
  Description:���ر�׼��λ���������������ĵ�λ֮��ı�����ϵ
  Calls:��
  Called By:      // ���ñ������ĺ����嵥
  Table Accessed: ��
  Table Updated: ��
  Input: LengthUnit orgUnit,����һ��ѹǿ��λ���ͣ�
  ��������ȷ���뷶Χ��0-9�������߽磩
  Output: ��
  Return: ���ر�����ϵ��һ��double������
  Others: ��
*************************************************/

double PressureTrans::TransToStd( int orgUnit)
{
	//ASSERT(orgUnit >= 0 && orgUnit <= 8);
	if (orgUnit >= 0 && orgUnit <= PRESSURE_UNIT_NUM - 1)
	{
		return PressureTrans::pressureTransRatio[orgUnit];
	}
	else
	{
		assert(0);
		return 0;
	}
}

/*************************************************
  Function: IsSIStd
  Description:�����������������ĵ�λ�Ƿ�Ϊ��������
  �ı�׼��λ
  Calls:��
  Called By:      // ���ñ������ĺ����嵥
  Table Accessed: ��
  Table Updated: ��
  Input: PressureUnit orgUnit,����һ��ѹǿ��λ���ͣ�
  ��������ȷ���뷶Χ��0-9�������߽磩
  Output: ��
  Return: ��������
  Others: ��
*************************************************/

bool PressureTrans::IsSIStd( int orgUnit)
{
	if (orgUnit == PRESSURE_STD_UNIT)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*************************************************
  Function: UnitClassToUnitString
  Description:�����������������ĵ�λ����
  ����Ӧ�ĵ�λ�����ַ���
  Calls:��
  Called By:   
  Table Accessed: ��
  Table Updated: ��
  Input: int UnitClass,����һ����λ����
  Output: ��
  Return: ��Ӧ�ĵ�λ�����ַ���
  Others: ��
*************************************************/

const StdString& PressureTrans::UnitClassToUnitString(int UnitClass)
{
	assert(UnitClass >= 0 && UnitClass <= PRESSURE_UNIT_NUM - 1);
	return PressureTrans::UnitStringArray[UnitClass];
}

/*************************************************
  Function: UnitStringToUnitClass
  Description:�����������������ĵ�λ�����ַ���
  ����Ӧ�ĵ�λ����
  Calls:��
  Called By:  Quantity(T data,const string currentunitstring) 
  Table Accessed: ��
  Table Updated: ��
  Input: const string UnitString,����һ����λ�����ַ�����
  Output: ��
  Return: ��Ӧ�ĵ�λ����
  Others: ��
*************************************************/

int PressureTrans::UnitStringToUnitClass(const StdString& UnitString)
{
	for (int i = 0; i < PRESSURE_UNIT_NUM; i++)
	{
		if (UnitString.CompareNoCase( PressureTrans::UnitStringArray[i] ) == 0 )
		{
			return i;
		}
	}
	assert(0);
	return -1;
}

/****************************************************
UnitStringArray��̬�����ŵ��ǵ�λ�����ַ�����
****************************************************/


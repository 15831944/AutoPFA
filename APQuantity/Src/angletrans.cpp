#include "StdAfx.h"
#include "AngleTrans.h"
#include "assert.h"

/*
SIStd�����������ǡ����ʱ�׼��
*/

/****************************************************
angleTransRatio��̬�����ŵ��ǽǶ������������õ�
�����е�λ���׼��λ֮��ı�����ϵ��
****************************************************/

double AngleTrans::angleTransRatio[ANGLE_UNIT_NUM]
					= {0.017453292,2.909/10000.0
					,4.848/1000000.0,1
					,6.283};

/****************************************************
UnitStringArray��̬�����ŵ��ǵ�λ�����ַ�����
****************************************************/

const StdString AngleTrans::UnitStringArray[ANGLE_UNIT_NUM]
					= {_T("deg"),_T("sec"),_T("min"),_T("rad")
					,_T("rotation")};

IMPLEMENT_UNITSTRING( AngleTrans );
/*************************************************
  Function: TransFromStd
  Description:�����������������ĵ�λ���׼��λ֮��ı�����ϵ
  Calls:��
  Called By:      
  Table Accessed: ��
  Table Updated: ��
  Input: int desUnit,����һ���Ƕȵ�λ���ͣ�
  ��������ȷ���뷶Χ��0-4�������߽磩
  Output: ��
  Return: ���ر�����ϵ��һ��double������
  Others: ��
*************************************************/

double AngleTrans::TransFromStd( int desUnit )
{
	if (desUnit >= 0 && desUnit <= ANGLE_UNIT_NUM - 1)
	{
		return 1.0/AngleTrans::angleTransRatio[desUnit];
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
  Called By:      Quantity(T data,const int currentunit)
  Table Accessed: ��
  Table Updated: ��
  Input: int orgUnit,����һ���Ƕȵ�λ���ͣ�
  ��������ȷ���뷶Χ��0-4�������߽磩
  Output: ��
  Return: ���ر�����ϵ��һ��double������
  Others: ��
*************************************************/

double AngleTrans::TransToStd( int orgUnit )
{
	if (orgUnit >= 0 && orgUnit <= ANGLE_UNIT_NUM - 1)
	{
		return AngleTrans::angleTransRatio[orgUnit];
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
  Called By:      
  Table Accessed: ��
  Table Updated: ��
  Input: int orgUnit,����һ���Ƕȵ�λ���ͣ�
  ��������ȷ���뷶Χ��0-4�������߽磩
  Output: ��
  Return: ��������
  Others: ��
*************************************************/

bool AngleTrans::IsSIStd( int orgUnit )
{
	if (orgUnit == ANGLE_STD_UNIT)
	{
		return true;
	}
	else
	{
		return false;
	}
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

int AngleTrans::UnitStringToUnitClass(const StdString& UnitString)
{
	for (int i = 0;i < ANGLE_UNIT_NUM;i++)
	{
		if ( UnitString.CompareNoCase( AngleTrans::UnitStringArray[i] ) == 0 )
		{
			return i;
		}
	}
	assert(0);
	return -1;
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

const StdString& AngleTrans::UnitClassToUnitString(int UnitClass)
{
	assert(UnitClass >= 0 && UnitClass <= ANGLE_UNIT_NUM - 1);
	return AngleTrans::UnitStringArray[UnitClass];
}

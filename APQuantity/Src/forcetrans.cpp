#include "StdAfx.h"
#include "ForceTrans.h"
#include <assert.h>

/*
SIStd�����������ǡ����ʱ�׼��
*/

/****************************************************
forceTransRatio��̬�����ŵ����������������õ�
�����е�λ���׼��λ֮��ı�����ϵ��
****************************************************/

double ForceTrans::forceTransRatio[FORCE_UNIT_NUM]
					= {1.0,9.807/1000.0,9.80665
					,4.448,1.0/100000.0,4.44822};

/****************************************************
UnitStringArray��̬�����ŵ��ǵ�λ�����ַ�����
****************************************************/

const StdString ForceTrans::UnitStringArray[FORCE_UNIT_NUM]
					={_T("N"),_T("gf"),_T("kgf"),_T("lbf"),_T("dyn"),_T("lb")};

IMPLEMENT_UNITSTRING( ForceTrans );
/*************************************************
  Function: TransFromStd
  Description:�����������������ĵ�λ���׼��λ֮��ı�����ϵ
  Calls:��
  Called By:      
  Table Accessed: ��
  Table Updated: ��
  Input: int desUnit,����һ������λ���ͣ�
  ��������ȷ���뷶Χ��0-4�������߽磩
  Output: ��
  Return: ���ر�����ϵ��һ��double������
  Others: ��
*************************************************/

double ForceTrans::TransFromStd( int desUnit)
{
	//ASSERT(desUnit >= 0 && desUnit <= 8);
	if (desUnit >= 0 && desUnit <= FORCE_UNIT_NUM - 1)
	{
		return 1.0/ForceTrans::forceTransRatio[desUnit];
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
  Input: int orgUnit,����һ�����ȵ�λ���ͣ�
  ��������ȷ���뷶Χ��0-4�������߽磩
  Output: ��
  Return: ���ر�����ϵ��һ��double������
  Others: ��
*************************************************/

double ForceTrans::TransToStd( int orgUnit)
{
	//ASSERT(orgUnit >= 0 && orgUnit <= 8);
	if (orgUnit >= 0 && orgUnit <= FORCE_UNIT_NUM - 1)
	{
		return ForceTrans::forceTransRatio[orgUnit];
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
  Input: int orgUnit,����һ������λ���ͣ�
  ��������ȷ���뷶Χ��0-4�������߽磩
  Output: ��
  Return: ��������
  Others: ��
*************************************************/

bool ForceTrans::IsSIStd( int orgUnit)
{
	if (orgUnit == FORCE_STD_UNIT)
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

const StdString& ForceTrans::UnitClassToUnitString(int UnitClass)
{
	assert(UnitClass >= 0 && UnitClass <= FORCE_UNIT_NUM - 1);
	return ForceTrans::UnitStringArray[UnitClass];
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

int ForceTrans::UnitStringToUnitClass(const StdString& UnitString)
{
	for (int i = 0; i < FORCE_UNIT_NUM; i++)
	{
		if (UnitString.CompareNoCase( ForceTrans::UnitStringArray[i] ) == 0 )
		{
			return i;
		}
	}
	assert(0);
	return -1;
}
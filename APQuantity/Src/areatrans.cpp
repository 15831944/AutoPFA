#include "StdAfx.h"
#include "AreaTrans.h"
#include <assert.h>

/*
SIStd�����������ǡ����ʱ�׼��
*/

/****************************************************
areaTransRatio��̬�����ŵ�����������������õ�
�����е�λ���׼��λ֮��ı�����ϵ��
****************************************************/

double AreaTrans::areaTransRatio[AREA_UNIT_NUM]
					= {1.0,0.01
					,1.0/10000.0,0.0929
					,0.8361274,6.452/10000.0,1.0/1000000};

/****************************************************
UnitStringArray��̬�����ŵ��ǵ�λ�����ַ�����
****************************************************/

const StdString AreaTrans::UnitStringArray[AREA_UNIT_NUM]
					= {_T("m_2"),_T("dm_2"),_T("cm_2"),_T("ft_2")
					,_T("yd_2"),_T("in_2"),_T("mm_2")};

IMPLEMENT_UNITSTRING( AreaTrans );
/*************************************************
  Function: TransFromStd
  Description:�����������������ĵ�λ���׼��λ֮��ı�����ϵ
  Calls:��
  Called By:      
  Table Accessed: ��
  Table Updated: ��
  Input: int desUnit,����һ�������λ���ͣ�
  ��������ȷ���뷶Χ��0-5�������߽磩
  Output: ��
  Return: ���ر�����ϵ��һ��double������
  Others: ��
*************************************************/

double AreaTrans::TransFromStd( int desUnit)
{
	//ASSERT(desUnit >= 0 && desUnit <= 8);
	if (desUnit >= 0 && desUnit <= AREA_UNIT_NUM - 1)
	{
		return 1.0/AreaTrans::areaTransRatio[desUnit];
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
  Called By:      Quantity(T data,const string currentunitstring)
  Table Accessed: ��
  Table Updated: ��
  Input: int orgUnit,����һ�������λ���ͣ�
  ��������ȷ���뷶Χ��0-5�������߽磩
  Output: ��
  Return: ���ر�����ϵ��һ��double������
  Others: ��
*************************************************/

double AreaTrans::TransToStd( int orgUnit)
{
	//ASSERT(orgUnit >= 0 && orgUnit <= 8);
	if (orgUnit >= 0 && orgUnit <= AREA_UNIT_NUM - 1)
	{
		return AreaTrans::areaTransRatio[orgUnit];
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
  Input: int orgUnit,����һ�������λ���ͣ�
  ��������ȷ���뷶Χ��0-5�������߽磩
  Output: ��
  Return: ��������
  Others: ��
*************************************************/

bool AreaTrans::IsSIStd( int orgUnit)
{
	if (orgUnit == AREA_STD_UNIT)
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

int AreaTrans::UnitStringToUnitClass(const StdString& UnitString)
{
	for (int i = 0;i < AREA_UNIT_NUM;i++)
	{
		if ( UnitString.CompareNoCase( AreaTrans::UnitStringArray[i] ) == 0 )
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

const StdString& AreaTrans::UnitClassToUnitString(int UnitClass)
{
	assert(UnitClass >= 0 && UnitClass <= AREA_UNIT_NUM - 1);
	return AreaTrans::UnitStringArray[UnitClass];
}


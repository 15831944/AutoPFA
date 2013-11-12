#include "StdAfx.h"
#include "LengthTrans.h"
#include <assert.h>

/*
SIStd�����������ǡ����ʱ�׼��
*/

/****************************************************
lengthTransRatio��̬�����ŵ��ǳ��������������õ�
�����е�λ���׼��λ֮��ı�����ϵ��
****************************************************/

double LengthTrans::lengthTransRatio[LENGTH_UNIT_NUM]
					= {0.001,0.01,0.1,1,1000,0.0254
					,0.3048,0.9144,1609.344};

/****************************************************
UnitStringArray��̬�����ŵ��ǵ�λ�����ַ�����
****************************************************/

const StdString	LengthTrans::UnitStringArray[LENGTH_UNIT_NUM]
					={_T("mm"),_T("cm"),_T("dm"),_T("m"),_T("km"),_T("in")
					,_T("ft"),_T("yd"),_T("mile")};

IMPLEMENT_UNITSTRING( LengthTrans );
/*************************************************
  Function: TransFromStd
  Description:�����������������ĵ�λ���׼��λ֮��ı�����ϵ
  Calls:��
  Called By:      // ���ñ������ĺ����嵥
  Table Accessed: ��
  Table Updated: ��
  Input: LengthUnit desUnit,����һ�����ȵ�λ���ͣ�
  ��������ȷ���뷶Χ��0-8�������߽磩
  Output: ��
  Return: ���ر�����ϵ��һ��double������
  Others: ��
*************************************************/

double LengthTrans::TransFromStd( int desUnit)
{
	//ASSERT(desUnit >= 0 && desUnit <= 8);
	if (desUnit >= 0 && desUnit <= LENGTH_UNIT_NUM - 1)
	{
		return 1.0/LengthTrans::lengthTransRatio[desUnit];
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
  Input: LengthUnit orgUnit,����һ�����ȵ�λ���ͣ�
  ��������ȷ���뷶Χ��0-8�������߽磩
  Output: ��
  Return: ���ر�����ϵ��һ��double������
  Others: ��
*************************************************/

double LengthTrans::TransToStd( int orgUnit)
{
	//ASSERT(orgUnit >= 0 && orgUnit <= 8);
	if (orgUnit >= 0 && orgUnit <= LENGTH_UNIT_NUM - 1)
	{
		return LengthTrans::lengthTransRatio[orgUnit];
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
  Input: LengthUnit orgUnit,����һ�����ȵ�λ���ͣ�
  ��������ȷ���뷶Χ��0-8�������߽磩
  Output: ��
  Return: ��������
  Others: ��
*************************************************/

bool LengthTrans::IsSIStd( int orgUnit)
{
	if (orgUnit == LENGTH_STD_UNIT)
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

const StdString& LengthTrans::UnitClassToUnitString(int UnitClass)
{
	assert(UnitClass >= 0 && UnitClass <= LENGTH_UNIT_NUM - 1);
	return LengthTrans::UnitStringArray[UnitClass];
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

int LengthTrans::UnitStringToUnitClass(const StdString& UnitString)
{
	for (int i = 0;i < LENGTH_UNIT_NUM;i++)
	{
		if (UnitString.CompareNoCase( LengthTrans::UnitStringArray[i] ) == 0 )
		{
			return i;
		}
	}
	assert(0);
	return -1;
}

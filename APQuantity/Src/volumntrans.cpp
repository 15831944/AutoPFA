#include "StdAfx.h"
#include "VolumnTrans.h"
#include <assert.h>
/*
SIStd��������// ���ǡ����ʱ�׼��
*/

/****************************************************
volumnTransRatio��̬�����ŵ�����������������õ�
�����е�λ���׼��λ֮��ı�����ϵ��
****************************************************/

double VolumnTrans::volumnTransRatio[VOLUMN_UNIT_NUM]
					= {1.0,1.0/100000.0
					,1.0/1000.0,3.785/1000.0
					,4.546/1000.0,0.02832,1.639/100000.0};

/****************************************************
UnitStringArray��̬�����ŵ��ǵ�λ�����ַ�����
****************************************************/

const StdString VolumnTrans::UnitStringArray[VOLUMN_UNIT_NUM]
					={	"m_3",_T("cm_3"),_T("litre"),_T("gallon_a"),
					_T("gallon_e"),_T("ft_3"),_T("in_3")};

IMPLEMENT_UNITSTRING( VolumnTrans );
/*************************************************
  Function: TransFromStd
  Description:�����������������ĵ�λ���׼��λ֮��ı�����ϵ
  Calls:��
  Called By:      
  Table Accessed: ��
  Table Updated: ��
  Input: int desUnit,����һ�������λ���ͣ�
  ��������ȷ���뷶Χ��0-6�������߽磩
  Output: ��
  Return: ���ر�����ϵ��һ��double������
  Others: ��
*************************************************/

double VolumnTrans::TransFromStd( int desUnit)
{
	//ASSERT(desUnit >= 0 && desUnit <= 8);
	if (desUnit >= 0 && desUnit <= VOLUMN_UNIT_NUM -1)
	{
		return 1.0/VolumnTrans::volumnTransRatio[desUnit];
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
  Called By:   Quantity(T data,const int currentunit)
  Table Accessed: ��
  Table Updated: ��
  Input: int orgUnit,����һ�������λ���ͣ�
  ��������ȷ���뷶Χ��0-6�������߽磩
  Output: ��
  Return: ���ر�����ϵ��һ��double������
  Others: ��
*************************************************/

double VolumnTrans::TransToStd( int orgUnit)
{
	if (orgUnit >= 0 && orgUnit <= VOLUMN_UNIT_NUM -1)
	{
		return VolumnTrans::volumnTransRatio[orgUnit];
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
  ��������ȷ���뷶Χ��0-6�������߽磩
  Output: ��
  Return: ��������
  Others: ��
*************************************************/

bool VolumnTrans::IsSIStd( int orgUnit)
{
	if (orgUnit == VOLUMN_STD_UNIT)
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

int VolumnTrans::UnitStringToUnitClass(const StdString& UnitString)
{
	for (int i = 0; i < VOLUMN_UNIT_NUM; i++)
	{
		if (UnitString.CompareNoCase( VolumnTrans::UnitStringArray[i] ) == 0 )
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

const StdString& VolumnTrans::UnitClassToUnitString(int UnitClass)
{
	assert(UnitClass >= 0 && UnitClass <= VOLUMN_STD_UNIT - 1);
	return VolumnTrans::UnitStringArray[UnitClass];
}
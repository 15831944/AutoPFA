/*************************************************
  Copyright (C), 2005-2006, UESOFT Co., Ltd.
  File name:      // DensityTrans
  Author:         // chenyong
  Date:           // 2006-8-1
  Description:    // �˳����ļ���ɵ���Ҫ���ܽ�����λ�µ��¶����׼�¶��໥ת��
                  // ��Ҫ���ⲿͳһ�¶ȵ�λ����
                  // 
  Function List:  // ��Ҫ�����б�
    1. TransToStd(const double, const temperatureUnit) ���¶ȵĳ��õ�λ�µ�ֵת��ΪSI�Ʊ�׼�¶ȵ�λ��Ӧֵ
	2. TransFromStd(const double, const temperatureUnit) ��SI�Ʊ�׼�¶ȵ�λ�µ�ֵת��Ϊ�¶ȵĳ��õ�λ��Ӧֵ
	3. IsSIStd(const temperatureUnit) �жϵ�ǰ���¶ȵ�λ�Ƿ���SI�Ʊ�׼��λ������
 *************************************************/

#include "StdAfx.h"
#include "TemperatureTrans.h"
#include <assert.h>

IMPLEMENT_UNITSTRING( TemperatureTrans );
bool TemperatureTrans::IsSIStd( int orgUnit)
{
	return (orgUnit == TEMPERATURE_STD_UNIT)?true:false;
}

/*************************************************
  Function:       // TransToStd
  Description:    // �������¶ȵ�λ��Ӧֵת��ΪSI��׼��λ�¶�Ӧ��ֵ
  Input:          
		double orgvalue ��ǰ��λ�µ�ֵ
		temperatureUnit orgUnit ��ǰ��λ
  Output:         // 
  Return:         // ���ض�Ӧ�����ĵ�λ�µ�ֵ
*************************************************/
double TemperatureTrans::TemperatureTransToStd( double orgvalue,int orgUnit)
{
	switch (orgUnit)
	{
	case 0:
		//�����϶�ת��Ϊ���϶�,������ת�����ֵ
		//return orgvalue + 273.15;
		return orgvalue;
	case 1:
		//�����϶�ת��Ϊ���϶�,������ת�����ֵ
		//return 5.0 / 9 * (orgvalue + 459.67);
		return ( orgvalue - 32 ) / 1.8;
	case 2:
		//�����Ϣ� ��ת��Ϊ���϶�,������ת�����ֵ
		//return 5.0 / 9 * orgvalue;
		return ( orgvalue - 491.67 ) / 1.8;
	case 3:
		//��������ת��Ϊ���϶�,������ת�����ֵ
		return orgvalue - 273.15;
	default:
		assert(0);
		return SPECIAL;
	}
}


/*************************************************
  Function:       // TransToStd
  Description:    // ��SI��׼��λ�¶�Ӧ��ֵת��Ϊ�����¶ȵ�λ��Ӧֵ
  Input:          
		double orgvalue IS��λ�µ�ֵ
		temperatureUnit orgUnit ת���Ķ�Ӧ��λ
  Output:         // 
  Return:         // ���ض�Ӧת����λ�µ�ֵ
*************************************************/
double TemperatureTrans::TemperatureTransFromStd(double orgvalue,int orgUnit)
{
	switch (orgUnit)
	{
	case 0:
		//return orgvalue - 273.15;
		return orgvalue;
	case 1:
		//�����϶�ת��Ϊ���϶�,������ת�����ֵ
		//return 9.0 / 5 * orgvalue - 459.67;
		return 1.8 * orgvalue + 32;
	case 2:
		//�����϶�ת��Ϊ���Ϣ� ��,������ת�����ֵ
		//return 9 / 5.0 * orgvalue;
		return 1.8 * orgvalue + 491.67;
	case 3:
		//��ת��Ϊ������,������ת�����ֵ
		return orgvalue + 273.15;
	default:
		assert(0);
		return SPECIAL;
	}
}

double TemperatureTrans::TransFromStd( int orgUnit)
{
	assert(0);
	return 0;
}

double TemperatureTrans::TransToStd( int orgUnit)
{
	assert(0);
	return 0;
}

int TemperatureTrans::UnitStringToUnitClass(const StdString& UnitString)
{
	for (int i = 0; i < TEMPERATURE_UNIT_NUM; i++)
	{
		if (UnitString.CompareNoCase( TemperatureTrans::UnitStringArray[i] ) == 0 )
		{
			return i;
		}
	}
	assert(0);
	return -1;
}

const StdString& TemperatureTrans::UnitClassToUnitString(int UnitClass)
{
	assert(UnitClass >= 0 && UnitClass <= TEMPERATURE_UNIT_NUM - 1);
	return TemperatureTrans::UnitStringArray[UnitClass];
}

const StdString TemperatureTrans::UnitStringArray[TEMPERATURE_UNIT_NUM]
			={	"C","F","R","K"
			};

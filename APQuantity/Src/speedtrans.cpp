/*************************************************
  Copyright (C), 2005-2006, UESOFT Co., Ltd.
  File name:      // SpeedTrans
  Author:         // chenyong
  Date:           // 2006-8-1
  Description:    // �˳����ļ���ɵ���Ҫ���ܵõ��ٶȳ��õ�λ��ת����
                  // ��Ҫ���ⲿͳһ�ٶȵ�λ����
                  // 
  Function List:  // ��Ҫ�����б�
    1. TransToStd(speedUnit) ���ٶȵ�Щ���õ�λת��ΪSI�Ʊ�׼�ٶȵ�λ
	2. TransFromStd(speedUnit) ��SI�Ʊ�׼�ٶȵ�λת��Ϊ�ٶȵĳ��õ�λ
	3. IsSIStd(speedUnit) �жϵ�ǰ���ٶȵ�λ�Ƿ���SI�Ʊ�׼��λ
 *************************************************/

#include "StdAfx.h"
#include "SpeedTrans.h"
#include <assert.h>

IMPLEMENT_UNITSTRING( SpeedTrans );
bool SpeedTrans::IsSIStd( int orgUnit)
{
	return (orgUnit == SPEED_STD_UNIT)?true:false;
}

/*************************************************
  Function:       // TransToStd
  Description:    // �������ٶȵ�λת��ΪSI��׼��λ�ٶȵ�λ
  Input:          // ö���͵ĳ��õ�λ����
                  // speedUnit��
  Output:         // 
  Return:         // �����ٶȵ�ǰ��λ��SI��׼��λ��ת����
				  //������0
*************************************************/
double SpeedTrans::TransToStd( int orgUnit)
{
	if (orgUnit < 0 || orgUnit >= SPEED_UNIT_NUM)
	{
		assert(0);
		return 0.0;
	}
	else
	{
		return speedTransRatio[orgUnit];
	}
}

/*************************************************
  Function:       // TransFromStd
  Description:    // ��SI��׼��λ�ٶȵ�λת��Ϊ�����ٶȵ�λ
  Input:          // ö���͵ĳ��õ�λ����
                  // speedUnit��
  Output:         // 
  Return:         // �����ٶ�SI��׼��λ����ǰ��λ��ת����
				  //������0
*************************************************/
double SpeedTrans::TransFromStd( int orgUnit)
{
	if (orgUnit < 0 || orgUnit >= SPEED_UNIT_NUM)
	{
		assert(0);
		return 0.0;
	}
	else
	{
		return 1.0/speedTransRatio[orgUnit];
	}
}

int SpeedTrans::UnitStringToUnitClass(const StdString& UnitString)
{
	for (int i = 0; i < SPEED_UNIT_NUM; i++)
	{
		if (UnitString.CompareNoCase( SpeedTrans::UnitStringArray[i] ) == 0 )
		{
			return i;
		}
	}
	assert(0);
	return -1;
}

const StdString& SpeedTrans::UnitClassToUnitString(int UnitClass)
{
	assert(UnitClass >= 0 && UnitClass <= SPEED_UNIT_NUM - 1);
	return SpeedTrans::UnitStringArray[UnitClass];
}

//��Ӧö���͸��ٶȵ�λ��SI��׼��λ��ת����
double SpeedTrans::speedTransRatio[SPEED_UNIT_NUM] \
				= {			1/3.6, 1.0, 1/3600, 0.01
				};

const StdString SpeedTrans::UnitStringArray[SPEED_UNIT_NUM] \
				={	"km/h","m/s","m/h","cm/s"
				};
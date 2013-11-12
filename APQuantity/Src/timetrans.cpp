/*************************************************
  Copyright (C), 2005-2006, UESOFT Co., Ltd.
  File name:      // TimeTrans
  Author:         // cy��hh
  Date:           // 2006-7-31
  Description:    // �˳����ļ���ɵ���Ҫ���ܵõ�ʱ�䳣�õ�λ��ת���Ľ���
                  // ֵ����Ҫ���ⲿͳһʱ�����
                  // 
  Function List:  // ��Ҫ�����б�ÿ����¼Ӧ���������������ܼ�Ҫ˵��
    1. TransToStd(time) ��ʱ���Щ���õ�λת��ΪSI�Ʊ�׼ʱ�䵥λ
	2. TransFromStd(time) ��SI�Ʊ�׼ʱ�䵥λת��Ϊʱ���Щ���õ�λ
	3. IsSIStd(time) �жϵ�ǰ��λ�Ƿ�Ϊ���ʱ�׼��λ
 *************************************************/

#include "StdAfx.h"
#include "TimeTrans.h"
#include <assert.h>

IMPLEMENT_UNITSTRING( TimeTrans );
bool TimeTrans::IsSIStd( int orgUnit)
{
	return (orgUnit == TIME_STD_UNIT)?true:false;
}

/*************************************************
  Function:       // TransToStd
  Description:    // ������ʱ�䵥λת��ΪSI��׼��λS
  Input:          // ö���͵ĳ��õ�λ����
                  // timeUnit = m..��
  Output:         // 
  Return:         // ���ص�ǰ��λ��SI��׼��λ��ת����
				  //������0
*************************************************/
double TimeTrans::TransToStd( int orgUnit)
{
	if (orgUnit < 0 || orgUnit >= TIME_UNIT_NUM)
	{
		assert(0);
		return 0.0;
	}
	else
	{
		return timeTransRatio[orgUnit];
	}
}

/*************************************************
  Function:       // TransFromStd
  Description:    // ��SI��׼��λSת��Ϊ����ʱ�䵥λ
  Input:          // ö���͵ĳ��õ�λ����
                  // timeUnit = m..��
  Output:         // 
  Return:         // ����SI��׼��λ����ǰ��λ��ת����
				  //������0
*************************************************/
double TimeTrans::TransFromStd( int orgUnit)
{
	if (orgUnit < 0 || orgUnit >= TIME_UNIT_NUM)
	{
		assert(0);
		return 0.0;
	}
	else
	{
		return 1.0/timeTransRatio[orgUnit];
	}
}

int TimeTrans::UnitStringToUnitClass(const StdString& UnitString)
{
	for (int i = 0; i < TIME_UNIT_NUM; i++)
	{
		if (UnitString.CompareNoCase( TimeTrans::UnitStringArray[i] ) == 0 )
		{
			return i;
		}
	}
	assert(0);
	return -1;
}

const StdString& TimeTrans::UnitClassToUnitString(int UnitClass)
{
	assert(UnitClass >= 0 && UnitClass <= TIME_UNIT_NUM - 1);
	return TimeTrans::UnitStringArray[UnitClass];
}

//��Ӧö���͸���λ��SI��׼��λS��ת����
double TimeTrans::timeTransRatio[TIME_UNIT_NUM] \
				= {			3600,		   60,			1
				};

const StdString TimeTrans::UnitStringArray[TIME_UNIT_NUM] \
				={"h","m","s"			
				};

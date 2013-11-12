/*************************************************
  Copyright (C), 2005-2006, UESOFT Co., Ltd.
  File name:      // PowerTrans
  Author:         // chenyong
  Date:           // 2006-8-1
  Description:    // �˳����ļ���ɵ���Ҫ���ܵõ����ʳ��õ�λ��ת����
                  // ��Ҫ���ⲿͳһ���ʵ�λ����
                  // 
  Function List:  // ��Ҫ�����б�
    1. TransToStd(powerUnit) �����ʵ�Щ���õ�λת��ΪSI�Ʊ�׼���ʵ�λ
	2. TransFromStd(powerUnit) ��SI�Ʊ�׼���ʵ�λת��Ϊ���ʵĳ��õ�λ
	3. IsSIStd(powerUnit) �жϵ�ǰ�Ĺ��ʵ�λ�Ƿ���SI�Ʊ�׼��λ
 *************************************************/

#include "StdAfx.h"
#include "PowerTrans.h"
#include <assert.h>

IMPLEMENT_UNITSTRING( PowerTrans );

bool PowerTrans::IsSIStd( int orgUnit)
{
	return (orgUnit == POWER_STD_UNIT)?true:false;
}

/*************************************************
  Function:       // TransToStd
  Description:    // �����ù��ʵ�λת��ΪSI��׼��λ���ʵ�λ
  Input:          // ö���͵ĳ��õ�λ����
                  // powerUnit��
  Output:         // 
  Return:         // ���ع��ʵ�ǰ��λ��SI��׼��λ��ת����
				  //������0
*************************************************/
double PowerTrans::TransToStd( int orgUnit)
{
	if (orgUnit < 0 || orgUnit >= POWER_UNIT_NUM)
	{
		assert(0);
		return 0.0;
	}
	else
	{
		return powerTransRatio[orgUnit];
	}
}

/*************************************************
  Function:       // TransFromStd
  Description:    // ��SI��׼��λ���ʵ�λת��Ϊ���ù��ʵ�λ
  Input:          // ö���͵ĳ��õ�λ����
                  // powerUnit��
  Output:         // 
  Return:         // ���ع���SI��׼��λ����ǰ��λ��ת����
				  //������0
*************************************************/
double PowerTrans::TransFromStd( int orgUnit)
{
	if (orgUnit < 0 || orgUnit >= POWER_UNIT_NUM)
	{
		assert(0);
		return 0.0;
	}
	else
	{
		return 1.0/powerTransRatio[orgUnit];
	}
}

//��Ӧö���͸����ʵ�λ��SI��׼��λ��ת����
double PowerTrans::powerTransRatio[POWER_UNIT_NUM] \
				= {	1.0, 1000, 735.5, 745.7, 9.807, 1.356, 4186, 1055
				};

const StdString	PowerTrans::UnitStringArray[POWER_UNIT_NUM]
					={"w","kw","ps","hp","kgfm/s","ibfft/s"
					,"kcal/s","btu"};

int PowerTrans::UnitStringToUnitClass(const StdString& UnitString)
{
	for (int i = 0;i < POWER_UNIT_NUM;i++)
	{
		if (UnitString.CompareNoCase( PowerTrans::UnitStringArray[i] ) == 0 )
		{
			return i;
		}
	}
	assert(0);
	return -1;
}

const StdString& PowerTrans::UnitClassToUnitString(int UnitClass)
{
	assert(UnitClass >= 0 && UnitClass <= POWER_UNIT_NUM - 1);
	return PowerTrans::UnitStringArray[UnitClass];
}

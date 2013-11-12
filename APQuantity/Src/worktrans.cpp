/*************************************************
  Copyright (C), 2005-2006, UESOFT Co., Ltd.
  File name:      // WorkTrans
  Author:         // chenyong
  Date:           // 2006-8-1
  Description:    // �˳����ļ���ɵ���Ҫ���ܵõ��ȹ����õ�λ��ת����
                  // ��Ҫ���ⲿͳһ�ȹ���λ����
                  // 
  Function List:  // ��Ҫ�����б�
    1. TransToStd(workUnit) ���ȹ���Щ���õ�λת��ΪSI�Ʊ�׼�ȹ���λ
	2. TransFromStd(workUnit) ��SI�Ʊ�׼�ȹ���λת��Ϊ�ȹ��ĳ��õ�λ
	3. IsSIStd(workUnit) �жϵ�ǰ���ȹ���λ�Ƿ���SI�Ʊ�׼��λ
 *************************************************/

#include "StdAfx.h"
#include "WorkTrans.h"
#include <assert.h>

IMPLEMENT_UNITSTRING( WorkTrans );
bool WorkTrans::IsSIStd( int orgUnit)
{
	return (orgUnit == WORK_STD_UNIT)?true:false;
}

/*************************************************
  Function:       // TransToStd
  Description:    // �������ȹ���λת��ΪSI��׼��λ�ȹ���λJ
  Input:          // ö���͵ĳ��õ�λ����
                  // workUnit��
  Output:         // 
  Return:         // �����ȹ���ǰ��λ��SI��׼��λ��ת����
				  //������0
*************************************************/
double WorkTrans::TransToStd( int orgUnit)
{
	if (orgUnit < 0 || orgUnit >= WORK_UNIT_NUM)
	{
		assert(0);
		return 0.0;
	}
	else
	{
		return workTransRatio[orgUnit];
	}
}

/*************************************************
  Function:       // TransFromStd
  Description:    // ��SI��׼��λ�ȹ���λJת��Ϊ�����ȹ���λ
  Input:          // ö���͵ĳ��õ�λ����
                  // workUnit��
  Output:         // 
  Return:         // �����ȹ�SI��׼��λ����ǰ��λ��ת����
				  //������0
*************************************************/
double WorkTrans::TransFromStd( int orgUnit)
{
	if (orgUnit < 0 || orgUnit >= WORK_UNIT_NUM)
	{
		assert(0);
		return 0.0;
	}
	else
	{	
		return 1.0/workTransRatio[orgUnit];
	}
}

int WorkTrans::UnitStringToUnitClass(const StdString& UnitString)
{
	for (int i = 0; i < WORK_UNIT_NUM; i++)
	{
		if ( UnitString.CompareNoCase( WorkTrans::UnitStringArray[i] ) == 0 )
		{
			return i;
		}
	}
	assert(0);
	return -1;
}

const StdString& WorkTrans::UnitClassToUnitString(int UnitClass)
{
	assert(UnitClass >= 0 && UnitClass <= WORK_UNIT_NUM - 1);
	return WorkTrans::UnitStringArray[UnitClass];
}

//��Ӧö���͸��ȹ���λ��SI��׼��λ��ת����
double WorkTrans::workTransRatio[WORK_UNIT_NUM] \
				= {	1.0,
					4186.75,
					9.80665,
					3600000,
					2648000,
					1.35582,
					1055.06
				};

const StdString WorkTrans::UnitStringArray[WORK_UNIT_NUM] \
				={	"j","kcal","kgfm","kwh","hph","ftlbf","btuw"
				};

/*************************************************
  Copyright (C), 2005-2006, UESOFT Co., Ltd.
  File name:      // DensityTrans
  Author:         // chenyong
  Date:           // 2006-8-1
  Description:    // �˳����ļ���ɵ���Ҫ���ܵõ��ܶȳ��õ�λ��ת����
                  // ��Ҫ���ⲿͳһ�ܶȵ�λ����
                  // 
  Function List:  // ��Ҫ�����б�
    1. TransToStd(densityUnit) ���ܶȵ�Щ���õ�λת��ΪSI�Ʊ�׼�ܶȵ�λ
	2. TransFromStd(densityUnit) ��SI�Ʊ�׼�ܶȵ�λת��Ϊ�ܶȵĳ��õ�λ
	3. IsSIStd(densityUnit) �жϵ�ǰ���ܶȵ�λ�Ƿ���SI�Ʊ�׼��λ
 *************************************************/

#include "StdAfx.h"
#include "DensityTrans.h"
#include <assert.h>

bool DensityTrans::IsSIStd( int orgUnit )
{
	return (orgUnit == DENSITY_STD_UNIT)?true:false;
}

/*************************************************
  Function:       // TransToStd
  Description:    // �������ܶȵ�λת��ΪSI��׼��λ�ܶȵ�λ
  Input:          // ö���͵ĳ��õ�λ����
                  // densityUnit��
  Output:         // 
  Return:         // �����ܶȵ�ǰ��λ��SI��׼��λ��ת����
				  //������0
*************************************************/
double DensityTrans::TransToStd( int orgUnit)
{
	if (orgUnit < 0 || orgUnit >= DENSITY_UNIT_NUM)
	{
		assert(0);
		return 0.0;
	}
	else
	{
		return densityTransRatio[orgUnit];
	}
}

/*************************************************
  Function:       // TransFromStd
  Description:    // ��SI��׼��λ�ܶȵ�λת��Ϊ�����ܶȵ�λ
  Input:          // ö���͵ĳ��õ�λ����
                  // densityUnit��
  Output:         // 
  Return:         // �����ܶ�SI��׼��λ����ǰ��λ��ת����
				  //������0
*************************************************/
double DensityTrans::TransFromStd( int orgUnit)
{
	if (orgUnit < 0 || orgUnit >= DENSITY_UNIT_NUM)
	{
		assert(0);
		return 0.0;
	}
	else
	{
		return 1.0/densityTransRatio[orgUnit];
	}
}

int DensityTrans::UnitStringToUnitClass(const StdString& UnitString)
{
	for (int i = 0; i < DENSITY_UNIT_NUM; i++)
	{
		if (UnitString.CompareNoCase( DensityTrans::UnitStringArray[i] ) == 0 )
		{
			return i;
		}
	}
	assert(0);
	return -1;
}

const StdString& DensityTrans::UnitClassToUnitString(int UnitClass)
{
	assert(UnitClass >= 0 && UnitClass <= DENSITY_UNIT_NUM - 1);
	return DensityTrans::UnitStringArray[UnitClass];
}

//��Ӧö���͸��ܶȵ�λ��SI��׼��λ��ת����
double DensityTrans::densityTransRatio[DENSITY_UNIT_NUM] \
				= {		1000, 1.0, 16.02, 119.8,1E+6,27679.899
				};

const StdString DensityTrans::UnitStringArray[DENSITY_UNIT_NUM] \
				={	"g/cm_3","kg/m_3","lb/ft_3","lb/USgal","kg/cu.cm","lb/cu.in"
				};

IMPLEMENT_UNITSTRING( DensityTrans );
/*************************************************
  Copyright (C), 2005-2006, UESOFT Co., Ltd.
  File name:      // MassTrans
  Author:         // chenyong
  Date:           // 2006-8-1
  Description:    // �˳����ļ���ɵ���Ҫ���ܵõ��������õ�λ��ת����
                  // ��Ҫ���ⲿͳһ������λ����
                  // 
  Function List:  // ��Ҫ�����б�
    1. TransToStd(massUnit) ��������Щ���õ�λת��ΪSI�Ʊ�׼������λ
	2. TransFromStd(massUnit) ��SI�Ʊ�׼������λת��Ϊ�����ĳ��õ�λ
	3. IsSIStd(massUnit) �жϵ�ǰ��������λ�Ƿ���SI�Ʊ�׼��λ
 *************************************************/

#include "StdAfx.h"
#include "MassTrans.h"
#include <assert.h>

bool MassTrans::IsSIStd( int orgUnit)
{
	return (orgUnit == MASS_STD_UNIT)?true:false;
}

/*************************************************
  Function:       // TransToStd
  Description:    // ������������λת��ΪSI��׼��λ������λ
  Input:          // ö���͵ĳ��õ�λ����
                  // massUnit��
  Output:         // 
  Return:         // ����������ǰ��λ��SI��׼��λ��ת����
				  //������0
*************************************************/
double MassTrans::TransToStd( int orgUnit)
{
	if (orgUnit < 0 || orgUnit >= MASS_UNIT_NUM)
	{
		assert(0);
		return 0.0;
	}
	else
	{
		return massTransRatio[orgUnit];
	}
}

/*************************************************
  Function:       // TransFromStd
  Description:    // ��SI��׼��λ������λת��Ϊ����������λ
  Input:          // ö���͵ĳ��õ�λ����
                  // massUnit��
  Output:         // 
  Return:         // ��������SI��׼��λ����ǰ��λ��ת����
				  //������0
*************************************************/
double MassTrans::TransFromStd( int orgUnit)
{
	if (orgUnit < 0 || orgUnit >= MASS_UNIT_NUM)
	{
		assert(0);
		return 0.0;
	}
	else
	{
		return 1.0/massTransRatio[orgUnit];
	}
}

//��Ӧö���͸�������λ��SI��׼��λ��ת����
double MassTrans::massTransRatio[MASS_UNIT_NUM] \
					= {	1000.0, 907.1847, 1.0, 0.001, 0.454,0.10204
					};

const StdString MassTrans::UnitStringArray[MASS_UNIT_NUM]
					={"t","at","kg","g","lb","N"};

IMPLEMENT_UNITSTRING( MassTrans );
const StdString& MassTrans::UnitClassToUnitString(int UnitClass)
{
	assert(UnitClass >= 0 && UnitClass <= MASS_UNIT_NUM - 1);
	return MassTrans::UnitStringArray[UnitClass];
}

int MassTrans::UnitStringToUnitClass(const StdString& UnitString)
{
	for (int i = 0;i < MASS_UNIT_NUM;i++)
	{
		if (UnitString.CompareNoCase( MassTrans::UnitStringArray[i] ) == 0 )
		{
			return i;
		}
	}
	assert(0);
	return -1;
}

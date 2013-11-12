/*************************************************
	Copyright (C), 1988-2006, UESOFT Co., Ltd.
	File name:AreaTrans.h
	Author:���(lobby)
	Version:1.0
	Date:2006.7.31
	Description:�����������������в�ͬ��λ���׼��λ֮���ת����
				���ṩ������ģ��ʹ�õ���һ���������ӣ���Ӧĳ��λ
				���׼��֮���������ϵ��
	Function List:  
    1. TransToStd
	����һ��int�ͱ�����Ϊ������
	���ظõ�λ���׼��λ֮��ı���ϵ����
	2. TransFromStd
	����һ��int�ͱ�����Ϊ������
	���ر�׼��λ��õ�λ֮��ı���ϵ����
	3.IsSIStd
	����һ��int�ͱ�����Ϊ������
	���ز���ֵ�������Ƿ�õ�λ�Ǳ�׼��λ
	4.UnitClassToUnitString
	����һ��int�ͱ�����Ϊ����,
	���ظõ�λ�����Ӧ�ĵ�λ�ַ���
	5.UnitStringToUnitClass
	����һ��string�ͱ�����Ϊ����,
	���ظõ�λ�ַ�����Ӧ�ĵ�λ����
*************************************************/
#ifndef _AREATRANS_H
#define _AREATRANS_H

#include <string>
#include "UnitString.h"
using namespace std;
#include "Quantity_share.h"

#define	AREA_UNIT_NUM	7
#define	AREA_STD_UNIT	0

//enum AreaUnit
/*{
	const int m2 = 0;//ƽ���ף���׼��λ��
	const int dm2 = 1;//ƽ������
	const int cm2 = 2;//ƽ������
	const int ft2 = 3;//ƽ��Ӣ��
	const int yd2 = 4;//ƽ����
	const int in2 = 5;//ƽ��Ӣ��
//};
*/

class QUANTITY_API AreaTrans
{
	DECLARE_UNITSTRING( AreaTrans, AREA_UNIT_NUM );
public:

	static const StdString& UnitClassToUnitString(int UnitClass);
	static int UnitStringToUnitClass(const StdString&);
	static	bool	IsSIStd( int );
	static	double	TransToStd( int );
	static	double	TransFromStd( int );
	static  int GetStdUnitIndex()
	{
		return AREA_STD_UNIT;
	}
protected:
private:
	
	static	double	areaTransRatio[AREA_UNIT_NUM];
	static	const StdString	UnitStringArray[AREA_UNIT_NUM];
};

#endif
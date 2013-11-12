/*************************************************
	Copyright (C), 1988-2006, UESOFT Co., Ltd.
	File name:AngleTrans.h
	Author:���(lobby)
	Version:1.0
	Date:2006.7.31
	Description:������ɽǶ��������в�ͬ��λ���׼��λ֮���ת����
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
	����һ��UeStdString�ͱ�����Ϊ����,
	���ظõ�λ�ַ�����Ӧ�ĵ�λ����
*************************************************/
#ifndef _ANGLETRANS_H
#define _ANGLETRANS_H
#include <string>
#include "UnitString.h"
#include "Quantity_share.h"

using namespace std;

#define	ANGLE_UNIT_NUM	5
#define	ANGLE_STD_UNIT	3

class QUANTITY_API AngleTrans//
{
	DECLARE_UNITSTRING( AngleTrans, ANGLE_UNIT_NUM );
public:
	static const StdString& UnitClassToUnitString(int UnitClass);
	static int UnitStringToUnitClass(const StdString&);
	static	bool	IsSIStd( int );
	static	double	TransToStd( int );
	static	double	TransFromStd( int );
	static  int GetStdUnitIndex()
	{
		return ANGLE_STD_UNIT;
	}
protected:
private:
	static	double	angleTransRatio[ANGLE_UNIT_NUM];
	static	const StdString	UnitStringArray[ANGLE_UNIT_NUM];
};

#endif
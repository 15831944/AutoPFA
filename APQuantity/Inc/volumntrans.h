/*************************************************
	Copyright (C), 1988-2006, UESOFT Co., Ltd.
	File name:VolumnTrans.h
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
#ifndef _VOLUMNTRANS_H
#define _VOLUMNTRANS_H

#include <string>
#include "UnitString.h"
using namespace std;
#include "Quantity_share.h"

#define	VOLUMN_UNIT_NUM	7
#define	VOLUMN_STD_UNIT	0

/*enum VolumnUnit
//{
	const int m3 = 0;//�����ף���׼��λ��
	const int cm3 = 1;//��������
	const int litre = 2;//�����������ף�
	const int gallon_a = 3;//���Ƽ���
	const int gallon_e = 4;//Ӣ�Ƽ���
	const int ft3 = 5;//����Ӣ��
	const int in3 = 6;//����Ӣ��
//};
*/
class QUANTITY_API VolumnTrans
{
	DECLARE_UNITSTRING( VolumnTrans, VOLUMN_UNIT_NUM );
public:

	static const StdString& UnitClassToUnitString(int UnitClass);
	static int UnitStringToUnitClass( const StdString& );
	static	bool	IsSIStd( int );
	static	double	TransToStd( int );
	static	double	TransFromStd( int );
	static  int GetStdUnitIndex()
	{
		return VOLUMN_STD_UNIT;
	}
protected:
private:

	static	double	volumnTransRatio[VOLUMN_UNIT_NUM];
	static	const StdString	UnitStringArray[VOLUMN_UNIT_NUM];
};

#endif
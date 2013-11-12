/*************************************************
	Copyright (C), 1988-2006, UESOFT Co., Ltd.
	File name:LengthTrans.h
	Author:���(lobby)
	Version:1.0
	Date:2006.7.31
	Description:������ɳ����������в�ͬ��λ���׼��λ֮���ת����
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
#ifndef _LENGTHTRANS_H
#define _LENGTHTRANS_H

#include <string>
#include "UnitString.h"
using namespace std;
#include "Quantity_share.h"

#define	LENGTH_UNIT_NUM	9
#define	LENGTH_STD_UNIT	3

/*enum LengthUnit
//{
	const int mm = 0;//����
	const int cm = 1;//����
	const int dm = 2;//����
	const int m= 3;//��(��׼��λ)
	const int km =4;//ǧ��
	const int in = 5;//Ӣ��
	const int ft = 6;//Ӣ��
	const int yd = 7;//��
	const int mile = 8;//Ӣ��
//};
*/

class QUANTITY_API LengthTrans
{
	DECLARE_UNITSTRING( LengthTrans, LENGTH_UNIT_NUM );
public:

	static int UnitStringToUnitClass(const StdString& UnitString);
	static const StdString& UnitClassToUnitString(int UnitClass);
	static	bool	IsSIStd( int );
	static	double	TransToStd( int );
	static	double	TransFromStd( int );
	static  int GetStdUnitIndex()
	{
		return LENGTH_STD_UNIT;
	}
protected:
private:
	
	static	double	lengthTransRatio[LENGTH_UNIT_NUM];
	static	const StdString	UnitStringArray[LENGTH_UNIT_NUM];
};

#endif
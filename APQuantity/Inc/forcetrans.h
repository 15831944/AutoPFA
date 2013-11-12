/*************************************************
	Copyright (C), 1988-2006, UESOFT Co., Ltd.
	File name:ForceTrans.h
	Author:���(lobby)
	Version:1.0
	Date:2006.8.1
	Description:����������������в�ͬ��λ���׼��λ֮���ת����
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
#ifndef _FORCETRANS_H
#define _FORCETRANS_H
#include <string>
#include "UnitString.h"
using namespace std;
#include "Quantity_share.h"


#define	FORCE_UNIT_NUM	6
#define	FORCE_STD_UNIT	0

/*enum ForceUnit
//{
	const int N = 0;//ţ��(��׼��λ)
	const int gf = 1;//����
	const int kgf = 2;//ǧ����
	const int lbf = 3;//����
	const int dyn = 4;//����
//};
*/
class QUANTITY_API ForceTrans
{
	DECLARE_UNITSTRING( ForceTrans, FORCE_UNIT_NUM );
public:

	static const StdString& UnitClassToUnitString(int UnitClass);
	static int UnitStringToUnitClass(const StdString& UnitString);
	static	bool	IsSIStd( int );
	static	double	TransToStd( int );
	static	double	TransFromStd( int );
	static  int GetStdUnitIndex()
	{
		return FORCE_STD_UNIT;
	}
protected:
private:

	static	const StdString UnitStringArray[FORCE_UNIT_NUM];
	static	double	forceTransRatio[FORCE_UNIT_NUM];
};

#endif
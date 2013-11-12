/*************************************************
	Copyright (C), 1988-2006, UESOFT Co., Ltd.
	File name:PressureTrans.h
	Author:���(lobby)
	Version:1.0
	Date:2006.7.31
	Description:�������ѹǿ�������в�ͬ��λ���׼��λ֮���ת����
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
#ifndef _PRESSURETRANS_H
#define _PRESSURETRANS_H
#include <string>
#include "UnitString.h"
#include "Quantity_share.h"
using namespace std;


#define	PRESSURE_UNIT_NUM	14
#define	PRESSURE_STD_UNIT	0

/*enum PressureUnit
//{
	const int Pa = 0;//��˹��(��׼��λ)
	const int KPa = 1;//ǧ��˹��
	const int MPa = 2;//����˹��
	const int kgf_m = 3;//ǧ����/��2�����ڱ�ʶ���޷�д��kgf/m2��ʽ��
	//���Խ���/����Ϊ��_��2�η���Ϊ2��kgf_cm�����ͬ��
	const int kgf_cm = 4;//ǧ����/����2
	const int bar = 5;//��
	const int atm = 6;//��׼����ѹ
	const int mmH2o = 7;//����ˮ��
	const int mmHg = 8;//����ˮ����
	const int psi = 9;//��/Ӣ��2��lb/in2��
//};
*/

class QUANTITY_API PressureTrans
{
	DECLARE_UNITSTRING( PressureTrans, PRESSURE_UNIT_NUM );
public:
	static int UnitStringToUnitClass(const StdString& UnitString);
	static const StdString& UnitClassToUnitString(int UnitClass);
	static	bool	IsSIStd( int );
	static	double	TransToStd( int );
	static	double	TransFromStd( int );
	static  int GetStdUnitIndex()
	{
		return PRESSURE_STD_UNIT;
	}
protected:
private:
	static const StdString UnitStringArray[PRESSURE_UNIT_NUM];
	static	double	pressureTransRatio[PRESSURE_UNIT_NUM];
};

#endif
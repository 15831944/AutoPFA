#ifndef _POWERTRANS_H
#define _POWERTRANS_H

#include <string>
#include "UnitString.h"
using namespace std;
#include "Quantity_share.h"

//���ʳ��õ�λ�ĸ���
#define	POWER_UNIT_NUM	8

#define	POWER_STD_UNIT	0//��ǹ��ʵ�SI��׼��λ

//���幦�ʵĵ�λ
/*
	const int w = 0;//�ߣ���׼��λ��
	const int kw = 1;//ǧ��
	const int ps = 2;//����
	const int hp = 3;//Ӣ����
	const int kgfm_s = 4;//ǧ����/��
	const int ibfft_s = 5;//Ӣ�߰���/��
	const int kcal_s = 6;//ǧ��/��
	const int btu = 7;//Ӣ�ȵ�λ/��
*/

class QUANTITY_API PowerTrans
{
	DECLARE_UNITSTRING( PowerTrans, POWER_UNIT_NUM );
public:
	static const StdString& UnitClassToUnitString(int UnitClass);
	static int UnitStringToUnitClass(const StdString& UnitString);
	static bool	IsSIStd( int );
	static double TransToStd( int );
	static double TransFromStd( int );
	static  int GetStdUnitIndex()
	{
		return POWER_STD_UNIT;
	}
protected:

private:
	static const StdString UnitStringArray[POWER_UNIT_NUM];

	static double powerTransRatio[POWER_UNIT_NUM];
};

#endif

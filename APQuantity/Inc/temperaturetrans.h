#ifndef _TEMPERATURETRANS_H
#define _TEMPERATURETRANS_H

#define SPECIAL 4294967295
//�¶ȳ��õ�λ�ĸ���
#define	TEMPERATURE_UNIT_NUM	4


#include <string>
#include "UnitString.h"
using namespace std;
#include "Quantity_share.h"


#define	TEMPERATURE_STD_UNIT	0//����¶�SI��׼��λ

//����ʱ��ĵ�λ
/*enum	TemperatureUnit
//{
	const int C = 0;//���϶�(��)����׼��λ��
	const int F = 1;//���϶�(�H)
	const int R = 2;//���Ϣ� ��(oR)
	const int K	= 3;//������(K)
//};
*/

class QUANTITY_API TemperatureTrans
{
	DECLARE_UNITSTRING( TemperatureTrans, TEMPERATURE_UNIT_NUM );
public:
	static const StdString& UnitClassToUnitString(int UnitClass);
	static int UnitStringToUnitClass( const StdString& );
	static bool	IsSIStd( int );
	static double TemperatureTransToStd( double, int );
	static double TemperatureTransFromStd( double,int );
	static double TransToStd( int );
	static double TransFromStd( int );
	static  int GetStdUnitIndex()
	{
		return TEMPERATURE_STD_UNIT;
	}

private:
	static	const StdString	UnitStringArray[TEMPERATURE_UNIT_NUM];
};

#endif


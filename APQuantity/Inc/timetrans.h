#ifndef _TIMETRANS_H
#define _TIMETRANS_H

#include <string>
#include "UnitString.h"
using namespace std;
#include "Quantity_share.h"

//ʱ�䳣�õ�λ�ĸ���
#define	TIME_UNIT_NUM	3
#define	TIME_STD_UNIT	2//��ΪSI��׼��λ

//����ʱ��ĵ�λ
/*enum	TimeUnit
//{
	const int h = 0;//Сʱ
	const int m = 1;//����
	const int s = 2;//�루��׼��λ��
//};
*/
class QUANTITY_API TimeTrans
{
	DECLARE_UNITSTRING( TimeTrans, TIME_UNIT_NUM );
public:
	static const StdString& UnitClassToUnitString( int UnitClass );
	static int UnitStringToUnitClass( const StdString& );
	static bool	IsSIStd( int );
	static double TransToStd( int );
	static double TransFromStd( int );
	static  int GetStdUnitIndex()
	{
		return TIME_STD_UNIT;
	}
protected:

private:

	static	double timeTransRatio[TIME_UNIT_NUM];
	static	const StdString	UnitStringArray[TIME_UNIT_NUM];
};

#endif

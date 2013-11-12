#ifndef _DENSITYTRANS_H
#define _DENSITYTRANS_H

#include <string>
#include "UnitString.h"
using namespace std;
#include "Quantity_share.h"

//�ܶȳ��õ�λ�ĸ���
#define	DENSITY_UNIT_NUM	6

#define	DENSITY_STD_UNIT	1//����ܶ�SI��׼��λ

//�����ܶȵĵ�λ
/*enum	DensityUnit
//{
	const int g_cm3 = 0;	//��ÿ��������
	const int kg_m3 = 1;	//ǧ��ÿ�����ף���׼��λ��
	const int lb_ft3 = 2;	//��/Ӣ��3
	const int lb_USgal =3;//��/������
//};
*/
class QUANTITY_API DensityTrans
{
	DECLARE_UNITSTRING( DensityTrans, DENSITY_UNIT_NUM );
public:
	
	static const StdString& UnitClassToUnitString(int UnitClass);
	static int UnitStringToUnitClass(const StdString&);
	static bool	IsSIStd( int );
	static double TransToStd( int );
	static double TransFromStd( int );
	static  int GetStdUnitIndex()
	{
		return DENSITY_STD_UNIT;
	}
protected:

private:

	static	double densityTransRatio[DENSITY_UNIT_NUM];
	static	const StdString	UnitStringArray[DENSITY_UNIT_NUM];

};

#endif

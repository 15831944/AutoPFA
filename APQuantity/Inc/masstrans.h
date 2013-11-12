#ifndef _MASSTRANS_H
#define _MASSTRANS_H
#include <string>
#include "UnitString.h"
using namespace std;
#include "Quantity_share.h"

//�������õ�λ�ĸ���
#define	MASS_UNIT_NUM	6

#define	MASS_STD_UNIT	2//ǧ��Ϊ����SI��׼��λ

//���������ĵ�λ

/*const int t = 0;//��
const int at = 1;//����
const int kg = 2;//ǧ�ˣ���׼��λ��
const int g = 3;//��
const int lb = 4;//��	
*/	

class QUANTITY_API MassTrans
{
	DECLARE_UNITSTRING( MassTrans, MASS_UNIT_NUM );
public:
	static int UnitStringToUnitClass(const StdString& UnitString);
	static const StdString& UnitClassToUnitString(int UnitClass);
	static bool	IsSIStd( int );
	static double TransToStd( int );
	static double TransFromStd( int );
	static  int GetStdUnitIndex()
	{
		return MASS_STD_UNIT;
	}
protected:

private:
	static const StdString UnitStringArray[MASS_UNIT_NUM];

	static double massTransRatio[MASS_UNIT_NUM];
};

#endif

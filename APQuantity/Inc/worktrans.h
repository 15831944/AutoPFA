#ifndef _WORKTRANS_H
#define _WORKTRANS_H

#include <string>
#include "UnitString.h"
using namespace std;
#include "Quantity_share.h"

//�ȹ����õ�λ�ĸ���
#define	WORK_UNIT_NUM	7

#define	WORK_STD_UNIT	0 //JΪ�ȹ�SI��׼��λ

//�����ȹ��ĵ�λ
/*enum	WorkUnit
//{
	const int j = 0;//��������׼��λ��
	const int kcal = 1;	//ǧ��
	const int kgfm = 2;	//ǧ����.��
	const int kwh = 3;	//ǧ��Сʱ
	const int hph = 4;	//��������Сʱ
	const int ftlbf = 5;	//Ӣ�߰���
	const int btuw = 6;	//Ӣ�ȵ�λ
//};
*/
class QUANTITY_API WorkTrans
{
	DECLARE_UNITSTRING( WorkTrans, WORK_UNIT_NUM );
public:
	static const StdString& UnitClassToUnitString(int UnitClass);
	static int UnitStringToUnitClass(const StdString&);
	static bool	IsSIStd( int );
	static double TransToStd( int );
	static double TransFromStd( int );
	static  int GetStdUnitIndex()
	{
		return WORK_STD_UNIT;
	}
protected:

private:

	static	double workTransRatio[WORK_UNIT_NUM];
	static	const StdString UnitStringArray[WORK_UNIT_NUM];
};

#endif
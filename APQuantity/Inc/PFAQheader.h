#ifndef PFAQHEADER_H
#define PFAQHEADER_H

#include <string>
#include <UTILITY>
#include <vector>
#include "Quantity_share.h"

#ifdef UNICODE
typedef std::wifstream Ueistream;
typedef std::wstring UeStdString;
#define UELPCSTR LPCWSTR
#else
typedef std::ifstream Ueistream;
typedef std::string UeStdString;
#define UELPCSTR LPCTSTR
#endif

#ifdef UNICODE
typedef std::wifstream Ueistream;
#else
typedef std::ifstream Ueistream;
#endif

using namespace std;
typedef vector< UeStdString > InputSet;
typedef vector< vector< UeStdString > > TypeStringSet;
typedef TypeStringSet SysSet;
typedef pair< double,double > RateAndDelta;//һ����λ����һ����λ֮��ı���
typedef pair< UeStdString,RateAndDelta > TransPair;//һ����λ��������ת������ɵ�pair
typedef vector< TransPair > TransPairSetOfOneType;//һ�ֵ�λ������ת��
typedef pair<UeStdString,pair< UeStdString,TransPairSetOfOneType > > QuantityType;//һ��������,��һ��UeStdString��ʾ���������ƣ��磺���ȣ�
//�ڶ���UeStdString��ʾĬ�ϵ�λ���磺�ף�
typedef vector< QuantityType > QuantityTypeSet;//���е�����������
typedef pair< UeStdString,QuantityTypeSet > Qsys;//һ����λ��
typedef vector< Qsys > QSysSet;//���еĵ�λ�Ƽ���
#endif
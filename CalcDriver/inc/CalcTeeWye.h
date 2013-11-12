// CalcTeeWye.h: interface for the CalcTeeWye class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CALCTEEWYE_H__07FE31B0_6905_4568_BF95_4C6E94DF3A06__INCLUDED_)
#define AFX_CALCTEEWYE_H__07FE31B0_6905_4568_BF95_4C6E94DF3A06__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CalcJun.h"

class AFX_EXT_CLASS CalcTeeWye : public CalcJun  
{
public:
	ostream& Write(ostream& CalcOut);
	static CalcJun* Creator();
	CalcTeeWye();
	virtual ~CalcTeeWye();
public:
	void Angle(double dValue);
	void Model(int nValue);
	void Type(int nValue);

	double Angle();
	int Model();
	int Type();
private:
	double m_dAngle;			//�Ƕ�
	int    m_nModel;			//��ʧģ�����ͣ�1����ģ��2����ϸģ�ͣ�
	int    m_nType;			    //���ͣ�0�����ֱ��ͨ1��Բ��ֱ��ͨ2������ı�3���Գƣ�

};

#endif // !defined(AFX_CALCTEEWYE_H__07FE31B0_6905_4568_BF95_4C6E94DF3A06__INCLUDED_)

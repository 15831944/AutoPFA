// CalcAreaChange.h: interface for the CalcAreaChange class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CALCAREACHANGE_H__B9677E7A_B3CB_476A_8B0D_E4F9C8703770__INCLUDED_)
#define AFX_CALCAREACHANGE_H__B9677E7A_B3CB_476A_8B0D_E4F9C8703770__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CalcJun.h"

class AFX_EXT_CLASS CalcAreaChange : public CalcJun  
{
public:
	ostream& Write(ostream& CalcOut);
	static CalcJun* Creator();
	CalcAreaChange();
	virtual ~CalcAreaChange();

public:
	void Type(int nValue);
	void Angle(double dValue);
	void K(double dValue);
	void BasisAreaType(int nValue);
	void BasisArea(double dValue);

	double K();
	int BasisAreaType();
	double BasisArea();

private:
	int     m_Type;								//�쾶�����ͣ�0��Բ׶��1��Բ����2���û����壩
	double  m_Angle;							//�Ƕ�
	double  m_K;								//Kϵ��ֵ
	int     m_nBasisAreaType;					//��ʧģ�͵��������0��Ĭ�����ιܵ������1�����ιܵ����2���û�ָ�����3���û�ָ��ֱ��
	double  m_dBasisArea;						//���Ŷorֱ��
};



#endif // !defined(AFX_CALCAREACHANGE_H__B9677E7A_B3CB_476A_8B0D_E4F9C8703770__INCLUDED_)

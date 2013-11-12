// CalcRelief.h: interface for the CalcRelief class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CALCRELIEF_H__DA86DA77_9AAF_4E88_82AB_04AEF14451F8__INCLUDED_)
#define AFX_CALCRELIEF_H__DA86DA77_9AAF_4E88_82AB_04AEF14451F8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CalcJun.h"
#include "CalcCurve.h"
#include "CalcTransData.h"

class AFX_EXT_CLASS CalcRelief : public CalcJun  
{
public:
	ostream& Write(ostream& CalcOut);
	static CalcJun* Creator();
	CalcRelief();
	virtual ~CalcRelief();
public:
	void Type(int nValue);
	void LossType(int nValue);
	void PressType(int nValue);
	void CrackPress(double dValue);
	void ExitPress(double dValue);
	void KOrCv(double dValue);
	void BasisAreaType(int nValue);
	void BasisArea(double dValue);

	int Type();
	int LossType();
	int PressType();
	double CrackPress();
	double ExitPress();
	double KOrCv();
	int BasisAreaType();
	double BasisArea();
private:
	int		 m_nType;							//����(1:�ڲ���ȫ����internal relief��2:���ڰ�ȫ����exit relief��3:��Ƕ��ȫ����inline relief��)
	int      m_nLossType;						//��ʧģ��(0������ϵ��ģ�ͣ�1��Kϵ��ģ��3��������ϵ��)
	double   m_dKOrCv;						    //K��Cvϵ��ֵ
	int      m_nBasisAreaType;					//��ʧģ�͵��������0��Ĭ�����ιܵ������1�����ιܵ����2���û�ָ�����3���û�ָ��ֱ��
	double   m_dBasisArea;						//���Ŷorֱ��
	int      m_nPressType;					    //0. ����ˮͷ, 2. ˮͷ��,  1������ѹ��, 3��ѹ����.
	double	 m_dCrackPress;				        //���ѵ�ѹ��
	double   m_dExitPress;					    //����ѹ��
public:
	CalcCurve m_Curve;
	CalcTransData m_TranData;

};

#endif // !defined(AFX_CALCRELIEF_H__DA86DA77_9AAF_4E88_82AB_04AEF14451F8__INCLUDED_)

// CalcControl.h: interface for the CalcControl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CALCCONTROL_H__9A7646C0_FF43_4423_A8A1_267A525A37F7__INCLUDED_)
#define AFX_CALCCONTROL_H__9A7646C0_FF43_4423_A8A1_267A525A37F7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CalcJun.h"
#include "CalcTransData.h"

class AFX_EXT_CLASS CalcControl : public CalcJun  
{
public:
	ostream& Write(ostream& CalcOut);
	static CalcJun* Creator();
	CalcControl();
	virtual ~CalcControl();

public:
	void Type(int nValue);
	void AlwayControl(int nValue);
	void UpInsuffic(int nValue);
	void DownExcess(int nValue);
	void ControlType(int nValue);
	void PressType(int nValue);
	void ControlValue(double dValue);
	void LossType(int nValue);
	void KOrCv(double dValue);
	void CvTable(const ListImp<StrArray<3> >& ref);
	void BasisAreaType(int nValue);
	void BasisArea(double dValue);

	int Type();
	int AlwayControl();
	int UpInsuffic();
	int DownExcess();
	int ControlType();
	int PressType();
	double ControlValue();
	int LossType();
	double KOrCv();
	ListImp<StrArray<3> >& CvTable();
	int BasisAreaType();
	double BasisArea();

private:
	int m_nType;								//��������0��PRF 1��PSV 2��FCV 3��PDCV
	int m_nAlwayControl;						//�ȶ�״̬���ǿ���0��û��ѡ�� 1��ѡ��
	int m_nUpInsuffic;							//����ѹ���������0��ȫ���� 1���ر�
	int m_nDownExcess;							//����ѹ����������0��ȫ���� 1���ر�
    int m_nControlType;					        //���Ƶ��������0��ˮͷ/ˮͷ��ʧ/�������1��ѹ��/ѹ����ʧ/��������
	int m_nPressType;							//0��ͣ��ѹ��1����̬ѹ��
	double m_dControlValue;						//���Ƶ����ֵ
	int	   m_nLossType;						    //��ʧģ��(0������ϵ��ģ�ͣ�1��Kϵ��ģ�� -2��ʹ��ϵ�����ֵ)
	double m_dKOrCv;							//K��Cvϵ��ֵ
	CalcTable<3> m_CvTable;

	int     m_nBasisAreaType;					//��ʧģ�͵��������0��Ĭ�����ιܵ������1�����ιܵ����2���û�ָ�����3���û�ָ��ֱ��
	double  m_dBasisArea;						//���Ŷorֱ��

public:
	CalcTransData m_TranData;	
	CalcTransData m_FailTranData;
};

#endif // !defined(AFX_CALCCONTROL_H__9A7646C0_FF43_4423_A8A1_267A525A37F7__INCLUDED_)

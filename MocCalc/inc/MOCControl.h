// MOCControl.h: interface for the MOCControl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MOCCONTROL_H__065120DB_784A_45A2_99FA_8F4F7CF48C89__INCLUDED_)
#define AFX_MOCCONTROL_H__065120DB_784A_45A2_99FA_8F4F7CF48C89__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MOCJun.h"
#include "MOCTranData.h"

class MOCControl : public MOCJun  
{
public:
	int ValveStatus();
	BOOL Read(CalcJun *pData);
	static MOCJun* Creator();
	MOCControl();
	virtual ~MOCControl();

private:
	BOOL InitEndInfo();
	void CalcStm();
	BOOL InitTranData(MOCComponentMgr &mgr);
	virtual void CalculateK();

private:
	void CalcImpulse(MOCTrans &trans,double dTime);
	void UpdataEnd();
	void FixStatus(double dControlValue);
	void Action(int nType,double dKOrCv);
	void SwitchStatus(double dKOrCv,double dControlValue);
	void FullOpenValve(double dKOrCv);
	void CloseValve();
	void PressControl(EndInfo *pControlEnd,EndInfo *pEnd,double dControlValue);
	void FlowControl(EndInfo *pControlEnd,double dFlow);
	void CalcPDCV(double dControlValue);
	void CalcFCV(double dControlValue);
	void CalcPSV(double dControlValue);
	void CalcPRV(double dControlValue);
	double GetCvFromCvTable();
	int m_nType;								//��������0��PRV 1��PSV 2��FCV 3��PDCV
	int m_nAlwayControl;						//�ȶ�״̬���ǿ���0��û��ѡ�� 1��ѡ��
	int m_nUpInsuffic;							//����ѹ���������0��ȫ���� 1���ر�
	int m_nDownExcess;							//����ѹ����������0��ȫ���� 1���ر�
                        				        //���Ƶ��������0��ˮͷ/ˮͷ��ʧ/�������1��ѹ��/ѹ����ʧ/��������
	int m_nPressType;							//0��ͣ��ѹ��1����̬ѹ��
	double m_dControlValue;						//���Ƶ����ֵ
	int	   m_nLossType;						    //��ʧģ��(0������ϵ��ģ�ͣ�1��Kϵ��ģ�� -2��ʹ��ϵ�����ֵ)
	double m_dKOrCv;							//K��Cvϵ��ֵ
	ListImp<StrArray<3> > m_CvTable;
	int     m_nBasisAreaType;					//��ʧģ�͵��������0��Ĭ�����ιܵ������1�����ιܵ����2���û�ָ�����3���û�ָ��ֱ��
	double  m_dBasisArea;						//���Ŷorֱ��

	int m_nValveStatus;

	MOCTranData m_tranData;
	MOCTranData m_fialTranData;
};

#endif // !defined(AFX_MOCCONTROL_H__065120DB_784A_45A2_99FA_8F4F7CF48C89__INCLUDED_)

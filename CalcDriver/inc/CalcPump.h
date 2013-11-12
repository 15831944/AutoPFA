// CalcPump.h: interface for the CalcPump class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CALCPUMP_H__92863BD5_5E5F_480C_BE18_CFCC57438D38__INCLUDED_)
#define AFX_CALCPUMP_H__92863BD5_5E5F_480C_BE18_CFCC57438D38__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CalcJun.h"
#include "CalcTransData.h"
#include "CalcPumpConfig.h"

class AFX_EXT_CLASS CalcPump : public CalcJun  
{
public:
	ostream& Write(ostream& CalcOut);
	static CalcJun* Creator();
	CalcPump();
	virtual ~CalcPump();
public:
	void FourQuadrantData(const ListImp<StrArray<3> >& ref);
	void AntiReverse(int nValue);
	void ExitCheck(int nValue);
	void CloseVel(double dValue);
	void PressType(int nValue);
	void SelSubmerge(int nValue);
	void SubmergePressType(int nValue);
	void SuctionPress(double dValue);
	void PumpSet(int nValue);
	void TranModel(int nValue);
	void PumpType(int nValue);
	void PumpFlow(double dValue);
	void SpeedRatio(double dValue);
	void PumpControl(int nValue);
	void ControlType(int nValue);
	void ControlValue(double dValue);
	void ControlApply(int nValue);
	void ReOpenPressType(int nValue);
	void ReOpenPress(double dValue);
	void RotateInertia(double dValue);
	void Speed(double dValue);
	void FourQuadrantAngle(int nValue);

	ListImp<StrArray<2> > FHData();
	ListImp<StrArray<2> > FBData();
	int AntiReverse();
	int ExitCheck();
	double CloseVel();
	int PressType();
	int SelSubmerge();
	int SubmergePressType();
	double SuctionPress();
	int PumpSet();
	int TranModel();
	int PumpType();
	double PumpFlow();
	double SpeedRatio();
	int PumpControl();
	int ControlType();
	double ControlValue();
	int ControlApply();
	int ReOpenPressType();
	double ReOpenPress();
	double RotateInertia();
	double Speed();
	int FourQuadrantAngle();
private:
	double      m_dNPRS;				//��ʴ�����ο��߳�
	int         m_bSelViscosCor;		//ճ��������0����ʹ��ճ��������-1��ʹ��ճ��������
    int         m_nBEFType;				//ѹ������ѡ��0���ٶ�����������BEF��1���û������������Ч�ʵ㣩
	double      m_dBEFFlow;				//�û������ֵ
	int 		m_bAntiReverse;			//1��ѡ�����Ʊ÷�ת��0û��ѡ�����Ʊ÷�ת
	int 		m_bExitCheck;			//1��ѡ�����ֹ�ط���0��û��ѡ�����ֹ�ط�
	double		m_dCloseVel;		    //�رշ��ŵ���С�ٶ�
	int         m_nReOpenPressType;
	double  	m_dReOpenPress;			//���´򿪷���Delta(ѹ����ˮͷ)0��ˮͷ1��ѹ��\ѹ��ֵ
	int        	m_bSelSubmerge;         //0��Ǳˮ��û��ѡ��1��Ǳˮ��ѡ��
	int         m_nSubmergePressType;	//ѹ��������0��ˮͷ1��ѹ��
	double      m_dSuctionPress;		//�����ѹ��ֵ
	int         m_nPumpSet;				//�û��飬�����ã��õ������������ã�����+�õ�����,0:����
	int			m_nTranModel;			//��˲��ģ��
	int 		m_nPumpType;			//��ģ�͵�����0�������ߣ�1��ָ���������2��ָ����������
	double   	m_dPumpFlow;			//������С
	double		m_dSpeedRatio;			//���ٱõ�������Ա����ߵ����ʣ�1����ʾ100%��
	int     	m_nPumpControl;			//���Ʊ����ͣ�0��û�п��ƣ���0��û�п��ƣ�1:����ˮͷ  2:����ѹ�� 3:  ���ˮͷ  4: ���ѹ�� 5: ������� 6: ��������
	int     	m_nControlType;			//���Ƶ��������0��ˮͷ/ˮͷ��ʧ/�������1��ѹ��/ѹ����ʧ/��������
	int         m_nPressType;			//0��ͣ��ѹ��1����̬ѹ��
	double   	m_dControlValue;		//���Ƶ����ֵ
	int 		m_nControlApply;         //���ƶ�Ӧ��������ã�0�����ǿ���1��ѹ��������������2��ѹ�����ڿ������ã�
	double      m_dRotateInertia;		//ת���������ã��綯�������壩\ת��������λ
	double      m_dSpeed;				//�öת��
	int         m_nFourQuadrantAngle;   //�Ƕ�ѡ��0��1
	CalcTable<3> m_FourQuadrantData;   //<FH,FB>
public:
	CalcTransData m_TranData;
	CalcPumpConfig m_Config;
};

#endif // !defined(AFX_CALCPUMP_H__92863BD5_5E5F_480C_BE18_CFCC57438D38__INCLUDED_)

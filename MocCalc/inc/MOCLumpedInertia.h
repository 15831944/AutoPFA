// MOCLumpedInertia.h: interface for the MOCLumpedInertia class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MOCLUMPEDINERTIA_H__13F5BAB9_C4AF_4EF0_BAB7_CBF927889470__INCLUDED_)
#define AFX_MOCLUMPEDINERTIA_H__13F5BAB9_C4AF_4EF0_BAB7_CBF927889470__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
class CalcOrifice;
class CalcShortPipe;

class MOCLumpedInertia  
{
public:
	double ElePress();
	double EleChange();
	BOOL IsOrifice();
	double CalcC1(double dPOld1,double dPOld3,double dMassOld);
	double CalcC2(double dMassOld,BOOL bInSys);
	BOOL Read(CalcOrifice &orifice,CalcShortPipe &shortPipe);
	MOCLumpedInertia();
	virtual ~MOCLumpedInertia();

private:
	int	    m_bOrificeModel;		//0��û��ѡ������װ�ģ�ͣ�1��ѡ������װ�ģ��
	double	m_dInFlowCD;			//�׿���������ϵ��
	double	m_dOutFlowCD;			//�׿��������ϵ��
	double	m_dOrificeArea;			//�׿����ֵ
	int		m_bShortPipeModel;		//0��û��ѡ��̹ܵ�ģ�ͣ�1��ѡ��̹ܵ�ģ��
	double	m_dFriction;			//�̹ܵ�Ħ��ϵ��
	double	m_dShortPipeArea;		//�̹ܵ����
	double	m_dInDia;				//�̹ܵ���ֱ��
	double	m_dLen;					//�̹ܵ�����
	double	m_dEle;					//�̹ܵ���߱仯

};

#endif // !defined(AFX_MOCLUMPEDINERTIA_H__13F5BAB9_C4AF_4EF0_BAB7_CBF927889470__INCLUDED_)

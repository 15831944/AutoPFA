// MOCSteady.h: interface for the MOCSteady class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MOCSTEADY_H__CD3C2D89_B8AE_4A7D_922A_4CFEEB2ACCF0__INCLUDED_)
#define AFX_MOCSTEADY_H__CD3C2D89_B8AE_4A7D_922A_4CFEEB2ACCF0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
class CalcSteady;
class MOCComponentMgr;
class SteadyOutModel;

class MOCSteady  
{
public:
	
	void CheckPress(double dOld, double &dNew);
	void CheckFlow(double dOld,double &dNew);
	void CalcStm(MOCComponentMgr &mgr,SteadyOutModel &model);
	BOOL Read(CalcSteady &data);
	MOCSteady();
	virtual ~MOCSteady();

private:
	BOOL CheckRel(double dOld, double dNew,double dEps);
	BOOL CheckAbs(double dOld, double dNew,double dEps);

private:
	void Result(SteadyOutModel &model,int n);
	void Relaxation(double dOld,double &dNew,double dRax);
	int m_PresTolType;			//ѹ���������ͱ�ǣ�0�����Թ��1����Թ���2�����Ի���Թ���3�����Ժ���Թ���
	double m_PresAbsTol;		//ѹ�����Թ���
	double m_PresRelTol;	    //ѹ����Թ���
	int m_FlowTolType;		    //�����������ͱ�ǣ�0�����Թ��1����Թ���2�����Ի���Թ���3�����Ժ���Թ���
	double m_FlowAbsTol;		//�������Թ���
	double m_FlowRelTol;		//������Թ���
	double m_FlowRelaxation;	//�����ɳ�����
	double m_PresRelaxation;	//ѹ���ɳ�����ֵ
	int m_MaxIterations;		//����������ֵ
	BOOL m_bOk;

};

#endif // !defined(AFX_MOCSTEADY_H__CD3C2D89_B8AE_4A7D_922A_4CFEEB2ACCF0__INCLUDED_)

// CaclSteady.h: interface for the CaclSteady class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CACLSTEADY_H__E2CEC3AA_ECC3_4D29_95D0_AD323F9F2C3B__INCLUDED_)
#define AFX_CACLSTEADY_H__E2CEC3AA_ECC3_4D29_95D0_AD323F9F2C3B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class AFX_EXT_CLASS CalcSteady  
{
public:
	CalcSteady();
	virtual ~CalcSteady();

public:
	int AnalysisType();
	void AnalysisType(int nValue);
	void PresTolType(int nValue);
	void PresAbsTolType(int nValue);
	void PresAbsTol(double dValue);
	void PresRelTol(double dValue);
	void FlowTolType(int nValue);
	void FlowAbsTolType(int nValue);
	void FlowAbsTol(double dValue);
	void FlowRelTol(double dValue);
	void MaxIterations(int nValue);
	void KeepHistory(int nValue);
	void FlowRelaxation(double dValue);
	void PresRelaxation(double dValue);

	double FlowRelaxation();
	double PresRelaxation();
	int PresTolType();
	int PresAbsTolType();
	double PresAbsTol();
	double PresRelTol();
	int FlowTolType();
	int FlowAbsTolType();
	double FlowAbsTol();
	double FlowRelTol();
	int MaxIterations();
	int KeepHistory();
	friend ostream& operator<< (ostream &CalcOut,const CalcSteady &ref);
	
private:
	int m_AnalysisType;			//��������������ֱ�ǣ�0��˲̬������1����̬����
	int m_PresTolType;			//ѹ���������ͱ�ǣ�0�����Թ��1����Թ���2�����Ի���Թ���3�����Ժ���Թ���
	int m_PresAbsTolType;        //ѹ������
	double m_PresAbsTol;		//ѹ�����Թ���
	double m_PresRelTol;	    //ѹ����Թ���
	int m_FlowTolType;		    //�����������ͱ�ǣ�0�����Թ��1����Թ���2�����Ի���Թ���3�����Ժ���Թ���
	int m_FlowAbsTolType;        //��������
	double m_FlowAbsTol;		//�������Թ���
	double m_FlowRelTol;		//������Թ���
//	int m_RelaxationType;
	double m_FlowRelaxation;	//�����ɳ�����
	double m_PresRelaxation;	//ѹ���ɳ�����ֵ
	int m_MaxIterations;		//����������ֵ
	int m_KeepHistory;			//0�������������ʷ��¼��1�����������ʷ��¼
//	int m_MatrixMethod;			//������Է����鷽��0����˹��ȥ����1��ѡ��Ԫ�صĸ�˹��ȥ����2����������Ƿֽ⣨LU�ֽ⣩
//	int m_AutoDetect;			//���������ʷ��¼�������
	int m_bUserGiveSteadyInitValue;

};

#endif // !defined(AFX_CACLSTEADY_H__E2CEC3AA_ECC3_4D29_95D0_AD323F9F2C3B__INCLUDED_)

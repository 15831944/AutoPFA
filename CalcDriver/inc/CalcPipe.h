// CalcPipe.h: interface for the CalcPipe class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CALCPIPE_H__4B3888EC_74A9_4FCA_A435_627071F4841C__INCLUDED_)
#define AFX_CALCPIPE_H__4B3888EC_74A9_4FCA_A435_627071F4841C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class AFX_EXT_CLASS CalcPipe  
{
public:
	CalcPipe();
	virtual ~CalcPipe();

public:
	void Key(int nValue);
	void InJunID(int nValue);
	void OutJunID(int nValue);
	void InDia(double dValue);
	void Len(double dValue);
	void InitFlowType(int nValue);
	void InitFlow(double dValue);
	void FitFactor(double dValue);
	void LocalK(double dValue);
	void PipeFactor(double dValue);
	void FrictionModel(int nValue);
	void Friction(double dValue);
	void B(double dValue);
	void WaveSpeed(double dValue);
	void SectionNum(int nValue);
	void InDiaReduce(double dValue);

	int    Key();
	int    InJunID();
	int    OutJunID();
	double InDia();
	double Len();
	int	   InitFlowType();
	double InitFlow();
	double FitFactor();
	double LocalK();
	double PipeFactor();
	int    FrictionModel();
	double Friction();
	double B();
	double WaveSpeed();
	int    SectionNum();
	double InDiaReduce();
	friend ostream& operator<< (ostream &CalcOut,const CalcPipe &ref);

private:
	int m_nKey;						//�ܵ����
	int m_nInJunID;				    //��ڽڵ��ID��
	int m_nOutJunID;				//���ڽڵ��ID��
	double m_dInDia;				//�ܵ��ھ�
	double m_dLen;				    //�ܵ�����
	int m_nInEleNum;				//�ڲ��ܶ���������ѭ��<��ʼ����� �߳�>
	int m_nPartFull;				//�Ƿ����ſչ�
	double m_dFullRate;				//��ʼ������
	int  m_nInitFlowType;			//��ʼ������²����ͣ�0�����1������2�����٣�
	double m_dInitFlow;				//��ʼ������²��С
	double m_dPipeFactor;			//�ܵ�Ħ����������ӣ�
	double m_dFitFactor;			//�ܵ�������ʧ�������
	double m_dLocalK;				//�ܹ��ֲ���Kϵ��
	int m_nFrictionModel;			//Friction Model����:
	double m_dFriction;				//Ħ��ϵ����С
	double m_dWaveSpeed;			//�ܵ��ֶ���������ֵ�����٣�
	int m_nSectionNum;				//�ܶηֶ���ȡ��
	double m_dInDiaReduce;			//��ֱ�����ٰٷֱ�
	double m_dB;                    //B(��λ������ת�����ݲ��ټ���)
};

#endif // !defined(AFX_CALCPIPE_H__4B3888EC_74A9_4FCA_A435_627071F4841C__INCLUDED_)

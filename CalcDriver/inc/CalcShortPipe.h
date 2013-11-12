// CalcShortPipe.h: interface for the CalcShortPipe class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CALCSHORTPIPE_H__D678D756_7266_4EDD_8F4C_C79898364566__INCLUDED_)
#define AFX_CALCSHORTPIPE_H__D678D756_7266_4EDD_8F4C_C79898364566__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class AFX_EXT_CLASS CalcShortPipe  
{
public:
	CalcShortPipe();
	virtual ~CalcShortPipe();
public:
	void Model(int nValue);
	void Friction(double dValue);
	void Area(double dValue);
	void InDia(double dValue);
	void Len(double dValue);
	void Ele(double dValue);

	int Model();
	double Friction();
	double Area();
	double InDia();
	double Len();
	double Ele();
    friend	ostream& operator<< (ostream &CalcOut,const CalcShortPipe &ref);
private:
	int		m_bModel;				//0��û��ѡ��̹ܵ�ģ�ͣ�1��ѡ��̹ܵ�ģ��
	double	m_dFriction;			//�̹ܵ�Ħ��ϵ��
	double	m_dArea;				//�̹ܵ����
	double	m_dInDia;				//�̹ܵ���ֱ��
	double	m_dLen;					//�̹ܵ�����
	double	m_dEle;					//�̹ܵ���߱仯
};

#endif // !defined(AFX_CALCSHORTPIPE_H__D678D756_7266_4EDD_8F4C_C79898364566__INCLUDED_)

// CalcTriger.h: interface for the CalcTriger class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CALCTRIGER_H__3A9704DE_8FE1_4E75_B55E_0E3F56BC2524__INCLUDED_)
#define AFX_CALCTRIGER_H__3A9704DE_8FE1_4E75_B55E_0E3F56BC2524__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class AFX_EXT_CLASS CalcTriger  
{
public:
	CalcTriger();
	virtual ~CalcTriger();
public:
	int EventType();
	int ConditionType();
	double Value();
	int Port1();
	int ComponentID1();
	int Port2();
	int ComponentID2();

	void EventType(int nValue);
	void ConditionType(int nValue);
	void Value(double dValue);
	void Port1(int nValue);
	void ComponentID1(int nValue);
	void Port2(int nValue);
	void ComponentID2(int nValue);
	friend ostream& operator<< (ostream &CalcOut,const CalcTriger &ref);
private:
	int m_nEventType;                //�¼�����
	int m_nConditionType;			 //��������
	double	m_dValue;				 //ֵ
	int m_nPort1;					 //�ܵ���ڴ����¼�Ϊ1���ܵ����ڴ����¼�Ϊ2
	int m_nComponentID1;			 //�����¼���������
	int m_nPort2;					 //�ܵ���ڴ����¼�Ϊ1���ܵ����ڴ����¼�Ϊ2
	int m_nComponentID2;			 //�����¼���������		
};

#endif // !defined(AFX_CALCTRIGER_H__3A9704DE_8FE1_4E75_B55E_0E3F56BC2524__INCLUDED_)

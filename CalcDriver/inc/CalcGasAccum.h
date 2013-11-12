// CalcGasAccum.h: interface for the CalcGasAccum class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CALCGASACCUM_H__8E4F8A55_1BC8_4BB4_87F4_59FC4A5F8381__INCLUDED_)
#define AFX_CALCGASACCUM_H__8E4F8A55_1BC8_4BB4_87F4_59FC4A5F8381__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CalcJun.h"
#include "CalcOrifice.h"
#include "CalcShortPipe.h"

class AFX_EXT_CLASS CalcGasAccum : public CalcJun  
{
public:
	ostream& Write(ostream& CalcOut);
	static CalcJun* Creator();
	CalcGasAccum();
	virtual ~CalcGasAccum();
public:
	void Polytropic(double dValue);
	void Type(int nValue);
	void InitVolume(double dValue);
	void RefPress(double dValue);
	void MaxVolume(double dValue);
	void MinVolume(double dValue);
	void SelInitPress(int nValue);
	void InitPressType(int nValue);
	void InitPress(double dValue);

	double Polytropic();
	int Type();
	double InitVolume();
	double RefPress();
	double MaxVolume();
	double MinVolume();
	int SelInitPress();
	int InitPressType();
	double InitPress();
private:
	double		  m_dPolytropic;					//�仯�ĳ���
	int           m_nType;						    //���ͣ�0����ʼ��ָ�������1����ʼ��ָ��ѹ����
	double	      m_dInitVolume;					//��ʼ��������
	double        m_dRefPress;				        //�ο�����ѹ��
	double		  m_dMaxVolume;					    //������
	double		  m_dMinVolume;					    //��С���											
	int			  m_bSelInitPress;					//��̬������ѹ����0��û��ѡ��1ѡ�У�
	int           m_nInitPressType;					//ѹ�����ͣ�0ˮͷ��1��ѹ����
	double        m_dInitPress;					    //��ʼ��ѹ��

public:
	CalcOrifice   m_Orifice;					
	CalcShortPipe m_ShortPipe;	
};

#endif // !defined(AFX_CALCGASACCUM_H__8E4F8A55_1BC8_4BB4_87F4_59FC4A5F8381__INCLUDED_)

// MOCBrecker.h: interface for the MOCBrecker class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MOCBRECKER_H__EADA4B80_1AB7_4866_A154_C962198D351C__INCLUDED_)
#define AFX_MOCBRECKER_H__EADA4B80_1AB7_4866_A154_C962198D351C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MOCJun.h"
#include "GasProperty.h"

class MOCBrecker : public MOCJun  
{
public:
	void UpdataEnd();
	BOOL Read(CalcJun *pData);
	static MOCJun* Creator();
	MOCBrecker();
	virtual ~MOCBrecker();

private:
	void CalcStm();
	BOOL InitEndInfo();

private:
	void CheckIsClose();
	BOOL IsCrack();
	void CalcImpulse(MOCTrans &trans,double dTime);
	int			m_nType;			             //��������0:����ƻ��������ͷ�1:����ƻ�2:�����ͷ�3:����ƻ������׶������ͷ�
	double      m_dOrificeInCdA;		         //�׿�ȫ�����������ֵ
	double      m_dOrificeOutCdA;			     //�������ֵ/��λ
	double      m_dInterMediateCdA;			     //�׿�ȫ����ý���������ֵ
	int		    m_nMediateActivationType;		 //ý��׿ڼ����׼0��ѹ����ͬ1�����ٲ�ͬ
	double      m_dMediateActivation;            //��׼ֵ
	double		m_dCrackPress;				     //���ѵ�ѹ��
	int			m_nConnectPipe;					 //���ӹܵ���0�������ܵ�1��һ���ܵ�
	GasProperty m_GasPropety;

	BOOL m_bClose;                              //��������״̬
};

#endif // !defined(AFX_MOCBRECKER_H__EADA4B80_1AB7_4866_A154_C962198D351C__INCLUDED_)

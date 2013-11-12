// MOCBend.h: interface for the MOCBend class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MOCBEND_H__B15F08EE_23F5_465E_BEEB_A20EE5039BE2__INCLUDED_)
#define AFX_MOCBEND_H__B15F08EE_23F5_465E_BEEB_A20EE5039BE2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MOCJun.h"

class MOCBend : public MOCJun  
{
public:
	BOOL Read(CalcJun *pData);
	static MOCJun* Creator();
	MOCBend();
	virtual ~MOCBend();

private:
	void CalcStm();
	BOOL InitEndInfo();

private:
	void CalcImpulse(MOCTrans &trans,double dTime);
	void UpdataEnd();
	double  m_dK;								//Kϵ��ֵ
	int     m_nBasisAreaType;					//��ʧģ�͵��������0��Ĭ�����ιܵ������1�����ιܵ����2���û�ָ�����3���û�ָ��ֱ��
	double  m_dBasisArea;						//���Ŷorֱ��
};

#endif // !defined(AFX_MOCBEND_H__B15F08EE_23F5_465E_BEEB_A20EE5039BE2__INCLUDED_)

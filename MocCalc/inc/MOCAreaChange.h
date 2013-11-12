// MOCAreaChange.h: interface for the MOCAreaChange class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MOCAREACHANGE_H__00191752_C0E3_44BB_BA42_07251D7C0F5B__INCLUDED_)
#define AFX_MOCAREACHANGE_H__00191752_C0E3_44BB_BA42_07251D7C0F5B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MOCJun.h"

class MOCAreaChange : public MOCJun  
{
public:
	BOOL Read(CalcJun *pData);
	static MOCJun* Creator();
	MOCAreaChange();
	virtual ~MOCAreaChange();

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

#endif // !defined(AFX_MOCAREACHANGE_H__00191752_C0E3_44BB_BA42_07251D7C0F5B__INCLUDED_)

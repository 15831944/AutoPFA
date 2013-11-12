// MOCReservior.h: interface for the MOCReservior class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MOCRESERVIOR_H__B18CE93B_F966_4B4C_9E86_5E7F4E557540__INCLUDED_)
#define AFX_MOCRESERVIOR_H__B18CE93B_F966_4B4C_9E86_5E7F4E557540__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MOCJun.h"
#include "MOCTranData.h"

class MOCReservior : public MOCJun  
{
public:
	BOOL Read(CalcJun *pData);
	static MOCJun* Creator();
	MOCReservior();
	virtual ~MOCReservior();

private:
	void CalcStm();
	BOOL InitEndInfo();

private:
	void SetTransZ(double dZ);
	void CalcImpulse(MOCTrans &trans,double dTime);
	BOOL InitTranData(MOCComponentMgr &mgr);
	void UpdataEnd();
	void InitPipeInfo(double dEle);
	double		 m_dSurfacePress;				//����ѹ��ֵ
	int			 m_nEleOrDepthType;			    //�ܵ���ˮ�����ӵ��߻�(���0)
	ListImp<StrArray<6> > m_PipeInfo;				
												//1�����ӹܵ������ֱ�ţ��ӽڵ������Ӹ��ţ�
												//2  ����
												//2������ӽڵ�����ܵ�ʱ�ܵ��˿�kϵ��
												//3������ӽڵ������ܵ�ʱ�ܵ��˿�kϵ��
												//4��r/d���˿ڵ�԰���ȣ�
												//5���ܵ���߻����

	MOCTranData m_tranData;
};

#endif // !defined(AFX_MOCRESERVIOR_H__B18CE93B_F966_4B4C_9E86_5E7F4E557540__INCLUDED_)

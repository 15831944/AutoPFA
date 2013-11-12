// MOCTeeWye.h: interface for the MOCTeeWye class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MOCTEEWYE_H__896D969D_C348_415A_9B98_3B0AF17CAFB5__INCLUDED_)
#define AFX_MOCTEEWYE_H__896D969D_C348_415A_9B98_3B0AF17CAFB5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MOCJun.h"

class MOCTeeWye : public MOCJun  
{
public:
	void UpdataEnd();
	BOOL Read(CalcJun *pData);
	static MOCJun* Creator();
	MOCTeeWye();
	virtual ~MOCTeeWye();

private:
	void CalcStm();
	BOOL InitEndInfo();

private:
	void CalcImpulse(MOCTrans &trans,double dTime);
	void CalcStmDetail();
	void CalcStmSimple();
	double ConvergeLosskcst(EndInfo *pAsEnd,EndInfo *pAcEnd,double Angle);
	double LossKcs(EndInfo *pAcEnd,EndInfo *pAsEnd,double Angle);
	double Losskcst(EndInfo *pAsEnd,EndInfo *pAstEnd,EndInfo *pAcEnd,double Angle);
	double ConvergeLossKcs(EndInfo *pAcEnd,EndInfo *pAsEnd,EndInfo *pAstEnd,double Angle);
	ListImp<StrArray<1> > m_PipeID;	
	double m_dAngle;			//�Ƕ�
	int    m_nModel;			//��ʧģ�����ͣ�1����ģ��2����ϸģ�ͣ�
	int    m_nType;			    //���ͣ�0�����ֱ��ͨ1��Բ��ֱ��ͨ2������ı�3���Գƣ�
};

#endif // !defined(AFX_MOCTEEWYE_H__896D969D_C348_415A_9B98_3B0AF17CAFB5__INCLUDED_)

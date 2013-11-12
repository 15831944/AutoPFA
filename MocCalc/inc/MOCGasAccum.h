// MOCGasAccum.h: interface for the MOCGasAccum class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MOCGASACCUM_H__91BFA432_2356_4699_AF34_707BF5B6953F__INCLUDED_)
#define AFX_MOCGASACCUM_H__91BFA432_2356_4699_AF34_707BF5B6953F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MOCJun.h"
#include "MOCLumpedInertia.h"

class MOCGasAccum : public MOCJun  
{
public:
	BOOL Read(CalcJun *pData);
	static MOCJun* Creator();
	MOCGasAccum();
	virtual ~MOCGasAccum();

private:
	void CalcStm();
	BOOL InitEndInfo();

private:
	void Result(JunTranOut &out, int nStep);
	BOOL InitTranData(MOCComponentMgr &mgr);
	void CalcImpulse(MOCTrans &trans,double dTime);
	void UpdataEnd();
	double		  m_dPolytropic;					//�仯�ĳ���
	int           m_nType;						    //���ͣ�0����ʼ��ָ�������1����ʼ��ָ��ѹ����
	double	      m_dInitVolume;					//��ʼ��������
	double        m_dRefPress;				        //�ο�����ѹ��
	double		  m_dMaxVolume;					    //������
	double		  m_dMinVolume;					    //��С���											
	int			  m_bSelInitPress;					//��̬������ѹ����0��û��ѡ��1ѡ�У�
	double        m_dInitPress;					    //��ʼ��ѹ��
	MOCLumpedInertia m_lumpedInertia;                //��������

	double m_dMass;                                  //˲̬����ϵͳ����
	double m_dCA;                                    //���ݳ��������ѹ������ĳ���
};

#endif // !defined(AFX_MOCGASACCUM_H__91BFA432_2356_4699_AF34_707BF5B6953F__INCLUDED_)

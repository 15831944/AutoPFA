// MOCSurge.h: interface for the MOCSurge class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MOCSURGE_H__3083F755_42C7_4C4A_A936_B7CE5BA6D680__INCLUDED_)
#define AFX_MOCSURGE_H__3083F755_42C7_4C4A_A936_B7CE5BA6D680__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MOCJun.h"
#include "MOCLumpedInertia.h"
#include "MOCTranData.h"
#include "MOCTable.h"

class MOCSurge : public MOCJun  
{
public:
	double GetLiquldHeight();
	double GetGL();
	BOOL Read(CalcJun *pData);
	static MOCJun* Creator();
	MOCSurge();
	virtual ~MOCSurge();

private:
	void CalcStm();
	BOOL InitEndInfo();

private:
	void Result(JunTranOut &out, int nStep);
	double GetArea(double dH);
	void CalcImpulse(MOCTrans &trans,double dTime);
	BOOL InitTranData(MOCComponentMgr &mgr);
	void UpdataEnd();
    ListImp<StrArray<4> >	m_PipeInfo;
	double			 m_dSurfacePress;				//����ѹ��
	double			 m_dSurgeHeight;				//��ѹ���ĸ߶�
	double			 m_dConstArea;					//�����ֵ
	DataTable        m_AreaTable;			
	int 			 m_bOneWay;						//��One-Way Surge Tank��0��û��ѡ��1ѡ������ģ��ֹ�ط������Ļ���ޡ�
	double           m_dCheckCv;					//ֹ�ط�����ϵ��
	int              m_nPosition;					//ֹ�ط���ʼλ��0����1���ر�
	double	         m_dReOpenPress;				//ѹ��ֵ         
	int     		 m_bSelVessel;					//ģ���������0��û��ѡ��1��ѡ��
	double           m_dVesselHeight;				//������ܵ��ܵ��ĸ߶�
	double			 m_dPolytropic;					//���ĳ���
	int              m_bSelSurfaceH;				//�ȶ�״̬��ʼ������߶�0��û��ѡ��1��ѡ��
	double			 m_dInitSurfaceH;	        	//�߶�ֵ
	MOCLumpedInertia m_lumpedInertia;               //��������
	MOCTranData m_tranData;

	double m_dLiquldHeight;
	double m_dMass;
};
inline double MOCSurge::GetLiquldHeight()
{
	return m_dLiquldHeight;
}

#endif // !defined(AFX_MOCSURGE_H__3083F755_42C7_4C4A_A936_B7CE5BA6D680__INCLUDED_)

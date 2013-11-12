// CalcSurge.h: interface for the CalcSurge class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CALCSURGE_H__871F151C_432F_441D_B83C_90D5C5559CC4__INCLUDED_)
#define AFX_CALCSURGE_H__871F151C_432F_441D_B83C_90D5C5559CC4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CalcJun.h"
#include "CalcOrifice.h"
#include "CalcShortPipe.h"
#include "CalcTransData.h"

class AFX_EXT_CLASS CalcSurge : public CalcJun  
{
public:
	ostream& Write(ostream& CalcOut);
	static CalcJun* Creator();
	CalcSurge();
	virtual ~CalcSurge();
public:
	void PipeInfo(const ListImp<StrArray<4> >& ref);
	void AreaTable(const ListImp<StrArray<2> >& ref);
	void SurfacePress(double dValue);
	void SurgeHeight(double dValue);
	void ConstArea(double dValue);
	void OneWay(int nValue);
	void CheckCv(double dValue);
	void Position(int nValue);
	void ReOpenPressType(int nValue);
	void ReOpenPress(double dValue);
	void SelVessel(int nValue);
	void VesselHeight(double dValue);
	void Polytropic(double dValue);
	void SelSurfaceH(int nValue);
	void InitSurfaceH(double dValue);


	ListImp<StrArray<4> >& PipeInfo();
	ListImp<StrArray<2> >& AreaTable();
	double SurfacePress();
	double SurgeHeight();
	double ConstArea();
	int OneWay();
	double CheckCv();
	int Position();
	int ReOpenPressType();
	double ReOpenPress();
	int SelVessel();
	double VesselHeight();
	double Polytropic();
	int SelSurfaceH();
	double InitSurfaceH();
private:
    CalcTable<4>	 m_PipeInfo;
	double			 m_dSurfacePress;				//����ѹ��
	double			 m_dSurgeHeight;				//��ѹ���ĸ߶�
	double			 m_dConstArea;					//�����ֵ
	CalcTable<2>     m_AreaTable;			
	int 			 m_bOneWay;						//��One-Way Surge Tank��0��û��ѡ��1ѡ������ģ��ֹ�ط������Ļ���ޡ�
	double           m_dCheckCv;						//ֹ�ط�����ϵ��
	int              m_nPosition;					//ֹ�ط���ʼλ��0����1���ر�
	int				 m_nReOpenPressType;			//���´򿪷���Delta(ѹ����ˮͷ)0��ˮͷ1��ѹ��
	double	         m_dReOpenPress;				//ѹ��ֵ         
	int     		 m_bSelVessel;					//ģ���������0��û��ѡ��1��ѡ��
	double           m_dVesselHeight;				//������ܵ��ܵ��ĸ߶�
	double			 m_dPolytropic;					//���ĳ���
	int              m_bSelSurfaceH;				//�ȶ�״̬��ʼ������߶�0��û��ѡ��1��ѡ��
	double			 m_dInitSurfaceH;	        	//�߶�ֵ	
													
public:
	CalcOrifice		 m_Orifice;					
	CalcShortPipe	 m_ShortPipe;
	CalcTransData	 m_TranData;
										
};

#endif // !defined(AFX_CALCSURGE_H__871F151C_432F_441D_B83C_90D5C5559CC4__INCLUDED_)

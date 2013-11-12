// ReserviorData.h: interface for the ReserviorData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RESERVIORDATA_H__656463BB_6674_44FE_986F_9F5AF78E7037__INCLUDED_)
#define AFX_RESERVIORDATA_H__656463BB_6674_44FE_986F_9F5AF78E7037__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//ˮ��
#include "Junction.h"
#include "JunTransData.h"

class AFX_EXT_CLASS ReserviorData : public JunctionData  
{
public:
	static JunctionData* Creator();
	ReserviorData();
	virtual ~ReserviorData();
public:
	ListImp<StrArray<6> > PipeInfo();
	void PipeInfo(const ListImp<StrArray<6> >& strValue);
	StrArray<2> EleOrDepth();
	void EleOrDepth(const StrArray<2>& strValue);
	StrArray<2> SurfacePress();
	void SurfacePress(const StrArray<2>& strValue);
	StrArray<2> Teamperature();
	void Teamperature(const StrArray<2>& strValue);
	StrArray<2> Density();
	void Density(const StrArray<2>& strValue);
	CString EleOrDepthType();
	void EleOrDepthType(CString strValue);
private:
	void AppendArray();
	void InitExtra(CString strData);
	virtual CString GetDefaultData();
public:
	JunTransData m_TranData;	
private:
	TableData<5> m_linkPipeK;			//����ӽڵ�����ܵ�ʱ�ܵ��˿�kϵ��
										//����ӽڵ������ܵ�ʱ�ܵ��˿�kϵ��
										//�ܿ����ͣ�0���û���1����ǳ��ڣ�2��Բ�ǳ��ڣ�3�����ͻ�߳��ڣ�
										//r/d
										//�ܵ���߻����ֵ
	RowObjectFace<2> m_EleOrDepth;		//�ܵ���߻����\��λ
	RowObjectFace<2> m_SurfacePress;	//����ѹ��ֵ\��λ
	RowObjectFace<2> m_Teamperature;	//�����¶�\��λ
	RowObjectFace<2> m_Density;			//�����ܶ�\��λ
	RowObjectFace<2> m_UnKown;			//0��δ֪��\0��δ֪��
	RowObjectFace<1> m_EleOrDepthType;	//�ܵ���߻����(-1,0)
	//JunTransData m_TranData;			//û�����ں���RowObjectFace<5> m_Periodic;
	RowObjectFace<5>  m_Fth2_1;         //
	RowObjectFace<14> m_Fth2;           //��������������м�����ݼ�¼��ˮ��ı��.
	RowObjectFace<2>  m_Fth3;

};

#endif // !defined(AFX_RESERVIORDATA_H__656463BB_6674_44FE_986F_9F5AF78E7037__INCLUDED_)

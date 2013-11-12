// introlValveData.h: interface for the CintrolValveData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INTROLVALVEDATA_H__024B4285_7EBB_44D0_967B_0097F3FEEBD1__INCLUDED_)
#define AFX_INTROLVALVEDATA_H__024B4285_7EBB_44D0_967B_0097F3FEEBD1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Junction.h"
#include "JunTransData.h"
//�������Ʒ�
class AFX_EXT_CLASS ControlValveData : public JunctionData  
{
public:
	static JunctionData* Creator();
	ControlValveData();
	virtual ~ControlValveData();
public:
	StrArray<5> ControlSet();
	void ControlSet(const StrArray<5>& strValue);
	CString ModelType();
	void ModelType(CString strValue);
	CString KOrCv();
	void KOrCv(CString strValue);
	StrArray<4> FailAction();
	void FailAction(const StrArray<4>& strValue);
	StrArray<3> KOrCvUnit();
	void KOrCvUnit(const StrArray<3>& strValue);
	ListImp<StrArray<3> > KOrCvData();
	void KOrCvData(const ListImp<StrArray<3> >& strValue);
private:
	int KOrCvNum();
	int DataUnitNum();
	void AppendArray();
	void InitExtra(CString strData);
	virtual CString GetDefaultData();
public:
	JunTransData m_TranData;
	JunTransData m_FailTranData;
private:
	RowObjectFace<5> m_ControlSet;				//��������0��PRF 1��PSV 2��FCV 3��PDCV
												//���Ƶ��������0��ˮͷ/ˮͷ��ʧ/�������1��ѹ��/ѹ����ʧ/��������
												//0��ͣ��ѹ��1����̬ѹ��
												//���Ƶ����ֵ
												//���Ƶ������λ
	RowObjectFace<2> m_UnKown;					//-2��δ֪��\0��δ֪��
	RowObjectFace<1> m_ModelType;				//��ʧģ��(0������ϵ��ģ�ͣ�1��Kϵ��ģ�� -2��ʹ��ϵ�����ֵ)
	RowObjectFace<1> m_KOrCv;					//K��Cvϵ��ֵ
	RowObjectFace<1> m_UnKown4;					//none 
	RowObjectFace<1> m_DataUnitNum;				//1(�򿪰ٷֱȣ�K/CVϵ��)2(�򿪰ٷֱȵ�λ\K/CVϵ����λ\���������λ)
	RowObjectFace<1> m_KOrCvNum;				//����ϵ�������ݵ�����

	ThreeDTable      m_KOrCvData;				//�򿪰ٷֱȵ�λ\K/CVϵ����λ\���������λ
												//�򿪰ٷֱȣ�K/CVϵ�����������ֵ

	//JunTransData m_TranData;					//û�����ں���RowObjectFace<5> m_Periodic;
												//û��RowObjectFace<1> m_Special;
												//û��TwoDTable m_Trans2Table;

	//JunTransData m_FailTranData;				//û��RowObjectFace<1> m_Special;
												//û�����ں���RowObjectFace<5> m_Periodic;
												//û��RowObjectFace<1> m_Repeat1;
												//û��RowObjectFace<1> m_Repeat2
												//û��RowObjectFace<1> m_TranType;
												//û��RowObjectFace<8> m_TranTriger1; 
												//û��RowObjectFace<8> m_TranTriger2; 
	RowObjectFace<3> m_UnKown5;					//0,0,None
	RowObjectFace<4> m_failAction;				//�ȶ�״̬���ǿ���0��û��ѡ�� 1��ѡ��
												//ʹ��Ĭ�ϵ���Ϊ  0��û��ѡ�� 1��ѡ��
												//����ѹ���������0��ȫ���� 1���ر�
												//����ѹ����������0��ȫ���� 1���ر�
	RowObjectFace<2> m_FthUnknown;				//0,1;
	RowObjectFace<5> m_FthUnknown1;				//0,None,0,0,NA
	RowObjectFace<1> m_FthAssert1;    
	RowObjectFace<1> m_FthAssert2;



};

#endif // !defined(AFX_INTROLVALVEDATA_H__024B4285_7EBB_44D0_967B_0097F3FEEBD1__INCLUDED_)

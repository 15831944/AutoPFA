// ReliefData.h: interface for the ReliefData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RELIEFDATA_H__1D9B9CC2_81D1_4716_BFCE_E4ADF95D5CB5__INCLUDED_)
#define AFX_RELIEFDATA_H__1D9B9CC2_81D1_4716_BFCE_E4ADF95D5CB5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Junction.h"
#include "JunTransData.h"
//��ȫ��
class AFX_EXT_CLASS ReliefData : public JunctionData  
{
public:
	static JunctionData* Creator();
	ReliefData();
	virtual ~ReliefData();
public:
	CString Type();
	void Type(CString strValue);
	StrArray<13> Curve();
	void Curve(const StrArray<13>& strValue);
	StrArray<5> CrackExitPress();
	void CrackExitPress(const StrArray<5>& strValue);
	CString KOrCv();
	void KOrCv(CString strValue);
	StrArray<3> BasisArea();
	void BasisArea(const StrArray<3>& strValue);
private:
	void AppendArray();
	void InitExtra(CString strData);
	virtual CString GetDefaultData();
public:
	JunTransData m_TranData;
private:
	RowObjectFace<1> m_Type;			//����(1:�ڲ���ȫ����internal relief��2:���ڰ�ȫ����exit relief��3:��Ƕ��ȫ����inline relief��)
	VariableFace<13,7> m_Curve;			//��ʧģ��(0������ϵ��ģ�ͣ�1��Kϵ��ģ��3��������ϵ��)
										//Y������������ֱ��[]
										//Y�������λ[]
										//X������������ֱ��[]
										//X�������λ[]
										//x�����ȡֵ[]
										//��������[�������ͣ�-2��Kֵ�仯��1��ѹ����ʧ����ʽ��2��ѹ����ʧ�ڲ�ֵ��]
										//��ʽ�в����ͳ����ĸ���[]
										//��ʽ�еĲ����ͳ���a��b��c��d��e��ֵ[]
	RowObjectFace<1> m_UnKown;			//1��δ֪��
	RowObjectFace<5> m_CrackExitPress;	//ѹ��/ˮͷ����0������ˮͷ1������ѹ��2��ˮͷ��3��ѹ����
										//����ѹ��\��λ
										//����ѹ��\��λ
	RowObjectFace<1> m_KOrCv;			//K��Cvϵ��ֵ
	RowObjectFace<3> m_BasisArea;		//��ʧģ�͵��������0��Ĭ�����ιܵ������1�����ιܵ����2���û�ָ�����3���û�ָ��ֱ��
										//ֵ
										//��λ
	//JunTransData m_TranData;			//û�����ں���RowObjectFace<5> m_Periodic;
										//û��RowObjectFace<1> m_Repeat1;
										//û��RowObjectFace<1> m_Repeat2
										//û��RowObjectFace<1> m_TranType;
										//û��RowObjectFace<8> m_TranTriger1; 
										//û��RowObjectFace<8> m_TranTriger2; 
	RowObjectFace<2> m_FthRestrictedFlowArea ;    //,22,feet2,��λ
	
};

#endif // !defined(AFX_RELIEFDATA_H__1D9B9CC2_81D1_4716_BFCE_E4ADF95D5CB5__INCLUDED_)

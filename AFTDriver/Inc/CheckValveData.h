// heckValveData.h: interface for the CheckValveData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HECKVALVEDATA_H__9A86B333_4BC0_4B37_AD76_EBFB375120BF__INCLUDED_)
#define AFX_HECKVALVEDATA_H__9A86B333_4BC0_4B37_AD76_EBFB375120BF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Junction.h"
#include "JunTransData.h"
//ֹ�ط�
class AFX_EXT_CLASS CheckValveData : public JunctionData  
{
public:
	static JunctionData* Creator();
	CheckValveData();
	virtual ~CheckValveData();
public:
	StrArray<13> Curve();
	void Curve(const StrArray<13>& strValue);
	StrArray<3> ReOpenPress();
	void ReOpenPress(const StrArray<3>& strValue);
	CString KOrCv();
	void KOrCv(CString strValue);
	StrArray<3> BasisArea();
	void BasisArea(const StrArray<3>& strValue);
	StrArray<2> CloseVel();
	void CloseVel(const StrArray<2>& strValue);
private:
	void AppendArray();
	void InitExtra(CString strData);
	virtual CString GetDefaultData();
public:
	JunTransData m_TranData;
private:
	VariableFace<13,7> m_Curve;			//��ʧģ��(0������ϵ��ģ�ͣ�1��Kϵ��ģ��)
										//Y������������ֱ��[]
										//Y�������λ[]
										//X������������ֱ��[]
										//X�������λ[]
										//x�����ȡֵ[]
										//��������[�������ͣ�-2��Kֵ�仯��1��ѹ����ʧ����ʽ��2��ѹ����ʧ�ڲ�ֵ��]
										//��ʽ�в����ͳ����ĸ���[]
										//��ʽ�еĲ����ͳ���a��b��c��d��e��ֵ[]
	RowObjectFace<1> m_UnKown;			//0��δ֪��//�ο�AssignFlowData::m_InitPress
	RowObjectFace<3> m_ReOpenPress;		//���´򿪷���Delta(ѹ����ˮͷ)0��ˮͷ1��ѹ��\ѹ��ֵ\��λ
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
	RowObjectFace<2> m_CloseVel;		//�رշ��ŵ���С�ٶ�\�ٶȵ�λ
	RowObjectFace<2> m_FthRestrictedArea; //ֵ/��λ��
	RowObjectFace<9> m_FthUnknown;		//None,2,0,inches,None,None,0,0,NA,
	


};

#endif // !defined(AFX_HECKVALVEDATA_H__9A86B333_4BC0_4B37_AD76_EBFB375120BF__INCLUDED_)

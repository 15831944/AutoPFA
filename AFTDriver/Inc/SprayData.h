// SprayData.h: interface for the SprayData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPRAYDATA_H__32EE6AFA_8995_40AC_9D64_10F5D126A036__INCLUDED_)
#define AFX_SPRAYDATA_H__32EE6AFA_8995_40AC_9D64_10F5D126A036__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//����ܿ�
#include "Junction.h"
#include "JunTransData.h"

class AFX_EXT_CLASS SprayData : public JunctionData  
{
public:
	static JunctionData* Creator();
	SprayData();
	virtual ~SprayData();
public:
	CString Type();
	void Type(CString strValue);
	StrArray<13> Curve();
	void Curve(const StrArray<13>& strValue);
	StrArray<3> ExitArea();
	void ExitArea(const StrArray<3>& strValue);
	CString KOrCv();
	void KOrCv(CString strValue);
	StrArray<3> ExitPress();
	void ExitPress(const StrArray<3>& strValue);
	//6.0�¹ܵ�����������Kϵ���͹ܵ��˿���ڵ���
	ListImp<StrArray<4> > PipeInfo();
	void PipeInfo(const ListImp<StrArray<4> >& strValue);
	CString DistanceUnit();
	void DistanceUnit(CString strValue);
private:
	void AppendArray();
	void InitExtra(CString strData);
	virtual CString GetDefaultData();
public:
	JunTransData m_TranData;	
private:
	RowObjectFace<1> m_Type;			//����(Spray����0������ܿ�1������)
	VariableFace<13,7> m_Curve;			//��ʧģ��(0������ϵ��1��Kϵ��(fire sprinklers Kֵ�Ķ����ǣ� K = Q/sqrt(dP))
										//Y������������ֱ��[ѡKϵ��������ֵΪ��1]
										//Y�������λ[sqrt(dP)�ĵ�λ]
										//X������������ֱ��[����������ͣ�0���������]
										//X�������λ[�����ĵ�λ]
										//x�����ȡֵ[δʹ��]
										//��������[δʹ��]
										//��ʽ�в����ͳ����ĸ���[δʹ��]
										//��ʽ�еĲ����ͳ���a��b��c��d��e��ֵ[δʹ��]
	RowObjectFace<3> m_SprayArea;		//�����׿ڵ����\�����λ\����׵�����
	RowObjectFace<1> m_KOrCv;			//K��Cvϵ��ֵ
	RowObjectFace<3> m_ExitPress;	    //����ѹ��������0��ˮͷ1��ѹ��
										//ѹ��ֵ
										//��λ
	//JunTransData m_TranData;			//û�����ں���RowObjectFace<5> m_Periodic;
	//6.0�¶����0,None,None,0,0,NA,0,None,��8��,�����������	
	RowObjectFace<2> m_Sparyfth1 ;		//6.0�¶��"0,None,"2��
										//���һ��,����m_EleUnit	
	RowObjectFace<5> m_Sparyfth2 ;		//6.0�¶����0,0,NA,0,None,��5��
	//6.0�¹ܵ�����������Kϵ���͹ܵ��˿���ڵ���
	TableData<3> m_linkPipeK;			//����ӽڵ�����ܵ�ʱ�ܵ��˿�kϵ��
										//����ӽڵ������ܵ�ʱ�ܵ��˿�kϵ��
										//�ܵ��˿���ڵ��߾���
	RowObjectFace<1> m_EleUnit;			//�ܵ��˿���ڵ��߾��뵥λ
};

#endif // !defined(AFX_SPRAYDATA_H__32EE6AFA_8995_40AC_9D64_10F5D126A036__INCLUDED_)

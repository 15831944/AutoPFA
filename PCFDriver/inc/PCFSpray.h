// PCFSpray.h: interface for the PCFSpray class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PCFSPRAY_H__32EE6AFA_8995_40AC_9D64_10F5D126A036__INCLUDED_)
#define AFX_PCFSPRAY_H__32EE6AFA_8995_40AC_9D64_10F5D126A036__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PCFJun.h"
#include "RowObjectFace.h"

class AFX_EXT_CLASS PCFSpray : public PCFJun  
{
public:
	static PCFJun* Creator();
	PCFSpray();
	virtual ~PCFSpray();
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

	void Init( const CStringArray& wordArray );
	
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
};

#endif // !defined(AFX_PCFSPRAY_H__32EE6AFA_8995_40AC_9D64_10F5D126A036__INCLUDED_)

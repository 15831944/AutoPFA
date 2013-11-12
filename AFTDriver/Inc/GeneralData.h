// GeneralData.h: interface for the GeneralData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GENERALDATA_H__56A00CC8_089F_47AC_92FA_14F934745960__INCLUDED_)
#define AFX_GENERALDATA_H__56A00CC8_089F_47AC_92FA_14F934745960__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Junction.h"
//ͨ������Ԫ��
class AFX_EXT_CLASS GeneralData : public JunctionData  
{
public:
	static JunctionData* Creator();
	GeneralData();
	virtual ~GeneralData();

public:
	CString Type();
	void Type(CString strValue);
	StrArray<13> Curve();
	void Curve(const StrArray<13>& strValue);
	CString KOrCv();
	void KOrCv(CString strValue);
	StrArray<3> BasisArea();
	void BasisArea(const StrArray<3>& strValue);

private:
	void AppendArray();
	void InitExtra(CString strData);
	virtual CString GetDefaultData();

private:
	RowObjectFace<1> m_Type;			//����(0)
	VariableFace<13,7> m_Curve;			//��ʧģ��(1��Kϵ���㶨��2��Kϵ���仯��3����������)
										//Y������������ֱ��[ѹ������0��ˮͷ��1��ѹ��]
										//Y�������λ[ѹ����λ]
										//X������������ֱ��[����������ͣ�0���������1����������2������3����ټ��]
										//X�������λ[��λ]
										//x�����ȡֵ[�����ֵ�����ȡֵ]
										//��������[�������ͣ�-2��Kֵ�仯��1��ѹ����ʧ����ʽ��2��ѹ����ʧ�ڲ�ֵ��]
										//��ʽ�в����ͳ����ĸ���[]
										//��ʽ�еĲ����ͳ���a��b��c��d��e��ֵ[]
	RowObjectFace<1> m_KOrCv;				//Kϵ��ֵ
	RowObjectFace<3> m_BasisArea;		//��ʧģ�͵��������0��Ĭ�����ιܵ������1�����ιܵ����2���û�ָ�����3���û�ָ��ֱ��
										//ֵ
										//��λ
	RowObjectFace<2> m_Fth2 ;			//0,None,
};

#endif // !defined(AFX_GENERALDATA_H__56A00CC8_089F_47AC_92FA_14F934745960__INCLUDED_)

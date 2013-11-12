// GasPropertyWrapper.h: interface for the GasPropertyWrapper class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GASPROPERTYWRAPPER_H__9E1E9012_9E10_4EAD_8EC7_CA40883EA52A__INCLUDED_)
#define AFX_GASPROPERTYWRAPPER_H__9E1E9012_9E10_4EAD_8EC7_CA40883EA52A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "ArrayFlyWeight.h"
class GasPropertyWrapper  
{
public:
	int GetType();
	void SetType(int nType);
	void SetWeight(CString strWeight);
	CString GetWeight();
	void SetCpCv(CString strCpCv);
	CString GetCpCv();
	void GetPress(CString &strValue,CString &strUnit);
	void SetPress(CString strValue,CString strUnit);
	void GetTemp(CString &strValue,CString &strUnit);
	void SetTemp(CString strValue,CString strUnit);
	void GetMass(CString &strValue,CString &strUnit);
	void SetMass(CString strValue,CString strUnit);
	GasPropertyWrapper(ArrayFlyWeight<9> &GasProperty);
	virtual ~GasPropertyWrapper();

private:
	ArrayFlyWeight<9> &m_GasProperty;			//��������0������1����������
												//������
												//Cp/Cv
												//�����¶�/��λ
												//����ѹ��/��λ
												//�ڲ���ʼ��������������/��λ

};

#endif // !defined(AFX_GASPROPERTYWRAPPER_H__9E1E9012_9E10_4EAD_8EC7_CA40883EA52A__INCLUDED_)

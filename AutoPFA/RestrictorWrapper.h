// RestrictorWrapper.h: interface for the RestrictorWrapper class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RESTRICTORWRAPPER_H__2AC86A4E_80E4_4D3F_A939_4FF06AC6E4E7__INCLUDED_)
#define AFX_RESTRICTORWRAPPER_H__2AC86A4E_80E4_4D3F_A939_4FF06AC6E4E7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "ArrayFlyWeight.h"

class RestrictorWrapper  
{
public:
	void SetModel(BOOL bModel);
	BOOL GetModel();
	void SetInFlowCD(CString strInFlowCD);
	CString GetInFlowCD();
	void SetOutFlowCD(CString strOutFlowCD);
	CString GetOutFlowCD();
	void SetArea(CString strValue,CString strUnit);
	void GetArea(CString &strValue,CString& strUnit);
	RestrictorWrapper(ArrayFlyWeight<5> &Orifice);
	virtual ~RestrictorWrapper();

private:
	ArrayFlyWeight<5> &m_Orifice;				//ѡ�н����װ�ģ�ͱ��\������ϵ��\������ϵ��\���ֵ\��λ

};

#endif // !defined(AFX_RESTRICTORWRAPPER_H__2AC86A4E_80E4_4D3F_A939_4FF06AC6E4E7__INCLUDED_)

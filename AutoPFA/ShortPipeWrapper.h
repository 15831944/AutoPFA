// ShortPipeWrapper.h: interface for the ShortPipeWrapper class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHORTPIPEWRAPPER_H__F6F6B137_D62A_4A97_A0CC_202F58245F0B__INCLUDED_)
#define AFX_SHORTPIPEWRAPPER_H__F6F6B137_D62A_4A97_A0CC_202F58245F0B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "ArrayFlyWeight.h"

class ShortPipeWrapper  
{
public:
	void SetModel(BOOL bModel);
	BOOL GetModel();
	void SetFriction(CString strFriction);
	CString GetFriction();
	void SetDia(CString strValue,CString strUnit);
	void GetDia(CString &strValue,CString& strUnit);
	void SetArea(CString strValue,CString strUnit);
	void GetArea(CString &strValue,CString& strUnit);
	void SetLen(CString strValue,CString strUnit);
	void GetLen(CString &strValue,CString& strUnit);
	void SetEleChange(CString strValue,CString strUnit);
	void GetEleChange(CString &strValue,CString& strUnit);
	ShortPipeWrapper(ArrayFlyWeight<10> &ShortPipe);
	virtual ~ShortPipeWrapper();

private:
	ArrayFlyWeight<10> &m_ShortPipe;			    	//0��û��ѡ��̹ܵ�ģ�ͣ�-1��ѡ��̹ܵ�ģ��
														//�̹ܵ�Ħ��ϵ��
														//�̹ܵ���ֱ��\��λ
														//�̹ܵ����\��λ
														//�̹ܵ�����\��λ
														//�̹ܵ���߱仯\��λ

};

#endif // !defined(AFX_SHORTPIPEWRAPPER_H__F6F6B137_D62A_4A97_A0CC_202F58245F0B__INCLUDED_)

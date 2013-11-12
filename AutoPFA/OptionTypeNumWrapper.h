// OptionTypeNumWrapper.h: interface for the OptionTypeNumWrapper class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPTIONTYPENUMWRAPPER_H__4D9BABE8_D6FA_4639_81B2_C82B72349480__INCLUDED_)
#define AFX_OPTIONTYPENUMWRAPPER_H__4D9BABE8_D6FA_4639_81B2_C82B72349480__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "ArrayFlyWeight.h"

class OptionTypeNumWrapper  
{
public:
	int GetModel();
	void SetModel(int bModel);
	void SetPress(int nType,CString strValue,CString strUnit);
	void GetPress(int &nType,CString &strValue,CString& strUnit);
	OptionTypeNumWrapper(ArrayFlyWeight<4>	&OptionTypeNum);
	virtual ~OptionTypeNumWrapper();

private:
	ArrayFlyWeight<4>	&m_OptionTypeNum;           	   //0��û��ѡ��-1��ѡ��
															//ѹ��������0��ˮͷ1��ѹ��
															//ѹ��ֵ
															//ѹ����λ

};

#endif // !defined(AFX_OPTIONTYPENUMWRAPPER_H__4D9BABE8_D6FA_4639_81B2_C82B72349480__INCLUDED_)

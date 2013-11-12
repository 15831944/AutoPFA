// OneWayWrapper.h: interface for the OneWayWrapper class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ONEWAYWRAPPER_H__CF414981_667E_4F84_A7B6_84E57A3613A4__INCLUDED_)
#define AFX_ONEWAYWRAPPER_H__CF414981_667E_4F84_A7B6_84E57A3613A4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "ArrayFlyWeight.h"

class OneWayWrapper  
{
public:
	BOOL GetCvModel();
	void SetCv(CString strCv);
	CString GetCv();
	int GetPostion();
	void SetPostion(int nPostion);
	void SetPress(int nType,CString strValue,CString strUnit);
	void GetPress(int &nType,CString &strValue,CString& strUnit);
	OneWayWrapper(ArrayFlyWeight<5>& checkValve);
	virtual ~OneWayWrapper();
	
private:
	ArrayFlyWeight<5>& m_CheckValve;						//ֹ�ط�����ϵ��
														//ֹ�ط���ʼλ��0����1���ر�
														//�򿪷���Deltaѹ����ˮͷ��ѹ������0��ˮͷ1��ѹ��
														//ѹ��ֵ\��λ

};

#endif // !defined(AFX_ONEWAYWRAPPER_H__CF414981_667E_4F84_A7B6_84E57A3613A4__INCLUDED_)

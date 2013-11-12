// TeeWyePerisist.h: interface for the TeeWyePerisist class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEEWYEPERISIST_H__AA9964C0_2FE1_4B1E_8CC2_E0983A842A32__INCLUDED_)
#define AFX_TEEWYEPERISIST_H__AA9964C0_2FE1_4B1E_8CC2_E0983A842A32__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Junperisist.h"

class AFX_EXT_CLASS TeeWyePerisist : public Junperisist  
{
public:
	static Junperisist* CreatTeeWye();
	TeeWyePerisist();
	virtual ~TeeWyePerisist();

public:
	CString Type();
	void Type(CString strValue);
	CString Angle();
	void Angle(CString strValue);
	CString Model();
	void Model(CString strValue);
private:
	CString m_Type;			    //���ͣ�0�����ֱ��ͨ1��Բ��ֱ��ͨ2������ı�3���Գƣ�
	CString m_Angle;			//�Ƕ�
	CString m_Model;			//��ʧģ�����ͣ�1����ģ��2����ϸģ�ͣ�

};
/*------------------------------------------*/
inline CString TeeWyePerisist::Type()
{
	return m_Type;
}
inline void TeeWyePerisist::Type(CString strValue)
{
	m_Type = strValue;
}

/*------------------------------------------*/
inline CString TeeWyePerisist::Angle()
{
	return m_Angle;
}
inline void TeeWyePerisist::Angle(CString strValue)
{
	m_Angle = strValue;
}
/*------------------------------------------*/
inline CString TeeWyePerisist::Model()
{
	return m_Model;
}
inline void TeeWyePerisist::Model(CString strValue)
{
	m_Model = strValue;
}
#endif // !defined(AFX_TEEWYEPERISIST_H__AA9964C0_2FE1_4B1E_8CC2_E0983A842A32__INCLUDED_)

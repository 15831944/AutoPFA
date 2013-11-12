// ControlPerisist.h: interface for the ControlPerisist class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONTROLPERISIST_H__5BE02207_70F9_4D10_BFB0_6E0CBE1CA78F__INCLUDED_)
#define AFX_CONTROLPERISIST_H__5BE02207_70F9_4D10_BFB0_6E0CBE1CA78F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Junperisist.h"
#include "TransDataPersistent.h"

class AFX_EXT_CLASS ControlPerisist : public Junperisist  
{
public:
	static Junperisist* CreatControlValve();
	ControlPerisist();
	virtual ~ControlPerisist();

public:
	StrArray<5>& ControlSet();
	void ControlSet(const StrArray<5>& strValue);
	CString ModelType();
	void ModelType(CString strValue);
	CString KOrCv();
	void KOrCv(CString strValue);
	StrArray<4>& FailAction();
	void FailAction(const StrArray<4>& strValue);
private:
	StrArray<5> m_ControlSet;					//��������0��PRF 1��PSV 2��FCV 3��PDCV
												//���Ƶ��������0��ˮͷ/ˮͷ��ʧ/�������1��ѹ��/ѹ����ʧ/��������
												//0��ͣ��ѹ��1����̬ѹ��
												//���Ƶ����ֵ
												//���Ƶ������λ
	CString		m_ModelType;					//��ʧģ��(0������ϵ��ģ�ͣ�1��Kϵ��ģ�� -2��ʹ��ϵ�����ֵ)
	CString		m_KOrCv;						//K��Cvϵ��ֵ
	StrArray<4> m_failAction;					//�ȶ�״̬���ǿ���0��û��ѡ�� 1��ѡ��
												//ʹ��Ĭ�ϵ���Ϊ  0��û��ѡ�� 1��ѡ��
												//����ѹ���������0��ȫ���� 1���ر�
												//����ѹ����������0��ȫ���� 1���ر�
public:

	TransDataPersistent m_TransPersistent;
	TransDataPersistent m_FailTransPersistent;
	ThreeDTablePersistent m_KOrCvData;
};
/*------------------------------------------*/
inline StrArray<5>& ControlPerisist::ControlSet()
{
	return m_ControlSet;
}
inline void ControlPerisist::ControlSet(const StrArray<5>& strValue)
{
	m_ControlSet = strValue;
}
/*------------------------------------------*/
inline CString ControlPerisist::ModelType()
{
	return m_ModelType;
}
inline void ControlPerisist::ModelType(CString strValue)
{
	m_ModelType = strValue;
}
/*------------------------------------------*/
inline CString ControlPerisist::KOrCv()
{
	return m_KOrCv;
}
inline void ControlPerisist::KOrCv(CString strValue)
{
	m_KOrCv = strValue;
}
/*------------------------------------------*/
inline StrArray<4>& ControlPerisist::FailAction()
{
	return m_failAction;
}
inline void ControlPerisist::FailAction(const StrArray<4>& strValue)
{
	m_failAction = strValue;
}
#endif // !defined(AFX_CONTROLPERISIST_H__5BE02207_70F9_4D10_BFB0_6E0CBE1CA78F__INCLUDED_)

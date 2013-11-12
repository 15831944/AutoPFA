// BreckerData.h: interface for the BreckerData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BRECKERDATA_H__36398309_949F_4F4A_9782_CF58CD82AEB8__INCLUDED_)
#define AFX_BRECKERDATA_H__36398309_949F_4F4A_9782_CF58CD82AEB8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Junction.h"
//����ƻ���(��)
class AFX_EXT_CLASS BreckerData : public JunctionData  
{
public:
	static JunctionData* Creator();
	BreckerData();
	virtual ~BreckerData();

private:
	CString GetDefaultData();
	void AppendArray();
	void InitExtra(CString strData);

public:
	StrArray<3> CrackPress();
	void CrackPress(const StrArray<3>& strValue);
	StrArray<2> OrificeInCdA();
	void OrificeInCdA(const StrArray<2>& strValue);
	StrArray<2> OrificeOutCdA();
	void OrificeOutCdA(const StrArray<2>& strValue);
	StrArray<3> LiquidTemp();
	void LiquidTemp(const StrArray<3>& strValue);
	StrArray<9> GasProperty();
	void GasProperty(const StrArray<9>& strValue);
	CString ConnectPipe();
	void ConnectPipe(CString strValue);
	CString ValveType();
	void ValveType(CString strValue);
	StrArray<2> InterMediateCdA();
	void InterMediateCdA(const StrArray<2>& strValue);
	StrArray<3> MediateActivation();
	void MediateActivation(const StrArray<3>& strValue);
	
private:
	RowObjectFace<3>   m_CrackPress;             //���ѵ�ѹ������0��ˮͷ��1��ѹ��/ѹ��ֵ/ѹ����λ
	RowObjectFace<2>   m_OrificeInCdA;             //�׿�ȫ�����������ֵ/��λ
	RowObjectFace<2>   m_OrificeOutCdA;			//�������ֵ/��λ
	RowObjectFace<3>   m_LiquidTemp;             //�����¶�ѡ��0��ϵͳ����1���û�ָ���¶�/�¶�ֵ/��λ
	RowObjectFace<9>   m_GasProperty;			//��������0������1����������/������/Cp/Cv/�����¶�/����ѹ��/�ڲ���ʼ��������������/��λ
	RowObjectFace<1>   m_ConnectPipe;			//���ӹܵ���0�������ܵ�1��һ���ܵ�
	RowObjectFace<1>   m_ValveType;				//��������
	RowObjectFace<2>   m_InterMediateCdA;		//�׿�ȫ����ý���������ֵ/��λ
	RowObjectFace<3>   m_MediateActivation;		//ý��׿ڼ����׼0��ѹ����ͬ1�����ٲ�ͬ/��׼ֵ/׼ֵ�ĵ�λ
};

#endif // !defined(AFX_BRECKERDATA_H__36398309_949F_4F4A_9782_CF58CD82AEB8__INCLUDED_)

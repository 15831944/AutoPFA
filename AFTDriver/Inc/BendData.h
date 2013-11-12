// BendData.h: interface for the BendData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BENDDATA_H__B325A443_4137_4B09_9A73_643D9A6DA350__INCLUDED_)
#define AFX_BENDDATA_H__B325A443_4137_4B09_9A73_643D9A6DA350__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//��ܣ���ͷ��
#include "Junction.h"
#include "RowObjectFace.h"

class AFX_EXT_CLASS BendData : public JunctionData  
{
public:
	static JunctionData* Creator();
	BendData();
	virtual ~BendData();
public:
	CString Type();
	void Type(CString strValue);
    CString Angel();
	void Angel(CString strValue);
	CString RD();
	void RD(CString strValue);
	CString K();
	void K(CString strValue);
	StrArray<2> RestriFlowArea();
	void RestriFlowArea(const StrArray<2>& strValue);
	StrArray<3> BasisArea();
	void BasisArea(const StrArray<3>& strValue);
private:
	void AppendArray();
	void InitExtra(CString strData);
	virtual CString GetDefaultData();

private:
	RowObjectFace<1> m_bendType;   //��ͷ���ͣ�0��Ϊ�⻬��ͷ��1Ϊ��׼��ͷ��2ΪMitre Bend,3,Ϊ�û�ָ����
    RowObjectFace<1> m_angel;      //�Ƕȣ�Ϊ���ٶȣ�
	RowObjectFace<1> m_rD;          //r/D
	RowObjectFace<1> m_K;			//������ʧ��K��
    RowObjectFace<2> m_RestriFlowArea;  //��ȷ���������Restricted Flow Area)�����ֺ͵�λ
	RowObjectFace<3> m_BasisArea;		//��ʧģ�͵��������0��Ĭ�����ιܵ������1�����ιܵ����2���û�ָ�����3���û�ָ��ֱ��
   
};

#endif // !defined(AFX_BENDDATA_H__B325A443_4137_4B09_9A73_643D9A6DA350__INCLUDED_)

// TeeWyeData.h: interface for the TeeWyeData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEEWYEDATA_H__D4F1B11A_2743_4ECD_A8B7_EC047987913D__INCLUDED_)
#define AFX_TEEWYEDATA_H__D4F1B11A_2743_4ECD_A8B7_EC047987913D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//��ͨ��Y��Ԫ��
#include "Junction.h"
#include "RowObjectFace.h"

class AFX_EXT_CLASS TeeWyeData : public JunctionData  
{
public:
	static JunctionData* Creator();
	TeeWyeData();
	virtual ~TeeWyeData();
public:
	CString Type();
	void Type(CString strValue);
	CString Angle();
	void Angle(CString strValue);
	void Arrangement(CString strValue);
	CString Arrangement();
	CString Model();
	void Model(CString strValue);
private:
	void AppendArray();
	void InitExtra(CString strData);
	virtual CString GetDefaultData();

private:
	RowObjectFace<1> m_Type;				//���ͣ�0�����ֱ��ͨ1��Բ��ֱ��ͨ2������ı�3���Գƣ�
	RowObjectFace<1> m_Angle;				//�Ƕ�
	RowObjectFace<1> m_arrangement;		    //ʵ�ʲ��ú�ͼ��ͬ��ѡ��Ϊ-1��0ûѡ��
	RowObjectFace<1> m_LossModel;			//��ʧģ�����ͣ�1����ģ��2����ϸģ�ͣ�

};

#endif // !defined(AFX_TEEWYEDATA_H__D4F1B11A_2743_4ECD_A8B7_EC047987913D__INCLUDED_)

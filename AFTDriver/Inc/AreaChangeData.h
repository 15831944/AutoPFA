// AreaChangeData.h: interface for the AreaChangeData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AREACHANGEDATA_H__85D070A4_BCB7_4E37_9418_CB1205EB080E__INCLUDED_)
#define AFX_AREACHANGEDATA_H__85D070A4_BCB7_4E37_9418_CB1205EB080E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "RowObjectFace.h"
#include "Junction.h"
//�쾶��
class AFX_EXT_CLASS AreaChangeData : public JunctionData  
{
public:
	void Type(CString strValue);
	CString Type();
	void Dir(CString strValue);
	CString Dir();
	void Angle(CString strValue);
	CString Angle();
	void K(CString strValue);
	CString K();
	void BasisArea(StrArray<3>& array);
	StrArray<3> BasisArea();
	static JunctionData* Creator();
	AreaChangeData();
	virtual ~AreaChangeData();
	
private:
	void AppendArray();
	void InitExtra(CString strData);
	CString GetDefaultData();

private:
	RowObjectFace<1> m_TypeID;			//�쾶�����ͣ�0��Բ׶��1��Բ����2���û����壩
	RowObjectFace<1> m_Dir;				//��1��������2�����ţ�
	RowObjectFace<1> m_Angle;			//�Ƕ�
	RowObjectFace<1> m_K;				//Kϵ��ֵ
    RowObjectFace<3> m_BasisArea;		//��ʧģ�͵��������

};

#endif // !defined(AFX_AREACHANGEDATA_H__85D070A4_BCB7_4E37_9418_CB1205EB080E__INCLUDED_)

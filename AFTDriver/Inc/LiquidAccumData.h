// LiquidAccumData.h: interface for the LiquidAccumData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LIQUIDACCUMDATA_H__6D4FDA75_D697_40E9_9F96_FB041FFF850E__INCLUDED_)
#define AFX_LIQUIDACCUMDATA_H__6D4FDA75_D697_40E9_9F96_FB041FFF850E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "RowObjectFace.h"
#include "Junction.h"

class AFX_EXT_CLASS LiquidAccumData : public JunctionData  
{
public:
	static JunctionData* Creator();
	LiquidAccumData();
	virtual ~LiquidAccumData();

private:
	void AppendArray();
	void InitExtra(CString strData);
	virtual CString GetDefaultData();

public:
	void Elastic(StrArray<2>& array);
	StrArray<2> Elastic();
	void InitVolume(StrArray<2>& array);
	StrArray<2> InitVolume();
private:
	RowObjectFace<2> m_Elastic;				//����ֵ\���Ե�λ
    RowObjectFace<2> m_Volume;				//��ʼ���ֵ\��ʼ���ֵ��λ
};

#endif // !defined(AFX_LIQUIDACCUMDATA_H__6D4FDA75_D697_40E9_9F96_FB041FFF850E__INCLUDED_)

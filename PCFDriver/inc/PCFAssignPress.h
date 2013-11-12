// PCFAssignPress.h: interface for the PCFAssignPress class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PCFASSIGNPRESS_H__4D1AA093_206D_4497_9DDC_383DC01098DA__INCLUDED_)
#define AFX_PCFASSIGNPRESS_H__4D1AA093_206D_4497_9DDC_383DC01098DA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PCFJun.h"
#include "RowObjectFace.h"
#include "JunTransData.h"
//ָ��ѹ��
class AFX_EXT_CLASS PCFAssignPress : public PCFJun  
{
public:
	static PCFJun* Creator();
	PCFAssignPress();
	virtual ~PCFAssignPress();
	void Init( const CStringArray& wordArray );
public:
	CString GetDistanceUnit();
	void SetDistanceUnit(CString strValue);
	StrArray<3> GetPressure();
	void SetPressure(const StrArray<3>& strValue);	
private:
	RowObjectFace<3> m_Press;			//ѹ������0��ͣ��ѹ��1����ֹѹ��\ֵ\��λ 
	RowObjectFace<1> m_EleUnit;			//�ܵ��˿���ڵ��߾��뵥λ
};

#endif // !defined(AFX_PCFASSIGNPRESS_H__4D1AA093_206D_4497_9DDC_383DC01098DA__INCLUDED_)

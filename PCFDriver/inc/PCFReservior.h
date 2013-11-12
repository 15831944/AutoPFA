// PCFReservior.h: interface for the PCFReservior class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PCFRESERVIOR_H__656463BB_6674_44FE_986F_9F5AF78E7037__INCLUDED_)
#define AFX_PCFRESERVIOR_H__656463BB_6674_44FE_986F_9F5AF78E7037__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PCFJun.h"
#include "RowObjectFace.h"
#include "PCFPortPoint.h"
//ˮ��
class AFX_EXT_CLASS PCFReservior : public PCFJun  
{
public:
	static PCFJun* Creator();
	PCFReservior();
	virtual ~PCFReservior();


	StrArray<2> GetEleOrDepth();
	void SetEleOrDepth(const StrArray<2>& strValue);
	StrArray<2> GetSurfacePress();
	void SetSurfacePress(const StrArray<2>& strValue);
public:
	void Init( const CStringArray& wordArray );
private:
//	RowObjectFace<1> m_EleOrDepthType;
	RowObjectFace<2> m_EleOrDepth;		//�ܵ���߻����\��λ
	RowObjectFace<2> m_SurfacePress;	//����ѹ��ֵ\��λ
	TableData<5> m_linkPipeK;

};

#endif // !defined(AFX_PCFRESERVIOR_H__656463BB_6674_44FE_986F_9F5AF78E7037__INCLUDED_)

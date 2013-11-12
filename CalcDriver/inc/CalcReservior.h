// CalcReservior.h: interface for the CalcReservior class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CALCRESERVIOR_H__1860353A_C9A0_4EA6_9BFD_4F1E22BBAC44__INCLUDED_)
#define AFX_CALCRESERVIOR_H__1860353A_C9A0_4EA6_9BFD_4F1E22BBAC44__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "CalcTable.h"
#include "CalcJun.h"
#include "CalcTransData.h"

class AFX_EXT_CLASS CalcReservior : public CalcJun  
{
public:
	ostream& Write(ostream& CalcOut);
	static CalcJun* Creator();
	CalcReservior();
	virtual ~CalcReservior();

public:
	void EleOrDepthType(int nValue);
	void SurfacePress(double dValue);
	void PipeInfo(const ListImp<StrArray<6> >& ref);

	int EleOrDepthType();
	double SurfacePress();
	ListImp<StrArray<6> >& PipeInfo();
private:
	double		 m_dSurfacePress;				//����ѹ��ֵ
	int			 m_nEleOrDepthType;			    //�ܵ���ˮ�����ӵ��߻����
	CalcTable<6> m_PipeInfo;					//<������������>
												//1�����ӹܵ������ֱ�ţ��ӽڵ������Ӹ��ţ�
												//2  ����
												//2������ӽڵ�����ܵ�ʱ�ܵ��˿�kϵ��
												//3������ӽڵ������ܵ�ʱ�ܵ��˿�kϵ��
												//4��r/d���˿ڵ�԰���ȣ�
												//5���ܵ���߻����

public:
	CalcTransData m_TranData;
};


#endif // !defined(AFX_CALCRESERVIOR_H__1860353A_C9A0_4EA6_9BFD_4F1E22BBAC44__INCLUDED_)

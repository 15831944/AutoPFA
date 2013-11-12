// CalcSpray.h: interface for the CalcSpray class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CALCSPRAY_H__415ED011_A337_44BF_A85E_7719AF4034C7__INCLUDED_)
#define AFX_CALCSPRAY_H__415ED011_A337_44BF_A85E_7719AF4034C7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CalcJun.h"
#include "CalcTransData.h"

class AFX_EXT_CLASS CalcSpray : public CalcJun  
{
public:
	ostream& Write(ostream& CalcOut);
	static CalcJun* Creator();
	CalcSpray();
	virtual ~CalcSpray();
	void HoleNum(int nValue);
	void LossType(int nValue);
	void ExitArea(double dValue);
	void KOrCv(double dValue);
	void ExitPressType(int nValue);
	void ExitPress(double dValue);

	int HoleNum();
	int LossType();
	double ExitArea();
	double KOrCv();
	int ExitPressType();
	double ExitPress();
	
private:
	int  m_nLossType;						//0������ϵ��1��Kϵ��(fire sprinklers Kֵ�Ķ����ǣ� K = Q/sqrt(dP)
	double  m_dExitArea;						//�׿ڵ����
	double	m_dKOrCv;					    	//K��Cvϵ��ֵ
    int     m_nExitPressType;					//����ѹ������0��ˮͷ1��ѹ��
	double  m_dExitPress;					    //����ѹ��
	int 	m_nHoleNum;							//�׵�����
	
public:
	CalcTransData m_TranData;
};

#endif // !defined(AFX_CALCSPRAY_H__415ED011_A337_44BF_A85E_7719AF4034C7__INCLUDED_)

// MOCJunControl.h: interface for the MOCJunControl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MOCJUNCONTROL_H__ACD6F08A_9EF7_4338_B1C0_671C8A6999FB__INCLUDED_)
#define AFX_MOCJUNCONTROL_H__ACD6F08A_9EF7_4338_B1C0_671C8A6999FB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "EndListRef.h"

class MOCJunControl  
{
public:
	void ControlApply(int nControlApply);
	void PressType(int nPressType);
	void ControlType(int nControlType);
	BOOL IsControlPump();
	MOCJunControl();
	virtual ~MOCJunControl();
public:
	void CalcStm(EndListRef &jun,double dControlValue,int nSet);
	void PressControl(EndListRef &jun,EndInfo *pEnd,double dControlValue);
	void FlowControl(EndListRef &jun,double dControlValue,int nSet);
	void InPressControl(EndListRef &jun,double dControlValue);
	void OutPressControl(EndListRef &jun,double dControlValue);
	void FlowControl(EndListRef &jun,EndInfo *pEnd,double dFlow);
private:
	int     	m_nPumpControl;			//���Ʊ����ͣ�0��û�п��ƣ�1:����ˮͷ  2:����ѹ�� 3:  ���ˮͷ  4: ���ѹ�� 5: ������� 6: ��������
	int         m_nPressType;			//0��ͣ��ѹ��1����̬ѹ��
	int 		m_nControlApply;        //���ƶ�Ӧ��������ã�0�����ǿ���1��ѹ��������������2��ѹ�����ڿ������ã�
};
inline void MOCJunControl::ControlApply(int nControlApply)
{
	m_nControlApply = nControlApply;
}
inline void MOCJunControl::PressType(int nPressType)
{
	m_nPressType = nPressType;
}
inline void MOCJunControl::ControlType(int nControlType)
{
	m_nPumpControl = nControlType;
}
inline BOOL MOCJunControl::IsControlPump()
{
	if(m_nPumpControl==0)
		return FALSE;
	return TRUE;
}
#endif // !defined(AFX_MOCJUNCONTROL_H__ACD6F08A_9EF7_4338_B1C0_671C8A6999FB__INCLUDED_)

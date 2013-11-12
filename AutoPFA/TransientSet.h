// TransientSet.h: interface for the TransientSet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRANSIENTSET_H__72CF4364_9A7B_493D_8625_433A8EF4DF83__INCLUDED_)
#define AFX_TRANSIENTSET_H__72CF4364_9A7B_493D_8625_433A8EF4DF83__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ScenarioObject.h"
class TransControlPerisistent;

class TransientSet : public ScenarioObject  
{
public:
	BOOL Read(TransControlPerisistent &persistent);
	BOOL Save(TransControlPerisistent &persistent);
	void SaveData();
	void InitData();
	static void Instance();
	NameArray& GetArray();
	int GetType();
	static ScenarioObject* CreatTransientSet();
	TransientSet();
	virtual ~TransientSet();
public:
	BOOL IsDefine();
	static NumFlyWeight ms_StartTime;				//˲̬ģ�⿪ʼʱ��
	static NumFlyWeight ms_StopTime;				//˲̬ģ�����ʱ��
	static StrFlyWeight ms_Frequency;				//�����������Ƶ��
	static StrFlyWeight ms_ModelCavitation;			//0����������Ѩ���ڣ�1�����Ǵ�����Ѩ
	static StrFlyWeight ms_VariableR;				//0���ܵ�����ϵ��ʹ����̬����ϵ����1�����ݵ�ǰ˲̬��������ܵ�����ϵ��
	static StrFlyWeight ms_StopOnArtificialTrans;	//ֹͣ���������⵽�˹�˲����0��������˹�˲�䣬1������˹�˲��
	static StrFlyWeight ms_Criteria;				//�㶨����������˲������ʼ���ݱ�׼�������ٷ��������磺0.5%��"0.5"��ʾ��
	static NumFlyWeight ms_CriteriaMinFlow;			//��������ֵ��׼�����������ڱ�׼��������������Ϊ����Ϊ0��
	static StrFlyWeight ms_TotalSteps;				//˲̬ģ���ܼ��㲽��
private:
    static NameArray s_StateName;
	ScenarioObject* DoClone();
};
inline int TransientSet::GetType()
{
	return 22;
}

inline NameArray& TransientSet::GetArray()
{
	return s_StateName;
}
#endif // !defined(AFX_TRANSIENTSET_H__72CF4364_9A7B_493D_8625_433A8EF4DF83__INCLUDED_)

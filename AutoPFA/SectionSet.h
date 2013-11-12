// SectionSet.h: interface for the SectionSet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SECTIONSET_H__250381C4_2C50_4B22_9531_5FF78041CAD1__INCLUDED_)
#define AFX_SECTIONSET_H__250381C4_2C50_4B22_9531_5FF78041CAD1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ScenarioObject.h"
class SectionPipePerisistent;
class ComponentManager;

class SectionSet : public ScenarioObject  
{
public:
	BOOL Read(SectionPipePerisistent &persistent);
	BOOL Save(SectionPipePerisistent &persistent);
	void SaveData();
	void InitData();
	static void Instance();
	NameArray& GetArray();
	int GetType();
	static ScenarioObject* CreatSectionSet();
	SectionSet();
	virtual ~SectionSet();

public:
	BOOL TimeStep(float &fTime,ComponentManager &Manager);
	void SearchSection(ListImp<StrArray<5> > &table,ComponentManager &Manager,int nMin,int nMax,double dIncrement,double dMaxError);
	double TimeStep();
	double MaxError();
	BOOL IsSection(ComponentManager &Manager);
	static StrFlyWeight ms_Search;		//ms_Search= -1��ʾͨ����ѯ���õ��ֶβ���
	static StrFlyWeight ms_MaxSections;	//���ƹܵ����Ի��ֵ���С�ܶ���
	static StrFlyWeight ms_MinSections;	//���ƹܵ����Ի��ֵ���С�ܶ���
	static StrFlyWeight ms_MaxError;	//���ƹܵ������������
	static StrFlyWeight ms_PctIncrement;//���ƹܵ��ֶ������Ӳ���
	static StrFlyWeight ms_Sort;		//
	static StrFlyWeight ms_IdealSections;//���ƹܵ�����ֶ�
	static StrFlyWeight ms_TimeStep;	 //���ƹܵ�ʱ�䲽��
private:
    static NameArray s_StateName;
	ScenarioObject* DoClone();

};
inline int SectionSet::GetType()
{
	return 21;
}

inline NameArray& SectionSet::GetArray()
{
	return s_StateName;
}
#endif // !defined(AFX_SECTIONSET_H__250381C4_2C50_4B22_9531_5FF78041CAD1__INCLUDED_)

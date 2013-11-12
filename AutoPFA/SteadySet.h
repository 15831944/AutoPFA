// SteadySet.h: interface for the SteadySet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STEADYSET_H__7E8F7071_57AC_494B_AA4D_B784B06362A7__INCLUDED_)
#define AFX_STEADYSET_H__7E8F7071_57AC_494B_AA4D_B784B06362A7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ScenarioObject.h"
class SteadyPersistent;

class SteadySet : public ScenarioObject  
{
public:
	BOOL Read(SteadyPersistent &persistent);
	BOOL Save(SteadyPersistent &persistent);
	void SaveData();
	void InitData();
	static void Instance();
	NameArray& GetArray();
	int GetType();
	static ScenarioObject* CreatSteadySet();
	SteadySet();
	virtual ~SteadySet();
public:
	BOOL IsDefine();
	int AnalysisType();
	void AnalysisType(int nType);
	static StrFlyWeight ms_AnalysisType;	//��������������ֱ�ǣ�0��˲̬������1����̬����
	static StrFlyWeight ms_PresTolType;		//ѹ���������ͱ�ǣ�0�����Թ��1����Թ���2�����Ի���Թ���3�����Ժ���Թ���		
	static NumFlyWeight ms_PresAbsTol;		//ѹ�����Թ���
	static StrFlyWeight ms_PresRelTol;		//ѹ����Թ���
	static StrFlyWeight ms_FlowTolType;		//�����������ͱ�ǣ�0�����Թ��1����Թ���2�����Ի���Թ���3�����Ժ���Թ���
	static NumFlyWeight ms_FlowAbsTol;		//�������Թ���
	static StrFlyWeight ms_FlowRelTol;		//������Թ���
	static StrFlyWeight ms_FlowRelaxation;	//�����ɳ�����
	static StrFlyWeight ms_PresRelaxation;	//�ɳ�����ֵ
	static StrFlyWeight ms_MaxIterations;	//����������ֵ
	static StrFlyWeight ms_KeepHistory;		//0�������������ʷ��¼��1�����������ʷ��¼
	static StrFlyWeight ms_MatrixMethod;	//������Է����鷽��0����˹��ȥ����1��ѡ��Ԫ�صĸ�˹��ȥ����2����������Ƿֽ⣨LU�ֽ⣩
	static StrFlyWeight ms_AutoDetect;		//���������ʷ��¼�������

	static const CmbDataItem ms_Method[3];
private:
    static NameArray s_StateName;
	ScenarioObject* DoClone();
};
inline int SteadySet::GetType()
{
	return 20;
}

inline NameArray& SteadySet::GetArray()
{
	return s_StateName;
}
#endif // !defined(AFX_STEADYSET_H__7E8F7071_57AC_494B_AA4D_B784B06362A7__INCLUDED_)

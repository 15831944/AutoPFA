// SteadyPersistent.h: interface for the SteadyPersistent class.
/*
 * Copyright (C), 2006,��ɳ���������˾CAE������
 * All rights reserved.
 *
  �ļ����ƣ�SteadyPersistent.h
  ժҪ�� �㶨��������Ʋ���  
  author  : LSP          
*/
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STEADYPERSISTENT_H__F5A87801_8F0B_4008_AC47_557078FB06C6__INCLUDED_)
#define AFX_STEADYPERSISTENT_H__F5A87801_8F0B_4008_AC47_557078FB06C6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class AFX_EXT_CLASS SteadyPersistent  
{
public:
	SteadyPersistent();
	virtual ~SteadyPersistent();

	CString AnalysisType();
	void AnalysisType(CString strValue);
	CString PresTolType();
	void PresTolType(CString strValue);
	StrArray<2>& PresAbsTol();
	void PresAbsTol(const StrArray<2>& strValue);
	CString PresRelTol();
	void PresRelTol(CString strValue);
	CString FlowTolType();
	void FlowTolType(CString strValue);
	StrArray<2>& FlowAbsTol();
	void FlowAbsTol(const StrArray<2>& strValue);
	CString FlowRelTol();
	void FlowRelTol(CString strValue);
	CString RelaxationType();
	void RelaxationType(CString strValue);
	CString FlowRelaxation();
	void FlowRelaxation(CString strValue);
	CString PresRelaxation();
	void PresRelaxation(CString strValue);
	CString MaxIterations();
	void MaxIterations(CString strValue);
	CString KeepHistory();
	void KeepHistory(CString strValue);
	CString MatrixMethod();
	void MatrixMethod(CString strValue);
	CString AutoDetect();
	void AutoDetect(CString strValue);

private:
	CString m_AnalysisType;			//��������������ֱ�ǣ�0��˲̬������1����̬����
	CString m_PresTolType;			//ѹ���������ͱ�ǣ�0�����Թ��1����Թ���2�����Ի���Թ���3�����Ժ���Թ���		
	StrArray<2> m_PresAbsTol;		//ѹ�����Թ���
	CString m_PresRelTol;			//ѹ����Թ���
	CString m_FlowTolType;			//�����������ͱ�ǣ�0�����Թ��1����Թ���2�����Ի���Թ���3�����Ժ���Թ���
	StrArray<2> m_FlowAbsTol;		//�������Թ���
	CString m_FlowRelTol;			//������Թ���
	CString m_RelaxationType;
	CString m_FlowRelaxation;		//�����ɳ�����
	CString m_PresRelaxation;		//�ɳ�����ֵ
	CString m_MaxIterations;		//����������ֵ
	CString m_KeepHistory;			//0�������������ʷ��¼��1�����������ʷ��¼
	CString m_MatrixMethod;			//������Է����鷽��0����˹��ȥ����1��ѡ��Ԫ�صĸ�˹��ȥ����2����������Ƿֽ⣨LU�ֽ⣩
	CString m_AutoDetect;			//���������ʷ��¼�������

};

/*------------------------------------------*/
inline CString SteadyPersistent::AnalysisType()
{
	return m_AnalysisType;
}
inline void SteadyPersistent::AnalysisType(CString strValue)
{
	m_AnalysisType = strValue;
}
/*------------------------------------------*/
inline CString SteadyPersistent::PresTolType()
{
	return m_PresTolType;
}
inline void SteadyPersistent::PresTolType(CString strValue)
{
	m_PresTolType = strValue;
}
/*------------------------------------------*/
inline StrArray<2>& SteadyPersistent::PresAbsTol()
{
	return m_PresAbsTol;
}
inline void SteadyPersistent::PresAbsTol(const StrArray<2>& strValue)
{
	m_PresAbsTol = strValue;
}
/*------------------------------------------*/
inline CString SteadyPersistent::PresRelTol()
{
	return m_PresRelTol;
}
inline void SteadyPersistent::PresRelTol(CString strValue)
{
	m_PresRelTol = strValue;
}
/*------------------------------------------*/
inline CString SteadyPersistent::FlowTolType()
{
	return m_FlowTolType;
}
inline void SteadyPersistent::FlowTolType(CString strValue)
{
	m_FlowTolType = strValue;
}
/*------------------------------------------*/
inline StrArray<2>& SteadyPersistent::FlowAbsTol()
{
	return m_FlowAbsTol;
}
inline void SteadyPersistent::FlowAbsTol(const StrArray<2>& strValue)
{
	m_FlowAbsTol = strValue;
}
/*------------------------------------------*/
inline CString SteadyPersistent::FlowRelTol()
{
	return m_FlowRelTol;
}
inline void SteadyPersistent::FlowRelTol(CString strValue)
{
	m_FlowRelTol = strValue;
}
/*------------------------------------------*/
inline CString SteadyPersistent::RelaxationType()
{
	return m_RelaxationType;
}
inline void SteadyPersistent::RelaxationType(CString strValue)
{
	m_RelaxationType = strValue;
}
/*------------------------------------------*/
inline CString SteadyPersistent::FlowRelaxation()
{
	return m_FlowRelaxation;
}
inline void SteadyPersistent::FlowRelaxation(CString strValue)
{
	m_FlowRelaxation = strValue;
}
/*------------------------------------------*/
inline CString SteadyPersistent::PresRelaxation()
{
	return m_PresRelaxation;
}
inline void SteadyPersistent::PresRelaxation(CString strValue)
{
	m_PresRelaxation = strValue;
}
/*------------------------------------------*/
inline CString SteadyPersistent::MaxIterations()
{
	return m_MaxIterations;
}
inline void SteadyPersistent::MaxIterations(CString strValue)
{
	m_MaxIterations = strValue;
}
/*------------------------------------------*/
inline CString SteadyPersistent::KeepHistory()
{
	return m_KeepHistory;
}
inline void SteadyPersistent::KeepHistory(CString strValue)
{
	m_KeepHistory = strValue;
}
/*------------------------------------------*/
inline CString SteadyPersistent::MatrixMethod()
{
	return m_MatrixMethod;
}
inline void SteadyPersistent::MatrixMethod(CString strValue)
{
	m_MatrixMethod = strValue;
}
/*------------------------------------------*/
inline CString SteadyPersistent::AutoDetect()
{
	return m_AutoDetect;
}
inline void SteadyPersistent::AutoDetect(CString strValue)
{
	m_AutoDetect = strValue;
}
#endif // !defined(AFX_STEADYPERSISTENT_H__F5A87801_8F0B_4008_AC47_557078FB06C6__INCLUDED_)

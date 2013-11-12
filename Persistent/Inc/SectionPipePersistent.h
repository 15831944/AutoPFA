// SectionPipePersistent.h: interface for the SectionPipePersistent class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SECTIONPIPEPERSISTENT_H__B0C8740F_DB31_4326_85B9_A9DA519484C9__INCLUDED_)
#define AFX_SECTIONPIPEPERSISTENT_H__B0C8740F_DB31_4326_85B9_A9DA519484C9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class AFX_EXT_CLASS SectionPipePerisistent  
{
public:
	SectionPipePerisistent();
	virtual ~SectionPipePerisistent();

public:
	CString Search();
	void Search(CString strValue);
	CString MaxSections();
	void MaxSections(CString strValue);
	CString MinSections();
	void MinSections(CString strValue);
	CString MaxError();
	void MaxError(CString strValue);
	CString PctIncrement();
	void PctIncrement(CString strValue);
	CString Sort();
	void Sort(CString strValue);
	CString IdealSections();
	void IdealSections(CString strValue);
	CString TimeStep();
	void TimeStep(CString strValue);

private:
	CString m_Search;		//ms_Search= -1��ʾͨ����ѯ���õ��ֶβ���
	CString m_MaxSections;	//���ƹܵ����Ի��ֵ���С�ܶ���
	CString m_MinSections;	//���ƹܵ����Ի��ֵ���С�ܶ���
	CString m_MaxError;		//���ƹܵ������������
	CString m_PctIncrement;	//���ƹܵ��ֶ������Ӳ���
	CString m_Sort;			//
	CString m_IdealSections;//���ƹܵ�����ֶ�
	CString m_TimeStep;		//���ƹܵ�ʱ�䲽��			
};
/*------------------------------------------*/
inline CString SectionPipePerisistent::Search()
{
	return m_Search;
}
inline void SectionPipePerisistent::Search(CString strValue)
{
	m_Search = strValue;
}
/*------------------------------------------*/
inline CString SectionPipePerisistent::MaxSections()
{
	return m_MaxSections;
}
inline void SectionPipePerisistent::MaxSections(CString strValue)
{
	m_MaxSections = strValue;
}
/*------------------------------------------*/
inline CString SectionPipePerisistent::MinSections()
{
	return m_MinSections;
}
inline void SectionPipePerisistent::MinSections(CString strValue)
{
	m_MinSections = strValue;
}
/*------------------------------------------*/
inline CString SectionPipePerisistent::MaxError()
{
	return m_MaxError;
}
inline void SectionPipePerisistent::MaxError(CString strValue)
{
	m_MaxError = strValue;
}
/*------------------------------------------*/
inline CString SectionPipePerisistent::PctIncrement()
{
	return m_PctIncrement;
}
inline void SectionPipePerisistent::PctIncrement(CString strValue)
{
	m_PctIncrement = strValue;
}
/*------------------------------------------*/
inline CString SectionPipePerisistent::Sort()
{
	return m_Sort;
}
inline void SectionPipePerisistent::Sort(CString strValue)
{
	m_Sort = strValue;
}
/*------------------------------------------*/
inline CString SectionPipePerisistent::IdealSections()
{
	return m_IdealSections;
}
inline void SectionPipePerisistent::IdealSections(CString strValue)
{
	m_IdealSections = strValue;
}
/*------------------------------------------*/
inline CString SectionPipePerisistent::TimeStep()
{
	return m_TimeStep;
}
inline void SectionPipePerisistent::TimeStep(CString strValue)
{
	m_TimeStep = strValue;
}
#endif // !defined(AFX_SECTIONPIPEPERSISTENT_H__B0C8740F_DB31_4326_85B9_A9DA519484C9__INCLUDED_)

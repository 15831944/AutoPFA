// TableData.h: interface for the TableData class.
/*
 * Copyright (C), 2006,��ɳ���������˾CAE������
 * All rights reserved.
 *
  �ļ����ƣ�TableData.h
  ժҪ��    AFTnά���ݱ��
  author  : LSP          
*/
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TABLEDATA_H__9F581750_6B02_45DB_828E_F7CC3D30F60F__INCLUDED_)
#define AFX_TABLEDATA_H__9F581750_6B02_45DB_828E_F7CC3D30F60F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "TableBase.h"

template <UINT size> 
class Table:public TableBase
{
public:
	virtual BOOL Read(CStdioFile &file);
	virtual BOOL Save(CStdioFile &file);
	virtual void Init();
public:
	Table(){};
    virtual ~Table(){};
	CString InitData(CString strData);
	TableData<size>& DataData();
	RowObjectFace<size>& UnitData();

public:
	StrArray<size> Unit();
	void Unit(const StrArray<size>& strValue);
	ListImp<StrArray<size> > Data();
	void Data(const ListImp<StrArray<size> >& strValue);

protected:
	RowObjectFace<size> m_Unit;			//��һ�����ݵ�λ\�ڶ������ݵ�λ
	TableData<size>     m_Data;

//m_Num������Table�������ݵĸ�����AFT�ڱ����ӹ�������ʱ���ֱ�ʾ�����ĵ����ݶ���д���ļ�������˲����������û��д���ļ�
//��������ӹ�����m_NumΪ�ձ�����Ҹ�����m_Num������m_Data���ݵĸ���������
};

template<UINT size>
BOOL Table<size>::Read(CStdioFile &file)
{
	return TRUE;
}

template<UINT size>
BOOL Table<size>::Save(CStdioFile &file)
{
	return TRUE;
}

template<UINT size>
void Table<size>::Init()
{
	
}

template<UINT size>
RowObjectFace<size>& Table<size>::UnitData()
{
	return m_Unit;
}

template<UINT size>
TableData<size>& Table<size>::DataData()
{
	return m_Data;
}

template<UINT size>
CString Table<size>::InitData(CString strData)
{
	strData = m_Unkown.InitData(strData);
	strData = m_Num.InitData(strData);
	strData = m_Unit.InitData(strData);
	strData = m_Data.InitData(strData,Num());
	return strData;
}


/*------------------------------------------*/
template<UINT size>
StrArray<size> Table<size>::Unit()
{
	return m_Unit.GetArray();
}

template<UINT size>
void Table<size>::Unit(const StrArray<size>& strValue)
{
	m_Unit.SetArray(strValue);
}

/*------------------------------------------*/
template<UINT size>
ListImp<StrArray<size> > Table<size>::Data()
{
	return m_Data.GetData();
}

template<UINT size>
void Table<size>::Data(const ListImp<StrArray<size> >& strValue)
{
	int n = strValue.GetCount();
	m_Num.SetData(n);
	m_Data.SetData(strValue);
	if(n > 0)
	{//˲�����ݱ��д������ݣ���˲������ǰ�ķָ���Ƶ����˲������ǰ��Ϊ���ŷָ�
		TCHAR chSeparator = m_Unit.GetSeparator();
		m_Unit.SetSeparator(',');
		m_Data.SetSeparator(chSeparator);
	}
	
}


typedef  Table<2> TwoDTable;
typedef  Table<3> ThreeDTable;

#endif // !defined(AFX_TABLEDATA_H__9F581750_6B02_45DB_828E_F7CC3D30F60F__INCLUDED_)

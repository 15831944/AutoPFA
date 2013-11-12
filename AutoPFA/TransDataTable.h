// TransDataTable.h: interface for the TransDataTable class.
/*
 * Copyright (C), 2006,��ɳ���������˾CAE������
 * All rights reserved.
 *
  �ļ����ƣ�TransDataTable.h
  ժҪ��    ˲�����ݱ��
  author  : LSP          
*/
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRANSDATATABLE_H__FBB5FAF2_DAA6_4E90_AD78_08ABE2B6BFD9__INCLUDED_)
#define AFX_TRANSDATATABLE_H__FBB5FAF2_DAA6_4E90_AD78_08ABE2B6BFD9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "ArrayFlyWeight.h"
#include "TableFlyWeigh.h"
#include "TwoDTablePersistent.h"


template<UINT size> 
class TransDataTable
{
public:
	BOOL IsEmpty();
	const ArrayFlyWeight<size>& Unit();
	void Unit(ArrayFlyWeight<size>& ref);
	const TableFlyWeight<size>& Data();
	void Data(TableFlyWeight<size>& ref);
	TransDataTable(){};
	virtual ~TransDataTable(){};

public:
	BOOL Save(GridTablePersistent<size> &Persistent,int num);
	BOOL Read(GridTablePersistent<size> &Persistent);
    ArrayFlyWeight<size>     m_Unit;			//��һ�����ݵ�λ\�ڶ������ݵ�λ
	TableFlyWeight<size>     m_Data;
};
/*----------------------------------------------*/
template<UINT size> 
BOOL TransDataTable<size>::IsEmpty()
{
	return m_Data.IsEmpty();
}
/*----------------------------------------------*/
template<UINT size> 
const ArrayFlyWeight<size>& TransDataTable<size>::Unit()
{
	return m_Unit;
}
/*----------------------------------------------*/
template<UINT size> 
void TransDataTable<size>::Unit(ArrayFlyWeight<size>& ref)
{
	m_Unit = ref;
}

/*----------------------------------------------*/
template<UINT size> 
const TableFlyWeight<size>& TransDataTable<size>::Data()
{
	return m_Data;
}
/*----------------------------------------------*/
template<UINT size> 
void TransDataTable<size>::Data(TableFlyWeight<size>& ref)
{
	m_Data = ref;
}
template<UINT size> 
BOOL TransDataTable<size>::Read(GridTablePersistent<size> &Persistent)
{
	m_Unit.SetData(Persistent.Unit());
	m_Data.SetData(Persistent.Data());
	
	return TRUE;
}
template<UINT size> 
BOOL TransDataTable<size>::Save(GridTablePersistent<size> &Persistent,int num)
{
	Persistent.Unit(m_Unit.GetData());
	Persistent.Data(m_Data.GetData(),num);
	return TRUE;
}
#endif // !defined(AFX_TRANSDATATABLE_H__FBB5FAF2_DAA6_4E90_AD78_08ABE2B6BFD9__INCLUDED_)

// MOCTrigerStrategyFactory.h: interface for the MOCTrigerStrategyFactory class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MOCTRIGERSTRATEGYFACTORY_H__17E64F5F_F3AC_4E73_B181_A8C92163654E__INCLUDED_)
#define AFX_MOCTRIGERSTRATEGYFACTORY_H__17E64F5F_F3AC_4E73_B181_A8C92163654E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Factory.h"
class MOCTrigerStrategy;

class MOCTrigerStrategyFactory:public CFactory<MOCTrigerStrategy,int>   
{
public:
	static MOCTrigerStrategyFactory* Instance();
	virtual ~MOCTrigerStrategyFactory();
	
protected:
	MOCTrigerStrategyFactory();
	
private:
	MOCTrigerStrategyFactory(const MOCTrigerStrategyFactory &ref);
	MOCTrigerStrategyFactory& operator=(const MOCTrigerStrategyFactory &ref);
};
/*
   0,"����ʱ��"
   1,"�ܵ���ֹѹ��"
   2,"�ڵ���ֹѹ��"
   3,"�ܵ���������"
   4,"�ܵ��������"
   5,"�ܵ�ˮͷ�¶���"
   6,"�ܵ������¶���"
   7,"��ת��"
   8,"ֹ�ط�״̬"
   9,"��ȫ��״̬"
   10,"���Ʒ�״̬"
   11,"�ڵ㾲ֹѹ����"
   12,"�ڵ���ֹѹ����"
   13,"�ڵ��¶��߲�"
   14,"�ڵ������¶��߲�"
   15,"�ܵ���ֹѹ����"
   16,"�ܵ���ֹѹ����"
   17,"�ܵ�ˮͷ�¶��߲�"
   18,"�ܵ������¶��߲�"
   19,"����ܿ�����"
   20,"��ѹ���¶���"
   21,"��ѹ������߶�"
   22,"�ܵ�����"
   23,"���ʱ��"
*/
#endif // !defined(AFX_MOCTRIGERSTRATEGYFACTORY_H__17E64F5F_F3AC_4E73_B181_A8C92163654E__INCLUDED_)

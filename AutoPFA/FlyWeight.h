// FlyWeight.h: interface for the FlyWeight class.
/*
 * Copyright (C), 2006,��ɳ���������˾CAE������
 * All rights reserved.
 *
  �ļ����ƣ�FlyWeight.h
  ժҪ��    
  author  : LSP          
*/
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FLYWEIGHT_H__F36B989D_39BD_4F60_9894_2B4B49C25E85__INCLUDED_)
#define AFX_FLYWEIGHT_H__F36B989D_39BD_4F60_9894_2B4B49C25E85__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class FlyWeight  
{
public:
	virtual void SetNull() = 0;
	virtual BOOL IsEmpty()const=0;
	virtual void Assign(FlyWeight *pFly)=0;
	virtual BOOL IsEqual(FlyWeight &ref)const=0;
    virtual BOOL GetValue(CString &strValue)const=0;
    virtual BOOL GetValue(CString &StrValue,CString &strUnit)const=0;
	FlyWeight();
	FlyWeight(const FlyWeight &ref);
	FlyWeight& operator=(const FlyWeight &ref);
	virtual ~FlyWeight();
	FlyWeight* Clone();

private:
	virtual FlyWeight* DoClone()=0;

};

#endif // !defined(AFX_FLYWEIGHT_H__F36B989D_39BD_4F60_9894_2B4B49C25E85__INCLUDED_)

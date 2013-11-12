// DriverFactory.h: interface for the DriverFactory class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRIVERFACTORY_H__2C8E7DBB_7E74_4898_987F_5956265CC22A__INCLUDED_)
#define AFX_DRIVERFACTORY_H__2C8E7DBB_7E74_4898_987F_5956265CC22A__INCLUDED_
/*
 * Copyright (C), 2006,��ɳ���������˾CAE������
 * All rights reserved.
 *
  �ļ����ƣ�DriverFactory.h
  ժҪ�� �ļ����������������ļ���չ��������ͬ���ļ�����   
  author  : LSP          
*/
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Factory.h"
class Driver;

class DriverFactory :public CFactory<Driver,CString>   
{
public:
	static DriverFactory* Instance();
	virtual ~DriverFactory();
	
protected:
	DriverFactory();
	
private:
	DriverFactory(const DriverFactory &ref);
	DriverFactory& operator=(const DriverFactory &ref);
};

#endif // !defined(AFX_DRIVERFACTORY_H__2C8E7DBB_7E74_4898_987F_5956265CC22A__INCLUDED_)

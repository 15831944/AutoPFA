// PersistentMgr.h: interface for the PersistentMgr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PERSISTENTMGR_H__F2BF87EF_BCD4_4E69_A51E_4A1A50449979__INCLUDED_)
#define AFX_PERSISTENTMGR_H__F2BF87EF_BCD4_4E69_A51E_4A1A50449979__INCLUDED_
/*
 * Copyright (C), 2006,��ɳ���������˾CAE������
 * All rights reserved.
 *
  �ļ����ƣ�PersistentMgr.h
  ժҪ�� �ļ�������������  
  author  : LSP          
*/

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "PersistenModel.h"
#include "ErrorStatus.h"
#include "DriverFactory.h"
#include "AFTScenarioMgr.h"

class AFX_EXT_CLASS PersistentMgr  
{
public:
	PersistentMgr();
	virtual ~PersistentMgr();

public:
	ErrorStatus::FileError Read(LPCTSTR filename,PersistentModel& model);
	ErrorStatus::FileError Save(LPCTSTR filename,PersistentModel& model);


private:
	Driver* FindDriver(LPCTSTR filename);
	PersistentMgr(const PersistentMgr &ref);
	PersistentMgr& operator=(const PersistentMgr &ref);
	DriverFactory *m_factory;

};

#endif // !defined(AFX_PERSISTENTMGR_H__F2BF87EF_BCD4_4E69_A51E_4A1A50449979__INCLUDED_)

// SysProperFactory.h: interface for the SysProperFactory class.
/*
 * Copyright (C), 2006,��ɳ���������˾CAE������
 * All rights reserved.
 *
  �ļ����ƣ�SysProperFactory.h
  ժҪ��    
  author  : LSP          
*/
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYSPROPERFACTORY_H__A2A56BEC_026D_4D59_8166_A6830D7B9980__INCLUDED_)
#define AFX_SYSPROPERFACTORY_H__A2A56BEC_026D_4D59_8166_A6830D7B9980__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Factory.h"

class ScenarioObject;

class SysProperFactory:public CFactory<ScenarioObject,int>  
{
public:
	static SysProperFactory* Instance();
	virtual ~SysProperFactory();

protected:
	SysProperFactory();

private:
	SysProperFactory(const SysProperFactory &ref);
	SysProperFactory& operator=(const SysProperFactory &ref);

};

#endif // !defined(AFX_SYSPROPERFACTORY_H__A2A56BEC_026D_4D59_8166_A6830D7B9980__INCLUDED_)

// Driver.h: interface for the Driver class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRIVER_H__8E0E0409_5B91_4CFD_8AAE_271F8FE8B7D2__INCLUDED_)
#define AFX_DRIVER_H__8E0E0409_5B91_4CFD_8AAE_271F8FE8B7D2__INCLUDED_
/*
 * Copyright (C), 2006,��ɳ���������˾CAE������
 * All rights reserved.
 *
  �ļ����ƣ�Driver.h
  ժҪ�� �ļ������ӿڣ�   
  author  : LSP          
*/


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "PersistenModel.h"

class Driver  
{
public:
	Driver();
	virtual ~Driver();
	virtual ErrorStatus::FileError Read(LPCTSTR filename,PersistentModel& model)=0;
	virtual ErrorStatus::FileError Save(LPCTSTR filename,PersistentModel& model)=0;

protected:
	BOOL Open(LPCTSTR filename,CStdioFile &File,UINT nOpenFlags);
};

#endif // !defined(AFX_DRIVER_H__8E0E0409_5B91_4CFD_8AAE_271F8FE8B7D2__INCLUDED_)

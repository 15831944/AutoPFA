/*************************************************
  Copyright (C), 1988-2006, UESOFT Co., Ltd.
  File name:      UEConnection.h
  Author:         ���
  Version:        1.0
  Date:           2006.8.22
  Description:    UEConnection����һ�����ض����ݿ������
				  
  Others:         
  Function List:  
    1. Close:�ر�����
	2. ExecuteNoSelectSQL:ִ�в���Ҫ���ؼ�¼���Ĳ���
	3. ExecuteSelectSQL:ִ����Ҫ���ؼ�¼���Ĳ���
	4. Open:��һ�����ݿ�����
*************************************************/

// UEConnection.h: interface for the UEConnection class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UECONNECTION_H__68839F94_AD6A_4297_9A9E_326CFDB8B331__INCLUDED_)
#define AFX_UECONNECTION_H__68839F94_AD6A_4297_9A9E_326CFDB8B331__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afx.h>
#include "UERecordset.h"
#include "SmartPointer.h"
#include "DataBaseDriverHeader.h"

class DataBaseDriver_Exp  UEConnection  
{
public:

	UEConnection();
	virtual ~UEConnection();
public:

	virtual void Close() = 0;
	virtual BOOL IsOpen() = 0;
	virtual BOOL ExecuteNoSelectSQL(const StdString& strSQL) = 0;
	virtual UERecordsetPtr ExecuteSelectSQL(const StdString& strSQL) = 0;
	virtual void Open(const StdString& strCource) =0;
	virtual LONG BeginTrans() = 0;
	virtual LONG CommitTrans() = 0;
	virtual LONG RollbackTrans() = 0;
	

};

typedef UeSmartPtr<UEConnection> UEConnectionPtr;
#endif // !defined(AFX_UECONNECTION_H__68839F94_AD6A_4297_9A9E_326CFDB8B331__INCLUDED_)

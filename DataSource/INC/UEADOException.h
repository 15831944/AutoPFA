/*************************************************
  Copyright (C), 1988-2006, UESOFT Co., Ltd.
  File name:      UEADOException.h
  Author:         ���
  Version:        1.0
  Date:           2006.8.22
  Description:    UEADOException��װADO�е�_com_error�쳣
  Others:         
  Function List:  
    1. Delete:ɾ�����׳����쳣�����Լ���
	2. Description:��ȡ�쳣��������Ϣ
	3. ReportError:���û���������Ծ���Ի������ʽ
*************************************************/


// UEADOException.h: interface for the UEADOException class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UEADOEXCEPTION_H__08C141D4_7CFB_4323_B4EC_9A433E5C8F96__INCLUDED_)
#define AFX_UEADOEXCEPTION_H__08C141D4_7CFB_4323_B4EC_9A433E5C8F96__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "UEException.h"
#include <comdef.h>
#include "DataBaseDriverHeader.h"

class DataBaseDriver_Exp  UEADOException : public UEException  
{
public:

	UEADOException();
	virtual ~UEADOException();
public:
	UEADOException( _com_error& er );
	UEADOException( HRESULT hr );
	void ReportError();
	StdString Description();
	void Delete();


private:
	_com_error m_Error;
};

#endif // !defined(AFX_UEADOEXCEPTION_H__08C141D4_7CFB_4323_B4EC_9A433E5C8F96__INCLUDED_)

/*************************************************
  Copyright (C), 1988-2006, UESOFT Co., Ltd.
  File name:      UEException.h
  Author:         ���
  Version:        1.0
  Date:           2006.8.22
  Description:    UEException��һ��������࣬����һ���쳣��
				  ���������쳣��Ļ��ࡣ
  Others:         
  Function List:  
    1. Delete:ɾ�����׳����쳣�����Լ���
	2. Description:��ȡ�쳣��������Ϣ
	3. ReportError:���û���������Ծ���Ի������ʽ
*************************************************/

// UEException.h: interface for the UEException class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UEEXCEPTION_H__D8F112C6_C529_43C4_9BCD_89638140AC07__INCLUDED_)
#define AFX_UEEXCEPTION_H__D8F112C6_C529_43C4_9BCD_89638140AC07__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class _declspec ( dllexport )   UEException  
{
public:

	UEException();
	virtual ~UEException();
public:

	virtual void ReportError() = 0;
	//���������ʲô�õģ�
	virtual void Delete() = 0;
	virtual CString Description() = 0;
	

};

#endif // !defined(AFX_UEEXCEPTION_H__D8F112C6_C529_43C4_9BCD_89638140AC07__INCLUDED_)

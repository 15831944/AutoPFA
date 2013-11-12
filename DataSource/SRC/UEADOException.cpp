// UEADOException.cpp: implementation of the UEADOException class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "UEADOException.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

UEADOException::UEADOException():m_Error(0)
{
	
}

UEADOException::~UEADOException()
{

}


/*************************************************
  Function:       Delete
  Description:    ɾ���쳣������
  Calls:          ������delete
  Called By:      �������
  Table Accessed: ��
  Table Updated:  ��
  Input:          ��
  Output:         ��
  Return:         ��
  Others:         
*************************************************/

void UEADOException::Delete()
{
	delete this;
}


/*************************************************
  Function:       Description
  Description:    ��ȡ�Ը��쳣��������Ϣ
  Calls:          _com_error����Description
  Called By:      �������
  Table Accessed: ��
  Table Updated:  ��
  Input:          ��
  Output:         ��
  Return:         ������Ϣ�ַ���
  Others:         
*************************************************/

StdString UEADOException::Description()
{
	_bstr_t tmp = this->m_Error.Description();
	const char* strtmp = tmp;
	return StdString(strtmp);
}


/*************************************************
  Function:       ReportError
  Description:    ���û������쳣��
  Calls:          ȫ�ֺ���AfxMessageBox
  Called By:      �������
  Table Accessed: ��
  Table Updated:  ��
  Input:          ��
  Output:         ��
  Return:         ��
  Others:         
*************************************************/

void UEADOException::ReportError()
{
	::AfxMessageBox(this->Description());	
}

UEADOException::UEADOException(HRESULT hr):m_Error(hr)
{
	
}

UEADOException::UEADOException(_com_error& er):m_Error(er)
{

}

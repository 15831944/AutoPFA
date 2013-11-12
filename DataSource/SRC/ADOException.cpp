// ADOException.cpp: implementation of the ADOException class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ADOException.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ADOException::ADOException():m_Error(0)
{

}

ADOException::~ADOException()
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

void ADOException::Delete()
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

CString ADOException::Description()
{
	_bstr_t tmp = this->m_Error.Description();
	const char* strtmp = tmp;
	return CString(strtmp);
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

void ADOException::ReportError()
{
	::AfxMessageBox(this->Description());	
}

ADOException::ADOException(HRESULT hr):m_Error(hr)
{
	
}

ADOException::ADOException(_com_error& e):m_Error(e)
{

}


// UEADORecordset.cpp: implementation of the UEADORecordset class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "UEADORecordset.h"
#include "UEADOException.h"
#include "ueassert.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

UEADORecordset::UEADORecordset()
{
	this->m_pRecordset = NULL;
}

UEADORecordset::~UEADORecordset()
{
	Close();
}

/*************************************************
  Function:       GetRecordCount
  Description:    ��ȡ��ǰ��¼���ļ�¼��Ŀ
  Calls:          
  Called By:      �������
  Table Accessed: ��ǰ��¼��
  Table Updated:  ��
  Input:          ��
  Output:         ��
  Return:         INTֵ����¼��Ŀ��
  Others:         
*************************************************/

INT UEADORecordset::GetRecordCount() const
{
	UEASSERT(m_pRecordset != NULL, _T ( "�ܼ򵥣���������" ));
	long lcount = 0;
	try
	{
		m_pRecordset->get_RecordCount(&lcount);
		return (INT)lcount;//Ϊʲô���ѷ���ֵ��ΪINT��
	}
	catch(_com_error e)
	{
		throw new UEADOException(e);
	} 
}


/*************************************************
  Function:       Close
  Description:    �رյ�ǰ��¼��
  Calls:          ADO����Close
  Called By:      �������
  Table Accessed: ��ǰ��¼��
  Table Updated:  ��ǰ��¼��
  Input:          ��
  Output:         ��
  Return:         ��
  Others:         
*************************************************/

void UEADORecordset::Close()
{
	try
	{
		if (m_pRecordset != NULL && m_pRecordset->State != adStateClosed)
		{
			SUCCEEDED(m_pRecordset->Close());
			m_pRecordset = NULL;
		}
	}
	catch (_com_error& e)
	{
		throw new UEADOException(e);
	}
}


/*************************************************
  Function:       IsBOF
  Description:    �ж��Ƿ�λ�ڼ�¼�����ʼ
  Calls:          
  Called By:      �������
  Table Accessed: ��ǰ��¼��
  Table Updated:  ��
  Input:          ��
  Output:         ��
  Return:         BOOLֵ
  Others:         
*************************************************/

BOOL UEADORecordset::IsBOF() const
{
	UEASSERT(m_pRecordset != NULL, _T ( "�ܼ򵥣���������" ));
	return m_pRecordset->BOF;
}

/*************************************************
  Function:       IsEOF
  Description:    �ж��Ƿ�λ�ڼ�¼�����ʼ
  Calls:          
  Called By:      �������
  Table Accessed: ��ǰ��¼��
  Table Updated:  ��
  Input:          ��
  Output:         ��
  Return:         BOOLֵ
  Others:         
*************************************************/

BOOL UEADORecordset::IsEOF() const
{
	UEASSERT(m_pRecordset != NULL, _T ( "�ܼ򵥣���������" ));
	return m_pRecordset->adoEOF;
}

/*************************************************
  Function:       IsEmpty
  Description:    �жϼ�¼���Ƿ�Ϊ��
  Calls:          
  Called By:      �������
  Table Accessed: ��ǰ��¼��
  Table Updated:  ��
  Input:          ��
  Output:         ��
  Return:         BOOLֵ
  Others:         
*************************************************/

BOOL UEADORecordset:: IsEmpty() const
{
	return IsEOF() && IsBOF();
}


/*************************************************
  Function:       MoveFirst
  Description:    �ƶ�����¼�����ʼ
  Calls:          ADO����MoveFirst
  Called By:      �������
  Table Accessed: ��ǰ��¼��
  Table Updated:  ��
  Input:          ��
  Output:         ��
  Return:         ��
  Others:         
*************************************************/

void UEADORecordset::MoveFirst()
{
	UEASSERT(m_pRecordset != NULL, _T ( "�ܼ򵥣���������" ));
	try
	{
		if (m_pRecordset != NULL) 
		{
			SUCCEEDED(m_pRecordset->MoveFirst());
		}
	}
	catch (_com_error e)
	{
		throw new UEADOException(e);
	} 
}


/*************************************************
  Function:       MovePrevious
  Description:    �ƶ�����¼�����ʼ
  Calls:          ADO����MovePrevious 
  Called By:      �������
  Table Accessed: ��ǰ��¼��
  Table Updated:  ��
  Input:          ��
  Output:         ��
  Return:         ��
  Others:         
*************************************************/

void UEADORecordset::MovePrevious()
{
	UEASSERT(m_pRecordset != NULL, _T ( "�ܼ򵥣���������" ));
	try
	{
		if (m_pRecordset != NULL) 
		{
			SUCCEEDED(m_pRecordset->MovePrevious());
		}
	}
	catch (_com_error e)
	{
		throw new UEADOException(e);
	} 
}


/*************************************************
  Function:       MoveNext
  Description:    �ƶ�����ǰ��¼����һ��λ��
  Calls:          ADO����MoveNext
  Called By:      �������
  Table Accessed: ��ǰ��¼��
  Table Updated:  ��
  Input:          ��
  Output:         ��
  Return:         ��
  Others:         
*************************************************/

void UEADORecordset::MoveNext()
{
	UEASSERT(m_pRecordset != NULL, _T ( "�ܼ򵥣���������" ));
	try
	{
		if (m_pRecordset != NULL) 
		{
			SUCCEEDED(m_pRecordset->MoveNext());
		}
	}
	catch (_com_error e)
	{
		throw new UEADOException(e);
	}
}


/*************************************************
  Function:       MoveLast
  Description:    �ƶ�����¼�������
  Calls:          ADO����MoveLast
  Called By:      �������
  Table Accessed: ��ǰ��¼��
  Table Updated:  ��
  Input:          ��
  Output:         ��
  Return:         ��
  Others:         
*************************************************/

void UEADORecordset::MoveLast()
{
	UEASSERT(m_pRecordset != NULL, _T ( "�ܼ򵥣���������" ));
	try
	{
		if (m_pRecordset != NULL) 
		{
			SUCCEEDED(m_pRecordset->MoveLast());
		}
	}
	catch (_com_error e)
	{
		throw new UEADOException(e);
	} 
}


/*************************************************
  Function:       Update
  Description:    �Ե�ǰ��¼������������
  Calls:          ADO����Update
  Called By:      �������
  Table Accessed: ��ǰ��¼��
  Table Updated:  ��ǰ��¼��
  Input:          ��
  Output:         ��
  Return:         ��
  Others:         
*************************************************/

BOOL UEADORecordset::Update()
{
	UEASSERT(m_pRecordset != NULL, _T ( "�ܼ򵥣���������" ));
	try
	{
		if (m_pRecordset != NULL) 
		{
			HRESULT hr = m_pRecordset->Update();
			if (SUCCEEDED(hr))
			{
				return TRUE;
			}
			else
			{
				return FALSE;
			}
		}
	}
	catch (_com_error e)
	{
		throw new UEADOException(e);
	} 
	return FALSE;
}


/*************************************************
  Function:       BatchUpdate
  Description:    �Ե�ǰ��¼������������
  Calls:          ADO����UpdateBatch
  Called By:      �������
  Table Accessed: ��ǰ��¼��
  Table Updated:  ��ǰ��¼��
  Input:          ��
  Output:         ��
  Return:         ��
  Others:         
*************************************************/

void UEADORecordset::BatchUpdate()
{
	UEASSERT(m_pRecordset != NULL, _T ( "�ܼ򵥣���������" ));
	try
	{
		m_pRecordset->UpdateBatch(adAffectAll);//Ĭ�Ϸ�ʽ
	}
	catch (_com_error e) 
	{
		throw new UEADOException(e);
	}
}

UEADORecordset::UEADORecordset(_RecordsetPtr m_pRecordset)
{
	this->m_pRecordset = m_pRecordset;
}


/*************************************************
  Function:       SetShort(const StdString &strIndex, SHORT nValue)
  Description:    ��ǰ��¼strIndex��������дSHORTֵ
  Calls:          ADO����PutCollect
  Called By:      �������
  Table Accessed: ��ǰ��¼��
  Table Updated:  ��ǰ��¼��
  Input:          const StdString &strIndex:����
				  SHORT nValue:�����õ�ֵ
  Output:         ��
  Return:         ��
  Others:         
*************************************************/

void UEADORecordset::SetShort(const StdString &strIndex, SHORT nValue)
{
	UEASSERT( m_pRecordset != NULL, _T ( "�ܼ򵥣���������" ) );
	try
	{
		m_pRecordset->PutCollect(_variant_t(strIndex),_variant_t(nValue));
	}
	catch (_com_error e)
	{
		throw new UEADOException(e);
	}
}


/*************************************************
  Function:       SetLong(const StdString &strIndex, LONG nValue)
  Description:    ��ǰ��¼strIndex��������дLONGֵ
  Calls:          ADO����PutCollect
  Called By:      �������
  Table Accessed: ��ǰ��¼��
  Table Updated:  ��ǰ��¼��
  Input:          const StdString &strIndex:����
				  LONG nValue:�����õ�ֵ
  Output:         ��
  Return:         ��
  Others:         
*************************************************/

void UEADORecordset::SetLong(const StdString &strIndex, LONG nValue)
{
	UEASSERT(m_pRecordset != NULL, _T ( "�ܼ򵥣���������" ));
	try
	{
		m_pRecordset->PutCollect(_variant_t(strIndex),_variant_t(nValue));
	}
	catch (_com_error e)
	{
		throw new UEADOException(e);
	}
}


/*************************************************
  Function:       SetDouble(const StdString &strIndex, DOUBLE dbValue)
  Description:    ��ǰ��¼strIndex��������дDoubleֵ
  Calls:          ADO����PutCollect
  Called By:      �������
  Table Accessed: ��ǰ��¼��
  Table Updated:  ��ǰ��¼��
  Input:          const StdString &strIndex:����
				  DOUBLE dbValue:�����õ�ֵ
  Output:         ��
  Return:         ��
  Others:         
*************************************************/

void UEADORecordset::SetDouble(const StdString &strIndex, DOUBLE dbValue)
{
	UEASSERT(m_pRecordset != NULL, _T ( "�ܼ򵥣���������" ));
	try
	{
		m_pRecordset->PutCollect(_variant_t(strIndex),_variant_t(dbValue));
	}
	catch (_com_error e)
	{
		throw new UEADOException(e);
	}
}


/*************************************************
  Function:       SetFloat(const StdString &strIndex, FLOAT fValue)
  Description:    ��ǰ��¼strIndex��������дFLOATֵ
  Calls:          ADO����PutCollect
  Called By:      �������
  Table Accessed: ��ǰ��¼��
  Table Updated:  ��ǰ��¼��
  Input:          const StdString &strIndex:����
				  FLOAT fValue:�����õ�ֵ
  Output:         ��
  Return:         ��
  Others:         
*************************************************/

void UEADORecordset::SetFloat(const StdString &strIndex, FLOAT fValue)
{
	UEASSERT(m_pRecordset != NULL, _T ( "�ܼ򵥣���������" ));
	try
	{
		m_pRecordset->PutCollect(_variant_t(strIndex),_variant_t(fValue));
	}
	catch (_com_error e)
	{
		throw new UEADOException(e);
	}
}


/*************************************************
  Function:       SetString(const StdString &strIndex, const StdString &strValue)
  Description:    ��ǰ��¼strIndex��������д�ַ���
  Calls:          ADO����PutCollect
  Called By:      �������
  Table Accessed: ��ǰ��¼��
  Table Updated:  ��ǰ��¼��
  Input:          const StdString &strIndex:����
				  const StdString &strValue:�����õ�ֵ
  Output:         ��
  Return:         ��
  Others:         
*************************************************/

void UEADORecordset::SetString(const StdString &strIndex, const StdString &strValue)
{
	UEASSERT(m_pRecordset != NULL, _T ( "�ܼ򵥣���������" ));
	try
	{
		m_pRecordset->PutCollect(_variant_t(strIndex),_variant_t(strValue));
	}
	catch (_com_error e)
	{
		throw new UEADOException(e);
	}
}


/*************************************************
  Function:       SetBool(const StdString &strIndex, BOOL bValue)
  Description:    ��ǰ��¼strIndex��������дBOOLֵ
  Calls:          ADO����PutCollect
  Called By:      �������
  Table Accessed: ��ǰ��¼��
  Table Updated:  ��ǰ��¼��
  Input:          const StdString &strIndex:����
				  BOOL bValue:�����õ�ֵ
  Output:         ��
  Return:         ��
  Others:         
*************************************************/

void UEADORecordset::SetBool(const StdString &strIndex, bool bValue)
{
	UEASSERT(m_pRecordset != NULL, _T ( "�ܼ򵥣���������" ));
	try
	{
		m_pRecordset->PutCollect(_variant_t(strIndex),_variant_t(bValue));
	}
	catch (_com_error e)
	{
		throw new UEADOException(e);
	}
}


/*************************************************
  Function:       NewRecord
  Description:    ��ǰ��¼������һ���հ׼�¼��������
				  �Ժ�ĳ��ʱ�����øü�¼������
  Calls:          ADO����Supports��AddNew
  Called By:      �������
  Table Accessed: ��ǰ��¼��
  Table Updated:  ��ǰ��¼��
  Input:          ��
  Output:         ��
  Return:         ��
  Others:         
*************************************************/

void UEADORecordset::NewRecord()
{
	UEASSERT( m_pRecordset != NULL, _T ( "�ܼ򵥣���������" ) );
	try
	{
		if (m_pRecordset->Supports(adAddNew))
		{
			m_pRecordset->AddNew();//ֻ����һ���¼�¼��û�����ֵ��
		}
		else
		{
			AfxMessageBox("���ܲ���");
		}
	}
	catch (_com_error e)
	{
		throw new UEADOException(e);
	}
}


/*************************************************
  Function:       GetShort(const StdString &strIndex)
  Description:    �ӵ�ǰ��¼�õ�һ��BOOLֵ
  Calls:          ADO����GetCollect
  Called By:      �������
  Table Accessed: ��ǰ��¼��
  Table Updated:  ��
  Input:          const StdString &strIndex:����Ҫȡ����
  Output:         ��
  Return:         Shortֵ
  Others:         
*************************************************/

short UEADORecordset::GetShort(const StdString &strIndex) const
{
	UEASSERT(m_pRecordset != NULL, _T ( "�ܼ򵥣���������" ));
	try
	{
		short sdefault = 0;
		_variant_t var;
		var = m_pRecordset->GetCollect(_variant_t(strIndex));
		if (var.vt == VT_NULL)
		{
			return sdefault;
		}
		return short(var);
	}
	catch (_com_error e)
	{
		throw new UEADOException(e);
	}
	return 0;
}


/*************************************************
  Function:       GetLong(const StdString &strIndex)
  Description:    �ӵ�ǰ��¼�õ�һ��BOOLֵ
  Calls:          ADO����GetCollect
  Called By:      �������
  Table Accessed: ��ǰ��¼��
  Table Updated:  ��
  Input:          const StdString &strIndex:����Ҫȡ����
  Output:         ��
  Return:         Longֵ
  Others:         
*************************************************/

LONG UEADORecordset::GetLong(const StdString &strIndex) const
{
	UEASSERT(m_pRecordset != NULL, _T ( "�ܼ򵥣���������" ));
	try
	{
		LONG ldefault = 0;
		_variant_t var;
		var = m_pRecordset->GetCollect(_variant_t(strIndex));
		if (var.vt == VT_NULL)
		{
			return ldefault;
		}
		return long(var);
	}
	catch (_com_error e)
	{
		throw new UEADOException(e);
	}
	return 0;
}


/*************************************************
  Function:       GetDouble(const StdString &strIndex)
  Description:    �ӵ�ǰ��¼�õ�һ��BOOLֵ
  Calls:          ADO����GetCollect
  Called By:      �������
  Table Accessed: ��ǰ��¼��
  Table Updated:  ��
  Input:          const StdString &strIndex:����Ҫȡ����
  Output:         ��
  Return:         Doubleֵ
  Others:         
*************************************************/

DOUBLE UEADORecordset::GetDouble(const StdString &strIndex) const
{
	UEASSERT(m_pRecordset != NULL, _T ( "�ܼ򵥣���������" ));
	try
	{
		double ddefault = 0;
		_variant_t var;
		var = m_pRecordset->GetCollect(_variant_t(strIndex));
		if (var.vt == VT_NULL)
		{
			return ddefault;
		}
		return double(var);
	}
	catch (_com_error e)
	{
		throw new UEADOException(e);
	}
	return 0;
}


/*************************************************
  Function:       GetFloat(const StdString &strIndex)
  Description:    �ӵ�ǰ��¼�õ�һ��BOOLֵ
  Calls:          ADO����GetCollect
  Called By:      �������
  Table Accessed: ��ǰ��¼��
  Table Updated:  ��
  Input:          const StdString &strIndex:����Ҫȡ����
  Output:         ��
  Return:         Floatֵ
  Others:         
*************************************************/

FLOAT UEADORecordset::GetFloat(const StdString &strIndex) const
{
	UEASSERT(m_pRecordset != NULL, _T ( "�ܼ򵥣���������" ));
	try
	{
		float fdefault = 0;
		_variant_t var;
		var = m_pRecordset->GetCollect(_variant_t(strIndex));
		if (var.vt == VT_NULL)
		{
			return fdefault;
		}
		return float(var);
	}
	catch (_com_error e)
	{
		throw new UEADOException(e);
	}
	return 0;
}


/*************************************************
  Function:       GetString(const StdString &strIndex)
  Description:    �ӵ�ǰ��¼�õ�һ��BOOLֵ
  Calls:          ADO����GetCollect
  Called By:      �������
  Table Accessed: ��ǰ��¼��
  Table Updated:  ��
  Input:          const StdString &strIndex:����Ҫȡ����
  Output:         ��
  Return:         �ַ���
  Others:         
*************************************************/

StdString UEADORecordset::GetString(const StdString &strIndex) const
{
	UEASSERT(m_pRecordset != NULL, _T ( "�ܼ򵥣���������" ));
	try
	{
		_variant_t var;
		StdString strdefault = "";
		var = m_pRecordset->GetCollect(_variant_t(strIndex));
		if (var.vt == VT_NULL)
		{
			return strdefault;
		}
		return (LPCSTR)_bstr_t(var);
	}
	catch (_com_error e)
	{
		throw new UEADOException(e);
	}
	return "";
}


/*************************************************
  Function:       Delete
  Description:    ɾ����ǰ��¼
  Calls:          ADO����Delete��Update
  Called By:      �������
  Table Accessed: ��ǰ��¼��
  Table Updated:  ��ǰ��¼��
  Input:          ��
  Output:         ��
  Return:         ��
  Others:         
*************************************************/

void UEADORecordset::Delete()
{
	UEASSERT(m_pRecordset != NULL, _T ( "�ܼ򵥣���������" ));
	try
	{
		m_pRecordset->Delete(adAffectCurrent);//Ĭ�ϡ���ɾ����ǰ��¼��
		m_pRecordset->Update();//���¡�Ҫ���ǲ�Ҫ�أ�
	}
	catch (_com_error e)
	{
		throw new UEADOException(e);
	}
}


/*************************************************
  Function:       GetBool(const StdString &strIndex)
  Description:    �ӵ�ǰ��¼�õ�һ��BOOLֵ
  Calls:          ADO����GetCollect
  Called By:      �������
  Table Accessed: ��ǰ��¼��
  Table Updated:  ��
  Input:          const StdString &strIndex:����Ҫȡ����
  Output:         ��
  Return:         BOOLֵ
  Others:         
*************************************************/

BOOL UEADORecordset::GetBool(const StdString &strIndex) const
{
	UEASSERT(m_pRecordset != NULL, _T ( "�ܼ򵥣���������" ));
	try
	{
		BOOL bdefault = FALSE;
		_variant_t var;
		var = m_pRecordset->GetCollect(_variant_t(strIndex));
		if (var.vt == VT_NULL)
		{
			return bdefault;
		}
		return bool(var);
	}
	catch (_com_error e)
	{
		throw new UEADOException(e);
	}
	return false;
}

/*************************************************
  Function:       Get_variant_t(const StdString &strIndex)
  Description:    �ӵ�ǰ��¼�õ�һ��_variant_tֵ
  Calls:          ADO����GetCollect
  Called By:      �������
  Table Accessed: ��ǰ��¼��
  Table Updated:  ��
  Input:          const StdString &strIndex:����Ҫȡ����
  Output:         ��
  Return:         _variant_tֵ
  Others:         
*************************************************/

_variant_t UEADORecordset::Get_variant_t(const StdString& strIndex) const
{
	UEASSERT(m_pRecordset != NULL, _T ( "�ܼ򵥣���������" ));
	try
	{
		_variant_t vdefault;
		_variant_t var;
		var = m_pRecordset->GetCollect(_variant_t(strIndex));
		if (var.vt == VT_NULL)
		{
			return vdefault;
		}
		return var;
	}
	catch (_com_error e)
	{
		throw new UEADOException(e);
	}
	return false;
}

/*************************************************
  Function:       Set_variant_t(const StdString& strIndex,_variant_t vr)
  Description:    ��ǰ��¼strIndex��������д_variant_tֵ
  Calls:          ADO����PutCollect
  Called By:      �������
  Table Accessed: ��ǰ��¼��
  Table Updated:  ��ǰ��¼��
  Input:          const StdString &strIndex:����
				  _variant_t vr:�����õ�ֵ
  Output:         ��
  Return:         ��
  Others:         
*************************************************/

void UEADORecordset::Set_variant_t(const StdString& strIndex,_variant_t vr)
{
	UEASSERT(m_pRecordset != NULL, _T ( "�ܼ򵥣���������" ));
	try
	{
		m_pRecordset->PutCollect(_variant_t(strIndex),vr);
	}
	catch (_com_error e)
	{
		throw new UEADOException(e);
	}
}

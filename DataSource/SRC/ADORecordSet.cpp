// ADORecordSet.cpp: implementation of the ADORecordSet class.
/************************************************************************
�汾: 8.0  ����ʱ��: 2008/12/18  ����:  denglb ������:
����:        ʵ�ֶ����ݼ��Ĳ���                                                      
����:                                                               
���:                                                              
< �޸��� >    < ʱ�� >     < �汾 >        < ���� >                                                                               
************************************************************************/

#include "stdafx.h"
#include "ADORecordSet.h"
#include "ADOException.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ADORecordSet::ADORecordSet()
{
	this->m_pRecordset = NULL;
}

ADORecordSet::~ADORecordSet()
{
	Close();
}

INT ADORecordSet::GetRecordCount() const
{
	// 	UEASSERT(m_pRecordset != NULL, _T ( "�ܼ򵥣���������" ));
	long lcount = 0;
	try
	{
		m_pRecordset->get_RecordCount(&lcount);
		return (INT)lcount;//Ϊʲô���ѷ���ֵ��ΪINT��
	}
	catch(_com_error&)
	{
		//throw new UEADOException(e);
	}
	
}

void ADORecordSet::Close()
{
	try
	{
		if (m_pRecordset != NULL && m_pRecordset->State != adStateClosed)
		{
			SUCCEEDED(m_pRecordset->Close());
			m_pRecordset = NULL;
		}
	}
	catch (_com_error&)
	{
		//throw new UEADOException(e);
	}
}

BOOL ADORecordSet::IsBOF() const
{
	// 	UEASSERT(m_pRecordset != NULL, _T ( "�ܼ򵥣���������" ));
	return m_pRecordset->BOF;
}

BOOL ADORecordSet::IsEOF() const
{
	// 	UEASSERT(m_pRecordset != NULL, _T ( "�ܼ򵥣���������" ));
	return m_pRecordset->adoEOF;
}

BOOL ADORecordSet:: IsEmpty() const
{
	return IsEOF() && IsBOF();
}

void ADORecordSet::MoveFirst()
{
	// 	UEASSERT(m_pRecordset != NULL, _T ( "�ܼ򵥣���������" ));
	try
	{
		if (m_pRecordset != NULL) 
		{
			SUCCEEDED(m_pRecordset->MoveFirst());
		}
	}
	catch (_com_error e)
	{
		//throw new UEADOException(e);
	} 
}

void ADORecordSet::MovePrevious()
{
	// 	UEASSERT(m_pRecordset != NULL, _T ( "�ܼ򵥣���������" ));
	try
	{
		if (m_pRecordset != NULL) 
		{
			SUCCEEDED(m_pRecordset->MovePrevious());
		}
	}
	catch (_com_error e)
	{
	//	throw new UEADOException(e);
	} 
}

void ADORecordSet::MoveNext()
{
	// 	UEASSERT(m_pRecordset != NULL, _T ( "�ܼ򵥣���������" ));
	try
	{
		if (m_pRecordset != NULL) 
		{
			SUCCEEDED(m_pRecordset->MoveNext());
		}
	}
	catch (_com_error e)
	{
	//	throw new UEADOException(e);
	}
}

void ADORecordSet::MoveLast()
{
	// 	UEASSERT(m_pRecordset != NULL, _T ( "�ܼ򵥣���������" ));
	try
	{
		if (m_pRecordset != NULL) 
		{
			SUCCEEDED(m_pRecordset->MoveLast());
		}
	}
	catch (_com_error e)
	{
	//	throw new UEADOException(e);
	} 
}

BOOL ADORecordSet::Update()
{
	// 	UEASSERT(m_pRecordset != NULL, _T ( "�ܼ򵥣���������" ));
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
	//	throw new UEADOException(e);
	} 
	return FALSE;
}

void ADORecordSet::BatchUpdate()
{
	// 	UEASSERT(m_pRecordset != NULL, _T ( "�ܼ򵥣���������" ));
	try
	{
		m_pRecordset->UpdateBatch(adAffectAll);//Ĭ�Ϸ�ʽ
	}
	catch (_com_error e) 
	{
		//throw new UEADOException(e);
	}
}

//ADORecordSet::ADORecordSet(_RecordsetPtr m_pRecordset)
//{
//	this->m_pRecordset = m_pRecordset;
//}

void ADORecordSet::SetShort(const CString &strIndex, SHORT nValue)
{
	// 	UEASSERT( m_pRecordset != NULL, _T ( "�ܼ򵥣���������" ) );
	try
	{
		m_pRecordset->PutCollect(_variant_t(strIndex),_variant_t(nValue));
	}
	catch (_com_error e)
	{
		//throw new UEADOException(e);
	}
}

void ADORecordSet::SetLong(const CString &strIndex, LONG nValue)
{
	// 	UEASSERT(m_pRecordset != NULL, _T ( "�ܼ򵥣���������" ));
	try
	{
		m_pRecordset->PutCollect(_variant_t(strIndex),_variant_t(nValue));
	}
	catch (_com_error e)
	{
	//	throw new UEADOException(e);
	}
}

void ADORecordSet::SetDouble(const CString &strIndex, DOUBLE dbValue)
{
	// 	UEASSERT(m_pRecordset != NULL, _T ( "�ܼ򵥣���������" ));
	try
	{
		m_pRecordset->PutCollect(_variant_t(strIndex),_variant_t(dbValue));
	}
	catch (_com_error e)
	{
	//	throw new UEADOException(e);
	}
}

void ADORecordSet::SetFloat(const CString &strIndex, FLOAT fValue)
{
	// 	UEASSERT(m_pRecordset != NULL, _T ( "�ܼ򵥣���������" ));
	try
	{
		m_pRecordset->PutCollect(_variant_t(strIndex),_variant_t(fValue));
	}
	catch (_com_error e)
	{
	//	throw new UEADOException(e);
	}
}

void ADORecordSet::SetString(const CString &strIndex, const CString &strValue)
{
	// 	UEASSERT(m_pRecordset != NULL, _T ( "�ܼ򵥣���������" ));
	try
	{
		m_pRecordset->PutCollect(_variant_t(strIndex),_variant_t(strValue));
	}
	catch (_com_error e)
	{
	//	throw new UEADOException(e);
	}
}

void ADORecordSet::SetBool(const CString &strIndex, bool bValue)
{
	// 	UEASSERT(m_pRecordset != NULL, _T ( "�ܼ򵥣���������" ));
	try
	{
		m_pRecordset->PutCollect(_variant_t(strIndex),_variant_t(bValue));
	}
	catch (_com_error e)
	{
	//	throw new UEADOException(e);
	}
}

void ADORecordSet::NewRecord()
{
	// 	UEASSERT( m_pRecordset != NULL, _T ( "�ܼ򵥣���������" ) );
	try
	{
		if (m_pRecordset->Supports(adAddNew))
		{
			m_pRecordset->AddNew();//ֻ����һ���¼�¼��û�����ֵ��
		}
		else
		{
			AfxMessageBox(_T("���ܲ���"));
		}
	}
	catch (_com_error e)
	{
	//	throw new UEADOException(e);
	}
}

short ADORecordSet::GetShort(const CString &strIndex) const
{
	// 	UEASSERT(m_pRecordset != NULL, _T ( "�ܼ򵥣���������" ));
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
	//	throw new UEADOException(e);
	}
	return 0;
}

LONG ADORecordSet::GetLong(const CString &strIndex) const
{
	// 	UEASSERT(m_pRecordset != NULL, _T ( "�ܼ򵥣���������" ));
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
		//throw new UEADOException(e);
	}
	return 0;
}

DOUBLE ADORecordSet::GetDouble(const CString &strIndex) const
{
	// 	UEASSERT(m_pRecordset != NULL, _T ( "�ܼ򵥣���������" ));
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
	//	throw new UEADOException(e);
	}
	return 0;
}

FLOAT ADORecordSet::GetFloat(const CString &strIndex) const
{
	// 	UEASSERT(m_pRecordset != NULL, _T ( "�ܼ򵥣���������" ));
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
	//	throw new UEADOException(e);
	}
	return 0;
}

CString ADORecordSet::GetString(const CString &strIndex) const
{
	// 	UEASSERT(m_pRecordset != NULL, _T ( "�ܼ򵥣���������" ));
	try
	{
		_variant_t var;
		CString strdefault = _T("");
		var = m_pRecordset->GetCollect(_variant_t(strIndex));
		if (var.vt == VT_NULL)
		{
			return strdefault;
		}
		return (LPCSTR)_bstr_t(var);
	}
	catch (_com_error e)
	{
	//	throw new UEADOException(e);
	}
	return _T("");
}

void ADORecordSet::Delete()
{
	// 	UEASSERT(m_pRecordset != NULL, _T ( "�ܼ򵥣���������" ));
	try
	{
		m_pRecordset->Delete(adAffectCurrent);//Ĭ�ϡ���ɾ����ǰ��¼��
		m_pRecordset->Update();//���¡�Ҫ���ǲ�Ҫ�أ�
	}
	catch (_com_error e)
	{
		//throw new UEADOException(e);
	}
}

BOOL ADORecordSet::GetBool(const CString &strIndex) const
{
	// 	UEASSERT(m_pRecordset != NULL, _T ( "�ܼ򵥣���������" ));
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
	//	throw new UEADOException(e);
	}
	return false;
}

_variant_t ADORecordSet::Get_variant_t(const CString& strIndex) const
{
	// 	UEASSERT(m_pRecordset != NULL, _T ( "�ܼ򵥣���������" ));
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
	//	throw new UEADOException(e);
	}
	return false;
}

void ADORecordSet::Set_variant_t(const CString& strIndex,_variant_t vr)
{
	// 	UEASSERT(m_pRecordset != NULL, _T ( "�ܼ򵥣���������" ));
	try
	{
		m_pRecordset->PutCollect(_variant_t(strIndex),vr);
	}
	catch (_com_error e)
	{
	//	throw new UEADOException(e);
	}
}

ADORecordSet::ADORecordSet(_RecordsetPtr m_pRecordset)
{
	this->m_pRecordset = m_pRecordset;
}

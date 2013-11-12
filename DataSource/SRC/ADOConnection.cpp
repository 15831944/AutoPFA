// ADOConnection.cpp: implementation of the ADOConnection class.
/************************************************************************
�汾: 8.0  ����ʱ��: 2008/12/18  ����: denglb ������:
����:     ʵ�ֶ����ݿ�Ĳ���                                                         
����:                                                               
���:                                                              
< �޸��� >    < ʱ�� >     < �汾 >        < ���� >                                                                               
************************************************************************/

#include "stdafx.h"
#include "ADOConnection.h"
#include "ADOException.h"
#include <afx.h>
#include <io.h>
#include <SYS/STAT.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ADOConnection::ADOConnection():m_pConnection(*m_pConn),m_pConn(new _ConnectionPtr)
{

}

ADOConnection::~ADOConnection()
{
	this->Close();
}

void ADOConnection::Open(const CString &strCource)
{
	HRESULT hr;
	try
	{
		CoInitialize(NULL); 
		hr = this->m_pConnection.CreateInstance(_T("ADODB.Connection")/*__uuidof(Connection)*/);
		if (SUCCEEDED(hr))
		{
			hr = m_pConnection->Open(_bstr_t( _T("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=") + strCource ),_T(""),_T(""),-1);
			/*******************************************
				HRESULT Connection15::Open ( _bstr_t ConnectionString, _bstr_t UserID, _bstr_t Password, long Options )
				ConnectionStringΪ�����ִ�,UserID���û���, Password�ǵ�½����,Options������ѡ��,����ָ��Connection��������ݵĸ������Ȩ,
				Options���������¼�������:
				adModeUnknown:ȱʡ����ǰ�����Ȩδ����
				adModeRead:ֻ��
				adModeWrite:ֻд
				adModeReadWrite:���Զ�д
				adModeShareDenyRead:��ֹ����Connection�����Զ�Ȩ�޴�����
				adModeShareDenyWrite:��ֹ����Connection������дȨ�޴�����
				adModeShareExclusive:��ֹ����Connection�����Զ�дȨ�޴�����
				adModeShareDenyNone:��ֹ����Connection�������κ�Ȩ�޴�����

				���Ǹ���һЩ���õ����ӷ�ʽ����Ҳο�:
				(1)ͨ��JET���ݿ������ACCESS2000���ݿ������

				m_pConnection->Open("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=C:\\test.mdb","","",adModeUnknown);

			**********************************************/
		}
	}
	catch (_com_error e)
	{
		AfxMessageBox( e.Description() );
	}
}

/*************************************************
  Function:       ExecuteSelectSQL
  Description:    ִ����Ҫ���ؼ�¼���Ĳ���
  Calls:          ADO����CreateInstance��Open
  Called By:      �������
  Table Accessed: ��ǰ�򿪱�
  Table Updated:  ��ǰ�򿪱�
  Input:          ��
  Output:         ��
  Return:         UERecordsetPtr
  Others:         
*************************************************/

ADORecordSetPtr ADOConnection::ExecuteSelectSQL(const CString &strSQL)
{
	try
	{	
		_RecordsetPtr m_pRecordset;
		m_pRecordset.CreateInstance(__uuidof(Recordset));
		m_pRecordset->Open(_bstr_t(strSQL)
							,(IDispatch*)(*m_pConn)
							,adOpenDynamic
							,adLockOptimistic
							,adCmdText);

		return new ADORecordSet(m_pRecordset);
	}
	catch (_com_error e)
	{
		AfxMessageBox( e.Description() );
	}

	return NULL;
}

_RecordsetPtr ADOConnection::ExecuteSelectSQL(const CString &strSQL,short nMode)
{
	try
	{	
		_RecordsetPtr m_pRecordset;
		m_pRecordset.CreateInstance(__uuidof(Recordset));
		m_pRecordset->Open(_bstr_t(strSQL)
			,(IDispatch*)m_pConnection
			,adOpenDynamic
			,adLockOptimistic
			,adCmdText);
		
		return m_pRecordset;
	}
	catch (_com_error e)
	{
		AfxMessageBox( e.Description() );
	}
	return NULL;//��ʱ���� 
}
/*************************************************
  Function:       ExecuteNoSelectSQL
  Description:    ִ�в���Ҫ���ؼ�¼���Ĳ���
  Calls:          ADO����Execute
  Called By:      �������
  Table Accessed: ��ǰ�򿪱�
  Table Updated:  ��ǰ�򿪱�
  Input:          ��
  Output:         ��
  Return:         ��
  Others:         
*************************************************/

BOOL ADOConnection::ExecuteNoSelectSQL(const CString &strSQL)
{
//	STATBEGIN ( ExecuteNoSelectSQL );
	try
	{
		//_variant_t RecordsAffected;
		//Ϊʲôɾ��һ���ձ�����һ���Ѿ����ڵı����򶼻�������������������鷳������
		//��û�н���ɾ��������أ�����
		_variant_t RecordsAffected;
		m_pConnection->Execute(_bstr_t(strSQL),NULL,adCmdText);
		ULONG iInfluence = (long)RecordsAffected;
	}
	catch (_com_error e)
	{
		//#ifndef NDEBUG
		
		CFile file;
		if ( file.Open( _T ( "C:\\SQL.err" ), CFile::modeReadWrite | CFile::modeNoTruncate ) )
		{
			
			
			SYSTEMTIME time;
			::GetLocalTime( &time );
			
			CString strTemp;
			strTemp.Format( _T("(%d-%d-%d-%d-%d )"), time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute );
			
			strTemp = strSQL + strTemp + _T ( "\r\n" );
			
			file.SeekToEnd();
			file.Write( strTemp, strTemp.GetLength() );
			
			file.Close();
		}	
		
		throw e;
	}
//	STATEND;
	return FALSE;
}

/*************************************************
  Function:       BeginTrans
  Description:    ����������
  Calls:          
  Called By:      �������
  Input:          ��
  Output:         ��
  Return:         LONG
  Others:         
*************************************************/

LONG ADOConnection::BeginTrans()
{
	LONG lResult = 0;
	try
	{
		m_pConnection->BeginTrans();
	}
	catch ( _com_error e ) 
	{
		throw  e;
	}
	return lResult;
}

/*************************************************
  Function:       Close
  Description:    �ر���ADO���ݿ������
  Calls:          ADO����Close
  Called By:      �������
  Table Accessed: ��
  Table Updated:  ��
  Input:          ��
  Output:         ��
  Return:         ��
  Others:         
*************************************************/

void ADOConnection::Close()
{
	try
	{
		if(m_pConnection->State != adStateClosed)
			{
				m_pConnection->Close();
				CoUninitialize();//�����2006-11.9
			}
			m_pConnection = NULL; 
		//	delete m_pConn;
	}
	catch (_com_error e)
	{
		throw new ADOException(e);
	}
}

BOOL ADOConnection::IsOpen()
{
	if( m_pConnection == NULL || m_pConnection->State == adStateClosed )
	{
		return FALSE;
	}
	return TRUE;
}

BOOL ADOConnection::GetConnectionptr( _ConnectionPtr& pConnect )
{
	pConnect = m_pConnection;
	return TRUE;
}
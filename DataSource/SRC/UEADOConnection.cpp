// UEADOConnection.cpp: implementation of the UEADOConnection class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\INC\UEADOConnection.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

UEADOConnection::UEADOConnection()
{

}

UEADOConnection::~UEADOConnection()
{

}

_RecordsetPtr UEADOConnection::ExecuteSelect( const char* szSql )
{
	try
	{	
		_RecordsetPtr m_pRecordset;
		m_pRecordset.CreateInstance(__uuidof(Recordset));
		m_pRecordset->Open(_bstr_t(szSql)
							,(IDispatch*)m_conPtr
							,adOpenDynamic
							,adLockOptimistic
							,adCmdText);

#ifndef NDEBUG	
	CFile file;
	if ( file.Open( _T ( "C:\\SQL.ini" ), CFile::modeReadWrite | CFile::modeNoTruncate ) )
	{
		
		
		SYSTEMTIME time;
		::GetLocalTime( &time );
		
		CString strTemp;
		strTemp.Format( "(%d-%d-%d-%d-%d )", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute );
		
		strTemp = szSql + strTemp + _T ( "\r\n" );
		
		file.SeekToEnd();
		file.Write( strTemp.GetBuffer( 1 ), strTemp.GetLength() );
		
		
		file.Close();
	}
#endif
		return m_pRecordset;
	}
	catch (_com_error e)
	{
		CFile file;
		if ( file.Open( _T ( "C:\\SQL.err" ), CFile::modeReadWrite | CFile::modeNoTruncate ) )
		{
			
			
			SYSTEMTIME time;
			::GetLocalTime( &time );
			
			CString strTemp;
			strTemp.Format( "(%d-%d-%d-%d-%d )", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute );
			
			strTemp = szSql + strTemp + _T ( "\r\n" );
			
			file.SeekToEnd();
			file.Write( strTemp.GetBuffer( 1 ), strTemp.GetLength() );
			
			
			file.Close();
		}
		AfxMessageBox( e.Description() );
	}

	return NULL;
}

void UEADOConnection::Open( const char* szDataSource )
{
	HRESULT hr;//
	try
	{
		CoInitialize(NULL); 
		hr = this->m_conPtr.CreateInstance("ADODB.Connection"/*__uuidof(Connection)*/);
		char szDb[0xff] = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=";
		strcat( szDb, szDataSource );
		if (SUCCEEDED(hr))
		{
			hr = m_conPtr->Open(_bstr_t( szDb ),"","",-1);
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
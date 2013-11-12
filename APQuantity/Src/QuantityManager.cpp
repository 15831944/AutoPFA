// QuantityManager.cpp: implementation of the QuantityManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "QuantityManager.h"
#include "QuantityPersist.h"
#include <vector>
#include "Quantity_share.h"
#include "ResourceInstance.h"
using namespace std;



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

QuantityManager::QuantityManager():m_pCurQSys( 0 )
{

}

QuantityManager::~QuantityManager()
{
	QuantitySystemSet::const_iterator ItBegin = m_QSysset.begin();

	for ( ;ItBegin != m_QSysset.end();ItBegin++ )
	{
		delete *ItBegin;
	}
}

BOOL QuantityManager::Init()
{
	QuantityPersist& qp = QuantityPersist::Instance();
	qp.SetConfigURL( m_configFilePath );
	QSysSet qtSet;
	if ( !qp.GetAllQSys( qtSet ) )
	{
		CResourceInstance ins;
		StdString strTmp,strWarnning;
		strTmp.LoadString( IDS_QUANTITY_LOAD_FAILED );
		strWarnning.LoadString( IDS_WARNNING );

		::MessageBox( NULL,strTmp,strWarnning,MB_OK );
		return FALSE;
	}

	QSysSet::const_iterator ItBegin = qtSet.begin();
	for ( ;ItBegin != qtSet.end();ItBegin++ )
	{
		QuantitySystem* pQSys = new QuantitySystem;
		pQSys->Init( *ItBegin );
		m_QSysset.push_back( pQSys );
		
	}
	
	//m_pCurQSys = *( m_QSysset.begin() );    //��ʱ��ôд��
	m_pCurQSys = *( m_QSysset.begin() );  
	return TRUE;
}

void QuantityManager::SetConfigFilePath( const UeStdString& strPath )
{
	m_configFilePath = strPath;
}

/********************************************************************
	����ʱ��:	2:6:2007   14:17
	������:		���
    ���ܣ�     	�õ����еĵ�λ������
    ���������	��
    ����������	set:���Ƽ���
    ����ֵ��	��
    �޸��ˣ�
*********************************************************************/
void QuantityManager::GetAllQuantitySysNames( vector< UeStdString >& set )
{	
	QuantitySystemSet::const_iterator ItBegin = m_QSysset.begin();

	for ( ;ItBegin != m_QSysset.end();ItBegin++ )
	{
		set.push_back( ( *ItBegin )->GetQuantitySysName() );
	}
}

/********************************************************************
	����ʱ��:	2:6:2007   14:21
	������:		���
    ���ܣ�     	����ϵͳ�е�ǰ�ĵ�λ�ƣ�����ѹ��Ƹ�ΪӢ��
    ���������	strQSysName
    ����������	��
    ����ֵ��	��
    �޸��ˣ�
*********************************************************************/
void QuantityManager::SetNewQuantitySys( const UeStdString& strQSysName )
{
	QuantitySystemSet::const_iterator ItBegin = m_QSysset.begin();

	for ( ;ItBegin != m_QSysset.end();ItBegin++ )
	{
		if ( ( *ItBegin )->GetQuantitySysName() == strQSysName )
		{
			m_pCurQSys = *ItBegin;
			return ;
		}
	}

	ASSERT( FALSE );
	return ;
}

/********************************************************************
	����ʱ��:	1:6:2007   17:28
	������:		���
	���ܣ�     	��ĳ��λ�µ���ֵת��Ϊ����������׼��λ����ֵ
	���������	strQuantity:���������磺���ȣ�
				strCurUnit:��ǰ��λ���磺�ף�
				d:��ֵ
	����������	��
	����ֵ��	����������׼��λ����ֵ
	�޸��ˣ�
*********************************************************************/
BOOL QuantityManager::TransformToStd( double& dOut,const UeStdString& strQuantity,const UeStdString& strCurUnit,double d )
{
	return m_pCurQSys->TransformToStd( dOut,strQuantity,strCurUnit,d );
}

BOOL QuantityManager::TransformToStd( double& dOut,const UeStdString& strCurUnit,double d )
{
	return m_pCurQSys->TransformToStd( dOut,strCurUnit,d );
}

BOOL QuantityManager::TransformFromStd( double& dOut,const UeStdString& strDesUnit,double d )
{
	return m_pCurQSys->TransformFromStd( dOut,strDesUnit,d );
}

/********************************************************************
	����ʱ��:	1:6:2007   17:31
	������:		���
	���ܣ�     	��һ�ֵ�λ����ֵת��Ϊ��һ�ֵ�λ����ֵ���������ϱ�����п�ת���ԣ�
	���������	strSrc:��ǰ��λ���磺�ף�
				strDes:Ŀ�굥λ���磺���ף�
				d:��ֵ
	����������	��
	����ֵ��	��һ�ֵ�λ����ֵ
	�޸��ˣ�
*********************************************************************/
BOOL QuantityManager::TransformFromTo( double& dOut,const UeStdString& strSrc,const UeStdString& strDes,double d )
{
	return m_pCurQSys->TransformFromTo( dOut,strSrc,strDes,d );
}

/********************************************************************
	����ʱ��:	1:6:2007   17:35
	������:		���
	���ܣ�     	�õ�ĳ�����������е�λ�ַ���
	���������	strQuantity:�����������ƣ��磺���ȣ�
	����������	set:��λ�ַ�������
	����ֵ��	BOOL
	�޸��ˣ�
*********************************************************************/
BOOL QuantityManager::GetUnitStringsOfOneQuantity( const UeStdString& strQuantity,vector< UeStdString >& set )
{
	
	return m_pCurQSys->GetUnitStringsOfOneQuantity( strQuantity,set );
}


/********************************************************************
	����ʱ��:	1:6:2007   17:35
	������:		���
	���ܣ�     	�õ�ĳ�����������е�λ�ַ���
	���������	strQuantity:�����������ƣ��磺���ȣ�
				strDefault:��λ�ַ���
	����ֵ��	BOOL
	�޸��ˣ�
*********************************************************************/
BOOL QuantityManager::GetDefaultUnitString( UeStdString& strDefault,const UeStdString& strQuantity ) const
{
	return m_pCurQSys->GetDefaultUnitString( strDefault,strQuantity );
}

/********************************************************************
	����ʱ��:	7:19:2008   17:35
	������:		�λ���
	���ܣ�     	����ĳ��������Ĭ�ϵ�λ�ַ���
	���������	strQuantity:�����������ƣ��磺���ȣ�
				strDefault:��λ�ַ���
	����ֵ��	BOOL
	�޸��ˣ�
*********************************************************************/
BOOL QuantityManager::SetDefaultUnitString(UeStdString& strDefault,const UeStdString& strQuantity)
{
	return m_pCurQSys->SetDefaultUnitString( strDefault,strQuantity);
}

vector< UeStdString >* QuantityManager::GetPFASet(const UeStdString& strQuantity)
{
    tempset.clear();
	GetUnitStringsOfOneQuantity( strQuantity,tempset );
	return &tempset;
}

void QuantityManager::SetConfigFilePathCString( const CString& strPath )
{
	CString strTemp( strPath );
	m_configFilePath = strTemp.GetBuffer( 0 );
}

void QuantityManager::SaveConfigFile(const UeStdString& strPath)
{

}

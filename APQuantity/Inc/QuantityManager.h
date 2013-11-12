// QuantityManager.h: interface for the QuantityManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_QUANTITYMANAGER_H__71D10FBC_111E_4187_A8B4_A4772C4E0C82__INCLUDED_)
#define AFX_QUANTITYMANAGER_H__71D10FBC_111E_4187_A8B4_A4772C4E0C82__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <string>
#include <vector>
#include <utility>
#include "QuantitySystem.h"
#include "Quantity_share.h"

using namespace std;


class QUANTITY_API QuantityManager  
{
	QuantityManager();
	QuantityManager( const QuantityManager& );
public:
	typedef vector< QuantitySystem* > QuantitySystemSet;
	virtual ~QuantityManager();
	
public:
	static QuantityManager& Instance()
	{
		static QuantityManager mg;
		return mg;
	}

	/********************************************************************
		����ʱ��:	13:6:2007   15:54
		������:		���
	    ���ܣ�     	��ĳ��λ����ֵת��Ϊ����������׼��λ������
	    ���������	strQuantity������������
					strCurUnit:��λ����
					d����ֵ
	    ����������	
	    ����ֵ��
	    �޸��ˣ�
	*********************************************************************/
	BOOL TransformToStd( double& dOut,const UeStdString& strQuantity,const UeStdString& strCurUnit,double d );

	BOOL TransformToStd( double& dOut,const UeStdString& strCurUnit,double d );

	BOOL TransformFromStd( double& dOut,const UeStdString& strDesUnit,double d );

	BOOL TransformFromTo( double& dOut,const UeStdString& strSrc,const UeStdString& strDes,double d );

	BOOL GetUnitStringsOfOneQuantity( const UeStdString& strQuantity,vector< UeStdString >& set );

	//�õ�ĳ��������Ĭ�ϵ�λ���ַ���
	BOOL GetDefaultUnitString( UeStdString& strDefault,const UeStdString& strQuantity ) const;

	//����ĳ��������Ĭ�ϵ�λ(write by: Liaohy)
	BOOL SetDefaultUnitString( UeStdString& strDefault,const UeStdString& strQuantity);
	
	void SetConfigFilePath( const UeStdString& strPath );

	void GetAllQuantitySysNames( vector< UeStdString >& set );

	void SetNewQuantitySys( const UeStdString& strQSysName );


	vector< UeStdString >* GetPFASet(const UeStdString& strQuantity);
	void SetConfigFilePathCString( const CString& strPath );

	//���浱ǰĬ�ϵ�λ�������ļ�
	void SaveConfigFile(const UeStdString& strPath);

public:
	BOOL Init();



private:
	UeStdString m_configFilePath;//��λ�����ļ���λ��
	QuantitySystemSet m_QSysset;//��λ�Ƽ���
	QuantitySystem* m_pCurQSys;//��ǰ��ʹ�õ�λ


	vector<UeStdString> tempset;


};

#endif // !defined(AFX_QUANTITYMANAGER_H__71D10FBC_111E_4187_A8B4_A4772C4E0C82__INCLUDED_)

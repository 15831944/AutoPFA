// QuantityPFA.h: interface for the QuantityPFA class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_QUANTITYPFA_H__B1101788_67F9_49BA_8169_02BDF3E340B2__INCLUDED_)
#define AFX_QUANTITYPFA_H__B1101788_67F9_49BA_8169_02BDF3E340B2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <vector>
using namespace std;
#include "UnitPFA.h"
#include <vector>
#include "Quantity_share.h"
#include "PFAQheader.h"


class QuantityPFA  
{
public:
	typedef vector< UnitPFA* > UnitPFASet;
	QuantityPFA();
	virtual ~QuantityPFA();

public:
	void Init( const QuantityType& qt );

public:
	BOOL CanTransform( const UeStdString& strSrc,const UeStdString& strDes ) const;
	BOOL GetAllUnitStrings( vector< UeStdString >& set ) const;
	const UeStdString GetDefaultUnitString() const
	{
		ASSERT( m_pUserDefaultUnit );
		return m_pUserDefaultUnit->GetUnitString();
	}
	
	const UeStdString& GetQuantityName() const
	{
		return m_QuantityName;
	}
	
	BOOL SetDefaultUnitString(UeStdString& strDefault);//write by Liaohy

	double TransformFromTo( const UeStdString& strSrc,const UeStdString& strDes,double d ) const;
	double TransformToStd( const UeStdString& strCurUnit,double d ) const;
	double TransformFromStd( const UeStdString& strDesUnit,double d ) const;
	BOOL IsIn( const UeStdString& strName ) const;

private:
	UnitPFA* GetUnitPFA( const UeStdString& strName ) const;
private:
	UeStdString m_QuantityName;//������������
	UnitPFASet m_UnitSet;//һ���������µ�λ����
	UnitPFA* m_pSysDefaultUnit;//ϵͳĬ�ϵĵ�λ����ת����Ϊ1.0�ĵ�λ��
	UnitPFA* m_pUserDefaultUnit;//�û������Ĭ�ϵ�λ������ʱ���������е�����һ����λ��

};

#endif // !defined(AFX_QUANTITYPFA_H__B1101788_67F9_49BA_8169_02BDF3E340B2__INCLUDED_)

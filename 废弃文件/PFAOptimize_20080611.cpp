// PFAOptimize.cpp: implementation of the CPFAOptimize class.
//
//////////////////////////////////////////////////////////////////////

#pragma once
#include "stdafx.h"
#include "autopfa.h"
#include "PFAOptimize.h"
#include "MainFrm.h"
#include "ChildFrm.h"
#include "AutoPFAView.h"
#include "AutoPFADoc.h"
#include "Scenario.h"
#include "Fuild.h"
#include "QuantityManager.h"
#include "MinimumSquareSum.h"

const CString MODULUS_ZERO = "ϵ��Ϊ0������������! ";

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPFAOptimize::CPFAOptimize()
{

}

CPFAOptimize::~CPFAOptimize()
{

}


void CPFAOptimize::FindJunOfCircle( Jun& PreJun, Jun& NextJun, ComAndCloseComs&  JunAndCloseJuns, int& iKeyOfChoiceJun )
{
	// ������Ч���ж� 
	ASSERT( NULL != &PreJun );
	ASSERT( NULL != &NextJun );
	ASSERT( NULL != &JunAndCloseJuns );

	ComAndCloseComs::iterator JunAndCloseJunsIterator = JunAndCloseJuns.find( NextJun.GetKey() );
	JunAndCenter* pJunAndCenter =  &JunAndCloseJunsIterator->second; 
	// ���JunAndCloseJuns��ֻ�������ܵ��� ��ô��û��Ҫ���ж��ˣ�ֻ��ָ������PreJun�ڵ�Ľڵ�Ϊ��һ�ڵ�
	if( 2 == pJunAndCenter->size() )
	{
		JunAndCenter::const_iterator JunIterator = pJunAndCenter->begin();
		for ( ; JunIterator != pJunAndCenter->end(); JunIterator++ )
		{
			if ( PreJun.GetKey() != JunIterator->first )
			{
				iKeyOfChoiceJun = JunIterator->first;
				return;
			}
		}
	}
	
	CPoint ptPreJun( PreJun.CenterPt() );
	CPoint ptNextJun( NextJun.CenterPt() );
	
	double dMaxTheta = 2 * PI;                         // ��С����Ի���ֵ�����нǴ�С
	double dPre = 0.0;                                 // ptNextJun-��ptPreJun
	double dNext = 0.0;    	                           // ptNextJun->pComJunCenter
	Pipe* pPipe = NULL;
	JunAndCenter JunCenterVector;
	pair<int, CPoint>* pComJunCenter;
	JunAndCenter::iterator JunCenterIt = pJunAndCenter->begin();
	for( ; JunCenterIt != pJunAndCenter->end(); JunCenterIt++ )
	{
		pComJunCenter = ( pair<int, CPoint>* )JunCenterIt;
		
		// ����ڵ���PreJun�㣬��Ҫ���㣬ֱ��������������һ��
		if ( pComJunCenter->first == PreJun.GetKey() )
		{
			continue;
		}
		
		// ������ԭ���ƶ���ptNextJun
		GetAngle( ( double )( ptPreJun.y - ptNextJun.y ), ( double )( ptPreJun.x - ptNextJun.x ), dPre );
	    GetAngle( ( double )( pComJunCenter->second.y - ptNextJun.y ), ( double )( pComJunCenter->second.x- ptNextJun.x ), dNext );
		dNext = -( dNext - dPre );     // ȡ����Ϊ�˷������
		dNext = dNext > 0 ? dNext : dNext + 2 * PI;
		
		// ȡ��С���ȵĹܵ���Ϊ��һ���ܵ�
		if( dMaxTheta > dNext )
		{
			dMaxTheta = dNext;
			iKeyOfChoiceJun = pComJunCenter->first;
		}
		
	}
}

void CPFAOptimize::GetAngle( const double& dY, const double& dX, double& dAngle )
{
	ASSERT( NULL != &dY );
	ASSERT( NULL != &dX );

	if( fabs(dX - 1e-6) < 0)
	{
		dAngle = dY > 0 ? PI : -PI;
		return;
	}
	dAngle = atan( dY / dX );
	if( dX < 0  )
	{
		dAngle += PI;
		return;
	} 
	if( ( dX > 0 ) && ( dY < 0 ) )
	{
	    dAngle += 2 * PI;
		return;
	}
	return;
}


void CPFAOptimize::CopyVector( JunAndCenter& DestinationVector, JunAndCenter& SourceVector )
{
	JunAndCenter::iterator SourceIt = SourceVector.begin();
	pair< int, CPoint > Temp;
	pair< int, CPoint >* pSource = NULL;
	for ( ; SourceIt != SourceVector.end(); SourceIt++ )
	{
		pSource = SourceIt;
		Temp.first = SourceIt->first;
		Temp.second.x = ( pSource->second ).x;
		Temp.second.y = ( pSource->second ).y;
		DestinationVector.push_back( Temp );
	}
}



BOOL CPFAOptimize::FindBaseCircle( ComponentManager& ComManager, Pipe& BasePipe, BaseCircleDirection Direction, ComMap& JunKeyMap, ComMap& PipeKeyMap, int iMostCircle[] )
{	
	//������Ч���ж�
	ASSERT( NULL != &ComManager );
	ASSERT( NULL != &BasePipe );

	ComAndCloseComs JunAndCloseJuns;
	JunAndCenter CloseJuns;   // ��¼�ڵ�ͽڵ�λ�õ�Vector����ʽ��(�ڵ��ţ��ڵ�λ��)
	Jun* pJun = NULL;
	Component* pJunComponent = NULL;
	Pipe* pPipe = NULL;
	Component* pPipeComponent = NULL;   
	Jun* pPreJun = NULL;
	Jun* pNextJun = NULL;
	Jun* pStartJun = NULL;
	Jun* pStartNextJun = NULL;

	// ͼ�ε��ϡ����ҡ����ĸ������λ�ã�Ϊȷ�������׼��
	int iTop = 2147483647;                       // 2��32�η���һ
	int iLeft = 2147483647;
	int iRight = 0;
	int iBotton = 0;

	IteratorPtr<Component> JunItPtr( ComManager.CreatJunIterator() );

	// �ѽڵ����ڵ������Ľڵ���Ϣ������JunAndCloseJuns
	// ��ڵ�1�ͽڵ�3��4��5��������( 1, ( (3,�ڵ�3λ��), (4���ڵ�4λ��), (5���ڵ�5λ��) ) )
	// Ȼ��ѹܵ�����ܵ������Ĺܵ���ŷ���PipeAndClosePipes
	// ��ܵ�1�͹ܵ�3��4��5��������(1,(3,4,5))
	for( JunItPtr->Fist(); !JunItPtr->IsDone(); JunItPtr->Next() )
    {
		CloseJuns.clear();
		pJunComponent = &JunItPtr->CurrentItem();
    	pJun = dynamic_cast<Jun*>( pJunComponent );

		IteratorPtr<Component> PipeItPtr( ComManager.CreatPipeIterator() );
		for( PipeItPtr->Fist(); !PipeItPtr->IsDone(); PipeItPtr->Next() )
		{
			pPipeComponent = &PipeItPtr->CurrentItem();
	        pPipe = dynamic_cast<Pipe*>( pPipeComponent );
			if( pPipe->StartJun() == pJun->GetKey() )
			{	
				pair< int , CPoint > Temp( pPipe->EndJun(), pPipe->EndPt() );
				CloseJuns.push_back( Temp );
			}
			if( pPipe->EndJun() == pJun->GetKey() )	
			{
				pair< int , CPoint > Temp( pPipe->StartJun(), pPipe->StartPt() );
				CloseJuns.push_back( Temp );
			}
			if( pPipe->GetKey() == BasePipe.GetKey() )
			{
				if ( DEASIL_DIRECTION == Direction )
				{
					pPreJun = ComManager.LookUpJun( pPipe->StartJun() );
					pNextJun = ComManager.LookUpJun( pPipe->EndJun() );
				}
				else
				{
					pPreJun = ComManager.LookUpJun( pPipe->EndJun() );
					pNextJun = ComManager.LookUpJun( pPipe->StartJun() );
				}
			}
		}
		JunAndCloseJuns.insert( ComAndCloseComs::value_type( pJun->GetKey(), CloseJuns ) );

		// ȷ���ĸ�����
		if( iTop > pJun->CenterPt().y )
		{
			iTop = pJun->CenterPt().y;
			iMostCircle[0] = pJun->GetKey();
		}
		if( iBotton < pJun->CenterPt().y )
		{
			iBotton = pJun->CenterPt().y;
			iMostCircle[1] = pJun->GetKey();
		}
		if( iLeft > pJun->CenterPt().x )
		{
			iLeft = pJun->CenterPt().x;
			iMostCircle[2] = pJun->GetKey();
		}
		if( iRight < pJun->CenterPt().x )
		{
			iRight = pJun->CenterPt().x;
			iMostCircle[3] = pJun->GetKey();
		}
	}

	JunItPtr->Fist();
	pJunComponent = &JunItPtr->CurrentItem();
    pJun = dynamic_cast<Jun*>( pJunComponent );
	CloseJuns.clear();
	ComAndCloseComs::iterator JunIt = JunAndCloseJuns.find( pJun->GetKey() );
	CopyVector( CloseJuns, JunIt->second );  
	
	// Ѱ�һ����ڵ����
	pStartJun = pPreJun;
	pStartNextJun = pNextJun;
	int iKeyOfChoiceJun = 0;                 // ��������ĸ��ڵ�����Ϊ��������һ�ڵ���
	JunKeyMap.push_back( pNextJun->GetKey() );
	BOOL bFirst = TRUE;
	while( ( pNextJun != pStartNextJun ) || ( pPreJun != pStartJun ) || bFirst )
	{
		bFirst = FALSE;
		FindJunOfCircle( *pPreJun, *pNextJun, JunAndCloseJuns, iKeyOfChoiceJun );
	    pPreJun = pNextJun;
		pNextJun = ComManager.LookUpJun( iKeyOfChoiceJun );
		JunKeyMap.push_back( pNextJun->GetKey() );
	}
	

	// Ѱ�һ����ܵ�����
	ComMap::const_iterator JunKeyNextIterator = NULL;
	int iJunNextkey = 0;                        // ����Ļ�-�ڵ�����нڵ�ı�ţ� �����Ҳһ��
	int iJunPreKey = 0;
	map< int, int > PipeOrder;                             // (�ܵ��ڻ��е�λ�ã��ܵ����)
	int iPipePosition = 0;                      // �ܵ��ڻ��е�λ��
	IteratorPtr<Component> PipeItPtr( ComManager.CreatPipeIterator() );
	for( PipeItPtr->Fist(); !PipeItPtr->IsDone(); PipeItPtr->Next() )
	{
		pPipeComponent = &PipeItPtr->CurrentItem();
		pPipe = dynamic_cast<Pipe*>( pPipeComponent );
		JunKeyNextIterator = JunKeyMap.begin();
		iPipePosition = 0;
		iJunPreKey = *JunKeyNextIterator;
		JunKeyNextIterator++;
        for ( ; JunKeyNextIterator != JunKeyMap.end(); JunKeyNextIterator++ )
		{
			iJunNextkey = *JunKeyNextIterator;
			
			// ����ܵ��ͻ�������ڽڵ���������ô����ܵ��϶��ǻ���Ĺܵ�
			if( ( ( pPipe->StartJun() == iJunPreKey ) && ( pPipe->EndJun() == iJunNextkey ) ))
			{
				PipeOrder.insert( map<int,int>::value_type( iPipePosition, pPipe->GetKey() ) );	
			}
			if( ( ( pPipe->EndJun() == iJunPreKey ) && ( pPipe->StartJun() == iJunNextkey ) ) )
			{
				int i = -1 * pPipe->GetKey();
                PipeOrder.insert( map<int,int>::value_type( iPipePosition, i ) );
			}
			iJunPreKey = iJunNextkey;
			iPipePosition++;
		}
	}
	
	// ��PipeOrder�����Ϣ����PipeKeyMap��
    // PipeOrder��Ϣ(�ܵ��ڻ��е�λ�ã��ܵ��ı��)
	int iCountCircleJun = PipeOrder.size();
	int iPipeKey = 0;
	map< int, int >::iterator PipeIterator = NULL;
	for ( iPipePosition = 0, iPipeKey = 0; iPipePosition < iCountCircleJun; iPipePosition++ )
	{
		PipeIterator = PipeOrder.find( iPipePosition );
		if( PipeIterator == PipeOrder.end() )
		{
			break;
		}
		iPipeKey = PipeIterator->second;
		PipeKeyMap.push_back( iPipeKey );
	}

	return TRUE;
}



BOOL CPFAOptimize::JudgeMaxCircle( ComMap& JunKeyMap, int iMostCircle[], vector< CString >& JunPointGather, CString& strMaxCircle )
{
	// 
	ASSERT( NULL != &JunKeyMap );
	ASSERT( NULL != iMostCircle );
	ComMap TempKeyMap;                                  // ����Ԫ��
	ComMap::iterator ComIt;
    CString strCircle = "";                               // ���Ľڵ���Ϣ���ڵ����Ѿ����к���
	CString strTemp = "";
	int i = 0;
	// �ѻ�JunKeyMap�еĵڶ��������һ��Ԫ�ؽڵ���Ϣ������TempKeyMap
	// ��ΪJunKeyMap�еĻ��ڵ���Ϣ�ظ��˿�ʼ�㣬 ����(5,4,6,1,5)
    for( ComIt = JunKeyMap.begin(), ComIt++; ComIt != JunKeyMap.end(); ComIt++ )
    {
		TempKeyMap.push_back( *ComIt );
    }

	sort( TempKeyMap.begin(), TempKeyMap.end() );     // �����㷨����С�����TempKeyMap����

    // �����кõĻ��ڵ���Ϣ����strCircle�У� ����(1,4,5,6)
	for( ComIt = TempKeyMap.begin(); ComIt != TempKeyMap.end(); ComIt++ )
	{
		strCircle = strCircle + COMPARTMENTATION + _itoa( *ComIt, strTemp.GetBuffer( 4 ), 10 );
	}
		
	// ������û�ҵ�����Ҫ�ж����ڵĻ��ǲ������
	if( strMaxCircle.IsEmpty() )
	{
		BOOL bFindMaxCircle = TRUE;

		// �˻�����󻷣����½ڵ���Ϣ��ֱ�ӷ���
		if( ( 0 < strCircle.Find( itoStr( iMostCircle[0] ).GetBuffer( 4 ) ) ) && ( 0 < strCircle.Find( itoStr( iMostCircle[1] ).GetBuffer( 4 ) ) )
			&& ( 0 < strCircle.Find( itoStr( iMostCircle[2] ).GetBuffer( 4 ) ) ) && ( 0 < strCircle.Find( itoStr( iMostCircle[3] ).GetBuffer( 4 ) ) ) )
		{
			strMaxCircle = strCircle;
			return TRUE;
		}

	}

	// ����˻�Ϊ��󻷣���ôû��Ҫ��������Ĳ����ˣ�ֱ�ӷ���
	if( strCircle == strMaxCircle )
	{
		return TRUE;
	}

	for( vector< CString >::const_iterator GatherIt = JunPointGather.begin(); GatherIt != JunPointGather.end(); GatherIt++ )
	{
		if( *GatherIt == strCircle)
		{
			return TRUE;
		}
	}
	
	// ����˻��ڵ���Ϣû��JunPointGather�У� �������û��ʱû���ظ���
    JunPointGather.push_back( strCircle );
	
	return FALSE;
}


bool CPFAOptimize::InsertCircleMatrix( const int& iKeyOfCircle, const int& iProperty, ComMap& ComponentKeyMap, PFAOptimitationData& OptData )
{
	ComMap::iterator ConstComIt = ComponentKeyMap.begin();
	int iPosition = 0;
	for( ; ConstComIt != ComponentKeyMap.end(); ConstComIt++ )
	{
		if( !OptData.SetProperty( iKeyOfCircle, iProperty, iPosition, *ConstComIt ) )
		{
			return false;
		}
		iPosition++;
	}
	return true;
}

void CPFAOptimize::JunSystemTransformCircleSystem( ComponentManager& ComManager, PFAOptimitationData& OptData )
{
	//
	ASSERT( NULL != &ComManager );
	vector< CString > JunPointGather;                       // ������Ż��Ľڵ���Ϣ�� �ڵ����Ѿ�����С�������к���
	                                                        // �����������ҳ����
	BOOL bMaxCircle = FALSE;                                // ����Ƿ��ҵ���FALSE��û���ҵ�
	Pipe* pPipe = NULL;
	Component* pPipeComponent = NULL;
	ComMap JunKeyMap;                                       // ���Ľڵ���Ϣ
	ComMap PipeKeyMap;                                      // ���Ĺܵ���Ϣ
	IteratorPtr<Component> PipeItPtr( ComManager.CreatPipeIterator() );
	int iKeyOfCircle = 0;                                  // ���ı��,������Ǵ�1��ʼ��
	int iMostCircle[4] = { 0, 0, 0, 0 };
	CString  strMaxCircle;
	for( PipeItPtr->Fist(); !PipeItPtr->IsDone(); PipeItPtr->Next() )
	{
		pPipeComponent = &PipeItPtr->CurrentItem();
		pPipe = dynamic_cast<Pipe*>( pPipeComponent );	
		
		// ˳ʱ��Ļ���
		JunKeyMap.clear();
		PipeKeyMap.clear();
		ASSERT( FindBaseCircle( ComManager, *pPipe, DEASIL_DIRECTION, JunKeyMap, PipeKeyMap, iMostCircle ) );
        bMaxCircle = JudgeMaxCircle( JunKeyMap, iMostCircle, JunPointGather, strMaxCircle );
		if( bMaxCircle == FALSE )     // ���û���ҵ�  
		{
			iKeyOfCircle++;
			InsertCircleMatrix( iKeyOfCircle, 101, JunKeyMap, OptData );
			InsertCircleMatrix( iKeyOfCircle, 100, PipeKeyMap, OptData );

		}

		// ��ʱ��Ļ���
		JunKeyMap.clear();
		PipeKeyMap.clear();
		ASSERT( FindBaseCircle( ComManager, *pPipe, ANTICLOCKWISE_DIRECTION, JunKeyMap, PipeKeyMap, iMostCircle ) );
        bMaxCircle = JudgeMaxCircle( JunKeyMap, iMostCircle, JunPointGather, strMaxCircle );
        if( bMaxCircle == FALSE )                   // ���û���ҵ�
		{
			iKeyOfCircle++;
			InsertCircleMatrix( iKeyOfCircle, 101, JunKeyMap, OptData );
			InsertCircleMatrix( iKeyOfCircle, 100, PipeKeyMap, OptData );
		}
	}	
}


void CPFAOptimize::DisplayMatrix( const CString& strFileDirectory, const int& iProperty, PFAOptimitationData& OptData )
{
	ofstream fout( strFileDirectory );
	if( !fout )
	{
		return;
	}
	for( int i = 1; i <= OptData.GetPropertyCount( iProperty ); i++ )
	{
		// MatrixDisplay�ﻷ�Ǵ�0��ʼ��ţ���ʾ��ʱ���1��ʼ���
		fout<< "\n====================\n" <<"����ţ�"<< i <<"\n";

		int iPosition = 0;
		int iKeyOfCom = 0;
		int iTempCirKey = 0;
		if( !OptData.GetProperty( i, iProperty, 0, iKeyOfCom ) )          // ��ȡָ����ָ��������ʧ�� 
		{
			return;
		}
		else
		{
			fout<< iKeyOfCom; 
		}
		for( int j = 1; j< OptData.GetPropertyCount( i, iProperty ); j++ )
		{	
			if( !OptData.GetProperty( i, iProperty, j, iKeyOfCom ) )          // ��ȡָ����ָ��������ʧ�� 
			{
				return;
			}
			else
			{
				fout<< "=>" << abs( iKeyOfCom );
			}
		}
		fout<< "\n";
	}
	fout.close();
}


bool CPFAOptimize::CalPipeCloseSubtract( ComponentManager& ComManager, PFAOptimitationData& OptData, map< int, double >& OptimitationParameterMap, map< int, double >& OptimitationAssistantMap )
{
	//
	ASSERT( NULL != &ComManager );
	ASSERT( NULL != &OptData );

	double dTemp = 0.0;
	double dTempDummyFlux = 0.0;
	double dTempFactFlux = 0.0;
	double dTempLength = 0.0;
	Pipe* pPipe = NULL;
	Component* pPipeComponent = NULL; 
	map< int, double >::iterator IntDouMap;
	IteratorPtr<Component> PipeItPtr( ComManager.CreatPipeIterator() );
	for( PipeItPtr->Fist(); !PipeItPtr->IsDone(); PipeItPtr->Next() )
	{
		pPipeComponent = &PipeItPtr->CurrentItem();
		pPipe = dynamic_cast<Pipe*>( pPipeComponent );
		
		// �ܵ������ԣ��ܵ����������ܵ������͹ܵ����ȣ����������һ�����Բ�����
		if( !OptData.GetProperty( pPipe->GetKey(), 1, dTempFactFlux ) || !OptData.GetProperty( pPipe->GetKey(), 2, dTempLength) 
			|| !OptData.GetProperty( pPipe->GetKey(), 0, dTempDummyFlux ) )
		{
			return false;
		}
		
		// ÿ���ܵ��ļ����������ȡ����ֵ��Ϊ�˱���pow���ִ���
		dTemp = pow( ( dTempFactFlux ), 2.0 * OptData.GetAlfaModulus() / ( OptData.GetAlfaModulus() + OptData.GetMModulus() ) )
			* fabs( dTempLength ) 
			* pow( ( dTempDummyFlux ), -1.0 * OptData.GetMModulus() / ( OptData.GetAlfaModulus() + OptData.GetMModulus() ) );
		dTemp = fabs( dTemp );
		IntDouMap = OptimitationParameterMap.find( pPipe->GetKey() );
		if( OptimitationParameterMap.end() == IntDouMap )
		{
			OptimitationParameterMap.insert( map< int, double >::value_type( pPipe->GetKey(), dTemp ) );
		}
		else
		{
			IntDouMap->second = dTemp;
		}
		
		// �������������ָ����ͬ
		dTemp /= dTempDummyFlux;
		IntDouMap = OptimitationAssistantMap.find( pPipe->GetKey() );
		if( OptimitationAssistantMap.end() == IntDouMap )
		{
			OptimitationAssistantMap.insert( map< int, double >::value_type( pPipe->GetKey(), dTemp ) );
		}
		else
		{
			IntDouMap->second = dTemp;
		}
	}
	return true;
}


bool CPFAOptimize::CalEconomyDiameterAndWaterHarmer( ComponentManager& ComManager, const double& dPrecision, const long& lMaxIterative, PFAOptimitationData& OptData )
{
	// 
	ASSERT( NULL != & ComManager );
	ASSERT( 0 < dPrecision );
	ASSERT( 0 < lMaxIterative );

	vector< double > TempVector;
	vector< int >* pPipeVector = NULL;
	vector< int >* pJunVector = NULL;
	map< int, double > OptimitationParameterMap;                 // �ܶεıպϲ�������㻷�ıպϲ�
	map< int, double > OptimitationAssistantMap;                 // ����ƽ���ʱ��
	int i = 0;
	int j = 0;
	double dTemp = 0.0;
	double dTempDummyFlux = 0.0;
	double dTempFactFlux = 0.0;
	double dTempLength = 0.0;
	bool bPrecisionFlag = false;                // ����Ҫ���־��Ϊtrue��ʾȫ��������������Ͼ���Ҫ��
	long lIterativeTime = 0;                    // ���ȵ�������
	Pipe* pPipe = NULL;
    CalPipeCloseSubtract( ComManager, OptData, OptimitationParameterMap, OptimitationAssistantMap );

	// ����ÿ�����Ĳ���������л��������ھ���Ҫ��dPrecision���������������ֱ��ÿ����������С�ھ���Ҫ��dPrecision�����������������
	while( ( false == bPrecisionFlag ) && ( lMaxIterative > lIterativeTime ) )
	{
		bPrecisionFlag = true;                   // ÿ�ε����������õ����ɹ���־Ϊtrue�������ĳ�����Ȳ���������Ϊfalse
		map< int, double >::iterator OptIt;
		vector< int >::iterator PipeIt;
		double dParameterTemp = 0.0;            // ���ıպϲ�
		double dAssistantTemp = 0.0;            // ����������ʱ�õĸ�������


		// ����-����˹�������ѻ����������ǣ��������������Դ˻�����ɵ�Ӱ��
		for( int i = 1; i <= OptData.GetCirPipeMatrixCount(); i++ )
		{
			dParameterTemp = 0.0;
			dAssistantTemp = 0.0;
			pPipeVector = OptData.GetCirPipeMatrix( i );
			pJunVector = OptData.GetCirJunMatrix( i );
			PipeIt = pPipeVector->begin();

			// ����ÿ�����Ĳ���
			for( ; PipeIt != pPipeVector->end(); PipeIt++ )
			{
				pPipe = ComManager.LookUpPipe( abs( *PipeIt ) );
				if( 0 < *PipeIt )
				{
					OptIt = OptimitationParameterMap.find( abs( *PipeIt ) );
					dTemp = OptIt->second;
					dParameterTemp += OptIt->second;
					OptIt = OptimitationAssistantMap.find( abs( *PipeIt ) );
					dAssistantTemp += OptIt->second;
				}
				
				else
				{
					OptIt = OptimitationParameterMap.find( abs( *PipeIt ) );
					dTemp = OptIt->second;
					dParameterTemp -= fabs( OptIt->second );
					OptIt = OptimitationAssistantMap.find( abs( *PipeIt ) );
					dAssistantTemp -= fabs( OptIt->second );
				}
			}

			// ����˻���������Ľ�������Ͼ���Ҫ��,��Ϊ��double������û�ӵȺţ����߼��жϵ�������
			if( dPrecision < fabs( dParameterTemp ) )
			{
				bPrecisionFlag = false;             // Ҫ���µ���

				// ��ֹ��ĸΪ0����������Ի��ǲ���ȫ�棬�Ժ���Ҫ�Ľ�
				ASSERT( 0 < fabs( ( OptData.GetMModulus() * dAssistantTemp - 1e-9 ) ) );

				// �˻���������У������
				dTemp = ( OptData.GetAlfaModulus() + OptData.GetMModulus() ) * dParameterTemp /
					( OptData.GetMModulus() * dAssistantTemp );

				// �����˻������еĹܵ�������,ע������
				// ��������������ǵ�һ����������ֻ�����˱�����Ӱ�죬û�п����ڻ���Ӱ�죬�ھ����ϻ����һ����ʧ��
				// �Ժ�ῼ����PFAOptimitationData�м������ԣ��������������Ϊ����������
				PipeIt = pPipeVector->begin();
				for( ; PipeIt != pPipeVector->end(); PipeIt++ )
				{
				    pPipe = ComManager.LookUpPipe( abs( *PipeIt ) );
					OptData.GetProperty( *PipeIt, 0, dAssistantTemp );
					
					if( 0 > dParameterTemp )
					{
						if( 0 < *PipeIt )
						{
							dAssistantTemp -= dTemp;
						}
						else
						{
							dAssistantTemp += dTemp;
						}
						dAssistantTemp = fabs( dAssistantTemp );
					}
					else
					{
						if( 0 < *PipeIt)
						{
							dAssistantTemp += dTemp;
						}
						else
						{
							dAssistantTemp -= dTemp;
						}
						dAssistantTemp = fabs( dAssistantTemp );
					}

 
					// dAssistantTemp += dTemp;
					OptData.SetProperty( *PipeIt, 0, dAssistantTemp );
				}
				// ���¼���ܵ��ıպϲ�
				
			}
		}
		CalPipeCloseSubtract( ComManager, OptData, OptimitationParameterMap, OptimitationAssistantMap );
        lIterativeTime++;              // ����������һ
	}

	// ���������ƽ��ɹ�
	if( ( false != bPrecisionFlag ) && ( lMaxIterative > lIterativeTime ) )
	{
		// ���㾭�ùܾ���ˮͷ��ʧ
		ASSERT( 0 < OptData.GetEconomyFactor() );
		int iKeyOfPipe = 0;	
		Pipe* pPipe = NULL;
		Component* pPipeComponent = NULL; 
      
		// �������йܵ�
        IteratorPtr<Component> PipeItPtr( ComManager.CreatPipeIterator() );
		for( PipeItPtr->Fist(); !PipeItPtr->IsDone(); PipeItPtr->Next() )
		{
			pPipeComponent = &PipeItPtr->CurrentItem();
	        pPipe = dynamic_cast<Pipe*>( pPipeComponent );
			if( NULL == pPipe )
			{
				return false;       // �Ҳ����ܵ����Ƿ�Ӧ�÷��͸��Զ�����Ϣ�����
			}
			OptData.GetProperty( pPipe->GetKey(), 0, dTempDummyFlux );
			OptData.GetProperty( pPipe->GetKey(), 1, dTempFactFlux );
			OptData.GetProperty( pPipe->GetKey(), 2, dTempLength );
			dTemp = OptData.GetEconomyFactor() * OptData.GetFluxSummation() * dTempDummyFlux 
				* dTempFactFlux*dTempFactFlux;
			
			// ���ùܾ�
			if( 0 > fabs( ( OptData.GetAlfaModulus() + OptData.GetMModulus() ) - 1e-6 ) )
			{
				AfxMessageBox( MODULUS_ZERO );
				return false;
			}
			double dDiameter = pow( fabs( dTemp ), 1.0 / ( OptData.GetAlfaModulus() + OptData.GetMModulus() ) );
			OptData.SetProperty( pPipe->GetKey(), 4, dDiameter );
			
			// ˮͷ��ʧ
			double dWater = OptData.GetKModulus() * pow( fabs( dTempFactFlux ), OptData.GetNModulus() ) * dTempLength 
				/ pow( fabs( dTemp ), OptData.GetMModulus() );
			OptData.SetProperty( pPipe->GetKey(), 5, dWater );
		}
	}
	return bPrecisionFlag;
}


bool CPFAOptimize::InitializePipeCircle( PFAOptimitationData& OptData )
{
	// i:���ţ�j�����йܵ���λ��
	for( int i = 1; i <= OptData.GetPropertyCount( 100 ); i++ )
	{
		int iPosition = 0;
		int iKeyOfPipe = 0;
		int iTempCirKey = 0;
		for( int j = 0; j< OptData.GetPropertyCount( i, 100 ); j++ )
		{
			if( !OptData.GetProperty( i, 100, j, iKeyOfPipe ) )          // ��ȡָ����ָ��������ʧ�� 
			{
				return false;
			}

			// �趨����������������ʾ�ܵ��뻷�ķ����Ƿ��෴
			iTempCirKey = iKeyOfPipe > 0 ? i : -i;

			iPosition = OptData.GetPropertyCount( iKeyOfPipe, 102 );
			if( !OptData.SetProperty( iKeyOfPipe, 102, iPosition, iTempCirKey ) )  // ����ָ����ָ����ֵʧ�� 
			{
				return false;
			}
		}
	}
	return true;
}





bool CPFAOptimize::CalFactFlux( ComponentManager& ComManager, const double& dPrecision, const long& lMaxIterative, PFAOptimitationData& OptData )
{
	// 
	ASSERT( NULL != & ComManager );
	ASSERT( 0 < dPrecision );
	ASSERT( 0 < lMaxIterative );

	vector< double > TempVector;
	vector< int >* pPipeVector = NULL;
	vector< int >* pJunVector = NULL;
	map< int, double > OptimitationParameterMap;                 // �ܶεıպϲ�������㻷�ıպϲ�
	map< int, double > PTempMap;                                 // ����Sq_2����������
	map< int, double > ATempMap;                                 // ����Sq
	map< int, double > ResultMap;                                // У��������int��ʾ��
	double dTemp = 0.0;
	double dTempDiameter = 0.0;
	double dTempFactFlux = 0.0;
	double dTempLength = 0.0;
	bool bPrecisionFlag = false;                // ����Ҫ���־��Ϊtrue��ʾȫ��������������Ͼ���Ҫ��
	long lIterativeTime = 0;                    // ���ȵ�������
	Pipe* pPipe = NULL;
	Component* pPipeComponent = NULL; 
	IteratorPtr<Component> PipeItPtr( ComManager.CreatPipeIterator() );

	map< int, double > CircleCloseSubtract;                // ���ıպϲ�
	map< int, double > CircleMiddleVariable;               // �м���� 
	map< int, vector< double > > FluxModulusMetrix;        // ���������ϵ������
    
	
	int i = 0;
	int j = 0;
	
	// ��ʼ������ϵ������,�����Ǵ�1��ʼ��
	for( i = 0; i <= OptData.GetPropertyCount( 100 ); i++ )
	{
		vector< double > DoubleVector;
		for( j = 0; j <= OptData.GetPropertyCount( 100 ); j++ )
		{
			DoubleVector.push_back( 0.0 );
		}
		FluxModulusMetrix.insert( map< int, vector< double > >::value_type( i+1, DoubleVector ) );
	}

	// ����ÿ���ܵ�
	for( PipeItPtr->Fist(); !PipeItPtr->IsDone(); PipeItPtr->Next() )
	{
		pPipeComponent = &PipeItPtr->CurrentItem();
	    pPipe = dynamic_cast<Pipe*>( pPipeComponent );

		// �ܵ������ԣ��ܵ������͹ܵ����ȣ����������һ�����Բ�����
		if( !OptData.GetProperty( pPipe->GetKey(), 1, dTempFactFlux ) && !OptData.GetProperty( pPipe->GetKey(), 2, dTempLength) 
		    && !OptData.GetProperty( pPipe->GetKey(), 4, dTempDiameter ) )
		{
			return false;
		}

		// ÿ���ܵ��ļ������
		// ���k��m��������ֵ����ֱ�Ӽ���
		if( ( 0 > fabs( OptData.GetKModulus() - 1.0e-13 ) ) && ( 0 > fabs( OptData.GetMModulus() - 1.0e-6 ) ) )
		{
			if( 0 < fabs( dTempDiameter -1e-6 ) )               // ��ĸ����Ϊ0
			{
				dTemp = OptData.GetKModulus() * dTempLength / pow( fabs( dTempDiameter ), 5.3 );  // ��ʽ��
			}
		}
		// Re
		if( 0 > fabs( dTempDiameter - 1e-6) )                   // ��ֹ���湫ʽ��ĸΪ0������ֱ��Ϊ0Ҳû����
		{
			return false;
		}	
		double dSpeed = 4.0 * dTempFactFlux / ( PI * dTempDiameter * dTempDiameter );  // ÿ���ܵ�������
        QuantityManager& qm = QuantityManager::Instance();     
		NumFlyWeight DynamicViscosity = ( ComManager.SysProperty().GetFuild() )->ms_Viscos; // ����Ķ���ճ��
		double dDynamicViscosity = DynamicViscosity.GetfValue();
		if( "kg/sec-m" != DynamicViscosity.GetUnit() )         // ת������׼��λ
		{	
			qm.TransformFromStd( dDynamicViscosity, DynamicViscosity.GetUnit().GetBuffer( 15 ), DynamicViscosity.GetfValue() );
		}
		if( 0 > fabs( dDynamicViscosity - 1e-6) )              // ����ճ�Ȳ���Ϊ0
		{
			return false;
		}
		double dRe = dSpeed * dTempDiameter / dDynamicViscosity;

		// ţ�ٵ�������¶������-κ�ع�ʽ
		if( !ColebrookNewton( 4.572e-5, dTempDiameter, dRe, dTemp ) )       // ţ�ٷ�����ʧ��
		{
			return false;                               
		}
		dTemp = dTemp * 8.0 * dTempLength / ( 9.8 * PI * PI * pow( fabs( dTempDiameter ), 5 ) ); // S�ļ��㣬��ѡ��Ħ��������ʽ�й�
		
		OptimitationParameterMap.insert( map< int, double >::value_type( pPipe->GetKey(), dTemp ) );
	}


	// Ϊʵ������ƽ����׼��
	map< int, vector< double > >::iterator FluxModMetIt = FluxModulusMetrix.begin();
	for( i = 1; i <= OptData.GetPropertyCount( 100 ); i++ )   // ��1�Ż���ʼ
	{
		double dPTemp = 0.0;
		double dATemp = 0.0;
		int iKeyOfPipe = 0;                                   // �ܵ����
		double dSTemp = 0.0;                                  // �����������OptimitationParameterMap�е�ֵ����ˮ��Ħ��  
		vector< double >::iterator DouVecIt = ( FluxModMetIt->second ).begin();
		for( j = 0; j < OptData.GetPropertyCount( i, 100 ); j++ )  // ����ÿ�����Ĺܵ�
		{
			OptData.GetProperty( i, 100, j, iKeyOfPipe);
			OptData.GetProperty( abs( iKeyOfPipe ), 1, dTemp );         // �ܵ�ʵ������
			map< int, double >::iterator IntDoubleIt = OptimitationParameterMap.find( abs( iKeyOfPipe ) );
			dSTemp = IntDoubleIt->second;
			dPTemp = dPTemp + ( iKeyOfPipe > 0 ? 1 : -1) * dSTemp * dTemp * dTemp; 
			dATemp = dATemp + dSTemp * dTemp;
		}
		PTempMap.insert( map< int, double >::value_type( i, dPTemp ) );
		ATempMap.insert( map< int, double >::value_type( i, dATemp ) );
	}

	// ����ÿ�����Ĳ���������л��������ھ���Ҫ��dPrecision�������ʵ��������ֱ��ÿ����������С�ھ���Ҫ��dPrecision�����������������
	while( ( false == bPrecisionFlag ) && ( lMaxIterative > lIterativeTime ) )
	{
		bPrecisionFlag = true;                   // ÿ�ε����������õ����ɹ���־Ϊtrue�������ĳ�����Ȳ���������Ϊfalse
		double dParameterTemp = 0.0;            
		map< int, vector< double > >::iterator FluxModMetIt = FluxModulusMetrix.begin();
		vector< double >::iterator DouVecIt;
		map< int, double >::iterator IntDouIt;
		for( i = 1; i <= OptData.GetPropertyCount( 100 ); i++ )   // ��1�Ż���ʼ
		{
			dParameterTemp = 0.0;
			DouVecIt = ( FluxModMetIt->second ).begin(); 
			
			double dModulus = 0.0;
			*DouVecIt = 1.0;	
			for( j = 0; j < OptData.GetPropertyCount( i, 100 ); j++ )   // ����ÿ�����Ĺܵ�
			{
				DouVecIt = ( FluxModMetIt->second ).begin();
	            int iKeyOfPipe = 0;
				int iCloseCircle = 0;
				int n = 0;
				OptData.GetProperty( i, 100, j, iKeyOfPipe );
				while( OptData.GetProperty( iKeyOfPipe, 102, n, iCloseCircle ) )
				{
					if( abs( iCloseCircle ) == i )            // ����Ǳ���������
					{
						n++;
						continue;
					}			
					double dATemp = 0.0;                               
					double dSTemp = 0.0;     
					IntDouIt = OptimitationParameterMap.find( abs( iKeyOfPipe ) );
					dSTemp = IntDouIt->second;                               // S
					OptData.GetProperty( abs( iKeyOfPipe ), 1, dTemp );      // ʵ������
					IntDouIt = ATempMap.find( i );
					dATemp = IntDouIt->second;                               // ����Sq��
					if( 0 > fabs( dATemp - 1e-6) )                           // ��ֹ������ʽ�ķ�ĸΪ0
					{
						return false;
					}
					dModulus = -1 * dSTemp * fabs( dTemp ) / dATemp;

					// ��ϵ��д�����
					for( int m = 1; m < iCloseCircle; m++ )                   
					{
						DouVecIt++;
					}
					if( ( FluxModMetIt->second ).end() == DouVecIt )           // ��ֹԽ��д����ֵ
					{
						return false;
					}
					*DouVecIt = dModulus;
					n++;
				}
			}

			// �ѳ�������Ҳ��������У�����ʽ���ұߣ�AX=B�е�B
			IntDouIt = PTempMap.find( i );
			dTemp = -1 * IntDouIt->second ;
			IntDouIt = ATempMap.find( i );
			if( 0 > fabs( IntDouIt->second - 1e-6 ) )            // ��ֹ��ĸΪ0
			{
				return false;
			}
			dModulus = dTemp / ( 2 * IntDouIt->second );
			DouVecIt = ( FluxModMetIt->second ).begin(); 
			for(int k = 0; k <= OptData.GetPropertyCount( 100 ); k++ ) // �ƶ���ÿ�����һ��λ�ã����ƶ� ����+1 ��λ��
			{
				DouVecIt++;
			}
			*DouVecIt = dModulus;

			FluxModMetIt++;                                  // �ƶ�����һ��
		}

		// ��FluxModulusMetrix���Է����飬�����������ResultMap
		//////////////////////////

		// �������л���
		IntDouIt = ResultMap.begin();
		for( ; ResultMap.end() != IntDouIt; IntDouIt++ )
		{
			dTemp = IntDouIt->second;
		    if( dPrecision < fabs( dTemp ) )   // ����л����������У�����������Ͼ���Ҫ��
			{
		    	bPrecisionFlag = false;             // Ҫ���µ���

			    // �����˻������еĹܵ�ʵ������,ע������
				int iKeyOfPipe = 0;
				for( i = 1; i <= OptData.GetPropertyCount( 100 ); i++ )
				{
					for( j = 0; j < OptData.GetPropertyCount( i, 100); j++ )
					{
						OptData.GetProperty( i, 100, j, iKeyOfPipe );             // ȡ�û��еĹܵ����
						OptData.GetProperty( iKeyOfPipe, 1, dParameterTemp );     // ȡ�Ĺܵ���Ӧ��ʵ������
						dParameterTemp += dTemp;                                  // ��������
						OptData.SetProperty( iKeyOfPipe, 1, dParameterTemp );
					}
				}
			}
		}
		lIterativeTime++;              // ����������һ
	}
	return bPrecisionFlag;
}

// ���ݾ��ùܾ�Ѱ�ұ�׼�ܾ�������Ӧ���ǰ��մ������������ҵģ����ڼ��£���50mmΪһ������
bool CPFAOptimize::FindStandardDiameter( PFAOptimitationData& OptData )
{
	bool bFlag = true;
	double dEconomyDiameter = 0.0;                // ���ùܾ�
	double dStandardDiameter = 0.0;               // Ҫȡ�õı�׼�ܾ�
	int iKeyOfPipe = 1;                           // �ܵ����
	int i = 0;
	while( i < OptData.GetPropertyCount( 2 ) )
	{
		// �ܵ�����п��ܲ���������
		if( !OptData.GetProperty( iKeyOfPipe, 2 , dEconomyDiameter ) )
		{
			iKeyOfPipe++;
			if( iKeyOfPipe > 500000 ) // ��ֹ������ѭ�����ܵ�����������500000
			{
				return false;
			}
		}

		int iBottonDiameter = ( int )( dEconomyDiameter / 0.05 );

		// �����( iBottonDiameter + 1 ) * 0.05 �ı�׼�ܾ��ȽϽ�
		if( ( dEconomyDiameter - iBottonDiameter * 0.05 ) > ( ( iBottonDiameter + 1 ) * 0.05 - dEconomyDiameter ) )
		{
			dStandardDiameter = ( iBottonDiameter + 1 ) * 0.05;
		}
		else         // �����iBottonDiameter * 0.05�ı�׼�ܾ��ȽϽ�
		{
			if( 0 != iBottonDiameter )
			{
                dStandardDiameter = iBottonDiameter * 0.05;
			}
			else     // ������Ϊ�ܵ����ùܾ�̫С������Ϊ0
			{
				dStandardDiameter = ( iBottonDiameter + 1 ) * 0.05;
			}
			
		}
		if( !OptData.SetProperty( iKeyOfPipe, 2, dStandardDiameter ) )  // �ѱ�׼�ܾ�д��ȥ
		{
			return false;                                               // д��ʧ���򷵻�
		} 
		i++;
	}
	return true;
}


bool CPFAOptimize::CalOthersVariable( ComponentManager& ComManager, PFAOptimitationData& OptData )
{
	int i = 0;
	int iKeyOfPipe = 0;
	double dTemp = 0.0;
	double dTempFactFlux = 0.0;
	double dTempLength = 0.0;
	double dTempDiameter = 0.0;
	double dTempWaterHammer = 0.0;
	double dTempJunWater = 0.0;               // �ڵ�ˮͷ
	double dA = 0.0;
	double dB = 0.0;
	double dAlfa = 0.0;
	double dDisinvestmentTime = 0.0;
	double dRepairModulus = 0.0;
	double dWorkExpenditure = 0.0;
	double dKModulus = 0.0; 
	double dMModulus = 0.0;
	double dNModulus = 0.0; 
	double dFluxSummation = 0.0;
	double dYConvertExpenditure = 0.0;          // ���������
	vector< int > JunToJunPipePath;
	dA = OptData.GetAModulus();
	dB = OptData.GetBModulus();
	dAlfa = OptData.GetAlfaModulus();
	dKModulus = OptData.GetKModulus();
	dMModulus = OptData.GetMModulus();
	dNModulus = OptData.GetNModulus();

	// ����ƽ����ˮͷ��ʧ 
	dTemp = 0.0;
	for( i = 0; i < OptData.GetPropertyCount( 102 ); i++ )
	{
		OptData.GetProperty( i, 102, iKeyOfPipe );
		OptData.GetProperty( iKeyOfPipe, 1, dTempFactFlux );
		OptData.GetProperty( iKeyOfPipe, 2, dTempLength );
		OptData.GetProperty( iKeyOfPipe, 4, dTempDiameter );
		dTempWaterHammer = dKModulus * pow( fabs( dTempFactFlux ), dNModulus ) * dTempLength / pow( fabs( dTempDiameter ), dMModulus );
	    OptData.SetProperty( iKeyOfPipe, 5, dTempWaterHammer );

		// Ϊ���㽨�������׼��
		dTemp = dTemp + ( dA + dB * pow( fabs( dTempDiameter ), dAlfa ) ) * dTempLength;
	}

	// ���㽨�����
	dRepairModulus = OptData.GetRepairModulus();
	dDisinvestmentTime = OptData.GetDisinvestmentTime();
	dYConvertExpenditure = ( dRepairModulus / 100 + 1 / dDisinvestmentTime ) * dTemp;
	OptData.SetConstructExpenditure( dYConvertExpenditure );

	// ����ڵ�ˮͷ
	Jun* pJun = NULL;
	Component *pComponent = NULL;
	int iKeyOfControlJun = 0;
	int iCountControlJun = OptData.GetPropertyCount( 201 );
	if( 0 == iCountControlJun )                                         // ���Ƶ�������Ϊ0
	{
		return false;
	}
	OptData.GetProperty( 0, 201, iKeyOfControlJun );                    // ѡȡ���Ƶ㼯���еĵ�һ��
	double dControlJunWater = 0.0;
    OptData.GetProperty( iKeyOfControlJun, 6, dControlJunWater );       // ��ȡ���Ƶ�ˮͷ
	vector< int >::iterator IntVecIt;
	IteratorPtr< Component > JunitPtr( ComManager.CreatJunIterator() );
	for( JunitPtr->Fist(); !JunitPtr->IsDone(); JunitPtr->Next() )      // �������нڵ�
	{
		pComponent = &( JunitPtr->CurrentItem() );
		pJun = dynamic_cast< Jun* > (pComponent);
		JunToJunPipePath.clear();
		FindShortCut( ComManager, pJun->GetKey(), iKeyOfControlJun, JunToJunPipePath ); 
		IntVecIt = JunToJunPipePath.begin();
		dTemp = 0.0;
		for( ; JunToJunPipePath.end() != IntVecIt; IntVecIt++ )
		{
			i = *IntVecIt > 0 ? 1 : -1;
			OptData.GetProperty( abs( *IntVecIt), 5, dTempWaterHammer );
			dTemp = dTemp + i * dTempWaterHammer;                        // ����ڵ㵽���Ƶ���ܵ�ˮͷ��ʧ
		}
		dTemp += dTempJunWater;                                          // �ڵ��ˮͷ
		OptData.SetProperty( pJun->GetKey(), 6, dTemp );
	}

	// ��������Ӫ����
	dWorkExpenditure = OptData.GetWorkExpenditure();
	dFluxSummation = OptData.GetFluxSummation();
	int iCountSupplyJun = OptData.GetPropertyCount( 200 );
	if( ( 0 == iCountSupplyJun ) || ( 0 == iCountControlJun ) )          // ��ˮԴ����Ƶ�û����
	{
		return false;
	}
	if( 0 > fabs( dWorkExpenditure - 1e-6 ) )                            // ����������������
	{
		OptData.SetYConvertExpenditure( dYConvertExpenditure );
		return true;
	}
	iKeyOfControlJun = 0;
	int iKeyOfSupplyJun = 0;
	OptData.GetProperty( 0, 201, iKeyOfControlJun );                      // ѡȡ��һ�����Ƶ�Ϊ������Ҫ�ĵ�
	dTemp = 0.0;
	for( i = 0; i < iCountSupplyJun; i++ )
	{
		OptData.GetProperty( i, 200, iKeyOfSupplyJun );                   //  ��ȡ��i����ˮԴ�ڵ���

		// �ҵ�����ˮԴ�����Ƶ�����·����������JunToJunPipePath��
		JunToJunPipePath.clear();
		FindShortCut( ComManager, iKeyOfSupplyJun, iKeyOfControlJun, JunToJunPipePath ); 

		IntVecIt = JunToJunPipePath.begin();
		for( ; JunToJunPipePath.end() != IntVecIt; IntVecIt++ )
		{
			OptData.GetProperty( abs( *IntVecIt ), 5, dTempWaterHammer );
			dTemp += dTempWaterHammer;                                     // ������ˮԴ�����Ƶ����ˮͷ��ʧ
		}
		OptData.GetProperty( iKeyOfControlJun, 6, dTempJunWater );         // ��ȡ���Ƶ�ˮͷ
		dTemp +=  dTempJunWater;                                           // ��ˮԴ��ˮͷ
	}
	dTemp = dTemp * dWorkExpenditure * dFluxSummation;                     // ����Ӫ����

	// ���������
	dYConvertExpenditure += dTemp;                                         // ��������� = ������� + ����Ӫ����
	OptData.SetYConvertExpenditure( dYConvertExpenditure );
	
	return true;
}


// ���·��,Dijkstra�㷨�����ϳ��ģ� �����е���
bool CPFAOptimize::FindShortCut( ComponentManager& ComManager, const int& iKeyOfStartJun, const int& iKeyOfEndJun, vector< int >& JunToJunPipePath )
{
	map< int, vector< int > > AbutMatrix;           //ͼ���ڽӾ�
	vector< int > MarkVector;                       //�������
	vector< int > DistanceVector;                   //��������
	vector< int > TempVector;                       //ǰ׺�ڵ�
	vector< int > PipePathVector;                   //��ʱ·���������
	int iCountOfJun = ComManager.GetJunNum();
	int iCountOfPipe = ComManager.GetPipeNum();
	int iTemp = 0;
	int i = 0;
	int j = 0;
	int k = 0;
	int iMinDistance = 0;

	//��������
	Component *pComponent = NULL;
	Pipe *pPipe = NULL;
	int iStartJun = 0;
	int iEndJun = 0;
	IteratorPtr<Component> PipeItPtr( ComManager.CreatPipeIterator() );
	for( PipeItPtr->Fist(); !PipeItPtr->IsDone(); PipeItPtr->Next() )
    {
		pComponent = &PipeItPtr->CurrentItem();
	    pPipe = dynamic_cast<Pipe*>(pComponent);
		iStartJun = pPipe->StartJun();
		iEndJun = pPipe->EndJun();
		SetProperties( AbutMatrix, iStartJun, iEndJun, 1 );
		SetProperties( AbutMatrix, iEndJun, iStartJun, 1);
	}
	
    //����ֵ	
	SetProperties( MarkVector, iKeyOfStartJun, 1 );
	SetProperties( TempVector, iKeyOfStartJun, 0 );
	for( i = 1; i <= iCountOfJun; i++ )
	{
		iTemp = GetProperties( AbutMatrix, 1, i );
		SetProperties( DistanceVector, i, iTemp );
		if( 0 < iTemp )
		{
			SetProperties( TempVector, i, 1 );
		}
	}

    //Dijkstra
	for( i = 0; i <= iCountOfJun; i++ )
	{
		//�ҵ�û�б�ŵ���Сdist�±�
		iMinDistance = 32000;
		k = 0;
		for( j = 1; j <= iCountOfJun; j++ )
		{
			if( ( 0 == GetProperties( MarkVector, j ) ) && ( 0 < GetProperties( DistanceVector, j ) )
				&& ( iMinDistance > GetProperties( DistanceVector, j ) ) )
			{
				k = j;
				iMinDistance = GetProperties( DistanceVector, j );
			}
		}
		if( 0 == k )                                           //����Ҳ�����ֱ���˳�
		{
			break;
		}
		SetProperties( MarkVector, k, 1 );                      //���

        //�޸����ֵ��·��
		for( j = 1; j <= iCountOfJun; j++ )
		{
			if( ( 0 == GetProperties( MarkVector, j ) ) && ( 0 < GetProperties( AbutMatrix, k, j ) )
				&& ( ( 0 == GetProperties( DistanceVector, j ) ) 
				|| ( GetProperties( DistanceVector, k ) + GetProperties( AbutMatrix, k, j ) < GetProperties( DistanceVector, j ) ) ) )
			{
				iTemp = GetProperties( DistanceVector, k ) + GetProperties( AbutMatrix, k, j );
				SetProperties( DistanceVector, j, iTemp );
				SetProperties( TempVector, j, k );
			}
		}
	}
	
    //���ֵ��·��
	k = iKeyOfEndJun;
	i = 0;
	while( 0 < GetProperties( TempVector, k ) )
	{
		SetProperties( PipePathVector, i++, k );
		k = GetProperties( PipePathVector, k );
	}
	SetProperties( PipePathVector, i, 1 );

	// ���ݽڵ�ѹܵ����д������ű�ʾ�ܵ�������ǰ�������෴
	JunToJunPipePath.clear();
	vector< int >::iterator IntVecIt = PipePathVector.begin();
	iStartJun = *IntVecIt;
	IntVecIt++;
	for( ; PipePathVector.end() != IntVecIt; IntVecIt++ )
	{
		iEndJun = *IntVecIt;
		for( PipeItPtr->Fist(); !PipeItPtr->IsDone(); PipeItPtr->Next() )
		{
			pComponent = &PipeItPtr->CurrentItem();
	        pPipe = dynamic_cast<Pipe*>(pComponent);
			if( ( pPipe->StartJun() == iStartJun ) && ( pPipe->EndJun() == iEndJun ) )
			{
				JunToJunPipePath.push_back( pPipe->GetKey() );
				break;
			}
			if( ( pPipe->StartJun() == iEndJun ) && ( pPipe->EndJun() == iStartJun ) )
			{
				JunToJunPipePath.push_back( -1 * pPipe->GetKey() );
				break;
			}
		}
		iStartJun = iEndJun;
	}
	return true;
}

bool CPFAOptimize::SetProperties( vector< int >& IntVector, const int& iPosition, const int& iValue )
{
	vector< int >::iterator IntVecIt = IntVector.begin();
	vector< int >::iterator IntVecNextIt = IntVecIt;
	IntVecNextIt++;
	for( int i = 1; i < iPosition; i++ )             // iPosition�Ǵ�1��ʼ��ŵģ����Ǵ�0��ʼ
	{	
		if( IntVector.end() == IntVecNextIt )
		{
			IntVector.push_back( 0 );
			IntVecNextIt = IntVecIt;
			IntVecNextIt++;
		}
		IntVecIt++;
		IntVecNextIt++;
	}
	*IntVecIt = iValue;
	return true;
}

int CPFAOptimize::GetProperties( const vector< int >& IntVector, const int& iPosition )
{
	vector< int >::const_iterator IntVecIt = IntVector.begin();
	for( int i = 1; i < iPosition; i++ ) 
	{
		if ( IntVector.end() == IntVecIt )
		{
			return 0;
		}
		IntVecIt++;
	}
	return *IntVecIt;
}

bool CPFAOptimize::SetProperties( map< int, vector< int > >& IntVecMap, const int& iRow, const int& iLine, const int& iValue )
{
	map< int, vector< int > >::iterator IntVecMapIt = IntVecMap.find( iRow );
	if( IntVecMap.end() == IntVecMapIt )
	{
		vector< int > TempVector;
		for( int i = 1; i < iLine; i++ )
		{
			TempVector.push_back( 0 );
		}
		IntVecMap.insert( map< int, vector< int > >::value_type( iRow, TempVector ) );
		return true;
	}
	return SetProperties( IntVecMapIt->second, iLine, iValue );
}

int CPFAOptimize::GetProperties( const map< int, vector< int > >& IntVecMap, const int& iRow, const int& iLine )
{
	map< int, vector< int > >::const_iterator IntVecMapIt = IntVecMap.find( iRow );
	if( IntVecMap.end() == IntVecMapIt )
	{
		return 0;
	}
	return GetProperties( IntVecMapIt->second, iLine );
}



// ţ�ٵ�������¶������-κ�ع�ʽ��ע��û����ϸ���ۣ����ܳ��ֲ����������
bool CPFAOptimize::ColebrookNewton( const double& dAbsoluteRoughness, const double& dDiameter, const double& dRe, double& dResult )
{
	int iIterativeTime = 0;                                    // ��������
	double dXFirst = 1.0;                                      // ��ʼֵ����Ϊ1.0
	double dTemp = 0.0;
	double dX = 0.0;
	while( 5000 > iIterativeTime )                             // �����������ܳ���5000
	{
		double dTemp = dAbsoluteRoughness / ( 3.76 * dDiameter ) + 2.51 / ( dRe * dXFirst );
		double dFirst = pow( fabs( -2 * log( fabs( dTemp ) ) ), -2 );
		double dSecond = -2 * pow( -2 * log10( dTemp ), -3 ) 
			* ( -2 ) * log( 10 ) / dTemp
			* 2.51 * ( -0.5 ) * pow( dXFirst, -1.5 ) / dRe;    // ƫ����
		if( 0 > fabs( dSecond - 1e-6 ) )                       // ��ĸ����Ϊ0
		{
			return false;
		}
		dX = dXFirst - dFirst / dSecond;
		if( 0.0001 > fabs( dX - dXFirst ) )                     // ���㾫��Ҫ��0.0001
		{
			dResult = dX;
			return true;
		}
		dXFirst = dX;
		iIterativeTime++;
	}
	return false;                                               // ������������
}


bool CPFAOptimize::DiameterIsEqual( PFAOptimitationData& OptData, map< int, double >& BeforeDiameterMap )
{
	double dTempDiameter = 0.0;
	int iKeyOfPipe = 0;
	bool bFlag = true;
	if( 0 == BeforeDiameterMap.size() )                      // ��һ��
	{
		for( int i = 0; i < OptData.GetPropertyCount( 102 ); i++ )  // �������йܵ�
		{
			OptData.GetProperty( i, 102, iKeyOfPipe );
			OptData.GetProperty( iKeyOfPipe, 4, dTempDiameter );
			BeforeDiameterMap.insert( map< int, double >::value_type( iKeyOfPipe, dTempDiameter ) );
		}
		bFlag = true;
	}
	else                                                    // �ǵ�һ��
	{
		map< int, double >::iterator IntDouMapIt;
		for( int i = 0; i < OptData.GetPropertyCount( 102 ); i++ )
		{
			OptData.GetProperty( i, 102, iKeyOfPipe );
			OptData.GetProperty( iKeyOfPipe, 4, dTempDiameter );
			IntDouMapIt = BeforeDiameterMap.find( iKeyOfPipe );
			if( 0 < fabs( IntDouMapIt->second - dTempDiameter) )    // ��������ı�׼�ܾ����ϴμ���Ĳ�ͬ
			{
				IntDouMapIt->second = dTempDiameter;                // ����μ�������ı�׼�ܾ�����BeforeDiameterMap
				return false;
			}
		}
	}
	return bFlag;
}

void CPFAOptimize::Example()
{
	
	CMainFrame* pMainFrame = NULL; 
	pMainFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CChildFrame* pChildFrame = NULL;
	pChildFrame = (CChildFrame*)pMainFrame->GetActiveFrame();
	CAutoPFAView* pAutoView = NULL;
	pAutoView = (CAutoPFAView*)pChildFrame->GetActiveView();
	ComponentManager* pComManager = pAutoView->GetDocument()->m_scenarioManager.GetCurScenario()->GetCompManager();
	JunSystemTransformCircleSystem( *pComManager, OptData );
	DisplayMatrix( "F://CirPipe.txt", 100, OptData );
	InitializePipeCircle( OptData );
	DisplayMatrix( "F://Pipe.txt", 102, OptData );

	// ��pComManager�г�ʼ��OptData�� ��ʼʵ���������ܵ����ȣ��ڵ���������ˮԴ�����Ƶ㣬
	// ���ֶ�������ˮԴ�Ϳ��Ƶ�
	int iTemp = 1;
	OptData.SetProperty( 0, 200, iTemp );          // �ڵ�1Ϊ��ˮԴ
	iTemp = 6;
	OptData.SetProperty( 0, 201, iTemp );         // �ڵ�10Ϊ���Ƶ�

	CMinimumSquareSum MinSquSum;

	//MinSquSum.InitializeFactFlux( *pComManager, OptData );   //  ��ʼʵ������
	///////////////////////////////////////
	int i = 0;
	int iKeyOfPipe = 0;
	double Temp = 0.0;
    Temp = 0.025;	
	OptData.SetProperty( 3, 1, Temp );
	OptData.SetProperty( 7, 1, Temp );
	OptData.SetProperty( 2, 1, Temp );
	OptData.SetProperty( 5, 1, Temp );
	OptData.SetProperty( 6, 1, Temp );
	OptData.SetProperty( 1, 1, Temp );
	////////////////////////////////////////

	double dTemp = 0.0;
	Pipe* pPipe = NULL;
	Component* pComponent = NULL; 
	map< int, double > BeforeDiameterMap;                     // �洢����һ�μ����ֱ��
	int iIteratorTime = 0;                                    // ��������
	IteratorPtr<Component> PipeItPtr( pComManager->CreatPipeIterator() );
	for( PipeItPtr->Fist(); !PipeItPtr->IsDone(); PipeItPtr->Next() )
	{
		pComponent = &PipeItPtr->CurrentItem();
	    pPipe = dynamic_cast<Pipe*>( pComponent );
		dTemp = pPipe->Len();
		OptData.SetProperty( pPipe->GetKey(), 2, dTemp );    
		dTemp = pPipe->InDia();
		OptData.SetProperty( pPipe->GetKey(), 4, dTemp );
	}

	// �ڵ�����
	QuantityManager& qm = QuantityManager::Instance();
	CString strUnit = "";
	CString strValue = "";
	Jun* pJun = NULL;
	IteratorPtr<Component> JunItPtr( pComManager->CreatJunIterator() );
	for( JunItPtr->Fist(); !JunItPtr->IsDone(); JunItPtr->Next() )
	{
		pComponent = &JunItPtr->CurrentItem();
	    pJun = dynamic_cast<Jun*>( pComponent );	
		strUnit = pJun->ms_InitGuess.GetValue( 2 );                            // ��õ�λ
		strValue = pJun->ms_InitGuess.GetValue( 1 );
		TCHAR* pChar = NULL;
		qm.TransformToStd( dTemp, strUnit.GetBuffer( 32 ), _tcstod( strValue.GetBuffer( 32 ), &pChar ) ); // ת���ɱ�׼��λ
		if( IDS_STRVOLUMEFLOW != _ttoi( pJun->ms_InitGuess.GetValue( 0 ).GetBuffer( 32 ) ) )            // ����������Ҫת��Ϊ�������
		{
			double dTempDensity = 0.0;
			NumFlyWeight *pDensity = &( ( pComManager->SysProperty().GetFuild() )->ms_Density );
			dTemp *= pDensity->GetNum();                                       // GetNum���ر�׼��λ��
		}
		OptData.SetProperty( pJun->GetKey(), 3, dTemp );
	}

	////////////
	dTemp = 0.05;
	OptData.SetProperty( 1, 3, dTemp );
	dTemp = -0.05;
	OptData.SetProperty( 6, 3, dTemp );
	////////////


    // ��ʼ�����ò���
	OptData.SetAModulus( 8.4 );
	OptData.SetBModulus( 107 );
	OptData.SetAlfaModulus( 1.6 );
	OptData.SetDisinvestmentTime( 3.0 );
	OptData.SetRepairModulus( 3.3 );
	OptData.SetEletricityPrice( 0.5 );
	OptData.SetAsymmetryModulus( 1.0 );
	OptData.SetPumpEfficiency( 0.7 );
	OptData.SetKModulus( 1.34e-10 );
	OptData.SetMModulus( 5.3 );
	OptData.SetNModulus( 2 );
	OptData.Initialization();
	
	BeforeDiameterMap.clear();
	iIteratorTime = 0;
	do
	{
	    // ��ʼ��������
	    MinSquSum.InitializeDummyFlux( *pComManager, OptData );

	    // ������ƽ��
	    CalEconomyDiameterAndWaterHarmer( *pComManager, 0.0001, 5000, OptData );

	    // ͨ�����ùܾ������׼�ܾ�
	    FindStandardDiameter( OptData );

        // ʵ������ƽ��
	    CalFactFlux( *pComManager, 0.0001, 5000, OptData );

	   // ����������һ
		iIteratorTime++;
		
	}
	while( !DiameterIsEqual( OptData, BeforeDiameterMap ) && ( 5000 > iIteratorTime ) ); // �Ƚ�ǰ��ܾ�������������� ��ʼ��������

	// ��������Ҫ��
    CalOthersVariable( *pComManager, OptData );

	// ������
}


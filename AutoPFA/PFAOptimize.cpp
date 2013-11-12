// PFAOptimize.cpp: implementation of the CPFAOptimize class.
//
//////////////////////////////////////////////////////////////////////

//#pragma once
#include "stdafx.h"
#include "PFAOptimize.h"
#include "AutoPFA.h"
#include "MainFrm.h"
#include "ChildFrm.h"
#include "AutoPFAView.h"
#include "Scenario.h"
#include "Fuild.h"
#include "QuantityManager.h"
#include "MinimumSquareSum.h"
#include "OutDataAttr.h"
#include "OutPutDataView.h"
#include "AutoPFADoc.h"



const CString COMPARTMENTATION = "#";
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
	m_DlgOptProGress.Create( IDD_DLGOPTPROGRESS );
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
		pComJunCenter = &( pair<int, CPoint> )(*JunCenterIt);
		
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
		pSource = &(*SourceIt);
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
	ComMap::const_iterator JunKeyNextIterator/* = NULL*/;
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
	for ( iPipePosition = 0, iPipeKey = 0; iPipePosition < iCountCircleJun; iPipePosition++ )
	{
		map< int, int >::iterator PipeIterator = PipeOrder.find( iPipePosition );
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
#ifdef UNICODE
		strCircle = strCircle + COMPARTMENTATION + _itow( *ComIt, strTemp.GetBuffer( 4 ), 10 );
#else
		strCircle = strCircle + COMPARTMENTATION + _itoa( *ComIt, strTemp.GetBuffer( 4 ), 10 );
#endif
	}
		
	// ������û�ҵ�����Ҫ�ж����ڵĻ��ǲ������
	if( strMaxCircle.IsEmpty() )
	{
		BOOL bFindMaxCircle = TRUE;

		// �˻�����󻷣����½ڵ���Ϣ��ֱ�ӷ���
		CString strTop;
		strTop.Format( _T("%d"), iMostCircle[0]);
		CString strBotton;
		strBotton.Format( _T("%d"), iMostCircle[1]);
		CString strLeft;
		strLeft.Format( _T("%d"), iMostCircle[2]);
		CString strRight;
		strRight.Format( _T("%d"), iMostCircle[3]);
		if( ( 0 < strCircle.Find( strTop.GetBuffer( 4 ) ) ) && ( 0 < strCircle.Find( strBotton.GetBuffer( 4 ) ) )
			&& ( 0 < strCircle.Find( strLeft.GetBuffer( 4 ) ) ) && ( 0 < strCircle.Find( strRight.GetBuffer( 4 ) ) ) )
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
		FindBaseCircle( ComManager, *pPipe, DEASIL_DIRECTION, JunKeyMap, PipeKeyMap, iMostCircle );
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
		FindBaseCircle( ComManager, *pPipe, ANTICLOCKWISE_DIRECTION, JunKeyMap, PipeKeyMap, iMostCircle );
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
		fout<< _T("\n====================\n") <<_T("����ţ�")<< i <<_T("\n");

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
				fout<< _T("=>") << abs( iKeyOfCom );
			}
		}
		fout<< _T("\n");
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


// �������������أ���ˮѹ����������õȣ����������ο�
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
	vector< int > NumToPipeVector;                   
	int iCountOfJun = ComManager.GetJunNum();
	int iCountOfPipe = ComManager.GetPipeNum();
	int iTemp = 0;
	int i = 0;
	int j = 0;
	int k = 0;
	int iMinDistance = 0;
	int iMax = 32000;

	//��������
	Component *pComponent = NULL;
	Pipe *pPipe = NULL;
	Jun* pJun = NULL;
	int iStartJun = 0;
	int iEndJun = 0;
	int iTempNumOfStart = -1;                // ��������˳��

	// ��ʼ���ڽӾ���
	AbutMatrix.clear();
	for( i = 0; i < iCountOfJun; i++ )
	{
		vector< int > TempVec;
		TempVec.clear();
		for( j = 0; j < iCountOfJun; j++ )
		{
			TempVec.push_back( iMax );
		}
		AbutMatrix.insert( map< int, vector< int > >::value_type( i, TempVec ) );
	}

	NumToPipeVector.clear();
	IteratorPtr<Component> PipeItPtr( ComManager.CreatPipeIterator() );
	
	// �ܵ���Ӧ��
	NumToPipeVector.push_back( iKeyOfEndJun );        // ���յ���Ϊ�㷨�����
	j = 1;                              // ��Ϊ֮ǰ�Ѿ����յ�ѹ��ȥ�� 
	for( PipeItPtr->Fist(); !PipeItPtr->IsDone(); PipeItPtr->Next() )
    {
		pComponent = &PipeItPtr->CurrentItem();
	    pPipe = dynamic_cast<Pipe*>(pComponent);
		if( pPipe->GetKey() == iKeyOfEndJun )  // ǰ���Ѿ���iKeyOfEndJunѹ��ȥ��
		{
			continue;
		}

		// ���������б��
		if( pPipe->GetKey() == iKeyOfStartJun )  
		{
			iTempNumOfStart = j;
		}
		j++;

		NumToPipeVector.push_back( pPipe->GetKey() );
	}


	for( PipeItPtr->Fist(); !PipeItPtr->IsDone(); PipeItPtr->Next() )
    {
		pComponent = &PipeItPtr->CurrentItem();
	    pPipe = dynamic_cast<Pipe*>(pComponent);
		vector< int >::iterator IntVecIt = NumToPipeVector.begin();
		iStartJun = pPipe->StartJun();
		iEndJun = pPipe->EndJun();
		for( i = 0, j = 0; NumToPipeVector.end() != IntVecIt; IntVecIt++, i++ )
		{
			if( iStartJun == *IntVecIt)
			{
				iStartJun = i;
				j++;
			}
			if( iEndJun == *IntVecIt )
			{
				iEndJun = i;
				j++;
			}
			if( 2 <= j )                   // ��Լʱ��
			{
				break;
			}
		}
		

		SetProperties( AbutMatrix, iStartJun, iEndJun, 1 );
		SetProperties( AbutMatrix, iEndJun, iStartJun, 1);

	
	}
	
    //����ֵ	
	for( i = 1; i <= iCountOfJun; i++ )
	{
		MarkVector.push_back( 0 );
		TempVector.push_back( 0 );
	}
	SetProperties( MarkVector, 0, 1 );
	SetProperties( TempVector, 0, -1 );
	for( i = 0; i < iCountOfJun; i++ )
	{
		iTemp = GetProperties( AbutMatrix, 0, i );
		SetProperties( DistanceVector, i, iTemp );
		if( ( iMax > iTemp ) && ( i != 0 ) )
		{
			SetProperties( TempVector, i, 0 );
		}
		else
		{
			SetProperties( TempVector, i, -1 );
		}
	}

    //Dijkstra
	for( i = 1; i < iCountOfJun; i++ )
	{
		//�ҵ�û�б�ŵ���Сdist�±�
		iMinDistance = iMax;
		k = -1;
		for( j = 0; j < iCountOfJun; j++ )
		{
			if( ( 0 == GetProperties( MarkVector, j ) ) && ( iMax > GetProperties( DistanceVector, j ) )
				&& ( iMinDistance > GetProperties( DistanceVector, j ) ) )
			{
				k = j;
				iMinDistance = GetProperties( DistanceVector, j );
			}
		}
		if( -1 == k )                                           //����Ҳ�����ֱ���˳�
		{
			break;
		}
		SetProperties( MarkVector, k, 1 );                      //���

        //�޸����ֵ��·��
		for( j = 0; j < iCountOfJun; j++ )
		{
			if( ( 0 == GetProperties( MarkVector, j ) ) && ( iMax > GetProperties( AbutMatrix, k, j ) )
				&& ( GetProperties( DistanceVector, k ) + GetProperties( AbutMatrix, k, j ) < GetProperties( DistanceVector, j ) ) )
			{
				iTemp = GetProperties( DistanceVector, k ) + GetProperties( AbutMatrix, k, j );
				SetProperties( DistanceVector, j, iTemp );
				SetProperties( TempVector, j, k );
			}
		}
	}
	
    //���ֵ��·��
	k = iTempNumOfStart;
	i = 0;
	while( 0 <= GetProperties( TempVector, k ) )
	{
		SetProperties( PipePathVector, i++, k );
		k = GetProperties( TempVector, k );
	}
	SetProperties( PipePathVector, i++, 0 );    // i �ǽڵ����


	// ���ն�Ӧ���PipePathVector���˳��ת���ɹܵ����
	vector< int >::iterator IntVecIt = PipePathVector.begin();
	for( ; PipePathVector.end() != IntVecIt; IntVecIt++ )
	{
		vector< int >::iterator TempIntVecIt = NumToPipeVector.begin();
		i = *IntVecIt;
		for( ; i > 0; i--, TempIntVecIt++ )
		{
			if( NumToPipeVector.end() == TempIntVecIt )
			{
				return false;
			}
		}
		*IntVecIt = *TempIntVecIt;
	}

	// ���ݽڵ�ѹܵ����д������ű�ʾ�ܵ�������ǰ�������෴
	JunToJunPipePath.clear();
	IntVecIt = PipePathVector.begin();
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
	ASSERT( NULL != &IntVector );
	vector< int >::iterator IntVecIt = IntVector.begin();
	vector< int >::iterator IntVecNextIt = IntVecIt;
	IntVecNextIt++;
	for( int i = 0; i < iPosition; i++ )             
	{	
		if( IntVector.end() == IntVecNextIt )
		{
			IntVector.push_back( 0 );
			/*IntVecIt = &IntVector.back();*/
            IntVecIt++;
			IntVecNextIt = IntVecIt;
			IntVecNextIt++;
			continue;
		}
		IntVecIt++;
		IntVecNextIt++;
	}
	if( 0 == IntVector.size() )
	{
		IntVector.push_back( iValue );
	}
	else
	{
		*IntVecIt = iValue;
	}	
	return true;
}

int CPFAOptimize::GetProperties( const vector< int >& IntVector, const int& iPosition )
{
	vector< int >::const_iterator IntVecIt = IntVector.begin();
	for( int i = 0; i < iPosition; i++ ) 
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
		for( int i = 0; i < iLine; i++ )
		{
			TempVector.push_back( 0 );
		}
		TempVector.push_back( iValue );
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
		return -1;
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
			* ( -2 ) * log( 10.0 ) / dTemp
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



bool CPFAOptimize::Example()
{
	CMainFrame* pMainFrame = NULL; 
	pMainFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CChildFrame* pChildFrame = NULL;
	pChildFrame = (CChildFrame*)pMainFrame->GetActiveFrame();
	CAutoPFAView* pAutoView = NULL;
	pAutoView = (CAutoPFAView*)pChildFrame->GetActiveView();
	ComponentManager* pComManager = pAutoView->GetDocument()->m_scenarioManager.GetCurScenario()->GetCompManager();
	ComponentManager ComManager( *pComManager );

	if( ( 0 == ComManager.GetJunNum() ) && ( 0 == ComManager.GetPipeNum() ) )  // û�й���
	{
		return false;
	}
	OptData.RemoveAll();
	// ���ֶ�������ˮԴ�Ϳ��Ƶ�
	int iTemp = 1;
	OptData.SetProperty( 0, 200, iTemp );          // �ڵ�1Ϊ��ˮԴ
	iTemp = 23;
	OptData.SetProperty( 0, 201, iTemp );         // �ڵ�23Ϊ���Ƶ�

	// ��ComManager���д���
 
	JunSystemTransformCircleSystem( ComManager, OptData );
	DisplayMatrix( _T("F://CirPipe.txt"), 100, OptData );
	InitializePipeCircle( OptData );
	DisplayMatrix( _T("F://PipeCir.txt"), 102, OptData );

	// ��pComManager�г�ʼ��OptData�� ��ʼʵ���������ܵ����ȣ��ڵ���������ˮԴ�����Ƶ㣬
	CMinimumSquareSum MinSquSum;

	//MinSquSum.InitializeFactFlux( *pComManager, OptData );   //  ��ʼʵ������
	///////////////////////////////////////
	int i = 0;
	int iKeyOfPipe = 0;
	double Temp = 0.0;
	double dTemp = 0.0;
	Pipe* pPipe = NULL;
	Component* pComponent = NULL; 



	// ����ֱ��
	IteratorPtr<Component> PipeItPtr( ComManager.CreatPipeIterator() );
	for( PipeItPtr->Fist(); !PipeItPtr->IsDone(); PipeItPtr->Next() )
	{
		pComponent = &PipeItPtr->CurrentItem();
	    pPipe = dynamic_cast<Pipe*>( pComponent );
		dTemp = pPipe->Len();
		OptData.SetProperty( pPipe->GetKey(), 2, dTemp );    
		dTemp = pPipe->InDia();
		OptData.SetProperty( pPipe->GetKey(), 4, dTemp );
	}

    // ��ʼ�����ò���
	OptData.SetAModulus( 8.4 );   // 8.4
	OptData.SetBModulus( 107 );
	OptData.SetAlfaModulus( 1.64 );
	OptData.SetDisinvestmentTime( 7.0 );
	OptData.SetRepairModulus( 0.033 );
	OptData.SetEletricityPrice( 0.5 );
	OptData.SetAsymmetryModulus( 0.3 );
	OptData.SetPumpEfficiency( 0.7 );
	OptData.SetKModulus( 1.34e-3 );
	OptData.SetMModulus( 5.33 );
	OptData.SetNModulus( 2 );
	OptData.Initialization();
	OptData.SetEconomyFactor( 1.94 );
	
	// �ڵ�����
	IteratorPtr<Component> JunItPtr( ComManager.CreatJunIterator() );
	Jun* pJun = NULL;
	CString strValue;
	CString strUnit;
	QuantityManager &qm = QuantityManager::Instance();
	for( JunItPtr->Fist(); !JunItPtr->IsDone(); JunItPtr->Next() )
	{
		pComponent = &JunItPtr->CurrentItem();
	    pJun = dynamic_cast<Jun*>( pComponent );
    	FlyWeight* pFW = pJun->GetValue( 7 );
		pFW->GetValue( strValue, strUnit );
		strValue.TrimLeft( _T(' ') );
		strValue.TrimRight( _T(' ') );
		i = strValue.ReverseFind( _T(' ') );
		ASSERT( -1 != i );
		strUnit = strValue.Right( strValue.GetLength() - i - 1 );
		strValue.ReleaseBuffer( i );
		if( !qm.TransformFromTo( Temp, strUnit.GetBuffer( 0 ), _T("m3/sec"), _tcstod( strValue, NULL ) ) )
		{
			if( !qm.TransformFromTo( Temp, strUnit.GetBuffer( 0 ), _T("kg/sec"), _tcstod( strValue, NULL ) ))
			{
				AfxMessageBox( _T( "�ڵ�������ʼ��ʧ��!" ) );
				return false;;
			}
			NumFlyWeight *pDensity = &( ( ComManager.SysProperty().GetFuild() )->ms_Density );                             
			double dDensity = pDensity->GetNum();     // GetNum���ر�׼��λ��
			if( !(1e-9 < fabs( dDensity - 1e-9 ) ) )
			{
				AfxMessageBox( _T( "�ܶ�Ϊ0������������!" ) );
				return false;
			}
			Temp /= dDensity; 
		}
		OptData.SetProperty( pJun->GetKey(), 3, Temp );
	}
	
	// ��ˮԴ����ˮͷ
	dTemp = 50.0;
	OptData.SetProperty( 1, 7, dTemp );

	// ������������������������������Ϊ����ͳ��
	double dFluxSummation = 0.0;
	IteratorPtr< Component > JunitPtr( ComManager.CreatJunIterator() );
	for( JunitPtr->Fist(); !JunitPtr->IsDone(); JunitPtr->Next() )      // �������нڵ�
	{
		pComponent = &( JunitPtr->CurrentItem() );
		pJun = dynamic_cast< Jun* > (pComponent);
		OptData.GetProperty( pJun->GetKey(), 3, dTemp );
		if( 0 > dTemp )             // Ϊ�����ڵ�
		{
			dFluxSummation += dTemp;
		}	
	}
	double dTmp = fabs( dFluxSummation );
    OptData.SetFluxSummation( dTmp );

	MinSquSum.InitializeDummyFlux( ComManager, OptData );   // ��ʼ�����������ý��淨
	MinSquSum.InitializeFactFlux( ComManager, OptData );    // ��ʼʵ������������Сƽ���ͷ�


	

	// �������Եģ�IMP�ļ�����  C:\Documents and Settings\ue101.UESOFT1.000\����\PFA\����.imp
	dTemp = 0.4793;
	Temp = 0.4824;
	OptData.SetProperty( 5, 0, dTemp );
	OptData.SetProperty( 5, 1, Temp );
	dTemp = 0.5207;
	Temp = 0.52986;
	OptData.SetProperty( 1, 0, dTemp );
	OptData.SetProperty( 1, 1, Temp );
	dTemp = 0.1704;
	Temp = 0.14621;
	OptData.SetProperty( 2, 0, dTemp );
	OptData.SetProperty( 2, 1, Temp );
	dTemp = 0.1672;
	Temp = 0.14742;
	OptData.SetProperty( 3, 0, dTemp );
	OptData.SetProperty( 3, 1, Temp );
	dTemp = 0.3031;
	Temp = 0.29841;
	OptData.SetProperty( 4, 0, dTemp );
	OptData.SetProperty( 4, 1, Temp );
	dTemp = 0.1762;
	Temp = 0.16849;
	OptData.SetProperty( 6, 0, dTemp );
	OptData.SetProperty( 6, 1, Temp );
	dTemp = 0.1762;
	Temp = 0.1571;
	OptData.SetProperty( 7, 0, dTemp );
	OptData.SetProperty( 7, 1, Temp );
	dTemp = 0.0368;
	Temp = 0.03453;
	OptData.SetProperty( 8, 0, dTemp );
	OptData.SetProperty( 8, 1, Temp );
	dTemp = 0.0919;
	Temp = 0.07161;
	OptData.SetProperty( 9, 0, dTemp );
	OptData.SetProperty( 9, 1, Temp );
	dTemp = 0.2584;
	Temp = 0.18933;
	OptData.SetProperty( 10, 0, dTemp );
	OptData.SetProperty( 10, 1, Temp );
	dTemp = 0.3334;
	Temp = 0.2049;
	OptData.SetProperty( 11, 0, dTemp );
	OptData.SetProperty( 11, 1, Temp );
	dTemp = 0.0042;
	Temp = 0.0132;
	OptData.SetProperty( 14, 0, dTemp );
	OptData.SetProperty( 14, 1, Temp );
	dTemp = 0.1359;
	Temp = 0.11654;
	OptData.SetProperty( 15, 0, dTemp );
	OptData.SetProperty( 15, 1, Temp );
	dTemp = 0.1359;
	Temp = 0.13334;
	OptData.SetProperty( 16, 0, dTemp );
	OptData.SetProperty( 16, 1, Temp );
	dTemp = 0.1401;
	Temp = 0.08073;
	OptData.SetProperty( 13, 0, dTemp );
	OptData.SetProperty( 13, 1, Temp );
	dTemp = 0.3879;
	Temp = 0.22787;
	OptData.SetProperty( 12, 0, dTemp );
	OptData.SetProperty( 12, 1, Temp );
	dTemp = 0.1393;
	Temp = 0.10649;
	OptData.SetProperty( 17, 0, dTemp );
	OptData.SetProperty( 17, 1, Temp );
	dTemp = 0.0533;
	Temp = 0.0288;
	OptData.SetProperty( 21, 0, dTemp );
	OptData.SetProperty( 21, 1, Temp );
	dTemp = 0.1288;
	Temp = 0.08508;
	OptData.SetProperty( 22, 0, dTemp );
	OptData.SetProperty( 22, 1, Temp );
	dTemp = 0.126;
	Temp = 0.05126;
	OptData.SetProperty( 23, 0, dTemp );
	OptData.SetProperty( 23, 1, Temp );
	dTemp = 0.2039;
	Temp = 0.08736;
	OptData.SetProperty( 24, 0, dTemp );
	OptData.SetProperty( 24, 1, Temp );
	dTemp = 0.2151;
	Temp = 0.07079;
	OptData.SetProperty( 29, 0, dTemp );
	OptData.SetProperty( 29, 1, Temp );
	dTemp = 0.528;
	Temp = 0.08275;
	OptData.SetProperty( 33, 0, dTemp );
	OptData.SetProperty( 33, 1, Temp );
	dTemp = 0.086;
	Temp = 0.05428;
	OptData.SetProperty( 18, 0, dTemp );
	OptData.SetProperty( 18, 1, Temp );
	dTemp = 0.086;
	Temp = 0.04104;
	OptData.SetProperty( 19, 0, dTemp );
	OptData.SetProperty( 19, 1, Temp );
	dTemp = 0.0561;
	Temp = 0.03031;
	OptData.SetProperty( 20, 0, dTemp );
	OptData.SetProperty( 20, 1, Temp );
	dTemp = 0.1421;
	Temp = 0.05071;
	OptData.SetProperty( 25, 0, dTemp );
	OptData.SetProperty( 25, 1, Temp );
	dTemp = 0.1148;
	Temp = 0.03894;
	OptData.SetProperty( 26, 0, dTemp );
	OptData.SetProperty( 26, 1, Temp );
	dTemp = 0.2569;
	Temp = 0.06789;
	OptData.SetProperty( 27, 0, dTemp );
	OptData.SetProperty( 27, 1, Temp );
	dTemp = 0.1652;
	Temp = 0.01518;
	OptData.SetProperty( 28, 0, dTemp );
	OptData.SetProperty( 28, 1, Temp );
	dTemp = 0.4221;
	Temp = 0.05957;
	OptData.SetProperty( 31, 0, dTemp );
	OptData.SetProperty( 31, 1, Temp );
	dTemp = 0.5779;
	Temp = 0.07533;
	OptData.SetProperty( 30, 0, dTemp );
	OptData.SetProperty( 30, 1, Temp );
	dTemp = 0.4221;
	Temp = 0.0442;
	OptData.SetProperty( 32, 0, dTemp );
	OptData.SetProperty( 32, 1, Temp );
	dTemp = 0.528;
	Temp = 0.23521;
	OptData.SetProperty( 34, 0, dTemp );
	OptData.SetProperty( 34, 1, Temp );

  
	/////////////////
	m_DlgOptProGress.ShowWindow( SW_SHOW );
	
	if( !DoOptimitation( ComManager, OptData ) )
	{
		return false;
	}
	m_DlgOptProGress.ShowWindow( SW_HIDE );
	// ��������Ҫ��
    //CalOthersVariable( *pComManager, OptData );
	DisplayResult( OptData );
	return true;
}

bool CPFAOptimize::DoOptimitation( ComponentManager& ComManager, PFAOptimitationData& OptData )
{
	double dWaterHammer = 0.0;
	double dTempCloseSubtract = 0.0;      // �������㻷��У������
	double dCloseSubtract = 0.0;          // ��У������
	double dPipeDiameter = 0.0;
	double dPipeFactFlux = 0.0;
	double dPipeLength = 0.0;
	double dTemp = 0.0;
	double dFactPrecision = 0.01;
	bool bFlagFactCloseSubtract = true;
	long lTimes = 0;
	int iKeyOfPipe = 0;
	int i = 0;
	int j = 0;
	int iFlagCircleOver = 0;                        // ���iFlagCircleOver���ڻ��������ʾ���л���ƽ�����
	map< int, double > PipeWaterHammerMap;          // �ܵ�ˮͷ��ʧ
	map< int, double > CirReviseValueMap;           // ��У������
	map< int, double > PipeTempDiameterMap;         // �ϴμ����ֱ��
	lTimes = 0;
	m_DlgOptProGress.ProssMove( 1, 0, 0 );                // ���������ƶ�0������0��ʼ
	do
	{	
		m_DlgOptProGress.ProssMove( 0, 0, 0 );            // �ӽ������ƶ�0������0��ʼ
		long lCount = 0;
		bFlagFactCloseSubtract = true;	
		CalDummyFlux( 0.12, OptData );
		while ( true )
		{
			lCount++;
			iFlagCircleOver = 0;
			PipeWaterHammerMap.clear();
			CirReviseValueMap.clear();
			for ( i = 1; i <= OptData.GetPropertyCount( 100 ); i++ )         // �������л�
			{
				dWaterHammer = 0.0;                    
				dTempCloseSubtract = 0.0;
				for ( j = 0; j < OptData.GetPropertyCount( i, 100 ); j++ )     // �������е����йܵ�
				{
					double dTempOne = 0.0;
					OptData.GetProperty( i, 100, j, iKeyOfPipe );
					OptData.GetProperty( iKeyOfPipe, 4, dPipeDiameter );
					OptData.GetProperty( iKeyOfPipe, 1, dPipeFactFlux );
					OptData.GetProperty( iKeyOfPipe, 2, dPipeLength );
					if( 0.3 < dPipeDiameter )          // Ӧ�����������㹫ʽ����û�鵽�����ܵ�ֱ����ѡ��ʽ
					{
						// �ܵ�ˮͷ��ʧ h = k*q`2*l / d`m
						dTemp = 0.002021 * dPipeLength * dPipeFactFlux * fabs( dPipeFactFlux ) / pow( dPipeDiameter, 5.33 );					  
					}
					else
					{
						dTemp = 0.000915 * dPipeLength * dPipeFactFlux * pow( fabs( dPipeFactFlux ), 0.774 ) / pow( dPipeDiameter, 4.774 );
					}
					
					if( !( 1.0e-6 > fabs( dPipeFactFlux - 1.0e-6 ) ) )    // �ж�F�Ƿ�Ϊ0
					{
						// ������У��������
						dTempCloseSubtract = dTemp / dPipeFactFlux + dTempCloseSubtract;
					}
					else
					{
						dTempCloseSubtract += 1.0;
					}
					PipeWaterHammerMap.insert( map< int, double >::value_type( abs( iKeyOfPipe ), dTemp ) );
					OptData.SetProperty( iKeyOfPipe, 11, dTemp );
					dTemp = ( iKeyOfPipe / abs( iKeyOfPipe ) ) * dTemp;					
					dWaterHammer += dTemp;                           // ���Ĺܵ�ˮͷ��ʧ��	                   		
				}	
				dCloseSubtract = dWaterHammer;                       // ���ıպϲ� 
				if( dFactPrecision > fabs( dCloseSubtract ) )            // �������ˮͷ��ʧ�պϲ�С�ڿ��ƾ���
				{
					iFlagCircleOver++;   
				}
				dTemp = -1.0 * 0.2 * dCloseSubtract / dTempCloseSubtract;  // ����У������ = -�ɳ����� * ��ˮͷ��ʧ / S
		                                                                   // 0.2Ϊ�ɳ����ӣ�0.2-1�����ԣ����������������
				CirReviseValueMap.insert( map< int, double >::value_type( i, dTemp ) ); 
			}
        
			if( 1 == ( iFlagCircleOver / OptData.GetPropertyCount( 101 ) ) )               // ���еĻ���ƽ�����  
			{
				break;
			}

			// �����ܵ�����
			int iKeyOfCir = 1;
			int iTempCir = 0;
			map< int, int > FinishPipeKeyMap;
			for ( i = 1; i <= OptData.GetPropertyCount( 100 ); i++, iKeyOfCir++ )  // �������л�
			{
				dTemp = 0.0;
				for( j = 0; j < OptData.GetPropertyCount( i, 100 ); j++ )
				{
					long lMaxCirCount = 0;
					if( !OptData.GetProperty( iKeyOfCir, 100, j, iKeyOfPipe ) )
					{
						iKeyOfCir++;
						lMaxCirCount++;
						if( 5000 < lMaxCirCount )
						{
							return false;
						}
					}
					
					// �ж��Ƿ�����
					if( FinishPipeKeyMap.end() != FinishPipeKeyMap.find( abs( iKeyOfPipe ) ) )
					{
						continue;
					}
					else
					{
						FinishPipeKeyMap.insert( map< int, int >::value_type( abs( iKeyOfPipe ), i ) );
					}

					OptData.GetProperty( iKeyOfPipe, 1, dPipeFactFlux );				
					dPipeFactFlux = ( iKeyOfPipe / abs( iKeyOfPipe ) ) * dPipeFactFlux;
					for( int k = 0; k < OptData.GetPropertyCount( iKeyOfPipe, 102 ); k++ )
					{
						if( !OptData.GetProperty( iKeyOfPipe, 102, k, iTempCir ) )
						{
							break;
						}
						
						map< int, double >::iterator IntDouMapIt = CirReviseValueMap.find( abs( iTempCir ) );
						if( CirReviseValueMap.end() == IntDouMapIt )
						{
							return false;                       // ��û�ж�Ӧ����������
						}
						else
						{
							dTemp = IntDouMapIt->second;
						}
						
						if( abs( iTempCir ) == iKeyOfCir )
						{
							dPipeFactFlux += dTemp;
						}
						else
						{
							dPipeFactFlux -= dTemp;
						}
					}
					dPipeFactFlux = ( iKeyOfPipe / abs( iKeyOfPipe ) ) * dPipeFactFlux;
				    OptData.SetProperty( iKeyOfPipe, 1, dPipeFactFlux );
				}
			}

			m_DlgOptProGress.ProssMove( 0 );              // �ӽ������ƶ�1��
			// ���������������5000����û�������
			if( 5000 < lCount )
			{
				return false;
			}
		}
	
	
		m_DlgOptProGress.ProssMove( 0, 0, 10000 );        // �ӽ������ƶ���10000
		// �ж�ǰ��2�μ���Ĺܾ�����Ƿ�С��45��
		map< int, double >::iterator IntDouMap;
		int iKeyOfCir = 1;
		bool bFlagInit = 0 < PipeTempDiameterMap.size();       // �Ƿ��һ�Σ�fasle�Ļ����ǵ�һ��
		for ( i = 1; i <= OptData.GetPropertyCount( 100 ); i++, iKeyOfCir++ )           // ������
		{	
			for ( j = 0; j < OptData.GetPropertyCount( i, 100 ); j++ )   // �������йܵ�
			{
				long lMaxCirCount = 0;
				if( !OptData.GetProperty( iKeyOfCir, 100, j, iKeyOfPipe ) )
				{
					iKeyOfCir++;
					lMaxCirCount++;
					if( 5000 < lMaxCirCount )
					{
						return false;
					}
				}	
				OptData.GetProperty( iKeyOfPipe, 4, dPipeDiameter );
				if( bFlagInit )
				{
			     	IntDouMap = PipeTempDiameterMap.find( abs( iKeyOfPipe ) );				
			    	double dTempDiameter = IntDouMap->second;				
			    	if( 0.045 < fabs( dTempDiameter - dPipeDiameter ) )
					{
					    bFlagFactCloseSubtract = false;
					}
			    	IntDouMap->second = dPipeDiameter;		
				}
				else
				{
					PipeTempDiameterMap.insert( map< int, double >::value_type( abs( iKeyOfPipe ), dPipeDiameter ) );
					bFlagFactCloseSubtract = false;
				}
			}
		}

		m_DlgOptProGress.ProssMove( 1 );             // ���������ƶ�1��
		lTimes++;
		if( 5000 < lTimes )
		{
			return false;
		}
	}while( false == bFlagFactCloseSubtract );

	


	// �ܵ�����
	map< int, vector< int > >* pMap = OptData.GetCirPipeMatrix();
	map< int, vector< int > >::iterator IntVecMapIt = pMap->begin();              
	double dConstructExpense = 0.0;                       // ������� 
	
	// ���㽨����õ�ϵ��
	double dTempConstruct = ( OptData.GetRepairModulus() + 1.0 / OptData.GetDisinvestmentTime() ) * OptData.GetBModulus();
	for ( ; pMap->end() != IntVecMapIt; IntVecMapIt++ )   // ������
	{
		int iKeyOfCir = IntVecMapIt->first;
		vector< int >::iterator IntVecIt = IntVecMapIt->second.begin();
		for ( ; IntVecMapIt->second.end() != IntVecIt; IntVecIt++ )    // �����ܵ�
		{
			OptData.GetProperty( *IntVecIt, 1, dPipeFactFlux );
			OptData.GetProperty( *IntVecIt, 4, dPipeDiameter );
			OptData.GetProperty( *IntVecIt, 2, dPipeLength );
			dTemp = 4.0 * dPipeFactFlux / ( PI * dPipeDiameter * dPipeDiameter );
			OptData.SetProperty( *IntVecIt, 6, dTemp );

			dConstructExpense = dConstructExpense + dPipeDiameter * dPipeLength * dTempConstruct; // ���㽨�����		
		}
	}
	
	/*
	// ����ڵ�ˮѹ
	POINT( 1 )=43.0+8;          // ��1�ڵ�ľ���ˮѹ,Ӧ����ָ��ˮԴ
	for ( i = 0; i < OptData.GetPropertyCount( 101 ); i++ )     // ������
	{
		HH=POINT( KL( I, 1 ) );     // HH = ��I����1���ڵ�ˮѹ
		for ( J = 1; J < LOTN( 1 ); J++ )  // �ӻ��ĵ�2���ڵ㿪ʼ����
		{
			K=KL( I, J );                // K = ��I����J���ڵ���
			HH=HH-H( I, J-1 );           // HH = ��I����J���ڵ��ˮѹ
			POINT( K )=HH;               // ���ñ��ΪK������I����J���ڵ㣩�Ľڵ�ľ���ˮѹ
			KJ( K )=K;                   // ���K�ڵ� 
		}
	}
	
	// �ѽڵ�ľ���ˮѹת�����ˮѹ 
	for ( I = 0; I < 23; I++ )   // �������нڵ㣬�ڵ����ܹ�23��
	{
		if( KJ( I )==0 )
		{
			WRITE( *, * );
		}
		HCP( I )=POINT( I )-BIAO( I );       // ����I�ڵ�����ˮѹ
	}	

  
	*/
	dTemp = 0.0;
	double dYConvertExpenditure = 0.0;
	double dWorkExpenditure = OptData.GetWorkExpenditure();
	double dFluxSummation = OptData.GetFluxSummation();
	double dK = OptData.GetKModulus();
	double dAlfa = OptData.GetAlfaModulus();
	double dM = OptData.GetMModulus();
	double dN = OptData.GetNModulus();
	int iCountSupplyJun = OptData.GetPropertyCount( 200 );
	int iCountControlJun = OptData.GetPropertyCount( 201 );
	vector< int > JunToJunPipePath;
	vector< int >::iterator IntVecIt;

	// �����������
	CirMatrix* pCirMatrix = OptData.GetPipeCirMatrix();
	IntVecMapIt = pCirMatrix->begin();

	if( ( 0 == iCountSupplyJun ) || ( 0 == iCountControlJun ) )          // ��ˮԴ����Ƶ�û����
	{
		return false;
	}

	dYConvertExpenditure = dConstructExpense;
	if( 0 > fabs( dWorkExpenditure - 1e-6 ) )                            // ����������������
	{
		OptData.SetYConvertExpenditure( dYConvertExpenditure );
		return true;
	}

	int iKeyOfControlJun = 0;
	int iKeyOfSupplyJun = 0;
	double dPipeDummyWaterHammer = 0.0;
	double dJunWater = 0.0;
	double dJunFlux = 0.0;
	double dTempWork = 0.0;
	OptData.GetProperty( 0, 201, iKeyOfControlJun );                      // ѡȡ��һ�����Ƶ�Ϊ������Ҫ�ĵ�
	dTemp = 0.0;
	for( i = 0; i < iCountSupplyJun; i++ )
	{
		OptData.GetProperty( i, 200, iKeyOfSupplyJun );                   //  ��ȡ��i����ˮԴ�ڵ���
			
		// �ҵ�����ˮԴ�����Ƶ�����·����������JunToJunPipePath��
		JunToJunPipePath.clear();
		FindShortCut( ComManager, iKeyOfSupplyJun, iKeyOfControlJun, JunToJunPipePath ); 	
		////////////////////////
		IntVecIt = JunToJunPipePath.begin();
		for( ; JunToJunPipePath.end() != IntVecIt; IntVecIt++ )
		{
			OptData.GetProperty( abs( *IntVecIt ), 10, dPipeDummyWaterHammer );
			dPipeDummyWaterHammer = ( *IntVecIt / abs( *IntVecIt ) ) * dPipeDummyWaterHammer;
			dTemp += dPipeDummyWaterHammer;                                     // ������ˮԴ�����Ƶ����ˮͷ��ʧ
		}
		dPipeDummyWaterHammer = dTemp;                                     // dPipeDummyWaterHammerΪ��ˮԴ�����Ƶ����ˮͷ��ʧ
		
		OptData.GetProperty( iKeyOfSupplyJun, 7, dJunWater );             // ��ȡ��ˮԴˮͷ
		OptData.GetProperty( iKeyOfSupplyJun, 3, dJunFlux );               // ��ȡ��ˮԴ�ڵ�����
		if( ( 1e-6 > fabs( dJunWater - 1e-6 ) ) || ( 1e-6 > fabs( dJunFlux - 1e-6 ) ) )
		{
			return false;
		}
		dWorkExpenditure = pow( dK * dPipeDummyWaterHammer / dJunWater, 1.0 / ( dAlfa + dM ) ) / dJunFlux;
		dTempWork = dTempWork + dTemp * dWorkExpenditure * fabs( dJunFlux ); // ����Ӫ����
	}
                 
		
	// ���������
	dYConvertExpenditure += dTempWork;                                         // ��������� = ������� + ����Ӫ����
	OptData.SetYConvertExpenditure( dYConvertExpenditure );
	
    return true;
	
}


bool CPFAOptimize::CalDummyFlux( const double& dDummyPrecision, PFAOptimitationData& OptData )
{
	long lTimes = 0;
	int i = 0;
	int j = 0;
	int iFlagCircleOver = 0; // ���iFlagCircleOver���ڻ��������ʾ���л���ƽ�����
	//////////////////////////////////////////////////////////////////////////
	double dWaterHammer = 0.0;
	double dTempCloseSubtract = 0.0;      // �������㻷��У������
	double dCloseSubtract = 0.0;          // ��У������
	double dPipeDiameter = 0.0;
	double dPipeDummyFlux = 0.0;
	double dPipeLength = 0.0;
	double dPipeFactFlux = 0.0;
	double dTemp = 0.0;
	double dM = OptData.GetMModulus();
	double dAlfa = OptData.GetAlfaModulus();
	double dN = OptData.GetNModulus();
	bool bFlagDummyCloseSubtract = false;
	int iKeyOfPipe = 0;
	map< int, double > PipeDummyWaterHammerMap; // �ܵ�ˮͷ��ʧ
	map< int, double > CirCloseSubtract;
	map< int, double > CirReviseValueMap;      // ��У������
	map< int, double > PipeTempDiameterMap;      // �ϴμ����ֱ��
	/////////////////
	while( false == bFlagDummyCloseSubtract )
	{
		bFlagDummyCloseSubtract = false;
		iFlagCircleOver = 0; 
		lTimes++;
		PipeDummyWaterHammerMap.clear();
		CirCloseSubtract.clear();
		CirReviseValueMap.clear();
		for ( i = 1; i <= OptData.GetPropertyCount( 100 ); i++ )  // ������
		{
			dCloseSubtract = 0.0;
			dTempCloseSubtract = 0.0;
			for ( j = 0; j < OptData.GetPropertyCount( i, 100 ); j++ )  // �����������йܵ�
			{
				OptData.GetProperty( i, 100, j, iKeyOfPipe );
				OptData.GetProperty( iKeyOfPipe, 0, dPipeDummyFlux );
				dTemp = ( dPipeDummyFlux / fabs( dPipeDummyFlux ) ) * pow( 1.0 / fabs( dPipeDummyFlux ), dM / ( dAlfa + dM ) );
				OptData.GetProperty( iKeyOfPipe, 1, dPipeFactFlux );
				OptData.GetProperty( iKeyOfPipe, 2, dPipeLength );
				dTemp = pow( fabs( dPipeFactFlux ), dN * dAlfa / ( dAlfa + dM ) ) * dPipeLength * dTemp;// ������ˮͷ��ʧ,��λ�� 
				PipeDummyWaterHammerMap.insert( map< int, double >::value_type( abs( iKeyOfPipe ), dTemp ) );  
				OptData.SetProperty( iKeyOfPipe, 10, dTemp );
				if( !(1.0e-6 > fabs( dPipeDummyFlux - 1.0e-6 ) ) )
				{
					dTempCloseSubtract = dTempCloseSubtract + fabs( dTemp ) / fabs( dPipeDummyFlux );// ������У�������� 
				}
				else
				{
					dTempCloseSubtract = dTempCloseSubtract + 1.0;
				}
				dTemp = ( iKeyOfPipe / abs( iKeyOfPipe ) ) * fabs( dTemp );
				dCloseSubtract += dTemp;           // ��ˮͷ��ʧ��
			}    
			CirCloseSubtract.insert( map< int, double >::value_type( i, dCloseSubtract ) );    // ��I��������ˮͷ��ʧ�պϲ�     
			if( dDummyPrecision > fabs( dCloseSubtract ) )            // ����������պϲ�С��ָ������
			{
				iFlagCircleOver++; 
			}
			dTemp = 0.15 * dCloseSubtract / ( ( dM / ( dAlfa + dM ) ) * dTempCloseSubtract );
			CirReviseValueMap.insert( map< int, double >::value_type( i, dTemp ) );   // ��IУ��������0.15�ɳ�����	
		}
		
		if( 1 == ( iFlagCircleOver / OptData.GetPropertyCount( 100 ) ) )  // ������еĻ���ƽ�����
		{
			bFlagDummyCloseSubtract = true;
			break;
		}
		
		long lTime = 0;
		int iKeyOfCir = 1;
		int iTempCir = 0;
		map< int, int > FinishPipeKeyMap;

		for ( i = 1; i <= OptData.GetPropertyCount( 100 ); i++, iKeyOfCir++ )  // �������л�
		{
			dTemp = 0.0;
			for( j = 0; j < OptData.GetPropertyCount( i, 100 ); j++ )
			{
				if( !OptData.GetProperty( iKeyOfCir, 100, j, iKeyOfPipe ) )
				{
					iKeyOfCir++;
					lTime++;
					if( 5000 < lTime )
					{
						return false;
					}
				}

				// �ж��Ƿ�����
				if( FinishPipeKeyMap.end() != FinishPipeKeyMap.find( abs( iKeyOfPipe ) ) )
				{
					continue;
				}
				else
				{
					FinishPipeKeyMap.insert( map< int, int >::value_type( abs( iKeyOfPipe ), i ) );
				}

				OptData.GetProperty( iKeyOfPipe, 0, dPipeDummyFlux );				
				dPipeDummyFlux = ( iKeyOfPipe / abs( iKeyOfPipe ) ) * dPipeDummyFlux;
				for( int k = 0; k < OptData.GetPropertyCount( iKeyOfPipe, 102 ); k++ )
				{
				    if( !OptData.GetProperty( iKeyOfPipe, 102, k, iTempCir ) )
					{
					    break;
					}

				   	map< int, double >::iterator IntDouMapIt = CirReviseValueMap.find( abs( iTempCir ) );
					if( CirReviseValueMap.end() == IntDouMapIt )
					{
						return false;                       // ��û�ж�Ӧ����������
					}
					else
					{
						dTemp = IntDouMapIt->second;
					}

					if( abs( iTempCir ) == iKeyOfCir )
					{
						dPipeDummyFlux += dTemp;
					}
					else
					{
						dPipeDummyFlux -= dTemp;
					}
				}
				dPipeDummyFlux = fabs( dPipeDummyFlux );
				OptData.SetProperty( iKeyOfPipe, 0, dPipeDummyFlux );
			}
		}

		m_DlgOptProGress.ProssMove( 0 );              // �ӽ������ƶ�1��
		if( 5000 < lTimes )       // ������������������������δƽ���������
		{
			return false;
		}
	}

	int iKeyOfCir = 1;
	long lCount = 0;
	for( i = 1; i <= OptData.GetPropertyCount( 100 ); i++, iKeyOfCir++ )       // �������л�
	{
		lCount = 0;
		if( !OptData.GetProperty( iKeyOfCir, 100, 0, iKeyOfPipe ) )
		{
			iKeyOfCir++;
			lCount++;
			if( 5000 < lCount )
			{
				return false;
			}
		}

		for ( j = 0; j < OptData.GetPropertyCount( iKeyOfCir, 100 ); j++ )    // �����������йܵ�
		{
			if( !OptData.GetProperty( iKeyOfCir, 100, j, iKeyOfPipe ) )
			{
				return false;
			}
			OptData.GetProperty( iKeyOfPipe, 0, dPipeDummyFlux );
			OptData.GetProperty( iKeyOfPipe, 1, dPipeFactFlux );
			dTemp = pow( OptData.GetEconomyFactor() * OptData.GetFluxSummation() * dPipeDummyFlux * dPipeFactFlux *dPipeFactFlux,
				1.0 / ( dAlfa + dM ) );      // ���㾭�ùܾ�
			OptData.SetProperty( iKeyOfPipe, OPT_PIPEECONOMYDIAMETER, dTemp );       // �洢���ùܾ�
			dPipeDiameter = CalStdDiameter( dTemp );   // Ӧ����ȡ��׼�ܾ�
			OptData.SetProperty( iKeyOfPipe, 4, dPipeDiameter );
		}
	}

	m_DlgOptProGress.ProssMove( 0, 0, 5000 );       // �ӽ������ƶ���5000
	return bFlagDummyCloseSubtract;
}
                                      
double CPFAOptimize::CalStdDiameter( const double& dCalDiameter ) // ȡ��׼�ܾ��ĺ���
{
	int iFactor = int( dCalDiameter * 100 / 5 );

	// ��ȡ��ֱ����ԭ����ֱ��С��5%������301�Ļ�iFactor=6����301-300=1С��301��5%����iFactor= 6��
	// �����320����iFactor=6����320-300=20����320��5%����iFactor=7��
	if( ( dCalDiameter * 0.05 ) < fabs( dCalDiameter - iFactor * 0.05 ) )
	{	
		iFactor++;
	}
	
	if( 0.3 < dCalDiameter )               // ֱ��300mm���ϾͲ�ȡ�м�ֵ�������������7��ȡ8��6��ȡ6
	{
		iFactor = iFactor % 2 + iFactor;      
	}
	return iFactor * 0.05;
}


bool CPFAOptimize::DisplayResult( PFAOptimitationData& OptData )
{
	CMainFrame* pMainFrame = NULL; 
	pMainFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CChildFrame* pChildFrame = NULL;
	pChildFrame = (CChildFrame*)pMainFrame->GetActiveFrame();
	CAutoPFADoc* pAutoDoc = NULL;
	pAutoDoc = (CAutoPFADoc*)pChildFrame->GetActiveDocument();
	NetModel* pNetModel = pAutoDoc->m_scenarioManager.GetCurScenario()->GetNetModel();
	PFAOutModel &outModel = pAutoDoc->m_OutModel; 
	PipeStmOutMgr &PipeStmOutMgrTemp = outModel.SteadyOut().ComponentOutMgr().PipeOutMgr();   
	OutMgr* pOutMgr = &PipeStmOutMgrTemp;                        // ����д��ĵط�
	
	PipeStmOutMgrTemp.EmptyOut();
	int iKeyOfPipe = 0;
	int i = 0;
	double dTemp = 0.0;
	
	// ������  
	pOutMgr->GetArray().RemoveAll();
	pOutMgr->GetArray().Add( OutDataAttr( pAutoDoc->m_unitSystem, 0, None, _T( "���" ) ) );      // ���	
	pOutMgr->GetArray().Add( OutDataAttr( pAutoDoc->m_unitSystem, 1, None, _T( "������" ) ) );    // ������
	pOutMgr->GetArray().Add( OutDataAttr( pAutoDoc->m_unitSystem, 2, VolumetricFlow, _T( "ʵ����" ) ) );    // ʵ����
	pOutMgr->GetArray().Add( OutDataAttr( pAutoDoc->m_unitSystem, 3, Diameter, _T( "���ùܾ�" ) ) );  // 
	pOutMgr->GetArray().Add( OutDataAttr( pAutoDoc->m_unitSystem, 4, Diameter, _T( "��׼�ܾ�" ) ) );
	pOutMgr->GetArray().Add( OutDataAttr( pAutoDoc->m_unitSystem, 5, Length, _T( "�ܵ�����" ) ) );
	
	ComponentStmOut* pComOut = NULL;
	for( i = 0; i < OptData.GetPropertyCount( OPT_PIPECIR ); i++ )
	{
		if( !OptData.GetProperty( i, OPT_PIPECIR, iKeyOfPipe ) )
		{
			return false;
		}
		pComOut = PipeStmOutMgrTemp.CreatorComponent( i + 1 );
		pComOut->SetValue( iKeyOfPipe, 0 );
		OptData.GetProperty( iKeyOfPipe, OPT_PIPEDUMMYFLUX, dTemp );
		pComOut->SetValue( dTemp, 1 );
		OptData.GetProperty( iKeyOfPipe, OPT_PIPEFACTFLUX, dTemp );
		pComOut->SetValue( dTemp, 2 );
		OptData.GetProperty( iKeyOfPipe, OPT_PIPEECONOMYDIAMETER, dTemp );
		pComOut->SetValue( dTemp, 3);
		OptData.GetProperty( iKeyOfPipe, OPT_PIPEDIAMETER, dTemp );
		pComOut->SetValue( dTemp, 4);
		OptData.GetProperty( iKeyOfPipe, OPT_PIPELENGTH, dTemp );
		pComOut->SetValue( dTemp, 5 );
	}

	return true;
}
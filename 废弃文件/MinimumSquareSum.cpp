// MinimumSquareSum.cpp: implementation of the CMinimumSquareSum class.
// 
//////////////////////////////////////////////////////////////////////
/************************************************************************
�汾: 8.0       ����ʱ��: 2008/05/31  ����: COM 

����: ��ʼ����������Ҫ��������ʼ��������
                                                             
����: 
                                                              
���: PFAOptimitationData& OptData����OptData�еĶ�Ӧλ�ü�¼������  
                                                        
< �޸��� >    < ʱ�� >     < �汾 >        < ���� > 
   COM        2008/05/31    8.0                                                                                            
************************************************************************/

#pragma once
#include "stdafx.h"
#include "autopfa.h"
#include "MinimumSquareSum.h"
#include "PFAOptimitationData.h"
#include "Iterator.h"
#include <math.h>
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMinimumSquareSum::CMinimumSquareSum()
{

}

CMinimumSquareSum::~CMinimumSquareSum()
{

}

bool CMinimumSquareSum::InitializeModulusMatrix( ComponentManager& ComManager, PFAOptimitationData& OptData, map< int, vector< double > >& ModulusMatrix )
{
	ASSERT( NULL != &ComManager );
	ASSERT( NULL != &OptData );

	Jun* pJun = NULL;
	Component* pJunComponent = NULL;
	Pipe* pPipe = NULL;
	Component* pPipeComponent = NULL; 
	ComMap CloseJuns;              // �����е� (3,4,5)
	vector< double > ModulusVector;// ϵ�������е�ĳһ��
	CirMatrix JunAndJuns;          // �ڵ����ڵ������Ľڵ���
	int iCountOfJuns = 0;          // �ڵ������

	// �ѽڵ����ڵ������Ľڵ��Ŷ�����JunAndJuns
	// ��ڵ�1�ͽڵ�3��4��5��������( 1, ( (3,4,5) )
	IteratorPtr<Component> JunItPtr( ComManager.CreatJunIterator() );
	for( JunItPtr->Fist(); !JunItPtr->IsDone(); JunItPtr->Next() )
    {
		iCountOfJuns++;
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
				CloseJuns.push_back( pPipe->EndJun() );
			}
			if( pPipe->EndJun() == pJun->GetKey() )	
			{
				CloseJuns.push_back( pPipe->StartJun() );
			}

		}
		JunAndJuns.insert( CirMatrix::value_type( pJun->GetKey(), CloseJuns ) );
	}

	ComMap::iterator CloseJunsIt;
	ComMap* pJunVector;
	CirMatrix::iterator JunsIt;
	for( JunItPtr->Fist(); !JunItPtr->IsDone(); JunItPtr->Next() )
    {
		ModulusVector.clear();
		pJunComponent = &JunItPtr->CurrentItem();
		pJun = dynamic_cast<Jun*>( pJunComponent );	

		// ��ʼ��������Ҫ��ʼ��iCountOfJuns+1��
		for( int i = 0; i <= iCountOfJuns; i++ )
		{
			ModulusVector.push_back( 0 );
		}

		JunsIt = JunAndJuns.find( pJun->GetKey() );
 	    pJunVector = ( ComMap* ) &( JunsIt->second );
		int j = 0;           // �ڵ�������
		for( CloseJunsIt = pJunVector->begin(); CloseJunsIt != pJunVector->end(); CloseJunsIt++ )
		{
			// ������ӽڵ�����ˮԴ�ڵ�Ļ��Ͳ���ϵ����Ϊ-1������Ȼ����ڵ�������
			j++;
			int iKeyOfSupplyJun = 0;
			for( int m = 0; m < OptData.GetPropertyCount( 200 ); m++ )
			{
				OptData.GetProperty( m, 200, iKeyOfSupplyJun);
				if( iKeyOfSupplyJun != *CloseJunsIt )
				{
					ModulusVector[ *CloseJunsIt - 1 ] = -1;	
				}
				else
				{
					break;
				}
			}		
		}
		ModulusVector[ pJun->GetKey() - 1 ] = j;                      // ÿ���ڵ�Ľڵ�������
		OptData.GetProperty( pJun->GetKey(), 3, ModulusVector[ iCountOfJuns ] );     // �ڵ�Ľڵ�������Q=1ʱҪ�ȴ���һ��
		ModulusVector[ iCountOfJuns ] *= -2.0;
		ModulusMatrix.insert( map< int, vector< double > >::value_type( pJun->GetKey(), ModulusVector ) );
	}
	return true;
}

bool CMinimumSquareSum::SetInitializePipeFlux( const int& iFluxType,ComponentManager& ComManager, IntDoubleMap& DummyFluxMap, PFAOptimitationData& OptData )
{
	ASSERT( NULL != &ComManager );
	ASSERT( NULL != & DummyFluxMap );

	Pipe* pPipe = NULL;
	Component* pPipeComponent = NULL; 
	IteratorPtr<Component> PipeItPtr( ComManager.CreatPipeIterator() );
	IntDoubleMap::iterator DumIt;
	double dStartDummyFlux = 0.0;
	double dEndDunmmyFlux = 0.0;
	
	// ����ˮ���ֵ����Ϊ0
	int iKeyOfSupplyJun = 0;
	for( int m = 0; m < OptData.GetPropertyCount( 200 ); m++ )
	{
		OptData.GetProperty( m, 200, iKeyOfSupplyJun);
		DumIt = DummyFluxMap.find(iKeyOfSupplyJun );
		if( DummyFluxMap.end() != DumIt )
		{
			DumIt->second = 0.0;
		}
	}

	// ���ùܵ�������
	for( PipeItPtr->Fist(); !PipeItPtr->IsDone(); PipeItPtr->Next() )
	{
		pPipeComponent = &PipeItPtr->CurrentItem();
		pPipe = dynamic_cast<Pipe*>( pPipeComponent );
		DumIt = DummyFluxMap.find( pPipe->StartJun() );
		dStartDummyFlux = DumIt->second;
		DumIt = DummyFluxMap.find( pPipe->EndJun() );
		dEndDunmmyFlux = DumIt->second;
		dEndDunmmyFlux = ( dEndDunmmyFlux - dStartDummyFlux ) / 2.0;
		if( ( 0 <= iFluxType ) && ( 1 >= iFluxType ) )
		{
			OptData.SetProperty( pPipe->GetKey(), iFluxType, dEndDunmmyFlux );
		}
		
	}
	return true;
}

bool CMinimumSquareSum::InitializeDummyFlux( ComponentManager& ComManager, PFAOptimitationData& OptData )
{
	double Variance = 0.0001;                              // ���ȿ���
	map< int, double > ResultMap;                         // �������
	int i = 0;
	map< int, vector< double > > ModulusMatrix;
	InitializeModulusMatrix( ComManager, OptData, ModulusMatrix );

	// �ѽڵ�������Ϊ Q�ڵ�/ Q������
	Jun* pJun = NULL;
	Component* pJunComponent = NULL;
	int iCountOfJuns = ComManager.GetJunNum();          // �ڵ������
	
	// ����������
	double dFluxSummation = 0.0;
	double dTemp = 0.0;
	int iKeyOfJun = 0;
	for( i = 0; i < OptData.GetPropertyCount( 200 ); i++ )
	{
		if( false != OptData.GetProperty( i, 200, iKeyOfJun ) )
		{
			OptData.GetProperty( iKeyOfJun, 3, dTemp );
		    dFluxSummation += dTemp;
		}
	}

	map< int, vector< double > >::iterator IntVecMapIt = ModulusMatrix.begin();
	for( ; IntVecMapIt != ModulusMatrix.end(); IntVecMapIt++ )
	{
		( IntVecMapIt->second )[ iCountOfJuns ] /= dFluxSummation; 
	}

	GaussMethod( ModulusMatrix, Variance, ResultMap );
	SetInitializePipeFlux( 0, ComManager, ResultMap, OptData );
	return true;
}


bool CMinimumSquareSum::InitializeFactFlux( ComponentManager& ComManager, PFAOptimitationData& OptData )
{
	double Variance = 0.0001;                              // ���ȿ���
	map< int, double > ResultMap;                         // �������
	map< int, vector< double > > ModulusMatrix;
	InitializeModulusMatrix( ComManager, OptData, ModulusMatrix );
	GaussMethod( ModulusMatrix, Variance, ResultMap );
	SetInitializePipeFlux( 1, ComManager, ResultMap, OptData );
	return true;
}



// ��NԪ���Է����飬��˹��Ԫ�������ϳ���, �޸����£������е���
void CMinimumSquareSum::OutputMatrix( double **pMatrix, const int& Size, vector< double >& ResultVector)   //�������ϵ��
{	
	ResultVector.clear();
	//vector< double >::iterator VecIt = ResultVector.begin();
	for( int i = 0; i < Size; i++ )
	{
		//if( ResultVector.end() == VecIt )
		//{
			ResultVector.push_back( pMatrix[i][Size] );
		//}
		//else
		//{
		//	*VecIt = pMatrix[i][Size];
		//}
		//VecIt++;
	}
}


void CMinimumSquareSum::InputMatrix( const map< int, vector< double > >& ModulusMatrix, double **pMatrix )
{
	int i = 0;
	int j = 0;
	map< int, vector< double > >::const_iterator ConstMapIt = ModulusMatrix.begin();
	for( ; ConstMapIt != ModulusMatrix.end(); ConstMapIt++ )
	{
		j = 0;
		vector< double >::const_iterator ConstVecIt = ( ConstMapIt->second ).begin();
		for( ; ConstVecIt != ( ConstMapIt->second ).end(); ConstVecIt++ )
		{
			pMatrix[i][j] = *ConstVecIt;
			j++;
		}
		i++;
	}
}
//ʵ��ѡ�������Ԫ����Ԫ
bool CMinimumSquareSum::VanishElement( double **pMatrix, int RowSize, int ColumnSize, double Var )
{	
	int iTemp,k;	
	double dTemp;	
	bool Exclusive;	
	for (int i=0; i<RowSize-1; i++)		
	{		
		iTemp=i;		
		for (k=i+1; k<RowSize; k++)//��aii��ai+1,i������ani��ѡ�������Ԫ 			
			if(fabs(pMatrix[iTemp][i])<fabs(pMatrix[k][i]))				
				iTemp=k;			
			if(pMatrix[iTemp][iTemp]>Var)  				
			{				
				Exclusive=true;				
				if( iTemp!=i)					
				{					
					for(int j=i; j<ColumnSize; j++)						
					{						
						dTemp=pMatrix[iTemp][j];						
						pMatrix[iTemp][j]=pMatrix[i][j];						
						pMatrix[i][j]=dTemp;						
					}					
				}
				
				//��Ԫ����				
				for (k=i+1; k<RowSize; k++)					
				{					
					pMatrix[k][i]=pMatrix[k][i]/pMatrix[i][i];					
					for (int j=i+1; j<ColumnSize; j++)						
						pMatrix[k][j]=pMatrix[k][j]-pMatrix[k][i] * pMatrix[i][j];					
				}				
			}			
			else				
			{				
				Exclusive=false;				
				break;     //��������Ψһ�⣬����ѭ��					
			}			
	}	
	return Exclusive;	
}

//��ת������ĩ֪����X��X��ֵ�������bλ���ϡ�
void CMinimumSquareSum::MatrixInvers( double **pMatrix, int RowSize, int ColumnSize)
{	
	for ( int i=RowSize-1; i>=0; i-- )		
	{		
		double sum=0;		
		for (int j=i+1; j<ColumnSize-1; j++)			
			sum += pMatrix[i][j] * pMatrix[j][ColumnSize-1];		
		pMatrix[i][ColumnSize-1]=(pMatrix[i][ColumnSize-1]-sum)/pMatrix[i][i];		
	}	
}

bool CMinimumSquareSum::GaussMethod( const map< int, vector< double > >& ModulusMatrix , const double& dVariance, map< int, double >& ResultMap )
{	
	ASSERT( NULL != &ModulusMatrix );
	ASSERT( 0 < dVariance );
	// ����VarianceΪ����������ͨ��Ϊ�Ƚ�С����ʵ����		
    // ��ĳ��ѡ������ԪС�ڸ���������Ϊ�÷�������Ψһ�⡣
	
	//�������Է����������";	����A���Ҷ�����b�ϳ�һ�����󣬹�����ΪSize������ΪSize��1��
	int Size = ModulusMatrix.size(); 
	vector< double > ResultVector;
	
	//���嶯̬��ά���顣	
	double* *Matrix=new double *[Size];	
	for (int n=0; n<Size; n++)		
		Matrix[n]=new double [Size+1];	
	InputMatrix( ModulusMatrix, Matrix ); 	
	if( VanishElement( Matrix, Size, Size+1, dVariance ))		
	{		
		MatrixInvers( Matrix, Size, Size+1 );		
		OutputMatrix( Matrix, Size, ResultVector ); //��������x��ֵ��Matrix��������һ��,�������ԭ����b�����ϡ�		
	}	
	else		
	{		
		return false;	
	}


	map< int, vector< double > >::const_iterator ConstMapIt = ModulusMatrix.begin();
	vector< double >::iterator VecIt = ResultVector.begin();
	for( ; ModulusMatrix.end() != ConstMapIt; ConstMapIt++, VecIt++ )
	{
		ResultMap.insert( map< int, double >::value_type( ConstMapIt->first, *VecIt ) );
	}
	// �ͷ��ڴ�
	for( int i = 0; i < Size; i++ )
	{
		delete[] Matrix[i];

	}
	return true;
}


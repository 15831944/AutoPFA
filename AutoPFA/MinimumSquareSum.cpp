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
#include <algorithm>

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

	// ����ǰ���ComManager���д���ʹ��ͼ����û�з�֧����ˮԴ������Ҳ������Ӧ�ڵ���
	double dLengthFactor = 3.0;        // �Ľ�����Сƽ���ͷ����г��ȵ��ݴΣ�2.5-3.0֮��Ч�����
	double dTemp = 0.0;
	Jun* pJun = NULL;
	Component* pJunComponent = NULL;
	Pipe* pPipe = NULL;
	Component* pPipeComponent = NULL; 
	ComMap CloseJuns;              // �����е� (3,4,5)
	ComMap ClosePipes;
	vector< double > ModulusVector;// ϵ�������е�ĳһ��
	CirMatrix JunAndJuns;          // �ڵ����ڵ������Ľڵ���
	CirMatrix JunAndPipes;
	int iCountOfJuns = 0;          // �ڵ������
	map< int, double > LengthMap;       // ���ȵ��ݴε���

	// �ѽڵ����ڵ������Ľڵ��Ŷ�����JunAndJuns
	// ��ڵ�1�ͽڵ�3��4��5��������( 1, ( (3,4,5) )
	JunAndJuns.clear();
	JunAndPipes.clear();
	LengthMap.clear();
	IteratorPtr<Component> JunItPtr( ComManager.CreatJunIterator() );
	for( JunItPtr->Fist(); !JunItPtr->IsDone(); JunItPtr->Next() )
    {
		iCountOfJuns++;
		CloseJuns.clear();
		ClosePipes.clear();
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
				ClosePipes.push_back( pPipe->GetKey() );
			}
			if( pPipe->EndJun() == pJun->GetKey() )	
			{
				CloseJuns.push_back( pPipe->StartJun() );
				ClosePipes.push_back( -1 * pPipe->GetKey() );
			}
		}
		JunAndJuns.insert( CirMatrix::value_type( pJun->GetKey(), CloseJuns ) );
		JunAndPipes.insert( CirMatrix::value_type( pJun->GetKey(), ClosePipes ) );
	}

	ComMap::iterator CloseJunsIt;
	ComMap* pJunVector = NULL;
	CirMatrix::iterator JunsIt;
	ComMap::iterator ClosePipesIt;
	ComMap* pJunAndPipeVector = NULL;
	CirMatrix::iterator JunsAndPipesIt;
	double dTempLength = 0.0; // �����ݴε�����
	
	// ����ܵ����ȵ��ݴε���
	IteratorPtr<Component> PipeItPtr( ComManager.CreatPipeIterator() );
	for( PipeItPtr->Fist(); !PipeItPtr->IsDone(); PipeItPtr->Next() )
	{
		pPipeComponent = &PipeItPtr->CurrentItem();
		pPipe = dynamic_cast<Pipe*>( pPipeComponent );
		OptData.GetProperty( pPipe->GetKey(), 2, dTemp );
		if( !( 1e-6 < fabs( dTemp - 1e-6 ) ))
		{
			return false;
		}
		dTemp = pow( dTemp, -1.0 * dLengthFactor );
		LengthMap.insert( map< int, double >::value_type( abs( pPipe->GetKey() ), dTemp ) );
	}

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
		JunsAndPipesIt = JunAndPipes.find( pJun->GetKey() );
 	    pJunVector = ( ComMap* ) &( JunsIt->second );
		pJunAndPipeVector = ( ComMap* ) &( JunsAndPipesIt->second );



		// �ڵ��ϵ��
		for( ClosePipesIt = pJunAndPipeVector->begin(); pJunAndPipeVector->end() != ClosePipesIt; ClosePipesIt++ )
		{
			map< int, double >::iterator TempIt = LengthMap.find( abs( *ClosePipesIt ) );
			dTemp += TempIt->second;
		}
		//ModulusVector[ pJun->GetKey() - 1 ] = dTemp;                      // ÿ���ڵ��ϵ��
		ModulusVector[ pJun->GetKey() - 1 ] = pJunAndPipeVector->size();
		
		// �����ڵ��ϵ��
		for( CloseJunsIt = pJunVector->begin(); CloseJunsIt != pJunVector->end(); CloseJunsIt++ )
		{
			for( PipeItPtr->Fist(); !PipeItPtr->IsDone(); PipeItPtr->Next() )
			{
				pPipeComponent = &PipeItPtr->CurrentItem();
		        pPipe = dynamic_cast<Pipe*>( pPipeComponent );
				if( ( pPipe->StartJun() == pJun->GetKey() ) && ( pPipe->EndJun() == *CloseJunsIt ) )
				{
					dTemp = -1 * pow( pPipe->Len(), -1.0 * dLengthFactor );
					break;
				}
				if( ( pPipe->EndJun() == pJun->GetKey() ) && ( pPipe->StartJun() == *CloseJunsIt ) )
				{
					dTemp = pow( pPipe->Len(), -1.0 * dLengthFactor );
					break;
				}
			}
			//ModulusVector[ abs( *CloseJunsIt ) - 1 ] = dTemp;
			ModulusVector[ abs( *CloseJunsIt ) - 1 ] = -1;
		}

		OptData.GetProperty( pJun->GetKey(), 3, ModulusVector[ iCountOfJuns ] );     // �ڵ�Ľڵ����� ,����Ϊ��������Ϊ��
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
	
	/*
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
	*/

	// ���ùܵ�������
	for( PipeItPtr->Fist(); !PipeItPtr->IsDone(); PipeItPtr->Next() )
	{
		pPipeComponent = &PipeItPtr->CurrentItem();
		pPipe = dynamic_cast<Pipe*>( pPipeComponent );
		DumIt = DummyFluxMap.find( pPipe->StartJun() );
		dStartDummyFlux = DumIt->second;
		DumIt = DummyFluxMap.find( pPipe->EndJun() );
		dEndDunmmyFlux = DumIt->second;
		dEndDunmmyFlux = dStartDummyFlux - dEndDunmmyFlux;
		if( ( 0 <= iFluxType ) && ( 1 >= iFluxType ) )
		{
			OptData.SetProperty( pPipe->GetKey(), iFluxType, dEndDunmmyFlux );
		}
		
	}
	return true;
}


// �ý��淨����������
bool CMinimumSquareSum::InitializeDummyFlux( ComponentManager& ComManager, PFAOptimitationData& OptData )
{
	int iCountOfJuns = ComManager.GetJunNum();          // �ڵ������
	
	// ��������������������ˮԴ�����ܺ�
	double dFluxSummation = 0.0;
	double dTem = 0.0;
	int iKeyOfJu = 0;
	int k = 0;
	for( k = 1; k <= iCountOfJuns; k++ )
	{
		
		{
			OptData.GetProperty( k, 3, dTem );
		    dFluxSummation += dTem;
		}
	}
    /*
	map< int, vector< double > >::iterator IntVecMapIt = ModulusMatrix.begin();
	for( ; IntVecMapIt != ModulusMatrix.end(); IntVecMapIt++ )
	{
		( IntVecMapIt->second )[ iCountOfJuns ] /= dFluxSummation; 
	}

	//GaussMethod( ModulusMatrix, Variance, ResultMap );
	if( !CholeskyMethod( ModulusMatrix, ResultMap ) )
	{
		return false;
	}
	SetInitializePipeFlux( 0, ComManager, ResultMap, OptData );

   */

	/////////////////////////////
	map< int, vector< int > > JunAndPipesMap;   // <�ڵ㣬<��ڵ������Ĺܵ�> >
	vector< int > PipesVector;                  // <��ڵ������Ĺܵ�>	
	int i = 0;
	double dTemp = 0.0;
	Component* pComponent = NULL;
	Pipe* pPipe = NULL;
	Jun* pJun = NULL;
	IteratorPtr<Component> JunItPtr( ComManager.CreatJunIterator() );
	JunAndPipesMap.clear();
	for( JunItPtr->Fist(); !JunItPtr->IsDone(); JunItPtr->Next() )
    {
		PipesVector.clear();
		pComponent = &JunItPtr->CurrentItem();
		pJun = dynamic_cast<Jun*>( pComponent );
		IteratorPtr<Component> PipeItPtr( ComManager.CreatPipeIterator() );
		for( PipeItPtr->Fist(); !PipeItPtr->IsDone(); PipeItPtr->Next() )
		{
			pComponent = &PipeItPtr->CurrentItem();
			pPipe = dynamic_cast<Pipe*>( pComponent );
			if( pPipe->StartJun() == pJun->GetKey() )
			{
				PipesVector.push_back( pPipe->GetKey() );
			}
			if( pPipe->EndJun() == pJun->GetKey() )
			{
				PipesVector.push_back( -pPipe->GetKey() );
			}
		}
		JunAndPipesMap.insert( map< int, vector< int > >::value_type( pJun->GetKey(), PipesVector ) );
		
	}

	vector< int > FindJunVector;                // Ҫ��Ѱ�ĵ�  
	vector< int > TempFindJunVector;            // �����洢Ҫ��Ѱ�ĵ�
	vector< int > FindPipeVector;                   // Ҫ�����������Ĺܵ�
	vector< int > AllPipesVector;               // ���йܶμ��ϣ������ж������������Ƿ�ɹ�
	
	// ���Ȱ����йܵ�������AllPipesVector
	AllPipesVector.clear();
	int iKeyOfPipe = 0;
	for( i = 0; i < OptData.GetPropertyCount( 102 ); i++ )
	{
		OptData.GetProperty( i, 102, iKeyOfPipe );
		AllPipesVector.push_back( abs( iKeyOfPipe ) );           
	}

	map< int, vector< int > >::iterator IntVecMapIt;
	vector< int >::iterator IntVecIt;
	vector< int >::iterator FindIntVecIt;
	vector< int >::iterator TempIntVecIt;
	int iKeyOfJun = 0;
	int iCountOfPipe = 0;

	// ����ˮԴ�ڵ��ʼ��FindJunVector
	FindJunVector.clear();
	for( i = 0; i < OptData.GetPropertyCount( 200 ); i++ )
	{
		OptData.GetProperty( i, 200, iKeyOfJun );
		FindJunVector.push_back( abs( iKeyOfJun ) );
	}

	TempFindJunVector.clear();
	while( 0 != FindJunVector.size() )
	{
		iCountOfPipe = 0;
		FindPipeVector.clear();
	    FindIntVecIt = FindJunVector.begin();
	    for( ; FindJunVector.end() != FindIntVecIt; FindIntVecIt++ )
		{
		    IntVecMapIt = JunAndPipesMap.find( abs( *FindIntVecIt ) );
	    	IntVecIt = IntVecMapIt->second.begin();
		    for( ; IntVecMapIt->second.end() != IntVecIt; IntVecIt++ )
			{
		    	TempIntVecIt = find( AllPipesVector.begin(), AllPipesVector.end(), abs( *IntVecIt ) );   // �����㷨
		    	if( AllPipesVector.end() != TempIntVecIt )                 // ����ܵ�֮ǰδ����������
				{
			    	iCountOfPipe++;
			    	AllPipesVector.erase( TempIntVecIt );   // ɾ���ܵ�����������ܵ��Ѵ���
					FindPipeVector.push_back( abs( *IntVecIt ) );            // �ѽ�Ҫ�����������Ĺܵ�����FindPipeVector

					// �ѹܵ�����һ���ڵ����TempFindJunVector��Ϊ��һ��FindJunVector������������׼��
					// ���ܻ���Ѿ��߹��Ľڵ�Ҳ������TempFindJunVector��������Ӱ�����������Ϊ�߹��ڵ�����ڹܵ�����AllPipesVector��
					pPipe = ComManager.LookUpPipe( abs( *IntVecIt ) );
					if( pPipe->StartJun() == *FindIntVecIt )
					{
						TempFindJunVector.push_back( abs( pPipe->EndJun() ) );
					}
					if( pPipe->EndJun() == *FindIntVecIt )
					{
						TempFindJunVector.push_back( abs( pPipe->StartJun() ) );
					}
				}
			}
		}
		
		// ��FindPipeVector�еĹܵ�������������ֵΪ1/TempFindJunVectorԪ�ظ���,��1/iCountOfPipe
		if( 0 != iCountOfPipe )   
		{
			FindIntVecIt = FindPipeVector.begin();
			dTemp = 1.0 / ( ( double )iCountOfPipe );
			for( ; FindPipeVector.end() != FindIntVecIt; FindIntVecIt++ )
			{		
				OptData.SetProperty( *FindIntVecIt, 0, dTemp );
			}			
		}

		// ��TempFindJunVector����FindJunVector��
		FindJunVector.clear();
		FindIntVecIt = TempFindJunVector.begin();
		for( ; TempFindJunVector.end() != FindIntVecIt; FindIntVecIt++ )
		{
			FindJunVector.push_back( abs( *FindIntVecIt ) );
		}
		TempFindJunVector.clear();
	}
	
	if( 0 != AllPipesVector.size() )                 // �ܵ�û����ȫ����
	{
		FindIntVecIt = AllPipesVector.begin();
		return false;
	}
	

	for( i = 0; i < OptData.GetPropertyCount( 102 ); i++ )
	{
		OptData.GetProperty( i, 102, iKeyOfPipe );
		OptData.GetProperty( iKeyOfPipe, 0, dTemp );
	}
	return true;
}


bool CMinimumSquareSum::InitializeFactFlux( ComponentManager& ComManager, PFAOptimitationData& OptData )
{
	double Variance = 0.0001;                              // ���ȿ���
	map< int, double > ResultMap;                         // �������
	map< int, vector< double > > ModulusMatrix;
	InitializeModulusMatrix( ComManager, OptData, ModulusMatrix );
	//GaussMethod( ModulusMatrix, Variance, ResultMap );
	if( !CholeskyMethod( ModulusMatrix, ResultMap ) )
	{
		return false;
	}
	SetInitializePipeFlux( 1, ComManager, ResultMap, OptData );
	return true;
}


////////////////////////////////////////////////////////////////
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


////////////////////////////////////////////////////////////////////////////////////////////
// Cholesky������������һά���Է����飬Ҫ������Ƿ�����Գƾ��󣬱ȸ�˹��Ԫ������ֵ�ȶ���Ҫ��

bool CMinimumSquareSum::Chobsb(double a[], int n, double d[], double b[])
{
	int i,j;
	double sum;
    for (i = 1; i<=n; i++)
	{
        sum = b[i];
        for (j = 1; j<=i - 1; j++)
		{
            sum = sum - a[(i-1)*n+j] * b[j];
        }
        b[i] = sum;
    }
    for (i = n; i>=1; i--)
	{
        if (d[i] == 0.0)
		{
            return false;
		}
        else
		{
            sum = b[i] / d[i];
        }
        for (j = i + 1; j<=n; j++)
		{
            sum = sum - a[(j-1)*n+i] * b[j];
        }
        b[i] = sum;
    }
	return true;
}

bool CMinimumSquareSum::Chodcm(double a[], int n, double d[], double t[])
{
	bool bFlag = true;
	int i,j,k;
	double sum;
    for (i = 1; i<=n; i++)
	{
        sum = a[(i-1)*n+i];
        for (j = 1; j<=i - 1; j++)
		{
            t[j] = a[(j-1)*n+i];
            for (k = 1; k<=j - 1; k++)
			{
                t[j] = t[j] - t[k] * a[(j-1)*n+k];
            }
            if (d[j] == 0.0)
			{
                if (t[j] != 0.0)
				{
                    bFlag = false;
				}
                else
				{
                    a[(i-1)*n+j] = 1.0;
                }
			}
            else
			{
                a[(i-1)*n+j] = t[j] / d[j];
            }
            sum = sum - t[j] * a[(i-1)*n+j];
        }
        d[i] = sum;
    }
	return bFlag;
}

// NΪ���������ں������Զ��ѵ�һ�е�һ��ʡ����
bool CMinimumSquareSum::CholeskyMethod( map< int, vector< double > >& ModulusMatrix, map< int, double >& ResultMap )
{
	ASSERT( NULL != &ModulusMatrix );

	bool bFlag = true;
	int iNumber = ModulusMatrix.size(); 
	int i = 0;
	int j = 0;

	// �ұ߳�������
	map< int, vector< double > >::iterator ConstIntVecMapIt = ModulusMatrix.begin();
	vector< double >::iterator ConstDouVecIt;
	double* pB = new double[iNumber];	// �ұ���������������ڴ�������
	for( i = 1; i <= iNumber; i++ )
	{
		const vector< double >* pDouVec = &( ConstIntVecMapIt->second );	
		*(pB + i - 1) = pDouVec->back();
		ConstIntVecMapIt++;
	}

	// ��Ϊֻ��J-1���������̣�����ȥ����һ�к͵�һ��,pCҲ�Ǵ�1��ʼ
	double* pC = new double[( iNumber - 1 ) * ( iNumber - 1 ) + 1];    // ������Ԫ�� ���δ��A�е�Ԫ��
	ConstIntVecMapIt = ModulusMatrix.begin();
	ConstIntVecMapIt++;                        // ȥ����һ��
	for( i = 1; i < iNumber; i++, ConstIntVecMapIt++ )
	{
		ConstDouVecIt = ConstIntVecMapIt->second.begin();
		ConstDouVecIt++;                       // ȥ����һ��
		for( j = 1; j < iNumber; j++, ConstDouVecIt++ )
		{
			*( pC + ( i - 1 ) * ( iNumber - 1 ) + j) = *ConstDouVecIt;
		}
	}
	
	// �ⷽ���飬���������pB��
	double* pD = new double[iNumber];    // ��ŷֽ��жԽǾ���D�ĶԽ�Ԫ��
	double* pT = new double[iNumber];    // ������Ԫ
	if( !Chodcm( pC, iNumber - 1, pD, pT ) )
	{
		return false;
	}
	if( !Chobsb( pC, iNumber - 1, pD, pB ) )
	{
		return false;
	}

	// �����һ�еĽ�
	ConstIntVecMapIt = ModulusMatrix.begin();
	double dTempFlux = ConstIntVecMapIt->second.back();
	double dTemp = dTempFlux;
	vector< double >::iterator DouVecIt = ConstIntVecMapIt->second.begin();
	DouVecIt++;                              
	for( i = 1; i < iNumber; i++, DouVecIt++ )
	{	
		dTemp = dTemp - ( *DouVecIt ) * pB[i];
	}
	
	ConstDouVecIt = ConstIntVecMapIt->second.begin();
	dTemp = dTemp / *ConstDouVecIt;
	pB[0] = dTemp;

	// �ѽ������ResultMap
	ResultMap.clear();
	for( i = 0; i < iNumber; i++ )
	{
		ResultMap.insert( map< int, double >::value_type( i + 1, pB[i] ) );
	}

	// �����ڴ�
	delete[] pB;
	delete[] pC;
	delete[] pD;
	delete[] pT;
	
	return true;
}

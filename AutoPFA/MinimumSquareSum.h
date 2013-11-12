// MinimumSquareSum.h: interface for the CMinimumSquareSum class.
//
//////////////////////////////////////////////////////////////////////
/************************************************************************
�汾: 8.0       ����ʱ��: 2008/05/31  ����: COM 

����: ������ʼ���е���Сƽ���ͷ���,�����и�˹����Ԫ���� Cholesky��,�����ѡ����Cholesky
                                                                                                                                         
************************************************************************/


#if !defined(AFX_MINIMUMSQUARESUM_H__C94D9225_38C9_4B44_9CF5_003057D18ABA__INCLUDED_)
#define AFX_MINIMUMSQUARESUM_H__C94D9225_38C9_4B44_9CF5_003057D18ABA__INCLUDED_

#include <map>
#include "ComponentManager.h"
#include "PFAOptimitationData.h"
using namespace std;
typedef map< int, double > IntDoubleMap;

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMinimumSquareSum  
{
public:
	CMinimumSquareSum();
	virtual ~CMinimumSquareSum();

    bool InitializeDummyFlux( ComponentManager& ComManager, PFAOptimitationData& OptData );
	bool InitializeFactFlux( ComponentManager& ComManager, PFAOptimitationData& OptData );
private:

	// �����Է���������ȡϵ�����ŵ�ϵ������ModulusMatrix��
	bool InitializeModulusMatrix( ComponentManager& ComManager, PFAOptimitationData& OptData, map< int, vector< double > >& ModulusMatrix );
    
	// ������Сƽ���ͷ�����õĳ�ʼ����������PFAOptimitationData& OptData��
	bool SetInitializePipeFlux( const int& iFluxType, ComponentManager& ComManager, IntDoubleMap& DummyFluxMap, PFAOptimitationData& OptData );
	
	// ��˹����Ԫ��, ��һ���ľ�����
	bool GaussMethod( const map< int, vector< double > >& ModulusMatrix , const double& dVariance, map< int, double >& ResultMap );

	// Cholesky��,������Գ�ϡ����������, ���÷�Χ�ȸ�˹����Ԫ����
	bool CholeskyMethod( map< int, vector< double > >& ModulusMatrix, map< int, double >& ResultMap );

	void MatrixInvers( double **pMatrix, int RowSize, int ColumnSize);
	bool VanishElement( double **pMatrix, int RowSize, int ColumnSize, double Var );
	void InputMatrix( const map< int, vector< double > >& ModulusMatrix, double **pMatrix );
	void OutputMatrix( double **pMatrix, const int& Size, vector< double >& ResultVector);

	bool Chobsb(double a[], int n, double d[], double b[]);
	bool Chodcm(double a[], int n, double d[], double t[]);
};

#endif // !defined(AFX_MINIMUMSQUARESUM_H__C94D9225_38C9_4B44_9CF5_003057D18ABA__INCLUDED_)

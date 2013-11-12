// PFAOptimize.h: interface for the CPFAOptimize class.
//
//////////////////////////////////////////////////////////////////////


#pragma once
#include "ComponentManager.h"
#include <algorithm>
#include <math.h>
#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include "PFAOptimitationData.h"
#include "Progress.h"
 
using namespace std;
typedef vector<int> ComMap;
typedef map< int, ComMap > CirMatrix;
typedef vector< pair< int, CPoint > > JunAndCenter;
typedef map< int, JunAndCenter > ComAndCloseComs; 
enum BaseCircleDirection{ DEASIL_DIRECTION = 1, ANTICLOCKWISE_DIRECTION };
const CString COMPARTMENTATION = "#";



#if !defined(AFX_PFAOPTIMIZE_H__2247B5DD_77CB_40A2_B446_829CC1710856__INCLUDED_)
#define AFX_PFAOPTIMIZE_H__2247B5DD_77CB_40A2_B446_829CC1710856__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CPFAOptimize  
{
public:
	CPFAOptimize();
	virtual ~CPFAOptimize();
	void FindJunOfCircle( Jun& PreJun, Jun& NextJun, ComAndCloseComs&  JunAndCloseJuns, int& iKeyOfChoiceJun );
    BOOL FindBaseCircle( ComponentManager& ComManager, Pipe& BasePipe, BaseCircleDirection Direction, ComMap& JunKeyMap, ComMap& PipeKeyMap, int iMostCircle[] );
	void CopyVector( JunAndCenter& DestinationVector, JunAndCenter& SourceVector );
	BOOL JudgeMaxCircle( ComMap& JunKeyMap, int iMostCircle[], vector< CString >& JunPointGather, CString& strMaxCircle );
	void JunSystemTransformCircleSystem( ComponentManager& ComManager, PFAOptimitationData& OptData );
	void DisplayMatrix( const CString& strFileDirectory, const int& iProperty, PFAOptimitationData& OptData );
	void Example();
	void GetAngle( const double& dX, const double& dY, double& dAngle );
    bool CalOthersVariable( ComponentManager& ComManager, PFAOptimitationData& OptData );
	PFAOptimitationData* GetOptDataPointer();
	
	PFAOptimitationData OptData;

private:
	// �ѽڵ���Ϣ��������OptData
	bool InsertCircleMatrix( const int& iKeyOfCircle, const int& iProperty, ComMap& ComponentKeyMap, PFAOptimitationData& OptData );
		
	// ����ܵ�-������Ϊ��������У������׼��
	bool InitializePipeCircle( PFAOptimitationData& OptData );
	
	// ���·��,Dijkstra�㷨
	bool FindShortCut( ComponentManager& ComManager, const int& iKeyOfStartJun, const int& iKeyOfEndJun, vector< int >& JunToJunPipePath );
	bool SetProperties( vector< int >& IntVector, const int& iPosition, const int& iValue );
	int GetProperties( const vector< int >& IntVector, const int& iPosition );
	bool SetProperties( map< int, vector< int > >& IntVecMap, const int& iRow, const int& iLine, const int& iValue );
	int GetProperties( const map< int, vector< int > >& IntVecMap, const int& iRow, const int& iLine );
	
	// ţ�ٵ�������¶������-κ�ع�ʽ
	bool ColebrookNewton( const double& dAbsoluteRoughness, const double& dDiameter, const double& dRe, double& dResult );

	// �ж�ǰ�����ܾ��Ƿ����
	bool DiameterIsEqual( PFAOptimitationData& OptData, map< int, double >& BeforeDiameterMap );

	// ����ܵ��պϲ�
	bool CalPipeCloseSubtract( ComponentManager& ComManager, PFAOptimitationData& OptData, map< int, double >& OptimitationParameterMap, map< int, double >& OptimitationAssistantMap );
	
	bool CalDummyFlux( const double& dDummyPrecision, PFAOptimitationData& OptData );
	double CalStdDiameter( const double& dCalDiameter );
	bool DoOptimitation( ComponentManager& ComManager, PFAOptimitationData& OptData );

	// �����Ż�֮ǰ��һЩ����
	bool DisposeManager(  const PFAOptimitationData& OptData, ComponentManager& ComManager );

	// ��ʾ���
	bool DisplayResult( PFAOptimitationData& OptData );

	CProgress m_ProGress;    // ������
};


inline PFAOptimitationData* CPFAOptimize::GetOptDataPointer()
{
	return &OptData;
}
#endif // !defined(AFX_PFAOPTIMIZE_H__2247B5DD_77CB_40A2_B446_829CC1710856__INCLUDED_)

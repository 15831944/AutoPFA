// PFAOptimize.h: interface for the CPFAOptimize class.
// 
//////////////////////////////////////////////////////////////////////
/************************************************************************
�汾: 8.0         ����ʱ��: 2008/06  ����: COM
 
����: �Ż�ģ�飬�������йܵ�ģ����Ż��������㷨��˼·�ɲο����������ˮ���̳�����ƣ���������                                                                                                                                             
************************************************************************/


#include "ComponentManager.h"
#include <algorithm>
#include <math.h>
#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include "PFAOptimitationData.h"
#include "DlgOptProGress.h"
//#include "OptResult.h"
 
using namespace std;
typedef vector<int> ComMap;
typedef map< int, ComMap > CirMatrix;
typedef vector< pair< int, CPoint > > JunAndCenter;
typedef map< int, JunAndCenter > ComAndCloseComs; 




#if !defined(AFX_PFAOPTIMIZE_H__2247B5DD_77CB_40A2_B446_829CC1710856__INCLUDED_)
#define AFX_PFAOPTIMIZE_H__2247B5DD_77CB_40A2_B446_829CC1710856__INCLUDED_



#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
enum BaseCircleDirection{ DEASIL_DIRECTION = 1, ANTICLOCKWISE_DIRECTION };

class CPFAOptimize  
{
public:
	CPFAOptimize();
	virtual ~CPFAOptimize();

	// Ѱ�һ�������һ���ڵ�
	void FindJunOfCircle( Jun& PreJun, Jun& NextJun, ComAndCloseComs&  JunAndCloseJuns, int& iKeyOfChoiceJun );
    
	// �ҳ������ܵ�BasePipe��˳ʱ�����ʱ�������ע�����ڻ�ֻ�ܴӵ�ˮԴ�޷�֧�������ҳ���
	BOOL FindBaseCircle( ComponentManager& ComManager, Pipe& BasePipe, BaseCircleDirection Direction, ComMap& JunKeyMap, ComMap& PipeKeyMap, int iMostCircle[] );
	
	void CopyVector( JunAndCenter& DestinationVector, JunAndCenter& SourceVector );
	
	// �ж��Ƿ�����󻷣���������Ļ�
	BOOL JudgeMaxCircle( ComMap& JunKeyMap, int iMostCircle[], vector< CString >& JunPointGather, CString& strMaxCircle );
	
	// ��Ϣ��¼��ʽת��
	void JunSystemTransformCircleSystem( ComponentManager& ComManager, PFAOptimitationData& OptData );
	
	void DisplayMatrix( const CString& strFileDirectory, const int& iProperty, PFAOptimitationData& OptData );
	bool Example();
	void GetAngle( const double& dX, const double& dY, double& dAngle );
    bool CalOthersVariable( ComponentManager& ComManager, PFAOptimitationData& OptData );
	PFAOptimitationData* GetOptDataPointer();
	


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


	// ����ܵ��պϲ�
	bool CalPipeCloseSubtract( ComponentManager& ComManager, PFAOptimitationData& OptData, map< int, double >& OptimitationParameterMap, map< int, double >& OptimitationAssistantMap );
	
	bool CalDummyFlux( const double& dDummyPrecision, PFAOptimitationData& OptData );
	double CalStdDiameter( const double& dCalDiameter );
	bool DoOptimitation( ComponentManager& ComManager, PFAOptimitationData& OptData );

	bool DisplayResult( PFAOptimitationData& OptData );
	CDlgOptProGress m_DlgOptProGress;    // ������
	PFAOptimitationData OptData;
};


inline PFAOptimitationData* CPFAOptimize::GetOptDataPointer()
{
	return &OptData;
}
#endif // !defined(AFX_PFAOPTIMIZE_H__2247B5DD_77CB_40A2_B446_829CC1710856__INCLUDED_)

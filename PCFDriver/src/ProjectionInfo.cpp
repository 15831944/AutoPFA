// ProjectionInfo.cpp: implementation of the ProjectionInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ProjectionInfo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ProjectionInfo::ProjectionInfo()
{
	Set_X_YZPlaneProjection( 0.05 ) ;
	m_dAddScale = 1.0 ;
}

ProjectionInfo::~ProjectionInfo()
{

}
void ProjectionInfo::operator = ( const ProjectionInfo& prjInfo) 
{
	m_vPalneNormal   = prjInfo.m_vPalneNormal     ;//ͶӰ��ķ��� 
	m_vProjectionDir = prjInfo.m_vProjectionDir    ;//ͶӰ����
	m_plProjPlane    = prjInfo.m_plProjPlane       ;//ͶӰ��
	m_dScale         = prjInfo.m_dScale            ;//����
	m_vPrimaryDir    = prjInfo.m_vPrimaryDir       ;//ת��ǰ�ĳ�ʼ����
	m_vTargetDir     = prjInfo.m_vTargetDir        ;//ת�����ȷ������	
	m_plTargerPlane  = prjInfo.m_plTargerPlane     ;//ת�����Ŀ��ƽ�� 

	m_mtProjMatrix   = prjInfo.m_mtProjMatrix      ;//ͶӰ�任����		
	m_mtToTargetPlane= prjInfo.m_mtToTargetPlane   ;//��ͶӰƽ��ת����Ŀ��ƽ��ľ��� 
	m_mtTransform    = prjInfo.m_mtTransform       ;//��ͶӰƽ��ת����Ŀ��ƽ��ľ��� 

}
void ProjectionInfo::SetScale( const double dScale )
{
	m_dScale = dScale ;
	InitMatrix() ;

}
const double ProjectionInfo::GetScale() 
{
	return m_dScale ;
}

void ProjectionInfo::SetAdditionalScale( const double dAddScale )
{
	m_dAddScale = dAddScale ;
	InitMatrix() ;

}
const double  ProjectionInfo::GetAdditionalScale()
{
	return m_dAddScale  ;
}
//ͶӰ���� 
const AcGeVector3d& ProjectionInfo::GetProjectionNormal()
{
	return m_vProjectionDir ;
}
const AcGeVector3d& ProjectionInfo::GetPlaneNormal()
{
	return m_vPalneNormal ;
}

//ͶӰ����
const AcGeMatrix3d& ProjectionInfo::GetProjectionMatrix()
{
	return m_mtProjMatrix ;
}
//��Ŀ��ƽ���ת������
const AcGeMatrix3d& ProjectionInfo::GetToTargetPlaneMatrix()
{
	return m_mtToTargetPlane ;
}

//����ת������
const AcGeMatrix3d& ProjectionInfo::GetTransformMatrix()
{
	return m_mtTransform ;
}
//�õ�ͶӰƽ��
const AcGePlane& ProjectionInfo::GetProjectionPlane()
{
	return m_plProjPlane ;
}
//�õ�Ŀ��ƽ��	
const AcGePlane& ProjectionInfo::GetTargetPlane() 
{
	return m_plTargerPlane ;
}
void ProjectionInfo::SetXYPlaneProjection( const double   dScale , const AcGePoint3d& ptCenter )
{
	AcGeVector3d vPrjNormal(0 , 0 , -1) ;
	AcGeVector3d vPalneNormal = - vPrjNormal ;
	AcGePlane plane( ptCenter , vPalneNormal ) ;
	SetProject( vPrjNormal , plane , dScale ,
		AcGeVector3d(1 , 0 , 0) ,
		AcGeVector3d(1 , 0 , 0)) ;
}
void ProjectionInfo::SetYZPlaneProjection( const double   dScale , const AcGePoint3d& ptCenter )
{
	AcGeVector3d vPrjNormal(-1 , 0 , 0) ;
	AcGeVector3d vPalneNormal = - vPrjNormal ;
	AcGePlane plane( ptCenter , vPalneNormal ) ;
	SetProject( vPrjNormal , plane , dScale ,
		AcGeVector3d(0 , 1 , 0) ,
		AcGeVector3d(0 , 1 , 0)) ;
	
}
void ProjectionInfo::SetZXPlaneProjection( const double   dScale , const AcGePoint3d& ptCenter )
{
	AcGeVector3d vPrjNormal(0 , 0 , -1) ;
	AcGeVector3d vPalneNormal = - vPrjNormal ;
	AcGePlane plane( ptCenter , vPalneNormal ) ;
	SetProject( vPrjNormal , plane , dScale ,
		AcGeVector3d(0 , 0 , 1) ,
		AcGeVector3d(0 , 0 , 1)) ;
}

void ProjectionInfo::SetXYZPlaneProjection( const double   dScale , const AcGePoint3d& ptCenter )
{
	AcGeVector3d vPrjNormal(-1 , -1 , -1) ;
	AcGeVector3d vPalneNormal = - vPrjNormal ;
	AcGePlane plane( ptCenter , vPalneNormal ) ;
	SetProject( vPrjNormal , plane , dScale ,
		AcGeVector3d(0 ,0 ,1) ,
		AcGeVector3d(0 , 1 , 0)) ;
}

void ProjectionInfo::Set_XYZPlaneProjection( const double   dScale , const AcGePoint3d& ptCenter )
{
	AcGeVector3d vPrjNormal( 1 , -1 , -1) ;
	AcGeVector3d vPalneNormal = - vPrjNormal ;
	AcGePlane plane( ptCenter , vPalneNormal ) ;
	SetProject( vPrjNormal , plane , dScale ,
		AcGeVector3d(0 , 0 , 1) ,
		AcGeVector3d(0 , 1 , 0)) ;
}

void ProjectionInfo::SetX_YZPlaneProjection( const double   dScale , const AcGePoint3d& ptCenter )
{
	AcGeVector3d vPrjNormal( -1 , 1 , -1) ;
	AcGeVector3d vPalneNormal = - vPrjNormal ;
	AcGePlane plane( ptCenter , vPalneNormal ) ;
	SetProject( vPrjNormal , plane , dScale ,
		AcGeVector3d(0 , 0 , 1) ,
		AcGeVector3d(0 , 1 , 0)) ;
}

void ProjectionInfo::Set_X_YZPlaneProjection( /*const*/ const double  dScale , const AcGePoint3d& ptCenter )
{
	AcGeVector3d vPrjNormal( 1 , 1 , -1) ;
	AcGeVector3d vPalneNormal = - vPrjNormal ;
	AcGePlane plane( ptCenter , vPalneNormal ) ;
	SetProject( vPrjNormal , plane , dScale ,
		AcGeVector3d(0 , 0 , 1) ,
		AcGeVector3d(0 , 1 , 0)) ;
}

/***********************************************************************
/* ����ͶӰ�������Ϣ��ʵ�����ά�ռ�ͶӰ��ͶӰƽ��Ȼ����ת����Ŀ��ƽ��                                                                 
***********************************************************************/
void ProjectionInfo::SetProject( const AcGeVector3d& vProjectionNormal ,
								 const AcGePlane&    plProjectPlane    , 
								 const double        dScale            ,
								 const AcGeVector3d& vPrimaryDir       , 
								 const AcGeVector3d& vTargetDir        ,
								 const AcGePlane&    plTargetPlane     )

{
	m_vProjectionDir    = vProjectionNormal ;
	m_plProjPlane       = plProjectPlane    ;
	m_dScale            = dScale            ;
	m_vPrimaryDir       = vPrimaryDir       ;
	m_vTargetDir        = vTargetDir        ;
	m_plTargerPlane     = plTargetPlane     ;
	m_vPalneNormal      = plProjectPlane.normal() ;
	InitMatrix() ;

}

void ProjectionInfo::InitMatrix()
{
	ASSERT( m_dScale > 0 ) ;
	//ͶӰ����
	AcGeMatrix3d mtProjMatrix = AcGeMatrix3d::projection( m_plProjPlane , m_vProjectionDir ) ;

	//��ͶӰƽ���ƽ�ƾ���
	AcGeVector3d vTranslation;
	vTranslation = m_plProjPlane.pointOnPlane().asVector();
	AcGeMatrix3d mtTranslation;
	mtTranslation = mtTranslation.translation( -vTranslation );

	//��תƽ�浽Ŀ��ƽ��ı仯����
	AcGeMatrix3d mtRotation;
	AcGeVector3d vProjPlaneNormal   = m_plProjPlane.normal();
	AcGeVector3d vTargetPlaneNormal = m_plTargerPlane.normal();
	mtRotation = vProjPlaneNormal.rotateTo( vTargetPlaneNormal, 
		vProjPlaneNormal.crossProduct( vTargetPlaneNormal ) );
	mtRotation = mtRotation * mtTranslation ;

	//ת������
	if ( !m_vPrimaryDir.isZeroLength() && 
		 !m_vPrimaryDir.isParallelTo( m_vProjectionDir ) && 
		 m_vTargetDir.isPerpendicularTo( vTargetPlaneNormal ) )
	{
		AcGeVector3d vCurDir = mtRotation*mtProjMatrix * m_vPrimaryDir;
		mtRotation = vCurDir.rotateTo( m_vTargetDir, vCurDir.crossProduct( m_vTargetDir ) ) * mtRotation;
	}

	vTranslation = m_plTargerPlane.pointOnPlane().asVector();
	mtTranslation = mtTranslation.translation( vTranslation );
	mtRotation = mtTranslation * mtRotation;

	//���÷�������
	m_mtProjMatrix      = mtProjMatrix*AcGeMatrix3d::scaling( m_dScale*m_dAddScale  ) ;
	m_mtToTargetPlane   = mtRotation ;
	m_mtTransform       = m_mtToTargetPlane * m_mtProjMatrix ;
}

void ProjectionInfo::SetPrimaryAndTargetDir(const AcGeVector3d &vPrimary, const AcGeVector3d &vTarget)
{
	m_vPrimaryDir  = vPrimary       ;
	m_vTargetDir   = vTarget        ;
	InitMatrix() ;
}

CArchive& ProjectionInfo::operator <<(CArchive &ar)
{
	AcGeVector3d nVec1,nVec2;
	AcGePoint3d  nPnt;
	ar << m_vPalneNormal  .x << m_vPalneNormal  .y << m_vPalneNormal  .z ;
	ar << m_vProjectionDir.x << m_vProjectionDir.y << m_vProjectionDir.z ;	
	m_plProjPlane.getCoordSystem(nPnt, nVec1, nVec2);
	ar << nPnt .x << nPnt .y << nPnt .z ;
	ar << nVec1.x << nVec1.y << nVec1.z ;
	ar << nVec2.x << nVec2.y << nVec2.z ;
	ar << m_dScale;
	ar << m_dAddScale ;
	ar << m_vPrimaryDir.x << m_vPrimaryDir.y << m_vPrimaryDir.z ;
	ar << m_vTargetDir .x << m_vTargetDir .y << m_vTargetDir .z ;
	m_plTargerPlane.getCoordSystem(nPnt, nVec1, nVec2);
	ar << nPnt .x << nPnt .y << nPnt .z ;
	ar << nVec1.x << nVec1.y << nVec1.z ;
	ar << nVec2.x << nVec2.y << nVec2.z ;
	return ar ;

 }
 
CArchive& ProjectionInfo::operator >>(CArchive &ar)
{
	AcGeVector3d nVec1,nVec2;
	AcGePoint3d  nPnt;
	ar >> m_vPalneNormal  .x >> m_vPalneNormal  .y >> m_vPalneNormal.z  ;
	ar >> m_vProjectionDir.x >> m_vProjectionDir.y >> m_vProjectionDir.z;	
	ar >> nPnt .x >> nPnt .y >> nPnt .z ;
	ar >> nVec1.x >> nVec1.y >> nVec1.z ;
	ar >> nVec2.x >> nVec2.y >> nVec2.z ;
	m_plProjPlane.set(nPnt, nVec1, nVec2);
	ar >> m_dScale;
	ar >> m_dAddScale ;
	ar >> m_vPrimaryDir.x >> m_vPrimaryDir.y >> m_vPrimaryDir.z ;
	ar >> m_vTargetDir .x >> m_vTargetDir .y >> m_vTargetDir .z ;
	ar >> nPnt .x >> nPnt .y >> nPnt .z ;
	ar >> nVec1.x >> nVec1.y >> nVec1.z ;
	ar >> nVec2.x >> nVec2.y >> nVec2.z ;
	m_plTargerPlane.set(nPnt, nVec1, nVec2);
	InitMatrix();
	return ar ;

}


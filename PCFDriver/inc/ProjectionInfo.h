// ProjectionInfo.h: interface for the ProjectionInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROJECTIONINFO_H__B5887CCE_0887_46A9_B146_3A3C6F4DD205__INCLUDED_)
#define AFX_PROJECTIONINFO_H__B5887CCE_0887_46A9_B146_3A3C6F4DD205__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class AFX_EXT_CLASS ProjectionInfo  
{
public:
	ProjectionInfo();
	virtual ~ProjectionInfo();
public:
	void SetXYZPlaneProjection( const double  dScale = 1.0 ,
		                       const AcGePoint3d& ptCenter = AcGePoint3d::kOrigin);
	void Set_XYZPlaneProjection(  const double  dScale = 1.0 ,
		                       const AcGePoint3d& ptCenter = AcGePoint3d::kOrigin);
	void SetX_YZPlaneProjection(  const double  dScale = 1.0 ,
		                       const AcGePoint3d& ptCenter = AcGePoint3d::kOrigin);
	void Set_X_YZPlaneProjection(   const double  dScale = 1.0 ,
		                       const AcGePoint3d& ptCenter = AcGePoint3d::kOrigin);
	void SetXYPlaneProjection(   const double  dScale = 1.0 ,
		                       const AcGePoint3d& ptCenter = AcGePoint3d::kOrigin);
	void SetYZPlaneProjection(  const double  dScale = 1.0 ,
		                       const AcGePoint3d& ptCenter = AcGePoint3d::kOrigin);
	void SetZXPlaneProjection( const double  dScale = 1.0 ,
		                       const AcGePoint3d& ptCenter = AcGePoint3d::kOrigin);

	void SetScale( const double dScale ) ;
	void SetAdditionalScale( const double dAddScale ) ;
	const double GetAdditionalScale() ;
	const double GetScale() ;

	const AcGeMatrix3d& GetProjectionMatrix()   ;//�õ�ת����ͶӰƽ��ľ���
	const AcGeMatrix3d& GetToTargetPlaneMatrix();//�õ���ͶӰƽ��ת����Ŀ��ƽ��ľ���
	const AcGeMatrix3d& GetTransformMatrix()    ;//�õ����յ�ת������	
	const AcGeVector3d& GetProjectionNormal()   ;//�õ�ͶӰ��ķ���
	const AcGeVector3d& GetPlaneNormal()        ;//�õ�ͶӰ��ķ���
	const AcGePlane&    GetProjectionPlane()    ;//�õ�ͶӰ��	
	const AcGePlane&    GetTargetPlane()        ;//�õ�Ŀ��ƽ��	

		
public:
	void operator = ( const ProjectionInfo& prjInfo) ;
	CArchive& operator <<(CArchive &ar);
	CArchive& operator >>(CArchive &ar);

	//���ó�ʼ���������Ŀ��ķ�������Ϊ���ն�λ�����
	void SetPrimaryAndTargetDir(const AcGeVector3d& vPrimary ,
								const AcGeVector3d& vTarget);
	void SetProject( const AcGeVector3d& vProjectionDir, //ͶӰ����
					 const AcGePlane&    plProjectPlane, //ͶӰ��ƽ��
					 const double         dScale        , //����
					 const AcGeVector3d& vPrimaryDir   , //ת��ǰ�ĳ�ʼ����
					 const AcGeVector3d& vTargetDir    , //ת�����ȷ������	
					 const AcGePlane&    plTargetPlane = AcGePlane::kXYPlane );//ת����ƽ��
private:
	void InitMatrix();

private:
	AcGeVector3d m_vPalneNormal      ;//ͶӰ��ķ��� 
	AcGeVector3d m_vProjectionDir    ;//ͶӰ����
	AcGePlane    m_plProjPlane       ;//ͶӰ��
	double       m_dScale            ;//����
	double       m_dAddScale         ;//�������
	AcGeVector3d m_vPrimaryDir       ;//ת��ǰ�ĳ�ʼ����
	AcGeVector3d m_vTargetDir        ;//ת�����ȷ������	
	AcGePlane    m_plTargerPlane     ;//ת�����Ŀ��ƽ�� 

	AcGeMatrix3d m_mtProjMatrix      ;//ͶӰ�任����		
	AcGeMatrix3d m_mtToTargetPlane   ;//��ͶӰƽ��ת����Ŀ��ƽ��ľ��� 
	AcGeMatrix3d m_mtTransform       ;//��ͶӰƽ��ת����Ŀ��ƽ��ľ��� 
};


#endif // !defined(AFX_PROJECTIONINFO_H__B5887CCE_0887_46A9_B146_3A3C6F4DD205__INCLUDED_)

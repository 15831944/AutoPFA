// MOCRelief.cpp: implementation of the MOCRelief class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MOCRelief.h"
#include "MOCFluid.h"
#include "CalcRelief.h"
#include "LocalRStrategy.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MOCRelief::MOCRelief()
{
	m_nType = 0;
	m_nLossType = 0;
	m_dKOrCv = 0;		
	m_bDeltaPress = FALSE;					  
	m_dCrackPress = 0;				      
	m_dExitPress = 0;					   				   
	m_nBasisAreaType = 0;				
	m_dBasisArea = 0;	

	m_dOutFlow = 0;
	m_bCrack = FALSE;
	m_nReliefStatus = 1;

	m_iCalcStatus = -1 ;
}

MOCRelief::~MOCRelief()
{

}

MOCJun* MOCRelief::Creator()
{
	MOCRelief *pData = new MOCRelief;
	return pData;
}

BOOL MOCRelief::Read(CalcJun *pData)
{
	ReadJun(pData);
	CalcRelief *pReliefData = dynamic_cast<CalcRelief*>(pData);
	ASSERT(pReliefData != NULL);
	m_nType = pReliefData->Type();
	m_nLossType = pReliefData->LossType();
	m_dKOrCv = pReliefData->KOrCv();
	m_dCrackPress = pReliefData->CrackPress();				      
	m_dExitPress = pReliefData->ExitPress();
	int nType = pReliefData->PressType();
	if(0==nType || 2 == nType)
	{
		m_dCrackPress = MOCFluid::TranHToPress(m_dCrackPress);				      
		m_dExitPress = MOCFluid::TranHGLToPress( m_dExitPress - m_dOutEle );
	}
	if(2==nType || 3==nType)
		m_bDeltaPress = TRUE;					  			   				   
	m_nBasisAreaType = pReliefData->BasisAreaType();				
	m_dBasisArea = pReliefData->BasisArea();
	m_tranData.Read(pReliefData->m_TranData);
	m_tranData.TranRel(RelToAbs,m_dKOrCv);
	return TRUE;
}

BOOL MOCRelief::InitEndInfo()
{
	//Add by Liuck [4/28/2009] ��ʧKϵ��
	if( 0 == m_nLossType )
	{
		double dArea = BasisArea( m_nBasisAreaType, m_dBasisArea );
		m_dLossK = K( m_dKOrCv, dArea );
	}
	else if ( 1 == m_nLossType )
	{
		m_dLossK = m_dKOrCv ;
	}
	return InitInOutEle();
}

double MOCRelief::GetCurCv()
{
	double dCv = 0;
	return dCv;
}
void MOCRelief::UpdataEnd()
{
	UpdataTwoEnd();
	if(2 == m_nType)
	{
		double dMass = fabs(m_EndList.GetInMass()-m_EndList.GetOutMass());
		m_dBasisArea = BasisArea(m_nBasisAreaType,m_dBasisArea) ;
	    double dStaticPress = m_dExitPress-MOCFluid::CalcPressLoss(dMass,m_dBasisArea);
		UpdataPress(m_dExitPress,dStaticPress,m_dOutEle,m_dOutStagPress,m_dOutStaticPress,m_dOutEGL,m_dOutHGL);
	}
	m_iCalcStatus = -1 ;//����״̬:��ʼ״̬Ϊ-1
}
void MOCRelief::CalcStm()
{
	if(2==JunStatus())
	{//���Ǵ�
		CalcStmOpen(m_dKOrCv);
	}
	else
	{
		EndInfo* pInEnd = GetInEnd() ;
		EndInfo* pOutEnd = GetOutEnd() ;
		double dTempEndPress = m_dExitPress ;

		//�ڳ�ʼ��״̬�£�������ȫ�ص�״̬�������ȫ���ڵ㴦������ѹ����ֵ������������ѹ��ֵ�ۺ�
		//��ȫ���ڵ��������жϸİ�ȫ�����ڴ򿪻��ǹر�״̬
		if ( -1 == m_iCalcStatus )
		{
			ASSERT( pInEnd ) ;
			CalcStmClose();//������ȫ�ص�״̬�������ȫ���ڵ㴦������ѹ����ֵ

			if ( 3 == m_nType )//�ڵ�Ϊ��Ƕ��ȫ��
			{
				ASSERT( pOutEnd ) ;
				//��������ѹ���͵�һ��С���ƻ�ѹ���˳�ѹ���ĺ͵�ʱ����Ƕ��ȫ���رգ��ܵ���ͨ
				if ( ( pInEnd->GetPress() + pOutEnd->GetPress() ) / 2 - m_dExitPress - m_dCrackPress < 1.0e-6 )
				{
					m_iCalcStatus = 0 ;
				}
				else
				{
					m_iCalcStatus = 1 ;
				}
				return ;
			}

			//�ڵ�Ϊ�ڲ���ȫ�����߳��ڰ�ȫ����ʱ��
			if ( NULL != pOutEnd )
			{
				dTempEndPress = pOutEnd->GetPress() ;
			}
			//Modify by Liuck [4/28/2009] ������ѹ��������ѹ��(����ѹ��)�Ĳ��������ѹ����
			//ʱ�򣬰�ȫ������
			if ( fabs( pInEnd->GetPress() - dTempEndPress ) - m_dCrackPress < -1.0e-6 )
			{
				pInEnd->SetZeroMassFlag( TRUE ) ;//����0������ǣ�Ϊ0�����ܵ��������׼��
				if ( NULL != pOutEnd )
				{
					pOutEnd->SetZeroMassFlag( TRUE ) ;//����0������ǣ�Ϊ0�����ܵ��������׼��
				}
				m_iCalcStatus = 0 ;
			} 
			else
			{
				pInEnd->SetZeroMassFlag( FALSE ) ;//ȥ��0�������
				if ( NULL != pOutEnd )
				{
					pOutEnd->SetZeroMassFlag( FALSE ) ;//ȥ��0�������
				}
				m_iCalcStatus = 1 ;
			}

			return ;
		}

		if ( 0 == m_iCalcStatus )
		{
			CalcStmClose();
			m_dLossK = 0.0 ;//ȫ��״̬��ʧKϵ������Ϊ0
		} 
		else
		{
			CalcStmOpen(m_dKOrCv);
		}
	}
}
void MOCRelief::CalcStmClose()
{
	if(1==m_nType || 2 == m_nType)
	{
		CalcCloseValve();
	}
	else if(3 == m_nType)
	{
		CalcCloseInline();
	}
	else
	{
		ASSERT(FALSE);
	}
}

void MOCRelief::CalcCloseValve()
{
	m_EndList.DeadStrategy();
}

void MOCRelief::CalcCloseInline()
{
	m_EndList.BranchStrategy(0);
}

void MOCRelief::CalcStmOpen(double dKOrCv)
{
	if(1==m_nType)
	{
		CalcInterValve(dKOrCv);
	}
	else if(3 == m_nType|| 2 == m_nType)
	{
		CalcExitValve(dKOrCv);
		if ( 3 == m_nType )
		{
			m_dLossK = 0.0 ;
		}
	}
	else
	{
		ASSERT(FALSE);
	}
}

void MOCRelief::CalcInterValve(double dKOrCv)
{
	double dArea = BasisArea(m_nBasisAreaType,m_dBasisArea);
	//Modify by Liuck [4/28/2009] �������Ħ��ϵ������
	if(m_nLossType==0)
	{
		m_EndList.CvStrategy( dKOrCv / sqrt( m_dDesignFactor ), dArea );
	}
	else
	{
		m_EndList.KStrategy(dKOrCv * m_dDesignFactor, dArea );
	}
}

void MOCRelief::CalcExitValve(double dKOrCv)
{
	double dArea = BasisArea(m_nBasisAreaType,m_dBasisArea);
	//Modify by Liuck [4/28/2009] �������Ħ��ϵ������
	if(m_nLossType==0)
	{
		m_EndList.CvStrategy(m_dExitPress,dKOrCv/sqrt( m_dDesignFactor ),dArea,m_dOutFlow);
	}
	else
	{
		m_EndList.KStrategy(m_dExitPress,dKOrCv*m_dDesignFactor,dArea,m_dOutFlow);
	}
}


BOOL MOCRelief::InitTranData(MOCComponentMgr &mgr)
{
	m_tranData.InitFixTrans(mgr,Key(),9);
	return TRUE;
}

void MOCRelief::CalcImpulse(MOCTrans &trans, double dTime)
{
	TestStatus();
	double dK = m_tranData.GeTransY(dTime,m_dKOrCv,trans.StartTime());
	dK = GetK(dK);//k= -1 ��ʾ�����
	if(0==ReliefStatus())
	{
		CalcStmOpen(m_dKOrCv);
	}
	else if(1==ReliefStatus())
	{
		CalcStmClose();
	}
	else
	{
		CalcStmOpen(dK);
	}
	
}

void MOCRelief::TestStatus()
{
	if(0==ReliefStatus()&&IsCloseTriger())
	{//��״̬���ҹر�״̬����
		m_nReliefStatus = 3;//��ʼ�ر�
		return;
	}
	if(1==ReliefStatus()&&IsCloseTriger())
	{//�ر�״̬���Ҵ�״̬����
		m_nReliefStatus = 4;//��ʼ��
		return;
	}
	if(3==ReliefStatus()&&m_bCrack)
	{//��ʼ��״̬
		m_nReliefStatus = 0;//��
		return;
	}
	if(4==ReliefStatus()&&!m_bCrack)
	{//��ʼ�ر�״̬
		m_nReliefStatus = 1;//�ر�
		return;
	}
}

int MOCRelief::ReliefStatus()
{
	return m_nReliefStatus;
}
void MOCRelief::Crack(BOOL bCrack)
{
	m_bCrack = bCrack;
}
BOOL MOCRelief::IsCloseTriger()
{
	return !IsCrackTriger();
}
BOOL MOCRelief::IsCrackTriger()
{
	if(1==m_nType || 2 == m_nType)
	{
		double dPress = m_EndList.GetPress();
		if(m_bDeltaPress)
			dPress -= m_dExitPress;
		return (dPress > m_dCrackPress);
	}
	else if(3 == m_nType)
	{
		double dPress1 = GetInEnd()->CalcPress();
		double dPress2 = GetOutEnd()->CalcPress();
		if(m_bDeltaPress)
		{
			return (fabs(dPress1-dPress2)>m_dCrackPress);
		}
		else
		{
			return((dPress1>m_dCrackPress)||(dPress2>m_dCrackPress));
		}

	}
	ASSERT(FALSE);
	return FALSE;
}
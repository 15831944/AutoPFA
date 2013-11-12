// ScenariManage.cpp: implementation of the ScenariManage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AutoPFA.h"
#include "ScenariManage.h"
#include "Scenario.h"
#include "NetModelPersist.h"
#include "ScenarioPersistMgr.h"
#include "NetModel.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ScenariManage::ScenariManage()
{
	m_pBaseScenario = new Scenario;
	m_pCurScenario = m_pBaseScenario;
}

ScenariManage::~ScenariManage()
{
	delete m_pBaseScenario;
	m_pBaseScenario = NULL;
	m_pCurScenario = NULL;
}

//--------------------------------------------
//Parameters:	 pScenario[IN]	    ��ǰѡ�񹤿�
//    return:    
//      Memo:	 ���õ�ǰ����������Ϊ��ǰѡ�񹤿�
//				
//---------------------------------------------
void ScenariManage::SetCurScenario(Scenario* pScenario)
{
	assert(pScenario != NULL);
	if(LookUp(m_pCurScenario->GetKey()) != NULL)
	{
		m_pCurScenario->DelState();
	}
	m_pCurScenario = pScenario;
	pScenario->InitState();
}

//--------------------------------------------
//Parameters:	 pScenario[IN]	      ��ǰѡ�񹤿�
//               strName[IN]          ��ǰѡ�񹤿����ӹ�������   
//    return:                         �ӹ���                     
//      Memo:	 Ϊ��ǰѡ�񹤿�����һ������ΪstrName���ӹ���
//				
//---------------------------------------------
Scenario* ScenariManage::AddChildScenario(Scenario* pScenario,CString strName)
{
	assert(pScenario != NULL);
	return pScenario->AddChild(strName);
}

//--------------------------------------------
//Parameters:	 pScenario[IN]	      ��ǰѡ�񹤿�
//               strName[IN]          ��ǰѡ�񹤿����ֵܹ�������   
//    return:                         ���ӵ��ֵܹ���                     
//      Memo:	 ��ǰѡ�񹤿�����һ������ΪstrName���ֵܹ��������Ƶ�ǰ���������﹤��
//				
//---------------------------------------------
Scenario* ScenariManage::CloneWithChild(Scenario* pScenario,CString strName)
{
	assert(pScenario != NULL);
	if(pScenario->GetAnScenario()!=NULL)
	{
		return pScenario->CloneWithChild(strName);
	}
	else
	{
		return NULL;
	}

	
}

//--------------------------------------------
//Parameters:	 pScenario[IN]	      ��ǰѡ�񹤿�
//               strName[IN]          ��ǰѡ�񹤿����ֵܹ�������   
//    return:                         ���ӵ��ֵܹ���                     
//      Memo:	 ��ǰѡ�񹤿�����һ������ΪstrName���ֵܹ�����������ǰ���������﹤��
//				
//---------------------------------------------
Scenario* ScenariManage::CloneWithOutChild(Scenario* pScenario,CString strName)
{
	assert(pScenario != NULL);
	if(pScenario->GetAnScenario()!=NULL)
	{
		return pScenario->CloneWithOutChild(strName);
	}
	else
	{
		return NULL;
	}
}

//--------------------------------------------
//Parameters:	 pScenario[IN]	      ��ǰѡ�񹤿�         
//    return:                         ���ӵ��ֵܹ���                     
//      Memo:	 ɾ����ǰѡ�񹤿�������ǰ�������ӹ���
//				
//---------------------------------------------
BOOL ScenariManage::DelScenario(Scenario* pScenario)
{
	assert(pScenario != NULL);
	Scenario *pAnScenario = pScenario->GetAnScenario();
	if(pAnScenario != NULL)
	{
		if(m_pCurScenario == pScenario)
		{
			m_pCurScenario = pAnScenario;
		}
		pAnScenario->DelChild(pScenario);
		return TRUE;
	}
	else
	{
		return FALSE;
	}

}

//--------------------------------------------
//Parameters:	 pScenario[IN]	      ��ǰѡ�񹤿�         
//    return:                                             
//      Memo:	 ������ǰѡ�񹤿���Ϊ�丸�������ֵܹ���
//				
//---------------------------------------------
BOOL ScenariManage::Promote(Scenario* pScenario)
{
	assert(pScenario != NULL);
	if(pScenario->GetAnScenario()!=NULL
		&&pScenario->GetAnScenario()->GetAnScenario()!=NULL)
	{
		pScenario->Promote();
		return TRUE;
	}
	else
	{
		return FALSE;
	}
	
}

//--------------------------------------------
//Parameters:	 nKey[IN]	      ���������ֱ��        
//    return:                     �����ֱ�Ƕ�Ӧ�Ĺ���                                      
//      Memo:	 ���ݹ�����Ψһ���ֱ�ǲ�ѯ������������
//				
//---------------------------------------------
Scenario* ScenariManage::LookUp(int nKey)
{
	return m_pBaseScenario->LookUp(nKey);
}

//--------------------------------------------
//Parameters:	      
//    return:    �õ���ǰ��������������������·��                                   
//      Memo:	 ���ݹ�����Ψһ���ֱ�ǲ�ѯ������������
//				
//---------------------------------------------
CString ScenariManage::GetCurAncestName()
{
	return m_pCurScenario->GetAncestName();
}

BOOL ScenariManage::Read(ScenarioPersistMgr &Persistent)
{
	BOOL bRet = TRUE;
	Scenario *pScenario = NULL;
	NetModelPersist *pNet = Persistent.GetBase();
	if(pNet != NULL)
	{
		m_pBaseScenario->SetKey(pNet->Key());
		m_pBaseScenario->SetName(pNet->Name());
		m_pBaseScenario->GetNetModel()->Read(pNet);
	}
	IteratorPtr<NetModelPersist> NetitPtr(Persistent.CreateIt());
	for(NetitPtr->Fist();!NetitPtr->IsDone();NetitPtr->Next())
	{
		pNet = &NetitPtr->CurrentItem();
		pScenario = LookUp(pNet->ParentKey());
		if(pScenario != NULL)
		{
			pScenario = AddChildScenario(pScenario,pNet->Name());
			pScenario->SetKey(pNet->Key());
			pScenario->GetNetModel()->Read(pNet);
		}
	}
	m_pCurScenario = LookUp(Persistent.CurKey());
	if(m_pCurScenario == NULL)
	{
		m_pCurScenario = m_pBaseScenario;
		bRet = FALSE;
	}
	else
	{
		SetCurScenario(m_pCurScenario);
	}
	return bRet;
}

BOOL ScenariManage::Save(ScenarioPersistMgr &Persistent)
{
	BOOL bRet = TRUE;
	Scenario *pScenario = m_pCurScenario;
	SetCurScenario(m_pBaseScenario);
	bRet = Save(Persistent,m_pBaseScenario);
	Persistent.CurKey(pScenario->GetKey());
	SetCurScenario(pScenario);
	return bRet;
}

BOOL ScenariManage::Save(ScenarioPersistMgr &Persistent,Scenario *pScenario)
{
	NetModelPersist *pNet = Persistent.CreatNetModel();
	pNet->Key(pScenario->GetKey());
	pNet->Name(pScenario->GetName());
	pNet->Ancest(pScenario->GetAncestPath());
	pScenario->GetNetModel()->Save(pNet);
	Scenario *pChild = NULL;
	IteratorPtr<Scenario> iteratorPtr(pScenario->CreatIterator());
	for(iteratorPtr->Fist();!iteratorPtr->IsDone();iteratorPtr->Next())
	{
		pChild = &iteratorPtr->CurrentItem();
		Save(Persistent,pChild);
	}
	return TRUE;
}

BOOL ScenariManage::SaveCurModel(ScenarioPersistMgr &Persistent,Scenario *pScenario)
{
	Scenario *pTempScenario = m_pCurScenario;
	SetCurScenario(pScenario);
	NetModelPersist *pNet = Persistent.CreatNetModel();
	pNet->Key(pScenario->GetKey());
	pNet->Name(pScenario->GetName());
	pNet->Ancest(pScenario->GetAncestPath());
	pScenario->GetNetModel()->Save(pNet);
	Persistent.CurKey(pScenario->GetKey());
	SetCurScenario(pTempScenario);
	return TRUE;
}
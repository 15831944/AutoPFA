// Scenario.cpp: implementation of the Scenario class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AutoPFA.h"
#include "Scenario.h"
#include "NetModel.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
int Scenario::s_nNewKey = 1;

Scenario::Scenario(Scenario* pAnScenario)
{
	m_nKey = s_nNewKey++;
	m_pAnScenario = pAnScenario;
	m_strName = "��������";
	m_pNetModel = new NetModel;
	m_childList.RemoveAll();
 	m_PipeSteadyArray = new CStringArray;
	m_PipeStationArray = new CStringArray;
 	m_PipeTranArray = new CStringArray;
 	m_JunArray = new CStringArray;
}

Scenario::Scenario(Scenario *pAnScenario,CString strName)
{
    m_nKey = s_nNewKey++;
	m_pAnScenario = pAnScenario;
	m_pNetModel   = NULL;
	m_strName     = strName;
	m_childList.RemoveAll();
}

Scenario::Scenario(const Scenario &ref)
{
    m_nKey = s_nNewKey++;
	m_pAnScenario = ref.m_pAnScenario;
	m_pNetModel   = new NetModel(*ref.m_pNetModel);
	m_strName     = ref.m_strName;
	POSITION pos = ref.m_childList.GetHeadPosition();
	Scenario *pChild = NULL;
	while(pos)
	{
		pChild = ref.m_childList.GetNext(pos);
		m_childList.AddTail(new Scenario(*pChild));
	}
}

Scenario& Scenario::operator=(const Scenario &ref)
{
	if(this == &ref)
	return *this;

	POSITION pos = m_childList.GetHeadPosition();
	Scenario *pChild = NULL;
	while(pos)
	{
		pChild = m_childList.GetNext(pos);
		delete pChild;
	}
	m_childList.RemoveAll();
	delete m_pNetModel;

	m_nKey = s_nNewKey++;
    m_pAnScenario = ref.m_pAnScenario;
	m_pNetModel   = new NetModel(*ref.m_pNetModel);
	m_strName     = ref.m_strName;
    pos = ref.m_childList.GetHeadPosition();
	pChild = NULL;
	while(pos)
	{
		pChild = ref.m_childList.GetNext(pos);
		m_childList.AddTail(new Scenario(*pChild));
	}
	
	return *this;
}

Scenario::~Scenario()
{
	POSITION pos = m_childList.GetHeadPosition();
	Scenario *pChild = NULL;
	while(pos)
	{
		pChild = m_childList.GetNext(pos);
		delete pChild;
	}
	delete m_pNetModel;
	//�ڴ�й
	delete m_PipeSteadyArray;
	delete m_PipeStationArray;
	delete m_PipeTranArray;
	delete m_JunArray;
}

//--------------------------------------------
//Parameters:	 nObjectType[IN]       ����Ķ�Ӧ������
//               nObjectKey[IN]        �����Keyֵ
//               nStateKey[IN]         �����״̬��Ӧ��Keyֵ         
//               ScenarioName[Out]	   ��ѯ�Ĺ���״̬���ڵĹ���������             
//    return:    ״̬��Ԫ����Ľӿ�                                    
//      Memo:	 ���ݶ��������Keyֵ�Ͷ����״̬��Keyֵ���Ҷ����״̬������
//               ��״̬�������״̬���ڵĹ������ơ�
//				
//---------------------------------------------
FlyWeight* Scenario::LookUp(int nObjectType,int nObjectKey,int nStateKey,CString &ScenarioName)
{
	//ʹ�����ģʽְ�������Ÿ���������ֱ���ҵ�
	FlyWeight *pFly = NULL;
	pFly = m_pNetModel->LookUp(nObjectType,nObjectKey,nStateKey);
	if(NULL==pFly)
	{
		ASSERT(m_pAnScenario != NULL);
		return m_pAnScenario->LookUp(nObjectType,nObjectKey,nStateKey,ScenarioName);
	}
	else
	{
		ScenarioName = m_strName;
		return pFly;
	}
}

//--------------------------------------------
//Parameters:	         
//    return:                                      
//      Memo:	 ����this����ʹ�ù�����Ϊ���������ֵܹ���
//				
//---------------------------------------------
void Scenario::Promote()
{
	ASSERT(m_pAnScenario != NULL);

	m_pAnScenario->RemoveChild(this);
	m_pNetModel->Promote(m_pAnScenario->m_pNetModel);
	m_pAnScenario = m_pAnScenario->GetAnScenario();
	m_pAnScenario->AddChild(this);
}

//--------------------------------------------
//Parameters:	 pChild[In]        ����
//    return:                                      
//      Memo:	Ϊthis��������pChild����Ϊ�����ӹ���
//				
//---------------------------------------------
void Scenario::AddChild(Scenario *pChild)
{
	m_childList.AddTail(pChild);
}

//--------------------------------------------
//Parameters:	 pChild[In]        ����
//    return:                                      
//      Memo:	����this������pChild�ӹ��������ӹ������Ƴ�
//				
//---------------------------------------------
void Scenario::RemoveChild(Scenario *pChild)
{
	POSITION pos = m_childList.Find(pChild);
	ASSERT(pos != NULL);
	m_childList.RemoveAt(pos);
}

//--------------------------------------------
//Parameters:	 pChild[In]        ����
//    return:                                      
//      Memo:	����this������pChild�ӹ��������ӹ�����ɾ��
//				
//---------------------------------------------
void Scenario::DelChild(Scenario *pChild)
{
	POSITION pos = m_childList.Find(pChild);
	ASSERT(pos != NULL);
	delete pChild;
	m_childList.RemoveAt(pos);
}

//--------------------------------------------
//Parameters:	 strName[In]        ��������
//    return:    ��ǰ���ӵĹ���                                  
//      Memo:	Ϊthis��������һ������ΪstrName���ӹ���
//				
//---------------------------------------------
Scenario* Scenario::AddChild(CString strName)
{
	Scenario *pChild = new Scenario(this,strName);
	pChild->m_pNetModel = m_pNetModel->CloneChild();
	AddChild(pChild);
	return pChild;
}

//--------------------------------------------
//Parameters:	 strName[In]        ��������
//    return:    ��ǰ���ӵĹ���                                  
//      Memo:	����this�������������﹤������һ������ΪstrName���ֵܹ���
//				
//---------------------------------------------
Scenario * Scenario::CloneWithOutChild(CString strName)
{
	assert(m_pAnScenario != NULL);
	Scenario *pClone = new Scenario(m_pAnScenario,strName);
	pClone->m_pNetModel = m_pNetModel->Clone();
	m_pAnScenario->AddChild(pClone);
	return pClone;
}

//--------------------------------------------
//Parameters:	 strName[In]        ��������
//    return:    ��ǰ���ӵĹ���                                  
//      Memo:	����this�����������﹤������һ������ΪstrName���ֵܹ���
//				
//---------------------------------------------
Scenario * Scenario::CloneWithChild(CString strName)
{
    Scenario *pClone = CloneWithOutChild(strName);
	
	POSITION pos = m_childList.GetHeadPosition();
	Scenario *pChild = NULL;
	while(pos)
	{
		pChild = m_childList.GetNext(pos);
		pClone->m_childList.AddTail(new Scenario(*pChild));
	}
	pClone->ChangeAncestor();
	return pClone;
}

//--------------------------------------------
//Parameters:	 
//    return:                             
//      Memo:	�Ƴ�this�����еĶ�������ȹ�����������״̬
//				
//---------------------------------------------
void Scenario::DelState()
{
	m_pNetModel->DelState();
}

//--------------------------------------------
//Parameters:	 
//    return:                             
//      Memo:	�����ȹ�������this���������ڵ�״̬��Ϊthis�������ⲿ����״̬
//				
//---------------------------------------------
void Scenario::InitState()
{
	m_pNetModel->InitState(this);
}

//--------------------------------------------
//Parameters:	 
//    return:                             
//      Memo:	��this�������ӹ�������ĸ�������Ϊthis
//				
//---------------------------------------------
void Scenario::ChangeAncestor()
{
	POSITION pos = m_childList.GetHeadPosition();
	Scenario *pChild = NULL;
	while(pos)
	{
		pChild = m_childList.GetNext(pos);
		pChild->m_pAnScenario = this;
		pChild->ChangeAncestor();
	}
}

//--------------------------------------------
//Parameters:	 
//    return:                             
//      Memo:	Ϊthis�������ӹ�������һ��������Ϊ�ⲿ�����ӹ����ṩһ���ӿ�
//				
//---------------------------------------------
Iterator<Scenario>* Scenario::CreatIterator()
{
	return new ListIterator<Scenario>(&m_childList);
}

//--------------------------------------------
//Parameters:	 nKey[In]     ������Ψһ���Key
//    return:                             
//      Memo:	����this���������﹤����Ψһ���Key=nKey�Ĺ���
//				
//---------------------------------------------
Scenario* Scenario::LookUp(int nKey)
{
	if(m_nKey == nKey)
	{
		return this;
	}
	else
	{
		POSITION pos = m_childList.GetHeadPosition();
		Scenario *pChild = NULL;
		Scenario *pFind = NULL;
		while(pos)
		{
			pChild = m_childList.GetNext(pos);
			pFind = pChild->LookUp(nKey);
			if(pFind != NULL)
				break;
		}
		return pFind;
	}
}

//--------------------------------------------
//Parameters:	 
//    return:   ���ȹ�������·��                         
//      Memo:	����this��������·��
//				
//---------------------------------------------
CString Scenario::GetAncestName()
{
	if(m_pAnScenario == NULL)
	{
		return m_strName;
	}
	else
	{
		return m_pAnScenario->GetAncestName() + "/" + m_strName;
	}
}

CString Scenario::GetAncestPath()
{
	if(m_pAnScenario == NULL)
	{
		return "";
	}
	else
	{
		return m_pAnScenario->GetAncestName();
	}
}
//--------------------------------------------
//Parameters:	 
//    return:     ���������                     
//      Memo:	  ����this������Ӧ�����������
//				
//---------------------------------------------
ComponentManager* Scenario::GetCompManager()
{
	 return &m_pNetModel->m_compManager;
}

CalcManager* Scenario::GetCalcManager()
{
	 return &m_pNetModel->m_calcManager;
}
//--------------------------------------------
//Parameters:	  strName[In]         ��������
//    return:     ���this������������ΪstrName���ӹ�������Ture                     
//      Memo:	  ���strName�Ƿ�this�������ӹ���ʹ��
//				
//---------------------------------------------
BOOL Scenario::CheckName(CString strName)
{
	BOOL bRet = TRUE;
	POSITION pos = m_childList.GetHeadPosition();
	Scenario *pChild = NULL;
	while(pos)
	{
		pChild = m_childList.GetNext(pos);
		if(0 == strName.Compare(pChild->GetName()))
		{
			bRet = FALSE;
		}
	}
	return bRet;
}


// ScenarioObject.cpp: implementation of the ScenarioObject class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AutoPFA.h"
#include "ScenarioObject.h"
#include "Scenario.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ScenarioObject::ScenarioObject()
{
	m_nObjectKey = 0;
	m_privateMap.RemoveAll();
	m_shareMap.RemoveAll();
}

ScenarioObject::ScenarioObject(const ScenarioObject&ref)
{
	m_privateMap.RemoveAll();
	m_shareMap.RemoveAll();
	m_nObjectKey = ref.m_nObjectKey;
	ClonePrivateState(ref.m_privateMap);
	//CloneShareState(ref.m_shareMap);
}

ScenarioObject& ScenarioObject::operator=(const ScenarioObject&ref)
{
	if(this == &ref)
		return *this;

	DelPrivateState();
	DelShareState();

	m_nObjectKey = ref.m_nObjectKey;
	ClonePrivateState(ref.m_privateMap);
	//CloneShareState(ref.m_shareMap);
	
	return *this;
}

ScenarioObject::~ScenarioObject()
{
	DelPrivateState();
}

//--------------------------------------------
//Parameters:	  pCurScenario[In]         ��������
//    return:                          
//      Memo:	  ��ʼ��pCurScenario�����Ķ�������ȹ����״̬
//				
//---------------------------------------------

void ScenarioObject::InitState(Scenario*pCurScenario)
{
	//Template Method (ģ�ⷽ��)
	InitState(pCurScenario,GetArray(),GetType());
}

//--------------------------------------------
//Parameters:	  pCurScenario[In]         ��������
//                array[In]                ScenarioObject��������ӵ�е�״̬
//                nObjectType[In]          ���������
//    return:                          
//      Memo:	  ��ʼ��pCurScenario�����Ķ�������ȹ����״̬
//				
//---------------------------------------------
void ScenarioObject::InitState(Scenario *pCurScenario,const NameArray &array,int nObjectType)
{
    int n = array.GetSize();
    FlyWeight *pFly = NULL;
	int nStateKey;
	for(int i=0; i<n; i++)
	{
		StateName& stateName = (StateName)array[i];
		nStateKey = stateName.Key();
		if(!m_privateMap.Lookup(nStateKey,pFly))
		{
			if(pCurScenario->GetAnScenario()!=NULL)
			{
				pFly = pCurScenario->GetAnScenario()->LookUp(nObjectType,m_nObjectKey,nStateKey);
				assert(pFly != NULL);
				m_shareMap.SetAt(nStateKey,pFly);
			}
		}
	}
}

//--------------------------------------------
//Parameters:	  pParent[In]         ��������
//    return:                          
//      Memo:	  ��this��������ΪpParent�������ֵܹ��������ƴ�pParent���������״̬
//				
//---------------------------------------------
void ScenarioObject::Promote(ScenarioObject *pParent)
{
	NameArray &Array = GetArray();
	int n = Array.GetSize();
    FlyWeight *pFly = NULL;
	int nStateKey;
	for(int i=0; i<n; i++)
	{   
		nStateKey = Array[i].Key();
		if(!m_privateMap.Lookup(nStateKey,pFly))
		{
			if(pParent->m_privateMap.Lookup(nStateKey,pFly))
			{
				m_privateMap.SetAt(nStateKey,pFly->Clone());
			}
		}
	}
}

//--------------------------------------------
//Parameters:	  
//    return:                          
//      Memo:	  ��¡
//				
//---------------------------------------------
ScenarioObject* ScenarioObject::Clone()
{
	ScenarioObject* pClone = DoClone();
	assert(typeid(*this)==typeid(*pClone));
	return pClone;
}

//--------------------------------------------
//Parameters:	  
//    return:                          
//      Memo:	  ��¡�����ǲ���¡�����״̬
//				
//---------------------------------------------
ScenarioObject* ScenarioObject::CloneChild()
{
	ScenarioObject* pClone = Clone();
	pClone->DelPrivateState();
	return pClone;
}

//--------------------------------------------
//Parameters:	  
//    return:                          
//      Memo:	  �Ƴ����������ȵ��ⲿ״̬
//				
//---------------------------------------------
void ScenarioObject::DelShareState()
{
	m_shareMap.RemoveAll();
}

//--------------------------------------------
//Parameters:	  
//    return:                          
//      Memo:	  ɾ�����󱣴��״̬
//				
//---------------------------------------------
void ScenarioObject::DelPrivateState()
{
	POSITION pos = m_privateMap.GetStartPosition();
	FlyWeight *pFly = NULL;
	int nKey;
	while(pos)
	{
		m_privateMap.GetNextAssoc(pos,nKey,pFly);
		delete pFly;
	}
	m_privateMap.RemoveAll();
}

//--------------------------------------------
//Parameters:	  mapFrom[In]           ״̬��
//    return:                          
//      Memo:	  ��¡mapFrom��״̬��Ϊ˽��״̬����
//				
//---------------------------------------------
void ScenarioObject::ClonePrivateState(const StateMap &mapFrom)
{
	POSITION pos = mapFrom.GetStartPosition();
	FlyWeight *pFly = NULL;
	int nKey;
	while(pos)
	{
		mapFrom.GetNextAssoc(pos,nKey,pFly);
		m_privateMap.SetAt(nKey,pFly->Clone());
	}
}

//--------------------------------------------
//Parameters:	  mapFrom[In]           ״̬��
//    return:                          
//      Memo:	  ��mapFrom��״̬��Ϊ����״̬����
//				
//---------------------------------------------
void ScenarioObject::CloneShareState(const StateMap &mapFrom)
{
	POSITION pos = mapFrom.GetStartPosition();
	FlyWeight *pFly = NULL;
	int nKey;
	while(pos)
	{
		mapFrom.GetNextAssoc(pos,nKey,pFly);
		m_shareMap.SetAt(nKey,pFly);
	}
}

//--------------------------------------------
//Parameters:	  
//    return:                          
//      Memo:	  ʹ��ģ�ⷽ����ʼ��ScenarioObject������
//				
//---------------------------------------------
void ScenarioObject::Init()
{
	FlyWeightFactory *m_factory = FlyWeightFactory::Instance();
	NameArray &Array = GetArray();
	int n = Array.GetSize();
    FlyWeight *pFly = NULL;
	int nStateKey;
	for(int i=0; i<n; i++)
	{   
		nStateKey = Array[i].Key();
		pFly = m_factory->CreatObject(Array[i].TypeKey());
		m_privateMap.SetAt(nStateKey,pFly);
	}
}

//--------------------------------------------
//Parameters:	  nStateKey[In]      ״̬Keyֵ
//    return:                          
//      Memo:	  ����״̬��Keyֵ�ȴӱ������˽���ٵ�����״̬�в���״̬
//				
//---------------------------------------------
FlyWeight* ScenarioObject::GetValue(int nStateKey)
{
	FlyWeight *pFly = NULL;
	if(!m_privateMap.Lookup(nStateKey,pFly))
	{
		m_shareMap.Lookup(nStateKey,pFly);
	}
	return pFly;
}

//--------------------------------------------
//Parameters:	  nStateKey[In]      ״̬Keyֵ
//    return:                          
//      Memo:	  ����״̬��Keyֵ�������˽��״̬�в���״̬
//				
//---------------------------------------------
FlyWeight* ScenarioObject::GetPrivate(int nStateKey)
{
	FlyWeight *pFly = NULL;
    m_privateMap.Lookup(nStateKey,pFly);
	return pFly;
}
BOOL ScenarioObject::DelPrivateState(int nStateKey)
{
	FlyWeight *pFly = NULL;
	if(m_privateMap.Lookup(nStateKey,pFly))
	{
		delete pFly;
		m_privateMap.RemoveKey(nStateKey);
		return TRUE;
	}
	return FALSE;
}
BOOL ScenarioObject::IsExistShare(int nStateKey)
{
	FlyWeight *pFly = NULL;
    return m_shareMap.Lookup(nStateKey,pFly);
}
BOOL ScenarioObject::IsExistPrivate(int nStateKey)
{
	FlyWeight *pFly = NULL;
	return m_privateMap.Lookup(nStateKey,pFly);
}
//--------------------------------------------
//Parameters:	  nStateKey[In]      ״̬Keyֵ
//                fly[In]                ״̬
//    return:                          
//      Memo:	 ��״̬fly����nStateKey��Ӧ��״̬
//               ���Ϊ˽��״ֱ̬�Ӹ������Ϊ����״̬��fly����ΪnStateKey��Ӧ��˽��״̬
//				 ������ļ�ʱ��������˽��״̬
//---------------------------------------------
void ScenarioObject::SetValue(int nStateKey,FlyWeight *fly)
{
	FlyWeight *pFlyShare = NULL;
	FlyWeight *pFlyPrivate = NULL;
	if(m_shareMap.Lookup(nStateKey,pFlyShare))
	{
		if(pFlyShare->IsEqual(*fly))
		{
			DelPrivateState(nStateKey);
		}
		else
		{
			m_privateMap.SetAt(nStateKey,fly->Clone());
		}
	}
	else
	{
		if(m_privateMap.Lookup(nStateKey,pFlyPrivate))
		{
			if(pFlyPrivate->IsEqual(*fly))
			{
			}
			else
			{
				pFlyPrivate->Assign(fly);
			}
		}
		else
		{
			m_privateMap.SetAt(nStateKey,fly->Clone());
		}
	}	
}
void ScenarioObject::SetValue(FlyWeight &fly,int nStateKey)
{
	if(fly.IsEmpty()
	   && !IsExistPrivate(nStateKey)
	   && !IsExistShare(nStateKey))
	{
		//���ļ�ʱ�ӹ�������Ϊ�ձ�ʾ������������
		//������˽�����Ժ͹������Ա�ʾ�ӹ����ڶ��ļ���ʼ������
		return;
	}
	else
	{
		SetValue(nStateKey,&fly);
	}
}

//--------------------------------------------
//Parameters:	  nStateKey[In]      ״̬Keyֵ
//                pCurScenario[In]   ��ǰ�����Ӧ�Ĺ���
//                ScenarioName[Out]  ���ҷ��ص�״̬��Ӧ�Ĺ���
//    return:     �����nStateKey��Ӧ��״̬                     
//      Memo:	  ���ݶ���״̬��Keyֵ�͵�ǰ�������ڵĹ�������״̬�����״̬���ڵĹ�������
//				
//---------------------------------------------
FlyWeight* ScenarioObject::LookUp(int nStateKey,Scenario*pCurScenario,CString &ScenarioName)
{
	FlyWeight *pFly = NULL;
	if(!m_privateMap.Lookup(nStateKey,pFly))
	{
		if(pCurScenario->GetAnScenario()!=NULL)
		pFly = pCurScenario->GetAnScenario()->LookUp(GetType(),m_nObjectKey,nStateKey,ScenarioName);
		return pFly;
	}
	else
	{
		ScenarioName = pCurScenario->GetName();
		return pFly;
	}
}

//--------------------------------------------
//Parameters:	  nStateKey[In]      ״̬Keyֵ
//                pCurScenario[In]   ��ǰ�����Ӧ�Ĺ���
//                ScenarioName[Out]  ���ҷ��ص�״̬��Ӧ�Ĺ���
//    return:     �����nStateKey��Ӧ��״̬                     
//      Memo:	  ���ݶ���״̬��Keyֵ�͵�ǰ�������ڵĹ������Ҷ��������ȵ�״̬�����״̬���ڵĹ�������
//				
//---------------------------------------------
FlyWeight* ScenarioObject::LookAncest(int nStateKey,Scenario*pCurScenario,CString &ScenarioName)
{
	FlyWeight *pFly = NULL;
	pFly = LookUp(nStateKey,pCurScenario,ScenarioName);
	if(m_privateMap.Lookup(nStateKey,pFly))
	{
		pFly = NULL;
		ScenarioName.Empty();
	}
	return pFly;
}

void ScenarioObject::CloneShare(ScenarioObject* ppPrototype)
{
	//��ԭ�͵Ĺ���״̬���Ƶ�����Ʒ��˽��״̬��
	ClonePrivateState(ppPrototype->m_shareMap);
}

BOOL ScenarioObject::IsEmpty()
{
	if(m_privateMap.IsEmpty()
		&&m_shareMap.IsEmpty())
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void ScenarioObject::InitAttr(NameArray &array,UINT nID,int nKey,int nType,BOOL bShow)
{
	CString strTemp;
	strTemp.LoadString(nID);
	StateName temp(strTemp,nKey,nType,bShow);
	array.Add(temp);
}
void ScenarioObject::InitAttr(NameArray &array,int nKey, int nType)
{
	StateName temp(nKey,nType);
	array.Add(temp);
}
// ScenarioPersistMgr.h: interface for the ScenarioPersistMgr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCENARIOPERSISTMGR_H__7026A85B_0495_402B_B767_759FF73E55EB__INCLUDED_)
#define AFX_SCENARIOPERSISTMGR_H__7026A85B_0495_402B_B767_759FF73E55EB__INCLUDED_
/*
 * Copyright (C), 2006,��ɳ���������˾CAE������
 * All rights reserved.
 *
  �ļ����ƣ�ScenarioPersistMgr.h
  ժҪ�� �����־û�����   
  author  : LSP          
*/
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "NetModelPersist.h"
#include "Iterator.h"

class AFX_EXT_CLASS ScenarioPersistMgr  
{
public:
	ScenarioPersistMgr();
	virtual ~ScenarioPersistMgr();

public:
	int GetModelNum();
	int CurKey();
	void CurKey(int iKey);
	NetModelPersist* CreatNetModel();
	NetModelPersist* GetBase();
	Iterator<NetModelPersist>* CreateIt();
	typedef CList<NetModelPersist*,NetModelPersist*> ModelList;
	
private:
	
private:
	ModelList m_NetList;
	int m_nCurModelKey;
};
inline void ScenarioPersistMgr::CurKey(int iKey)
{
	m_nCurModelKey = iKey;
}

inline int ScenarioPersistMgr::CurKey()
{
	return m_nCurModelKey;
}

#endif // !defined(AFX_SCENARIOPERSISTMGR_H__7026A85B_0495_402B_B767_759FF73E55EB__INCLUDED_)

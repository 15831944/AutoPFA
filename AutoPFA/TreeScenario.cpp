// TreeScenario.cpp : implementation file
//

#include "stdafx.h"
#include "AutoPFA.h"
#include "TreeScenario.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// TreeScenario

TreeScenario::TreeScenario()
{
}

TreeScenario::~TreeScenario()
{
}

BEGIN_MESSAGE_MAP(TreeScenario, CTreeCtrl)
	//{{AFX_MSG_MAP(TreeScenario)
	ON_WM_RBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// TreeScenario message handlers

void TreeScenario::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CTreeCtrl::OnRButtonDown(nFlags, point);
	CMenu popUpMenu;
	popUpMenu.CreatePopupMenu();
	popUpMenu.AppendMenu(MF_STRING,ID_CREATCHILD,_T("�����ӹ���"));
    popUpMenu.AppendMenu(MF_STRING,ID_CLONEWITHCHILD,_T("��¡�ֵܺ��ӹ���"));
	popUpMenu.AppendMenu(MF_STRING,ID_CLONEWITHOUT,_T("��¡�ֵܹ���"));
	popUpMenu.AppendMenu(MF_STRING,ID_PROMOTE,_T("��������"));
	popUpMenu.AppendMenu(MF_STRING,ID_DELSCENARIO,_T("ɾ������"));
	popUpMenu.AppendMenu(MF_STRING,ID_RENAME,_T("����������"));
	popUpMenu.AppendMenu(MF_STRING,ID_SAVESCENARIO,_T("����ѡ�񹤿�"));
	ClientToScreen(&point);
	popUpMenu.TrackPopupMenu(TPM_RIGHTBUTTON,point.x,point.y,GetParent());
}

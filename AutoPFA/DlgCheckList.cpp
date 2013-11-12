// DlgCheckList.cpp : implementation file
//

#include "stdafx.h"
#include "autopfa.h"
#include "DlgCheckList.h"
#include "DlgSteadySet.h"
#include "Scenario.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgCheckList dialog


DlgCheckList::DlgCheckList(CWnd* pParent /*=NULL*/)
	: CDialog(DlgCheckList::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgCheckList)
	m_b1 = FALSE;
	m_b2 = FALSE;
	m_b3 = FALSE;
	m_b4 = FALSE;
	m_b5 = FALSE;
	//}}AFX_DATA_INIT
	m_bTran =FALSE;
	m_pCurDoc = NULL;
}


void DlgCheckList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgCheckList)
	DDX_Check(pDX, IDC_CHECK1, m_b1);
	DDX_Check(pDX, IDC_CHECK2, m_b2);
	DDX_Check(pDX, IDC_CHECK3, m_b3);
	DDX_Check(pDX, IDC_CHECK4, m_b4);
	DDX_Check(pDX, IDC_CHECK5, m_b5);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgCheckList, CDialog)
	//{{AFX_MSG_MAP(DlgCheckList)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK2, OnCheck2)
	ON_BN_CLICKED(IDC_CHECK3, OnCheck3)
	ON_BN_CLICKED(IDC_CHECK4, OnCheck4)
	ON_BN_CLICKED(IDC_CHECK5, OnCheck5)
	ON_BN_CLICKED(IDC_BUT_ShowSteadySet, OnShowSteadySet)
	ON_BN_CLICKED(IDC_BUT_ShowSystemProper, OnShowSystemProper)
	ON_BN_CLICKED(IDC_BUT_ShowSectionPipe, OnShowSectionPipe)
	ON_BN_CLICKED(IDC_BUT_ShowTransControl, OnShowTransControl)
	ON_BN_CLICKED(IDC_BUT_UndefinedObjects, OnShowUndefinedObjects)

	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgCheckList message handlers

void DlgCheckList::Init(BOOL bCheck[],BOOL bTran)
{
	m_b1 = bCheck[0];
	m_b2 = bCheck[1];
	m_b3 = bCheck[2];
	m_b4 = bCheck[3];
	m_b5 = bCheck[4];
	m_bTran = bTran;
}

void DlgCheckList::OnCheck1() 
{
	// TODO: Add your control notification handler code here
	UpdateData(FALSE);
}

void DlgCheckList::OnCheck2() 
{
	// TODO: Add your control notification handler code here
	UpdateData(FALSE);
}

void DlgCheckList::OnCheck3() 
{
	// TODO: Add your control notification handler code here
	UpdateData(FALSE);
}

void DlgCheckList::OnCheck4() 
{
	// TODO: Add your control notification handler code here
	UpdateData(FALSE);
}

void DlgCheckList::OnCheck5() 
{
	// TODO: Add your control notification handler code here
	UpdateData(FALSE);
}

BOOL DlgCheckList::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	if(!m_bTran)
	{
		GetDlgItem(IDC_CHECK4)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK5)->EnableWindow(FALSE);
	}
	return TRUE; 
}

//��ʾ�㶨���������ƶԻ���
void DlgCheckList::OnShowSteadySet() 
{
	if ( m_pCurDoc != NULL )
	{
		m_pCurDoc->OnSteadyControl();
	}
}

//���õ�ǰ�����ĵ�
void DlgCheckList::SetCurDoc(CAutoPFADoc *pCurDoc)
{
   m_pCurDoc = pCurDoc;
}

//��ʾϵͳ���ԶԻ���
void DlgCheckList::OnShowSystemProper() 
{
	if ( m_pCurDoc != NULL )
	{
		m_pCurDoc->OnSystemProper();
	}
}

//��ʾ�ܵ��ֶζԻ���
void DlgCheckList::OnShowSectionPipe() 
{
	if ( m_pCurDoc != NULL )
	{
        m_pCurDoc->OnSectionPipe();
	}
}

//��ʾ˲�����������ƶԻ���
void DlgCheckList::OnShowTransControl() 
{
	if ( m_pCurDoc != NULL )
	{
		m_pCurDoc->OnTransControl();
	}
}

void DlgCheckList::OnShowUndefinedObjects() 
{
	if ( m_pCurDoc != NULL )
	{
		//������е�PIPE��JUN���Ѿ�����������ʾ�Ի���
		if ( m_pCurDoc->m_scenarioManager.GetCurScenario()->GetCompManager()->IsAllJunDefine( TRUE ) 
			&& m_pCurDoc->m_scenarioManager.GetCurScenario()->GetCompManager()->IsAllPipeDefine( TRUE ) )
		{
			return ;
		}
		CDlgUndefinedObjects m_dlgUndefinedObjects( &m_pCurDoc->m_unitSystem, m_pCurDoc->m_scenarioManager.GetCurScenario()->GetCompManager() );
        m_dlgUndefinedObjects.DoModal();		 	
	}
	m_pCurDoc->OnCheckModel();
}

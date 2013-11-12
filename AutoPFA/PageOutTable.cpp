// PageOutTable.cpp : implementation file
//

#include "stdafx.h"
#include "autopfa.h"
#include "PageOutTable.h"
#include "DlgChangeUnit.h"
#include "AutoPFADoc.h"
#include "OutPutRef.h"
#include "MainFrm.h"
#include "ChildFrm.h"
#include "AutoPFAView.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// PageOutTable dialog


PageOutTable::PageOutTable(CWnd* pParent /*=NULL*/)
	: PageDataTable(pParent)
{
	//{{AFX_DATA_INIT(PageOutTable)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pOutMgr = NULL;
	m_pArray  = NULL;

	m_pComponentMgr = NULL;
	m_pUnitSubSys   = NULL;
}


void PageOutTable::DoDataExchange(CDataExchange* pDX)
{
	PageDataTable::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(PageOutTable)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(PageOutTable, PageDataTable)
	//{{AFX_MSG_MAP(PageOutTable)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// PageOutTable message handlers

void PageOutTable::LoadData(OutMgr &mgr,OutAttrArray &Array,int nType)
{
	m_pOutMgr = &mgr;
	m_pArray = &Array;
	
	
	
	m_table.DeleteAllItems();
	InitTableHeader(Array);
	Loading(mgr,Array,nType);
}

void PageOutTable::InitTableData(OutAttrArray &array,ComponentStmOut *pStmOut)
{
	int nRow = m_table.InsertRow(_T(""));
	int nCol = 0;
	CString strText;
	int n = array.GetSize();
	for(int i=0;i<n;i++)
	{
		strText = pStmOut->GetValue(array[i].Key());
		m_table.SetItemText(nRow,nCol++,array[i].TranData(strText));
	}
}

void PageOutTable::InitTableHeader(OutAttrArray &array)
{
	int n = array.GetSize();
	int nCol = 0;
	for(int i=0;i<n;i++)
	{
		nCol = m_table.InsertColumn(array[i].GetTitle(),DT_CENTER|DT_VCENTER);
		m_table.SetItemData(0,nCol,i);
	}
	
	m_table.SetRowHeight(0,35);
	m_table.SetFixedRowCount();
	m_table.SetFixedColumnCount();
}

// BOOL PageOutTable::SavePipeUnitOrder()
// {
// 	CStdioFile File;
// 
// 	TCHAR exeFullPath[MAX_PATH];
// 	::GetModuleFileName(NULL,exeFullPath,MAX_PATH);
// 	CString strPath(exeFullPath);
// 	int index = strPath.ReverseFind('\\');
// 	ASSERT(index != -1);
// 	strPath = strPath.Left(index+1);
// 	strPath += _T("PipeUnitOder.txt");
// 
// 	if ( !File.Open(strPath,CFile::modeWrite|CFile::modeCreate|CFile::typeText))
// 	{
// 		return FALSE;
// 	}
// 	File.WriteString(strTemp);
// 	File.Close();
// 	
// 	m_OutPutData.SetPipeUnitOrder()=model.GetScenarioPersist().GetBase()->GetOutputRef().PipeUnitOrder();
// 	m_OutPutData.SetPipeDataOrder()=model.GetScenarioPersist().GetBase()->GetOutputRef().PipeDataOrder();
// 	
// 	return TRUE;
// }

// BOOL PageOutTable::SaveJunUnitOrder()
// {
// // 	CStdioFile File;
// // 	
// // 	TCHAR exeFullPath[MAX_PATH];
// // 	::GetModuleFileName(NULL,exeFullPath,MAX_PATH);
// // 	CString strPath(exeFullPath);
// // 	int index = strPath.ReverseFind('\\');
// // 	ASSERT(index != -1);
// // 	strPath = strPath.Left(index+1);
// // 	strPath += _T("JunUnitOder.txt");
// // 	
// // 	if ( !File.Open(strPath,CFile::modeWrite|CFile::modeCreate|CFile::typeText))
// // 	{
// // 		return FALSE;
// // 	}
// // 	File.WriteString(strTemp);
// // 	File.Close();
// 	OutputRefPersist m_OutPutData;
// 	PersistentModel model;
// 	m_OutPutData.SetJunUnitOrder()=model.GetScenarioPersist().GetBase()->GetOutputRef().JunUnitOrder();
// 	m_OutPutData.SetJunDataOrder()=model.GetScenarioPersist().GetBase()->GetOutputRef().JunDataOrder();
// 	return TRUE;
// }

BOOL PageOutTable::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{

	NM_GRIDVIEW * m_GridView=(NM_GRIDVIEW *) lParam;
	if(IDC_TABLE==wParam)
	{
		if(m_GridView->hdr.code ==NM_DBLCLK && m_GridView->iRow == 0 )
		{
			m_table.SetFocusCell( m_GridView->iRow, m_GridView->iColumn );//ǿ�������б��㵥Ԫ�������õĻ���ʾ��λ�Ի����ʧ�ܣ���Ϊ�ò������㵥Ԫ
			ShowDlg(0);	//���˫���ڱ�ͷ������ʾ�޸ĵ�λ�Ի���
		}
		else if ( m_GridView->hdr.code ==NM_DBLCLK && m_GridView->iRow > 0 )
		{
			ShowDlg(1);//������ʾԪ����Ϣ�Ի���
		}
	}
	return CDialog::OnNotify(wParam, lParam, pResult);
}

void PageOutTable::ShowDlg(int iDlgType)
{
	if ( 0 == iDlgType )
	{
		ShowUnitDlg();
	}
	else if ( 1 == iDlgType )
	{
		ShowComponentDlg();
	}
}

void PageOutTable::UpDataTableData(OutDataAttr &attr,int nCol)
{
	CString strText;
	for(int i=1;i<m_table.GetRowCount();i++)
	{
		strText = LookUp(attr.Key(),i);
		m_table.SetItemText(i,nCol,attr.TranData(strText));
	}
}

/************************************************************************
�汾: 8.0  ����ʱ��: [2009/3/27]  ����: [ue8] ������:
����:�ṩԪ�����������Ա�˫�����ʱ���Ը��ݹ�������ʾԪ����Ϣ                                                              
����:                                                               
���:                                                              
< �޸��� >    < ʱ�� >     < �汾 >        < ���� >                                                                               
************************************************************************/
void PageOutTable::LoadComponentMgr(ComponentManager* pComMgr, UnitSubSystem* pUnitSys)
{
	m_pComponentMgr = pComMgr;
	m_pUnitSubSys   = pUnitSys;
}

BOOL PageOutTable::ComponentType(CString strType)
{
	if ( strType != UeCoponentType::eJun && strType != UeCoponentType::ePipe )
	{
		return FALSE;
	}
	 
	m_strComponentType = strType;
	return TRUE;
}

void PageOutTable::ShowUnitDlg()
{
	CCellID cell = m_table.GetFocusCell();
    if(!m_table.IsValid(cell))
    {
        return;
    }
	int nIndex = m_table.GetItemData(0,cell.col);
	OutDataAttr &attr = m_pArray->GetAt(nIndex);
	
	if ( ( cell.col == 1 ) && ( cell.row ==1 ) )
	{
		ShowTranStepDlg();
	}
	else
	{	
		DlgChangeUnit dlg(attr);
		if(dlg.DoModal()==IDOK)
		{
			m_table.SetItemText(0,cell.col,attr.GetTitle());
			UpDataTableData(attr,cell.col);
			m_pArray->SetAt(nIndex,attr);
			m_table.RedrawColumn(cell.col);
		}
	}

	
	CString strTemp="";
	int j=m_pArray->GetSize();
	for (int i=1;i<m_pArray->GetSize()-1;i++)
	{
		strTemp+=m_pArray->GetAt(i).Unit()+",";		
	}
	
	strTemp+=m_pArray->GetAt(m_pArray->GetSize()-1).Unit();
	
	CMainFrame* pMainFrame = NULL;
	pMainFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CChildFrame* pChildFrame = NULL;
	pChildFrame= (CChildFrame*)pMainFrame->GetActiveFrame();
	CAutoPFADoc* pAutoDoc = NULL;
	pAutoDoc= (CAutoPFADoc*)pChildFrame->GetActiveDocument();
	OutputRefPersist &m_OutPutData=pAutoDoc->m_OutPutData;
	
	if ( "�ܵ�"== m_pArray->GetAt(0).Name())
	{	
		m_OutPutData.PipeUnitOrder(strTemp);		
	}
	
	//	AfxMessageBox(m_pArray->GetAt(0).Name());
	if ( "�ڵ�" == m_pArray->GetAt(0).Name() )
	{
		m_OutPutData.JunUnitOrder(strTemp);
		//		SaveJunUnitOrder();
	}
}

void PageOutTable::ShowTranStepDlg()
{

}

void PageOutTable::ShowComponentDlg()
{
	CCellID cell = m_table.GetFocusCell();
    if( !m_table.IsValid(cell) || m_pComponentMgr == NULL )//�жϺϷ���
    {
        return;
    }
	 
	CString strKey = m_table.GetItemText( cell.row, 0 );//��ȡ�ؼ���
	int iKey = _ttoi( strKey );

	if ( UeCoponentType::ePipe == m_strComponentType )
	{
		Component* pCom = m_pComponentMgr->LookUpPipe(iKey);//���ݹؼ��ֲ��ҹܵ�
		if( pCom )
		{
			pCom->Show( *m_pUnitSubSys, m_pComponentMgr, TRUE );//��ʾ�ܵ���Ϣ�Ի���
		}
		
	}
	else if ( UeCoponentType::eJun == m_strComponentType )
	{
		Component* pCom = m_pComponentMgr->LookUpJun(iKey);
		if( pCom )
		{
			pCom->Show( *m_pUnitSubSys, m_pComponentMgr, TRUE );//��ʾԪ����Ϣ�Ի���
		}
	}
}

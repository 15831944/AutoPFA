// PagePipeOutControl.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AutoPFA.h"
#include "PagePipeOutControl.h"
#include "UnitSubSystem.h"


// PagePipeOutControl �Ի���

IMPLEMENT_DYNAMIC(PagePipeOutControl, CDialog)

PagePipeOutControl::PagePipeOutControl(PFAOutModel& outModel, CWnd* pParent /*=NULL*/)
	: CDialog(PagePipeOutControl::IDD, pParent)
	,m_pPageAtt(outModel)
	,m_outModel(outModel)
{


}

PagePipeOutControl::~PagePipeOutControl()
{
}



void PagePipeOutControl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_NOTSHOWOUT, m_tab);
	DDX_Control(pDX, IDC_LIST_SHOWOUT, m_lstArrShow);
	DDX_Control(pDX, IDC_COMBO_Unit, m_comboUnit);
}


BEGIN_MESSAGE_MAP(PagePipeOutControl, CDialog)
	ON_BN_CLICKED(IDC_BTN_ADD, &PagePipeOutControl::OnBnClickedAdd)
	ON_BN_CLICKED(IDC_BTN_DELETE, &PagePipeOutControl::OnBnClickedDelete)
	ON_BN_CLICKED(IDC_BUTTON3, &PagePipeOutControl::OnBtnDeleteAll)
	ON_CBN_SELCHANGE(IDC_COMBO_Unit, &PagePipeOutControl::OnCbnSelchangeComboUnit)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_SHOWOUT, &PagePipeOutControl::OnLvnItemchangedListShowout)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(PagePipeOutControl, CDialog)
END_DISPATCH_MAP()

// ע��: ������� IID_IPagePipeOutControl ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡��� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {EABE335B-E85F-4329-8350-9F6539AFA4B9}
static const IID IID_IPagePipeOutControl =
{ 0xEABE335B, 0xE85F, 0x4329, { 0x83, 0x50, 0x9F, 0x65, 0x39, 0xAF, 0xA4, 0xB9 } };

BEGIN_INTERFACE_MAP(PagePipeOutControl, CDialog)
	INTERFACE_PART(PagePipeOutControl, IID_IPagePipeOutControl, Dispatch)
END_INTERFACE_MAP()


// PagePipeOutControl ��Ϣ�������
BOOL PagePipeOutControl::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_tab.AddPage( _T(""), &m_pPageAtt, IDD_DATALIST );
	m_tab.Show();

	m_lstArrShow.InsertColumn( 0, _T("") ,LVCFMT_CENTER , 100 );
	m_lstArrShow.InsertColumn( 1, _T(""), LVCFMT_CENTER , 100 );
	m_lstArrShow.SetExtendedStyle( LVS_EX_FULLROWSELECT );

	OutMgr &outMgr = m_outModel.SteadyOut().ComponentOutMgr().PipeOutMgr();
	OutAttrArray& arr = outMgr.GetArray();        //Ĭ����ʾ���ֶ� 
	OutAttrArray& arrAll = outMgr.GetAllArray();  //���п�����ʾ���ֶ�

	m_strPipeOrder = outMgr.m_OutPutData.PipeDataOrder();
	m_strPipeUnit = outMgr.m_OutPutData.PipeUnitOrder();

	LoadShowAtt( outMgr );//����Ĭ����ʾ�������ֶ�
	LoadAllAtt( outMgr );      //�������п�����ʾ�������ֶ�

	UpdateData( FALSE );
	return TRUE;
}

void PagePipeOutControl::OnBnClickedAdd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	int nItem = m_pPageAtt.GetSelectedItem();
	if ( nItem == -1 )
	{
		return;
	}
	int nKey = m_pPageAtt.GetItemData(nItem);
	CString strName = m_pPageAtt.GetItemText( nItem, 0 );
	CString strUnit = m_pPageAtt.GetItemText( nItem, 1 );
	if ( -1 == nKey )
	{
		return;
	}
    
	CString strKey;
	strKey.Format( _T("%d"), nKey );

	m_lstArrShow.InsertItem( m_lstArrShow.GetItemCount(), strName );
	m_lstArrShow.SetItemText( m_lstArrShow.GetItemCount()-1, 1, strUnit );
	m_lstArrShow.SetItemData( m_lstArrShow.GetItemCount()-1, nKey );

	m_pPageAtt.DeleteItem(nItem);


}

void PagePipeOutControl::OnBnClickedDelete()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	POSITION pos = m_lstArrShow.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		TRACE0("No items were selected!\n");
	}
	else
	{
		while (pos)
		{
			int nItem = m_lstArrShow.GetNextSelectedItem(pos);
			TRACE1("Item %d was selected!\n", nItem);
			// you could do your own processing on nItem here
			int nKey = (int)m_lstArrShow.GetItemData( nItem );
			CString strUnit = m_lstArrShow.GetItemText( nItem, 1 );
			CString strText = m_lstArrShow.GetItemText( nItem, 0 );
			m_lstArrShow.DeleteItem( nItem );
			m_pPageAtt.AddItem( strText, strUnit, nKey );

			break;
		}
	}
}

void PagePipeOutControl::OnBtnDeleteAll()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void PagePipeOutControl::InitData(CString InData,CString str[50])
{
	InData.TrimLeft();
	int nIdex=0;
	int i;
	int strj=0;
	for (i=0;i<50;i++)
	{
		nIdex=InData.Find(_T(','));
		strj++;
		if (nIdex==-1)
		{
			InData.TrimRight();
			str[strj-1]=InData;
			break;
		}
		if (nIdex==0)
		{
			InData.Delete(0,1);
			continue;
		}
		str[i]=InData.Left(nIdex);
		InData.Delete(0,nIdex+1);		
	}

	for (;strj<50;strj++)
	{
		str[strj]="0";
	}

}

void PagePipeOutControl::LoadAllAtt(  OutMgr& outMgr  )
{
	m_pPageAtt.DeleteAllItems();

	int i=0;   
	for (i = 1; i < outMgr.m_OutPutSys.GetPipeOutArray().GetSize(); i++ )
	{
		CString strName = outMgr.m_OutPutSys.GetPipeOutArray()[i].GetStrName();
		CString strUnit = outMgr.m_OutPutSys.GetPipeOutArray()[i].GetStrUnit();
		CString strKey = outMgr.m_OutPutSys.GetPipeOutArray()[i].GetKey();

		if ( !Find( strKey ) )//�鿴�������Ƿ�����ʾ�����б���ǵĻ�������ӵ�����ʾ�����б���
		{
			m_pPageAtt.AddItem( strName,strUnit, _ttoi(strKey) );
		}
	}
}

void PagePipeOutControl::LoadShowAtt( OutMgr& outMgr )
{
	m_lstArrShow.DeleteAllItems();

	CString str1[50];//����Key;
	InitData(m_strPipeOrder,str1);
    OutAttrArray& outShowArr = outMgr.GetArray();

	int k=0;
	int j; 
	for (k = 0; k < 30;k++)
	{
		if (str1[k] == "0")
			break;

		for(j = 0; j < 30; j++)
		{	
			if (str1[k] != "0" && str1[k] == outMgr.m_OutPutSys.GetPipeOutArray()[j].GetKey())
			{
				CString strKey = outMgr.m_OutPutSys.GetPipeOutArray()[j].GetKey();
				CString strName = /*outMgr.m_OutPutSys.GetPipeOutArray()[j].GetStrName();*/outShowArr.GetAt(j+1).Name();
				CString strUnit = /*outMgr.m_OutPutSys.GetPipeOutArray()[j].GetStrUnit();*/outShowArr.GetAt(j+1).Unit();

				m_lstArrShow.InsertItem( m_lstArrShow.GetItemCount(), strName );
				m_lstArrShow.SetItemText( m_lstArrShow.GetItemCount()-1 ,1, strUnit );
				m_lstArrShow.SetItemData( m_lstArrShow.GetItemCount()-1, _ttoi(strKey) );
				break;
			}
		}
	}
}

void PagePipeOutControl::UpData()
{
	OutMgr &outMgr = m_outModel.SteadyOut().ComponentOutMgr().PipeOutMgr();
	CString strTemp1 = outMgr.m_OutPutData.PipeDataOrder();
//	OutAttrArray& arr = outMgr.GetArray();
	CString strOrder = _T("");
	CString strUnit = _T("");

//	arr.RemoveAll();
	int i = 0;
	for ( ; i < m_lstArrShow.GetItemCount(); i++ )
	{
//		arr.Add( m_outShowArr.GetAt(i) );

		if ( m_lstArrShow.GetItemData(i) == 0 )
		{
			continue;
		}
		CString strDataTemp;
		strDataTemp.Format( _T("%d") , m_lstArrShow.GetItemData(i) );
		strOrder += strDataTemp;
		strOrder += _T(",");
      
		strUnit += m_lstArrShow.GetItemText( i, 1 );
		strUnit += _T(",");
		
	}
    strOrder.TrimRight( _T(",") );
	strUnit.TrimRight( _T(",") );
    outMgr.m_OutPutData.PipeDataOrder( strOrder );
	outMgr.m_OutPutData.PipeUnitOrder( strUnit );
}

BOOL PagePipeOutControl::Find( CString strKey )
{

	int i = 0;
	int nkey = _ttoi(strKey);

	for ( ; i < m_lstArrShow.GetItemCount(); i++ )
	{
		if ( nkey == (int)m_lstArrShow.GetItemData(i) )
		{
			return TRUE;
		}
	}
	return FALSE;

}
void PagePipeOutControl::OnCbnSelchangeComboUnit()
{
	int nIndex = m_comboUnit.GetCurSel();
	if ( nIndex < 0 )
	{
		return;
	}
	CString strUnit = _T("");
	m_comboUnit.GetLBText( nIndex , strUnit );

	POSITION pos = m_lstArrShow.GetFirstSelectedItemPosition();
	if ( pos == NULL )
	{
		return;
	}
	int nItem = m_lstArrShow.GetNextSelectedItem( pos );
	if ( nItem < 0 )
	{
		return;
	}
    m_lstArrShow.SetItemText( nItem , 1 , strUnit );
}

/************************************************************************
�汾: 8.0  ע��ʱ��: [2009/4/21]  ����: [Zhufy] ������: 
����:    ������ѡ�е��г�ʼ����λ�б�                                                        
����:                                                               
���:                                                              
< �޸��� >    < ʱ�� >     < �汾 >        < ���� >                                                                               
************************************************************************/
void PagePipeOutControl::OnLvnItemchangedListShowout(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	POSITION pos = m_lstArrShow.GetFirstSelectedItemPosition();
	if ( pos == NULL )
	{
		return;
	}

	int nItem = m_lstArrShow.GetNextSelectedItem( pos );
	int nKey = (int)m_lstArrShow.GetItemData(nItem);
	if ( -1 == nKey )
	{
		return;
	}
	CString strKey;
	strKey.Format( _T("%d") , nKey );

	OutMgr &outMgr = m_outModel.SteadyOut().ComponentOutMgr().PipeOutMgr();
	OutAttrArray& AttArr = outMgr.GetArray();
	OutDataAttr &dataAttr = AttArr.GetAt( 0 );
	int i;
	for(i = 0; i < 30; i++)
	{	
		if ( strKey != _T("0") && strKey == outMgr.m_OutPutSys.GetPipeOutArray()[i].GetKey())
		{
            dataAttr = AttArr.GetAt( i + 1 );
			break;
		}
	}
	m_comboUnit.ResetContent();
	SymbolArray array;
	UnitSubSystem &system = dataAttr.UnitSys();
	UnitTypeID id = dataAttr.UnitType();
	CString m_strCurSymbol = dataAttr.Unit();
	system.FindSymbolArray( id,array );
	for( i=0;i<array.GetSize();i++ )
	{
		m_comboUnit.AddString( array.GetAt(i) );
	}
	m_comboUnit.SelectString( -1,m_strCurSymbol );
	*pResult = 0;
}

/************************************************************************
�汾: 8.0  ����ʱ��: [2009/4/22]  ����: [ue8] ������:
����: ��bat�ļ���ȡ�ܵ������ֶζ�Ӧ��keyֵ����Ӧ�ĵ�λ                                                             
����:                                                               
���:                                                              
< �޸��� >    < ʱ�� >     < �汾 >        < ���� >                                                                               
************************************************************************/
BOOL PagePipeOutControl::Read(CStdioFile& file)
{
	BOOL bPipeFlag = FALSE;//��ȡ���ܵ����Ա�־
	CString strPipeOrder;
	file.ReadString(strPipeOrder);//��ȡ�ܵ������ֶ�
	while ( strPipeOrder.IsEmpty() )
	{
		file.ReadString(strPipeOrder);
	}
	if ( -1 != strPipeOrder.Find( _T("Pipe Data Order") ) )
	{
		int pos = strPipeOrder.Find( _T("=") );
		if ( -1 != pos )
		{
			strPipeOrder = strPipeOrder.Mid(pos+1);
			strPipeOrder.TrimLeft();
			strPipeOrder.TrimRight();
		}
		bPipeFlag = TRUE;//�Ѿ���ȡ���ܵ�����
	}

	BOOL bUnitFlag = FALSE;//��ȡ�ܵ����Զ�Ӧ�ĵ�λ��־
	CString strPipeUnit;
	file.ReadString(strPipeUnit);//��ȡ�ܵ���λ
	while ( strPipeUnit.IsEmpty() )
	{
		file.ReadString(strPipeUnit);
	}
	if ( -1 != strPipeUnit.Find( _T("Pipe Data Units") ) )
	{
		int pos = strPipeUnit.Find( _T("=") );
		if ( -1 != pos )
		{
			strPipeUnit = strPipeUnit.Mid(pos+1);
			strPipeUnit.TrimLeft();
			strPipeUnit.TrimRight();
		}
		bUnitFlag = TRUE;//��ȷ��ȡ���ܵ����Զ�Ӧ�ĵ�λ��Ϣ
	}

	if ( bPipeFlag && bUnitFlag )
	{
		m_strPipeOrder = strPipeOrder;
		m_strPipeUnit  = strPipeUnit;

        OutMgr &outMgr = m_outModel.SteadyOut().ComponentOutMgr().PipeOutMgr();
		LoadShowAtt(outMgr);
		LoadAllAtt(outMgr);
		return TRUE;
	}
	return FALSE;
}

/************************************************************************
�汾: 8.0  ����ʱ��: [2009/4/22]  ����: [ue8] ������:
����: ������ܵ����ݶ�Ӧ��key�Ͷ�Ӧ�ĵ�λ���浽bat�ļ�                                                             
����:                                                               
���:                                                              
< �޸��� >    < ʱ�� >     < �汾 >        < ���� >                                                                               
************************************************************************/
BOOL PagePipeOutControl::Save(CStdioFile& File)
{
	CString strPipeOrder = _T("Pipe Data Order=");
	m_strPipeOrder.TrimRight( _T("\n") );
	strPipeOrder += m_strPipeOrder;
	strPipeOrder += _T("\n");
	File.WriteString(strPipeOrder);

	CString strUnitOrder = _T("Pipe Data Units=");
	m_strPipeUnit.TrimRight( _T("\n") );
	strUnitOrder += m_strPipeUnit;
	strUnitOrder += _T("\n");
	File.WriteString(strUnitOrder);
	return TRUE;
}
// DlgOutPutControl.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AutoPFA.h"
#include "DlgOutPutControl.h"


// CDlgOutPutControl �Ի���

IMPLEMENT_DYNAMIC(CDlgOutPutControl, CDialog)

CDlgOutPutControl::CDlgOutPutControl(PFAOutModel& outModel, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgOutPutControl::IDD, pParent)
	,m_PagePipe(outModel)
	,m_PageJun(outModel)
{
    m_pAutoPFADoc = NULL;
}

CDlgOutPutControl::~CDlgOutPutControl()
{
}

void CDlgOutPutControl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB, m_tab);
}


BEGIN_MESSAGE_MAP(CDlgOutPutControl, CDialog)
	ON_BN_CLICKED(IDOK, &CDlgOutPutControl::OnBnClickedOk)
	ON_BN_CLICKED(ID_BTN_IMPORT, &CDlgOutPutControl::OnBnImport)
	ON_BN_CLICKED(ID_BTN_SAVE, &CDlgOutPutControl::OnBnSave)
END_MESSAGE_MAP()


// CDlgOutPutControl ��Ϣ�������

BOOL CDlgOutPutControl::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_tab.AddPage( _T("�ܵ�"), &m_PagePipe, IDD_PAGE_PIPEOUTCONTROL, TRUE );
	m_tab.AddPage( _T("�ڵ�"), &m_PageJun, IDD_PAGE_PIPEOUTCONTROL, TRUE );
	m_tab.Show();
	return TRUE;
}

void CDlgOutPutControl::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_PagePipe.UpData();
	m_PageJun.UpData();
/*	m_pAutoPFADoc->OnViewOutput();*/
	OnOK();
}

void CDlgOutPutControl::SetCurDoc( CAutoPFADoc* pDoc )
{
    m_pAutoPFADoc = pDoc;
}

void CDlgOutPutControl::OnBnImport()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	static TCHAR BASED_CODE szFilter[] = _T("BAT�ļ�(*.bat)|*.bat| �����ļ�(*.*)|*.*||");

	CFileDialog dlg( TRUE,_T("bat"),NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,szFilter,this);
	if(IDOK == dlg.DoModal())
	{
		CString strFileName = dlg.GetPathName();
		CStdioFile File;
		if( File.Open( strFileName, CFile::modeRead ) )
		{
			CString strTemp;
			File.ReadString(strTemp);
			if ( strTemp == _T("AutoPFA Output Preferences") )
			{
				File.ReadString(strTemp);
				if ( strTemp == _T("[OUTPUT PREFERENCES]") )
				{
					m_PagePipe.Read(File);
					m_PageJun.Read(File);
				}
			}
			File.Close();
		}
	}
}

void CDlgOutPutControl::OnBnSave()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	static TCHAR BASED_CODE szFilter[] = _T("BAT�ļ�(*.bat)|*.bat| �����ļ�(*.*)|*.*||");

	CFileDialog dlg( FALSE,_T("bat"),NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,szFilter,this);
	if(IDOK == dlg.DoModal())
	{
		CString strFileName = dlg.GetPathName();
		CStdioFile File;
		if( File.Open( strFileName, CFile::modeCreate | CFile::modeWrite ) )
		{
			CString str = _T("AutoPFA Output Preferences\n");
			File.WriteString(str);
			str = _T("[OUTPUT PREFERENCES]\n");
			File.WriteString(str);

			m_PagePipe.Save(File);
			File.Close();
		}
	}
}

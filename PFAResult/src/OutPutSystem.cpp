// OutPutSystem.cpp: implementation of the OutPutSystem class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PipeOutShow.h"
#include "JunOutShow.h"
#include "OutPutSystem.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
OutPutSystem::OutPutSystem()
{

}

OutPutSystem::~OutPutSystem()
{

}

#include <locale.h>
void OutPutSystem::Read(LPCTSTR filename)//���ļ��ж�ȡ��Ϣ��ÿ�ζ�һ��
{
	//��������������Ի�������Ϊ��������õĻ������������ĵ��ı���ʱ��������������룬
	//�������ʱ������Ϊ���Ļ����������ļ����ٻ�ԭΪԭ�������Ի�����
	char* old_locale=_strdup( setlocale(LC_CTYPE,NULL) ); 
	setlocale( LC_CTYPE,"chs");
	CStdioFile File;
	if (!File.Open(filename,CFile::modeRead|CFile::typeText/*CFile::typeText*/))
	{
		exit(0);
	}
	File.ReadString(m_JunKey);
	File.ReadString(m_JunId);
	File.ReadString(m_JunUnit);
	File.ReadString(m_JunName);

	File.ReadString(m_PipeKey);
	File.ReadString(m_PipeId);
	File.ReadString(m_PipeUnit);
	File.ReadString(m_PipeName);

	File.Close();
	setlocale( LC_CTYPE, old_locale ); //��ԭ�������������
}

void OutPutSystem::InitData(CString InData,CString str[50],TCHAR chSeparator)
{
	InData.TrimLeft();
	int nIdex=0;
	int i;
	int strj=0;
	
	for (i=0;i<50;i++)
	{
		nIdex=InData.Find(chSeparator);
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
		str[strj]=_T("0");
	}
	
}

CString OutPutSystem::Read(CString InData, TCHAR chSeparator)
{
	CString m_strData;
	InData.TrimLeft();
	int nIndex = InData.Find(chSeparator);
	if(nIndex != -1)
	{
		InData.Delete(0,nIndex);//ɾ���ָ����ǰ����ַ�
		InData.SetAt(0,' ');//�ָ��������Ϊ��
	}
	return InData;
}

CString OutPutSystem::GetOutData(CString StrTemp)
{
	StrTemp.TrimLeft();
	StrTemp=Read(StrTemp,'=');
	return StrTemp;
}
void OutPutSystem::InitOutPutSystem()
{
	TCHAR exeFullPath[MAX_PATH];
	::GetModuleFileName(NULL,exeFullPath,MAX_PATH);
	CString strPath(exeFullPath);
	int index = strPath.ReverseFind('\\');
	ASSERT(index != -1);
	strPath = strPath.Left(index+1);
	strPath += _T("outputref.txt");
	Read(strPath);

	m_JunKey = GetOutData(m_JunKey);//�õ��ڵ�������Ϣ
	m_JunId = GetOutData(m_JunId);
	m_JunUnit = GetOutData(m_JunUnit);
	m_JunName = GetOutData(m_JunName);

	m_PipeKey = GetOutData(m_PipeKey);//�õ��ܵ��������Ϣ
	m_PipeId = GetOutData(m_PipeId);
	m_PipeUnit = GetOutData(m_PipeUnit);
	m_PipeName = GetOutData(m_PipeName);

	InitData(m_JunKey,m_JunKeyArray);//�ѽڵ����Ϣ��������
	InitData(m_JunId,m_JunIdArray);
	InitData(m_JunUnit,m_JunUnitArray);
	InitData(m_JunName,m_JunNameArray);

	InitData(m_PipeKey,m_PipeKeyArray);//�ѹܵ�����Ϣ��������
	InitData(m_PipeId,m_PipeIdArray);
	InitData(m_PipeUnit,m_PipeUnitArray);
	InitData(m_PipeName,m_PipeNameArray);

	for (int i=0;i<50;i++)//ʹID��������CStringת��ΪUnitTypeId
	{
		if (m_PipeIdArray[i]==_T("None"))
		{
			m_PipeTypeId[i]=None;
		}
		if(m_PipeIdArray[i]==_T("Pressure"))
		{
			m_PipeTypeId[i]=Pressure;
		}
		if (m_PipeIdArray[i]==_T("VolumetricFlow"))
		{
			m_PipeTypeId[i]=VolumetricFlow;
		}
		if (m_PipeIdArray[i]==_T("Velocity"))
		{
			m_PipeTypeId[i]=Velocity;
		}
		if (m_PipeIdArray[i]==_T("Length"))
		{
			m_PipeTypeId[i]=Length;
		}
		if (m_PipeIdArray[i]==_T("Density"))
		{
			m_PipeTypeId[i]=Density;
		}
		if (m_PipeIdArray[i]==_T("Diameter"))
		{
			m_PipeTypeId[i]=Diameter;
		}
		if (m_PipeIdArray[i]==_T("Area"))
		{
			m_PipeTypeId[i]=Area;
		}
		if (m_PipeIdArray[i]==_T("MassFlow"))
		{
			m_PipeTypeId[i]=MassFlow;
		}
		if (m_PipeIdArray[i]==_T("PressPerMeter"))
		{
			m_PipeTypeId[i]=PressPerMeter;
		}
		if (m_PipeIdArray[i]==_T("Resistance"))
		{
			m_PipeTypeId[i]=Resistance;
		}
		if (m_PipeIdArray[i]==_T("Viscosity"))
		{
			m_PipeTypeId[i]=Viscosity;
		}
		if (m_PipeIdArray[i]==_T("0"))
		{
			m_PipeTypeId[i]=None;
		}

	}	
		
	for ( int j=0; j<50; j++)
	{
		if (m_JunIdArray[j]==_T("None")||m_JunIdArray[j]==_T("0"))
		{
			m_JunTypeId[j]=None;
		}
		if (m_JunIdArray[j]==_T("Pressure"))
		{
			m_JunTypeId[j]=Pressure;
		}
		if (m_JunIdArray[j]==_T("VolumetricFlow"))
		{
			m_JunTypeId[j]=VolumetricFlow;
		}
		if (m_JunIdArray[j]==_T("MassFlow"))
		{
			m_JunTypeId[j]=MassFlow;
		}
		if (m_JunIdArray[j]==_T("Length"))
		{
			m_JunTypeId[j]=Length;
		}

	}
		
	for (int k=0; k<50; k++)//��ʼ���ڵ�͹ܵ����������
	{
		
		m_JunOutArray.SetSize(50);
		m_PipeOutArray.SetSize(50);
		m_JunOutArray[k].SetKey(m_JunKeyArray[k]);
		m_JunOutArray[k].SetTypeId(m_JunTypeId[k]);
		m_JunOutArray[k].SetStrUnit(m_JunUnitArray[k]);
		m_JunOutArray[k].SetStrName(m_JunNameArray[k]);
		m_JunOutArray[k].SetShow(FALSE);
		
		m_PipeOutArray[k].SetKey(m_PipeKeyArray[k]);
		m_PipeOutArray[k].SetTypeId(m_PipeTypeId[k]);
		m_PipeOutArray[k].SetStrUnit(m_PipeUnitArray[k]);
		m_PipeOutArray[k].SetStrName(m_PipeNameArray[k]);
		m_PipeOutArray[k].SetShow(FALSE);			
	}
}

PipeOutArray& OutPutSystem::GetPipeOutArray()
{
//	InitOutPutSystem();
	return m_PipeOutArray;//���عܵ�������Ϣ
}

JunOutArray& OutPutSystem::GetJunOutArray()
{
//	InitOutPutSystem();
	return m_JunOutArray;//���ؽڵ�������Ϣ
}


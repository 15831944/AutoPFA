// PersistentMgr.cpp: implementation of the PersistentMgr class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PersistentMgr.h"
#include "Driver.h"
#include "PersistentObj.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

PersistentMgr::PersistentMgr()
{
	m_factory = DriverFactory::Instance();
}

PersistentMgr::~PersistentMgr()
{

}

ErrorStatus::FileError PersistentMgr::Read(LPCTSTR filename,PersistentModel& model)
{
	ErrorStatus::FileError errorMark;

	Driver * pDriver = FindDriver(filename);
	if(pDriver == NULL)
	{
		errorMark = ErrorStatus::UnRegisterType;
	}
	else
	{
		 errorMark = pDriver->Read(filename,model);
		 delete pDriver;
		 pDriver = NULL;
	}
	return errorMark;
}

ErrorStatus::FileError PersistentMgr::Save(LPCTSTR filename,PersistentModel& model)
{
	ErrorStatus::FileError errorMark;

	Driver * pDriver = FindDriver(filename);
	if(pDriver == NULL)
	{
		errorMark = ErrorStatus::UnRegisterType;
	}
	else
	{
		 errorMark = pDriver->Save(filename,model);
		 delete pDriver;
		 pDriver = NULL;
	}
	return errorMark;
}



Driver* PersistentMgr::FindDriver(LPCTSTR filename)
{
	CString  strName(filename);
	CString  strExtensionName;
	int nIndex = strName.ReverseFind('.');
	if(-1 != nIndex)
	{
		int nCount = strName.GetLength()-nIndex-1;
		strExtensionName = strName.Right(nCount);
	}
	strExtensionName.MakeLower();
	if("fth"==strExtensionName)
	{//Ĭ��Ϊʹ��imp��ʽ�������򣬷���������������
		strExtensionName = "imp";
		PersistentObj::isImpFile = FALSE ;
	}
	else
	{
		PersistentObj::isImpFile = TRUE ;   //������ᵼ�¶�Fth�ļ�����Imp���� by chf
		if("imp"!=strExtensionName && "pcf"!=strExtensionName)
		{//Ĭ��Ϊʹ��imp��ʽ�������򣬷���������������
			strExtensionName = "imp";
		}
	}
	return m_factory->CreatObject(strExtensionName); 
}

/*************************************************
  Copyright (C), 1988-2006, UESOFT Co., Ltd.
  File name:      UEADORecordset.h
  Author:         ���
  Version:        1.0
  Date:           2006.8.22
  Description:    UEADORecordset����һ����ADO����
				  �����ݿ��ļ��ж����ļ�¼����
  Others:         
  Function List:  
    1. BatchUpdate:�Լ�¼���������¡�
	2. Close:�رռ�¼��
	3. Delete:ɾ����ǰ��¼
	4. GetBool:�ӵ�ǰ��¼�ж�ȡһ��BOOLֵ
	5. GetDouble:�ӵ�ǰ��¼�ж�ȡһ��Doubleֵ
	6. GetFloat:�ӵ�ǰ��¼�ж�ȡһ��Floatֵ
	7. GetLong:�ӵ�ǰ��¼�ж�ȡһ��Longֵ
	8. GetRecordCount:��ȡ��ǰ��¼���ļ�¼��
	9. GetShort:�ӵ�ǰ��¼�ж�ȡһ��Shortֵ
	10.GetString:�ӵ�ǰ��¼�ж�ȡһ���ַ���ֵ
	11.Get_variant_t�ӵ�ǰ��¼�ж�ȡһ������ֵ
	12.IsBOF:�ж��Ƿ�λ�ڼ�¼�����ʼ
	13.IsEOF:�ж��Ƿ�λ�ڼ�¼������ĩβ
	14.IsEmpty:�жϼ�¼���Ƿ�Ϊ��
	15.MoveFirst:�ƶ�����¼�����ʼλ��
	16.MoveLast:�ƶ�����¼�������λ��
	17.MoveNext:�ƶ�����¼���е�ǰ��¼����һ��λ��
	18.MovePrevious:�ƶ�����¼���е�ǰ��¼��ǰһ��λ��
	19.NewRecord:���¼��������һ������Ϊ�յ��¼�¼
	20.SetBool:���¼����ǰλ��дһ��BOOLֵ
	21.SetDouble:���¼����ǰλ��дһ��Doubleֵ
	22.SetFloat:���¼����ǰλ��дһ��Floatֵ
	23.SetLong:���¼����ǰλ��дһ��Longֵ
	24.SetShort:���¼����ǰλ��дһ��shortֵ
	25.SetString:���¼����ǰλ��дһ���ַ���
	26.Set_variant_t:���¼����ǰλ��дһ������ֵ
	27.Update:���µ�ǰ��¼
*************************************************/

// UEADORecordset.h: interface for the UEADORecordset class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UEADORECORDSET_H__2CE0052C_1060_423F_9513_7FF5AC552648__INCLUDED_)
#define AFX_UEADORECORDSET_H__2CE0052C_1060_423F_9513_7FF5AC552648__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "UEADO.h"
#include "UERecordset.h"
#include "DataBaseDriverHeader.h"

class DataBaseDriver_Exp  UEADORecordset : public UERecordset  
{
public:

	UEADORecordset(_RecordsetPtr m_pRecordset);
	UEADORecordset();
	virtual ~UEADORecordset();
public:
	void Delete();

	BOOL GetBool(const StdString& strIndex) const;
	StdString GetString(const StdString& strIndex) const;
	FLOAT GetFloat(const StdString& strIndex) const;
	DOUBLE GetDouble(const StdString& strIndex) const;
	LONG GetLong(const StdString& strIndex) const;
	short GetShort(const StdString& strIndex) const;
	_variant_t Get_variant_t(const StdString& strIndex) const;

	void NewRecord();
	
	void SetBool(const StdString& strIndex, bool bValue);
	void SetString(const StdString& strIndex, const StdString& strValue);
	void SetFloat(const StdString& strIndex, FLOAT fValue);
	void SetDouble(const StdString& strIndex, DOUBLE dbValue);
	void SetLong(const StdString& strIndex, LONG nValue);
	void SetShort(const StdString& strIndex, SHORT nValue);
	void Set_variant_t(const StdString& strIndex,_variant_t vr);
	
	void BatchUpdate();
	BOOL Update();

	void MovePrevious();
	void MoveLast();
	void MoveNext();
	void MoveFirst();

	BOOL IsEOF() const;
	BOOL IsBOF() const;
	BOOL IsEmpty() const;
	void Close();
	
	INT GetRecordCount() const;

private:
	_RecordsetPtr m_pRecordset;//��װ��_Recordset������ָ��
};

#endif // !defined(AFX_UEADORECORDSET_H__2CE0052C_1060_423F_9513_7FF5AC552648__INCLUDED_)

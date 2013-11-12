// Manipulator.h: interface for the Manipulator class.
/*
 * Copyright (C), 2006,��ɳ���������˾CAE������
 * All rights reserved.
 *
  �ļ����ƣ�Manipulator.h
  ժҪ��    
  author  : LSP          
*/
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MANIPULATOR_H__35E8E803_FA49_459E_A248_C582931FFAD0__INCLUDED_)
#define AFX_MANIPULATOR_H__35E8E803_FA49_459E_A248_C582931FFAD0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
class ComponentManager;
class WorkSpaceRef;

class Manipulator  
{
public:

	//��point�Ƿ��ڵ�ǰ����ͼ����
	virtual BOOL IsManipulator(CPoint point)=0;
	//��������ƶ���Ϣ����
	virtual void Move(UINT nFlags,CPoint point,CDC* pDc)=0;
	virtual void UpClick(UINT nFlags, CPoint point)=0;
	virtual void DownClick(UINT nFlags, CPoint point)=0;
	virtual BOOL DbClick(UnitSubSystem &UnitSys);
	virtual Manipulator* Clone();
	//�õ��������͵�ID��
	virtual int  CetTypeID()=0;
	virtual void Delete()=0;
	//�ı䵱ǰ������ͼ�ε���ɫ��Ϊ�����ı��
	virtual void DrawMark(CDC* pDc,WorkSpaceRef &ref)=0;
	//�õ���ǰ����ͼ�ε�����
	virtual CRect Region(CPoint pt)const=0;
	Manipulator();
	virtual ~Manipulator();

protected:
	BOOL IsInClient(CPoint pt);
	
};

#endif // !defined(AFX_MANIPULATOR_H__35E8E803_FA49_459E_A248_C582931FFAD0__INCLUDED_)

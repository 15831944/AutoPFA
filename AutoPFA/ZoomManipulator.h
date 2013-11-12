// ZoomManipulator.h: interface for the ZoomManipulator class.
/*
 * Copyright (C), 2006,��ɳ���������˾CAE������
 * All rights reserved.
 *
  �ļ����ƣ�ZoomManipulator.h
  ժҪ��    
  author  : LSP          
*/
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZOOMMANIPULATOR_H__525547EE_8046_4734_A320_1752CD3CD729__INCLUDED_)
#define AFX_ZOOMMANIPULATOR_H__525547EE_8046_4734_A320_1752CD3CD729__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Manipulator.h"
class CAutoPFAView;
class ZoomManipulator : public Manipulator  
{
public:
	CRect Region(CPoint pt)const;
	int  CetTypeID();
	void Move(UINT nFlags,CPoint point,CDC* pDc);
	void UpClick(UINT nFlags, CPoint point);
	void DownClick(UINT nFlags, CPoint point);
	void Delete();
	void DrawMark(CDC* pDc,WorkSpaceRef &ref);
	BOOL IsManipulator(CPoint point);
	static ZoomManipulator* Instance(CAutoPFAView *pView);
	virtual ~ZoomManipulator();
private:
	ZoomManipulator();
	ZoomManipulator(const ZoomManipulator&);
	ZoomManipulator& operator=(const ZoomManipulator&);
	CAutoPFAView *m_pView;
	CRect m_Rc;
	BOOL m_bManipulator;
	CPoint m_downPt;
};

#endif // !defined(AFX_ZOOMMANIPULATOR_H__525547EE_8046_4734_A320_1752CD3CD729__INCLUDED_)

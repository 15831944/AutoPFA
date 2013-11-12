// Graphics.h: interface for the Graphics class.
/*
 * Copyright (C), 2006,��ɳ���������˾CAE������
 * All rights reserved.
 *
  �ļ����ƣ�Graphics.h
  ժҪ��    
  author  : LSP          
*/
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRAPHICS_H__A8AD932C_B23F_4493_B306_A3CF5705C5E9__INCLUDED_)
#define AFX_GRAPHICS_H__A8AD932C_B23F_4493_B306_A3CF5705C5E9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class Graphics  
{
public:
	void DrawText(CDC *pDc,CString strText, CPoint point);
	Graphics();
	virtual ~Graphics();
	virtual BOOL Pick(CPoint point,int Size=0)=0;
	virtual void Draw(CDC* pDc,COLORREF color,int nStyle,int nWidth,int Size=0)=0;
	virtual void DrawMark(CDC* pDc,COLORREF color,int nStyle,int nWidth,int Size=0)=0;
};

#endif // !defined(AFX_GRAPHICS_H__A8AD932C_B23F_4493_B306_A3CF5705C5E9__INCLUDED_)

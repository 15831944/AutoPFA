// BrachJunStrategy.h: interface for the BrachJunStrategy class.
/*
 * Copyright (C), 2006,��ɳ���������˾CAE������
 * All rights reserved.
 *
  �ļ����ƣ�BrachJunStrategy.h
  ժҪ��    ��֧�߽�������
  author  : LSP           
*/
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BRACHJUNSTRATEGY_H__361CC2F3_1084_4BA7_80AE_F71BCAB7DACD__INCLUDED_)
#define AFX_BRACHJUNSTRATEGY_H__361CC2F3_1084_4BA7_80AE_F71BCAB7DACD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
class EndListRef;

class BrachJunStrategy  
{
public:
	static BrachJunStrategy* Instance();
	virtual ~BrachJunStrategy();
protected:
	void Calc(EndListRef &jun,double dOutMass);
	BrachJunStrategy();
private:
	double CalcPress(EndListRef &jun,double dOutMass);
	BrachJunStrategy(const BrachJunStrategy &ref);
	BrachJunStrategy& operator=(const BrachJunStrategy &ref);
	friend class EndListRef;
};

#endif // !defined(AFX_BRACHJUNSTRATEGY_H__361CC2F3_1084_4BA7_80AE_F71BCAB7DACD__INCLUDED_)

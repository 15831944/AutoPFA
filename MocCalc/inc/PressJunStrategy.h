// PressJunStrategy.h: interface for the PressJunStrategy class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PRESSJUNSTRATEGY_H__1558AAF8_2438_403A_B2DE_FA559FC58EB0__INCLUDED_)
#define AFX_PRESSJUNSTRATEGY_H__1558AAF8_2438_403A_B2DE_FA559FC58EB0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
class EndListRef;
class EndInfo;

class PressJunStrategy  
{
public:
	static PressJunStrategy* Instance();
	virtual ~PressJunStrategy();
protected:
	PressJunStrategy();
	void CalcStatic(EndListRef &jun,double dStaticPress);
	void CalcStag(EndListRef &jun);
	void CalcStag(EndListRef &jun,double dStagPress);//���ö˵����ֹѹ��������
	void CalcStatic(EndInfo &end,double dStaticPress);
	void CalcStag(EndInfo &end);//����ǰ���ö˵�Ŀ�����ֹѹ��
	void CalcStag(EndInfo &end,double dStagPress);//���ö˵����ֹѹ��������
private:
	PressJunStrategy(const PressJunStrategy &ref);
	PressJunStrategy& operator=(const PressJunStrategy &ref);
	friend class EndListRef;
};

#endif // !defined(AFX_PRESSJUNSTRATEGY_H__1558AAF8_2438_403A_B2DE_FA559FC58EB0__INCLUDED_)

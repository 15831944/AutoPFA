// Junction.h: interface for the JunctionData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_JUNCTION_H__C69BB6F7_C789_4A29_92EC_342E3829BA9B__INCLUDED_)
#define AFX_JUNCTION_H__C69BB6F7_C789_4A29_92EC_342E3829BA9B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "PersistentObj.h"
#include "ListFlyWeightImp.h"
#include "RowObjectFace.h"

class AFX_EXT_CLASS JunctionData: public PersistentObj
{
public:
	ListImp<StrArray<1> > PipeID();
	void PipeID(ListImp<StrArray<1> >& list);
	int Key();
	int ID();
	CString Name();
	CString CenterPtX();
	CString CenterPtY();
	CString InEle();
	CString OutEle();
	CString EleUnit();
	CString RawKey();

	void RawKey(CString strValue);
	void InEle(CString strValue);
	void OutEle(CString strValue);
	void EleUnit(CString strValue);
	void Key(int iKey);
	void ID(int iID);
	void Name(CString strValue);
	void CenterPtX(CString strValue);
	void CenterPtY(CString strValue);
	CString DesignFactor();
	void DesignFactor(CString strValue);
	StrArray<3> InitGuess();
	void InitGuess(const StrArray<3>& strValue);
	StrArray<3> SpecialMark();
	void SpecialMark(const StrArray<3>& strValue);
public:
	void Init();
	BOOL Save(CStdioFile &file);
	BOOL Read(CStdioFile &file);
	BOOL Read(CString strData);
	JunctionData();
	virtual ~JunctionData();
protected:
	int PipeNum();
private:
	BOOL IsSameInEle();
	void InitData(CString strData);
	virtual void InitExtra(CString strData)=0;
	virtual CString GetDefaultData()=0;
	void InitArray();
	RowObjectFace<1>  m_TypeID;			//�ڵ����ͱ��ID
	RowObjectFace<1>  m_Number;            //�ڵ�Ԫ�����
	RowObjectFace<1>  m_UnKown1;           //9
	RowObjectFace<1>  m_UnKown2;			//1
	RowObjectFace<1>  m_Name;				//����
	RowObjectFace<1>  m_PipeNum;            //���ӹܵ�����
	TableData<1>      m_PipeArray;		    //��ڵ����ӵĹܵ���
	RowObjectFace<2>  m_CenterPt;			//����
	RowObjectFace<1>  m_JunSize;			//ͼ�γߴ�
	RowObjectFace<2>  m_JunState;		    //λͼ�ķ���\��һϵ��ͼ���е�λ��
	RowObjectFace<1>  m_JunPipeMark;       //�ܵ��������
	RowObjectFace<1>  m_LockMark;			//0��ʾû������ͼ��-1��ʾ����ͼ��
public:
	RowObjectFace<3>  m_EleArray;			//�ڵ����\���ڱ��\��λ
	//��fth�ļ�ʱ,ˮ���еı�߲��ǹ�������,Ҫ��ˮ�������ȡ������Ϊpublicʹ�������ReserviorData�������.
	//change by wenzk
private:
	RowObjectFace<5>  m_UnKown3;           //0\0\0\0\none(��һ������Ϊ���ڱ���Ƿ�����ڱ����ͬ)
	RowObjectFace<1>  m_DisignFactor;		//���������ʧ
	RowObjectFace<3>  m_InitGuess;			//��ʼ������²����ͣ�0��1��\��С\��λ
	RowObjectFace<3>  m_UnKown4;           //0\none\0
	RowObjectFace<1>  m_HandBook;			//�������ݿ��ֲ�����
	RowObjectFace<1>  m_PumpConfig;		    //[RAW DATA SETS]��[RAW DATA REFERENCES]�ı��
	RowObjectFace<3>  m_SpecialMark;		//ָ���ر��������ͱ��(3)
	RowObjectFace<1>  m_UnKown5;			//1		
	RowObjectFace<4>  m_LabLocation;		//������������ʾλ��(4)
	RowObjectFace<1>  m_Display;			//��������ʾ
	RowObjectFace<4>  m_UnKown6;			//5\-1\-1\25
	RowObjectFace<2>  m_notes;				//notes�ַ��ĸ���\notes������
	RowObjectFace<2>  m_UnKown7;			//1\-1
	RowObjectFace<5>  m_Font;				//��������5

	RowObjectFace<1>  m_UnKown9;			//0/2  δ֪
	RowObjectFace<1>  m_UnKown10;			//999  δ֪
	RowObjectFace<2> m_Fth1;                // δ֪ -1 3
	RowObjectFace<1> m_Fth2; 				//���ݿ���� 0 ѡ�����ݿ�; 1 �������ݿ�(Ĭ��)
	RowObjectFace<1> m_Fth3; 				//%ALL% �������ݿ�(ֻ��m_Fth2Ϊ1ʱ�Ż����һ��)
	RowObjectFace<1> m_Fth4; 				//�������ݿ���� 0 ѡ�����ݿ�; 1 �������ݿ�(Ĭ��) (����Ǳ���Ż����һ��)
	RowObjectFace<1> m_Fth5; 				//%ALL% �������ݿ�(ֻ��m_Fth4Ϊ1ʱ�Ż����һ��) (����Ǳ���Ż����һ��)
	RowObjectFace<1> m_Fth6; 				//��Ч����ʾ���� 3 ����Ԫ��; 4 ��ʱ
	RowObjectFace<1> m_Fth7; 				//��Ч��������λ Decimal/Percent
	TableData<1>     m_FthArray;		    //����m_Fth6���ֵ��2���������м��� �� 3*2/4*2,Ϊ��Ӧ��Ч���е�������
	RowObjectFace<1> m_Fth8;                //δ֪ 0
	RowObjectFace<4> m_Fth9;                //�������� ��ʱ��λ ��ʼʱ�� ����ʱ��
};

#endif // !defined(AFX_JUNCTION_H__C69BB6F7_C789_4A29_92EC_342E3829BA9B__INCLUDED_)

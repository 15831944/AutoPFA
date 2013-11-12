// PCFSurge.h: interface for the SurgeData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SURGEDATA_H__D101EBE3_BFC2_4B5A_9C19_6E86EE4A9C29__INCLUDED_)
#define AFX_SURGEDATA_H__D101EBE3_BFC2_4B5A_9C19_6E86EE4A9C29__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Junction.h"
#include "PCFJun.h"
//��ѹ��
class AFX_EXT_CLASS PCFSurge: public PCFJun   
{
public:
	static PCFJun* Creator();
	PCFSurge();
	virtual ~PCFSurge();
public:
	CString DistanceUnit();
	void DistanceUnit(CString strValue);
	StrArray<2> SurgeHeight();
	void SurgeHeight(const StrArray<2>& strValue);
	StrArray<2> ConstArea();
	void ConstArea(const StrArray<2>& strValue);
	StrArray<2> SurfacePress();
	void SurfacePress(const StrArray<2>& strValue);
	StrArray<5> Orifice();
	void Orifice(const StrArray<5>& strValue);
	StrArray<10> ShortPipe();
	void ShortPipe(const StrArray<10>& strValue);
	CString OneWay();
	void OneWay(CString strValue);
	StrArray<4> Vessel();
	void Vessel(const StrArray<4>& strValue);
	CString Variable();
	void Variable(CString strValue);
	StrArray<3> InitSurfaceH();
	void InitSurfaceH(const StrArray<3>& strValue);
	StrArray<5> Check();
	void Check(const StrArray<5>& strValue);

	void Init( const CStringArray& wordArray );
private:
//	void AppendArray();
//	void InitExtra(CString strData);
//	virtual CString GetDefaultData();
public:
//	TwoDTable m_AreaTable;
//	JunTransData m_TranData;	
private:
//	TableData<3> m_linkPipeK;			//����ӽڵ�����ܵ�ʱ�ܵ��˿�kϵ��
										//����ӽڵ������ܵ�ʱ�ܵ��˿�kϵ��
										//�ܵ��˿���ڵ��߾���
	RowObjectFace<1> m_EleUnit;			//�ܵ��˿���ڵ��߾��뵥λ
	RowObjectFace<2> m_SurgeHeight;			//��ѹ���ĸ߶�\��λ
	RowObjectFace<2> m_ConstArea;		//�����ֵ\��λ
	RowObjectFace<2> m_SurfacePress;	//����ѹ��\��λ
	RowObjectFace<5> m_Orifice;			//ѡ�н����װ�ģ�ͱ��\������ϵ��\������ϵ��\���ֵ\��λ
	RowObjectFace<10> m_ShortPipe;		    //0��û��ѡ��̹ܵ�ģ�ͣ�-1��ѡ��̹ܵ�ģ��
										//�̹ܵ�Ħ��ϵ��
										//�̹ܵ���ֱ��
										//�̹ܵ���ֱ����λ
										//�̹ܵ����
										//�̹ܵ������λ
										//�̹ܵ�����
										//�̹ܵ����ȵ�λ
										//�̹ܵ���߱仯
										//�̹ܵ���ߵ�λ
	RowObjectFace<1> m_OneWay;			//��One-Way Surge Tank��0��û��ѡ��-1ѡ������ģ��ֹ�ط������Ļ���ޡ�
	RowObjectFace<4> m_Vessel;			//ģ���������0��û��ѡ��-1��ѡ��
										//������ܵ��ܵ��ĸ߶�
										//������ܸ߶ȵ�λ
										//���ĳ���
	RowObjectFace<1> m_Variable;		//��ǣ�ѡ������㶨0������仯1
	//TwoDTable m_AreaTable;				//None��δ֪��\1��δ֪��
										//�仯���������
										//�߶ȵ�λ\�����λ
										//�߶Ⱥ����
	RowObjectFace<3> m_InitSurfaceH;	//�ȶ�״̬��ʼ������߶�0��û��ѡ��-1��ѡ��
										//�߶�ֵ
										//�߶ȵ�λ
	//JunTransData m_TranData;			//û�����ں���RowObjectFace<5> m_Periodic;
    									//û��RowObjectFace<1> m_ValueType;
										//û��RowObjectFace<1> m_Special;
										//û��RowObjectFace<1> m_Repeat1;
										//û��RowObjectFace<1> m_Repeat2
										//û��RowObjectFace<1> m_TranType;
	                                    //AFT�ļ���Bug���������ݲ��ܱ��浽�ļ�
	RowObjectFace<5> m_CheckValve;		//ֹ�ط�����ϵ��
										//ֹ�ط���ʼλ��0����1���ر�
										//�򿪷���Deltaѹ����ˮͷ��ѹ������0��ˮͷ1��ѹ��
										//ѹ��ֵ
										//ѹ����λ


};

#endif // !defined(AFX_SURGEDATA_H__D101EBE3_BFC2_4B5A_9C19_6E86EE4A9C29__INCLUDED_)

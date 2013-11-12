// Pump.h: interface for the Pump class.
/*
 * Copyright (C), 2006,��ɳ���������˾CAE������
 * All rights reserved.
 *
  �ļ����ƣ�Pump.h
  ժҪ��    
  author  : LSP          
*/
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PUMP_H__3028A462_3227_4AA8_B028_35251C8D57CC__INCLUDED_)
#define AFX_PUMP_H__3028A462_3227_4AA8_B028_35251C8D57CC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Jun.h"
#include "PumpTransient.h"
#include "Configuration.h"

class Pump : public Jun  
{
public:
	CBitmap& GetBitMap();
	static void Instance();
	NameArray& GetArray();
	static Component* CreatPump();
	Pump();
	virtual ~Pump();

private:
	ScenarioObject* DoClone();

public:
	void DelLinkPipeInfo(UINT nKey);
	
	void SaveData();
	void InitData();
	BOOL Show(UnitSubSystem &UnitSys,ComponentManager *pManager, BOOL bDlgReadOnly = FALSE);//������������ʾ����ʾ�ڵ����ԵĶԻ����ﲻ���޸Ľڵ��κ�����
	BOOL Save(Junperisist *pPersistent);
	BOOL Read(Junperisist *pPersistent);
	CString GetTypeName();
	int GetID();
	static const int m_nTypeID;
private:
	BOOL CanLink(int nMaxLink,int nKey);
	void AddLinkPipeInfo(UINT nKey);
private:
	void EmptyPipeInfo();
	static NameArray s_StateName;
    static CBitmap m_bitmap;
	static CString s_typeName;

public:
	virtual Transient* GetTransient();
    static StrFlyWeight			ms_PumpType;				//��ģ�͵�����0�������ߣ�1��ָ���������2��ָ����������
	static ArrayFlyWeight<3>	ms_PumpFlow;				//��������\������С\��λ
	static StrFlyWeight			ms_SpeedRatio;				//���ٱõ�������Ա����ߵ����ʣ�1����ʾ100%��
	static ArrayFlyWeight<4>	ms_PumpControl;				//���Ʊ����ͣ�0��û�п��ƣ�1�������ѹ��/ˮͷ���ƣ�3�������ѹ��/ˮͷ���ƣ�2����������
															//���Ƶ��������0��ˮͷ/ˮͷ��ʧ/�������1��ѹ��/ѹ����ʧ/��������
															//���Ƶ����ֵ
															//���Ƶ������λ
	static StrFlyWeight			ms_ControlApply;            //���ƶ�Ӧ��������ã�0�����ǿ���1��ѹ��������������2��ѹ�����ڿ������ã�
	static StrFlyWeight			ms_PressType;				//0��ͣ��ѹ��1����̬ѹ��
	static ArrayFlyWeight<4>	ms_SubmergePump;           	//0��Ǳˮ��û��ѡ��-1��Ǳˮ��ѡ��
															//ѹ��������0��ˮͷ1��ѹ��
															//�����ѹ��ֵ
															//�����ѹ����λ
	static StrFlyWeight			ms_ExitCheck;				//-1��ѡ�����ֹ�ط���0��û��ѡ�����ֹ�ط�
	static NumFlyWeight			ms_CloseVel;		        //�رշ��ŵ���С�ٶ�\�ٶȵ�λ
	static StrFlyWeight			ms_antiReverse;				//-1��û��ѡ�����Ʊ÷�ת��0ѡ�����Ʊ÷�ת
	static ArrayFlyWeight<3>	ms_ReOpenPress;				//���´򿪷���Delta(ѹ����ˮͷ)0��ˮͷ1��ѹ��\ѹ��ֵ\��λ
	static StrFlyWeight			ms_PumpSet;					//�û��飬�����ã��õ������������ã�����+�õ�����,0:����
    static PumpTransient        ms_Transient; 
	static Configuration        ms_Configuration;
public:
	void Status(ComponentStatus &ref,BOOL bTrans=TRUE);
	static const CmbDataItem    ms_TransModel1[2];           //�ݻ���˲��ģ��
	static const CmbDataItem    ms_TransModel2[8];           //���ı�˲��ģ��

private:
	int m_nTran1Num;				//˲�����ݱ�1��������
	int m_nTran2Num;				//˲�����ݱ�2��������
	int m_nFourQuadNum;				//������������������

private:
	int m_nCurve1;
	int m_nCurve2;
	int m_nCurve3;
};

inline CBitmap& Pump::GetBitMap()
{
	return m_bitmap;
}

inline NameArray& Pump::GetArray()
{
	return s_StateName;
}

#endif // !defined(AFX_PUMP_H__3028A462_3227_4AA8_B028_35251C8D57CC__INCLUDED_)

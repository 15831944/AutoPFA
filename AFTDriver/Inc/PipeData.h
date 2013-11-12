// PipeData.h: interface for the PipeData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PIPEDATA_H__A4ABFA5F_1B98_4C9C_8F67_D6EE18E977E2__INCLUDED_)
#define AFX_PIPEDATA_H__A4ABFA5F_1B98_4C9C_8F67_D6EE18E977E2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "PersistentObj.h"
#include "RowObjectFace.h"

class AFX_EXT_CLASS PipeData:public PersistentObj
{
public:
	void Name(CString strValue);
	void EndPtX(CString strValue);
	void StartPtX(CString strValue);
	void EndPtY(CString strValue);
	void StartPtY(CString strValue);
	void InJunID(CString strValue);
	void OutJunID(CString strValue);
	void InDia(CString strValue);
	void InDiaUnit(CString strValue);
	void Len(CString strValue);
	void LenUnit(CString strValue);
	void WaveSpeed(CString strValue);
	void WaveSpeedUnit(CString strValue);
	void B(CString strValue);
	void Material(CString strValue);
	void Size(CString strValue);
	void PipeType(CString strValue);
	void Thick(CString strValue);
	void ThickUnit(CString strValue);
	void Elasticity(CString strValue);
	void ElasticityUnit(CString strValue);
	void PossionRatio(CString strValue);
	void InDiaReduce(CString strValue);
	void CalcWave(CString strValue);
	void C1(CString strValue);
	void SupportType(CString strValue);
	void FrictionModel(CString strValue);
	void Friction(CString strValue);
	void FrictionUnit(CString strValue);
    void LocalK(CString strValue);
	void PipeFactor(CString strValue);
	void FitFactor(CString strValue);
	void InitFlow(const StrArray<3>& strValue);
	void SectionNum(CString strValue);
	void ParaNum(CString strValue);
	void PartFull(CString strValue);

	CString PartFull();
	CString LocalK();
	CString PipeFactor();
	CString FitFactor();
	StrArray<3> InitFlow();
	CString SectionNum();
	CString ParaNum();
	CString Material();
	CString Size();
	CString PipeType();
	CString Thick();
	CString ThickUnit();
	CString Elasticity();
	CString ElasticityUnit();
	CString PossionRatio();
	CString InDiaReduce();
	CString CalcWave();
	CString C1();
	CString SupportType();
	CString FrictionModel();
	CString Friction();
	CString FrictionUnit();
	CString InDia();
	CString InDiaUnit();
	CString Len();
	CString LenUnit();
	CString WaveSpeed();
	CString WaveSpeedUnit();
	CString B();
	CString InJunID();
	CString OutJunID();
	CString Name();
	CString EndPtX();
	CString StartPtX();
	CString EndPtY();
	CString StartPtY();
	int GetNum();//�ܵ����
	void SetNum(int nNum);
	
	void Init();
	BOOL Save(CStdioFile &file);
	BOOL Read(CStdioFile &file);
	PipeData();
	virtual ~PipeData();

private:
	void InitData(CString strData);
	void InitArray();
	RowObjectFace<1>  m_Number;             //�ܵ����
	RowObjectFace<1>  m_Name;				//�ܵ�����
	RowObjectFace<1>  m_LenUnit;			//���ȵĵ�λ
	RowObjectFace<1>  m_EleUnit;			//��ߵ�λ
	RowObjectFace<1>  m_InEle;				//��ڱ��
	RowObject  m_OutLenEleList;		//�ܵ��ڲ���߼�ĩ�α������(����,���)
	RowObjectFace<1>  m_UnKown1;           //0
	RowObject  m_PtArray;			//�ܵ�ͼ�ε�ĸ���
	RowObjectFace<1>  m_UnKown2;			//None
	RowObjectFace<1>  m_definedMark;       //�ܵ������Ƿ���ɱ��0(Ϊ���)-1(�ܵ��������)
	RowObjectFace<1>  m_LockMark;			//0��ʾ����ͼ��-1��ʾ����ͼ��
	RowObjectFace<1>  m_InJunID;			//��ڽڵ��ID��
	RowObjectFace<1>  m_OutJunID;			//���ڽڵ��ID��
	RowObjectFace<2>  m_InDia;				//�ܵ��ھ����ܵ��ھ���λ
	RowObjectFace<4>  m_FrictionModel;		//Ħ����ģ�͡����͡�ϵ������λ
	RowObjectFace<1>  m_UnKown3;			//0
	RowObjectFace<1>  m_UnKown4;			//0
	RowObjectFace<3>  m_PipeAttr;			//�ܵ����ϡ��ߴ硢����
	RowObjectFace<2>  m_LocalK;			//�ܹ��ֲ���Kϵ��,�ֲ�������
	RowObjectFace<2>  m_DisignFactor;		//������ӹܵ�Ħ����\�ܵ�������ʧ
	RowObjectFace<3>  m_InitFlow;			//��ʼ������²����ͣ�0��1��2��\��С\��λ
	RowObjectFace<1>  m_FuildMark;			//����Ƿ�ʹ�ñ���������
	RowObjectFace<11>  m_FuildAttr;			//��������11������
	RowObjectFace<2>  m_SpecialMark;		//ָ���ر��������ͱ�ǣ�û��Ϊ0��\�����Ľڵ�Ĺرսڵ�
	RowObjectFace<1>  m_UnKown5;			//1		
	RowObjectFace<4>  m_LabLocation;		//������������ʾλ��(4)
	RowObjectFace<1>  m_Display;			//��������ʾ
	RowObjectFace<4>  m_UnKown6;			//5\-1\-1\25
	RowObjectFace<1>  m_PipeColor;			//�ܵ���ɫֵ��-1�����ù������ã�
	RowObjectFace<1>  m_UnKown7;			//-1
	RowObjectFace<1>  m_LineThick;			//���ߴ�ϸ����
	RowObject  m_Alerts;					//������Ƶ��������ͺ�\ ���2������С��1��\��ֵ\��λ
	RowObjectFace<2>  m_notes;				//
	RowObjectFace<1>  m_UnKown8;			//-1
	RowObjectFace<5>  m_Font;				//��������
	RowObjectFace<2>  m_PipeThick;			//�ܵ��ں�ֵ\��λ
	RowObjectFace<2>  m_ElasModulus;		//��������ֵ\��λ
	RowObjectFace<1>  m_PoissonRatio;		//���ɱ���
	RowObjectFace<7>  m_WaveSpeed;			//����(7)
	RowObjectFace<1>  m_UnKown9;			//1
	RowObjectFace<1>  m_UnKown10;			//-1
	RowObjectFace<1>  m_SectionNum;			//�ܶηֶ���ȡ��
	RowObjectFace<1>  m_UnKown11;			//-1
	RowObjectFace<1>  m_UnKown12;			//-1
	RowObjectFace<1>  m_UnKown13;			//-1
	RowObjectFace<1>  m_ParaNum;		    //�ܵ�������
	RowObjectFace<1>  m_PartFull;			//�ܵ����������ܰٷֱ�(-1:��ʾû��ѡ����һ��)
	RowObjectFace<1>  m_IDReduce;			//��ֱ�����ٰٷֱ�
	RowObjectFace<4>  m_Fth1;				///��������fth29��˵�ǵ�25~28λδ֪��None,0,None,None
	RowObjectFace<8>  m_Fth2;	            //��������fth29��˵�ǵ�25~28λδ֪��0,0,None,1,0,0,,1,
	RowObjectFace<1>   m_Fth3;				//None δ֪��
	RowObjectFace<1>  m_Fth4;			//���ΪNone�򣬺����0,0,;�����ΪNone�������AFT6.0��insulation������
	RowObject m_Fth5;
// 	RowObjectFace<6>  m_Fth5_1;
// 	RowObjectFace<13> m_Fth5_2;
	RowObjectFace<2>  m_Fth6;				//-1,0
};

#endif // !defined(AFX_PIPEDATA_H__A4ABFA5F_1B98_4C9C_8F67_D6EE18E977E2__INCLUDED_)

// PCFPumpData.h: interface for the PCFPumpData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PCFPUMPDATA_H__85B00E3B_4168_4A88_A0C0_5A58227C933E__INCLUDED_)
#define AFX_PCFPUMPDATA_H__85B00E3B_4168_4A88_A0C0_5A58227C933E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//��
#include "Junction.h"
#include "PumpConfig.h"
#include "JunTransData.h"
#include "PCFJun.h"
#include "RowObjectFace.h"
#include "RowObject.h"
class AFX_EXT_CLASS PCFPumpData : public PCFJun
{
public:
	static PCFJun* Creator();
	PCFPumpData();
	virtual ~PCFPumpData();
public:
	CString PumpType();
	void PumpType(CString strValue);
	StrArray<3> PumpFlow();
	void PumpFlow(const StrArray<3>& strValue);
	CString SpeedRatio();
	void SpeedRatio(CString strValue);
	StrArray<4> PumpControl();
	void PumpControl(const StrArray<4>& strValue);
	CString ControlApply();
	void ControlApply(CString strValue);
	CString PressType();
	void PressType(CString strValue);
	StrArray<4> SubmergePump();
	void SubmergePump(const StrArray<4>& strValue);
	CString ExitCheck();
	void ExitCheck(CString strValue);
	StrArray<2> CloseVel();
	void CloseVel(const StrArray<2>& strValue);
	CString AntiReverse();
	void AntiReverse(CString strValue);
	StrArray<3> ReOpenPress();
	void ReOpenPress(const StrArray<3>& strValue);
	CString PumpSet();
	void PumpSet(CString strValue);

	
private:
	void AppendArray();
	void InitExtra(CString strData);
	void Init( const CStringArray& wordArray );
// 	void Init(CString strData);
	virtual CString GetDefaultData();
public:
	PumpConfig       m_Config;
	JunTransData m_TranData;
private:
	RowObjectFace<1> m_PumpType;				//��ģ�͵�����0�������ߣ�1��ָ���������2��ָ����������
	RowObjectFace<3> m_PumpFlow;				//��������\������С\��λ
	
	RowObjectFace<1> m_SpeedRatio;				//���ٱõ�������Ա����ߵ����ʣ�1����ʾ100%��
	RowObjectFace<1> m_UnKown3;					////0��δ֪���ο����Ʒ��ſ�������
	RowObjectFace<4> m_PumpControl;				//���Ʊ����ͣ�0��û�п��ƣ�1�������ѹ��/ˮͷ���ƣ�3�������ѹ��/ˮͷ���ƣ�2����������
	//���Ƶ��������0��ˮͷ/ˮͷ��ʧ/�������1��ѹ��/ѹ����ʧ/��������
	//���Ƶ����ֵ
	//���Ƶ������λ
	RowObjectFace<1> m_ControlApply;            //���ƶ�Ӧ��������ã�0�����ǿ���1��ѹ��������������2��ѹ�����ڿ������ã�
	RowObjectFace<4> m_ViscosCorrection;		//ճ��������0����ʹ��ճ��������-1��ʹ��ճ��������
	//ѹ������ѡ��0���ٶ�����������BEF��1���û������������Ч�ʵ㣩
	//�û������ֵ
	//�û������ֵ�ĵ�λ
	RowObjectFace<1> m_NPSHRefValule;			//NPSH�ο�
	RowObjectFace<1> m_PressType;				//0��ͣ��ѹ��1����̬ѹ��
	RowObjectFace<4> m_SubmergePump;           	//0��Ǳˮ��û��ѡ��-1��Ǳˮ��ѡ��
	//ѹ��������0��ˮͷ1��ѹ��
	//�����ѹ��ֵ
	//�����ѹ����λ
	RowObjectFace<1> m_ExitCheck;				//-1��ѡ�����ֹ�ط���0��û��ѡ�����ֹ�ط�
	//	RowObjectFace<1> m_TranModel;				//˲��ģ��
	//	RowObjectFace<2> m_RotateInertia;			//ת���������ã��綯�������壩\ת��������λ
	//	RowObjectFace<1> m_Speed;					//�öת��
	RowObjectFace<1> m_PumpSet;					//�����ã��õ������������ã�����+�õ�����
	//	RowObjectFace<3> m_FourQuadrantData;        //����������Դ���\���������ݵ�����\�Ƕ�ѡ��0��1��
	//	RowObjectFace<6> m_UnKown4;					//None,2,0,None,,,
	RowObjectFace<2> m_CloseVel;		        //�رշ��ŵ���С�ٶ�\�ٶȵ�λ
	RowObjectFace<1> m_antiReverse;				//-1��û��ѡ�����Ʊ÷�ת��0ѡ�����Ʊ÷�ת
	RowObjectFace<3> m_ReOpenPress;				//���´򿪷���Delta(ѹ����ˮͷ)0��ˮͷ1��ѹ��\ѹ��ֵ\��λ
	
	typedef CArray<RowObject*,RowObject*>RowArrayRef;
	RowArrayRef   m_RowArray;
};

#endif // !defined(AFX_PCFPumpData_H__85B00E3B_4168_4A88_A0C0_5A58227C933E__INCLUDED_)

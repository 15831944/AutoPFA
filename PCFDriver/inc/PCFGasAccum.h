// PCFGasAccum.h: interface for the PCFGasAccum class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PCFGASACCUM_H__84567B8D_01F4_4FBE_AE5A_2CEA60C6E13E__INCLUDED_)
#define AFX_PCFGASACCUM_H__84567B8D_01F4_4FBE_AE5A_2CEA60C6E13E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//������
#include "Junction.h"
#include "PCFJun.h"

class AFX_EXT_CLASS PCFGasAccum : public PCFJun  
{
public:
	static PCFJun* Creator();
	PCFGasAccum();
	virtual ~PCFGasAccum();
public:
	CString Polytropic();
	void Polytropic(CString strValue);
	StrArray<2> InitVolume();
	void InitVolume(const StrArray<2>& strValue);
	StrArray<5> Orifice();
	void Orifice(const StrArray<5>& strValue);
	StrArray<10> ShortPipe();
	void ShortPipe(const StrArray<10>& strValue);
	StrArray<4> InitPress();
	void InitPress(const StrArray<4>& strValue);
	CString MaxVolume();
	void MaxVolume(CString strValue);
	CString MinVolume();
	void MinVolume(CString strValue);
	StrArray<3> GasVolume();
	void GasVolume(const StrArray<3>& m_GasVolume);

	void Init( const CStringArray& wordArray );
private:
	
private:
	RowObjectFace<1> m_Polytropic;			//�仯�ĳ���
	RowObjectFace<2> m_InitVolume;			//��ʼ���������
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
	RowObjectFace<4> m_InitPress;       //0:û��ѡ�����þ�̬������ѹ����-1:û��ѡ�����þ�̬������ѹ��
	//0��ѹ������Ϊˮͷ��1��ѹ������Ϊѹ��
	//ѹ����С\��λ
	RowObjectFace<1> m_MaxVolume;		//������
	RowObjectFace<1> m_MinVolume;		//��С���
	RowObjectFace<3> m_GasVolume;		//���ͣ�0����ʼ��ָ�������1����ʼ��ָ��ѹ����
	//��ʼ������ѹ��
	//��ʼ������ѹ����λ
};

#endif // !defined(AFX_PCFGASACCUM_H__84567B8D_01F4_4FBE_AE5A_2CEA60C6E13E__INCLUDED_)

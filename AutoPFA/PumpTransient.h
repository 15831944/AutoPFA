// PumpTransient.h: interface for the PumpTransient class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PUMPTRANSIENT_H__3575F9CC_126C_4F58_BEDF_0CD279A6E11E__INCLUDED_)
#define AFX_PUMPTRANSIENT_H__3575F9CC_126C_4F58_BEDF_0CD279A6E11E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Transient.h"

class PumpTransient : public Transient  
{
public:
	PumpTransient();
	virtual ~PumpTransient();
	const StrFlyWeight& TranModel();
	void TranModel(const StrFlyWeight& ref);
	const StrFlyWeight& Speed();
	void Speed(const StrFlyWeight& ref);
    const NumFlyWeight& RotateInertia();
	void RotateInertia(const NumFlyWeight& ref);
	const ArrayFlyWeight<3>& FourQuadrantData();
	void FourQuadrantData(const ArrayFlyWeight<3>& ref);
public:
	StrFlyWeight m_TranModel;				//��˲��ģ��
	NumFlyWeight m_RotateInertia;			//ת���������ã��綯�������壩\ת��������λ
	StrFlyWeight m_Speed;					//�öת��
	ArrayFlyWeight<3> m_FourQuadrantData;   // ����������Դ���\���������ݵ�����\�Ƕ�ѡ��0��1 
	TransDataTable<3> m_FourquadTable;

public:
	void InitData(ScenarioObject *pObject);
	BOOL SaveData(ScenarioObject *pObject,int &num1,int &num2,int &num3);
	void Instance(NameArray &array,int nKey);
	BOOL Save(TransDataPersistent &Persistent,int num1,int num2,int num3);
	BOOL Read(TransDataPersistent &Persistent);

};
/*----------------------------------------------*/
inline const StrFlyWeight& PumpTransient::TranModel()
{
	return m_TranModel;
}
/*----------------------------------------------*/
inline void PumpTransient::TranModel(const StrFlyWeight& ref)
{
	m_TranModel = ref;
}

/*----------------------------------------------*/
inline const StrFlyWeight& PumpTransient::Speed()
{
	return m_Speed;
}
/*----------------------------------------------*/
inline void PumpTransient::Speed(const StrFlyWeight& ref)
{
	m_Speed = ref;
}

/*----------------------------------------------*/
inline const NumFlyWeight& PumpTransient::RotateInertia()
{
	return m_RotateInertia;
}
/*----------------------------------------------*/
inline void PumpTransient::RotateInertia(const NumFlyWeight& ref)
{
	m_RotateInertia = ref;
}

/*----------------------------------------------*/
inline const ArrayFlyWeight<3>& PumpTransient::FourQuadrantData()
{
	return m_FourQuadrantData;
}
/*----------------------------------------------*/
inline void PumpTransient::FourQuadrantData(const ArrayFlyWeight<3>& ref)
{
	m_FourQuadrantData = ref;
}
#endif // !defined(AFX_PUMPTRANSIENT_H__3575F9CC_126C_4F58_BEDF_0CD279A6E11E__INCLUDED_)

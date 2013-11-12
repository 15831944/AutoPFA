// CalcCurveFace.h: interface for the CalcCurveFace class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CALCCURVEFACE_H__024BCC1B_30EC_435E_B245_97CE6CAA1F16__INCLUDED_)
#define AFX_CALCCURVEFACE_H__024BCC1B_30EC_435E_B245_97CE6CAA1F16__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
class CalcCurve;

class AFX_EXT_CLASS CalcCurveFace  
{
public:
	CalcCurveFace();
	virtual ~CalcCurveFace();
	ErrorStatus::FileError fireK(double &Data,StrArray<13> &Model);
	ErrorStatus::FileError LossType(int &Data,StrArray<13> &Model);
	ErrorStatus::FileError Save(CalcCurve &Data,StrArray<13> &Model);
										//��ʧģ��(1��Kϵ���㶨��2��Kϵ���仯��3����������)
										//Y������������ֱ��[ѹ������0��ˮͷ��1��ѹ��]
										//Y�������λ[ѹ����λ]
										//X������������ֱ��[����������ͣ�0���������1����������2������3����ټ��]
										//X�������λ[��λ]
										//x�����ȡֵ[�����ֵ�����ȡֵ]
										//��������[�������ͣ�-2��Kֵ�仯��1��ѹ����ʧ����ʽ��2��ѹ����ʧ�ڲ�ֵ��]
										//��ʽ�в����ͳ����ĸ���[]
										//��ʽ�еĲ����ͳ���a��b��c��d��e��ֵ[]
	ErrorStatus::FileError Save(CalcCurve &Data,StrArray<7> &Model,CString strXUnit,CString strYUnit);
										//�������ͣ�1��ѹ����ʧ����ʽ��2��ѹ����ʧ�ڲ�ֵ��
										//��ʽ�в����ͳ����ĸ���
										//��ʽ�еĲ����ͳ���a��b��c��d��e��ֵ
};

#endif // !defined(AFX_CALCCURVEFACE_H__024BCC1B_30EC_435E_B245_97CE6CAA1F16__INCLUDED_)

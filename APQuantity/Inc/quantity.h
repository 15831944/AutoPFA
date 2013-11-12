/*************************************************
  Copyright (C), 1988-1999, UESOFT Co., Ltd.
  File name:      Quantity.h
  Author:         ��尡�����
  Version:        1.0
  Date:           2006.8.9
  Description:    ��ͷ�ļ���Ҫ������һ��ģ���࣬�����������
				  ģ�����������T��������������ֵ���ͣ�T��ȡֵ��Χ
				  ��int,long,float,double�ȣ�ģ�����Dimensions
				  �����޶��������������ͣ������������ٶȣ������ȵȣ�
				  ģ�����DimensionsTrans_Type�Ǹ���������Ӧ�ĵ�λת����
				  ��ģ����Ϊ��λģ��������ģ��Ľӿڣ���Ҫʵ��������
				  ����λ���������㡣
  Others:         ��
  Function List:  
    1. GetDimension():ȡ�ø���������Ӧ�ĵ�λ������
	2. GetPrecision():ȡ���ڽ��бȽ����ʱ�õ��ľ���ֵ��
	3. GetValue():ȡ�ø�����������ֵ��
	4. IsSameDimensions():�жϸ�����������һ�������Ƿ�Ϊͬһ��������
	5. operator !=():�ж�����ͬ���������Ƿ���ȡ�
	6. operator * ():����������������*������
	7. operator + ():������ͬ������������+������
	8. operator - ():������ͬ������������-������
	9. operator / ():����������������/������
	10.operator = ():������ͬ���������н��и�ֵ��
	11.operator ==():�ж�����ͬ���������Ƿ���ȡ�
	12.Quantity():���캯��
	13.~Quantity():��������
	14.SetDimension():���õ�λ������
	15.SetPrecision():���ñȽϾ���ֵ��
	16.SetValue():������������ֵ��
  History:        ��
*************************************************/

#ifndef _QUANTITY_H
#define _QUANTITY_H


#include <cmath>
#include <assert.h>
#include <string>

#include "UnitHead.h"
#include "Result.h"
using namespace std;
#include "Quantity_share.h"

template<class T>
class Result;//��ǰ����

//����������ģ�壬������λ
template <class T,class Dimensions,class DimensionsTrans_Type>
class Quantity
{
public:
	static double precision;

public:
	static const UnitStringSet& UnitString() {
		return DimensionsTrans_Type::UnitString();
	}
private:
	T m_value;//�����ֵ��Զ�Ǹ��������ڱ�׼��λ�µ���ֵ
	int m_currentunit;//ʹ���߿�����Ϊ���������ڴ˵�λ������

	static Dimensions m_dimension;
	double m_precision;

	bool SetQuantity(const T &data, int currentunit)
	{
		bool IsTemp = this->GetDimension().IsTemprature();
		if (IsTemp)
		{
			this->m_value = TemperatureTrans::TemperatureTransToStd(data,currentunit);
		}
		else
		{
			double ratio = DimensionsTrans_Type::TransToStd(currentunit);
			this->m_value = ratio * data;
		}
		return true;
	}

public:
	StdString GetCurrentUnit() const
	{
		return DimensionsTrans_Type::UnitClassToUnitString( m_currentunit );
	}
	
	void SetCurrentUnit( const StdString& strCurrentUnit )
	{
		m_currentunit = DimensionsTrans_Type::UnitStringToUnitClass( strCurrentUnit );
	}

	void SetCurrentUnit( int nCurrentUnit )
	{
		m_currentunit = nCurrentUnit;
	}
	explicit Quantity(double dprecision = Quantity::precision)
	{	
		m_currentunit = DimensionsTrans_Type::GetStdUnitIndex();
		m_precision = dprecision;
		m_value = (T)(0);
	}

	Quantity( const Quantity& quantity )
	{
		*this = quantity;
	}
/*************************************************
  Function:       Quantity(const T &data, int currentunit)
  Description:    �������������󣬲����Ǳ�׼��λ��������ֵת��Ϊ
				  ��Ӧ�ı�׼��λ��������ֵ��
  Calls:          
	1.GetDimension()
	2.TemperatureTransToStd()
	3.TransToStd()
  Called By:      �ⲿ����ģ��
  Input:          
	1.data:��������currentunit��λ�����ϵ���ֵ
	2.currentunit:��λ����currentunit��ȡֵ��Χ
	��0������������λ������-1֮�䣨�����߽�ֵ��
  Output:         ���ڴ��в�������������
  Return:         ��
  Others:         ��
*************************************************/

	Quantity(const T &data, int currentunit,double dprecision = Quantity::precision)
	{
		m_currentunit = currentunit;
		m_precision = dprecision;
		SetQuantity(data,currentunit);
	}

/*************************************************
  Function:       Quantity(const T &data, const string currentunitstring)
  Description:    �������������󣬲����Ǳ�׼��λ������ֵת��Ϊ
				  ��Ӧ�ı�׼��λ��������ֵ��
  Calls:          
	1.UnitStringToUnitClass()
	2.Quantity(data,currentunit)
  Called By:      �ⲿ����ģ��
  Input:          
	1.data:��������currentunitstring��λ�����ϵ���ֵ
	2.currentunitstring:��λ���𣬸ò�������ΪԤ�ȵ�
	������ַ�������������һ����λ������mm�����ף�
  Output:         ���ڴ��в�������������
  Return:         ��
  Others:         ��
*************************************************/
	Quantity(const T &data, const StdString& currentunitstring,double dprecision = Quantity::precision)
	{
		int currentunit = DimensionsTrans_Type::UnitStringToUnitClass(currentunitstring);
		m_currentunit = currentunit;
		SetQuantity(data,currentunit);
		m_precision = dprecision;
	}


	//��÷Ǳ�׼��λ��������������ֵ
	T GetValue( const StdString& currentunitstring ) const
	{
		int currentunit = DimensionsTrans_Type::UnitStringToUnitClass( currentunitstring );
		bool IsTemp = this->GetDimension().IsTemprature();
		if (IsTemp)
		{
			return TemperatureTrans::TemperatureTransFromStd( this->m_value,currentunit );
		}
		else
		{
			double ratio = DimensionsTrans_Type::TransFromStd( currentunit );
			return ratio * this->m_value;
		}
	}

	T GetValue( int currentunit ) const
	{
		bool IsTemp = this->GetDimension().IsTemprature();
		if (IsTemp)
		{
			return TemperatureTrans::TemperatureTransFromStd( this->m_value,currentunit );
		}
		else
		{
			double ratio = DimensionsTrans_Type::TransFromStd( currentunit );
			return ratio * this->m_value;
		}
	}

	T GetValueOfCurrentUnit() const//�õ���ǰ��λ�����µ���ֵ
	{
		return GetValue( m_currentunit );
	}
	//��õ�λ����

	DimensionVector GetDimension() const
	{	
		return m_dimension.GetDimension();
	}

	//��ñ�׼��λ��������������ֵ

	T GetValue() const
	{	
		return m_value;
	}
private:
	//���õ�λ����
	void SetDimension(const DimensionVector& d)
	{	
		m_dimension.SetDimension(d);
	}
	
	//���ñ�׼��λ��������ֵ

	void SetValue(T data)
	{	
		m_value = data;	
	}

	//�õ�����ֵ
public:

	double GetPrecision() const
	{
		return m_precision;
	}
	
	//���þ���ֵ

	void SetPrecision(double pre)
	{
		m_precision = pre;
	}

	//�жϵ�λ�Ƿ���ͬ

	bool IsSameDimensions( const Result<T> &q) const
	{
		if (this->GetDimension() == q.GetDimension())
		{
			return true;
		}
		else
		{
			assert(0);
			return false;
		}
	}
	//���ؼӷ������
	
	Quantity<T,Dimensions,DimensionsTrans_Type> operator+
		( const Quantity<T,Dimensions,DimensionsTrans_Type> &y) const
	{
		Quantity<T,Dimensions,DimensionsTrans_Type> result;
		result.SetValue(this->GetValue() + y.GetValue());
		return result;
	}

	//���ؼӷ������
	
	Quantity<T,Dimensions,DimensionsTrans_Type> operator+
		( const Result<T> &y) const
	{
		Quantity<T,Dimensions,DimensionsTrans_Type> result;
		if (this->IsSameDimensions(y))
		{
			result.SetValue(this->GetValue() + y.GetValue());
		}
		else
		{
			assert(0);	
		}
		return result;
	}

	//���ؼ��������
	
	Quantity<T,Dimensions,DimensionsTrans_Type> operator-
		( const Quantity<T,Dimensions,DimensionsTrans_Type> &y) const
	{
		Quantity<T,Dimensions,DimensionsTrans_Type> result;
		result.SetValue(this->GetValue() - y.GetValue());
		return result;
	}
	
	Quantity<T,Dimensions,DimensionsTrans_Type> operator-
		( const Result<T> &y) const
	{
		Quantity<T,Dimensions,DimensionsTrans_Type> result;
		if (this->IsSameDimensions(y))
		{
			result.SetValue(this->GetValue() - y.GetValue());
		}
		else
		{
			assert(0);
		}	
		return result;
	}
	
	//���س˷������

	template<class Dimensions1,class DimensionsTrans_Type1>
	Result<T> operator*( const Quantity<T,Dimensions1,DimensionsTrans_Type1> &y) const
	{
		Result<T> result;
		DimensionVector dVector;

		//����ֵ
		
		result.SetValue(this->GetValue()*y.GetValue());
		
		//���õ�λ

		dVector = this->GetDimension() + y.GetDimension();		
		result.SetDimension(dVector);
		
		return result;
	}

	//���س˷������
	
	Result<T> operator*( const Result<T> &y) const
	{
		Result<T> result;
		DimensionVector dVector;
		//����ֵ
		result.SetValue(this->GetValue()*y.GetValue());
		
		//���õ�λ
		dVector = this->GetDimension() + y.GetDimension();
		
		result.SetDimension(dVector);
		
		return result;
	}

	//���س��������

	template<class Dimensions1,class DimensionsTrans_Type1>
	Result<T> operator/( const Quantity<T,Dimensions1,DimensionsTrans_Type1> &y) const
	{
		Result<T> result;
		DimensionVector dVector;

		//����ֵ

		result.SetValue(this->GetValue()/y.GetValue());
		
		//���õ�λ

		dVector = this->GetDimension() - y.GetDimension();
		result.SetDimension(dVector);
		
		return result;
	}

	Result<T> operator/( const Result<T> &y) const
	{
		Result<T> result;
		DimensionVector dVector;

		//����ֵ

		result.SetValue(this->GetValue()/y.GetValue());
		
		//���õ�λ

		dVector = this->GetDimension() - y.GetDimension();
		result.SetDimension(dVector);
		
		return result;
	}

	//�������
	
	bool operator==(const Quantity<T,Dimensions,DimensionsTrans_Type> &q) const
	{
		if (fabs(this->GetValue() - q.GetValue()) 
			 <= this->GetPrecision())
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	//�������
	
	bool operator==(const Result<T> &r) const
	{
		if (this->GetDimension() == r.GetDimension())
		{
			if (fabs(this->GetValue() - r.GetValue()) 
				<= this->GetPrecision())
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			assert(0);
			return false;
		}
	}

	//���ز���
	
	bool operator != (const Result<T> &r) const
	{
		if (this->GetDimension() == r.GetDimension())
		{
			if (fabs(this->GetValue() - r.GetValue()) 
				> this->GetPrecision())
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			assert(0);
			return false;
		}
	}

	//���ز���
	
	bool operator!=( const Quantity<T,Dimensions,DimensionsTrans_Type> &q) const
	{
		if (fabs(this->GetValue()-q.GetValue()) 
			> this->GetPrecision())
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	//���ظ�ֵ

	const Quantity<T,Dimensions,DimensionsTrans_Type>& operator = (const Result<T>& x)
	{
		if (this->IsSameDimensions(x))
		{
			this->SetValue(x.GetValue());
			this->m_currentunit = DimensionsTrans_Type::GetStdUnitIndex();
		}
		else
		{
			assert(0);
		}

		return *this;
	}

	const Quantity& operator=( const Quantity& quantity )
	{
		if ( this == &quantity )
		{
			return *this;
		}
		
		m_value = quantity.m_value;
		m_precision = quantity.m_precision;
		m_currentunit = quantity.m_currentunit;

		return *this;
	}
};

//��ʼ������ֵ

template <class T,class Dimensions,class DimensionsTrans_Type>
double Quantity<T,Dimensions,DimensionsTrans_Type>::precision = 1.0e-4;

template <class T,class Dimensions,class DimensionsTrans_Type>
Dimensions Quantity<T,Dimensions,DimensionsTrans_Type>::m_dimension;
#endif

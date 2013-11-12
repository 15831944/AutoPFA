/*************************************************
  Copyright (C), 1988-1999, UESOFT Co., Ltd.
  File name:      Result.h
  Author:         ��尡�����
  Version:        1.0
  Date:           2006.8.9
  Description:    ��ͷ�ļ���Ҫ������һ��ģ���࣬�������һ��
				  ģ�����������T��������������ֵ���ͣ���ģ����
				  �Ĵ�����Ϊ�˽��ܳ˳�����Ľ��������λ��ʾ����
  Others:         ��
  Function List:  
    1. GetDimension():ȡ�ø���������Ӧ�ĵ�λ������
	2. GetValue():ȡ�ø�����������ֵ��
	3. IsSameDimensions():�жϸ�����������һ�������Ƿ�Ϊͬһ��������
	4. operator * ():����������������*������
	5. operator + ():������ͬ������������+������
	6. operator - ():������ͬ������������-������
	7. operator / ():����������������/������
	8. SetDimension():���õ�λ������
	9. SetValue():������������ֵ��
  History:        ��
*************************************************/
#ifndef _RESULT_H
#define _RESULT_H

#include <assert.h>
#include "DimensionType.h"
#include "Quantity_share.h"

template<class T,class Dimensions,class DimensionsTrans_Type>
class Quantity;//��ǰ����

template<class T>
class /*QUANTITY_API*/ Result
{
	
public:	

	Result()
	{
		this->m_value = 0;
	}

	~Result()
	{
		
	}

	//�õ�ֵ

	T GetValue() const
	{	
		return m_value;	
	}
	
	//����ֵ

	void SetValue(T m)
	{	
		m_value = m;
	}	

	//�õ���λ

	DimensionVector GetDimension() const
	{	
		return m_dVector;
	}
	//���õ�λ

	void SetDimension(DimensionVector d)
	{	
		m_dVector = d;
	}
	//�жϵ�λ�Ƿ���ͬ
	
	template<class Dimensions,class DimensionsTrans_Type>
	bool IsSameDimensions(Quantity<T,Dimensions,DimensionsTrans_Type> &q) const
	{
		if ( this->GetDimension() == q.GetDimension())
		{
			return true;
		}
		else
		{
			assert(0);
			return false;
		}
	}

	//�жϵ�λ�Ƿ���ͬ

	bool IsSameDimensions(Result<T> &q) const
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

	//����+
	
	template<class Dimensions,class DimensionsTrans_Type>
	Quantity<T,Dimensions,DimensionsTrans_Type> operator+
	(Quantity<T,Dimensions,DimensionsTrans_Type> &y)
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

	//����+
	
	Result<T> operator+(Result<T> &y)
	{
		Result<T> result;
		if (this->IsSameDimensions(y))
		{
			result.SetValue(this->GetValue() + y.GetValue());
			result.SetDimension(this->GetDimension());
		}
		else
		{
			assert(0);
		}
		
		return result;
	}

	//����-

	template<class Dimensions,class DimensionsTrans_Type>
	Quantity<T,Dimensions,DimensionsTrans_Type>  operator-
	(Quantity<T,Dimensions,DimensionsTrans_Type> &y)
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

	//����-
	
	Result<T>  operator-(Result<T> &y)
	{
		Result<T> result;
		if (this->IsSameDimensions(y))
		{
			result.SetValue(this->GetValue() - y.GetValue());
			result.SetDimension(this->GetDimension());
		}
		else
		{
			assert(0);
		}
		
		return result;
	}

	//����*

	template<class Dimensions,class DimensionsTrans_Type>
	Result<T> operator*(Quantity<T,Dimensions,DimensionsTrans_Type> &y)
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

	//����*
	
	Result<T> operator*(Result<T> &y)
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

	//����/
	
	template<class Dimensions,class DimensionsTrans_Type>
	Result<T> operator/(Quantity<T,Dimensions,DimensionsTrans_Type> &y)
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

	//����/
	
	Result<T> operator/(Result<T> &y)
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
private:

	T m_value;//��ֵ
	DimensionVector m_dVector;//��λ����
};

#endif
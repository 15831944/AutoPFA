/*************************************************
  Copyright (C), 1988-1999, UESOFT Co., Ltd.
  File name:      dimensiontype.h
  Author:         ��尡�����
  Version:        1.0
  Date:           2006.8.9
  Description:    ��ͷ�ļ�������һ��ģ���࣬��һ����ͨ�ࡣ
				  ��ͨ��Ĵ�����ȫ��Ϊ��ʵ�ֺ����Result�ࡣ
				  ģ�������λ������ģ������Ĳ�ͬ����ͬ
				  �ĵ�λ��
  Others:         ��
  DimensionVector Function List:
	1. IsTemprature():�ж��Ƿ�Ϊ��λ������
	2. operator+():ʵ�ֵ�λ�������
	3. operator-():ʵ�ֵ�λ�������
	4. operator!=():�ж���������λ�����Ƿ���ͬ
	5. operator==():�ж���������λ�����Ƿ���
  DimensionType<> Function List:
	1. GetDimension():�õ���λ����ֵ
	2. SetDimension():���õ�λ����ֵ
  History:        ��
*************************************************/
#ifndef _DIMENSIONTYPE_H
#define _DIMENSIONTYPE_H

//�ýṹ���ʾ����λ��Ϊ��ʵ��Result<T>��

class DimensionVector
{
public:
	
	int mass;
	int length;
	int time;
	int current;
	int temprature;
	int angle;
	int mol;
public:

	bool IsTemprature() const
	{
		if ((this->angle == 0) & (this->current == 0)
			& (this->length == 0) & (this->mass == 0)
			& (this->mol == 0) & (this->time == 0)
			& (this->temprature == 1))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	//���ؼӷ����㣬�Ե�λ�ĸ����ٽ������

	DimensionVector operator+(DimensionVector dVector)
	{
		DimensionVector dVecRet;
		dVecRet.mass = this->mass + dVector.mass;
		dVecRet.length = this->length + dVector.length;
		dVecRet.time = this->time + dVector.time;
		dVecRet.current = this->current + dVector.current;
		dVecRet.temprature = this->temprature + dVector.temprature;
		dVecRet.angle = this->angle + dVector.angle;
		dVecRet.mol = this->mol + dVector.mol;
	
		return dVecRet;
	}

	//���ؼ������㣬�Ե�λ�ĸ����ٽ������

	DimensionVector operator-(DimensionVector dVector)
	{
		DimensionVector dVecRet;
		dVecRet.mass = this->mass - dVector.mass;
		dVecRet.length = this->length - dVector.length;
		dVecRet.time = this->time - dVector.time;
		dVecRet.current = this->current - dVector.current;
		dVecRet.temprature = this->temprature - dVector.temprature;
		dVecRet.angle = this->angle - dVector.angle;
		dVecRet.mol = this->mol - dVector.mol;
	
		return dVecRet;
	}
	//����!=�жϵ�λ������ʽ�Ƿ�Ϊ����
	
	bool operator != (DimensionVector dVector) const
	{
		if ((this->mass != dVector.mass)
			|| (this->length != dVector.length)
			|| (this->angle != dVector.angle)
			|| (this->temprature != dVector.temprature)
			|| (this->time != dVector.time)
			|| (this->mol != dVector.mol)
			|| (this->current != dVector.current)
			)
		{
			return true;  //�ǲ���ȵ�
		}
		else
		{
			return false; //����ȵ�
		}
	}

	//����==�жϵ�λ������ʽ�Ƿ�Ϊ���
	
	bool operator == (DimensionVector dVector) const
	{
		if ((this->mass == dVector.mass)
			&& (this->length == dVector.length)
			&& (this->angle == dVector.angle)
			&& (this->temprature == dVector.temprature)
			&& (this->time == dVector.time)
			&& (this->mol == dVector.mol)
			&& (this->current == dVector.current)
			)
		{
			return true;  //����ȵ�
		}
		else
		{
			return false; //������ȵ�
		}
	}
} ;


//���嵥λģ��

template <int mass, int length,int time
					,int current,int temprature
					,int angle,int mol>
					
class DimensionType
{
public:

    DimensionType()
	{
		m_dVector.mass = mass;
		m_dVector.length = length;
		m_dVector.time = time;
		m_dVector.current = current;
		m_dVector.temprature = temprature;
		m_dVector.angle = angle;
		m_dVector.mol = mol;
	}

	DimensionVector GetDimension() const
	{
		return m_dVector;
	}
	void SetDimension(DimensionVector d)
	{
		m_dVector = d;
	}
private:
	DimensionVector m_dVector;
};



#endif

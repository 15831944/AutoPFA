/*************************************************
  Copyright (C), 1988-1999, UESOFT Co., Ltd.
  File name:      Unit.h
  Author:         ���£����
Version:          1.0
Date:             2006.8.10
  Description:    ���ͷ�ļ�����Ҫ������һЩ���ⲿ����ģ����õ�
                  ���������������ͣ�
  Function List:  ��
    1. ....
  History:        �� 
*************************************************/

#ifndef _UNIT_H
#define _UNIT_H

#include "quantity.h"

//���峣�õ�λ

typedef DimensionType<0,0,0,0,0,1,0> AngleDimension;
typedef DimensionType<0,2,0,0,0,0,0> AreaDimension;
typedef DimensionType<1,-3,0,0,0,0,0> DensityDimension;
typedef DimensionType<1,1,-2,0,0,0,0> ForceDimension;
typedef DimensionType<0,1,0,0,0,0,0> LengthDimension;
typedef DimensionType<1,0,0,0,0,0,0> MassDimension;
typedef DimensionType<1,2,-3,0,0,0,0> PowerDimension;
typedef DimensionType<1,-1,-2,0,0,0,0> PressureDimension;
typedef DimensionType<0,1,-1,0,0,0,0> SpeedDimension;
typedef DimensionType<0,0,0,0,1,0,0> TemperatureDimension;
typedef DimensionType<0,0,1,0,0,0,0> TimeDimension;
typedef DimensionType<0,3,0,0,0,0,0> VolumnDimension;
typedef DimensionType<1,2,-2,0,0,0,0> WorkDimension;
typedef DimensionType<1,1,-1,0,0,0,0> MomentumDimension;
typedef DimensionType<0,0,0,0,-1,0,0> ExpansionCoefDimension;
typedef DimensionType<1,0,-2,0,0,0,0> RigidityDimension;
typedef DimensionType<1,2,-2,0,0,-1,0> RSFDimension;


//���峣��������
typedef Quantity<double,AngleDimension,AngleTrans> AngleUnit;//�Ƕ�
typedef AngleUnit AngleDisplaceUnit;//�Ƕ�ƫ����

typedef Quantity<double,AreaDimension,AreaTrans> AreaUnit;//���

typedef Quantity<double,DensityDimension,DensityTrans> DensityUnit;//�ܶ�
typedef DensityUnit InsulationDensityUnit;//���²��ܶ�
typedef DensityUnit FluidDensityUnit;//�����ܶ�
typedef DensityUnit PipeDensityUnit;//�ܵ��ܶ�

typedef Quantity<double,ForceDimension,ForceTrans> ForceUnit;//��

typedef Quantity<double,LengthDimension,LengthTrans> LengthUnit;//����
typedef LengthUnit ThicknessUnit;//�ں�
typedef LengthUnit DiameterUnit;//ֱ��
typedef LengthUnit CLenUnit;//�ϳɳ��ɣ���
typedef LengthUnit EleUnit;//���
typedef LengthUnit LineDisplaceUnit;//��λ��

typedef Quantity<double,MassDimension,MassTrans> MassUnit;//����
typedef MassUnit WeightUnit;//����

typedef Quantity<double,PowerDimension,PowerTrans> PowerUnit;//����
typedef Quantity<double,PressureDimension,PressureTrans> PressureUnit;//ѹǿ
typedef PressureUnit WindForceUnit;//�����
typedef PressureUnit StressUnit;//Ӧ��
typedef PressureUnit PreUnit;//ѹ����λ����
typedef PressureUnit EModulusUnit;//����ģ����λ����

typedef Quantity<double,SpeedDimension,SpeedTrans> SpeedUnit;//�ٶ�
typedef Quantity<double,TemperatureDimension,TemperatureTrans> TemperatureUnit;//�¶�
typedef Quantity<double,TimeDimension,TimeTrans> TimeUnit;//ʱ��
typedef Quantity<double,VolumnDimension,VolumnTrans> VolumnUnit;//���
typedef Quantity<double,WorkDimension,WorkTrans> WorkUnit;//��


typedef Quantity<double,MomentumDimension,MomentTrans> MomentUnit;
typedef MomentUnit OutMomentUnit;//�������

typedef Quantity<double,ExpansionCoefDimension,ExpansionCoefTrans> ExpansionCoefUnit;//������ϵ��

typedef Quantity<double,RigidityDimension,RigidityTrans> TSFUnit;//ƽ������
typedef TSFUnit AverageForceUnit;//�����غ�

typedef Quantity<double,RSFDimension,RSFTrans> RSFUnit;//ת������








//�ǳ�����λ

typedef DimensionType<0,1,-2,0,0,0,0> AccelerationDimension;
typedef DimensionType<0,0,-1,0,0,1,0> RadSpeedDimension;
typedef DimensionType<0,0,-1,0,0,0,0> FrequencyDimension;
typedef DimensionType<0,0,0,1,0,0,0> CurrentDimension;
typedef DimensionType<0,0,0,0,0,0,1> MolDimension;
typedef DimensionType<0,2,-2,0,-1,0,0> SpecificHeatDimension;//������
typedef DimensionType<1,0,0,0,0,0,-1> MolMassDimension;		//Ħ������
typedef DimensionType<0,3,0,0,0,0,-1> MolVolumnDimension;		//Ħ�����
#endif
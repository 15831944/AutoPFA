// PFAOptimitationData.h: interface for the PFAOptimitationData class.
//
//////////////////////////////////////////////////////////////////////
/************************************************************************

�汾: 8.0  ����ʱ��: 2008/06  ����: COM 

����: �Ż�����������Ҫ�ľ��󲿷�����, �о��Ե���Щӷ��,      
                                                                                                                                        
************************************************************************/

#if !defined(AFX_PFAOPTIMITATIONDATA_H__3FB00A99_D0F1_49CD_8DE1_16288CF29DA5__INCLUDED_)
#define AFX_PFAOPTIMITATIONDATA_H__3FB00A99_D0F1_49CD_8DE1_16288CF29DA5__INCLUDED_


#pragma  once
#include <vector>
#include <map>
using namespace std;
typedef vector<int> ComMap;
typedef map< int, ComMap > CirMatrix;
const CString ECONOMY_FAILE = "�������ؼ���ʧ�ܣ���������Ƿ����ô���";

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

enum PropertyType
{ 
	OPT_PIPEDUMMYFLUX = 0, OPT_PIPEFACTFLUX, OPT_PIPELENGTH, OPT_JUNFLUX, OPT_PIPEDIAMETER, OPT_PIPEWATERHAMMER, 
	OPT_PIPEFLUXSPEED, OPT_JUNPRESSURE, OPT_PIPEECONOMYDIAMETER,
	OPT_PIPEDUMMYWATERHAMMER = 10, OPT_PIPEFACTWATERHAMMER,

    OPT_CIRPIPE = 100, OPT_CIRJUN, OPT_PIPECIR, OPT_PIPEKEY,

    OPT_SUPPLYJUN = 200, OPT_CONTROLJUN, OPT_DUMMYCIRCLE, OPT_DUMMYJUNANDPIPE,

    OPT_A = 300, OPT_B, OPT_ALFA, OPT_DISINVESTMENTTIME, OPT_REPAIRMODULUS, OPT_WORKEXPENDITURE, OPT_ELETRICITYPRICE, 
	OPT_ASYMMETRYMODULUS, OPT_PUMPEFFICIENCY, OPT_K, OPT_M, OPT_N, OPT_ECONOMYFACTOR,OPT_FLUXSUMMATION, OPT_CONSTRUCTEXPENDITURE,
	OPT_YCONVERTEXPENDITURE, 

	OPT_NULL = 2000
};

class PFAOptimitationData  
{
public:
	PFAOptimitationData();
	virtual ~PFAOptimitationData();
	bool Initialization();
	void RemoveAll();

	inline bool SetCirJunMatrix( const int& iKeyOfCircle, const ComMap& CircleJunOrder );
    inline CirMatrix* GetCirJunMatrix();
	ComMap* GetCirJunMatrix( const int& iKeyOfCircle );
	inline int GetCirJunMatrixCount();

	inline bool SetCirPipeMatrix( const int& iKeyOfCircle, const ComMap& CirclePipeOrder );
	inline CirMatrix* GetCirPipeMatrix();
	ComMap* GetCirPipeMatrix( const int& iKeyOfCircle );
	inline int GetCirPipeMatrixCount();

	inline CirMatrix* GetPipeCirMatrix();

	// 0+
	bool GetProperty( const int& iKeyOfComponent, const int& iProperty, double& dValueOfProperty );  // ���Ҳ����򷵻�FALSE��
	bool SetProperty( const int& iKeyOfComponent, const int& iProperty, double& dValueOfProperty );
	
	// 100+
	bool GetProperty( const int& iKeyOfComponent, const int& iProperty, const int& iPosition, int& iValueOfProperty );  // ���Ҳ����򷵻�FALSE��
	bool SetProperty( const int& iKeyOfComponent, const int& iProperty, const int& iPosition, int& iValueOfProperty );

	// 200+
	bool GetProperty( const int& iKeyOfComponent, const int& iProperty, int& iValueOfProperty );
	bool SetProperty( const int& iKeyOfComponent, const int& iProperty, int& iValueOfProperty );

	// 300+
	double GetProperty( const PropertyType& eProperty );
	bool SetProperty( const PropertyType& eProperty, const double& dValueOfProperty );
	
	int GetPropertyCount( const int& iProperty );                                    // ȡ���и���
	int GetPropertyCount( const int& iKeyOfComponent, const int& iProperty );        // ȡ�ö�Ӧ�е�����

	inline double GetAModulus();
	inline double GetBModulus();
	inline double GetAlfaModulus();
	inline double GetDisinvestmentTime();
	inline double GetRepairModulus();
	inline double GetWorkExpenditure();
	inline double GetEletricityPrice();
	inline double GetAsymmetryModulus();
	inline double GetPumpEfficiency();
	inline double GetKModulus();
	inline double GetMModulus();
	inline double GetNModulus();
	inline double GetEconomyFactor();
	inline double GetFluxSummation();
	inline double GetConstructExpenditure();
	inline double GetYConvertExpenditure();
	

	inline void SetAModulus( const double& dTempAModulus );
	inline void SetBModulus( const double& dTempBModulus );
	inline void SetAlfaModulus( const double& dTempAlfaModulus );
	inline void SetDisinvestmentTime( const double& dTempDisinvestmentTime );
	inline void SetRepairModulus( const double& dTempRepairModulus );
	inline void SetWorkExpenditure(const double& dTempWorkExpenditure );
	inline void SetEletricityPrice( const double& dTempEletricityPrice );
	inline void SetAsymmetryModulus( const double& dTempAsymmetryModulus );
	inline void SetPumpEfficiency( const double& dTempPumpEfficiency );
	inline void SetKModulus( const double& dTempKModulus );
	inline void SetMModulus( const double& dTempMModulus );
	inline void SetNModulus( const double& dTempNModulus );
	inline void SetEconomyFactor( const double& dTempEconomyFactor );
	inline void SetFluxSummation( const double& dTempFluxSummation );
	inline void SetConstructExpenditure( const double& dTempConstructExpenditure );
    inline void SetYConvertExpenditure( const double& dTempYConvertExpenditure );
	
private:
	// �洢��-�ܵ�����:100
	CirMatrix CirPipeMatrix;
	
	// �洢��-�ڵ����:101     
	CirMatrix CirJunMatrix;

	// �洢�ܵ�-������:102
	CirMatrix PipeCirMatrix;


	// ���Դ������������������Ƴ���������
	
	// ��¼�ܵ���������:0
	map< int, double > PipeDummyFluxMap;
	
	// ��¼�ܵ���ʵ������:1
	map< int, double > PipeFactFluxMap;
	
	// ��¼�ܵ��ĳ���:2
	map< int, double > PipeLengthMap;

	// ��¼�ڵ�������3
	map< int, double > JunFluxMap;

	// ��¼�Ż���Ĺܾ���4
	map< int, double > PipeDiameter;

	// ��¼�Ż����ˮͷ��ʧ��5
	map< int, double > PipeWaterHammer;

	// ��¼�ܵ�����: 6
	map< int, double > PipeFluxSpeedMap;

	// ��¼�ڵ����ˮѹ: 7
	map< int, double > JunPressureMap;

	// ��¼��������ľ��ùܾ���8
	map< int, double > PipeEconomyDiameterMap;

	// ��¼�ܵ���ˮͷ��ʧ: 10
	map< int, double > PipeDummyWaterHammer;

	// ��¼�ܵ�ʵ��ˮͷ��ʧ: 11
	map< int, double > PipeFactWaterHammer;

	// ��¼��ˮԴ�ڵ�:200
	vector< int > SupplyJunVector;

	// ��¼���Ƶ�ڵ㣺201
	vector< int > ControlJunVector;

	// ��¼�黷��� : 202
	vector< int > DummyCircleVector;

	// ��¼��ڵ����ܵ���ֻ������һ����ڵ㣬�������ڵ�һ��λ�ã� 203
	vector< int > DummyJunAndPipeVector;

	// ���и������ǰ�double����һ���࣬������������dDummyFlux, dFactFlux, dLength������Ա������Ȼ��Ϊ��������Ա�����ṩ�ӿڣ�
	// �����д洢����ã������ĸ���ʽ��Щ�������޷��жϣ�ֻ�����Ժ�������Ѱ��𰸡�
	// �������ṩһ�����ʽӿ�BOOL GetPipeProperty( int iKeyOfPipe, int iProperty )��ʹ�ü�ʹ�Ժ�ı���DummyFlux, FactFlux, Length�Ĵ洢��ʽ��Ҳ���øı�����Ĵ��롣
	
	// ˮ�ܽ�����ã�����ˮ�ܲ��Ϸ��ú����ʩ���ȷ��ã���λԪ/m���е�a:300
	double dA;

	// ˮ�ܽ�������е�b: 301
	double dB;

	// ˮ�ܽ�������е�ָ����:302
	double dAlfa;

	// ����Ͷ�ʻ�����,��λ���ꡣ����Ͷ��Ч��ϵ��E=1/dDisinvestmentTime��:303
	double dDisinvestmentTime;
	
	// p:����ÿ���۾ɺʹ��ްٷ��ʣ��Թ���������õ�%���� : 304
	double dRepairModulus;

	// K:���ˮ�йصľ���ָ�꣬������1m~3/s ��ˮ��1m�߶ȵ�ÿ����; :305
	double dWorkExpenditure;

	// ��ۣ���������K�� :306
	double dEletricityPrice;

	// ���������ڹ�ˮ����������ϵ��, ��������K :307
	double dAsymmetryModulus;

	// ��Ч��,��������K :308
	double dPumpEfficiency;

	// k,m,n:ϵ����ȡ���������õ�ˮ���������㹫ʽ,nһ��ȡ2.0  :309
	double dKModulus; 
	double dMModulus;                 // 310
	double dNModulus;                 // 311

	// f:��������  :312
	double dEconomyFactor;

	// Q:��������������� : 313
	double dFluxSummation;

	// ������� : 314
	double dConstructExpenditure;

	// W:��������� : 315
	double dYConvertExpenditure;

	// ��Ա�����ķ��ʽӿڣ���֤����Ķ�����.TRUE��ʾGet��FALSE��ʾSet
    bool ChangeProperty( const int& iKeyOfComponent, const int& iProperty, const bool bChangeType, double& dValueOfProperty );
	bool ChangeProperty( const int& iKeyOfComponent, const int& iProperty, const int& iPosition, const bool bChangeType, int& iValueOfProperty );
	bool ChangeProperty( const int& iKeyOfComponent, const int& iProperty, const bool bChangeType, int& iValueOfProperty );
};

inline bool PFAOptimitationData::SetCirPipeMatrix( const int& iKeyOfCircle, const ComMap& CirclePipeOrder )
{
	CirPipeMatrix.insert( CirMatrix::value_type( iKeyOfCircle, CirclePipeOrder ) );
    return true; 
}

inline CirMatrix* PFAOptimitationData::GetCirPipeMatrix()
{
	return &CirPipeMatrix;
} 

inline int PFAOptimitationData::GetCirPipeMatrixCount()
{
	return CirPipeMatrix.size();
}

inline bool PFAOptimitationData::SetCirJunMatrix( const int& iKeyOfCircle, const ComMap& CircleJunOrder )
{
    CirJunMatrix.insert( CirMatrix::value_type( iKeyOfCircle, CircleJunOrder ) );
    return true;
}

inline CirMatrix* PFAOptimitationData::GetCirJunMatrix()
{
	return &CirJunMatrix;
} 

inline int PFAOptimitationData::GetCirJunMatrixCount()
{
	return CirJunMatrix.size();
}

inline CirMatrix* PFAOptimitationData::GetPipeCirMatrix()
{
	return &PipeCirMatrix;
}


///////////////////////////////////////////////////////
inline double PFAOptimitationData::GetAModulus()
{
	return dA;
}

inline double PFAOptimitationData::GetBModulus()
{
	return dB;
}

inline double PFAOptimitationData::GetAlfaModulus()
{
	return dAlfa;
}

inline double PFAOptimitationData::GetDisinvestmentTime()
{
	return dDisinvestmentTime;
}

inline double PFAOptimitationData::GetRepairModulus()
{
	return dRepairModulus;
}

inline double PFAOptimitationData::GetWorkExpenditure()
{
	return dWorkExpenditure;
}

inline double PFAOptimitationData::GetEletricityPrice()
{
	return dEletricityPrice;
}

inline double PFAOptimitationData::GetAsymmetryModulus()
{
    return dAsymmetryModulus;
}

inline double PFAOptimitationData::GetPumpEfficiency()
{
	return dPumpEfficiency;
}

inline double PFAOptimitationData::GetKModulus()
{
	return dKModulus;
}
inline double PFAOptimitationData::GetMModulus()
{
	return dMModulus;
}

inline double PFAOptimitationData::GetNModulus()
{
	return dNModulus;
}

inline double PFAOptimitationData::GetEconomyFactor()
{
	return dEconomyFactor;
}

inline double PFAOptimitationData::GetFluxSummation()
{
	return dFluxSummation;
}

inline double PFAOptimitationData::GetConstructExpenditure()
{
	return dConstructExpenditure;
}

inline void PFAOptimitationData::SetConstructExpenditure( const double& dTempConstructExpenditure )
{
	dConstructExpenditure = dTempConstructExpenditure;
}


inline double PFAOptimitationData::GetYConvertExpenditure()
{
	return dYConvertExpenditure;
}

inline void PFAOptimitationData::SetYConvertExpenditure( const double& dTempYConvertExpenditure )
{
	dYConvertExpenditure = dTempYConvertExpenditure;
}

inline void PFAOptimitationData::SetAModulus( const double& dTempAModulus )
{
	dA =dTempAModulus;
}

inline void PFAOptimitationData::SetBModulus( const double& dTempBModulus )
{
	dB = dTempBModulus;
}

inline void PFAOptimitationData::SetAlfaModulus( const double& dTempAlfaModulus )
{
	dAlfa = dTempAlfaModulus;
}

inline void PFAOptimitationData::SetDisinvestmentTime( const double& dTempDisinvestmentTime )
{
	dDisinvestmentTime = dTempDisinvestmentTime;
}

inline void PFAOptimitationData::SetRepairModulus( const double& dTempRepairModulus )
{
	dRepairModulus = dTempRepairModulus;
}

inline void PFAOptimitationData::SetWorkExpenditure(const double& dTempWorkExpenditure )
{
	dWorkExpenditure = dTempWorkExpenditure;
}

inline void PFAOptimitationData::SetEletricityPrice( const double& dTempEletricityPrice )
{
	dEletricityPrice = dTempEletricityPrice;
}

inline void PFAOptimitationData::SetAsymmetryModulus( const double& dTempAsymmetryModulus )
{
    dAsymmetryModulus = dTempAsymmetryModulus;
}

inline void PFAOptimitationData::SetPumpEfficiency( const double& dTempPumpEfficiency )
{
	dPumpEfficiency = dTempPumpEfficiency;
}

inline void PFAOptimitationData::SetKModulus( const double& dTempKModulus )
{
	dKModulus = dTempKModulus;
}
inline void PFAOptimitationData::SetMModulus( const double& dTempMModulus )
{
	dMModulus = dTempMModulus;
}

inline void PFAOptimitationData::SetNModulus( const double& dTempNModulus )
{
	dNModulus = dTempNModulus;
}

inline void PFAOptimitationData::SetEconomyFactor( const double& dTempEconomyFactor )
{
	dEconomyFactor = dTempEconomyFactor;
}

inline void PFAOptimitationData::SetFluxSummation( const double& dTempFluxSummation )
{
	dFluxSummation = dTempFluxSummation;
}

#endif // !defined(AFX_PFAOPTIMITATIONDATA_H__3FB00A99_D0F1_49CD_8DE1_16288CF29DA5__INCLUDED_)

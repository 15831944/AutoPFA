// FCFComponentMgr.cpp: implementation of the FCFComponentMgr class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FCFComponentMgr.h"
#include "PCFPipe.h"
#include "PCFJun.h"
#include "math.h"
#include "PCFJunsMgr.h"
#include "PCFPipesMgr.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
#include <vector>
using namespace std;

typedef vector<AcGePoint3d> UnJunPoint;
typedef vector<UnJunPoint> UnJunCon;
UnJunCon UnJun; 

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
const CString PCFComponentMgr::m_strKeyWordArray[] =
{
	_T("TEE-SET-ON"),
	_T("SUPPORT"),
	_T("BEND"),
	_T("BEND-TEED"),
	_T("CAP"),
	_T("CLAMP"),
	_T("CONNECTOR"),
	_T("COUPLING"),
	_T("CROSS"),
	_T("CROSS-SET-ON"),
	_T("CROSS-STUB"),
	_T("ELBOLET"),
	_T("ELBOW"),
	_T("FTUBE"),
	_T("BOLT"),
	_T("ELBOW-TEED"),
	_T("FILTER"),
	_T("FILTER-ANGLE"),
	_T("FILTER-OFFSET"),
	_T("FILTER-RETURN"),
	_T("FLANGE"),
	_T("FLANGE-BLIND"),
	_T("FLANGE-REDUCING-CONCENTRIC"),
	_T("FLANGE-REDUCING-ECCENTRIC"),
	_T("GAP"),
	_T("GASKET"),
	_T("INSTRUMENT"),
	_T("INSTRUMENT-3WAY"),
	_T("INSTRUMENT-4WAY"),
	_T("INSTRUMENT-ANGLE"),
	_T("INSTRUMENT-BALLOON"),
	_T("INSTRUMENT-DIAL"),
	_T("INSTRUMENT-OFFSET"),
	_T("INSTRUMENT-RETURN"),
	_T("INSTRUMENT-TEE"),
	_T("LAPJOINT-STUBEND"),
	_T("LAPJOINT-RING"),
    _T("MESSAGE"),
	_T("MISC-COMPONENT"),
	_T("MISC-COMPONENT-ANGLE"),
	_T("MISC-COMPONENT-OFFSET"),
	_T("MISC-COMPONENT-OFFSET"),
	_T("MISC-COMPONENT-RETURN"),
	_T("MISC-HYGENIC"),
	_T("MULTI-PORT-COMPONENT"),
//	_T("NOZZLE"),
	_T("NUT"),
	_T("OLET"),
	_T("PENETRATION-PLATE"),
	_T("PIPE"),
	_T("PIPE-BLOCK-FIXED"),
	_T("PIPE-BLOCK-VARIABLE"),
	_T("PIPE-FIXED"),
	_T("REDUCER-CONCENTRIC"),
	_T("REDUCER-CONCENTRIC-TEED"),
	_T("REDUCER-ECCENTRIC"),
	_T("REDUCER-ECCENTRIC-TEED"),
	_T("REINFORCEMENT-PAD"),
	_T("SAFETY-DISC"),
	_T("TEE"),
	_T("TEE-STUB"),
	_T("TRAP"),
	_T("TRAP-ANGLE"),
	_T("TRAP-OFFSET"),
	_T("TRAP-RETURN"),
	_T("UNION"),
	_T("VALVE"),
	_T("VALVE-3WAY"),
	_T("VALVE-4WAY"),
	_T("VALVE-ANGLE"),
	_T("VALVE-MULTIWAY"),
	_T("WELD"),
	_T("Y-PIECE-FABRICATED"),
	_T("Y-PIECE-FITTING"),
	_T("END-CONNECTION-EQUIPMENT"),
	_T("END-CONNECTION-NULL"),
 	_T("ASSIGNFLOW"),
//	_T("PUMP"),   //��ʱ���ã�ʹ���豸�ֶζ���
	_T("RESERVIOR"),
	_T("ASSIGNPRESS"),
	_T("SURGE"),
	_T("GASACCUM"),
	_T("LIQUIDACCUM"),
	_T("SPRAY"),
	_T("OVER")
};


PCFComponentMgr::PCFComponentMgr()
{

}

PCFComponentMgr::~PCFComponentMgr()
{

}




void PCFComponentMgr::Init(const CStringArray &strSet)
{
	int i=0;
	CStringArray lineHeaderArray ;
	for ( i = 0 ; i< strSet.GetSize() ; i++ )
	{
		if (IsKeyWord(strSet.GetAt(i)))
			break;
		lineHeaderArray.Add(strSet.GetAt(i));
	}
	m_pipeHead.Init(lineHeaderArray);

	CStringArray strPipe ;
	//ȥ����֧ͷ����Ϣ�󱣴浽strPipe��ȥ��
	for( ; i < strSet.GetSize() ; i++)
		strPipe.Add(strSet.GetAt(i)) ;
	strPipe.Add( _T("Over"));

	InitEquipment_PT(strPipe);
  	InitNOZZLE_Ptconcet(strPipe);                 //��ʼ���豸���֧�Ľӵ�����
 // InitJunKey_DelDiscription( strPipe ) ;		//���������������ݣ�
 // InitJunKey_AddPipeAndAssignFlow( strPipe ) ;	//�ڷǷ�������Ԫ���ĺ������PIPE��
//  InitJunKey_AddAssignFlowStartBranch( strPipe ) ;	//�ڷ�֧ͷ����ָ��������
//  InitJunKey_AddAssignFlowEndBranch( strPipe ) ;		//�ڷ�֧β����ָ��������
// InitJunKey_NoPCFJuntoPipe( strPipe ) ;		//�Ѳ���PCFԪ���Ĺؼ��ָ�ΪPIPE��
 // InitJunKey_MergePipe( JuntoPipe ) ;			//�ϲ����ڵ�PIPE���ܵ�����
 // InitJunKey_KeepPtConcet( MergePipe ) ;		//��֤���ڵ�ͬһ����֧����Ľڵ�����
//  InitJunKey_DelTeeBranch( MergePipe ) ;		//��֤��ͨcref����������PIPE
//	InitJunKey_AddPipe( strPipe ) ;	//��ͬһ����֧���溸�ӵ�Ԫ���ӹܵ������������豸��������ڵ㣻
 //	InitComponet( ElementBuff1 ) ;				//�����豸�ڵ㣻
	
	InitElement(strPipe);

	Init_JunPt(m_JunsMgr,m_PipesMgr);                 //��ʼ���ܵ������ڵ�
	Init_AddPipetoJun(m_JunsMgr);                        //�����ӵ�������������м�ӹܵ� 

	CombinationPipes(m_PipesMgr);                          // �ϲ������Ĺܵ�
	Init_AddPipe(m_JunsMgr,m_PipesMgr);                     //�ڷǷ�������Ԫ���ĺ������PIPE
	InitAddAssignFlow(m_JunsMgr,m_PipesMgr);                    //����ָ������ 

	
	CombinationFit();

	TripJunLen();
	CombinationPipe();


	InitNetLink();

	


	Tran3dTo2d();
	MoveGraph();
	ChangeOrigin();
	
}

void PCFComponentMgr::Init_AddPipetoJun(PCFJunsMgr& pJunMgr)  //�ڵ���������ܵ�
{
	PCFJun* PcfJun1 = NULL;
	PCFJun* PcfJun2 = NULL;
	int n = 0;
	int i = 0;
	int j = 0;
	IteratorPtr<PCFJun> JunitPtr(pJunMgr.CreateIt());
	for(JunitPtr->Fist();!JunitPtr->IsDone();JunitPtr->Next())
	{
			n = max(n,JunitPtr->CurrentItem().GetKey());
	}
	
	for (i = 0; i < n+1;i++)
	{
		PcfJun1 = pJunMgr.LookUp(i);
		j = i+1;
		for (;j < n+1;j++)
		{
			PcfJun2 = pJunMgr.LookUp(j);
			if(PcfJun1 == NULL || PcfJun2 == NULL)
				break;
			CampareJJPt(*PcfJun1,*PcfJun2);
		}
	}
}

BOOL PCFComponentMgr::IsKeyWord(const CString &strKeyWord)
{
	int nSize = sizeof( m_strKeyWordArray )/sizeof( CString ) ;
	for( int i = 0 ; i < nSize ; ++i)
	{
		if( !m_strKeyWordArray[i].CompareNoCase( strKeyWord ) )
			return TRUE ;
	}
	return FALSE ;
}

void PCFComponentMgr::InitElement(CStringArray &strSet)
{
	unsigned long wordnum = 0;
	unsigned long wordsize =strSet.GetSize();
	CStringArray CurElementBuff1;
	CStringArray Equipments;
	int i = 0;
	for (wordnum = 0;wordnum < wordsize;wordnum++)
	{
		if (IsKeyWord(strSet.GetAt(wordnum)) && strSet.GetAt(wordnum) != _T("Over") && strSet.GetAt(wordnum) != _T("END-CONNECTION-NULL"))
		{
			int j = wordnum;
			if (strSet.GetAt( wordnum ) == _T("CAP") || strSet.GetAt( wordnum ) == _T("FLANGE") || strSet.GetAt( wordnum ) == _T("GASKET") || strSet.GetAt( wordnum ) == _T("FBLIND") 
				|| strSet.GetAt( wordnum ) == _T("FTUBE") || strSet.GetAt(wordnum) == _T("BOLT"))
				strSet.SetAt(wordnum,_T("PIPE"));  //��PAFԪ������ʱ���ܵ�����
				do 
				{
					CurElementBuff1.Add(strSet.GetAt(j));
					j++;
				} while (!IsKeyWord(strSet.GetAt(j)));
			if (strSet.GetAt(wordnum) == _T("END-CONNECTION-EQUIPMENT"))
				InitComponet(CurElementBuff1);
			else
				CreatComponet(CurElementBuff1);
		}
		CurElementBuff1.RemoveAll();
	}
}

void PCFComponentMgr::Init_JunPt(PCFJunsMgr& pJunMgr,PCFPipesMgr& pPipeMgr)
{
	PCFPipe* pPipe = NULL;
	PCFJun* pJun = NULL;
	int k = 0;
	IteratorPtr<PCFPipe> PipeitPtr(pPipeMgr.CreateIt());
	IteratorPtr<PCFJun> JunitPtr(pJunMgr.CreateIt());
	for(PipeitPtr->Fist();!PipeitPtr->IsDone();PipeitPtr->Next())
	{
		pPipe = &PipeitPtr->CurrentItem();
		for(JunitPtr->Fist();!JunitPtr->IsDone();JunitPtr->Next())
		{
			pJun = &JunitPtr->CurrentItem();
			k = CamparePt(*pJun,*pPipe);
		}
	}
}

void PCFComponentMgr::Init_AddPipe(PCFJunsMgr& pJunMgr,PCFPipesMgr& pPipeMgr) //�Ƿ������ڵ����ܵ�
{
	IteratorPtr<PCFJun> JunitPtr(pJunMgr.CreateIt()); //�ڵ��б�
	IteratorPtr<PCFPipe> PipeitPtr(pPipeMgr.CreateIt()); //�ܵ��б�
	int k = 0;
	int ChoisePt = 0;
	CStringArray strPipe;
	PCFJun* pJun = NULL;
	PCFPipe *pPipe =NULL;
	for(JunitPtr->Fist();!JunitPtr->IsDone();JunitPtr->Next()) //�����ڵ�
	{
		ChoisePt = 0;
		pJun = &JunitPtr->CurrentItem();
		if(pJun->GetName() == _T("Pump") || pJun->GetName() == _T("Reservior")) //�豸��������Ƿ�
			continue;
		for(PipeitPtr->Fist();!PipeitPtr->IsDone();PipeitPtr->Next())
		{
			pPipe = &PipeitPtr->CurrentItem();
			if (pPipe == NULL || pJun == NULL)
				break;
			k = CamparePt(*pJun,*pPipe);
			ChoisePt = ChoisePt+k;
			if (ChoisePt > 2)
				break;
		}
		if (ChoisePt == 3 || ChoisePt ==0 || ChoisePt ==4 || ChoisePt ==5)
			continue;
		else
		{
			AcGePoint3d* AssignPt;
			strPipe.InsertAt(0,_T("PIPE"));
			AssignPt = pJun->GetPtList().GetTail();
			double m_bore = pPipe->Bore();
			CString strx;
			CString stry;
			CString strz;
			CString strbo;
			strx.Format(_T("%f"),AssignPt->x);
			stry.Format(_T("%f"),AssignPt->y);
			strz.Format(_T("%f"),AssignPt->z);
			strbo.Format(_T("%f"),m_bore);
			strPipe.InsertAt(1,_T("END-POINT"));
			strPipe.InsertAt(2,strx);
			strPipe.InsertAt(3,stry);
			strPipe.InsertAt(4,strz);
			strPipe.InsertAt(5,strbo);
			strPipe.InsertAt(6,"END-POINT");
			CString str1;
			CString str2;
			CString str3;
			str1.Format(_T("%f"),AssignPt->x+2);
			str2.Format(_T("%f"),AssignPt->y+2);
			str3.Format(_T("%f"),AssignPt->z+2);
			strPipe.InsertAt(7,str1);
			strPipe.InsertAt(8,str2);
			strPipe.InsertAt(9,str3);
			strPipe.InsertAt(10,strbo);
			CreatComponet(strPipe);
		}
	}
}



void PCFComponentMgr::InitAddAssignFlow(PCFJunsMgr& pJunMgr,PCFPipesMgr& pPipeMgr)  //���ܵ���������ָ������
{
	int n = 0;
	int i = 0;
	int m = 0;
	int j = 0;
	int k = 0;
	int ChoisePt = 0;
	IteratorPtr<PCFJun> JunitPtr(pJunMgr.CreateIt()); //�ڵ��б�
	IteratorPtr<PCFPipe> PipeitPtr(pPipeMgr.CreateIt()); //�ܵ��б�
	CStringArray strAssignFlow;
	PCFPipe* pPipe = NULL;
	PCFJun* pJun = NULL;
	for(PipeitPtr->Fist();!PipeitPtr->IsDone();PipeitPtr->Next())  //�����ܵ�
	{
		ChoisePt = 0;
		pPipe = &PipeitPtr->CurrentItem();
		for(JunitPtr->Fist();!JunitPtr->IsDone();JunitPtr->Next()) //�����ڵ�
		{
			pJun = &JunitPtr->CurrentItem();
			if(pJun == NULL || pPipe == NULL)
				break;
			k = CamparePt(*pJun,*pPipe);
			ChoisePt = ChoisePt+k;
			if (ChoisePt > 2)
				break;
		}
		if (ChoisePt == 3 || ChoisePt ==0 || ChoisePt ==4 || ChoisePt ==5) //��Ϊ��ͬ������ʹ��Ϊ4��5
			continue;
		else
		{
			AcGePoint3d AssignPt;
			strAssignFlow.InsertAt(0,_T("ASSIGNFLOW"));
			if (ChoisePt ==1)
				AssignPt = pPipe->EndPt();
			else
				AssignPt = pPipe->StartPt();
				double m_bore = pPipe->Bore();
				CString strx;
				CString stry;
				CString strz;
				CString strbo;
				strx.Format(_T("%f"),AssignPt.x);
				stry.Format(_T("%f"),AssignPt.y);
				strz.Format(_T("%f"),AssignPt.z);
				strbo.Format(_T("%f"),m_bore);
				strAssignFlow.InsertAt(1,_T("END-POINT"));
				strAssignFlow.InsertAt(2,strx);
				strAssignFlow.InsertAt(3,stry);
				strAssignFlow.InsertAt(4,strz);
				strAssignFlow.InsertAt(5,strbo);
				strAssignFlow.InsertAt(6,_T("END-POINT"));
				strAssignFlow.InsertAt(7,strx);
				strAssignFlow.InsertAt(8,stry);
				strAssignFlow.InsertAt(9,strz);
				strAssignFlow.InsertAt(10,strbo);
				CreatComponet(strAssignFlow);
		}
	}
}

int PCFComponentMgr::CamparePt(PCFJun& InJun,PCFPipe& InPipe)  //�ڵ���ܵ��Ƚ�
{
	AcGePoint3d* InjunPt;
	int ChoisePt = 0;
	int EndPt = 0;
	int StartPt = 0;
	int i = 0;
	AcGePoint3d InPipeStartPt = InPipe.StartPt();
	AcGePoint3d InPipeEndPt = InPipe.EndPt();
	POSITION position = InJun.GetPtList().GetHeadPosition();  //�ڵ������б�
	int n = InJun.GetPtList().GetCount();
	for (i = 0;i < n;i++)
	{
		if (position != NULL)
		{
			InjunPt = InJun.GetPtList().GetNext(position);
			if (fabs((*InjunPt).x-InPipeEndPt.x)<0.1 && fabs((*InjunPt).y-InPipeEndPt.y)<0.1 && fabs((*InjunPt).z-InPipeEndPt.z)<0.1)
			{
				EndPt = 2;
				InPipe.EndPt(*InjunPt);  //����ڵ���ܵ���������ʼ�ܵ�������ڵ�
				InPipe.OutJun(InJun.GetKey());
			}
			if (fabs((*InjunPt).x-InPipeStartPt.x)<0.1 && fabs((*InjunPt).y-InPipeStartPt.y)<0.1 && fabs((*InjunPt).z-InPipeStartPt.z)<0.1)
			{
				StartPt = 1;
				InPipe.StartPt(*InjunPt);
				InPipe.InJun(InJun.GetKey());
			}
		}
	}
	ChoisePt = EndPt + StartPt;
	return ChoisePt;
}

void PCFComponentMgr::CombinationPipes(PCFPipesMgr& pPipeMgr)  //�ϲ��ֶεĹܵ�
{
	int i = 0;
	int j = 0;
	int n = 0; 
	IteratorPtr<PCFPipe> PipeitPtr(pPipeMgr.CreateIt());   //�ܵ��б�
	for(PipeitPtr->Fist();!PipeitPtr->IsDone();PipeitPtr->Next())
	{
			n = max(n,PipeitPtr->CurrentItem().GetKey());  //��ùܵ��б��йܵ�ID����
	}
	for (i = 0;i < n+1;i++)
	{
		PCFPipe* PcfPipe1 = pPipeMgr.LookUp(i);
		j = i+1;
		for (;j < n+1;j++)
		{
			PCFPipe* PcfPipe2 = pPipeMgr.LookUp(j);  //�����ܵ��б�
			if(PcfPipe1 == NULL || PcfPipe2 == NULL)
				break;
			if(PcfPipe2->StartPt() == PcfPipe1->EndPt() && PcfPipe2->InJun() == 0)
			{
				PcfPipe1->EndPt(PcfPipe2->EndPt());
				pPipeMgr.Del(PcfPipe2->GetKey());//����ܵ���ܵ��������ϲ���ɾ�����е�һ��
				i--;
			}
		}
	}

}

void PCFComponentMgr::CampareJJPt(PCFJun& InJun,PCFJun& OutJun)  //�ڵ���ڵ���бȽ�
{
	AcGePoint3d* InjunPt;
	int EndPt = 0;
	int StartPt = 0;
	int i = 0;
	int j = 0;
	AcGePoint3d* OutjunPt;
	POSITION positionIn = InJun.GetPtList().GetHeadPosition();
	int n = InJun.GetPtList().GetCount();	
	int m = OutJun.GetPtList().GetCount();           //�ڵ�������б�
	for (i = 0;i < n;i++)
	{
		if (positionIn != NULL)
		{
			InjunPt = InJun.GetPtList().GetNext(positionIn);
			POSITION positionOut = OutJun.GetPtList().GetHeadPosition(); //��ýڵ�����ͷָ��λ��
			for (j = 0;j < m;j++)
			{
				if (positionOut != NULL)
				{
					OutjunPt = OutJun.GetPtList().GetNext(positionOut);
					if (fabs((*InjunPt).x-(*OutjunPt).x)<0.1 && fabs((*InjunPt).y-(*OutjunPt).y)<0.1 && fabs((*InjunPt).z-(*OutjunPt).z)<0.1)
					{
						AcGePoint3d* AssignPt = NULL;               //������ڽڵ�������ڵ�������ȵ�����������ܵ�
						AcGePoint3d* outpt = NULL;
						CStringArray strPipe;
						outpt = InjunPt;
						strPipe.RemoveAll();
						strPipe.InsertAt(0,_T("PIPE"));
						AssignPt = OutjunPt;
						double m_bore = 200;
						CString strx = _T(' ');
						CString stry = _T(' ');
						CString strz = _T(' ');
						CString strbo = _T(' ');
						strx.Format(_T("%f"),AssignPt->x);
						stry.Format(_T("%f"),AssignPt->y);
						strz.Format(_T("%f"),AssignPt->z);
						strbo.Format(_T("%f"),m_bore);
						strPipe.InsertAt(1,_T("END-POINT"));
						strPipe.InsertAt(2,strx);
						strPipe.InsertAt(3,stry);
						strPipe.InsertAt(4,strz);
						strPipe.InsertAt(5,strbo);
						strPipe.InsertAt(6,_T("END-POINT"));
						CString str1 = _T(' ');
						CString str2 = _T(' ');
						CString str3 = _T(' ');
						str1.Format(_T("%f"),outpt->x);
						str2.Format(_T("%f"),outpt->y);
						str3.Format(_T("%f"),outpt->z);
						strPipe.InsertAt(7,str1);
						strPipe.InsertAt(8,str2);
						strPipe.InsertAt(9,str3);
						strPipe.InsertAt(10,strbo);
						CreatComponet(strPipe);
						break;
					}
				}
			}
		}
	}
}

void PCFComponentMgr::InitNOZZLE_Ptconcet(CStringArray &strSet)
{
	unsigned long wordnum = 0;
	unsigned long wordsize = strSet.GetSize();
	unsigned long i = 0;
	int j = 0;
	CStringArray temppt;
	bool tempflag = false;
	CString tem1,tem2,tem3;

	for(wordnum = 0;wordnum < wordsize;wordnum++)
	{
		temppt.RemoveAll();
		tempflag = false;
		if (strSet.GetAt( wordnum ) == _T("NOZZLE"))
		{       
			for (i = wordnum;i < wordnum+20;i++)
			{
				if (strSet.GetAt(i) == _T("CO-ORDS"))
				{
					temppt.Add(strSet.GetAt(i+1));
					temppt.Add(strSet.GetAt(i+2));
					temppt.Add(strSet.GetAt(i+3));
					break;
				}
			}
			for (i = wordnum, j = wordnum;i < wordnum+30,j > wordnum-30;i++,j--)
			{
				if (strSet.GetAt(i) == _T("END-CONNECTION-EQUIPMENT"))
				{
					j = i;
					break;
				}
				if (strSet.GetAt(j) == _T("END-CONNECTION-EQUIPMENT"))
				{
					i = j;
					break;
				}
			}
			for (;i < j+30;i++)
			{
				if (strSet.GetAt(i) == _T("CENTRE-POINT"))
				{
					temppt.Add(strSet.GetAt(i+1));
					temppt.Add(strSet.GetAt(i+2));             
					temppt.Add(strSet.GetAt(i+3));
					tempflag = true;
					break;
				}
			}	
		}
		if(tempflag == true)
		{
			for (i = 0;i <wordsize;i++)
			{
				if (strSet.GetAt(i) == _T("END-POINT"))
				{
					if ((temppt.GetAt(0) == strSet.GetAt(i+1))&&(temppt.GetAt(1) == strSet.GetAt(i+2))&&(temppt.GetAt(2) == strSet.GetAt(i+3)))
					{
						tem1 = strSet.GetAt(i+1);
						tem2 = strSet.GetAt(i+2);
						tem3 = strSet.GetAt(i+3);
						strSet.SetAt((i+1),temppt.GetAt(3));
						strSet.SetAt((i+2),temppt.GetAt(4));
						strSet.SetAt((i+3),temppt.GetAt(5));
						tem1 = strSet.GetAt(i+1);
						tem2 = strSet.GetAt(i+2);
						tem3 = strSet.GetAt(i+3);
						break;                                   //Ѱ�ҷ�֧������֧�����Ϊ�豸����
					}
				}
			}
		}
	}
}

void PCFComponentMgr::InitEquipment_PT(CStringArray &strSet)
{
	unsigned long wordnum = 0;
	unsigned long wordsize = strSet.GetSize();
	AcGePoint3d EquipElement;
	AcGePoint3d NozzleElement;
	CString str;
	unsigned long i = 0;
	int n=0;
	int j=0;
	int m = 0;
	int k = 0;
	CStringArray temppt;
	for (wordnum = 0;wordnum < wordsize;wordnum++)
	{
		if (strSet.GetAt( wordnum ) == _T("NOZZLE"))
		{
			for (i = wordnum; i < wordnum+100; i++)
			{
				if (strSet.GetAt(i) == _T("CO-ORDS"))
				{
					temppt.Add(strSet.GetAt(i+1));
					temppt.Add(strSet.GetAt(i+2));
					temppt.Add(strSet.GetAt(i+3));
				}
				if (strSet.GetAt(i) == _T("CONNECTION-REFERENCE"))
				{
					temppt.Add(strSet.GetAt(i+1));                   //��¼�豸������
					break;
				}
			}
		}
	}
	for (i = 3; i < temppt.GetSize();)
	{
		float k = 1;
		for (j = i+4; j < temppt.GetSize();)
		{
			if(temppt.GetAt(j) == temppt.GetAt(i))
			{
				EquipElement.x = _tcstod( UELPCSTR (temppt.GetAt(j-3)), NULL );
				EquipElement.y = _tcstod( UELPCSTR (temppt.GetAt(j-2)), NULL );
				EquipElement.z = _tcstod( UELPCSTR (temppt.GetAt(j-1)), NULL );
				NozzleElement.x = _tcstod( UELPCSTR (temppt.GetAt(i-3)), NULL );
				NozzleElement.y = _tcstod( UELPCSTR (temppt.GetAt(i-2)), NULL );
				NozzleElement.z = _tcstod( UELPCSTR (temppt.GetAt(i-1)), NULL );
				CString strx;
				CString stry;
				CString strz;
				strx.Format(_T("%f"),EquipElement.x+NozzleElement.x);
				stry.Format(_T("%f"),EquipElement.y+NozzleElement.y);
				strz.Format(_T("%f"),EquipElement.z+NozzleElement.z);
				temppt.SetAt(i-3,strx);
				temppt.SetAt(i-2,stry);
				temppt.SetAt(i-1,strz);
				temppt.RemoveAt(j-3,4);
				k = k+1;
			}
			else
				j=j+4;
		}
		NozzleElement.x = _tcstod( UELPCSTR (temppt.GetAt(i-3)), NULL )/k; //k��ʾ�м�����֧��NOZZLE
		NozzleElement.y = _tcstod( UELPCSTR (temppt.GetAt(i-2)), NULL )/k;
		NozzleElement.z = _tcstod( UELPCSTR (temppt.GetAt(i-1)), NULL )/k;    
		CString str1;
		CString str2;
		CString str3;
		str1.Format(_T("%f"),NozzleElement.x);
		str2.Format(_T("%f"),NozzleElement.y);
		str3.Format(_T("%f"),NozzleElement.z);
		temppt.SetAt(i-3,str1);
		temppt.SetAt(i-2,str2);
		temppt.SetAt(i-1,str3);                    //��¼�豸���ĵ�
		i=i+4;
	}
	for (wordnum = 0;wordnum < wordsize;wordnum++)
	{
		if (strSet.GetAt( wordnum ) == _T("NOZZLE"))
		{
			for (i = 3; i < temppt.GetSize();)
			{
				for (j = wordnum ;j < wordnum+50 ;j++)
				{
					if (strSet.GetAt(j) == temppt.GetAt(i))
					{
						n = wordnum;
						m = wordnum;
						for (k = 0; k < 100;k++)
						{
							n++;
							m--;
							if (strSet.GetAt(m) == _T("END-CONNECTION-EQUIPMENT"))
							{
								n = m;
								break;
							}
							if (strSet.GetAt(n) == _T("END-CONNECTION-EQUIPMENT"))
							{
								m = n;
								break;
							}
						}
						for (n = m;n < m+50;n++)                //�����豸���ĵ�
						{
							if (strSet.GetAt(n) == _T("CENTRE-POINT"))
							{
								strSet.SetAt(n+1,temppt.GetAt(i-3));
								CString str = temppt.GetAt(i-3);
								strSet.SetAt(n+2,temppt.GetAt(i-2));
								strSet.SetAt(n+3,temppt.GetAt(i-1));
								break;
							}
						}
					}
				}
				i=i+4;
			}
		}
	}
	temppt.RemoveAll();
}

// void PCFComponentMgr::InitJunKey_DelDiscription( CStringArray &strDelDiscription )		//���������������⣻
// {
// 	unsigned long wordnum ;
// 	for ( wordnum = 0; wordnum < strDelDiscription.GetSize(); wordnum ++ )		//�������飻
// 	{
// 		//�Է�֮�ڵ�Ԫ�����������ݽ��б����޸ģ�
// 		if ( IsKeyWord( strDelDiscription.GetAt( wordnum ) ) && strDelDiscription.GetAt( wordnum ) != _T("NOZZLE")
// 			&& strDelDiscription.GetAt( wordnum ) != _T("END-CONNECTION-EQUIPMENT") && strDelDiscription.GetAt( wordnum ) != _T("END-CONNECTION-NULL") 
// 			&& strDelDiscription.GetAt( wordnum ) != _T("Over") && strDelDiscription.GetAt( wordnum ) != _T("INSTRUMENT")
// 			&& strDelDiscription.GetAt( wordnum ) != _T("FTUBE") && strDelDiscription.GetAt( wordnum ) != _T("CLOS")
// 			&& strDelDiscription.GetAt( wordnum ) != _T("WELD"))
// 		{
// 			int k = wordnum;
// 			int p = 0;
// 			int q = 0;
// 			do 
// 			{
// 				if ( strDelDiscription.GetAt( k ) == _T("PUMP") || strDelDiscription.GetAt( k ) == _T("VESS") )
// 				{
// 					break ;
// 				}
// 				if ( strDelDiscription.GetAt( k ) == _T("ITEM-DESCRIPTION") )
// 				{
// 					p = k ;		//��¼ITEM-DESCRIPTION��λ��
// 				}
// 				else
// 				{
// 					if ( strDelDiscription.GetAt( k ) == _T("INSULATION") )
// 					{
// 						q = k ;	//��¼INSULATION��λ��
// 						break ;	//����ѭ��
// 					}
// 				}
// 				k ++ ;
// 			} while ( 1 );		//��Ϊÿһ��Ԫ������������������ԣ����Բ����������ѭ����
// 			
// 			strDelDiscription.SetAt( ( p + 1 ), _T("unset") ) ;		//����������������Ϊunset��
// 			int des_size = q - p ;
// 			for ( int m = 2; m< des_size;m ++ )				//�Ƴ��м������ֽڣ�
// 			{				
// 				strDelDiscription.RemoveAt( ( p + m ) ) ;
// 			}
// 			wordnum = k ;    //������һ��Ԫ����
// 		}
// 	}
// }
// 
// void PCFComponentMgr::InitJunKey_AddAssignFlowStartBranch( CStringArray &strAssignFlow )		//��û������Ԫ���ķ�֧ͷ����ָ��������
// {
// 	CStringArray AddAssignFlow ;
// 	CStringArray CurCapMsg ;
// 	unsigned long wordnum ;
// 	for ( wordnum = 0; wordnum < strAssignFlow.GetSize(); wordnum ++ )		//��������б���������Ϊ��̬�ģ�
// 	{		//��֧ͷΪCAP��ͷ��Ԫ������Ϊ���Ժ�Ҫ��CAP��ΪPIPE
// 		if ( IsKeyWord( strAssignFlow.GetAt( wordnum ) ) && strAssignFlow.GetAt( wordnum ) == _T("END-CONNECTION-NULL") 
// 			 && strAssignFlow.GetAt( wordnum + 7 ) == _T("CAP") )
// 		{
// 			int m = wordnum + 7 ;
// 			int k = wordnum + 7 ;
// 			CurCapMsg.RemoveAll() ;		//��ʹ��֮ǰ������飻
// 			do 
// 			{
// 				CurCapMsg.Add( strAssignFlow.GetAt( m ) ) ;
// 				m ++ ;
// 			} while ( !IsKeyWord( strAssignFlow.GetAt( m ) ) );
// 			strAssignFlow.InsertAt( k, _T("ASSIGNFLOW") ) ;			//����ָ������
// 			strAssignFlow.InsertAt( ( k + 1 ),_T("END-POINT") ) ;
// 			strAssignFlow.InsertAt( ( k + 2 ), CurCapMsg.GetAt( 2 ) ) ;
// 			strAssignFlow.InsertAt( ( k + 3 ), CurCapMsg.GetAt( 3 ) ) ;
// 			strAssignFlow.InsertAt( ( k + 4 ), CurCapMsg.GetAt( 4 ) ) ;
// 			strAssignFlow.InsertAt( ( k + 5 ), CurCapMsg.GetAt( 5 ) ) ;
// 			strAssignFlow.InsertAt( ( k + 6 ),_T("END-POINT") ) ;
// 			strAssignFlow.InsertAt( ( k + 7 ), CurCapMsg.GetAt( 2 ) ) ;
// 			strAssignFlow.InsertAt( ( k + 8 ), CurCapMsg.GetAt( 3 ) ) ;
// 			strAssignFlow.InsertAt( ( k + 9 ), CurCapMsg.GetAt( 4 ) ) ;
// 			strAssignFlow.InsertAt( ( k + 10 ), CurCapMsg.GetAt( 5 ) ) ;
// 
// 			wordnum = 0 ;		//���¿�ʼ������
// 		}
// 	}
// 
// 	for ( wordnum = 0; wordnum < strAssignFlow.GetSize(); wordnum ++ )		//��������б�����Ϊ��̬�����飻
// 	{		//�����PIPE��ʼ�ķ�֧��
// 		if ( IsKeyWord( strAssignFlow.GetAt( wordnum ) ) && strAssignFlow.GetAt( wordnum ) == _T("END-CONNECTION-NULL") 
// 			&& strAssignFlow.GetAt( wordnum + 7 ) == _T("PIPE") )
// 		{
// 			int m = wordnum + 7 ;
// 			int k = wordnum + 7 ;
// 			bool b_conentbranch = FALSE ;
// 			CurCapMsg.RemoveAll() ;			//�����ʱ���飻
// 			do 
// 			{
// 				CurCapMsg.Add( strAssignFlow.GetAt( m ) ) ;
// 				m ++ ;
// 			} while ( !IsKeyWord( strAssignFlow.GetAt( m ) ) );
// 			for ( int p = 0 ;p < strAssignFlow.GetSize()-3; p ++ )		//�ж��Ƿ������������ķ�֧��
// 			{
// 				double strAssignFlow1 = _tcstod( UELPCSTR (strAssignFlow.GetAt( p+1 ) ) ) ;
// 				double strAssignFlow2 = _tcstod( UELPCSTR (strAssignFlow.GetAt( p+2 ) ) ) ;
// 				double strAssignFlow3 = _tcstod( UELPCSTR (strAssignFlow.GetAt( p+3 ) ) ) ;
// 				double CurCapMsg1 = _tcstod( UELPCSTR (CurCapMsg.GetAt( 2 ) ) ) ;
// 				double CurCapMsg2 = _tcstod( UELPCSTR (CurCapMsg.GetAt( 3 ) ) ) ;
// 				double CurCapMsg3 = _tcstod( UELPCSTR (CurCapMsg.GetAt( 4 ) ) ) ;
// 				unsigned long StrminusCurCap1 = fabs( strAssignFlow1 - CurCapMsg1 ) ;
// 				unsigned long StrminusCurCap2 = fabs( strAssignFlow2 - CurCapMsg2 ) ;
// 				unsigned long StrminusCurCap3 = fabs( strAssignFlow3 - CurCapMsg3 ) ;
// 				if ( strAssignFlow.GetAt( p ) == "BRANCH1-POINT" && StrminusCurCap1 < 0.01
// 					&& StrminusCurCap2 < 0.01 && StrminusCurCap3 < 0.01 )
// 				{
// 					b_conentbranch = TRUE ;		//�����������ķ�֧Ϊ��
// 					break ;
// 				}
// 			}
// 			if ( !b_conentbranch )		//���û�����������ķ�֧�����ָ��������
// 			{
// 				strAssignFlow.InsertAt( k, _T("ASSIGNFLOW") ) ;
// 				strAssignFlow.InsertAt( ( k + 1 ),_T("END-POINT") ) ;
// 				strAssignFlow.InsertAt( ( k + 2 ), CurCapMsg.GetAt( 2 ) ) ;
// 				strAssignFlow.InsertAt( ( k + 3 ), CurCapMsg.GetAt( 3 ) ) ;
// 				strAssignFlow.InsertAt( ( k + 4 ), CurCapMsg.GetAt( 4 ) ) ;
// 				strAssignFlow.InsertAt( ( k + 5 ), CurCapMsg.GetAt( 5 ) ) ;
// 				strAssignFlow.InsertAt( ( k + 6 ),_T("END-POINT") ) ;
// 				strAssignFlow.InsertAt( ( k + 7 ), CurCapMsg.GetAt( 2 ) ) ;
// 				strAssignFlow.InsertAt( ( k + 8 ), CurCapMsg.GetAt( 3 ) ) ;
// 				strAssignFlow.InsertAt( ( k + 9 ), CurCapMsg.GetAt( 4 ) ) ;
// 				strAssignFlow.InsertAt( ( k + 10 ), CurCapMsg.GetAt( 5 ) ) ;
// 
// 				wordnum = 0 ;		//���¿�ʼ������
// 			}
// 		}
// 	}
// }
// 
// void PCFComponentMgr::InitJunKey_AddAssignFlowEndBranch( CStringArray &strAssignFlow )		//�ڷ�֧β����ָ��������
// {
// 	CStringArray AddAssignFlow ;
// 	CStringArray CurCapMsg ;
// 	unsigned long wordnum ;
//     for ( wordnum = 0; wordnum < strAssignFlow.GetSize(); wordnum ++ )	//�������� ��
// 	{	//��CAP��βʱ����ָ������
// 		if ( IsKeyWord( strAssignFlow.GetAt( wordnum ) ) && strAssignFlow.GetAt( wordnum ) == _T("CAP") 
// 			&& strAssignFlow.GetAt( wordnum + 28 ) == _T("END-CONNECTION-NULL") )
// 		{
// 			int m = wordnum ;
// 			int k ;
// 			CurCapMsg.RemoveAll() ;		//�����ʱ���飻
// 			do 
// 			{
// 				CurCapMsg.Add( strAssignFlow.GetAt( m ) ) ;
// 				m ++ ;
// 			} while ( !IsKeyWord( strAssignFlow.GetAt( m ) ) );
// 			k = m ;
// 			strAssignFlow.InsertAt( k, _T("ASSIGNFLOW") ) ;		//����ָ��������
// 			strAssignFlow.InsertAt( ( k + 1 ),_T("END-POINT") ) ;
// 			strAssignFlow.InsertAt( ( k + 2 ), CurCapMsg.GetAt( 7 ) ) ;
// 			strAssignFlow.InsertAt( ( k + 3 ), CurCapMsg.GetAt( 8 ) ) ;
// 			strAssignFlow.InsertAt( ( k + 4 ), CurCapMsg.GetAt( 9 ) ) ;
// 			strAssignFlow.InsertAt( ( k + 5 ), CurCapMsg.GetAt( 5 ) ) ;
// 			strAssignFlow.InsertAt( ( k + 6 ),_T("END-POINT") ) ;
// 			strAssignFlow.InsertAt( ( k + 7 ), CurCapMsg.GetAt( 7 ) ) ;
// 			strAssignFlow.InsertAt( ( k + 8 ), CurCapMsg.GetAt( 8 ) ) ;
// 			strAssignFlow.InsertAt( ( k + 9 ), CurCapMsg.GetAt( 9 ) ) ;
// 			strAssignFlow.InsertAt( ( k + 10 ), CurCapMsg.GetAt( 5 ) ) ;
// 
// 			wordnum = 0 ;		//���¿�ʼ���� ��
// 		}
// 	}
// 	
// 	for ( wordnum = 0; wordnum < strAssignFlow.GetSize(); wordnum ++ )		//�������� ��
// 	{		//�����PIPE��β�������ָ��������
// 		if ( IsKeyWord( strAssignFlow.GetAt( wordnum ) ) && strAssignFlow.GetAt( wordnum ) == _T("PIPE") 
// 			&& strAssignFlow.GetAt( wordnum + 26 ) == _T("END-CONNECTION-NULL") )
// 		{
// 			int m = wordnum ;
// 			int k ;
// 			bool b_conentbranch = FALSE ;
// 			CurCapMsg.RemoveAll() ;			//�����ʱ���� ��
// 			do 
// 			{
// 				CurCapMsg.Add( strAssignFlow.GetAt( m ) ) ;
// 				m ++ ;
// 			} while ( !IsKeyWord( strAssignFlow.GetAt( m ) ) );
// 			k = m ;
// 			for ( int p = 0 ;p < strAssignFlow.GetSize()-3; p ++ )	//�ж��Ƿ���������ķ�֧ ��
// 			{
// 				if ( strAssignFlow.GetAt( p ) == "BRANCH1-POINT" && strAssignFlow.GetAt( p + 1 ) == CurCapMsg.GetAt( 7 )
// 					&& strAssignFlow.GetAt( p + 2 ) == CurCapMsg.GetAt( 8 ) && strAssignFlow.GetAt( p + 3 ) == CurCapMsg.GetAt( 9 ) )
// 				{
// 					b_conentbranch = TRUE ;		//������������ķ�֧��Ϊ�棻
// 					break ;
// 				}
// 			}
// 			if ( !b_conentbranch )		//���û�н������ķ�֧�����ָ������ ��
// 			{
// 				strAssignFlow.InsertAt( k, "ASSIGNFLOW" ) ;
// 				strAssignFlow.InsertAt( ( k + 1 ),"END-POINT" ) ;
// 				strAssignFlow.InsertAt( ( k + 2 ), CurCapMsg.GetAt( 7 ) ) ;
// 				strAssignFlow.InsertAt( ( k + 3 ), CurCapMsg.GetAt( 8 ) ) ;
// 				strAssignFlow.InsertAt( ( k + 4 ), CurCapMsg.GetAt( 9 ) ) ;
// 				strAssignFlow.InsertAt( ( k + 5 ), CurCapMsg.GetAt( 10 ) ) ;
// 				strAssignFlow.InsertAt( ( k + 6 ),"END-POINT" ) ;
// 				strAssignFlow.InsertAt( ( k + 7 ), CurCapMsg.GetAt( 7 ) ) ;
// 				strAssignFlow.InsertAt( ( k + 8 ), CurCapMsg.GetAt( 8 ) ) ;
// 				strAssignFlow.InsertAt( ( k + 9 ), CurCapMsg.GetAt( 9 ) ) ;
// 				strAssignFlow.InsertAt( ( k + 10 ), CurCapMsg.GetAt( 10 ) ) ;
// 
// 				wordnum = 0 ;		//���¿�ʼ���� ��
// 			}
// 
// 		}
// 	}
// }
// 
// void PCFComponentMgr::InitJunKey_AddPipeAndAssignFlow( CStringArray &strPipeAndAssignFlow )  //�ڷǷ���Ԫ���ĺ������ؼ��֣�
// {
// 	CStringArray CurElement ;    //�������ķǷ�������Ԫ������Ϣ ��
// 	unsigned long wordnum = 0 ;
// 	for ( wordnum = 0; wordnum < strPipeAndAssignFlow.GetSize(); wordnum ++ )  //��������б��� ��
// 	{		//����������ЩԪ����������ǷǷ�Ԫ����β ��
// 		if ( IsKeyWord( strPipeAndAssignFlow.GetAt( wordnum ) ) && strPipeAndAssignFlow.GetAt( wordnum ) != "PIPE"
// 			 && strPipeAndAssignFlow.GetAt( wordnum ) != "END-CONNECTION-NULL" && strPipeAndAssignFlow.GetAt( wordnum ) != "END-CONNECTION-EQUIPMENT" 
// 			 && strPipeAndAssignFlow.GetAt( wordnum ) != "Over" && strPipeAndAssignFlow.GetAt( wordnum ) != "CAP"
// 			 && strPipeAndAssignFlow.GetAt( wordnum ) != "NOZZLE" && strPipeAndAssignFlow.GetAt( wordnum ) != "VALVE"
// 			 && strPipeAndAssignFlow.GetAt( wordnum ) != "ASSIGNFLOW" && strPipeAndAssignFlow.GetAt( wordnum ) != "PUMP"
// 			 && strPipeAndAssignFlow.GetAt( wordnum ) != "VESS" && strPipeAndAssignFlow.GetAt( wordnum ) != "FLANGE" )
// 		{
// 			CurElement.RemoveAll() ;		//�����ʱ���� ��
// 			int m = wordnum ;
// 			do		//���浱ǰ�ڵ����Ϣ��
// 			{
// 				CurElement.Add( strPipeAndAssignFlow.GetAt( m ) ) ;
// 				m ++ ;
// 				if ( strPipeAndAssignFlow.GetAt( m ) == "PUMP" || strPipeAndAssignFlow.GetAt( m ) == "VESS" )	//�����豸��Ϣʱ������
// 				{
// 					continue ;
// 				}
// 			} while ( !IsKeyWord( strPipeAndAssignFlow.GetAt( m ) ) );
// 			if ( strPipeAndAssignFlow.GetAt( m ) == "END-CONNECTION-NULL" )		//����Ƿ�֧β ��
// 			{
// 				bool b_ConenctBranch = FALSE ;		//�ж��Ƿ������з�֧ ��
// 				for ( int p = 0; p < strPipeAndAssignFlow.GetSize()-3; p ++ )
// 				{
// 					if ( ( strPipeAndAssignFlow.GetAt( p ) == "BRANCH1-POINT" || strPipeAndAssignFlow.GetAt( p ) == "END-POINT" ) && strPipeAndAssignFlow.GetAt( p + 1 ) == CurElement.GetAt( 7 )
// 						 && strPipeAndAssignFlow.GetAt( p + 2 ) == CurElement.GetAt( 8 ) && strPipeAndAssignFlow.GetAt( p + 3 ) == CurElement.GetAt( 9 ) )
// 					{
// 						b_ConenctBranch = TRUE ;	//�����˷�֧��Ϊ�棻
// 						break ;
// 					}
// 				}
// 				if ( !b_ConenctBranch )		//���û�����ӷ�֧�������ܵ���Ϣ��
// 				{
// 					strPipeAndAssignFlow.InsertAt( m,"PIPE" ) ;
// 					strPipeAndAssignFlow.InsertAt( ( m + 1 ),"END-POINT" ) ;
// 					strPipeAndAssignFlow.InsertAt( ( m + 2 ),CurElement.GetAt( 7 ) ) ;
// 					strPipeAndAssignFlow.InsertAt( ( m + 3 ),CurElement.GetAt( 8 ) ) ;
// 					strPipeAndAssignFlow.InsertAt( ( m + 4 ),CurElement.GetAt( 9 ) ) ;
// 					strPipeAndAssignFlow.InsertAt( ( m + 5 ),CurElement.GetAt( 10 ) ) ;
// 					strPipeAndAssignFlow.InsertAt( ( m + 6 ),"END-POINT" ) ;
// 					strPipeAndAssignFlow.InsertAt( ( m + 7 ),CurElement.GetAt( 7 ) ) ;
// 					strPipeAndAssignFlow.InsertAt( ( m + 8 ),CurElement.GetAt( 8 ) ) ;
// 					strPipeAndAssignFlow.InsertAt( ( m + 9 ),CurElement.GetAt( 9 ) ) ;
// 					strPipeAndAssignFlow.InsertAt( ( m + 10 ),CurElement.GetAt( 10 ) ) ;
// 					strPipeAndAssignFlow.InsertAt( ( m + 11 ), "ITEM-CODE") ;
// 					strPipeAndAssignFlow.InsertAt( ( m + 12 ), "PA200") ;
// 					strPipeAndAssignFlow.InsertAt( ( m + 13 ), "FABRICATION-ITEM") ;
// 					strPipeAndAssignFlow.InsertAt( ( m + 14 ), "WEIGHT") ;
// 					strPipeAndAssignFlow.InsertAt( ( m + 15 ), "0.000000") ;
// 					strPipeAndAssignFlow.InsertAt( ( m + 16 ), "ITEM-DESCRIPTION") ;
// 					strPipeAndAssignFlow.InsertAt( ( m + 17 ), "unset") ;
// 					strPipeAndAssignFlow.InsertAt( ( m + 18 ), "INSULATION") ;
// 					strPipeAndAssignFlow.InsertAt( ( m + 19 ), "OFF") ;
// 					strPipeAndAssignFlow.InsertAt( ( m + 20 ), "INSULATION-SPEC") ;
// 					strPipeAndAssignFlow.InsertAt( ( m + 21 ), "unset") ;
// 					strPipeAndAssignFlow.InsertAt( ( m + 22 ), "TRACING") ;
// 					strPipeAndAssignFlow.InsertAt( ( m + 23 ), "OFF") ;
// 					strPipeAndAssignFlow.InsertAt( ( m + 24 ), "TRACING-SPEC") ;
// 					strPipeAndAssignFlow.InsertAt( ( m + 25 ), "unset") ;
// 					wordnum = 0 ;     //���¿�ʼ���� ��
// 				}
// 			}
// 		}
// 	}
// 
// }
// 
// 
// void PCFComponentMgr::InitJunKey_KeepPtConcet( CStringArray &strConectPt )		//ʹ���ڵĽڵ�֮���������ģ�
// {
// 	AcGePoint3d CurElement ;	//��ǰ�ڵ����ꣻ
// 	AcGePoint3d AfterElement ;	//��һ���ڵ�����
// 	unsigned long wordnum ;
// 
// 	int p ;
// 	int q ;
// 	int r ;
// 
// 	double minlength = 0.5 ;
// 
// 	for ( wordnum = 0 ; wordnum < strConectPt.GetSize(); wordnum ++ )	//��������б���
// 	{
// 		if ( IsKeyWord( strConectPt.GetAt( wordnum ) ) && strConectPt.GetAt( wordnum ) != "END-CONNECTION-NULL" && strConectPt.GetAt( wordnum ) != "END-CONNECTION-EQUIPMENT" && strConectPt.GetAt( wordnum ) != "NOZZLE" )
// 		{									//��ǰ�ڵ㱣֤��ͬһ����֧�У�
// 			int m = wordnum ;
// 			int num = 0 ;
// 
// 			if ( strConectPt.GetAt( wordnum ) == "Over" )	//����ǽ�β������ѭ��������������
// 			{
// 				break ;
// 			}
// 
// 			do			//���浱ǰ�ڵ����Ϣ��
// 			{
// 				if ( strConectPt.GetAt( m ) == _T("END-POINT") && num == 0 )
// 				{	
// 					num++;
// 					m = m+5;
// 				
// 				}
// 				
// 				if ( strConectPt.GetAt( m ) == _T("END-POINT") && num == 1 )
// 				{			
// 					CurElement.x = _tcstod( UELPCSTR (strConectPt.GetAt( m+1 ) ) );
// 					CurElement.y = _tcstod( UELPCSTR (strConectPt.GetAt( m+2 ) ) );
// 					CurElement.z = _tcstod( UELPCSTR (strConectPt.GetAt( m+3 ) ) );
// 
// 					m = m + 5 ; 
// 				}
// 				m++ ;
// 			}while( !IsKeyWord( strConectPt.GetAt( m ) ) ); 
// 
// 			if ( strConectPt.GetAt( m ) != "END-CONNECTION-NULL" && strConectPt.GetAt( m ) != "END-CONNECTION-EQUIPMENT" && strConectPt.GetAt( m ) != "NOZZLE" )
// 			{												//��һ���ڵ㱣֤��һ����֧�У�
// 				if ( strConectPt.GetAt( m ) == "Over" )		//������־���˳�ѭ����
// 				{
// 					break ;
// 				}
// 
// 				int j = m ;
// 				int k = 0 ;
// 				do			//������һ���ڵ����Ϣ��
// 				{
// 					if ( strConectPt.GetAt( j ) == _T("END-POINT") && k == 0 )
// 					{	
// 						AfterElement.x = _tcstod( UELPCSTR (strConectPt.GetAt( j+1 ) ) );
// 						AfterElement.y = _tcstod( UELPCSTR (strConectPt.GetAt( j+2 ) ) );
// 						AfterElement.z = _tcstod( UELPCSTR (strConectPt.GetAt( j+3 ) ) );
// 						p = j + 1 ;
// 						q = j + 2 ;
// 						r = j + 3 ;
// 						k++;
// 						j = j+5;
// 					
// 					}
// 				
// 					if ( strConectPt.GetAt( j ) == _T("END-POINT") && k == 1 )
// 					{			
// 						j = j+5; 
// 					}
// 
// 					j++ ;
// 				} while ( !IsKeyWord( strConectPt.GetAt( j ) ) );
// 					//�������ڵ����������С��ʱ�����Ϊ�������ģ�
// 				if ( CurElement.x != AfterElement.x && fabs( CurElement.x - AfterElement.x ) < minlength  )
// 				{				
// 					AfterElement.x = CurElement.x ;	
// 					CString str ;
// 					str.Format( "%f",AfterElement.x ) ;
// 					strConectPt.SetAt( p, str ) ; 
// 				} 
// 
// 				if ( CurElement.y != AfterElement.y && fabs( CurElement.y - AfterElement.y ) < minlength  )
// 				{				
// 					AfterElement.y = CurElement.y ;	
// 					CString str ;
// 					str.Format( "%f",AfterElement.y ) ;
// 					strConectPt.SetAt( q, str ) ; 
// 				} 
// 
// 				if ( CurElement.z != AfterElement.z && fabs( CurElement.z - AfterElement.z ) < minlength  )
// 				{				
// 					AfterElement.z = CurElement.z ;	
// 					CString str ;
// 					str.Format( "%f",AfterElement.z ) ;
// 					strConectPt.SetAt( r, str ) ; 
// 				} 
// 
// 			
// 			}
// 			wordnum = m - 1 ;
// 		}
// 	}
// }
// 
// void PCFComponentMgr::InitJunKey_NoPCFJuntoPipe( const CStringArray &strSet )    //����PCF�ڵ��Ԫ������ΪPIPE
// {
// 	unsigned long wordnum = 0 ;
// 	unsigned long wordsize = strSet.GetSize() ;
// 
// 	for ( wordnum = 0 ; wordnum < wordsize ; wordnum ++ )
// 	{
// 		if ( IsKeyWord( strSet.GetAt( wordnum ) ) )    //�����ǰ�ڵ��ǹؼ������ַ����鲻Ϊ��;
// 		{
// 			if ( strSet.GetAt( wordnum ) == "NOZZLE" )		//�������ڲ���ʶNOZZLE���������ַ����а������ε���12/11/2008
// 			{
// 				wordnum = wordnum + 6 ;
// 				continue ;
// 			}
// 			if ( strSet.GetAt( wordnum ) == "WELD" )		//�������ڲ���ʶNOZZLE���������ַ����а������ε���12/11/2008
// 			{
// 				wordnum = wordnum + 27 ;
// 				continue ;
// 			}
// 			if ( strSet.GetAt( wordnum ) == "SUPPORT" )
// 			{
// 				wordnum = wordnum + 6 ;
// 				continue ;
// 			}
// 			if (strSet.GetAt( wordnum ) == "CAP" || strSet.GetAt( wordnum ) == "FLANGE" || strSet.GetAt( wordnum ) == "GASKET" || strSet.GetAt( wordnum ) == "FBLIND" 
// 				 || strSet.GetAt( wordnum ) == "FTUBE" )
// 			{
// 				JuntoPipe.Add( "PIPE" ) ;		//����ڵ�Ĺؼ��ֲ���PCF�Ľڵ�,��ʹ��ؼ���ΪPIPE,���浽JuntoPipe�ַ�������;
// 			}
// 			else
// 			{
// 				if ( strSet.GetAt( wordnum ) == "BEND" )		//����ؼ�����BEND�����ͳһ��ΪELBOW
// 				{
// 					JuntoPipe.Add( "ELBOW" ) ;
// 				}
// 				else
// 				{
// 					JuntoPipe.Add( strSet.GetAt( wordnum ) ) ;//��PCF�Ĺؼ��������ı�,���浽JuntoPipe
// 				}
// 			}
// 		}
// 		else
// 		{
// 			JuntoPipe.Add( strSet.GetAt( wordnum ) ) ;//���ǹؼ����򱣴浽JuntoPipe
// 		}
// 	}
// }
// 
// void PCFComponentMgr::InitJunKey_MergePipe( const CStringArray &strMerge )
// {
// 	CStringArray MergePipe1 ;
// 	CStringArray MergePipe2 ;
// 	CStringArray strSet ;
// 	unsigned long wordnum = 0 ;
// 	unsigned long wordsize = strMerge.GetSize() ;
// 	int i = 0 ;
// 
// 	for ( wordnum = 0 ; wordnum < wordsize ; wordnum ++ )
// 	{
// 		strSet.Add( strMerge.GetAt( wordnum ) ) ;  //���ں���Ҫ���ַ��������SetAt����,��������������Ϊconst��ʽ������Ҫ�Ѹ��ַ����鱣�浽����һ���У��Ա������
// 	}
// 	for ( wordnum = 0 ; wordnum < strSet.GetSize() ; wordnum ++ )
// 	{
// 		if ( IsKeyWord( strSet.GetAt( wordnum ) ) && strSet.GetSize() != 0 )
// 		{
// 			if ( strSet.GetAt( wordnum ) == "PIPE" )   //�����ǰ�ؼ�����PIPE
// 			{
// 				int i = wordnum ;
// 				
// 				do								//�Ȱѵ�ǰ��Ԫ������Ϣ���浽MergePipe1��
// 				{
// 					MergePipe1.Add( strSet.GetAt( i ) ) ;
// 					i++ ;
// 				} while ( !IsKeyWord( strSet.GetAt( i ) ) ) ;
// 				
// 				if ( strSet.GetAt( i ) == _T("PIPE") )  //�����һ���ؼ���Ҳ��PIPE
// 				{
// 					int j = i ;
// 					do								//�Ȱ���һ��Ԫ������Ϣ���浽MergePipe2
// 					{
// 						MergePipe2.Add( strSet.GetAt( j ) ) ;
// 						j++ ;
// 					} while ( !IsKeyWord( strSet.GetAt( j ) ) ) ;
// 					//�ѵ�ǰ��PIPEԪ���ĵڶ�������ֵ��Ϊ��һ��PIPEԪ���ĵڶ�������ֵ�����ϲ�����������PIPE
// 					strSet.SetAt( ( wordnum+7 ), MergePipe2.GetAt( 7 ) ) ;  //x����
// 					strSet.SetAt( ( wordnum+8 ), MergePipe2.GetAt( 8 ) ) ;  //y����
// 					strSet.SetAt( ( wordnum+9 ), MergePipe2.GetAt( 9 ) ) ;  //z����
// 					strSet.SetAt( ( wordnum+10 ), MergePipe2.GetAt( 10 ) ) ; //PIPE�ھ�
// 
// 					int m = i ;
// 					do         //ɾ���ڶ���PIPEԪ������Ϣ��
// 					{
// 						strSet.RemoveAt( m ) ;
// 						m++ ;
// 					} while ( !IsKeyWord( strSet.GetAt( m ) ) );
// 
// 					wordnum = wordnum - 1 ;  //������1����һ��ѭ�����ӵ�ǰ�ڵ㿪ʼ�����Ժϲ������Ķ��PIPE�ڵ㣻
// 					MergePipe1.RemoveAll() ; //���MergePipe1��MergePipe2���´���ʹ�ã�
// 					MergePipe2.RemoveAll() ;
// 				}
// 				else     //��һ������PIPE�ؼ����򲻱䣻
// 				{
// 					MergePipe.Add( strSet.GetAt( wordnum ) ) ;
// 				}
// 			}
// 			else    //��ǰ����PIPE�ؼ����򲻱䣻
// 			{
// 				MergePipe.Add( strSet.GetAt( wordnum ) ) ;
// 			}
// 			
// 		} 
// 		else   //���ǹؼ����򲻱䣻
// 		{
// 			MergePipe.Add( strSet.GetAt( wordnum ) ) ;
// 		}
// 	} 
// 		
// }

void PCFComponentMgr::InitComponet(CStringArray &strSet)
{
	CStringArray ElemeneBuff;
	unsigned long wordnum = 0 ;
	unsigned long wordsize ;
	bool PerFlag = FALSE ;
	wordsize = strSet.GetSize() ;
	int q = 0 ; 
	int b=0;
	bool tempflag=true;
			
	if ( strSet.GetSize() != 0 )		//�Ա�����豸�ڵ���Ϣ���д���
	{
		int j;
		tempflag=true;
		for ( j = 0; j < strSet.GetSize(); j++ )		//��ElemeneBuff���б�����
		{
			if ( strSet.GetAt( j ) == _T("SKEY") )			//SKEY�ַ���������Ǹ��ַ�����Ϊ�豸�ؼ��֡�
			{
				if ( strSet.GetAt( j+1 ) != _T("UNKNOW") )		//������ַ�����ΪUNKNOW
				{
					if ( strSet.GetAt( j+1 ) == _T("PUMP") )
					{
						strSet.SetAt( 0, strSet.GetAt( j+1 ) ) ;  //�Ѹýڵ�ĵ�һ���ַ�����Ϣ��Ϊ�ؼ���
					}
					if ( strSet.GetAt( j+1 ) == _T("VESS") )
					{
						strSet.SetAt( 0, _T("RESERVIOR") ) ; 
					}					
				} 
				else		//���ΪUNKNOW�������û�������豸�Ĺؼ��֣�Ҫ����֮�����µ���ϵͳ���ܽ�����
				{
					AfxMessageBox( _T("�����Ƿ����е��豸���йؼ��ֵ����������µ���PCF���ܰ������е��豸��") ) ;
				}						
			}
		}
		for ( j = 0; j < strSet.GetSize(); j++ )
		{					
			if ( strSet.GetAt( j ) == _T("SKEY") )			//��SKEY������ַ�����Ϣ���ݸı䣬һ���ڵ�ֻ��һ���ؼ��ֹ�������
			{
				strSet.SetAt( ( j+1 ),_T("HAVECHANGE") ) ;
			}
		} 
		for (j=0;j<strSet.GetSize();j++)              //���豸���б���,��ͬһ�豸ֻ����һ��
		{
			if (strSet.GetAt(j)==_T("CENTRE-POINT"))
			{
				ElementBuff1.Add(strSet.GetAt(j+1));
				ElementBuff1.Add(strSet.GetAt(j+2));
				ElementBuff1.Add(strSet.GetAt(j+3));
				CString str1 = strSet.GetAt(j+1);
				CString str2 = strSet.GetAt(j+2);
				CString str3 = strSet.GetAt(j+3);
				break;
			}
		}
		b=ElementBuff1.GetSize();
		if (b!=3)
		{
			for (j=0;j<b-3;)
			{
				if ((ElementBuff1.GetAt(b-3)==ElementBuff1.GetAt(j))&&(ElementBuff1.GetAt(b-2)==ElementBuff1.GetAt(j+1))&&(ElementBuff1.GetAt(b-1)==ElementBuff1.GetAt(j+2)))
				{
					tempflag=false;
					break;
				}
				j=j+3;
			}
		}
		if (tempflag==true)
		{
			CreatComponet( strSet ) ;          //�����豸�ڵ㣻
		}
				//ElemeneBuff.RemoveAll() ;
	}
			//JuntoPipe.RemoveAll() ;			//�����ʱ���飬�Ա��´���
		//	MergePipe.RemoveAll() ;
			//ElementBuff1.RemoveAll() ;
}

void PCFComponentMgr::InitJunKey_DelTeeBranch( CStringArray &strDelBranch )		//��֤��ͨ���ӵķ�֧���ùܵ����ӵģ�
{
	unsigned long wordnum ;
	CStringArray BranchPt ;   //��ͨ��cref�˵���Ϣ��
	CStringArray AddBranchPipe ;	//��ͨcref������Ԫ������Ϣ��
	CStringArray TeeStartPt ;		//��ͨ�����������Ϣ
	CStringArray TeeEndPt ;			//��ͨ���յ�������Ϣ��
//	unsigned long wordsize = strDelBranch.GetSize() ;
	for ( wordnum = 0; wordnum < strDelBranch.GetSize(); wordnum++ )	//��������б�����
	{
		BranchPt.RemoveAll() ;    //�����ʱ���飻
		AddBranchPipe.RemoveAll() ;
		
		if ( strDelBranch.GetAt( wordnum ) == _T("TEE") )		//�������ͨ
		{
			int j ;
			j = wordnum ;

			TeeStartPt.RemoveAll() ;		//���´�ʹ��֮ǰ������飻
			TeeEndPt.RemoveAll() ;
			BranchPt.RemoveAll() ;
			do 
			{
				int num = 0 ;
				if ( strDelBranch.GetAt( j ) == _T("END-POINT") && num == 0 )		//������ͨ���������
				{
					TeeStartPt.Add( strDelBranch.GetAt( j ) ) ;
					TeeStartPt.Add( strDelBranch.GetAt( j + 1 ) ) ;
					TeeStartPt.Add( strDelBranch.GetAt( j + 2 ) ) ;
					TeeStartPt.Add( strDelBranch.GetAt( j + 3 ) ) ;
					num ++ ;
					j = j + 5 ;
				}
				if ( strDelBranch.GetAt( j ) == _T("END-POINT") && num == 1 )		//������ͨ���յ�����
				{
					TeeEndPt.Add( strDelBranch.GetAt( j ) ) ;
					TeeEndPt.Add( strDelBranch.GetAt( j + 1 ) ) ;
					TeeEndPt.Add( strDelBranch.GetAt( j + 2 ) ) ;
					TeeEndPt.Add( strDelBranch.GetAt( j + 3 ) ) ;
					j = j + 5 ;
				}

				if ( strDelBranch.GetAt( j ) == _T("BRANCH1-POINT") )		//������ͨ��cref������
				{
					BranchPt.Add( _T("END-POINT") ) ;
					BranchPt.Add( strDelBranch.GetAt( j+1 ) ) ;
					BranchPt.Add( strDelBranch.GetAt( j+2 ) ) ;
					BranchPt.Add( strDelBranch.GetAt( j+3 ) ) ;
					break ;
				}
				j++ ;
			} while ( !IsKeyWord( strDelBranch.GetAt( j ) ) );

// 			for ( int m = 0 ; m < 4 ; m ++ )		//�ж�����Ƿ����cref�˵�����
// 			{
// 				if ( TeeStartPt.GetAt( m )  == BranchPt.GetAt( m ) )
// 				{
// 					strDelBranch.SetAt( wordnum, _T("TEECURRENT") ) ;	//������ڱ�ʾ��ͨ�Ǳ����ı���ͨ�Ĺؼ��֣��Ա��´α�������ʱ�������
// 				}
// 			}
			//�ж�����Ƿ����cref�˵�����
			if ( TeeStartPt.GetAt( 0 ) == BranchPt.GetAt( 0 ) && TeeStartPt.GetAt( 1 ) == BranchPt.GetAt( 1 )
				 && TeeStartPt.GetAt( 2 ) == BranchPt.GetAt( 2 ) && TeeStartPt.GetAt( 3 ) == BranchPt.GetAt( 3 ) )
			{
				strDelBranch.SetAt( wordnum, _T("TEECURRENT") ) ;	//������ڱ�ʾ��ͨ�Ǳ����ı���ͨ�Ĺؼ��֣��Ա��´α�������ʱ�������
			}

			for ( int q = 0; q < strDelBranch.GetSize(); q++ )		//�������飬strDelBranch�Ƕ�̬�ģ�
			{
				if ( strDelBranch.GetAt( q ) == BranchPt.GetAt( 0 ) && strDelBranch.GetAt( q + 1 ) == BranchPt.GetAt( 1 )
					 && strDelBranch.GetAt( q +2 ) == BranchPt.GetAt( 2 ) && strDelBranch.GetAt( q +3 ) == BranchPt.GetAt( 3 ) )
				{		//��ͨ��cref�����ӵ������ķ�֧�Ƿ���ڣ�
					if ( IsKeyWord( strDelBranch.GetAt( q - 1 ) ) && strDelBranch.GetAt( q - 1 ) != _T("PIPE") )	//���ӵķ�֧��ΪPIPE�������Ƿ�֧ͷ��
					{
						int k = q - 1 ;		//��ס��֧ͷ��λ��
						int p = q - 1 ;
						do			//��ͨcref������Ԫ������Ϣ��
						{
							AddBranchPipe.Add( strDelBranch.GetAt( k ) );
							k++ ;
						} while ( !IsKeyWord( strDelBranch.GetAt( k ) ) );

						AcGePoint3d StartCurPt,EndCurPt,BaseCurPt,StartAddPt,EndAddPt;

						double long InitPipeData = 0.0 ;
						bool CurHaveBasePt = FALSE ;
						for (int m=0;m<AddBranchPipe.GetSize();m++)//�õ����ӽڵ��������Ϣ
						{
							int num=0;
							if ( AddBranchPipe.GetAt(m) == _T("END-POINT") && num == 0 )  //���������Ϣ
							{	
								StartCurPt.x = _tcstod( UELPCSTR (AddBranchPipe.GetAt( m+1 ) ), NULL );
								StartCurPt.y = _tcstod( UELPCSTR (AddBranchPipe.GetAt( m+2 ) ), NULL );
								StartCurPt.z = _tcstod( UELPCSTR (AddBranchPipe.GetAt( m+3 ) ), NULL );
								InitPipeData = _tcstod( UELPCSTR (AddBranchPipe.GetAt( m+4 ) ), NULL );
								num++;
								m = m+5;
								
							}
							
							if ( AddBranchPipe.GetAt(m) == _T("END-POINT") && num == 1 )		//�յ�������Ϣ
							{
								
								EndCurPt.x = _tcstod( UELPCSTR (AddBranchPipe.GetAt( m+1 ) ), NULL  );
								EndCurPt.y = _tcstod( UELPCSTR (AddBranchPipe.GetAt( m+2 ) ), NULL  );
								EndCurPt.z = _tcstod( UELPCSTR (AddBranchPipe.GetAt( m+3 ) ), NULL  );
								m = m+5;
							}
							
							if (AddBranchPipe.GetAt(m) == _T("CENTRE-POINT") ) //���ĵ�������Ϣ
							{
								BaseCurPt.x = _tcstod( UELPCSTR (AddBranchPipe.GetAt( m+1 ) ), NULL  );
								BaseCurPt.y = _tcstod( UELPCSTR (AddBranchPipe.GetAt( m+2 ) ), NULL  );
								BaseCurPt.z = _tcstod( UELPCSTR (AddBranchPipe.GetAt( m+3 ) ), NULL  );
								m = m+5;
								CurHaveBasePt = TRUE ;		//�ж��Ƿ������ĵ�
							}
						}
						
						if ( !CurHaveBasePt )	//���ӽڵ�û�����ĵ㣬������ǰ���һ���ܵ�
						{
							StartAddPt = StartCurPt ; //���ӹܵ������Ϊ��ǰ�ڵ�����
							if ( fabs( StartCurPt.x - EndCurPt.x ) < 1 )//�յ�Ϊ��ǰ�ڵ��ȥһ�ι��ӵĵ�
							{
								EndAddPt.x = StartCurPt.x ;
							} 
							else
							{
								if ( StartCurPt.x > EndCurPt.x )
								{
									EndAddPt.x = StartCurPt.x - 1 ;
								} 
								else
								{
									EndAddPt.x = StartCurPt.x + 1 ;
								}
							}
							if ( fabs( StartCurPt.y - EndCurPt.y ) < 1 )
							{
								EndAddPt.y = StartCurPt.y ;
							} 
							else
							{
								if ( StartCurPt.y > EndCurPt.y )
								{
									EndAddPt.y = StartCurPt.y - 1 ;
								} 
								else
								{
									EndAddPt.y = StartCurPt.y + 1 ;
								}
							}
							if ( fabs( StartCurPt.z - EndCurPt.z ) < 1 )
							{
								EndAddPt.z = StartCurPt.z ;
							} 
							else
							{
								if ( StartCurPt.z > EndCurPt.z )
								{
									EndAddPt.z = StartCurPt.z - 1 ;
								} 
								else
								{
									EndAddPt.z = StartCurPt.z + 1 ;
								}
							}
							StartCurPt = EndAddPt ; //��ǰ�ڵ�����Ϊ���ӹܵ����յ�
							CString str ;
							str.Format(_T("%f"),StartCurPt.x ) ;		//�������ñ仯�ĵ�ǰ�ڵ����Ϣ
							strDelBranch.SetAt( ( p + 2 ),str ) ;
							str.Format(_T("%f"),StartCurPt.y ) ;
							strDelBranch.SetAt( ( p + 3 ),str ) ;
							str.Format(_T("%f"),StartCurPt.z ) ;
							strDelBranch.SetAt( ( p + 4 ),str ) ;

							strDelBranch.InsertAt( p,_T("PIPE") ) ;     //����ܵ�����Ϣ
							strDelBranch.InsertAt( ( p + 1 ),_T("END-POINT") ) ;
							str.Format(_T("%f"),StartAddPt.x ) ;
							strDelBranch.InsertAt( ( p + 2 ),str ) ;
							str.Format(_T("%f"),StartAddPt.y ) ;
							strDelBranch.InsertAt( ( p + 3 ),str ) ;
							str.Format(_T("%f"),StartAddPt.z ) ;
							strDelBranch.InsertAt( ( p + 4 ),str ) ;
							str.Format(_T("%f"),InitPipeData ) ;
							strDelBranch.InsertAt( ( p + 5 ),str ) ;
							strDelBranch.InsertAt( ( p + 6 ),_T("END-POINT") ) ;
							str.Format(_T("%f"),EndAddPt.x ) ;
							strDelBranch.InsertAt( ( p + 7 ),str ) ;
							str.Format(_T("%f"),EndAddPt.y ) ;
							strDelBranch.InsertAt( ( p + 8 ),str ) ;
							str.Format(_T("%f"),EndAddPt.z ) ;
							strDelBranch.InsertAt( ( p + 9 ),str ) ;
							str.Format(_T("%f"),InitPipeData ) ;
							strDelBranch.InsertAt( ( p + 10 ),str ) ;
							strDelBranch.InsertAt( ( p + 11 ), _T("ITEM-CODE")) ;
							strDelBranch.InsertAt( ( p + 12 ), _T("PA150")) ;
							strDelBranch.InsertAt( ( p + 13 ), _T("FABRICATION-ITEM")) ;
							strDelBranch.InsertAt( ( p + 14 ), _T("WEIGHT")) ;
							strDelBranch.InsertAt( ( p + 15 ), _T("0.000000")) ;
							strDelBranch.InsertAt( ( p + 16 ), _T("ITEM-DESCRIPTION")) ;
							strDelBranch.InsertAt( ( p + 17 ), _T("unset")) ;
							strDelBranch.InsertAt( ( p + 18 ), _T("INSULATION")) ;
							strDelBranch.InsertAt( ( p + 19 ), _T("OFF")) ;
							strDelBranch.InsertAt( ( p + 20 ), _T("INSULATION-SPEC")) ;
							strDelBranch.InsertAt( ( p + 21 ), _T("unset")) ;
							strDelBranch.InsertAt( ( p + 22 ), _T("TRACING")) ;
							strDelBranch.InsertAt( ( p + 23 ), _T("OFF")) ;
							strDelBranch.InsertAt( ( p + 24 ), _T("TRACING-SPEC")) ;
							strDelBranch.InsertAt( ( p + 25 ), _T("unset")) ;						
						}
						else		//�����ǰ�ڵ������ĵ㣬Ҳ������ǰ�����һ���ܵ�
						{
							StartAddPt = StartCurPt ;  //���Ϊ��ǰ�ڵ�����
							if ( fabs( StartCurPt.x - BaseCurPt.x ) < 1 )	//�յ�Ϊ��ǰ�ڵ��ȥһС�ι��ӣ�
							{
								EndAddPt.x = StartCurPt.x ; 
							} 
							else
							{
								if ( StartCurPt.x > BaseCurPt.x )
								{
									EndAddPt.x = StartCurPt.x - 1 ;
								} 
								else
								{
									EndAddPt.x = StartCurPt.x + 1 ;
								}
							}
							if ( fabs( StartCurPt.y - BaseCurPt.y ) < 1 )
							{
								EndAddPt.y = StartCurPt.y ; 
							} 
							else
							{
								if ( StartCurPt.y > BaseCurPt.y )
								{
									EndAddPt.y = StartCurPt.y - 1 ;
								} 
								else
								{
									EndAddPt.y = StartCurPt.y + 1 ;
								}
							}
							if ( fabs( StartCurPt.z - BaseCurPt.z ) < 1 )
							{
								EndAddPt.z = StartCurPt.z ; 
							} 
							else
							{
								if ( StartCurPt.z > BaseCurPt.z )
								{
									EndAddPt.z = StartCurPt.z - 1 ;
								} 
								else
								{
									EndAddPt.z = StartCurPt.z + 1 ;
								}
							}
							StartCurPt = EndAddPt ;	//��ǰ�ڵ�����Ϊ���ӹܵ����յ㣻
							CString str ;
							str.Format(_T("%f"),StartCurPt.x ) ;	//�������øı�ĵ�ǰ�ڵ����Ϣ��
							strDelBranch.SetAt( ( p + 2 ),str ) ;
							str.Format(_T("%f"),StartCurPt.y ) ;
							strDelBranch.SetAt( ( p + 3 ),str ) ;
							str.Format(_T("%f"),StartCurPt.z ) ;
							strDelBranch.SetAt( ( p + 4 ),str ) ;
							
							strDelBranch.InsertAt( p,_T("PIPE") ) ;		//����ܵ�����Ϣ��
							strDelBranch.InsertAt( ( p + 1 ),_T("END-POINT") ) ;
							str.Format(_T("%f"),StartAddPt.x ) ;
							strDelBranch.InsertAt( ( p + 2 ),str ) ;
							str.Format(_T("%f"),StartAddPt.y ) ;
							strDelBranch.InsertAt( ( p + 3 ),str ) ;
							str.Format(_T("%f"),StartAddPt.z ) ;
							strDelBranch.InsertAt( ( p + 4 ),str ) ;
							str.Format(_T("%f"),InitPipeData ) ;
							strDelBranch.InsertAt( ( p + 5 ),str ) ;
							strDelBranch.InsertAt( ( p + 6 ),_T("END-POINT") ) ;
							str.Format(_T("%f"),EndAddPt.x ) ;
							strDelBranch.InsertAt( ( p + 7 ),str ) ;
							str.Format(_T("%f"),EndAddPt.y ) ;
							strDelBranch.InsertAt( ( p + 8 ),str ) ;
							str.Format(_T("%f"),EndAddPt.z ) ;
							strDelBranch.InsertAt( ( p + 9 ),str ) ;
							str.Format(_T("%f"),InitPipeData ) ;
							strDelBranch.InsertAt( ( p + 10 ),str ) ;
							strDelBranch.InsertAt( ( p + 11 ), _T("ITEM-CODE")) ;
							strDelBranch.InsertAt( ( p + 12 ), _T("PA150")) ;
							strDelBranch.InsertAt( ( p + 13 ), _T("FABRICATION-ITEM")) ;
							strDelBranch.InsertAt( ( p + 14 ), _T("WEIGHT")) ;
							strDelBranch.InsertAt( ( p + 15 ), _T("0.000000")) ;
							strDelBranch.InsertAt( ( p + 16 ), _T("ITEM-DESCRIPTION")) ;
							strDelBranch.InsertAt( ( p + 17 ), _T("unset")) ;
							strDelBranch.InsertAt( ( p + 18 ), _T("INSULATION")) ;
							strDelBranch.InsertAt( ( p + 19 ), _T("OFF")) ;
							strDelBranch.InsertAt( ( p + 20 ), _T("INSULATION-SPEC")) ;
							strDelBranch.InsertAt( ( p + 21 ), _T("unset")) ;
							strDelBranch.InsertAt( ( p + 22 ), _T("TRACING")) ;
							strDelBranch.InsertAt( ( p + 23 ), _T("OFF")) ;
							strDelBranch.InsertAt( ( p + 24 ), _T("TRACING-SPEC")) ;
							strDelBranch.InsertAt( ( p + 25 ), _T("unset")) ;
						}
 						wordnum = 0 ;		//��wordnum����Ϊ0����ѭ������
 						break ;
					}
									//������ӽڵ�Ϊ��֧β�Ĵ���
					if ( IsKeyWord( strDelBranch.GetAt( q - 6 ) ) && strDelBranch.GetAt( q - 6 ) != _T("PIPE") )
					{
						int k = q - 6 ;//��¼�ýڵ��λ�ã�
						int p = q - 6 ;
						do		//�õ��ýڵ����Ϣ��
						{
							AddBranchPipe.Add( strDelBranch.GetAt( k ) );
							k++ ;
						} while ( !IsKeyWord( strDelBranch.GetAt( k ) ) );
						
						AcGePoint3d StartCurPt,EndCurPt,BaseCurPt,StartAddPt,EndAddPt;
						
						double long InitPipeData = 0.0 ;
						bool CurHaveBasePt = FALSE ;
						for (int m=0;m<AddBranchPipe.GetSize();m++)		//�Ե�ǰ�ڵ��������Ϣ������
						{
							int num=0;
							if ( AddBranchPipe.GetAt(m) == _T("END-POINT") && num == 0 )	//�������
							{	
								StartCurPt.x = _tcstod( UELPCSTR (AddBranchPipe.GetAt( m+1 ) ), NULL );
								StartCurPt.y = _tcstod( UELPCSTR (AddBranchPipe.GetAt( m+2 ) ), NULL );
								StartCurPt.z = _tcstod( UELPCSTR (AddBranchPipe.GetAt( m+3 ) ), NULL );								
								num++;
								m = m+5;
								
							}
							
							if ( AddBranchPipe.GetAt(m) == _T("END-POINT") && num == 1 )	//�յ�����
							{
								
								EndCurPt.x = _tcstod( UELPCSTR (AddBranchPipe.GetAt( m+1 ) ), NULL );
								EndCurPt.y = _tcstod( UELPCSTR (AddBranchPipe.GetAt( m+2 ) ), NULL );
								EndCurPt.z = _tcstod( UELPCSTR (AddBranchPipe.GetAt( m+3 ) ), NULL );
								InitPipeData = _tcstod( UELPCSTR (AddBranchPipe.GetAt( m+4 ) ), NULL );
								m = m+5;
							}
							
							if (AddBranchPipe.GetAt(m) == _T("CENTRE-POINT"))		//���ĵ�����
							{
								BaseCurPt.x = _tcstod( UELPCSTR (AddBranchPipe.GetAt( m+1 ) ), NULL );
								BaseCurPt.y = _tcstod( UELPCSTR (AddBranchPipe.GetAt( m+2 ) ), NULL );
								BaseCurPt.z = _tcstod( UELPCSTR (AddBranchPipe.GetAt( m+3 ) ), NULL );
								m = m+5;
								CurHaveBasePt = TRUE ;		//�ж��Ƿ������ĵ�
							}
						}
						if ( !CurHaveBasePt )		//û�����ĵ㣬�ڵ�ǰ�ڵ�ĺ����һ���ܵ�
						{
							EndAddPt = EndCurPt ;	//���ӹܵ����յ�Ϊ��ǰ�ڵ���յ�
							if ( fabs( StartCurPt.x - EndCurPt.x ) < 1 )		//���ӹܵ������Ϊ��ǰ�ڵ������ȥһС����
							{
								StartAddPt.x = StartCurPt.x ;
							} 
							else
							{
								if ( StartCurPt.x > EndCurPt.x )
								{
									StartAddPt.x = EndCurPt.x + 1 ;
								} 
								else
								{
									StartAddPt.x = EndCurPt.x - 1 ;
								}
							}
							if ( fabs( StartCurPt.y - EndCurPt.y ) < 1 )
							{
								StartAddPt.y = StartCurPt.y ;
							} 
							else
							{
								if ( StartCurPt.y > EndCurPt.y )
								{
									StartAddPt.y = EndCurPt.y + 1 ;
								} 
								else
								{
									StartAddPt.y = EndCurPt.y - 1 ;
								}
							}
							if ( fabs( StartCurPt.z - EndCurPt.z ) < 1 )
							{
								StartAddPt.z = StartCurPt.z ;
							} 
							else
							{
								if ( StartCurPt.z > EndCurPt.z )
								{
									StartAddPt.z = EndCurPt.z + 1 ;
								} 
								else
								{
									StartAddPt.z = EndCurPt.z - 1 ;
								}
							}
							EndCurPt = StartAddPt ;		//��ǰ�ڵ���յ�����Ϊ���ӹܶεĿ�ʼ����
							CString str ;
							str.Format(_T("%f"),EndCurPt.x ) ;	//��������һ�¸ı��˵ĵ�ǰ�ڵ�ı��˵�����
							strDelBranch.SetAt( ( p + 7 ),str ) ;
							str.Format(_T("%f"),EndCurPt.y ) ;
							strDelBranch.SetAt( ( p + 8 ),str ) ;
							str.Format(_T("%f"),EndCurPt.z ) ;
							strDelBranch.SetAt( ( p + 9 ),str ) ;
							
							strDelBranch.InsertAt( k,_T("PIPE") ) ;	//�������ӹܵ�����Ϣ
							strDelBranch.InsertAt( ( k + 1 ),_T("END-POINT") ) ;
							str.Format(_T("%f"),StartAddPt.x ) ;
							strDelBranch.InsertAt( ( k + 2 ),str ) ;
							str.Format(_T("%f"),StartAddPt.y ) ;
							strDelBranch.InsertAt( ( k + 3 ),str ) ;
							str.Format(_T("%f"),StartAddPt.z ) ;
							strDelBranch.InsertAt( ( k + 4 ),str ) ;
							str.Format(_T("%f"),InitPipeData ) ;
							strDelBranch.InsertAt( ( k + 5 ),str ) ;
							strDelBranch.InsertAt( ( k + 6 ),_T("END-POINT") ) ;
							str.Format(_T("%f"),EndAddPt.x ) ;
							strDelBranch.InsertAt( ( k + 7 ),str ) ;
							str.Format(_T("%f"),EndAddPt.y ) ;
							strDelBranch.InsertAt( ( k + 8 ),str ) ;
							str.Format(_T("%f"),EndAddPt.z ) ;
							strDelBranch.InsertAt( ( k + 9 ),str ) ;
							str.Format(_T("%f"),InitPipeData ) ;
							strDelBranch.InsertAt( ( k + 10 ),str ) ;
							strDelBranch.InsertAt( ( k + 11 ), _T("ITEM-CODE")) ;
							strDelBranch.InsertAt( ( k + 12 ), _T("PA150")) ;
							strDelBranch.InsertAt( ( k + 13 ), _T("FABRICATION-ITEM")) ;
							strDelBranch.InsertAt( ( k + 14 ), _T("WEIGHT")) ;
							strDelBranch.InsertAt( ( k + 15 ), _T("0.000000")) ;
							strDelBranch.InsertAt( ( k + 16 ), _T("ITEM-DESCRIPTION")) ;
							strDelBranch.InsertAt( ( k + 17 ), _T("unset")) ;
							strDelBranch.InsertAt( ( k + 18 ), _T("INSULATION")) ;
							strDelBranch.InsertAt( ( k + 19 ), _T("OFF")) ;
							strDelBranch.InsertAt( ( k + 20 ), _T("INSULATION-SPEC")) ;
							strDelBranch.InsertAt( ( k + 21 ), _T("unset")) ;
							strDelBranch.InsertAt( ( k + 22 ), _T("TRACING")) ;
							strDelBranch.InsertAt( ( k + 23 ), _T("OFF")) ;
							strDelBranch.InsertAt( ( k + 24 ), _T("TRACING-SPEC")) ;
							strDelBranch.InsertAt( ( k + 25 ), _T("unset")) ;	

						} 
						else		//��������ĵ㣬Ҳ�ڵ�ǰ�ڵ�ĺ����һ���ܵ���
						{
							EndAddPt = EndCurPt ;	//���ӹܵ����յ�����Ϊ��ǰ�ڵ���յ�����
							if ( fabs( EndCurPt.x - BaseCurPt.x ) < 1 )		//���ӹܵ����������Ϊ��ǰ�ڵ���յ������ȥһС�Σ�
							{
								StartAddPt.x = EndCurPt.x ; 
							} 
							else
							{
								if ( EndCurPt.x > BaseCurPt.x )
								{
									StartAddPt.x = EndCurPt.x - 1 ;
								} 
								else
								{
									StartAddPt.x = EndCurPt.x + 1 ;
								}
							}
							if ( fabs( EndCurPt.y - BaseCurPt.y ) < 1 )
							{
								StartAddPt.y = EndCurPt.y ; 
							} 
							else
							{
								if ( EndCurPt.y > BaseCurPt.y )
								{
									StartAddPt.y = EndCurPt.y - 1 ;
								} 
								else
								{
									StartAddPt.y = EndCurPt.y + 1 ;
								}
							}
							if ( fabs( EndCurPt.z - BaseCurPt.z ) < 1 )
							{
								StartAddPt.z = EndCurPt.z ; 
							} 
							else
							{
								if ( EndCurPt.z > BaseCurPt.z )
								{
									StartAddPt.z = EndCurPt.z - 1 ;
								} 
								else
								{
									StartAddPt.z = EndCurPt.z + 1 ;
								}
							}
							EndCurPt = StartAddPt ;		//��ǰ�ڵ���յ�����Ϊ���ӹܵ����������
							CString str ;
							str.Format(_T("%f"),EndCurPt.x ) ;		//�������õ�ǰ�ڵ�ı��˵��յ�����ꣻ
							strDelBranch.SetAt( ( p + 7 ),str ) ;
							str.Format(_T("%f"),EndCurPt.y ) ;
							strDelBranch.SetAt( ( p + 8 ),str ) ;
							str.Format(_T("%f"),EndCurPt.z ) ;
							strDelBranch.SetAt( ( p + 9 ),str ) ;
							
							strDelBranch.InsertAt( k,_T("PIPE") ) ;		//�������ӹܵ�����Ϣ
							strDelBranch.InsertAt( ( k + 1 ),_T("END-POINT") ) ;
							str.Format(_T("%f"),StartAddPt.x ) ;
							strDelBranch.InsertAt( ( k + 2 ),str ) ;
							str.Format(_T("%f"),StartAddPt.y ) ;
							strDelBranch.InsertAt( ( k + 3 ),str ) ;
							str.Format(_T("%f"),StartAddPt.z ) ;
							strDelBranch.InsertAt( ( k + 4 ),str ) ;
							str.Format(_T("%f"),InitPipeData ) ;
							strDelBranch.InsertAt( ( k + 5 ),str ) ;
							strDelBranch.InsertAt( ( k + 6 ),_T("END-POINT") ) ;
							str.Format(_T("%f"),EndAddPt.x ) ;
							strDelBranch.InsertAt( ( k + 7 ),str ) ;
							str.Format(_T("%f"),EndAddPt.y ) ;
							strDelBranch.InsertAt( ( k + 8 ),str ) ;
							str.Format(_T("%f"),EndAddPt.z ) ;
							strDelBranch.InsertAt( ( k + 9 ),str ) ;
							str.Format(_T("%f"),InitPipeData ) ;
							strDelBranch.InsertAt( ( k + 10 ),str ) ;
							strDelBranch.InsertAt( ( k + 11 ), _T("ITEM-CODE")) ;
							strDelBranch.InsertAt( ( k + 12 ), _T("PA150")) ;
							strDelBranch.InsertAt( ( k + 13 ), _T("FABRICATION-ITEM")) ;
							strDelBranch.InsertAt( ( k + 14 ), _T("WEIGHT")) ;
							strDelBranch.InsertAt( ( k + 15 ), _T("0.000000")) ;
							strDelBranch.InsertAt( ( k + 16 ), _T("ITEM-DESCRIPTION")) ;
							strDelBranch.InsertAt( ( k + 17 ), _T("unset")) ;
							strDelBranch.InsertAt( ( k + 18 ), _T("INSULATION")) ;
							strDelBranch.InsertAt( ( k + 19 ), _T("OFF")) ;
							strDelBranch.InsertAt( ( k + 20 ), _T("INSULATION-SPEC")) ;
							strDelBranch.InsertAt( ( k + 21 ), _T("unset")) ;
							strDelBranch.InsertAt( ( k + 22 ), _T("TRACING")) ;
							strDelBranch.InsertAt( ( k + 23 ), _T("OFF")) ;
							strDelBranch.InsertAt( ( k + 24 ), _T("TRACING-SPEC")) ;
							strDelBranch.InsertAt( ( k + 25 ), _T("unset")) ;	

						}

						wordnum = 0 ;		//��wordnum����Ϊ0���˳�ѭ�����±�����
						break ;
					}


				}
				
			}
		}
	}
	for (int m = 0 ; m < strDelBranch.GetSize(); m ++ )		//����е�ǰ�ڵ���ѵ�ǰ�ڵ�Ĺؼ������¸�ΪTEE
	{
		if ( strDelBranch.GetAt( m ) == _T("TEECURRENT") )
		{
			strDelBranch.SetAt( m, _T("TEE") ) ;
		}
	} 
}
/*
void PCFComponentMgr::InitJunKey_BranchtoPipe( CStringArray &strBranch )
{
	unsigned long wordnum ;
	CStringArray branch ;
	CStringArray ElementBranch ;

	for ( wordnum = 0; wordnum < strBranch.GetSize(); wordnum++ )
	{
		if ( IsKeyWord( strBranch.GetAt( wordnum ) ) && ElementBranch.GetSize() != 0 )
		{
			CreatComponet( ElementBranch ) ;
			ElementBranch.RemoveAll() ;
		}
		ElementBranch.Add( strBranch.GetAt( wordnum ) ) ;
	}
}
*/
// void PCFComponentMgr::InitJunKey_SearchAndAdd( CStringArray &strSearchadd )
// {
// 	CStringArray TeeBranch ;
// 	unsigned long wordnum ;
// 	for ( wordnum = 0; wordnum < strSearchadd.GetSize() wordnum ++ )
// 	{
// 		
// 	}
// }

void PCFComponentMgr::InitJunKey_AddPipe(const CStringArray &strSet)
{
	CStringArray PerElement;
	CStringArray CurElement;
	CStringArray AddPerElement;
	CStringArray AddCurElement;
	CStringArray PipeAftElement;

	CStringArray ElementBuff;
	
	unsigned long wordnum = 0;
	unsigned long wordsize ;
	wordsize = strSet.GetSize();
	BOOL PerFlag=FALSE;
	BOOL PipeFlag=FALSE;
	for ( wordnum = 0; wordnum < wordsize; wordnum++ )
	{
		ElementBuff1.Add( strSet.GetAt( wordnum ) ) ;
	}

	for( wordnum = 0; wordnum < ElementBuff1.GetSize(); wordnum++)
	{
	
		if( IsKeyWord(ElementBuff1.GetAt(wordnum) ) && ElementBuff1.GetAt( wordnum ) != _T("PUMP") && ElementBuff1.GetAt( wordnum ) != _T("VESS")
			&& ( ElementBuff.GetSize() != 0 ) )					//��Ϊ��������PUMP��VESS���ǹؼ��֣�������Ҫ�ų����Ժ�Ҫ��ʲô�豸ҲҪ�ų��������ཨ�����豸�ģ�
		{	
			
			if (PerFlag) //���ǰһ�����ǽڵ����ǰһ������Ԫ����
 			{
				CreatComponet(ElementBuff);
				PerFlag=FALSE;
 			}


			BOOL flag=FALSE;
			double MinPipeLength=0.01;
			double MinLength=0.001;
			if ( ElementBuff1.GetAt(wordnum)==_T("PIPE") || ElementBuff1.GetAt(wordnum)==_T("END-CONNECTION-EQUIPMENT") || ElementBuff1.GetAt(wordnum)==_T("END-CONNECTION-NULL")
				 || ElementBuff1.GetAt(wordnum)==_T("ASSIGNFLOW") )
			{
				flag=TRUE;//��ǰ���ǲ��ǽڵ㣬����(TRUE)����(FALSE)
			}

			if (!flag&&ElementBuff1.GetAt(wordnum)!=_T("Over"))//����ǽڵ㲢��û�е�.pcf�ļ��Ľ�����־�򱣴�ΪҪ�����ܶ�����Ҫ����Ϣ�����潫�ж��Ƿ񴴽��ܶΣ�
			{


				for (int i=0;i<ElementBuff.GetSize();i++)
				{
					PerElement.Add(ElementBuff.GetAt(i));
				}
				
				int j=wordnum;
				
				do 
				{
					CurElement.Add(ElementBuff1.GetAt(j));
					j++;
				} while (!IsKeyWord(ElementBuff1.GetAt(j)));
				
			
				AcGePoint3d StartPerPt;
				AcGePoint3d EndPerPt;
				AcGePoint3d StartCurPt;
				AcGePoint3d EndCurPt;
		
				AcGePoint3d StartPerPipePt;
				AcGePoint3d EndPerPipept;

				AcGePoint3d BasePerPt;
				AcGePoint3d BaseCurPt;

				BOOL PerHaveBasePt=FALSE;
				BOOL CurHaveBasePt=FALSE;

				double InPipeData=0.0;//�õ���ǰ�ڵ���ھ�
				for (int m=0;m<PerElement.GetSize();m++)//�õ�ǰһ���ڵ��������Ϣ
				{
					int num=0;
 					if ( PerElement.GetAt(m) == _T("END-POINT") && num == 0 )
					{	
						StartPerPt.x = _tcstod( UELPCSTR (PerElement.GetAt( m+1 ) ), NULL );
						StartPerPt.y = _tcstod( UELPCSTR (PerElement.GetAt( m+2 ) ), NULL );
						StartPerPt.z = _tcstod( UELPCSTR (PerElement.GetAt( m+3 ) ), NULL );
					
						num++;
						m = m+5;
				 				
					}
				 				
					if ( PerElement.GetAt(m) == _T("END-POINT") && num == 1 )
					{

						EndPerPt.x = _tcstod( UELPCSTR (PerElement.GetAt( m+1 ) ), NULL );
					 	EndPerPt.y = _tcstod( UELPCSTR (PerElement.GetAt( m+2 ) ), NULL );
						EndPerPt.z = _tcstod( UELPCSTR (PerElement.GetAt( m+3 ) ), NULL );
						m = m+5;
					}

					if (PerElement.GetAt(m) == _T("CENTRE-POINT") )
					{
						BasePerPt.x = _tcstod( UELPCSTR (PerElement.GetAt( m+1 ) ), NULL );
						BasePerPt.y = _tcstod( UELPCSTR (PerElement.GetAt( m+2 ) ), NULL );
						BasePerPt.z = _tcstod( UELPCSTR (PerElement.GetAt( m+3 ) ), NULL );
						m = m+5;
						PerHaveBasePt=TRUE;
					}
				}

				
				for (int mTemp =0; mTemp<CurElement.GetSize(); mTemp++)  //�õ���ǰ�ڵ��������Ϣ
				{
					int num=0;
					if ( CurElement.GetAt(mTemp) == _T("END-POINT") && num == 0 )
					{	
						StartCurPt.x = _tcstod( (UELPCSTR)(CurElement.GetAt( mTemp+1 ) ), NULL );
						StartCurPt.y = _tcstod( (UELPCSTR)(CurElement.GetAt( mTemp+2 ) ), NULL );
						StartCurPt.z = _tcstod( (UELPCSTR)(CurElement.GetAt( mTemp+3 ) ), NULL );
						InPipeData = _tcstod( (UELPCSTR)(CurElement.GetAt( mTemp+4 ) ), NULL );
						num++;
						mTemp = mTemp+5;
						
					}
				
					if ( CurElement.GetAt(mTemp) == _T("END-POINT") && num == 1 )
					{			
						EndCurPt.x = _tcstod( (UELPCSTR)(CurElement.GetAt( mTemp+1 ) ), NULL );
						EndCurPt.y = _tcstod( (UELPCSTR)(CurElement.GetAt( mTemp+2 ) ), NULL );
						EndCurPt.z = _tcstod( (UELPCSTR)(CurElement.GetAt( mTemp+3 ) ), NULL );
						mTemp = mTemp+5; 
					}

					if (CurElement.GetAt(mTemp) == _T("CENTRE-POINT"))
					{
						BaseCurPt.x = _tcstod( (UELPCSTR)(CurElement.GetAt( mTemp+1 ) ), NULL );
						BaseCurPt.y = _tcstod( (UELPCSTR)(CurElement.GetAt( mTemp+2 ) ), NULL );
						BaseCurPt.z = _tcstod( (UELPCSTR)(CurElement.GetAt( mTemp+3 ) ), NULL );
						CurHaveBasePt=TRUE;
					}
				}

				
					//(1,��û���㣻2,��ǰ��û��ǰһ���У�3�����л��㣻4����ǰ���У�ǰһ��û)
					if(!PerHaveBasePt&&CurHaveBasePt)//4�������ǰ�Ľڵ��л��㣬ǰһ���ڵ�û�л��㣬�ͼ�һ���ܶΣ�
					{
						StartPerPipePt=StartCurPt;   //�ܶε����Ϊ��ǰ�ڵ����㣬
						if (abs(StartPerPt.x-EndPerPt.x)<MinLength)    //�յ�Ϊǰһ���ڵ���յ�(��ʵ�͵�ǰ�ڵ�����������ͬ��������õ�ǰ�ڵ��������ӹܶε�����ͻ��෴����֪Ϊʲô)��ȥ���ӵĹܶΡ�
						{
							EndPerPipept.x=EndPerPt.x;
						}
						else
						{
							if (EndPerPt.x>0)
							{
								EndPerPipept.x=EndPerPt.x+MinPipeLength;
							} 
							else
							{
								EndPerPipept.x=EndPerPt.x-MinPipeLength;
							}
							
						}
						
						if (abs(StartPerPt.y-EndPerPt.y)<MinLength)
						{
							EndPerPipept.y=EndPerPt.y;
						}
						else
						{
							
							if (EndPerPt.y>0)
							{
								EndPerPipept.y=EndPerPt.y+MinPipeLength;
							} 
							else
							{
								EndPerPipept.y=EndPerPt.y-MinPipeLength;
							}
							
						}
						
						if (abs(StartPerPt.z-EndPerPt.z)<MinLength)
						{
							EndPerPipept.z=EndPerPt.z;
						} 
						else
						{
							if (EndPerPt.z>0)
							{
								EndPerPipept.z=EndPerPt.z-MinPipeLength;
							} 
							else
							{
								EndPerPipept.z=EndPerPt.z-MinPipeLength;
							}
							
						}
						StartCurPt=EndPerPipept;     //��ǰ�Ľڵ���������Ϊ���ӹܶε��յ����ꡣ
					}
					else         //1��2��3�����ҲҪ�ӹܶΡ�
					{
						if (PerHaveBasePt&&!CurHaveBasePt)  //2�����ǰһ���ڵ��л��㣬��ǰ�ڵ�û�л��㡣(��һ����Ҫ�Ǳ�֤������ͷ��ȡ�ܶΣ�ʹ���򲻻��෴)
						{
							StartPerPipePt=StartCurPt;      //���ӹܶε����Ϊ��ǰ�ڵ�����
							if (abs(StartPerPt.x-EndPerPt.x)<MinLength)  //�յ�Ϊǰһ���ڵ���յ�(��ʵ�͵�ǰ�ڵ�����������ͬ��������õ�ǰ�ڵ��������ӹܶε�����ͻ��෴����֪Ϊʲô)��ȥ���ӵĹܶΡ�
							{
								EndPerPipept.x=EndPerPt.x;
							}
							else
							{
								if (EndPerPt.x>0)
								{
									EndPerPipept.x=EndPerPt.x+MinPipeLength;
								} 
								else
								{
									EndPerPipept.x=EndPerPt.x-MinPipeLength;
								}
								
							}
							
							if (abs(StartPerPt.y-EndPerPt.y)<MinLength)
							{
								EndPerPipept.y=EndPerPt.y;
							}
							else
							{
								
								if (EndPerPt.y>0)
								{
									EndPerPipept.y=EndPerPt.y+MinPipeLength;
								} 
								else
								{
									EndPerPipept.y=EndPerPt.y-MinPipeLength;
								}
								
							}
							
							if (abs(StartPerPt.z-EndPerPt.z)<MinLength)
							{
								EndPerPipept.z=EndPerPt.z;
							} 
							else
							{
								if (EndPerPt.z>0)
								{
									EndPerPipept.z=EndPerPt.z-MinPipeLength;
								} 
								else
								{
									EndPerPipept.z=EndPerPt.z-MinPipeLength;
								}
								
							}
						StartCurPt=EndPerPipept;   //��ǰ�Ľڵ���������Ϊ���ӹܶε��յ����ꡣ
						}
						else           //1����û���㣻3�����л���
						{
							if (!PerHaveBasePt&&!CurHaveBasePt)  //1����û���㣻
							{
								StartPerPipePt=StartCurPt;      //���ӹܶε����Ϊ��ǰ�ڵ�����
								if (abs(StartCurPt.x-EndPerPt.x)<MinLength)  //�յ�Ϊǰһ���ڵ���յ��ȥ���ӵĹܶΡ�
								{
									EndPerPipept.x=StartCurPt.x;
								}
								else
								{
									if (StartCurPt.x>0)
									{
										EndPerPipept.x=StartCurPt.x+MinPipeLength;
									} 
									else
									{
										EndPerPipept.x=StartCurPt.x-MinPipeLength;
									}
									
								}
								
								if (abs(StartCurPt.y-EndPerPt.y)<MinLength)
								{
									EndPerPipept.y=StartCurPt.y;
								}
								else
								{
									
									if (StartCurPt.y>0)
									{
										EndPerPipept.y=StartCurPt.y+MinPipeLength;
									} 
									else
									{
										EndPerPipept.y=StartCurPt.y-MinPipeLength;
									}
									
								}
								
								if (abs(StartCurPt.z-EndPerPt.z)<MinLength)
								{
									EndPerPipept.z=StartCurPt.z;
								} 
								else
								{
									if (StartCurPt.z>0)
									{
										EndPerPipept.z=StartCurPt.z-MinPipeLength;
									} 
									else
									{
										EndPerPipept.z=StartCurPt.z-MinPipeLength;
									}
									
								}
								StartCurPt=EndPerPipept;   //��ǰ�Ľڵ���������Ϊ���ӹܶε��յ����ꡣ								
							} 
							else   //3�����л���							
							{
								EndPerPipept=StartCurPt;  //�ܶε��յ�Ϊ��ǰ�ڵ�����
								if (abs(BasePerPt.x-StartCurPt.x)<MinLength)  //�յ�Ϊ��ǰ�ڵ������ȥ���ӵĹܶ�
								{
									StartPerPipePt.x=StartCurPt.x;
								}
								else
								{
									if (StartCurPt.x>0)
									{
										StartPerPipePt.x=EndPerPt.x+MinPipeLength;
									} 
									else
									{
										StartPerPipePt.x=EndPerPt.x-MinPipeLength;
									}
									
								}
								
								if (abs(BasePerPt.y-StartCurPt.y)<MinLength)
								{
									StartPerPipePt.y=EndPerPt.y;
								}
								else
								{
									if (StartCurPt.y>0)
									{
										StartPerPipePt.y=EndPerPt.y+MinPipeLength;
									} 
									else
									{
										StartPerPipePt.y=EndPerPt.y-MinPipeLength;
									}
									
								}
								
								if (abs(BasePerPt.z-StartCurPt.z)<MinLength)
								{
									StartPerPipePt.z=EndPerPt.z;
								} 
								else
								{
									if (StartCurPt.z>0)
									{
										StartPerPipePt.z=EndPerPt.z+MinPipeLength;
									} 
									else
									{
										StartPerPipePt.z=EndPerPt.z-MinPipeLength;
									}
									
								}
								EndPerPt=StartPerPipePt;  //��ǰ�ڵ������Ϊ���ӹܵ����յ㡣
							}
						}

					}
				
 				

				CString str;         //���ӹܵ�����Ϣ
				AddPerElement.Add(_T("PIPE"));
				AddPerElement.Add(_T("END-POINT"));
				str.Format(_T("%f"),StartPerPipePt.x);
				AddPerElement.Add(str);
				str.Format(_T("%f"),StartPerPipePt.y);
				AddPerElement.Add(str);
				str.Format(_T("%f"),StartPerPipePt.z);
				AddPerElement.Add(str);
				str.Format(_T("%f"),InPipeData);
				AddPerElement.Add(str);
				AddPerElement.Add(_T("END-POINT"));
				str.Format(_T("%f"),EndPerPipept.x);
				AddPerElement.Add(str);
				str.Format(_T("%f"),EndPerPipept.y);
				AddPerElement.Add(str);
				str.Format(_T("%f"),EndPerPipept.z);
				AddPerElement.Add(str);
				str.Format(_T("%f"),InPipeData);
				AddPerElement.Add(str);
				AddPerElement.Add(_T("ITEM-CODE"));
				AddPerElement.Add(_T("PA150"));
				AddPerElement.Add(_T("FABRICATION-ITEM"));
				AddPerElement.Add(_T("WEIGHT"));
				AddPerElement.Add(_T("0.000000"));
				AddPerElement.Add(_T("ITEM-DESCRIPTION"));
				AddPerElement.Add(_T("unset"));
				AddPerElement.Add(_T("INSULATION"));
				AddPerElement.Add(_T("OFF"));
				AddPerElement.Add(_T("INSULATION-SPEC"));
				AddPerElement.Add(_T("unset"));
				AddPerElement.Add(_T("TRACING"));
				AddPerElement.Add(_T("OFF"));
				AddPerElement.Add(_T("TRACING-SPEC"));
				AddPerElement.Add(_T("unset"));


				AddCurElement.Add(CurElement.GetAt(0));//��ȥ���ӹܵ��󣬵�ǰ�ڵ����Ϣ
				AddCurElement.Add(_T("END-POINT"));
				str.Format(_T("%f"),StartCurPt.x);
				AddCurElement.Add(str);
				str.Format(_T("%f"),StartCurPt.y);
				AddCurElement.Add(str);
				str.Format(_T("%f"),StartCurPt.z);
				AddCurElement.Add(str);
				for ( int mIndex =5;mIndex<CurElement.GetSize();mIndex++)
				{
					AddCurElement.Add(CurElement.GetAt(mIndex));				
				}
				
				if (PipeFlag)  //����ڵ�ǰһ��Ԫ���ǹܵ���ֻ������ǰ��Ԫ���ڵ㣬
				{
					CreatComponet(CurElement);
					PipeFlag=FALSE;
				} 
				else      //���ǰһ�����ǹܵ������������ڵ���ֱ���������򴴽��ܵ��͵�ǰԪ���ڵ㡣
				{
					CreatComponet(AddPerElement);
					CreatComponet(AddCurElement);
				}
 			}
			ElementBuff.RemoveAll();//���������ʱ������
			PerElement.RemoveAll();
			CurElement.RemoveAll();
			AddCurElement.RemoveAll();
			AddPerElement.RemoveAll();

		}
		ElementBuff.Add(ElementBuff1.GetAt( wordnum ));

		if (ElementBuff1.GetAt(wordnum)==_T("PIPE")||ElementBuff1.GetAt(wordnum)==_T("END-CONNECTION-EQUIPMENT")||ElementBuff1.GetAt(wordnum)==_T("END-CONNECTION-NULL") || ElementBuff1.GetAt(wordnum)==_T("ASSIGNFLOW") )
		{
			PerFlag=TRUE;  //�ж�ǰһ���ǲ��ǽڵ㣬����(TRUE),��(FALSE)
		}
		if (ElementBuff1.GetAt(wordnum)==_T("PIPE")) //�ж�ǰһ���ǲ��ǹܵ�
		{
			PipeFlag=TRUE;
		}
	}

}

void PCFComponentMgr::CreatComponet(CStringArray &strSet)
{
	CString strKey = strSet.GetAt(0) ;
	strKey.MakeUpper() ;
	if (strKey.CompareNoCase(_T("NOZZLE"))==0)
		return;
	if(strKey.CompareNoCase(_T("PIPE"))==0)
	{
		PCFPipe *pPipe = m_PipesMgr.Creator();
		if(pPipe != NULL)
			pPipe->Init(strSet);
	}
	else
	{
		PCFJun *pJun = m_JunsMgr.Creator(strKey);
		if(pJun != NULL)
			pJun->Init(strSet);
	}
}
PCFJunsMgr& PCFComponentMgr::GetJunMgr()
{
	return m_JunsMgr;
}
PCFPipesMgr& PCFComponentMgr::GetPipeMgr()
{
	return m_PipesMgr;
}
//����ά����ͶӰ����ά����
void PCFComponentMgr::Tran3dTo2d()
{
	m_PipesMgr.Tran3dTo2d();
	m_JunsMgr.Tran3dTo2d();
}

void PCFComponentMgr::MoveGraph()
{
	double dMinX=0;
	double dMinY=0;
	GetMinXY(dMinX,dMinY);
	AcGePoint3d OriginPt(dMinX,dMinY,0);
	OffSet(OriginPt);

}
//�õ���С��x��y������ֵ��
void PCFComponentMgr::GetMinXY(double &dMinX, double &dMinY)
{
	m_PipesMgr.GetMinXY(dMinX,dMinY);
}

//�ƶ������ϵʹ����2ά�������0
void PCFComponentMgr::OffSet(AcGePoint3d& OriginPt)
{
	m_PipesMgr.OffSet(OriginPt);
	m_JunsMgr.OffSet(OriginPt);
}

//���ݽڵ������ҵ����ӹܵ������ڵ�ĳ��ȼӵ��ܵ��ϡ�
void PCFComponentMgr::TripJunLen()
{
	m_JunsMgr.TripLen(m_PipesMgr);
}

//�޳�ĳЩ�ڵ㲢�ϲ������ܶ�
void PCFComponentMgr::CombinationPipe()
{
	m_JunsMgr.CombinationPipe(m_PipesMgr);
}
//�����ܵ��ͽڵ�����ӹ�ϵ
void PCFComponentMgr::InitNetLink()
{
	m_JunsMgr.InitNetLink(m_PipesMgr);
}
//
void PCFComponentMgr::CombinationFit()
{
	m_JunsMgr.CombinationFit(m_PipesMgr);
}

void PCFComponentMgr::ChangeOrigin()
{
	double dMaxX=0;
	double dMaxY=0;
	m_PipesMgr.GetMaxXY(dMaxX,dMaxY);
	AcGePoint3d OriginPt(dMaxX+100,dMaxY+100,0);
	m_PipesMgr.ChangeOrigin(OriginPt);
	m_JunsMgr.ChangeOrigin(OriginPt);
}

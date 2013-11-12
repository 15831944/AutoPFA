// FCFComponentMgr.h: interface for the FCFComponentMgr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FCFCOMPONENTMGR_H__0325095A_8AA1_4836_83E6_CDB0FE64F4A7__INCLUDED_)
#define AFX_FCFCOMPONENTMGR_H__0325095A_8AA1_4836_83E6_CDB0FE64F4A7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "PipeLineHead.h"
#include "PCFJunsMgr.h"
#include "PCFPipesMgr.h"

class AFX_EXT_CLASS PCFComponentMgr  
{
public:
	
	PCFJunsMgr& GetJunMgr();
	PCFPipesMgr& GetPipeMgr();
	void Init(const CStringArray &strSet);
	PCFComponentMgr();
	virtual ~PCFComponentMgr();
	CStringArray ElementBuff1 ;

private:
	BOOL IsKeyWord( const CString& strKeyWord  );
	PipeLineHead m_pipeHead;
	PCFPipesMgr m_PipesMgr;
	PCFJunsMgr  m_JunsMgr;


private:
	void ChangeOrigin();
	void CombinationFit();
	void InitNetLink();
	void CombinationPipe();
	void Tran3dTo2d();
	void TripJunLen();
	void OffSet(AcGePoint3d& OriginPt);//�ƶ�����ԭ�㵽��СX,Y����
	void MoveGraph();// �ƶ�ͼ�������ʹ�������0
	void GetMinXY(double &dMinX,double &dMinY);//�õ���СX,Y����ֵ
	void CreatComponet(CStringArray &strSet);		//����PCF��Ԫ����ͨ������PCF�ļ��е���Ϣ��������
	void InitComponet(CStringArray &strSet);  //��ElementBuff1�еĹؼ���END-CONNECTION-EQUIPMENT��ΪSKEY֮����Ǹ��ؼ��ֵ��ַ������飻�������ʾΪPFA����ʶ������ͣ�
	static const CString m_strKeyWordArray[] ;		//PFA�п���ʶ��Ĺؼ��֣�����������䣻

	void InitNOZZLE_Ptconcet(CStringArray &strSet);                 //�����豸���֧����
	void InitEquipment_PT(CStringArray &strSet);                    //�����豸���ĵ����֧��಻̫Զ
	void InitJunKey_KeepPtConcet( CStringArray &strConectPt ) ;		//���ָ����ڵ���������໥���ӵġ�
	void InitJunKey_DelTeeBranch( CStringArray &strDelBranch ) ;	//������ͨ���ӵķ�֧���ǹٵ��������
	void InitJunKey_NoPCFJuntoPipe( const CStringArray &strSet );//����ڵ�ؼ��֣��Ѳ��ǽڵ��Ԫ������Ϊ�ܵ���
	void InitJunKey_MergePipe( const CStringArray &strMerge );//����ڵ�ؼ��֣��ϲ������Ĺؼ��ֶ���PIPE�Ľڵ㡣
	void InitJunKey_AddPipe( const CStringArray &strAdd );	//���ں��ӵ�Ԫ����������Ԫ����ͨ��PIPE�������м��һ�ιܼ���������Ԫ����
	void InitJunKey_AddAssignFlowStartBranch( CStringArray &strAssignFlow ) ;	//��֧ͷ���û��Ԫ���������ָ������
	void InitJunKey_DelDiscription( CStringArray &strDelDiscription ) ;  //���������ؼ��ֺ�����ַ��п�����Ԫ���ؼ��֣�����Ҫ���������������ݣ�
	void InitJunKey_AddAssignFlowEndBranch( CStringArray &strAssignFlow ) ;	//��֧β���û��Ԫ������Ҳ����ָ��������
	void InitJunKey_AddPipeAndAssignFlow( CStringArray &strPipeAndAssignFlow ) ;  //�ڷǷ�������Ԫ���ķ�֧β����PIPE��
	void InitElement(CStringArray &strSet);               //���豸
	void InitAddAssignFlow(PCFJunsMgr& pJunMgr,PCFPipesMgr& pPipeMgr);  //�Ƿ������Ĺܵ�����ָ������
	void Init_AddPipe(PCFJunsMgr& pJunMgr,PCFPipesMgr& pPipeMgr);   //�Ƿ������Ľڵ����ܵ�
	int CamparePt(PCFJun& InJun,PCFPipe& InPipe);           //�ȽϽڵ���ܵ�����
	void CampareJJPt(PCFJun& InJun,PCFJun& OutJun);          //�ȽϽڵ���ڵ�����
	void CombinationPipes(PCFPipesMgr& pPipeMgr);           //�ϲ������Ĺܵ�
	void Init_JunPt(PCFJunsMgr& pJunMgr,PCFPipesMgr& pPipeMgr);         //��ʼ���ڵ�����ڵ�ID  
	void Init_AddPipetoJun(PCFJunsMgr& pJunMgr);                       //�ڵ�������ʱ�����ܵ�
//	void Del_AddJun(PCFJunsMgr& pJunMgr,PCFPipesMgr& pPipeMgr);
	
	CStringArray JuntoPipe ;   //�Խڵ�ؼ��ִ���֮�����еĹؼ��ֶ���PCF�Ľڵ�ؼ��֣��䱣�����ַ�������JuntoPipe�У�
	CStringArray MergePipe ;	//��JuntoPipe�еĹؼ�����PIPE�Ľڵ�ϲ��󣬵õ�����Ϣ������MergePipe�У�
	//��ElementBuff1�ж�����Ԫ��֮�䲻��PIPE�Ĺؼ��ִ���

};

#endif // !defined(AFX_FCFCOMPONENTMGR_H__0325095A_8AA1_4836_83E6_CDB0FE64F4A7__INCLUDED_)

//---------------------------------------------------------------------------
//
// "�ؘa��" for ����ȊO�̉����ȊO�̉���
// KawariInlineScript��{�N���X
//
//      Programed by NAKAUE.T (Meister)
//
//  2001.05.14  Phase 0.50    �C�����C���X�N���v�g����
//  2001.05.24  Phase 5.1     �C���^�[�v���^�E�R���p�C����
//
//---------------------------------------------------------------------------
#ifndef KIS_BASE_H
#define KIS_BASE_H
//---------------------------------------------------------------------------
#include "config.h"
//---------------------------------------------------------------------------
#include <string>
#include <vector>
using namespace std;
//---------------------------------------------------------------------------
// �C�����C���X�N���v�g�֐��̊�{�N���X
// (Th!rd�̃A�C�f�A�����t�@�C��)
class TKisFunction_base {
protected:

	// �֐����
	char *Name_;
	char *Format_;
	char *Returnval_;
	char *Information_;

	// �C�����C���X�N���v�g�G���W��
	class TKisEngine *KisEngine;

public:

	TKisFunction_base(void)
	{
		Name_="none.";
		Format_="none.";
		Returnval_="none.";
		Information_="none.";
	}

	// �֐����擾
	const char* Name(void) const {return(Name_);}
	const char* Format(void) const {return(Format_);}
	const char* Returnval(void) const {return(Returnval_);}
	const char* Information(void) const {return(Information_);}

	// �C�����C���X�N���v�g�G���W���ݒ�
	void NotifyEngine(class TKisEngine *engine)
	{
		KisEngine=engine;
	}

	// ������
	virtual bool Init(void)=0;

	// �C���^�[�v���^
	virtual string Function(const vector<string>& args)=0;
};
//---------------------------------------------------------------------------
#if 0
class KIS_SampleFunction : public TKisFunction_base {
public:

	// Init�Ŗ��O���̑��̏���ݒ肵�Ă�������
	virtual bool Init(void)
	{
		Name_="SampleFunction";
		Format_="SampleFunction [Arg1 ...]";
		Returnval_="string which join all argument";
		Information_="KawariInlineScript sample";

		return(true);
	}

	// �C���^�[�v���^
	virtual string Function(const vector<string>& args)
	{
		string ret;
		for(unsigned int i=0;i<args;i++) ret=ret+args[i]+" ";
		return(ret);
	}
};
// ����œo�^
INLINE_SCRIPT_REGIST(KIS_SampleFunction);
#endif
//---------------------------------------------------------------------------
#endif


//---------------------------------------------------------------------------
//
// "�ؘa��" for ����ȊO�̉����ȊO�̉���
// KawariInlineScript -- �J�E���^ --
//
//      Programed by NAKAUE.T (Meister)
//
//  2001.05.30  Phase 5.1     First version
//
//---------------------------------------------------------------------------
// �֐��e�[�u���ւ̓o�^
#ifdef INLINE_SCRIPT_REGIST
INLINE_SCRIPT_REGIST(KIS_inc);
INLINE_SCRIPT_REGIST(KIS_dec);
#else
//---------------------------------------------------------------------------
#ifndef KIS_COUNTER_H
#define KIS_COUNTER_H
//---------------------------------------------------------------------------
#include "config.h"
//---------------------------------------------------------------------------
#include "kis/kis_base.h"
//---------------------------------------------------------------------------
class KIS_inc : public TKisFunction_base {
public:

	// Init�Ŗ��O���̑��̏���ݒ肵�Ă�������
	virtual bool Init(void)
	{
		Name_="inc";
		Format_="inc Entry1 increment upperbound";
		Returnval_="(NULL)";
		Information_="increase a value of Entry1 in an increment";

		return(true);
	}

	// �C���^�[�v���^
	virtual string Function(const vector<string>& args);
};
//---------------------------------------------------------------------------
class KIS_dec : public TKisFunction_base {
public:

	// Init�Ŗ��O���̑��̏���ݒ肵�Ă�������
	virtual bool Init(void)
	{
		Name_="dec";
		Format_="dec Entry1 decrement lowerbound";
		Returnval_="(NULL)";
		Information_="decrease a value of Entry1 in a decrement";

		return(true);
	}

	// �C���^�[�v���^
	virtual string Function(const vector<string>& args);
};
//---------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------
#endif


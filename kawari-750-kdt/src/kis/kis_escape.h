//---------------------------------------------------------------------------
//
// "�ؘa��" for ����ȊO�̉����ȊO�̉���
// KawariInlineScript -- �G�X�P�[�v --
//
//      Programed by NAKAUE.T (Meister)
//
//  2001.07.14  Phase 6.1     First version
//
//---------------------------------------------------------------------------
// �֐��e�[�u���ւ̓o�^
#ifdef INLINE_SCRIPT_REGIST
INLINE_SCRIPT_REGIST(KIS_escape);
#else
//---------------------------------------------------------------------------
#ifndef KIS_ESCAPE_H
#define KIS_ESCAPE_H
//---------------------------------------------------------------------------
#include "config.h"
//---------------------------------------------------------------------------
#include "kis/kis_base.h"
//---------------------------------------------------------------------------
class KIS_escape : public TKisFunction_base {
public:

	// Init�Ŗ��O���̑��̏���ݒ肵�Ă�������
	virtual bool Init(void)
	{
		Name_="escape";
		Format_="escape Word1 ...";
		Returnval_="Word1 ...";
		Information_="replace \\ into \\\\ in all arguments";

		return(true);
	}

	// �C���^�[�v���^
	virtual string Function(const vector<string>& args);
};
//---------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------
#endif


//---------------------------------------------------------------------------
//
// "�ؘa��" for ����ȊO�̉����ȊO�̉���
// KawariInlineScript -- �ێ�Ipiro --
//
//      Programed by NAKAUE.T (Meister)
//
//  2001.03.19  Phase 0.5     Piroject-X
//  2001.05.31  Phase 5.2     KIS�C���^�[�t�F�[�X
//  2001.08.25  Phase 6.3     pirocall�d�l�ǉ�
//
//---------------------------------------------------------------------------
// �֐��e�[�u���ւ̓o�^
#ifdef INLINE_SCRIPT_REGIST
INLINE_SCRIPT_REGIST(KIS_pirocall);
#else
//---------------------------------------------------------------------------
#ifndef KIS_CPIRO_H
#define KIS_CPIRO_H
//---------------------------------------------------------------------------
#include "config.h"
//---------------------------------------------------------------------------
#include "kis/kis_base.h"
//---------------------------------------------------------------------------
class KIS_pirocall : public TKisFunction_base {
public:

	// Init�Ŗ��O���̑��̏���ݒ肵�Ă�������
	virtual bool Init(void)
	{
		Name_="pirocall";
		Format_="pirocall piro-type-entry [Word1]";
		Returnval_="string or word of \"script.txt\"";
		Information_="call a piro type entry from the innner piro enigne";

		return(true);
	}

	// �C���^�[�v���^
	virtual string Function(const vector<string>& args);
};
//---------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------
#endif


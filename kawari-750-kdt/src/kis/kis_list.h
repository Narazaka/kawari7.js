//---------------------------------------------------------------------------
//
// "�ؘa��" for ����ȊO�̉����ȊO�̉���
// KawariInlineScript -- ���X�g --
//
//      Programed by Kouji.U (Suikyo)
//
//  2001.05.16  Phase 0.01
//
//---------------------------------------------------------------------------
// �֐��e�[�u���ւ̓o�^
#ifdef INLINE_SCRIPT_REGIST
INLINE_SCRIPT_REGIST(KIS_shift);
INLINE_SCRIPT_REGIST(KIS_unshift);
INLINE_SCRIPT_REGIST(KIS_push);
INLINE_SCRIPT_REGIST(KIS_pop);
#else
//---------------------------------------------------------------------------
#ifndef KIS_LIST_H
#define KIS_LIST_H
//---------------------------------------------------------------------------
#include "kis/kis_base.h"
//---------------------------------------------------------------------------
class KIS_shift : public TKisFunction_base {
public:

	// Init�Ŗ��O���̑��̏���ݒ肵�Ă�������
	virtual bool Init(void)
	{
		Name_="shift";
		Format_="shift �G���g��1";
		Returnval_="�P��";
		Information_="�G���g��1�̐擪�P��𔲂����A���̒l��Ԃ�";

		return(true);
	}

	// �C���^�[�v���^
  virtual string Function(const vector<string>& args);
};
//---------------------------------------------------------------------------
class KIS_unshift : public TKisFunction_base {
public:

	// Init�Ŗ��O���̑��̏���ݒ肵�Ă�������
	virtual bool Init(void)
	{
		Name_="unshift";
		Format_="unshift �G���g��1 �P��1";
		Returnval_="�Ȃ�";
		Information_="�G���g��1�̐擪�ɒP��1��������";

		return(true);
	}

	// �C���^�[�v���^
  virtual string Function(const vector<string>& args);
};
//---------------------------------------------------------------------------
class KIS_push : public TKisFunction_base {
public:

	// Init�Ŗ��O���̑��̏���ݒ肵�Ă�������
	virtual bool Init(void)
	{
		Name_="push";
		Format_="push �G���g��1 �P��1";
		Returnval_="�Ȃ�";
		Information_="�G���g��1�̍Ō�ɒP��1��������(adddict�Ɠ���)";

		return(true);
	}

	// �C���^�[�v���^
	virtual string Function(const vector<string>& args)
	{
		if(args.size()>=3) KawariDictionary->Insert(args[1],args[2]);
		return("");
	}
};
//---------------------------------------------------------------------------
class KIS_pop : public TKisFunction_base {
public:

	// Init�Ŗ��O���̑��̏���ݒ肵�Ă�������
	virtual bool Init(void)
	{
		Name_="pop";
		Format_="pop �G���g��1";
		Returnval_="�P��";
		Information_="�G���g��1�̖����P��𔲂����A���̒l��Ԃ�";

		return(true);
	}

	// �C���^�[�v���^
  virtual string Function(const vector<string>& args);
};
//---------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------
#endif


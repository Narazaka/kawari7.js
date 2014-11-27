//---------------------------------------------------------------------------
//
// "�ؘa��" for ����ȊO�̉����ȊO�̉���
// KawariInlineScript -- �������� --
//
//      Programed by NAKAUE.T (Meister)
//
//  2001.05.14  Phase 0.50    First version
//  2001.05.30  Phase 5.1     
//  2001.07.08  Phase 6.0     eval�o�O�t�B�b�N�X
//  2001.07.14  Phase 6.1     clear�ǉ�
//  2001.08.08  Phase 6.2     entry�ǉ�
//  2001.08.25  Phase 6.3     entry�d�l�ǉ�
//                            get��������ǉ�
//                            size�ǉ�
//  2001.12.18  Phase 7.2     array����ɂ�������ǉ�
//
//---------------------------------------------------------------------------
// �֐��e�[�u���ւ̓o�^
#ifdef INLINE_SCRIPT_REGIST
INLINE_SCRIPT_REGIST(KIS_set);
INLINE_SCRIPT_REGIST(KIS_adddict);
INLINE_SCRIPT_REGIST(KIS_clear);
INLINE_SCRIPT_REGIST(KIS_enumerate);
INLINE_SCRIPT_REGIST(KIS_eval);
INLINE_SCRIPT_REGIST(KIS_entry);
INLINE_SCRIPT_REGIST(KIS_get);
INLINE_SCRIPT_REGIST(KIS_size);
INLINE_SCRIPT_REGIST(KIS_array);
#else
//---------------------------------------------------------------------------
#ifndef KIS_DICT_H
#define KIS_DICT_H
//---------------------------------------------------------------------------
#include "config.h"
//---------------------------------------------------------------------------
#include "kis/kis_base.h"
//---------------------------------------------------------------------------
class KIS_set : public TKisFunction_base {
public:

	// Init�Ŗ��O���̑��̏���ݒ肵�Ă�������
	virtual bool Init(void)
	{
		Name_="set";
		Format_="set Entry1 Word1";
		Returnval_="(NULL)";
		Information_="set Word1 to Entry1";

		return(true);
	}

	// �C���^�[�v���^
	virtual string Function(const vector<string>& args);
};
//---------------------------------------------------------------------------
class KIS_adddict : public TKisFunction_base {
public:

	// Init�Ŗ��O���̑��̏���ݒ肵�Ă�������
	virtual bool Init(void)
	{
		Name_="adddict";
		Format_="adddict Entry1 Word1";
		Returnval_="(NULL)";
		Information_="append Word1 to Entry1";

		return(true);
	}

	// �C���^�[�v���^
	virtual string Function(const vector<string>& args);
};
//---------------------------------------------------------------------------
class KIS_clear : public TKisFunction_base {
public:

	// Init�Ŗ��O���̑��̏���ݒ肵�Ă�������
	virtual bool Init(void)
	{
		Name_="clear";
		Format_="clear Entry1";
		Returnval_="(NULL)";
		Information_="clear all content of Entry1";

		return(true);
	}

	// �C���^�[�v���^
	virtual string Function(const vector<string>& args);
};
//---------------------------------------------------------------------------
class KIS_enumerate : public TKisFunction_base {
public:

	// Init�Ŗ��O���̑��̏���ݒ肵�Ă�������
	virtual bool Init(void)
	{
		Name_="enumerate";
		Format_="enumerate Entry1";
		Returnval_="all words in Entry1";
		Information_="enumerate all words in Entry1";

		return(true);
	}

	// �C���^�[�v���^
	virtual string Function(const vector<string>& args);
};
//---------------------------------------------------------------------------
class KIS_eval : public TKisFunction_base {
public:

	// Init�Ŗ��O���̑��̏���ݒ肵�Ă�������
	virtual bool Init(void)
	{
		Name_="eval";
		Format_="eval Word1 ...";
		Returnval_="decode result";
		Information_="parse all arguments and return its decode result";

		return(true);
	}

	// �C���^�[�v���^
	virtual string Function(const vector<string>& args);
};
//---------------------------------------------------------------------------
class KIS_entry : public TKisFunction_base {
public:

	// Init�Ŗ��O���̑��̏���ݒ肵�Ă�������
	virtual bool Init(void)
	{
		Name_="entry";
		Format_="entry Entry1 [Word1]";
		Returnval_="${Entry1} or Word1";
		Information_="equivalent to \"${Entry1}\"";

		return(true);
	}

	// �C���^�[�v���^
	virtual string Function(const vector<string>& args);
};
//---------------------------------------------------------------------------
class KIS_get : public TKisFunction_base {
public:

	// Init�Ŗ��O���̑��̏���ݒ肵�Ă�������
	virtual bool Init(void)
	{
		Name_="get";
		Format_="get Entry1 index(zero origin)";
		Returnval_="inner expression of Entry1";
		Information_="Now testing...";

		return(true);
	}

	// �C���^�[�v���^
	virtual string Function(const vector<string>& args);
};
//---------------------------------------------------------------------------
class KIS_size : public TKisFunction_base {
public:

	// Init�Ŗ��O���̑��̏���ݒ肵�Ă�������
	virtual bool Init(void)
	{
		Name_="size";
		Format_="size Entry1";
		Returnval_="a word number in Entry1";
		Information_="return a word number in Entry1";

		return(true);
	}

	// �C���^�[�v���^
	virtual string Function(const vector<string>& args);
};
//---------------------------------------------------------------------------
class KIS_array : public TKisFunction_base {
public:

	// Init�Ŗ��O���̑��̏���ݒ肵�Ă�������
	virtual bool Init(void)
	{
		Name_="array";
		Format_="array Entry1 index(zero origin)";
		Returnval_="the [index+1]th word in Entry1";
		Information_="Now testing...";

		return(true);
	}

	// �C���^�[�v���^
	virtual string Function(const vector<string>& args);
};
//---------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------
#endif


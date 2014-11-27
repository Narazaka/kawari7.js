//---------------------------------------------------------------------------
//
// "�ؘa��" for ����ȊO�̉����ȊO�̉���
// KawariInlineScript -- file attribute --
//
//      Programed by NAKAUE.T (Meister)
//
//  2001.05.14   Phase 0.50    First version
//  2001.06.17   Phase6.0�ɂ��킹�ďC�� (NAKAUE.T)
//               load
//  2001.12.09  Phase 7.1.2   kis_textfile�Ɠ���
//
//---------------------------------------------------------------------------
// �֐��e�[�u���ւ̓o�^
#ifdef INLINE_SCRIPT_REGIST
INLINE_SCRIPT_REGIST(KIS_save);
INLINE_SCRIPT_REGIST(KIS_savecrypt);
INLINE_SCRIPT_REGIST(KIS_load);
// INLINE_SCRIPT_REGIST(KIS_load);
INLINE_SCRIPT_REGIST(KIS_textload);
INLINE_SCRIPT_REGIST(KIS_readdir);
#else
//---------------------------------------------------------------------------
#ifndef KIS_FILE_H
#define KIS_FILE_H
//---------------------------------------------------------------------------
#include "kis/kis_base.h"
//---------------------------------------------------------------------------
class KIS_save : public TKisFunction_base {
public:

	// Init�Ŗ��O���̑��̏���ݒ肵�Ă�������
	virtual bool Init(void)
	{
		Name_="save";
		Format_="save File1 Entry1 [Entry2...]";
		Returnval_="(NULL)";
		Information_="save entries to File1";

		return(true);
	}

	// �C���^�[�v���^
    virtual string Function(const vector<string>& args){
        Run(args, false);
        return "";
    }
protected:
    virtual void Run(const vector<string>& args, bool crypt);
};
//---------------------------------------------------------------------------
class KIS_savecrypt : public KIS_save {
public:

	// Init�Ŗ��O���̑��̏���ݒ肵�Ă�������
	virtual bool Init(void)
	{
		Name_="savecrypt";
		Format_="savecrypt File1 Entry1 [Entry2...]";
		Returnval_="(NULL)";
		Information_="save entries to File1 by encrypt expression";

		return(true);
	}

	// �C���^�[�v���^
	virtual string Function(const vector<string>& args)
	{
		Run(args, true);
		return "";
	}
};
//---------------------------------------------------------------------------
class KIS_load : public TKisFunction_base {
public:

	// Init�Ŗ��O���̑��̏���ݒ肵�Ă�������
	virtual bool Init(void)
	{
		Name_="load";
		Format_="load File1";
		Returnval_="(NULL)";
		Information_="load dictionary file";

		return(true);
	}

	// �C���^�[�v���^
	virtual string Function(const vector<string>& args);

};
//---------------------------------------------------------------------------
class KIS_textload : public TKisFunction_base {
public:

	// Init�Ŗ��O���̑��̏���ݒ肵�Ă�������
	virtual bool Init(void)
	{
		Name_="textload";
		Format_="textload File1 Entry1";
		Returnval_="(NULL)";
		Information_="load textfile to Entry1";

		return(true);
	}

	// �C���^�[�v���^
	virtual string Function(const vector<string>& args);
};
//---------------------------------------------------------------------------
class KIS_readdir : public TKisFunction_base {
public:

	// Init�Ŗ��O���̑��̏���ݒ肵�Ă�������
	virtual bool Init(void)
	{
		Name_="readdir";
		Format_="readdir Dir1 Entry1";
		Returnval_="(NULL)";
		Information_="read directory entries and set to Entry1";

		return(true);
	}

	// �C���^�[�v���^
	virtual string Function(const vector<string>& args);
};
//---------------------------------------------------------------------------
#endif	// KIS_FILE_H
//---------------------------------------------------------------------------
#endif	// INLINE_SCRIPT_REGIST


//---------------------------------------------------------------------------
//
// "�ؘa��" for ����ȊO�̉����ȊO�̉���
// KawariInlineScript -- �I�����C���w���v --
//
//      Programed by NAKAUE.T (Meister)
//
//  2001.07.21  Phase 6.2     First version
//  2001.08.06  Phase 6.2     ver�ǉ�
//  2001.08.08  Phase 6.2     help�Ɋ֐��ꗗ�ǉ�
//
//---------------------------------------------------------------------------
// �֐��e�[�u���ւ̓o�^
#ifdef INLINE_SCRIPT_REGIST
INLINE_SCRIPT_REGIST(KIS_help);
INLINE_SCRIPT_REGIST(KIS_ver);
#else
//---------------------------------------------------------------------------
#ifndef KIS_HELP_H
#define KIS_HELP_H
//---------------------------------------------------------------------------
#include "config.h"
//---------------------------------------------------------------------------
#include "kis/kis_base.h"
//---------------------------------------------------------------------------
class KIS_help : public TKisFunction_base {
public:

	// Init�Ŗ��O���̑��̏���ݒ肵�Ă�������
	virtual bool Init(void)
	{
		Name_="help";
		Format_="help Command1";
		Returnval_="help message";
		Information_="print online help of KIS command (for Kosui use)";

		return(true);
	}

	// �C���^�[�v���^
	virtual string Function(const vector<string>& args);
};
//---------------------------------------------------------------------------
class KIS_ver : public TKisFunction_base {
public:

	// Init�Ŗ��O���̑��̏���ݒ肵�Ă�������
	virtual bool Init(void)
	{
		Name_="ver";
		Format_="ver [ license ]";
		Returnval_="version info, or license info";
		Information_="return KAWARI version info formatted by \"basename.subname/verNo.\", or print license information to logfile";

		return(true);
	}

	// �C���^�[�v���^
	virtual string Function(const vector<string>& args);
};
//---------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------
#endif


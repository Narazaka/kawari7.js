//---------------------------------------------------------------------------
//
// "�ؘa��" for ����ȊO�̉����ȊO�̉���
// KawariInlineScript -- ���w --
//
//      Programed by Kouji.U (SUIKYO)
//
//  2001.06.17  Phase 5.4     
//
//---------------------------------------------------------------------------
// �֐��e�[�u���ւ̓o�^
#ifdef INLINE_SCRIPT_REGIST
INLINE_SCRIPT_REGIST(KIS_rand);
#else
//---------------------------------------------------------------------------
#ifndef KIS_MATH_H
#define KIS_MATH_H
//---------------------------------------------------------------------------
#include "config.h"
//---------------------------------------------------------------------------
#include <string>
#include <cstdlib>
using namespace std;
//---------------------------------------------------------------------------
#include "misc/misc.h"
#include "kis/kis_base.h"
//---------------------------------------------------------------------------
class KIS_rand : public TKisFunction_base {
public:
    // Init�Ŗ��O���̑��̏���ݒ肵�Ă�������
	virtual bool Init(void)
	{
		Name_="rand";
		Format_="rand MAX";
		Returnval_="(NULL)";
		Information_="return a random number (0 to MAX-1)";

		return(true);
	}

	// �C���^�[�v���^
    virtual string Function(const vector<string>& args){
        if (args.size()>=2) 
            return (IntToString(Random(atoi(args[1].c_str()))));
        else
            return ("");
    }

};



//---------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------
#endif

//---------------------------------------------------------------------------
//
// "�ؘa��" for ����ȊO�̉����ȊO�̉���
// KawariInlineScript -- expr --
//
//      Programed by Kouji.U (sky)
//
//  2001.06.02  Phase 0.50��2   First version
//  2001.06.09  BCC5.5.1�ŃR���p�C���ł���悤�ɏC�� (NAKAUE.T)
//  2001.07.21  Phase 6.2    config.h�������Ă��� (NAKAUE.T)
//  2002.01.07  Phase 7.3     findpos�T�u�R�}���h�ǉ� (���Ɓ[)
//                            split�R�}���h�ǉ�(���Ɓ[)
//
//---------------------------------------------------------------------------
// �֐��e�[�u���ւ̓o�^
#ifdef INLINE_SCRIPT_REGIST
INLINE_SCRIPT_REGIST(KIS_expr);
INLINE_SCRIPT_REGIST(KIS_split);
#else
//---------------------------------------------------------------------------
#ifndef KIS_EXPR_H__
#define KIS_EXPR_H__
//---------------------------------------------------------------------------
#include "config.h"
//---------------------------------------------------------------------------
#include "kis/kis_base.h"
#include <string>
#include <vector>
#ifdef EXPR_LOG
#	include <fstream>
#endif

using namespace std;

class KIS_expr : public TKisFunction_base {
public:

    // Init�Ŗ��O���̑��̏���ݒ肵�Ă�������
    virtual bool Init(void){
        Name_="expr";
        Format_="expr EXPRESSION";
        Returnval_="evalation result";
        Information_="return the value of expression";
        return(true);
    }

private:
    unsigned int Index;
    vector<string> Args;
    inline bool testNext(const string& ref){
        return ((Index<Args.size()) && (Args[Index]==ref));
    }
    string EvalRegex(const std::string& l, const std::string& r);
    string Eval7();
    string Eval6();
//    string Eval5();
    string Eval4();
    string Eval3();
    string Eval2();
    string Eval1();
    string Eval();

#ifdef EXPR_LOG
    ofstream* LogFS;
#endif
public:
    virtual string Function(const vector<string>& args);
};

/*
  eval = eval1 '|' eval1
  eval1 = eval2 '&' eval2
  eval2 = eval3 comparison eval3
  comparison = <, <=, =, ==, !=, >=, >
  eval3 = eval4 num-operator eval4
  num-operator = +, -
  eval4 = eval5 *,/,% eval5
  eval5 = eval6 : eval6
  eval6 = quote, length, match, index, substr / eval7
  eval7 = bare-operand / ( eval )
  */

//---------------------------------------------------------------------------
class KIS_split : public TKisFunction_base {
public:

	// Init�Ŗ��O���̑��̏���ݒ肵�Ă�������
	virtual bool Init(void){
		Name_="split";
		Format_="split Entry1 string delimiter";
		Returnval_="(NULL)";
		Information_="split a string by delimiter";

		return(true);
	}

	// �C���^�[�v���^
	virtual string Function(const vector<string>& args);
};

class tokenizer {
private:

	string str;					// �؂�o��������
	string cs;					// ��؂蕶����
	string::size_type pos;		// ��͊J�n�ʒu
	string::size_type size;		// �؂�o��������̒���

public:

	// �g�[�N���؂�o�����ʂ�Ԃ��\����
	struct Parse {
		enum TParseState {
			parseOK,	// �g�[�N���؂�o������
			parseEND	// �g�[�N���͂���ȏ�Ȃ�
		} ParseState;
		
		string str;		// �؂�o�����g�[�N��
	};

	// �������͐؂�o��������A��؂蕶����̏���
	tokenizer(const string s, const string c);
	
	// �g�[�N����؂�o��
	Parse token(void);
};
//---------------------------------------------------------------------------
#endif // KIS_EXPR_H__
//---------------------------------------------------------------------------
#endif


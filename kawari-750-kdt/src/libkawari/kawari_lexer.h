//---------------------------------------------------------------------------
//
// "�ؘa��" for ����ȊO�̉����ȊO�̉���
// ������
//
//      Programed by NAKAUE.T (Meister)
//
//  2001.04.24  Phase 0.5     �����͋@����
//  2001.05.20  Phase 5.1     �C���^�[�v���^�E�R���p�C����
//
//---------------------------------------------------------------------------
#ifndef KAWARI_LEXER_H
#define KAWARI_LEXER_H
//---------------------------------------------------------------------------
#include "config.h"
//---------------------------------------------------------------------------
#include <string>
#include <vector>
using namespace std;
//---------------------------------------------------------------------------
// �����͊֌W
//---------------------------------------------------------------------------
extern const string StartMacro;
extern const string StartSeparator;
extern const string StartWhiteSpace;
extern const string StartQuote;
extern const string StartAll;
//---------------------------------------------------------------------------
// �����͋@
class TKawariLexer : public string {
public:

	// �g�[�N��
	struct TToken {
		// �g�[�N���̎��
		enum TTokenType {
			ttokError,			// �G���[
			ttokSentence,		// ������
			ttokMacroEntry,		// ${
			ttokMacroInline,	// $(
			ttokSeparator,		// ��؂蕶�� :;,](!&|)
			ttokSpace,			// �󔒕����� " \t"
			ttokDummy
		} Type;

		// �g�[�N���̕�����
		string Str;
	};


	// ���ɉ�͂��镶���̈ʒu
	unsigned int Pos;

	// ���[�U�̃��������p
	unsigned int Pos2;


	TKawariLexer(void) : Pos(0) , Pos2(0) , string() {}

	TKawariLexer(const string& str) : Pos(0) , Pos2(0) , string(str) {}

	TKawariLexer(const char *str) : Pos(0) , Pos2(0) , string(str) {}

	string operator=(const TKawariLexer& r)
	{
		return(*((string*)&r));
	}

	TKawariLexer& operator=(const string& r)
	{
		*((string*)this)=r;
		Pos=0;
		Pos2=0;
		return(*this);
	}

	bool IsEnd(void)
	{
		return(Pos>=size());
	}


	// ���ߊ֐� Accept�n (Pos�����������Ȃ�)

	// �󔒕������T��
	// ���߂ł����Ō�̕����̎��̈ʒu���A��
	unsigned int AcceptSpace(void) const;

	// '�܂���"�ň͂܂ꂽ�������T��
	// ���߂ł����Ō�̕����̎��̈ʒu���A��
	unsigned int AcceptQuotedString(char quote='"') const;

	// �G���g������T��
	// ���߂ł����Ō�̕����̎��̈ʒu���A��
	unsigned int AcceptEntryName(void) const;


	// ���ߊ֐� Get�n (Pos������������)

	// �G���g�����w��q�����؂�o��
	// Pos�͉��߂����������i�߂���
	void GetEntryList(vector<string>& entrytable,char separator='&');

	// �g�[�N������؂�o��
	// Pos�͉��߂����������i�߂���
	TToken GetToken(void);

	// �P�ꕶ�������؂�o��
	// Pos�͉��߂����������i�߂���
	string GetWordString(const char *separator_=NULL);


	// �T�[�r�X�֐�

	// '�܂���"�ň͂܂ꂽ�����񂩂�N�H�[�g�������͂���
	static string DecodeQuotedString(const string& orgsen);

};
//---------------------------------------------------------------------------
#endif

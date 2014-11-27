//---------------------------------------------------------------------------
//
// "�ؘa��" for ����ȊO�̉����ȊO�̉���
// ������
//
//      Programed by NAKAUE.T (Meister)
//
//  2001.04.24  Phase 0.5     �����͋@����
//  2001.05.20  Phase 5.1     �C���^�[�v���^�E�R���p�C����
//	2002.01.11  Phase 7.3.1   I18N Hack (kpcg.I18Nhack)
//  2003.02.16  Phase 7.5.0
//
//---------------------------------------------------------------------------
#include "config.h"
//---------------------------------------------------------------------------
#include "libkawari/kawari_lexer.h"
//---------------------------------------------------------------------------
#include <cctype>
using namespace std;
//---------------------------------------------------------------------------
#include "misc/misc.h"
#include "misc/i18n.h"
//---------------------------------------------------------------------------
// ��؂蕶���̒�`
#define CONST_START_MACRO		"$"			// �}�N���̊J�n����
#define CONST_START_SEPARATOR	":;,](!&|)"		// ���̑��P�Ƃ̋�؂蕶��
#define CONST_START_WHITESPACE	" \t"		// ��
#define CONST_START_QUOTE		"\""		// �N�H�[�g������
//---------------------------------------------------------------------------
const string StartMacro(CONST_START_MACRO);
const string StartSeparator(CONST_START_SEPARATOR);
const string StartWhiteSpace(CONST_START_WHITESPACE);
const string StartQuote(CONST_START_QUOTE);
const string StartAll(
 CONST_START_MACRO
 CONST_START_SEPARATOR
 CONST_START_WHITESPACE
 CONST_START_QUOTE);
//---------------------------------------------------------------------------
// �󔒕������T��
// ���߂ł����Ō�̕����̎��̈ʒu���A��
#if defined(STRING_APPEND_INATOMIC)
unsigned int TKawariLexer::AcceptSpace(void) const
{
	const string &orgsen=(*this);
	unsigned int cntsen = orgsen.size();
	unsigned int endpos=Pos;

	while(endpos<cntsen) {
		if((orgsen[endpos]!=' ')&&(orgsen[endpos]!='\t')) break;
		endpos++;
	}

	return(endpos);
}
#else
unsigned int TKawariLexer::AcceptSpace(void) const
{
	const string &orgsen=(*this);

	unsigned int endpos=Pos;

	while(endpos<orgsen.size()) {
		if((orgsen[endpos]!=' ')&&(orgsen[endpos]!='\t')) break;
		endpos++;
	}

	return(endpos);
}
#endif
//---------------------------------------------------------------------------
// '�܂���"�ň͂܂ꂽ�������T��
// ���߂ł����Ō�̕����̎��̈ʒu���A��

#if defined(STRING_APPEND_INATOMIC)
unsigned int TKawariLexer::AcceptQuotedString(char quote) const
{
	const string &orgsen=(*this);
	unsigned int cntsen = orgsen.size();

	if((Pos>=cntsen)||(orgsen[Pos]!=quote)) return(Pos);

	unsigned int endpos=Pos+1;

	while(endpos<cntsen) {
		if(orgsen[endpos]==quote) {
			endpos++;
			break;
		}

		if(orgsen[endpos]=='\\') {
			if((endpos+1)<cntsen) endpos++;
		}

#ifdef I18N_HACK
		if(int trail = lang.moreBytes(orgsen[endpos])) {
			// jump over one character in MBCS environment
			if((endpos+trail)<cntsen) endpos+=trail;
		}
#else
		if(iskanji1st(orgsen[endpos])) {
			// ����
			if((endpos+1)<cntsen) endpos++;
		}
#endif
		endpos++;
	}

	return(endpos);
}
#else
unsigned int TKawariLexer::AcceptQuotedString(char quote) const
{
	const string &orgsen=(*this);

	if((Pos>=orgsen.size())||(orgsen[Pos]!=quote)) return(Pos);

	unsigned int endpos=Pos+1;

	while(endpos<orgsen.size()) {
		if(orgsen[endpos]==quote) {
			endpos++;
			break;
		}

		if(orgsen[endpos]=='\\') {
			if((endpos+1)<orgsen.size()) endpos++;
		}

#ifdef I18N_HACK
		if(int trail = lang.moreBytes(orgsen[endpos])) {
			// jump over one character in MBCS environment
			if((endpos+trail)<orgsen.size()) endpos+=trail;
		}
#else
		if(iskanji1st(orgsen[endpos])) {
			// ����
			if((endpos+1)<orgsen.size()) endpos++;
		}
#endif
		endpos++;
	}

	return(endpos);
}
#endif
//---------------------------------------------------------------------------
// �G���g������T��
// ���߂ł����Ō�̕����̎��̈ʒu���A��
#if defined(STRING_APPEND_INATOMIC)
unsigned int TKawariLexer::AcceptEntryName(void) const
{
	const string &orgsen=(*this);
	unsigned int cntsen = orgsen.size();

	unsigned int endpos=Pos;

	while(endpos<cntsen) {
#ifdef I18N_HACK
		if(int trail=lang.moreBytes(orgsen[endpos])) {
			if((endpos+trail)<cntsen) {
				endpos += (trail+1);
			} else {
				break;
			}
#else
		if(iskanji1st(orgsen[endpos])) {
			// ����
			if((endpos+1)<cntsen) {
				endpos += 2;
			} else {
				break;
			}
#endif
		} else if(
		 isalnum(orgsen[endpos])
		 ||(orgsen[endpos]=='_')
		 ||(orgsen[endpos]=='.')
		 ||((orgsen[endpos]=='-')&&(endpos-Pos>0)) ) {
			// �p����,'_'��'-'
			// '-'�͓񕶎��ڈȍ~�ł����g���Ȃ�
			endpos++;
		} else if(orgsen[endpos]=='@') {
			// ���[�J���ϐ�������킷'@'
			// �����I�ɂ́A�񕶎��ڈȍ~�Ŏg�p���邱�Ƃ�����
			endpos++;
		} else {
			break;
		}
	}

	return(endpos);
}
#else
unsigned int TKawariLexer::AcceptEntryName(void) const
{
	const string &orgsen=(*this);

	unsigned int endpos=Pos;

	while(endpos<orgsen.size()) {
#ifdef I18N_HACK
		if(int trail=lang.moreBytes(orgsen[endpos])) {
			if((endpos+trail)<orgsen.size()) {
				endpos += (trail+1);
			} else {
				break;
			}
#else
		if(iskanji1st(orgsen[endpos])) {
			// ����
			if((endpos+1)<orgsen.size()) {
				endpos++;
				endpos++;
			} else {
				break;
			}
#endif
		} else if(
		 isalnum(orgsen[endpos])
		 ||(orgsen[endpos]=='_')
		 ||(orgsen[endpos]=='.')
		 ||((orgsen[endpos]=='-')&&(endpos-Pos>0)) ) {
			// �p����,'_'��'-'
			// '-'�͓񕶎��ڈȍ~�ł����g���Ȃ�
			endpos++;
		} else if(orgsen[endpos]=='@') {
			// ���[�J���ϐ�������킷'@'
			// �����I�ɂ́A�񕶎��ڈȍ~�Ŏg�p���邱�Ƃ�����
			endpos++;
		} else {
			break;
		}
	}

	return(endpos);
}
#endif

//---------------------------------------------------------------------------
// ������̎w��ʒupos����G���g�����w��q�����؂�o��
// pos�͉��߂����������i�߂���

#if defined(STRING_APPEND_INATOMIC)
void TKawariLexer::GetEntryList(vector<string>& entrytable,char separator)
{
	const string &orgsen=(*this);
	unsigned int cntsen = orgsen.size();

	while(Pos<cntsen) {
		Pos=AcceptSpace();
		unsigned int startpos=Pos;
		Pos=AcceptEntryName();
		if(startpos!=Pos) {
			entrytable.push_back(orgsen.substr(startpos,Pos-startpos));
		} else if(orgsen[Pos]==separator) {
			// �}���`�G���g���̋�؂蕶��
			Pos++;
		} else {
			break;
		}
	}

	Pos=AcceptSpace();	// �T�[�r�X

	return;
}
#else
void TKawariLexer::GetEntryList(vector<string>& entrytable,char separator)
{
	const string &orgsen=(*this);

	while(Pos<orgsen.size()) {
		Pos=AcceptSpace();
		unsigned int startpos=Pos;
		Pos=AcceptEntryName();
		if(startpos!=Pos) {
			entrytable.push_back(orgsen.substr(startpos,Pos-startpos));
		} else if(orgsen[Pos]==separator) {
			// �}���`�G���g���̋�؂蕶��
			Pos++;
		} else {
			break;
		}
	}

	Pos=AcceptSpace();	// �T�[�r�X

	return;
}
#endif
//---------------------------------------------------------------------------
// ������̎w��ʒupos����g�[�N������؂�o��
// pos�͉��߂����������i�߂���
#if defined(STRING_APPEND_INATOMIC)
TKawariLexer::TToken TKawariLexer::GetToken(void)
{
	const string &orgsen=(*this);
	unsigned int cntsen = orgsen.size();

	TToken result;
	result.Type=TToken::ttokError;
	result.Str="";

	if(Pos>=cntsen) return(result);

	unsigned int startpos=Pos;

	try {
		if(orgsen[Pos]==CONST_START_MACRO[0]) {
			// �}�N��
			if((++Pos)>=orgsen.size()) throw("error");

			if(orgsen[Pos]=='{') {
				// ${�G���g����}
				result.Type=TToken::ttokMacroEntry;

				if((++Pos)>=orgsen.size()) throw("error");

				result.Str+="${";
			} else if(orgsen[Pos]=='(') {
				// $(�C�����C���X�N���v�g)
				result.Type=TToken::ttokMacroInline;

				if((++Pos)>=orgsen.size()) throw("error");

				result.Str+="$(";
			} else {
				// ���m�̃}�N��
				Pos++;
				throw("error");
			}
		} else if(StartSeparator.find(orgsen[Pos])!=string::npos) {
			// ��؂蕶��
			result.Type=TToken::ttokSeparator;

			result.Str+=orgsen[Pos++];
		} else if(StartWhiteSpace.find(orgsen[Pos])!=string::npos) {
			// �󔒕�����
			result.Type=TToken::ttokSpace;

			unsigned int startpos=Pos;
			Pos=AcceptSpace();
			result.Str+=orgsen.substr(startpos,Pos-startpos);
		} else if(StartQuote.find(orgsen[Pos])!=string::npos) {
			// �N�H�[�g������
			result.Type=TToken::ttokSentence;

			unsigned int startpos=Pos;
			Pos=AcceptQuotedString();
			result.Str+=DecodeQuotedString(orgsen.substr(startpos,Pos-startpos));
		} else {
			// ������
			result.Type=TToken::ttokSentence;
			
			unsigned int tmppos = Pos;
			while((Pos<cntsen)
			 &&(StartAll.find(orgsen[Pos])==string::npos)) {
#ifdef I18N_HACK
				if(int trail=lang.moreBytes(orgsen[Pos])) {
					if((Pos+trail)<cntsen) {
							Pos+=trail+1;
					} else Pos++;
				} else {
					Pos++;
				}
#else
				if(iskanji1st(orgsen[Pos])) {
					if((Pos+1)<cntsen) {
						Pos += 2;
					} else Pos++;
				} else {
					Pos++;
				}
#endif
			}
			if (Pos > tmppos)
				result.Str += orgsen.substr(tmppos, Pos - tmppos);
		}
	} catch(...) {
		// �G���[����
		result.Type=TToken::ttokError;
		result.Str=orgsen.substr(startpos,Pos-startpos);
		return(result);
	}

	// ����I��
	return(result);
}
#else
TKawariLexer::TToken TKawariLexer::GetToken(void)
{
	const string &orgsen=(*this);

	TToken result;
	result.Type=TToken::ttokError;
	result.Str="";

	if(Pos>=orgsen.size()) return(result);

	unsigned int startpos=Pos;

	try {
		if(orgsen[Pos]==CONST_START_MACRO[0]) {
			// �}�N��
			if((++Pos)>=orgsen.size()) throw("error");

			if(orgsen[Pos]=='{') {
				// ${�G���g����}
				result.Type=TToken::ttokMacroEntry;

				if((++Pos)>=orgsen.size()) throw("error");

				result.Str+="${";
			} else if(orgsen[Pos]=='(') {
				// $(�C�����C���X�N���v�g)
				result.Type=TToken::ttokMacroInline;

				if((++Pos)>=orgsen.size()) throw("error");

				result.Str+="$(";
			} else {
				// ���m�̃}�N��
				Pos++;
				throw("error");
			}
		} else if(StartSeparator.find(orgsen[Pos])!=string::npos) {
			// ��؂蕶��
			result.Type=TToken::ttokSeparator;

			result.Str+=orgsen[Pos++];
		} else if(StartWhiteSpace.find(orgsen[Pos])!=string::npos) {
			// �󔒕�����
			result.Type=TToken::ttokSpace;

			unsigned int startpos=Pos;
			Pos=AcceptSpace();
			result.Str+=orgsen.substr(startpos,Pos-startpos);
		} else if(StartQuote.find(orgsen[Pos])!=string::npos) {
			// �N�H�[�g������
			result.Type=TToken::ttokSentence;

			unsigned int startpos=Pos;
			Pos=AcceptQuotedString();
			result.Str+=DecodeQuotedString(orgsen.substr(startpos,Pos-startpos));
		} else {
			// ������
			result.Type=TToken::ttokSentence;
			while((Pos<orgsen.size())
			 &&(StartAll.find(orgsen[Pos])==string::npos)) {
#ifdef I18N_HACK
				if(int trail=lang.moreBytes(orgsen[Pos])) {
					if((Pos+trail)<orgsen.size()) {
						for(int i=0; i <= trail; i++)
							result.Str+=orgsen[Pos++];
					} else Pos++;
				} else {
					result.Str+=orgsen[Pos++];
				}
#else
				if(iskanji1st(orgsen[Pos])) {
					if((Pos+1)<orgsen.size()) {
						result.Str+=orgsen[Pos++];
						result.Str+=orgsen[Pos++];
					} else Pos++;
				} else {
					result.Str+=orgsen[Pos++];
				}
#endif
			}
		}
	} catch(...) {
		// �G���[����
		result.Type=TToken::ttokError;
		result.Str=orgsen.substr(startpos,Pos-startpos);
		return(result);
	}

	// ����I��
	return(result);
}
#endif
//---------------------------------------------------------------------------
// ������̎w��ʒupos����}�N�����܂܂Ȃ��P�ꕶ�������؂�o��
// pos�͉��߂����������i�߂���
string TKawariLexer::GetWordString(const char *separator_)
{
	string separator=separator_?string(separator_):string(",");

	Pos=AcceptSpace();

	string word;
	string ws;

	while(!IsEnd()) {
		unsigned int oldpos=Pos;
		TKawariLexer::TToken token=GetToken();

		// �P��̋�؂�L��������
		if((token.Type==TKawariLexer::TToken::ttokSeparator)
		 &&(separator.find(token.Str)!=string::npos)) {
			// �o�b�N�g���b�N
			Pos=oldpos;
			break;
		}

		// �G���g���Ăяo��
		// $(�C�����C���X�N���v�g)
		// �{���G���[����
		if((token.Type==TKawariLexer::TToken::ttokMacroEntry)
		 ||(token.Type==TKawariLexer::TToken::ttokMacroInline)) {
			// �o�b�N�g���b�N
			Pos=oldpos;
			break;
		}

		// ����ȊO
		switch(token.Type) {
		case TKawariLexer::TToken::ttokSpace :
			// �󔒕�����
			ws=token.Str;
			break;
		default:
			// ������E�E�E��������Ȃ�
			if(ws.size()) {
				word+=ws;
				ws="";
			}
			word+=token.Str;
		}
	}

	return(word);
}
//---------------------------------------------------------------------------
// '�܂���"�ň͂܂ꂽ�����񂩂�N�H�[�g�������͂���
string TKawariLexer::DecodeQuotedString(const string& orgsen)
{
	if(orgsen.size()==0) return("");

	char quote=orgsen[0];

	unsigned int pos=1;
	string retstr;

	while(pos<orgsen.size()) {
		if(orgsen[pos]==quote) break;

		if(orgsen[pos]=='\\') {
			if(((pos+1)<orgsen.size())&&(orgsen[pos+1]==quote)) pos++;
		}

#ifdef I18N_HACK
		if(int trail = lang.moreBytes(orgsen[pos])) {
			// MBCS
			if((pos+trail)<orgsen.size()) {
				for(int i=0; i < trail; i++)
					retstr+=orgsen[pos++];
			}
		}
#else
		if(iskanji1st(orgsen[pos])) {
			// ����
			if((pos+1)<orgsen.size()) retstr+=orgsen[pos++];
		}
#endif
		retstr+=orgsen[pos++];
	}

	return(retstr);
}
//---------------------------------------------------------------------------


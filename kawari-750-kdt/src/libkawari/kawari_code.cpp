//---------------------------------------------------------------------------
//
// "�ؘa��" for ����ȊO�̉����ȊO�̉���
// ���ԃR�[�h
//
//      Programed by NAKAUE.T (Meister)
//
//  2001.05.27  Phase 5.1     �C���^�[�v���^�E�R���p�C����
//  2001.06.12  Phase 5.3.2   �������z�G���g���ɂ�����R���e�L�X�g�̃o�O�C��
//  2001.06.17  Phase 5.4     �C�����C���X�N���v�g���̒P��؂�o���̃o�O�C��
//                            �C�����C���X�N���v�g���̗����Q�Ƃ̃o�O�C��
//                            �t�R���p�C��
//
//---------------------------------------------------------------------------
#include "config.h"
//---------------------------------------------------------------------------
#include <cstdlib>
#include <iostream>
using namespace std;
//---------------------------------------------------------------------------
#include "libkawari/kawari_code.h"
#include "libkawari/kawari_dict.h"
#include "misc/misc.h"
//---------------------------------------------------------------------------
// ���ԃR�[�h�̊��N���X
ostream& TKawariCode_base::DebugIndent(ostream& os,unsigned int level) const
{
	for(unsigned int i=0;i<level;i++) os << "    ";
	return(os);
}
//---------------------------------------------------------------------------
// ������
bool TKawariCodeString::Compile(TKawariLexer &source)
{
	string word;

	bool flag=false;
	while((!source.IsEnd())&&(!flag)) {
		unsigned int pos=source.Pos;
		TKawariLexer::TToken token=source.GetToken();

		switch(token.Type) {
		case TKawariLexer::TToken::ttokSentence:
			// �����񂾂���
			word+=token.Str;
			break;
		case TKawariLexer::TToken::ttokSeparator:
			// ��؂蕶���̒��ɂ͒P�ꈵ�����Ă悢���̂�����
			switch(token.Str[0]) {
			case ']':
				word+=token.Str;
				break;
			default:
				flag=true;
			}
			break;
		default:
			flag=true;
		}

		if(flag) {
			// �o�b�N�g���b�N
			source.Pos=pos;
		}
	}

	if(word.size()==0) return(false);

	Data=word;

	return(true);
}
//---------------------------------------------------------------------------
#if defined(STRING_APPEND_INATOMIC)
string TKawariCodeString::DisCompile(void) const
{
	string retstr="\"";
	unsigned int cnt = Data.size();
	unsigned int pos = 0;

	while(pos < cnt) {
		unsigned int pos2 = Data.find_first_of('"', pos);
		if (pos2 == string::npos) {
			if ((cnt - pos) > 0) retstr += Data.substr(pos, cnt - pos);
			break;
		}
		if ((pos2 - pos) > 0) retstr += Data.substr(pos, pos2 - pos);
		retstr += "\\\"";
		pos = pos2 + 1;
	}

	retstr+="\"";

	return(retstr);
}
#else
string TKawariCodeString::DisCompile(void) const
{
	string retstr="\"";

	for(unsigned int i=0;i<Data.size();i++) {
		if(Data[i]!='"') retstr+=Data[i];
		 else retstr+="\\\"";
	}

	retstr+="\"";

	return(retstr);
}
#endif
//---------------------------------------------------------------------------
// ${�G���g����}
string TKawariCodeEntryCall::Run(TKisEngine *engine)
{
	TEntryID entry=engine->Dictionary()->GetEntryID(EntryName);

	if(entry==0) return("");

	vector<TWordID> wordlist;
	engine->Dictionary()->FindAll(entry,wordlist);

	if(wordlist.size()==0) return("");

	TWordID id=wordlist[Random(wordlist.size())];
	TKawariCode_base *code=engine->Dictionary()->GetWordFromID(id);

	if(!code) return("");

	engine->CreateNullContext();
	string retstr=code->Run(engine);
	engine->DeleteContext();

	if(engine->Context()) engine->Context()->TempDict.push_back(retstr);

	return(retstr);
}
//---------------------------------------------------------------------------
string TKawariCodeEntryCall::DisCompile(void) const
{
	return(string("${")+EntryName+"}");
}
//---------------------------------------------------------------------------
// ${0}
string TKawariCodeTempEntryCall::Run(TKisEngine *engine)
{
	if(!engine->Context()) return("");

	if(engine->Context()->TempDict.size()<=EntryNo) return("");

	return(engine->Context()->TempDict[EntryNo]);
}
//---------------------------------------------------------------------------
string TKawariCodeTempEntryCall::DisCompile(void) const
{
	return(string("${")+IntToString(EntryNo)+"}");
}
//---------------------------------------------------------------------------
// ${�G���g����&�G���g����}
string TKawariCodeAndEntryCall::Run(TKisEngine *engine)
{
	vector<TEntryID> key;
	for(unsigned int i=0;i<EntryName.size();i++) {
		TEntryID entry=engine->Dictionary()->GetEntryID(EntryName[i]);
		if(entry) key.push_back(entry);
	}

	if(key.size()==0) return("");

	set<TWordID> wordset;
	engine->Dictionary()->GetWordCollection(key,wordset);

	if(wordset.size()==0) return("");

	unsigned int index=Random(wordset.size());

	set<TWordID>::iterator it=wordset.begin();
	for(unsigned int i=0;i<index;i++) it++;

	TKawariCode_base *code=engine->Dictionary()->GetWordFromID(*it);

	if(!code) return("");

	engine->CreateNullContext();
	string retstr=code->Run(engine);
	engine->DeleteContext();

	if(engine->Context()) engine->Context()->TempDict.push_back(retstr);

	return(retstr);
}
//---------------------------------------------------------------------------
string TKawariCodeAndEntryCall::DisCompile(void) const
{
	string retstr="${";

	for(unsigned int i=0;i<EntryName.size()-1;i++) retstr+=EntryName[i]+"&";
	retstr+=EntryName.back()+"}";

	return(retstr);
}
//---------------------------------------------------------------------------
void TKawariCodeAndEntryCall::Debug(ostream& os,unsigned int level) const
{
	DebugIndent(os,level) << "EntryName:";
	for(unsigned int i=0;i<EntryName.size()-1;i++) os << EntryName[i] << "&";
	os << EntryName.back() << endl;

	return;
}
//---------------------------------------------------------------------------
bool TKawariCodeAndEntryCall::Less(const TKawariCode_base &R_) const
{
	const TKawariCodeAndEntryCall& R=dynamic_cast<const TKawariCodeAndEntryCall&>(R_);

	if(EntryName.size()!=R.EntryName.size()) return(EntryName.size()<R.EntryName.size());

	for(unsigned int i=0;i<EntryName.size();i++) {
		if(EntryName[i]<R.EntryName[i]) return(true);
		if(EntryName[i]>R.EntryName[i]) return(false);
	}

	return(false);
}
//---------------------------------------------------------------------------
// 1�P���ێ�����
string TKawariCodeWord::Run(TKisEngine *engine)
{
	string retstr;
	for(unsigned int i=0;i<Code.size();i++) {
		retstr+=Code[i]->Run(engine);
	}

	return(retstr);
}
//---------------------------------------------------------------------------
string TKawariCodeWord::DisCompile(void) const
{
	string retstr;

	for(unsigned int i=0;i<Code.size();i++) retstr+=Code[i]->DisCompile();

	return(retstr);
}
//---------------------------------------------------------------------------
void TKawariCodeWord::Debug(ostream& os,unsigned int level) const
{
	DebugIndent(os,level) << "Word:" << endl;
	for(unsigned int i=0;i<Code.size();i++) Code[i]->Debug(os,level+1);

	return;
}
//---------------------------------------------------------------------------
bool TKawariCodeWord::Less(const TKawariCode_base &R_) const
{
	const TKawariCodeWord& R=dynamic_cast<const TKawariCodeWord&>(R_);

	if(Code.size()!=R.Code.size()) return(Code.size()<R.Code.size());

	for(unsigned int i=0;i<Code.size();i++) {
		TKawariCode_base *l=Code[i];
		TKawariCode_base *r=R.Code[i];

		if(TKawariCode_baseP_Less()(l,r)) return(true);
		if(TKawariCode_baseP_Less()(r,l)) return(false);
	}

	return(false);
}
//---------------------------------------------------------------------------
TKawariCodeWord::~TKawariCodeWord()
{
	for(unsigned int i=0;i<Code.size();i++) delete Code[i];
}
//---------------------------------------------------------------------------
// �R���e�L�X�g�𐶐�����
string TKawariCodeContext::Run(TKisEngine *engine)
{
	// �R���e�L�X�g����
	engine->CreateContext();

	string retstr=Code->Run(engine);

	// �R���e�L�X�g�j��
	engine->DeleteContext();

	return(retstr);
}
//---------------------------------------------------------------------------
// �C�����C���X�N���v�g�ꕶ
string TKawariCodeInlineScriptStatement::Run(TKisEngine *engine)
{
	vector<string> args;

	for(unsigned int i=0;i<Code.size();i++) {
		args.push_back(Code[i]->Run(engine));
	}

	return(engine->FunctionCall(args));
}
//---------------------------------------------------------------------------
string TKawariCodeInlineScriptStatement::DisCompile(void) const
{
	string retstr;

	for(unsigned int i=0;i<Code.size();i++) retstr+=Code[i]->DisCompile()+" ";

	return(retstr);
}
//---------------------------------------------------------------------------
void TKawariCodeInlineScriptStatement::Debug(ostream& os,unsigned int level) const
{
	DebugIndent(os,level) << "Statement:" << endl;
	for(unsigned int i=0;i<Code.size();i++) Code[i]->Debug(os,level+1);

	return;
}
//---------------------------------------------------------------------------
bool TKawariCodeInlineScriptStatement::Less(const TKawariCode_base &R_) const
{
	const TKawariCodeInlineScriptStatement& R=dynamic_cast<const TKawariCodeInlineScriptStatement&>(R_);

	if(Code.size()!=R.Code.size()) return(Code.size()<R.Code.size());

	for(unsigned int i=0;i<Code.size();i++) {
		TKawariCode_base *l=Code[i];
		TKawariCode_base *r=R.Code[i];

		if(TKawariCode_baseP_Less()(l,r)) return(true);
		if(TKawariCode_baseP_Less()(r,l)) return(false);
	}

	return(false);
}
//---------------------------------------------------------------------------
TKawariCodeInlineScriptStatement::~TKawariCodeInlineScriptStatement()
{
	for(unsigned int i=0;i<Code.size();i++) delete Code[i];
}
//---------------------------------------------------------------------------
// �C�����C���X�N���v�g�ꕶ
// �擪�p�����[�^��]�������Ɏ擾����
// �擪�p�����[�^��������ł͂Ȃ��ꍇ�ɂ͋󕶎����Ԃ�
string TKawariCodeInlineScriptStatement::GetArg0(void) const
{
	TKawariCodeString *str=dynamic_cast<TKawariCodeString*>(Code[0]);
	if(!str) return("");

	return(str->Get());
}
//---------------------------------------------------------------------------
// �C�����C���X�N���v�g
string TKawariCodeInlineScript::Run(TKisEngine *engine)
{
	unsigned int frame=engine->LinkContext();

	string retstr=engine->Run(Code);

	engine->UnlinkContext(frame);

	return(retstr);
}
//---------------------------------------------------------------------------
string TKawariCodeInlineScript::DisCompile(void) const
{
	string retstr="$(";

	for(unsigned int i=0;i<Code.size()-1;i++) retstr+=Code[i]->DisCompile()+";";
	retstr+=Code.back()->DisCompile()+")";

	return(retstr);
}
//---------------------------------------------------------------------------
void TKawariCodeInlineScript::Debug(ostream& os,unsigned int level) const
{
	DebugIndent(os,level) << "InlineScript:" << endl;
	for(unsigned int i=0;i<Code.size();i++) Code[i]->Debug(os,level+1);

	return;
}
//---------------------------------------------------------------------------
bool TKawariCodeInlineScript::Less(const TKawariCode_base &R_) const
{
	const TKawariCodeInlineScript& R=dynamic_cast<const TKawariCodeInlineScript&>(R_);

	if(Code.size()!=R.Code.size()) return(Code.size()<R.Code.size());

	for(unsigned int i=0;i<Code.size();i++) {
		TKawariCode_base *l=Code[i];
		TKawariCode_base *r=R.Code[i];

		if(TKawariCode_baseP_Less()(l,r)) return(true);
		if(TKawariCode_baseP_Less()(r,l)) return(false);
	}

	return(false);
}
//---------------------------------------------------------------------------
TKawariCodeInlineScript::~TKawariCodeInlineScript()
{
	for(unsigned int i=0;i<Code.size();i++) delete Code[i];
}
//---------------------------------------------------------------------------
// �����񂩂��P���؂�o���A���ԃR�[�h�ɃR���p�C������
bool TKawariCodeWord::Compile(vector<TKawariCode_base*> &codelist,TKawariLexer &source)
{
	unsigned int oldsize=codelist.size();

	while(!source.IsEnd()) {
		unsigned int pos=source.Pos;
		TKawariLexer::TToken token=source.GetToken();

		bool flag=false;
		switch(token.Type) {
		case TKawariLexer::TToken::ttokSpace :
			// �󔒕����񂾂����̂Ńo�b�N�g���b�N
			source.Pos=pos;
			flag=true;
			break;
		case TKawariLexer::TToken::ttokMacroEntry :
			// �G���g���Ăяo��
			{
				vector<string> key;
				source.GetEntryList(key);

				if(!source.IsEnd()&&(source[source.Pos]=='}')) {
					source.Pos++;
					if(key.size()==1) {
						if(('0'<=key[0][0])&&(key[0][0]<='9')) {
							// �ꎞ�G���g���Ăяo��
							TKawariCodeTempEntryCall *code=new TKawariCodeTempEntryCall;
							code->Set((unsigned int)atoi(key[0].c_str()));
							codelist.push_back(code);
						} else {
							// �P�ƃG���g���Ăяo��
							TKawariCodeEntryCall *code=new TKawariCodeEntryCall;
							code->Set(key[0]);
							codelist.push_back(code);
						}
					} else if(key.size()>1) {
						// AND�G���g���Ăяo��
						TKawariCodeAndEntryCall *code=new TKawariCodeAndEntryCall;
						code->Set(key);
						codelist.push_back(code);
					}
				} else {
					// ${�G���g����}�Ƃ��ĉ��߂ł��Ȃ������̂�
					// ������ɂ��Ă��܂�
					TKawariCodeString *str=new TKawariCodeString(source.substr(pos,source.Pos-pos));
					codelist.push_back(str);
				}
			}
			break;
		case TKawariLexer::TToken::ttokMacroInline :
			// $(�C�����C���X�N���v�g)
			source.Pos=pos;
			{
				vector<TKawariCodeInlineScriptStatement*> codelist2;
				if(TKawariCodeInlineScript::Compile(codelist2,source)) {
					TKawariCodeInlineScript *code=new TKawariCodeInlineScript;
					code->Add(codelist2);
					codelist.push_back(code);
				} else {
					// $(�C�����C���X�N���v�g)�Ƃ��ĉ��߂ł��Ȃ������̂�
					// ������ɂ��Ă��܂�
					TKawariCodeString *str=new TKawariCodeString(source.substr(pos,source.Pos-pos));
					codelist.push_back(str);
				}
			}
			break;
		default:
			// ������E�E�E��������Ȃ�
			source.Pos=pos;
			{
				TKawariCodeString *code=new TKawariCodeString;
				if(code->Compile(source)) {
					codelist.push_back(code);
				} else {
					// ������ł͂Ȃ������̂Ńo�b�N�g���b�N
					delete code;
					source.Pos=pos;
					flag=true;
				}
			}
		}

		if(flag) break;
	}

	return(codelist.size()!=oldsize);
}
//---------------------------------------------------------------------------
// �����񂩂��P���؂�o���A���ԃR�[�h�ɃR���p�C������
// �w��̋�؂蕶���ȊO�͑S�ĕ�����Ƃ���
// ��؂蕶�����w�肳�ꂽ���́A�����̋󔒂���������
bool TKawariCodeWord::Compile2(vector<TKawariCode_base*> &codelist,TKawariLexer &source,char separator)
{
	unsigned int oldsize=codelist.size();
	string ws;

	while(!source.IsEnd()) {
		unsigned pos=source.Pos;
		TKawariLexer::TToken token=source.GetToken();

		// �P��̋�؂��,������
		if((token.Type==TKawariLexer::TToken::ttokSeparator)&&(token.Str[0]==separator)) break;

		// ����ȊO
		switch(token.Type) {
		case TKawariLexer::TToken::ttokSpace :
			// �󔒕�����
			ws=token.Str;
			break;
		default:
			source.Pos=pos;
			{
				vector<TKawariCode_base*> codelist2;

				if(TKawariCodeWord::Compile(codelist2,source)) {
					if(ws.size()) {
						TKawariCodeString *str=new TKawariCodeString(ws);
						codelist.push_back(str);
						ws="";
					}
					for(unsigned int i=0;i<codelist2.size();i++) {
						codelist.push_back(codelist2[i]);
					}
				} else {
					token=source.GetToken();
					if(token.Str.size()) {
						TKawariCodeString *str=new TKawariCodeString(ws+token.Str);
						codelist.push_back(str);
						ws="";
					}
				}
			}
		}
	}

	if(ws.size()&&(separator==0)) {
		TKawariCodeString *str=new TKawariCodeString(ws);
		codelist.push_back(str);
	}

	return(codelist.size()!=oldsize);
}
//---------------------------------------------------------------------------
// �����񂩂�C�����C���X�N���v�g���ꕶ�؂�o���A���ԃR�[�h�ɃR���p�C������
// true�Ōp��,false�ŃC�����C���X�N���v�g�I��
bool TKawariCodeInlineScriptStatement::Compile(vector<TKawariCode_base*> &codelist,TKawariLexer &source)
{
	unsigned int oldsize=codelist.size();
	bool statusflag=false;

	vector<TKawariCode_base*> codelist2;
	while(!source.IsEnd()) {
		unsigned pos=source.Pos;
		TKawariLexer::TToken token=source.GetToken();

		if(token.Type==TKawariLexer::TToken::ttokSeparator) {
			if(token.Str==")") {
				// �C�����C���X�N���v�g�I����")"������
				break;
			} else if(token.Str==";") {
				// �}���`�X�e�[�g�����g�̋�؂�
				statusflag=true;
				break;
			}
		}

		switch(token.Type) {
		case TKawariLexer::TToken::ttokSpace :
			// �󔒕�����
			if(codelist2.size()==1) {
				codelist.push_back(codelist2[0]);
			} else if(codelist2.size()>1) {
				TKawariCodeWord *code=new TKawariCodeWord;
				code->Add(codelist2);
				codelist.push_back(code);
			}
			codelist2.clear();
			break;
		default:
			// ��{�I�ɒP��
			source.Pos=pos;
			if(!TKawariCodeWord::Compile(codelist2,source)) {
				// ������Ȃ����̂͂Ƃ肠����������
				token=source.GetToken();
				if(token.Str.size()) {
					TKawariCodeString *str=new TKawariCodeString(token.Str);
					codelist2.push_back(str);
				}
			}
		}
	}

	if(codelist2.size()==1) {
		codelist.push_back(codelist2[0]);
	} else if(codelist2.size()>1) {
		TKawariCodeWord *code=new TKawariCodeWord;
		code->Add(codelist2);
		codelist.push_back(code);
	}

	return((codelist.size()!=oldsize)&&statusflag);
}
//---------------------------------------------------------------------------
// �����񂩂�C�����C���X�N���v�g��؂�o���A���ԃR�[�h�ɃR���p�C������
bool TKawariCodeInlineScript::Compile(vector<TKawariCodeInlineScriptStatement*> &codelist,TKawariLexer &source)
{
	if(source.IsEnd()) return(false);

	unsigned int oldsize=codelist.size();
	unsigned int pos=source.Pos;
	TKawariLexer::TToken token=source.GetToken();

	if(token.Type!=TKawariLexer::TToken::ttokMacroInline) {
		// �o�b�N�g���b�N
		source.Pos=pos;
		return(false);
	}

	while(true) {
		vector<TKawariCode_base*> codelist2;

		bool status=TKawariCodeInlineScriptStatement::Compile(codelist2,source);

		if(codelist2.size()) {
			TKawariCodeInlineScriptStatement *code=new TKawariCodeInlineScriptStatement;
			code->Add(codelist2);
			codelist.push_back(code);
		}

		if(!status) break;
	}

	return(codelist.size()!=oldsize);
}
//---------------------------------------------------------------------------

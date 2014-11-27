//---------------------------------------------------------------------------
//
// "�ؘa��" for ����ȊO�̉����ȊO�̉���
// �ؘa���G���W��
//
//      Programed by NAKAUE.T (Meister)
//
//  2001.05.27  Phase 5.1     �C���^�[�v���^�E�R���p�C����
//                            �N���X�K�w����
//  2001.05.31  Phase 5.2     �ێ�Ipiro
//  2001.06.09  Phase 5.3     �}�b�`�G���g��
//  2001.06.10  Phase 5.3.1   �C�x���g���Ŏg����L�����u_�v����u.�v�ɕύX
//  2001.06.17  Phase 5.4     �����G���g���ւ̓����ǉ��̃o�O�C��
//                            save
//  2001.08.06  Phase 6.2     �p���s�ɑΉ�
//  2001.08.07  Phase 6.2     ostrstream�o�O�C��
//                            �p���s���(�v���@�Č���)
//  2001.08.25  Phase 7.0     �Z�L�����e�B�΍�(WriteProtect)
//  2001.12.08  Phase 7.1.2   �e�L�X�g�t�@�C���ǂݍ��ݑΉ�
//
//---------------------------------------------------------------------------
#include "config.h"
//---------------------------------------------------------------------------
#include "libkawari/kawari_engine.h"
//---------------------------------------------------------------------------
#include <iostream>
#include <fstream>
using namespace std;
//---------------------------------------------------------------------------
#include "libkawari/kawari_crypt.h"
#include "libkawari/sequence_gen.h"
#include "misc/misc.h"
//---------------------------------------------------------------------------
// ��������G���g�����Ŏg�p�\�ȕ�����ɃG���R�[�h����
#if defined(STRING_APPEND_INATOMIC)
string TKawariEngine::EncodeEntryName(const string &orgsen) const
{
	// 2001-10-29 �����������Ă݂�...
	string entsen(orgsen);
	unsigned cntsen = entsen.size();
	
	for(unsigned int pos=0;pos<cntsen;pos++) {
		char	c = entsen[pos];
		if(iskanji1st(c)) {
			// �����Ƃ͎v���������͎�e
			if((pos+1)<cntsen) pos++;
			else break;
		} else if(!isalnum(c)) {
			// �g���Ȃ������͑S��'.'�ɕϊ�
			entsen[pos] = '.';
		}
	}
	
	return(entsen);
}
#else
string TKawariEngine::EncodeEntryName(const string &orgsen) const
{
	string entsen;

	for(unsigned int pos=0;pos<orgsen.size();pos++) {
		if(iskanji1st(orgsen[pos])) {
			// �����Ƃ͎v���������͎�e
			if((pos+1)<orgsen.size()) {
				entsen+=orgsen[pos++];
				entsen+=orgsen[pos];
			} else {
				break;
			}
		} else if(isalnum(orgsen[pos])) {
			// �C�x���g�������ɂ�'.'�ȊO�̋L�����g��Ȃ�
			entsen+=orgsen[pos];
		} else {
			// �g���Ȃ������͑S��'.'�ɕϊ�
			entsen+='.';
		}
	}

	return(entsen);
}
#endif
//---------------------------------------------------------------------------
// �w�肳�ꂽ�G���g������ɂ���
void TKawariEngine::ClearEntry(const string& entryname)
{
	TEntryID entry=Dictionary->GetEntryID(entryname);
	if(entry==0) return;
	if(ProtectedEntry.count(entry)) return;

	Dictionary->ClearEntry(entry);

	return;
}
//---------------------------------------------------------------------------
// �����ւ̒P��̒ǉ�
void TKawariEngine::Insert(const string& entryname,const string& word)
{
	TEntryID entry=Dictionary->CreateEntry(entryname);
	if(ProtectedEntry.count(entry)) return;

	Dictionary->Insert(entry,word);

	return;
}
//---------------------------------------------------------------------------
// �w�肳�ꂽ�G���g������ɂ��Ă���P���ǉ�
void TKawariEngine::InsertAfterClear(const string& entryname,const string& word)
{
	TEntryID entry=Dictionary->CreateEntry(entryname);
	if(ProtectedEntry.count(entry)) return;


	Dictionary->InsertAfterClear(entry,word);

	return;
}
//---------------------------------------------------------------------------
// �w�肳�ꂽ�G���g���ւ̏������݂��֎~����
void TKawariEngine::WriteProtect(const string& entryname)
{
	TEntryID entry=Dictionary->CreateEntry(entryname);

	ProtectedEntry.insert(entry);

	return;
}
//---------------------------------------------------------------------------
// �w�肳�ꂽ�G���g���̐擪�̒P���Ԃ�
string TKawariEngine::FindFirst(const string& entryname) const
{
	TWordID id=Dictionary->FindFirst(Dictionary->GetEntryID(entryname));

	if(id==0) return("");

	TKawariCode_base *code=Dictionary->GetWordFromID(id);

	if(!code) return("");

	return(code->Run(KisEngine));
}
//---------------------------------------------------------------------------
// �w�肳�ꂽ�G���g���̒P��������_���ɑI�����ĕԂ�
string TKawariEngine::RandomSelect(const string& entryname) const
{
	vector<TWordID> wordlist;

	Dictionary->FindAll(Dictionary->GetEntryID(entryname),wordlist);

	if(wordlist.size()==0) return("");

	TWordID id=wordlist[Random(wordlist.size())];
	TKawariCode_base *code=Dictionary->GetWordFromID(id);

	if(!code) return("");

	return(code->Run(KisEngine));
}
//---------------------------------------------------------------------------
// ���������̂�������}�b�`�G���g���̒P��������_���ɑI�����ĕԂ�
string TKawariEngine::MatchEntryRandomSelect(const string& entryname) const
{
	vector<TEntryID> entrylist;

	if(MatchDictionary->Evaluation(entrylist)==0) return("");

	TEntryID entry=entrylist[Random(entrylist.size())];

	vector<TWordID> wordlist;

	Dictionary->FindAll(entry,wordlist);

	if(wordlist.size()==0) return("");

	TWordID id=wordlist[Random(wordlist.size())];
	TKawariCode_base *code=Dictionary->GetWordFromID(id);

	if(!code) return("");

	return(code->Run(KisEngine));
}
//---------------------------------------------------------------------------
// �ؘa���t�H�[�}�b�g�����t�@�C����ǂݍ���
bool TKawariEngine::LoadKawariDict(const string &filename)
{
	ifstream ifs;
	ifs.open(filename.c_str());

	if(!ifs.is_open()) return(false);

	string localid="LocalID"+SequenceGenerator.GetString("Local")+"@";

//	if(LogFS) (*LogFS) << "Load:" << (filename) << endl;
//	if(LogFS) (*LogFS) << "Load(id):" << (localid) << endl;

	string strbuff;
	while(getline(ifs,strbuff)) {
		strbuff=StringTrim(strbuff);
		if((strbuff.size()>0)&&(strbuff[0]=='!')) {
			if(CheckCrypt(strbuff)) {
				strbuff=StringTrim(DecryptString(strbuff));
			} else {
				strbuff="";
			}
		}

		if(strbuff.size()==0) continue;

		TKawariLexer buff(strbuff);

		if(buff[0]=='#') {
			// �R�����g
		} else if(buff[0]==':') {
			// �v���v���Z�b�T
		} else if(buff[0]=='[') {
			// �}�b�`�G���g��
			buff.Pos=1;

			TKawariMatchFind *match=new TKawariMatchFind;

			try {
				match->SetEntryName("system.Sentence");

				while(!buff.IsEnd()) {
					string key=buff.GetWordString(",&]");

					if(key.size()) match->Add(key);

					buff.Pos=buff.AcceptSpace();

					if(buff.IsEnd()) throw("error");

					if(buff[buff.Pos]==']') {
						buff.Pos++;
						break;
					}

					if((buff[buff.Pos]!=',')&&(buff[buff.Pos]!='&')) throw("error");

					buff.Pos++;
				}

				buff.Pos=buff.AcceptSpace();
				if(buff.IsEnd()||(buff[buff.Pos]!=':')) throw("error");
				buff.Pos++;

				TEntryID entry=MatchDictionary->CreateMatchEntry(match);
				match=NULL;

				while(!buff.IsEnd()) {
					TKawariCode_base *code=ParseKawariDict(buff,localid);
					if(code) Dictionary->Insert(entry,code);
				}
			} catch(...) {
				if(match) delete match;
//				if(LogFS) (*LogFS) << "ERROR:Load(matchentry):" << ((string)buff) << endl;
			}
		} else {
			// �P��o�^
			try {
				vector<string> keystr;
				buff.GetEntryList(keystr,',');

				if(keystr.size()) {
					if(buff.IsEnd()) throw("error");

					if(buff[buff.Pos]==':') {
						buff.Pos++;
#if 0
// �p���s���(�v���@�Č���)
					} else if(buff[buff.Pos]=='{') {
						buff.Pos++;
						buff.Pos=buff.AcceptSpace();
						// �u�G���g���� {�v�̍s������(�u}�v�܂Ōp��)
						string linebuff=buff.substr(buff.Pos);
						string strbuff;
						while(getline(ifs,strbuff)) {
							strbuff=StringTrim(strbuff);
							if((strbuff.size()>0)&&(strbuff[0]=='!')) {
								if(CheckCrypt(strbuff)) {
									strbuff=StringTrim(DecryptString(strbuff));
								} else {
									strbuff="";
								}
							}

							if((strbuff.size()==0)||(strbuff[0]=='#')||(strbuff[0]==':')) continue;
							if(strbuff[0]=='}') break;

							if(linebuff.size()>0) linebuff+=" ";
							linebuff+=strbuff;
						}

						buff=linebuff;
#endif
					} else throw("error");

					vector<TEntryID> key;
					for(unsigned int i=0;i<keystr.size();i++) {
						key.push_back(Dictionary->CreateEntry(keystr[i]));
					}

					while(!buff.IsEnd()) {
						TKawariCode_base *code=ParseKawariDict(buff,localid);

						if(code) {
							TWordID id=Dictionary->Insert(key[0],code);
							for(unsigned int i=1;i<key.size();i++) {
								Dictionary->Insert(key[i],id);
							}
    					}
	    			}
                }
			} catch(...) {
//				if(LogFS) (*LogFS) << "ERROR:Load(entry):" << ((string)buff) << endl;
			}
		}
	}
	ifs.close();

	return(true);
}
//---------------------------------------------------------------------------
// �e�L�X�g�t�@�C���ǂݍ���
bool TKawariEngine::LoadTextFile(const string &filename,const string &baseentry)
{
	ifstream ifs;
	ifs.open(filename.c_str());

	if(!ifs.is_open()) return(false);

	string buff;
	int line=0;
	int nline=0;
	while(getline(ifs,buff)) {
//		buff=StringTrim(buff);
		line++;
		string entry=baseentry+string(".")+IntToString(line);
		if(buff.size()>0) { // ��s�ł͂Ȃ�������G���g���ɒǉ�
			InsertAfterClear(entry,buff);
		} else { // ��s���J�E���g
			nline++;
			ClearEntry(entry);
		}
	}

	if((line>0)&&(nline!=line)) { // ��̃t�@�C���ł͂Ȃ�������s�����Z�b�g
		InsertAfterClear(baseentry+string(".size"),IntToString(line));
	}
	ifs.close();

	return(true);
}
//---------------------------------------------------------------------------
// �ؘa���t�H�[�}�b�g�t�@�C���̒P������߂��Ď擾
TKawariCode_base *TKawariEngine::ParseKawariDict(TKawariLexer &buff,const string& localid)
{
	buff.Pos=buff.AcceptSpace();

	vector<TKawariCode_base*> codelist;

	if(!TKawariCodeWord::Compile2(codelist,buff,',')) return(NULL);

	if(codelist.size()==1) return(codelist[0]);

	TKawariCodeWord *code=new TKawariCodeWord;
	code->Add(codelist);

	return(code);
}
//---------------------------------------------------------------------------
// �ؘa���t�H�[�}�b�g�����t�@�C������������
bool TKawariEngine::SaveKawariDict(const string &filename,const vector<string>& entry,bool crypt) const
{
	ofstream ofs;
	ofs.open(filename.c_str());

	if(!ofs.is_open()) return(false);

	ofs << "#" << endl << "# Kawari saved file" << endl << "#" << endl;

	for(unsigned int i=0;i<entry.size();i++) {
		ofs << "# Entry " << entry[i] << endl;

		vector<TWordID> wordcol;
		Dictionary->FindAll(Dictionary->GetEntryID(entry[i]),wordcol);
		if(wordcol.size()) {
			string line;
			line=entry[i]+" : "+Dictionary->GetWordFromID(wordcol[0])->DisCompile();

			for(unsigned int j=1;j<wordcol.size();j++) {
				line+=" , ";
				line+=Dictionary->GetWordFromID(wordcol[j])->DisCompile();
			}

			if(!crypt) {
				ofs << line << endl;
			} else {
				ofs << EncryptString(line) << endl;
			}
		}
	}

	ofs.close();

	return(true);
}
//---------------------------------------------------------------------------
// �^����ꂽ�P������߂���
string TKawariEngine::Parse(const string& word)
{
	TKawariCode_base *code=Dictionary->StringToCode(word);
    if (!code) return string("");
	code=code->CreateContext();
	string retstr=code->Run(KisEngine);
	delete code;
	return(retstr);
}
//---------------------------------------------------------------------------
// ���O�X�g���[���𓾂�
ostream *TKawariEngine::GetLogStream(void){
	if (Kawari)
		return Kawari->LogFS;
	else
		return NULL;
}
//---------------------------------------------------------------------------
// SAORI���W���[���̓o�^
void TKawariEngine::RegisterSAORIModule(const string &aliasname, const string &path, const SAORILOADTYPE type){
	SaoriPark->RegisterModule(aliasname, path, (TSaoriModule::LOADTYPE)type);
}
//---------------------------------------------------------------------------
// SAORI���W���[���o�^�̍폜
void TKawariEngine::EraseSAORIModule(const string &aliasname){
	SaoriPark->EraseModule(aliasname);
}
//---------------------------------------------------------------------------
// SAORI���N�G�X�g���s��
bool TKawariEngine::RequestToSAORIModule(
	const string &aliasname,
	const TPHMessage &request, TPHMessage &response)
{
	TSaoriModule *module=SaoriPark->GetModule(aliasname);
	if (!module)
		return false;
	else
		return module->Request(request, response);
}
//---------------------------------------------------------------------------
TKawariEngine::TKawariEngine(TNS_KawariANI *kawari)
{
	Dictionary=new TNS_KawariDictionary;
	KisEngine=new TKisEngine(Dictionary,this);
	MatchDictionary=new TNS_KawariMatchDictionary(Dictionary,this);
	SaoriPark=new TSaoriPark();
	Kawari=kawari;
}
//---------------------------------------------------------------------------

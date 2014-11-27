//---------------------------------------------------------------------------
//
// "�ؘa��" for ����ȊO�̉����ȊO�̉���
// ���ԃR�[�h
//
//      Programed by NAKAUE.T (Meister)
//
//  2001.05.27  Phase 5.1     �C���^�[�v���^�E�R���p�C����
//  2001.06.17  Phase 5.4     �t�R���p�C��
//
//---------------------------------------------------------------------------
#ifndef KAWARI_CODE_H
#define KAWARI_CODE_H
//---------------------------------------------------------------------------
#include "config.h"
//---------------------------------------------------------------------------
#include <string>
#include <vector>
#include <iostream>
#include <typeinfo>
using namespace std;
//---------------------------------------------------------------------------
#include "libkawari/kawari_lexer.h"
#include "libkawari/kawari_iscript.h"
#include "misc/misc.h"
//---------------------------------------------------------------------------
// ���ԃR�[�h�̊��N���X
class TKawariCode_base {
public:

	// ���s
	virtual string Run(TKisEngine *engine)=0;

	// �t�R���p�C��
	virtual string DisCompile(void) const =0;

	// �R���e�L�X�g����
	virtual TKawariCode_base* CreateContext(void) {return(this);}

	// �f�o�b�O�p�c���[�\��
	virtual void Debug(ostream& os,unsigned int level=0) const =0;

	// Debug�ŏo�͂����낦��
	ostream& DebugIndent(ostream& os,unsigned int level) const;

	// ����
	virtual bool Less(const TKawariCode_base& R_) const =0;

	virtual ~TKawariCode_base() {}
};
//---------------------------------------------------------------------------
class TKawariCode_baseP_Less {
public:
	bool operator()(const TKawariCode_base *L,const TKawariCode_base *R) const
	{
		if(typeid(*L)==typeid(*R)) return (L->Less(*R));
		return(string(typeid(*L).name())<string(typeid(*R).name()));
	}
};
//---------------------------------------------------------------------------
// �R���e�L�X�g�𐶐�����
class TKawariCodeContext : public TKawariCode_base {
private:

	TKawariCode_base* Code;

public:

	TKawariCodeContext(TKawariCode_base *code) : Code(code) {}


	virtual string Run(TKisEngine *engine);

	virtual string DisCompile(void) const
	{
		return(Code->DisCompile());
	}

	virtual void Debug(ostream& os,unsigned int level=0) const
	{
		DebugIndent(os,level) << "Context:" << endl;
		Code->Debug(os,level+1);
	}

	virtual bool Less(const TKawariCode_base &R_) const
	{
		const TKawariCodeContext& R=dynamic_cast<const TKawariCodeContext&>(R_);
		return TKawariCode_baseP_Less()(Code,R.Code);	// ���ʂ������̂�GCC2.95.2�̃o�O���
	}

	virtual ~TKawariCodeContext()
	{
		delete Code;
	}

};
//---------------------------------------------------------------------------
// ������
class TKawariCodeString : public TKawariCode_base {
private:

	string Data;

public:

	TKawariCodeString(void) {}

	TKawariCodeString(const string& str) : Data(str) {}

	bool Compile(TKawariLexer &source);

	virtual string Get(void) const
	{
		return(Data);
	}

	virtual string Run(TKisEngine *)
	{
		return(Data);
	}

	virtual string DisCompile(void) const;

	virtual void Debug(ostream& os,unsigned int level=0) const
	{
		DebugIndent(os,level) << "String:" << Data << endl;
	}

	virtual bool Less(const TKawariCode_base &R_) const
	{
		const TKawariCodeString& R=dynamic_cast<const TKawariCodeString&>(R_);
		return(Data<R.Data);
	}

};
//---------------------------------------------------------------------------
// ${�G���g����}
class TKawariCodeEntryCall : public TKawariCode_base {
private:

	string EntryName;

public:

	bool Set(const string& entryname)
	{
		EntryName=entryname;
		return(true);
	}

	const string& Get(void)
	{
		return(EntryName);
	}

	virtual string Run(TKisEngine *engine);

	virtual string DisCompile(void) const;

	virtual void Debug(ostream& os,unsigned int level=0) const
	{
		DebugIndent(os,level) << "EntryCall:" << EntryName << endl;
	}

	virtual bool Less(const TKawariCode_base &R_) const
	{
		const TKawariCodeEntryCall& R=dynamic_cast<const TKawariCodeEntryCall&>(R_);
		return(EntryName<R.EntryName);
	}

};
//---------------------------------------------------------------------------
// ${0}
class TKawariCodeTempEntryCall : public TKawariCode_base {
private:

	unsigned int EntryNo;

public:

	bool Set(unsigned int no)
	{
		EntryNo=no;
		return(true);
	}

	virtual string Run(TKisEngine *engine);

	virtual string DisCompile(void) const;

	virtual void Debug(ostream& os,unsigned int level=0) const
	{
		DebugIndent(os,level) << "TempEntryCall:" << EntryNo << endl;
	}

	virtual bool Less(const TKawariCode_base &R_) const
	{
		const TKawariCodeTempEntryCall& R=dynamic_cast<const TKawariCodeTempEntryCall&>(R_);
		return(EntryNo<R.EntryNo);
	}

};
//---------------------------------------------------------------------------
// ${�G���g����&�G���g����}
class TKawariCodeAndEntryCall : public TKawariCode_base {
private:

	vector<string> EntryName;

public:

	bool Set(const vector<string>& key)
	{
		EntryName.insert(EntryName.end(),key.begin(),key.end());
		return(true);
	}


	virtual string Run(TKisEngine *engine);

	virtual string DisCompile(void) const;

	virtual void Debug(ostream& os,unsigned int level=0) const;

	virtual bool Less(const TKawariCode_base &R_) const;

};
//---------------------------------------------------------------------------
// 1�P���ێ�����
class TKawariCodeWord : public TKawariCode_base {
private:

	vector<TKawariCode_base*> Code;

public:

	bool Add(const vector<TKawariCode_base*>& codelist)
	{
		Code.insert(Code.end(),codelist.begin(),codelist.end());
		return(true);
	}


	bool Add(TKawariCode_base* code)
	{
		Code.push_back(code);
		return(true);
	}


	// �����񂩂��P���؂�o���A���ԃR�[�h�ɃR���p�C������
	static bool Compile(vector<TKawariCode_base*> &codelist,TKawariLexer &source);

	// �����񂩂��P���؂�o���A���ԃR�[�h�ɃR���p�C������
	// �w��̋�؂蕶���ȊO�͑S�ĕ�����Ƃ���
	// ��؂蕶�����w�肳�ꂽ���́A�����̋󔒂���������
	static bool Compile2(vector<TKawariCode_base*> &codelist,TKawariLexer &source,char separator=0);

	virtual string Run(TKisEngine *engine);

	virtual TKawariCode_base* CreateContext(void)
	{
		return(new TKawariCodeContext(this));
	}

	virtual string DisCompile(void) const;

	virtual void Debug(ostream& os,unsigned int level=0) const;

	virtual bool Less(const TKawariCode_base &R_) const;

	virtual ~TKawariCodeWord();

};
//---------------------------------------------------------------------------
// �C�����C���X�N���v�g�ꕶ
class TKawariCodeInlineScriptStatement : public TKawariCode_base {
private:
public:

	vector<TKawariCode_base*> Code;

	// �����񂩂�C�����C���X�N���v�g���ꕶ�؂�o���A���ԃR�[�h�ɃR���p�C������
	// true�Ōp��,false�ŃC�����C���X�N���v�g�I��
	static bool Compile(vector<TKawariCode_base*> &codelist,TKawariLexer &source);

	// �^����ꂽ���ԃR�[�h���i�[(�ǉ�)����
	bool Add(const vector<TKawariCode_base*>& codelist)
	{
		Code.insert(Code.end(),codelist.begin(),codelist.end());
		return(true);
	}

	// �^����ꂽ���ԃR�[�h���i�[(�ǉ�)����
	bool Add(TKawariCode_base* code)
	{
		Code.push_back(code);
		return(true);
	}

	// �擪�p�����[�^��]�������Ɏ擾����
	// �擪�p�����[�^��������ł͂Ȃ��ꍇ�ɂ͋󕶎����Ԃ�
	string GetArg0(void) const;

	virtual string Run(TKisEngine *engine);

	virtual TKawariCode_base* CreateContext(void)
	{
		return(new TKawariCodeContext(this));
	}

	virtual string DisCompile(void) const;

	virtual void Debug(ostream& os,unsigned int level=0) const;

	virtual bool Less(const TKawariCode_base &R_) const;

	virtual ~TKawariCodeInlineScriptStatement();
};
//---------------------------------------------------------------------------
// �C�����C���X�N���v�g
class TKawariCodeInlineScript : public TKawariCode_base {
private:

	vector<TKawariCodeInlineScriptStatement*> Code;

public:


	bool Add(const vector<TKawariCodeInlineScriptStatement*>& codelist)
	{
		Code.insert(Code.end(),codelist.begin(),codelist.end());
		return(true);
	}


	bool Add(TKawariCodeInlineScriptStatement* code)
	{
		Code.push_back(code);
		return(true);
	}

	// �����񂩂�C�����C���X�N���v�g��؂�o���A���ԃR�[�h�ɃR���p�C������
	static bool Compile(vector<TKawariCodeInlineScriptStatement*> &codelist,TKawariLexer &source);

	virtual string Run(TKisEngine *engine);

	virtual TKawariCode_base* CreateContext(void)
	{
		return(new TKawariCodeContext(this));
	}

	virtual string DisCompile(void) const;

	virtual void Debug(ostream& os,unsigned int level=0) const;

	virtual bool Less(const TKawariCode_base &R_) const;

	virtual ~TKawariCodeInlineScript();
};
//---------------------------------------------------------------------------
#endif

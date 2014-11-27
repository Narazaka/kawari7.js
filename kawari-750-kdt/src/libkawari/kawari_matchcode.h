//---------------------------------------------------------------------------
//
// "�ؘa��" for ����ȊO�̉����ȊO�̉���
// �}�b�`�G���g�����ԃR�[�h
//
//      Programed by NAKAUE.T (Meister)
//
//  2001.06.09  Phase 5.3     �}�b�`�G���g���Ď���
//
//---------------------------------------------------------------------------
#ifndef KAWARI_MATCHCODE_H
#define KAWARI_MATCHCODE_H
//---------------------------------------------------------------------------
#include "config.h"
//---------------------------------------------------------------------------
#include <string>
#include <vector>
#include <iostream>
#include <typeinfo>
using namespace std;
//---------------------------------------------------------------------------
#include "libkawari/kawari_engine_fwd.h"
//---------------------------------------------------------------------------
// �}�b�`�G���g�����ԃR�[�h�̊��N���X
class TKawariMatch_base {
public:

	virtual bool Evaluation(TKawariEngine *engine)=0;

	virtual void Debug(ostream& os,unsigned int level=0) const =0;

	ostream& DebugIndent(ostream& os,unsigned int level) const;

	virtual bool Less(const TKawariMatch_base& R_) const =0;

	virtual ~TKawariMatch_base() {}
};
//---------------------------------------------------------------------------
class TKawariMatch_baseP_Less {
public:
	bool operator()(const TKawariMatch_base *L,const TKawariMatch_base *R) const
	{
		if(typeid(*L)==typeid(*R)) return (L->Less(*R));
		return(string(typeid(*L).name())<string(typeid(*R).name()));
	}
};
//---------------------------------------------------------------------------
// �w��G���g�����Ɏw�蕶���񂪑S�Ċ܂܂�Ă���ΐ^
class TKawariMatchFind : public TKawariMatch_base {
private:

	string EntryName;

	vector<string> KeyWord;

public:

	void SetEntryName(const string& entry)
	{
		EntryName=entry;
	}

	void Add(const string& key)
	{
		KeyWord.push_back(key);
	}

	void Add(const vector<string>& key)
	{
		KeyWord.insert(KeyWord.end(),key.begin(),key.end());
	}

	virtual bool Evaluation(TKawariEngine *engine);

	virtual void Debug(ostream& os,unsigned int level=0) const;

	virtual bool Less(const TKawariMatch_base& R_) const;

};
//---------------------------------------------------------------------------
// NOT
class TKawariMatchNot : public TKawariMatch_base {
private:

	TKawariMatch_base *Match;

public:


	void Set(TKawariMatch_base *match)
	{
		Match=match;
	}

	virtual bool Evaluation(TKawariEngine *engine)
	{
		return(!Match->Evaluation(engine));
	}

	virtual void Debug(ostream& os,unsigned int level=0) const
	{
		DebugIndent(os,level) << "Not:" << endl;
		Match->Debug(os,level+1);
	}

	virtual bool Less(const TKawariMatch_base& R_) const
	{
		const TKawariMatchNot& R=dynamic_cast<const TKawariMatchNot&>(R_);
		return TKawariMatch_baseP_Less()(Match,R.Match);	// ���ʂ������̂�GCC2.95.2�̃o�O���
	}

	virtual ~TKawariMatchNot()
	{
		delete Match;
	}

};
//---------------------------------------------------------------------------
// AND
class TKawariMatchAnd : public TKawariMatch_base {
private:

	vector<TKawariMatch_base*> Match;

public:

	void Add(TKawariMatch_base *match)
	{
		Match.push_back(match);
	}

	void Add(const vector<TKawariMatch_base*>& match)
	{
		Match.insert(Match.end(),match.begin(),match.end());
	}

	virtual bool Evaluation(TKawariEngine *engine);

	virtual void Debug(ostream& os,unsigned int level=0) const;

	virtual bool Less(const TKawariMatch_base& R_) const;

	virtual ~TKawariMatchAnd();

};
//---------------------------------------------------------------------------
// OR
class TKawariMatchOr : public TKawariMatch_base {
private:

	vector<TKawariMatch_base*> Match;

public:

	void Add(TKawariMatch_base *match)
	{
		Match.push_back(match);
	}

	void Add(const vector<TKawariMatch_base*>& match)
	{
		Match.insert(Match.end(),match.begin(),match.end());
	}

	virtual bool Evaluation(TKawariEngine *engine);

	virtual void Debug(ostream& os,unsigned int level=0) const;

	virtual bool Less(const TKawariMatch_base& R_) const;

	virtual ~TKawariMatchOr();

};
//---------------------------------------------------------------------------
#endif

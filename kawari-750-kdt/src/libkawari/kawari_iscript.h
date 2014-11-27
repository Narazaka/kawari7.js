//---------------------------------------------------------------------------
//
// "�ؘa��" for ����ȊO�̉����ȊO�̉���
// �C�����C���X�N���v�g�G���W��
//
//      Programed by NAKAUE.T (Meister)
//
//  2001.05.24  Phase 5.1     �C���^�[�v���^�E�R���p�C����
//  2001.06.12  Phase 5.3.2   �_�~�[�R���e�L�X�g
//  2001.06.17  Phase 6.0     �C�����C���X�N���v�g���̗����Q�Ƃ̃o�O�C��
//  2001.07.21  Phase 6.2     �֐����Q��
//  2001.08.08  Phase 6.2     �֐��e�[�u���Q��
//
//---------------------------------------------------------------------------
#ifndef KAWARI_ISCRIPT_H
#define KAWARI_ISCRIPT_H
//---------------------------------------------------------------------------
#include "config.h"
//---------------------------------------------------------------------------
#include <string>
#include <vector>
#include <map>
using namespace std;
//---------------------------------------------------------------------------
class TKisEngine {
public:
	struct TContext {
		vector<string> TempDict;
	};

private:

	// �֐��e�[�u��
	map<string,class TKisFunction_base*> FunctionTable;

	// �֐����X�g
	vector<class TKisFunction_base*> FunctionList;

	// ����
	class TNS_KawariDictionary *KawariDictionary;

	// �G���W��
	class TKawariEngine *KawariEngine;

	vector<TContext*> ContextStack;


public:

	TKisEngine(class TNS_KawariDictionary *dict,class TKawariEngine *engine);
	~TKisEngine();

	// �֐����s
	string FunctionCall(const vector<string>& args);

	// ���s
	string Run(const vector<class TKawariCodeInlineScriptStatement*> codelist);

	// �^�U����
	bool IsTrue(const string &str)
	{
		return(!((str=="")||(str=="0")||(str=="false")));
	}


	// �R���e�L�X�g����
	void CreateContext(void)
	{
		ContextStack.push_back(new TContext);
	}

	// �_�~�[�R���e�L�X�g����
	void CreateNullContext(void)
	{
		ContextStack.push_back(NULL);
	}

	// �R���e�L�X�g�j��
	void DeleteContext(void)
	{
		if(ContextStack.size()) {
			if(ContextStack.back()) delete ContextStack.back();
			ContextStack.pop_back();
		}
	}

	// �R���e�L�X�g�擾
	TContext *Context(void)
	{
		if(ContextStack.size()==0) return(NULL);
		return(ContextStack.back());
	}

	// ���݂̃R���e�L�X�g�̃X�^�b�N�t���[���̃|�C���^���擾
	// (���[�����A�悤��MC68000��LINK��)
	unsigned int LinkContext(void)
	{
		if(Context()) return(Context()->TempDict.size());
		 else return(0);
	}

	// ���݂̃R���e�L�X�g�̃X�^�b�N�t���[���̃|�C���^�𕜋A
	// (���[�����A�悤��MC68000��UNLINK��)
	void UnlinkContext(unsigned int pos)
	{
		if(Context()) {
			if(pos<Context()->TempDict.size()) Context()->TempDict.resize(pos);
		}
	}


	// �����̎擾
	class TNS_KawariDictionary *Dictionary(void)
	{
		return(KawariDictionary);
	}

	// �G���W���̎擾
	class TKawariEngine *Engine(void)
	{
		return(KawariEngine);
	}


	// �֐����̎擾
	const TKisFunction_base* Function(const string& name)
	{
		if(FunctionTable.count(name)==0) return(NULL);
		return(FunctionTable[name]);
	}

	// �֐��e�[�u���̎擾
	const vector<class TKisFunction_base*>& GetFunctionTable(void)
	{
		return(FunctionList);
	}

};
//---------------------------------------------------------------------------
#endif

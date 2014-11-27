//---------------------------------------------------------------------------
//
// "�ؘa��" for ����ȊO�̉����ȊO�̉���
// �C�����C���X�N���v�g�G���W��
//
//      Programed by NAKAUE.T (Meister)
//
//  2001.05.24  Phase 5.1     �C���^�[�v���^�E�R���p�C����
//  2001.06.10  Phase 5.3.1   if�̃o�O�t�B�b�N�X
//  2001.06.17  Phase 5.4     foreach�ǉ�(by ��������)
//  2001.07.14  Phase 6.1     NULL�ǉ�
//  2001.07.21  Phase 6.2     foreach�ł̓R���e�L�X�g�𐶐�
//
//---------------------------------------------------------------------------
#include "config.h"
//---------------------------------------------------------------------------
#include <cstdlib>
using namespace std;
//---------------------------------------------------------------------------
#include "libkawari/kawari_iscript.h"
#include "libkawari/kawari_code.h"
#include "libkawari/kawari_engine.h"
#include "kis/kis_config.h"
//---------------------------------------------------------------------------
TKisEngine::TKisEngine(class TNS_KawariDictionary *dict,class TKawariEngine *engine)
 : KawariDictionary(dict),KawariEngine(engine)
{
	#define INLINE_SCRIPT_REGIST(T) \
	{ \
		TKisFunction_base *func=new T; \
		func->NotifyEngine(this); \
		if(func->Init()) { \
			FunctionTable[func->Name()]=func; \
			FunctionList.push_back(func); \
		} else delete func; \
	}

	#include "kis/kis_config.h"

	#undef INLINE_SCRIPT_REGIST
}
//---------------------------------------------------------------------------
TKisEngine::~TKisEngine()
{
	for(unsigned int i=0;i<FunctionList.size();i++) delete FunctionList[i];
}
//---------------------------------------------------------------------------
// �֐����s
string TKisEngine::FunctionCall(const vector<string>& args)
{
	if(FunctionTable.count(args[0])==0) return("");

	return(FunctionTable[args[0]]->Function(args));
}
//---------------------------------------------------------------------------
// ���s
string TKisEngine::Run(const vector<class TKawariCodeInlineScriptStatement*> codelist)
{
	unsigned int pc=0;

	string retstr;

	while(true) {
		if(pc>=codelist.size()) break;

		TKawariCodeInlineScriptStatement *code=codelist[pc];

		string result;

		// �ŏ��̃p�����[�^�����W�J����
		string arg0=code->GetArg0();

		// �u�\���̏����v

		if(arg0=="NULL") {
			result="";
		} else if(arg0=="if") {
			if((code->Code.size()==3)||(code->Code.size()==4)) {
				// �����̕]��(��1�p�����[�^)
				if(IsTrue(code->Code[1]->Run(this))) {
					// true�̎�(��2�p�����[�^)
					result=code->Code[2]->Run(this);
				} else {
					// false�̎�(��3�p�����[�^)
					if(code->Code.size()==4) result=code->Code[3]->Run(this);
				}
			} else {
				// �G���[
			}
		} else if(arg0=="while") {
			if(code->Code.size()==3) {
				// �����̕]��(��1�p�����[�^)
				while(IsTrue(code->Code[1]->Run(this))) {
					// true�̎�(��2�p�����[�^)
					CreateContext();	// �R���e�L�X�g����
					result+=code->Code[2]->Run(this);
					DeleteContext();	// �R���e�L�X�g�j��
				}
			} else {
				// �G���[
			}
		} else if(arg0=="until") {
			if(code->Code.size()==3) {
				// �����̕]��(��1�p�����[�^)
				while(!IsTrue(code->Code[1]->Run(this))) {
					// true�̎�(��2�p�����[�^)
					CreateContext();	// �R���e�L�X�g����
					result+=code->Code[2]->Run(this);
					DeleteContext();	// �R���e�L�X�g�j��
				}
			} else {
				// �G���[
			}
		} else if(arg0=="loop") {
			if(code->Code.size()==3) {
				// �񐔂̕]��(��1�p�����[�^)
				int limit=atoi(code->Code[1]->Run(this).c_str());
				for(int i=0;(i<limit)&&(limit>0);i++) {
					// ���s(��2�p�����[�^)
					CreateContext();	// �R���e�L�X�g����
					result+=code->Code[2]->Run(this);
					DeleteContext();	// �R���e�L�X�g�j��
				}
			} else {
				// �G���[
			}
		} else if(arg0=="foreach") {
			// foreach �����Ă��ꂽ�l�F��������
			if(code->Code.size()==4) {
				// �e���|�����G���g��(��1�p�����[�^)
				string tmpentryname=code->Code[1]->Run(this);
				// �񋓑Ώ�(��2�p�����[�^)
				string listrefname=code->Code[2]->Run(this);
				if(listrefname.size()) {
					TEntryID listref=KawariDictionary->GetEntryID(listrefname);
					vector<TWordID> wordcol;
					KawariDictionary->FindAll(listref,wordcol);
					for(unsigned int i=0;i<wordcol.size();i++) {
						TKawariCode_base *item=KawariDictionary->GetWordFromID(wordcol[i]);
						KawariEngine->InsertAfterClear(tmpentryname,item->Run(this));

						// ���s(��3�p�����[�^)
						CreateContext();	// �R���e�L�X�g����
						result+=code->Code[3]->Run(this);
						DeleteContext();	// �R���e�L�X�g�j��
					}
				}
			}else{
				// �G���[
			}
		} else if(arg0=="?") {
			if(code->Code.size()>1) {
				// ��1�p�����[�^�ȍ~�����I��
				unsigned int index=Random(code->Code.size()-1)+1;
				result+=code->Code[index]->Run(this);
			}
		} else if(arg0=="silent") {
			retstr="";
		} else {
			// �u�֐��v�̏���
			result=code->Run(this);
		}

		retstr+=result;
		pc++;
	}

	return(retstr);
}
//---------------------------------------------------------------------------


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
//  2001.06.10  Phase 5.3.1   ������
//  2001.06.17  Phase 5.4     save
//  2001.08.25  Phase 7.0     �Z�L�����e�B�΍�(WriteProtect)
//  2001.12.08  Phase 7.1.2   �e�L�X�g�t�@�C���ǂݍ��ݑΉ�
//
//---------------------------------------------------------------------------
#ifndef KAWARI_ENGINE_H
#define KAWARI_ENGINE_H
//---------------------------------------------------------------------------
#include "config.h"
//---------------------------------------------------------------------------
#include <set>
#include <string>
#include <vector>
#include <iostream>
using namespace std;
//---------------------------------------------------------------------------
// #include "libkawari/kawari_engine_base.h"
#include "libkawari/kawari_dict.h"
#include "libkawari/kawari_iscript.h"
#include "libkawari/kawari_matchdict.h"
#include "libkawari/kawari.h"
#include "saori/saori.h"
//---------------------------------------------------------------------------
class TKawariEngine {
private:

	// �����t�@�C���̃p�X��
	string DataPath;

	// ����
	TNS_KawariDictionary *Dictionary;

	// �X�N���v�g�G���W��
	TKisEngine *KisEngine;

	// �ؘa���t�H�[�}�b�g�t�@�C���̒P������߂��Ď擾
	TKawariCode_base *ParseKawariDict(TKawariLexer &buff,const string& localid);

	// �}�b�`�G���g��
	TNS_KawariMatchDictionary *MatchDictionary;

	set<TEntryID> ProtectedEntry;

	// �ؘa���C���^�[�t�F�[�X(���O�ւ̃A�N�Z�X�p)
	class TNS_KawariANI *Kawari;

	// SAORI
	class TSaoriPark *SaoriPark;
public:

	// ���nAPI

	// ���P�ꐔ���擾
	unsigned int WordCollectionSize(void) const
	{
		return(Dictionary->WordCollectionSize());
	}

	// �L���G���g�������擾
	unsigned int EntryCollectionSize(void) const
	{
		return(Dictionary->EntryCollectionSize());
	}

	// �}�b�`�G���g�������擾
	unsigned int MatchCollectionSize(void) const
	{
		return(MatchDictionary->Size());
	}


	// �����ǉ��E�폜�nAPI

	// ��������G���g�����Ŏg�p�\�ȕ�����ɃG���R�[�h����
	string EncodeEntryName(const string &orgsen) const;

	// �w�肳�ꂽ�G���g������ɂ���
	// �������ɋ�G���g���ƒP�ꂪ�c���Ă��ǂ�
	void ClearEntry(const string& entryname);

	// �����ւ̒P��̒ǉ�
	// ���ɒP�ꂪ���݂���ꍇ�ł��A����ɒǉ����� (���݂̎d�l)
	// ���ɒP�ꂪ���݂���ꍇ�ɂ́A�o���m����ύX���� (�����̎d�l)
	void Insert(const string& entryname,const string& word);

	// �w�肳�ꂽ�G���g������ɂ��Ă���P���ǉ�
	// �G���g����ϐ��I�ɗ��p���鎞�Ɏg�p����
	void InsertAfterClear(const string& entryname,const string& word);

	// �w�肳�ꂽ�G���g���ւ̏������݂��֎~����
	virtual void WriteProtect(const string& entryname);


	// �����nAPI

	// �w�肳�ꂽ�G���g���̐擪�̒P���Ԃ�
	// �߂�l : �P��̕�����
	string FindFirst(const string& entryname) const;

	// �w�肳�ꂽ�G���g���̒P��������_���ɑI�����ĕԂ�
	// �߂�l : �P��̕�����
	string RandomSelect(const string& entryname) const;

	// ���������̂�������}�b�`�G���g���̒P��������_���ɑI�����ĕԂ�
	// �߂�l : �P��̕�����
	string MatchEntryRandomSelect(const string& entryname) const;


	// �t�@�C��API

	// �����t�@�C���̃p�X����ݒ肷��
	void SetDataPath(const string &datapath)
	{
		DataPath=datapath;
	}

	// �����t�@�C���̃p�X�����擾����
	string GetDataPath(void) const
	{
		return(DataPath);
	}

	// �ؘa���t�H�[�}�b�g�����t�@�C����ǂݍ���
	// �߂�l : ������true
	bool LoadKawariDict(const string &filename);

	// �ؘa���t�H�[�}�b�g�����t�@�C������������
	// �߂�l : ������true
	bool SaveKawariDict(const string &filename,const vector<string>& entry,bool crypt=false) const;

	// �e�L�X�g�t�@�C����ǂݍ���
	// �߂�l : ������true
	bool LoadTextFile(const string &filename,const string &baseentry);


	// SAORI�֌WAPI

	enum SAORILOADTYPE {
		PRELOAD=TSaoriModule::PRELOAD,
		LOADONCALL,
		NORESIDENT
	};

	// SAORI���W���[���̓o�^
	void RegisterSAORIModule(const std::string &aliasname, const std::string &path, const SAORILOADTYPE type);

	// SAORI���W���[���o�^�̍폜
	void EraseSAORIModule(const std::string &aliasname);

	// SAORI���N�G�X�g���s��
	bool RequestToSAORIModule(
		const std::string &aliasname,
		const TPHMessage &request, TPHMessage &response);


	// �񋤒�API

	// �^����ꂽ�P������߂���
	string Parse(const string& word);

	// ���O�X�g���[���𓾂�
	ostream *GetLogStream(void);
public:

	TKawariEngine(TNS_KawariANI *kawari);
//	{
//		Dictionary=new TNS_KawariDictionary;
//		KisEngine=new TKisEngine(Dictionary,this);
//		MatchDictionary=new TNS_KawariMatchDictionary(Dictionary,this);
//		SaoriPark=new TSaoriPark();
//		Kawari=kawari;
//	}

	~TKawariEngine(){
		delete SaoriPark;
		delete Dictionary;
		delete KisEngine;
		delete MatchDictionary;
	}

};
//---------------------------------------------------------------------------
#endif


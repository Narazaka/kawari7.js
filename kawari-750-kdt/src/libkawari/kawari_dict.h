//---------------------------------------------------------------------------
//
// "�ؘa��" for ����ȊO�̉����ȊO�̉���
// ����
//
//      Programed by NAKAUE.T (Meister)
//
//  2001.04.21  Phase 0.50a1   �����Ǘ��̃N���X��
//  2001.05.03  Phase 0.50a4  �C�����C���X�N���v�g
//  2001.05.26  Phase 5.1     �C���^�[�v���^�E�R���p�C����
//                            API����
//  2001.06.17  Phase 6.0     �����G���g���ւ̓����ǉ��̃o�O�C��
//
//---------------------------------------------------------------------------
#ifndef KAWARI_DICT_H
#define KAWARI_DICT_H
//---------------------------------------------------------------------------
#include "config.h"
//---------------------------------------------------------------------------
#include <string>
#include <vector>
#include <map>
#include <set>
using namespace std;
//---------------------------------------------------------------------------
#include "libkawari/kawari_code.h"
#include "libkawari/wordcollection.h"
//---------------------------------------------------------------------------
// �P��ID
typedef unsigned int TWordID;
//---------------------------------------------------------------------------
// �G���g��ID
typedef unsigned int TEntryID;
//---------------------------------------------------------------------------
class TNS_KawariDictionary {
private:

	// ���ׂĂ̒P���ێ�����
	TWordPointerCollection<TKawariCode_base,TKawariCode_baseP_Less> WordCollection;

	// ���ׂẴG���g������ێ�����
	TWordCollection<string,less<string> > EntryCollection;

	// �������z�P��(PVW:PureVirtualWord)�ƃG���g���̑Ή��\

	map<TWordID,TEntryID> PVWToEntry;
	map<TEntryID,TWordID> EntryToPVW;

	// ����
	map<TEntryID,vector<TWordID> > Dictionary;

	// �t��������
	map<TWordID,multiset<TEntryID> > ReverseDictionary;


public:

	~TNS_KawariDictionary (){
	}
	// ���P�ꐔ���擾
	unsigned int WordCollectionSize(void) const;

	// �L���G���g�������擾
	unsigned int EntryCollectionSize(void) const;

	// �����񂩂璆�ԃR�[�h�c���[�𐶐�����
	TKawariCode_base *StringToCode(const string& word) const;


	// ID�ϊ��nAPI

	// �P��ID�擾
	// �߂�l : 1�I���W���A������Ȃ����0��Ԃ�
	TWordID GetWordID(TKawariCode_base* word) const;
	TWordID GetWordID(const string& word) const;

	// ID����P��ɕϊ�
	// �߂�l : ���ԃR�[�h�c���[
	TKawariCode_base *GetWordFromID(TWordID id) const;

	// �G���g��ID�擾
	// �߂�l : 1�I���W���A������Ȃ����0��Ԃ�
	TEntryID GetEntryID(const string& entry) const;


	// �����ǉ��E�폜�nAPI

	// �G���g���𐶐�����
	// ���ɃG���g�������݂���ꍇ�́A����������ID��Ԃ�
	// �߂�l : ���������G���g����ID
	TEntryID CreateEntry(const string& entry);

	// �w�肳�ꂽ�G���g������ɂ���
	// �������ɋ�G���g���ƒP�ꂪ�c��
	// �߂�l : ������true
	bool ClearEntry(TEntryID entry);

	// �����ւ̒P��̒ǉ�
	// ���ɒP�ꂪ���݂���ꍇ�ł��A����ɒǉ����� (���݂̎d�l)
	// ���ɒP�ꂪ���݂���ꍇ�ɂ́A�o���m����ύX���� (�����̎d�l)
	// ���ӁE���ɒP��ID�����P��ł������ꍇ�Adelete�����
	// �߂�l : �ǉ������P���ID
	TWordID Insert(TEntryID entry,TKawariCode_base* word);
	TWordID Insert(TEntryID entry,const string& word);
	TWordID Insert(TEntryID entry,TWordID id);

	// �w�肳�ꂽ�G���g������ɂ��Ă���P���ǉ�
	// ���ӁE���ɒP��ID�����P��ł������ꍇ�Adelete�����
	// �G���g����ϐ��I�ɗ��p���鎞�Ɏg�p����
	// �߂�l : �ǉ������P���ID
	TWordID InsertAfterClear(TEntryID entry,TKawariCode_base* word);
	TWordID InsertAfterClear(TEntryID entry,const string& word);


	// �����nAPI

	// �w�肳�ꂽ�G���g���̐擪�̒P���Ԃ�
	// �߂�l : �P���ID
	TWordID FindFirst(TEntryID entry) const;

	// �w�肳�ꂽ�G���g���̒P���S�ė�
	// �߂�l : �P��̌�
	unsigned int FindAll(TEntryID entry,vector<TWordID> &wordcol) const;

	// �w�肳�ꂽ�G���g���S�ĂɊ܂܂��P���
	// �������z�P��u${�G���g����}�v�̂ݓW�J���čċA�I�ɗ񋓂���
	// �߂�l : �P��̌�
	unsigned int GetWordCollection(TEntryID entry,set<TWordID> &wordcol) const;
	unsigned int GetWordCollection(const vector<TEntryID>& entrytable,set<TWordID> &wordcol) const;

};
//---------------------------------------------------------------------------
// ���P�ꐔ���擾
inline unsigned int TNS_KawariDictionary::WordCollectionSize(void) const
{
	return(ReverseDictionary.size());
}
//---------------------------------------------------------------------------
// �L���G���g�������擾
inline unsigned int TNS_KawariDictionary::EntryCollectionSize(void) const
{
	return(Dictionary.size());
}
//---------------------------------------------------------------------------
// �P��ID�擾
inline TWordID TNS_KawariDictionary::GetWordID(TKawariCode_base* word) const
{
	return(WordCollection.Find(word));
}
//---------------------------------------------------------------------------
// �G���g��ID�擾
inline TEntryID TNS_KawariDictionary::GetEntryID(const string& entry) const
{
	return(EntryCollection.Find(entry));
}
//---------------------------------------------------------------------------
// �w�肳�ꂽ�G���g������ɂ��Ă���P���ǉ�
inline TWordID TNS_KawariDictionary::InsertAfterClear(TEntryID entry,TKawariCode_base* word)
{
	ClearEntry(entry);
	return(Insert(entry,word));
}
//---------------------------------------------------------------------------
#endif

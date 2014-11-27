//---------------------------------------------------------------------------
//
// "�ؘa��" for ����ȊO�̉����ȊO�̉���
// �}�b�`�G���g������
//
//      Programed by NAKAUE.T (Meister)
//
//  2001.06.09  Phase 5.3     �}�b�`�G���g���Ď���
//
//---------------------------------------------------------------------------
#ifndef KAWARI_MATCHDICT_H
#define KAWARI_MATCHDICT_H
//---------------------------------------------------------------------------
#include "config.h"
//---------------------------------------------------------------------------
#include <string>
#include <vector>
#include <map>
using namespace std;
//---------------------------------------------------------------------------
#include "libkawari/kawari_engine_fwd.h"
#include "libkawari/kawari_matchcode.h"
#include "libkawari/wordcollection.h"
#include "libkawari/kawari_dict.h"
//---------------------------------------------------------------------------
class TNS_KawariMatchDictionary {
private:

	// �}�b�`�G���g��ID
	typedef unsigned int TMatchID;

	// ���ׂẴ}�b�`�G���g������ێ�����
//	TWordCollection<TKawariMatch_base*,TKawariMatch_baseP_Less> MatchCollection;
	TWordPointerCollection<TKawariMatch_base,TKawariMatch_baseP_Less> MatchCollection;

	// �}�b�`�G���g���ƃG���g���̑Ή��\
	map<TMatchID,TEntryID> MatchToEntry;
	map<TEntryID,TMatchID> EntryToMatch;

	// ����
	TNS_KawariDictionary *Dictionary;

	// �G���W��
	class TKawariEngine *Engine;

public:

	TNS_KawariMatchDictionary(TNS_KawariDictionary *dictionary,class TKawariEngine *engine);
//	TNS_KawariMatchDictionary(TNS_KawariDictionary *dictionary,class TKawariEngine *engine)
//	 : Dictionary(dictionary),Engine(engine)
//	{
//		MatchToEntry[0]=0;
//		EntryToMatch[0]=0;
//	}

	// �}�b�`�G���g�������擾
	unsigned int Size(void) const;

	// �}�b�`�G���g���̃G���g��ID�擾
	// �߂�l : 1�I���W���A������Ȃ����0��Ԃ�
	TEntryID GetMatchEntryID(TKawariMatch_base* match) const;

	// �}�b�`�G���g���𐶐�����
	// ���Ƀ}�b�`�G���g�������݂���ꍇ�́A����������ID��Ԃ�
	// �߂�l : ���������G���g����ID
	TEntryID CreateMatchEntry(TKawariMatch_base* match);

	// ������������������}�b�`�G���g����S�ė�
	// �߂�l : ������������������}�b�`�G���g���̌�
	unsigned int Evaluation(vector<TEntryID> &entrycol);

};
//---------------------------------------------------------------------------
// �R���X�g���N�^
inline TNS_KawariMatchDictionary::TNS_KawariMatchDictionary(TNS_KawariDictionary *dictionary,class TKawariEngine *engine)
{
	Dictionary=dictionary;
	Engine=engine;
	MatchToEntry[0]=0;
	EntryToMatch[0]=0;
}
//---------------------------------------------------------------------------
// �}�b�`�G���g�������擾
inline unsigned int TNS_KawariMatchDictionary::Size(void) const
{
	return(MatchCollection.Size());
}
//---------------------------------------------------------------------------
// �}�b�`�G���g���̃G���g��ID�擾
inline TEntryID TNS_KawariMatchDictionary::GetMatchEntryID(TKawariMatch_base* match) const
{
	return(MatchToEntry.find(MatchCollection.Find(match))->second);
}
//---------------------------------------------------------------------------
#endif


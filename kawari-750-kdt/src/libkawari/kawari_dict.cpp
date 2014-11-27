//---------------------------------------------------------------------------
//
// "�ؘa��" for ����ȊO�̉����ȊO�̉���
// ����
//
//      Programed by NAKAUE.T (Meister)
//
//  2001.04.21  Phase 0.50a1  �����Ǘ��̃N���X��
//  2001.05.03  Phase 0.50a4  �C�����C���X�N���v�g
//  2001.05.26  Phase 5.1     �C���^�[�v���^�E�R���p�C����
//                            API����
//  2001.06.17  Phase 5.4     �����G���g���ւ̓����ǉ��̃o�O�C��
//                            �t�R���p�C��
//  2001.12.16  Phase 7.2     ClearEntry(TEntryID entry)�̃o�O�C��
//                            (Thanks: ����)
//
//---------------------------------------------------------------------------
#include "config.h"
//---------------------------------------------------------------------------
#include "libkawari/kawari_dict.h"
//---------------------------------------------------------------------------
//#include <algorithm>
//using namespace std;
//---------------------------------------------------------------------------
#include "misc/misc.h"
//---------------------------------------------------------------------------
// �����񂩂璆�ԃR�[�h�c���[�𐶐�����
TKawariCode_base *TNS_KawariDictionary::StringToCode(const string& word) const
{
	TKawariLexer buff(word);

	vector<TKawariCode_base*> codelist;

	if(!TKawariCodeWord::Compile2(codelist,buff)) return(0);

	if(codelist.size()==1) return(codelist[0]);

	TKawariCodeWord *code=new TKawariCodeWord;
	code->Add(codelist);

	return(code);
}
//---------------------------------------------------------------------------
// �P��ID�擾
// �߂�l : 1�I���W���A������Ȃ����0��Ԃ�
TWordID TNS_KawariDictionary::GetWordID(const string& word) const
{
	TKawariCode_base *code=StringToCode(word);
	TWordID id=GetWordID(code);
	delete code;

	return(id);
}
//---------------------------------------------------------------------------
// ID����P��ɕϊ�
// �߂�l : ���ԃR�[�h�c���[
TKawariCode_base *TNS_KawariDictionary::GetWordFromID(TWordID id) const
{
	TKawariCode_base *const*word=WordCollection.Find(id);

	return(word?(*word):NULL);
}
//---------------------------------------------------------------------------
// �G���g���𐶐�����
// ���ɃG���g�������݂���ꍇ�́A����������ID��Ԃ�
// �߂�l : ���������G���g����ID
TEntryID TNS_KawariDictionary::CreateEntry(const string& entry)
{
	TEntryID id=0;
	EntryCollection.Insert(entry,&id);

	return(id);
}
//---------------------------------------------------------------------------
// �����ւ̒P��̒ǉ�
// ���ɒP�ꂪ���݂���ꍇ�ł��A����ɒǉ����� (���݂̎d�l)
// ���ɒP�ꂪ���݂���ꍇ�ɂ́A�o���m����ύX���� (�����̎d�l)
// �߂�l : �ǉ������P���ID
TWordID TNS_KawariDictionary::Insert(TEntryID entry,TKawariCode_base* word)
{
	if(!word) return(0);

	// �G���g�����̒P��̓R���e�L�X�g������
	word=word->CreateContext();

	TWordID id=0;
	if(!WordCollection.Insert(word,&id)) {
		// ���ɓo�^�ς݂̒P�ꂾ����
		delete word;
		word=GetWordFromID(id);
	}

	TKawariCodeEntryCall *macro=dynamic_cast<TKawariCodeEntryCall *>(word);
	if(macro) {
		// �ǉ�����̂͏������z�P��
		TEntryID child=CreateEntry(macro->Get());

		PVWToEntry[id]=child;
		EntryToPVW[child]=id;
	}

	Dictionary[entry].push_back(id);
	ReverseDictionary[id].insert(entry);

	return(id);
}
//---------------------------------------------------------------------------
TWordID TNS_KawariDictionary::Insert(TEntryID entry,const string& word)
{
	TKawariCode_base *code=StringToCode(word);
	TWordID id=Insert(entry,code);

	return(id);
}
//---------------------------------------------------------------------------
TWordID TNS_KawariDictionary::Insert(TEntryID entry,TWordID id)
{
	if(id==0) return(0);

	TKawariCode_base* word=GetWordFromID(id);
	if(word==NULL) return(0);

	TKawariCodeEntryCall *macro=dynamic_cast<TKawariCodeEntryCall *>(word);
	if(macro) {
		// �ǉ�����̂͏������z�P��
		TEntryID child=CreateEntry(macro->Get());

		PVWToEntry[id]=child;
		EntryToPVW[child]=id;
	}

	Dictionary[entry].push_back(id);
	ReverseDictionary[id].insert(entry);

	return(id);
}
//---------------------------------------------------------------------------
// �w�肳�ꂽ�G���g������ɂ���
// �������ɋ�G���g���ƒP�ꂪ�c��
// �߂�l : ������true
bool TNS_KawariDictionary::ClearEntry(TEntryID entry)
{
	if(Dictionary.count(entry)==0) return(false);

	// �t���������̏���
	for(unsigned int i=0;i<Dictionary[entry].size();i++) {
		unsigned int id=Dictionary[entry][i];
		ReverseDictionary[id].erase(
		 ReverseDictionary[id].lower_bound(entry));
	}

//	Dictionary[entry].clear();
	Dictionary.erase(entry);

	return(true);
}
//---------------------------------------------------------------------------
// �w�肳�ꂽ�G���g������ɂ��Ă���P���ǉ�
// �G���g����ϐ��I�ɗ��p���鎞�Ɏg�p����
// �߂�l : �ǉ������P���ID
TWordID TNS_KawariDictionary::InsertAfterClear(TEntryID entry,const string& word)
{
	TKawariCode_base *code=StringToCode(word);
	TWordID id=InsertAfterClear(entry,code);

	return(id);
}
//---------------------------------------------------------------------------
// �w�肳�ꂽ�G���g���̐擪�̒P���Ԃ�
// �߂�l : �P���ID
TWordID TNS_KawariDictionary::FindFirst(TEntryID entry) const
{
	if(Dictionary.count(entry)==0) return(0);

	return(Dictionary.find(entry)->second[0]);
}
//---------------------------------------------------------------------------
// �w�肳�ꂽ�G���g���̒P���S�ė�
// �߂�l : �P��̌�
unsigned int TNS_KawariDictionary::FindAll(TEntryID entry,vector<TWordID> &wordcol) const
{
	if(Dictionary.count(entry)==0) return(0);

	map<TEntryID,vector<TWordID> >::const_iterator it=Dictionary.find(entry);
	wordcol.insert(wordcol.end(),it->second.begin(),it->second.end());

	return(it->second.size());
}
//---------------------------------------------------------------------------
// �w�肳�ꂽ�G���g���S�ĂɊ܂܂��P���
// �������z�P��u${�G���g����}�v�̂ݓW�J���čċA�I�ɗ񋓂���
// �߂�l : �P��̌�
unsigned int TNS_KawariDictionary::GetWordCollection(TEntryID entry,set<TWordID> &wordcol) const
{
	if(Dictionary.count(entry)==0) return(0);


	// �ߋ��Ɍ����ς݂̃G���g��
	set<TEntryID> donelist;
	// �����\��̃G���g��
	vector<TEntryID> parselist;

	parselist.push_back(entry);

	while(parselist.size()) {
		TEntryID entryid=parselist.back();
		parselist.pop_back();
		if(donelist.count(entryid)) continue;

		donelist.insert(entryid);

		if(Dictionary.count(entryid)==0) continue;

		map<TEntryID,vector<TWordID> >::const_iterator it=Dictionary.find(entryid);
		for(unsigned int i=0;i<it->second.size();i++) {
			TWordID id=it->second[i];
			if(PVWToEntry.count(id)==0) {
				wordcol.insert(id);
			} else {
				// �������z�P��
				TEntryID child=PVWToEntry.find(id)->second;
				if(donelist.count(child)==0) parselist.push_back(child);
			}
		}
	}

	return(wordcol.size());
}
//---------------------------------------------------------------------------
unsigned int TNS_KawariDictionary::GetWordCollection(const vector<TEntryID>& entrytable,set<TWordID> &wordcol) const
{
	if(entrytable.size()==0) return(0);

	if(entrytable.size()==1) return(GetWordCollection(entrytable[0],wordcol));

	set<TWordID> collection[3];

	GetWordCollection(entrytable[0],collection[0]);

	for(unsigned int no=1;no<entrytable.size();no++) {
		unsigned int pre=(no*2-2)%3;
		unsigned int current=(no*2-1)%3;
		unsigned int next=(no*2)%3;
		collection[current].clear();
		GetWordCollection(entrytable[no],collection[current]);

		// �ȉ��ABorland C++ 5.5.1��set_intersection���o�O�����Ȃ̂�(iterator����̃o�O)

		set<TWordID>::iterator first1=collection[pre].begin();
		set<TWordID>::iterator first2=collection[current].begin();
		set<TWordID>::iterator last1=collection[pre].end();
		set<TWordID>::iterator last2=collection[current].end();
		set<TWordID> *result;

		if(no<(entrytable.size()-1)) {
			result=&collection[next];
		} else {
			result=&wordcol;
		}

		result->clear();
		while (first1 != last1 && first2 != last2) {
			if (*first1 < *first2) ++first1;
			 else if (*first2 < *first1) ++first2;
			 else {
				result->insert(*first1);
				++first1;
				++first2;
			}
		}
	}

	return(wordcol.size());
}
//---------------------------------------------------------------------------


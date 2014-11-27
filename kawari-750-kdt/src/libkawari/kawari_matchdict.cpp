//---------------------------------------------------------------------------
//
// "�ؘa��" for ����ȊO�̉����ȊO�̉���
// �}�b�`�G���g������
//
//      Programed by NAKAUE.T (Meister)
//
//  2001.06.09  Phase 5.3     �}�b�`�G���g���Ď���
//  2001.06.17  Phase 6.0     �}�b�`�G���g���̍Ō��ǂ܂Ȃ��o�O�C��
//
//---------------------------------------------------------------------------
#include "config.h"
//---------------------------------------------------------------------------
//using namespace std;
//---------------------------------------------------------------------------
#include "libkawari/kawari_matchdict.h"
#include "libkawari/kawari_engine.h"
#include "misc/misc.h"
//---------------------------------------------------------------------------
// �}�b�`�G���g���𐶐�����
// ���Ƀ}�b�`�G���g�������݂���ꍇ�́A����������ID��Ԃ�
// �߂�l : ���������G���g����ID
TEntryID TNS_KawariMatchDictionary::CreateMatchEntry(TKawariMatch_base* match)
{
	if(!match) return(0);

	TMatchID matchid=0;
	if(!MatchCollection.Insert(match,&matchid)) {
		// ���ɓo�^�ς݂̃}�b�`�G���g��������
		delete match;
		TKawariMatch_base *const*m=MatchCollection.Find(matchid);
		match=(m?*m:NULL);
	}

	TEntryID id=Dictionary->CreateEntry(string("system.match")+IntToString(matchid));

	MatchToEntry[matchid]=id;
	EntryToMatch[id]=matchid;

	return(id);
}
//---------------------------------------------------------------------------
// ������������������}�b�`�G���g����S�ė�
// �߂�l : ������������������}�b�`�G���g���̌�
unsigned int TNS_KawariMatchDictionary::Evaluation(vector<TEntryID> &entrycol)
{
	entrycol.clear();

	// TWordCollection�̗񋓕��@�͍čl�̗]�n����
	// TMatchID��1�I���W��
	for(unsigned int matchid=1;matchid<=MatchCollection.Size();matchid++) {
		TKawariMatch_base *const*match=MatchCollection.Find(matchid);
		if(!match) continue;

		if((*match)->Evaluation(Engine)) {
			entrycol.push_back(MatchToEntry[matchid]);
		}
	}

	return(entrycol.size());
}
//---------------------------------------------------------------------------


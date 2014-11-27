//---------------------------------------------------------------------------
//
// "�ؘa��" for ����ȊO�̉����ȊO�̉���
// �f�[�^�ێ��N���X
//
//      Programed by NAKAUE.T (Meister)
//
//  2001.04.24  Phase 0.5     ����
//  2001.05.26  Phase 5.1     �C���^�[�v���^�E�R���p�C�������ɔ���template��
//
//---------------------------------------------------------------------------
#ifndef WORDCOLLECTION_H
#define WORDCOLLECTION_H
//---------------------------------------------------------------------------
#include "config.h"
//---------------------------------------------------------------------------
#include <string>
#include <vector>
#include <map>
using namespace std;
//---------------------------------------------------------------------------
// �f�[�^��ێ���ID������U��N���X
template<class T,class Compare>
class TWordCollection {
protected:

	// �S�Ẵf�[�^
	// NULL�͖������ꂽ�f�[�^
	vector<T> WordList;

	// �f�[�^��ID�̑Ή��\
	// 0�͖������ꂽ�f�[�^
	typedef map<T,unsigned int,Compare> TWordIDMap;
	TWordIDMap WordIDMap;

public:

	// ���P�ꐔ���擾
	unsigned int Size(void) const
	{
		return(WordList.size());
	}

	// �f�[�^�̒ǉ�
	// ������true,ID��1�I���W��
	bool Insert(const T& word,unsigned int *id_=NULL);

	// �f�[�^�̖���
//	bool Delete(unsigned int id);


	// ID->�f�[�^
	const T* Find(unsigned int id) const;

	// �f�[�^->ID
	unsigned int Find(const T& word) const;

};

//---------------------------------------------------------------------------
// �|�C���^��ێ���ID������U��N���X
template<class T,class Compare>
class TWordPointerCollection : public TWordCollection<T*, Compare>{
public:
    ~TWordPointerCollection (){
        for (typename vector<T*>::iterator it=this->WordList.begin(); it < this->WordList.end(); it++){
            delete (*it);
        }
    }
};
//---------------------------------------------------------------------------
// �f�[�^�̒ǉ�
// �߂�l��ID (1�I���W��)
template<class T,class Compare>
bool TWordCollection<T,Compare>::Insert(const T& word,unsigned int *id_)
{
	unsigned int id=Find(word);
	if(id_) *id_=id;

	if(id!=0) return(false);

	this->WordList.push_back(word);
	id=this->WordList.size();

	WordIDMap[word]=id;

	if(id_) *id_=id;

	return(true);
}
//---------------------------------------------------------------------------
// ID->�f�[�^
template<class T,class Compare>
 const T* TWordCollection<T,Compare>::Find(unsigned int id) const
{
	if((id==0)||(this->WordList.size()<=(id-1))) return(NULL);

	return(&(this->WordList[id-1]));
}
//---------------------------------------------------------------------------
// �f�[�^->ID
template<class T,class Compare>
 unsigned int TWordCollection<T,Compare>::Find(const T& word) const
{
	typename TWordIDMap::const_iterator it=WordIDMap.find(word);

	return((it!=WordIDMap.end())?it->second:0);
}
//---------------------------------------------------------------------------
class TStringP_Less {
public:
	bool operator ()(const string *l,const string *r) const
	{
		return((*l)<(*r));
	}
};
//---------------------------------------------------------------------------
#endif

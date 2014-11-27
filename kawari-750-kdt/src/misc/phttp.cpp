//---------------------------------------------------------------------------
//
// TPHMessage - �UHTTP���b�Z�[�W -
//
//      Programed by Suikyo.
//
//---------------------------------------------------------------------------
#include "config.h"
//---------------------------------------------------------------------------
#include "misc/phttp.h"
//---------------------------------------------------------------------------
#include <strstream>
#include <iostream>
#include <string>
using namespace std;
//---------------------------------------------------------------------------
// �V���A���C�Y
string TPHMessage::Serialize(void) const{
	string ret=startline;
	ret+="\x0d\x0a";

	for(TPHMessage::const_iterator it=begin();it!=end();it++) {
		if(it->second.size())
			ret+=it->first+": "+it->second+"\x0d\x0a";
	}
	ret+="\x0d\x0a";
	return ret;
}
//---------------------------------------------------------------------------
// �f�V���A���C�Y
void TPHMessage::Deserialize(const string &mes){
	istrstream *ifs=new istrstream(mes.c_str());
	string buff;

	getline(*ifs,buff,'\x0a');
	if(buff[buff.size()-1]=='\x0d') buff.erase(buff.size()-1);	// 0x0d����菜��
	startline=buff;

	// �w�b�_�𕪉�����map�ɐς�
	while(getline(*ifs,buff,'\x0a')) {
		if(buff.size()==0) break;
		if(buff[buff.size()-1]=='\x0d') buff.erase(buff.size()-1);	// 0x0d����菜��
		if(buff.size()==0) break;

		unsigned int pos=buff.find(':');
		string key=buff.substr(0,pos);

		pos++;
		while(buff[pos]==' ') pos++;

		Add(key,buff.substr(pos));
	}

	delete ifs;
}
//---------------------------------------------------------------------------
// �_���v
void TPHMessage::Dump(ostream &os) const{
	os << startline << endl;
	for (TPHMessage::const_iterator it=begin(); it!=end(); it++){
		os << it->first << ": " << it->second << endl;
	}
	os << endl;
}
//---------------------------------------------------------------------------

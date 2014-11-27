//---------------------------------------------------------------------------
//
// ����ȊO�̉����ȊO�̉���
// SHIORI/2.4�C���^�[�t�F�[�X
//
//      Programed by NAKAUE.T (Meister)
//
//  2001.05.22  Phase 5.1     SHIORI/2.3�Ή�
//  2001.06.09  Phase 5.3     GET Version�΍�
//  2001.06.10  Phase 5.3.1   �o�[�W�����ԍ��ꊇ�Ǘ�
//  2001.07.10  Phase 6.0     getmoduleversion�ǉ�
//  2001.10.29  Phase 7.0.2   GET Version���ēxkawari.cpp�ֈڊ�
//
//---------------------------------------------------------------------------
#include "config.h"
//---------------------------------------------------------------------------
#include <string>
#include <strstream>
#include <cstdlib>
using namespace std;
//---------------------------------------------------------------------------
#include "shiori/shiori_interface.h"
#include "shiori/shiori_impl.h"	// �����Ńo�[�W�����ԍ�(SHIORIVER)���`
//---------------------------------------------------------------------------
static TShioriInterface *ShioriInterface=0;
//---------------------------------------------------------------------------
// �C���^�[�t�F�[�X�K�i�̃o�[�W�����ԍ���Ԃ�
string Shiori_GetVersion(void)
{
	return("SHIORI/"SHIORIVER);
}
//---------------------------------------------------------------------------
// �UAI���W���[���̃o�[�W�����ԍ���Ԃ�
string Shiori_GetModuleVersion(void)
{
	return(ShioriInterface->GetModuleVersion());
}
//---------------------------------------------------------------------------
// ���W���[���ǂݍ��ݎ��ɌĂ΂��
bool Shiori_Load(const string& dllpath)
{
	ShioriInterface=new TShioriInterface;

	return(ShioriInterface->Load(dllpath));
}
//---------------------------------------------------------------------------
// ���W���[���؂藣�����ɌĂ΂��
bool Shiori_Unload(void)
{
	bool status=ShioriInterface->Unload();

	delete ShioriInterface;

	return(status);
}
//---------------------------------------------------------------------------
// �UAI���N�G�X�g
string Shiori_Request(const string& requeststr)
{
	TMMap<string,string> requestdata;
	requestdata.Add("ORIGINAL",requeststr);		// �f�o�b�O�p

	istrstream *ifs=new istrstream(requeststr.c_str());
	string buff;
	string::size_type pos;

	// ���N�G�X�g�̎�ނ�؂�o��
	// ex. �uGET Sentence SHIORI/2.0�v->�uGET Sentence�v
	getline(*ifs,buff,'\x0a');
	pos=buff.find(" SHIORI/");
	string type=buff.substr(0,pos);

	string response;
	if(!ShioriInterface) {
		// �UAI������������Ă��Ȃ�
		response=Shiori_GetVersion()+" 500 Internal Server Error\x0d\x0a\x0d\x0a";
	} else {
		// ���N�G�X�g�w�b�_�𕪉�����map�ɐς�
		while(getline(*ifs,buff,'\x0a')) {
			if(buff.size()==0) break;
			if(buff[buff.size()-1]=='\x0d') buff.erase(buff.size()-1);	// 0x0d����菜��
			if(buff.size()==0) break;

			pos=buff.find(':');
			string key=buff.substr(0,pos);

			pos++;
			while(buff[pos]==' ') pos++;

			requestdata.Add(key,buff.substr(pos));
		}

		response=ShioriInterface->Request(type,requestdata);
	}

	delete ifs;

	return(response);
}
//---------------------------------------------------------------------------

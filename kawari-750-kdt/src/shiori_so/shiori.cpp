//---------------------------------------------------------------------------
//
// ����ȊO�̉����ȊO�̉���
// SharedObject�G���g��
// (�����������ˑ�)
//
//      Programed by NAKAUE.T (Meister)
//
//  2001.05.22  Phase 5.10    SHIORI/2.3�Ή�
//  2001.07.10  Phase 6.0     getmoduleversion�ǉ�
//
//---------------------------------------------------------------------------
#include "config.h"
//---------------------------------------------------------------------------
#include <string>
using namespace std;
//---------------------------------------------------------------------------
#include "shiori/shiori_interface.h"
//---------------------------------------------------------------------------
#define DLL_API extern "C"
//---------------------------------------------------------------------------
// �C���^�[�t�F�[�X�K�i�̃o�[�W�����ԍ���Ԃ�
DLL_API const char *getversion(void)
{
	static string verstr;

	verstr=Shiori_GetVersion();

	return(verstr.c_str());
}
//---------------------------------------------------------------------------
// �UAI���W���[���̃o�[�W�����ԍ���Ԃ�
DLL_API const char *getmoduleversion(void)
{
	static string verstr;

	verstr=Shiori_GetModuleVersion();

	return(verstr.c_str());
}
//---------------------------------------------------------------------------
// ���W���[���ǂݍ��ݎ��ɌĂ΂��
DLL_API int load(const char *datapath)
{
	return(Shiori_Load(datapath));
}
//---------------------------------------------------------------------------
// ���W���[���؂藣�����ɌĂ΂��
DLL_API int unload(void)
{
	return(Shiori_Unload());
}
//---------------------------------------------------------------------------
// �UAI���N�G�X�g
DLL_API char *request(const char *requeststr)
{
	string aistr=Shiori_Request(requeststr);

	char *reth=(char*)malloc(aistr.size());
	memcpy(reth,aistr.c_str(),aistr.size());

	return(reth);
}
//---------------------------------------------------------------------------

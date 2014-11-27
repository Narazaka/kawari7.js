//---------------------------------------------------------------------------
//
// "�ؘa��" for ����ȊO�̉����ȊO�̉���
// SAORI �C���^�[�t�F�[�X
//
//      Programed by Suikyo.
//
//  2002.04.15  Phase 8.0.0   ���т��킳��o�[�W�������Q�l�ɓ���
//
//---------------------------------------------------------------------------
#ifndef SAORI_WIN32_H
#define SAORI_WIN32_H
//---------------------------------------------------------------------------
#include <windows.h>
//---------------------------------------------------------------------------
#include "config.h"
//---------------------------------------------------------------------------
#include <string>
//---------------------------------------------------------------------------
// �����肽�񔛂�
class TSaoriBindingW32{
private:
	HMODULE	hModule;
	BOOL	(__cdecl *func_load)(HGLOBAL, long);
	HGLOBAL	(__cdecl *func_request)(HGLOBAL, long *);
	BOOL	(__cdecl *func_unload)();
	std::string dllpath;

	TSaoriBindingW32 ()
		: hModule(NULL), func_load(NULL), func_request(NULL), func_unload(NULL){}

	bool Load (const std::string &path);

public:

	// SAORI���W���[���̃��[�h
	// ����  path : ���L���C�u�����̐�΃p�X
	// �߂�l : ��������΃I�u�W�F�N�g�ւ̃|�C���^�B���s����NULL
	static TSaoriBindingW32 *Bind(const std::string &path){
		TSaoriBindingW32 *bind=new TSaoriBindingW32();
		if(bind->Load(path)){
			return bind;
		}else{
			delete bind;
			return NULL;
		}
	}

	// SAORI/1.0 request
	std::string Request(const std::string &request);

	// ���n���h���̃��C�u�����̃��[�h�J�E���g�𓾂�
	unsigned int GetLoadCount(void);

	// �A�����[�h
	~TSaoriBindingW32 ();
};
//---------------------------------------------------------------------------
#endif // SAORI_WIN32_H

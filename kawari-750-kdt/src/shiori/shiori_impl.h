//---------------------------------------------------------------------------
//
// ����ȊO�̉����ȊO�̉���
// shiori.dll�C���^�[�t�F�[�X
//
//      Programed by NAKAUE.T (Meister)
//
//  2001.02.03  Phase 0.3     �m�[�R�����g
//  2001.03.15  Phase 0.42    unload�\��
//  2001.04.25  Phase 0.50a1  inverse
//  2001.04.27  Phase 0.50a2  SHIORI/2.1�Ή�
//  2001.05.12  Phase 0.50    SHIORI/1.1�؂�̂�
//  2001.07.10  Phase 6.0     getmoduleversion�ǉ�
//
//---------------------------------------------------------------------------
#ifndef SHIORI_IMPL_H
#define SHIORI_IMPL_H
//---------------------------------------------------------------------------
#include "config.h"
//---------------------------------------------------------------------------
#if 0
// ����Ȃ̗p�ӂ��Ă�������
#define SHIORIVER	"2.0"
#include <string>
using namespace std;
class TNS_ANI {
public:
	// SHIORI/2.0 API

	// DLL���[�h���ɌĂ΂��
	// const string& datapath : DLL�̃f�B���N�g���p�X
	// �߂�l bool : ������true
	bool Load(const string& datapath);

	// DLL�A�����[�h���ɌĂ΂��
	// �߂�l bool : ������true
	bool Unload(void);

	// �UAI���N�G�X�g
	// const string& type : ���N�G�X�g�̎��
	// const map<string,string>& request : ���N�G�X�g�w�b�_
	// �߂�l string : ���X�|���X�f�[�^
	string Request(const string& type,const map<string,string>& request);


	// SHIORI for POSIX 2.4

	// �UAI���W���[���̃o�[�W�����ԍ���Ԃ�
	// �߂�l string : "��{����[.�⏕����[.�⏕����]]/�o�[�W�����ԍ�"
	// ex. "KAWARI/6.0"         �ؘa�� Phase6.0
	// ex. "KAWARI.sky/5.4.1"   ������ �ؘa�� Phase5.4��
	string GetModuleVersion(void);

};
#endif
//---------------------------------------------------------------------------
// �g�p����N���X��ύX����Ƃ��͈ȉ�������������
#include "libkawari/kawari.h"
#define TShioriInterface TNS_KawariANI
//---------------------------------------------------------------------------
#endif

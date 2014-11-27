//---------------------------------------------------------------------------
//
// "�ؘa��" for ����ȊO�̉����ȊO�̉���
// �UAI��p�i
//
//      Programed by NAKAUE.T (Meister)
//
//  2001.02.03  Phase 0.3     �m�[�R�����g
//  2001.02.11  Phase 0.31    �ċA��`����
//  2001.02.23  Phase 0.4     ���_�푈�I��F�O
//                            �`���炩�ɂ����艺�����A�߂��͌J��Ԃ��܂���`
//                                                                �o�[�W����
//                            kawari.ini����
//                            ���������t�@�C��
//                            sentence.txt�p�~
//  2001.03.15  Phase 0.42    unload�\��
//  2001.04.25  Phase 0.50a1  ���X�|���X�Ή�
//  2001.04.27  Phase 0.50a2  SHIORI/2.1�Ή�
//  2001.04.28  Phase 0.50a3  COMMUNICATE�푈
//       |
//  2001.05.02
//  2001.05.03  Phase 0.50a4  �C�����C���X�N���v�g
//  2001.05.12  Phase 0.50    Piroject-X ������
//                            SHIORI/2.2�Ή�
//                            SHIORI/1.1�؂�̂�
//  2001.05.27  Phase 5.1     �C���^�[�v���^�E�R���p�C����
//  2001.05.31  Phase 5.2     �ێ�Ipiro
//  2001.06.10  Phase 5.3.1   GET Version�΍�
//                            �USHIORI/2.4���� (^_^;
//  2001.06.18  Phase 5.4     �C�����C���X�N���v�g�啝����
//  2001.07.10  Phase 6.0     getmoduleversion�ǉ�
//  2001.07.14  Phase 6.1     BCC�������Q����΍�
//  2001.07.19  Phase 6.2     SHIORI/2.5����
//  2001.08.08  Phase 6.2     �K���p��LoadSub��V��
//  2001.08.25  Phase 6.3     �Z�L�����e�B�[�z�[���΍�
//  2001.08.25  Phase 7.0     �Z�L�����e�B�΍�(WriteProtect)
//  2001.09.23  Phase 7.0.1   �Z�L�����e�B�΍��redo34�ȍ~�̕����ɑΉ�
//                            Sender�o�H���ǉ�(System.Sender.Path)
//                            3�G���g���ȏ�ł�AND�����o�O���C��
//                            SHIORI/2.3b�Ή�
//                            �C�����C���X�N���v�g����
//                            �N�����x�̍�����
//                            �n�C�t�����g�p���鋌�G���g���̑Ή���~
//  2001.10.29  Phase 7.0.2   GhostEx�w�b�_�Ή�
//                            GET Version���ēxkawari.cpp�Ɉڊ�
//                            SHIORI/2.6���Ή�(����Shift_JIS�ɌŒ�)
//                            �����C�x���g�ǉ�(OnEventUnknown)
//  2001.10.31  Phase 7.0.3   SecurityLevel�w�b�_�Ή�
//  2001.11.21  Phase 7.1     �G���g�������_���Ăяo���̃o�O�C��
//                            �[��������MT�A���S���Y�����̗p
//  2001.11.25  Phase 7.1.1   �����_���̏����l�Ɏ������g���悤�ύX
//                            [�K��] help�R�}���h�̃��b�Z�[�W��(�R�L��)�p���
//                            SecurityLevel��0�`3�ɕύX(4��p�~)
//  2001.12.08  Phase 7.1.2   kawari.ini�Ńe�L�X�g�t�@�C���ǂݍ��ݑΉ�
//  2001.12.16  Phase 7.2     TMMap�̒l����������o�O���C��
//                            (Thanks: ���́A����)
//  2002.01.07  Phase 7.3     ����ҕ\���p�w�b�_�ǉ�(Thanks: ���т���)
//                            �`�B�o�H����SecurityLevel�݂̂Ŕ���
//  2002.01.08  Phase 7.3.1   BalloonOffset�w�b�_�Ή�
//  2002.05.07  Phase 7.4.0   �C��BSD���C�Z���X�ɓ���
//  2003.02.16  Phase 7.5.0   I18N(Thanks:Sanori,whoami)
//
//---------------------------------------------------------------------------
#ifndef KAWARI_H
#define KAWARI_H
//---------------------------------------------------------------------------
// �ؘa���̃o�[�W�����ԍ��͂����ɏ���
#define KAWARI_NAME	"KAWARI.kdt.i18n"
#define KAWARI_AUTHOR	"KawariDevelopmentTeam"	// �����(�p��������)
//#define KAWARI_NAME	"KAWARI.sky"
#define KAWARI_MAJOR	"7"		// ���W���[�ԍ�(�s���I�h�����A��������)
#define KAWARI_MINOR	"5"		// �}�C�i�[�ԍ�(�s���I�h�����A��������)
#define KAWARI_SUBMINOR	"0"		// ����Ƀ}�C�i�[(�s���I�h�����A��������)
//---------------------------------------------------------------------------
#include "config.h"
//---------------------------------------------------------------------------
#include <string>
#include <vector>
#include <map>
#include <fstream>
using namespace std;
//---------------------------------------------------------------------------
#include "libkawari/kawari_engine.h"
#include "misc/phttp.h"
#include "misc/mmap.h"
//---------------------------------------------------------------------------
#define SHIORIVER	"2.6"
//---------------------------------------------------------------------------
#define SENDER_SYSTEM	0
#define SENDER_LOCAL	1
#define SENDER_UNKNOWN	2
#define SENDER_EXTERNAL	3
//---------------------------------------------------------------------------
class TNS_KawariANI {
private:
public:

	// �ؘa���G���W��
	TKawariEngine *Engine;

	// ���O�t�@�C���o�͗p
	ofstream *LogFS;

	// ���ʗp�̃S�[�X�g��
	// NOTIFY�ő����Ă��閼�O
	string GhostName;

	// ���̃S�[�X�g�̃��X�g
	set<string> OtherGhostName;
	// ���̃S�[�X�g�̃��X�g(�T�[�t�F�X�ԍ��t)
	set<string> OtherGhostExName;

	// �Z�L�����e�B���x��
	class TSecurityLevel {
	private:
		unsigned int Level;
	public:
		// �Z�L�����e�B���x����ݒ肷��
		// 3 : LOCAL��������
		// 2 : LOCAL, UNKNOWN��������
		// 1 : (�\��,�Ƃ肠����2�Ɠ���)
		// 0 : LOCAL, UNKNOWN, EXTERNAL��������
		bool Set(unsigned int lv)
		{
			Level=(lv<=3)?lv:Level;
			return(Level==lv);
		}

		unsigned int Get(void)
		{
			return(Level);
		}

		// Sender��������Ă��邩�ǂ����`�F�b�N����
		bool Check(const unsigned int path)
		{
			switch(Level) {
//			case 4: return(path==SENDER_SYSTEM);
			case 3: return(path==SENDER_LOCAL);
			case 2: return(path<=SENDER_UNKNOWN);
			case 1: return(path<=SENDER_UNKNOWN);
			case 0: return(path<=SENDER_EXTERNAL);
			default: return(path<=SENDER_UNKNOWN);
			}
		}

		TSecurityLevel(unsigned int lv)
		{
			Set(lv);
		}
	} SecurityLevel;


	// ���N�G�X�g�ɉ����ĕԓ����𐶐�����
	unsigned int RequestGetSentence(TMMap<string,string>& request,map<string,string> &response);

	// Communicate�̑����T��
	bool SearchCommunicateTarget(const string &targetghost,map<string,string> &response);

	// �G���g���Ɉ�v���郉���_���P���Ԃ�
	string GetSentence(const string& key);

	// ���͂ɕԓ����郉���_���P���Ԃ�
	string GetResponse(string sentence);

	// �f�[�^�t�@�C���ǂݍ���
	bool LoadFile(const string &filename,const string &type);

	// SAKURA�t�H�[�}�b�g�f�[�^�t�@�C���ǂݍ���
	bool LoadSakuraFile(const string &filename,const string &type);

	// ini�t�@�C���ǂݍ���
	bool LoadINI(const string &filename,const string &datapath,vector<string> &dictfiles);


public:

	TNS_KawariANI(void);

	~TNS_KawariANI();

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
	// const TMMap<string,string>& request : ���N�G�X�g�w�b�_
	// �߂�l string : ���X�|���X�f�[�^
	string Request(const string& type,TMMap<string,string>& request);


	// SHIORI for POSIX 2.4

	// �UAI���W���[���̃o�[�W�����ԍ���Ԃ�
	// �߂�l string : "��{����[.�⏕����[.�⏕����]]/�o�[�W�����ԍ�"
	// ex. "KAWARI/6.0"         �ؘa�� Phase6.0
	// ex. "KAWARI.sky/5.4.1"   ������ �ؘa�� Phase5.4��
	string GetModuleVersion(void)
	{
		return(KAWARI_NAME "/" KAWARI_MAJOR "." KAWARI_MINOR "." KAWARI_SUBMINOR);
	}


	// �K���p

	// �������ƃt�@�C���ǂݍ���
	// const string& datapath : DLL�̃f�B���N�g���p�X
	// const string& inifile : kawari.ini�t�@�C���̃p�X
	// �߂�l bool : ������true
	bool LoadSub(const string& datapath,const string& inifile);

};
//---------------------------------------------------------------------------
#endif

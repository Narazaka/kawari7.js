//---------------------------------------------------------------------------
//
// "�ؘa��" for ����ȊO�̉����ȊO�̉���
// �R���p�C���ˑ�
//
//      Programed by NAKAUE.T (Meister)
//
// ���̂���autoconf�ɑΉ��������肷��̂��낤��?
//
//---------------------------------------------------------------------------
#ifndef CONFIG_H
#define CONFIG_H
//---------------------------------------------------------------------------
#ifdef _MSC_VER

	// STL���g���ƕK���o�鎯�ʖ�255������Warning��}��
	#pragma warning(disable:4786)

	// for�̃X�R�[�v��ANSI�ɏ������Ă��Ȃ����΍�(���N�l�Ă̎�@)
	// �Q�l���� http://www.ksky.ne.jp/~seahorse/cpp/loopvar.html
	#ifndef for
	#define for if(0);else for
	#endif

	// cstdlib����std���O��Ԃ��g���Ă��Ȃ����߂ɋN����G���[��}��
	namespace std{}

	// POSIX opendir/readdir/closedir���������߁A��֕i�̎w��
	#define NOHAVE_READDIR

#endif
//---------------------------------------------------------------------------
#ifdef __BORLANDC__
	// BCC��vector�̓f�t�H���g�ōŏ���1KB�������[���m�ۂ���̂�
	// �������[�g�p��������������
	// �Q�� : BCC5.5.1 memory.stl��111�s�ڕt��
	#define _RWSTD_CONTAINER_BUFFER_SIZE 4
	
	#define STRING_APPEND_INATOMIC
#endif
//---------------------------------------------------------------------------
#ifdef __MINGW32__
# if defined(_WIN32)
	// ���̃w�b�_������� windows.h ��ǂݍ��� 
	// �i�łȂ��Ɛ����o�C�i������O�ŗ�����݂����Ȃ̂Łj 
# include <windows.h>
# endif
	#define STRING_APPEND_INATOMIC
#endif
//---------------------------------------------------------------------------
#endif


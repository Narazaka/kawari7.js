//---------------------------------------------------------------------------
/**
  * @brief		SHIORI/2.0 �UAI���W���[�� �C���|�[�g�w�b�_�t�@�C��
  *				���̃t�@�C����PDS(Public Domain Software)�Ƃ���B
  *
  * �u�x�v�Ƃ́A�u�f���B�v�p�UAI���W���[���K�i�̖��̂ł���B
  * �x�K�i�́AHTTP�ɍ����������N�G�X�g�E���X�|���X�^���b�Z�[�W���O�����Ƃ���
  * �a�������f���ł���A�UAI���W���[�������u�x�T�[�o�v�A����𗘗p���鑤��
  * �u�x�N���C�A���g�v�ƌĂԁB
  *
  * API���A�󂯓n���ɗp�����郁�����̈�́A�v���b�g�t�H�[���ˑ��̗̈�m��
  * �֐��Ŋm�ۂ���A�󂯎�葤���������B
  * �̈�m�ہA����ɗp����֐��͈ȉ��B
  * Win32�v���b�g�t�H�[�� : GlobalAlloc(GMEM_FIXED, len), GlobalFree()
  * POSIX�v���b�g�t�H�[�� : malloc(len), free()
  *	                        (�������A�N���C�A���g�ŗLC���C�u�����ˑ�)
  */
//
//  2003.02.25                �쐬 <suikyo@yk.rim.or.jp>
//
//---------------------------------------------------------------------------
#ifndef SHIORI_H__
#define SHIORI_H__
//-------------------------------------------------------------------------
#if defined(WIN32)||defined(_WIN32)||defined(_Windows)||defined(__CYGWIN__)
// Win32
#	include <windows.h>
#	ifdef __BORLANDC__
// 		Borland C++
#		define SHIORI_EXPORT	extern "C"
#	else
// 		Visual C++ / Cygwin32 / Mingw32
#		define SHIORI_EXPORT	extern "C" __declspec(dllexport)
#	endif
#	define SHIORI_CALL			__cdecl
#	define MEMORY_HANDLE		HGLOBAL
#	define SHIORI_MALLOC(len)	::GlobalAlloc(GMEM_FIXED, len)
#	define SHIORI_FREE(ptr)		::GlobalFree((HGLOBAL)ptr)
#else
// Other Platform
#	define SHIORI_EXPORT		extern "C"
#	define SHIORI_CALL
#	define MEMORY_HANDLE		char *
#	define SHIORI_MALLOC(len)	malloc(len)
#	define SHIORI_FREE(ptr)		free((void *)ptr)
#endif
#ifndef BOOL
#	define BOOL					int
#	define TRUE					1
#	define FALSE				0
#endif
//---------------------------------------------------------------------------
/**
  * @brief		���W���[���ǂݍ��ݒ���ɌĂ΂��
  *
  * @param h	(I) DLL�t�@�C�������݂���f�B���N�g���p�X��\��������ւ�
  *				�|�C���^�B�������̈�͞x�T�[�o��������邱�ƁB
  * @param len	(I) h������������̒���
  * @return		�����̂Ƃ��ATRUE�B���s�̂Ƃ��AFALSE�B
  */
SHIORI_EXPORT BOOL SHIORI_CALL load(const MEMORY_HANDLE h,long len);
//---------------------------------------------------------------------------
/**
  * @brief		���W���[���؂藣�����O�ɌĂ΂��
  *
  * @return		�����̂Ƃ��ATRUE�B���s�̂Ƃ��AFALSE�B
  */
SHIORI_EXPORT BOOL SHIORI_CALL unload(void);
//---------------------------------------------------------------------------
/**
  * @brief		�UAI���N�G�X�g
  *
  * @param h	(I) �v��������ւ̃|�C���^�B�x�T�[�o��������邱�ƁB
  * @param len	(IO) �Ăяo�����͗v���������byte�����i�[����A�ԓ��������
  *				byte�����i�[����ĕԂ�B
  * @return		�ԓ�������ւ̃|�C���^�B�x�T�[�o���m�ۂ��A�x�N���C�A���g��
  *				������邱�ƁB
  */
SHIORI_EXPORT MEMORY_HANDLE SHIORI_CALL request(const MEMORY_HANDLE h,long *len);
//---------------------------------------------------------------------------
#endif // SHIORI_H__
//---------------------------------------------------------------------------

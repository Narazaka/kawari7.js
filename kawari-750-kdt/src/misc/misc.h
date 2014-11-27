//---------------------------------------------------------------------------
//
// �G�p
//
//      Programed by NAKAUE.T (Meister)
//
//---------------------------------------------------------------------------
#ifndef MISC_H
#define MISC_H
//---------------------------------------------------------------------------
#include "config.h"
//---------------------------------------------------------------------------
#include <string>
#include <cstdlib>
using namespace std;
//---------------------------------------------------------------------------
#include "misc/mt19937ar.h"
//---------------------------------------------------------------------------
extern TMTRandomGenerator MTRandomGenerator;
//---------------------------------------------------------------------------
// 0����num-1�܂ł̗����𔭐�
inline int Random(int num)
{
	return((int)(MTRandomGenerator.genrand_real2()*num));
}
//---------------------------------------------------------------------------
// �����̃V�[�h��ݒ�
inline void SRandom(int seed)
{
	MTRandomGenerator.init_genrand((unsigned long)seed);
}
//---------------------------------------------------------------------------
// ������̑O��̋󔒂���菜��
inline string StringTrim(const string& str)
{
	string::size_type linetop=str.find_first_not_of(" \t\r\n");
//	string::size_type lineend=str.find_last_not_of(" \t\r\n");
	string::size_type lineend=str.find_last_not_of('\0');
	lineend=str.find_last_not_of(" \t\r\n",lineend);
	if(linetop==string::npos) return(string(""));

	return(str.substr(linetop,lineend-linetop+1));
}
//---------------------------------------------------------------------------
// 2�o�C�g������1�o�C�g�ڂ�?
inline bool iskanji1st(char c)
{
#if 1
	// SJIS
	// 0x00-0x7f ASCII
	// 0x80-0x9f,0xe0-0xfc ������S�p1�o�C�g��
	// 0xa0-0xdf �����锼�p�J�i
	return((unsigned char)((c^0x20)-0xa1)<=0x3b);
	// ���Ȃ݂�2�o�C�g�ڂ�0x40-0xfc
#else
	// EUC
	return(c<0);
#endif
}
//---------------------------------------------------------------------------
// �����l���當����𓾂�
string IntToString(int n);
//---------------------------------------------------------------------------
#endif

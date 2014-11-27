//---------------------------------------------------------------------------
//
// "�ؘa��" for ����ȊO�̉����ȊO�̉���
// �Í���/������
//
//      Programed by NAKAUE.T (Meister)
//
//  2001.03.15  Phase 0.42    �Í�������
//
//---------------------------------------------------------------------------
#include "config.h"
//---------------------------------------------------------------------------
#include "libkawari/kawari_crypt.h"
#include "misc/base64.h"
//---------------------------------------------------------------------------
// �Í����`�����m�F����
bool CheckCrypt(const string& encodedstr)
{
	string id=encodedstr.substr(0,9);
	return(id=="!KAWA0000");
}
//---------------------------------------------------------------------------
// �W���Í���
string EncryptString(const string& str)
{
	string encodedstr;

	for(unsigned int i=0;i<str.size();i++) {
		encodedstr+=str[i]^0xcc;
	}

	return(string("!KAWA0000")+EncodeBase64(encodedstr));
}
//---------------------------------------------------------------------------
// �W��������
#if defined(STRING_APPEND_INATOMIC)
string DecryptString(const string& encodedstr)
{
	// long int = 32bit �ł��邱�ƂɈˑ������R�[�f�B���O�ɂȂ��Ă܂� 
	string str=DecodeBase64(encodedstr.substr(9));

	unsigned cnt = str.size();
	string decodedstr;
	
	char *s = new char[cnt + 4];
	
	str.copy(s, cnt);
	
	for(unsigned int i=0;i<cnt ;i += 4) {
		*(unsigned long *)(s + i) ^= 0xccccccccUL;
	}

	decodedstr.assign(s, cnt);
	delete[] s;
	return(decodedstr);
}
#else
string DecryptString(const string& encodedstr)
{
	string str=DecodeBase64(encodedstr.substr(9));

	string decodedstr;
	for(unsigned int i=0;i<str.size();i++) {
		decodedstr+=str[i]^0xcc;
	}

	return(decodedstr);
}
#endif
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//
// ����ȊO�̉����ȊO�̉���
// DLL�G���g��
// (�����������ˑ�)
//
//      Programed by NAKAUE.T (Meister)
//
//  2001.02.03  Phase 0.3     �m�[�R�����g
//  2001.03.15  Phase 0.42    construct/destruct�̎g�p���~�߂�
//  2001.04.25  Phase 0.50a1  inverse
//  2001.04.27  Phase 0.50a2  SHIORI/2.1�Ή�
//  2001.05.09  Phase 0.50    SHIORI/2.2�Ή�
//  2001.05.22  Phase 5.10    SHIORI/2.3�Ή�
//  2001.07.10  Phase 6.0     Cygwin�Ή�
//  2001.07.10  Phase 6.1     getmoduleversion�ǉ�
//  2001.07.19  Phase 6.2     Mingw�Ή�
//  2002.01.07  Phase 7.3     getversion�폜(����ҕ\���΍�)
//
//---------------------------------------------------------------------------
#include <windows.h>	// Mingw�΍�Ő^�����include
//---------------------------------------------------------------------------
#include "config.h"
//---------------------------------------------------------------------------
#include <string>
using namespace std;
//---------------------------------------------------------------------------
#include "shiori/shiori_interface.h"
//---------------------------------------------------------------------------
#ifdef __BORLANDC__
	// Borland C++
	#define DLL_API extern "C"
#else
	// Visual C++ / Cygwin32 / Mingw32
	#define DLL_API extern "C" __declspec(dllexport)
#endif
//---------------------------------------------------------------------------
// �C���^�[�t�F�[�X�K�i�̃o�[�W�����ԍ���Ԃ�
#if 0
DLL_API HGLOBAL __cdecl getversion(long *len)
{
	string verstr=Shiori_GetVersion();

	*len=verstr.size();
	HGLOBAL reth;
	reth=GlobalAlloc(GMEM_FIXED,*len);
	memcpy(reth,verstr.c_str(),*len);

	return(reth);
}
#endif
//---------------------------------------------------------------------------
// �UAI���W���[���̃o�[�W�����ԍ���Ԃ�
DLL_API HGLOBAL __cdecl getmoduleversion(long *len)
{
	string verstr=Shiori_GetModuleVersion();

	*len=verstr.size();
	HGLOBAL reth;
	reth=GlobalAlloc(GMEM_FIXED,*len);
	memcpy(reth,verstr.c_str(),*len);

	return(reth);
}
//---------------------------------------------------------------------------
// ���W���[���ǂݍ��ݎ��ɌĂ΂��
DLL_API BOOL __cdecl load(HGLOBAL h,long len)
{
	string datapath((char*)h,len);
	GlobalFree(h);

	return(Shiori_Load(datapath));
}
//---------------------------------------------------------------------------
// ���W���[���؂藣�����ɌĂ΂��
DLL_API BOOL __cdecl unload(void)
{
	return(Shiori_Unload());
}
//---------------------------------------------------------------------------
// �UAI���N�G�X�g
DLL_API HGLOBAL __cdecl request(HGLOBAL h,long *len)
{
	string requeststr((char*)h,*len);
	GlobalFree(h);

	string aistr=Shiori_Request(requeststr);

	*len=aistr.size();
	HGLOBAL reth;
	reth=GlobalAlloc(GMEM_FIXED,*len);
	memcpy(reth,aistr.c_str(),*len);

	return(reth);
}
//---------------------------------------------------------------------------

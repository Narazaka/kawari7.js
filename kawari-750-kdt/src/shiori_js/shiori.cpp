//---------------------------------------------------------------------------
//
// ����ʳ��β����ʳ��β���
// ��ͭ�饤�֥�ꥨ��ȥ�
//
//      Programed by NAKAUE.T (Meister)
//
//  2001.02.03  Phase 0.3     �Ρ�������
//  2001.03.15  Phase 0.42    construct/destruct�λ��Ѥ�ߤ��
//  2001.04.25  Phase 0.50a1  inverse
//  2001.04.27  Phase 0.50a2  SHIORI/2.1�б�
//  2001.05.09  Phase 0.50    SHIORI/2.2�б�
//  2001.05.22  Phase 5.10    SHIORI/2.3�б�
//  2001.07.10  Phase 6.0     Cygwin�б�
//  2001.07.10  Phase 6.1     getmoduleversion�ɲ�
//  2001.07.19  Phase 6.2     Mingw�б�
//  2002.01.07  Phase 7.3     getversion���(�����ɽ���к�)
//  2014.11.24  Phase 7.3em   emscripten
//
//---------------------------------------------------------------------------
//#include "config.h"
//---------------------------------------------------------------------------
#include "include/shiori.h"
//---------------------------------------------------------------------------
#include <string>
using namespace std;
//---------------------------------------------------------------------------
#include "shiori/shiori_interface.h"
#include <cstdlib>
//---------------------------------------------------------------------------
// ��AI�⥸�塼��ΥС�������ֹ���֤�
SHIORI_EXPORT MEMORY_HANDLE SHIORI_CALL getmoduleversion(long *len)
{
	string verstr=Shiori_GetModuleVersion();

	*len=verstr.size();
	MEMORY_HANDLE reth;
	reth=(MEMORY_HANDLE)SHIORI_MALLOC(*len);
	memcpy(reth,verstr.c_str(),*len);

	return(reth);
}
//---------------------------------------------------------------------------
// �⥸�塼���ɤ߹��߻��˸ƤФ��
SHIORI_EXPORT BOOL SHIORI_CALL load(const MEMORY_HANDLE h,long len)
{
	string datapath((char*)h,len);
	SHIORI_FREE(h);

	return(Shiori_Load(datapath));
}
//---------------------------------------------------------------------------
// �⥸�塼���ڤ�Υ�����˸ƤФ��
SHIORI_EXPORT BOOL SHIORI_CALL unload(void)
{
	return(Shiori_Unload());
}
//---------------------------------------------------------------------------
// ��AI�ꥯ������
SHIORI_EXPORT MEMORY_HANDLE SHIORI_CALL request(const MEMORY_HANDLE h,long *len)
{
	string requeststr((char*)h,*len);
	SHIORI_FREE(h);

	string aistr=Shiori_Request(requeststr);

	*len=aistr.size();
	MEMORY_HANDLE reth;
	reth=(MEMORY_HANDLE)SHIORI_MALLOC(*len);
	memcpy(reth,aistr.c_str(),*len);

	return(reth);
}
//---------------------------------------------------------------------------

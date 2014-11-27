//---------------------------------------------------------------------------
//
// あれ以外の何か以外の何か
// 共有ライブラリエントリ
//
//      Programed by NAKAUE.T (Meister)
//
//  2001.02.03  Phase 0.3     ノーコメント
//  2001.03.15  Phase 0.42    construct/destructの使用を止める
//  2001.04.25  Phase 0.50a1  inverse
//  2001.04.27  Phase 0.50a2  SHIORI/2.1対応
//  2001.05.09  Phase 0.50    SHIORI/2.2対応
//  2001.05.22  Phase 5.10    SHIORI/2.3対応
//  2001.07.10  Phase 6.0     Cygwin対応
//  2001.07.10  Phase 6.1     getmoduleversion追加
//  2001.07.19  Phase 6.2     Mingw対応
//  2002.01.07  Phase 7.3     getversion削除(著作者表示対策)
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
// 偽AIモジュールのバージョン番号を返す
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
// モジュール読み込み時に呼ばれる
SHIORI_EXPORT BOOL SHIORI_CALL load(const MEMORY_HANDLE h,long len)
{
	string datapath((char*)h,len);
	SHIORI_FREE(h);

	return(Shiori_Load(datapath));
}
//---------------------------------------------------------------------------
// モジュール切り離し時に呼ばれる
SHIORI_EXPORT BOOL SHIORI_CALL unload(void)
{
	return(Shiori_Unload());
}
//---------------------------------------------------------------------------
// 偽AIリクエスト
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

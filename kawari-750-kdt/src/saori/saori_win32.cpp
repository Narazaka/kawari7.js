//---------------------------------------------------------------------------
//
// "�ؘa��" for ����ȊO�̉����ȊO�̉���
// SAORI �C���^�[�t�F�[�X Win32��(�ėp)
//
//      Programed by Suikyo.
//
//  2002.04.15  Phase 8.0.0   ���т��킳��o�[�W�������Q�l�ɓ���
//
//---------------------------------------------------------------------------
#if defined(WIN32)||defined(_WIN32)||defined(_Windows)||defined(_MSC_VER)
#include <windows.h>
#endif
//---------------------------------------------------------------------------
#include "config.h"
#include "saori/saori_win32.h"
#ifdef __KAWARI__
#	include "libkawari/kawari_log.h"
using namespace kawari_log;
#endif
//---------------------------------------------------------------------------
//#include <ios>
#include <iostream>
#include <map>
using namespace std;
//---------------------------------------------------------------------------
namespace {
	FARPROC getpadd(HMODULE hm, const char *p){
		FARPROC	lpfn;
#if defined(WIN32)||defined(_WIN32)||defined(_Windows)||defined(_MSC_VER)
	
		lpfn = (FARPROC)GetProcAddress(hm, p + 1);
		if (!lpfn) lpfn = (FARPROC)GetProcAddress(hm, p);
#else
		lpfn = (FARPROC)::dlsym((void *)hm, p);
#endif
		return lpfn;
	}
	map<HMODULE, unsigned int> loadcount;
}
//---------------------------------------------------------------------------
// SAORI���W���[���̃��[�h
bool TSaoriBindingW32::Load (const string &path){
	if (hModule) return false;

	string fn(path);
	for (unsigned int i=0; i<fn.length(); i++)
		if(fn[i]=='/') fn[i]='\\';
	dllpath=fn;

#if defined(WIN32)||defined(_WIN32)||defined(_Windows)||defined(_MSC_VER)
	HMODULE hm=LoadLibrary(fn.c_str());
#else
	HMODULE hm = (HMODULE)::dlopen(fn.c_str(), RTLD_LAZY);
#endif
	if (!hm){
#ifdef __KAWARI__
		Logger.GetStream(LOG_ERROR) << "[SAORI Win32] DLL ("+fn+") load failed." << endl;
#endif
		return false;
	}

	func_load=(BOOL (__cdecl *)(HGLOBAL, long))getpadd(hm, "_load");
	func_request=(HGLOBAL (__cdecl *)(HGLOBAL, long *))getpadd(hm, "_request");
	func_unload=(BOOL (__cdecl *)())getpadd(hm, "_unload");

	if (func_request==NULL){
#ifdef __KAWARI__
		Logger.GetStream(LOG_ERROR) << "[SAORI Win32] import 'request' from ("+fn+") failed." << endl;
#endif
#if defined(WIN32)||defined(_WIN32)||defined(_Windows)||defined(_MSC_VER)
		FreeLibrary(hm);
#else
		::dlclose((void *)hm);
#endif
		return false;
	}

	hModule=hm;
	if (loadcount.count(hModule)){
		loadcount[hModule] ++;
	}else{
		loadcount[hModule] = 1;
	}

	if (func_load){
		string basepath;
		unsigned int pos=fn.find_last_of('\\');
		if (pos==string::npos){
			basepath=fn+"\\";
		}else{
			basepath=fn.substr(0, pos+1);
		}
		long len=basepath.size();
		HGLOBAL h=(HGLOBAL)SHIORI_MALLOC(len);
		if (!h) return false;
		basepath.copy((char *)h, len);
		if (!(func_load(h, len)))
			return false;
	}
#ifdef __KAWARI__
	Logger.GetStream(LOG_INFO) << "[SAORI Win32] DLL ("+fn+") loaded. loadcount=" << GetLoadCount() << endl;
#endif
	return true;
}
//---------------------------------------------------------------------------
// �A�����[�h
TSaoriBindingW32::~TSaoriBindingW32 (){
	if (hModule){
		if (func_unload)
			(func_unload)();
#if defined(WIN32)||defined(_WIN32)||defined(_Windows)||defined(_MSC_VER)
		FreeLibrary(hModule);
#else
		::dlclose((void *)hModule);
#endif
		if (loadcount.count(hModule)){
			--loadcount[hModule];
			if (!loadcount[hModule])
				loadcount.erase(hModule);
		}
	}
#ifdef __KAWARI__
	Logger.GetStream(LOG_INFO) << "[SAORI Win32] DLL ("+dllpath+") unloaded. loadcount=" << GetLoadCount() << endl;
#endif
}
//---------------------------------------------------------------------------
// SAORI/1.0 request
string TSaoriBindingW32::Request(const string &req){
	if (!func_request) return ("");

	string	res;
	HGLOBAL	h;
	long	len;
	
	len = (long)(req.size());
	h = (HGLOBAL)SHIORI_MALLOC(len);
	if (!h) return ("");
	req.copy((char *)h, len);
	
	h = func_request(h, &len);
	
	if (h) {
		res.assign((const char *)h, len);
		SHIORI_FREE(h);
	}

	return res;
}
//---------------------------------------------------------------------------
// ���n���h���̃��C�u�����̃��[�h�J�E���g�𓾂�
unsigned int TSaoriBindingW32::GetLoadCount(void){
	if (loadcount.count(hModule))
		return loadcount[hModule];
	else
		return 0;
}
//---------------------------------------------------------------------------

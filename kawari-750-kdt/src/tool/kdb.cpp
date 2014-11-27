//---------------------------------------------------------------------------
//
// �ؘa���f�o�b�K
//
//      Programed by NAKAUE.T (Meister)
//
//  2001.05.24  Phase 0.10    �R���\�[����
//  2001.08.12  Phase 6.2.1   �K���Ɠ���
//
//---------------------------------------------------------------------------
#include "config.h"
//---------------------------------------------------------------------------
#include <cstdlib>
#include <strstream>
using namespace std;
//---------------------------------------------------------------------------
#include "tool/kdb.h"
//---------------------------------------------------------------------------
// SakuraAPI/1.3 �C�x���g���M
void TKawariInterfaceSakuraAPI::SakuraEvent(const string& event,const string& param)
{
	const WPARAM SA_GETPROCESSID=138;
	const WPARAM SA_GETSHAREDMEMORY=139;
	const WPARAM SA_NOTIFYEVENT=256;

	UINT WM_SAKURAAPI=RegisterWindowMessage("Sakura");

	DWORD processid=(DWORD)SendMessage(Target,WM_SAKURAAPI,SA_GETPROCESSID,0);
	HANDLE hProcess=OpenProcess(PROCESS_VM_OPERATION|PROCESS_VM_WRITE,0,processid);

	HGLOBAL slot;

	for(int i=-1;i<=7;i++) {
		slot=(HGLOBAL)SendMessage(Target,WM_SAKURAAPI,SA_GETSHAREDMEMORY,(LPARAM)i);
		unsigned char dummy[8192]={0};
		WriteProcessMemory(hProcess,slot,(LPVOID)dummy,8192,NULL);
	}

	slot=(HGLOBAL)SendMessage(Target,WM_SAKURAAPI,SA_GETSHAREDMEMORY,(LPARAM)-1);
	WriteProcessMemory(hProcess,slot,(LPVOID)event.c_str(),event.size(),NULL);

	slot=(HGLOBAL)SendMessage(Target,WM_SAKURAAPI,SA_GETSHAREDMEMORY,(LPARAM)0);
	WriteProcessMemory(hProcess,slot,(LPVOID)param.c_str(),param.size(),NULL);

	CloseHandle(hProcess);

	SendMessage(Target,WM_SAKURAAPI,SA_NOTIFYEVENT,0);

	return;
}
//---------------------------------------------------------------------------
// �F���\�ȑ��S�[�X�g��HWnd�ꗗ��Ԃ�
void GetGhostList(map<HWND,string> &ghostlist)
{
	// Win32API���g�p�\�ŁAFile Mapping Object ��������擾����ꍇ

	HANDLE hFmo=OpenFileMapping(FILE_MAP_READ,FALSE,(LPCTSTR)"Sakura");
	if(!hFmo) return;	// ���XFileMappingObject�����Ă���

	char *fmobuff=(char*)MapViewOfFile(hFmo,FILE_MAP_READ,0,0,0);

	// File Mapping Object �̃T�C�Y
	// �G���f�B�A���R���Ȃ�
	unsigned int fmosize=
	 (((unsigned int)fmobuff[3])<<24)
	 +(((unsigned int)fmobuff[2])<<16)
	 +(((unsigned int)fmobuff[1])<<8)
	 +(((unsigned int)fmobuff[0]));

	istrstream *ifs=new istrstream(&fmobuff[4],fmosize-4);

	map<string,HWND> idmap;
	map<string,string> namemap;

	string buff;
	while(ifs->peek()!=0) {
		getline(*ifs,buff,'\x0a');
		if(buff.size()==0) break;	// �I���������킩��Ȃ��̂�

		string::size_type pos1=buff.find('.');
		string::size_type pos2=buff.find('\x1');
		string::size_type pos3=buff.find('\x0d');

		if((pos1==string::npos)||(pos2==string::npos)) break;	// �I���������킩��Ȃ��̂�

		string processid=buff.substr(0,pos1);
		string key=buff.substr(pos1+1,pos2-pos1-1);
		string value=buff.substr(pos2+1,pos3-pos2-1);

		if(key=="hwnd") {
			idmap[processid]=((HWND)atoi(value.c_str()));;
		} else if(key=="name") {
			namemap[processid]=value;
		}
	}

	delete ifs;

	UnmapViewOfFile((LPVOID)fmobuff);

	CloseHandle(hFmo);

	map<string,HWND>::iterator it;
	for(it=idmap.begin();it!=idmap.end();it++) {
		ghostlist[it->second]=namemap[it->first];
	}

	return;
}
//---------------------------------------------------------------------------

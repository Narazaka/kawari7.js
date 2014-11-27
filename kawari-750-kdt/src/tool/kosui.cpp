//---------------------------------------------------------------------------
//
// KOSUI -- Kawari cOnSole Use Interpritor --
// �K�� -- �R���\�[���ŉؘa���C���^�[�v���^ --
//
//      Programed by NAKAUE.T (Meister)
//
//  2001.05.30  Phase 5.1     �R���\�[���C���^�[�v���^
//  2001.08.06  Phase 6.2     KawariDebugger�ɍ��킹�ăf�t�H���g��echo-mode��
//  2001.08.12  Phase 6.2.1   KawariDebugger�Ɠ���
//
//---------------------------------------------------------------------------
#include "config.h"
//---------------------------------------------------------------------------
#include <string>
#include <iostream>
using namespace std;
//---------------------------------------------------------------------------
#include "tool/kosui_base.h"
#include "libkawari/kawari.h"
#include "libkawari/kawari_engine.h"
#ifdef USEKDB
	#include "tool/kdb.h"
#endif
//---------------------------------------------------------------------------
// �K����
class TKawariInterfaceKosui: public TKawariInterface_base {
private:

	TNS_KawariANI *Kawari;
	TKawariEngine *KawariEngine;

public:

	TKawariInterfaceKosui(const string& datapath,const string& inifile)
	{
		Kawari=new TNS_KawariANI;
		KawariEngine=dynamic_cast<TKawariEngine*>(Kawari->Engine);
		if(!KawariEngine) throw("error");

		Kawari->LoadSub(datapath,inifile);
	}

	~TKawariInterfaceKosui()
	{
		Kawari->Unload();

		delete Kawari;
	}

	// �o�[�W�����ԍ���Ԃ�
	virtual string GetModuleVersion(void)
	{
		return(Kawari->GetModuleVersion());
	}

	// �^����ꂽ�X�N���v�g�����߁E���s����
	virtual string Parse(const string& script)
	{
		return(KawariEngine->Parse(script));
	}
};
//---------------------------------------------------------------------------
// �ڑ�����S�[�X�g��I��
TKawariInterface_base* AttachTarget(const string& datapath,const string& inifile)
{
	cout << "[" << 0 << "] : " << "Interpreter mode" << endl;

	#ifdef USEKDB
		// �ؘa���f�o�b�K��g�ݍ��ޏꍇ
		map<HWND,string> ghostname;
		GetGhostList(ghostname);

		if(ghostname.size()>0) {
			vector<HWND> ghostlist;
			map<HWND,string>::iterator it;
			for(it=ghostname.begin();it!=ghostname.end();it++) {
				ghostlist.push_back(it->first);
				cout << "[" << ghostlist.size() << "] : " << it->second << endl;
			}

			unsigned int no;
			while(true) {
				cout << "Attach : ";
				cin >> no;
				if(no<=ghostlist.size()) break;
			}
			string buff;
			getline(cin,buff);

			if(no>0) return(new TKawariInterfaceSakuraAPI(ghostlist[no-1]));
		}
	#endif

	return(new TKawariInterfaceKosui(datapath,inifile));
}
//---------------------------------------------------------------------------
int main(int argc,char *argv[])
{
	string datapath="./";
	string inifile="./kawari.ini";

	if(argc>1) {
		inifile=argv[1];
		unsigned int pos=inifile.rfind('/');
		if(pos==string::npos) pos=inifile.rfind('\\');
		// ini�t�@�C�������u�\.ini�v�������肵�Ȃ�����j�]���Ȃ�(����)
		datapath=inifile.substr(0,pos+1);
	}

	cout << "K O S U I -- Kawari cOnSole Use Interpritor --" << endl;
	cout << "2001 Programed by NAKAUE.T (Meister)" << endl << endl;

	TKawariInterface_base *Kawari=AttachTarget(datapath,inifile);

	cout << endl;
	cout << "Kernel version " << Kawari->GetModuleVersion() << endl << endl;

	cout << "mode change by \".\"" << endl;

	bool commode=false;
	while(true) {
		if(commode) cout << "command-mode > ";
		 else cout << "echo-mode > ";

		string buff;
		getline(cin,buff);
		buff=buff.c_str();

		if(buff.size()==0) continue;

		if(buff=="exit") break;
		if(buff==".") {
			commode=!commode;
			continue;
		}

		if(commode) cout << Kawari->Parse(string("$(")+buff+")") << endl;
		 else cout << Kawari->Parse(buff) << endl;
	}

	delete Kawari;

	return(0);
}
//---------------------------------------------------------------------------


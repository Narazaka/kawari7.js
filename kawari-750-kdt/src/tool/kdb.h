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
#ifndef KDB_H
#define KDB_H
//---------------------------------------------------------------------------
#include "config.h"
//---------------------------------------------------------------------------
#include <string>
#include <map>
using namespace std;
//---------------------------------------------------------------------------
#include <windows.h>
//---------------------------------------------------------------------------
#include "tool/kosui_base.h"
//---------------------------------------------------------------------------
// SakuraAPI��
class TKawariInterfaceSakuraAPI : public TKawariInterface_base {
private:

	HWND Target;

public:

	TKawariInterfaceSakuraAPI(HWND target) : Target(target) {}

	// SakuraAPI/1.3 �C�x���g���M
	void SakuraEvent(const string& event,const string& param);

	// �o�[�W�����ԍ���Ԃ�
	virtual string GetModuleVersion(void)
	{
		return("UNKNOWN/0.0.0");
	}

	// �^����ꂽ�X�N���v�g�����߁E���s����
	virtual string Parse(const string& script)
	{
		SakuraEvent("ShioriEcho",script);
		return("");
	}
};
//---------------------------------------------------------------------------
// �F���\�ȑ��S�[�X�g��HWnd�ꗗ��Ԃ�
void GetGhostList(map<HWND,string> &ghostlist);
//---------------------------------------------------------------------------
#endif


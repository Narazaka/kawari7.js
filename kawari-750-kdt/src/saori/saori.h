//---------------------------------------------------------------------------
//
// "�ؘa��" for ����ȊO�̉����ȊO�̉���
// SAORI �C���^�[�t�F�[�X
//
//      Programed by Suikyo.
//
//  2002.04.15  Phase 8.0.0   ���т��킳��o�[�W�������Q�l�ɓ���
//
//---------------------------------------------------------------------------
#ifndef SAORI_H
#define SAORI_H
//---------------------------------------------------------------------------
#include "config.h"
#include "misc/phttp.h"
//---------------------------------------------------------------------------
#include <string>
#include <map>
//---------------------------------------------------------------------------
// �Q�ƃJ�E���g�̓n���h���Ɋ�Â���Binding���Ǘ����邱��
// Windows��OS���Ǘ����Ă���B
#if defined(WIN32) || defined(_WIN32)
#	include "saori/saori_win32.h"
typedef TSaoriBindingW32 TSaoriBinding;
#elif defined(linux) || defined(__linux__)
#	include "saori/saori_linux.h"
typedef TSaoriBindingLnx TSaoriBinding;
#endif

//---------------------------------------------------------------------------
class TSaoriModule{
public:
	enum LOADTYPE {
		PRELOAD,
		LOADONCALL,
		NORESIDENT
	};

	// SAORI/1.0 request
	bool Request(const TPHMessage &request, TPHMessage &response);

	~TSaoriModule();
private:
	LOADTYPE type;
	std::string libpath;
	TSaoriBinding *bind;

	TSaoriModule(const std::string &path, const LOADTYPE t);
		
	void Attatch(void);
	void Detatch(void);

	// ���ɂ�����܂����B
	friend class TSaoriPark;
};
//---------------------------------------------------------------------------
class TSaoriPark {
public:
	// ���W���[���̓o�^
	void RegisterModule(const std::string &aliasname, const std::string &path, const TSaoriModule::LOADTYPE type);

	// ���W���[���o�^�̍폜
	void EraseModule(const std::string &aliasname);

	// ���W���[���𓾂�
	TSaoriModule * const GetModule(const std::string &alias);

	~TSaoriPark();
private:
	// alias -> Module
	std::map<std::string, TSaoriModule *> aliasmap;
};
//---------------------------------------------------------------------------
#endif // SAORI_H

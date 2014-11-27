//---------------------------------------------------------------------------
//
// TPHMessage - �UHTTP���b�Z�[�W -
//
//      Programed by Suikyo.
//
//---------------------------------------------------------------------------
#ifndef PHTTP_H
#define PHTTP_H
//---------------------------------------------------------------------------
#include "config.h"
//---------------------------------------------------------------------------
#include "misc/mmap.h"
//---------------------------------------------------------------------------
#include <iostream>
#include <string>
//---------------------------------------------------------------------------
class TPHMessage : public TMMap<std::string, std::string> {
private:
	std::string startline;
public:
	// �X�^�[�g���C���̐ݒ�
	void SetStartline(const std::string &line) { startline=line; }

	// �X�^�[�g���C���𓾂�
	std::string GetStartline(void) const { return startline; }

	// �V���A���C�Y
	std::string Serialize(void) const;

	// �f�V���A���C�Y
	void Deserialize(const std::string &mes);

	// �_���v
	void Dump(std::ostream &os) const;
};
//---------------------------------------------------------------------------
#endif // PHTTP_H

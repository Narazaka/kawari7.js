//---------------------------------------------------------------------------
//
// "�ؘa��" for ����ȊO�̉����ȊO�̉���
// KawariInlineScript -- �ێ�Ipiro --
//
//      Programed by NAKAUE.T (Meister)
//
//  2001.03.19  Phase 0.5     Piroject-X
//  2001.05.31  Phase 5.2     KIS�C���^�[�t�F�[�X
//  2001.06.10  Phase 5.3.1   �u-�v���u.�v��
//
//---------------------------------------------------------------------------
#include "config.h"
//---------------------------------------------------------------------------
#include "kis/kis_cpiro.h"
//---------------------------------------------------------------------------
#include "libkawari/kawari_engine.h"
//---------------------------------------------------------------------------
string KIS_pirocall::Function(const vector<string>& args)
{
	if((args.size()!=2)&&(args.size()!=3)) return("");

	string entry="piro."+KisEngine->Engine()->EncodeEntryName(args[1]);

	string retstr=KisEngine->Engine()->RandomSelect(entry);
	if(retstr.size()) return(retstr);
	 else if(args.size()==3) return(args[2]);

	return("");

}
//---------------------------------------------------------------------------


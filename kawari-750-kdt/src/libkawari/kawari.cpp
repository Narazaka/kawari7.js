//---------------------------------------------------------------------------
//
// "�ؘa��" for ����ȊO�̉����ȊO�̉���
// �b��shiori.dll
//
//      Programed by NAKAUE.T (Meister)
//
//  2001.02.03  Phase 0.3     �m�[�R�����g
//  2001.02.11  Phase 0.31    �ċA��`����
//  2001.02.23  Phase 0.4     ���_�푈�I��F�O
//                            �`���炩�ɂ����艺�����A�߂��͌J��Ԃ��܂���`
//                                                                �o�[�W����
//                            kawari.ini����
//                            ���������t�@�C��
//                            sentence.txt�p�~
//  2001.02.27  Phase 0.41    �T���S�����Ȃ������o�O���(getword�֘A)
//  2001.03.15  Phase 0.42    unload�\��
//                            ���M���O�@�\
//                            �Í����t�@�C���Ή�
//                            �����G���g���Ή�
//                            ���[�J���ϐ��Ή�
//  2001.04.25  Phase 0.50a1  ���X�|���X�Ή�
//  2001.04.27  Phase 0.50a2  SHIORI/2.1�Ή�
//  2001.04.28  Phase 0.50a3  COMMUNICATE�푈
//       |
//  2001.05.02
//  2001.05.03  Phase 0.50a4  �C�����C���X�N���v�g
//  2001.05.12  Phase 0.50b2  Piroject-X ������
//                            SHIORI/2.2�Ή�
//                            �C�����C���X�N���v�g��$()�ɕύX
//  2001.05.30  Phase 5.1     �C���^�[�v���^�E�R���p�C����
//                             Phase0.50b2�܂ł̃o�O�t�B�b�N�X
//  2001.05.31  Phase 5.2     �ێ�Ipiro
//  2001.06.10  Phase 5.3.1   GET Version�΍�
//                            �USHIORI/2.4���� (^_^;
//  2001.06.18  Phase 5.4     �C�����C���X�N���v�g�啝����
//  2001.07.10  Phase 6.0     getmoduleversion�ǉ�
//                            �o�O�t�B�b�N�X
//  2001.07.21  Phase 6.2     SHIORI/2.5����
//                            �����C�x���g�ǉ�(OnLoad,OnUnload,SHIORI/2.4)
//                            �n�[�h�R�[�f�B���O�̃G���[���b�Z�[�W�p�~
//                            kawari.ini��adddict�Ainclude�ǉ�
//  2001.08.06  Phase 6.2     Age��d�J�E���g�A�b�v�̃o�O�C��
//  2001.08.07  Phase 6.2     �����C�x���g�̃v���t�B�b�N�X��system.�ɓ���
//                            �����C�x���g�ǉ�(OnNotifyGhost,OnNotifyOther,OnGetStatus)
//  2001.08.08  Phase 6.2     �K���p��LoadSub��V��
//  2001.08.25  Phase 6.3     �Z�L�����e�B�[�z�[���΍�
//  2001.08.25  Phase 7.0     �Z�L�����e�B�΍�(WriteProtect)
//  2001.09.23  Phase 7.0.1   �Z�L�����e�B�΍��redo34�ȍ~�̕����ɑΉ�
//                            Sender�o�H���ǉ�(System.Sender.Path)
//                            3�G���g���ȏ�ł�AND�����o�O���C��
//                            SHIORI/2.3b�Ή�
//                            �C�����C���X�N���v�g����
//                            �N�����x�̍�����
//                            �n�C�t�����g�p���鋌�G���g���̑Ή���~
//  2001.10.29  Phase 7.0.2   GhostEx�w�b�_�Ή�
//                            GET Version���ēxkawari.cpp�Ɉڊ�
//                            SHIORI/2.6���Ή�(����Shift_JIS�ɌŒ�)
//                            �����C�x���g�ǉ�(OnEventUnknown)
//  2001.10.31  Phase 7.0.3   SecurityLevel�w�b�_�Ή�
//  2001.11.21  Phase 7.1     �G���g�������_���Ăяo���̃o�O�C��
//                            �[��������MT�A���S���Y�����̗p
//  2001.11.25  Phase 7.1.1   �����_���̏����l�Ɏ������g���悤�ύX
//                            [�K��] help�R�}���h�̃��b�Z�[�W��(�R�L��)�p���
//                            SecurityLevel��0�`3�ɕύX(4��p�~)
//  2001.12.08  Phase 7.1.2   kawari.ini�Ńe�L�X�g�t�@�C���ǂݍ��ݑΉ�
//  2001.12.16  Phase 7.2     TMMap�̒l����������o�O���C��
//                            (Thanks: ���́A����)
//  2002.01.07  Phase 7.3     ����ҕ\���p�w�b�_�ǉ�(Thanks: ���т���)
//                            �`�B�o�H����SecurityLevel�݂̂Ŕ���
//  2002.01.08  Phase 7.3.1   BalloonOffset�w�b�_�Ή�
//  2002.05.07  Phase 7.4.0   �C��BSD���C�Z���X�ɓ���
//  2003.02.16  Phase 7.5.0   I18N(Thanks:Sanori,whoami)
//
//---------------------------------------------------------------------------
#include "config.h"
//---------------------------------------------------------------------------
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <vector>
using namespace std;
//---------------------------------------------------------------------------
#include "libkawari/kawari.h"
#include "libkawari/sequence_gen.h"
#include "misc/misc.h"
#include "misc/i18n.h"
#include "misc/mmap.h"
#include "saori/saori.h"
//---------------------------------------------------------------------------
// SHIORI/2.0 API
//---------------------------------------------------------------------------
// DLL���[�h���ɌĂ΂��
bool TNS_KawariANI::Load(const string& datapath)
{
	return(LoadSub(datapath,datapath+"kawari.ini"));
}
//---------------------------------------------------------------------------
// DLL�A�����[�h���ɌĂ΂��
bool TNS_KawariANI::Unload(void)
{
	string aistr=GetSentence("system.OnUnload");
	if(LogFS) (*LogFS) << aistr << endl;

	if(LogFS) (*LogFS) << "Unload:" << endl;

	return(true);
}
//---------------------------------------------------------------------------
// �UAI���N�G�X�g
string TNS_KawariANI::Request(const string& type,TMMap<string,string>& request)
{
	bool logmode=true;
	// OnSecondChange��OnMouseMove�ň�X���O���c���Ă�����g���ۂ��܂���
	if(request.count("Event")) {
//		if((request["Event"]=="OnSecondChange")||(request["Event"]=="OnMouseMove")) {
		if(request["Event"]=="OnMouseMove") {
			logmode=false;
		}
	}

	if(logmode&&LogFS) {
		(*LogFS) << "Begin Request" << endl;
		(*LogFS) << type << endl;
//		(*LogFS) << request["ORIGINAL"] << endl;
		TMMap<string,string>::iterator it;
		for(it=request.begin();it!=request.end();it++) {
			if(it->first!="ORIGINAL") (*LogFS) << it->first << " : " << it->second << endl;
		}
		(*LogFS) << endl;
	}


	map<string,string> response;
	unsigned int statuscode=400;

	string sender;
	if(request.count("Sender")) sender=request["Sender"];
//	 else sender="(external)";
    // �����̋󔒂���菜��
//	size_t ilastchr=sender.find_last_not_of(" ");
//	if((ilastchr!=string::npos)&&(ilastchr<(sender.length()-1)))
//		sender = sender.substr(0, ilastchr+1);

    // Sender��`�B�o�H���ƕ���
    unsigned int sender_path;
    string sender_path_name="unknown";
//	if((sender.rfind("(local)")==(sender.length()-7))||(request["SecurityLevel"]=="local")){
    if(request["SecurityLevel"]=="local"){
        sender_path=SENDER_LOCAL;
        sender_path_name="local";
        sender=sender.substr(0, sender.length()-7);
//    }else if((sender=="embryo")||(sender=="SSP")){
//        sender_path=SENDER_SYSTEM;
//        sender_path_name="system";
//	}else if((sender.rfind("(external)")==(sender.length()-10))||(request["SecurityLevel"]=="external")){
    }else if(request["SecurityLevel"]=="external"){
        sender_path=SENDER_EXTERNAL;
        sender_path_name="external";
        sender=sender.substr(0, sender.length()-10);
    }else{
        sender_path=SENDER_UNKNOWN;
        sender_path_name="unknown";
    }

    // ������x�����̋󔒂���菜��
//	ilastchr=sender.find_last_not_of(" ");
//	if((ilastchr!=string::npos)&&(ilastchr<(sender.length()-1)))
//		sender = sender.substr(0, ilastchr+1);

    Engine->InsertAfterClear("system.Sender",sender);
    request["Sender"] = sender;
    Engine->InsertAfterClear("system.Sender.Path",sender_path_name);

	if(SecurityLevel.Check(sender_path)) {
		switch(type[0]) {
		case 'N':
			if((type=="NOTIFY")||(type=="NOTIFY Ghost")||(type=="NOTIFY OwnerGhostName")) {
//				Engine->InsertAfterClear("system-Ghost",request["Ghost"]);
				Engine->InsertAfterClear("system.Ghost",request["Ghost"]);
				GhostName=request["Ghost"];
				statuscode=200;
				string aistr=GetSentence("system.OnNotifyGhost");
				if(LogFS) (*LogFS) << aistr << endl;
			} else if(type=="NOTIFY OtherGhostName") {
				OtherGhostName.clear();
				OtherGhostExName.clear();
//				Engine->ClearEntry("system-OtherGhost");
				Engine->ClearEntry("system.OtherGhost");
				Engine->ClearEntry("system.OtherGhostEx");

				TMMap<string,string>::iterator it;
				for(it=request.lower_bound("Ghost");it!=request.upper_bound("Ghost");it++) {
					OtherGhostName.insert(it->second);
//					Engine->Insert("system-OtherGhost",it->second);
					Engine->Insert("system.OtherGhost",it->second);
				}

				for(it=request.lower_bound("GhostEx");it!=request.upper_bound("GhostEx");it++) {
					OtherGhostExName.insert(it->second);
					Engine->Insert("system.OtherGhostEx",it->second);
				}

				statuscode=200;
				string aistr=GetSentence("system.OnNotifyOther");
				if(LogFS) (*LogFS) << aistr << endl;
			}
			break;
		case 'G':
			if(type=="GET Version") {
				response["ID"] = KAWARI_NAME;
				response["Craftman"] = KAWARI_AUTHOR;
				response["Version"] = KAWARI_MAJOR "." KAWARI_MINOR "."KAWARI_SUBMINOR;
				statuscode=200;
			} else if(type=="GET Sentence") {
				statuscode=RequestGetSentence(request,response);

				string targetghost=Engine->FindFirst("system.communicate");
				if(targetghost.size()==0) {
					targetghost=request["Sender"];
//					targetghost=Engine->FindFirst("system-communicate");
//					if(targetghost.size()==0) {
//						targetghost=request["Sender"];
//					}
				}
				Engine->ClearEntry("system.communicate");
//				Engine->ClearEntry("system-communicate");

				int age=0;
				if(targetghost==request["Sender"]) {
					if(request.count("Age")) age=atoi(request["Age"].c_str())+1;
				}

				if((statuscode==200)&&(targetghost!="stop")&&(age<20)) {
					if(SearchCommunicateTarget(targetghost,response)) {
						response["Age"]=IntToString(age);
					}
				}
			} else if(type=="GET Word") {
				if(request.count("Type")) {
					// Type�ɂ́u\ms�v�̂悤�ȕ����񂪓n�����

					string key("compatible.");
					key+=request["Type"].substr(1);

					string aistr=GetSentence(key);
//					if(aistr.size()==0) {
//						key=string("compatible-")+request["Type"].substr(1);
//						aistr=GetSentence(key);
//					}
					if(aistr.size()) {
						statuscode=200;
						response["Word"]=aistr;
					} else {
						statuscode=204;
					}
				} else {
					statuscode=204;
				}
			} else if(type=="GET Status") {
				string aistr=GetSentence("system.OnGetStatus");
				if(aistr.size()>0) {
					response["Status"]=aistr;
				} else {
					response["Status"]=
					 IntToString(Engine->WordCollectionSize())+","
					 +IntToString(Engine->EntryCollectionSize()-Engine->MatchCollectionSize())+","
					 +IntToString(Engine->MatchCollectionSize())+","
					 +KAWARI_MAJOR KAWARI_MINOR KAWARI_SUBMINOR ","	// �ؘa���̃o�[�W�����ԍ�
					 +"100,"
					 +"100";
				}
				statuscode=200;
			} else if(type=="GET String") {
				// SHIORI/2.5
				if(request.count("ID")) {
					string key("resource.");
					key+=Engine->EncodeEntryName(request["ID"]);

					Engine->InsertAfterClear("system.ID",request["ID"]);
					string aistr=GetSentence(key);

					if(aistr.size()) {
						statuscode=200;
						response["String"]=aistr;
					} else {
						statuscode=204;
					}
				}
			}
			break;
		case 'T':
			if(type=="TEACH") {
				// �USHIORI/2.4

				Engine->InsertAfterClear("system.Sentence",request["Word"]);

				statuscode=200;
				response["Sentence"]=GetSentence("system.OnTeach");
			} else if(type=="TRANSLATE Sentence") {
				// SHIORI/2.6
				Engine->InsertAfterClear("system.Sentence",request["Sentence"]);
				statuscode=200;
				string aistr=GetSentence("system.OnTranslate");
				if(aistr.size()) {
					response["Sentence"]=aistr;
				} else {
					statuscode=400;
				}
			}
		}
	} else {
		// ���s���Ȃ�
	}



	string statusheader;
	switch(statuscode) {
	case 200:
		statusheader="200 OK";
		break;
	case 204:
		statusheader="204 No Content";
		break;
	case 311:
		statusheader="311 Not Enough";
		break;
	case 312:
		statusheader="312 Advice";
		break;
	case 400:
		statusheader="400 Bad Request";
		break;
	default:
		statusheader="500 Internal Server Error";
		break;
	}

	string status="SHIORI/"SHIORIVER" "+statusheader+"\x0d\x0a";
	// �������Ȃ鎞���Aresponse�ɂ�Charset��t��
	response["Charset"]=lang.getShioriCharset();

	// BalloonOffset�w�b�_��sentence�n�Ȃ�S�ċN���肤��̂ŁA�����őΉ�
	// 2002/1/8 ���Ɓ[
	string BalloonOffset=Engine->FindFirst("system.BalloonOffset");
	if(BalloonOffset.size()) {
		response["BalloonOffset"]=BalloonOffset;
		Engine->ClearEntry("system.BalloonOffset");
	}

	map<string,string>::iterator it;
	for(it=response.begin();it!=response.end();it++) {
		if(it->second.size()) status=status+it->first+": "+it->second+"\x0d\x0a";
	}
	status+="\x0d\x0a";

	if(logmode&&LogFS) {
		(*LogFS) << endl << "Response" << endl;
		(*LogFS) << status << endl;
		(*LogFS) << "End Request" << endl << endl;
	}

	return(status);
}
//---------------------------------------------------------------------------
// �ȉ���API�ȊO
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
TNS_KawariANI::TNS_KawariANI(void) : LogFS(NULL),SecurityLevel(2)
{
	Engine=new TKawariEngine(this);
}
TNS_KawariANI::~TNS_KawariANI()
{
	if(LogFS) {
		(*LogFS) << "delete object." << endl;
		LogFS->close();
		delete LogFS;
	}
	delete Engine;
}

// ���N�G�X�g�ɉ����ĕԓ����𐶐�����
unsigned int TNS_KawariANI::RequestGetSentence(TMMap<string,string>& request,map<string,string> &response)
{
	string aistr;

	if(request.count("Event")||request.count("Sentence")) {
		for(int i=0;i<=7;i++){
			string refno=IntToString(i);
//			Engine->InsertAfterClear("system-Reference"+refno,request["Reference"+refno]);
			Engine->InsertAfterClear("system.Reference"+refno,request["Reference"+refno]);
		}
	}

	if(request.count("Event")) {
//		Engine->InsertAfterClear("system-EventName",request["Event"]);
		Engine->InsertAfterClear("system.EventName",request["Event"]);

		string entry="event."+Engine->EncodeEntryName(request["Event"]);
		aistr=GetSentence(entry);

		if(aistr.size()==0) {
			aistr=GetSentence("system.OnEventUnknown");
		}

//		if(aistr.size()==0) {
//			entry="event-"+Engine->EncodeEntryName(request["Event"]);
//			aistr=GetSentence(entry);
//		}

		if(aistr.size()==0) return(204);
	} else if(request.count("Sentence")) {
//		Engine->InsertAfterClear("system-Sentence",request["Sentence"]);
//		Engine->InsertAfterClear("system-Sender",request["Sender"]);
//		Engine->InsertAfterClear("system-Age",request["Age"]);
		Engine->InsertAfterClear("system.Sentence",request["Sentence"]);
		Engine->InsertAfterClear("system.Sender",request["Sender"]);
		Engine->InsertAfterClear("system.Age",request["Age"]);
		Engine->InsertAfterClear("system.Surface",request["Surface"]);
		// SHIORI/2.3b�p���t�@�����X�G���g���̏��� (2001/09/15 ���Ɓ[)
		for(int i=0;i<=7;i++){
			Engine->ClearEntry("system.Response"+IntToString(i));
		}
		aistr=GetResponse(request["Sentence"]);
	} else if(request.count("Word")) {
//		Engine->InsertAfterClear("system-Sentence",request["Word"]);
		Engine->InsertAfterClear("system.Sentence",request["Word"]);
		aistr=GetResponse(request["Word"]);
	} else {
		aistr=GetSentence("sentence");
		if(aistr.size()==0) return(204);
	}

	response["Sentence"]=aistr;

	return(200);
}
//---------------------------------------------------------------------------
// Communicate�̑����T��
bool TNS_KawariANI::SearchCommunicateTarget(const string &targetghost,map<string,string> &response)
{
	if(targetghost.size()==0) return(false);
	if(OtherGhostName.count(targetghost)==0) return(false);

	response["Sender"]=GhostName;
	response["To"]=targetghost;

	// Reference�w�b�_�̒ǉ� (2001/09/15 ���Ɓ[)
	for(unsigned int i=0;i<=7;i++) {
		string key=Engine->FindFirst("system.Response"+IntToString(i));
		if(key.size()) {
			response["Reference"+IntToString(i)]=key;
		}
	}

	return(true);
}
//---------------------------------------------------------------------------
// �G���g���Ɉ�v���郉���_���P���Ԃ�
string TNS_KawariANI::GetSentence(const string& key)
{
	return(Engine->RandomSelect(key));
}
//---------------------------------------------------------------------------
// ���͂ɕԓ����郉���_���P���Ԃ�
string TNS_KawariANI::GetResponse(string sentence)
{
	string aistr=GetSentence("system.OnResponse");
	if(aistr.size()==0) aistr=GetSentence("event.Response");
//	if(aistr.size()==0) aistr=GetSentence("event-Response");

	if(aistr.size()==0) aistr=Engine->MatchEntryRandomSelect("match.Response");

	if(aistr.size()==0) aistr=GetSentence("system.OnResponseUnknown");
	if(aistr.size()==0) aistr=GetSentence("system.response.unknown");
//	if(aistr.size()==0) aistr=GetSentence("system-response-unknown");

	return(aistr);
}
//---------------------------------------------------------------------------
// �f�[�^�t�@�C���ǂݍ���
bool TNS_KawariANI::LoadFile(const string &filename,const string &type)
{
	ifstream ifs;
	ifs.open(filename.c_str());

	if(!ifs.is_open()) return(false);

	string buff;
	getline(ifs,buff);
	buff=StringTrim(buff);

	ifs.close();

	if(buff!="[SAKURA]") {
		// �ؘa���t�H�[�}�b�g
		return(Engine->LoadKawariDict(filename));
	} else {
		// SAKURA�t�H�[�}�b�g
		return(LoadSakuraFile(filename,type));
	}
}
//---------------------------------------------------------------------------
// SAKURA�t�H�[�}�b�g�f�[�^�t�@�C���ǂݍ���
bool TNS_KawariANI::LoadSakuraFile(const string &filename,const string &type)
{
	if(type!="dict") return(false);

	ifstream ifs;
	ifs.open(filename.c_str());
	if(!ifs.is_open()) return(false);

	string buff;
	string key="";
	bool countflag=false;
	string countstring="";
	while(getline(ifs,buff)) {
		buff=StringTrim(buff);
		if(buff.size()>0) {
			if(buff[0]=='#') {
				if(!countflag) {
					key=buff;
				}else {
					if(buff.substr(0,buff.size()-1)==countstring) {
						key=countstring;
					} else {
						key=buff;
						countflag=false;
					}
				}
			} else if(key.size()>0) {
				if(buff.substr(0,5)=="count") {
					countflag=true;
					countstring=key;
				} else {
					string entry="piro."+Engine->EncodeEntryName(key);
					Engine->Insert(entry,buff);
					key="";
				}
			}
		}
	}

	return(true);
}
//---------------------------------------------------------------------------
// ini�t�@�C���ǂݍ���
bool TNS_KawariANI::LoadINI(const string &filename,const string &datapath,vector<string> &dictfiles)
{
	ifstream ifs;
	ifs.open(filename.c_str());

	if(!ifs.is_open()) return(false);

	string buff;
	while(getline(ifs,buff)) {
		buff=StringTrim(buff);
		if((buff.size()>0)&&(buff[0]!='#')) {
			string key,value;
			string::size_type pos=buff.find(':');
			if(pos==string::npos) {
				key=buff;
				value="";
			} else {
				key=StringTrim(buff.substr(0,pos));
				value=StringTrim(buff.substr(pos+1));
			}

			if(key=="security") {
				SecurityLevel.Set((unsigned int)atoi(value.c_str()));
				if(LogFS) (*LogFS) << "SecurityLevel " << SecurityLevel.Get() << endl;
			} if(key=="randomseed") {
				SRandom(atoi(value.c_str()));
			} else if(key=="dict") {
				dictfiles.push_back(value);
			} else if(key=="text") {
				string::size_type pos=value.find_first_of(" \t");
				if(pos!=string::npos) {
					string entry=StringTrim(value.substr(0,pos));
					value=StringTrim(value.substr(pos+1));
					Engine->LoadTextFile(datapath+value,entry);
				}
			} else if(key=="adddict") {
				string::size_type pos=value.find_first_of(" \t");
				if(pos!=string::npos) {
					string entry=StringTrim(value.substr(0,pos));
					value=StringTrim(value.substr(pos+1));
					Engine->Insert(entry,value);
				}
			} else if(key=="set") {
				string::size_type pos=value.find_first_of(" \t");
				if(pos!=string::npos) {
					string entry=StringTrim(value.substr(0,pos));
					value=StringTrim(value.substr(pos+1));
					Engine->InsertAfterClear(entry,value);
				}
			} else if(key=="include") {
				LoadINI(datapath+value,datapath,dictfiles);
#ifdef I18N_HACK
			} else if(key=="locale") {
				string s = lang.setLocale(value);
				if(LogFS) {
					(*LogFS) << "Setting Locale \"" << value << "\": ";
					if (s =="") {
						(*LogFS) << "Failed";
					} else {
						(*LogFS) << "Succeeded (" << s << ")";
					}
					(*LogFS) << endl;
				}
#endif
			} else if(key=="debug") {
				if(value=="log") {
					if(!LogFS) LogFS=new ofstream((datapath+"kawari.log").c_str());
				} else if(value=="debugger") {
					if(LogFS) (*LogFS) << "Debugger Enable" << endl;

					Engine->Insert("event.ShioriEcho","${system.Reference0}\\e");
					Engine->Insert("event.KawariCommand","$(echo \"$(\"${system.Reference0}\")\" )\\e");
				}
			} else if(key=="saori") {
				vector<string> args;
				string::size_type curp = 0;
				string::size_type nextp;
				while(1) {
					string param;
					nextp = value.find(',', curp);
					if (nextp == string::npos) {
						param = value.substr(curp);
					} else {
						param = value.substr(curp, nextp - curp);
					}
					args.push_back(StringTrim(param));
					if (nextp == string::npos) break;
					curp = nextp + 1;
				}
				if(args.size()==2||args.size()==3) {
					TKawariEngine::SAORILOADTYPE loadopt=TKawariEngine::LOADONCALL;
					if (args.size()>=3){
						if (args[2]=="preload")
							loadopt=TKawariEngine::PRELOAD;
						else if (args[2]=="noresident")
							loadopt=TKawariEngine::NORESIDENT;
					}
					Engine->RegisterSAORIModule(args[1], Engine->GetDataPath()+args[0], loadopt);
					if (LogFS) {
						(*LogFS) << "SAORI:";
						(*LogFS) << " regist " << args[0];
						(*LogFS) << " as " << args[1];
						(*LogFS) << endl;
					}
				}
			}
		}
	}
	ifs.close();

	return(true);
}
//---------------------------------------------------------------------------
// �������ƃt�@�C���ǂݍ���
bool TNS_KawariANI::LoadSub(const string& datapath,const string& inifile)
{
	Engine->SetDataPath(datapath);

	// ���̃^�C�~���O�ŗ������������܂�
	SRandom((int)time(NULL));

	// �ǂݍ��ނׂ������t�@�C���ꗗ
	vector<string> dictfiles;

	// ini�t�@�C���̓ǂݍ���
	LoadINI(inifile,datapath,dictfiles);

	if(dictfiles.size()) {
		for(unsigned int i=0;i<dictfiles.size();i++) {
			LoadFile(datapath+dictfiles[i],"dict");
		}
	}

	string aistr=GetSentence("system.OnLoad");
	if(LogFS) (*LogFS) << aistr << endl;

	// �Z�L�����e�B���x�����Ⴂ�Ƃ��́Ahomeurl�̕ύX���֎~����
	if(SecurityLevel.Get()<3) Engine->WriteProtect("resource.homeurl");

	return(true);
}
//---------------------------------------------------------------------------
// �ȉ��̃G���g���͓��ʈ��������
//
// �ȉ��͖{�̂���̒ʒm���
// system.OtherGhost        : NOTIFY�Œʒm���ꂽ�S�[�X�g��
// system.OtherGhostEx      : NOTIFY�Œʒm���ꂽ�S�[�X�g��(�T�[�t�F�X�ԍ��t)
// system.Reference0        : �C�x���g����Reference0�`7
//        |
// system.Reference7
// system.Sender            : �b���|���Ă����S�[�X�g���A���̓V�X�e����
// system.Sender.Path       : Sender�̌o�H���(SYSTEM/LOCAL/UNKNOWN/EXTERNAL)
// system.Age               : COMMUNICATE�̉�
// system.Sentence          : �n���ꂽ����
// system.EventName         : ���������C�x���g��
// system.ID                : �v�����ꂽ���\�[�XID
// system.BalloonOffset     : �o���[���̃I�t�Z�b�g
//
// �ȉ��̓X�N���v�g����ؘa���ւ̒ʒm
// system.communicate       : �b���|�������S�[�X�g��
//                            "stop"��COMMUNICATE�ł��؂�
// system.Response0         : COMMUNICATE�œn��Reference0�`7
//        |
// system.Response7
//
// �ȉ��̓C�x���g����
// event.�C�x���g��         : �O���C�x���g����
// resource.���\�[�X��      : SHIORI/2.5���\�[�X�擾
// system.OnLoad            : �ǂݍ��݃C�x���g(�����C�x���g)
// system.OnUnload          : �؂藣���C�x���g(�����C�x���g)
// system.OnTeach           : SHIORI/2.4Teach�C�x���g(�����C�x���g)
// system.OnResponse        : �����C�x���g(�����C�x���g)
// system.OnResponseUnknown : �����s���C�x���g(�����C�x���g)
// system.OnNotifyGhost     : �S�[�X�g���ʒm�C�x���g(�����C�x���g)
// system.OnNotifyOther     : ���S�[�X�g���ʒm�C�x���g(�����C�x���g)
// system.OnGetStatus       : �X�e�[�^�X�擾�C�x���g(�����C�x���g)
// system.OnEventUnknown    : SHIORI/2.2����`�C�x���g(�����C�x���g)
// system.OnTranslate       : SHIORI/2.6
//
// �ȉ���getword,getdms�p
// compatible.ms           : ����-�l
// compatible.mz           : ����-���@��
// compatible.mc           : ����-�Ж�
// compatible.mh           : ����-�X��
// compatible.mt           : ����-�Z
// compatible.me           : ����-�H��
// compatible.mp           : ����-�n���݂����Ȃ���
// compatible.m            : ����-�����
// compatible.dms          : �u�`�Ɂ`����`�v�I�ȁA�i���������A�����ꂽ���߂̖���
//
//---------------------------------------------------------------------------

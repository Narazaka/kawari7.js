//---------------------------------------------------------------------------
//
// "�ؘa��" for ����ȊO�̉����ȊO�̉���
// KawariInlineScript -- ���� --
//
//      Programed by NAKAUE.T (Meister)
//
//  2001.05.14  Phase 0.50    First version
//  2001.05.19  Phase 5.1     ��������
//  2001.06.17  Phase 6.0     ������������
//  2001.08.08  Phase 6.2     ostrstream�o�O�C��
//
//---------------------------------------------------------------------------
#include "config.h"
//---------------------------------------------------------------------------
#include "kis/kis_date.h"
//---------------------------------------------------------------------------
#include <string>
#include <vector>
#include <ctime>
#include <strstream>
#include <iomanip>
using namespace std;
//---------------------------------------------------------------------------
string KIS_date::Function(const vector<string>& args)
{
	time_t nowtt=time(NULL);
	struct tm *now=localtime(&nowtt);

	string format="%y/%m/%d %H:%M:%S";
	if(args.size()>=2) format=args[1];

	ostrstream ret;
	format+=' ';	// �_�~�[
	for(unsigned int i=0;i<(format.size()-1);i++) {
		if(format[i]=='%') {
			i++;
			switch(format[i]) {
			case 'd':	// �� (01..31)
				ret << setw(2) << setfill('0') << now->tm_mday;
				break;
			case 'e':	// �� (1..31)
				ret << now->tm_mday;
				break;
			case 'H':	// �� (00..23)
				ret << setw(2) << setfill('0') << now->tm_hour;
				break;
			case 'j':	// ��������̒ʎZ�� (001..366)
				ret << setw(3) << setfill('0') << (now->tm_yday+1);
				break;
			case 'J':	// ��������̒ʎZ�� (1..366)
				ret << (now->tm_yday+1);
				break;
			case 'k':	// �� (0..23)
				ret << now->tm_hour;
				break;
			case 'm':	// �� (01..12)
				ret << setw(2) << setfill('0') << (now->tm_mon+1);
				break;
			case 'M':	// �� (00..59)
				ret << setw(2) << setfill('0') << now->tm_min;
				break;
			case 'n':	// �� (1..12)
				ret << (now->tm_mon+1);
				break;
			case 'N':	// �� (0..59)
				ret << now->tm_min;
				break;
			case 'r':	// �b (0..59)
				ret << now->tm_sec;
				break;
			case 'S':	// �b (00..59)
				ret << setw(2) << setfill('0') << now->tm_sec;
				break;
			case 'w':	// �j�� (0..6) ���j����0
				ret << now->tm_wday;
				break;
			case 'y':	// �N (2000...) 4��
			case 'Y':	// �N (2000...) 4��
				ret << (now->tm_year+1900);
				break;
			case '%':
				ret << '%';
				break;
			default:
				ret << '%';
				i--;
			}
		} else {
			ret << format[i];
		}
	}
	ret << ends;

	string retstr(ret.str());
	ret.freeze(false);

	return(retstr);
}
//---------------------------------------------------------------------------



                         KAWARI SHIORI�� ����ȭ ��ŷ

							����� ���ֿ�
							(sanori@sanori.net)
����
====
�̰��� Meister�� �˷��� Nakaue T �Բ��� ������ KAWARI SHIORI (���� ī�͸�)��
patch�Դϴ�. �� patch�� �����Ͻø� KSC-5601 �ѱ۷� �ۼ��� ī�͸� ������
������ ���� ���� ����Ͻ� �� �ֽ��ϴ�.
����� �ѱ� �� �ƴ϶� �߱��� ���� �ϵ��ƽþƾ� �� ���Ͼ�� ���� �������
�ۼ��� ������ ����� �� �ֵ��� ��������ϴ�.

����
====
(�ڼ��� ������ readme-i18n.en.txt�� ������ �ֽʽÿ�)

���
====
(�ڼ��� ������ readme-i18n.en.txt�� ������ �ֽʽÿ�)

����
======   
1. �ѱ��� (Ȥ�� �� �Ϻ���) ��Ʈ�� shiori.dll�� �� ��ġ�� ���Ե� ������
   �ٲ۴�.

2. kawari.ini�� ������(locale) �̸��� �� �ִ´�. ������� �ѱ�����

	locale: ko_ko.eucKR

   �Ǵ� �ٿ���

   	locale: ko

   ��� �� �ִ´�.

   �Ϲ������� ������ �̸��� ������ ���� ���¸� ������.

	language[_territory][.codeset][@modifier]

   language : ISO 639 2���� ��� �ڵ�
   territory: ISO 3166 2���� ����
   codeset  : ISO-8859-1 Ȥ�� UTF-8�� ���� ��ȣȭ�� �������� �̸�

   �� �ڵ忡 ���ؼ��� ���� ������ ã�ƺ� �� �ִ�.
	http://www.ics.uci.edu/pub/ietf/http/related/iso639.txt
	http://www.ics.uci.edu/pub/ietf/http/related/iso3166.txt

   ���� �����Ǵ� ��� ������:
	en(����), fr(��������), de(���Ͼ�), es(�����ξ�), ru(���þƾ�),
	ja(�Ϻ���), ko(�ѱ���), zh(�߱���)

   ���� �����Ǵ� ��ȣȭ�� �������� �̸�:
	iso-8859-1, iso-8859-2, iso-8859-5, SJIS(shift_jis),
	EUC-JP, EUC-KR, EUC-CN, EUC-TW, BIG5, KOI8,
	UTF8 (KIS���� 'expr'�Լ��� ���� ����, ���� ���۵�)

������ ���
===========
�� patch�� �ҽ�ȭ�� ���� patch ȭ�ϸ��� ������ �ֽ��ϴ�. ����
���� compile�� �Ϸ��� http://meister-d-i.hoops.ne.jp/ ����
kawari-2001-0825-1900�� �޾ƿ��� �� patch ������� �ҽ��� ��ġ�ž�
�մϴ�.

�������� MinGW���� �ۿ� �غ��� ���߽��ϴ�. ����� 

	make -r -f mingw_kawari.mak

�� src ���丮���� �����ϸ� �˴ϴ�.

* ��: �ֱ��� ������� ���Ͽ�, �� ��ġ�� KAWARI-731-kpcg "������" ��
      (http://users.goo.ne.jp/shobu/ ���� ã�� �� ����)�� �⺻���� �մϴ�.
      ����, M$ Visual C++ 6.0 ���� �׽�Ʈ�Ǿ����ϴ�. �ٸ� �����Ϸ���
      ����Ϸ���, �ش� �����Ϸ��� MAKEFILEF �������� I18N_HACK �� �ڵ�����
      �����ϵ��� ��ġ�ñ� �ٶ��ϴ�.

ȯ��
====
����ȯ��: MinGW 1.0.1 on M$ Windows 98 SE  (http://www.mingw.org)
	  (�׷����ϴ�. ��� compiler�� �ƴϰ� cygwin1.dll�� �ʿ�����ϴ�. -- �����)
          M$ Visual C++ 6.0 on M$ Windows 98 SE
          (��, ���� ������ ������ ����� :P -- whoami)
����ȯ��: M$ Windows 98 SE Korean

���
====
ī�͸��� '����'��� �������α׷��� �κ��� �����մϴ�. '����'�� ���ؼ���

	http://futaba.mikage.to/ (�Ϻ���) 
	http://yser.cool4u.co.kr/nanika/ (�ѱ���)
	http://homepage1.nifty.com/znc/ (����)

���� ����Ʈ�� �����Ͻñ� �ٶ��ϴ�.

���� �ֱ� ������ ī�͸��� http://meister-d-i.hoops.ne.jp/ ���� ã�� �� �ֽ��ϴ�.
* ��: "������" ���� http://users.goo.ne.jp/shobu/ ���� ã�� �� �ֽ��ϴ�.


����
====
2002.01.11  "������" �� KAWARI-731-kpcg �� ����.
            whoami (uotakie@kebi.com)
2001.10.09  KIS�� 'expr'���� ����� ���� �ذ�. �׷��� ������ UTF-8�� �ȵȴ�.
            whoami (uotalkie@kebi.com)
2001.09.09  �ѱ��� �� �ƴ϶� �ٸ� �� ó���ϰԲ� ����ȭ
            Visual C++�����ۿ� compile �ȵǰ� �� �κ� ���� (�����)
2001.09.03  EUC-KR�� ��ȣȭ�� �ѱ�� ó���� �� �ֵ��� kawari�� patch.
            whoami (uotalkie@kebi.com)



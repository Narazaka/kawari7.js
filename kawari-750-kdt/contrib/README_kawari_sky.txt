
�ؘa��20010914-sky

-----------------------------------------------------------------------------
09/14/2001

sky / �������͐����ł��B

���̃p�b�P�[�W��Mesiter���J���ɂ��
�u"�ؘa��" for ����ȊO�̉����ȊO�̉����v Phase 7.0
�ɑ΂���o�O�t�B�b�N�X���s�������̂ł��B

�T�����ȍ~�A�{�Ɓu����ȊO�̉����ȊO�̉����v���W�F�N�g�v����������i��
�o��Ǝv���܂��B


-----------------------------------------------------------------------------
[ �p�b�P�[�W���e ]

  shiori-20010914-sky.dll      �ؘa��
  kosui-20010914-sky.exe       �K��
  README_kawari_sky.txt        ���̃h�L�������g
  kawari-20010914-sky.patch    �p�b�` from �{��Phase 7.0
  readme.html                  �I���W�i���ɕt���̃h�L�������g
  + document /                 ���Ɓ[���쐬�A�x�[�^��Phase 7.0�h�L�������g


-----------------------------------------------------------------------------
[ 20010914�ύX�_ ]

�E3���ȏ��AND�����Ɋւ���o�O�t�B�b�N�X

  ${entry1 & entry2}����AND�����^�G���g���Ăяo���ɂ����āA3���ڈȍ~�̃G���g��
�w�肪��������Ă��������t�B�b�N�X�B


-----------------------------------------------------------------------------
[ 20010907�ύX�_ ]

�E�Z�L�����e�B�p�b�`�B������redo34�ύX�_�ɑΉ��B

  SHIORI�́A���̉\��Sender��Event�w�b�_�ɗ��邱�ƂȂ��A�S�ẴC�x���g��
�`�B�o�H��m��K�v������B�ڂ����͌��Ȃ����ASSTP��ʂ��ĊO�����爫�ӂ���
�C�x���g�R�[�h�𑗂邱�Ƃɂ��A�V�X�e���ɒv���I�Ȕ�Q��^���邱�Ƃ��\��
����ł���B

  �Z�L�����e�B�΍�Ƃ��āAredo20���_�ŁA�{�Ƃ͈ȉ��̂悤�Ȏd�l���߂��B

����EMBRYO - �S SHIORI ���N�G�X�g�� Sender �w�b�_�t���B
��Sender: embryo
���Ƃ������d�l���ł͂����ƑO����t���Ă����̂ŁA�t���Ă��Ȃ����Ƃ̕�����
����B

����EMBRYO - SSTP Notify �ɂ���ă��[�J���}�V���O�Ŕ��������C�x���g�� 
��Sender �� External �ƒ�`�B
�����ǂ̂Ƃ���N���V�ѕ����v�����Ȃ��̂ŗv����� External ���u���b�N����
�������̓��e�ɂȂ�Ǝv���܂��B

  �����ŉؘa�� Phase 7.0�ł́ASender�̒l����C�x���g�����̑��s�𔻒f����X
�e�b�v��݂����B���f��͈ȉ��̒ʂ�ł������B

  level 4: "embryo"�̂݋���
  level 3: "External"�ASender�s���ȊO������ (�܂�A������Ă���DirectSSTP
           �͒ʂ�)
  level 2: "External"�ȊO������(������Ă��Ȃ�DirectSSTP��ʂ�)
  level 1: (level2�Ɠ��l)
  level 0: �S�ċ���

  ����ɑ΂�redo34�ɂ����āA�{�Ƃ͐V���Ȏd�l���߂��B

����EMBRYO - SSTP NOTIFY �ɂ��C�x���g�ʒm���S�� Sender: External �ɂȂ�
�������C���B��������SSTP NOTIFY �� Sender ���Z�b�g����̂��Ó��Ǝv����B
��
��Sender: �L�ǂ�� (local)
��Sender: �L�ǂ�� (external)
��
�������ۂ̔L�ǂ�ӃC�x���g�� Sender �����������B

  ����̃p�b�`�͂��̎d�l�ύX�ɔ������̂ł���B
  ����̖{�Ǝd�l�ύX�ɂ���āA�o�H���Ƃ�����'Sender'�𕪗����邱�Ƃ���
�\�ƂȂ����B�]���āA�t�B���^�����O�͌o�H���݂̂ɗ�����̂Ƃ����B
  ���f��2�X�e�b�v�ƂȂ�B

STEP1:
  �o�H�����肷��B

  SYSTEM  : "Sender: embryo"
  LOCAL   : (local)�����Ă������
  UNKNOWN : "Sender: User"(�R�~���j�P�[�g�{�b�N�X)�Ȃ�
  EXTERNAL: (external)�����Ă������

  �o�H���ȊO��system.Sender����폜�B
  �o�H���('system'/'local'/'external'/'unknown')��system.Sender.Path�Ɋi�[
(EXPERIMENTAL)�B

STEP2:
  �o�H�Ɋ�Â��ăt�B���^�����O����B

  level 4: SYSTEM�̂݋�����
  level 3: SYSTEM, LOCAL��������
  level 2: SYSTEM, LOCAL, UNKNOWN��������
  level 1: (level 2�Ɠ��l)
  level 0: �S�ċ�����

  ������Ȃ������ꍇ�A400 Bad Request���Ԃ�BNOTIFY/1.1�̏ꍇ��"�ی�"
Sentence���\������邱�Ƃ�����B


-----------------------------------------------------------------------------
[ �A���� ]
�I�t�B�V������O��(�����A�u�g���|���v�A�u�����c�v)�̌f���͑S�Č��Ă��܂��B
���̂Ƃ���̌f���A���[���ł��\���܂���B
http://www.yk.rim.or.jp/~suikyo/
suikyo@yk.rim.or.jp

�z�z�����͏C��BSD�ł��B


-----------------------------------------------------------------------------
[ �ӎ� ]

���񋟂��Ă����������ؘa���J����/�S�[�X�g�x���_�̊F�l�A
upx���g�킹�Ē����Ă���Markus F.X.J. Oberhumer����
# http://wildsau.dv.uni-linz.ac.at/mfx/
�Ɋ��ӂ������܂��B



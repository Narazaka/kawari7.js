
# -rオプション(デフォルトルール抑制)付で実行してください

include files.mak

.SUFFIXES : .cxx .cpp .hxx .h

MACHSRC = ./saori/saori_win32.cpp

KAWAOBJ =  $(KAWASRC:.cpp=.o) $(MACHSRC:.cpp=.o)

SHIOOBJ =  $(SHIOSRC:.cpp=.o)

CRYPTOBJ = $(CRYPTSRC:.cpp=.o)

CFLAGS = -O3 -I. -DUSEKDB -DI18N_HACK -UWIN32 -U_WIN32 -U_Windows -U__CYGWIN__ -s ALLOW_MEMORY_GROWTH=1
EXPORTED_FUNCTIONS = "['_load','_unload','_request']"
LIBS   = 

#UPX = upx
#UPX = rem
# upxは実行ファイル圧縮ツール
# http://wildsau.idv.uni-linz.ac.at/mfx/upx.html
# を参照してください


## TARGETS ##

ALLTARGET = ./shiori_js/kawari7.js ./tool/kosui.exe ./tool/kawari_encode.exe

all : $(ALLTARGET)


./shiori_js/kawari7.js : ./shiori_js/shiori.o $(SHIOOBJ) $(KAWAOBJ)
	em++ -o $@ $? $(LIBS) -shared -O3 --memory-init-file 0 --pre-js em-pre.js --post-js em-post.js -s EXPORTED_FUNCTIONS=$(EXPORTED_FUNCTIONS) -s ALLOW_MEMORY_GROWTH=1 -s DISABLE_EXCEPTION_CATCHING=0


./tool/kosui.exe : ./tool/kosui.o ./tool/kdb.o $(KAWAOBJ)
	em++ -o $@ ./tool/kosui.o ./tool/kdb.o $(KAWAOBJ) $(LIBS)


./tool/kawari_encode.exe : ./tool/kawari_encode.o $(CRYPTOBJ)
	em++ -o $@ ./tool/kawari_encode.o $(CRYPTOBJ) $(LIBS)


%.o : %.cxx
	em++ $(CFLAGS) $(SHIORIVER) -o $@ -c $<

%.cxx : %.cpp
	cp $< $@
#	ruby sjis2ascii.rb < $< > $@

%.hxx : %.h
	cp $< $@
#	ruby sjis2ascii.rb < $< > $@



cleanxx : 
	-rm ./kis/*.cxx ./libkawari/*.cxx ./shiori_dll/*.cxx ./shiori_js/*.cxx ./shiori/*.cxx ./saori/*.cxx ./tool/*.cxx ./misc/*.cxx
	-rm ./kis/*.hxx ./libkawari/*.hxx ./shiori_dll/*.hxx ./shiori_js/*.hxx ./shiori/*.hxx ./saori/*.hxx ./tool/*.hxx ./misc/*.hxx
	-rm config.hxx

clean : cleanxx
	-rm $(KAWAOBJ) $(SHIOOBJ) $(CRYPTOBJ) ./shiori_dll/shiori.o ./shiori_js/shiori.o ./tool/kosui.o ./tool/kdb.o ./tool/kawari_encode.o 

cleanall : clean
	-rm $(ALLTARGET)

depend : clean
	ruby ./makedepend.rb --with-sjis2ascii > depend.mak


include depend.mak


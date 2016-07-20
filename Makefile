BUILD_DIR = ./kawari7/src

all:
	cd $(BUILD_DIR) && $(MAKE) -f emscripten_kawari.mak ./shiori_js/kawari7.js
	cp ./kawari7/src/shiori_js/kawari7.js kawari7.js

clean:
	cd $(BUILD_DIR) && $(MAKE) -f emscripten_kawari.mak clean

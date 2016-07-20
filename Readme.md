kawari7.js
=======================================

Programmable pseudo AI KAWARI 7 on JavaScript

Original SHIORI module
---------------------------------------

[KAWARI](http://kawari.sourceforge.net/) by KAWARI Development Team

**Caution**:
This module is maintained by [Narazaka](http://narazaka.net/) and not officially supported by KAWARI Development Team.
Do not report bugs or something that is caused by kawari.js to KAWARI Development Team.

Installation
---------------------------------------

    npm install kawari7.js

or

    bower install kawari7.js

or download zip archive and get kawari7.js

Usage
---------------------------------------

This module has only low level API, that is provided by emscripten.

So use the wrapper module, [nativeshiori](https://github.com/Narazaka/nativeshiori), and do like below.

    <script src="encoding.min.js"></script>
    <script src="nativeshiori.js"></script>
    <script src="kawari7.js"></script>
    <script>
    
    var kawari_ini_str = 'dict : dict.txt\r\n';
    var kawari_ini = Encoding.convert(Encoding.stringToCode(kawari_ini_str), 'SJIS', 'UNICODE');
    var dict_txt_str = 'event.OnBoot : Hello World\r\n';
    var dict_txt = Encoding.convert(Encoding.stringToCode(dict_txt_str), 'SJIS', 'UNICODE');
    var storage = {
      'kawari.ini': new Uint8Array(kawari_ini), // filename: ArrayBufferView
      'dict.txt': new Uint8Array(dict_txt)
    };
    
    // Shiori instance and optional storage (/path/to/ghost/master/*)
    var nativeshiori = new NativeShiori(new Kawari7(), storage);
    
    // write files in storage to FS then load() if storage exists, else load()
    var load_code = nativeshiori.load('/path/to/ghost/master'); 
    
    // request()
    var response = nativeshiori.request('GET Sentence SHIORI/2.6\r\nCharset: Shift_JIS\r\nEvent: OnBoot\r\n\r\n');
    
    // unload()
    var unload_code = nativeshiori.unload();
    
    </script>

LICENSE
--------------------------------

(C) 2016 Narazaka : Licensed under [The BSD 3-Clause License](http://narazaka.net/license/BSD3?2016)

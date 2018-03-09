# wasm-test

compile version : emscripten 1.37.33

compile command : emcc call.c -s WASM=1 -o call.js -s EXPORTED_FUNCTIONS="['_getvalue','_set_parameter','_getsrting','_WebAssembly_func']" -s EXTRA_EXPORTED_RUNTIME_METHODS="['ccall','cwrap','setValue']" -s FETCH=1

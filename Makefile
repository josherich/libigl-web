default_target: link

.PHONY : default_target

MAKE = emcc

nrosy:
	$(MAKE) hard_nrosy.cpp --std=c++11 -o nrosy.bc -s USE_PTHREADS=1 -s PTHREAD_POOL_SIZE=2 -s USE_GLFW=3

glad:
	$(MAKE) glad.c -o glad.bc -s USE_PTHREADS=1 -s PTHREAD_POOL_SIZE=2 -s USE_GLFW=3 -s ASSERTIONS=2 -s ALIASING_FUNCTION_POINTERS=0

src/main.cpp:
	$(MAKE) main.cpp --std=c++11 -o main.bc -s USE_PTHREADS=1 -s PTHREAD_POOL_SIZE=2 -s USE_GLFW=3 -s ASSERTIONS=2 -s ALIASING_FUNCTION_POINTERS=0 -s  SAFE_HEAP=1 -s FULL_ES2=1 -s FULL_ES3=1 -s USE_WEBGL2=1 -s WEBGL2_BACKWARDS_COMPATIBILITY_EMULATION=1 -s DEMANGLE_SUPPORT=1

link: nrosy glad src/main.cpp
	$(MAKE) nrosy.bc main.bc glad.bc -o index.html --preload-file data -Os -s USE_PTHREADS=1 -s TOTAL_MEMORY=67108864 -s WASM=1 -s PTHREAD_POOL_SIZE=2 -s USE_GLFW=3 -s ASSERTIONS=2 -s ALIASING_FUNCTION_POINTERS=0 -s  SAFE_HEAP=1 -s FULL_ES2=1 -s FULL_ES3=1 -s USE_WEBGL2=1 -s WEBGL2_BACKWARDS_COMPATIBILITY_EMULATION=1 -s DEMANGLE_SUPPORT=1

.PHONY : link

SOURCES=`find ./src/* -mindepth 1 -name '*.cpp'`
DIST=build

emcc -O3 -std=c++1z -s WASM=1 -s NO_EXIT_RUNTIME=1 -s USE_WEBGL2=1 -s FULL_ES3=1 -s USE_GLFW=3 -o $DIST/out.js ./src/main.cpp $SOURCES


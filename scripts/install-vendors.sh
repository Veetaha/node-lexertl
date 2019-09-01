# Build fmtlib with emscripten
(
cd vendor/fmt && 
mkdir build && 
cd build && 
emcmake cmake .. -DFMT_TEST=false &&
emmake make
)

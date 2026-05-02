odyssey

cd build
cmake ..
make
./odyssey

// use the current folder as the src dir, and generate the build files in the build folder
// build whatever was generated in build
cmake -S . -B build
cmake --build build

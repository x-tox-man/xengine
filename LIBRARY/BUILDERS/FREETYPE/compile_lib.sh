mkdir LIBS
mkdir -p HEADERS/include/freetype/internal/services
mkdir -p HEADERS/include/freetype/config

cd ../../COMMON/FREETYPE/

brew install automake
brew install libtool
brew install autoconf

make setup ansi
make

cp **/*.a ../../BUILDERS/FREETYPE/LIBS/
cp -R include/ ../../BUILDERS/FREETYPE/HEADERS/include

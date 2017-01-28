mkdir LIBS
mkdir -p HEADERS
mkdir BUILDIR

cd ../../COMMON/ZLIB

./configure
make

cp *.a ../../BUILDERS/ZLIB/LIBS/
cp *.h ../../BUILDERS/ZLIB/HEADERS/

mkdir LIBS
mkdir -p HEADERS
mkdir BUILDIR

curl -R -O http://www.lua.org/ftp/lua-5.3.3.tar.gz
tar zxf lua-5.3.3.tar.gz
cd lua-5.3.3
make macosx
cd ..
cp src/*.a LIBS/
cp src/*.h HEADERS/

mkdir -p HEADERS
mkdir -p BUILDDIR
mkdir -p LIBS

CD BUILDDIR

cmake ../../COMMON/JSON/
make

cp ../../COMMON/JSON/*.hpp ../../BUILDERS/JSON/HEADERS/

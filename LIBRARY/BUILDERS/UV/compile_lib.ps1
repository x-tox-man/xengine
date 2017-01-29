brew install pkgconfig
brew install --universal pcre

mkdir BUILDIR
mkdir LIBS
mkdir HEADERS

cd BUILDIR

cmake -G Xcode ../../../COMMON/OPENCOLLADA
xcodebuild ONLY_ACTIVE_ARCH=NO -configuration Release -target ALL_BUILD clean
xcodebuild ONLY_ACTIVE_ARCH=NO -configuration Release -target ALL_BUILD

cp lib/Release/*.a ../LIBS/

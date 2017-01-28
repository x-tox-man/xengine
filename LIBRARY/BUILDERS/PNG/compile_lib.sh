mkdir LIBS
mkdir -p HEADERS
mkdir BUILDIR

cd ../../COMMON/PNG

cmake -G "Xcode"

xcodebuild ONLY_ACTIVE_ARCH=NO -configuration Release -target ALL_BUILD clean
xcodebuild ONLY_ACTIVE_ARCH=NO -configuration Release -target ALL_BUILD

cp **/*.a ../../BUILDERS/PNG/LIBS/
cp *.h ../../BUILDERS/PNG/HEADERS/

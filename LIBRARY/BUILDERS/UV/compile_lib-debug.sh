#REQUIRES NODE JS
npm install -g node-gyp

mkdir LIBS
mkdir -p HEADERS/include
mkdir BUILDIR

cd ../../COMMON/UV

./gyp_uv.py -f xcode
xcodebuild ONLY_ACTIVE_ARCH=NO -project uv.xcodeproj clean
xcodebuild ONLY_ACTIVE_ARCH=NO -project uv.xcodeproj -configuration Debug -target All

cp *.a ../../BUILDERS/UV/LIBS/
cp include/ ../../BUILDERS/UV/HEADERS/

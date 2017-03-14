#REQUIRES NODE JS
npm install -g node-gyp

mkdir LIBS-ANDROID
mkdir -p HEADERS-ANDROID/include
mkdir BUILDIR-ANDROID

cd ../../COMMON/UV/
#cd BUILDIR-ANDROID
export NDK_DIR_LOC=/Users/CBE/Library/Developer/Xamarin/android-sdk-macosx/ndk-bundle

export TOOLCHAIN=$PWD/android-toolchain
mkdir -p $TOOLCHAIN
$NDK_DIR_LOC/build/tools/make-standalone-toolchain.sh \
    --toolchain=arm-linux-androideabi-4.9 \
    --arch=arm \
    --install-dir=$TOOLCHAIN \
    --platform=android-16 \
    --force
export PATH=$TOOLCHAIN/bin:$PATH
export AR=arm-linux-androideabi-ar
export CC=arm-linux-androideabi-gcc
export CXX=arm-linux-androideabi-g++
export LINK=arm-linux-androideabi-g++
export PLATFORM=android

#cd ../../../COMMON/UV

git clone https://chromium.googlesource.com/external/gyp build

gyp_uv.py -Dtarget_arch=arm -DOS=android -f make-android

make -C out

cp *.a ../../BUILDERS/UV/LIBS/
cp include/ ../../BUILDERS/UV/HEADERS/

sudo rm -R android-toolchain

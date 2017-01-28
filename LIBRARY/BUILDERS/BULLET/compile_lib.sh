

mkdir LIBS

mkdir -p HEADERS

cd ../../COMMON/BULLET/

cd build3

chmod +x premake4_osx
./premake4_osx xcode4
cd xcode4

xcodebuild -workspace 0_Bullet3Solution.xcworkspace -scheme Bullet3Common ONLY_ACTIVE_ARCH=NO -configuration Release
xcodebuild -workspace 0_Bullet3Solution.xcworkspace -scheme Bullet3Collision ONLY_ACTIVE_ARCH=NO -configuration Release
xcodebuild -workspace 0_Bullet3Solution.xcworkspace -scheme Bullet3Dynamics ONLY_ACTIVE_ARCH=NO -configuration Release
xcodebuild -workspace 0_Bullet3Solution.xcworkspace -scheme Bullet3Geometry ONLY_ACTIVE_ARCH=NO -configuration Release
cd ..

#./premake4_linux gmake
#./premake4_linux64 gmake
#./premake4_osx gmake

#cd gmake
#make
#cd ..

cd ..

pwd
cp **/*.a ../../BUILDERS/BULLET/LIBS
rm **/*.a

ditto  src/**/*.h ../../BUILDERS/BULLET/HEADERS

#cp -R **/*.h ../../BUILDERS/BULLET/HEADERS/ --parents
#find src -name "*.h" -exec cp --parents \{\} ../../BUILDERS/BULLET/HEADERS/ \;
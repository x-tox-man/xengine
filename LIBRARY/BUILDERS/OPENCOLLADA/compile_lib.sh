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

mkdir -p ../HEADERS/COLLADABaseUtils/include
cp -R ../../../COMMON/OPENCOLLADA/COLLADABaseUtils/include/ ../HEADERS/COLLADABaseUtils/include/

mkdir -p ../HEADERS/COLLADAFramework/include
cp -R ../../../COMMON/OPENCOLLADA/COLLADAFramework/include/ ../HEADERS/COLLADAFramework/include/

mkdir -p ../HEADERS/COLLADASaxFrameworkLoader/include
cp -R ../../../COMMON/OPENCOLLADA/COLLADASaxFrameworkLoader/include/ ../HEADERS/COLLADASaxFrameworkLoader/include/

mkdir -p ../HEADERS/COLLADAStreamWriter/include
cp -R ../../../COMMON/OPENCOLLADA/COLLADAStreamWriter/include/ ../HEADERS/COLLADAStreamWriter/include/
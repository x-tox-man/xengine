brew install pkgconfig
brew install pcre

mkdir BUILDIR
cd BUILDIR

cmake -G Xcode ../../../COMMON/OPENCOLLADA
xcodebuild ONLY_ACTIVE_ARCH=NO -configuration Release -target ALL_BUILD clean
xcodebuild ONLY_ACTIVE_ARCH=NO -configuration Release -target ALL_BUILD

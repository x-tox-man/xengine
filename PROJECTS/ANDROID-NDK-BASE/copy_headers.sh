mkdir HEADERS
rm HEADERS/*.h

find ../../CODE  -name "*.h" -exec cp {} HEADERS \;
find ../../CODE  -name "*.hpp" -exec cp {} HEADERS \;
find ../XCODE  -name "*.h" -exec cp {} HEADERS \;
find ../XCODE  -name "*.hpp" -exec cp {} HEADERS \;
rm HEADERS/*WINDOWS*
rm HEADERS/*OSX*
rm HEADERS/*IOS*
rm HEADERS/*OPENGL_2*


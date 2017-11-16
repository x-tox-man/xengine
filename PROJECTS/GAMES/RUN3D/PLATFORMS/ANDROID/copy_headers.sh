mkdir HEADERS
rm HEADERS/*.h
rm HEADERS/*.hpp

find /Users/christophebernard/Develop/Project/game-engine/CODE   -name "*.h" -exec cp {} HEADERS \;
find /Users/christophebernard/Develop/Project/game-engine/CODE   -name "*.hpp" -exec cp {} HEADERS \;
find /Users/christophebernard/Develop/Project/game-engine/PROJECTS/GAMES/RUN3D/CODE  -name "*.h" -exec cp {} HEADERS \;
find /Users/christophebernard/Develop/Project/game-engine/PROJECTS/GAMES/RUN3D/CODE  -name "*.hpp" -exec cp {} HEADERS \;

rm HEADERS/*WINDOWS*
rm HEADERS/*OSX*
rm HEADERS/*IOS*
rm HEADERS/*OPENGL_2*


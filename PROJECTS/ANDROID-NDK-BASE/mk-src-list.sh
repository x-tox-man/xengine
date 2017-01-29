cd jni/
echo 'LOCAL_SRC_FILES := ' > "../engine.mk"
find ../../../CODE  -name "*.cpp" | grep -v IOS | grep -v OSX | grep -v WINDOWS | grep -v OPENGL_ | grep -v _OPENGL | grep -v FONT_EDITOR | grep -v ATLAS_COMPILER | grep -v COLLADA | grep -v Gte >> "../engine.mk"
find ../../../PROJECTS/XCODE/GAME-ENGINE-REBORN  -name "*.cpp" | grep -v IOS | grep -v OSX | grep -v WINDOWS | grep -v OPENGL_ | grep -v _OPENGL | grep -v FONT_EDITOR | grep -v ATLAS_COMPILER | grep -v COLLADA | grep -v Gte >> "../engine.mk"
cd ..
sed -i -e 's/$/ \\/' "engine.mk"

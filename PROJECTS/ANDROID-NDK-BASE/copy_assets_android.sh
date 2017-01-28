rm -R assets
mkdir assets
find ../../RESOURCES -name "*" -not -path "*OPENGL2/*" -exec cp {}  assets \;

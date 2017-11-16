rm -R assets
mkdir assets
find ../../../../../RESOURCES -name "*" -not -path "*OPENGL2/*" -exec cp {}   app/src/main/assets \;

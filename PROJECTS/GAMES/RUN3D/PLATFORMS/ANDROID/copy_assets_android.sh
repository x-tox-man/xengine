rm -R assets
mkdir assets
find ../../../../../RESOURCES -name "*" -not -path "*OPENGL4/*" -not -path "*MODELS_BASE/*" -not -path "*TEXTURES_BASE/*" -exec cp {}   app/src/main/assets \;

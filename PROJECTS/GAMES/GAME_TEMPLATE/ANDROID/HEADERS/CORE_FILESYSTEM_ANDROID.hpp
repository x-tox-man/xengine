//
//  CORE_FILESYSTEM_ANDROID.hpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 2/08/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

public :

AAssetDir * GetAndroidAssetDirectory() { return AssetDirectory; }
AAssetManager * GetAndroidAssetManager() { return AssetManager; }

void SetJNIEnv( JNIEnv* jni ) { JNIEnvironment = jni; }
void SetAssetManagerObject( jobject manager) { JAVAManagerObject = manager; }
void SetAssetManager( AAssetManager * manager) { AssetManager = manager; }
void SetAssetDirectory( AAssetDir * dir ) { AssetDirectory = dir; }

AAssetManager *GetAssetManager() { return AssetManager; }
JNIEnv* GetJNIEnvironment() { return JNIEnvironment; }

private :

AAssetDir * AssetDirectory;
AAssetManager * AssetManager;
jobject JAVAManagerObject;
JNIEnv* JNIEnvironment;
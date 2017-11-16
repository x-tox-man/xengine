//
//  CORE_FILESYSTEM_FILE_ANDROID.hpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 2/08/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

public :
    inline AAsset * GetAssetFile() { return AssetFile; }
    int OpenFileDescriptor();

private :

    AAsset
        * AssetFile;

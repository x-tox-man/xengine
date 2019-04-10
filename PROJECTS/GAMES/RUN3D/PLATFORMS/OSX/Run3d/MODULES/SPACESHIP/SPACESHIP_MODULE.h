//
//  SPACESHIP_MODULE.hpp
//  RUN3D
//
//  Created by Christophe Bernard on 09/04/2019.
//  Copyright © 2019 IGZ. All rights reserved.
//

#ifndef SPACESHIP_MODULE_hpp
#define SPACESHIP_MODULE_hpp

#include "RUN3D_APPLICATION.h"

extern "C" void Load( RUN3D_APPLICATION & context );
extern "C" void Reload( RUN3D_APPLICATION & context );
extern "C" void Initialize();
extern "C" void FinalizeTest( RUN3D_APPLICATION & context );

#endif /* SPACESHIP_MODULE_hpp */

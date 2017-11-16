//
//  GAME.hpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 22/01/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#ifndef GAME_hpp
#define GAME_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GAMEPLAY_SCENE.h"

XS_CLASS_BEGIN( GAME )

GAME();
virtual ~GAME();

virtual void Initialize();
virtual void Update( const float);
virtual void Finalize();

virtual void Start();
virtual void Pause();
virtual void Resume();
virtual void End();

GAMEPLAY_SCENE * GetScene() { return Scene; }

private :

long int
    GameStartTime;
GAMEPLAY_SCENE
    * Scene;

XS_CLASS_END

#endif /* GAME_hpp */

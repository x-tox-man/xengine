//
//  APPLICATION_SCREENS_NAVIGATION.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 31/10/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#include "APPLICATION_SCREENS_NAVIGATION.h"
#include "GRAPHIC_UI_ANIMATION.h"

APPLICATION_SCREENS_NAVIGATION::APPLICATION_SCREENS_NAVIGATION() {
    
}

APPLICATION_SCREENS_NAVIGATION::~APPLICATION_SCREENS_NAVIGATION() {
    
}

bool APPLICATION_SCREENS_NAVIGATION::NavigateBackAsync() {
    
    auto item = GetPreviousItem();
    
    if ( item == NULL )
        return false;
    
    CORE_MATH_VECTOR start_position = item->GetFrame()->GetPosition();
    CORE_MATH_VECTOR destination(-GRAPHIC_UI_SYSTEM::GetInstance().GetScreenSize().X(), 0.0f );
    
    auto anim = new GRAPHIC_UI_ANIMATION(
        this->CurrentNavigationItem->GetFrame(),
        [] (GRAPHIC_UI_ELEMENT * element ) {
            
        },
        [start_position, destination] (GRAPHIC_UI_ELEMENT * element, float percentage) {
            float total = sinf( percentage * M_PI_2 );
            element->SetPosition( start_position + destination * total );
            
            element->SetOpacity( 1.0f - total );
        },
        [ this, item ] (GRAPHIC_UI_ELEMENT * element) {
            
            CORE_PARALLEL_TASK_BEGIN(this, item)
                CORE_PARALLEL_TASK_SYNCHRONIZE_WITH_MUTEX(GRAPHIC_UI_SYSTEM::GetInstance().GetLockMutex())
                    if ( this->CurrentNavigationItem != NULL ) {

                        GRAPHIC_UI_SYSTEM::GetInstance().UnregisterScreen(this->CurrentNavigationItem->GetScreenName().c_str());
                    }

                    this->CurrentNavigationItem = item;

                    GRAPHIC_UI_SYSTEM::GetInstance().RegisterView(this->CurrentNavigationItem->GetFrame(), CurrentNavigationItem->GetScreenName().c_str());
                CORE_PARALLEL_TASK_SYNCHRONIZE_WITH_MUTEX_END()
            CORE_PARALLEL_TASK_END()
        },
        2.66f);
    
    GRAPHIC_UI_SYSTEM::GetInstance().CommitAnimation( anim );
    
    return true;
}

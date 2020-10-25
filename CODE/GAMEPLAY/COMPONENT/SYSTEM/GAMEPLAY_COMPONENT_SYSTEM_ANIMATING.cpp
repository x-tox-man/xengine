//
//  GAMEPLAY_COMPONENT_SYSTEM_ANIMATING.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 1/04/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "GAMEPLAY_COMPONENT_SYSTEM_ANIMATING.h"
#include "GAMEPLAY_COMPONENT_ANIMATION.h"
#include "GAMEPLAY_COMPONENT_RENDER.h"
#include <execution>
#include <thread>
#include <algorithm>
#include <mutex>

GAMEPLAY_COMPONENT_SYSTEM_ANIMATING::GAMEPLAY_COMPONENT_SYSTEM_ANIMATING() :
    GAMEPLAY_COMPONENT_SYSTEM() {
    
}

GAMEPLAY_COMPONENT_SYSTEM_ANIMATING::~GAMEPLAY_COMPONENT_SYSTEM_ANIMATING() {

}

void GAMEPLAY_COMPONENT_SYSTEM_ANIMATING::Initialize() {
    
}

void GAMEPLAY_COMPONENT_SYSTEM_ANIMATING::Update( void * ecs_base_pointer, float time_step ) {
    
    {
        int nloop = EntitiesTable.size();
        
        
        
        //printf( "----------- START ----------\n" );
        const size_t nthreads = std::thread::hardware_concurrency();
          {
            std::vector< std::thread > threads(nthreads);
            std::mutex critical;
              
            for( int t = 0; t < nthreads; t++ )
            {
              threads[t] = std::thread(std::bind(
                [&](const int bi, const int ei, const int t)
                {
                  // loop over all items
                  for( int i = bi ; i < nloop; i+=nthreads )
                  {
                    // inner loop
                    {
                        // (optional) make output critical
                        //

                        auto entity = ( GAMEPLAY_COMPONENT_ENTITY *) (((int*) ecs_base_pointer) + EntitiesTable[i].GetOffset());
                        GAMEPLAY_COMPONENT_ANIMATION * animation = entity->GetComponent<GAMEPLAY_COMPONENT_ANIMATION>();
                        
#if DEBUG
                        assert( animation != NULL );
#endif
                        
                        animation->Update( time_step, & animation->GetAnimation().GetAnimation(0)->GetSkeleton() );
                    }
                  }
                }, t, nloop, nthreads ) );
            }
              
            std::lock_guard<std::mutex> lock(critical);
            std::for_each(threads.begin(),threads.end(),[](std::thread& x){x.join();});
          }
    }
    
    
    /*std::for_each(
                  EntitiesTable.begin(),
                  EntitiesTable.end(),
                  [ecs_base_pointer, time_step](GAMEPLAY_COMPONENT_ENTITY_HANDLE & item)
    {
        auto entity = ( GAMEPLAY_COMPONENT_ENTITY *) (((int*) ecs_base_pointer) + item.GetOffset());
        GAMEPLAY_COMPONENT_ANIMATION * animation = entity->GetComponent<GAMEPLAY_COMPONENT_ANIMATION>();
        GAMEPLAY_COMPONENT_RENDER * render = entity->GetComponent<GAMEPLAY_COMPONENT_RENDER>();
        
        assert( animation != NULL || render != NULL );
        
        animation->Update( time_step, & animation->GetAnimation().GetAnimation(0)->GetSkeleton() );
        //it++;
    });*/
}

void GAMEPLAY_COMPONENT_SYSTEM_ANIMATING::Finalize() {
    
    GAMEPLAY_COMPONENT_SYSTEM::Finalize();
}

void GAMEPLAY_COMPONENT_SYSTEM_ANIMATING::Render( void * ecs_base_pointer, GRAPHIC_RENDERER & renderer ) {
    
    CORE_RUNTIME_Abort();
}

//
//  CORE_TIMELINE.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 3/05/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__CORE_TIMELINE__
#define __GAME_ENGINE_REBORN__CORE_TIMELINE__

#include "CORE_HELPERS_CLASS.h"
#include "CORE_DATA_BUFFER.h"
#include "CORE_TIMELINE_EVENT.h"
#include "CORE_HELPERS_CALLBACK.h"

XS_CLASS_BEGIN( CORE_TIMELINE )

    XS_DEFINE_SERIALIZABLE

    CORE_TIMELINE();
    virtual    ~CORE_TIMELINE();

    void Update( float time_step );
    void Reset();
    void InsertNewEvent( CORE_TIMELINE_EVENT * event );
    void CancelEvent( CORE_TIMELINE_EVENT * item );
    inline float GetTimeOffset() const { return TimeOffset; }
    inline void SetOnEventAddedCallback( const CORE_HELPERS_CALLBACK_1< CORE_TIMELINE_EVENT * > & callback ) { OnEventAddedCallback = callback; }
    inline void SetOnEventCancelledCallback( const CORE_HELPERS_CALLBACK_1< CORE_TIMELINE_EVENT * > & callback ) { OnEventCancelledCallback = callback; }

private :

    void InsertNextEvent( CORE_TIMELINE_EVENT * event, std::list< CORE_TIMELINE_EVENT * >::iterator existing_event );
    void InsertPreviousEvent( CORE_TIMELINE_EVENT * event, std::list< CORE_TIMELINE_EVENT * >::iterator existing_event );

    float TimeOffset;
    std::list< CORE_TIMELINE_EVENT * > EventTable;
    std::list< CORE_TIMELINE_EVENT * >::iterator CurrentItem;
    CORE_HELPERS_CALLBACK_1< CORE_TIMELINE_EVENT * >
        OnEventAddedCallback,
        OnEventCancelledCallback;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__CORE_TIMELINE__) */

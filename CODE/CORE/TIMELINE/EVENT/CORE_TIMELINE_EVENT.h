//
//  CORE_TIMELINE_EVENT.hpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 8/02/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#ifndef CORE_TIMELINE_EVENT_h
#define CORE_TIMELINE_EVENT_h

#include "CORE_HELPERS_CLASS.h"
#include "CORE_HELPERS_UNIQUE_IDENTIFIER.h"
#include "CORE_TIMELINE_COMMAND.h"

XS_CLASS_BEGIN( CORE_TIMELINE_EVENT )

    XS_DEFINE_SERIALIZABLE

    CORE_TIMELINE_EVENT();

    inline float GetStart() const { return Start; }
    inline float GetEnd() const { return End; }
    inline bool HasEnded() const { return Ended; }
    inline bool IsCancelled() const { return Cancelled; }

    void Setup( float start, float end, const CORE_HELPERS_UNIQUE_IDENTIFIER & identifier, CORE_TIMELINE_COMMAND * command );
    void Complete();

    void SetCommand( CORE_TIMELINE_COMMAND * command ) { Command = command; }
    CORE_TIMELINE_COMMAND * GetCommand() { return Command;}

private :

    long
        Id;
    float
        Start,
        End;
    bool
        Ended,
        Cancelled;
    CORE_HELPERS_UNIQUE_IDENTIFIER
        Identifier;
    CORE_TIMELINE_COMMAND
        * Command;

XS_CLASS_END

#endif /* CORE_TIMELINE_EVENT_hpp */

//
//  GAMEPLAY_RULE_PROPERTY_GROUP.hpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 4/03/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#ifndef GAMEPLAY_RULE_PROPERTY_GROUP_hpp
#define GAMEPLAY_RULE_PROPERTY_GROUP_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GAMEPLAY_RULE.h"

class GAMEPLAY_RULE_PROPERTY;
class GAMEPLAY_PLAYER;

XS_CLASS_BEGIN_WITH_ANCESTOR( GAMEPLAY_RULE_PROPERTY_GROUP, GAMEPLAY_RULE )

    GAMEPLAY_RULE_PROPERTY_GROUP();
    virtual ~GAMEPLAY_RULE_PROPERTY_GROUP();

    virtual void OnVisit( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) override {}
    virtual void OnPassOntoCell( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) override {}
    virtual void OnLeftCell( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) override {}
    virtual void OnStoppedCell( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) override {}
    virtual bool Apply( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) override { return true; }

    void AddProperty( GAMEPLAY_RULE_PROPERTY * property );
    bool DoesPlayerOwnAllPropertiesInGroup( GAMEPLAY_PLAYER * player);
    bool HouseOnGroupAreEven(int size_to_ask );
    inline std::vector<GAMEPLAY_RULE_PROPERTY *> & GetProperties() { return Properties; }

    XS_DEFINE_SERIALIZABLE

private:

    std::vector<GAMEPLAY_RULE_PROPERTY *>
        Properties;

XS_CLASS_END


#endif /* GAMEPLAY_RULE_PROPERTY_GROUP_hpp */

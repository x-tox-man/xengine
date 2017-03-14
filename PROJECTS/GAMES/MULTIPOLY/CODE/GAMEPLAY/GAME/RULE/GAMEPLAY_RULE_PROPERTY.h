//
//  GAMEPLAY_RULE_FIELD.hpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 24/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#ifndef GAMEPLAY_RULE_PROPERTY_hpp
#define GAMEPLAY_RULE_PROPERTY_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GAMEPLAY_RULE.h"
#include "GAMEPLAY_RULE_PROPERTY_GROUP.h"
#include "GAMEPLAY_GAME_HOUSE.h"

XS_CLASS_BEGIN_WITH_ANCESTOR_2( GAMEPLAY_RULE_PROPERTY, GAMEPLAY_RULE, GAMEPLAY_ACTION )

    GAMEPLAY_RULE_PROPERTY();
    GAMEPLAY_RULE_PROPERTY( int front_price, int rent_price, int house_price, int mortgage_price, GAMEPLAY_RULE_PROPERTY_GROUP * group );
    virtual ~GAMEPLAY_RULE_PROPERTY();

    virtual void OnVisit( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) override;
    virtual void OnPassOntoCell( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) override;
    virtual void OnLeftCell( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) override;
    virtual void OnStoppedCell( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) override;
    virtual bool Apply( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) override;
    virtual void OnPicked(GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) override;
    virtual void OnDismiss(GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) override;

    inline GAMEPLAY_PLAYER * GetOwner() { return Owner; }
    inline std::vector< GAMEPLAY_GAME_HOUSE * > & GetHouseTable() { return HouseTable; }
    inline bool IsInMortgage() const { return ItIsInMortgage; }
    inline void SetIsInMortgage( bool in_mortgage ) { ItIsInMortgage = in_mortgage; }
    inline GAMEPLAY_RULE_PROPERTY_GROUP * GetPropertyGroup() { return PropertyGroup; }

    void Buy( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player);
    virtual bool CanBuyHouse( GAMEPLAY_PLAYER * player );
    void BuyHouse( GAMEPLAY_SCENE * scene, GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player, GAMEPLAY_GAME_HOUSE * house );

    XS_DEFINE_SERIALIZABLE

    CORE_HELPERS_FACTORY_Element( GAMEPLAY_RULE_PROPERTY, GAMEPLAY_ACTION, GAMEPLAY_ACTION_TYPE, GAMEPLAY_ACTION_TYPE_Custom_15 )

    virtual void Apply() override;

    SimpleTrickForSerialization()

private:

    virtual int CalculateAmount( GAMEPLAY_PLAYER * player );
    void ProposeBuy( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player);
    void ProposeBuyHouse( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player);
    void TransferTo( GAMEPLAY_PLAYER * player);

    GAMEPLAY_PLAYER
        * Owner;
    GAMEPLAY_RULE_PROPERTY_GROUP
        * PropertyGroup;
    int
        BuyPrice,
        HousePrice,
        RentPrice,
        MortgagePrice;
    bool
        ItIsInMortgage;
    std::vector< GAMEPLAY_GAME_HOUSE * >
        HouseTable;

XS_CLASS_END

#endif /* GAMEPLAY_RULE_PROPERTY_hpp */

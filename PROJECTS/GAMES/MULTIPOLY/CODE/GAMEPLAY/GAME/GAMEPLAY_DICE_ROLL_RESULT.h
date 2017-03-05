//
//  GAMEPLAY_DICE_ROLL_RESULT.h
//  MULTIPOLY
//
//  Created by Christophe Bernard on 25/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#ifndef GAMEPLAY_DICE_ROLL_RESULT_h
#define GAMEPLAY_DICE_ROLL_RESULT_h

typedef struct {
    
    int FirstDice;
    int SecondDice;
    int Total;
    int DoublesInRowCount;
    bool IsDouble;
} GAMEPLAY_DICE_ROLL_RESULT;

#endif /* GAMEPLAY_DICE_ROLL_RESULT_h */

//
//  PERIPHERIC_INTERRACTION_MOUSE.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 29/03/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__PERIPHERIC_INTERACTION_MOUSE__
#define __GAME_ENGINE_REBORN__PERIPHERIC_INTERACTION_MOUSE__

#include "CORE_HELPERS_CLASS.h"
#include "CORE_MATH_VECTOR.h"

XS_CLASS_BEGIN( PERIPHERIC_INTERACTION_MOUSE )

PERIPHERIC_INTERACTION_MOUSE();

enum MOUSE_BUTTON_STATE{
    MOUSE_BUTTON_STATE_Up = 0x0000,
    MOUSE_BUTTON_STATE_Pressed = 0x0001,
    MOUSE_BUTTON_STATE_Released = 0x0010
};

void Initialize();
void Update();

inline void SetLeftButtonClicked() { LeftButton = LeftButton | MOUSE_BUTTON_STATE_Pressed; }
inline void SetRightButtonClicked() { RightButton = RightButton | MOUSE_BUTTON_STATE_Pressed; }

inline const CORE_MATH_VECTOR & GetPointCoordinates() { return PointCoordinates; }
inline const CORE_MATH_VECTOR & GetScreenCoordinates() { return ScreenCoordinates; }
inline const CORE_MATH_VECTOR & GetPreviousScreenCoordinates() { return PreviousScreenCoordinates; }
inline const CORE_MATH_VECTOR & GetNormalizedDisplacement() { return NormalizedDisplacement; }
inline const CORE_MATH_VECTOR & GetCenteredCoordinates() { return CenteredCoordinates; }

inline void SetLeftButtonReleased() {
    
    LeftButton = LeftButton | MOUSE_BUTTON_STATE_Released;
    LeftButton = LeftButton & ~MOUSE_BUTTON_STATE_Pressed;
}

inline void SetRightButtonReleased() {
    
    RightButton = RightButton | MOUSE_BUTTON_STATE_Released;
    RightButton = RightButton & ~MOUSE_BUTTON_STATE_Pressed;
}

inline void SetScreenCoordinates( const float x, const float y ) {
    
    ScreenCoordinates.Set(x, y, 0.0f, 1.0f );
    CenteredCoordinates.Set(x -0.5f, y-0.5f, 0.0f, 1.0f );
}

inline void SetScrollCoordinates( const float x, const float y ) {
    
    ScrollCoordinates.Set(x, y, 0.0f, 1.0f );
}

inline void SetPointCoordinates( const float x, const float y ) {
    
    PointCoordinates.Set(x, y, 0.0f, 1.0f );
}

inline void AddNormalizedDisplacement( const float x, const float y ) {
    
    
    NormalizedDisplacement[0] += x;
    NormalizedDisplacement[1] += y;
}

inline bool GetLeftButtonClicked() { return LeftButton & MOUSE_BUTTON_STATE_Pressed; }
inline bool GetRightButtonClicked(){ return RightButton & MOUSE_BUTTON_STATE_Pressed; }

inline bool GetLeftButtonReleased() { return LeftButton & MOUSE_BUTTON_STATE_Released; }
inline bool GetRightButtonReleased(){ return RightButton & MOUSE_BUTTON_STATE_Released; }

private :

int LeftButton;
int RightButton;

CORE_MATH_VECTOR
    ScreenCoordinates,
    CenteredCoordinates,
    PointCoordinates,
    NormalizedDisplacement,
    PreviousScreenCoordinates,
    ScrollCoordinates;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__PERIPHERIC_INTERACTION_MOUSE__) */

//
//  R3D_UI.h
//  Run3d
//
//  Created by Christophe Bernard on 28/12/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#ifndef Header_h
#define Header_h

#define DESIGNER_W 1024.0f
#define DESIGNER_H 768.0f

#include "CORE_MATH_VECTOR.h"

class R3D_UI {
    
public:
    static const CORE_MATH_VECTOR & AdaptSize( const CORE_MATH_VECTOR & v ) {
        
        static const float x_ratio = ScreenWidth / DESIGNER_W;
        static const float y_ratio = ScreenHeight / DESIGNER_H;
        
        const_cast<CORE_MATH_VECTOR &>(v).X( v.X() * x_ratio );
        const_cast<CORE_MATH_VECTOR &>(v).Y( v.Y() * y_ratio );
        
        return v;
    }
    
    static const CORE_MATH_VECTOR & AdaptPosition( const CORE_MATH_VECTOR & v ) {
        static const float x_ratio = ScreenWidth / DESIGNER_W;
        static const float y_ratio = ScreenHeight / DESIGNER_H;
        
        //const_cast<CORE_MATH_VECTOR &>(v).X( v.X() * x_ratio, v.Y() * y_ratio, v.Z(), v.W() );
        return v;
    }
    
    static float
        ScreenWidth,
        ScreenHeight,
        ScreenDensity;
};

#endif /* Header_h */

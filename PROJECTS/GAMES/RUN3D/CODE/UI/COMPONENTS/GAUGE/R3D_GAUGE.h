//
//  R3D_GAUGE.hpp
//  RUN3D
//
//  Created by Christophe Bernard on 5/01/18.
//  Copyright © 2018 IGZ. All rights reserved.
//

#ifndef R3D_GAUGE_hpp
#define R3D_GAUGE_hpp

#include "GRAPHIC_UI_FRAME.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( R3D_GAUGE, GRAPHIC_UI_FRAME )

    R3D_GAUGE();

    virtual void Initialize() override;

    void SetPercent( float percent );
    void SetColor( const CORE_HELPERS_COLOR & color );

    void SetPercentAnimated( float percent );
    void SetColorAnimated( const CORE_HELPERS_COLOR & color );

private:

    float
        Percent;
    static CORE_HELPERS_IDENTIFIER
        Gauge;

XS_CLASS_END

#endif /* R3D_GAUGE_hpp */

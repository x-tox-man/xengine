//
//  RESOURCE_REPRESENTATION.hpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 31/05/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#ifndef RESOURCE_REPRESENTATION_hpp
#define RESOURCE_REPRESENTATION_hpp

#include "CORE_HELPERS_CLASS.h"
#include "RESOURCE.h"

XS_CLASS_BEGIN( RESOURCE_REPRESENTATION )

    RESOURCE_REPRESENTATION();
    ~RESOURCE_REPRESENTATION();

    void SetResourceForRepresentation(int representation, BASE_RESOURCE * resource );

private:

    std::vector<BASE_RESOURCE *>
        ResourceRepresentationTable;

XS_CLASS_END

#endif /* RESOURCE_RESPRESENTATION_hpp */

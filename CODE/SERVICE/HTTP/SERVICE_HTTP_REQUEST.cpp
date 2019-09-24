//
//  SERVICE_HTTP_REQUEST.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 04/03/2019.
//  Copyright © 2019 Christophe Bernard. All rights reserved.
//

#include "SERVICE_HTTP_REQUEST.h"

SERVICE_HTTP_REQUEST::SERVICE_HTTP_REQUEST( const char * path, const char * body, SERVICE_HTTP_REQUEST_TYPE method ) :
    Body( body ),
    Path( path ),
    Method( method ) {

}

SERVICE_HTTP_REQUEST::~SERVICE_HTTP_REQUEST() {
    
}

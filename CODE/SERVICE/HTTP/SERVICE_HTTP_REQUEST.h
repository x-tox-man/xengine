//
//  SERVICE_HTTP_REQUEST.hpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 04/03/2019.
//  Copyright © 2019 Christophe Bernard. All rights reserved.
//

#ifndef SERVICE_HTTP_REQUEST_hpp
#define SERVICE_HTTP_REQUEST_hpp

#include "CORE_HELPERS_CLASS.h"
#include <curl/curl.h>

enum SERVICE_HTTP_REQUEST_TYPE {
    SERVICE_HTTP_REQUEST_TYPE_Post,
    SERVICE_HTTP_REQUEST_TYPE_Get,
    SERVICE_HTTP_REQUEST_TYPE_Put,
    SERVICE_HTTP_REQUEST_TYPE_Delete,
    SERVICE_HTTP_REQUEST_TYPE_Path,
    SERVICE_HTTP_REQUEST_TYPE_Node
};

XS_CLASS_BEGIN( SERVICE_HTTP_REQUEST )

    SERVICE_HTTP_REQUEST( const char * path, const char * body, SERVICE_HTTP_REQUEST_TYPE method );
    ~SERVICE_HTTP_REQUEST();

    SERVICE_HTTP_REQUEST_TYPE
        Method;
    const char
        * Body,
        * Path;

private:

XS_CLASS_END

#endif /* SERVICE_HTTP_REQUEST_hpp */

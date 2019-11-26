//
//  SERVICE_HTTP_CLIENT.hpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 03/03/2019.
//  Copyright © 2019 Christophe Bernard. All rights reserved.
//

#ifndef SERVICE_HTTP_CLIENT_hpp
#define SERVICE_HTTP_CLIENT_hpp

#include "CORE_HELPERS_CLASS.h"
#include "CORE_HELPERS_UNIQUE.h"
#include "CORE_HELPERS_CALLBACK.h"
#include "SERVICE_HTTP_REQUEST.h"

#include <curl/curl.h>

#define BASE_URL_MAX_LEN 256

#define CURL_CHECK( __METHOD__ ) \
    { \
        CURLcode result = __METHOD__ \
        if ( result != CURLE_OK ) { \
            printf( "curl_easy_perform() failed: %s\n", curl_easy_strerror( result ) ); \
        }\
    }

struct CurlOutMemoryStruct {
    char
        * Memory;
    size_t
        Size;
};

XS_CLASS_BEGIN( SERVICE_HTTP_CLIENT )

    XS_DEFINE_UNIQUE( SERVICE_HTTP_CLIENT )

    ~SERVICE_HTTP_CLIENT();

    void SetBaseUrl( const char * base_url );
    void SetHeader(  const char * header_value );
    void PerformRequestAsync( SERVICE_HTTP_REQUEST & request );

private:

    CURL *
        CurlEasyHandle;
    char
        BaseUrl[ BASE_URL_MAX_LEN ];
    struct CurlOutMemoryStruct
        Chunk;
    struct curl_slist *
        Headers;

XS_CLASS_END

#endif /* SERVICE_HTTP_CLIENT_hpp */

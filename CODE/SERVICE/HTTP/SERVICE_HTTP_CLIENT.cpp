//
//  SERVICE_HTTP_CLIENT.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 03/03/2019.
//  Copyright © 2019 Christophe Bernard. All rights reserved.
//

#include "SERVICE_HTTP_CLIENT.h"

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    size_t realsize = size * nmemb;
    struct CurlOutMemoryStruct * mem = (struct CurlOutMemoryStruct *)userp;
    
    char *ptr = (char *) realloc(mem->Memory, mem->Size + realsize + 1);
    if(ptr == NULL) {
        /* out of memory! */
        printf("not enough memory (realloc returned NULL)\n");
        return 0;
    }
    
    mem->Memory = ptr;
    memcpy(&(mem->Memory[mem->Size]), contents, realsize);
    mem->Size += realsize;
    mem->Memory[mem->Size] = 0;
    
    return realsize;
}

SERVICE_HTTP_CLIENT::SERVICE_HTTP_CLIENT() :
    CurlEasyHandle( NULL ),
    Chunk(),
    Headers( NULL ),
    BaseUrl() {
    
    Chunk.Memory = (char*) malloc(1);  /* will be grown as needed by the realloc above */
    Chunk.Size = 0;    /* no data at this point */
    
    curl_global_init( CURL_GLOBAL_ALL );
    CurlEasyHandle = curl_easy_init();
    
    /* send all data to this function  */
    curl_easy_setopt( CurlEasyHandle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
    
    /* we pass our 'chunk' struct to the callback function */
    curl_easy_setopt( CurlEasyHandle, CURLOPT_WRITEDATA, (void *) &Chunk );
    curl_easy_setopt( CurlEasyHandle, CURLOPT_USERAGENT, "libcurl-agent/1.0");
    
    /* pass our list of custom made headers */
    curl_easy_setopt(CurlEasyHandle, CURLOPT_HTTPHEADER, Headers);
}

SERVICE_HTTP_CLIENT::~SERVICE_HTTP_CLIENT() {
    
    free( Chunk.Memory );
    curl_easy_cleanup( CurlEasyHandle );
    curl_global_cleanup();
    
    if ( Headers ) {
        
        curl_slist_free_all( Headers ); /* free the header list */
    }
}

void SERVICE_HTTP_CLIENT::SetBaseUrl( const char * base_url ) {
    
    CORE_DATA_COPY_STRING( BaseUrl, base_url );
}

void SERVICE_HTTP_CLIENT::SetHeader(  const char * header_value ) {
    
    Headers = curl_slist_append( Headers, header_value );
}

void SERVICE_HTTP_CLIENT::PerformRequestAsync( SERVICE_HTTP_REQUEST & request ) {
    
    char LOCAL_TotalUrl[256 * 2];
    
    CORE_DATA_COPY_STRING( LOCAL_TotalUrl, BaseUrl );
    CORE_DATA_STRING_CONCAT(LOCAL_TotalUrl, request.Path );
    
    switch ( request.Method ) {
        case SERVICE_HTTP_REQUEST_TYPE_Get:
            
            break;
        
        case SERVICE_HTTP_REQUEST_TYPE_Post:
            
            curl_easy_setopt(CurlEasyHandle, CURLOPT_POST, 1);
            /* post binary data */
            curl_easy_setopt(CurlEasyHandle, CURLOPT_POSTFIELDS, request.Body);
            
            /* set the size of the postfields data */
            curl_easy_setopt(CurlEasyHandle, CURLOPT_POSTFIELDSIZE, strlen( request.Body ) );
            
            break;
        default:
            abort(); // TODO
            break;
    }
    /* get it! */
    
    curl_easy_setopt( CurlEasyHandle, CURLOPT_URL, LOCAL_TotalUrl );
    curl_easy_setopt( CurlEasyHandle, CURLOPT_HTTPHEADER, Headers );
    
    CURL_CHECK( curl_easy_perform( CurlEasyHandle ); )
}

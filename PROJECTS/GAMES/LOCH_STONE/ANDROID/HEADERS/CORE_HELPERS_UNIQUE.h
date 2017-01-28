
//
//  UNIQUE.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 3/11/13.
//  Copyright (c) 2013 Christophe Bernard. All rights reserved.
//

#ifndef __UNIQUE__
#define __UNIQUE__

template < typename __NAMED_CLASS__ >
class UNIQUE {
public:
    
    static __NAMED_CLASS__ & GetInstance() {
        return InnerInstance ? *InnerInstance : CreateInstance();
    }
    
    void RemoveInstance() {
        if ( InnerInstance ) {
            delete InnerInstance;
        }
        else {
            // Do something to crash te app
        }
    }
    
private :
    UNIQUE() {
        
    }
    
    static __NAMED_CLASS__ & CreateInstance() {
        InnerInstance = new __NAMED_CLASS__();
        
        return *InnerInstance;
    }
    
    static __NAMED_CLASS__ *InnerInstance;
};

template < typename __NAMED_CLASS__ >
__NAMED_CLASS__ * UNIQUE<__NAMED_CLASS__>::InnerInstance = 0;

#define XS_DEFINE_UNIQUE( __CLASS_NAME__ ) \
    public : friend class UNIQUE< __CLASS_NAME__ >; \
    private : \
        __CLASS_NAME__(); \
    public : \
        static __CLASS_NAME__ & GetInstance() { \
            return UNIQUE< __CLASS_NAME__ >::GetInstance(); \
        }

#endif

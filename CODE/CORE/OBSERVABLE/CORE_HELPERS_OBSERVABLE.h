//
//  CORE_HELPERS_OBSERVABLE.hpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 6/01/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#ifndef CORE_HELPERS_OBSERVABLE_hpp
#define CORE_HELPERS_OBSERVABLE_hpp

#include "CORE_RUNTIME_ENVIRONMENT.h"
#include "CORE_HELPERS_CALLBACK.h"
#include "SERVICE_LOGGER.h"

template <typename __OBSERVABLE_CLASS__>
class __INNER_OBSERVABLE__ {
public:
    
    __INNER_OBSERVABLE__( __OBSERVABLE_CLASS__ * instance ) : InnerCallbackTable() {
        
        ObservableInstance = instance;
    }
    
    template <typename __SOURCE_CLASS__>
    void AddObserver(__SOURCE_CLASS__ * object) {
        
        auto * callback =
        new CORE_HELPERS_CALLBACK_1<__OBSERVABLE_CLASS__ *>(
            &Wrapper1<__SOURCE_CLASS__, __OBSERVABLE_CLASS__ *, &__SOURCE_CLASS__::NotifyPropertyChanged >, object );
        
        InnerCallbackTable.push_back( callback );
        
#if DEBUG
        if ( InnerCallbackTable.size() > 10 )
        {
            SERVICE_LOGGER_Info("WARNING : a lot of observers" );
        }
#endif
    }
    
    template <typename __SOURCE_CLASS__>
    void RemoveObserver( __SOURCE_CLASS__ * object ) {
        
        typename std::vector<CORE_HELPERS_CALLBACK_1< __OBSERVABLE_CLASS__ *> * >::iterator it = InnerCallbackTable.begin();
        
        while (it != InnerCallbackTable.end() ) {
            
            if ( (*it)->GetObjectPointer() == (void *) object) {
                
                InnerCallbackTable.erase(it);
                
                break;
            }
        }
    }
    
    void NotifyObservers() {
        
        typename std::vector<CORE_HELPERS_CALLBACK_1< __OBSERVABLE_CLASS__ *> * >::iterator it = InnerCallbackTable.begin();
        
        while (it != InnerCallbackTable.end() ) {
            (*it)->operator()(ObservableInstance);
        }
    }
    
private:
    
    std::vector<CORE_HELPERS_CALLBACK_1< __OBSERVABLE_CLASS__ *> * > InnerCallbackTable;
    __OBSERVABLE_CLASS__ * ObservableInstance;
};

#define XS_DEFINE_OBSERVABLE(__OBSERVABLE_CLASS__ ) \
    private : \
    __INNER_OBSERVABLE__<__OBSERVABLE_CLASS__>  * __InnerObservable; \
    public: \
    void InitializeObservable() { \
        __InnerObservable = new __INNER_OBSERVABLE__<__OBSERVABLE_CLASS__>( this ); \
    }\
    template <typename __SOURCE_CLASS__> \
    void AddObserver(__SOURCE_CLASS__ * object) { __InnerObservable->AddObserver<__SOURCE_CLASS__>( object ); } \
    template <typename __SOURCE_CLASS__> \
    void RemoveObserver(__SOURCE_CLASS__ * object) { __InnerObservable->RemoveObserver<__SOURCE_CLASS__>( object ); } \
    void NotifyObservers() { __InnerObservable->NotifyObservers(); }

#endif /* CORE_HELPERS_OBSERVABLE_hpp */

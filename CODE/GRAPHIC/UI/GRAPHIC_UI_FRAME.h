//
//  GRAPHIC_UI_FRAME.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 16/06/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__GRAPHIC_UI_FRAME__
#define __GAME_ENGINE_REBORN__GRAPHIC_UI_FRAME__

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_UI_ELEMENT.h"
#include "CORE_HELPERS_IDENTIFIER.h"

#include "CORE_ABSTRACT_PROGRAM_FACTORY.h"
#include "CORE_ABSTRACT_RUNTIME_LUA.h"
#include "CORE_ABSTRACT_PROGRAM_BINDER.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( GRAPHIC_UI_FRAME, GRAPHIC_UI_ELEMENT )

    GRAPHIC_UI_FRAME();
    virtual ~GRAPHIC_UI_FRAME();

    CORE_ABSTRACT_PROGRAM_DECLARE_CLASS( GRAPHIC_UI_FRAME );

    virtual void Initialize() override;
    virtual void Finalize()  override{}

    virtual void Update( const float ) override;
    virtual void Render( GRAPHIC_RENDERER & ) override;
    virtual void Click( const CORE_MATH_VECTOR & cursor_position ) override;
    virtual void Hover( const CORE_MATH_VECTOR & cursor_position ) override;
    virtual void Hover( const bool force_hover ) override;

    virtual GRAPHIC_UI_ELEMENT * GetObjectForIdentifier( const CORE_HELPERS_IDENTIFIER & ) override;
    virtual GRAPHIC_UI_ELEMENT * GetObjectAtIndex(int index );
    virtual GRAPHIC_UI_ELEMENT * Contains( const CORE_MATH_VECTOR & cursor_position ) override;
    virtual void SetObjectForIdentifier( const CORE_HELPERS_IDENTIFIER &, GRAPHIC_UI_ELEMENT * element);
    virtual void OnPlacementPropertyChanged() override;

    void AddObject( GRAPHIC_UI_ELEMENT * );
    void RemoveObject( GRAPHIC_UI_ELEMENT * );
    void RemoveObjects();

    void SetOffset( const CORE_MATH_VECTOR & offset ) { GetPlacement().SetOffset( offset );OnPlacementPropertyChanged(); }

    GRAPHIC_UI_ELEMENT * GetElement( const char * element_name );
    std::map< CORE_HELPERS_IDENTIFIER, GRAPHIC_UI_ELEMENT * > & GetNamedElementTable() { return NamedElementTable; }
    std::vector<GRAPHIC_UI_ELEMENT *> & GetElementTable() { return ElementTable; }

    virtual GRAPHIC_UI_ELEMENT * Copy() override;
    virtual void SetOpacity( float opacity ) override;

    friend class GRAPHIC_UI_PRESENTER;

protected:

virtual GRAPHIC_UI_ELEMENT * InnerCopy( GRAPHIC_UI_FRAME * other_frame );

private :

    std::vector<GRAPHIC_UI_ELEMENT *>
        ElementTable;
    std::map< CORE_HELPERS_IDENTIFIER, GRAPHIC_UI_ELEMENT * >
        NamedElementTable;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GRAPHIC_UI_FRAME__) */

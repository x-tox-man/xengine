//
//  APPLICATION_MAIN_WINDOW.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 21/06/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__APPLICATION_MAIN_WINDOW__
#define __GAME_ENGINE_REBORN__APPLICATION_MAIN_WINDOW__

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_UI_FRAME.h"
#include "GRAPHIC_OBJECT_SHAPE.h"
#include "GRAPHIC_UI_ELEMENT_STATE.h"
#include "GRAPHIC_TEXT.h"
#include "GRAPHIC_FONT.h"
#include "CORE_HELPERS_CALLBACK.h"
#include "NETWORK_SERVER.h"
#include "NETWORK_CLIENT.h"
#include "SERVICE_NETWORK_SYSTEM.h"
#include "GRAPHIC_TEXTURE_ATLAS.h"
#include "GLOBAL_RESOURCES.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( APPLICATION_MAIN_WINDOW, GRAPHIC_UI_FRAME )

APPLICATION_MAIN_WINDOW();

void Initialize();

void StartLobbyButtonClicked( GRAPHIC_UI_ELEMENT * clicked_element, GRAPHIC_UI_ELEMENT_STATE event );
void StartServerButtonClicked( GRAPHIC_UI_ELEMENT * clicked_element, GRAPHIC_UI_ELEMENT_STATE event );
void StartClientButtonClicked( GRAPHIC_UI_ELEMENT * clicked_element, GRAPHIC_UI_ELEMENT_STATE event );
void StopLobbyButtonClicked( GRAPHIC_UI_ELEMENT * clicked_element, GRAPHIC_UI_ELEMENT_STATE event );
void SendCommandButtonClicked( GRAPHIC_UI_ELEMENT * clicked_element, GRAPHIC_UI_ELEMENT_STATE event );

void SetShape( GRAPHIC_OBJECT_SHAPE * shape ) { Shape = shape; }
void SetNetworkServer( NETWORK_SERVER * server ) { Server = server; }
void SetNetworkClient( NETWORK_CLIENT * client ) { Client = client; }

virtual void Update( const float );

private:

GRAPHIC_OBJECT_SHAPE
    * Shape;
GRAPHIC_TEXT
    * TextShape,
    * TextShape2;
GRAPHIC_TEXT
    Text;
CORE_HELPERS_CALLBACK_2<GRAPHIC_UI_ELEMENT *, GRAPHIC_UI_ELEMENT_STATE>
    *StartLobbyButtonClickedCallback,
    *StartServerButtonClickedCallback,
    *StartClientButtonClickedCallback,
    *StopLobbyButtonClickedCallback,
    *SendCommandButtonClickedCallback;
NETWORK_SERVER
    * Server;
NETWORK_CLIENT
    * Client;
bool
    IsClient;
static CORE_HELPERS_IDENTIFIER
    IdStartLobby,
    IdText,
    IdTextClient,
    IdStartServer,
    IdStartClient,
    IdStopLobby,
    IdSendCommand;

XS_CLASS_END


#endif /* defined(__GAME_ENGINE_REBORN__APPLICATION_MAIN_WINDOW__) */

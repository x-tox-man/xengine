//
//  AppDelegate.m
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 15/10/13.
//  Copyright (c) 2013 Christophe Bernard. All rights reserved.
//

#import "AppDelegate.h"

#include "Application.h"
#include "PERIPHERIC_INTERACTION_SYSTEM.h"
#include "KEYBOARD_KEY.h"

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    // Insert code here to initialize your application
    
#ifdef __UNIT_TESTING__
    return;
#endif
    
    self.application = new MyTestApp();
    self.application->setApplicationName( "test" );
    
    self.applicationMainScreen = new GRAPHIC_WINDOW_OSX;
    self.applicationMainScreen->setHeight(768);
    self.applicationMainScreen->setWidth(1024);
    self.applicationMainScreen->Initialize();
    
    self.application->SetApplicationWindow( *self.applicationMainScreen );
    self.application->Initialize();
}

- (void)applicationDidBecomeActive:(NSNotification *)notification
{
    self.window = [[NSApplication sharedApplication] mainWindow];
    
    [self.window setFrame:CGRectMake(0.0f, 0.0f, 1024.0f, 768.0f) display:YES];
    [self.window.contentView addSubview:self.applicationMainScreen->GetGlView()];
    
    NSEventMask mask =
    NSLeftMouseDownMask |
    NSLeftMouseUpMask |
    NSRightMouseDownMask |
    NSRightMouseUpMask |
    NSKeyDownMask |
    NSKeyUpMask |
    NSMouseMovedMask;
    
    [NSEvent addLocalMonitorForEventsMatchingMask:mask handler:^NSEvent *(NSEvent * event) {
        
        switch ( [event type] ) {
                
            case NSKeyUp: {
                
                int value = [[event characters] characterAtIndex:0 ];
                
                if ( value >= 'a' && value <= 'z' ) {
                    
                    PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetKeyboard().SetKeyReleased(
                                                                                              ( KEYBOARD_KEY ) ( ( ( int ) KEYBOARD_KEY_CHAR_A ) + ( value - 'a' ) ) );
                }
                else if ( value >= 'A' && value <= 'Z' ) {
                    
                    PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetKeyboard().SetKeyReleased(
                                                                                              ( KEYBOARD_KEY ) ( ( ( int ) KEYBOARD_KEY_CHAR_A ) + ( value - 'A' ) ) );
                }
                else if ( value >= '0' && value <= '9' ) {
                    
                    PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetKeyboard().SetKeyReleased(
                                                                                              ( KEYBOARD_KEY ) ( ( ( int ) KEYBOARD_KEY_NUM_0 ) + ( value - '0' ) ) );
                }
                else {
                    
                    //int keyChar = [event charactersIgnoringModifiers] characterAtIndex:0];
                    
                    //PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetKeyboard().SetKeyPressed( [event keyCode] );
                }
                
                break;
            }
                
            case NSKeyDown: {
                
                int value = [[event characters] characterAtIndex:0 ];
                
                if ( value >= 'a' && value <= 'z' ) {
                    
                    PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetKeyboard().SetKeyPressed(
                                                                                             ( KEYBOARD_KEY ) ( ( ( int ) KEYBOARD_KEY_CHAR_A ) + ( value - 'a' ) ) );
                }
                else if ( value >= 'A' && value <= 'Z' ) {
                    
                    PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetKeyboard().SetKeyPressed(
                                                                                             ( KEYBOARD_KEY ) ( ( ( int ) KEYBOARD_KEY_CHAR_A ) + ( value - 'A' ) ) );
                }
                else if ( value >= '0' && value <= '9' ) {
                    
                    PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetKeyboard().SetKeyPressed(
                                                                                             ( KEYBOARD_KEY ) ( ( ( int ) KEYBOARD_KEY_NUM_0 ) + ( value - '0' ) ) );
                }
                else {
                    
                    //int keyChar = [event charactersIgnoringModifiers] characterAtIndex:0];
                    
                    //PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetKeyboard().SetKeyPressed( [event keyCode] );
                }
                
                break;
            }
                
            case NSMouseMoved: {
                int32_t deltaX, deltaY;
                
                CGGetLastMouseDelta(&deltaX, &deltaY);
                
                PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetMouse().AddNormalizedDisplacement( deltaX / [self.window frame].size.width, deltaY / [self.window frame].size.height);
                PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetMouse().SetScreenCoordinates( [event locationInWindow].x / [self.window frame].size.width, [event locationInWindow].y / [self.window frame].size.height);
                PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetMouse().SetPointCoordinates( [event locationInWindow].x, [event locationInWindow].y );
                
                break;
            }
                
            case NSLeftMouseDown: {
                
                PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetMouse().SetLeftButtonClicked();
                
                break;
            }
                
            case NSLeftMouseUp: {
                
                PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetMouse().SetLeftButtonReleased();
                
                break;
            }
                
            case NSRightMouseDown: {
                
                PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetMouse().SetRightButtonClicked();
                
                break;
            }
                
            case NSRightMouseUp: {
                
                PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetMouse().SetRightButtonReleased();
                
                break;
            }
                
            default:
                
                break;
        }
        
        return event;
    }];
}

- (void)applicationWillResignActive:(NSNotification *)notification
{
    
}

@end

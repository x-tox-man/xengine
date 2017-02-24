//
//  AppDelegate.m
//  MULTIPOLY
//
//  Created by Christophe Bernard on 19/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#import "AppDelegate.h"

#include "PERIPHERIC_INTERACTION_SYSTEM.h"
#include "KEYBOARD_KEY.h"

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    // Insert code here to initialize your application
    
#ifdef __UNIT_TESTING__
    return;
#endif
    
    self.Application = new MULTIPOLY_APPLICATION();
    self.Application->setApplicationName( "test" );
    
    self.ApplicationMainScreen = new GRAPHIC_WINDOW_OSX;
    self.ApplicationMainScreen->SetHeight(768);
    self.ApplicationMainScreen->SetWidth(1024);
    self.ApplicationMainScreen->Initialize();
    
    self.Application->SetApplicationWindow( *self.ApplicationMainScreen );
    self.Application->Initialize();
    
    self.ApplicationMainScreen->Display();
    
    [[self Window] setDelegate: self];
}

- (void) windowWillClose: (NSNotification *)notification {
    
    //[_applicationMainScreen->GetGlView() StopUpdate];
}

- (void) windowDidBecomeMain:(NSNotification *) notification {
    
}

- (void)applicationDidBecomeActive:(NSNotification *)notification
{
    self.Window = [[NSApplication sharedApplication] mainWindow];
    
    [self.Window setFrame:CGRectMake(0.0f, 0.0f, 1024.0f, 768.0f) display:YES];
    [self.Window.contentView setAcceptsTouchEvents:YES];
    [self.ApplicationMainScreen->GetGlView() setAcceptsTouchEvents:YES];
    [self.Window.contentView addSubview:self.ApplicationMainScreen->GetGlView()];
    
    NSEventMask mask =
    NSEventMaskLeftMouseDown |
    NSEventMaskLeftMouseUp |
    NSEventMaskRightMouseDown |
    NSEventMaskRightMouseUp |
    NSEventMaskKeyDown |
    NSEventMaskKeyUp |
    NSEventMaskLeftMouseDragged |
    NSEventMaskMouseMoved;
    
    [NSEvent addLocalMonitorForEventsMatchingMask:mask handler:^NSEvent *(NSEvent * event) {
        
        
        switch ( [event type] ) {
                
            case NSEventTypeKeyUp: {
                
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
                
            case NSEventTypeKeyDown: {
                
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
                
            case NSEventTypeLeftMouseDragged: {
                
                int32_t deltaX, deltaY;
                
                CGGetLastMouseDelta(&deltaX, &deltaY);
                
                PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetMouse().AddNormalizedDisplacement( deltaX / [self.Window frame].size.width, deltaY / [self.Window frame].size.height);
                PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetMouse().SetScreenCoordinates( [event locationInWindow].x / [self.Window frame].size.width, [event locationInWindow].y / [self.Window frame].size.height);
                PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetMouse().SetPointCoordinates( [event locationInWindow].x, [event locationInWindow].y );
                
                break;
            }
                
            case NSEventTypeMouseMoved: {
                int32_t deltaX, deltaY;
                
                CGGetLastMouseDelta(&deltaX, &deltaY);
                
                PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetMouse().AddNormalizedDisplacement( deltaX / [self.Window frame].size.width, deltaY / [self.Window frame].size.height);
                PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetMouse().SetScreenCoordinates( [event locationInWindow].x / [self.Window frame].size.width, [event locationInWindow].y / [self.Window frame].size.height);
                PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetMouse().SetPointCoordinates( [event locationInWindow].x, [event locationInWindow].y );
                
                break;
            }
                
            case NSEventTypeScrollWheel : {
                
                PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetMouse().SetScrollCoordinates([event scrollingDeltaX], [event scrollingDeltaY]);
                
                break;
            }
                
            case NSEventTypeGesture : {
                
                PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetMouse().SetScrollCoordinates([event deltaX], [event deltaY]);
                
                break;
            }
                
            case NSEventTypeLeftMouseDown: {
                
                PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetMouse().SetLeftButtonClicked();
                
                break;
            }
                
            case NSEventTypeLeftMouseUp: {
                
                PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetMouse().SetLeftButtonReleased();
                
                break;
            }
                
            case NSEventTypeRightMouseDown: {
                
                PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetMouse().SetRightButtonClicked();
                
                break;
            }
                
            case NSEventTypeRightMouseUp: {
                
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

-(void)applicationWillTerminate:(NSNotification *)notification {
    
    _Application->Finalize();
    
    CORE_MEMORY_ObjectSafeDeallocation( _Application );
    CORE_MEMORY_ObjectSafeDeallocation( _ApplicationMainScreen );
}

- (void)touchesBeganWithEvent:(NSEvent *)event {
    
}

- (void)touchesMovedWithEvent:(NSEvent *)event {
    
    
}

@end

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

@implementation AppDelegate {
    CGPoint initialPoint;
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    // Insert code here to initialize your application
    
    #ifdef __UNIT_TESTING__
        return;
    #endif
    
    self.application = new MyTestApp();
    self.application->setApplicationName( "test" );
    
    self.applicationMainScreen = new GRAPHIC_WINDOW_OSX;
    self.applicationMainScreen->SetHeight(768);
    self.applicationMainScreen->SetWidth(1024);
    self.applicationMainScreen->Initialize();
    
    self.application->SetApplicationWindow( *self.applicationMainScreen );
    self.application->Initialize();
    
    self.applicationMainScreen->Display();
    
    [[self window] setDelegate: self];
}

- (void) windowWillClose: (NSNotification *)notification {
    
    //[_applicationMainScreen->GetGlView() StopUpdate];
}

- (void) windowDidBecomeMain:(NSNotification *) notification {
    
}

- (void)applicationDidBecomeActive:(NSNotification *)notification
{
    self.window = [[NSApplication sharedApplication] mainWindow];
    
    [self.window setFrame:CGRectMake(0.0f, 0.0f, 1024.0f, 768.0f) display:YES];
    [self.window.contentView setAcceptsTouchEvents:YES];
    [self.applicationMainScreen->GetGlView() setAcceptsTouchEvents:YES];
    [self.window.contentView addSubview:self.applicationMainScreen->GetGlView()];
    
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
                
                PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetMouse().AddNormalizedDisplacement( deltaX / [self.window frame].size.width, deltaY / [self.window frame].size.height);
                PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetMouse().SetScreenCoordinates( [event locationInWindow].x / [self.window frame].size.width, [event locationInWindow].y / [self.window frame].size.height);
                PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetMouse().SetPointCoordinates( [event locationInWindow].x, [event locationInWindow].y );
                
                break;
            }
                
            case NSEventTypeMouseMoved: {
                int32_t deltaX, deltaY;
                
                CGGetLastMouseDelta(&deltaX, &deltaY);
                
                PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetMouse().AddNormalizedDisplacement( deltaX / [self.window frame].size.width, deltaY / [self.window frame].size.height);
                PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetMouse().SetScreenCoordinates( [event locationInWindow].x / [self.window frame].size.width, [event locationInWindow].y / [self.window frame].size.height);
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
    
    _application->Finalize();
    
    CORE_MEMORY_ObjectSafeDeallocation( _application );
    CORE_MEMORY_ObjectSafeDeallocation( _applicationMainScreen );
}

- (void)touchesBeganWithEvent:(NSEvent *)event {
    
    /*NSSet *touches = [event touchesMatchingPhase:NSTouchPhaseTouching inView:self.applicationMainScreen->GetGlView()];
    
    if (touches.count == 2) {
        self->initialPoint = [self.applicationMainScreen->GetGlView() convertPointFromBase:[event locationInWindow]];
        NSArray *array = [touches allObjects];
        _initialTouches[0] = [[array objectAtIndex:0] retain];
        _initialTouches[1] = [[array objectAtIndex:1] retain];
        _currentTouches[0] = [_initialTouches[0] retain];
        _currentTouches[1] = [_initialTouches[1] retain];
    }*/
}

- (void)touchesMovedWithEvent:(NSEvent *)event {
    
    /*self.modifiers = [event modifierFlags];
    NSSet *touches = [event touchesMatchingPhase:NSTouchPhaseTouching inView:self.view];
    if (touches.count == 2 && _initialTouches[0]) {
        NSArray *array = [touches allObjects];
        [_currentTouches[0] release];
        [_currentTouches[1] release];
        
        NSTouch *touch;
        touch = [array objectAtIndex:0];
        if ([touch.identity isEqual:_initialTouches[0].identity]) {
            _currentTouches[0] = [touch retain];
        } else {
            _currentTouches[1] = [touch retain];
        }
        touch = [array objectAtIndex:1];
        if ([touch.identity isEqual:_initialTouches[0].identity]) {
            _currentTouches[0] = [touch retain];
        } else {
            _currentTouches[1] = [touch retain];
        }
        if (!self.isTracking) {
            NSPoint deltaOrigin = self.deltaOrigin;
            NSSize  deltaSize = self.deltaSize;
            if (fabs(deltaOrigin.x) > _threshold ||
                fabs(deltaOrigin.y) > _threshold ||
                fabs(deltaSize.width) > _threshold ||
                fabs(deltaSize.height) > _threshold) {
                self.isTracking = YES;
                if (self.beginTrackingAction)
                    [NSApp sendAction:self.beginTrackingAction to:self.view from:self];
            }
        } else {
            if (self.updateTrackingAction)
                [NSApp sendAction:self.updateTrackingAction to:self.view from:self];
        }
    }*/
}

@end

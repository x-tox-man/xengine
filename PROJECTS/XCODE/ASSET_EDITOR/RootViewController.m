//
//  ViewController.m
//  ASSET_EDITOR
//
//  Created by Christophe Bernard on 14/02/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#import "RootViewController.h"
#import "PERIPHERIC_INTERACTION_SYSTEM.h"

@implementation RootViewController

- (void)viewDidLoad {
    
    [super viewDidLoad];

    // Do any additional setup after loading the view.
    self.Application = new ASSET_EDITOR();
    
    self.Application->setApplicationName( "test" );
    
    self.applicationMainScreen = new GRAPHIC_WINDOW_OSX();
    
    CORE_HELPERS_CALLBACK_1<const char *> callback( &Wrapper1<ASSET_EDITOR, const char *, &ASSET_EDITOR::OnDraggedPath>, self.Application );
    
    self.applicationMainScreen->SetOndraggedCallback(callback );
    
    self.applicationMainScreen->Initialize();
    self.applicationMainScreen->Resize( 1024, 768 );
    
    self.Application->SetApplicationWindow( *self.applicationMainScreen );
    self.Application->Initialize();
    
    self.applicationMainScreen->Display();
}

- (void)setRepresentedObject:(id)representedObject {
    [super setRepresentedObject:representedObject];

    // Update the view, if already loaded.
}

-(void) viewWillAppear {
    
    //[self.view setFrame:CGRectMake(0.0f, 0.0f, 1024.0f, 768.0f) display:YES];
    //[self.view.contentView setAcceptsTouchEvents:YES];
    [self.applicationMainScreen->GetGlView() setAcceptsTouchEvents:YES];
    [self.view addSubview:self.applicationMainScreen->GetGlView()];
    
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
                
                PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetMouse().AddNormalizedDisplacement( deltaX / [self.view frame].size.width, deltaY / [self.view frame].size.height);
                PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetMouse().SetScreenCoordinates( [event locationInWindow].x / [self.view frame].size.width, [event locationInWindow].y / [self.view frame].size.height);
                PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetMouse().SetPointCoordinates( [event locationInWindow].x, [event locationInWindow].y );
                
                break;
            }
                
            case NSEventTypeMouseMoved: {
                int32_t deltaX, deltaY;
                
                CGGetLastMouseDelta(&deltaX, &deltaY);
                
                PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetMouse().AddNormalizedDisplacement( deltaX / [self.view frame].size.width, deltaY / [self.view frame].size.height);
                PERIPHERIC_INTERACTION_SYSTEM::GetInstance().GetMouse().SetScreenCoordinates( [event locationInWindow].x / [self.view frame].size.width, [event locationInWindow].y / [self.view frame].size.height);
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
@end

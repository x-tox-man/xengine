//
//  LeftPane3DViewController.m
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 19/04/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#import "LeftPane3DViewController.h"
#import "Cpp3dDataProxy.h"
#import "GAMEPLAY_COMPONENT_ENTITY.h"
#import "GAMEPLAY_COMPONENT_MANAGER.h"

@interface LeftPane3DViewController ()

@end

@implementation LeftPane3DViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do view setup here.
}

- (IBAction)CreateItem:(id)sender {
    
    static int c_index = 0;
    GAMEPLAY_COMPONENT_ENTITY * component_entity = GAMEPLAY_COMPONENT_MANAGER::GetInstance().CreateEntity();
    component_entity->SetIndex( c_index++ );
    
    component_entity->SetCompononent( GAMEPLAY_COMPONENT::FactoryCreate( GAMEPLAY_COMPONENT_TYPE_Position ), GAMEPLAY_COMPONENT_TYPE_Position );
    
    [self.OutlineView reloadData];
}

-(void)outlineViewSelectionDidChange:(NSNotification *)notification {
    
    
}

-(BOOL)outlineView:(NSOutlineView *)outlineView isItemExpandable:(id)item {
    
    Cpp3dDataProxy * itemProxy = item;
    
    GAMEPLAY_COMPONENT_ENTITY * entity = itemProxy.Entity;
    
    if ( entity == NULL ) {
        return NO;
    }
    
    for (int i =0; i < GAMEPLAY_COMPONENT_ENTITY_MAX_CHILDS; i++) {
        
        if ( entity->GetChild( i ) != NULL) {
            return YES;
        }
    }
    
    return NO;
}

-(NSInteger)outlineView:(NSOutlineView *)outlineView numberOfChildrenOfItem:(id)item {
    
    if ( item != nil ) {
        
        Cpp3dDataProxy * itemProxy = item;
        
        GAMEPLAY_COMPONENT_ENTITY * entity = itemProxy.Entity;
        
        if ( entity == NULL ) {
            return NO;
        }
        
        int count = 0;
        
        for (int i =0; i < GAMEPLAY_COMPONENT_ENTITY_MAX_CHILDS; i++) {
            
            if ( entity->GetChild( i ) != NULL) {
                count++;
            }
        }
        
        return count;
    }
    else {
        
        static bool hack = true;
        
        if ( hack ) {
            hack = false;
            return 0;
        }
        
        int count = 0;
        
        for ( int i =0; i < 2048; i++ ) {
            
            auto v = &GAMEPLAY_COMPONENT_MANAGER::GetInstance();
            
            if ( v && GAMEPLAY_COMPONENT_MANAGER::GetInstance().GetEntity( i ) != NULL ) {
                count++;
            }
            else {
                break;
            }
        }
        
        
        return count;
    }
}

-(void)outlineView:(NSOutlineView *)outlineView setObjectValue:(id)object forTableColumn:(NSTableColumn *)tableColumn byItem:(id)item {
    
    /*NSInteger col = [[outlineView tableColumns ] indexOfObject:tableColumn];
    
    CppUIDataProxy * itemProxy = item;
    
    CORE_MATH_VECTOR size = itemProxy.Element->GetPlacement().GetSize();
    CORE_MATH_VECTOR position = itemProxy.Element->GetPlacement().GetRelativePosition();
    
    NSString * str = object;
    
    switch (col) {
        case 0:
            
            break;
        case 1:
            
            position.X( str.floatValue );
            break;
        case 2:
            
            position.Y( str.floatValue );
            break;
        case 3:
            
            size.X( str.floatValue );
            break;
        case 4:
            
            size.Y( str.floatValue );
            break;
            
    }
    
    itemProxy.Element->GetPlacement().SetSize( size );
    itemProxy.Element->GetPlacement().SetRelativePosition( position );*/
}

-(id)outlineView:(NSOutlineView *)outlineView child:(NSInteger)index ofItem:(id)item {
    
    Cpp3dDataProxy * proxy = [[Cpp3dDataProxy alloc] init];
    
    proxy.Entity = NULL;
    
    if ( item == nil ) {
        
        
    }
    else {
        
        
    }
    
    return proxy;
}

-(id)outlineView:(NSOutlineView *)outlineView objectValueForTableColumn:(NSTableColumn *)tableColumn byItem:(id)item {
    
    Cpp3dDataProxy * proxy = item;
    
    if ( proxy.Entity == NULL )
        return @"1";
    
    /*NSInteger col = [[outlineView tableColumns ] indexOfObject:tableColumn];
    
    switch (col) {
        case 0:
            
            return [NSString stringWithFormat:@"%s", proxy.Entity->GetIdentifier().GetTextValue()];
        case 1:
            
            return [NSString stringWithFormat:@"%f", proxy.Element->GetPlacement().GetRelativePosition().X()];
        case 2:
            
            return [NSString stringWithFormat:@"%f", proxy.Element->GetPlacement().GetRelativePosition().Y()];
        case 3:
            
            return [NSString stringWithFormat:@"%f", proxy.Element->GetPlacement().GetSize().X()];
        case 4:
            
            return [NSString stringWithFormat:@"%f", proxy.Element->GetPlacement().GetSize().Y()];
            
        default:
            return @"0";
    }*/
    
    return @"2";
}

@end

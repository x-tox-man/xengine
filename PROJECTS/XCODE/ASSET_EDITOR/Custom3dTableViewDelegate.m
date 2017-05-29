//
//  Custom3dTableViewDelegate.m
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 16/05/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#import "Custom3dTableViewDelegate.h"
#import "GAMEPLAY_COMPONENT_ENTITY.h"
#import "GAMEPLAY_COMPONENT_POSITION.h"
#import "CORE_MATH_VECTOR.h"
#import "CORE_MATH_QUATERNION.h"

@implementation Custom3dTableViewDelegate

-(NSInteger)numberOfRowsInTableView:(NSTableView *)tableView {
    
    if (self.Entity.Entity == NULL) {
        return 0;
    }
    else
    {
        int count = 0;
        
        for (int i = 0; i < GAMEPLAY_COMPONENT_ENTITY_MAX_COMPONENTS; i++ ) {
            
            if ( ((GAMEPLAY_COMPONENT_ENTITY *) self.Entity.Entity)->GetComponent( i ) != NULL ) {
                count++;
            }
        }
    
        return count;
    }
}

-(CGFloat)tableView:(NSTableView *)tableView heightOfRow:(NSInteger)row {
    return 128.0f;
}

-(NSView *)tableView:(NSTableView *)tableView viewForTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row {
    
    if ( self.Entity.Entity == NULL ) {
        
        return nil;
    }
    else {
        switch (row) {
            case 0:
            {
                GAMEPLAY_COMPONENT_POSITION * pos = (GAMEPLAY_COMPONENT_POSITION *) [self.Entity Entity]->GetComponent( 0 );
                
                CORE_MATH_VECTOR position( pos->GetPosition() );
                CORE_MATH_QUATERNION rotation( pos->GetOrientation() );
                
                [self.XposTextField setStringValue:[NSString stringWithFormat:@"%f", position.X()]];
                [self.YposTextField setStringValue:[NSString stringWithFormat:@"%f", position.Y()]];
                [self.ZposTextField setStringValue:[NSString stringWithFormat:@"%f", position.Z()]];
                [self.WposTextField setStringValue:[NSString stringWithFormat:@"%f", position.W()]];
                [self.XRotTextField setStringValue:[NSString stringWithFormat:@"%f", rotation.X()]];
                [self.YRotTextField setStringValue:[NSString stringWithFormat:@"%f", rotation.Y()]];
                [self.ZRotTextField setStringValue:[NSString stringWithFormat:@"%f", rotation.Z()]];
                [self.WRotTextField setStringValue:[NSString stringWithFormat:@"%f", rotation.W()]];
                
                return [tableView makeViewWithIdentifier:@"PositionComponent" owner:self];
            }
            case 1:
            {
                //TODO Configure view
                return [tableView makeViewWithIdentifier:@"PhysicsComponent" owner:self];
                break;
            }
            case 2:
            {
                //TODO Configure view
                return [tableView makeViewWithIdentifier:@"RenderComponent" owner:self];
                break;
            }
            default:
                //TODO Configure view
                return [tableView makeViewWithIdentifier:@"PositionComponent" owner:self];
                break;
        }
    }
}

- (IBAction)SetXPos:(id)sender {
    NSTextField *tf = sender;
    
    auto pos = (GAMEPLAY_COMPONENT_POSITION *) ((GAMEPLAY_COMPONENT_ENTITY *) self.Entity.Entity)->GetComponent( 0 );
    CORE_MATH_VECTOR position = pos->GetPosition();
    position.X( [tf floatValue] );
    pos->SetPosition(position);
}

- (IBAction)SetYPos:(id)sender {
    NSTextField *tf = sender;
    
    auto pos = (GAMEPLAY_COMPONENT_POSITION *) ((GAMEPLAY_COMPONENT_ENTITY *) self.Entity.Entity)->GetComponent( 0 );
    CORE_MATH_VECTOR position = pos->GetPosition();
    position.Y( [tf floatValue] );
    pos->SetPosition(position);
}

- (IBAction)SetZPos:(id)sender {
    NSTextField *tf = sender;
    
    auto pos = (GAMEPLAY_COMPONENT_POSITION *) ((GAMEPLAY_COMPONENT_ENTITY *) self.Entity.Entity)->GetComponent( 0 );
    CORE_MATH_VECTOR position = pos->GetPosition();
    position.Z( [tf floatValue] );
    pos->SetPosition(position);
}

- (IBAction)SetWPos:(id)sender {
    NSTextField *tf = sender;
    
    auto pos = (GAMEPLAY_COMPONENT_POSITION *) ((GAMEPLAY_COMPONENT_ENTITY *) self.Entity.Entity)->GetComponent( 0 );
    CORE_MATH_VECTOR position = pos->GetPosition();
    position.Z( [tf floatValue] );
    pos->SetPosition(position);
}

- (IBAction)SetXRot:(id)sender {
    NSTextField *tf = sender;
    
    auto pos = (GAMEPLAY_COMPONENT_POSITION *) ((GAMEPLAY_COMPONENT_ENTITY *) self.Entity.Entity)->GetComponent( 0 );
    CORE_MATH_QUATERNION rotation = pos->GetOrientation();
    
    
    rotation.X( [tf floatValue] );
    rotation.Normalize();
    
    pos->SetOrientation(rotation);
    
    [tf setFloatValue:rotation.X()];
    
}

- (IBAction)SetYRot:(id)sender {
    NSTextField *tf = sender;
    
    auto pos = (GAMEPLAY_COMPONENT_POSITION *) ((GAMEPLAY_COMPONENT_ENTITY *) self.Entity.Entity)->GetComponent( 0 );
    CORE_MATH_QUATERNION rotation = pos->GetOrientation();
    rotation.Y( [tf floatValue] );
    rotation.Normalize();
    
    pos->SetOrientation(rotation);
    
    [tf setFloatValue:rotation.Y()];
}

- (IBAction)SetZRot:(id)sender {
    NSTextField *tf = sender;
    
    auto pos = (GAMEPLAY_COMPONENT_POSITION *) ((GAMEPLAY_COMPONENT_ENTITY *) self.Entity.Entity)->GetComponent( 0 );
    CORE_MATH_QUATERNION rotation = pos->GetOrientation();
    rotation.Z( [tf floatValue] );
    rotation.Normalize();
    
    pos->SetOrientation(rotation);
    
    [tf setFloatValue:rotation.Z()];
}

- (IBAction)SetWRot:(id)sender {
    NSTextField *tf = sender;
    
    auto pos = (GAMEPLAY_COMPONENT_POSITION *) ((GAMEPLAY_COMPONENT_ENTITY *) self.Entity.Entity)->GetComponent( 0 );
    CORE_MATH_QUATERNION rotation = pos->GetOrientation();
    rotation.W( [tf floatValue] );
    rotation.Normalize();
    
    pos->SetOrientation(rotation);
    
    [tf setFloatValue:rotation.W()];
}

@end

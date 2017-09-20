//
//  Create3dItem.m
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 8/05/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#import "Create3dItem.h"
#import "Constants.h"
#import "ResourceManager.h"
#import "GAMEPLAY_COMPONENT_POSITION.h"

@interface Create3dItem ()

@end

@implementation Create3dItem {
    NSString * ResourceType;
}

- (void)viewDidLoad {
    
    [super viewDidLoad];
    // Do view setup here.
}


- (IBAction)OnSelectMesh:(id)sender {
    
    ResourceType = @"Model";
    [self performSegueWithIdentifier:@CHOOSE_RESOURCE_SEGUE sender:self];
}

- (IBAction)OnSelectEffect:(id)sender {
    
    ResourceType = @"Effect";
    [self performSegueWithIdentifier:@CHOOSE_RESOURCE_SEGUE sender:self];
}

-(void)prepareForSegue:(NSStoryboardSegue *)segue sender:(id)sender {
    
    ResourceManager * rma = segue.destinationController;
    
    rma.ResourceDelegate = self;
    
    rma.ResourceType = ResourceType;
}

- (IBAction)OnCreate:(id)sender {
    
    static int c_index = 0;
    GAMEPLAY_COMPONENT_ENTITY * component_entity = GAMEPLAY_COMPONENT_MANAGER::GetInstance().CreateEntity();
    GAMEPLAY_COMPONENT_HANDLE handle;
    
    handle.Create< GAMEPLAY_COMPONENT_POSITION >( GAMEPLAY_COMPONENT_TYPE_Position );
    
    
    component_entity->SetCompononent( handle, GAMEPLAY_COMPONENT_TYPE_Position );
    
    [self.BackDelegate OnBack];
    
    [self dismissViewController:self];
}

- (IBAction)OnCancel:(id)sender {
    
    [self dismissViewController:self];
}

-(void) OnResourceSelected:(ResourceProxy *)Resource {
    
    if ( Resource.Object3d ) {
        
    }
    else {
        abort();
    }
}

@end

//
//  ResourceManager.m
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 19/05/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#import "ResourceManager.h"
#import "ASSET_EDITOR.h"
#import "RESOURCE_CONTAINER.h"

@interface ResourceManager ()

@property RESOURCE_CONTAINER * ResourceContainer;
@end

@implementation ResourceManager

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do view setup here.
    
    ASSET_EDITOR * editor = (ASSET_EDITOR*) &ASSET_EDITOR::GetApplicationInstance();
    
    self.ResourceContainer = &editor->GetResourceContainer();
}

-(NSView *)tableView:(NSTableView *)tableView viewForTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row {
    
    NSUInteger index = [[self.TableView tableColumns] indexOfObject:tableColumn];
    
    if(  index == 0 ){
        
        // Get an existing cell with the MyView identifier if it exists
        NSTextField *result = [tableView makeViewWithIdentifier:@"TitleCell" owner:self];
        
        // There is no existing cell to reuse so create a new one
        if (result == nil) {
            
            // Create the new NSTextField with a frame of the {0,0} with the width of the table.
            // Note that the height of the frame is not really relevant, because the row height will modify the height.
            
            
            result = [[NSTextField alloc] init];
            
            // The identifier of the NSTextField instance is set to MyView.
            // This allows the cell to be reused.
            result.identifier = @"TitleCell";
        }
        
        // result is now guaranteed to be valid, either as a reused cell
        // or as a new cell, so set the stringValue of the cell to the
        // nameArray value at row
        
        // Return the result
        return result;
    }
    else
    {
        NSTextField *result = [tableView makeViewWithIdentifier:@"ContentCell" owner:self];
        
        if (result == nil) {
            
            // Create the new NSTextField with a frame of the {0,0} with the width of the table.
            // Note that the height of the frame is not really relevant, because the row height will modify the height.
            
            
            result = [[NSTextField alloc] init];
            
            // The identifier of the NSTextField instance is set to MyView.
            // This allows the cell to be reused.
            result.identifier = @"ContentCell";
        }
        
        return result;
    }
}

-(NSInteger)numberOfRowsInTableView:(NSTableView *)tableView {
    
    return self.ResourceContainer->GetResourceMap().size();
}

@end

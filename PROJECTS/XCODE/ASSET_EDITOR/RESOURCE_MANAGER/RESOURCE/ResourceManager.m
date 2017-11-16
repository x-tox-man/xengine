//
//  ResourceManager.m
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 19/05/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#import "ResourceManager.h"
#import "ResourceProxy.h"

#import "ASSET_EDITOR.h"
#import "RESOURCE_CONTAINER.h"


@interface ResourceManager ()

@property RESOURCE_CONTAINER * ResourceContainer;
@end

@implementation ResourceManager

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do view setup here.
    
    self.TableView.delegate = self;
    self.TableView.dataSource = self;
    
    self.FilteredTypes = [[NSMutableArray alloc] init];
    
    [self.TableView setDoubleAction:@selector(rowDoubleClicked)];
    
    if ( [self.ResourceType isEqualToString:@"Model"] ) {
        
        std::map< CORE_HELPERS_UNIQUE_IDENTIFIER, GRAPHIC_OBJECT * >::iterator it = GRAPHIC_OBJECT::GetResourceCache()->GetItemMap().begin();
        
        while (it != GRAPHIC_OBJECT::GetResourceCache()->GetItemMap().end() ) {
            
            ResourceProxy * rpr = [[ResourceProxy alloc] init];
            
            rpr.Object3d = it->second;
            
            [self.FilteredTypes addObject:rpr];
            it++;
        }
    }
    else if ( [self.ResourceType isEqualToString:@"Effect"] ) {
        
        std::map< CORE_HELPERS_UNIQUE_IDENTIFIER, GRAPHIC_SHADER_EFFECT * >::iterator it = GRAPHIC_SHADER_EFFECT::GetResourceCache()->GetItemMap().begin();
        
        while (it != GRAPHIC_SHADER_EFFECT::GetResourceCache()->GetItemMap().end() ) {
            
            ResourceProxy * rpr = [[ResourceProxy alloc] init];
            
            rpr.Effect = it->second;
            
            [self.FilteredTypes addObject:rpr];
            it++;
        }
    }
    
    [self.TableView reloadData];
}

-(void) rowDoubleClicked {
    int row = [self.TableView selectedRow];
    
    [self.ResourceDelegate OnResourceSelected:[self.FilteredTypes objectAtIndex:row]];
    [self dismissViewController:self];
}

-(NSView *)tableView:(NSTableView *)tableView viewForTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row {
    
    NSUInteger index = [[self.TableView tableColumns] indexOfObject:tableColumn];
    
    if(  index == 0 ) {
        
        // Get an existing cell with the MyView identifier if it exists
        NSTextField *result = [tableView makeViewWithIdentifier:@"TitleCell" owner:self];
        
        // There is no existing cell to reuse so create a new one
        if (result == nil) {
            
            // Create the new NSTextField with a frame of the {0,0} with the width of the table.
            // Note that the height of the frame is not really relevant, because the row height will modify the height.
            
            
            result = [[NSTextField alloc] init];
            
            // The identifier of the NSTextField instance is set to MyView.
            // This allows the cell to be reused.
            result.identifier = self.ResourceType;
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
            if ( [[self.FilteredTypes objectAtIndex:row] Object3d] != NULL ) {
                result.identifier = [NSString stringWithCString:[[self.FilteredTypes objectAtIndex:row] Object3d]->GetIdentifier().GetIdentifier() encoding:NSASCIIStringEncoding];
            }
            else if ( [[self.FilteredTypes objectAtIndex:row] Effect] != NULL ){
                result.identifier = [NSString stringWithCString:[[self.FilteredTypes objectAtIndex:row] Effect]->GetIdentifier().GetIdentifier() encoding:NSASCIIStringEncoding];
            }
            else {
                abort();
            }
            
        }
        
        return result;
    }
}

-(NSInteger)numberOfRowsInTableView:(NSTableView *)tableView {
    
    return self.FilteredTypes.count;
}

@end

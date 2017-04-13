//
//  LeftPane.m
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 2/04/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#import "LeftPaneViewController.h"
#import "ASSET_EDITOR.h"
#import "Constants.h"

@implementation LeftPaneViewController

-(void)viewDidLoad
{
    [super viewDidLoad];
    
    self.Menu.delegate = self;
    self.TableView.delegate = self;
    self.TableView.dataSource = self;
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(onObjectCollectionChanged) name:@CREATE_OBJECT_NOTIFICATION object:nil];
}

- (IBAction)CreateAtlas:(id)sender {
    
    [self performSegueWithIdentifier:@ATLAS_CREATION_SEGUE sender:self];
}

- (IBAction)CreateItemButtonClicked:(id)sender {
    
    [self performSegueWithIdentifier:@"XSCreateGUIItem" sender:self];
}

- (IBAction)DeleteItemButtonClicked:(id)sender {
}

- (IBAction)PrintViewButtonClicked:(id)sender {
}

- (IBAction)OnResolutionChanged:(id)sender {
    
    NSString * title = [[self.PopupButton selectedItem] title];
    
    NSArray * listItems = [title componentsSeparatedByString:@" - "];
    
    
    int width = [[listItems firstObject] intValue];
    int height = [[listItems objectAtIndex:1] intValue];
    CORE_APPLICATION::GetApplicationInstance().GetApplicationWindow().Resize( width, height);
}

//
- (NSInteger)numberOfRowsInTableView:(NSTableView *)tableView {
    
    auto editor = ((ASSET_EDITOR*) &CORE_APPLICATION::GetApplicationInstance());
    int size = 0;
    
    if ( editor != NULL ) {
        auto screen = &editor->GetGUIView();
        size = screen->GetElementTable().size();
    }
    
    return size;
}

-(void) onObjectCollectionChanged {
    [self.TableView reloadData];
}

- (NSView *)tableView:(NSTableView *)tableView
   viewForTableColumn:(NSTableColumn *)tableColumn
                  row:(NSInteger)row {
    
    // Get an existing cell with the MyView identifier if it exists
    NSTextField *result = [tableView makeViewWithIdentifier:@"MyView" owner:self];
    
    // There is no existing cell to reuse so create a new one
    if (result == nil) {
        
        // Create the new NSTextField with a frame of the {0,0} with the width of the table.
        // Note that the height of the frame is not really relevant, because the row height will modify the height.
        
        NSRect rect;
        rect.origin.x = 0;
        rect.origin.y = 0;
        
        rect.size.width = self.view.frame.size.width;
        
        result = [[NSTextField alloc] initWithFrame:rect];
        
        // The identifier of the NSTextField instance is set to MyView.
        // This allows the cell to be reused.
        result.identifier = @"MyView";
    }
    
    // result is now guaranteed to be valid, either as a reused cell
    // or as a new cell, so set the stringValue of the cell to the
    // nameArray value at row
    
    auto editor = ((ASSET_EDITOR*) &CORE_APPLICATION::GetApplicationInstance());
    int size = 0;
    
    if ( editor != NULL ) {
        auto screen = &editor->GetGUIView();
        
        result.stringValue = @"test";
    }
    
    // Return the result
    return result;
}


@end

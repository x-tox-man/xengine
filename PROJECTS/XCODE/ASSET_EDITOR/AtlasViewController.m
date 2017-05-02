//
//  AtlasViewController.m
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 9/04/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#import "AtlasViewController.h"

#import "RESOURCE_IMAGE.h"
#import "RESOURCE_IMAGE_ATLAS_COMPILER.h"
#import "RESOURCE_IMAGE_PNG_WRITER.h"
#import "ASSET_EDITOR.h"

#import "ImageView.h"
#import "Constants.h"

@interface AtlasViewController ()

@end

@implementation AtlasViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do view setup here.
    
    self.TableView.delegate = self;
    self.TableView.dataSource = self;
}

- (NSInteger)numberOfRowsInTableView:(NSTableView *)tableView {
    
    int size = [self.DirFiles count];
    
    return size;
}

- (NSView *)tableView:(NSTableView *)tableView
   viewForTableColumn:(NSTableColumn *)tableColumn
                  row:(NSInteger)row {
    
    NSUInteger index = [[self.TableView tableColumns] indexOfObject:tableColumn];
    
    if(  index == 0 ){
        
        // Get an existing cell with the MyView identifier if it exists
        NSTextField *result = [tableView makeViewWithIdentifier:@"MyView" owner:self];
        
        // There is no existing cell to reuse so create a new one
        if (result == nil) {
            
            // Create the new NSTextField with a frame of the {0,0} with the width of the table.
            // Note that the height of the frame is not really relevant, because the row height will modify the height.
            
            
            result = [[NSTextField alloc] init];
            
            // The identifier of the NSTextField instance is set to MyView.
            // This allows the cell to be reused.
            result.identifier = @"MyView";
        }
        
        // result is now guaranteed to be valid, either as a reused cell
        // or as a new cell, so set the stringValue of the cell to the
        // nameArray value at row
        
        result.stringValue = [self.DirFiles objectAtIndex:row];
        
        // Return the result
        return result;
    }
    else
    {
        NSImageView *thisCell = [tableView makeViewWithIdentifier:@"MyViewImage" owner:self];
        
        //NSImage *image = [[NSImage alloc] initWithData:[NSData dataWithContentsOfURL:[NSURL URLWithString:url]]];
        [thisCell setImage:[[NSImage alloc] initByReferencingFile:[self.DirFiles objectAtIndex:row]]];
                                 
        return thisCell;
        
        /*NSImageCell * cell = [[NSImageCell alloc] initImageCell:[[NSImage alloc] initByReferencingFile:[self.DirFiles objectAtIndex:row]]];
        
        return [cell controlView];*/
        /*NSTableCellView *view = [tableView makeViewWithIdentifier:@"MyViewImage" owner:self];
        
        if (view == nil ) {
            
            // Create the new NSTextField with a frame of the {0,0} with the width of the table.
            // Note that the height of the frame is not really relevant, because the row height will modify the height.
            
            view = [[NSTableCellView alloc] init];
            
            NSRect frame;
            
            frame.size.height = 64;
            frame.size.width = 64;
            
            // The identifier of the NSTextField instance is set to MyView.
            // This allows the cell to be reused.
            view.identifier = @"MyViewImage";
            
            [view.imageView setImage:];
        }
        
        return view;*/
    }
}

- (IBAction)ChooseDirAction:(id)sende
{
    // Create the File Open Dialog class.
    NSOpenPanel* openDlg = [NSOpenPanel openPanel];
    
    // Enable the selection of files in the dialog.
    [openDlg setCanChooseFiles:NO];
    [openDlg setTitle:@"Select your images directory"];
    
    // Enable the selection of directories in the dialog.
    [openDlg setCanChooseDirectories:YES];
    
    // Display the dialog.  If the OK button was pressed,
    // process the files.
    if ( [openDlg runModalForDirectory:nil file:nil] == NSModalResponseOK )
    {
        // Get an array containing the full filenames of all
        // files and directories selected.
        NSArray* files = [openDlg filenames];
        self.DirectoryPath =[files objectAtIndex:0];
        
        self.DirFiles = [[NSFileManager defaultManager] contentsOfDirectoryAtPath:self.DirectoryPath error:nil];
    }
    
    [self.TableView reloadData];
}

- (IBAction)GenerateAtlasAction:(id)sender {
    
    std::vector< RESOURCE_IMAGE *> images;
    
    RESOURCE_IMAGE_ATLAS_COMPILER atlas_compiler;
    
    RESOURCE_IMAGE_PNG_LOADER loader;
    RESOURCE_IMAGE_PNG_WRITER writer;
    
    images.resize( [self.DirFiles count] );
    
    int offset = 0;
    
    // Loop through all the files and process them.
    for( int i = 0; i < [self.DirFiles count]; i++ )
    {
        if ( [[self.DirFiles objectAtIndex:i] containsString:@".png"] && ! [[self.DirFiles objectAtIndex:i] containsString:@"atlas"]) {
            
            NSString* fileName = [self.DirectoryPath stringByAppendingString:[NSString stringWithFormat:@"/%@", [self.DirFiles objectAtIndex:i]]];
            
            images[offset] = (RESOURCE_IMAGE *) loader.Load( CORE_FILESYSTEM_PATH([fileName cStringUsingEncoding:NSASCIIStringEncoding]));
            const char * strp = [[[self.DirFiles objectAtIndex:i] stringByReplacingOccurrencesOfString:@".png" withString:@""] cStringUsingEncoding:NSASCIIStringEncoding];
            
            if ( strlen(strp) > 31 ) {
                
                NSRange range;
                range.length = 31;
                range.location = 0;
                strp = [[[self.DirFiles objectAtIndex:i] substringWithRange:range] cStringUsingEncoding:NSASCIIStringEncoding];
            }
            
            images[offset]->SetIdentifier( CORE_HELPERS_UNIQUE_IDENTIFIER( strp ) );
            
            offset++;
        }
    }
    
    self.DesintationAtlasFile = [self.DirectoryPath stringByAppendingString:@"/atlas_test"];
    
    images.resize( offset );
    
    atlas_compiler.Compile( [self.DesintationAtlasFile cStringUsingEncoding:NSASCIIStringEncoding], images );
    
    sleep(1);
    
    [self performSegueWithIdentifier:@ALTAS_SHOW_IMAGE_SEGUE sender:self];
    [self dismissViewController:self];
    
}

-(void)prepareForSegue:(NSStoryboardSegue *)segue sender:(id)sender {
    
    ImageView * iv = [segue destinationController];
    iv.DestinationFile = self.DesintationAtlasFile;
}

- (IBAction)CancelAction:(id)sender {
    
    [self dismissViewController:self];
}

@end

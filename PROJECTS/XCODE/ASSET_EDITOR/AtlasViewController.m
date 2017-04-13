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

#import "ImageView.h"
#import "Constants.h"

@interface AtlasViewController ()

@end

@implementation AtlasViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do view setup here.
}

- (IBAction)ChooseDirAction:(id)sende
{
    // Create the File Open Dialog class.
    NSOpenPanel* openDlg = [NSOpenPanel openPanel];
    
    // Enable the selection of files in the dialog.
    [openDlg setCanChooseFiles:NO];
    
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
        
        self.DirFiles =[[NSFileManager defaultManager] contentsOfDirectoryAtPath:self.DirectoryPath error:nil];
    }
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

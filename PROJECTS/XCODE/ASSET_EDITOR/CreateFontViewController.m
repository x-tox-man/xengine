//
//  CreateFontViewController.m
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 15/04/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#import "CreateFontViewController.h"
#import "FONT_EDITOR.h"
#import "FONT_DESCRIPTOR.h"

@interface CreateFontViewController ()

@end

@implementation CreateFontViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do view setup here.
    
    for (int i = 1; i < 72; i++ ) {
        
        [self.Size addItemWithTitle:[NSString stringWithFormat:@"%d", i]];
    }
}
- (IBAction)GenerateFontAction:(id)sender {
    
    if ( [[self.FontName stringValue] length] > 0 ) {
        FONT_EDITOR
            editor;
        FONT_DESCRIPTOR
            descriptor;
        
        NSString *fontNameTextValue = [[[self.SelectedFont selectedItem] title] stringByReplacingOccurrencesOfString:@".otf" withString:@""];
        
        descriptor.Size = [[[self.Size selectedItem] title] intValue];
        
        fontNameTextValue = [fontNameTextValue stringByReplacingOccurrencesOfString:@".ttf" withString:@""];
        fontNameTextValue = [fontNameTextValue stringByAppendingString:[NSString stringWithFormat:@"_%d", [[[self.Size selectedItem] title] intValue]]];
        
        CORE_FILESYSTEM_PATH
            image_target_path( CORE_FILESYSTEM_PATH::FindFilePath( [fontNameTextValue cStringUsingEncoding:NSASCIIStringEncoding] , "png", "FONTS" ) ),
            font_target_path( CORE_FILESYSTEM_PATH::FindFilePath( [fontNameTextValue cStringUsingEncoding:NSASCIIStringEncoding], "fxb", "FONTS" ) );
        
        descriptor.color[0] = 255;
        descriptor.color[1] = 255;
        descriptor.color[2] = 255;
        descriptor.color[3] = 255;
        
        int string_size = strlen( " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789&é\"'\(§è!çà)-" );
        char * string = (char *) CORE_MEMORY_ALLOCATOR_Allocate (string_size);
        memcpy(string, " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789&é\"'\(§è!çà)-", string_size );
        
        descriptor.CharacterSet.resize( string_size );
        
        for (int i = 0; i < string_size; i++ ) {
            
            descriptor.CharacterSet[ i ] = string[i];
        }
        
        NSString * filename = [NSString stringWithFormat:@"/Library/Fonts/"];
        filename = [filename stringByAppendingString:[[self.SelectedFont selectedItem] title] ];
        
        editor.CompileFont(512, 512, [filename cStringUsingEncoding:NSASCIIStringEncoding], descriptor, image_target_path, font_target_path );
    }
    
}
- (IBAction)SearchForFontAction:(id)sender {
    
    NSString * font_name = [NSString stringWithFormat:[self.FontName stringValue]];
    
    NSArray * dirs = [[NSFileManager defaultManager] contentsOfDirectoryAtPath:@"/Library/Fonts" error:nil];
    
    NSArray * fonts = [dirs filteredArrayUsingPredicate:[NSPredicate predicateWithFormat:@"self contains[cd] %@", font_name ]];
    
    [self.SelectedFontMenu removeAllItems];
    
    for (NSString * string in fonts) {
        
        NSMenuItem * item  =[[NSMenuItem alloc] initWithTitle:string action:nil keyEquivalent:string];
        [self.SelectedFontMenu addItem:item];
    }
}
- (IBAction)OnSelectedSizeAction:(id)sender {
}

@end

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
#import "CustomUITableCell.h"
#import "CppUIDataProxy.h"
#import "CreateItemViewController.h"

@implementation LeftPaneViewController {
    CppUIDataProxy * selectedItem;
}

-(void)viewDidLoad
{
    [super viewDidLoad];
    
    self.Menu.delegate = self;
    
    self.OutlineView.delegate = self;
    self.OutlineView.dataSource = self;
    
    selectedItem = NULL;
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(onObjectCollectionChanged) name:@CREATE_OBJECT_NOTIFICATION object:nil];
}
- (IBAction)LoadAtlas:(id)sender {
    
    // Create the File Open Dialog class.
    NSOpenPanel* openDlg = [NSOpenPanel openPanel];
    
    // Enable the selection of files in the dialog.
    [openDlg setCanChooseFiles:YES];
    [openDlg setTitle:@"Select your atlas file"];
    
    // Enable the selection of directories in the dialog.
    [openDlg setCanChooseDirectories:NO];
    
    // Display the dialog.  If the OK button was pressed,
    // process the files.
    
    
    
    if ( [openDlg runModal] == NSModalResponseOK )
    {
        // Get an array containing the full filenames of all
        // files and directories selected.
        NSArray* files = [openDlg filenames];
        
        NSString * filenameWithoutExtensions = [[files objectAtIndex:0] stringByReplacingOccurrencesOfString:@".iax" withString:@""];
        filenameWithoutExtensions = [filenameWithoutExtensions stringByReplacingOccurrencesOfString:@".png" withString:@""];
        
        auto editor = ((ASSET_EDITOR*) &CORE_APPLICATION::GetApplicationInstance());
        int size = 0;
        
        if ( editor != NULL ) {
            auto screen = &editor->GetGUIView();
            screen->LoadAtlas([[filenameWithoutExtensions stringByAppendingString:@".iax"] cStringUsingEncoding:NSASCIIStringEncoding], [[filenameWithoutExtensions stringByAppendingString:@".png"] cStringUsingEncoding:NSASCIIStringEncoding]);
        }
    }
}
- (IBAction)LoadFontButtonClicked:(id)sender {
    
    // Create the File Open Dialog class.
    NSOpenPanel* openDlg = [NSOpenPanel openPanel];
    
    // Enable the selection of files in the dialog.
    [openDlg setCanChooseFiles:YES];
    [openDlg setTitle:@"Select your font file"];
    
    // Enable the selection of directories in the dialog.
    [openDlg setCanChooseDirectories:NO];
    
    // Display the dialog.  If the OK button was pressed,
    // process the files.
    
    if ( [openDlg runModal] == NSModalResponseOK )
    {
        // Get an array containing the full filenames of all
        // files and directories selected.
        NSArray* files = [openDlg filenames];
        
        NSString * filenameWithoutExtensions = [[files objectAtIndex:0] stringByReplacingOccurrencesOfString:@".fxb" withString:@""];
        filenameWithoutExtensions = [filenameWithoutExtensions stringByReplacingOccurrencesOfString:@".png" withString:@""];
        
        auto editor = ((ASSET_EDITOR*) &CORE_APPLICATION::GetApplicationInstance());
        
        if ( editor != NULL ) {
            auto screen = &editor->GetGUIView();
            
            screen->LoadFont([[filenameWithoutExtensions stringByAppendingString:@".fxb"] cStringUsingEncoding:NSASCIIStringEncoding], [[filenameWithoutExtensions stringByAppendingString:@".png"] cStringUsingEncoding:NSASCIIStringEncoding]);
        }
    }
}

- (IBAction)CreateAtlas:(id)sender {
    
    [self performSegueWithIdentifier:@ATLAS_CREATION_SEGUE sender:self];
}

- (IBAction)CreateItemButtonClicked:(id)sender {
    
    [self performSegueWithIdentifier:@"XSCreateGUIItem" sender:self];
}
- (IBAction)CreateFontButtonClicked:(id)sender {
    
    [self performSegueWithIdentifier:@"ShowCreateFontScreen" sender:self];
}

-(void)prepareForSegue:(NSStoryboardSegue *)segue sender:(id)sender {
    
    if ( [[segue identifier] isEqualToString:@"XSCreateGUIItem" ]) {
        CreateItemViewController * iv = [segue destinationController];
        
        iv.Parent = (GRAPHIC_UI_FRAME * ) selectedItem.Element;
    }
}

- (IBAction)DeleteItemButtonClicked:(id)sender {
    
    CppUIDataProxy * proxy = [self.OutlineView itemAtRow:[self.OutlineView selectedRow]];
    
    selectedItem = [self.OutlineView itemAtRow:[self.OutlineView selectedRow]];
    
    CppUIDataProxy * proxyParent  = [self.OutlineView parentForItem:selectedItem];
    
    if ( proxy != nil && proxyParent != nil) {
        
        auto editor = ((ASSET_EDITOR*) &CORE_APPLICATION::GetApplicationInstance());
        
        if ( editor == NULL ) {
            
            return;
        }
        
        GRAPHIC_UI_FRAME * f = (GRAPHIC_UI_FRAME * ) proxyParent.Element;
        
        f->RemoveObject( selectedItem.Element );
    }
    
    [self.OutlineView reloadData];
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

-(void) onObjectCollectionChanged {

    [self.OutlineView reloadData];
    selectedItem = NULL;
    
}
-(BOOL)outlineView:(NSOutlineView *)outlineView isItemExpandable:(id)item {
    
    CppUIDataProxy * itemProxy = item;
    
    GRAPHIC_UI_ELEMENT * element = itemProxy.Element;
    
    if ( element == NULL ) {
        return NO;
    }
    
    return element->GetChildCount() >= 0;
}

-(NSInteger)outlineView:(NSOutlineView *)outlineView numberOfChildrenOfItem:(id)item {
    
    if ( item != nil ) {
        
        CppUIDataProxy * itemProxy = item;
        
        GRAPHIC_UI_ELEMENT * element = itemProxy.Element;
        
        if ( element == NULL ) {
            return 0;
        }
        
        int cc = element->GetChildCount();
        
        if ( cc < 0 ) {
            cc = 0;
        }
        
        return cc;
    }
    else {
        return 1;
    }
}

-(void)outlineView:(NSOutlineView *)outlineView setObjectValue:(id)object forTableColumn:(NSTableColumn *)tableColumn byItem:(id)item {
    
    NSInteger col = [[outlineView tableColumns ] indexOfObject:tableColumn];
    
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
    itemProxy.Element->GetPlacement().SetRelativePosition( position );
}

-(id)outlineView:(NSOutlineView *)outlineView child:(NSInteger)index ofItem:(id)item {
    
    CppUIDataProxy * proxy = [[CppUIDataProxy alloc] init];
    
    proxy.Element = NULL;
    
    if ( item == nil ) {

        auto editor = ((ASSET_EDITOR*) &CORE_APPLICATION::GetApplicationInstance());
        
        if ( editor == NULL ) {
            
            return proxy;
        }
        
        auto view = &editor->GetGUIView();
        
        proxy.Element = view;
    }
    else {
        CppUIDataProxy * itemProxy = item;
        
        GRAPHIC_UI_FRAME * element = (GRAPHIC_UI_FRAME *) itemProxy.Element;
        
        proxy.Element = element->GetObjectAtIndex( index );
    }
    
    return proxy;
}

-(id)outlineView:(NSOutlineView *)outlineView objectValueForTableColumn:(NSTableColumn *)tableColumn byItem:(id)item {
    
    CppUIDataProxy * proxy = item;
    
    if ( proxy.Element == NULL )
        return @"";
    
    NSInteger col = [[outlineView tableColumns ] indexOfObject:tableColumn];
    
    switch (col) {
        case 0:
            
            return [NSString stringWithFormat:@"%s", proxy.Element->GetIdentifier().GetTextValue()];
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
    }
}

-(void)outlineViewSelectionDidChange:(NSNotification *)notification {
    
    CppUIDataProxy * proxy = [self.OutlineView itemAtRow:[self.OutlineView selectedRow]];
    
    if ( proxy.Element != NULL && proxy.Element->GetChildCount() >= 0) {
        
        selectedItem = [self.OutlineView itemAtRow:[self.OutlineView selectedRow]];
    }
}
@end

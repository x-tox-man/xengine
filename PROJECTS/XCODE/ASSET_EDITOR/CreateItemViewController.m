//
//  CreateItemViewController.m
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 3/04/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#import "CreateItemViewController.h"
#import "ASSET_EDITOR.h"
#import "GRAPHIC_UI_RENDER_STYLE.h"
#import "GRAPHIC_UI_RENDER_STYLE.h"
#import "ASSET_SCREEN.h"
#import "GRAPHIC_SHADER_EFFECT_LOADER.h"
#import "CORE_PARALLEL.h"
#import "Constants.h"

@implementation CreateItemViewController

-(void)viewDidLoad {
    [super viewDidLoad];
    
    self.TableView.delegate  = self;
    self.TableView.dataSource = self;
    
    [[NSColorPanel sharedColorPanel] setShowsAlpha:YES];
    
    [NSColor setIgnoresAlpha:NO];
}

-(void)viewWillAppear {
    [self.ColorWell setColor:[NSColor whiteColor]];
    [self.ColorWell setAlphaValue:1.0f];
}

-(NSInteger)numberOfRowsInTableView:(NSTableView *)tableView {
    
    auto editor = ((ASSET_EDITOR*) &CORE_APPLICATION::GetApplicationInstance());
    
    if ( editor != NULL ) {
        auto screen = &editor->GetGUIView();
        
        auto tb_table = &screen->GetAtlas().GetTextureBlockTable();
        
        return tb_table->size();
    }
    
    return 0;
}

- (id)tableView:(NSTableView *)tableView objectValueForTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row {
    auto editor = ((ASSET_EDITOR*) &CORE_APPLICATION::GetApplicationInstance());
    
    if ( editor != NULL ) {
        auto screen = &editor->GetGUIView();
        
        auto tb_table = &screen->GetAtlas().GetTextureBlockTable();
        
        std::map< CORE_HELPERS_UNIQUE_IDENTIFIER , GRAPHIC_TEXTURE_BLOCK >::iterator it = tb_table->begin();
        
        int i = 0;
        while (it != tb_table->end() ) {
            
            if ( i == row ) {
                
                return [NSString stringWithFormat:@"%s", it->first.GetIdentifier()];
                break;
            }
            i++;
            it++;
        }
    }
    
    return @"";
}

-(void)tableViewSelectionDidChange:(NSNotification *)notification {
    
    
}

- (IBAction)CancelButtonClicked:(id)sender {
    
    [self dismissViewController:self];
}

- (IBAction)CreateTextButtonClicked:(id)sender {
    
    int anchor;
    NSString * title = [[self.PopupMenu selectedItem] title];
    
    auto editor = ((ASSET_EDITOR*) &CORE_APPLICATION::GetApplicationInstance());
    int size = 0;
    
    if ( editor != NULL && [[self.ObjectIdentifierTextField stringValue] length]) {
        auto screen = &editor->GetGUIView();
        
        if ( screen->GetFont().GetSize() == 0 ) {
            return;
        }
    }
    else {
        return;
    }
    
    if ( [title isEqualToString:@"Top"]) {
        anchor = GRAPHIC_UI_Top;
    }
    else if ( [title isEqualToString:@"TopRight"]) {
        anchor = GRAPHIC_UI_TopRight;
    }
    else if ( [title isEqualToString:@"TopLeft"]) {
        anchor = GRAPHIC_UI_TopLeft;
    }
    else if ( [title isEqualToString:@"Left"]) {
        anchor = GRAPHIC_UI_Left;
    }
    else if ( [title isEqualToString:@"BottomLeft"]) {
        anchor = GRAPHIC_UI_BottomLeft;
    }
    else if ( [title isEqualToString:@"BottomRight"]) {
        anchor = GRAPHIC_UI_BottomRight;
    }
    else if ( [title isEqualToString:@"Right"]) {
        anchor = GRAPHIC_UI_Right;
    }
    else if ( [title isEqualToString:@"Bottom"]) {
        anchor = GRAPHIC_UI_Bottom;
    }
    else {
        anchor = GRAPHIC_UI_Center;
    }
    
    auto app = ( ( ASSET_EDITOR * ) & CORE_APPLICATION::GetApplicationInstance() );
    
    CORE_PARALLEL_TASK_SYNCHRONIZE_WITH_MUTEX( GRAPHIC_SYSTEM::GraphicSystemLock )
        CORE_APPLICATION::GetApplicationInstance().GetApplicationWindow().EnableBackgroundContext(true);
        auto item = app->CreateUIText( "test", "testtest", CORE_MATH_VECTOR( 0.0f, 0.0f ), CORE_MATH_VECTOR( 1.0f, 1.0f ), anchor, self.Parent );
    
        CORE_APPLICATION::GetApplicationInstance().GetApplicationWindow().EnableBackgroundContext(false);
    CORE_PARALLEL_TASK_SYNCHRONIZE_WITH_MUTEX_END()
    
    [self dismissViewController:self];
    
    //Send notification
    
    [[NSNotificationCenter defaultCenter] postNotificationName:@CREATE_OBJECT_NOTIFICATION object:nil];
}

- (IBAction)CreateButtonCkicked:(id)sender {
    
    auto app = ( ( ASSET_EDITOR * ) & CORE_APPLICATION::GetApplicationInstance() );
    
    if ( [[self.ObjectIdentifierTextField stringValue] length] == 0 ) {
        
        return;
    }
    
    NSString * title = [[self.PopupMenu selectedItem] title];
    
    int anchor;
    if ( [title isEqualToString:@"Top"]) {
        anchor = GRAPHIC_UI_Top;
    }
    else if ( [title isEqualToString:@"TopRight"]) {
        anchor = GRAPHIC_UI_TopRight;
    }
    else if ( [title isEqualToString:@"TopLeft"]) {
        anchor = GRAPHIC_UI_TopLeft;
    }
    else if ( [title isEqualToString:@"Left"]) {
        anchor = GRAPHIC_UI_Left;
    }
    else if ( [title isEqualToString:@"BottomLeft"]) {
        anchor = GRAPHIC_UI_BottomLeft;
    }
    else if ( [title isEqualToString:@"BottomRight"]) {
        anchor = GRAPHIC_UI_BottomRight;
    }
    else if ( [title isEqualToString:@"Right"]) {
        anchor = GRAPHIC_UI_Right;
    }
    else if ( [title isEqualToString:@"Bottom"]) {
        anchor = GRAPHIC_UI_Bottom;
    }
    else {
        anchor = GRAPHIC_UI_Center;
    }
    
    CORE_PARALLEL_TASK_SYNCHRONIZE_WITH_MUTEX( GRAPHIC_SYSTEM::GraphicSystemLock )
        CORE_APPLICATION::GetApplicationInstance().GetApplicationWindow().EnableBackgroundContext(true);
        auto item = app->CreateUIItem( [[self.ObjectIdentifierTextField stringValue] cStringUsingEncoding:NSASCIIStringEncoding], CORE_MATH_VECTOR( 0.0f, 0.0f ), CORE_MATH_VECTOR( 128.0f, 128.0f ), anchor, self.Parent );
        
        auto render_style = new GRAPHIC_UI_RENDER_STYLE;
    GRAPHIC_TEXTURE_BLOCK * tb;
    
        GRAPHIC_SHADER_EFFECT::PTR ui_textured_shader_effect = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::UIShader"), CORE_FILESYSTEM_PATH::FindFilePath( "UIShaderTextured" , "vsh", "OPENGL2" ) );
    
    
        ui_textured_shader_effect->Initialize(GRAPHIC_SHADER_BIND_PositionNormalTexture);
    
        auto editor = ((ASSET_EDITOR*) &CORE_APPLICATION::GetApplicationInstance());
        
        if ( editor != NULL ) {
            auto screen = &editor->GetGUIView();
            
            auto tb_table = &screen->GetAtlas().GetTextureBlockTable();
            
            std::map< CORE_HELPERS_UNIQUE_IDENTIFIER , GRAPHIC_TEXTURE_BLOCK >::iterator it = tb_table->begin();
            
            int i = 0;
            while (it != tb_table->end() ) {
                
                if ( i == [self.TableView selectedRow] ) {
                    
                    tb = &it->second;
                    break;
                }
                i++;
                it++;
            }
        }
        
    
        GRAPHIC_MATERIAL * material = new GRAPHIC_MATERIAL;
        material->SetTexture(GRAPHIC_SHADER_PROGRAM::ColorTexture, tb);
    
        ui_textured_shader_effect->SetMaterial( material );
    
        render_style->SetShape( ASSET_SCREEN::CreateUIPlanShape( ui_textured_shader_effect ) );
        render_style->SetEffect( ui_textured_shader_effect );
        render_style->SetColor( CORE_COLOR_White );
        
        item->SetRenderStyleForState( GRAPHIC_UI_ELEMENT_STATE_Default, render_style );
        CORE_APPLICATION::GetApplicationInstance().GetApplicationWindow().EnableBackgroundContext(false);
    CORE_PARALLEL_TASK_SYNCHRONIZE_WITH_MUTEX_END()
    
    [self dismissViewController:self];
    
    //Send notification
    
    [[NSNotificationCenter defaultCenter] postNotificationName:@CREATE_OBJECT_NOTIFICATION object:nil];
}

- (IBAction)OnMenuItemChanged:(id)sender {
    
}


- (IBAction)CreateContainerAction:(id)sender {
    
    auto app = ( ( ASSET_EDITOR * ) & CORE_APPLICATION::GetApplicationInstance() );
    
    if ( [[self.ObjectIdentifierTextField stringValue] length] == 0 ) {
        
        return;
    }
    
    NSString * title = [[self.PopupMenu selectedItem] title];
    
    int anchor;
    if ( [title isEqualToString:@"Top"]) {
        anchor = GRAPHIC_UI_Top;
    }
    else if ( [title isEqualToString:@"TopRight"]) {
        anchor = GRAPHIC_UI_TopRight;
    }
    else if ( [title isEqualToString:@"TopLeft"]) {
        anchor = GRAPHIC_UI_TopLeft;
    }
    else if ( [title isEqualToString:@"Left"]) {
        anchor = GRAPHIC_UI_Left;
    }
    else if ( [title isEqualToString:@"BottomLeft"]) {
        anchor = GRAPHIC_UI_BottomLeft;
    }
    else if ( [title isEqualToString:@"BottomRight"]) {
        anchor = GRAPHIC_UI_BottomRight;
    }
    else if ( [title isEqualToString:@"Right"]) {
        anchor = GRAPHIC_UI_Right;
    }
    else if ( [title isEqualToString:@"Bottom"]) {
        anchor = GRAPHIC_UI_Bottom;
    }
    else {
        anchor = GRAPHIC_UI_Center;
    }
    
    CORE_PARALLEL_TASK_SYNCHRONIZE_WITH_MUTEX( GRAPHIC_SYSTEM::GraphicSystemLock )
        CORE_APPLICATION::GetApplicationInstance().GetApplicationWindow().EnableBackgroundContext(true);
            app->CreateUIFrame( [[self.ObjectIdentifierTextField stringValue] cStringUsingEncoding:NSASCIIStringEncoding], CORE_MATH_VECTOR( 0.0f, 0.0f ), CORE_MATH_VECTOR( 128.0f, 128.0f ), anchor, self.Parent );
        CORE_APPLICATION::GetApplicationInstance().GetApplicationWindow().EnableBackgroundContext(false);
    CORE_PARALLEL_TASK_SYNCHRONIZE_WITH_MUTEX_END()
    
    [self dismissViewController:self];
    
    //Send notification
    
    [[NSNotificationCenter defaultCenter] postNotificationName:@CREATE_OBJECT_NOTIFICATION object:nil];
}
@end

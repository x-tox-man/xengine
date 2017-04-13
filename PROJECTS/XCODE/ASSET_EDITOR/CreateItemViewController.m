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

- (instancetype)init
{
    self = [super init];
    
    if (self) {
        
        self.Source = [[ItemTableViewSource alloc] init];
        self.Delegate = [[ItemTableViewDelegate alloc] init];
        
        self.TableView.delegate  = self.Delegate;
        self.TableView.dataSource = self.Source;
    }
    
    return self;
}

- (IBAction)CancelButtonClicked:(id)sender {
    
    [self dismissViewController:self];
}

- (IBAction)CreateButtonCkicked:(id)sender {
    
    auto app = ( ( ASSET_EDITOR * ) & CORE_APPLICATION::GetApplicationInstance() );
    
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
        auto item = app->CreateItem( "test", CORE_MATH_VECTOR( 0.0f, 0.0f ), CORE_MATH_VECTOR( 128.0f, 128.0f ), anchor );
        
        auto render_style = new GRAPHIC_UI_RENDER_STYLE;
        auto tb = new GRAPHIC_TEXTURE_BLOCK;
        GRAPHIC_SHADER_EFFECT::PTR ui_textured_shader_effect = GRAPHIC_SHADER_EFFECT::LoadResourceForPath(CORE_HELPERS_UNIQUE_IDENTIFIER( "SHADER::UIShader"), CORE_FILESYSTEM_PATH::FindFilePath( "UIShaderTextured" , "vsh", "OPENGL2" ) );
    
    
        ui_textured_shader_effect->Initialize(GRAPHIC_SHADER_BIND_PositionNormalTexture);
        
        
        tb->SetTexture( ASSET_SCREEN::CreateTextureFromImagePath("fireButton") );
        tb->Initialize();
        
        render_style->SetShape( ASSET_SCREEN::CreateUIPlanShape( ui_textured_shader_effect ) );
        render_style->SetTextureBlock( tb );
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


@end

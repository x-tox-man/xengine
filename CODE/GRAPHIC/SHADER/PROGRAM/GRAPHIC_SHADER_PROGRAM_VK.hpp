#ifndef __GAME_ENGINE_REBORN__GRAPHIC_SHADER_PROGRAM_VK__
#define __GAME_ENGINE_REBORN__GRAPHIC_SHADER_PROGRAM_VK__

    #if X_VK
        void LinkTogether( const GRAPHIC_SHADER_BIND shader_bind );
        void BindAttribute( GRAPHIC_SHADER_ATTRIBUTE & shader_attribute, CORE_HELPERS_IDENTIFIER & identifier );

        bool ValidateProgram();
        bool LinkProgram();

    #endif

#endif
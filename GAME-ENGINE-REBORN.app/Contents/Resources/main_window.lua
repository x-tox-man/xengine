
print ( "Main Window Init" )

local AnimatedElementTable = {}
local end_screen = false
local pos = CORE_MATH_VECTOR:new()
local animation = {}
local ellapsed_time = 0.0
local start_screen = false

function Setup( UI_Frame )

    print ( "Setup" )

    animation["Element"] = UI_Frame
    animation["Width"] = 0.0
    animation["Height"] = 0.0

    table.insert( AnimatedElementTable, animation )

    print( getmetatable( GRAPHIC_UI_ELEMENT ) )

    local callback = CORE_ABSTRACT_PROGRAM_LUA_HELPERS:CreateLuaCallback( "OnAction" )

    GRAPHIC_UI_SYSTEM:GetInstance():GetCurrentScreen():GetElement( "MW:start_lobby_button" ):SetActionCallback( callback )

    GRAPHIC_UI_SYSTEM:GetInstance():GetCurrentScreen():GetElement( "MW:second_text" ):SetTextValue( "tentative deux troix mots\net passer a la ligne" )
end

function update( time_step )

    print( "update" )
    print ( time_step )
    print ( ellapsed_time )
    print ( end_screen )

    if end_screen == true and ellapsed_time < 1.0 then

        ellapsed_time = ellapsed_time + time_step

        UpdateExitScreen( ellapsed_time )

        if ellapsed_time > 1.0 then 

            start_screen = true
            end_screen = false
            ellapsed_time = 0.0
        end
    elseif start_screen == true and ellapsed_time < 1.0 then

        ellapsed_time = ellapsed_time + time_step

        UpdateEnterScreen( ellapsed_time )

        if ellapsed_time > 1.0 then 

            start_screen = false
            ellapsed_time = 0.0
        end
    end
end

function OnAction( element, state )

    print( "OnAction" )

    if end_screen == false and state == 1 then

        AUDIO_SYSTEM:GetInstance():PlaySound( "ElectricSound" )

        end_screen = true
        ellapsed_time = 0.0
    end
end

function UpdateEnterScreen( time )

    pos:X( -1024.0/2 * (math.cos(math.pi * time) - 1.0) - 1024.0 )
    pos:Y( 0/2 * (math.cos(math.pi * time) - 1.0) + animation["Height"] )
    animation["Element"]:SetPosition( pos )
end

function UpdateExitScreen( time )

    pos:X( 1024.0/2 * (math.cos(math.pi * time) - 1.0) + animation["Width"] )
    pos:Y( 0/2 * (math.cos(math.pi * time) - 1.0) + animation["Height"] )
    animation["Element"]:SetPosition( pos )
end

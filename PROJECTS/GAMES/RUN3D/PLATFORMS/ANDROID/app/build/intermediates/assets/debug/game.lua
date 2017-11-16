-- require "other.lua"

-- io.write("test excellent ")

--print(getmetatable(ScriptEntity))

-- for k, v in pairs( _G ) do
--print ( "global key" , k , "value", v )
-- end

b = ScriptEntity:new()

-- print( getmetatable( b ) )

-- b:mySuperScriptMethod()

-- b:mySuperScriptMethodWithParameter( "kegf" )

--AUDIO_SYSTEM:GetInstance():PlayMusic( "RammsteinSound" )
-- AUDIO_SYSTEM:GetInstance():PlaySound( "ElectricSound" )

frame = GRAPHIC_UI_SYSTEM:GetInstance():GetCurrentScreen()

print( getmetatable( frame ) )
print( "getmetatable( frame )" )

-- element = frame:GetElement( "APPLICATION_MAIN_WINDOW::start_lobby_button" )
-- element:SetPosition( math.random(1, 99) * 1.0, math.random(1, 99) * 1.0)

ScriptEntity:Ping()
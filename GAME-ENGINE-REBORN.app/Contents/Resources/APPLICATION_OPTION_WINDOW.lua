
function Setup( UI_Element )

    elem = GRAPHIC_UI_HELPER:CreateElement( "OW:BaseElement" )
UI_Element:AddObject( elem )

    pos = CORE_MATH_VECTOR:new()

    print (elem )
    print ( pos )

    pos:X( 100.0 )
    pos:Y( 100.0 )

    elem:SetPosition( pos )

    print ( UI_Element )
end

function Update( ellapsed_time )

end
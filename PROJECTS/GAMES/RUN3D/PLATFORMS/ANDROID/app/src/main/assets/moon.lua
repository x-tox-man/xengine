posZ = 0.0
posX = 0.0
posY = 0.0

print( "init script")

function Update( object_parameter )
	
	comp_pos = object_parameter:GetComponentPosition()

	ori = comp_pos:GetOrientation()
	pos = comp_pos:GetPosition()

	ori:RotateZ( 0.002 )

	pos:X( 500.0 )
	pos:Y( -400.0 )
	pos:Z( 100.0 )

	comp_pos:SetOrientation( ori )
	comp_pos:SetPosition( pos )
end



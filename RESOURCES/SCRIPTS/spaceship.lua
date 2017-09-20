posZ = 0.0
posX = 0.0

function Update( object_parameter )
	
	comp_pos = object_parameter:GetComponentPosition()
	comp_phys = object_parameter:GetComponentPhysics()
	
	pos = comp_pos:GetPosition()

	
	if PERIPHERIC_INTERACTION_SYSTEM:GetInstance():GetKeyboard():IsKeyPressed( 13 ) then

		posZ = posZ + 5.0 * 0.033

		--pos:Y( posZ )
	end

	if PERIPHERIC_INTERACTION_SYSTEM:GetInstance():GetKeyboard():IsKeyPressed( 14 ) then

		posZ = posZ - 5.0 * 0.033

		--pos:Y( posZ )
	end

	if PERIPHERIC_INTERACTION_SYSTEM:GetInstance():GetKeyboard():IsKeyPressed( 15 ) then

		posX = posX + 5.0 * 0.033

		--pos:Z( posX )

	end
	if PERIPHERIC_INTERACTION_SYSTEM:GetInstance():GetKeyboard():IsKeyPressed( 16 ) then

		posX = posX - 5.0 * 0.033

		--pos:Z( posX )
	end

	posZ = math.min( posZ, 10 )
	posX = math.min( posX, 10 )

	vv = CORE_MATH_VECTOR:new()
	vv:X( posX)
	vv:Y( posZ)

	print( vv:GetX() )
	--comp_phys:SetVelocity( vv )

end

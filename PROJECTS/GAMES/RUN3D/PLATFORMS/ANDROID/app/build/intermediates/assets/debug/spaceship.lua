posZ = 0.0
posX = 0.0

function Update( object_parameter )
	
	comp_pos = object_parameter:GetComponentPosition()
	comp_phys = object_parameter:GetComponentPhysics()
	
	pos = comp_pos:GetPosition()
	vel = comp_phys:GetVelocity()
	ori = comp_pos:GetOrientation()

	
	if PERIPHERIC_INTERACTION_SYSTEM:GetInstance():GetKeyboard():IsKeyPressed( 13 ) then

		vel:Y( vel:GetY()  + 5.0 * 0.033 )

		--pos:Y( posZ )

		comp_phys:SetVelocity( vel )
	end

	if PERIPHERIC_INTERACTION_SYSTEM:GetInstance():GetKeyboard():IsKeyPressed( 14 ) then

		vel:Y( vel:GetY()  - 5.0 * 0.033 )

		--pos:Y( posZ )

		comp_phys:SetVelocity( vel )
	end

	if PERIPHERIC_INTERACTION_SYSTEM:GetInstance():GetKeyboard():IsKeyPressed( 15 ) then

		vel:X( vel:GetX()  + 5.0 * 0.033 )

		--pos:Z( posX )

		comp_phys:SetVelocity( vel )

	end
	if PERIPHERIC_INTERACTION_SYSTEM:GetInstance():GetKeyboard():IsKeyPressed( 16 ) then

		vel:X( vel:GetX()  - 5.0 * 0.033 )

		--pos:Z( posX )

		comp_phys:SetVelocity( vel )
	end

	-- G touch
	if PERIPHERIC_INTERACTION_SYSTEM:GetInstance():GetKeyboard():IsKeyPressed( 17 ) then

		
		ori:RotateY( math.pi * 0.033 )

		--pos:Y( posZ )

		object_parameter:SetOrientation( ori );
	end

end


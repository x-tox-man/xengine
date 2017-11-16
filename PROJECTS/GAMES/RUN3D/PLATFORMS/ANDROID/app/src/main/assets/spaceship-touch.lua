
function Update( object_parameter )

	comp_pos = object_parameter:GetComponentPosition()
	comp_phys = object_parameter:GetComponentPhysics()
	
	pos = comp_pos:GetPosition()
	vel = comp_phys:GetVelocity()
	ori = comp_pos:GetOrientation()

	x = PERIPHERIC_INTERACTION_SYSTEM:GetInstance():GetTouch():GetX()

	vel:Y( vel:GetY() + x * 0.033 )

	comp_phys:SetVelocity( vel )
end

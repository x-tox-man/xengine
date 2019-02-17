function init()

	vec = CORE_MATH_VECTOR:new()
	rot = CORE_MATH_QUATERNION:new()
	vec:Y( 0.0 )
	vec:Z( 0.5 )
	base = R3D_LEVEL_HELPER:Create( "flat", vec )
	base_cp = R3D_LEVEL_HELPER:Create( "checkpoint", vec )
	base_capsule = R3D_LEVEL_HELPER:Create( "capsule", vec )
	turn = R3D_LEVEL_HELPER:Create( "turn", vec )

	vec:Y( -1.0 )
	for i= 0, 20, 1 do
		vec:Z( vec:GetZ() + 1.0 )
		base:SetPosition( vec )
		
		track = R3D_LEVEL_HELPER:Clone( base )
		R3D_LEVEL_HELPER:AddToSystemRenderAndPhysics( track )
	end

	vec:X( -1.0 )
	for i= 0, 20, 1 do
		vec:X( vec:GetX() + 1.0 )
		base:SetPosition( vec )
		
		track = R3D_LEVEL_HELPER:Clone( base )
		R3D_LEVEL_HELPER:AddToSystemRenderAndPhysics( track )
	end

	vec:Z( -1.0 )
	for i= 0, 20, 1 do
		vec:Z( vec:GetZ() + 1.0 )
		base:SetPosition( vec )
		
		track = R3D_LEVEL_HELPER:Clone( base )
		R3D_LEVEL_HELPER:AddToSystemRenderAndPhysics( track )
	end

	vec:X( 0.1 )
	vec:Y( 0.1 )
	vec:Z( 0.6 )
	
	base:SetPosition( vec )
		
	track = R3D_LEVEL_HELPER:Clone( base )
	R3D_LEVEL_HELPER:AddToSystemRenderAndPhysics( track )	
	
end	

init()
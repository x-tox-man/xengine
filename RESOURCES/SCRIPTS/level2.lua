
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
		vec:Y( vec:GetY() + 1.0 )
		base:SetPosition( vec )
		
		track = R3D_LEVEL_HELPER:Clone( base )
		R3D_LEVEL_HELPER:AddToSystemRenderAndPhysics( track )
	end

	rot:RotateZ( -math.pi * 0.5 )

	vec:Y( vec:GetY() + 1.0 )
	turn:SetPosition( vec )
	--turn:SetOrientation( rot )

	track = R3D_LEVEL_HELPER:Clone( turn )
	R3D_LEVEL_HELPER:AddToSystemRenderAndPhysics( track )

	base:SetOrientation( rot )
	vec:X( vec:GetX() + 1.0 )
	vec:Y( vec:GetY() + 1.0 )

	for i= 0, 0, 1 do
		vec:X( vec:GetX() + 1.0 )
		base:SetPosition( vec )	
		
		track = R3D_LEVEL_HELPER:Clone( base )
		R3D_LEVEL_HELPER:AddToSystemRenderAndPhysics( track )
		track:SetOrientation( rot );
	end

	for i= 0, 5, 1 do
		vec:X( 0.1 + i * 0.2 )
		vec:Y( 0.0 )
		vec:Z( -0.2 + i * 0.1 )
		base:SetPosition( vec )	
		track = R3D_LEVEL_HELPER:Clone( base )

		R3D_LEVEL_HELPER:AddToSystemRender( track )
	end
end	

init()
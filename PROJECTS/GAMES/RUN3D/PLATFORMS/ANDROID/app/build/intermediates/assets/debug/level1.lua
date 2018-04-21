
function init()

	vec = CORE_MATH_VECTOR:new()
	vec:Y( 0.0 )
	vec:Z( 0.5 )
	base = R3D_LEVEL_HELPER:Create( "flat", vec )
	--base_cp = R3D_LEVEL_HELPER:Create( "flat", vec )
	--base_capsule = R3D_LEVEL_HELPER:Create( "flat", vec )

	for i= -1, 20, 1 do
		vec:Y( i * 1.0 )
		base:SetPosition( vec )
		
		track = R3D_LEVEL_HELPER:Clone( base )
		R3D_LEVEL_HELPER:AddToSystemRenderAndPhysics( track )
	end
end

init()
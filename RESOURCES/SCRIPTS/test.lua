print( "Lua execute" )
print(getmetatable(GAMEPLAY_COMPONENT))
print(getmetatable(GAMEPLAY_COMPONENT_POSITION))

function Update( object_parameter )
	print( "Update" )
	comp_pos = object_parameter:GetComponent(0)
	print (comp_pos )
	mt = getmetatable( GAMEPLAY_COMPONENT_POSITION )
	print( mt )
	--setmetatable(comp_pos, mt)

	--print (comp_pos )
end
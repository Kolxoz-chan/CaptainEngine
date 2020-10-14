function Core:onSetup()
	-- Settings --
	Core.setProperty("fps", 60)
	set = Core.loadTileset("gamedata/tilesets/tileset_01.tsx", "TILED_TILESET_LOADER")
	set = Core.loadTilesetsForLevel("gamedata/tilesets/tileset_01.tsx", "TILED_TILESET_LOADER")
	print(set)

end

function Core:onClose()

	return true
end

function Core:onUpdate()
	
end
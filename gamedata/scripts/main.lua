require "class_maker"
require "player"

function Core:onSetup()
	-- Settings --
	Core.setProperty("window_size", Point(1280, 720))
	Core.setProperty("fps", 60)

	-- Resources loading --
	Core.loadTilesetsForLevel("gamedata/levels/test", "TILED_MANAGER")
	lvl = Core.loadLevel("gamedata/levels/test.tmx", "TILED_MANAGER")

	Core.setCurrentLevel(lvl)
end

function Core:onClose()

	return true
end

function Core:onUpdate()
	
end
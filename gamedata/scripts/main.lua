function Core:onSetup()
	-- Settings --
	Core.setProperty("fps", 60)

end

function Core:onClose()

	return true
end

function Core:onUpdate()
	print(Core.deltaTime)
end
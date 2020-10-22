Player = ClassMaker:newClass()

function Player:new()
	return ClassMaker:newObject(self, DrawableEntity())
end